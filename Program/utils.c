#define PARSE_STRING	"PARSE_STRING"

#event_handler(PARSE_STRING, "ParseString");

int AddStr2Array(ref rNames, int iNum, string sStr)
{
	SetArraySize(rNames, iNum + 1);
	rNames[iNum] = sStr;
	iNum++;
	return iNum;
}
// boal 101004 -->
string GetSubStringByNum(string sStr, int iSelect)
{
	string sTemp;
	int iFindPos = findSubStr(&sStr, ",", 0);
	if (iFindPos < 0) return sStr;	// one word in string
	int iNumFind = 1;
    while (iFindPos > 0)
	{
		iNumFind++;
		iFindPos = findSubStr(&sStr, ",", iFindPos + 1);
	}
	if (iNumFind <= iSelect)
	{
        return GetSubStringByNum(sStr, 0);
	}
	int	iLastPos = 0;
	iFindPos = 0;
	for (int i=0; i<iNumFind; i++)
	{
		iFindPos = findSubStr(&sStr, ",", iFindPos + 1);
		if (i == iSelect)
		{
			if (iFindPos < 0)
            {
                iFindPos = strlen(&sStr);
            }
            if (iLastPos >=  iFindPos) iFindPos = iLastPos + 2;
			sTemp = strcut(&sStr, iLastPos, iFindPos - 1);
			return sTemp;
		}
		iLastPos = iFindPos + 1;
	}

	return GetSubStringByNum(sStr, 0);
}
// boal <--
string GetRandSubString(string strInput)
{
	string sTemp;
    string sStr = strInput;

    if (strlen(sStr) > 0)//fix
    {
    	//int iFindPos = findSubStr(&sStr, ",", 0);
    	int iFindPos = findSubStr(sStr, ",", 0);
    	if (iFindPos < 0) return sStr;	// one word in string
    	int iNumFind = 1;
    	while (iFindPos > 0)
    	{
    		iNumFind++;
    		//iFindPos = findSubStr(&sStr, ",", iFindPos + 1);
    		iFindPos = findSubStr(sStr, ",", iFindPos + 1);
    	}
    	int iSelect = rand(iNumFind - 1);
    	int	iLastPos = 0;
    	iFindPos = 0; // ��� ��� ������ ��������!!!!! ������ � ���� ���� :) Boal
    	for (int i=0; i<iNumFind; i++)
    	{
    		//iFindPos = findSubStr(&sStr, ",", iFindPos + 1);
    		iFindPos = findSubStr(sStr, ",", iFindPos + 1);
    		if (i == iSelect)
    		{
    			if (iFindPos == -1)
                {
                    //iFindPos = strlen(&sStr);
                    iFindPos = strlen(sStr);
                }
                // ����������!!!
                 if (iLastPos >=  iFindPos) return "";
    			//sTemp = strcut(&sStr, iLastPos, iFindPos - 1);
    			sTemp = strcut(sStr, iLastPos, iFindPos - 1);
    			return sTemp;
    		}
    		iLastPos = iFindPos + 1;
    	}
    	return "ERROR: bad string return";
	}
	return   "";
}

// Warship 06.08.09 ������ �� -999 �� 999 ��������
String GetRussianNumberString(int _num)
{
	if(_num < -999 || _num > 999) return "Error";
	if(_num == 0) return XI_ConvertString("zero");
	
	String numString = its(abs(_num));
	
	int strLength = strlen(numString);
	
	String ones = GetSymbol(numString, strLength - 1);
	String tens = GetSymbol(numString, strLength - 2) + "0";
	String hundreds = GetSymbol(numString, strLength - 3) + "00";
	
	numString = "";
	
	if(_num < 0)
	{
		numString = XI_ConvertString("minus") + " ";
	}
	
	if(tens == "10")
	{
		tens = "";
		ones = "1" + ones;
	}
	
	ones = XI_ConvertString(ones);
	
	if(tens != "")
	{
		tens = XI_ConvertString(tens) + " ";
	}
	
	if(hundreds != "")
	{
		hundreds = XI_ConvertString(hundreds) + " ";
	}
	
	return numString + hundreds + tens + ones;
}
float GetDotProduct(float fA1, float fA2)
{
    return cos(fA2 - fA1);  // boal �������� ����������� ����
}

void ParseString()
{
	int		i, iLen;
	string	sParams[2];
	string	sDst = "";

	aref aRes = GetEventData();
	string rSourceString = GetEventData();
	int	iNumParameters = GetEventData();

	//Trace("parser started: " + rSourceString + ", params = " + iNumParameters);

	if (iNumParameters == 0)
	{
		aRes.Str = rSourceString;
		return;
	}

	SetArraySize(&sParams, iNumParameters + 1);
	for (i=0; i<iNumParameters; i++) { sParams[i] = GetEventData();	}

	iLen = strlen(&rSourceString);
	for (i=0; i<iLen; i++)
	{
		string sChar = GetSymbol(&rSourceString, i);
		if (sChar == "%")
		{
			if (GetSymbol(&rSourceString, i + 1) == "%")
			{
				sDst = sDst + "%";
				i++;
				continue;
			}
			// get parameter number
			string sNumber = "";
			i++;
			while (i < iLen)
			{
				string sTmp = GetSymbol(&rSourceString, i);
				if (!isDigit(&sTmp, 0)) { break; }
				sNumber = sNumber + sTmp;
				i++;
			}
			sDst = sDst + sParams[sti(sNumber) - 1]; i--;
			continue;
		}
		sDst = sDst + sChar;
	}

	aRes.Str = sDst;
}

float GetDistance2D(float x1, float y1, float x2, float y2)
{
	return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}

// Warship 21.07.09 ���������� � 3D
float GetDistance3D(float _x1, float _y1, float _z1, float _x2, float _y2, float _z2)
{
	return sqrt(sqr(_x1 - _x2) + sqr(_y1 - _y2) + sqr(_z1 - _z2));
}

//#20180524-01 Remove unneeded sqrt
float GetDistance2DRel(float x1, float y1, float x2, float y2)
{
	return sqr(x1 - x2) + sqr(y1 - y2);
}

void RotateAroundY(ref rX, ref rZ, float fCos, float fSin)
{
	float xxx = rX;
	float zzz = rZ;
	float xx = xxx * fCos + zzz * fSin;
	float zz = zzz * fCos - xxx * fSin;
	rX = xx;
	rZ = zz;
}

int Tonnes2CWT(int iTonnes)
{
	int a = iTonnes * 10000 / 508;
	a = 100 * ((a + 99) / 100);
	return a;
}

int i_min(int a1, int a2)
{
	if (a1 < a2) { return a1; }
	return a2;
}

string GetVerNum()
{
 	string  VERSION_STR = VERSION_NUMBER2;

    if (MOD_BETTATESTMODE == "On")
    {
       VERSION_STR = VERSION_STR + "  DEV";
    }
    if (MOD_BETTATESTMODE == "Test")
    {
       VERSION_STR = VERSION_STR + "  TST";
    }
    return VERSION_STR;
}

void Log_Info(string _str)
{
    Log_SetStringToLog(_str);
}

void Log_TestInfo(string logtext)
{
	if (bBettaTestMode)
	{
		Log_SetStringToLog(logtext);
		trace("TestInfo: " + GetQuestBookDataDigit() + " " + logtext)
	}
}
void Log_QuestInfo(string _info)
{
    if (bQuestLogShow)
	{
		Log_SetStringToLog(_info);
	}
}

string NewStr()
{
    int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
    string sTemp;
    sTemp = LanguageConvertString(idLngFile,"new_string");
    LanguageCloseFile(idLngFile);

    return sTemp;
}

Object objGrass;

void CreateGrass(string sDataFile, string sTextureFile, float fScale, float fW,float fH, float fMinDist,float fMaxDist, float fMinLod)
{
	CreateEntity(&objGrass,"Grass");
	if( bSeaActive && !bAbordageStarted )
	{
		LayerAddObject(SEA_EXECUTE,&objGrass,1000);
		LayerAddObject(SEA_REALIZE,&objGrass,1000);
	}
	else
	{
		LayerAddObject("execute",&objGrass,1000);
		LayerAddObject("realize",&objGrass,1000);
	}
	SendMessage(objGrass,"ls",41666, sTextureFile); // #define MSG_GRASS_SET_TEXTURE 41666
	SendMessage(objGrass,"lffffff",42666, fScale, fW,fH, fMinDist,fMaxDist, fMinLod); // #define MSG_GRASS_SET_PARAM 42666
	SendMessage(objGrass,"ls",40666, sDataFile); // #define MSG_GRASS_LOAD_DATA 40666
}

void DeleteGrass()
{
	if (IsEntity(&objGrass))
	{
		DeleteClass(&objGrass); // boal �������� ���������� ������
	}
	DeleteEntitiesByType("Grass");
}

void HideGrass()
{
	if (IsEntity(&objGrass))
	{
        LayerDelObject("execute", &objGrass);
		LayerDelObject("realize", &objGrass);
		LayerDelObject(SEA_EXECUTE, &objGrass);
		LayerDelObject(SEA_REALIZE, &objGrass);
	}
}

void ShowGrass()
{
	if (IsEntity(&objGrass))
	{
        LayerAddObject(SEA_EXECUTE, &objGrass, 1000);
		LayerAddObject(SEA_REALIZE, &objGrass, 1000);
	}
}
// boal 16.03.2004 -->
void CalcLocalTime(float _inc)
{
	if (locTmpTime >= _inc)
	{
		/*int hour = GetHour();
		if (AddTimeToCurrent(0, makeint(locTmpTime / _inc)) > 0)
		{
			//����� ��� ������ ������ ������� PostEvent("NextDay", 20); // �������� ����� ����
		}        */
        locTmpTime = 0.0;
        /*if (hour != GetHour() && !bStorm && !bTornado && !bDisableMapEnter && !LAi_grp_alarmactive) // �� � ���
		{
            RefreshWeather();
		} */
    }
}
void RefreshWeather()
{
    Whr_UpdateWeather();
	// �����
	/*
	if (bSeaActive && !bAbordageStarted)
	{
	    SetSchemeForSea();
	    if (Whr_IsDay() && sti(pchar.Ship.Lights) == 1)
	    {
	        //��������� ������.
	        Ship_SetLightsOff(pchar, 15.0, true, true, false);
	    }
	}
	else
	{ // ����
	    LoadSceneSound();
	} */
}
void RefreshLandTime()
{
    objLandInterface.textinfo.datatext.text = XI_convertString("Date:") + GetQuestBookData();
}
// boal 16.03.2004 <--
string stripblank(string str)
{
	string retstr = "";
	int iMax = strlen(str);
	for(int i = 0; i < iMax; i++) {
		if(GetSymbol(str,i) != " ") { retstr += GetSymbol(str,i); }}
	return retstr;
}
// boal <--

void ResetTimeScale()
{
    SetTimeScale(1.0);
	TimeScaleCounter = 0;
	if(IsPerkIntoList("TimeSpeed"))
	{	DelPerkFromActiveList("TimeSpeed");
	}
}

void FreeChangeFlagMode(string _tmp)
{
	DeleteAttribute(pchar, "DisableChangeFlagMode");
}

string  xiStr(string _str) // ������ ����������
{
	return XI_ConvertString(_str);
}

string  xiDStr(string _str) // ������ ����������
{
	return GetConvertStr(_str, "DialogSource.txt");
}

void Dev_Trace(string _str) // ���� ������ � ��� ������
{
    if (MOD_BETTATESTMODE	==	"On")	Trace(_str);
}

// Warship -->
String FindStringAfterChar(string _string, string _char)
{
	int i = FindSubStr(_string, _char , 0);
	if(i == -1) return "";
	string sRetStr = strcut(_string, i+1, strlen(_string)-1);
	return sRetStr;
}

String FindStringBeforeChar(string _string, string _char) // ����� ������ ����� ��������
{
	int i = FindSubStr(_string, _char , 0);
	if(i == -1) return "";
	string sRetStr = strcut(_string, 0, i-1);
	return sRetStr;
}

float retMin(float x, float y)																											   
{
	x = makefloat(x); y = makefloat(y);
	if(x<y) return x;
	return y;
}

float retMax(float x, float y)
{
	if(x>y) return makefloat(x);
	return makefloat(y);
}

int iretMin(int x, int y)
{
	if(x<y) return x;
	return y;
}

int iretMax(int x, int y)
{
	if(x>y) return x;
	return y;
}
// ������ ����������
void Log_AStr(string _str) // ���������� ������. � ������ ������ �� ��������
{
	Log_SetEternalString(_str);
}

void Log_TestAStr(string _str)
{
	if (bBettaTestMode)
	{
		Log_AStr(_str);
		trace("TestInfo: " + GetQuestBookDataDigit() + " " + _str)
	}
}

void Log_Clear()
{
	ClearAllLogStrings();  
}
// ������ � 10 ��������. ����������
// ������ ��� � �� ����� ����, ��� ���� ��������� ��� ����� ����
string TenSpaceStr()
{
	string sTemp = XI_ConvertString("TenSpace");
	return sTemp;
}
// <--

int round(float num)
{
	return makeint(num + 0.5);
}

void TraceAndLog(string ltext) //to log _and_ trace info
{
	Log_SetStringToLog(ltext);
	trace(ltext);
}

float pow2(float num, float exp) // supports exponents of less than one via sqrt and a loop.
{
	if(exp == 1.0) return num; // NK 05-03-30 add this check
	if(exp > 1.0) return pow(num, exp);
	int sqrtx = 0;
	while(exp < 1.0)
	{
		exp *= 2;
		sqrtx++;
	}
	num = pow(num, exp);
	for(int i = 0; i < sqrtx; i++)
	{
		num = sqrt(num);
	}
	return num;
}

int GetCurrentModelrNumber()
{
	int n = 0;
	aref arModel;
	if (FindClass(&arModel, "modelr")) 
	{
		n++;
		while (FindClassNext(&arModel)) 
		{
			n++;
		}
	}
	trace("GetCurrentModelrNumber   n : " + n);
	return n;
}


bool HasSubStr(string basestr, string findstr)
{
	return findSubStr(basestr, findstr, 0) != -1;
}

// KK -->
string strreplace(string strSource, string from, string into)
{
	int pos = findSubStr(strSource, from, 0);
	if (pos < 0) return strSource;
	if (HasSubStr(into, from)) return strSource;
	string ret = "";
	if (pos > 0) ret = strcut(strSource, 0, pos - 1);
	ret += into;
	if (pos + strlen(from) <= strlen(strSource) - 1) ret += strcut(strSource, pos + strlen(from), strlen(strSource) - 1);
	return strreplace(ret, from, into);
}
// <-- KK

