
int LocationInitReefs(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ”щелье ƒь€вола
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	locations[n].id = "MountainPath";
	locations[n].id.label = "MountainPath";
	locations[n].image = "loading\outside\MountainPath.tga";
	locations[n].worldmap = "MountainPath";
	locations[n].parent_colony = "MountainPath";
	//Sound
	locations[n].type = "MountainPath";
	locations[n].islandId = "Reefs";
	locations[n].onUninhabitedIsland = true;
	locations[n].DisableEncounters = true;
	locations[n].questflower = 1;
	locations[n].Chestgennot = true; // не генерить сундуки
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\MountainPathDMChest";
	Locations[n].models.always.shore = "MountainPathDMChest";
	locations[n].models.always.shore.sea_reflection = 1;
	Locations[n].models.always.seabed = "MountainPathDMChest_sb";
	Locations[n].models.always.locators = "MountainPathDMChest_locators"; 
		
	Locations[n].models.always.grassPatch = "MountainPath_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	Locations[n].models.always.Waterfall1 = "WaterFall1";
	Locations[n].models.always.Waterfall1.uvslide.v0 = 0.6;
    Locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall1.level = 50;
	
	Locations[n].models.always.Waterfall2 = "WaterFall2";
	Locations[n].models.always.Waterfall2.uvslide.v0 = 0.3;
    Locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall2.level = 49;
	
	//Day
	locations[n].models.day.charactersPatch = "MountainPathDMChest_patch_day";
	//Night
	locations[n].models.night.charactersPatch = "MountainPathDMChest_patch_day";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";		
	//Reload map
	Locations[n].reload.l1.name = "reload1_back";
    Locations[n].reload.l1.go = "Reefs";
    Locations[n].reload.l1.emerge = "reload_2";
    Locations[n].reload.l1.autoreload = "0";
    Locations[n].reload.l1.label = "Sea";
	Locations[n].locators_radius.reload.reload1_back = 2.5;
	
	Locations[n].locators_radius.item.splash1 = 1.0;
	Locations[n].locators_radius.item.splash2 = 1.0;
	Locations[n].locators_radius.item.splash3 = 1.0;
	Locations[n].locators_radius.item.splash4 = 1.0;
	Locations[n].locators_radius.item.splash5 = 1.0;

	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Ѕухта прокл€тых
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "DeckWithReefs";
	locations[n].id.label = "DeckWithReefs";
	locations[n].filespath.models = "locations\Outside\Shores\GuardGrot";
	locations[n].image = "loading\outside\DeckWithReefs.tga";
	//Sound
	locations[n].type = "DeckWithReefs";
 	locations[n].islandId = "Reefs";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	locations[n].Chestgennot = true; // не генерить сундуки
	//Models
	//Always
	locations[n].models.always.grot = "Grotto1";
	locations[n].models.always.grot.sea_reflection = 1;
	locations[n].models.always.seabed = "Grotto1_sb";
	locations[n].models.always.grassPatch = "Grotto1_grass";
	locations[n].models.always.locators = "Grotto1_locators";
	
	locations[n].models.always.Cfall = "Cfall";
	locations[n].models.always.Water = "Water";
	
	Locations[n].models.always.Waterfall1 = "Waterfall1";
	Locations[n].models.always.Waterfall1.uvslide.v0 = 0.7;
	Locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall1.level = 50;

	Locations[n].models.always.Waterfall2 = "Waterfall2";
	Locations[n].models.always.Waterfall2.uvslide.v0 = 0.3;
	Locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall2.level = 50;
	//Day
	locations[n].models.day.charactersPatch = "Grotto1_patch";
	//Night
	locations[n].models.night.charactersPatch = "Grotto1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	// locations[n].alwaysStorm = true; //живем в штормах
	// locations[n].storm = true;
	// locations[n].tornado = true;

	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Reefs";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1 = 3.0;
	
	// locations[n].DisableOfficers = "1";
	
	string sloc;
	int i;
	for (i=1; i<=95; i++)
	{
		sloc = "fire"+i;
		locations[n].locators_radius.item.(sloc) = 1.0;
	}
	for (i=1; i<=4; i++)
	{
		sloc = "incasfire"+i;
		locations[n].locators_radius.item.(sloc) = 1.5;
	}
	n = n + 1;

	return n;
}
