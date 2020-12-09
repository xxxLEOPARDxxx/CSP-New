// BUHO Commodore In Command (CIC) Mod
// Vars and routines
// Vers. 01.000.000 - GOF 1.2
// KEYWORD: BUHO-CIC

//USAGE
/*
In the battle interface (sea):
- 5: All fleet load balls.
- 6: All fleet load grapes.
- 7: All fleet load chain.
- 8: All fleet load bombs.
- 9: All fleet load at will.
- O: All fleet sail away (letter "O").
- L: All fleet lower sails.
- P: All fleet protect flagship.
*/

// NOTES AND CHANGELOG

/*
COMPATIBILITY: GOF 1.1
DEPENDENCIES
- Program\seadogs.c
- Program\battle_interface\BattleInterface.c
- Program\Controls\init_pc.c
- texts\russian\ControlNames.txt -> Uncommentable file <-
*/
bool CIC_CdreCommand = False;			// Fleet command flag - True if commands are fleet-wide.

/*
Called from ProcessControls (key event handler) in seadogs.c.
The procedure iterates the companions, sending the engine messages needed to activate
BI_LaunchCommand in Program\battle_interface\BattleInterface.c
*/
void CIC_SendCommand(string sComm)
{
	int nShipType;
	ref rChr;
	int i;

	CIC_CdreCommand = True;						// Set the fleet-wide flag to stop per-ship logs and sounds.
												// Do NOT "ret" without toggling the flag!

	for (i = 1; i < COMPANION_MAX; i++)
	{
		int cn;									// Companion index
		cn = GetCompanionIndex(PChar, i);
		if (cn == -1) continue;
		makeref(rChr, Characters[cn]);			// Companion char
		nShipType = GetCharacterShipType(rChr);
		if (nShipType == SHIP_NOTUSED) continue;
		// Event used here:
		// Event("BI_LaunchCommand",		<--- The event handler
		//       "lsls",					<--- Parameters mask
		//       charIdx,					<--- Involved char (the companion)
		//       "<BI_command_name>",		<--- the BI command
		//       targetNum,					<--- Variable parameter - Magic number 1...4 for ammo
		//       locName					<--- Variable parameter
		//       );
		switch (sComm)
		{
			case "CIC_LoadBalls"	:
                /*
                If ship cannons are charged with balls do nothing,
                else send the message.
                Same for grapes, chain and bombs.
                */
                if (!CheckAttribute(rChr, "Ship.Cannons.ChargeOverride") || rChr.Ship.Cannons.ChargeOverride != GOOD_BALLS)
                {
                    Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 1, "");
                }
			break;
			case "CIC_LoadGrapes"	:
                if (!CheckAttribute(rChr, "Ship.Cannons.ChargeOverride") || rChr.Ship.Cannons.ChargeOverride != GOOD_GRAPES)
                {
                    Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 2, "");
                }
			break;
			case "CIC_LoadChain"	:
                if (!CheckAttribute(rChr, "Ship.Cannons.ChargeOverride") || rChr.Ship.Cannons.ChargeOverride != GOOD_KNIPPELS)
                {
                    Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 3, "");
                }
			break;
			case "CIC_LoadBombs"	:
                if (!CheckAttribute(rChr, "Ship.Cannons.ChargeOverride") || rChr.Ship.Cannons.ChargeOverride != GOOD_BOMBS)
                {
                    Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 4, "");
                }
			break;
			case "CIC_LoadAtWill"	:
                // A double charge will do the trick.
                Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 1, "");
                Event("BI_LaunchCommand","lsls", cn, "BI_Charge", 1, "");
			break;
			case "CIC_SailAway"		:
				Event("BI_LaunchCommand","lsls", cn, "BI_SailAway", -1, "");
			break;
			case "CIC_LowerSails"	:
				Event("BI_LaunchCommand","lsls", cn, "BI_HeaveToDrift", -1, "");
			break;
			case "CIC_ProtFlagship"	:
				Event("BI_LaunchCommand","lsls", cn, "BI_Defend", GetMainCharacterIndex(), "");
			break;
		}
	}
	CIC_CdreCommand = False;			// Toggle the flag.
}
