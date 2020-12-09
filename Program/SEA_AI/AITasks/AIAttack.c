// Set task attack for SeaAI 
void AIAttack_GroupAttack(string sGroupAttacker, string sGroupAttacked, bool bAttackedTask)
{
	ref rG1 = Group_GetGroupByID(sGroupAttacker);
	ref rG2 = Group_GetGroupByID(sGroupAttacked);

	//float fHP1 = Group_GetPowerHP_R(rG1);
	//float fHP2 = Group_GetPowerHP_R(rG2);

	//float fHPRatio1 = fHP1 / (fHP2 + 0.0001);
	//float fHPRatio2 = fHP2 / (fHP1 + 0.0001);  //to_do

	//string sGroupType1 = Group_GetTypeR(rG1);
	string sGroupType2 = Group_GetTypeR(rG2);

    //fix ������� - �������� -->
    if (!CheckAttribute(rG1, "Task")) { return; }
    //fix ������� - �������� <--
    
	// check for already attack
	if (sti(rG1.Task) == AITASK_ATTACK)
	{
		if (rG1.Task.Target != sGroupAttacked) { return; }
		//return;
	}
	// ====================================================== set attack task to ships
	if (sGroupAttacker != PLAYER_GROUP)
	{
		int iIndex = 0;

		int iCharactersNum2 = Group_GetCharactersNumR(rG2);
		int iDeadCharactersNum2 = Group_GetDeadCharactersNumR(rG2);
		int iCharactersNum1 = Group_GetCharactersNumR(rG1) - Group_GetDeadCharactersNumR(rG1); //���-�� ����� �������� � ��������� ������

		// find targets for rG1
		if (iCharactersNum2 != iDeadCharactersNum2 && iCharactersNum2 > 0)
		{
			int i = 0;
			while (true)
			{
				int iCharacterIndex = Group_GetCharacterIndexR(rG1, i); i++;
				if (iCharacterIndex < 0) { break; }
				//SetCharacterRelationBoth(sti(rCharacter2.index), iCharacterIndex, RELATION_ENEMY);
				if (LAi_IsDead(&Characters[iCharacterIndex])) { continue; }

				int iCharacterVictim = -1;
				while (iCharacterVictim < 0)
				{
					iCharacterVictim = Group_GetCharacterIndexR(rG2, iIndex); 
					if (iCharacterVictim < 0) { iIndex = 0; continue; }
					if (LAi_IsDead(&Characters[iCharacterVictim])) { iCharacterVictim = -1; }
					iIndex++;
				}
                if (CheckAttribute(&Characters[iCharacterIndex], "ShipTaskLock"))  { continue; } // boal eddy
				//eddy. ����� ���� ���� ���������. 
				if (CheckAttribute(&Characters[iCharacterIndex], "AnalizeShips"))
				{
					//���� ������ ��� ������ �� ����� - �� ���������� ����, � ��������� � �� �� �����
					if (CheckAttribute(&Characters[iCharacterIndex], "Tmp.fWatchFort.Qty") && sti(Characters[iCharacterIndex].Tmp.fWatchFort.Qty) == 200)
					{
						Characters[iCharacterIndex].Tmp.fWatchFort = 199; //��������� ������ � �� �������� ����
						Characters[iCharacterIndex].Ship.LastBallCharacter = iCharacterVictim;
					}
					else
					{	
						//����� �� ��� ���
						if (stf(Characters[iCharacterIndex].ship.hp) > (stf(Characters[iCharacterVictim].ship.hp) / 2) || GetCrewQuantity(&Characters[iCharacterIndex]) > GetCrewQuantity(&Characters[iCharacterVictim]))
						{	//���� ���� ���� ��������, �� �������� �������������� ����������� - �� ����� �� ������� �������
							if (((iCharactersNum2 - iDeadCharactersNum2) / iCharactersNum1) >= 2.0 && sti(RealShips[sti(characters[iCharacterIndex].ship.type)].Class) > sti(RealShips[sti(characters[iCharacterVictim].ship.type)].Class))
							{							
								Ship_SetTaskRunaway(SECONDARY_TASK, iCharacterIndex, iCharacterVictim);								
							}
							else
							{
								Ship_SetTaskAttack(SECONDARY_TASK, iCharacterIndex, iCharacterVictim);
							}
						}
						else
						{	//���� ���������� ������, �� ��������� - � �� ����� �� �� �� ����������
							if ((iCharactersNum1 / (iCharactersNum2 - iDeadCharactersNum2)) >= 2.2)
							{
								Ship_SetTaskAttack(SECONDARY_TASK, iCharacterIndex, iCharacterVictim);
							}
							else
							{
								Ship_SetTaskRunaway(SECONDARY_TASK, iCharacterIndex, iCharacterVictim);
							}
						}
					}
				}
				else
				{
					Ship_SetTaskAttack(SECONDARY_TASK, iCharacterIndex, iCharacterVictim);
				}
				// boal ��� ��� ������, ����� �� ������� SetCharacterRelationBoth(iCharacterVictim, iCharacterIndex, RELATION_ENEMY); //fix
			}	
		}
	}
	// ====================================================== set attack task to ships
	bool bTaskLock = false;

	if (sGroupAttacked == PLAYER_GROUP) { return; }
	if (!bAttackedTask) { return; } 

	if (Group_isTaskLockR(rG2)) 
	{ 
        //fix ������� - �������� -->
	    if (!CheckAttribute(rG2, "Task")) { return; }
	    //fix ������� - �������� <--
		if (sti(rG2.Task) != AITASK_ATTACK) { return; }
		if (rG2.Task.Target != sGroupAttacker) { return; }

		bTaskLock = true;
	}

	/*float fTmp = fHPRatio2;// * Clampf(fLeadership + 0.01);

	int iTask = AITASK_ATTACK;
	if (!bTaskLock) iTask = AIAttack_SelectTask(sGroupType2, fTmp);
	switch (iTask)
	{
		case AITASK_ATTACK:
			Group_SetTaskAttackEx(sGroupAttacked, sGroupAttacker, false);
		break;
		case AITASK_RUNAWAY:
			Group_SetTaskRunaway(sGroupAttacked, sGroupAttacker);
		break;
	}  */
	// �������� �� ������� �������, ������� ����� ��� � ������ �� ������, � �� �������
	Group_SetTaskAttackEx(sGroupAttacked, sGroupAttacker, false);
}

int AIAttack_SelectTask(string sGroupType, float fRatio)
{
	return AITASK_ATTACK; // boal ��� ������ ������ �� ���, ������ �� ����� � ������ �������, ���� �� �������
	/*
	int iTask = AITASK_RUNAWAY;
	switch (sGroupType)
	{
		case "war":
			if (fRatio > 0.8) iTask = AITASK_ATTACK;
		break;
		case "trade":
			if (fRatio > 1.5) iTask = AITASK_ATTACK;
		break;
		case "pirate":
			if (fRatio > 0.7) iTask = AITASK_ATTACK;
		break;
	}
	return iTask;
	*/
}

// check attack task for Group
void AIAttack_CheckTask(string sGroupID)
{
	ref rG1 = Group_GetGroupByID(sGroupID);
	ref rG2;
    
	string sGroupType1 = Group_GetTypeR(rG1);

	ref rCharacter1 = Group_GetGroupCommanderR(rG1);

	// skip if group is player group
	if (sGroupID == PLAYER_GROUP) { return; }

	// if group task is lock, check for task complete, if not - continue task
	float fAng = frnd() * PIm2;
	
	// boal �������� �� ������� ����� (������ �� �������� �����) -->
	string rG2name = "none_group_1"; // ��� ����� ������
	if (CheckAttribute(rG1, "Task.Target"))
	{
        rG2name = rG1.Task.Target;
	}
	if (Group_isDead(rG2name))
	{
		switch (sGroupType1)
		{
			case "trade":
			    if (CheckAttribute(rG1, "Task.Target.Pos.x")) // boal bug fix  TO_DO ������ ��� ���������?
				{
					Group_SetTaskMove(sGroupID, stf(rG1.Task.Target.Pos.x), stf(rG1.Task.Target.Pos.z));
				}
				else
				{
				    Group_SetTaskMove(sGroupID, 10000.0 * sin(fAng) , 10000.0 * cos(fAng));
				}
			break;
			case "war":
				Group_SetTaskMove(sGroupID, 10000.0 * sin(fAng) , 10000.0 * cos(fAng));
			break;
			case "pirate":
				Group_SetTaskMove(sGroupID, 10000.0 * sin(fAng) , 10000.0 * cos(fAng));
			break;
		}
		// find new task
		return;
	}
    // boal �������� �� ������� ����� (������ �� �������� �����) -->
    rG2 = Group_GetGroupByID(rG1.Task.Target);
    // boal �������� �� ������� ����� (������ �� �������� �����) <--
	/*if (!Group_isTaskLockR(rG1))
	{
		// to_Do ������������ ������ - ������ �� �������� 
		float fHP1 = Group_GetPowerHP_R(rG1);
		float fHP2 = Group_GetPowerHP_R(rG2);
		float fAHP1 = Group_GetAttackHPDistance_R(rG1, 300.0);

		float fAHPRatio1 = fHP1 / (fAHP1 + 0.0001);
		float fHPRatio1 = fHP1 / (fHP2 + 0.0001);

		float fTmp = fAHPRatio1;// * Clampf(fLeadership + 0.01);

		switch (AIAttack_SelectTask(sGroupType1, fTmp))
		{
			case AITASK_RUNAWAY:
				Group_SetTaskRunaway(sGroupID, rG1.Task.Target);
				return;
			break;
		}
	}  */

	// check attack task for dead targets
	int iIndex = 0;

	int iCharactersNum2 = Group_GetCharactersNumR(rG2);

	// find targets for rG1
	int i = 0;
	// navy -->
	bool isDead = false;
	int  newCommanderIndex = -1;
	int iCharacterIndex;
	// navy <--
	//#20190421-01 fix
	int nChar1Idx = -1;
	if(CheckAttribute(rCharacter1, "index"))
        nChar1Idx = sti(rCharacter1.index);
    int nNumChar = Group_GetCharactersNumR(rG1);
	while (true)
	{
		iCharacterIndex = Group_GetCharacterIndexR(rG1, i);
		i++;
		if (iCharacterIndex < 0) { break; }
		ref rCharacter = GetCharacter(iCharacterIndex);
		if (LAi_IsDead(rCharacter))
		{
   			if (iCharacterIndex == nChar1Idx || nChar1Idx < 0) {isDead = true;} //navy
			continue;
		}
		if (iCharacterIndex != nChar1Idx) newCommanderIndex = iCharacterIndex; //navy

		if (CheckAttribute(rCharacter, "SeaAI.Task"))
		{
			if (sti(rCharacter.SeaAI.Task) != AITASK_ATTACK) { continue; }
			if (!LAi_IsDead(&Characters[sti(rCharacter.SeaAI.Task.Target)])) { continue; }
		}

		int iCharacterVictim = -1;
		while (iCharacterVictim < 0)
		{
			iCharacterVictim = Group_GetCharacterIndexR(rG2, iIndex); 
			if (iCharacterVictim < 0) { iIndex = 0; continue; }
			if (LAi_IsDead(&Characters[iCharacterVictim])) { iCharacterVictim = -1; }
			iIndex++;
		}
        if (CheckAttribute(&Characters[iCharacterIndex], "ShipTaskLock"))  { continue; } // boal eddy
		Ship_SetTaskAttack(SECONDARY_TASK, iCharacterIndex, iCharacterVictim);
	}
	if (isDead && newCommanderIndex != -1) Group_SetGroupCommander(sGroupID, Characters[newCommanderIndex].id); //navy
}
