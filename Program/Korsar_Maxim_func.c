//Korsar Maxim - функции для некоторых вычислений
string GetPggTavernGreeting(ref rChar)
{
    switch (rChar.sex)
    {
    case "skeleton":
        return "skeleton";
    break;
	
    case "man":
        return "Gr_Tavern_Mate";
    break;
	
    case "woman":
        return "Gr_Woman_Citizen";
    break;
    }
}

string GetPGGDialog(ref rChar)
{
    switch (rChar.sex)
    {
    case "skeleton":
        return "pgg_dialog.c";
    break;
    case "man":
        return "pgg_dialog.c";
    break;
    case "woman":
        return "pgg_dialog_town.c";
    break;
    }
}