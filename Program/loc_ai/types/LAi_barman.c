/*
���: �������, ������ �����, �������� �� �������, ������� �� ������

	������������ �������:
		stay
		dialog



	������: barmen
		������� ��������� ������� ��������: stay
		������� ����� ����� �� ������ (������): bar1
		������� ����� ����� ������ (���� ��� �� ������ �� bar1): bar2

*/



#define LAI_TYPE_BARMAN		"barman"


//�������������
void LAi_type_barman_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_BARMAN;
	chr.chr_ai.type.state = "stay";
	chr.chr_ai.type.time = "0";
	chr.chr_ai.type.who = "-1";
	chr.chr_ai.type.timewait = "0";
	chr.chr_ai.type.locator = "stay";
	chr.chr_ai.type.wait = 5.0;
	LAi_tmpl_stay_InitTemplate(chr);
	//��������� �������� ���������
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//��������������� ���� ���������
void LAi_type_barman_CharacterUpdate(aref chr, float dltTime)
{	
	float time, tw;
	chr.chr_ai.type.wait = stf(chr.chr_ai.type.wait) - dltTime;
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
	{
		chr.chr_ai.type.time = "0";
		chr.chr_ai.type.who = "-1";
		chr.chr_ai.type.timewait = "1";
		return;
	}
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY)
	{
		//������� ������ ���������� ����������
		int num = FindNearCharacters(chr, 3.0, -1.0, -1.0, 0.001, false, true);
		if(num > 0)
		{
			if(LAi_type_barman_FindEnemy(chr, num) < 0)
			{
				for(int i = 0; i < num; i++)
				{
					if(nMainCharacterIndex == sti(chrFindNearCharacters[i].index))
					{					
						//����� ��, ���������, �� � ������� ��.						
						if (bMainCharacterInBox && chr.chr_ai.type.state != "afraid")
						{
							if (chr.sex == "man") chr.greeting = "VOICE\Russian\soldier_arest_1.wav";
							else chr.greeting = "VOICE\Russian\Gr_Woman_Citizen_11.wav";
							chr.dialog.currentnode = chr.sex  + "_FackYou";
							LAi_SetActorTypeNoGroup(chr); //�������� �����, ����� �������� ������� �� ������. ������ ��� ��� � � ���� ���� - �������. 
							LAi_ActorDialog(chr, pchar, "", 0.0, 0);
							return;
						}
					}
				}				
				int ichr = sti(chrFindNearCharacters[0].index);
				bool isTrp = true;
				if(IsEntity(&Characters[ichr]))
				{
					if(SendMessage(&Characters[ichr], "ls", MSG_CHARACTER_EX_MSG, "IsFightMode") != 0)
					{
						isTrp = false;
					}
				}else{
					isTrp = false;
				}
				if(CheckAttribute(&Characters[ichr], "chr_ai.type"))
				{
					if(Characters[ichr].chr_ai.type == LAI_TYPE_WAITRESS)
					{
						isTrp = false;
						//�������� � ����������
						if(rand(100) == 55)
						{
							LAi_CharacterPlaySound(chr, "barman_wtrs");
						}
					}
				}
				if(isTrp)
				{
					//�������� � ����������
					time = stf(chr.chr_ai.type.time);
					time = time + dltTime;
					chr.chr_ai.type.time = time;
					if(stf(chr.chr_ai.type.who) != ichr)
					{
						chr.chr_ai.type.time = "0";
						chr.chr_ai.type.who = ichr;
					}
					tw = stf(chr.chr_ai.type.timewait);
					tw = tw + dltTime;
					chr.chr_ai.type.timewait = tw;
					if(time < 60.0)
					{
						if(tw > 6.0)
						{
							if(rand(100) < 30)
							{
								//�������� ����� ����������� �����������
								LAi_type_barman_Ask(chr);
								chr.chr_ai.type.timewait = "0";
								CharacterTurnByChr(chr, &Characters[ichr]);
							}
						}
					}else{
						LAi_type_barman_RestoreAngle(chr);
						LAi_type_barman_PlayWaitAni(chr);
						if(time > 200.0)
						{
							chr.chr_ai.type.time = "0";					
						}				
					}
				}else{
					if(rand(100) < 10) LAi_type_barman_PlayWaitAni(chr);
				}
			}else{
				//������
				chr.chr_ai.type.state = "afraid";
				LAi_tmpl_ani_PlayAnimation(chr, "afraid", -1.0);
				LAi_SetAfraidDead(chr);
				LAi_type_barman_RestoreAngle(chr);
			}
		}else{
			chr.chr_ai.type.time = "0";
			chr.chr_ai.type.who = "-1";
			chr.chr_ai.type.timewait = "1";
			LAi_type_barman_RestoreAngle(chr);
			LAi_type_barman_PlayWaitAni(chr);
			if(rand(100) > 90)
			{
				LAi_type_barman_SetGoto(chr);
			}
		}
	}else{
		if(chr.chr_ai.tmpl != LAI_TMPL_ANI)
		{
			chr.chr_ai.type.time = "0";
			chr.chr_ai.type.who = "-1";
			chr.chr_ai.type.timewait = "3";
		}else{
			//������� ������ ���������� ����������
			time = stf(chr.chr_ai.type.time);
			num = FindNearCharacters(chr, 4.5, -1.0, -1.0, 0.001, false, false);
			if(num > 0)
			{
				if(LAi_type_barman_FindEnemy(chr, num) < 0) num = 0;
			}
			if(num <= 0)
			{
				if(chr.chr_ai.type.state == "afraid")
				{
					LAi_SetDefaultDead(chr);
					LAi_type_barman_SetGoto(chr);
				}
			}else{
				LAi_SetAfraidDead(chr);
			}
		}
	}
}

//�������� ��������� � �������
bool LAi_type_barman_CharacterLogin(aref chr)
{
	return true;
}

//�������� ��������� �� �������
bool LAi_type_barman_CharacterLogoff(aref chr)
{
	return true;
}

//���������� ������ ���������
void LAi_type_barman_TemplateComplite(aref chr, string tmpl)
{
	switch(chr.chr_ai.type.state)
	{
	case "waiting":
		LAi_tmpl_stay_InitTemplate(chr);
		chr.chr_ai.type.state = "stay";
		break;
	case "goto":
		//����� ����� �������
		LAi_type_barman_SetAfterGoto(chr);
		break;
	case "work":
		LAi_type_barman_SetGoto(chr);
		break;
	case "stay":
		LAi_tmpl_stay_InitTemplate(chr);
		break;
	}
}

//�������� � ������� ������� ������
void LAi_type_barman_NeedDialog(aref chr, aref by)
{
}

//������ �� ������, ���� ���������� true �� � ���� ������ ����� ������ ������
bool LAi_type_barman_CanDialog(aref chr, aref by)
{
	//���������� �� ������
	if(chr.chr_ai.type.state == "afraid") return false;
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY || chr.chr_ai.tmpl == LAI_TMPL_GOTO || chr.chr_ai.tmpl == LAI_TMPL_ANI) return true;
	return false;
}

//������ ������
void LAi_type_barman_StartDialog(aref chr, aref by)
{
	//���� �� �������, ��������� ������ ��� ������� ����������
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//��������� ������
void LAi_type_barman_EndDialog(aref chr, aref by)
{
	if(chr.chr_ai.type.state == "goto")
	{
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, "barmen", chr.chr_ai.type.locator, 600.0);
	}else{
		LAi_tmpl_stay_InitTemplate(chr);
		LAi_CharacterRestoreAy(chr);
	}
}

//�������� ���������
void LAi_type_barman_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{

}


//�������� ��������
void LAi_type_barman_Attacked(aref chr, aref by)
{
	
}

//��������� �������� ��������� �����������
void LAi_type_barman_Ask(aref chr)
{
	//�������� ��������
	string animation;
	switch(rand(3))
	{
	case 0:
		animation = "dialog_stay2";
		break;
	case 1:
		animation = "dialog_stay3";
		break;
	case 2:
		animation = "dialog_stay4";
		break;
	case 3:
		animation = "dialog_stay5";
		break;
	}
	LAi_tmpl_ani_PlayAnimation(chr, animation, 4.0 + frand(3.0));
	//�������� ������������� ����
	LAi_CharacterPlaySound(chr, "barman");
}

//��������������� �� �������� ��������
void LAi_type_barman_RestoreAngle(aref chr)
{
	CharacterTurnByLoc(chr, "barmen", chr.chr_ai.type.locator);
}

//����� �����
int LAi_type_barman_FindEnemy(aref chr, int num)
{
	if(LAi_grp_alarmactive == true)
	{
		for(int i = 0; i < num; i++)
		{
			int idx = sti(chrFindNearCharacters[i].index);
			if(LAi_group_IsEnemy(chr, &Characters[idx])) return idx;
		}
	}
	return -1;
}

//� ������� ������������ ��������� �������� ������������� �� ����
void LAi_type_barman_PlayWaitAni(aref chr)
{
	if(chr.chr_ai.type.state != "stay") return;
	if(rand(100) > 20) return;
	if(stf(chr.chr_ai.type.wait) > 0.0) return;
	//������ �������� �� ������
	chr.chr_ai.type.state = "waiting";
	float wait = 20.0;
	LAi_tmpl_ani_PlayAnimation(chr, "Barman_look_around", wait);
	chr.chr_ai.type.wait = wait;
}

//��������� ������� � ������ �������
void LAi_type_barman_SetGoto(aref chr)
{
	if(chr.chr_ai.type.locator == "stay")
	{
		if(rand(100) < 50)
		{
			chr.chr_ai.type.locator = "bar1";
		}else{
			chr.chr_ai.type.locator = "bar2";
		}
	}else{
		chr.chr_ai.type.locator = "stay";
	}
	LAi_tmpl_goto_InitTemplate(chr);
	LAi_tmpl_goto_SetLocator(chr, "barmen", chr.chr_ai.type.locator, 600.0);
	chr.chr_ai.type.state = "goto";
}

//���������� ������� ����� ������� � �������
void LAi_type_barman_SetAfterGoto(aref chr)
{
	LAi_type_barman_RestoreAngle(chr);
	bool isSet = false;
	switch(chr.chr_ai.type.locator)
	{
	case "bar1":
		chr.chr_ai.type.state = "work";
		LAi_tmpl_ani_PlayAnimation(chr, "Barman_idle", 5.0 + frand(3.0));
		if(rand(100) < 30)
		{
			LAi_CharacterPlaySound(chr, "barman_do");
		}
		isSet = true;
		break;
	case "bar2":
		chr.chr_ai.type.state = "work";
		LAi_tmpl_ani_PlayAnimation(chr, "Barman_idle", 5.0 + frand(3.0));
		if(rand(100) < 30)
		{
			LAi_CharacterPlaySound(chr, "barman_wtrs");
		}
		isSet = true;
		break;
	}
	if(!isSet)
	{
		LAi_tmpl_stay_InitTemplate(chr);
		chr.chr_ai.type.state = "stay";
	}
}
