
void InitInterface(string iniName)
{
    	GameInterface.title = "titleAttackMessage";

    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	MessageInfo();

	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_SALARY_EXIT);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_SALARY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
	    case "BUTTON":
		  if(comName=="activate" || comName=="click")
		  {
			 PostEvent("evntDoPostExit",1,"l",RC_INTERFACE_SALARY_EXIT);
		  }
	    break;
	    
	    /*
	    case "TO_NOTICE":
		  if(comName=="activate" || comName=="click")
		  {
			IDoExit(RC_INTERFACE_CREATE_NOTICE, false);
			return;
		  }
	    break;
	    */
	}
}


void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void MessageInfo()
{
	string sMessageFrom = "";

	CreateString(true,"Header", "������� ���������", FONT_CAPTION, COLOR_NORMAL, 395,153,SCRIPT_ALIGN_CENTER,1.5);
	
	string sColonyName = "������";
	if(CheckAttribute(PChar, "ColonyBuilding.ColonyName"))
	{
		sColonyName = PChar.ColonyBuilding.ColonyName;
	}
	
	bool bFirst = sti(PChar.ColonyBuilding.MessageInfo.First);
	
	string sTarget = PChar.ColonyBuilding.MessageInfo.Target;
	string sType = PChar.ColonyBuilding.MessageInfo.Type;
	string sEnd = PChar.ColonyBuilding.MessageInfo.End;
	int iTime = sti(PChar.ColonyBuilding.MessageInfo.Time);
	int iNation = sti(PChar.ColonyBuilding.MessageInfo.Nation);
	
	string sNation = GetNationNameByType(iNation) + "Gen";
	string sNationEnd = GetNationNameByType(iNation) + "Abl";
	string sNationDat = "people" + GetNationNameByType(iNation) + "Dat";
	
	sNation = XI_ConvertString(sNation);
	sNationEnd = XI_ConvertString(sNationEnd);
	sNationDat = XI_ConvertString(sNationDat);
	
	string sTexture = GetPictureForMessage(sTarget, true);
	string sPicture = GetPictureForMessage(sTarget, false);
	
	if(PChar.ColonyBuilding.Stage == "1" && sTarget == "Colony")
	{
		SetNewPicture("TARGET", "loading\towns\pearl1.tga");
	}
	else
	{
		SetNewGroupPicture("TARGET", sTexture, sPicture);
	}
	
	string sTemp = "";
	string sMessage = "";
	
	if(bFirst)
	{
		sMessage += "������� " + GetName(PChar, "f") + ", ��������� ����� ������ �� ������� ''" + sColonyName + "''!";
	}
	
	sMessage += newStr();
	
	if(bFirst)
	{
		sPicture = "Enemy";
		
		switch(sTarget)
		{
			case "Colony": 
				switch(sType)
				{
					case "Mutiny": sTemp = "� ����� ������� ��������� �����. �� ���������, ���������� �� �������, �������� ������ ������������ "; break;
					case "BattleLand": sTemp = "�� ���� ������� ��������� ��������� � ����. �� ���������, ���������� �� �������, �������� ������ ������������ "; break;
					case "BattleSea": sTemp = "�� ������� ��������� ��������� �������� ��� ������ " + sNation + ". �� ���������� ��������� ������ ������ ������������ "; break;
				}
			break;
			
			case "Mines": 
				switch(sType)
				{
					case "Mutiny": sTemp = "�� ����� �������� ��������� �����. �� ���������� ���������, �������� ������ ������������ "; break;
					case "BattleLand": sTemp = "�� ���� ������� ��������� ���������. �� ���������� ���������, �������� ������ ������������ "; break;
					case "BattleSea": sTemp = ""; break;
				}
			break;
			
			case "Plantation": 
				switch(sType)
				{
					case "Mutiny": sTemp = "�� ����� ��������� ��������� �����. �� ���������� ���������, �������� ������ ������������ "; break;
					case "BattleLand": sTemp = ""; break;
					case "BattleSea": sTemp = ""; break;
				}
			break;
		}
	}
	else
	{
		if(sEnd == "Good")
		{
			sPicture = "Friend";
		}
		else
		{
			sPicture = "Enemy";
		}
		
		switch(sTarget)
		{
			case "Colony": 
				switch(sType)
				{	
					case "Mutiny": if(sEnd == "Good") { sTemp = "����� � ����� ������� ������� ��������."; }else{ sTemp = "���������� ������� ������� ������������� ��������� �������."; } break;
					case "BattleLand": if(sEnd == "Good") { sTemp = "�� ������� ������ ������� �������! ���������, �������������� ������, ���� ������!"; }else{ sTemp = "�� ������� ������ ������ �������... ������� �� ������ �������� ���� � ���� �����������."; } break;
					case "BattleSea": if(sEnd == "Good") { sTemp = "�������� ������� �������� �� �������! ������ �������� ������ ������� ������� ���� ����� ��������� " + sNationDat + "."; }else{ sTemp = "������ ������� ������ �� �������. ���������, ������������ " + sNationEnd + ", �� ������� �������������. ������� ���� �����������."; } break;
				}
			break;
			
			case "Mines": 
				switch(sType)
				{	
					case "Mutiny": if(sEnd == "Good") { sTemp = "����� �� ����� �������� ������� ��������."; }else{ sTemp = "���� ������� ������������� ��������� �������� � ���������� � �������, ������� ��������� ��������, ����������� � ������� ����."; } break;
					case "BattleLand": if(sEnd == "Good") { sTemp = "�� ������� ������ ������� �������! ���������, �������������� ������ �� �������, ���� ������!"; }else{ sTemp = "�� ������� ������ ������ �������... ��������, ���������� �������, �� ���� ���������������� ��������� �������������. ������� ���� �����������."; } break;
				}
			break;
			
			case "Plantation": 
				switch(sType)
				{	
					case "Mutiny": if(sEnd == "Good") { sTemp = "����� �� ����� ��������� ������� ��������."; }else{ sTemp = "���� ������� ������������� ��������� � ���������� � �������, ������� ��������� ��������, ����������� � ������� ��������."; } break;
				}
			break;
		}
	}
	
	SetNewGroupPicture("STATE", "RELATIONS", sPicture);
	
	bool bLoose = sType == "MutinyLoose" || sType == "BattleLandLoose" || sType == "BattleSeaLoose";
	if(!bFirst && bLoose)
	{
		switch(sTarget)
		{
			case "Colony":
				switch(sType)
				{
					case "MutinyLoose": sTemp = "� ����� ������� �������� �����. ��-�� ���������� ������������ ��������� ��������� ����������� ������."; break;
					case "BattleLandLoose": sTemp = "�� ���� ������� ���� ��������� ��������� � ����. ��-�� ���������� ������������ ��������� ���������� ����� ����� ������� ���� � ���������� �."; break;
					case "BattleSeaLoose": sTemp = "�� ������� ������ ������� ��� ������ " + sNation + ". ��-�� ���������� ��������� ������ ��������� ����� � ��������� ������� ���������� �������."; break;
				}
			break;
			
			case "Mines":
				switch(sType)
				{
					case "MutinyLoose": sTemp = "�� ����� �������� �������� �����. ��-�� ���������� ������������ ��������� ��������� ����������� ������ � ��������� � �������."; break;
					case "BattleLandLoose": sTemp = "�� ���� ������� ���� ��������� ���������. ��-�� ���������� ������������ ��������� ���������� ����� ����� ������� ���� � ���������� ��."; break;
				}
			break;
			
			case "Plantation":
				switch(sType)
				{
					case "MutinyLoose": sTemp = "�� ����� ��������� �������� �����. ��-�� ���������� ������������ ��������� ��������� ����������� ������ � ��������� � �������."; break;
				}
			break;
		}
	}
	
	sMessage += sTemp;
	
	if(bFirst)
	{
		sMessage += FindRussianDaysString(iTime) + "."
	}
	
	SetFormatedText("MESSAGE", sMessage);
}

string GetPictureForMessage(string sTarget, bool bTexture)
{
	int iTown = 1;
	if(CheckAttribute(PChar, "ColonyBuilding.Architecture.Town"))
	{
		iTown = sti(PChar.ColonyBuilding.Architecture.Town);
	}
	
	switch(sTarget)
	{
		case "Colony": 		if(bTexture) { return "COLONY_ARCHITECTURE"; 	}else{ return "Town_Type_" + iTown; } 	break;
		case "Mines": 		if(bTexture) { return GetCurrentTexture(); 	}else{ return "GoldMine"; } 		break;
		case "Plantation": 	if(bTexture) { return GetCurrentTexture(); 	}else{ return "Plantation"; } 		break;
	}
	
	return "none";
}

string GetCurrentTexture()
{
	if(CheckAttribute(PChar, "ColonyBuilding.CurrentIconsTexture"))
	{
		return "COLONY_BUILDINGS_" + sti(PChar.ColonyBuilding.CurrentIconsTexture);
	}
	
	return "COLONY_BUILDINGS_1";
}




