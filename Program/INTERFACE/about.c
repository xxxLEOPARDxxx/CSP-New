// ������, ����� ��� ��� :)
// boal ������ ������ �� ����, ���� ���� ������ �� ��������, ����� �� ��� ;)
float fNewPos;
#define MAX_LINE         97

string STR_TEXT[MAX_LINE] = {
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"��������� �����������",
"",
"LEOPARD's team",
"Corsairs Ship Pack: MaelStrom Edition",
"",
"",
"",
"",
"",
"���������� ����",
"LEOPARD",
"",
"������",
"LEOPARD",
"Gregg",
"Sinistra",
"BlackThorn",
"Qwerry, St.",
"Lipsar",
"Arty",
"",
"",
"",
"������ � ��������� �����������",
"LEOPARD",
"Gregg",
"Qwerry, St.",
"BlackThorn",
"Lipsar",
"",
"������������",
"LEOPARD",
"Gregg",
"Googman",
"Qwerry, St.",
"Shaharan",
"BlackThorn",
"Lipsar",
"Sinistra",
"Arty",
"",
"",
"��� �������� ����������� ����",
"������������ ��������� �������",
"",
"��� � ������� �� �������: ��������� �������",
"",
"��� � ������� �� �������: ������� ����",
"",
"��� � ������� �� �������: ������� ������",
"",
"������� �� ������� 2: ������ ���������� ����",
"",
"��� � ������� �� �������: New abilities 0.4.0",
"",
"��� � ������� �� Gentelmen of Fortune: Eras II",
"",
"������� � ����� '������ ��������'",
"",
"�������� ������� ��������� �����",
"��� ����, ����������� � ������ �������",
"���������� ����� � ������ CSP",
"",
"",
"������� �� ��� ����������� ����� '������ ��������' � �� ������ �� �������",
"Konstrush �� ��� �������� ��� ������ � �� ������, ������ HUD",
"Etienne � Narve �� �������� ���������� �� ׸����� ������� � �� ������",
"karlik-nos �� ������ �� ������������� ������ �����",
"johnny88 �� �������� ��� � ��������� ���� ���������",
"Kormach �� ��������� ��������� ����������",
"",
"",
"������, ����� ���������� �� �������",
"Korsar Maxim",
"Zik",
"crem_soda",
"Krah_an_Krait",
"",
"",
"������ ������������� �������������",
"������ MaelStrom ChezJfrey �� Buccaneer's Reef",
"��� ���� �� ���� �� �� ������� �������� �������!",
};

string STR_COLOR[MAX_LINE] = {
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"blue",
"",
"yellow",
"yellow",
"",
"",
"",
"",
"",
"yellow",
"",
"",
"yellow",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"yellow",
"",
"",
"",
"",
"",
"",
"yellow",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"blue",
"blue",
"",
"yellow",
"",
"yellow",
"",
"yellow",
"",
"yellow",
"",
"yellow",
"",
"yellow",
"",
"yellow",
"",
"blue",
"blue",
"blue",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"yellow",
"",
"",
"",
"",
"",
"",
"yellow",
"yellow",
"red",
};


void InitInterface(string iniName)
{
	GameInterface.title = "";
	
	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak", "ProcessCancelExit", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("My_MoveText", "MoveText", 0);

	SetFormatedText("INFO_TEXT", "");
	int i, k;
	
	for(i = 0; i < MAX_LINE; i++)
	{
		SendMessage(&GameInterface, "lsle", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 0, STR_TEXT[i] + "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	
		if(STR_COLOR[i] != "")
		{
			switch (STR_COLOR[i])
			{
				case "yellow":
					SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 8, i, argb(255,251,237,68));
				break;
				case "red":
					SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 8, i, argb(255,255,162,162));
				break;
				case "blue":
					SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 8, i, argb(255,0,255,255));
				break;
			}
		}
	}

	PostEvent("My_MoveText", 370);
	fNewPos = 0;
}

void ProcessCancelExit()
{
	if(CheckAttribute(&InterfaceStates, "showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
	{
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU);
		return;
	}

	IDoExit(RC_INTERFACE_OPTIONSCREEN_EXIT);
	if(!CheckAttribute(&InterfaceStates, "InstantExit") || sti(InterfaceStates.InstantExit) == false) ReturnToMainMenu();
}

void IDoExit(int exitCode)
{
 	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("My_MoveText","MoveText");
    
	interfaceResultCommand = exitCode;
	if(CheckAttribute(&InterfaceStates,"InstantExit") && sti(InterfaceStates.InstantExit) == true)
		EndCancelInterface(true);
	else
		EndCancelInterface(false);
}

void MoveText()
{
	if(fNewPos >= 1)
	{
		ProcessCancelExit();
	}
	else
	{
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",2, fNewPos);
		PostEvent("My_MoveText", 20);
		fNewPos = fNewPos + 0.0003;
	}
}