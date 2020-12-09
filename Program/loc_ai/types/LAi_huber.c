/*
���: ����������, �������� �� �������, ������� �� ������

	������������ �������:
		stay
		dialog
*/



#define LAI_TYPE_HUBER		"huber"


//�������������
void LAi_type_huber_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_HUBER;
	LAi_tmpl_stay_InitTemplate(chr);
	//��������� �������� ���������
	LAi_SetHuberSitAnimation(chr);
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//��������������� ���� ���������
void LAi_type_huber_CharacterUpdate(aref chr, float dltTime)
{	
	int num;
	float locx, locy, locz;
	if (CheckAttribute(chr, "standUp") && !LAi_IsCapturedLocation) //�� ��� ������� �������
	{
		num = FindNearCharacters(chr, 15.0, -1.0, -1.0, 0.01, false, false);
		int iNumEnemy = LAi_type_huber_FindEnemy(chr, num);
		if (iNumEnemy > 0) //���� �����
		{
			GetCharacterPos(chr, &locx, &locy, &locz);			
            Pchar.quest.MayorSitBack.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.MayorSitBack.win_condition.l1.location = pchar.location;
            Pchar.quest.MayorSitBack.function = "MayorSitBack";
			Pchar.quest.MayorSitBack.mayorId = chr.id;
			Pchar.quest.MayorSitBack.locationName = chr.location;
			Pchar.quest.MayorSitBack.locatorName = chr.location.locator;
			EquipCharacterByItem(chr, FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE));
			EquipCharacterByItem(chr, FindCharacterItemByGroup(chr, GUN_ITEM_TYPE));
			LAi_SetWarriorTypeNoGroup(chr); //���������� � ������ �� �����
			ChangeCharacterAddressGroup(chr, chr.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_group_Attack(chr, &characters[iNumEnemy]);
			if (CheckAttribute(chr, "standUp.exitDisable")) chrDisableReloadToLocation = true;
		}
	}
	//�������� ��������� �� � �����
	if (CheckAttribute(chr, "watchBoxes")&& chr.chr_ai.tmpl != LAI_TMPL_DIALOG) 
	{
		num = FindNearCharacters(chr, 10.0, -1.0, 180.0, 0.01, true, true);
		for(int i = 0; i < num; i++)
		{
			if(nMainCharacterIndex == sti(chrFindNearCharacters[i].index))
			{					
				//����� ��, ���������, �� � ������� ��.						
				if (bMainCharacterInBox)
				{
					//�������� �� ����� ����
					GetCharacterPos(chr, &locx, &locy, &locz);	
					LAi_SetWarriorTypeNoGroup(chr); //���������� � ������ �� �����
					ChangeCharacterAddressGroup(chr, chr.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
					LAi_group_Attack(chr, pchar);
					if (CheckAttribute(chr, "watchBoxes.exitDisable")) chrDisableReloadToLocation = true;
				}
			}
		}
	}
	if(chr.chr_ai.tmpl != LAI_TMPL_DIALOG)
	{
		if(rand(1000) == 313)
		{
			LAi_CharacterPlaySound(chr, "governor");
		}
	}
}

//�������� ��������� � �������
bool LAi_type_huber_CharacterLogin(aref chr)
{
	return true;
}

//�������� ��������� �� �������
bool LAi_type_huber_CharacterLogoff(aref chr)
{
	return true;
}

//���������� ������ ���������
void LAi_type_huber_TemplateComplite(aref chr, string tmpl)
{
	LAi_tmpl_player_InitTemplate(chr);
}

//�������� � ������� ������� ������
void LAi_type_huber_NeedDialog(aref chr, aref by)
{
}

//������ �� ������, ���� ���������� true �� � ���� ������ ����� ������ ������
bool LAi_type_huber_CanDialog(aref chr, aref by)
{
	//���� ��� �������, �� �������
	if(chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	//���������� �� ������
	return true;
}

//������ ������
void LAi_type_huber_StartDialog(aref chr, aref by)
{
	//���� �� �������, ��������� ������ ��� ������� ����������
	//LAi_tmpl_stay_InitTemplate(chr);
	LAi_tmpl_SetActivatedDialog(chr, by);
	//LAi_tmpl_dialog_NoAni(chr);
	chr.chr_ai.tmpl.firstAnim = 1;
}

//��������� ������
void LAi_type_huber_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_SetHuberSitAnimation(chr);
}

//�������� ���������
void LAi_type_huber_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//�������� ��������
void LAi_type_huber_Attacked(aref chr, aref by)
{
	
}

//����� �����
int LAi_type_huber_FindEnemy(aref chr, int num)
{
	if(num <= 0) return -1;
	int i, idx;
	if(LAi_grp_playeralarm > 0)
	{
		for(i = 0; i < num; i++)
		{
			idx = sti(chrFindNearCharacters[i].index);
			if(LAi_group_IsEnemy(chr, &Characters[idx])) return idx;
		}
	}
	else
	{		
		for(i = 0; i < num; i++)
		{
			idx = sti(chrFindNearCharacters[i].index);
			if(LAi_CheckFightMode(&Characters[idx])) return idx;
		}
	}
	return -1;
}

