														  
void ProcessDialogEvent() 
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
    int iTemp, i; // ����� ��� ���������� ����� ����� (�����)
	string attrName; // ����� ������ ��� ����������
	ref sld;

    switch(Dialog.CurrentNode)
	{
		case "exit":
			StopCoastalGuardPursuit();
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			LAi_SetPlayerType(Pchar);
		break;

		case "First time":			
			chrDisableReloadToLocation = false;
   			LAi_LockFightMode(pchar, false);
			dialog.text = RandPhraseSimple("�������, ����� ���������� ���-�� ����������.",
                                     "������ "+NationKingsName(npchar)+ ", ���������� ������� ����������!!!");
			Link.l1 = "���-���, ������. �� � �������� ������ �������� � ����.";
			if (makeint(Pchar.reputation) >= 70 && GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) >= 5)
			{
				Link.l1.go = "ThisTimeFree";
			}
			else
			{
				Link.l1.go = "IDontBelieveYou";
			}
			Link.l2 = "� ������ ������. ��� ����� ������� ���������� ��������?";
			if(makeint(Pchar.rank) >= 4 && GetSummonSkillFromNameToOld(Pchar, SKILL_COMMERCE) >= 5)
			{
				Link.l2.go = "GiveMeSomeMoneyToo";
			}
			else
			{
				Link.l2.go = "TryingToGiveBribe";
			}
			Link.l3 = "����������, ��������. ��� ���� �� ��������!";
			//#20181215-02
			bool bFencing = false;
			if(GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) >= 8)
                bFencing = true;
            if(!bFencing && GetSummonSkillFromNameToOld(Pchar, SKILL_F_LIGHT) >= 8)
                bFencing = true;
            if(!bFencing && GetSummonSkillFromNameToOld(Pchar, SKILL_F_HEAVY) >= 8)
                bFencing = true;
			if(makeint(Pchar.reputation) <= 25 && bFencing)
			{
				Link.l3.go = "GettingLostFromHere";
			}
			else
			{
				Link.l3.go = "howDareYou";
			}

		break;

		case "ThisTimeFree":
			dialog.snd = "Voice\COGU\COGU002";		
			dialog.text = "�� �������� ��� ������, ������� " + Pchar.name + "! � ��� ��� ��������, ��� ����� ������������� � ��������� ����� �������, ��� ��, �������� ������������!";
			Link.l1 = "���, ��� ��������� ������. �� � ��� �����������!";
			Link.l1.go = "ThisTimeFree_1";
			Link.l2 = "������ � ������ ���� ������!";
			Link.l2.go = "ThisTimeFree_fight";				
		break;

		case "ThisTimeFree_1":	
			dialog.snd = "Voice\COGU\COGU003";	
			ChangeCharacterReputation(pchar, -40);
			dialog.text = "��������� � ������ � ��� ������ �������, � ���� ��� � �������� ���. � ���� ��������� �� ���������!";
			Link.l1 = "��������� ���, ������. ����� ��� ��������!";
			Link.l1.go = "ThisTimeFree_exit";
		break;

		case "ThisTimeFree_fight":			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
    			attrName = "SoldierIDX"+i;
				sld = GetCharacter(sti(Pchar.quest.contraband.(attrName)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetRelation(pchar.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_ENEMY);
			LAi_group_SetHearRadius("CoastalGuards", 100.0);
			LAi_group_SetHearRadius(pchar.GenQuest.Smugglers_Group, 100.0);
			LAi_group_FightGroups("CoastalGuards", pchar.GenQuest.Smugglers_Group, true);
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);

			//LAi_SetPlayerType(Pchar);
            LAi_SetFightMode(Pchar, true);
			//trace("And we fight those soldiers!!" + Pchar.quest.contraband.CurrentPlace);
		break;

		case "ThisTimeFree_exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			
            DialogExit();
			StopCoastalGuardPursuit();
			ChangeContrabandRelation(pchar, -30);
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
    			attrName = "SoldierIDX"+i;
				sld = GetCharacter(sti(Pchar.quest.contraband.(attrName)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			LAi_group_SetRelation(pchar.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_ENEMY);			
			LAi_group_FightGroups(pchar.GenQuest.Smugglers_Group, "CoastalGuards", true);
			LAi_SetPlayerType(Pchar);
		break;

		case "IDontBelieveYou":
			dialog.snd = "Voice\COGU\COGU004";
			dialog.text = "��� �� ��� �������������! � �� ������! �������� �� ���� - �� ����������, � ����� �����������!";
			Link.l1 = "������, � ������ ��� �����!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "GiveMeSomeMoneyToo":	
			dialog.snd = "Voice\COGU\COGU005";		
			dialog.text = "��� ���? ���, �������, ��� ������� ���������� ����������... ���� ���, �������, ���� ����������. � �� ������� �� ��������?";
			Link.l1 = "�����, ��� " + makeint(sti(Pchar.money)/10) + " �������� ����� ����������.";
			if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/10))
			{
				Link.l1.go = "MoneyAccepted10";
			}
			else
			{
				Link.l1.go = "TryingToGiveBribe";
			}

			Link.l2 = "��� ������ " + makeint(sti(Pchar.money)/5) + " ��������?";
			if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/5))
			{
				Link.l2.go = "MoneyAccepted5";
			}
			else
			{
				Link.l2.go = "TryingToGiveBribe";
			}

			Link.l3 = "���, ������, � ����� ������ " + makeint(sti(Pchar.money)/2) + " ��������!";
			if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/2))
			{
				Link.l3.go = "MoneyAccepted2";
			}
			else
			{
				Link.l3.go = "TryingToGiveBribe";
			}
		break;

		case "TryingToGiveBribe":
			dialog.snd = "Voice\COGU\COGU006";
			dialog.text = "���, ����������� ������? ��� ��, ��� ����� ������� ������! �������� ��������� �� ����!";
			Link.l1 = "���������! ���� ��� ��������������, �� ���� �� �� ����-���� ������ �������!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "MoneyAccepted10":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "� �������� ����� ���� �������������. ��� �� �� ����������� ��������������������.";
			Link.l1 = "������ � ����� �������.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/10));
		break;
		
		case "MoneyAccepted5":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "� �������� ����� ���� �������������. ��� �� �� ����������� ��������������������.";
			Link.l1 = "������ � ����� �������.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/5));
		break;
		
		case "MoneyAccepted2":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "� �������� ����� ���� �������������. ��� �� �� ����������� ��������������������.";
			Link.l1 = "������ � ����� �������.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/2));
		break;

		case "GettingLostFromHere":
			dialog.snd = "Voice\COGU\COGU008";
			dialog.text = "��... ������... � �� ������ ��� ����������!";
			Link.l1 = "�����! �� ��� �����? ���� �������?";
			Link.l1.go = "GettingLostFromHere_1";
		break;

		case "GettingLostFromHere_1":
			dialog.snd = "Voice\COGU\COGU009";
			dialog.text = "�... � ���� ����������! � ����� ��� �� �������...";
			Link.l1 = "���!";
			Link.l1.go = "GettingLostFromHere_exit";
		break;

		case "GettingLostFromHere_exit":
			ChangeContrabandRelation(pchar, 10);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
            DialogExit();
            
			StopCoastalGuardPursuit();
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
                attrName = "SoldierIDX"+i;
                LAi_SetActorType(&Characters[sti(Pchar.quest.contraband.(attrName))]);
                LAi_ActorRunToLocation(&Characters[sti(Pchar.quest.contraband.(attrName))], "reload", "Reload1", "none", "", "", "", 40);
			}
			LAi_SetPlayerType(Pchar);
		break;

		case "howDareYou":
			dialog.snd = "Voice\COGU\COGU010";
			dialog.text = "�� ��, ������! ������ ���� ����� �� �����������. �� �� ���� ������ ��������!";
			Link.l1 = "�������� ��������� ����� � �����, ���������!";
			Link.l1.go = "ThisTimeFree_fight";
		break;
	}
}
