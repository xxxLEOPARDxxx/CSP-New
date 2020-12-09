#include "TEXT\$language\DIALOGS\EncShipSale_dialog.h"
//#20180914-02
void ProcessDialogEvent()
{
    ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

    switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "First time":
            FillShipEncDialog(true, NPChar, Link);
            NextDiag.TempNode = "Meeting";
        break;
        case "Meeting":
            FillShipEncDialog(false, NPChar, Link);
            NextDiag.TempNode = "Meeting";
        break;
        case "DeclineShip":
            NPChar.dialog.filename = "Common_citizen.c";
			NextDiag.CurrentNode = "First time";
			DialogExit();
        break;
        case "ShowMeShip":
            NextDiag.TempNode = "Meeting";
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
            LaunchShipEncSale(npchar);
        break;
        case "ShipSold":
            dialog.text = GetRandSubString(DLG_TEXT_BASE[72]);
            link.l1 = GetRandSubString(DLG_TEXT_BASE[56]);
            NPChar.dialog.filename = "Common_citizen.c";
            NextDiag.CurrentNode = "First time";
        break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

void FillShipEncDialog(bool isFirst, ref NPChar, aref Link)
{
    string sTemp1, sTemp2;
    int nIdx1, nIdx2, nIdx3, nIdx4;
    bool isMine = false;
    bool isDead = false;

    int iShip = sti(NPChar.Ship.Type);
    ref refBaseShip = GetRealShip(iShip);
    string sShip = XI_Convertstring(refBaseShip.BaseName);

    if(isFirst) {
        sTemp2 = LinkRandPhrase(DLG_TEXT_BASE[37], DLG_TEXT_BASE[38], DLG_TEXT_BASE[39]);
        nIdx3 = 18;
        if(rand(4)==1) {
            nIdx3 = 16;
            isDead = true;
        }
        if(NPChar.sex == "man") {
            if(rand(3)==1) {
                isMine = true;
                isDead = false;
                nIdx1 = 1;
                nIdx2 = 4;
                nIdx3 = 17;
            }
            else {
                 nIdx1 = 0;
                 nIdx2 = 6;
            }
        }
        else {
            nIdx1 = 0;
            nIdx2 = 5;
        }
        sTemp1 = sTemp2 + DLG_TEXT_BASE[nIdx1] + GetRandSubString(DLG_TEXT_BASE[nIdx2]) + GetRandSubString(DLG_TEXT_BASE[12]);
        if(isDead)
            nIdx1 = 7;
        else
            nIdx1 = 8;
        sTemp1 += GetRandSubString(DLG_TEXT_BASE[nIdx1]);
        sTemp2 = DLG_TEXT_BASE[nIdx3] + NPChar.ship.name + DLG_TEXT_BASE[19] + sShip + GetRandSubString(DLG_TEXT_BASE[20]);
        sTemp1 += sTemp2;
        sTemp1 += GetRandSubString(DLG_TEXT_BASE[43]);
        sTemp1 += GetRandSubString(DLG_TEXT_BASE[44]);
        sTemp1 += GetRandSubString(DLG_TEXT_BASE[29]);
        sTemp1 += GetRandSubString(DLG_TEXT_BASE[33]);

        dialog.text = sTemp1;
        link.l1 = LinkRandPhrase(DLG_TEXT_BASE[48], DLG_TEXT_BASE[49], RandPhraseSimple(DLG_TEXT_BASE[50], DLG_TEXT_BASE[51]));
    }
    else {
        dialog.text = GetRandSubString(DLG_TEXT_BASE[62]);
        link.l1 = GetRandSubString(DLG_TEXT_BASE[52]);
    }
    link.l1.go = "ShowMeShip";
    link.l2 = RandPhraseSimple(GetRandSubString(DLG_TEXT_BASE[65]), GetRandSubString(DLG_TEXT_BASE[69]));
    link.l2.go = "Exit";
    link.l3 = GetRandSubString(DLG_TEXT_BASE[68]);
    link.l3.go = "DeclineShip";
}
