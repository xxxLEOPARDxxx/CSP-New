/////////////////////////
// CSP 2.1.0
/////////////////////////

string totalInfo = "";
string CurTable, CurRow;
string sMessageMode;
ref chr;

int iSelected; // курсор в таблице		

void InitInterface(string iniName)
{
 	StartAboveForm(true);
	
    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

    SetFormatedText("MAP_CAPTION", XI_ConvertString("titlePsHero"));

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ShowPGGInfo","ShowPGGInfo",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0); // выход из интерфейса
	sMessageMode = "";
	FillTable();
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_ANY_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_ANY_EXIT );
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ShowPGGInfo","ShowPGGInfo");
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

	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}


void FillTable()
{
	ref chr;
	int i, n;
	string row;
	
	
	n = 1;
	// шапка -->
    GameInterface.TABLE_HERO.select = 0;
    GameInterface.TABLE_HERO.hr.td1.str = "Фото";
    GameInterface.TABLE_HERO.hr.td1.scale = 1.0;
    GameInterface.TABLE_HERO.hr.td2.str = "Имя";
    GameInterface.TABLE_HERO.hr.td2.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td3.str = "Ранг";
	GameInterface.TABLE_HERO.hr.td3.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td4.str = "Нация";
	GameInterface.TABLE_HERO.hr.td4.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td5.str = "Корабль";
	GameInterface.TABLE_HERO.hr.td5.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td6.str = "Местоположение";
	GameInterface.TABLE_HERO.hr.td6.scale = 1.0;
	// GameInterface.TABLE_HERO.hr.td7.str = "Пункт назначения";
	GameInterface.TABLE_HERO.hr.td7.str = "P.I.R.A.T.E.S.";
	GameInterface.TABLE_HERO.hr.td7.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td8.str = "Репутация";
	GameInterface.TABLE_HERO.hr.td8.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td9.str = "Отношение";
	GameInterface.TABLE_HERO.hr.td9.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td10.str = "Пиастры";
	GameInterface.TABLE_HERO.hr.td10.scale = 1.0;

	for (i = 1; i <= PsHeroQty; i++)
	{
		chr = CharacterFromID("PsHero_" + i);
		if(!CharacterIsDead(chr))
		{
			if(chr.PGGAi.IsPGG != false)
			{
				//временно либо офицер, либо компаньон... не работаем с ним.
				//if (!sti(chr.PGGAi.IsPGG)) continue;
				//помер, нефиг мертвых качать.
				//if (LAi_IsDead(chr)) continue;
				
				row = "tr" + n;
				GameInterface.TABLE_HERO.(row).index = i;
				GameInterface.TABLE_HERO.(row).td1.icon.texture = "INTERFACES\PORTRAITS\128\face_" + chr.faceId + ".tga";
				GameInterface.TABLE_HERO.(row).td1.icon.uv = "0,0,1,1";
				GameInterface.TABLE_HERO.(row).td1.icon.width = 40;
				GameInterface.TABLE_HERO.(row).td1.icon.height = 40;
				GameInterface.TABLE_HERO.(row).td1.icon.offset = "-2, -1";
				// GameInterface.TABLE_HERO.(row).td1.str = chr.id;
				GameInterface.TABLE_HERO.(row).td1.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td2.str = GetFullName(chr);
				GameInterface.TABLE_HERO.(row).td2.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td3.str = chr.rank;
				GameInterface.TABLE_HERO.(row).td3.scale = 1.0;
				GameInterface.TABLE_HERO.(row).td4.str = XI_ConvertString(Nations[sti(chr.nation)].name);
				GameInterface.TABLE_HERO.(row).td4.scale = 0.8;
				if (GetCharacterShipType(chr) != SHIP_NOTUSED)
				{
					GameInterface.TABLE_HERO.(row).td5.str = XI_ConvertString(RealShips[GetCharacterShipType(chr)].BaseName);
					GameInterface.TABLE_HERO.(row).td5.scale = 0.8;
				}
				else
				{
					GameInterface.TABLE_HERO.(row).td5.str = "Нет корабля";
					GameInterface.TABLE_HERO.(row).td5.scale = 0.8;
				}
				GameInterface.TABLE_HERO.(row).td6.str = XI_ConvertString("Colony"+chr.PGGAi.location.town);
				GameInterface.TABLE_HERO.(row).td6.scale = 0.8;
				/* if (CheckAttribute(chr, "PGGAi.task.target"))
				{
					GameInterface.TABLE_HERO.(row).td7.str = XI_ConvertString("Colony"+chr.PGGAi.task.target);
					GameInterface.TABLE_HERO.(row).td7.scale = 0.8;
				}
				else
				{
					GameInterface.TABLE_HERO.(row).td7.str = "Находится в колонии";
					GameInterface.TABLE_HERO.(row).td7.scale = 0.8;
				} */
				GameInterface.TABLE_HERO.(row).td7.str = "" + chr.SPECIAL.Strength + " " + chr.SPECIAL.Perception + " "+chr.SPECIAL.Agility + " " + chr.SPECIAL.Charisma + " "+chr.SPECIAL.Intellect + " " + chr.SPECIAL.Endurance   + " " + chr.SPECIAL.Luck;
				GameInterface.TABLE_HERO.(row).td7.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td8.str = ""+makeint(chr.reputation);
				GameInterface.TABLE_HERO.(row).td8.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td9.str = ""+PGG_ChangeRelation2MainCharacter(chr, 0);
				GameInterface.TABLE_HERO.(row).td9.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td10.str = ""+chr.Money;
				GameInterface.TABLE_HERO.(row).td10.scale = 0.8;
				n++;
			}
		}
	}
	Table_UpdateWindow("TABLE_HERO");
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
}

void ShowPGGInfo()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index"))
	{ // нет ПГГ в списке
	chr = CharacterFromID("PsHero_" + GameInterface.TABLE_HERO.(CurRow).index);
	SetSPECIALMiniTable("TABLE_SMALLSKILL", chr);
	SetOTHERMiniTable("TABLE_SMALLOTHER", chr);
	SetFormatedText("OFFICER_NAME", GetFullName(chr));
	SetNewPicture("CHARACTER_BIG_PICTURE", "interfaces\portraits\256\face_" + chr.faceId + ".tga");
	SetNewPicture("CHARACTER_FRAME_PICTURE", "interfaces\Frame3.tga");
	
	XI_WindowShow("RPG_WINDOW", true);
	XI_WindowDisable("RPG_WINDOW", false);
	sMessageMode = "RPG_Hint";
	}
}

void ExitRPGHint()
{
	if (sMessageMode == "RPG_Hint")
	{
		XI_WindowShow("RPG_WINDOW", false);
		XI_WindowDisable("RPG_WINDOW", true);
		sMessageMode = "";
	}
}

void HideInfoWindow()
{
	CloseTooltip();
	ExitRPGHint();
}