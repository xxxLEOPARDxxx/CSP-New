//#20170605-01 PANQL mod
string totalInfo;
void InitInterface(string iniName)
{
    bQuestCheckProcessFreeze = true;
    if(IsEntity(worldMap))
    {
    	wdmLockReload            = true;
    }
    StartAboveForm(true);

    GameInterface.title = "titleNationLegend";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	//CalculateNationRelat();

	totalInfo = XI_ConvertString("PANQLTimePass");

	//Log_SetStringToLog(totalInfo);

	SetNewGroupPicture("RelNat", "NATIONS", GetNationNameByType(sti(pchar.nation)));
    //SetNewGroupPicture("Nat1", "NATIONS",  GetNationNameByType(Nation1));
    //SetNewGroupPicture("Nat2", "NATIONS", GetNationNameByType(Nation2));
    //SetNewGroupPicture("RelNat", "relations", GetRelationName(GetNationRelation(Nation1, Nation2)));

	SetFormatedText("INFO_TEXT",totalInfo);
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
    PostEvent("StopQuestCheckProcessFreeze", 500);
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

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}
