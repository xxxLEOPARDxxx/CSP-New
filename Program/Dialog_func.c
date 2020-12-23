#include "scripts\utils.c"

// boal -->
#define CARDS_RULE  "������� �������. ������ � '�������� ����'. � ������ 36 ����, �� ����� �� ��������. ��� -11, ������ - 4, ���� - 3, ����� - 2, ��������� ��� ��������. ����� ������� 21 ����. \n ������� �� ����� �����, ����� �������� ���� ����������� (���� �� ������). ��� ���������� ������ �� �������� � �������� � ������ ������� ���� ������. ���� �������, �� ���� �������������. ������ ����� - ��� ���� ������. ������ ���� �����, ���� � ���� ���� ������ ���� �� ��� ���� ������. ������ ���� ���� �� ������, ����� - ������� ��� Esc."
#define DICE_RULE   "������ � '�����-������'. ���� ������� � �������, ������� �� ������� ��� ����. ����� ����������� ����� ����� �������, ������ ������ �� ������, �� ������ ���� ���. ����� �������� ������������ ���������. \n ���������� �� �����������: ���� ���� (2), ��� ���� (2+2), ������ (3), ��� (3+2), ���� (4), ����� (������ ������) � ����� (5). ���� ��������� ������, �� ������� ���, � ���� ������ ����������. \n ����������: ���� �� ������� - ������ �������, ���� �� ������ - �� �������� (������ �� ������ ������ ����), ���� �� �������� - �������� ��� (����� �������� �� �����)."
#define MAX_TITLENEXTRATE   13 // ������� ��� ������
#define MAX_TITLE           5
// boal <--

object Address_Form;

void Set_inDialog_Attributes()
{ 
	ref The_Character_is;

	The_Character_is = GetMainCharacter();
    if (!CheckAttribute(The_Character_is, "sex") || The_Character_is.sex == "man" || The_Character_is.sex == "skeleton")
	{
		Address_Form.Spa = "������";
		Address_Form.Fra = "�����";
		Address_Form.Eng = "���";
		Address_Form.Hol = "������";
		Address_Form.Pir = "���";
    }
    else
    {
		Address_Form.Spa = "���������";
		Address_Form.Fra = "����������";
		Address_Form.Eng = "����";
		Address_Form.Hol = "�������";
		Address_Form.Pir = "����";
	}
	Address_Form.Spa.Title1 = "������";
	Address_Form.Fra.Title1 = "��������";
	Address_Form.Eng.Title1 = "�����";
	Address_Form.Hol.Title1 = "����������";
	Address_Form.Pir.Title1 = "�����";

    Address_Form.Spa.Title2 = "���������";
	Address_Form.Fra.Title2 = "���������";
	Address_Form.Eng.Title2 = "���������";
	Address_Form.Hol.Title2 = "���������";
	Address_Form.Pir.Title2 = "���������";
	
	Address_Form.Spa.Title3 = "�������";
	Address_Form.Fra.Title3 = "�������";
	Address_Form.Eng.Title3 = "�������";
	Address_Form.Hol.Title3 = "�������";
	Address_Form.Pir.Title3 = "�������";

	Address_Form.Spa.Title4 = "��������";
	Address_Form.Fra.Title4 = "��������";
	Address_Form.Eng.Title4 = "��������";
	Address_Form.Hol.Title4 = "��������";
	Address_Form.Pir.Title4 = "��������";

	Address_Form.Spa.Title5 = "�������";
	Address_Form.Fra.Title5 = "�������";
	Address_Form.Eng.Title5 = "�������";
	Address_Form.Hol.Title5 = "�������";
	Address_Form.Pir.Title5 = "�������";

	Address_Form.Spa.woman = "�������";
	Address_Form.Fra.woman = "�����";
	Address_Form.Eng.woman = "������";
	Address_Form.Hol.woman = "�������";
	Address_Form.Pir.woman = "������";

	Address_Form.Spa.man = "������";
	Address_Form.Fra.man = "�����";
	Address_Form.Eng.man = "���";
	Address_Form.Hol.man = "������";
	Address_Form.Pir.man = "���";
	/*switch (The_Character_is.id)
	{	
		case "Blaze":
			
			Address_Form.Spa = GlobalStringConvert("Address_Form_Spa");
			Address_Form.Fra = GlobalStringConvert("Address_Form_Fra");
			Address_Form.Eng = GlobalStringConvert("Address_Form_Eng");
			Address_Form.Por = GlobalStringConvert("Address_Form_Por");
			Address_Form.Hol = GlobalStringConvert("Address_Form_Hol");
			return;
		break;

		case "Beatriss":

			Address_Form.Spa = "Senorita";
			Address_Form.Fra = "Mademoiselle";
			Address_Form.Eng = "Miss";
			Address_Form.Por = "Senhorita";
			Address_Form.Hol = "Juffrouw";
			return;
		break;
	}
	trace("ERROR: Player Character is not defined - can't select address form");
	*/
}

// boal -->

string RandSwear()
{
	switch (rand(14))
	{
		case 0:
			return "�������! ";
		break;

		case 1:
			return "���������! ";
		break;

		case 2:
			return "������! ";
		break;

		case 3:
			return "����! ";
		break;

		case 4:
			return "����� ��� � ... ";
		break;

		case 5:
			return "������ ����! ";
		break;

		case 6:
			return "�����!!! ";
		break;

		case 7:
			return "������ ������! ";
		break;	 
		
		case 8:
			return "���� ������! ";	// ����������� ��������� "���� ����"
		break;
		case 9:
			return "������� ���� ����! ";
		break;

		case 10:
			return "��-�, ���� ������! ";
		break;
		
		case 11:
			return "�, ���� ����... ";
		break;
		
		case 12:
			return "������ ����! ";
		break;
		
		case 13:
			return "����� ���� �������! ";
		break;
		
		case 14:
			return "��� ������ ������! ";
		break;
	}
}

//navy --> ����� ������� �����������,
//�.�. "�, ����!!! � ������ ���� ������" ������ ����� ������ ������� :)
string RandExclamation()
{
	switch(rand(2))
	{
		case 0:
			return "�, ����!! ";
		break;

		case 1:
			return "�, ������! ";
		break;

		case 2:
			return "������ �������! ";
		break;
	}
}
//navy <--
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                ����� ���� ��� �������
////////////////////////////////////////////////////////////////////////////////////////////////////////
// boal 13.03.2004 -->
string RandPhraseSimple(string Var1, string Var2);
{
	int RandP;
	RandP = Rand(1);
	switch(RandP)
	{
		case 0:
			return /*"First phrase selected" + */ Var1;
		break;

		case 1:
			return /*"Second phrase selected" + */Var2;
		break;
	}
	return "ERROR";
}
// ����� ����� �� ����
string LinkRandPhrase (string Var1, string Var2, string Var3)
{
	int RandP;
	RandP = Rand(2);
	switch(RandP)
	{
		case 0:

			return /*"First phrase selected" + */ Var1;

		break;

		case 1:

			return /*"Second phrase selected" + */Var2;

		break;

		case 2:

			return /*"Third phrase selected" + */Var3;

		break;
	}
	return "ERROR";
}

string NationKingsCrown(ref Character)
{
    switch(sti(Character.nation))
	{
		case ENGLAND:
            return "����������� ��������";
		break;
		case FRANCE:
            return "����������� ������";
		break;
		case SPAIN:
            return "��������� ������";
		break;
		case HOLLAND:
			return "����������� ����������";
		break;
		case PIRATE:
			return "���������� ��������";
		break;
	}
}
string NationKingsName(ref NPChar)
{
    switch(sti(NPChar.nation))
	{
		case ENGLAND:
            return "��� ���������� ����� II �������";
		break;
		case FRANCE:
            return "��� ���������� �������� XIV";
		break;
		case SPAIN:
            return "��� ������������� ���������� ����� II ���������";
		break;
		case HOLLAND:
			return "��� ���������� ���������� III ���������";
		break;
		case PIRATE:
			return "���������� ���������� ��������";
		break;
	}
}

string NationNameMan(int pNation)
{
    switch(pNation)
	{
		case ENGLAND:
            return "����������";
		break;
		case FRANCE:
            return "�������";
		break;
		case SPAIN:
            return "�������";
		break;
		case HOLLAND:
			return "���������";
		break;
		case PIRATE:
			return "�����";
		break;
	}
}
// boal 13.03.2004 <--
string NationNamePeople(int pNation)
{
    switch(pNation)
	{
		case ENGLAND:
            return "���������";
		break;
		case FRANCE:
            return "��������";
		break;
		case SPAIN:
            return "�������";
		break;
		case HOLLAND:
			return "���������";
		break;
		case PIRATE:
			return "������";
		break;
	}
}

string NationNamePeopleAcc(int pNation)
{
    switch(pNation)
	{
		case ENGLAND:
            return "�����������";
		break;
		case FRANCE:
            return "����������";
		break;
		case SPAIN:
            return "���������";
		break;
		case HOLLAND:
			return "�����������";
		break;
		case PIRATE:
			return "��������";
		break;
	}
}

string NationNameAblative(int iNation) //������������ �����
{
    switch(iNation)
	{
		case ENGLAND:
            return "�������";
		break;
		case FRANCE:
            return "��������";
		break;
		case SPAIN:
            return "��������";
		break;
		case HOLLAND:
			return "����������";
		break;
		case PIRATE:
			return "��������";
		break;
	}
}

string NationNameNominative(int iNation) //������������ �����
{
    switch(iNation)
	{
		case ENGLAND:
            return "������";
		break;
		case FRANCE:
            return "�������";
		break;
		case SPAIN:
            return "�������";
		break;
		case HOLLAND:
			return "���������";
		break;
		case PIRATE:
			return "��������� ��������";
		break;
	}
}

string NationNameGenitive(int iNation) // ����������� �����
{
    switch(iNation)
	{
		case ENGLAND:
            return "������";
		break;
		case FRANCE:
            return "�������";
		break;
		case SPAIN:
            return "�������";
		break;
		case HOLLAND:
			return "���������";
		break;
		case PIRATE:
			return "�������";
		break;
	}
}

///////����� ����� �������������� ������� ������ ����
string NationEuropaTown(int iNation)
{
    switch(iNation)
	{
		case ENGLAND:
            return "������";
		break;
		case FRANCE:
            return "�� ������";
		break;
		case SPAIN:
            return "�������";
		break;
        case PIRATE:
	    	return "�������";
		break;
		case HOLLAND:
	    	return "���������";
		break;
	}
}
string GetCityName(string city) // ����� ������� �� ��������� char.city
{
    string ret;
    int nFile = LanguageOpenFile("LocLables.txt");
    
	ret = LanguageConvertString(nFile, city + " Town")
	LanguageCloseFile( nFile );
	
	return  ret;
}

string GetPortByCityName(string city) // ����� ������ �� ������� �� ��������� char.city
{
    switch(city)
	{
		case "Bridgetown":
            return "Bridgetown_town";
		break;
		case "SanJuan":
            return "SanJuan_town";
		break;
		case "Santiago":
            return "Santiago_town";
		break;
		case "PuertoPrincipe":
            return "PuertoPrincipe_port";
		break;
		case "SentJons":
            return "SentJons_town";
		break;
		case "PortRoyal":
            return "PortRoyal_town";
		break;
		case "FortOrange":
            return "Shore35";
		break;
		case "Villemstad":
            return "Villemstad_town";
		break;
		case "BasTer":
            return "BasTer_town";
		break;
		case "LaVega":
            return "LaVega_port";
		break;
		case "Bridgetown":
            return "Bridgetown_town";
		break;
		case "SantoDomingo":
            return "SantoDomingo_town";
		break;
		case "PortPax":
            return "PortPax_town";
		break;
		case "Pirates":
            return "Pirates_town";
        break;
		case "FortFrance":
            return "FortFrance_town";
		break;
		case "LeFransua":
            return "LeFransua_port";
		break;
		case "Havana":
            return "Havana_town";
		break;
		case "Charles":
            return "Charles_town";
		break;
		case "PortoBello":
            return "PortoBello_town";
		break;
		case "PortSpein":
            return "PortSpein_town";
		break;
		case "Tortuga":
            return "Tortuga_town";
		break;
		case "Marigo":
            return "Marigo_town";
		break;
		case "Panama":
            return "Panama_town";
		break;
		case "Cartahena":
            return "Cartahena_town";
		break;
		case "Maracaibo":
            return "Maracaibo_town";
		break;
		case "Caracas":
            return "Caracas_town";
		break;
		case "Cumana":
            return "Cumana_town";
		break;
		case "SantaCatalina":
            return "SantaCatalina_town";
		break;
		case "Beliz":
            return "Beliz_town";
		break;
	}
	return "";
}

string GetMayakByCityName(string city) // �������� id ����� �� �������� ������
{
    switch(city)
	{
		case "Bridgetown":
			return "Mayak2";
		break;
		case "Santiago":
			return "Mayak9";
		break;
		case "PortRoyal":
            return "Mayak3";
		break;		
		case "BasTer":
            return "Mayak4";
		break;				
		case "SantoDomingo":
            return "Mayak8";
		break;				
		case "PortPax":
            return "Mayak7";
		break;		
		case "Havana":
            return "Mayak10";
		break;								
		case "Charles":
            return "Mayak5";
		break;				
		case "PortSpein":
            return "Mayak1";
		break;				
		case "Tortuga":
            return "Mayak6";
		break;		
		case "Cartahena":
            return "Mayak11";
		break;		
	}
	return "";
}

string GetCityNameByMayak(string mayak) // �������� id ������ �� �����
{
    switch(mayak)
	{
		case "Mayak1":
            return "PortSpein";
		break;				
		case "Mayak2":
			return "Bridgetown";
		break;
		case "Mayak3":
            return "PortRoyal";
		break;				
		case "Mayak4":
            return "BasTer";
		break;		
		case "Mayak5":
            return "Charles";
		break;	
		case "Mayak6":
            return "Tortuga";
		break;				
		case "Mayak7":
            return "PortPax";
		break;				
		case "Mayak8":
            return "SantoDomingo";
		break;						
		case "Mayak9":
			return "Santiago";
		break;						
		case "Mayak10":
            return "Havana";
		break;
		case "Mayak11":
            return "Cartahena";
		break;			
	}
	return "";
}

string GetIslandByArealName(string areal)
{
	string sAreal = areal;
	if(areal == "PortoBello" || areal == "Panama" || areal == "Cartahena" || 
		areal == "Maracaibo" || areal == "Caracas" || areal == "Cumana" || areal == "SantaCatalina" || 
		areal == "Beliz" || areal == "Tenotchitlan")
	{
		sAreal = "Mein";
	}
	return sAreal;
}

string GetIslandByCityName(string city) // ����� ������� �� ������ �� ��������� char.city
{
    switch(city)
	{
		case "Bridgetown":
            return "Barbados";
		break;
		case "SanJuan":
            return "PuertoRico";
		break;
		case "Santiago":
            return "Cuba";
		break;
		case "PuertoPrincipe":
            return "Cuba";
		break;
		case "SentJons":
            return "Antigua";
		break;
		case "PortRoyal":
            return "Jamaica";
		break;
		case "FortOrange":
            return "Jamaica";
		break;
		case "Villemstad":
            return "Curacao";
		break;
		case "BasTer":
            return "Guadeloupe";
		break;
		case "LaVega":
            return "Hispaniola";
		break;
		case "SantoDomingo":
            return "Hispaniola";
		break;
		case "PortPax":
            return "Hispaniola";
		break;
		case "Pirates":
            return "Bermudes";
        break;
		case "FortFrance":
            return "Martinique";
		break;
		case "LeFransua":
            return "Martinique";
		break;
		case "Havana":
            return "Cuba";
		break;
		case "Charles":
            return "Nevis";
		break;
		case "PortoBello":
            return "Mein";
		break;
		case "PortSpein":
            return "Trinidad";
		break;
		case "Tortuga":
            return "Tortuga";
		break;
		case "Marigo":
            return "SentMartin";
		break;
		case "Panama":
            return "Mein";
		break;
		case "Cartahena":
            return "Mein";
		break;
		case "Maracaibo":
            return "Mein";
		break;
		case "Caracas":
            return "Mein";
		break;
		case "Cumana":
            return "Mein";
		break;
		case "SantaCatalina":
            return "Mein";
		break;
		case "Beliz":
            return "Mein";
		break;
		case "Tenotchitlan":
            return "Mein";
		break;
	}
	return "";
}

string GetArealByCityName(string city) // ����� �� ������ �� ��������� char.city
{
    switch(city)
	{
		case "Bridgetown":
            return "Barbados";
		break;
		case "SanJuan":
            return "PuertoRico";
		break;
		case "Santiago":
            return "Cuba1";
		break;
		case "PuertoPrincipe":
            return "Cuba1";
		break;
		case "SentJons":
            return "Antigua";
		break;
		case "PortRoyal":
            return "Jamaica";
		break;
		case "FortOrange":
            return "Jamaica";
		break;
		case "Villemstad":
            return "Curacao";
		break;
		case "BasTer":
            return "Guadeloupe";
		break;
		case "LaVega":
            return "Hispaniola1";
		break;
		case "SantoDomingo":
            return "Hispaniola1";
		break;
		case "PortPax":
            return "Hispaniola2";
		break;
		case "Pirates":
            return "Bermudes";
        break;
		case "FortFrance":
            return "Martinique";
		break;
		case "LeFransua":
            return "Martinique";
		break;
		case "Havana":
            return "Cuba2";
		break;
		case "Charles":
            return "Nevis";
		break;
		case "PortoBello":
            return "PortoBello";
		break;
		case "PortSpein":
            return "Trinidad";
		break;
		case "Tortuga":
            return "Tortuga";
		break;
		case "Marigo":
            return "SentMartin";
		break;
		case "Panama":
            return "Panama";
		break;
		case "Cartahena":
            return "Cartahena";
		break;
		case "Maracaibo":
            return "Maracaibo";
		break;
		case "Caracas":
            return "Caracas";
		break;
		case "Cumana":
            return "Cumana";
		break;
		case "SantaCatalina":
            return "SantaCatalina";
		break;
		case "Beliz":
            return "Beliz";
		break;
		case "Tenotchitlan":
            return "Tenotchitlan";
		break;
	}
	return "";
}

string GiveArealByLocation(ref location)
{
	string sAreal;
	if (CheckAttribute(location, "MustSetReloadBack")) return "none";
	if (CheckAttribute(location, "fastreload")) 
	{
		sAreal = GetArealByCityName(location.fastreload); 
		return sAreal;
	}
	if (CheckAttribute(location, "parent_colony")) 
	{
		sAreal = GetArealByCityName(location.parent_colony); 
		return sAreal;
	}
	if (!CheckAttribute(location, "islandId")) return "none";
	if (location.islandId == "Cuba" || location.islandId == "Hispaniola" || location.islandId == "Mein") 
	{			
		if (!CheckAttribute(location, "islandIdAreal")) return "none";
		sAreal = location.islandIdAreal;
	}
	else sAreal = location.islandId;
	return sAreal;
}

// ����� ���� ����  �� ������� ���� ����� (������� ����� ������� � ������)
string GetCityNameByIsland(string CurIslandId)
{
	string TargetLocation;

	TargetLocation = "None";

	switch (CurIslandId)
	{
    	case "Antigua":
			TargetLocation = "SentJons";
		break;
		case "Bermudes":
			TargetLocation = "Pirates";
		break;
		case "Barbados":
			TargetLocation = "Bridgetown";
		break;
		case "Beliz":
			TargetLocation = "Beliz";
		break;
		case "Cuba1":
			TargetLocation = "Santiago";
		break;
		case "Cuba2":
			TargetLocation = "Havana";
		break;
		case "Cumana":
			TargetLocation = "Cumana";
		break;
		case "Caracas":
			TargetLocation = "Caracas";
		break;
		case "Curacao":
			TargetLocation = "Villemstad";
		break;
		case "Cartahena":
			TargetLocation = "Cartahena";
		break;
		case "Guadeloupe":
			TargetLocation = "BasTer";
		break;
		case "Hispaniola1":
			TargetLocation = "SantoDomingo";
		break;
		case "Hispaniola2":
			TargetLocation = "PortPax";
		break;
		case "Jamaica":
			TargetLocation = "PortRoyal";
		break;
		case "Maracaibo":
			TargetLocation = "Maracaibo";
		break;
		case "Martinique":
			TargetLocation = "FortFrance";
		break;
		case "SentMartin":
			TargetLocation = "Marigo";
		break;
		case "Nevis":
			TargetLocation = "Charles";
		break;
		case "PuertoRico":
			TargetLocation = "SanJuan";
		break;
		case "PortoBello":
			TargetLocation = "PortoBello";
		break;
		case "Pearl":
			TargetLocation = "none";
		break;
		case "Panama":
			TargetLocation = "Panama";
		break;
		case "SantaCatalina":
			TargetLocation = "SantaCatalina";
		break;
		case "Terks":
			TargetLocation = "none";
		break;
		case "Dominica":
			TargetLocation = "none";
		break;
		case "Caiman":
			TargetLocation = "none";
		break;
		case "Tortuga":
			TargetLocation = "Tortuga";
		break;
		case "Trinidad":
			TargetLocation = "PortSpein";
		break;
		case "Tenotchitlan":
			TargetLocation = "none";
		break;
	}
    return TargetLocation;
} 

string TimeGreeting()
{
    if (GetHour() >= 18 && GetHour() < 23)
    {
       return "������ �����";
    }
    if (GetHour() >= 6 && GetHour() < 12)
    {
       return "������ ����";
    }
    if (GetHour() >= 12 && GetHour() < 18)
    {
       return "������ ����";
    }
    if (GetHour() >= 23 || GetHour() < 6)
    {
       return "������ ����";
    }
    return "�������";
}

// ����� ����� �� ���������
string PCharRepPhrase (string bad, string good)
{
	return NPCharRepPhrase(pchar, bad, good);
}
// boal ��� ���
string NPCharRepPhrase(ref _pchar, string bad, string good)
{
	if(makeint(_pchar.reputation) < 41)
	{
		return bad;
	}
	else
	{
		return good;
	}
}

////////// ����� ������� ����� ��� �������
string GetCharIDByParam(string attrPresent1, string attr2, string val2)
{
    ref rCharacter; //����
	int n = GetCharIDXByParam(attrPresent1, attr2, val2);

    if (n > 0)
    {
        makeref(rCharacter,Characters[n]);
        return  rCharacter.id;
    }
    return  "";
}
int GetCharIDXByParam(string attrPresent1, string attr2, string val2)
{
    ref rCharacter; //����
	int n;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, attrPresent1))
		{
            if (rCharacter.(attr2) == val2)
                return  n;
		}
    }
    return  -1;
}
int GetCharIDXForTownAttack(string attrPresent1)
{
    ref   rColony; //����
	int   n;
	bool  ok;

	for (n=0; n<MAX_COLONIES; n++)
	{
		makeref(rColony, colonies[n]);
		ok = false;
		if (CheckAttribute(rColony, "Default.BoardLocation2") && rColony.Default.BoardLocation2 == attrPresent1)
		{
		    ok = true;
		}
		if (rColony.Default.BoardLocation == attrPresent1 || ok)
        {
			if (rColony.HeroOwn == true)
			{
			    return  -1;
			}
			
			return GetFortCommanderIdx(rColony.id);
		}
    }
    return  -1;
}
// ��������� ��� � ��, ������� �� ����� ���
string GetAddress_Form(ref NPChar)
{
    string attr = NationShortName(sti(NPChar.nation));
    return address_form.(attr);
}
// ��������� �� � ���, ������� �� ����� ��� � ��� ����
string GetAddress_FormToNPC(ref NPChar)
{
    string attr  = NationShortName(sti(NPChar.nation));
    string attr2 = NPChar.sex;
    // �������� �� ��������
    if (attr2 != "woman")
    {
        attr2 = "man";
    }
    return address_form.(attr).(attr2);
}
string GetAddress_FormTitle(int nation, int num)
{
    string attr  =  NationShortName(nation);
    string attr2 =  "Title" + num;
    string ret   =  "��� ������";
    if (CheckAttribute(address_form, attr + "." + attr2))
    {
        ret = address_form.(attr).(attr2);
    }
    return ret;
}

bool isCityHasFort(string _city)
{
    int iTest = FindColony(_city); // �����
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		if (!CheckAttribute(rColony, "HasNoFort")) return true;
	}
	return false;
}

string GetCityFrom_Sea(string _city)
{
    int iTest = FindColony(_city); // �����
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		return rColony.from_sea;
	}
	return "";
}
// boal <--

// eddy. ��� �� ��������� (������ ��� ������� ��������, �� ��������). sPrefix - ��������� ��� �������: Gen, Dat..
string GetWorkTypeOfMan(ref NPChar, string sPrefix)
{
	string sCity, sTemp;
	sTemp = "unknown";
	if (CheckAttribute(NPChar, "City")) 
	{
		sCity = NPChar.City;
		sTemp = NPChar.id;
		sTemp = strcut(sTemp, strlen(sCity)+1, strlen(sTemp)-1);
	}
	return XI_ConvertString("Who" + sTemp + sPrefix);
}
// Warship 07.08.09 -->
// ���������� ���� � ������
int GetNamesCount(String _nameType)
{
	aref typeNames;
	makearef(typeNames, Names.Pirates.(_nameType));
	
	return GetAttributesNum(typeNames);
}

// ��������� ��� �� ������������ ������ � ������������ ������
String GetRandName(String _nameType, String _case)
{
	String nameId;
	
	nameId = "l" + rand(GetNamesCount(_nameType) - 1);
	
	return GetName(_nameType, nameId, _case);
}

// ������ ��� �� ������ � �������� Id � � ��������� ������
String GetName(String _nameType, String _nameId, String _nameCase)
{
	return Names.Pirates.(_nameType).(_nameId).(_nameCase);
}

// ������ ��������� ��� � ������ ������, ����� �� ������ ������ _nameType
String ChangeNameCaseEx(String _nameType, String _name, String _fromCase, String _toCase)
{
	aref typeNames;
	String nameId;
	
	makearef(typeNames, Names.Pirates.(_nameType));
	
	for(int i = 0; i < GetAttributesNum(typeNames); i++)
	{
		nameId = "l" + i;
		
		if(GetName(_nameType, nameId, _fromCase) == _name)
		{
			return GetName(_nameType, nameId, _toCase);
		}
	}
	
	return "";
}

// ���� �����, ��� � ����, ������ ������ ���������� - ���� ����
String ChangeNameCase(String _nameType, String _name, String _toCase)
{
	aref typeNames;
	String nameId;
	
	makearef(typeNames, Names.Pirates.(_nameType));
	
	for(int i = 0; i < GetAttributesNum(typeNames); i++)
	{
		nameId = "l" + i;
		
		if(GetName(_nameType, nameId, NAME_NOM) == _name || GetName(_nameType, nameId, NAME_GEN) || GetName(_nameType, nameId, NAME_DAT) ||
			GetName(_nameType, nameId, NAME_ACC) == _name || GetName(_nameType, nameId, NAME_ABL) || GetName(_nameType, nameId, NAME_VOC))
		{
			return GetName(_nameType, nameId, _toCase);
		}
	}
	
	return "";
}
// <-- Warship 07.08.09