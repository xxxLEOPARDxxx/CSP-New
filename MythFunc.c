// Check and return voice NPC
string GetVoiceChr(aref chr)
{
    string voice = "none GetVoiceChr";
    if (CheckAttribute(chr, "greeting") && chr.greeting != "")
    {
        return chr.greeting;
    }
    else
    {
        switch (chr.sex)
        {
        case "man":
            voice = "cit_common";
            break;
        case "skeleton":
            voice = "skeleton";
            break;
        case "woman":
            voice = "Gr_Woman_Citizen";
            break;
        }
    }
    return voice;
}
// New random functions
string RandFromThreeDightText(string _Num0, string _Num1, string _Num2)
{
    switch (rand(2))
    {
    case 0:
        return _Num0;
        break;
    case 1:
        return _Num1;
        break;
    case 2:
        return _Num2;
        break;
    }
}
string RandFromFourDightText(string _Num0, string _Num1, string _Num2, string _Num3)
{
    switch (rand(3))
    {
    case 0:
        return _Num0;
        break;
    case 1:
        return _Num1;
        break;
    case 2:
        return _Num2;
        break;
    case 3:
        return _Num3;
        break;
    }
}
// Find locator from group by search type
string FindLocatorFromGroup(string group, string typefind)
{
    float locx = 0.0;
    float locy = 0.0;
    float locz = 0.0;
    string homelocator = "";
    GetCharacterPos(GetMainCharacter(), &locx, &locy, &locz);
    if (typefind == "random" || typefind == "random_must_be")
    {
        homelocator = LAi_FindFreeRandomLocator(group);
    }
    if (typefind == "random_must_be_far")
    {
        homelocator = LAi_FindFarLocator(group, locx, locy, locz);
    }
    else
    {
        homelocator = LAi_FindNearestFreeLocator(group, locx, locy, locz);
    }
    if (homelocator == "" && typefind == "random_must_be_far")
    {
        homelocator = LAi_FindFarLocator(group, locx, locy, locz);
    }
    if (homelocator == "" && typefind == "random_must_be")
    {
        homelocator = LAi_FindFarLocator(group, locx, locy, locz);
    }
    if (homelocator == "" && typefind == "random_must_be_near")
    {
        homelocator = LAi_FindNearestLocator(group, locx, locy, locz);
    }
    return homelocator;
}
// Correct BackSlash
//string BackSlash()
//{
//    int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
//    string sTemp = LanguageConvertString(idLngFile,"backslash");
//    LanguageCloseFile(idLngFile);
//    return sTemp;
//}
// Restore Guns for MH and officers
void RestoreGunPlayerOrOff(ref chref)
{
    aref arItm;
    string stmp = GetCharacterEquipByGroup(chref,GUN_ITEM_TYPE);
    if(stmp!="")
    {
        Items_FindItem(stmp,&arItm);
        if(CheckAttribute(arItm,"chargeQ"))
        {
            LAi_GunSetChargeQuant(chref,sti(arItm.chargeQ));
        }
        else
        {
            LAi_GunSetChargeQuant(chref,0);
        }
    }
}
void FullLoadForGuns()
{
    int i, iOfficer;
    RestoreGunPlayerOrOff(pchar);
    for (i=1; i<=MAX_NUM_FIGHTERS; i++)
    {
        iOfficer = GetOfficersIndex(Pchar, i);
        if (iOfficer != -1)
        {
            RestoreGunPlayerOrOff(&characters[iOfficer]);
        }
    }
}
// Get Contraband relation For MH without change relation
int GetContrabandRep()
{
    if(!CheckAttribute(pchar, "questTemp.Contraband.relation"))
    {
        pchar.questTemp.Contraband.relation = 60;
    }
    return makeint(pchar.questTemp.Contraband.relation);
}
// Need clear dead_body on load location
void DelDeadMan(string locid)
{
    ref loc   = &locations[FindLocation(locid)];
    if (CheckAttribute(loc, "locators.dead_body"))
    {
        int i,iDead;
        string locatorName = "";
        aref DeadLoc, st;
        makearef(st, loc.locators.dead_body);
        iDead = GetAttributesNum(st);
        for (i=0; i<iDead; i++)
        {
            DeadLoc = GetAttributeN(st, i);
            locatorName = GetAttributeName(DeadLoc);
            Location_DeleteLocator(loc, locatorName, "dead_body");
        }
        Log_SetActiveAction("Nothing");
        BLI_RefreshCommandMenu();
    }
}
// Weather: new storm clean
void SetTimersForBadWeather()
{
    if(WeatherParams.Rain && !CheckAttribute(pchar, "timers_for_bad_weather.Rain"))
    {
        SetTimerConditionParam("DeleteRain", "DeleteRain", 0, 0, 0, MakeInt(GetHour() + 6 + rand(7)), false);
        pchar.timers_for_bad_weather.Rain = true;
    }
    if(WeatherParams.Tornado && !CheckAttribute(pchar, "timers_for_bad_weather.Tornado"))
    {
        SetTimerConditionParam("DeleteTornado", "DeleteTornado", 0, 0, 0, MakeInt(GetHour() + 6 + rand(7)), false);
        pchar.timers_for_bad_weather.Tornado = true;
    }
    if(WeatherParams.Storm && !CheckAttribute(pchar, "timers_for_bad_weather.Storm"))
    {
        SetTimerConditionParam("DeleteStorm", "DeleteStorm", 0, 0, 0, MakeInt(GetHour() + 6 + rand(7)), false);
        pchar.timers_for_bad_weather.Storm = true;
    }
}
// Fixes for mushkets
// No write same code in many files, need just call this function
void FirstSetMush (aref chr)
{
    while (FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE) != "")
    {
        TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE));
    }
    while (FindCharacterItemByGroup(chr, GUN_ITEM_TYPE) != "")
    {
        TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, GUN_ITEM_TYPE));
    }
    GiveItem2Character(chr, "unarmed");
    EquipCharacterbyItem(chr, "unarmed");
    string sMush = "mushket";
    if (chr.model == "MusketeerEnglish_2")
        sMush = "mushket2x2";
    GiveItem2Character(chr, sMush);
    EquipCharacterbyItem(chr, sMush);
    chr.items.bullet = 300;
    chr.isMusketer = true;
    if (!CheckAttribute(chr, "MusketerDistance"))
        chr.MusketerDistance = 5.0 + frand(5.0);
}
void RestoreMushketForMHFromSit(aref chr)
{
    if(chr.id == pchar.id && IsEquipMusketItem (chr) && chr.model.animation == "man")
    {
        chr.model.animation = "mushketer";
        SetNewModelToChar(chr);
    }
}
// Need for main menu, aslo need for trade book, filters of grass & select MH, aslo use in save\load & speak interface
bool UseWideScreenMonitor()
{
    float screen_x = stf(Render.screen_x);
    float screen_y = stf(Render.screen_y);
    float screen_ratio = screen_x/screen_y;
    if(screen_ratio > 1.7)
    {
        return true;
    }
    return false;
}
int GetIntegralDataFromScreen(int oldscreen, int newscreen)
{
    if(UseWideScreenMonitor())
    {
        return newscreen;
    }
    else
    {
        return oldscreen;
    }
}
void HideSectionFromScreen(string secName)
{
    if(UseWideScreenMonitor())
    {
        SetNodeUsing(secName, false);
        SetNodeUsing(secName + "_WD", true);
    }
    else
    {
        SetNodeUsing(secName, true);
        SetNodeUsing(secName + "_WD", false);
    }
}
string GetSectionFromScreen(string secName)
{
    if(UseWideScreenMonitor())
    {
        return secName + "_WD";
    }
    else
    {
        return secName;
    }
}
/// Use in ChestToOfficers.c, fix box
void FreeFromBox(string temp)
{
    bMainCharacterInBox = false;
}
// A new label system. The text is taken not from the locator parameters, take from the location parameters.
string FindLableReload(string FromLocIsl)
{
    int iTmp, iTmp1;
    iTmp = FindLocation(FromLocIsl);
    if(iTmp != -1)
    {
        if(CheckAttribute(&Locations[FindLocation(FromLocIsl)], "id.label"))
        {
            if(Locations[iTmp].id.label == "Street")
            {
                return Locations[iTmp].townsack + " Town";
            }
            else
            {
                return Locations[iTmp].id.label;
            }
        }
    }
    else
    {
        iTmp1 = FindIsland(FromLocIsl);
        if(iTmp1 != -1)
        {
            return "Near_Island_Sea";
        }
    }
    return "";
}
// Chech ship name, need for dialogs.
bool GetShipName(ref _refCharacter)
{
    if (CheckAttribute(_refCharacter, "Ship.Type") && sti(_refCharacter.Ship.Type) != SHIP_NOTUSED && CheckAttribute(_refCharacter, "Ship.name") && _refCharacter.Ship.Name != "")
    {
        return true;
    }
    return false;
}
string DialogByCheckShip (ref _refCharacter, string sTextNoShip, string sTextHaveShip)
{
    if (!GetShipName(_refCharacter))
    {
        return sTextNoShip;
    }
    return sTextHaveShip;
}
// Fix island line on sea battle interface
string GetLineIslandText()
{
    string island = Sea_FindNearIsland();
    if(island == "none")
    {
        return "Open sea";
    }
    return island;
}
// Fix lighting after relax in cabin
void RestartCapCabine()
{
    int ldLoc = FindLoadedLocation();
    UnloadLocation(&Locations[ldLoc]);
    bCabinStarted = false;
    Sea_CabinStartNow();
}
// Check Enable New rest in tavern
bool EnableNewRentRoom()
{
    if (chrDisableReloadToLocation || CheckAttribute(pchar, "questTemp.different.Church_NightGuard"))
    {
        return false;
    }
    if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern")
    {
        return false;
    }
    if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackStreet_toRoom")
    {
        return false;
    }
    if (pchar.questTemp.different == "FackWaitress_toRoomUp" || pchar.questTemp.different == "FackStreet_toRoomUp")//Waitress quest
    {
        return false;
    }
    return true;
}
bool FreeDialog (ref _refCharacter)
{
    if(CheckAttribute(_refCharacter, "FreezeDialog"))
    {
        DeleteAttribute(_refCharacter, "FreezeDialog");
        return false;
    }
    if(CheckAttribute(_refCharacter, "chr_ai.hpchecker") && _refCharacter.chr_ai.hpchecker == true && !CheckAttribute(_refCharacter, "AlwaysFreeDialog"))
    {
        return false
    }
    return true;
}
