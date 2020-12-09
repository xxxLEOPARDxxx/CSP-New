//  ��������� ����� ��������� ������
string totalInfo;
string sCity;
int    iNation, iDay;

void InitInterface(string iniName)
{
    LAi_group_SetAlarm("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, 0.0);
    StartAboveForm(true);
    // ����� ����� � �����
    bQuestCheckProcessFreeze = true;
    
    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

    if (CheckAttribute(Pchar, "GenQuestFort.ColonySiegeId"))
    {
        // ����� �����
        sCity    = pchar.GenQuestFort.ColonySiegeId;
		iNation  = sti(pchar.GenQuestFort.ColonySiegeNation);
		DeleteAttribute(Pchar, "GenQuestFort.ColonySiegeId");
		DeleteAttribute(Pchar, "GenQuestFort.ColonySiegeNation");
		
		if (CheckAttribute(Pchar, "GenQuestFort.ColonySiegeEnd"))
		{// ����� �����
            DeleteAttribute(Pchar, "GenQuestFort.ColonySiegeEnd");
			CalculateEndSiegeCity();
		}
		else
		{
            iDay     = sti(pchar.GenQuestFort.ColonySiegeTime);
            DeleteAttribute(Pchar, "GenQuestFort.ColonySiegeTime");
			CalculateSiegeCity();
		}
    }
    else
    {
		// ����� ������� ������, �� ������������
		sCity    = pchar.GenQuest.CapturedCity;
		iNation  = sti(pchar.GenQuest.CaptureNation);
		CalculateCapturedCity();
	}
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);
    
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
    PostEvent("StopQuestCheckProcessFreeze", 100);//��������� �������� �������
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
    	case "B_OK":
    		if(comName=="activate" || comName=="click")
    		{
                IDoExit(RC_INTERFACE_SALARY_EXIT);
    		}
    	break;
	}
}

void CalculateEndSiegeCity()
{
    string sTemp =  GetNationNameByType(iNation);
    
	totalInfo = "����� " + GetCityName(sCity) + " �������� �������� " + XI_ConvertString(sTemp + "Gen") + ".";

    SetNewGroupPicture("Nat1", "NATIONS",  sTemp);
    SetFormatedText("INFO_TEXT",totalInfo);
}

void CalculateSiegeCity()
{
    string sTemp =  GetNationNameByType(iNation);
    
	if (!isCityHasFort(sCity)) // ���������� �����
	{
	    totalInfo = "������ "+XI_ConvertString(sTemp + "Gen")+" ������ ����� "+GetCityName(sCity)+". � ��� ���� "+FindRussianDaysString(iDay)+" ��� ������ �����.";
	}
	else
	{
		totalInfo = "������� "+XI_ConvertString(sTemp + "Gen")+" ������� ����� "+GetCityName(sCity)+". � ��� ���� "+FindRussianDaysString(iDay)+" ��� ������ �����.";
	}
    SetNewGroupPicture("Nat1", "NATIONS",  sTemp);
    SetFormatedText("INFO_TEXT",totalInfo);
}

void CalculateCapturedCity()
{

    totalInfo = "��� ������� " + XI_ConvertString("Colony" + sCity) + " ������ ����� ����.";

    SetNewGroupPicture("Nat1", "NATIONS",  GetNationNameByType(iNation));
    SetFormatedText("INFO_TEXT",totalInfo);
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}
