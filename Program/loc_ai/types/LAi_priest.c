/*
���: �������, ������ �����, �������� �� �������, ������� �� ������. � ��� �� ������� � ������, ������� � ����������� 
�����������, ����� �� ��������� ������ "barmen" � ������ ������. ���� ���� ���� ��������.

	������������ �������:
		stay
		dialog
		goto
		ani
*/



#define LAI_TYPE_PRIEST		"priest"


//�������������
void LAi_type_priest_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_PRIEST;
	chr.chr_ai.type.state = "stay";
	chr.chr_ai.type.locator = "stay";
	chr.chr_ai.type.time = "0";
	chr.chr_ai.type.who = "-1";
	chr.chr_ai.type.timewait = "0";
	chr.chr_ai.type.afraid = "0";
	LAi_tmpl_stay_InitTemplate(chr);
	//��������� �������� ���������
	LAi_SetDefaultStayAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//��������������� ���� ���������
void LAi_type_priest_CharacterUpdate(aref chr, float dltTime)
{
	float time, tw;
	if(chr.chr_ai.tmpl == LAI_TMPL_ANI || chr.chr_ai.tmpl == LAI_TMPL_GOTO)
	{
		//chr.chr_ai.type.time = "0";
		chr.chr_ai.type.who = "-1";
		chr.chr_ai.type.timewait = "3";
		return;
	}
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY)
	{
		//������� ������ ���������� ����������
		time = stf(chr.chr_ai.type.time) + dltTime;
		chr.chr_ai.type.time = time;
		int num = FindNearCharacters(chr, 4.0, -1.0, -1.0, 0.001, false, true);
		if(num > 0)
		{
			if(LAi_type_priest_FindEnemy(chr, num) < 0)
			{
				int ichr = sti(chrFindNearCharacters[0].index);
				//�������� � ����������
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
							LAi_type_priest_Ask(chr);
							chr.chr_ai.type.timewait = "0";
							CharacterTurnByChr(chr, &Characters[ichr]);
						}
					}
				}else{
					LAi_type_priest_RestoreAngle(chr);
					if(time > 200.0)
					{
						chr.chr_ai.type.time = "0";					
					}				
				}
			}else{
				//������
				chr.chr_ai.type.afraid = "1";
				LAi_tmpl_ani_PlayAnimation(chr, "afraid", -1.0);
				LAi_SetAfraidDead(chr);
				LAi_type_priest_RestoreAngle(chr);
			}
		}else{
			//������ ������� ��������
			if(time > 4.0 && time < 15.0 && rand(100) < 10 && chr.chr_ai.type.locator == "stay")
			{
				LAi_CharacterPlaySound(chr, "priest_bead");
				LAi_tmpl_ani_PlayAnimation(chr, "bead", 5.0 + rand(15));
				chr.chr_ai.type.time = stf(chr.chr_ai.type.time) + 15.0;
			}
			else
			{
				LAi_type_priest_RestoreAngle(chr);
				if (time > 15.0) //���� � ������ �������
				{
					chr.chr_ai.type.time = "0";
					if (rand(100) > 60 || chr.chr_ai.type.locator == "bar1" || chr.chr_ai.type.locator == "bar2")
					{
						LAi_type_priest_SetGoto(chr);
						chr.chr_ai.type.who = "-1";
						chr.chr_ai.type.timewait = "1";
					}
				}
			}
		}
	}else{
		//������� ������ ���������� ����������
		time = stf(chr.chr_ai.type.time);
		num = FindNearCharacters(chr, 5.5, -1.0, -1.0, 0.001, false, false);
		if(num > 0)
		{
			if(LAi_type_priest_FindEnemy(chr, num) < 0) num = 0;
		}
		if(num <= 0)
		{
			chr.chr_ai.type.afraid = "0";
			LAi_SetDefaultDead(chr);
			LAi_tmpl_stay_InitTemplate(chr);
		}else{
			LAi_SetAfraidDead(chr);
		}
	}
}

//�������� ��������� � �������
bool LAi_type_priest_CharacterLogin(aref chr)
{
	return true;
}

//�������� ��������� �� �������
bool LAi_type_priest_CharacterLogoff(aref chr)
{
	return true;
}

//���������� ������ ���������
void LAi_type_priest_TemplateComplite(aref chr, string tmpl)
{
	switch(chr.chr_ai.type.state)
	{
	case "goto":
		//����� ����� �������
		LAi_type_priest_SetAfterGoto(chr);
		break;
	case "stay":
		LAi_tmpl_stay_InitTemplate(chr);
		break;
	}
}

//�������� � ������� ������� ������
void LAi_type_priest_NeedDialog(aref chr, aref by)
{
}

//������ �� ������, ���� ���������� true �� � ���� ������ ����� ������ ������
bool LAi_type_priest_CanDialog(aref chr, aref by)
{
	//���������� �� ������
	if(chr.chr_ai.type.afraid == "1") return false;
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	if(chr.chr_ai.tmpl == LAI_TMPL_ANI) return true;
	return false;
}

//������ ������
void LAi_type_priest_StartDialog(aref chr, aref by)
{
	//���� �� �������, ��������� ������ ��� ������� ����������
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//��������� ������
void LAi_type_priest_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
}


//�������� ���������
void LAi_type_priest_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{

}


//�������� ��������
void LAi_type_priest_Attacked(aref chr, aref by)
{
	
}

//��������� �������� ��������� �����������
void LAi_type_priest_Ask(aref chr)
{
	//�������� ��������
	string animation;
	switch(rand(2))
	{
	case 0:
		animation = "dialog_stay3";
		break;
	case 1:
		animation = "dialog_stay4";
		break;
	case 2:
		animation = "dialog_stay5";
		break;
	}
	LAi_tmpl_ani_PlayAnimation(chr, animation, -1.0);
	//�������� ������������� ����
	LAi_CharacterPlaySound(chr, "priest");
}

//��������������� �� �������� ��������
void LAi_type_priest_RestoreAngle(aref chr)
{
	CharacterTurnByLoc(chr, "barmen", chr.chr_ai.type.locator);
}

//����� �����
int LAi_type_priest_FindEnemy(aref chr, int num)
{
	if(LAi_grp_playeralarm > 0)
	{
		for(int i = 0; i < num; i++)
		{
			int idx = sti(chrFindNearCharacters[i].index);
			if(LAi_group_IsEnemy(chr, &Characters[idx])) return idx;
		}
	}
	return -1;
}

//��������� ���������� � ������ �������
void LAi_type_priest_SetGoto(aref chr)
{
	if(chr.chr_ai.type.locator == "stay")
	{
		chr.chr_ai.type.locator = "bar" + (rand(1)+1);
	}else{
		chr.chr_ai.type.locator = "stay";
	}
	LAi_tmpl_goto_InitTemplate(chr);
	LAi_tmpl_goto_SetLocator(chr, "barmen", chr.chr_ai.type.locator, 600.0);
	chr.chr_ai.type.state = "goto";
}

//���������� ������� ����� ������� � �������
void LAi_type_priest_SetAfterGoto(aref chr)
{
	//����������� �� ��������
	LAi_type_priest_RestoreAngle(chr);
	//�������
	LAi_tmpl_stay_InitTemplate(chr);
	chr.chr_ai.type.state = "stay";
}