#include "Addons\Korsar_Maxim_func.c"		//������� Korsar-� Maxim-�
#include "Addons\LORD_func.c"	        	//������� LORD-�


/* PROGRAM/LUGGER/UTILS.C */
/////////////////////////////////////////////////////////////////////////////////
// ������� ���
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
			case 1: d = 12; break;
			case 2: d = 14; break;
			case 3: d = 16; break;
			case 4: d = 18; break;
			case 5: d = 20; break;
		}
		
		iSum = makeint(iFoodQuantity / d)+1;
		TakeNItems(chr, sFood, iSum);
	}
}

/////////////////////////////////////////////////////////////////////////////////
// ������������ ������ ��������
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
	
	Log_TestInfo("��������� ��� ��������.");
	Log_TestInfo("������� �������� ��� ������� ��������: " + loc.id);
	Log_TestInfo("��� ����� ��������� ��� ������� ��������: " + loc.models.always.locators);
}