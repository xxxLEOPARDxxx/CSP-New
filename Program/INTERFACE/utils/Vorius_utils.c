/* Vorius 09/06/2009
   returns a string representing the given officer's position */
string GetOfficerPosition(string sCharacter)
{
	if (CheckAttribute(pchar,"Fellows.Passengers.navigator") && sCharacter == sti(pchar.Fellows.Passengers.navigator))
		return XI_ConvertString("navigator");
	if (CheckAttribute(pchar,"Fellows.Passengers.boatswain") && sCharacter == sti(pchar.Fellows.Passengers.boatswain))
		return XI_ConvertString("boatswain");
	if (CheckAttribute(pchar,"Fellows.Passengers.cannoner") && sCharacter == sti(pchar.Fellows.Passengers.cannoner))
		return XI_ConvertString("cannoner");
	if (CheckAttribute(pchar,"Fellows.Passengers.doctor") && sCharacter == sti(pchar.Fellows.Passengers.doctor))
		return XI_ConvertString("doctor");
	if (CheckAttribute(pchar,"Fellows.Passengers.treasurer") && sCharacter == sti(pchar.Fellows.Passengers.treasurer))
		return XI_ConvertString("treasurer");
	if (CheckAttribute(pchar,"Fellows.Passengers.carpenter") && sCharacter == sti(pchar.Fellows.Passengers.carpenter))
		return XI_ConvertString("carpenter");

	//#20170318-20
	for(int i=1; i<=MAX_NUM_FIGHTERS; i++)
	{
		if (sti(GetOfficersIndex(pchar, i)) == sti(sCharacter))
			return XI_ConvertString("fighter");
	}

	return XI_ConvertString("passengership");
}
