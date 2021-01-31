
void extrnInitPerks()
{
    DeleteAttribute(&ChrPerksList, "list");
    // NPCOnly - ������ ���  PlayerOnly - ������ ��, Hiden - ����� ��� ����, ��������� ����� ������-���
    // navigator  boatswain  cannoner doctor carpenter treasurer fighter  - �������  ���  .OfficerType
    
    // ������ �� ��� -->
    //	Personal Skills Group
	//==========================================================
	ChrPerksList.list.BasicDefense.descr = "perkBasicDefense";
    ChrPerksList.list.BasicDefense.BaseType = "self"; // boal 05.05.04 ���� �������������

	ChrPerksList.list.AdvancedDefense.descr = "perkAdvancedDefense";
	ChrPerksList.list.AdvancedDefense.condition.BasicDefense = true;
    ChrPerksList.list.AdvancedDefense.BaseType = "self";

    ChrPerksList.list.Ciras.descr = "perkCiras";
	ChrPerksList.list.Ciras.condition.AdvancedDefense = true;
	ChrPerksList.list.Ciras.BaseType = "self";

    ChrPerksList.list.CriticalHit.descr = "perkCriticalHit";
    ChrPerksList.list.CriticalHit.BaseType = "self";
    
	ChrPerksList.list.HPPlus.descr = "perkHPPlus";
	ChrPerksList.list.HPPlus.BaseType = "self";
	ChrPerksList.list.HPPlus.condition.AdvancedDefense = true;
	ChrPerksList.list.HPPlus.NPCOnly = true;
	
	ChrPerksList.list.HPPlusFixed.descr = "perkHPPlusFixed";
	ChrPerksList.list.HPPlusFixed.BaseType = "self";
	ChrPerksList.list.HPPlusFixed.condition.AdvancedDefense = true;
	ChrPerksList.list.HPPlusFixed.PlayerOnly = true;
	
	ChrPerksList.list.HardHitter.descr = "perkHardHitter";
	ChrPerksList.list.HardHitter.BaseType = "self";
	
	ChrPerksList.list.Tireless.descr = "perkTireless";
	ChrPerksList.list.Tireless.BaseType = "self";
	
	ChrPerksList.list.Rush.descr = "perkRush";
	ChrPerksList.list.Rush.TimeDelay    = 70; // 10+60
	ChrPerksList.list.Rush.TimeDuration = 10;
	ChrPerksList.list.Rush.BaseType = "self";
	ChrPerksList.list.Rush.condition.Tireless     = true;
	ChrPerksList.list.Rush.condition.BasicDefense = true;
	ChrPerksList.list.Rush.PlayerOnly = true;
	
	ChrPerksList.list.EnergyPlus.descr = "perkEnergyPlus";
	ChrPerksList.list.EnergyPlus.BaseType = "self";
	ChrPerksList.list.EnergyPlus.condition.Tireless = true;
	ChrPerksList.list.EnergyPlus.NPCOnly = true;
	
	ChrPerksList.list.EnergyPlusFixed.descr = "perkEnergyPlusFixed";
	ChrPerksList.list.EnergyPlusFixed.BaseType = "self";
	ChrPerksList.list.EnergyPlusFixed.condition.Tireless = true;
	ChrPerksList.list.EnergyPlusFixed.PlayerOnly = true;
	
	ChrPerksList.list.Sliding.descr = "perkSliding";
	ChrPerksList.list.Sliding.condition.AdvancedDefense = true;
	ChrPerksList.list.Sliding.BaseType = "self";
	
	ChrPerksList.list.BladeDancer.descr = "perkBladeDancer";
	ChrPerksList.list.BladeDancer.condition.CriticalHit = true;
	ChrPerksList.list.BladeDancer.condition.AdvancedDefense = true;
	ChrPerksList.list.BladeDancer.BaseType = "self";
	
	ChrPerksList.list.SwordplayProfessional.descr = "perkSwordplayProfessional";
	ChrPerksList.list.SwordplayProfessional.condition.CriticalHit = true;
	ChrPerksList.list.SwordplayProfessional.condition.AdvancedDefense = true;
	ChrPerksList.list.SwordplayProfessional.condition.Tireless = true;
	ChrPerksList.list.SwordplayProfessional.BaseType = "self";
	
	ChrPerksList.list.AgileMan.descr = "perkAgileMan";
	ChrPerksList.list.AgileMan.condition.SwordplayProfessional = true;
	ChrPerksList.list.AgileMan.condition.GunProfessional = true;
	ChrPerksList.list.AgileMan.BaseType = "self";
	ChrPerksList.list.AgileMan.PlayerOnly = true;
	
	ChrPerksList.list.Buldozer.descr = "perkBuldozer";
	ChrPerksList.list.Buldozer.BaseType = "self";
	ChrPerksList.list.Buldozer.PlayerOnly = true;
	
	ChrPerksList.list.Gunman.descr = "perkGunman";
	ChrPerksList.list.Gunman.BaseType = "self";

	ChrPerksList.list.GunProfessional.descr = "perkGunProfessional";
	ChrPerksList.list.GunProfessional.condition.Gunman = true;
	ChrPerksList.list.GunProfessional.BaseType = "self";

	ChrPerksList.list.Grus.descr = "perkGrus";
	ChrPerksList.list.Grus.BaseType = "self";

 	ChrPerksList.list.Medic.descr = "perkMedic";
	ChrPerksList.list.Medic.condition.AdvancedDefense = true;
	ChrPerksList.list.Medic.BaseType = "self";
	ChrPerksList.list.Medic.PlayerOnly = true;
	
	ChrPerksList.list.ByWorker.descr = "perkByWorker";
	ChrPerksList.list.ByWorker.BaseType = "self";
	ChrPerksList.list.ByWorker.NPCOnly = true;
	
	ChrPerksList.list.ByWorker2.descr = "perkByWorker2";
	ChrPerksList.list.ByWorker2.BaseType = "self";
	ChrPerksList.list.ByWorker2.condition.ByWorker = true;
	ChrPerksList.list.ByWorker2.NPCOnly = true;

	ChrPerksList.list.SharedExperience.descr = "perkSharedExperience";
	ChrPerksList.list.SharedExperience.BaseType = "self";
	ChrPerksList.list.SharedExperience.PlayerOnly = true;

	ChrPerksList.list.IronWill.descr = "perkIronWill";
	ChrPerksList.list.IronWill.BaseType = "self";
	ChrPerksList.list.IronWill.OfficerType = "boatswain";

	ChrPerksList.list.ShipEscape.descr = "perkShipEscape";
	ChrPerksList.list.ShipEscape.condition.IronWill = true;
	ChrPerksList.list.ShipEscape.BaseType = "self";

	ChrPerksList.list.Trustworthy.descr = "perkTrustworthy";
	ChrPerksList.list.Trustworthy.condition.AdvancedCommerce = true;
	ChrPerksList.list.Trustworthy.condition.IronWill = true;
	ChrPerksList.list.Trustworthy.BaseType = "self";
	ChrPerksList.list.Trustworthy.PlayerOnly = true;
	
	ChrPerksList.list.UnlimitedContra.descr = "perkUnlimitedContra";
	ChrPerksList.list.UnlimitedContra.condition.Trustworthy = true;
	ChrPerksList.list.UnlimitedContra.condition.AboardCollector = true;
	ChrPerksList.list.UnlimitedContra.BaseType = "self";
	ChrPerksList.list.UnlimitedContra.PlayerOnly = true;
	
	ChrPerksList.list.AboardCollector.descr = "perkAboardCollector";
	ChrPerksList.list.AboardCollector.condition.Grus = true;
	ChrPerksList.list.AboardCollector.condition.GrapplingProfessional = true;
	ChrPerksList.list.AboardCollector.BaseType = "self";
	ChrPerksList.list.AboardCollector.PlayerOnly = true;
	
	/////////////////////////  ����������� /////////////////////////////////////
    /////////////////////////////////////////////////////////////
	/// ����� ��� ��
	/////////////////////////////////////////////////////////////
    ChrPerksList.list.FlagPir.descr = "perkFlagPir";   // ����� ��
    ChrPerksList.list.FlagPir.BaseType = "ship";
    ChrPerksList.list.FlagPir.PlayerOnly = true;

    ChrPerksList.list.FlagEng.descr = "perkFlagEng";
    ChrPerksList.list.FlagEng.BaseType = "ship";
    ChrPerksList.list.FlagEng.PlayerOnly = true;

    ChrPerksList.list.FlagFra.descr = "perkFlagFra";
    ChrPerksList.list.FlagFra.BaseType = "ship";
    ChrPerksList.list.FlagFra.PlayerOnly = true;

    ChrPerksList.list.FlagSpa.descr = "perkFlagSpa";
    ChrPerksList.list.FlagSpa.BaseType = "ship";
    ChrPerksList.list.FlagSpa.PlayerOnly = true;

    ChrPerksList.list.FlagHol.descr = "perkFlagHol";
    ChrPerksList.list.FlagHol.BaseType = "ship";
    ChrPerksList.list.FlagHol.PlayerOnly = true;
    
	//����� ���� ����� ����� ! //zagolski
 	ChrPerksList.list.SeaDogProfessional.descr = "perkSeaDogProfessional";
	ChrPerksList.list.SeaDogProfessional.condition.SailingProfessional = true;
	ChrPerksList.list.SeaDogProfessional.BaseType = "ship";
	ChrPerksList.list.SeaDogProfessional.PlayerOnly = true;
    
	/////////////////////////////////////////////////////////////
	/// ����� ��� ������
	/////////////////////////////////////////////////////////////
	ChrPerksList.list.Brander.descr = "perkBrander";  // ������
	ChrPerksList.list.Brander.BaseType = "ship";
	ChrPerksList.list.Brander.OfficerType = "boatswain";

	/*ChrPerksList.list.Aboard.descr = "perkAboard";
	ChrPerksList.list.Aboard.condition.Brander = true;
	ChrPerksList.list.Aboard.BaseType = "ship"; */ // ��� ������ ���� �����

	ChrPerksList.list.Troopers.descr = "perkTroopers";  // ������
	ChrPerksList.list.Troopers.BaseType = "ship";
	ChrPerksList.list.Troopers.OfficerType = "boatswain";
	
	ChrPerksList.list.LongRangeGrappling.descr = "perkLongRangeGrappling";  // ������
	ChrPerksList.list.LongRangeGrappling.BaseType = "ship";
    ChrPerksList.list.LongRangeGrappling.OfficerType = "boatswain";
    
	ChrPerksList.list.GrapplingProfessional.descr = "perkGrapplingProfessional";   // ������
	ChrPerksList.list.GrapplingProfessional.condition.LongRangeGrappling = true;
	ChrPerksList.list.GrapplingProfessional.condition.MusketsShoot = true;
	ChrPerksList.list.GrapplingProfessional.BaseType = "ship";
	ChrPerksList.list.GrapplingProfessional.OfficerType = "boatswain";
	
	ChrPerksList.list.MusketsShoot.descr = "perkMusketsShoot";     // ������
	ChrPerksList.list.MusketsShoot.condition.CrewDamageUp = true;
	ChrPerksList.list.MusketsShoot.BaseType = "ship";
	ChrPerksList.list.MusketsShoot.OfficerType = "boatswain";

    /////////////////////////////////////////////////////////////
	/// ����� ��� �������
	/////////////////////////////////////////////////////////////
	
	ChrPerksList.list.BasicCommerce.descr = "perkBasicCommerce";  // ��������
	ChrPerksList.list.BasicCommerce.BaseType = "ship";
	ChrPerksList.list.BasicCommerce.OfficerType = "treasurer";

	ChrPerksList.list.AdvancedCommerce.descr = "perkAdvancedCommerce";  // ��������
	ChrPerksList.list.AdvancedCommerce.condition.BasicCommerce = true;
	ChrPerksList.list.AdvancedCommerce.BaseType = "ship";
	ChrPerksList.list.AdvancedCommerce.OfficerType = "treasurer";

	/////////////////////////////////////////////////////////////
	/// ����� ��� �������
	/////////////////////////////////////////////////////////////
	ChrPerksList.list.FastReload.descr = "perkFastReload";  // �������
	ChrPerksList.list.FastReload.BaseType = "ship";
	ChrPerksList.list.FastReload.OfficerType = "cannoner";

	ChrPerksList.list.ImmediateReload.descr = "perkImmediateReload";  // �������
	ChrPerksList.list.ImmediateReload.condition.FastReload = true;
	ChrPerksList.list.ImmediateReload.TimeDelay = 300;
	ChrPerksList.list.ImmediateReload.TimeDuration = 60;
	ChrPerksList.list.ImmediateReload.BaseType = "ship";
	ChrPerksList.list.ImmediateReload.OfficerType = "cannoner";

	ChrPerksList.list.HullDamageUp.descr = "perkHullDamageUp";   // �������
	ChrPerksList.list.HullDamageUp.BaseType = "ship";
	ChrPerksList.list.HullDamageUp.OfficerType = "cannoner";

	ChrPerksList.list.SailsDamageUp.descr = "perkSailsDamageUp";  // �������
	ChrPerksList.list.SailsDamageUp.BaseType = "ship";
	ChrPerksList.list.SailsDamageUp.OfficerType = "cannoner";

	ChrPerksList.list.CrewDamageUp.descr = "perkCrewDamageUp";   // �������
	ChrPerksList.list.CrewDamageUp.BaseType = "ship";
	ChrPerksList.list.CrewDamageUp.OfficerType = "cannoner";

	ChrPerksList.list.CriticalShoot.descr = "perkCriticalShoot";  // �������
	ChrPerksList.list.CriticalShoot.condition.HullDamageUp = true;
	ChrPerksList.list.CriticalShoot.condition.SailsDamageUp = true;
	ChrPerksList.list.CriticalShoot.condition.CrewDamageUp = true;
	ChrPerksList.list.CriticalShoot.BaseType = "ship";
	ChrPerksList.list.CriticalShoot.OfficerType = "cannoner";

	ChrPerksList.list.LongRangeShoot.descr = "perkLongRangeShoot";   // �������
	ChrPerksList.list.LongRangeShoot.BaseType = "ship";
	ChrPerksList.list.LongRangeShoot.OfficerType = "cannoner";

	ChrPerksList.list.CannonProfessional.descr = "perkCannonProfessional";  // �������
	ChrPerksList.list.CannonProfessional.condition.CriticalShoot = true;
	ChrPerksList.list.CannonProfessional.condition.LongRangeShoot = true;
	ChrPerksList.list.CannonProfessional.condition.FastReload = true;
	ChrPerksList.list.CannonProfessional.BaseType = "ship";
	ChrPerksList.list.CannonProfessional.OfficerType = "cannoner";



	// Ship Control Skills Group
	//================================================================
	/////////////////////////////////////////////////////////////
	/// ����� ��� ��������
	/////////////////////////////////////////////////////////////
	ChrPerksList.list.Carpenter.descr = "perkCarpenter";
    ChrPerksList.list.Carpenter.OfficerType = "carpenter";
    ChrPerksList.list.Carpenter.BaseType = "ship";
    
	ChrPerksList.list.Builder.descr = "perkBuilder";
	ChrPerksList.list.Builder.condition.Carpenter = true;
    ChrPerksList.list.Builder.OfficerType = "carpenter";
    ChrPerksList.list.Builder.BaseType = "ship";
    
	ChrPerksList.list.LightRepair.descr = "perkLightRepair";   // �������
	ChrPerksList.list.LightRepair.TimeDelay = 240;
	ChrPerksList.list.LightRepair.TimeDuration = 60;
	ChrPerksList.list.LightRepair.BaseType = "ship";
	ChrPerksList.list.LightRepair.OfficerType = "carpenter";

	ChrPerksList.list.InstantRepair.descr = "perkInstantRepair";    // �������
	ChrPerksList.list.InstantRepair.condition.LightRepair = true;
	ChrPerksList.list.InstantRepair.condition.Carpenter = true;
	ChrPerksList.list.InstantRepair.TimeDelay = 240;// boal 13.02.2004
	ChrPerksList.list.InstantRepair.TimeDuration = 30;
	ChrPerksList.list.InstantRepair.BaseType = "ship";
	ChrPerksList.list.InstantRepair.OfficerType = "carpenter";
    
    ChrPerksList.list.BasicBattleState.descr = "perkBasicBattleState";   // ������� ��������� � �������� ������ � �������
    ChrPerksList.list.BasicBattleState.OfficerType = "carpenter";
	ChrPerksList.list.BasicBattleState.BaseType = "ship";

	ChrPerksList.list.AdvancedBattleState.descr = "perkAdvancedBattleState";
	ChrPerksList.list.AdvancedBattleState.condition.BasicBattleState = true;
	ChrPerksList.list.AdvancedBattleState.OfficerType = "carpenter";
	ChrPerksList.list.AdvancedBattleState.BaseType = "ship";

	ChrPerksList.list.ShipDefenseProfessional.descr = "perkShipDefenseProfessional";
	ChrPerksList.list.ShipDefenseProfessional.condition.AdvancedBattleState = true;
	ChrPerksList.list.ShipDefenseProfessional.BaseType = "ship";
	ChrPerksList.list.ShipDefenseProfessional.OfficerType = "carpenter";
    /////////////////////////////////////////////////////////////
	/// ����� ��� �������
	/////////////////////////////////////////////////////////////
	ChrPerksList.list.ShipSpeedUp.descr = "perkShipSpeedUp";  // �������
	ChrPerksList.list.ShipSpeedUp.BaseType = "ship";
	ChrPerksList.list.ShipSpeedUp.OfficerType = "navigator";

	ChrPerksList.list.ShipTurnRateUp.descr = "perkShipTurnRateUp";    // �������
	ChrPerksList.list.ShipTurnRateUp.BaseType = "ship";
	ChrPerksList.list.ShipTurnRateUp.OfficerType = "navigator";

	ChrPerksList.list.StormProfessional.descr = "perkStormProfessional";   // �������
	ChrPerksList.list.StormProfessional.BaseType = "ship";
	ChrPerksList.list.StormProfessional.OfficerType = "navigator";

	ChrPerksList.list.WindCatcher.descr = "perkWindCatcher";
	ChrPerksList.list.WindCatcher.BaseType = "ship";
	ChrPerksList.list.WindCatcher.OfficerType = "navigator";

	ChrPerksList.list.SailsMan.descr = "perkSailsMan";
	ChrPerksList.list.SailsMan.BaseType = "ship";
	ChrPerksList.list.SailsMan.OfficerType = "navigator";
	
	ChrPerksList.list.Turn180.descr = "perkTurn180";           // �������
	ChrPerksList.list.Turn180.condition.ShipSpeedUp = true;
	ChrPerksList.list.Turn180.condition.ShipTurnRateUp = true;
	ChrPerksList.list.Turn180.condition.WindCatcher = true;
	ChrPerksList.list.Turn180.TimeDelay = 240;
	ChrPerksList.list.Turn180.TimeDuration = 60;
	ChrPerksList.list.Turn180.BaseType = "ship";
	ChrPerksList.list.Turn180.OfficerType = "navigator";

	ChrPerksList.list.SailingProfessional.descr = "perkSailingProfessional";   // �������
	ChrPerksList.list.SailingProfessional.condition.SailsMan = true;
	ChrPerksList.list.SailingProfessional.condition.StormProfessional = true;
	ChrPerksList.list.SailingProfessional.condition.Turn180 = true;
	ChrPerksList.list.SailingProfessional.BaseType = "ship";
	ChrPerksList.list.SailingProfessional.OfficerType = "navigator";
    // ������ �� ��� <--

	/////////////////////////////////////////////////////////////
	/// ����� ��� �������
	/////////////////////////////////////////////////////////////
	ChrPerksList.list.Doctor1.descr = "perkDoctor1";
    ChrPerksList.list.Doctor1.BaseType = "ship";
	ChrPerksList.list.Doctor1.OfficerType = "doctor";
	
	ChrPerksList.list.Doctor2.descr = "perkDoctor2";
	ChrPerksList.list.Doctor2.condition.Doctor1 = true;
    ChrPerksList.list.Doctor2.BaseType = "ship";
	ChrPerksList.list.Doctor2.OfficerType = "doctor";
	
	ChrPerksList.list.EmergentSurgeon.descr = "perkEmergentSurgeon";
	ChrPerksList.list.EmergentSurgeon.condition.Doctor2 = true;
    ChrPerksList.list.EmergentSurgeon.BaseType = "ship";
	ChrPerksList.list.EmergentSurgeon.OfficerType = "doctor";
	
	/////////////////////////////////////////////////////////////
	/// ����� ��� �����������
	/////////////////////////////////////////////////////////////
	//ChrPerksList.list.Smuggler.descr = "perkSmuggler";

	/////////////////////////////////////////////////////////////
	/// ������� �����
	/////////////////////////////////////////////////////////////
	
	// ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
	ChrPerksList.list.Energaiser.descr = "perkEnergaiser";
	ChrPerksList.list.Energaiser.Hiden = true;


	// ������� ���� ���� ����� � 5 ��������� � ������� �������� ������� ��� ������� ���� ����
	ChrPerksList.list.MapMaker.descr = "perkMapMaker";
	ChrPerksList.list.MapMaker.PlayerOnly = true;
	ChrPerksList.list.MapMaker.Hiden = true;
	
	// ������� ���� ����������. ��� ����������� ��� ��������� � ����������� �������� ����������� �������� �� 15v
	ChrPerksList.list.Buccaneer.descr = "perkBuccaneer";
	ChrPerksList.list.Buccaneer.PlayerOnly = true;
	ChrPerksList.list.Buccaneer.Hiden = true;
	
	// ������� ���� ��������. ��� ��� ������� ���� � �������� ����� �
	ChrPerksList.list.Trader.descr = "perkBuccaneer";
	ChrPerksList.list.Trader.PlayerOnly = true;
	ChrPerksList.list.Trader.Hiden = true;
	
	// ������� ���� �������������. ��� 10 ��������� ���� �������� ����� � ��������� ����������� 5% �����
	ChrPerksList.list.Fencer.descr = "perkBuccaneer";
	ChrPerksList.list.Fencer.PlayerOnly = true;
	ChrPerksList.list.Fencer.Hiden = true;
	
	// ������� ���� ������. ��� �������� +30 ������� � 15 ��������� � ���������� �����
	ChrPerksList.list.Grunt.descr = "perkBuccaneer";
	ChrPerksList.list.Grunt.PlayerOnly = true;
	ChrPerksList.list.Grunt.Hiden = true;
	
	// ������� ���� �����������. ��� �����
	ChrPerksList.list.Adventurer.descr = "perkBuccaneer";
	ChrPerksList.list.Adventurer.PlayerOnly = true;
	ChrPerksList.list.Adventurer.Hiden = true;
	
	// ������� ���� ������. ��� �������� ������� ����������
	ChrPerksList.list.Agent.descr = "perkBuccaneer";
	ChrPerksList.list.Agent.PlayerOnly = true;
	ChrPerksList.list.Agent.Hiden = true;
	
	// ������� ���� ������. ��� �������� ������� ����������
	ChrPerksList.list.SeaWolf.descr = "perkBuccaneer";
	ChrPerksList.list.SeaWolf.PlayerOnly = true;
	ChrPerksList.list.SeaWolf.Hiden = true;
}