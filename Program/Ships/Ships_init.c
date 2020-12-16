void InitShips()
{
  ref refShip;

	for (int idx=0;idx<SHIP_TYPES_QUANTITY_WITH_FORT;idx++)
	{
		makeref(refShip,ShipsTypes[idx]);

		refship.index = idx;

		refship.InertiaAccelerationX = 0.2;		refship.InertiaBrakingX = 0.7;
		refship.InertiaAccelerationY = 0.4;		refship.InertiaBrakingY = 0.4;
		refship.InertiaAccelerationZ = 1.0;		refship.InertiaBrakingZ = 1.0;

		refship.Rocking.y = 0.5;
		refship.Rocking.az = 0.05;

		refship.NetGeraldSails = "";
		refship.Soundtype = "";

		refship.WaterLine = 0.0;
		refship.SpeedDependWeight = 0.0;
		refship.SubSeaDependWeight = 0.0;
		refship.TurnDependWeight = 0.0;
		refship.TurnDependSpeed = 0.0;

		refShip.Height.Bombs.Y		= 3.0;		refShip.Height.Bombs.DY		= 1.0;
		refShip.Height.Grapes.Y		= 4.0;		refShip.Height.Grapes.DY	= 1.0;
		refShip.Height.Knippels.Y	= 25.0;		refShip.Height.Knippels.DY	= 15.0;
		refShip.Height.Balls.Y		= 3.0;		refShip.Height.Balls.DY		= 1.0;

        refship.WindAgainstSpeed   = 1.0;//boal
		refship.CabinType          = "Cabin_Small"; // ����� �������� ����� My_ � ����� ������ ��� ��
        refShip.AbordageLocation			= "BOARDING_SMALL_DECK";
        refship.DeckType          = "Low";
        
		refShip.MaxCaliber	= 8;
		refShip.Cannon		= CANNON_TYPE_CANNON_LBS8;

		aref cannonl, cannonr, cannonb, cannonf;

		refship.CanEncounter = true;
		refship.Type.Merchant = true;
		refship.Type.War = true;
		refship.Track.Enable = false;
		refShip.FireHeight = 3.0;

		refShip.Massa = 1500000.0;
		refShip.Volume = 900.0;
		refShip.lowpolycrew = 5;
		refShip.buildtime = 10;

		refShip.rcannon = 0;
		refShip.lcannon = 0;
		refShip.fcannon = 0;
		refShip.bcannon = 0;
		
		ShipsTypes[idx].Cannons.Borts.cannonl = "";
		ShipsTypes[idx].Cannons.Borts.cannonr = "";
		ShipsTypes[idx].Cannons.Borts.cannonf = "";
		ShipsTypes[idx].Cannons.Borts.cannonb = "";

		makearef(cannonl,ShipsTypes[idx].Cannons.Borts.cannonl);
		makearef(cannonr,ShipsTypes[idx].Cannons.Borts.cannonr);
		makearef(cannonf,ShipsTypes[idx].Cannons.Borts.cannonf);
		makearef(cannonb,ShipsTypes[idx].Cannons.Borts.cannonb);

		cannonf.FireZone	= Degree2Radian(30.0);
		cannonf.FireDir		= Degree2Radian(0.0);
		cannonf.FireAngMin	= -0.35;
		cannonf.FireAngMax	= 0.60;

		cannonr.FireZone	= Degree2Radian(80.0);
		cannonr.FireDir		= Degree2Radian(90.0);
		cannonr.FireAngMin	= -0.35;
		cannonr.FireAngMax	= 0.60;

		cannonb.FireZone	= Degree2Radian(30.0);
		cannonb.FireDir		= Degree2Radian(180.0);
		cannonb.FireAngMin	= -0.35;
		cannonb.FireAngMax	= 0.60;

		cannonl.FireZone	= Degree2Radian(80.0);
		cannonl.FireDir		= Degree2Radian(270.0);
		cannonl.FireAngMin	= -0.35;
		cannonl.FireAngMax	= 0.60;
	}

	///////////////////////////////////////////////////////////////////////////
	//// Boat			�����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BOAT]);
	refShip.Name									= "Boat";
	refship.Soundtype								= "lugger";
	refShip.Class									= 7;
	refShip.Cannon								= CANNON_TYPE_NONECANNON;
	refShip.MaxCaliber						= 8;
	refShip.Weight								= Tonnes2CWT(10);
	refShip.Capacity							= 50;
	refShip.CannonsQuantity				= 0;
	refShip.rcannon 							= 0;
	refShip.lcannon 							= 0;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 0;
	refShip.MaxCrew								= 10; //sailing crew
	refShip.MinCrew								= 2;
	refShip.SpeedRate							= 4;
	refShip.TurnRate							= 40;
	refShip.Price									= 100;
	refShip.HP										= 100;
	refShip.SP										= 100;
	refship.CanEncounter					= false;
	refship.Type.Merchant					= false;
	refship.Type.War						= false;
	refShip.lowpolycrew = 0;

	refship.WaterLine							= -0.3;

	refShip.Massa = 10000.0;
	refShip.Volume = 100.0;
	
	refShip.Flags.Mast0.Flag1 = FLAG_SPECIAL;
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 0.4;	refship.InertiaBrakingY		= 0.2;
	refship.InertiaAccelerationZ	= 0.15;	refship.InertiaBrakingZ		= 0.05;

	///////////////////////////////////////////////////////////////////////////
	//// Tartane			�������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_TARTANE]);
	refShip.Name								= "Tartane";
	refship.Soundtype							= "lugger";
	refShip.Class								= 7;
	refShip.Cannon								= CANNON_TYPE_NONECANNON;
	refShip.MaxCaliber							= 8;
	refShip.Weight								= Tonnes2CWT(10);
	refShip.Capacity							= 50;
	refShip.CannonsQuantity						= 0;
	refShip.rcannon 									= 0;
	refShip.lcannon 									= 0;
	refShip.fcannon 									= 0;
	refShip.bcannon 									= 0;
	refShip.MaxCrew									= 12;
	refShip.MinCrew									= 1;
	refShip.SpeedRate						= 7.0;
	refShip.TurnRate						= 50;
	refShip.Price								= 5000;
	refShip.HP										= 100;
	refShip.SP										= 100;
	refship.CanEncounter						= true;
	refship.Type.Merchant						= true;
	refship.Type.War							= true;
	refShip.fWindAgainstSpeed					= 10.0;
	refShip.sea_enchantment						= 4.0;
	refShip.lowpolycrew = 3;
	refShip.buildtime = 10;

	refShip.Massa 								= 10000.0;
	refShip.Volume 								= 20.0;
	refship.WindAgainstSpeed   					= 8.0;//boal
	
	refShip.Flags.Mast1.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 3.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 14;	refship.InertiaBrakingY		= 5;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.Height.Bombs.Y				= 0.4;	refShip.Height.Bombs.DY		= 0.2;
	refShip.Height.Grapes.Y				= 1.3;	refShip.Height.Grapes.DY	= 0.6;
	refShip.Height.Knippels.Y			= 6.5;	refShip.Height.Knippels.DY	= 5.8;
	refShip.Height.Balls.Y				= 0.4;	refShip.Height.Balls.DY		= 0.2;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "1.0, 2.0";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "1.2, 2.0";
	refship.Track2.Speed	= "0.15, 0.25";

	 //Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Plot			����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_PLOT]);
	refShip.Name								= "Plot";
	refship.Soundtype							= "lugger";
	refShip.Class								= 7;
	refShip.Cannon								= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber							= 8;
	refShip.Weight								= Tonnes2CWT(10);
	refShip.Capacity							= 210;
	refShip.CannonsQuantity						= 5;
	refShip.rcannon 									= 0;
	refShip.lcannon 									= 0;
	refShip.fcannon 									= 2;
	refShip.bcannon 									= 3;
	refShip.MaxCrew									= 10;
	refShip.MinCrew									= 2;
	refShip.SpeedRate						= 3;
	refShip.TurnRate						= 10;
	refShip.Price								= 12000;
	refShip.HP										= 100;
	refShip.SP										= 100;
	refship.CanEncounter						= false;
	refship.Type.Merchant						= false;
	refship.Type.War							= false;
	refShip.fWindAgainstSpeed					= 10.0;
	refShip.sea_enchantment						= 4.0;
	refShip.lowpolycrew							= 3;
	refShip.buildtime 							= 10;
	
	refShip.Massa = 50000.0;
	refShip.Volume = 100.0;

	refship.WaterLine				= -0.4;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.4;
	refship.TurnDependWeight			= 0.2;
    refship.WindAgainstSpeed   = 7.0;//boal
    
	refship.InertiaAccelerationX	= 3.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 14;	refship.InertiaBrakingY		= 5;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "1.0, 2.0";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "1.2, 2.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	 //Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// War Tartane			������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_WAR_TARTANE]);
	refShip.Name								= "WarTartane";
	refship.Soundtype							= "lugger";
	refShip.Class								= 7;
	refShip.Cannon								= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber							= 8;
	refShip.Weight								= Tonnes2CWT(10);
	refShip.Capacity							= 210;
	refShip.CannonsQuantity						= 8;
	refShip.rcannon 									= 4;
	refShip.lcannon 									= 4;
	refShip.fcannon 									= 0;
	refShip.bcannon 									= 0;
	refShip.MaxCrew									= 20;
	refShip.MinCrew									= 4;
	refShip.SpeedRate						= 14.0;
	refShip.TurnRate						= 70;
	refShip.Price								= 22000;
	refShip.HP										= 210;
	refShip.SP										= 100;
	refship.CanEncounter						= false;
	refship.Type.Merchant						= true;
	refship.Type.War							= false;
	refShip.fWindAgainstSpeed					= 10.0;
	refShip.sea_enchantment						= 4.0;
	refShip.lowpolycrew							= 3;
	refShip.buildtime = 10;

	refShip.Flags.Mast1.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	
	refShip.Massa = 50000.0;
	refShip.Volume = 100.0;

	refship.WaterLine					= 0.1;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.4;
	refship.TurnDependWeight			= 0.2;
    refship.WindAgainstSpeed   = 7.0;//boal
    
	refship.InertiaAccelerationX	= 3.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 14;	refship.InertiaBrakingY		= 5;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 1.8;	refShip.Height.Grapes.DY	= 0.9;
	refShip.Height.Knippels.Y			= 6.7;	refShip.Height.Knippels.DY	= 6.7;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "1.0, 2.0";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "1.2, 2.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	 //Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Bermsloop		˸�. ����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BERMSLOOP]);
	refShip.Name            			= "Bermsloop";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(150);
	refShip.Capacity        			= 600;
	refShip.CannonsQuantity				= 8;
	refShip.rcannon 							= 3;
	refShip.lcannon 							= 3;
	refShip.fcannon 							= 1;
	refShip.bcannon 							= 1;
	refShip.MaxCrew         				= 45;
	refShip.MinCrew         				= 9;
	refShip.SpeedRate       		= 15.8;
	refShip.TurnRate        		= 55;
	refShip.Price           			= 56000;
	refShip.HP              				= 700;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 6.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew = 8;
	refShip.buildtime = 20;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	
	refship.WaterLine							= -0.5;
	refship.SpeedDependWeight			= 0.1;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 9.0;//boal
	refship.CabinType          = "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refship.InertiaAccelerationX	= 10.0;	refship.InertiaBrakingX		= 10.0;
	refship.InertiaAccelerationY	= 10;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ	= 10.0;	refship.InertiaBrakingZ		= 10.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 10.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.5";
	refship.Track2.Speed	= "0.15, 0.25";	
	
	 //Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Empress			�����������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_EMPRESS]);
	refShip.Name            			= "Empress";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 8;
	refShip.Weight						= Tonnes2CWT(200);
	refShip.Capacity       				= 1200;
	refShip.CannonsQuantity				= 10;
	refShip.rcannon 							= 5;
	refShip.lcannon 							= 5;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 0;
	refShip.MaxCrew         				= 94;
	refShip.MinCrew         				= 18;
	refShip.SpeedRate				= 13.3;
	refShip.TurnRate        		= 50;
	refShip.Price           			= 48000;
	refShip.HP              				= 1750;
	refShip.SP              				= 100;
	refship.EmblemedSails.normalTex = "ships\sail_Empress.tga";
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew 				= 10;
	refShip.buildtime 					= 40;
	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.25;
	
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.WaterLine				= 0.04;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.8;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   			= 7.0;//boal
	refship.CabinType          			= "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refship.InertiaAccelerationX	= 0.2;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 4.0;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 4.0;

	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime 			= 7.5;
	refship.Track1.Width				= "6.0, 7.0";
	refship.Track1.Speed				= "7.2, 9.2";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime 			= 5.0;
	refship.Track2.Width				= "6.0, 8.0";
	refship.Track2.Speed				= "0.15, 0.25";

	 //Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Pink			˸�. ����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_PINK]);
	refShip.Name            			= "Pink";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(160);
	refShip.Capacity        			= 700;
	refShip.CannonsQuantity				= 12;
	refShip.rcannon 							= 4;
	refShip.lcannon 							= 4;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 55;
	refShip.MinCrew         				= 11;
	refShip.SpeedRate       		= 15;
	refShip.TurnRate        		= 50;
	refShip.Price           			= 50000;
	refShip.HP              				= 800;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 6.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew = 8;
	refShip.buildtime = 20;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	
	refship.WaterLine							= -0.40;
	refship.SpeedDependWeight			= 0.1;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 8.5;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refship.InertiaAccelerationX	= 10.0;	refship.InertiaBrakingX		= 10.0;
	refship.InertiaAccelerationY	= 10;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ	= 10.0;	refship.InertiaBrakingZ		= 10.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 10.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.5";
	refship.Track2.Speed	= "0.15, 0.25";
	
	 //Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Lugger			������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LUGGER]);
	refShip.Name            			= "Lugger";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(150);
	refShip.Capacity        			= 600;
	refShip.CannonsQuantity				= 12;
	refShip.rcannon 							= 4;
	refShip.lcannon 							= 4;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 40;
	refShip.MinCrew         				= 8;
	refShip.SpeedRate       		= 16.5;
	refShip.TurnRate        		= 60;
	refShip.Price           			= 45000;
	refShip.HP              				= 600;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 6.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew = 8;
	refShip.buildtime = 20;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;

	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;					

	refship.WaterLine							= 0.2;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 10.0;//boal
	refship.CabinType          = "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refship.InertiaAccelerationX	= 10.0;	refship.InertiaBrakingX		= 10.0;
	refship.InertiaAccelerationY	= 10;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ	= 10.0;	refship.InertiaBrakingZ		= 10.0;
	
	refShip.Height.Bombs.Y				= 2.1;	refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.1;	refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y			= 10.5;	refShip.Height.Knippels.DY	= 8.5;
	refShip.Height.Balls.Y				= 2.1;	refShip.Height.Balls.DY		= 1.0;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 10.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.5";
	refship.Track2.Speed	= "0.15, 0.25";
	
	 //Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Lugger_h	���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LUGGER_H]);
	refShip.Name            			= "Lugger_h";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(200);
	refShip.Capacity        			= 900;
	refShip.CannonsQuantity				= 12;
	refShip.rcannon 							= 4;
	refShip.lcannon 							= 4;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 50;
	refShip.MinCrew         				= 15;
	refShip.SpeedRate       		= 15.5;
	refShip.TurnRate        		= 50;
	refShip.Price           			= 55000;
	refShip.HP              				= 850;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 6.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew = 8;
	refShip.buildtime = 20;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	refship.WaterLine							= -0.01;
	refship.SpeedDependWeight			= 0.4;
	refship.SubSeaDependWeight			= 0.4;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 10.0;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refship.InertiaAccelerationX	= 10.0;	refship.InertiaBrakingX		= 10.0;
	refship.InertiaAccelerationY	= 10;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ	= 10.0;	refship.InertiaBrakingZ		= 10.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 10.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.5";
	refship.Track2.Speed	= "0.15, 0.25";
	
	 //Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Speedy			��. ����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SPEEDY]);
	refShip.Name            			= "Speedy";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(250);
	refShip.Capacity        			= 1000;
	refShip.CannonsQuantity				= 14;
	refShip.rcannon 							= 7;
	refShip.lcannon 							= 7;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 0;
	refShip.MaxCrew         				= 70;
	refShip.MinCrew         				= 14;
	refShip.SpeedRate       			= 15;
	refShip.TurnRate        			= 45;
	refShip.Price           			= 87000;
	refShip.HP              				= 1150;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed	= 4.0;
	refShip.sea_enchantment		= 1.8;
	refShip.lowpolycrew 		= 16;
	refShip.buildtime 		= 60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refship.WaterLine		= 0.1;
	refship.SpeedDependWeight	= 0.27;
	refship.SubSeaDependWeight	= 0.6;
	refship.TurnDependWeight	= 0.3;
	refship.WindAgainstSpeed   	= 3.3;//boal
	refship.CabinType          	= "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refShip.Flags.Mast1.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y		= 1.0;	refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y		= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y	= 15.0;	refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y		= 1.0;	refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable		= true;
	refship.Track1.ZStart		= 0.20;
	refship.Track1.LifeTime 	= 12;
	refship.Track1.Width		= "2.0, 3.0";
	refship.Track1.Speed		= "6.0, 8.0";

	refship.Track2.ZStart		= -0.15;
	refship.Track2.LifeTime 	= 7.5;
	refship.Track2.Width		= "4.0, 6.0";
	refship.Track2.Speed		= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// FR_Sloop			���. ����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FR_SLOOP]);
	refShip.Name            			= "FR_Sloop";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(200);
	refShip.Capacity        			= 800;
	refShip.CannonsQuantity				= 14;
	refShip.rcannon 							= 6;
	refShip.lcannon 							= 6;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 72;
	refShip.MinCrew         				= 14;
	refShip.SpeedRate				= 15.3;
	refShip.TurnRate        		= 55;
	refShip.Price           			= 77000;
	refShip.HP              				= 1500;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 5;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew = 8;
	refShip.buildtime = 20;
	
	refship.Rocking.y = 0.45;
	refship.Rocking.az = 0.02;

	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	
	refShip.WaterLine = 0.0;//BB was 0.1
	refShip.SpeedDependWeight = 0.3;
	refShip.SubSeaDependWeight = 0.5;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 8.0;//boal	
	refship.CabinType          = "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refShip.GeraldSails.rey_a2	= 1;

	refShip.Height.Bombs.Y			= 1.0;	refShip.Height.Bombs.DY 	= 0.5;
	refShip.Height.Grapes.Y 		= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y		= 10.0; refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y			= 1.0;	refShip.Height.Balls.DY 	= 0.5;
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 8.0;	refship.InertiaBrakingZ		= 8.0;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 2.5";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.05;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Galeoth_h			������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_Galeoth_h]);
	refShip.Name            			= "Galeoth_h";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(170);
	refShip.Capacity        			= 1950;
	refShip.CannonsQuantity				= 16;
	refShip.rcannon 							= 6;
	refShip.lcannon 							= 6;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 90;
	refShip.MinCrew         				= 18;
	refShip.SpeedRate       		= 12;
	refShip.TurnRate        		= 47;
	refShip.Price           			= 71000;
	refShip.HP              				= 1800;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 6.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew = 8;
	refShip.buildtime = 20;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	
	refship.WaterLine							= -0.4;
	refship.SpeedDependWeight			= 0.1;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 8.0;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refship.InertiaAccelerationX	= 8.5;	refship.InertiaBrakingX		= 8.5;
	refship.InertiaAccelerationY	= 9;	refship.InertiaBrakingY		= 9;
	refship.InertiaAccelerationZ	= 9.0;	refship.InertiaBrakingZ		= 9.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 10.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.5";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Sloop			����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SLOOP]);
	refShip.Name            			= "Sloop";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(170);
	refShip.Capacity        			= 800;
	refShip.CannonsQuantity				= 16;
	refShip.rcannon 							= 6;
	refShip.lcannon 							= 6;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 75;
	refShip.MinCrew         				= 15;
	refShip.SpeedRate				= 13.8;
	refShip.TurnRate        		= 39;
	refShip.Price           			= 95000;
	refShip.HP              				= 900;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 5;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew = 8;
	refShip.buildtime = 20;
	
	refship.Rocking.y = 0.45;
	refship.Rocking.az = 0.02;

	refShip.Flags.Mast1.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	
	refship.WaterLine							= -0.0;

	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 8.0;//boal
	refship.CabinType          = "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refShip.Height.Bombs.Y				= 2.0;	refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.8;	refShip.Height.Grapes.DY	= 1.9;
	refShip.Height.Knippels.Y			= 15.2;	refShip.Height.Knippels.DY	= 13.9;
	refShip.Height.Balls.Y				= 2.0;	refShip.Height.Balls.DY		= 1.0;
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 8.0;	refship.InertiaBrakingZ		= 8.0;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 2.5";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.05;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Sloop_b			������ ����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SLOOP_B]);
	refShip.Name            			= "Sloop_b";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(175);
	refShip.Capacity        			= 1200;	
	refShip.CannonsQuantity				= 16;
	refShip.rcannon 							= 6;
	refShip.lcannon 							= 6;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 95;
	refShip.MinCrew         				= 19;	
	refShip.SpeedRate				= 14;
	refShip.TurnRate        		= 42;
	refShip.Price           			= 108000;
	refShip.HP              				= 1450;
	refShip.SP              				= 100;

	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;	
	refShip.lowpolycrew 				= 9;
	
	refship.Rocking.y 					= 0.45;
	refship.Rocking.az 					= 0.02;
	
	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.3;
	
	refship.WindAgainstSpeed   			= 4.3;
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refShip.Height.Bombs.Y				= 1.6;	refShip.Height.Bombs.DY		= 1.25;
	refShip.Height.Grapes.Y				= 2.75;	refShip.Height.Grapes.DY	= 0.6;
	refShip.Height.Knippels.Y			= 13.2;	refShip.Height.Knippels.DY	= 8.5;
	refShip.Height.Balls.Y				= 1.6;	refShip.Height.Balls.DY		= 1.25;

	refShip.GeraldSails.rey_a2		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 8.0;	refship.InertiaBrakingZ		= 8.0;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 2.5";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.05;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Neptunus			����. ����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_NEPTUNUS]);
	refShip.Name            			= "Neptunus";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(190);
	refShip.Capacity        			= 950;
	refShip.CannonsQuantity				= 16;
	refShip.rcannon 							= 8;
	refShip.lcannon 							= 8;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 0;
	refShip.MaxCrew         				= 110;
	refShip.MinCrew         				= 22;
	refShip.SpeedRate				= 13.5;
	refShip.TurnRate        		= 45;
	refShip.Price           			= 110000;
	refShip.HP              				= 1700;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 3.5;
	refShip.sea_enchantment					= 1.5;
	refShip.lowpolycrew = 16;
	refShip.buildtime = 80;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refship.WaterLine							= -0.4;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.7;
	refship.TurnDependWeight			= 0.35;
	refship.WindAgainstSpeed   = 2.8;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refShip.Flags.Mast1.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.17;
	refship.Track1.LifeTime = 12.5;
	refship.Track1.Width	= "4.0, 5.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6.5;
	refship.Track2.Width	= "5.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// SOPHIE			���. ����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SOPHIE]);
	refShip.Name 				= "Sophie";
	refship.Soundtype 			= "lugger";
	refShip.Class 				= 6;
	refShip.Cannon 				= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber 			= 12;
	refShip.Weight 				= Tonnes2CWT(400);
	refShip.Capacity 			= 1600;
	refShip.CannonsQuantity 	= 18;
	refShip.rcannon 					= 9;
	refShip.lcannon 					= 9;
	refShip.fcannon 					= 0;
	refShip.bcannon 					= 0;
	refShip.MaxCrew 				= 125;
	refShip.MinCrew 				= 25;
	refShip.SpeedRate 		= 13.3;
	refShip.TurnRate 		= 45;
	refShip.Price 				= 88000;
	refShip.HP 						= 1450;
	refShip.SP 						= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant 					= true;
	refship.Type.War 						= true;
	refShip.fWindAgainstSpeed = 4.0;
	refShip.sea_enchantment = 1.8;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;

	refship.WaterLine = -1.0;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 1.3;
	refship.TurnDependWeight = 0.3;
	refship.WindAgainstSpeed = 3.3;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           = "Small";
	
	refShip.Flags.Mast1.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;

	refship.InertiaAccelerationX = 0.2; refship.InertiaBrakingX = 2.0;
	refship.InertiaAccelerationY = 12; refship.InertiaBrakingY = 9;
	refship.InertiaAccelerationZ = 6.0; refship.InertiaBrakingZ = 4.0;

	refShip.Height.Bombs.Y = 1.0; refShip.Height.Bombs.DY = 1.0;
	refShip.Height.Grapes.Y = 2.0; refShip.Height.Grapes.DY = 1.0;
	refShip.Height.Knippels.Y = 15.0; refShip.Height.Knippels.DY = 10.0;
	refShip.Height.Balls.Y = 1.0; refShip.Height.Balls.DY = 1.0;

	refShip.GeraldSails.rey_b2 = 1;
	refShip.GeraldSails.rey_b3 = 1;
	refShip.GeraldSails.rey_b2.vscale = 0.8;
	refShip.GeraldSails.rey_b3.vscale = 0.8;

	refship.Track.Enable = true;
	refship.Track1.ZStart = 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width = "2.0, 3.0";
	refship.Track1.Speed = "6.0, 8.0";

	refship.Track2.ZStart = -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width = "4.0, 6.0";
	refship.Track2.Speed = "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Polacca			�������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_POLACCA]);
	refShip.Name            			= "Polacca";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(400);
	refShip.Capacity        			= 2250;
	refShip.CannonsQuantity				= 14;
	refShip.rcannon 							= 7;
	refShip.lcannon 							= 7;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 0;
	refShip.MaxCrew         				= 150;
	refShip.MinCrew         				= 30;
	refShip.SpeedRate       		= 11;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 105000;
	refShip.HP              				= 2100;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= false;
	refShip.fWindAgainstSpeed				= 5.0;
	refShip.sea_enchantment					= 2;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 60;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.15;
	
	refship.WaterLine							= -0.7;
	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 0.8;
	refship.TurnDependWeight			= 0.35;
	refship.WindAgainstSpeed   = 7.2;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refship.InertiaAccelerationX	= 0.2;	refship.InertiaBrakingX		= 1.0;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 4.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;
	
	refShip.GeraldSails.rey_a2	= 1;
	refShip.GeraldSails.rey_a3	= 1;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 2.5";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.05;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Barque			����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BARQUE]);
	refShip.Name            			= "Barque";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(350);
	refShip.Capacity       				= 2300;
	refShip.CannonsQuantity				= 16;
	refShip.rcannon 							= 6;
	refShip.lcannon 							= 6;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 105;
	refShip.MinCrew         				= 21;
	refShip.SpeedRate				= 9;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 80000;
	refShip.HP              				= 1500;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= false;
	refShip.fWindAgainstSpeed				= 3.0;
	refShip.sea_enchantment					= 1.8;
	refShip.lowpolycrew = 10;
	refShip.buildtime = 40;

	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.025;
	
	refship.WaterLine							= 1.15;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.8;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 3.6;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;					
	
	refShip.Height.Bombs.Y				= 3.3;	refShip.Height.Bombs.DY		= 1.6;
	refShip.Height.Grapes.Y				= 4.9;	refShip.Height.Grapes.DY	= 2.4;
	refShip.Height.Knippels.Y			= 15.8;	refShip.Height.Knippels.DY	= 12.4;
	refShip.Height.Balls.Y				= 3.3;	refShip.Height.Balls.DY		= 1.6;	
	
	refship.InertiaAccelerationX	= 4.0;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4.0;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 7.5;
	refship.Track1.Width	= "6.0, 7.0";
	refship.Track1.Speed	= "7.2, 9.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 5.0;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	// refShip.hullNums = 5; // LEO
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// FR_Postillionen			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FR_POSTILLIONEN]);
	refShip.Name            			= "FR_Postillionen";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(550);
	refShip.Capacity        			= 1200;
	refShip.CannonsQuantity				= 20;
	refShip.rcannon 							= 10;
	refShip.lcannon 							= 10;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 0;
	refShip.MaxCrew         				= 140;
	refShip.MinCrew         				= 28;
	refShip.SpeedRate				= 14.8;
	refShip.TurnRate        		= 44;
	refShip.Price           			= 196000;
	refShip.HP              				= 2300;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 8.0;
	refShip.sea_enchantment					= 2.0;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 40;

	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.03;

	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_SPECIAL;
	refship.Flags.Mast5.Flag1 = FLAG_ENSIGN;
	refship.Flags.Mast7.Flag1 = FLAG_ENSIGN;

	refShip.WaterLine 						= 0;
	refShip.SpeedDependWeight 				= 0.3;
	refShip.SubSeaDependWeight 				= 0.6;
	refship.TurnDependWeight				= 0.3;
	refship.WindAgainstSpeed   				= 7.5;//boal
	refship.CabinType          = "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Medium";
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y		= 1.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y		= 2.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y	= 15.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y		= 1.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_a2	= 1;
	refShip.GeraldSails.rey_a3	= 1;
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 8;
	refship.Track1.Width	= "1.2, 2.2";
	refship.Track1.Speed	= "7.2, 8.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6;
	refship.Track2.Width	= "2.2, 3.2";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Schooner			�����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SCHOONER]);
	refShip.Name            			= "Schooner";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(200);
	refShip.Capacity        			= 1400;
	refShip.CannonsQuantity				= 20;
	refShip.rcannon 							= 8;
	refShip.lcannon 							= 8;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 120;
	refShip.MinCrew         				= 24;
	refShip.SpeedRate				= 14.2;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 178000;
	refShip.HP              				= 1550;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 8.0;
	refShip.sea_enchantment					= 2.0;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 40;

	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.03;

	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;

	refship.WaterLine					= -0.2;

	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.2;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 7.5;//boal
	refship.CabinType          = "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;		refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.7;		refShip.Height.Bombs.DY		= 0.8;
	refShip.Height.Grapes.Y				= 2.9;		refShip.Height.Grapes.DY	= 1.4;
	refShip.Height.Knippels.Y			= 13.9;		refShip.Height.Knippels.DY	= 13.7;
	refShip.Height.Balls.Y				= 1.7;		refShip.Height.Balls.DY		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 8;
	refship.Track1.Width	= "1.2, 2.2";
	refship.Track1.Speed	= "7.2, 8.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6;
	refship.Track2.Width	= "2.2, 3.2";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// ColonialSchooner			���. �����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_COLONIALSCHOONER]);
	refShip.Name            			= "ColonialSchooner";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(180);
	refShip.Capacity        			= 1100;
	refShip.CannonsQuantity				= 20;
	refShip.rcannon 							= 8;
	refShip.lcannon 							= 8;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 100;
	refShip.MinCrew         				= 20;
	refShip.SpeedRate       		= 15.5;
	refShip.TurnRate        		= 45;
	refShip.Price           			= 205000;
	refShip.HP              			= 1100;
	refShip.SP              			= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 6.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew = 8;
	refShip.buildtime = 20;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	
	refship.WaterLine							= 0.0;
	refship.SpeedDependWeight			= 0.0;
	refship.SubSeaDependWeight			= 0.0;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 8.0;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refship.InertiaAccelerationX	= 10.0;	refship.InertiaBrakingX		= 10.0;
	refship.InertiaAccelerationY	= 10;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ	= 10.0;	refship.InertiaBrakingZ		= 10.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 10.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.5";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Xebec			������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_XEBEC]);
	refShip.Name            			= "Xebec";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(200);
	refShip.Capacity        			= 1800;
	refShip.CannonsQuantity				= 20;
	refShip.rcannon 							= 8;
	refShip.lcannon 							= 8;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 140;
	refShip.MinCrew         				= 28;
	refShip.SpeedRate				= 14.5;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 170000;
	refShip.HP              				= 1850;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 6.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew				= 8;
	refShip.buildtime 				= 20;

	refship.Rocking.y 				= 0.5;
	refship.Rocking.az 				= 0.035;
	
	refship.WaterLine = 0.0;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.3;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 9.6;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refship.InertiaAccelerationX	= 0.2;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 15;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ	= 9.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 10.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.5";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Battle Xebec			����. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BATTLEXEBEC]);
	refShip.Name            			= "BattleXebec";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(200);
	refShip.Capacity        			= 1300;
	refShip.CannonsQuantity				= 20;
	refShip.rcannon 							= 8;
	refShip.lcannon 							= 8;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         			= 140;
	refShip.MinCrew         			= 28;
	refShip.SpeedRate				= 14;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 215000;
	refShip.HP              				= 2400;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 6.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew				= 8;
	refShip.buildtime 				= 20;

	refship.Rocking.y 				= 0.5;
	refship.Rocking.az 				= 0.035;
	
	refship.WaterLine = 0.0;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.3;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 9.2;//boal
	refship.CabinType          = "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refship.InertiaAccelerationX	= 0.2;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 15;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ	= 9.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 10.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.5";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	//////////////////////////////////////////////////////////////////////////
	/// XebecLight			���. ������
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_XEBECLIGHT]);
	refShip.Name				= "XebecLight";
	refship.Soundtype			= "lugger";
	refShip.Class				= 5;
	refShip.Cannon  			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber 			= 8;
	refShip.Weight				= Tonnes2CWT(400);
	refShip.Capacity   			= 1600;
	refShip.CannonsQuantity		= 22;
	refShip.rcannon 					= 8;
	refShip.lcannon 					= 8;
	refShip.fcannon 					= 4;
	refShip.bcannon 					= 2;
	refShip.MaxCrew        			= 120;
	refShip.MinCrew        			= 24;
	refShip.SpeedRate      	= 15.3;
	refShip.TurnRate       	= 46;
	refShip.Price          		= 191000;
	refShip.HP             			= 1800;
	refShip.SP             			= 100;
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";
	refship.CanEncounter		= true;
	refship.Type.Merchant		= true;
	refship.Type.War			= true;
	refShip.fWindAgainstSpeed	= 2.0;
	refShip.sea_enchantment		= 1.8;
	refShip.lowpolycrew			= 12;
	refShip.buildtime			= 60;
	refship.WindAgainstSpeed   = 10.0;//boal

	refship.Rocking.y	= 0.5;
	refship.Rocking.az	= 0.04;
	
	refship.WaterLine	= -0.10;
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y	= 1.0;			refShip.Height.Bombs.DY	= 1.0;
	refShip.Height.Grapes.Y	= 2.0;			refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y	= 16.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y		= 1.0;		refShip.Height.Balls.DY	= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// SchoonerLight			��. �����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SCHOONERLIGHT]);
	refShip.Name            			= "SchoonerLight";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(200);
	refShip.Capacity        			= 1000;
	refShip.CannonsQuantity				= 22;
	refShip.rcannon 							= 9;
	refShip.lcannon 							= 9;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 130;
	refShip.MinCrew         				= 26;
	refShip.SpeedRate				= 14;
	refShip.TurnRate        		= 40;
	refShip.Price           			= 195000;
	refShip.HP              				= 1700;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 8.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 40;

	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.03;

	refship.WaterLine					= -0.2;

	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.2;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 7.5;//boal
	refship.CabinType          = "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refShip.InertiaAccelerationX	= 0.2;	refShip.InertiaBrakingX		= 2.0;
	refShip.InertiaAccelerationY	= 12;	refShip.InertiaBrakingY		= 8;
	refShip.InertiaAccelerationZ	= 5.0;	refShip.InertiaBrakingZ		= 4.0;
	
	refShip.Height.Bombs.Y				= 1.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 2.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 15.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y				= 1.0;		refShip.Height.Balls.DY		= 1.0;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 8;
	refship.Track1.Width	= "1.2, 2.2";
	refship.Track1.Speed	= "7.2, 8.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6;
	refship.Track2.Width	= "2.2, 3.2";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Mirage			���. �����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_MIRAGE]);
	refShip.Name            			= "Mirage";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(250);
	refShip.Capacity        			= 1300;
	refShip.CannonsQuantity				= 22;
	refShip.rcannon 							= 8;
	refShip.lcannon 							= 8;
	refShip.fcannon 							= 4;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 150;
	refShip.MinCrew         				= 30;
	refShip.SpeedRate				= 13.5;
	refShip.TurnRate        		= 45;
	refShip.Price           			= 195000;
	refShip.HP              				= 2150;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 7.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew				= 8;
	refShip.buildtime 				= 20;

    refShip.Rocking.y 		= 0.5;
    refShip.Rocking.az 		= 0.035;
	
	refShip.WaterLine = -0.2;
	refShip.SpeedDependWeight = 0.2;
	refShip.SubSeaDependWeight = 0.2;
	refship.TurnDependWeight = 0.8;
	refship.WindAgainstSpeed   			= 5.4;//boal
	refship.CabinType          			= "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag2 = FLAG_ENSIGN;
	
	refShip.GeraldSails.rey_a2	= 1;
	refShip.GeraldSails.rey_b2	= 1;
	
    refShip.InertiaAccelerationX	= 10.0;
    refShip.InertiaBrakingX		= 10.0;
    refShip.InertiaAccelerationY	= 10;
    refShip.InertiaBrakingY		= 10;
    refShip.InertiaAccelerationZ	= 10.0;
    refShip.InertiaBrakingZ		= 10.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 10.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.5";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	///	Polacre			 ������
	///////////////////////////////////////////////////////////////////////////	
	makeref(refShip,ShipsTypes[SHIP_POLACRE]);
	refShip.Name						= "Polacre";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(550);
	refShip.Capacity        			= 1450;
	refShip.CannonsQuantity				= 22;
	refShip.rcannon 							= 9;
	refShip.lcannon 							= 9;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 135;
	refShip.MinCrew         				= 27;
	refShip.SpeedRate       		= 14.5;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 200000;
	refShip.HP              				= 2550;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 3.5;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y	= 0.5;
	refship.Rocking.az	= 0.04;

	refship.WaterLine = 0.0;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 1.1;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 7.6;//boal
	refship.CabinType          = "New_Cabin2"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refShip.Flags.Mast201.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast302.Flag1 = FLAG_ENSIGN;

	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y		= 1.7;		refShip.Height.Bombs.DY	= 0.8;
	refShip.Height.Grapes.Y		= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y	= 10.1;		refShip.Height.Knippels.DY	= 9.2;
	refShip.Height.Balls.Y		= 1.7;		refShip.Height.Balls.DY	= 0.8;
	
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";	

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Enslaver			���. ����������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_ENSLAVER]);
	refShip.Name            			= "Enslaver";
	refship.Soundtype					= "corvette";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 12;
	refShip.Weight						= Tonnes2CWT(350);
	refShip.Capacity        			= 1300;
	refShip.CannonsQuantity				= 22;
	refShip.rcannon 							= 8;
	refShip.lcannon 							= 8;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 150;
	refShip.MinCrew         				= 30;
	refShip.SpeedRate       		= 16;
	refShip.TurnRate        		= 40;
	refShip.Price           			= 185000;
	refShip.HP              				= 2000;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.8;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.04;
	
	refship.WaterLine							= 0.1;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 9.1;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 2.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 15.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y				= 1.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Shnyava			�����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SHNYAVA]);
	refShip.Name            			= "Shnyava";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 8;
	refShip.Weight						= Tonnes2CWT(250);
	refShip.Capacity        			= 1950;
	refShip.CannonsQuantity				= 22;
	refShip.rcannon 							= 8;
	refShip.lcannon 							= 8;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 150;
	refShip.MinCrew         				= 30;
	refShip.SpeedRate       		= 14;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 162000;
	refShip.HP              				= 2300;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 3;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refship.WaterLine							= 0.0;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 6.6;//boal
	refship.CabinType          = "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 2.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 15.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y				= 1.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Brig			����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BRIG]);
	refShip.Name            			= "Brig";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(400);
	refShip.Capacity        			= 1800;
	refShip.CannonsQuantity				= 16;
	refShip.rcannon 							= 6;
	refShip.lcannon 							= 6;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 160;
	refShip.MinCrew         				= 32;
	refShip.SpeedRate       		= 14.5;
	refShip.TurnRate        		= 45;
	refShip.Price           			= 135000;
	refShip.HP              				= 2700;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.8;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.04;
	
	refship.WaterLine							= 0.1;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 3.3;//boal
	refship.CabinType          = "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 2.0;		refShip.Height.Bombs.DY		= 2.0;
	refShip.Height.Grapes.Y				= 3.3;		refShip.Height.Grapes.DY	= 1.6;
	refShip.Height.Knippels.Y			= 14.9;		refShip.Height.Knippels.DY	= 14.0;
	refShip.Height.Balls.Y				= 2.0;		refShip.Height.Balls.DY		= 2.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// BrigHeavy			���. ����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BRIGHEAVY]);
	refShip.Name            			= "BrigHeavy";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(400);
	refShip.Capacity        			= 2000;
	refShip.CannonsQuantity				= 16;
	refShip.rcannon 							= 6;
	refShip.lcannon 							= 6;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 180;
	refShip.MinCrew         				= 36;
	refShip.SpeedRate       		= 14.0;
	refShip.TurnRate        		= 40;
	refShip.Price           			= 148000;
	refShip.HP              				= 3000;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.8;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.04;
	
	refship.WaterLine							= 0.1;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 3.0;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 2.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 15.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y				= 1.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";
    
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Barkentine			����������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BARKENTINE]);
	refShip.Name            			= "Barkentine";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(350);
	refShip.Capacity       				= 2200;
	refShip.CannonsQuantity				= 16;
	refShip.rcannon 							= 6;
	refShip.lcannon 							= 6;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 180;
	refShip.MinCrew         				= 36;
	refShip.SpeedRate       		= 10.4;
	refShip.TurnRate        		= 40;
	refShip.Price           			= 107000;
	refShip.HP              				= 2400;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.8;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.04;
	
	refship.WaterLine					= 1.15;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 8.5;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           = "Small";

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
		
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 3.5;		refShip.Height.Bombs.DY		= 1.7;
	refShip.Height.Grapes.Y				= 4.8;		refShip.Height.Grapes.DY	= 2.4;
	refShip.Height.Knippels.Y			= 16.7;		refShip.Height.Knippels.DY	= 12.8;
	refShip.Height.Balls.Y				= 3.5;		refShip.Height.Balls.DY		= 1.7;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";	

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;
		
	///////////////////////////////////////////////////////////////////////////
	//// Brigantine			����������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BRIGANTINE]);
	refShip.Name            			= "Brigantine";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(350);
	refShip.Capacity        			= 1400;
	refShip.CannonsQuantity				= 16;
	refShip.rcannon 							= 6;
	refShip.lcannon 							= 6;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 140;
	refShip.MinCrew         				= 28;
	refShip.SpeedRate       		= 15.5;
	refShip.TurnRate        		= 50;
	refShip.Price           			= 117000;
	refShip.HP              				= 2300;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.8;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.04;
	
	refship.WaterLine							= 0.1;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 9.1;//boal
	refship.CabinType          = "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;

	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 2.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y			= 13.2;		refShip.Height.Knippels.DY	= 11.6;
	refShip.Height.Balls.Y				= 2.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// CastelF			���. ����������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CASTELF]);
	refShip.Name            			= "Castelf";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(650);
	refShip.Capacity        			= 1600;
	refShip.CannonsQuantity				= 16;
	refShip.rcannon 							= 7;
	refShip.lcannon 							= 7;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 150;
	refShip.MinCrew         				= 30;
	refShip.SpeedRate       		= 15;
	refShip.TurnRate        		= 50;
	refShip.Price           			= 131000;
	refShip.HP              				= 2550;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 4.0;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refship.WaterLine							= 0.0;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 6.1;//boal
	refship.CabinType          = "New_Cabin2"; // boal 28.03.05
	refship.DeckType           = "Medium";
	
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 2.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 15.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y				= 1.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Derfflinger			����. �����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_DERFFLINGER]);
	refShip.Name            	= "Derfflinger";
	refship.Soundtype			= "corvette";
	refShip.Class				= 4;
	refShip.Cannon          	= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      	= 16;
	refShip.Weight				= Tonnes2CWT(450);
	refShip.Capacity        	= 2600;
	refShip.CannonsQuantity		= 16;
	refShip.rcannon 					= 8;
	refShip.lcannon 					= 8;
	refShip.fcannon 					= 0;
	refShip.bcannon 					= 0;
	refShip.MaxCrew         		= 240;
	refShip.MinCrew         		= 48;
	refShip.SpeedRate		= 13;
	refShip.TurnRate        = 30;
	refShip.Price           	= 118000;
	refShip.HP              		= 2700;
	refShip.SP              		= 100;
	refship.CanEncounter		= true;
	refship.Type.Merchant		= true;
	refship.Type.War			= true;
	refShip.fWindAgainstSpeed	= 1.2;
	refShip.sea_enchantment		= 1.5;
	refShip.lowpolycrew 		= 16;
	refShip.buildtime 		= 60;
	
	refship.Rocking.y 		= 0.5;
	refship.Rocking.az 		= 0.35;
	
	refship.WaterLine		= -0.6;
	refship.SpeedDependWeight	= 0.15;
	refship.SubSeaDependWeight	= 0.8;
	refship.TurnDependWeight	= 0.25;
	refship.WindAgainstSpeed   	= 4.0;//boal
	refship.CabinType          	= "Cabin_Medium"; // boal 28.03.05
	refship.DeckType           	= "Medium";
	
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 4.0;	refship.InertiaBrakingZ		= 4.0;
	
	refShip.Height.Bombs.Y				= 1.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 2.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 15.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y				= 1.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;

	refship.Track.Enable		= true;
	refship.Track1.ZStart		= 0.20;
	refship.Track1.LifeTime 	= 12;
	refship.Track1.Width		= "2.0, 3.0";
	refship.Track1.Speed		= "8.0, 8.0";

	refship.Track2.ZStart		= -0.15;
	refship.Track2.LifeTime 	= 7.5;
	refship.Track2.Width		= "6.0, 8.0";
	refship.Track2.Speed		= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Interceptor			���-�����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_INTERCEPTOR]);
	refShip.Name = 								"Interceptor";
	refship.Soundtype = 						"lugger";
	refShip.Class = 							4;
	refShip.Cannon = 							CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber = 						16;
	refShip.Weight = 							Tonnes2CWT(450);
	refShip.Capacity = 							1900;
	refShip.CannonsQuantity = 					18;
	refShip.rcannon = 									8;
	refShip.lcannon = 									8;
	refShip.fcannon = 									0;
	refShip.bcannon = 									2;
	refShip.MaxCrew = 								160;
	refShip.MinCrew = 								32;
	refShip.SpeedRate = 					15;
	refShip.TurnRate = 						40;
	refShip.Price = 							132000;
	refShip.HP = 									2800;
	refShip.SP = 									100;
	refship.CanEncounter = 						true;
	refship.Type.Merchant = 					false;
	refship.Type.War = 							true;
	refShip.fWindAgainstSpeed = 				2.0;
	refShip.sea_enchantment = 					1.8;
	refShip.lowpolycrew = 						12;
	refShip.buildtime = 						60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.04;

	refship.WaterLine = 1.0;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.3;
	refship.TurnDependWeight = 0.3;
	refship.WindAgainstSpeed = 4.3;//boal
	refship.CabinType          = "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refship.InertiaAccelerationX = 0.2; refship.InertiaBrakingX = 2.0;
	refship.InertiaAccelerationY = 12; refship.InertiaBrakingY = 9;
	refship.InertiaAccelerationZ = 6.0; refship.InertiaBrakingZ = 4.0;

	refShip.Height.Bombs.Y = 1.0; refShip.Height.Bombs.DY = 1.0;
	refShip.Height.Grapes.Y = 2.0; refShip.Height.Grapes.DY = 1.0;
	refShip.Height.Knippels.Y = 15.0; refShip.Height.Knippels.DY = 10.0;
	refShip.Height.Balls.Y = 1.0; refShip.Height.Balls.DY = 1.0;

	refShip.GeraldSails.rey_b2 = 1;
	refShip.GeraldSails.rey_b3 = 1;
	refShip.GeraldSails.rey_b2.vscale = 0.8;
	refShip.GeraldSails.rey_b3.vscale = 0.8;

	refship.Track.Enable = true;
	refship.Track1.ZStart = 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width = "2.0, 3.0";
	refship.Track1.Speed = "6.0, 8.0";

	refship.Track2.ZStart = -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width = "4.0, 6.0";
	refship.Track2.Speed = "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Fleut			�����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FLEUT]);
	refShip.Name            			= "Fleut";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(450);
	refShip.Capacity        			= 3000;
	refShip.CannonsQuantity				= 18;
	refShip.rcannon 							= 7;
	refShip.lcannon 							= 7;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 170;
	refShip.MinCrew         				= 34;
	refShip.SpeedRate				= 12;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 100000;
	refShip.HP              				= 3100;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= false;
	refShip.fWindAgainstSpeed				= 2;
	refShip.sea_enchantment					= 1.5;
	refShip.lowpolycrew = 16;
	refShip.buildtime = 60;
	
	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	
	refship.WaterLine							= 1.2;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.8;
	refship.TurnDependWeight			= 0.25;
	refship.WindAgainstSpeed   = 4.0;//boal
	refship.CabinType          = "Cabin_Medium"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;							
		
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 4.0;	refship.InertiaBrakingZ		= 4.0;
	
	refShip.Height.Bombs.Y				= 3.4;		refShip.Height.Bombs.DY		= 1.7;
	refShip.Height.Grapes.Y				= 5.0;		refShip.Height.Grapes.DY	= 2.5;
	refShip.Height.Knippels.Y			= 17.8;		refShip.Height.Knippels.DY	= 13.3;
	refShip.Height.Balls.Y				= 3.4;		refShip.Height.Balls.DY		= 1.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// PO_Fleut50			����. �����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_PO_FLEUT50]);
	refShip.Name            			= "PO_Fleut50";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(450);
	refShip.Capacity        			= 3200;
	refShip.CannonsQuantity						= 20;
	refShip.rcannon 							= 8;
	refShip.lcannon 							= 8;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 160;
	refShip.MinCrew         				= 32;
	refShip.SpeedRate				= 12;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 239000;
	refShip.HP              				= 3600;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.2;
	refShip.sea_enchantment				= 2.1;
	refShip.lowpolycrew = 16;
	refShip.buildtime = 60;
	
	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.35;
	
	refship.WaterLine							= 0.0;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 1.3;
	refship.TurnDependWeight			= 0.25;
	refship.WindAgainstSpeed   = 4.0;//boal
	refship.CabinType          = "Cabin_Medium"; // boal 28.03.05
	refship.DeckType           			= "Medium";
	
	refship.InertiaAccelerationX	= 2.0;	refship.InertiaBrakingX		= 1.0;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 4.0;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Galeon LIGHT			������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_GALEON_L]);
	refShip.Name            			= "Galeon_l";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(800);
	refShip.Capacity        			= 3400;
	refShip.CannonsQuantity						= 20;
	refShip.rcannon 							= 8;
	refShip.lcannon 							= 8;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 320;
	refShip.MinCrew         				= 64;
	refShip.SpeedRate				= 11;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 230000;
	refShip.HP              				= 3800;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew = 16;
	refShip.buildtime = 60;

	refship.Rocking.y = 0.45;
	refship.Rocking.az = 0.035;
	
	refship.WaterLine							= 0.85;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.95;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 3.2;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;					
		
	refship.InertiaAccelerationX	= 4.0;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 4.0;	refship.InertiaBrakingZ		= 4.0;
	
	refShip.Height.Bombs.Y				= 4.3;		refShip.Height.Bombs.DY		= 2.1;
	refShip.Height.Grapes.Y				= 5.6;		refShip.Height.Grapes.DY	= 2.8;
	refShip.Height.Knippels.Y			= 18.7;		refShip.Height.Knippels.DY	= 12.7;
	refShip.Height.Balls.Y				= 4.3;		refShip.Height.Balls.DY		= 2.1;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Greyhound			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_GREYHOUND]);
	refShip.Name            			= "Greyhound";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(250);
	refShip.Capacity        			= 1600;
	refShip.CannonsQuantity				= 22;
	refShip.rcannon 							= 10;
	refShip.lcannon 							= 10;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 150;
	refShip.MinCrew         				= 30;
	refShip.SpeedRate       		= 17.5;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 206000;
	refShip.HP              				= 2400;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 4.0;
	refShip.sea_enchantment				= 3;
	refShip.lowpolycrew = 16;
	refShip.buildtime = 60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refship.WaterLine							= 0.2;
	refship.SpeedDependWeight			= 0.37;
	refship.SubSeaDependWeight			= 0.4;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 4.0;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 0.2;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 12;	refship.InertiaBrakingY		= 9;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 4.0;
	
	refShip.Height.Bombs.Y				= 1.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 2.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 15.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y				= 1.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// LightCorvette			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CORVETTELIGHT]);
	refShip.Name            			= "CorvetteLight";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(500);
	refShip.Capacity        			= 1400;
	refShip.CannonsQuantity						= 22;
	refShip.rcannon 							= 9;
	refShip.lcannon 							= 9;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 170;
	refShip.MinCrew         				= 34;
	refShip.SpeedRate				= 16.8;
	refShip.TurnRate        		= 60;
	refShip.Price           			= 244000;
	refShip.HP              				= 2700;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.2;
	refShip.sea_enchantment				= 1.5;
	refShip.lowpolycrew = 16;
	refShip.buildtime = 80;

	refship.Rocking.y = 0.8;
	refship.Rocking.az = 0.025;
	
	refship.WaterLine							= -0.6;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.7;
	refship.TurnDependWeight			= 0.35;
	refship.WindAgainstSpeed   = 5.8;//boal
	refship.CabinType          = "New_Cabin2"; // boal 28.03.05
	refship.DeckType           			= "Medium";
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.17;
	refship.Track1.LifeTime = 12.5;
	refship.Track1.Width	= "4.0, 5.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6.5;
	refship.Track2.Width	= "5.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// PacketBrig			����. ����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_PACKET_BRIG]);
	refShip.Name            			= "Packet_Brig";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(500);
	refShip.Capacity        			= 1900;
	refShip.CannonsQuantity				= 22;
	refShip.rcannon 							= 9;
	refShip.lcannon 							= 9;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 170;
	refShip.MinCrew         				= 34;
	refShip.SpeedRate       		= 14.5;
	refShip.TurnRate        		= 40;
	refShip.Price           			= 159000;
	refShip.HP              				= 3000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 3;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.04;
	
	refship.WaterLine							= 0.3;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 3.0;//boal
	refship.CabinType          = "New_Cabin1"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 2.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 15.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y				= 1.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// PDN					���. ����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_PDN]);
	refShip.Name            			= "PDN";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(1000);
	refShip.Capacity        			= 1700;
	refShip.CannonsQuantity				= 24;
	refShip.rcannon 							= 10;
	refShip.lcannon 							= 10;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 190;
	refShip.MinCrew         				= 36;
	refShip.SpeedRate				= 14;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 192000;
	refShip.HP              				= 3750;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 3.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refship.WaterLine							= -1.0;
	refship.SpeedDependWeight			= 0.1;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.8;
	refship.WindAgainstSpeed   = 4.5;//boal
	refship.CabinType          = "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y = 1.0; refShip.Height.Bombs.DY = 0.5;
	refShip.Height.Grapes.Y = 2.0; refShip.Height.Grapes.DY = 1.0;
	refShip.Height.Knippels.Y = 10.0; refShip.Height.Knippels.DY = 8.0;
	refShip.Height.Balls.Y = 1.0; refShip.Height.Balls.DY = 0.5;

	refShip.GeraldSails.rey_b1 = 1;
	refShip.GeraldSails.rey_b2 = 1;
	refShip.GeraldSails.rey_b3 = 1;
	refShip.GeraldSails.rey_b1.vscale = 0.9;
	refShip.GeraldSails.rey_b2.vscale = 0.7;
	refShip.GeraldSails.rey_b3.vscale = 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// ENTERPRISE			����. ���-�����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_ENTERPRISE]);
	refShip.Name            			= "Enterprise";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(400);
	refShip.Capacity        			= 1700;
	refShip.CannonsQuantity				= 24;
	refShip.rcannon 							= 10;
	refShip.lcannon 							= 10;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 180;
	refShip.MinCrew         				= 36;
	refShip.SpeedRate       		= 14.5;
	refShip.TurnRate        		= 50;
	refShip.Price           			= 227000;
	refShip.HP              				= 2800;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 4.0;
	refShip.sea_enchantment				= 3;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.04;
	
	refship.WaterLine							= 0,0;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 4.3;//boal
	refship.CabinType          = "New_Cabin2"; // boal 28.03.05
	refship.DeckType           			= "Small";

	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 2.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 15.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y				= 1.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.8;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Polacre_H			������ ������
	///////////////////////////////////////////////////////////////////////////	
	makeref(refShip,ShipsTypes[SHIP_POLACRE_H]);
	refShip.Name						= "Polacre_H";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon  					= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber  				= 16;
	refShip.Weight						= Tonnes2CWT(600);
	refShip.Capacity   					= 2200;
	refShip.CannonsQuantity				= 24;
	refShip.rcannon 							= 10;
	refShip.lcannon 							= 10;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew        					= 170;
	refShip.MinCrew        					= 34;
	refShip.SpeedRate      			= 14;
	refShip.TurnRate       			= 30;
	refShip.Price          				= 247000;
	refShip.HP             					= 3800;
	refShip.SP             					= 100;
	refship.CabinType          			= "New_Cabin2";
	refship.DeckType           			= "Small";
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	
	refShip.lowpolycrew					= 12;

	refship.WindAgainstSpeed   			= 5.0;
		
	refship.Rocking.y	= 0.5;
	refship.Rocking.az	= 0.04;
	
	refship.WaterLine	= 0.0;
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y		= 1.7;		refShip.Height.Bombs.DY	= 0.8;
	refShip.Height.Grapes.Y		= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y	= 10.1;		refShip.Height.Knippels.DY	= 9.2;
	refShip.Height.Balls.Y		= 1.7;		refShip.Height.Balls.DY	= 0.8;
	
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Caravel			���������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CARAVEL]);
	refShip.Name            			= "Caravel";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(500);
	refShip.Capacity        			= 3000;
	refShip.CannonsQuantity				= 30;
	refShip.rcannon 							= 13;
	refShip.lcannon 							= 13;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 195;
	refShip.MinCrew         				= 39;
	refShip.SpeedRate				= 10;
	refShip.TurnRate        		= 29;
	refShip.Price           			= 272000;
	refShip.HP              				= 2300;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= false;
	refShip.fWindAgainstSpeed				= 2;
	refShip.sea_enchantment					= 1.5;
	refShip.lowpolycrew = 16;
	refShip.buildtime = 40;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	refship.CabinType          = "New_Cabin2"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;					
	
	refship.WaterLine							= 1.0;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 4.0;//boal
	
	refship.InertiaAccelerationX	= 3.0;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 3.0;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.Height.Bombs.Y				= 2.7;	refShip.Height.Bombs.DY		= 1.3;
	refShip.Height.Grapes.Y				= 4.3;	refShip.Height.Grapes.DY	= 2.1;
	refShip.Height.Knippels.Y			= 13.0;	refShip.Height.Knippels.DY	= 11.7;
	refShip.Height.Balls.Y				= 2.7;	refShip.Height.Balls.DY		= 1.3;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 10;
	refship.Track1.Width	= "4.0, 5.0";
	refship.Track1.Speed	= "7.2, 9.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "5.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

    ///////////////////////////////////////////////////////////////////////////
    /// FrigateMedium				��. ������
    ///////////////////////////////////////////////////////////////////////////
    makeref(refShip,ShipsTypes[SHIP_FRIGATEMEDIUM]);
    refShip.Name            			= "FrigateMedium";
    refShip.Soundtype					= "corvette";
    refShip.Class						= 4;
    refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
    refShip.MaxCaliber      			= 16;
    refShip.Weight						= Tonnes2CWT(900);
    refShip.Capacity        			= 2300;
    refShip.CannonsQuantity				= 30;
    refShip.rcannon 								= 14;
    refShip.lcannon 								= 14;
    refShip.fcannon 								= 0;
    refShip.bcannon 								= 2;
    refShip.MaxCrew         					= 220;
    refShip.MinCrew         					= 44;
    refShip.SpeedRate				= 13.5;
    refShip.TurnRate        		= 40;
    refShip.Price           			= 130000;
    refShip.HP              				= 4000;
    refShip.SP              				= 100;
    refShip.CanEncounter                    = true;
    refShip.Type.Merchant					= false;
    refShip.Type.War						= true;
    refShip.fWindAgainstSpeed				= 3.0;
    refShip.sea_enchantment					= 1.2;
    refShip.lowpolycrew = 20;
    refShip.buildtime = 100;

    refShip.Rocking.y = 0.4;
    refShip.Rocking.az = 0.035;

    refShip.WaterLine							= 0.2;
    refShip.SpeedDependWeight			= 0.3;
    refShip.SubSeaDependWeight			= 0.6;
    refShip.TurnDependWeight			= 0.4;
    refShip.WindAgainstSpeed   = 4.5;//boal
    refShip.CabinType          = "New_Cabin2";
    refShip.DeckType           = "Medium";

    refShip.InertiaAccelerationX	= 5.0;
    refShip.InertiaBrakingX		= 5.0;
    refShip.InertiaAccelerationY	= 4;
    refShip.InertiaBrakingY		= 4;
    refShip.InertiaAccelerationZ	= 5.0;
    refShip.InertiaBrakingZ		= 5.0;

    refShip.Height.Bombs.Y = 1.0;
    refShip.Height.Bombs.DY = 0.5;
    refShip.Height.Grapes.Y = 2.0;
    refShip.Height.Grapes.DY = 1.0;
    refShip.Height.Knippels.Y = 10.0;
    refShip.Height.Knippels.DY = 8.0;
    refShip.Height.Balls.Y = 1.0;
    refShip.Height.Balls.DY = 0.5;

    refShip.GeraldSails.rey_b1 = 1;
    refShip.GeraldSails.rey_b2 = 1;
    refShip.GeraldSails.rey_b3 = 1;
    refShip.GeraldSails.rey_b1.vscale = 0.9;
    refShip.GeraldSails.rey_b2.vscale = 0.7;
    refShip.GeraldSails.rey_b3.vscale = 0.7;

    refShip.Track.Enable	= true;
    refShip.Track1.ZStart	= 0.20;
    refShip.Track1.LifeTime = 14.5;
    refShip.Track1.Width	= "3.7, 3.9";
    refShip.Track1.Speed	= "7.0, 8.0";

    refShip.Track2.ZStart	= -0.15;
    refShip.Track2.LifeTime = 8.5;
    refShip.Track2.Width	= "8.0, 9.0";
    refShip.Track2.Speed	= "0.15, 0.25";

    //Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// RaaFrigate			��. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_RaaFrigate]);
	refShip.Name            			= "RaaFrigate";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(1000);
	refShip.Capacity        			= 2000;
	refShip.CannonsQuantity				= 32;
	refShip.rcannon 							= 15;
	refShip.lcannon 							= 15;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 0;
	refShip.MaxCrew         				= 250;
	refShip.MinCrew         				= 50;
	refShip.SpeedRate				= 14;
	refShip.TurnRate        		= 40;
	refShip.Price           			= 333000;
	refShip.HP              				= 3500;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 3.0;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refship.WaterLine							= 0.3;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed   = 4.5;//boal
	refship.CabinType          = "New_Cabin2"; // boal 28.03.05
	refship.DeckType           			= "Medium";
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;

    refShip.Height.Bombs.Y = 1.0; refShip.Height.Bombs.DY = 0.5;
	refShip.Height.Grapes.Y = 2.0; refShip.Height.Grapes.DY = 1.0;
	refShip.Height.Knippels.Y = 10.0; refShip.Height.Knippels.DY = 8.0;
	refShip.Height.Balls.Y = 1.0; refShip.Height.Balls.DY = 0.5;

	refShip.GeraldSails.rey_b1 = 1;
	refShip.GeraldSails.rey_b2 = 1;
	refShip.GeraldSails.rey_b3 = 1;
	refShip.GeraldSails.rey_b1.vscale = 0.9;
	refShip.GeraldSails.rey_b2.vscale = 0.7;
	refShip.GeraldSails.rey_b3.vscale = 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Caravel2			����. ���������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CARAVEL2]);
	refShip.Name            			= "Caravel2";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(500);
	refShip.Capacity        			= 2800;
	refShip.CannonsQuantity				= 32;
	refShip.rcannon 							= 13;
	refShip.lcannon 							= 13;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 280;
	refShip.MinCrew         				= 56;
	refShip.SpeedRate				= 10.6;
	refShip.TurnRate        		= 32;
	refShip.Price           			= 317000;
	refShip.HP              				= 2700;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.5;
	refShip.lowpolycrew = 16;
	refShip.buildtime = 40;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	refship.CabinType          = "New_Cabin2"; // boal 28.03.05
	refship.DeckType           			= "Medium";
	
	refship.WaterLine							= 0.11;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.61;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 4.0;//boal
	
	refship.InertiaAccelerationX	= 0.2;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 3.0;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 10;
	refship.Track1.Width	= "4.0, 5.0";
	refship.Track1.Speed	= "7.2, 9.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "5.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// FLEUTWAR			���. ����. �����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FLEUTWAR]);
	refShip.Name            			= "FleutWar";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(405);
	refShip.Capacity        			= 3000;
	refShip.CannonsQuantity				= 34;
	refShip.rcannon 							= 15;
	refShip.lcannon 							= 15;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 200;
	refShip.MinCrew         				= 40;
	refShip.SpeedRate				= 11;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 290000;
	refShip.HP              				= 4500;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.2;
	refShip.sea_enchantment				= 2.1;
	refShip.lowpolycrew = 16;
	refShip.buildtime = 60;
	
	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.35;
	
	refShip.WaterLine = 0.3;
	refShip.SpeedDependWeight = 0.3;
	refShip.SubSeaDependWeight = 0.9;
	refship.TurnDependWeight			= 0.25;
	refship.WindAgainstSpeed   = 4.0;//boal
	refship.CabinType          = "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Medium";
	
	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast5.Flag1 = FLAG_ENSIGN;
	
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;
	
	refShip.InertiaAccelerationX	= 0.2;	refShip.InertiaBrakingX		= 1.0;
	refShip.InertiaAccelerationY	= 8;	refShip.InertiaBrakingY		= 6;
	refShip.InertiaAccelerationZ	= 5.0;	refShip.InertiaBrakingZ		= 4.0;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// FleutWarSat			���. ���. �����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FLEUTWARSAT]);
	refShip.Name            			= "FleutWarSat";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(405);
	refShip.Capacity        			= 2700;
	refShip.CannonsQuantity				= 34;
	refShip.rcannon 							= 15;
	refShip.lcannon 							= 15;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 230;
	refShip.MinCrew         				= 46;
	refShip.SpeedRate				= 12.5;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 279000;
	refShip.HP              				= 4000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.2;
	refShip.sea_enchantment				= 2.1;
	refShip.lowpolycrew = 16;
	refShip.buildtime = 60;
	
	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.35;
	
	refShip.WaterLine = 0.3;
	refShip.SpeedDependWeight = 0.3;
	refShip.SubSeaDependWeight = 0.9;
	refship.TurnDependWeight			= 0.25;
	refship.WindAgainstSpeed   = 4.0;//boal
	refship.CabinType          = "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Medium";
	
	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast5.Flag1 = FLAG_ENSIGN;
	
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;
	
	refShip.InertiaAccelerationX	= 0.2;	refShip.InertiaBrakingX		= 1.0;
	refShip.InertiaAccelerationY	= 8;	refShip.InertiaBrakingY		= 6;
	refShip.InertiaAccelerationZ	= 5.0;	refShip.InertiaBrakingZ		= 4.0;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// GaleonTrader			����. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_GALEONTRADER]);
	refShip.Name            			= "GaleonTrader";
	refship.Soundtype					= "frigate";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity        			= 5000;
	refShip.CannonsQuantity				= 34;
	refShip.rcannon 							= 13;
	refShip.lcannon 							= 13;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 6;
	refShip.MaxCrew         				= 250;
	refShip.MinCrew         				= 50;
	refShip.SpeedRate				= 8;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 320000;
	refShip.HP              				= 2000;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= false;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 80;

	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.02;
	
	refship.WaterLine							= 0.6;

	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 2.6;//boal
	refship.CabinType          = "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Medium";
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Lydia			�������� ������� 
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LYDIA]);
	refShip.Name            			= "Lydia";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;	
	refShip.Weight						= Tonnes2CWT(1100);	
	refShip.Capacity        			= 4000;	
	refShip.CannonsQuantity				= 36;
	refShip.rcannon 							= 15;
	refShip.lcannon 							= 15;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 170;
	refShip.MinCrew         				= 34;	
	refShip.SpeedRate				= 12.5;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 350000;
	refShip.HP              				= 2700;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.lowpolycrew 				= 20;

	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.035;

	refship.WaterLine					= -1.6;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 2.6;
	refship.CabinType          			= "Cabin_Medium2"; 
	refship.DeckType           			= "Medium";
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 3.0;		refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.5;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 24.0;		refShip.Height.Knippels.DY	= 17.0;
	refShip.Height.Balls.Y				= 3.0;		refShip.Height.Balls.DY		= 1.5;

	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Pinnace		�����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_PINNACE]);
	refShip.Name            			= "Pinnace";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(800);
	refShip.Capacity        			= 4000;
	refShip.CannonsQuantity				= 18;
	refShip.rcannon 							= 6;
	refShip.lcannon 							= 6;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew							= 270;
	refShip.MinCrew         				= 54;
	refShip.SpeedRate				= 13;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 115000;
	refShip.HP              				= 4950;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.3;
	refShip.sea_enchantment					= 1.1;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 80;

	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;

	refship.WaterLine							= 0.8;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 1.3;
	refship.TurnDependWeight			= 0.25;
	refship.WindAgainstSpeed   = 6.0;//boal
    refship.CabinType          = "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;					    
	
	refship.InertiaAccelerationX	= 3.0;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 3.0;	refship.InertiaBrakingZ		= 3.0;

	refShip.Height.Bombs.Y				= 3.0;		refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 5.5;		refShip.Height.Grapes.DY	= 2.7;
	refShip.Height.Knippels.Y			= 24.1;		refShip.Height.Knippels.DY	= 20.7;
	refShip.Height.Balls.Y				= 3.0;		refShip.Height.Balls.DY		= 1.5;	
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.85;
	refShip.GeraldSails.rey_b2.vscale		= 0.65;
	refShip.GeraldSails.rey_b3.vscale		= 0.65;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.7, 7.9";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "10.0, 12.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;
	
	///////////////////////////////////////////////////////////////////////////
	/// DutchPinnace			����. �����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_DUTCHPINNACE]);
	refShip.Name            	= "DutchPinnace";
	refship.Soundtype			= "frigate";
	refShip.Class				= 3;
	refShip.Cannon          	= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      	= 24;
	refShip.Weight				= Tonnes2CWT(600);
	refShip.Capacity        	= 3600;
	refShip.CannonsQuantity		= 20;
	refShip.rcannon 					= 8;
	refShip.lcannon 					= 8;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;
	refShip.MaxCrew					= 310;
	refShip.MinCrew         		= 62;
	refShip.SpeedRate		= 12.5;
	refShip.TurnRate        = 30;
	refShip.Price           	= 220000;
	refShip.HP              		= 5000;
	refShip.SP              		= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed	= 1.1;
	refShip.sea_enchantment		= 1.1;
	refShip.lowpolycrew 		= 20;
	refShip.buildtime 		= 80;

	refship.Rocking.y 		= 0.4;
	refship.Rocking.az 		= 0.35;

	refship.WaterLine		= 0.0;
	refship.SpeedDependWeight	= 0.2;
	refship.SubSeaDependWeight	= 1.3;
	refship.TurnDependWeight	= 0.25;
	refship.WindAgainstSpeed   	= 6.0;//boal
    refship.CabinType          	= "New_Cabin2"; // boal 28.03.05
	refship.DeckType           			= "Medium";
	
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
    
	refship.InertiaAccelerationX	= 3.0;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 3.0;	refship.InertiaBrakingZ		= 3.0;

	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.85;
	refShip.GeraldSails.rey_b2.vscale	= 0.65;
	refShip.GeraldSails.rey_b3.vscale	= 0.65;

	refship.Track.Enable		= true;
	refship.Track1.ZStart		= 0.30;
	refship.Track1.LifeTime 	= 14.5;
	refship.Track1.Width		= "5.7, 7.9";
	refship.Track1.Speed		= "6.0, 8.0";

	refship.Track2.ZStart		= -0.15;
	refship.Track2.LifeTime 	= 8.5;
	refship.Track2.Width		= "10.0, 12.0";
	refship.Track2.Speed		= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// LightPinnace			���������. �����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_PINNACELIGHT]);
	refShip.Name            			= "PinnaceLight";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(800);
	refShip.Capacity        			= 3000;
	refShip.CannonsQuantity				= 30;
	refShip.rcannon 						= 12;
	refShip.lcannon 						= 12;
	refShip.fcannon 						= 2;
	refShip.bcannon 						= 4;
	refShip.MaxCrew								= 290;
	refShip.MinCrew         					= 58;
	refShip.SpeedRate				= 13;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 275000;
	refShip.HP              				= 5500;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.3;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 80;

	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;

	refship.WaterLine							= 0.5;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 1.3;
	refship.TurnDependWeight			= 0.25;
	refship.WindAgainstSpeed   = 6.0;//boal
    refship.CabinType          = "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Medium";
    
	refship.InertiaAccelerationX	= 3.0;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 3.0;	refship.InertiaBrakingZ		= 3.0;

	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.85;
	refShip.GeraldSails.rey_b2.vscale		= 0.65;
	refShip.GeraldSails.rey_b3.vscale		= 0.65;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.7, 7.9";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "10.0, 12.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	//////////////////////////////////////////////////////////////////////////
	/// XebekVT			���. ����. ������
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_XEBEKVT]);
	refShip.Name						= "XebekVT";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon  					= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber  				= 24;
	refShip.Weight						= Tonnes2CWT(900);
	refShip.Capacity   					= 2600;
	refShip.CannonsQuantity				= 30;
	refShip.rcannon 							= 13;
	refShip.lcannon 							= 13;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew        					= 240;
	refShip.MinCrew        					= 48;
	refShip.SpeedRate      			= 14.5;
	refShip.TurnRate       			= 45;
	refShip.Price          				= 295000;
	refShip.HP             				= 4600;
	refShip.SP             				= 100;

	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.lowpolycrew					= 21;
	refship.WindAgainstSpeed   			= 8.8;
	refship.CabinType          			= "Cabin_Medium2";
	refship.DeckType           			= "Medium";
	
	refship.Rocking.y	= 0.5;
	refship.Rocking.az	= 0.04;
	
	refship.WaterLine	= -0.1;
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y		= 1.0;		refShip.Height.Bombs.DY	= 1.0;
	refShip.Height.Grapes.Y		= 2.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y	= 16.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y		= 1.0;		refShip.Height.Balls.DY	= 1.0;
	
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";	
	
	refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Felipe			����. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FELIPE]);
	refShip.Name            	= "Felipe";
	refship.Soundtype			= "frigate";
	refShip.Class				= 3;
	refShip.Cannon          	= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      	= 32;
	refShip.Weight				= Tonnes2CWT(900);
	refShip.Capacity        	= 4950;
	refShip.CannonsQuantity		= 30;
	refShip.rcannon 					= 14;
	refShip.lcannon 					= 14;
	refShip.fcannon 					= 0;
	refShip.bcannon 					= 2;
	refShip.MaxCrew         		= 440;
	refShip.MinCrew         		= 88;
	refShip.SpeedRate		= 7.7;
	refShip.TurnRate        = 25;
	refShip.Price           	= 305000;
	refShip.HP              		= 7000;
	refShip.SP              		= 100;
	refship.CanEncounter 		= true;
	refship.Type.Merchant		= true;
	refship.Type.War			= true;
	refShip.fWindAgainstSpeed		= 1.1;
	refShip.sea_enchantment		= 1.2;
	refShip.lowpolycrew 		= 20;
	refShip.buildtime 		= 80;

	
	refship.Rocking.y 		= 0.4;
	refship.Rocking.az 		= 0.41;
	
	refship.WaterLine		= 0.0;

	refship.SpeedDependWeight	= 0.15;
	refship.SubSeaDependWeight	= 0.3;
	refship.TurnDependWeight	= 0.2;
	refship.WindAgainstSpeed   	= 2.6;//boal
	refship.CabinType          	= "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Medium";
	
	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.98;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable		= true;
	refship.Track1.ZStart		= 0.0;
	refship.Track1.LifeTime 	= 14.5;
	refship.Track1.Width		= "5.2, 7.3";
	refship.Track1.Speed		= "5.5, 6.5";

	refship.Track2.ZStart		= -0.15;
	refship.Track2.LifeTime 	= 8.5;
	refship.Track2.Width		= "6.0, 8.0";
	refship.Track2.Speed		= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Shnyava			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CRIMSONBLOOD]);
	refShip.Name            			= "CrimsonBlood";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(600);
	refShip.Capacity        			= 2000;
	refShip.CannonsQuantity				= 30;
	refShip.rcannon 							= 13;
	refShip.lcannon 							= 13;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 250;
	refShip.MinCrew         				= 50;
	refShip.SpeedRate       		= 16.8;
	refShip.TurnRate        		= 55;
	refShip.Price           			= 287000;
	refShip.HP              				= 4200;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 3;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 60;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refShip.WaterLine 					= 0.2;
	refShip.SpeedDependWeight 			= 0.3;
	refShip.SubSeaDependWeight 			= 0.55;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 4.8	;//boal
	refship.CabinType          = "Cabin_Medium"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 2.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 15.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y				= 1.0;		refShip.Height.Balls.DY		= 1.0;
	
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Corvette			������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CORVETTE]);
	refShip.Name            			= "Corvette";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(600);
	refShip.Capacity        			= 2250;
	refShip.CannonsQuantity				= 32;
	refShip.rcannon 							= 13;
	refShip.lcannon 							= 13;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 200;
	refShip.MinCrew         				= 40;
	refShip.SpeedRate				= 16.2;
	refShip.TurnRate        		= 55;
	refShip.Price           			= 308000;
	refShip.HP              				= 4450;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.2;
	refShip.sea_enchantment					= 1.5;
	refShip.lowpolycrew = 16;
	refShip.buildtime = 80;

	refship.Rocking.y = 0.8;
	refship.Rocking.az = 0.025;
	
	refship.WaterLine							= -0.4;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.7;
	refship.TurnDependWeight			= 0.35;
	refship.WindAgainstSpeed   = 4.8;//boal
	refship.CabinType          = "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;					
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.2;		refShip.Height.Bombs.DY		= 0.6;
	refShip.Height.Grapes.Y				= 3.0;		refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y			= 15.4;		refShip.Height.Knippels.DY	= 14.9;
	refShip.Height.Balls.Y				= 1.2;		refShip.Height.Balls.DY		= 0.6;	
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.17;
	refship.Track1.LifeTime = 12.5;
	refship.Track1.Width	= "4.0, 5.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6.5;
	refship.Track2.Width	= "5.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Frigate_l			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FRIGATE_l]);
	refShip.Name            			= "FRIGATE_l";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(600);
	refShip.Capacity        			= 2000;
	refShip.CannonsQuantity				= 32;
	refShip.rcannon 							= 13;
	refShip.lcannon 							= 13;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 260;
	refShip.MinCrew         				= 52;
	refShip.SpeedRate				= 15.7;
	refShip.TurnRate        		= 45;
	refShip.Price           			= 324000;
	refShip.HP              				= 4700;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 4.1;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refship.WaterLine							= 0.15;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed   = 4.5;//boal
	refship.CabinType          = "New_Cabin2"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;

    refShip.Height.Bombs.Y = 1.0; refShip.Height.Bombs.DY = 0.5;
	refShip.Height.Grapes.Y = 2.0; refShip.Height.Grapes.DY = 1.0;
	refShip.Height.Knippels.Y = 10.0; refShip.Height.Knippels.DY = 8.0;
	refShip.Height.Balls.Y = 1.0; refShip.Height.Balls.DY = 0.5;

	refShip.GeraldSails.rey_b1 = 1;
	refShip.GeraldSails.rey_b2 = 1;
	refShip.GeraldSails.rey_b3 = 1;
	refShip.GeraldSails.rey_b1.vscale = 0.9;
	refShip.GeraldSails.rey_b2.vscale = 0.7;
	refShip.GeraldSails.rey_b3.vscale = 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// BattleCorvette			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BATTLECORVETTE]);
	refShip.Name            			= "BattleCorvette";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(600);
	refShip.Capacity        			= 2500;
	refShip.CannonsQuantity				= 32;
	refShip.rcannon 							= 13;
	refShip.lcannon 							= 13;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 230;
	refShip.MinCrew         				= 46;
	refShip.SpeedRate				= 16;
	refShip.TurnRate        		= 45;
	refShip.Price           			= 365000;
	refShip.HP              				= 4800;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.2;
	refShip.sea_enchantment				= 1.5;
	refShip.lowpolycrew 				= 16;
	refShip.buildtime 					= 80;

	refship.Rocking.y = 0.8;
	refship.Rocking.az = 0.025;
	
	refship.WaterLine = 0.1;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.6;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 3.8;//boal
	refship.CabinType          = "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refShip.Height.Bombs.Y				= 1.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 18.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y				= 1.0;		refShip.Height.Balls.DY		= 1.0;
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.17;
	refship.Track1.LifeTime = 12.5;
	refship.Track1.Width	= "4.0, 5.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6.5;
	refship.Track2.Width	= "5.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Black Angel			������ ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BLACKANGEL]);
	refShip.Name            			= "BlackAngel";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(600);
	refShip.Capacity        			= 2000;
	refShip.CannonsQuantity				= 32;
	refShip.rcannon 							= 13;
	refShip.lcannon 							= 13;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 200;
	refShip.MinCrew         				= 40;
	refShip.SpeedRate				= 15.5;
	refShip.TurnRate        		= 50;
	refShip.Price           			= 358000;
	refShip.HP              				= 4000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.2;
	refShip.sea_enchantment				= 1.5;
	refShip.lowpolycrew 				= 16;
	refShip.buildtime 					= 80;

	refship.Rocking.y = 0.8;
	refship.Rocking.az = 0.025;
	
	refship.WaterLine = 0.1;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.6;
	refship.TurnDependWeight = 0.4;
	refship.TurnDependWeight			= 0.35;
	refship.WindAgainstSpeed   = 4.8;//boal
	refship.CabinType          = "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refShip.Height.Bombs.Y				= 1.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 18.0;		refShip.Height.Knippels.DY	= 10.0;
	refShip.Height.Balls.Y				= 1.0;		refShip.Height.Balls.DY		= 1.0;
	
	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.17;
	refship.Track1.LifeTime = 12.5;
	refship.Track1.Width	= "4.0, 5.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6.5;
	refship.Track2.Width	= "5.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

    ///////////////////////////////////////////////////////////////////////////
    /// CoastalFrigate				��������� ������
    ///////////////////////////////////////////////////////////////////////////
    makeref(refShip,ShipsTypes[SHIP_COASTALFRIGATE]);
    refShip.Name            			= "CoastalFrigate";
    refShip.Soundtype					= "corvette";
    refShip.Class						= 3;
    refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
    refShip.MaxCaliber      			= 24;
    refShip.Weight						= Tonnes2CWT(900);
    refShip.Capacity        			= 3200;
    refShip.CannonsQuantity				= 32;
    refShip.rcannon 								= 15;
    refShip.lcannon 								= 15;
    refShip.fcannon 								= 0;
    refShip.bcannon 								= 2;
    refShip.MaxCrew         					= 290;
    refShip.MinCrew         					= 58;
    refShip.SpeedRate				= 15;
    refShip.TurnRate        		= 45;
    refShip.Price           			= 135000;
    refShip.HP              				= 4800;
    refShip.SP              				= 100;
    refShip.CanEncounter                	= true;
    refShip.Type.Merchant					= false;
    refShip.Type.War						= true;
    refShip.fWindAgainstSpeed				= 3.0;
    refShip.sea_enchantment					= 1.2;
    refShip.lowpolycrew = 20;
    refShip.buildtime = 100;

    refShip.Rocking.y = 0.4;
    refShip.Rocking.az = 0.035;

    refShip.WaterLine							= 0.2;
    refShip.SpeedDependWeight			= 0.3;
    refShip.SubSeaDependWeight			= 0.6;
    refShip.TurnDependWeight			= 0.4;
    refShip.WindAgainstSpeed   = 4.5;//boal
    refShip.CabinType          = "New_Cabin2";
    refShip.DeckType           = "Frigate";

    refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;

    refShip.Height.Bombs.Y = 1.0;
    refShip.Height.Bombs.DY = 0.5;
    refShip.Height.Grapes.Y = 2.0;
    refShip.Height.Grapes.DY = 1.0;
    refShip.Height.Knippels.Y = 10.0;
    refShip.Height.Knippels.DY = 8.0;
    refShip.Height.Balls.Y = 1.0;
    refShip.Height.Balls.DY = 0.5;

    refShip.GeraldSails.rey_b1 = 1;
    refShip.GeraldSails.rey_b2 = 1;
    refShip.GeraldSails.rey_b3 = 1;
    refShip.GeraldSails.rey_b1.vscale = 0.9;
    refShip.GeraldSails.rey_b2.vscale = 0.7;
    refShip.GeraldSails.rey_b3.vscale = 0.7;

    refShip.Track.Enable	= true;
    refShip.Track1.ZStart	= 0.20;
    refShip.Track1.LifeTime = 14.5;
    refShip.Track1.Width	= "3.7, 3.9";
    refShip.Track1.Speed	= "7.0, 8.0";

    refShip.Track2.ZStart	= -0.15;
    refShip.Track2.LifeTime = 8.5;
    refShip.Track2.Width	= "8.0, 9.0";
    refShip.Track2.Speed	= "0.15, 0.25";

    //Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// FR_Frigate			���������� ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FR_FRIGATE]);
	refShip.Name            			= "FR_Frigate";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1000);
	refShip.Capacity        			= 2400;
	refShip.CannonsQuantity				= 36;
	refShip.rcannon 							= 16;
	refShip.lcannon 							= 16;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 330;
	refShip.MinCrew         				= 66;
	refShip.SpeedRate       		= 14.5;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 370000;
	refShip.HP              				= 5800;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;
	
	refShip.WaterLine					= 0.3;
	refShip.SpeedDependWeight 			= 0.3;
	refShip.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 4.6;//boal
	refship.CabinType          = "New_Cabin2"; // boal 28.03.05
	refship.DeckType           			= "Frigate";
	
	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 3.0;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.5;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 24.0;	refShip.Height.Knippels.DY	= 17.0;
	refShip.Height.Balls.Y				= 3.0;	refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Jamaicaship			���. �����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_JAMAICASHIP]);
	refShip.Name            			= "Jamaicaship";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity        			= 4500;
	refShip.CannonsQuantity				= 36;
	refShip.rcannon 							= 16;
	refShip.lcannon 							= 16;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 300;
	refShip.MinCrew         				= 60;
	refShip.SpeedRate       		= 12;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 340000;
	refShip.HP              				= 5000;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;
	
	refship.WaterLine							= -1.0;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 2.6;//boal
	refship.CabinType          = "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Frigate";
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 3.0;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.5;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 24.0;	refShip.Height.Knippels.DY	= 17.0;
	refShip.Height.Balls.Y				= 3.0;	refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// TheBlackPearl			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_THEBLACKPEARL]);
	refShip.Name            		= "TheBlackPearl";
	refship.Soundtype				= "frigate";
	refShip.Class					= 3;
	refShip.Cannon          		= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      		= 24;
	refShip.Weight					= Tonnes2CWT(1000);
	refShip.Capacity        		= 4000;
	refShip.CannonsQuantity			= 36;
	refShip.rcannon 						= 16;
	refShip.lcannon 						= 16;
	refShip.fcannon 						= 2;
	refShip.bcannon 						= 2;
	refShip.MaxCrew         			= 390;
	refShip.MinCrew         			= 78;
	refShip.SpeedRate       	= 9;
	refShip.TurnRate        	= 25;
	refShip.Price           		= 380000;
	refShip.HP              			= 6500;
	refShip.SP              			= 100;
	refship.CanEncounter			= true;
	refship.Type.Merchant			= false;
	refship.Type.War				= true;
	refShip.fWindAgainstSpeed		= 2.0;
	refShip.sea_enchantment			= 1.2;
	refShip.lowpolycrew 			= 20;
	refShip.buildtime 				= 100;
	
	refship.Rocking.y 				= 0.4;
	refship.Rocking.az 				= 0.035;
	
	refship.WaterLine				= 0.5;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 2.6;//boal
	refship.CabinType          			= "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Medium";
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;
	
	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime 			= 14.5;
	refship.Track1.Width				= "3.7, 3.9";
	refship.Track1.Speed				= "7.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime 			= 8.5;
	refship.Track2.Width				= "8.0, 9.0";
	refship.Track2.Speed				= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Galeon HEAVY			������ ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_GALEON_H]);
	refShip.Name            			= "Galeon_h";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity        			= 4650;
	refShip.CannonsQuantity				= 36;
	refShip.rcannon 							= 15;
	refShip.lcannon 							= 15;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 400;
	refShip.MinCrew         				= 80;
	refShip.SpeedRate				= 8;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 365000;
	refShip.HP              				= 6200;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 80;
	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.02;
	
	refship.WaterLine							= -0.2;

	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 2.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;					
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;

	refShip.Height.Bombs.Y				= 3.0;		refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.4;		refShip.Height.Grapes.DY	= 2.2;
	refShip.Height.Knippels.Y			= 21.4;		refShip.Height.Knippels.DY	= 19.8;
	refShip.Height.Balls.Y				= 3.0;		refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Galeon1			���. ���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_GALEON1]);
	refShip.Name            			= "Galeon1";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity        			= 5950;
	refShip.CannonsQuantity				= 38;
	refShip.rcannon 							= 16;
	refShip.lcannon 							= 16;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 520;
	refShip.MinCrew         				= 104;
	refShip.SpeedRate				= 7.5;
	refShip.TurnRate        		= 20;
	refShip.Price           			= 384000;
	refShip.HP              				= 7800;
	refShip.SP              				= 100;
	refship.CanEncounter 					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 1.2;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 80;

	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.35;
	
	refship.WaterLine							= 0.2;

	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.4;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 2.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Frigate";
	
	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";	

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// La_Marianna			���������� ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LA_MARIANNA]);
	refShip.Name            			= "La_Marianna";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1700);
	refShip.Capacity        			= 4800;
	refShip.CannonsQuantity				= 38;
	refShip.rcannon 							= 16;
	refShip.lcannon 							= 16;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 380;
	refShip.MinCrew         				= 76;
	refShip.SpeedRate				= 9;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 404000;
	refShip.HP              				= 5600;
	refShip.SP              				= 100;
	refship.CanEncounter 				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.2;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 80;

	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.35;
	
	refShip.WaterLine = -0.48;
	refShip.SpeedDependWeight = 0.3;
	refShip.SubSeaDependWeight = 1.0;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 4.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;
	
	refShip.GeraldSails.rey_b2 = 1;
	refShip.GeraldSails.rey_b3 = 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";	

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// PiratFastGal			���. ������� ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_PIRATFASTGAL]);
	refShip.Name            			= "PiratFastGal";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1700);
	refShip.Capacity        			= 4000;
	refShip.CannonsQuantity				= 38;
	refShip.rcannon 							= 16;
	refShip.lcannon 							= 16;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 350;
	refShip.MinCrew         				= 70;
	refShip.SpeedRate				= 10.5;
	refShip.TurnRate        		= 20;
	refShip.Price           			= 364000;
	refShip.HP              				= 6300;
	refShip.SP              				= 100;
	refship.CanEncounter 				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.2;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 80;

	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.35;
	
	refShip.WaterLine = -0.7;
	refShip.SpeedDependWeight = 0.3;
	refShip.SubSeaDependWeight = 0.5;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 3.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Medium";
	
	refShip.Flags.Mast1.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast4.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast5.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;
	
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";	

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	///  Unicorn			������������ ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_UNICORN]);
	refShip.Name            			= "Unicorn";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(1000);
	refShip.Capacity        			= 3300;
	refShip.CannonsQuantity				= 38;
	refShip.rcannon 							= 18;
	refShip.lcannon 							= 18;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 0;
	refShip.MaxCrew         				= 360;
	refShip.MinCrew         				= 72;
	refShip.SpeedRate       		= 13.5;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 390000;
	refShip.HP              				= 6300;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 3.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew 				= 20;
	refShip.buildtime 					= 220;

	
	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refship.WaterLine		= -0.35;

	refship.SpeedDependWeight	= 0.3;
	refship.SubSeaDependWeight	= 1.0;
	refship.TurnDependWeight	= 0.3;
	refship.WindAgainstSpeed  	= 5.5;//boal
	refship.CabinType          	= "New_Cabin2"; // boal 28.03.05
	refship.DeckType           			= "Frigate";
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y		= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y		= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y	= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y		= 1.0;	refShip.Height.Balls.DY		= 0.5;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.9;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable		= true;
	refship.Track1.ZStart		= 0.20;
	refship.Track1.LifeTime 	= 14.5;
	refship.Track1.Width		= "3.7, 3.9";
	refship.Track1.Speed		= "7.0, 8.0";

	refship.Track2.ZStart		= -0.15;
	refship.Track2.LifeTime 	= 8.5;
	refship.Track2.Width		= "8.0, 9.0";
	refship.Track2.Speed		= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Revenge			������ ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_REVENGE]);
	refShip.Name            			= "Revenge";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity        			= 4000;
	refShip.CannonsQuantity				= 40;
	refShip.rcannon 							= 19;
	refShip.lcannon 							= 19;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 400;
	refShip.MinCrew         				= 80;
	refShip.SpeedRate				= 8;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 725000;
	refShip.HP              				= 7000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;

	refShip.fWindAgainstSpeed			= 1.6;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew                             = 20;
	refShip.buildtime                               = 80;


	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;

	refship.WaterLine				= 0.0;

	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed                        = 2.6;//boal
	refship.CabinType          			= "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;

	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Linefrigate			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LINEFRIGATE]);
	refShip.Name            			= "Linefrigate";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(1700);
	refShip.Capacity        			= 3500;
	refShip.CannonsQuantity				= 40;
	refShip.rcannon 							= 17;
	refShip.lcannon 							= 17;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 380;
	refShip.MinCrew         				= 76;
	refShip.SpeedRate       		= 14;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 680000;
	refShip.HP              				= 5000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 4.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refship.WaterLine							= 0.86;
	
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 3.5;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Frigate";

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// LightFrigate			����. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LIGHTFRIGATE]);
	refShip.Name            			= "LightFrigate";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity        			= 4000;
	refShip.CannonsQuantity				= 40;
	refShip.rcannon 							= 17;
	refShip.lcannon 							= 17;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 420;
	refShip.MinCrew         				= 84;
	refShip.SpeedRate				= 13.7;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 600000;
	refShip.HP              				= 6500;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;

	refship.WaterLine = 0.0;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.9;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 2.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Frigate";
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY	= 3.5;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.0;

	refShip.Height.Bombs.Y				= 3.0;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.5;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 24.0;	refShip.Height.Knippels.DY	= 17.0;
	refShip.Height.Balls.Y				= 3.0;	refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.9;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Boussole			���. ����. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BOUSSOLE]);
	refShip.Name 				= "Boussole";
	refship.Soundtype 			= "frigate";
	refShip.Class 				= 3;
	refShip.Cannon 				= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber 			= 24;
	refShip.Weight 				= Tonnes2CWT(1000);
	refShip.Capacity 			= 2300;
	refShip.CannonsQuantity 	= 42;
	refShip.rcannon 					= 19;
	refShip.lcannon 					= 19;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;
	refShip.MaxCrew 				= 280;
	refShip.MinCrew 				= 56;
	refShip.SpeedRate 		= 15.2;
	refShip.TurnRate 		= 30;
	refShip.Price 				= 615000;
	refShip.HP 						= 5150;
	refShip.SP  					= 100;
	refship.CanEncounter		= true;
	refship.Type.Merchant 		= false;
	refship.Type.War 			= true;
	refShip.fWindAgainstSpeed 	= 3.3;
	refShip.sea_enchantment 	= 1.2;
	refShip.lowpolycrew 		= 20;
	refShip.buildtime 		= 100;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;

	refship.WaterLine 		= 0.50;
	refship.SpeedDependWeight 	= 0.3;
	refship.SubSeaDependWeight 	= 1.0;
	refship.TurnDependWeight 	= 0.4;
	refship.WindAgainstSpeed 	= 4.5;//boal
	refship.CabinType 		= "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;

	refShip.Height.Bombs.Y = 1.0; refShip.Height.Bombs.DY = 0.5;
	refShip.Height.Grapes.Y = 2.0; refShip.Height.Grapes.DY = 1.0;
	refShip.Height.Knippels.Y = 10.0; refShip.Height.Knippels.DY = 8.0;
	refShip.Height.Balls.Y = 1.0; refShip.Height.Balls.DY = 0.5;
	
	refShip.GeraldSails.rey_b1 = 1;
	refShip.GeraldSails.rey_b2 = 1;
	refShip.GeraldSails.rey_b3 = 1;
	refShip.GeraldSails.rey_b1.vscale = 0.9;
	refShip.GeraldSails.rey_b2.vscale = 0.7;
	refShip.GeraldSails.rey_b3.vscale = 0.7;

	refship.Track.Enable = true;
	refship.Track1.ZStart = 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width = "3.7, 3.9";
	refship.Track1.Speed = "7.0, 8.0";

	refship.Track2.ZStart = -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width = "8.0, 9.0";
	refship.Track2.Speed = "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Surprise			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SURPRISE]);
	refShip.Name 						= "Surprise";
	refship.Soundtype 					= "frigate";
	refShip.Class 						= 3;
	refShip.Cannon 						= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber 					= 24;
	refShip.Weight 						= Tonnes2CWT(900);
	refShip.Capacity 					= 3300;
	refShip.CannonsQuantity 			= 42;
	refShip.rcannon 							= 19;
	refShip.lcannon 							= 19;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew 						= 320;
	refShip.MinCrew 						= 64;
	refShip.SpeedRate 				= 14;
	refShip.TurnRate 				= 35;
	refShip.Price 						= 810000;
	refShip.HP 								= 5600;
	refShip.SP 								= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed = 2.0;
	refShip.sea_enchantment = 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;

	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;
	refship.WaterLine = 0.1;

	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 1.0;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed = 4.5;//boal
	refship.CabinType 					= "Cabin_Medium2"; // boal 28.03.05
	refship.DeckType           			= "Frigate";

	refship.InertiaAccelerationX = 5.0; refship.InertiaBrakingX = 5.0;
	refship.InertiaAccelerationY = 4; refship.InertiaBrakingY = 4;
	refship.InertiaAccelerationZ = 5.0; refship.InertiaBrakingZ = 5.0;

	refShip.Height.Bombs.Y = 1.0; refShip.Height.Bombs.DY = 0.5;
	refShip.Height.Grapes.Y = 2.0; refShip.Height.Grapes.DY = 1.0;
	refShip.Height.Knippels.Y = 10.0; refShip.Height.Knippels.DY = 8.0;
	refShip.Height.Balls.Y = 1.0; refShip.Height.Balls.DY = 0.5;

	refShip.GeraldSails.rey_b1 = 1;
	refShip.GeraldSails.rey_b2 = 1;
	refShip.GeraldSails.rey_b3 = 1;
	refShip.GeraldSails.rey_b1.vscale = 0.9;
	refShip.GeraldSails.rey_b2.vscale = 0.7;
	refShip.GeraldSails.rey_b3.vscale = 0.7;

	refship.Track.Enable = true;
	refship.Track1.ZStart = 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width = "3.7, 3.9";
	refship.Track1.Speed = "7.0, 8.0";

	refship.Track2.ZStart = -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width = "8.0, 9.0";
	refship.Track2.Speed = "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Salamander			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SALAMANDER]);
	refShip.Name            			= "Salamander";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1000);
	refShip.Capacity        			= 2700;
	refShip.CannonsQuantity				= 44;
	refShip.rcannon 							= 19;
	refShip.lcannon 							= 19;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 300;
	refShip.MinCrew         				= 60;
	refShip.SpeedRate       		= 15;
	refShip.TurnRate        		= 45;
	refShip.Price           			= 736000;
	refShip.HP              				= 5400;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;

	refship.WaterLine = -0.8;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.9;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 3.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Frigate";

	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y			= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y			= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y		= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y			= 1.0;	refShip.Height.Balls.DY		= 0.5;
	
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Frigate_sat			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FRIGATE_SAT]);
	refShip.Name            			= "Frigate_sat";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity        			= 3600;
	refShip.CannonsQuantity				= 44;
	refShip.rcannon 							= 19;
	refShip.lcannon 							= 19;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 300;
	refShip.MinCrew         				= 60;
	refShip.SpeedRate       		= 13.5;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 710000;
	refShip.HP              				= 6000;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;

	refship.WaterLine = 0.2;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.9;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 3.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Frigate";
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y				= 3.0;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.5;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 24.0;	refShip.Height.Knippels.DY	= 17.0;
	refShip.Height.Balls.Y				= 3.0;	refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// BattleFrigate			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BATTLEFRIGATE]);
	refShip.Name            			= "BattleFrigate";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity        			= 2500;
	refShip.CannonsQuantity				= 44;
	refShip.rcannon 							= 19;
	refShip.lcannon 							= 19;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 350;
	refShip.MinCrew         				= 70;
	refShip.SpeedRate       		= 14;
	refShip.TurnRate        		= 45;
	refShip.Price           			= 760000;
	refShip.HP              				= 5800;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;
	
	refship.WaterLine 			= 0.3;
	refship.SpeedDependWeight 		= 0.3;
	refship.SubSeaDependWeight 		= 1.0;
	refship.TurnDependWeight 		= 0.4;
	refship.WindAgainstSpeed   = 3.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Frigate";

	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 3.0;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.5;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 24.0;	refShip.Height.Knippels.DY	= 17.0;
	refShip.Height.Balls.Y				= 3.0;	refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b3.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Nightmare			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_NIGHTMARE]);
	refShip.Name            			= "Nightmare";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1000);
	refShip.Capacity        			= 2800;
	refShip.CannonsQuantity						= 44;
	refShip.rcannon 							= 19;
	refShip.lcannon 							= 19;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 330;
	refShip.MinCrew         				= 66;
	refShip.SpeedRate       		= 15;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 740000;
	refShip.HP              				= 5000;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;

	refship.WaterLine = -1.0;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.9;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 3.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Frigate";
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y				= 3.0;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.5;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 24.0;	refShip.Height.Knippels.DY	= 17.0;
	refShip.Height.Balls.Y				= 3.0;	refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Mordaunt			������ ��������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_MORDAUNT]);
	refShip.Name            			= "Mordaunt";
	refship.Soundtype					= "lineship";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(860);
	refShip.Capacity        			= 2100;
	refShip.CannonsQuantity 			= 46;
	refShip.rcannon 							= 20;
	refShip.lcannon 							= 20;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 310;
	refShip.MinCrew         				= 62;
	refShip.SpeedRate       		= 15;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 700000;
	refShip.HP              				= 5800;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y 						= 0.5;
	refship.Rocking.az 						= 0.035;

	refship.WaterLine = -0.5;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.9;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 3.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Frigate";

	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y = 2.7;			refShip.Height.Bombs.DY = 1.3;
	refShip.Height.Grapes.Y = 4.3;			refShip.Height.Grapes.DY = 2.1;
	refShip.Height.Knippels.Y = 13.0;		refShip.Height.Knippels.DY = 11.7;
	refShip.Height.Balls.Y = 2.7;			refShip.Height.Balls.DY = 1.3;
	
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;

	refship.Track.Enable					= true;
	refship.Track1.ZStart					= 0.25;
	refship.Track1.LifeTime				 	= 16.5;
	refship.Track1.Width					= "6.0, 8.2";
	refship.Track1.Speed					= "9.0, 9.0";

	refship.Track2.ZStart					= 0.0;
	refship.Track2.LifeTime 				= 13.5;
	refship.Track2.Width					= "8.0, 9.0";
	refship.Track2.Speed					= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Frigate			������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FRIGATE]);
	refShip.Name            			= "Frigate";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1000);
	refShip.Capacity        			= 3000;
	refShip.CannonsQuantity				= 46;
	refShip.rcannon 							= 20;
	refShip.lcannon 							= 20;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 300;
	refShip.MinCrew         				= 60;
	refShip.SpeedRate       		= 14.3;
	refShip.TurnRate        		= 38;
	refShip.Price           			= 661000;
	refShip.HP              				= 5400;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;

	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;
	
	refship.WaterLine							= 0.5;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 3.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Frigate";
	
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 3.7;	refShip.Height.Bombs.DY		= 1.8;
	refShip.Height.Grapes.Y				= 5.2;	refShip.Height.Grapes.DY	= 2.6;
	refShip.Height.Knippels.Y			= 24.0;	refShip.Height.Knippels.DY	= 19.7;
	refShip.Height.Balls.Y				= 3.7;	refShip.Height.Balls.DY		= 1.8;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refShip.hullNums = 5; // LEO
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Amsterdam			������ 3-�� ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_AMSTERDAM]);
	refShip.Name            			= "Amsterdam";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(1000);
	refShip.Capacity        			= 2800;
	refShip.CannonsQuantity				= 50;
	refShip.rcannon 							= 22;
	refShip.lcannon 							= 22;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 350;
	refShip.MinCrew         				= 70;
	refShip.SpeedRate       		= 12.5;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 814000;
	refShip.HP              				= 4900;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.2;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;

	refship.WaterLine = -0.13;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.43;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 3.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Medium";
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y				= 3.0;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.5;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 24.0;	refShip.Height.Knippels.DY	= 17.0;
	refShip.Height.Balls.Y				= 3.0;	refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Carraca			�������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CARRACA]);
	refShip.Name            			= "Carraca";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(2500);
	refShip.Capacity        			= 6500;
	refShip.CannonsQuantity				= 56;
	refShip.rcannon 							= 26;
	refShip.lcannon 							= 26;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 550;
	refShip.MinCrew         				= 110;
	refShip.SpeedRate				= 7;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 690000;
	refShip.HP              				= 7200;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 1.3;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 80;

	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.02;
	
	refship.WaterLine							= 0.0;

	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 1.1;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 2.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 4;	refship.InertiaBrakingX		= 2.5;
	refship.InertiaAccelerationY	= 2;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 3.5;	refship.InertiaBrakingZ		= 4.5;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Galeon50			������������� ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_GALEON50]);
	refShip.Name            		= "Galeon50";
	refship.Soundtype				= "frigate";
	refShip.Class					= 2;
	refShip.Cannon          		= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      		= 32;
	refShip.Weight					= Tonnes2CWT(2300);
	refShip.Capacity        		= 7500;
	refShip.CannonsQuantity			= 40;
	refShip.rcannon 						= 17;
	refShip.lcannon 						= 17;
	refShip.fcannon 						= 2;
	refShip.bcannon 						= 4;
	refShip.MaxCrew         			= 540;
	refShip.MinCrew         			= 108;
	refShip.SpeedRate			= 8.8;
	refShip.TurnRate        	= 25;
	refShip.Price           		= 850000;
	refShip.HP              			= 7000;
	refShip.SP              			= 100;
	refship.CanEncounter			= true;
	refship.Type.Merchant			= true;
	refship.Type.War				= true;

	refShip.fWindAgainstSpeed		= 1.6;
	refShip.sea_enchantment			= 1.2;
	refShip.lowpolycrew				= 20;
	refShip.buildtime				= 80;

	refship.Rocking.y 				= 0.5;
	refship.Rocking.az 				= 0.15;

	refShip.WaterLine 				= 0.0;
	refShip.SpeedDependWeight 		= 0.3;
	refShip.SubSeaDependWeight 		= 1.0;
	refShip.TurnDependWeight 		= 0.4;
	refship.WindAgainstSpeed		= 3.0;//boal
	refship.CabinType          		= "Cabin"; // boal 28.03.05
	refship.DeckType           		= "Medium";
	
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast4.Flag2 = FLAG_ENSIGN;

	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;

	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// FastFrigate			������ ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FASTFRIGATE]);
	refShip.Name            			= "FastFrigate";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(920);
	refShip.Capacity        			= 3200;
	refShip.CannonsQuantity				= 42;
	refShip.rcannon 							= 17;
	refShip.lcannon 							= 17;
	refShip.fcannon 							= 4;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 320;
	refShip.MinCrew         				= 64;
	refShip.SpeedRate       		= 15.5;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 585000;
	refShip.HP              				= 6000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;

	refShip.lowpolycrew 				= 20;
	
	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.035;	
	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 5.0;
	refship.CabinType          			= "Cabin"; 
	refship.DeckType           			= "Frigate";
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 3.4;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 5.3;	refShip.Height.Grapes.DY	= 1.575;
	refShip.Height.Knippels.Y			= 19.5;	refShip.Height.Knippels.DY	= 13.5;
	refShip.Height.Balls.Y				= 3.4;	refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// FR_Essex			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FR_ESSEX]);
	refShip.Name            			= "FR_Essex";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1300);
	refShip.Capacity        			= 3700;
	refShip.CannonsQuantity				= 46;
	refShip.rcannon 							= 21;
	refShip.lcannon 							= 21;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 350;
	refShip.MinCrew         				= 70;
	refShip.SpeedRate       		= 15;
	refShip.TurnRate        		= 40;
	refShip.Price           			= 861000;
	refShip.HP              				= 7000;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;

	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;
	
	refShip.WaterLine = 0.0;
	refShip.SpeedDependWeight = 0.3;
	refShip.SubSeaDependWeight = 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 3.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Frigate";
	
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 3.7;	refShip.Height.Bombs.DY		= 1.8;
	refShip.Height.Grapes.Y				= 5.2;	refShip.Height.Grapes.DY	= 2.6;
	refShip.Height.Knippels.Y			= 24.0;	refShip.Height.Knippels.DY	= 19.7;
	refShip.Height.Balls.Y				= 3.7;	refShip.Height.Balls.DY		= 1.8;
	
	refShip.GeraldSails.rey_a22	= 1;
	refShip.GeraldSails.rey_c2	= 1;
	refShip.GeraldSails.rey_a33	= 1;
	refShip.GeraldSails.rey_c3	= 1;
	refShip.GeraldSails.rey_c4	= 1;
	refShip.GeraldSails.rey_b4	= 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Frigate_h			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FRIGATE_H]);
	refShip.Name            			= "Frigate_h";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(1200);
	refShip.Capacity        			= 3500;
	refShip.CannonsQuantity				= 50;
	refShip.rcannon 							= 20;
	refShip.lcannon 							= 20;
	refShip.fcannon 							= 4;
	refShip.bcannon 							= 6;	
	refShip.MaxCrew         				= 320;
	refShip.MinCrew         				= 64;
	refShip.SpeedRate       		= 14.5;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 750000;
	refShip.HP              				= 6400;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.lowpolycrew 				= 20;
	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.035;	
	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   			= 4.4;
	refship.CabinType          			= "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Frigate";
		
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 2.7;		refShip.Height.Bombs.DY		= 1.35;
	refShip.Height.Grapes.Y				= 5.325;	refShip.Height.Grapes.DY	= 1.575;
	refShip.Height.Knippels.Y			= 19.5;		refShip.Height.Knippels.DY	= 13.5;
	refShip.Height.Balls.Y				= 2.7;		refShip.Height.Balls.DY		= 1.35;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.spain	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;

	///////////////////////////////////////////////////////////////////////////
	/// WarGalleon2			���. ����. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_WARGALLEON2]);
	refShip.Name            			= "WarGalleon2";
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity        			= 5500;
	refShip.CannonsQuantity				= 52;
	refShip.rcannon 							= 22;
	refShip.lcannon 							= 22;
	refShip.fcannon 							= 4;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 510;
	refShip.MinCrew         				= 85;
	refShip.SpeedRate				= 8.5;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 890000;
	refShip.HP              				= 7500;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 80;

	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.02;
	
	refship.WaterLine							= 0.2;

	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 2.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Lineship";
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// NL_PinnaceofWar47			���. ����. �����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_NL_PINNACEOFWAR47]);
	refShip.Name            			= "NL_PinnaceofWar47";
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity        			= 5000;
	refShip.CannonsQuantity				= 54;
	refShip.rcannon 							= 23;
	refShip.lcannon 							= 23;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 6;
	refShip.MaxCrew         				= 400;
	refShip.MinCrew         				= 108;
	refShip.SpeedRate				= 11;
	refShip.TurnRate        		= 28;
	refShip.Price           			= 870000;
	refShip.HP              				= 6500;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 80;

	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.02;
	
	refShip.WaterLine = 0.5;
	refShip.SpeedDependWeight = 0.3;
	refShip.SubSeaDependWeight = 1.1;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   = 2.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           = "Lineship";

	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.GeraldSails.rey_a2	= 1;
	refShip.GeraldSails.rey_a3	= 1;
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// HollGaleon_h			���. ����. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_HOLLGALEON_H]);
	refShip.Name            			= "HollGaleon_h";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(1050);
	refShip.Capacity        			= 5300;
	refShip.CannonsQuantity				= 54;
	refShip.rcannon 							= 22;
	refShip.lcannon 							= 22;
	refShip.fcannon 							= 4;
	refShip.bcannon 							= 6;	
	refShip.MaxCrew         				= 470;
	refShip.MinCrew         				= 94;	
	refShip.SpeedRate				= 9.2;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 745000;
	refShip.HP              				= 6800;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;	
	refShip.lowpolycrew 				= 20;
	
	refship.Rocking.y 					= 0.4;
	refship.Rocking.az 					= 0.02;
	
	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   			= 3.0;
	refship.CabinType          			= "Cabin";
	refship.DeckType           			= "Big";

	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;

	refShip.Height.Bombs.Y				= 3.0;		refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.4;		refShip.Height.Grapes.DY	= 2.2;
	refShip.Height.Knippels.Y			= 21.4;		refShip.Height.Knippels.DY	= 19.8;
	refShip.Height.Balls.Y				= 3.0;		refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b2				= 1;
	refShip.GeraldSails.rey_b3				= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.0;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "5.2, 7.3";
	refship.Track1.Speed	= "5.5, 6.5";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "6.0, 8.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.spain	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Fearless			����. ����. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FEARLESS]);
	refShip.Name            			= "Fearless";
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity        			= 4000;
	refShip.CannonsQuantity				= 56;
	refShip.rcannon 							= 25;
	refShip.lcannon 							= 25;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 400;
	refShip.MinCrew         				= 80;
	refShip.SpeedRate       		= 13.5;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 870000;
	refShip.HP              				= 7000;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 2.0;
	refShip.sea_enchantment					= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;

	refship.WaterLine = 0.0;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.9;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 3.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Lineship";

	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y			= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y			= 2.0;	refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y		= 10.0;	refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y			= 1.0;	refShip.Height.Balls.DY		= 0.5;
	
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Lineship			����. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LINESHIP]);
	refShip.Name            			= "Lineship";
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(2000);
	refShip.Capacity        			= 4350;
	refShip.CannonsQuantity				= 56;
	refShip.rcannon 							= 25;
	refShip.lcannon 							= 25;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 420;
	refShip.MinCrew         				= 84;
	refShip.SpeedRate				= 13;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 860000;
	refShip.HP              				= 8800;
	refShip.SP              				= 100;
	refship.CanEncounter					= true;
	refship.Type.Merchant					= false;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 1.0;
	refShip.sea_enchantment					= 1.1;
	refShip.lowpolycrew = 24;
	refShip.buildtime = 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
		
	refship.WaterLine					= 2.2;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.15;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed            = 1.7;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Lineship";

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY	= 3.5;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.0;
	
	refShip.Height.Bombs.Y				= 6.7;		refShip.Height.Bombs.DY		= 3.3;
	refShip.Height.Grapes.Y				= 8.3;		refShip.Height.Grapes.DY	= 4.1;
	refShip.Height.Knippels.Y			= 32.1;		refShip.Height.Knippels.DY	= 25.8;
	refShip.Height.Balls.Y				= 6.7;		refShip.Height.Balls.DY		= 3.3;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.6;
	refShip.GeraldSails.rey_b3.vscale		= 0.6;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.15;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "3.0, 4.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.25;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "6.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// NL_FWzP			���. ����. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_NL_FWZP]);
	refShip.Name            			= "NL_FWzP";
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(2300);
	refShip.Capacity        			= 5500;
	refShip.CannonsQuantity				= 56;
	refShip.rcannon 							= 27;
	refShip.lcannon 							= 27;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 550;
	refShip.MinCrew         				= 110;
	refShip.SpeedRate				= 8;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 825000;
	refShip.HP              				= 8500;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew 				= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	
	refShip.WaterLine = -0.5;
	refShip.SpeedDependWeight = 0.2;
	refShip.SubSeaDependWeight = 0.5;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed            = 1.7;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Big";

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast1.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast4.Flag1 = FLAG_SPECIAL;

	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;
	
	refShip.Height.Bombs.Y				= 6.7;		
	refShip.Height.Bombs.DY		= 3.3;
	refShip.Height.Grapes.Y				= 8.3;		
	refShip.Height.Grapes.DY	= 4.1;
	refShip.Height.Knippels.Y			= 32.1;		
	refShip.Height.Knippels.DY	= 25.8;
	refShip.Height.Balls.Y				= 6.7;		
	refShip.Height.Balls.DY		= 3.3;
	
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.15;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "3.0, 4.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.25;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "6.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Constitution			���. ���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CONSTITUTION]);
	refShip.Name 								= "Constitution";
	refship.Soundtype 							= "lineship";
	refShip.Class 								= 2;
	refShip.Cannon 								= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber 							= 32;
	refShip.Weight 								= Tonnes2CWT(1000);
	refShip.Capacity 							= 3000;
	refShip.CannonsQuantity 					= 56;
	refShip.rcannon 									= 26;
	refShip.lcannon 									= 26;
	refShip.fcannon 									= 2;
	refShip.bcannon 									= 2;
	refShip.MaxCrew 								= 340;
	refShip.MinCrew 								= 68;
	refShip.SpeedRate 						= 14;
	refShip.TurnRate 						= 35;
	refShip.Price 								= 920000;
	refShip.HP 										= 7700;
	refShip.SP 										= 100;
	refship.CanEncounter						= true;
	refship.Type.Merchant 						= false;
	refship.Type.War 							= true;
	refShip.fWindAgainstSpeed 					= 2.0;
	refShip.sea_enchantment 					= 1.2;
	refShip.lowpolycrew 						= 20;
	refShip.buildtime 							= 100;

	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;
	refship.WaterLine = -0.1;

	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 1.0;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed = 3.5;//boal
	refship.CabinType = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Frigate";

	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y = 1.0; refShip.Height.Bombs.DY = 0.5;
	refShip.Height.Grapes.Y = 2.0; refShip.Height.Grapes.DY = 1.0;
	refShip.Height.Knippels.Y = 10.0; refShip.Height.Knippels.DY = 8.0;
	refShip.Height.Balls.Y = 1.0; refShip.Height.Balls.DY = 0.5;

	refShip.GeraldSails.rey_b1 = 1;
	refShip.GeraldSails.rey_b2 = 1;
	refShip.GeraldSails.rey_b3 = 1;
	refShip.GeraldSails.rey_b1.vscale = 0.9;
	refShip.GeraldSails.rey_b2.vscale = 0.7;
	refShip.GeraldSails.rey_b3.vscale = 0.7;

	refship.Track.Enable = true;
	refship.Track1.ZStart = 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width = "3.7, 3.9";
	refship.Track1.Speed = "7.0, 8.0";

	refship.Track2.ZStart = -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width = "8.0, 9.0";
	refship.Track2.Speed = "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Oxford			������ �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_OXFORD]);
	refShip.Name            			= "Oxford";
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(860);
	refShip.Capacity        			= 3300;
	refShip.CannonsQuantity 			= 58;
	refShip.rcannon 							= 26;
	refShip.lcannon 							= 26;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 380;
	refShip.MinCrew         				= 62;
	refShip.SpeedRate       		= 14.5;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 256000;
	refShip.HP              				= 7000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew 				= 20;
	refShip.buildtime 					= 100;
	
	refship.Rocking.y 						= 0.5;
	refship.Rocking.az 						= 0.035;

	refship.WaterLine = -0.6;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.9;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 3.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Frigate";

	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y = 2.7;			refShip.Height.Bombs.DY = 1.3;
	refShip.Height.Grapes.Y = 4.3;			refShip.Height.Grapes.DY = 2.1;
	refShip.Height.Knippels.Y = 13.0;		refShip.Height.Knippels.DY = 11.7;
	refShip.Height.Balls.Y = 2.7;			refShip.Height.Balls.DY = 1.3;
	
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;

	refship.Track.Enable					= true;
	refship.Track1.ZStart					= 0.25;
	refship.Track1.LifeTime				 	= 16.5;
	refship.Track1.Width					= "6.0, 8.2";
	refship.Track1.Speed					= "9.0, 9.0";

	refship.Track2.ZStart					= 0.0;
	refship.Track2.LifeTime 				= 13.5;
	refship.Track2.Width					= "8.0, 9.0";
	refship.Track2.Speed					= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Dutchlineship			��. ����. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_DUTCHLINESHIP]);
	refShip.Name            		= "Dutchlineship";
	refship.Soundtype				= "lineship";
	refShip.Class					= 2;
	refShip.Cannon          		= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      		= 32;
	refShip.Weight					= Tonnes2CWT(2000);
	refShip.Capacity        		= 3800;
	refShip.CannonsQuantity			= 60;
	refShip.rcannon 						= 26;
	refShip.lcannon 						= 26;
	refShip.fcannon 						= 4;
	refShip.bcannon 						= 4;
	refShip.MaxCrew         			= 380;
	refShip.MinCrew         			= 76;
	refShip.SpeedRate			= 13.5;
	refShip.TurnRate        	= 35;
	refShip.Price           		= 1445000;
	refShip.HP              			= 7000;
	refShip.SP              			= 100;
	refship.CanEncounter			= true;
	refship.Type.Merchant			= false;
	refship.Type.War				= true;
	refShip.fWindAgainstSpeed		= 1.0;
	refShip.sea_enchantment			= 1.1;
	refShip.lowpolycrew 			= 24;
	refShip.buildtime 				= 120;

	refship.Rocking.y 				= 0.3;
	refship.Rocking.az 				= 0.035;
		
	refship.WaterLine				= -0.2;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.15;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed            		= 1.7;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY	= 3.5;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.0;
	
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.6;
	refShip.GeraldSails.rey_b3.vscale		= 0.6;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.15;
	refship.Track1.LifeTime 			= 16.5;
	refship.Track1.Width				= "3.0, 4.0";
	refship.Track1.Speed				= "8.0, 8.0";

	refship.Track2.ZStart				= -0.25;
	refship.Track2.LifeTime 			= 10.5;
	refship.Track2.Width				= "6.0, 7.0";
	refship.Track2.Speed				= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;
	
	///////////////////////////////////////////////////////////////////////////
	/// Dutchship			����. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_DUTCHSHIP]);
	refShip.Name            			= "Dutchship";
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(2500);
	refShip.Capacity        			= 4500;
	refShip.CannonsQuantity				= 60;
	refShip.rcannon 							= 24;
	refShip.lcannon 							= 24;
	refShip.fcannon 							= 4;
	refShip.bcannon 							= 8;	
	refShip.MaxCrew         				= 450;
	refShip.MinCrew         				= 90;	
	refShip.SpeedRate				= 12;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 1400000;
	refShip.HP              				= 9900;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	
	refShip.lowpolycrew 				= 24;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;
		
	refship.WaterLine					= 0.99;
	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed            = 2.5;
	refship.CabinType          			= "Cabin_Huge";
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 6.7;		refShip.Height.Bombs.DY		= 3.3;
	refShip.Height.Grapes.Y				= 8.3;		refShip.Height.Grapes.DY	= 4.1;
	refShip.Height.Knippels.Y			= 32.1;		refShip.Height.Knippels.DY	= 25.8;
	refShip.Height.Balls.Y				= 6.7;		refShip.Height.Balls.DY		= 3.3;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.65;
	refShip.GeraldSails.rey_b3.vscale		= 0.55;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.25;
	refship.Track1.LifeTime = 9.5;
	refship.Track1.Width	= "7.0, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "8.0, 10.0";
	refship.Track2.Speed	= "1.0, 2.0";	
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;
	
	///////////////////////////////////////////////////////////////////////////
	/// NL_ConvoiShip			���������� �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_NL_CONVOISHIP]);
	refShip.Name            		= "NL_ConvoiShip";
	refship.Soundtype				= "lineship";
	refShip.Class					= 2;
	refShip.Cannon          		= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      		= 32;
	refShip.Weight					= Tonnes2CWT(2000);
	refShip.Capacity        		= 4000;
	refShip.CannonsQuantity			= 60;
	refShip.rcannon 						= 28;
	refShip.lcannon 						= 28;
	refShip.fcannon 						= 2;
	refShip.bcannon 						= 2;
	refShip.MaxCrew         			= 420;
	refShip.MinCrew         			= 84;
	refShip.SpeedRate			= 13;
	refShip.TurnRate        	= 30;
	refShip.Price           		= 1570000;
	refShip.HP              			= 8200;
	refShip.SP              			= 100;
	refship.CanEncounter			= true;
	refship.Type.Merchant			= false;
	refship.Type.War				= true;
	refShip.fWindAgainstSpeed		= 1.0;
	refShip.sea_enchantment			= 1.1;
	refShip.lowpolycrew 			= 24;
	refShip.buildtime 				= 120;

	refship.Rocking.y 				= 0.3;
	refship.Rocking.az 				= 0.035;
		
	refship.WaterLine = -0.5;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 1.0;
	refship.TurnDependWeight = 0.4;
	
	refship.WindAgainstSpeed            		= 2.7;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";
	
	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.GeraldSails.rey_a2	= 1;
	refShip.GeraldSails.rey_a3	= 1;
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.15;
	refship.Track1.LifeTime 			= 16.5;
	refship.Track1.Width				= "3.0, 4.0";
	refship.Track1.Speed				= "8.0, 8.0";

	refship.Track2.ZStart				= -0.25;
	refship.Track2.LifeTime 			= 10.5;
	refship.Track2.Width				= "6.0, 7.0";
	refship.Track2.Speed				= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Couronne			���. ����. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_COURONNE]);
	refShip.Name            		= "Couronne";
	refship.Soundtype				= "lineship";
	refShip.Class					= 2;
	refShip.Cannon          		= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      		= 32;
	refShip.Weight					= Tonnes2CWT(3000);
	refShip.Capacity        		= 6500;
	refShip.CannonsQuantity			= 64;
	refShip.rcannon 						= 24;
	refShip.lcannon 						= 24;
	refShip.fcannon 						= 8;
	refShip.bcannon 						= 8;
	refShip.MaxCrew         			= 580;
	refShip.MinCrew         			= 116;
	refShip.SpeedRate			= 7.5;
	refShip.TurnRate        	= 25;
	refShip.Price           		= 1590000;
	refShip.HP              			= 9900;
	refShip.SP              			= 100;
	refship.CanEncounter			= true;
	refship.Type.Merchant			= true;
	refship.Type.War				= true;
	refShip.fWindAgainstSpeed		= 1.4;
	refShip.sea_enchantment			= 1.1;
	refShip.lowpolycrew 			= 24;
	refShip.buildtime 				= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
		
	refship.WaterLine		= 0.1;
	refship.SpeedDependWeight	= 0.35;
	refship.SubSeaDependWeight	= 0.75;
	refship.TurnDependWeight	= 0.4;
	refship.WindAgainstSpeed   	= 1.5;//boal
	refship.CabinType          	= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY	= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.5;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.7;
	refShip.GeraldSails.rey_b2.vscale	= 0.65;
	refShip.GeraldSails.rey_b3.vscale	= 0.65;

	refship.Track.Enable		= true;
	refship.Track1.ZStart		= 0.25;
	refship.Track1.LifeTime 	= 16.5;
	refship.Track1.Width		= "6.0, 8.2";
	refship.Track1.Speed		= "9.0, 9.0";

	refship.Track2.ZStart		= 0.0;
	refship.Track2.LifeTime 	= 13.5;
	refship.Track2.Width		= "8.0, 9.0";
	refship.Track2.Speed		= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;
	
	///////////////////////////////////////////////////////////////////////////
	/// Alexis			������ 2-�� ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_ALEXIS]);
	refShip.Name            			= "Alexis";
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(2000);
	refShip.Capacity        			= 4400;
	refShip.CannonsQuantity				= 64;
	refShip.rcannon 							= 29;
	refShip.lcannon 							= 29;
	refShip.fcannon 							= 4;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 470;
	refShip.MinCrew         				= 94;
	refShip.SpeedRate				= 11.5;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 1500000;
	refShip.HP              				= 11500;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew 				= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
		
	refship.WaterLine					= -0.7;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.15;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed            = 1.7;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Lineship";
	
	refship.InertiaAccelerationX	= 4.5;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY	= 3.5;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ	= 4.5;	refship.InertiaBrakingZ		= 4.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.6;
	refShip.GeraldSails.rey_b3.vscale		= 0.6;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.15;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "3.0, 4.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.25;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "6.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// LineShipHeavy			���. ����. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LINESHIPHEAVY]);
	refShip.Name            			= "LineShipHeavy";
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(2000);
	refShip.Capacity        			= 5300;
	refShip.CannonsQuantity				= 64;
	refShip.rcannon 							= 28;
	refShip.lcannon 							= 28;
	refShip.fcannon 							= 6;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 420;
	refShip.MinCrew         				= 84;
	refShip.SpeedRate       		= 12;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 1600000;
	refShip.HP              				= 10000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew 				= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
		
	refship.WaterLine = 0.0;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.55;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed            = 1.7;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Lineship";

	refShip.Height.Bombs.Y				= 4.5;		refShip.Height.Bombs.DY		= 2.0;
	refShip.Height.Grapes.Y				= 8.0;		refShip.Height.Grapes.DY	= 2.0;
	refShip.Height.Knippels.Y			= 35.0;		refShip.Height.Knippels.DY	= 30.0;
	refShip.Height.Balls.Y				= 4.5;		refShip.Height.Balls.DY		= 2.0;
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.6;
	refShip.GeraldSails.rey_b3.vscale		= 0.6;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.15;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "3.0, 4.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.25;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "6.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Warship			�������� �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_WARSHIP]);
	refShip.Name            			= "Warship";
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(2500);
	refShip.Capacity        			= 5000;
	refShip.CannonsQuantity				= 66;
	refShip.rcannon 							= 30;
	refShip.lcannon 							= 30;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 500;
	refShip.MinCrew         				= 100;
	refShip.SpeedRate				= 12.5;
	refShip.TurnRate        		= 35;
	refShip.Price           			= 1658000;
	refShip.HP              				= 8900;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew					= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;
	
	refship.WaterLine					= 0.5;

	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed   			= 1.5;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Lineship";

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 4.0;	refship.InertiaBrakingX		= 3.5;
	refship.InertiaAccelerationY	= 3.0;		refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 4.0;	refship.InertiaBrakingZ		= 3.5;
	
	refShip.Height.Bombs.Y				= 7.2;		refShip.Height.Bombs.DY		= 3.6;
	refShip.Height.Grapes.Y				= 8.5;		refShip.Height.Grapes.DY	= 4.2;
	refShip.Height.Knippels.Y			= 28.3;		refShip.Height.Knippels.DY	= 22.0;
	refShip.Height.Balls.Y				= 7.2;		refShip.Height.Balls.DY		= 3.6;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.65;
	refShip.GeraldSails.rey_b3.vscale		= 0.55;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.25;
	refship.Track1.LifeTime = 9.5;
	refship.Track1.Width	= "7.0, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "8.0, 10.0";
	refship.Track2.Speed	= "1.0, 2.0";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// HeavyWarship			������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_HEAVYWARSHIP]);
	refShip.Name            			= "HeavyWarship";
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(3000);
	refShip.Capacity        			= 4800;
	refShip.CannonsQuantity				= 74;
	refShip.rcannon 							= 34;
	refShip.lcannon 							= 34;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 460;
	refShip.MinCrew         				= 92;
	refShip.SpeedRate				= 13,5;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 1830000;
	refShip.HP              				= 9000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.4;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew 				= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	
	refship.WaterLine							= 1.6;

	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 2.0;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed   = 2.5;//boal
	refship.CabinType          = "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 7.2;		refShip.Height.Bombs.DY		= 3.6;
	refShip.Height.Grapes.Y				= 8.5;		refShip.Height.Grapes.DY	= 4.2;
	refShip.Height.Knippels.Y			= 28.3;		refShip.Height.Knippels.DY	= 22.0;
	refShip.Height.Balls.Y				= 7.2;		refShip.Height.Balls.DY		= 3.6;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.65;
	refShip.GeraldSails.rey_b3.vscale		= 0.55;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.25;
	refship.Track1.LifeTime = 9.5;
	refship.Track1.Width	= "7.0, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "8.0, 10.0";
	refship.Track2.Speed	= "1.0, 2.0";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// HeavyLineship			���. ���. �����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_HEAVYLINESHIP]);
	refShip.Name            			= "HeavyLineship";
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(1200);
	refShip.Capacity        			= 5400;
	refShip.CannonsQuantity				= 82;
	refShip.rcannon 							= 37;
	refShip.lcannon 							= 37;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 6;
	refShip.MaxCrew         				= 480;
	refShip.MinCrew         				= 96;
	refShip.SpeedRate				= 11.5;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 2480000;
	refShip.HP              				= 6000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew 				= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;

	refShip.WaterLine 					= 1.0;
	refShip.SpeedDependWeight 			= 0.3;
	refShip.SubSeaDependWeight			= 0.9;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed   			= 1.0;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Lineship";

	refShip.Flags.Mast1.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast4.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast4.Flag2 = FLAG_ENSIGN;	
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 6.8;		refShip.Height.Bombs.DY		= 3.4;
	refShip.Height.Grapes.Y				= 8.2;		refShip.Height.Grapes.DY	= 4.1;
	refShip.Height.Knippels.Y			= 33.6;		refShip.Height.Knippels.DY	= 24.8;
	refShip.Height.Balls.Y				= 6.8;		refShip.Height.Balls.DY		= 3.4;
	
	refShip.GeraldSails.rey_a2	= 1;
	refShip.GeraldSails.rey_a3	= 1;
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.25;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "6.0, 8.2";
	refship.Track1.Speed	= "9.0, 9.0";

	refship.Track2.ZStart	= 0.0;
	refship.Track2.LifeTime = 13.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Poseidon			������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_POSEIDON]);
	refShip.Name            			= "Poseidon";
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(2500);
	refShip.Capacity        			= 3400;
	refShip.CannonsQuantity				= 66;
	refShip.rcannon 							= 30;
	refShip.lcannon 							= 30;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 420;
	refShip.MinCrew         				= 84;
	refShip.SpeedRate				= 13.5;
	refShip.TurnRate        		= 45;
	refShip.Price           			= 1550000;
	refShip.HP              				= 8200;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.1;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew 				= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refship.WaterLine		= 0.05;

	refship.SpeedDependWeight	= 0.35;
	refship.SubSeaDependWeight	= 1.0;
	refship.TurnDependWeight	= 0.4;
	refship.WindAgainstSpeed   	= 2.0;//boal
	refship.CabinType          	= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Lineship";
	
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 4.0;	refship.InertiaBrakingX		= 3.5;
	refship.InertiaAccelerationY	= 3.0;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 4.0;	refship.InertiaBrakingZ		= 3.5;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.8;
	refShip.GeraldSails.rey_b2.vscale	= 0.65;
	refShip.GeraldSails.rey_b3.vscale	= 0.55;

	refship.Track.Enable		= true;
	refship.Track1.ZStart		= 0.25;
	refship.Track1.LifeTime 	= 9.5;
	refship.Track1.Width		= "7.0, 7.5";
	refship.Track1.Speed		= "8.0, 9.0";

	refship.Track2.ZStart		= -0.15;
	refship.Track2.LifeTime 	= 7.5;
	refship.Track2.Width		= "8.0, 10.0";
	refship.Track2.Speed		= "1.0, 2.0";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;
	
	///////////////////////////////////////////////////////////////////////////
	/// HMS_Centurion			������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_HMS_CENTURION]);
	refShip.Name            			= "HMS_Centurion";
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(2500);
	refShip.Capacity        			= 3900;
	refShip.CannonsQuantity				= 68;
	refShip.rcannon 							= 32;
	refShip.lcannon 							= 32;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 400;
	refShip.MinCrew         				= 80;
	refShip.SpeedRate				= 12.7;
	refShip.TurnRate        		= 38;
	refShip.Price           			= 1652000;
	refShip.HP              				= 9000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.1;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew 				= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refShip.WaterLine 					= 0;
	refShip.SpeedDependWeight 			= 0.3;
	refShip.SubSeaDependWeight 			= 0.55;
	refship.TurnDependWeight	= 0.4;
	refship.WindAgainstSpeed   	= 1.8;//boal
	refship.CabinType          	= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           	= "Big";

	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast5.Flag2 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 4.0;	refship.InertiaBrakingX		= 3.5;
	refship.InertiaAccelerationY	= 3.0;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 4.0;	refship.InertiaBrakingZ		= 3.5;
	
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable		= true;
	refship.Track1.ZStart		= 0.25;
	refship.Track1.LifeTime 	= 9.5;
	refship.Track1.Width		= "7.0, 7.5";
	refship.Track1.Speed		= "8.0, 9.0";

	refship.Track2.ZStart		= -0.15;
	refship.Track2.LifeTime 	= 7.5;
	refship.Track2.Width		= "8.0, 10.0";
	refship.Track2.Speed		= "1.0, 2.0";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// resolution			������ ���������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_RESOLUTION]);
	refShip.Name            			= "resolution";
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(990);
	refShip.Capacity        			= 4400;
	refShip.CannonsQuantity				= 70;
	refShip.rcannon 							= 32;
	refShip.lcannon 							= 32;
	refShip.fcannon 							= 4;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 450;
	refShip.MinCrew         				= 90;
	refShip.SpeedRate				= 13.5;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 1700000;
	refShip.HP              				= 7000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew 				= 20;
	refShip.buildtime 					= 100;
	
	refship.Rocking.y 						= 0.5;
	refship.Rocking.az 						= 0.035;

	refship.WaterLine = 0.1;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.9;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 3.6;//boal
	refship.CabinType          = "Cabin"; // boal 28.03.05
	refship.DeckType           			= "Big";

	refship.InertiaAccelerationX = 3.5;		refship.InertiaBrakingX = 3.0;
	refship.InertiaAccelerationY = 2.5;		refship.InertiaBrakingY = 2.5;
	refship.InertiaAccelerationZ = 3.5;		refship.InertiaBrakingZ = 3.0;

	refShip.Height.Bombs.Y = 3.5;			refShip.Height.Bombs.DY = 1.7;
	refShip.Height.Grapes.Y = 4.8;			refShip.Height.Grapes.DY = 2.4;
	refShip.Height.Knippels.Y = 16.7;		refShip.Height.Knippels.DY = 12.8;
	refShip.Height.Balls.Y = 3.5;			refShip.Height.Balls.DY = 1.7;
	
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;

	refship.Track.Enable					= true;
	refship.Track1.ZStart					= 0.25;
	refship.Track1.LifeTime				 	= 16.5;
	refship.Track1.Width					= "6.0, 8.2";
	refship.Track1.Speed					= "9.0, 9.0";

	refship.Track2.ZStart					= 0.0;
	refship.Track2.LifeTime 				= 13.5;
	refship.Track2.Width					= "8.0, 9.0";
	refship.Track2.Speed					= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;
	
	///////////////////////////////////////////////////////////////////////////
	/// FR_SuperiorWarship1			������ �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FR_SUPERIORWARSHIP1]);
	refShip.Name            			= "FR_SuperiorWarship1";
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(3200);
	refShip.Capacity        			= 4000;
	refShip.CannonsQuantity				= 74;
	refShip.rcannon 							= 34;
	refShip.lcannon 							= 34;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 540;
	refShip.MinCrew         				= 108;
	refShip.SpeedRate				= 13;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 1635000;
	refShip.HP              				= 11500;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.4;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew 				= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refship.WaterLine = 0.30;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.55;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 1.0;//boal
	refship.CabinType          = "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Lineship";
	
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;

	refShip.Height.Bombs.Y				= 4.0;		refShip.Height.Bombs.DY		= 2.0;
	refShip.Height.Grapes.Y				= 7.0;		refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y			= 36.0;		refShip.Height.Knippels.DY	= 32.0;
	refShip.Height.Balls.Y				= 4.0;		refShip.Height.Balls.DY		= 2.0;
	
	refship.InertiaAccelerationX	= 3.5;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 2.5;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 3.5;	refship.InertiaBrakingZ		= 3.0;

	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.65;
	refShip.GeraldSails.rey_b3.vscale		= 0.65;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.25;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "6.0, 8.2";
	refship.Track1.Speed	= "9.0, 9.0";

	refship.Track2.ZStart	= 0.0;
	refship.Track2.LifeTime = 13.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Link			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LINK]);
	refShip.Name            			= "Link";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(3500);
	refShip.Capacity        			= 6000;
	refShip.CannonsQuantity				= 78;
	refShip.rcannon 							= 37;
	refShip.lcannon 							= 37;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 550;
	refShip.MinCrew         				= 136;
	refShip.SpeedRate				= 11;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 1750000;
	refShip.HP              				= 10000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.0;
	refShip.lowpolycrew = 28;
	refShip.buildtime = 140;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;

	refship.WaterLine							= -0.2;
	refship.SpeedDependWeight			= 0.45;
	refship.SubSeaDependWeight			= 1.8;
	refship.TurnDependWeight			= 0.45;
	refship.WindAgainstSpeed   = 1.0;//boal
	refship.CabinType          = "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";
	
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;	
	
	refship.InertiaAccelerationX	= 1.5;	refship.InertiaBrakingX		= 1.5;
	refship.InertiaAccelerationY	= 1.5;	refship.InertiaBrakingY		= 1.5;
	refship.InertiaAccelerationZ	= 1.5;	refship.InertiaBrakingZ		= 1.5;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_c1		= 1;
	refShip.GeraldSails.rey_c1.vscale		= 0.98;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.98;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 18.5;
	refship.Track1.Width	= "6.5, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "16.0, 18.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Superbe			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SUPERBE]);
	refShip.Name            		= "Superbe";  
	refship.Soundtype				= "lineship";
	refShip.Class					= 1;
	refShip.Cannon          		= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      		= 42;
	refShip.Weight					= Tonnes2CWT(2500);
	refShip.Capacity        		= 4500;
	refShip.CannonsQuantity			= 78;
	refShip.rcannon 						= 37;
	refShip.lcannon 						= 37;
	refShip.fcannon 						= 2;
	refShip.bcannon 						= 2;
	refShip.MaxCrew         			= 600;
	refShip.MinCrew         			= 120;
	refShip.SpeedRate			= 12.5;
	refShip.TurnRate        	= 25;
	refShip.Price           		= 1850000;
	refShip.HP              			= 11000;
	refShip.SP              			= 100;
	refship.CanEncounter			= true;
	refship.Type.Merchant			= false;
	refship.Type.War				= true;
	refShip.fWindAgainstSpeed		= 1.4;
	refShip.sea_enchantment			= 1.1;
	refShip.lowpolycrew 			= 24;
	refShip.buildtime 				= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	refship.WaterLine			= -0.1;

	refship.SpeedDependWeight	= 0.35;
	refship.SubSeaDependWeight	= 1.0;
	refship.TurnDependWeight	= 0.4;
	refship.WindAgainstSpeed   	= 2.0;//boal
	refship.CabinType          		= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Lineship";
	
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 3.5;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 2.5;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 3.5;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;
	refShip.GeraldSails.rey_b1	= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.8;
	refShip.GeraldSails.rey_b2.vscale	= 0.65;
	refShip.GeraldSails.rey_b3.vscale	= 0.55;

	refship.Track.Enable		= true;
	refship.Track1.ZStart		= 0.25;
	refship.Track1.LifeTime 		= 9.5;
	refship.Track1.Width		= "7.0, 7.5";
	refship.Track1.Speed		= "8.0, 9.0";

	refship.Track2.ZStart		= -0.15;
	refship.Track2.LifeTime 		= 7.5;
	refship.Track2.Width		= "8.0, 10.0";
	refship.Track2.Speed		= "1.0, 2.0";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// Battleship			������ �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BATTLESHIP]);
	refShip.Name            			= "Battleship";
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(3000);
	refShip.Capacity        			= 4900;
	refShip.CannonsQuantity				= 80;
	refShip.rcannon 							= 36;
	refShip.lcannon 							= 36;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 6;
	refShip.MaxCrew         				= 600;
	refShip.MinCrew         				= 120;
	refShip.SpeedRate				= 11.5;
	refShip.TurnRate        		= 32;
	refShip.Price           			= 2500000;
	refShip.HP              				= 12000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew 				= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	
	
	refship.WaterLine							= -0.2;
	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 0.75;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed   			= 1.0;//boal
	refship.CabinType         			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Lineship";
	
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;	
	
	refship.InertiaAccelerationX	= 3.5;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 2.5;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 3.5;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.Height.Bombs.Y				= 6.8;		refShip.Height.Bombs.DY		= 3.4;
	refShip.Height.Grapes.Y				= 8.2;		refShip.Height.Grapes.DY	= 4.1;
	refShip.Height.Knippels.Y			= 33.6;		refShip.Height.Knippels.DY	= 24.8;
	refShip.Height.Balls.Y				= 6.8;		refShip.Height.Balls.DY		= 3.4;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.7;
	refShip.GeraldSails.rey_b2.vscale		= 0.65;
	refShip.GeraldSails.rey_b3.vscale		= 0.65;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.25;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "6.0, 8.2";
	refship.Track1.Speed	= "9.0, 9.0";

	refship.Track2.ZStart	= 0.0;
	refship.Track2.LifeTime = 13.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Link2			���. ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LINK2]);
	refShip.Name            		= "Link2";  
	refship.Soundtype				= "manowar";
	refShip.Class					= 1;
	refShip.Cannon          		= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      		= 42;
	refShip.Weight					= Tonnes2CWT(3500);
	refShip.Capacity        		= 5500;
	refShip.CannonsQuantity			= 82;
	refShip.rcannon 						= 38;
	refShip.lcannon 						= 38;
	refShip.fcannon 						= 2;
	refShip.bcannon 						= 4;
	refShip.MaxCrew         			= 850;
	refShip.MinCrew         			= 170;
	refShip.SpeedRate			= 9.5;
	refShip.TurnRate        	= 25;
	refShip.Price           		= 2565000;
	refShip.HP              			= 15000;
	refShip.SP              			= 100;
	refship.CanEncounter			= true;
	refship.Type.Merchant			= false;
	refship.Type.War				= true;
	refShip.fWindAgainstSpeed		= 1.4;
	refShip.sea_enchantment			= 1.1;
	refShip.lowpolycrew 			= 24;
	refShip.buildtime 				= 120;

	refship.Rocking.y 				= 0.3;
	refship.Rocking.az 				= 0.02;
	
	refship.WaterLine					= 0.2;
	refship.SpeedDependWeight			= 0.45;
	refship.SubSeaDependWeight			= 0.7;
	refship.TurnDependWeight			= 0.45;
	refship.WindAgainstSpeed            = 1.8;
	refship.CabinType          			= "Cabin_Huge"; 
	refship.DeckType           			= "Big";
	
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 3.5;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 2.5;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 3.5;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_c1		= 1;
	refShip.GeraldSails.rey_c1.vscale		= 0.98;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.98;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 18.5;
	refship.Track1.Width	= "6.5, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "16.0, 18.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Bellona			������ 1-�� ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BELLONA]);
	refShip.Name            			= "Bellona";
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(2500);
	refShip.Capacity        			= 4500;
	refShip.CannonsQuantity				= 84;
	refShip.rcannon 							= 40;
	refShip.lcannon 							= 40;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 500;
	refShip.MinCrew         				= 100;
	refShip.SpeedRate				= 12;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 2620000;
	refShip.HP              				= 8500;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.4;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew 				= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;
	
	
	refship.WaterLine							= 0.5;
	refship.SpeedDependWeight	= 0.35;
	refship.SubSeaDependWeight	= 1.0;
	refship.TurnDependWeight	= 0.4;
	refship.WindAgainstSpeed   	= 1.0;//boal
	refship.CabinType          	= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           	= "Lineship";
	
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 3.5;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 2.5;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 3.5;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.Height.Bombs.Y				= 6.8;		refShip.Height.Bombs.DY		= 3.4;
	refShip.Height.Grapes.Y				= 8.2;		refShip.Height.Grapes.DY	= 4.1;
	refShip.Height.Knippels.Y			= 33.6;		refShip.Height.Knippels.DY	= 24.8;
	refShip.Height.Balls.Y				= 6.8;		refShip.Height.Balls.DY		= 3.4;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.8;
	refShip.GeraldSails.rey_b2.vscale	= 0.65;
	refShip.GeraldSails.rey_b3.vscale	= 0.55;

	refship.Track.Enable		= true;
	refship.Track1.ZStart		= 0.25;
	refship.Track1.LifeTime 	= 9.5;
	refship.Track1.Width		= "7.0, 7.5";
	refship.Track1.Speed		= "8.0, 9.0";

	refship.Track2.ZStart		= -0.15;
	refship.Track2.LifeTime 	= 7.5;
	refship.Track2.Width		= "8.0, 10.0";
	refship.Track2.Speed		= "1.0, 2.0";
	
	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;
	
	///////////////////////////////////////////////////////////////////////////
	/// Linearship			���. ���. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LINEARSHIP]);
	refShip.Name            			= "Linearship";
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(3500);
	refShip.Capacity        			= 4500;
	refShip.CannonsQuantity				= 84;
	refShip.rcannon 							= 39;
	refShip.lcannon 							= 39;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 650;
	refShip.MinCrew         				= 130;
	refShip.SpeedRate				= 11.8;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 2450000;
	refShip.HP              				= 11000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed				= 1.0;
	refShip.sea_enchantment					= 1.1;
	refShip.lowpolycrew = 24;
	refShip.buildtime = 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
		
	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight 			= 0.55;
	refship.TurnDependWeight 			= 0.8;
	refship.WindAgainstSpeed            = 1.0;//boal
	refship.CabinType          = "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 3.5;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 2.5;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 3.5;	refship.InertiaBrakingZ		= 3.0;
	
	refShip.Height.Bombs.Y				= 6.7;		refShip.Height.Bombs.DY		= 3.3;
	refShip.Height.Grapes.Y				= 8.3;		refShip.Height.Grapes.DY	= 4.1;
	refShip.Height.Knippels.Y			= 32.1;		refShip.Height.Knippels.DY	= 25.8;
	refShip.Height.Balls.Y				= 6.7;		refShip.Height.Balls.DY		= 3.3;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.6;
	refShip.GeraldSails.rey_b3.vscale		= 0.6;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.15;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "3.0, 4.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.25;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "6.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Shark			���. ���. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SHARK]);
	refShip.Name            			= "Shark";
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(3500);
	refShip.Capacity        			= 5500;
	refShip.CannonsQuantity				= 84;
	refShip.rcannon 							= 39;
	refShip.lcannon 							= 39;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 550;
	refShip.MinCrew         				= 110;
	refShip.SpeedRate				= 12.5;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 2400000;
	refShip.HP              				= 10000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew 				= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	
	refship.WaterLine = 0.0;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.55;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   			= 1.0;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Lineship";

	refShip.Height.Bombs.Y				= 4.0;		refShip.Height.Bombs.DY		= 2.0;
	refShip.Height.Grapes.Y				= 7.0;		refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y			= 36.0;		refShip.Height.Knippels.DY	= 32.0;
	refShip.Height.Balls.Y				= 4.0;		refShip.Height.Balls.DY		= 2.0;
	
	refship.InertiaAccelerationX	= 3.5;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 2.5;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 3.5;	refship.InertiaBrakingZ		= 3.0;

	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.25;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "6.0, 8.2";
	refship.Track1.Speed	= "9.0, 9.0";

	refship.Track2.ZStart	= 0.0;
	refship.Track2.LifeTime = 13.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// Intrepide			���. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_INTREPIDE]);
	refShip.Name            			= "Intrepide";
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(2000);
	refShip.Capacity        			= 5800;
	refShip.CannonsQuantity						= 90;
	refShip.rcannon 							= 45;
	refShip.lcannon 							= 45;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 0;
	refShip.MaxCrew         				= 650;
	refShip.MinCrew         				= 130;
	refShip.SpeedRate				= 11;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 2520000;
	refShip.HP              				= 12000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.4;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew 				= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
		
	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.4;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed            = 1.7;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Lineship";

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 2.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 2;	refship.InertiaBrakingY		= 2;
	refship.InertiaAccelerationZ	= 2.0;	refship.InertiaBrakingZ		= 2.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.6;
	refShip.GeraldSails.rey_b3.vscale		= 0.6;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.15;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "3.0, 4.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.25;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "6.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	/// FR_Trinity			����. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FR_TRINITY]);
	refShip.Name            			= "FR_Trinity";
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(3500);
	refShip.Capacity        			= 6200;
	refShip.CannonsQuantity				= 96;
	refShip.rcannon 							= 46;
	refShip.lcannon 							= 46;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 720;
	refShip.MinCrew         				= 144;
	refShip.SpeedRate				= 10;
	refShip.TurnRate        		= 30;
	refShip.Price           			= 2620000;
	refShip.HP              				= 13000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.4;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew 				= 24;
	refShip.buildtime 					= 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	
	refShip.WaterLine					= -0.4;
	refShip.SpeedDependWeight			= 0.3;
	refShip.SubSeaDependWeight			= 1.15;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed            = 1.7;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Lineship";

	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast5.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 2.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 2;	refship.InertiaBrakingY		= 2;
	refship.InertiaAccelerationZ	= 2.0;	refship.InertiaBrakingZ		= 2.0;
	
	refShip.GeraldSails.rey_a2	= 1;
	refShip.GeraldSails.rey_a3	= 1;
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.15;
	refship.Track1.LifeTime = 16.5;
	refship.Track1.Width	= "3.0, 4.0";
	refship.Track1.Speed	= "8.0, 8.0";

	refship.Track2.ZStart	= -0.25;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "6.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;
	
	///////////////////////////////////////////////////////////////////////////
	/// Manowar_fast			���. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_MANOWAR_FAST]);
	refShip.Name            			= "Manowar_fast";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(4000);
	refShip.Capacity        			= 6000;
	refShip.CannonsQuantity				= 100;
	refShip.rcannon 							= 45;
	refShip.lcannon 							= 45;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 8;
	refShip.MaxCrew         				= 850;
	refShip.MinCrew         				= 170;
	refShip.SpeedRate				= 9.5;
	refShip.TurnRate        		= 20;
	refShip.Price           			= 2730000;
	refShip.HP              			= 17000;
	refShip.SP              			= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.0;
	refShip.lowpolycrew 				= 28;
	refShip.buildtime 					= 140;

	refship.Rocking.y = 0.3;
	refship.Rocking.az = 0.02;

	refship.WaterLine = 0.0;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.9;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   			= 1.0;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";

	refShip.Height.Bombs.Y				= 6.7;		refShip.Height.Bombs.DY		= 3.0;
	refShip.Height.Grapes.Y				= 11.0;		refShip.Height.Grapes.DY	= 3.0;
	refShip.Height.Knippels.Y			= 46.0;		refShip.Height.Knippels.DY	= 40.0;
	refShip.Height.Balls.Y				= 6.7;		refShip.Height.Balls.DY		= 3.0;
	
	refship.InertiaAccelerationX	= 2.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 2;	refship.InertiaBrakingY		= 2;
	refship.InertiaAccelerationZ	= 2.0;	refship.InertiaBrakingZ		= 2.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.98;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 18.5;
	refship.Track1.Width	= "6.5, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "16.0, 18.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// BattleManowar			���. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BATTLEMANOWAR]);
	refShip.Name            			= "BattleManowar";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(4000);
	refShip.Capacity        			= 6500;
	refShip.CannonsQuantity				= 100;
	refShip.rcannon 							= 45;
	refShip.lcannon 							= 45;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 8;
	refShip.MaxCrew         				= 950;
	refShip.MinCrew         				= 190;
	refShip.SpeedRate				= 9;
	refShip.TurnRate        		= 20;
	refShip.Price           			= 2660000;
	refShip.HP              				= 16000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.0;
	refShip.lowpolycrew 				= 28;
	refShip.buildtime 					= 140;

	refship.Rocking.y = 0.3;
	refship.Rocking.az = 0.02;

	refship.WaterLine							= -1.0;
	refship.SpeedDependWeight			= 0.45;
	refship.SubSeaDependWeight			= 1.8;
	refship.TurnDependWeight			= 0.45;
	refship.WindAgainstSpeed   			= 1.0;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";
	
	refship.InertiaAccelerationX	= 2.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 2;	refship.InertiaBrakingY		= 2;
	refship.InertiaAccelerationZ	= 2.0;	refship.InertiaBrakingZ		= 2.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_c1		= 1;
	refShip.GeraldSails.rey_c1.vscale		= 0.98;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.98;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 18.5;
	refship.Track1.Width	= "6.5, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "16.0, 18.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;
	
	///////////////////////////////////////////////////////////////////////////
	/// Manowar_gub			���. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_MANOWAR_GUB]);
	refShip.Name            			= "Manowar_gub";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(3500);
	refShip.Capacity        			= 7000;
	refShip.CannonsQuantity				= 100;
	refShip.rcannon 							= 45;
	refShip.lcannon 							= 45;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 8;
	refShip.MaxCrew         				= 1050;
	refShip.MinCrew         				= 210;
	refShip.SpeedRate				= 8.5;
	refShip.TurnRate        		= 20;
	refShip.Price           			= 2760000;
	refShip.HP              				= 15000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.0;
	refShip.lowpolycrew 				= 28;
	refShip.buildtime 					= 140;

	refship.Rocking.y = 0.3;
	refship.Rocking.az = 0.02;

	refShip.WaterLine = -0.9;
	refShip.SpeedDependWeight = 0.3;
	refShip.SubSeaDependWeight = 0.9;
	refship.TurnDependWeight			= 0.45;
	refship.WindAgainstSpeed   			= 1.0;//boal
	refship.CabinType         			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";
	
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast5.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 2.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 2;	refship.InertiaBrakingY		= 2;
	refship.InertiaAccelerationZ	= 2.0;	refship.InertiaBrakingZ		= 2.0;
	
	refShip.GeraldSails.rey_a2	= 1;
	refShip.GeraldSails.rey_a3	= 1;
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;
	refShip.GeraldSails.rey_b4	= 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 18.5;
	refship.Track1.Width	= "6.5, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "16.0, 18.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= true;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// Prince				����������� ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_PRINCE]);
	refShip.Name            			= "Prince";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(1250);
	refShip.Capacity        			= 5000;
	refShip.CannonsQuantity				= 100;
	refShip.rcannon 							= 46;
	refShip.lcannon 							= 46;
	refShip.fcannon 							= 4;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 750;
	refShip.MinCrew         				= 150;
	refShip.SpeedRate				= 11;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 2850000;
	refShip.HP              				= 12000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.0;
	refShip.lowpolycrew 				= 28;
	refShip.buildtime 					= 140;
	
	refship.Rocking.y 						= 0.5;
	refship.Rocking.az 						= 0.035;

	refship.WaterLine = 0.0;
	refship.SpeedDependWeight = 0.3;
	refship.SubSeaDependWeight = 0.9;
	refship.TurnDependWeight = 0.4;
	refship.WindAgainstSpeed   = 1.0;//boal
	refship.CabinType          = "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";

	refship.InertiaAccelerationX	= 2.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 2;	refship.InertiaBrakingY		= 2;
	refship.InertiaAccelerationZ	= 2.0;	refship.InertiaBrakingZ		= 2.0;

	refShip.Height.Bombs.Y = 4.3;			refShip.Height.Bombs.DY = 2.1;
	refShip.Height.Grapes.Y = 5.6;			refShip.Height.Grapes.DY = 2.8;
	refShip.Height.Knippels.Y = 18.7;		refShip.Height.Knippels.DY = 12.7;
	refShip.Height.Balls.Y = 4.3;			refShip.Height.Balls.DY = 2.1;
	
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;


	refship.Track.Enable					= true;
	refship.Track1.ZStart					= 0.30;
	refship.Track1.LifeTime 				= 18.5;
	refship.Track1.Width					= "6.5, 7.5";
	refship.Track1.Speed					= "8.0, 9.0";

	refship.Track2.ZStart					= -0.15;
	refship.Track2.LifeTime 				= 10.5;
	refship.Track2.Width					= "16.0, 18.0";
	refship.Track2.Speed					= "0.15, 0.25";


	//Nation
    refship.nation.england	= false;
	refship.nation.france	= true;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	//// Manowar			���. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_MANOWAR]);
	refShip.Name            			= "Manowar";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(4000);
	refShip.Capacity        			= 6800;
	refShip.CannonsQuantity				= 102;
	refShip.rcannon 							= 45;
	refShip.lcannon 							= 45;
	refShip.fcannon 							= 4;
	refShip.bcannon 							= 8;
	refShip.MaxCrew         				= 800;
	refShip.MinCrew         				= 160;
	refShip.SpeedRate				= 9.5;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 2700000;
	refShip.HP              				= 10500;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.0;
	refShip.lowpolycrew 				= 28;
	refShip.buildtime 					= 140;

	refship.Rocking.y = 0.3;
	refship.Rocking.az = 0.02	;

	refship.WaterLine							= 0.5;
	refship.SpeedDependWeight			= 0.45;
	refship.SubSeaDependWeight			= 1.8;
	refship.TurnDependWeight			= 0.45;
	refship.WindAgainstSpeed   			= 0.7;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";

	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 1.5;	refship.InertiaBrakingX		= 1.5;
	refship.InertiaAccelerationY	= 1.5;	refship.InertiaBrakingY		= 1.5;
	refship.InertiaAccelerationZ	= 1.5;	refship.InertiaBrakingZ		= 1.5;
	
	refShip.Height.Bombs.Y				= 8.6;		refShip.Height.Bombs.DY		= 4.3;
	refShip.Height.Grapes.Y				= 12.5;		refShip.Height.Grapes.DY	= 6.2;
	refShip.Height.Knippels.Y			= 36.8;		refShip.Height.Knippels.DY	= 29.6;
	refShip.Height.Balls.Y				= 8.6;		refShip.Height.Balls.DY		= 4.3;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_c1		= 1;
	refShip.GeraldSails.rey_c1.vscale		= 0.98;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.98;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 18.5;
	refship.Track1.Width	= "6.5, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "16.0, 18.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= true;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;

	///////////////////////////////////////////////////////////////////////////
	/// HMS_Victory			������� ��������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_HMS_VICTORY]);
	refShip.Name            			= "HMS_Victory";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(4000);
	refShip.Capacity        			= 6000;
	refShip.CannonsQuantity				= 104;
	refShip.rcannon 							= 50;
	refShip.lcannon 							= 50;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 900;
	refShip.MinCrew         				= 180;
	refShip.SpeedRate				= 9.8;
	refShip.TurnRate        		= 22;
	refShip.Price           			= 2800000;
	refShip.HP              				= 14000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.0;
	refShip.lowpolycrew 				= 28;
	refShip.buildtime 					= 140;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;

	refship.WaterLine							= 0.5;
	refship.SpeedDependWeight			= 0.45;
	refship.SubSeaDependWeight			= 1.8;
	refship.TurnDependWeight			= 0.45;
	refship.WindAgainstSpeed   			= 1.0;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";

	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 2.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 2;	refship.InertiaBrakingY		= 2;
	refship.InertiaAccelerationZ	= 2.0;	refship.InertiaBrakingZ		= 2.0;
	
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_c1			= 1;
	refShip.GeraldSails.rey_c1.vscale		= 0.98;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.98;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 18.5;
	refship.Track1.Width	= "6.5, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "16.0, 18.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= true;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= false;
	
	///////////////////////////////////////////////////////////////////////////
	/// SP_SanFelipe			���. �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SP_SANFELIPE]);
	refShip.Name            			= "SP_SanFelipe";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(3000);
	refShip.Capacity        			= 7500;
	refShip.CannonsQuantity				= 108;
	refShip.rcannon 							= 51;
	refShip.lcannon 							= 51;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 750;
	refShip.MinCrew         				= 150;
	refShip.SpeedRate				= 9.5;
	refShip.TurnRate        		= 25;
	refShip.Price           			= 2890000;
	refShip.HP              				= 13000;
	refShip.SP              				= 100;
	refship.CanEncounter				= true;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.0;
	refShip.lowpolycrew 				= 28;
	refShip.buildtime 					= 140;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.15;

	refShip.WaterLine = 0.0;
	refShip.SpeedDependWeight			= 0.3;
	refShip.SubSeaDependWeight			= 0.9;
	refship.TurnDependWeight			= 0.45;
	refship.WindAgainstSpeed   			= 1.0;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast1.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast4.Flag1 = FLAG_SPECIAL;

	refship.InertiaAccelerationX	= 2.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 2;	refship.InertiaBrakingY		= 2;
	refship.InertiaAccelerationZ	= 2.0;	refship.InertiaBrakingZ		= 2.0;
	
	refShip.GeraldSails.rey_a2	= 1;
	refShip.GeraldSails.rey_a3	= 1;
	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 18.5;
	refship.Track1.Width	= "6.5, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "16.0, 18.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//Nation
    refship.nation.england	= false;
	refship.nation.france	= false;
	refship.nation.holland	= false;
	refship.nation.pirate	= false;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// LuggerQuest			���������� ������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LUGGERQUEST]);
	refShip.Name            			= "LuggerQuest";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 16;
	refShip.Weight						= Tonnes2CWT(145);
	refShip.Capacity        			= 990								+ 31 * MOD_SKILL_ENEMY_RATE;
	refShip.CannonsQuantity				= 12;
	refShip.rcannon 							= 4;
	refShip.lcannon 							= 4;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 96							+ 3 * MOD_SKILL_ENEMY_RATE;
	refShip.MinCrew         				= 18;
	refShip.SpeedRate       		= 17.5									+ 0.1 * MOD_SKILL_ENEMY_RATE;
	refShip.TurnRate        		= 60									+ 1.2 * MOD_SKILL_ENEMY_RATE;
	refShip.Price           			= 50000;
	refShip.HP              				= 1100							+ 40 * MOD_SKILL_ENEMY_RATE;
	refShip.SP              				= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;
	refShip.fWindAgainstSpeed			= 6.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew = 8;
	refShip.buildtime = 20;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;

	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast5.Flag1 = FLAG_ENSIGN;					

	refship.WaterLine							= 0.2;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   			= 11.0								+ 0.1 * MOD_SKILL_ENEMY_RATE;
	refship.CabinType          			= "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";
	
	refship.InertiaAccelerationX	= 10.0;	refship.InertiaBrakingX		= 10.0;
	refship.InertiaAccelerationY	= 10;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ	= 10.0;	refship.InertiaBrakingZ		= 10.0;
	
	refShip.Height.Bombs.Y				= 1.5;	refShip.Height.Bombs.DY		= 0.7;
	refShip.Height.Grapes.Y				= 2.7;	refShip.Height.Grapes.DY	= 1.3;
	refShip.Height.Knippels.Y			= 13.4;	refShip.Height.Knippels.DY	= 9.7;
	refShip.Height.Balls.Y				= 1.5;	refShip.Height.Balls.DY		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "8.0, 10.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "3.0, 4.5";
	refship.Track2.Speed	= "0.15, 0.25";

	//////////////////////////////////////////////////////////////////////////
	// XebekVML			������
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_XebekVML]);
	refShip.Name				= "XebekVML";
	refship.Soundtype			= "lugger";
	refShip.Class				= 4;
	refShip.Cannon  			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber  		= 16;
	refShip.Weight				= Tonnes2CWT(380);
	refShip.Capacity   			= 1800								+ 50 * MOD_SKILL_ENEMY_RATE;
	refShip.CannonsQuantity		= 22;
	refShip.rcannon 					= 8;
	refShip.lcannon 					= 8;
	refShip.fcannon 					= 4;
	refShip.bcannon 					= 2;
	refShip.MaxCrew        			= 180							+ 4 * MOD_SKILL_ENEMY_RATE;
	refShip.MinCrew        			= 36;
	refShip.SpeedRate      	= 17.5									+ 0.1 * MOD_SKILL_ENEMY_RATE;
	refShip.TurnRate       	= 55									+ 1.0 * MOD_SKILL_ENEMY_RATE;
	refShip.Price          		= 150500;
	refShip.HP             			= 2500							+ 50 * MOD_SKILL_ENEMY_RATE;
	refShip.SP             			= 100;
	refship.CabinType          	= "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";
	refship.Type.Merchant		= false;
	refship.Type.War			= true;
	refship.QuestShip			= true; 
	refShip.fWindAgainstSpeed	= 2.0;
	refShip.sea_enchantment		= 1.8;
	refShip.lowpolycrew			= 7;
	refShip.buildtime			= 60;

	refship.WindAgainstSpeed   = 9.0;//boal

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast1.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
		
	refship.Rocking.y	= 0.5;
	refship.Rocking.az	= 0.04;
	
	refship.WaterLine	= -0.10;
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y	= 1.7;			refShip.Height.Bombs.DY	= 0.8;
	refShip.Height.Grapes.Y	= 3.4;			refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y	= 10.1;		refShip.Height.Knippels.DY	= 9.2;
	refShip.Height.Balls.Y		= 1.7;		refShip.Height.Balls.DY	= 0.8;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//////////////////////////////////////////////////////////////////////////
	// BrigQeen			����
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BRIGQEEN]);
	refShip.Name				= "BrigQeen";
	refship.Soundtype			= "lugger";
	refShip.Class				= 4;
	refShip.Cannon  			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber  		= 16;
	refShip.Weight				= Tonnes2CWT(350);
	refShip.Capacity   			= 2000								+ 50 * MOD_SKILL_ENEMY_RATE;
	refShip.CannonsQuantity		= 24;
	refShip.rcannon 					= 10;
	refShip.lcannon 					= 10;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;
	refShip.MaxCrew        			= 200							+ 4 * MOD_SKILL_ENEMY_RATE;
	refShip.MinCrew        			= 45;
	refShip.SpeedRate      	= 16.5									+ 0.1 * MOD_SKILL_ENEMY_RATE;
	refShip.TurnRate       	= 45									+ 1.0 * MOD_SKILL_ENEMY_RATE;
	refShip.Price          		= 167500;
	refShip.HP             			= 2800							+ 50 * MOD_SKILL_ENEMY_RATE;
	refShip.SP             			= 100;
	refship.CabinType          = "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";
	refship.Type.Merchant		= false;
	refship.Type.War			= true;
	refship.QuestShip			= true; 
	refShip.fWindAgainstSpeed	= 2.0;
	refShip.sea_enchantment		= 1.8;
	refShip.lowpolycrew			= 12;
	refShip.buildtime			= 60;

	refship.WindAgainstSpeed   = 6.0;//boal

	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag2 = FLAG_ENSIGN;
	
	refship.Rocking.y	= 0.5;
	refship.Rocking.az	= 0.04;
	
	refship.WaterLine	= -0.80;
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y	= 1.2;			refShip.Height.Bombs.DY	= 0.6;
	refShip.Height.Grapes.Y	= 3.1;			refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y	= 17.7;		refShip.Height.Knippels.DY	= 16.7;
	refShip.Height.Balls.Y		= 1.2;		refShip.Height.Balls.DY	= 0.6;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";

	//////////////////////////////////////////////////////////////////////////
	// BrigSW			���� ������� ����
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BRIGSW]);
	refShip.Name				= "BrigSW";
	refship.Soundtype			= "lugger";
	refShip.Class				= 4;
	refShip.Cannon  			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber  		= 16;
	refShip.Weight				= Tonnes2CWT(400);
	refShip.Capacity   			= 2100								+ 50 * MOD_SKILL_ENEMY_RATE;
	refShip.CannonsQuantity		= 24;
	refShip.rcannon 					= 10;
	refShip.lcannon 					= 10;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;
	refShip.MaxCrew        			= 210							+ 4 * MOD_SKILL_ENEMY_RATE;
	refShip.MinCrew        			= 42;
	refShip.SpeedRate      	= 15									+ 0.1 * MOD_SKILL_ENEMY_RATE;
	refShip.TurnRate       	= 45									+ 1.0 * MOD_SKILL_ENEMY_RATE;
	refShip.Price          		= 170500;
	refShip.HP             			= 3200							+ 50 * MOD_SKILL_ENEMY_RATE;
	refShip.SP             			= 100;
	refship.CabinType          	= "Cabin_Small"; // boal 28.03.05
	refship.DeckType           			= "Small";
	refship.Type.Merchant		= false;
	refship.Type.War			= true;
	refship.QuestShip			= true; 
	refShip.fWindAgainstSpeed	= 2.0;
	refShip.sea_enchantment		= 1.8;
	refShip.lowpolycrew			= 12;
	refShip.buildtime			= 60;

	refship.WindAgainstSpeed   = 7.50;//boal

	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag2 = FLAG_ENSIGN;
		
	refship.Rocking.y	= 0.5;
	refship.Rocking.az	= 0.04;
	
	refship.WaterLine	= -0.80;
	refship.SpeedDependWeight		= 0.3;
	refship.SubSeaDependWeight		= 0.6;
	refship.TurnDependWeight		= 0.3;
	
	refship.InertiaAccelerationX	= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY	= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y	= 1.5;			refShip.Height.Bombs.DY	= 0.7;
	refShip.Height.Grapes.Y	= 2.8;			refShip.Height.Grapes.DY	= 1.4;
	refShip.Height.Knippels.Y	= 16.9;		refShip.Height.Knippels.DY	= 15.4;
	refShip.Height.Balls.Y		= 1.5;		refShip.Height.Balls.DY	= 0.7;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;
	
	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 12;
	refship.Track1.Width	= "2.0, 3.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "4.0, 6.0";
	refship.Track2.Speed	= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	/// Corvette_quest			������ ���������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CORVETTE_QUEST]);
	refShip.Name            			= "Corvette_quest";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 24;
	refShip.Weight						= Tonnes2CWT(680);
	refShip.Capacity        			= 2700								+ 50 * MOD_SKILL_ENEMY_RATE;
	refShip.CannonsQuantity				= 40;
	refShip.rcannon 							= 18;
	refShip.lcannon 							= 18;
	refShip.fcannon 							= 2;
	refShip.bcannon 							= 2;
	refShip.MaxCrew         				= 250							+ 7 * MOD_SKILL_ENEMY_RATE;
	refShip.MinCrew         				= 50;
	refShip.SpeedRate				= 18									+ 0.2 * MOD_SKILL_ENEMY_RATE;
	refShip.TurnRate        		= 60									+ 0.7 * MOD_SKILL_ENEMY_RATE;
	refShip.Price           			= 1150000;
	refShip.HP              				= 3800							+ 70 * MOD_SKILL_ENEMY_RATE;
	refShip.SP              				= 100;
	refship.EmblemedSails.normalTex 	= "ships\parus_common_torn1.tga";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true; 
	refShip.fWindAgainstSpeed			= 2.2;
	refShip.sea_enchantment				= 1.5;
	refShip.lowpolycrew = 16;
	refShip.buildtime = 80;

	refship.Rocking.y = 0.8;
	refship.Rocking.az = 0.025;
	
	refship.WaterLine					= -0.50;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.7;
	refship.TurnDependWeight			= 0.35;
	refship.WindAgainstSpeed   = 5.5;//boal
	refship.CabinType          = "Cabin_Quest"; // boal 28.03.05
	refship.DeckType           			= "Medium";

	refShip.Flags.Mast1.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;

	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;
	
	refShip.Height.Bombs.Y				= 1.3;		refShip.Height.Bombs.DY		= 0.6;
	refShip.Height.Grapes.Y				= 3.1;		refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y			= 14.7;		refShip.Height.Knippels.DY	= 15.0;
	refShip.Height.Balls.Y				= 1.3;		refShip.Height.Balls.DY		= 0.6;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.17;
	refship.Track1.LifeTime = 12.5;
	refship.Track1.Width	= "4.0, 5.0";
	refship.Track1.Speed	= "6.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6.5;
	refship.Track2.Width	= "5.0, 7.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	//Nation
    refship.nation.england	= true;
	refship.nation.france	= true;
	refship.nation.holland	= true;
	refship.nation.pirate	= true;
	refship.nation.spain	= true;

	///////////////////////////////////////////////////////////////////////////
	//// ArabellaShip			������ ��������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_ARABELLA]);
	refShip.Name            			= "ArabellaShip";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(1050);
	refShip.Capacity        			= 3700						 + 50 * MOD_SKILL_ENEMY_RATE;
	refShip.CannonsQuantity				= 52;
	refShip.rcannon 							= 22;
	refShip.lcannon 							= 22;
	refShip.fcannon 							= 4;
	refShip.bcannon 							= 4;
	refShip.MaxCrew         				= 350					 + 7 * MOD_SKILL_ENEMY_RATE;
	refShip.MinCrew         				= 70;
	refShip.SpeedRate       		= 16							 + 0.1 * MOD_SKILL_ENEMY_RATE;
	refShip.TurnRate        		= 42							 + 0.8 * MOD_SKILL_ENEMY_RATE;
	refShip.Price           			= 1850000;
	refShip.HP              				= 6000					 + 150 * MOD_SKILL_ENEMY_RATE;
	refShip.SP              				= 100;
	refship.EmblemedSails.normalTex 	= "ships\sail_Arabella.tga";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true; 
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;	
	refship.WaterLine							= -0.6;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 4.0;//boal
	refship.CabinType          = "Cabin_Quest"; // boal 28.03.05
	refship.DeckType           			= "Frigate";

	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 3.1;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.5;	refShip.Height.Grapes.DY	= 2.2;
	refShip.Height.Knippels.Y			= 21.2;	refShip.Height.Knippels.DY	= 18.3;
	refShip.Height.Balls.Y				= 3.1;	refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	refShip.hullNums = 5; // LEO

	///////////////////////////////////////////////////////////////////////////
	//// FrigateQueen			����� �������� ����
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FRIGATEQUEEN]);
	refShip.Name            			= "FrigateQueen";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 32;
	refShip.Weight						= Tonnes2CWT(950);
	refShip.Capacity        			= 3200								+ 50 * MOD_SKILL_ENEMY_RATE;
	refShip.CannonsQuantity				= 52;
	refShip.rcannon 							= 22;
	refShip.lcannon 							= 22;
	refShip.fcannon 							= 6;
	refShip.bcannon 							= 6;
	refShip.MaxCrew         				= 300							+ 7 * MOD_SKILL_ENEMY_RATE;
	refShip.MinCrew         				= 60;
	refShip.SpeedRate       		= 17									+ 0.1 * MOD_SKILL_ENEMY_RATE;
	refShip.TurnRate        		= 45									+ 0.8 * MOD_SKILL_ENEMY_RATE;
	refShip.Price           			= 1270000;
	refShip.HP              				= 5500							+ 150 * MOD_SKILL_ENEMY_RATE;
	refShip.SP              				= 100;
	refship.EmblemedSails.normalTex 	= "ships\parus_common_torn2.tga";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true; 
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew = 20;
	refShip.buildtime = 100;
	
	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.035;	
	refship.WaterLine							= -0.6;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 4.5;//boal
	refship.CabinType          = "Cabin_Quest"; // boal 28.03.05
	refship.DeckType           			= "Frigate";
	
	refShip.Flags.Mast0.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY	= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 5.0;
	
	refShip.Height.Bombs.Y				= 3.1;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.5;	refShip.Height.Grapes.DY	= 2.2;
	refShip.Height.Knippels.Y			= 21.2;	refShip.Height.Knippels.DY	= 18.3;
	refShip.Height.Balls.Y				= 3.1;	refShip.Height.Balls.DY		= 1.5;
	
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.9;
	refShip.GeraldSails.rey_b2.vscale		= 0.7;
	refShip.GeraldSails.rey_b3.vscale		= 0.7;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 14.5;
	refship.Track1.Width	= "3.7, 3.9";
	refship.Track1.Speed	= "7.0, 8.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 8.5;
	refship.Track2.Width	= "8.0, 9.0";
	refship.Track2.Speed	= "0.15, 0.25";
	
	///////////////////////////////////////////////////////////////////////////
	/// Flyingdutchman			������� ���������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FLYINGDUTCHMAN]);
	refShip.Name            			= "Flyingdutchman";  // ��
	refship.Soundtype					= "lineship";
	refShip.Class						= 2;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(1800);
	refShip.Capacity        			= 5200								+ 50 * MOD_SKILL_ENEMY_RATE;
	refShip.CannonsQuantity				= 52;
	refShip.rcannon 							= 23;
	refShip.lcannon 							= 23;
	refShip.fcannon 							= 6;
	refShip.bcannon 							= 0;
	refShip.MaxCrew         				= 444							+ 7 * MOD_SKILL_ENEMY_RATE;
	refShip.MinCrew         				= 88;
	refShip.SpeedRate				= 15									+ 0.1 * MOD_SKILL_ENEMY_RATE;
	refShip.TurnRate        		= 40									+ 0.8 * MOD_SKILL_ENEMY_RATE;
	refShip.Price           			= 2890000;
	refShip.HP              				= 7700							+ 150 * MOD_SKILL_ENEMY_RATE;
	refShip.SP              				= 100;
	refship.EmblemedSails.normalTex 	= "ships\parus_common_torn.tga";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true; 
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew = 24;
	refShip.buildtime = 120;

	refship.Rocking.y = 0.5;
	refship.Rocking.az = 0.035;
	
	refship.WaterLine							= 0.5;

	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed   = 3.0;//boal
	refship.CabinType          = "CabineFDM"; // boal 28.03.05
	refship.DeckType           = "Big";
	
	refShip.Flags.Mast1.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 4.0;	refship.InertiaBrakingX		= 3.5;
	refship.InertiaAccelerationY	= 3.0;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ	= 4.0;	refship.InertiaBrakingZ		= 3.5;
	
	refShip.Height.Bombs.Y				= 6.4;		refShip.Height.Bombs.DY		= 3.2;
	refShip.Height.Grapes.Y				= 8.5;		refShip.Height.Grapes.DY	= 4.2;
	refShip.Height.Knippels.Y			= 27.4;		refShip.Height.Knippels.DY	= 23.4;
	refShip.Height.Balls.Y				= 6.4;		refShip.Height.Balls.DY		= 3.2;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_b1		= 1;
	refShip.GeraldSails.rey_b1.vscale		= 0.8;
	refShip.GeraldSails.rey_b2.vscale		= 0.65;
	refShip.GeraldSails.rey_b3.vscale		= 0.55;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.25;
	refship.Track1.LifeTime = 9.5;
	refship.Track1.Width	= "7.0, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7.5;
	refship.Track2.Width	= "8.0, 10.0";
	refship.Track2.Speed	= "1.0, 2.0";

	///////////////////////////////////////////////////////////////////////////
	//// Santisima			������� �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SANTISIMA]);
	refShip.Name            			= "Santisima";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(3200);
	refShip.Capacity        			= 5750								+ 75 * MOD_SKILL_ENEMY_RATE;
	refShip.CannonsQuantity				= 106;
	refShip.rcannon 							= 46;
	refShip.lcannon 							= 46;
	refShip.fcannon 							= 6;
	refShip.bcannon 							= 8;
	refShip.MaxCrew         				= 800							+ 10 * MOD_SKILL_ENEMY_RATE;
	refShip.MinCrew         				= 160;
	refShip.SpeedRate				= 13									+ 0.1 * MOD_SKILL_ENEMY_RATE;
	refShip.TurnRate        		= 32									+ 0.5 * MOD_SKILL_ENEMY_RATE;
	refShip.Price           			= 3000000;
	refShip.HP              				= 10700							+ 130 * MOD_SKILL_ENEMY_RATE;
	refShip.SP              				= 100;
	refship.CanEncounter = false;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true; 
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.0;
	refShip.lowpolycrew = 28;
	refShip.buildtime = 140;

	refship.Rocking.y = 0.3;
	refship.Rocking.az = 0.02	;

	refship.WaterLine							= 0.5;
	refship.SpeedDependWeight			= 0.45;
	refship.SubSeaDependWeight			= 1.8;
	refship.TurnDependWeight			= 0.45;
	refship.WindAgainstSpeed  			= 1.2;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";

	refShip.Flags.Mast2.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast3.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast5.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 2.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 2;	refship.InertiaBrakingY		= 2;
	refship.InertiaAccelerationZ	= 2.0;	refship.InertiaBrakingZ		= 2.0;
	
	refShip.Height.Bombs.Y				= 8.0;		refShip.Height.Bombs.DY		= 4.0;
	refShip.Height.Grapes.Y				= 9.7;		refShip.Height.Grapes.DY	= 4.8;
	refShip.Height.Knippels.Y			= 34.7;		refShip.Height.Knippels.DY	= 26.0;
	refShip.Height.Balls.Y				= 8.0;		refShip.Height.Balls.DY		= 4.0;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_c1		= 1;
	refShip.GeraldSails.rey_c1.vscale		= 0.98;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.98;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 18.5;
	refship.Track1.Width	= "6.5, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "16.0, 18.0";
	refship.Track2.Speed	= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	//// SoleyRu			����������� �������
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SOLEYRU]);
	refShip.Name            			= "SoleyRu";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber      			= 42;
	refShip.Weight						= Tonnes2CWT(4500);
	refShip.Capacity        			= 6800								+ 120 * MOD_SKILL_ENEMY_RATE;
	refShip.CannonsQuantity				= 112;
	refShip.rcannon 							= 48;
	refShip.lcannon 							= 48;
	refShip.fcannon 							= 6;
	refShip.bcannon 							= 10;
	refShip.MaxCrew         				= 1200							+ 20 * MOD_SKILL_ENEMY_RATE;
	refShip.MinCrew         				= 240;
	refShip.SpeedRate				= 10.6									+ 0.1 * MOD_SKILL_ENEMY_RATE;
	refShip.TurnRate        		= 29									+ 0.5 * MOD_SKILL_ENEMY_RATE;
	refShip.Price           			= 3950000;
	refShip.HP              				= 18000							+ 200 * MOD_SKILL_ENEMY_RATE;
	refShip.SP              				= 100;
	refship.EmblemedSails.normalTex 	= "ships\parus_SoleyRu.tga";

	refship.CanEncounter = false;
	
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true; 
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.0;
	refShip.lowpolycrew = 28;
	refShip.buildtime = 140;

	refship.Rocking.y = 0.3;
	refship.Rocking.az = 0.02	;

	refship.WaterLine							= 0.5;
	refship.SpeedDependWeight			= 0.45;
	refship.SubSeaDependWeight			= 1.8;
	refship.TurnDependWeight			= 0.45;
	refship.WindAgainstSpeed   			= 1.3;//boal
	refship.CabinType          			= "Cabin_Huge"; // boal 28.03.05
	refship.DeckType           			= "Big";

	refShip.Flags.Mast1.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast2.Flag1 = FLAG_SPECIAL;
	refShip.Flags.Mast3.Flag1 = FLAG_ENSIGN;
	refShip.Flags.Mast4.Flag1 = FLAG_ENSIGN;
	
	refship.InertiaAccelerationX	= 2.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 2;	refship.InertiaBrakingY		= 2;
	refship.InertiaAccelerationZ	= 2.0;	refship.InertiaBrakingZ		= 2.0;
	
	refShip.Height.Bombs.Y				= 8.6;		refShip.Height.Bombs.DY		= 4.3;
	refShip.Height.Grapes.Y				= 12.5;		refShip.Height.Grapes.DY	= 6.2;
	refShip.Height.Knippels.Y			= 36.8;		refShip.Height.Knippels.DY	= 29.6;
	refShip.Height.Balls.Y				= 8.6;		refShip.Height.Balls.DY		= 4.3;
	
	refShip.GeraldSails.rey_b2		= 1;
	refShip.GeraldSails.rey_b3		= 1;
	refShip.GeraldSails.rey_c1		= 1;
	refShip.GeraldSails.rey_c1.vscale		= 0.98;
	refShip.GeraldSails.rey_b2.vscale		= 0.98;
	refShip.GeraldSails.rey_b3.vscale		= 0.98;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.30;
	refship.Track1.LifeTime = 18.5;
	refship.Track1.Width	= "6.5, 7.5";
	refship.Track1.Speed	= "8.0, 9.0";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 10.5;
	refship.Track2.Width	= "16.0, 18.0";
	refship.Track2.Speed	= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	/// FORT
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FORT]);
	refShip.Name									= "Fort";
	refShip.isFort      				= true; // ��� �������� �������� �� rRealShip
	refShip.Class						= 1;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS48;
	refShip.MaxCaliber					= 48;
	refShip.Weight								= Tonnes2CWT(22500);
	refShip.Capacity							= 900000;
	refShip.CannonsQuantity						= 68;
	refShip.rcannon 							= 68;
	refShip.lcannon 							= 0;
	refShip.fcannon 							= 0;
	refShip.bcannon 							= 0;
	refShip.MaxCrew         			= 3200;
	refShip.OptCrew         			= 2400;
	refShip.MinCrew         			= 1600;
	refShip.SpeedRate							= 0.0;
	refShip.TurnRate							= 0;
	refShip.Price									= 120000;
	refShip.HP										= 60000;
	refShip.SP										= 100;
	refShip.buildtime = 240;

	refShip.CanEncounter	= false;

	/// Check
	for (int i=0; i<SHIP_TYPES_QUANTITY_WITH_FORT-1; i++)
	{
	  	makeref(refShip, ShipsTypes[i]);
		if (!CheckAttribute(refShip,"Name")) { continue; }
		if (!CheckAttribute(refShip,"TurnRate"))
		{
			Trace("ERROR: Ship " + i + " doesn't have TurnRate attribute");
		}
		if (!CheckAttribute(refShip,"SpeedRate"))
		{
			Trace("ERROR: Ship " + i + " doesn't have SpeedRate attribute");
		}
		if (!CheckAttribute(refShip,"Class"))
		{
			Trace("ERROR: Ship " + i + " doesn't have class attribute");
		}
		else
		{
			int iClass = sti(refShip.Class);
			if (iClass > 7) { Trace("ERROR: Ship " + i + " class > 7"); }
			if (iClass < 1) { Trace("ERROR: Ship " + i + " class < 1"); }
		}
		refship.InertiaAccelerationY = stf(refship.InertiaAccelerationY) / 6.0;
		// boal 10/11/05 ������� ����������� ������
		refShip.OptCrew = sti(refShip.MaxCrew);
		refShip.MaxCrew = makeint(sti(refShip.MaxCrew) * 1.25 + 0.5); // ��������
		/// ��� ��������� ��� ���� - ������� ���� �������?  ���������� ��������� � ������������� ����, ������� ��� ������� �� ����� ��� ����
		refShip.cannonr  = refShip.rcannon;
		refShip.cannonl  = refShip.lcannon;
		refShip.cannonf  = refShip.fcannon;
		refShip.cannonb  = refShip.bcannon;
	}
}