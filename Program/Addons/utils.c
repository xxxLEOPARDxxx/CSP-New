#include "Addons\Korsar_Maxim_func.c"		//Функции Korsar-а Maxim-а
#include "Addons\LORD_func.c"	        	//Функции LORD-а


/* PROGRAM/LUGGER/UTILS.C */
/////////////////////////////////////////////////////////////////////////////////
// Раздача еды
/////////////////////////////////////////////////////////////////////////////////
void SetFoodToCharacter(ref chr, int iQuantity, int iFoodQuantity)
{
	int d = 1;
	int iSum = 0;
	string sFood = "";
	for(int f = 1; f <= iQuantity; f++)
	{
		sFood = "Food" + f;
		if(CheckAttribute(chr, "items." + sFood))
		{
			DeleteAttribute(chr, "items." + sFood);
		}
		
		switch(f)
		{
			case 1: d = 2; break;
			case 2: d = 4; break;
			case 3: d = 6; break;
			case 4: d = 8; break;
			case 5: d = 10; break;
		}
		
		iSum = iFoodQuantity / d;	
		TakeNItems(chr, sFood, iSum);
	}
}

/////////////////////////////////////////////////////////////////////////////////
// Переключение режима абордажа
/////////////////////////////////////////////////////////////////////////////////
void GetBoardModeToLocation(ref loc)
{
	if(!CheckAttribute(loc, "CheckBoardMode"))
	{
		return;	
	}
	
	string sFile = "DeckLowVSMedium_locators";
	
	switch(loc.id)
	{
		case "BOARDING_SMALL_DECK":
			if(bBoardMode)
			{
				sFile = "DeckLowVSMedium_locators_lugger";
			}
			else
			{
				sFile = "DeckLowVSMedium_locators";
			}
		break;
		
		case "BOARDING_MEDIUM_DECK":
			if(bBoardMode)
			{
				sFile = "deckLowVSBig_locators_lugger";
			}
			else
			{
				sFile = "deckLowVSBig_locators";
			}
		break;
		
		case "BOARDING_BIG_DECK":
			if(bBoardMode)
			{
				sFile = "deckMediumVSBig_locators_lugger";
			}
			else
			{
				sFile = "deckMediumVSBig_locators";
			}
		break;	

		case "BOARDING_LNSHP_FRGT_DECK":
			if(bBoardMode)
			{
				sFile = "deckLineshipVSFrigate_locators_lugger";
			}
			else
			{
				sFile = "deckLineshipVSFrigate_locators";
			}
		break;
	}
	
	loc.models.always.locators = sFile;
	
	Log_TestInfo("Считываем тип абордажа.");
	Log_TestInfo("Сменили локаторы для локации абордажа: " + loc.id);
	Log_TestInfo("Имя файла локаторов для локации абордажа: " + loc.models.always.locators);
}