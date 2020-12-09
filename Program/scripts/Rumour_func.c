string ttttstr;

//////////////////////////////////////////////////////////////////////////////////////////////////////
int DateToInt(int plus)// ������� �������� ���� � ���������� ����
                                    // ���� ������� 0 - ������� ������� ����
{

      int  yy = sti(Environment.date.year);
      int  mm = sti(Environment.date.month);
      int  dd = sti(Environment.date.day);

    return (yy * 365 + mm * 30 + dd + plus);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
void SelectAction(ref rid) //CASE � ���������� ��� ������
{
	ref CurrentRumour;
	int pos, sid;
	string other,sled,att;
	pos = FindRumour(rid.id);
	makeref(CurrentRumour, Rumour[pos]);
	switch(CurrentRumour.event) // ���� ���� � ���������, �� ���������:
	{
		case "GoldFleet":
		{
			//////////////////////////////////////////
			EndTime_GoldFleet(rid.id);
			///////////////////////////////////////////
		}
		break;

		case "GoldFleetMonth":
		{
			//////////////////////////////////////////
			if (CurrentRumour.actualtime >= DateToInt(0))
			{
				ReOpenQuestHeader("Rumour_GoldFleet");
				AddQuestRecord("Rumour_GoldFleet", 10+rand(2));
				AddQuestUserData("Rumour_GoldFleet", "smonth", GoldMonth);
				CurrentRumour.event = "none";
			}
			///////////////////////////////////////////
		}
		break;

		case "MerchantOnMap":
		{
			//////////////////////////////////////////
			rid.text = GenerateMerchant();
			///////////////////////////////////////////
		}
		break;
		
		case "OnMerchantDie":
		{
			//////////////////////////////////////////
			rid.text = AfteMerchantRumour();
			///////////////////////////////////////////
		}
		break;
		
		case "GetPrices":
		{
			//////////////////////////////////////////
			string HomeColony = All_GetColony();
            int iNation = sti(Colonies[FindColony(HomeColony)].nation);
			int icnum = FindNonEnemyColonyForAdventure(iNation, HomeColony, false);
			if (icnum != -1)
			{
                ref rcolony = &Colonies[icnum];
			    SetPriceListByStoreMan(rcolony);
                PlayStereoSound("notebook");
			    object otmp;
			    ref rtmp;
                rtmp = &otmp;
        	    rtmp.colony = GetConvertStr(rcolony.id+" Town", "LocLables.txt");
                rid.text = GetAssembledString( rid.text, rtmp);
            }
            else rid.text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // ���� ������				           
            
			///////////////////////////////////////////
		}
		break;
//============ ����� ===============
		case "OnSiege_1":
		//////////////////////////////////////////
		rid.text = SiegeRumourText(1);
		///////////////////////////////////////////
		break;
		
		case "OnSiege_2":
		//////////////////////////////////////////
		rid.text = SiegeRumourText(2);
		///////////////////////////////////////////
		break;
		
		case "OnSiege_3":
		//////////////////////////////////////////
		rid.text = SiegeRumourText(3);
		///////////////////////////////////////////
		break;
		
		
//============ ����� ===============
		case "DuelHero":
			rid.text = Event_DuelHero(rid);
			break;

//============= ��� ===============
		case "PGG_WorkWithContra":
			rid.text = PGG_Event_WorkWithContra(rid);
			break;
		//����� ���������� �����
		case "PortmansBook_DeliveryToCap":
			PortmansBook_writeQuestBook(rid);
		break;
		//����� ����� ���������� �������
		case "Portmans_SeekShip_rum":
			PortmansSeekShip_writeQuestBook(rid);
		break;
		//����� �� ������ ����� �� �������
		case "Citiz_SeekCap_rum":
			CitizSeekCap_writeQuestBook(rid);
		break;
		//������� ���, ��������� � ������ ����� �������� �� ������
		case "LSC_HillBrunnerDead":
			if (pchar.questTemp.LSC == "barmenIsDead")
			{
				pchar.questTemp.LSC = "barmenIsDeadYouKnow";
			}
		break;
		//������� ���, ���������� ���� ���� ������
		case "LSC_rumourElisHusband":
			LSC_rumourElisHusband();
		break;
		//������� ���, ����� � ������� ��������
		case "LSC_rumourLostDecster":
			LSC_rumourLostDecster();
		break;
		case "LSC_rumourAdmiralLostKey":
			LSC_rumourAdmiralLostKey();
		break;
		
		case "CaptainComission_rumourCapDeath":
			CaptainComission_RumourCaptainDeath();
		break;
		
		case "CaptainComission_rumourCapPrison":
			CaptainComission_RumourCaptainPrison();
		break;
	}

	if (CurrentRumour.next != "none" ) // ���� ���� � ������������
	{
		//////////////////////////////////////////
		sled = CurrentRumour.next;
		sid = sti(CurrentRumour.id);
		DeleteRumor(pos);           // ��� ���� �������
		AddTemplRumour(sled, sid);  // � ��������� ����������� �������� �������
		///////////////////////////////////////////
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void AddRumourLogInfo(int rid)
{
    ref CurrentRumour;
    int pos = FindRumour(rid);
    makeref(CurrentRumour, Rumour[pos]);
    if(CheckAttribute(CurrentRumour, "loginfo"))
    {
        if(CheckAttribute(CurrentRumour, "loginfo.begin"))
        {
            AddQuestRecord(CurrentRumour.loginfo.begin, CurrentRumour.loginfo.textnum);
            
        }
        if(CheckAttribute(CurrentRumour, "loginfo.end"))
        {
            AddQuestRecord(CurrentRumour.loginfo.end, CurrentRumour.loginfo.textnum)
            
            CloseQuestHeader(CurrentRumour.loginfo.end);
        }

        DeleteAttribute(CurrentRumour, "loginfo");
        
    }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////
string SelectRumour() // �������� ��������� ���� �� �������
{
    string rez;
    int Rumour_Index;
    int st;
    ref CurrentRumour;
    Rumour_Index = rand(MAX_RUMOURS - 1);
    for(Rumour_Index; Rumour_Index<MAX_RUMOURS; Rumour_Index++)
    {
        makeref(CurrentRumour, Rumour[Rumour_Index]);
        st=sti(CurrentRumour.state);

        if ((sti(CurrentRumour.actualtime) >= DateToInt(0))
        && (st > 0) && CurrentRumour.text != "") // ���� �� ���������
        {                                                                    // �� ������� �� ����� ��������� ���

            if (sti(CurrentRumour.starttime) <= DateToInt(0))
            {
                st--;
                CurrentRumour.state = st;  //n ��� ������ � ���!
                rez = CurrentRumour.text;
                AddRumourLogInfo(CurrentRumour.id); // fix
                SelectAction(CurrentRumour); // ���� ���� � ���������, �� ���������:
                if (CurrentRumour.text!= "" && CurrentRumour.text!="error") rez = CurrentRumour.text; //fix
                return rez;
            }
            else
            {
                 return NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // ���� ������
            }
        }
        else
        {
            if (CheckAttribute(CurrentRumour, "care") && CurrentRumour.care > 0) SelectAction(CurrentRumour);
            DeleteRumor(FindRumour(CurrentRumour.id)); // ������������ ����� ����
        }

    }
    return NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // ���� ������

}
//////////////////////////////////////////////////////////////////////////////////////////////////////
bool RumourCheker(ref rRumour, string key, aref arPrm)
{
	int iNation = sti(arPrm.nation);
	bool a = true; // �� ����� � �������
	if (CheckAttribute(rRumour, "nonation"))
	{
		//--> fix eddy. �������� ������� � ����
		aref aNation;
		makearef(aNation, rRumour.nonation);
		for (int i = 1 ; i <= GetAttributesNum(aNation) ; i++)
		{
			string svar = "n"+i;
            if (CheckAttribute(aNation, svar) && sti(aNation.(svar)) == iNation ) //fix
			{
                a = false;
				break;
			}
		}
	}
//homo ����� ����
    if (sti(rRumour.starttime) > DateToInt(0)) //�� �������� �� �������
    {
      a = false;
    }

//navy --> �������� �� �������...
    if (CheckAttribute(rRumour, "City"))  // homo 06/11/06 ������ ����� �������� ��������� "!�����"
	{                                    // �.�. ���� ����� �� ���� ������� ����� ���������

        if (CheckAttribute(arPrm, "City"))  // fix homo 15/03/07 (homo ������� �� ��� 06/02/08)
        {
            if (findsubstr(rRumour.City, "!" , 0) != -1)
            {
                if(findsubstr(rRumour.City, arPrm.City, 0) != -1)
                a = false;
            }
            else
            {
                if (rRumour.City != arPrm.City)
                a = false;
            }
        }
        else a = false; // fix homo 15/03/07 (homo ������� �� ��� 06/02/08)

	}
//navy <--
	if ((CheckAttribute(rRumour, "onlynation")) && sti(rRumour.onlynation) != iNation ){ a = false;}
    bool taverncheat = (key == "tavern") && (rand(1)== 1);
	bool b = (rRumour.rep == "none") || (PCharRepPhrase ("bad", "good") == rRumour.rep) || (taverncheat);// � �� ���������
	bool rez = (a) && (b);
	return rez;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
string SelectRumourEx(string key, aref arChr) // �������� ��������� ���� �� ������ �� �������
{                              // key - ���� ����. �����
    int Rumour_Index,i,rnd;
    int st;
    ref CurrentRumour;
    object TEMP[MAX_RUMOURS];
    i = 0;
    for(Rumour_Index = 0; Rumour_Index < MAX_RUMOURS; Rumour_Index++)
    {
        makeref(CurrentRumour, Rumour[Rumour_Index]);
        string tip = CurrentRumour.tip;
        st =  CurrentRumour.state;

        //15/09/06 homo ������ ����� ����������� ��������� ������� ����� �������
        if( findsubstr(tip, key , 0) != -1 || findsubstr(tip, "all" , 0) != -1)  // ���� ����������� ��� �����
        {
            if (sti(CurrentRumour.actualtime) >= DateToInt(0) && st > 0 && CurrentRumour.text != "" )  // ��������������
            {
                // homo 03/09/06 fix � ������ ���� ������ �������� �����!
                if (RumourCheker(CurrentRumour, key, arChr))
                {
                    TEMP[i] = CurrentRumour;
                    i++;
                }

            }
            else
            {
                if (CheckAttribute(CurrentRumour, "care") && CurrentRumour.care > 0) SelectAction(CurrentRumour);
                DeleteRumor(FindRumour(CurrentRumour.id)); // ������������ ����� ����
            }
        }
    }
    if (i > 0)// ���� �� ���������� �����
    {
        rnd=rand(i - 1);
        //-> homo ���� ���������� ����� ������ �� ��������
        int it =0;
        
        while (it < 7 && CheckAttribute(&TEMP[rnd], "LastNPC") && TEMP[rnd].LastNPC == arChr.id)
        {
            rnd=rand(i - 1);
            it++;
        }
        if (it == 7) 
		{
			if (key == "LSC")
				return NO_RUMOUR_LSC_TEXT[rand(4)];// ���� ������
			else
				return NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
		}
        int pin = FindRumour(TEMP[rnd].id);
        Rumour[pin].LastNPC = arChr.id;
        //<-
        AddRumourLogInfo(TEMP[rnd].id);
        SelectAction(&TEMP[rnd]); // ���� ���� � ���������, �� ���������
        st = TEMP[rnd].state;

        st--;  //n ��� ������ � ���!
        makeref(CurrentRumour, Rumour[pin]);
        CurrentRumour.state = st;
        return TEMP[rnd].text;

    }
	return NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];// ���� ������
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
string SelectRumourExSpecial(string key, aref arChr) // �������� ��������� ���� �� ������ �� �������
{                              // key - ���� ����. �����
    int Rumour_Index,i,rnd;
    int st;
    ref CurrentRumour;
    object TEMP[MAX_RUMOURS];
    i = 0;
    for(Rumour_Index = 0; Rumour_Index < MAX_RUMOURS; Rumour_Index++)
    {
        makeref(CurrentRumour, Rumour[Rumour_Index]);
        string tip = CurrentRumour.tip;
        st =  CurrentRumour.state;

        //15/09/06 homo ������ ����� ����������� ��������� ������� ����� �������
        if( findsubstr(tip, key , 0) != -1)  // ���� ������ ����������� 
        {
            if (sti(CurrentRumour.actualtime) >= DateToInt(0) && st > 0 && CurrentRumour.text != "" )  // ��������������
            {
                // homo 03/09/06 fix � ������ ���� ������ �������� �����!
                if (RumourCheker(CurrentRumour, key, arChr))
                {
                    TEMP[i] = CurrentRumour;
                    i++;
                }

            }
            else
            {
                if (CheckAttribute(CurrentRumour, "care") && CurrentRumour.care > 0) SelectAction(CurrentRumour);
                DeleteRumor(FindRumour(CurrentRumour.id)); // ������������ ����� ����
            }
        }
    }
    if (i > 0)// ���� �� ���������� �����
    {
        rnd=rand(i - 1);
        //-> homo ���� ���������� ����� ������ �� ��������
        int it =0;
        
        while (it < 7 && CheckAttribute(&TEMP[rnd], "LastNPC") && TEMP[rnd].LastNPC == arChr.id)
        {
            rnd=rand(i - 1);
            it++;
        }
        if (it == 7) 
		{
			if (key == "LSC")
				return NO_RUMOUR_LSC_TEXT[rand(4)];// ���� ������
			else
				return NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
		}
        int pin = FindRumour(TEMP[rnd].id);
        Rumour[pin].LastNPC = arChr.id;
        //<-
        AddRumourLogInfo(TEMP[rnd].id);
        SelectAction(&TEMP[rnd]); // ���� ���� � ���������, �� ���������
        st = TEMP[rnd].state;

        st--;  //n ��� ������ � ���!
        makeref(CurrentRumour, Rumour[pin]);
        CurrentRumour.state = st;
        return TEMP[rnd].text;

    }
    if (key == "LSC")
		return NO_RUMOUR_LSC_TEXT[rand(4)];// ���� ������
	else
		return NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];// ���� ������
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int AddRumor(string Text, string Status, string Key, string Repa, string Start, string Period, string action, string Next)//��������� ���� � ������� ������
{
 ref tmp1;

    tmp1.text = Text;
    tmp1.state = Status;
    tmp1.tip = Key;
    tmp1.rep = Repa;
    tmp1.starttime = DateToInt(sti(Start));
    tmp1.actualtime = DateToInt(sti(Period)+sti(Start));
    tmp1.event = action;
    tmp1.next = Next;
    return AddRumorR(tmp1);
}

int AddRumorR(ref rum)
{
	object tmp1, tmp2;
	int Rumour_Index;
	bool add, nextORevent;
	add = false;
	ref CurrentRumour;

	tmp1 = rum;
	tmp1.starttime = DateToInt(sti(rum.starttime));
	tmp1.actualtime = DateToInt(sti(rum.starttime)+sti(rum.actualtime)); //fix
	id_counter++; // ������� ������ ++

	tmp1.id = id_counter;

	for(Rumour_Index = 0; Rumour_Index < MAX_RUMOURS; Rumour_Index++)
	{
		makeref(CurrentRumour, Rumour[(MAX_RUMOURS - Rumour_Index - 1)]);
		if (CurrentRumour.text == "" )
		{
			CurrentRumour = tmp1;
			add = true;
			break;
		}
	}

	for(Rumour_Index = 0; (Rumour_Index < MAX_RUMOURS) && (add == false); Rumour_Index++)
	{
		makeref(CurrentRumour, Rumour[Rumour_Index]);
		nextORevent = (CurrentRumour.next != "none")||(CurrentRumour.event != "none");

		// ���� ���� � ������������ ��� � ��������� � �� �����, �� ��������� (!!!!)
		if (nextORevent == true &&	CheckAttribute(CurrentRumour, "care") && 
			sti(CurrentRumour.care) > 0 && Rumour_Index == ( MAX_RUMOURS - 1 )) 
			//navy -- CurrentRumour.care > 0, ���� �� ����������, �.�. ������ � �����.. �������� ����!
		{
			SelectAction(sti(CurrentRumour.id)); 
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//navy -- � ��� ��� �� �����? .tip ������!!! ������� �� ���������
		if (sti(CurrentRumour.tip) != 0  &&				//���� ���� ����������� 
			sti(tmp1.tip) > sti(CurrentRumour.tip) &&	//� ������ 
			Rumour_Index == ( MAX_RUMOURS-1 ) )			//� �� �����
		{
			tmp1 = CurrentRumour;  //�� ���� ����������� ���� ���������
		}

		tmp2 = CurrentRumour;
		CurrentRumour = tmp1;
		tmp1 = tmp2;
	}

	return id_counter;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
int AddTemplRumour(string stName, int nid )//��������� ��������� ���� � ��� �����������
{                                      // tName -  �������  //nid - ID ������� ����� � �������
	object CurTpl; //navy -- ������ ��������� ����� �������
	ref tmpref;
	string att, Next;
	int lngFileID, ishods, tNum;

	tNum = TplNameToNum(stName);
//navy fix --> ����� �� ��������� �������!!! ������ ����������.
	if (tNum == -1)
	{
		if (bBettaTestMode)
		{
			trace("ERROR: <Rumour_func.c>: template " + stName + " not found. Skipped!");
		}
		return -1;
	}
//navy fix <--

	CurTpl = templat[tNum];
	lngFileID = LanguageOpenFile("RumourTexts.txt");

	string tid = CurTpl.name+"_t"+rand(sti(CurTpl.texts)-1);
	ttttstr = LanguageConvertString(lngFileID, tid);

//navy --> ������� ����� �������, �������� ������ �� ����� �������, ����� ������ ��������� ����� ����� ��� ������ �����.
	CurTpl.id = nid;
	string sTemp = CurTpl.function;
	if (sTemp != "")
	{
		call sTemp(&CurTpl);
	}
//navy <--
	ishods = sti(CurTpl.next);
	if (ishods > 0)   // ���� ���� ��������� ��������� ��������
	{   ishods--;
		att = "n" + ishods;
		Next = CurTpl.next.(att);

	}
	else  Next = CurTpl.next;
	// ��������� � ����
	CurTpl.text = ttttstr;
	int rez = AddRumorR(&CurTpl);
	return rez;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int ReplaceTemlpRumour(int rNum, string stName, int nid )//�������� ��������� ���� � ��� �����������
{                                      // tName -  �������  //nid - ID ������� ����� � �������
    ref CurTpl;
    string att, Next;
    int lngFileID, ishods, tNum;
    tNum = TplNameToNum(stName);
    makeref(CurTpl,  templat[tNum]);
    lngFileID = LanguageOpenFile("RumourTexts.txt");

    string tid = CurTpl.name+"_t"+rand(sti(CurTpl.texts)-1);
    ttttstr = LanguageConvertString(lngFileID, tid);
    string sTemp = CurTpl.function;

    if (sTemp != "")
    {
        call sTemp(nid);
    }
    ishods = sti(CurTpl.next);
    if (ishods > 0)   // ���� ���� ��������� ��������� ��������
    {   ishods--;
        att = "n" + ishods;
        Next = CurTpl.next.(att);

    }
    else  Next = CurTpl.next;
    // ��������� � ����
    //int rez = ReplaceRumor(rid ,ttttstr, CurTpl.state, CurTpl.tip, CurTpl.rep, CurTpl.starttime, CurTpl.actualtime, CurTpl.event, Next );
    CurTpl.text = ttttstr;
    ReplaceRumorR(rNum, CurTpl);
    return ;



}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int TplNameToNum(string stName)
{
    int i;
    ref CurTpl;

    for(i = 0; i < MAX_TEMPL; i++)
    {
        makeref(CurTpl, templat[i]);

        if (CheckAttribute(CurTpl, "name") &&  CurTpl.name == stName  )
        {
             return i;
        }

    }
    return -1;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void  DeleteRumor(int del)  //    �������   ���� (�� ������) �� ������� �� ������� �������
{
    object tmp1,tmp2;
    int R_Index;
    ref CurRumour;

    tmp1.id = "";
    tmp1.text = "";
    tmp1.state = "";
    tmp1.tip = "";
    tmp1.rep = "";
    tmp1.starttime = "";
    tmp1.actualtime = "";
    tmp1.event = "none";
    tmp1.next = "none";
    del++;
    for(R_Index = 0; R_Index < del; R_Index++)
    {
        makeref(CurRumour, Rumour[R_Index]);
        tmp2 = CurRumour;
        CurRumour = tmp1;
        tmp1 = tmp2;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void  ReplaceRumorR(int rep, ref rum);
{
	ref CurRumour;
	if (rep != -1)
	{
		makeref(CurRumour, Rumour[rep]);
		rum.id = id_counter;
		rum.starttime = DateToInt(sti(rum.starttime));
		rum.actualtime = DateToInt(sti(rum.actualtime)+sti(rum.actualtime));
		CopyAttributes(CurRumour, rum);
		id_counter++;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//�������� ���� (�� ������)
void  ReplaceRumor(int rep, string Text, string Status, string Key, string Repa, string Start, string Period, string action, string Next)
{
	ref CurRumour;
	if (rep != -1)
	{
		makeref(CurRumour, Rumour[rep]);
		CurRumour.id = id_counter;
		CurRumour.text = Text;
		CurRumour.state = Status;
		CurRumour.tip = Key;
		CurRumour.rep = Repa;
		CurRumour.starttime = DateToInt(sti(Start));
		CurRumour.actualtime = DateToInt(sti(Period)+sti(Start));
		CurRumour.event = action;
		CurRumour.next = Next;
		id_counter++;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
int FindRumour(int Id)  // ���������� ����� �������� �����, ���� ��� �� -1 (����� �� ID)
{
	int Rumour_Index;
	ref CurrentRumour;

	for(Rumour_Index = 0; Rumour_Index < MAX_RUMOURS; Rumour_Index++)
	{
		makeref(CurrentRumour, Rumour[Rumour_Index]);

		if ( CurrentRumour.id == Id  )// ���� ����� Id �� ���� ������ �� ����
		{
			return Rumour_Index;
		}
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
int AddSimpleRumour(string stext, int nation, int terms, int qty)
{
    object tmp;
    ref mc;
	mc = GetMainCharacter();

    tmp.text = stext;
    tmp.state = qty;//���-�� ���
    tmp.tip = "all";
    tmp.rep = "none";
	//10, 11, 12, 13 - ��������� ��� ����� �� ������ 
	if (nation > 5) tmp.nonation = nation - 10; 
	else tmp.onlynation = nation; //�����������
    tmp.starttime = 0;
    tmp.actualtime = terms; //�����
    tmp.event = "none";
    tmp.next = "none";
    return AddRumorR(&tmp)
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int AddSimpleRumourEx(string stext, int City, int terms, int qty, string sEvent, string AddString)
{
    object tmp;
    ref mc;
	mc = GetMainCharacter();

    tmp.text = stext;
    tmp.state = qty;//���-�� ���
    tmp.tip = "all";
    tmp.rep = "none";
	tmp.City = City; //�����������
    tmp.starttime = 0;
    tmp.actualtime = terms; //�����
    tmp.event = sEvent;
    tmp.next = "none";
	tmp.addString = AddString; //������ � �����������, �������������
    return AddRumorR(&tmp)
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int AddSimpleRumourCity(string stext, string City, int terms, int qty, string sEvent)
{
    object tmp;
    ref mc;
	mc = GetMainCharacter();

    tmp.text = stext;
    tmp.state = qty;//���-�� ���
    tmp.tip = "all";
    tmp.rep = "none";
	tmp.City = City;
    tmp.starttime = 0;
    tmp.actualtime = terms; //�����
    tmp.next = "none";
	tmp.event = sEvent;
    return AddRumorR(&tmp)
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int AddSimpleRumourCityTip(string stext, string City, int terms, int qty, string Tip, string sEvent)
{
    object tmp;
    ref mc;
	mc = GetMainCharacter();

    tmp.text = stext;
    tmp.state = qty;//���-�� ���
    tmp.tip = Tip;
    tmp.rep = "none";
	tmp.City = City;
    tmp.starttime = 0;
    tmp.actualtime = terms; //�����
    tmp.event = "none";
    tmp.next = "none";
	tmp.event = sEvent;
    return AddRumorR(&tmp)
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int AddSimpleRumourTip(string stext, int terms, int qty, string Tip, string sEvent)
{
    object tmp;
    ref mc;
	mc = GetMainCharacter();

    tmp.text = stext;
    tmp.state = qty;//���-�� ���
    tmp.tip = Tip;
    tmp.rep = "none";
    tmp.starttime = 0;
    tmp.actualtime = terms; //�����
    tmp.event = "none";
    tmp.next = "none";
	tmp.event = sEvent;
    return AddRumorR(&tmp)
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RumourHasInformation(string RumText)
{
	for(int i = 0; i < SIMPLE_RUMOUR_NUM - 1; i++)
	{
		if(RumText == NO_RUMOUR_TEXT[i]) return false;
	}   
    return true;
}
            