/*
	������: waitress
		������� ����� ���������� ������: barmen
		������� � ������: stay1
		������� ������� � �������: stay2
	������ ��������� ����� ������: tables
		����� �� ����� ��������
*/


#define LAI_TYPE_WAITRESS	"waitress"


//�������������
void LAi_type_waitress_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}else{
		if(chr.chr_ai.type != LAI_TYPE_WAITRESS) isNew = true;
	}
	if(isNew == true)
	{
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_WAITRESS;
		chr.chr_ai.type.time = "0";
		chr.chr_ai.type.task = "wait";
		chr.chr_ai.type.locator = "";
		//��������� ������ �������
		LAi_tmpl_stay_InitTemplate(chr);
	}	
	//��������� �������� ���������
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//��������������� ���� ���������
void LAi_type_waitress_CharacterUpdate(aref chr, float dltTime)
{	
	bool isProcessed;
	//���� ������
	if(LAi_CanNearEnemy(chr, 5.0))
	{
		chr.chr_ai.type.task = "afraid";
		LAi_tmpl_ani_PlayAnimation(chr, "afraid", -1.0);
		LAi_SetAfraidDead(chr);
		return;
	}else{
		if(chr.chr_ai.type.task == "afraid")
		{
			LAi_SetDefaultDead(chr);
			LAi_tmpl_stay_InitTemplate(chr);
			chr.chr_ai.type.task = "wait";
			chr.chr_ai.type.time = 1 + rand(2);
			return;
		}
	}
	//������������ �������
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY)
	{
		//����� ���� ������ ��� �������� � ��������
		float time = stf(chr.chr_ai.type.time);
		time = time - dltTime;
		chr.chr_ai.type.time = time;
		if(time <= 0)
		{
			//���� �������� �����������
			isProcessed = false;
			switch(chr.chr_ai.type.task)
			{
			case "wait":
				isProcessed = true;
				if(rand(100) < 70)
				{
					//��� � �������
					LAi_type_waitress_GotoBarm(chr);
				}else{
					//��� � �����
					LAi_type_waitress_GotoTable(chr);
				}
				break;
			case "wait barm":
				isProcessed = true;
				//��� � �����
				if(rand(100) < 30)
				{
					//��� ��������
					LAi_type_waitress_GotoStay(chr);
				}else{
					//��� � �����
					LAi_type_waitress_GotoTable(chr);
				}
				break;
			case "wait table":
				isProcessed = true;
				//��� � �������
				LAi_type_waitress_GotoBarm(chr);
				break;
			}
			if(!isProcessed)
			{
				LAi_type_waitress_Reset(chr);
			}
		}
	}
}

//�������� ��������� � �������
bool LAi_type_waitress_CharacterLogin(aref chr)
{
	return true;
}

//�������� ��������� �� �������
bool LAi_type_waitress_CharacterLogoff(aref chr)
{
	return true;
}

//���������� ������ ���������
void LAi_type_waitress_TemplateComplite(aref chr, string tmpl)
{
	if(tmpl == LAI_TMPL_GOTO)
	{
		if(chr.chr_ai.type.task == "goto table")
		{
			if(rand(100) < 70)
			{
				chr.chr_ai.type.task = "tidy out";
				CharacterTurnByLoc(chr, "tables", chr.chr_ai.type.locator);
				LAi_tmpl_ani_PlayAnimation(chr, "taverngirl", 2.0 + rand(6));
			}else{
				LAi_type_waitress_Wait(chr, 3.0 + rand(3));
				chr.chr_ai.type.task = "wait table";
			}
			if(rand(100) < 20)
			{
				LAi_CharacterPlaySound(chr, "waitress");
			}
		}else{
			CharacterTurnByLoc(chr, "waitress", chr.chr_ai.type.locator);
			if(chr.chr_ai.type.task == "goto barm")
			{
				LAi_type_waitress_Wait(chr, 2.0 + rand(3));
				chr.chr_ai.type.task = "wait barm";
				LAi_CharacterPlaySound(chr, "waitress_brm");
			}else{
				LAi_type_waitress_Wait(chr, 5.0 + rand(5));
				if(rand(100) < 30)
				{
					LAi_CharacterPlaySound(chr, "waitress");
				}
			}
		}
	}else{
		if(tmpl == LAI_TMPL_ANI)
		{
			if(chr.chr_ai.type.task == "tidy out")
			{
				LAi_type_waitress_Wait(chr, rand(2));
			}
		}else{
			LAi_type_waitress_Reset(chr);
		}
	}
}

//�������� � ������� ������� ������
void LAi_type_waitress_NeedDialog(aref chr, aref by)
{
}

//������ �� ������, ���� ���������� true �� � ���� ������ ����� ������ ������
bool LAi_type_waitress_CanDialog(aref chr, aref by)
{
	//���� ������ �����, �� ���������� �� ������
	if(chr.chr_ai.tmpl == LAI_TMPL_GOTO) return true;
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	return false;
}

//������ ������
void LAi_type_waitress_StartDialog(aref chr, aref by)
{
	//���� �� �������, ��������� ������ ��� ������� ����������
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//��������� ������
void LAi_type_waitress_EndDialog(aref chr, aref by)
{
	//�������������� ������� ����� �������
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
	bool isProcessed = false;
	switch(chr.chr_ai.type.task)
	{
	case "wait":
		if(chr.chr_ai.type.locator != "") CharacterTurnByLoc(chr, "waitress", chr.chr_ai.type.locator);
		LAi_tmpl_stay_InitTemplate(chr);
		isProcessed = true;
		break;
	case "wait barm":
		CharacterTurnByLoc(chr, "waitress", chr.chr_ai.type.locator);
		LAi_tmpl_stay_InitTemplate(chr);
		isProcessed = true;
		break;
	case "wait table":
		CharacterTurnByLoc(chr, "tables", chr.chr_ai.type.locator);
		LAi_tmpl_stay_InitTemplate(chr);
		isProcessed = true;
		break;
	case "tidy out":
		CharacterTurnByLoc(chr, "tables", chr.chr_ai.type.locator);
		LAi_tmpl_ani_PlayAnimation(chr, "taverngirl", 2.0 + rand(6));
		isProcessed = true;
		break;
	case "goto table":
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, "tables", chr.chr_ai.type.locator, -1.0);
		isProcessed = true;
		break;
	case "goto barm":
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, "waitress", "barmen", -1.0);
		isProcessed = true;
		break;
	case "goto stay":
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, "waitress", chr.chr_ai.type.locator, -1.0);
		isProcessed = true;
		break;
	}
	if(!isProcessed)
	{
		LAi_type_waitress_Reset(chr);
	}
}


//�������� ���������
void LAi_type_waitress_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//�������� ��������
void LAi_type_waitress_Attacked(aref chr, aref by)
{
	
}

//������ � �����
void LAi_type_waitress_Wait(aref chr, float time)
{
	LAi_tmpl_stay_InitTemplate(chr);
	chr.chr_ai.type.task = "wait";
	chr.chr_ai.type.time = time;	
}

//��� � �������
void LAi_type_waitress_GotoBarm(aref chr)
{
	chr.chr_ai.type.task = "goto barm";
	chr.chr_ai.type.time = 5 + rand(5);
	chr.chr_ai.type.locator = "barmen";
	LAi_tmpl_goto_InitTemplate(chr);
	LAi_tmpl_goto_SetLocator(chr, "waitress", "barmen", -1.0);
}

//��� ��������
void LAi_type_waitress_GotoStay(aref chr)
{
	chr.chr_ai.type.task = "goto stay";
	chr.chr_ai.type.time = 7 + rand(8);
	if(rand(100) < 70)
	{
		chr.chr_ai.type.locator = "stay1";
	}else{
		chr.chr_ai.type.locator = "stay2";
	}
	LAi_tmpl_goto_InitTemplate(chr);
	LAi_tmpl_goto_SetLocator(chr, "tables", chr.chr_ai.type.locator, -1.0);
}

//��� � �����
void LAi_type_waitress_GotoTable(aref chr)
{
	chr.chr_ai.type.task = "goto table";
	chr.chr_ai.type.time = 5 + rand(3);
	//�������� �������
	string locator = LAi_FindRandomLocator("tables");
	if(locator != "")
	{
		chr.chr_ai.type.locator = locator;
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, "tables", locator, -1.0);
	}else{
		LAi_type_waitress_Reset(chr);
	}
}

void LAi_type_waitress_Reset(aref chr)
{
	LAi_tmpl_stay_InitTemplate(chr);
	chr.chr_ai.type.task = "wait";
	chr.chr_ai.type.time = "20";
}
