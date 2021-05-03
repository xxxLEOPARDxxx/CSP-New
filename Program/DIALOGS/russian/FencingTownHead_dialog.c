
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "� ��� ���� ����� �������������?";
			link.l1 = "�-�... ���� ����� " + PChar.name + " " + PChar.lastname + ", � - ������� ����� ''" + PChar.Ship.Name + "''.";
			link.l1.go = "talk_1";
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			dialog.text = "��� ������, ������� " + PChar.name + " " + PChar.lastname + "?";
			link.l1 = "�������� �� ������ ������ ����������� ���������.";
			link.l1.go = "ArenaBattle_1";
			link.l2 = "�������� �� ���������������.";
			link.l2.go = "academy";
			link.l3 = "����� ������ �������� ���, " + NPChar.name + " " + NPChar.lastname + ". �� �������.";
			link.l3.go = "exit";
			NextDiag.TempNode = "meeting";
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////
		/////////// ��� �� ����� - ����������� ������� ������ ��� ������ ����������� ////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		case "ArenaBattle_1":
			if(GetCharacterItem(PChar, "ArenaBilet") > 0)
			{
				dialog.text = "�������, �� ���������� ����� � ���������� ������������.";
				link.l1 = "��-��, � �����.";
				link.l1.go = "exit";
				break;
			}
		
			if(CheckAttribute(PChar, "Arena"))
			{
				if(PChar.AcademyLand.Begin == true)
				{
					dialog.text = "��... �� �����, �� ��� �� ��������� ����������, � ������� �� ������� ������������.";
					link.l1 = "�-�-�, ��?.. � ����� ������, ��������� �����������.";
					link.l1.go = "exit";				
				}
				else
				{
					if(PChar.Arena == "Generate")
					{
						dialog.text = "���� ���� ����������, �� � ��������� ����� ��������� ��������� ��������.";
						link.l1 = "��, ���� ���������� ���. ���� ������ �� ���� ���������.";
						link.l1.go = "ArenaBattle_2";
						link.l2 = "��.. ������� �� ����������, �� ���, �������, ������ �� �� �����...";
						link.l2.go = "exit";
					}
					else
					{
						if(PChar.Arena == "Prepare")
						{
							dialog.text = "��... ��-�����, �������, �� ��� ������ ���� �� ����� ����������� - ���� �� ��� ������� ������������!";
							link.l1 = "��?.. �-�-�.. ��� ����!";
							link.l1.go = "exit";
						}
						else
						{
							dialog.text = "� ���������, ������� " + PChar.lastname + ", ���� ��������� �� ���������.";
							link.l1 = "����. �����, �� �������!";
							link.l1.go = "exit";
						}
					}
				}
			}
			else
			{
				dialog.text = "� ���������, ������� " + PChar.lastname + ", ���� ��������� �� ���������.";
				link.l1 = "����. �����, �� �������!";
				link.l1.go = "exit";
			}
		
		break;

		case "ArenaBattle_2":
			dialog.text = "������� ������� ������� � �������� ��� ���������� ���������� ������� �����?";
			link.l1 = "� �� � ������������� ������ ������� ��� ������ �� ������.";
			link.l1.go = "ArenaBattle_3";
			link.l3 = "���� ��� ��������, �� �������� �� ������ ����������� �� ����.";
			link.l3.go = "ArenaBattle_5";
		break;

		case "ArenaBattle_3":
			NextDiag.CurrentNode = "Meeting";
			DialogExit();
			LaunchArena(false);
		break;
		
		case "ArenaBattle_5":
			int iMoney = sti(PChar.Arena.ViewCost);
			dialog.text = "��... �������, � ���� ������������ ���� ����� �����������. �� " + iMoney + " �������, ����������.";
			
			if(sti(PChar.money) >= iMoney)
			{
				link.l1 = "� ��������. ��� ���, ���� " + iMoney + " �������.";
				link.l1.go = "ArenaBattle_6";
			}
			else
			{
				link.l1 = "�-��.. �������, �������� ����������� ��� �� �� �������. ����� � ������ ���.";
				link.l1.go = "exit";
			}
				
			link.l2 = "��� ���, ������� �� ����� �� ������ �������!";
			link.l2.go = "exit";
		break;
		
		case "ArenaBattle_6":
			AddMoneyToCharacter(PChar, -sti(PChar.Arena.ViewCost));
			GiveItem2Character(PChar, "ArenaBilet");
			dialog.text = "��� � ������. �������� ��� ������� - �������� ��� �����... ...(���������)...";
			link.l1 = "���. ���������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PrepareArenaOdds");
			PChar.Arena.Mode.NotOdd = true;
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////// ���������� ////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		case "academy":
			if(GetCharacterItem(PChar, "ArenaBilet") > 0)
			{
				dialog.text = "�������, �� ���������� ����� � ���������� ������������.";
				link.l1 = "��-��, � �����.";
				link.l1.go = "exit";
				break;
			}
			
			if(PChar.AcademyLand.Can == false)
			{
				if(PChar.AcademyLand.Begin == true)
				{
					dialog.text = "��... �� �����, �� ��� �� ��������� ���������� ����������...";
					link.l1 = "�-�-�, ��?.. � ����� ������, ��������� �����������.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "��... � ������ ������ � �� ���� ������������ ���� ����� ��� �����. ������� �����.";
					link.l1 = "��� �, ����.";
					link.l1.go = "exit";
				}
			}
			else
			{
				if(PChar.Arena != "Prepare")
				{
					dialog.text = "��... ����� ������ �� ������� ����������?";
					link.l1 = "������� ���������.";
					link.l1.go = "academy_land";
				}
				else
				{
					dialog.text = "��... ��-�����, �������, �� ��� ������� ������������! ��� ������ ���� �� �� ����������.";
					link.l1 = "��?.. �-�-�.. ��� ����!";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "academy_land":
			NextDiag.CurrentNode = "Meeting";
			DialogExit();
			LaunchAcademyLand();
		break;
		
		case "academy_sea":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		/////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////// ������ ������� ////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		case "talk_1":
			dialog.text = "��� ����������, �������. ����� ���� " + NPChar.name + " " + NPChar.lastname + ". ��.. ������ ������, �� ������ � ���. ��� �� ��� ���� �������, �������?";
			link.l1 = "��, ��� �������. ��� ����������� ����������� ����� ���������� ����������. ������ ������� � ����� ���� ��������� �����. ��, ��� ��� �� ���������?";
			link.l1.go = "talk_2";
		break;

		case "talk_2":
			dialog.text = "�-�, ��� ����� ������ �������, ������� ��� ������� ����������.. ��, ��������, ����� ����������... ���� �� �������� ������� �.";
			link.l1 = "��... ���-�� �� ����������.";
			link.l1.go = "talk_3";
		break;

		case "talk_3":
			dialog.text = "��������� ��� ����� �� ���� ������� ���� ������� ������������� ������� ������� �������. �������� ������� ��������������� ������� ������, ��� ������������� �������. \n ����� ������������� ����� ���� ���������, ������ ���� ���������� � ������������� ����� �������... �� �������� ������������ ������� ������ � ����������� � ������ ��������� � ��� �������������. ����������� ��� ���� �����, � ���� � ������� ����� ������� ���������... ������� ���� ��������� ������, ��� ���� ������� � ����. \n ����, ��� ������ ���� � ���� ��������� ����� ���� ��������� ������, �� ��� ���� ���������� ������ - � ��� ������ �� ���������� � ������� � ������� ��������, � ���������� ������� ��� ����������... ��� ��, ��� ������ ���� � ���� ��������� - ���������, �� ������� ���� ������ ��������.";
			link.l1 = "��-�... ��������� �������. �� ��� �� �� ����� �����������?";
			link.l1.go = "talk_4";
		break;

		case "talk_4":
			dialog.text = "������ ����� �������, ���� �� ���������� �� ������ ��������, ��� ����� ��������� ���� �� ����������� �������. ����������� �������� ���������� � ����������. �� �� �������� ��� ������� ��������� ��� ���������, � �����, ������� ��������, �� ����� ��������� ����������� ����������, � �� ��������� � ����, ������� ���� �� ������ � ������ � ���� ������� ����� � �����, ��������� ����������� �������� � ������� ������ ������� ��������� ��������� ����������. \n ������ ��� ������� �������� ����������� ������������ ���� �������, � � ����� ��������� ������ ����������� ����� �� ���� �������. ������ �����, � ������ ����� �������, ��� ���� �� �� �� ���������, �������������� � ���� - �������� ������ ����� � �� ����, � �� ���� ���������� �����, ������� �� ������� �������� � ����������� ��������, � �� ��� � ������ �� ����� ����� �����, ����������� ����� ����� ���������... \n ������ ����� ����� �� ������� ���������� ��������� ������� - �� ������ �� ����������� ��������, � ����� ����������� ������ ������. ����������� �� ������ ���� ��������, �� ���� �������� - ��� ������ ������ ������! �� � �������, �� ����� ������������ ��� ����� ��� ���������� ���� ����������. �� ��������� �����, ����������.";
			link.l1 = "����� ���������! �����, � ���� �� ��������������� ������ ��������.";
			link.l1.go = "meeting";
			NextDiag.TempNode = "meeting";
		break;
		// ������� ��� ������ ������� <--

		// �� ����� -->
		case "FightInArena_1":
			dialog.text = "����������� ����, ������� " + PChar.lastname + ". ���� ��������� ��������� � ��������� ����������\n ����� �������� � ��������� �������: �� ��� ����� ������ �� ����������. ����� �����!";
			link.l1 = "��������� �� ����������, " + NPChar.lastname + ".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaDuelTalkWithEnemy");
		break;
	
		case "FightInArena_2":
			switch(sti(PChar.Arena.Duel.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("�� ���������, ������� " + GetNameLugger(PChar, "f") + "! ��������, � ��������� ��� �� ��������� �������!", "����� ����, ��� �� ��������� �������, ������� " + GetNameLugger(PChar, "l") + ".", "��, ��� ������ ����-���� �� ������� �� ������! �� ��� �, �������� � ��������� ��� ��� ������ ������.");
					link.l1 = LinkRandPhrase("��.. �� �������.", "�� �� ����� ��� � ��� ����� �������?!", "�������� - ��� ���� �����!");
					link.l1.go = "exit";
					AddDialogExitQuestFunction("ArenaDuelTheEnd");
				break;
			
				case 1:
					dialog.text = LinkRandPhrase("�� ������� ���, ���! � ����� �� ���. �� ������ ���������� ���� �������. ���, ������ ��� " + sti(PChar.Arena.Duel.Prize) + " ������� �� ����� ����������� ���.", "��� �� ��� �������, �������! � ��� �� ����������� ������ �������! � ���������� ������ ����������. �� ��������� ���� " + sti(PChar.Arena.Duel.Prize) + " �������.", "�� ����� �������� ����, ��� ����� �������. ����������, ��� ���� " + sti(PChar.Arena.Duel.Prize) + " ������� � �������� �����.");
					link.l1 = LinkRandPhrase("���������! �� ������ ������.", "�������, ���������. ����������� ����� � ��������� ���.", "��-��!");
					link.l1.go = "exit";
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Duel.Prize));
					AddDialogExitQuestFunction("ArenaDuelTheEnd");
				break;
			}
		break;
	
		case "FightInArena_3":
			dialog.text = LinkRandPhrase("��-��-��! ����� ���������� � ��, ������� " + PChar.lastname + "! ���� �������� �������� �����������, ����� ����� �� ���� ������� � ������������ ������� �����������.", "�� ���, ����� � ������� � ��������� �����?", "��, ��� � ��, �������. ��-��, �� ��� � - ������� ����.");;
			link.l1 = LinkRandPhrase("� �� ����� ������.", "� �������� �� � ���������!", "��������� �������, ��������.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("StartArenaEtapsBattle");
		break;
	
		case "FightInArena_4":
			switch(sti(PChar.Arena.Etaps.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("��� ����� ���� �� ��������� ��� �� �����! �������� � ��������� ��� �� ��������� �������.", "��-�, �� ��� ���� �� ������� ���! ��-��-��!", "������ �� ���� ������ �������! �� �� ���� ��� �� �������. ��������� ���.");
					link.l1 = LinkRandPhrase("�� ��� � ��� ������ ����� �����! �� ����� ��������...", "��� �� ����� ���� ��������?! �� ������, � ��� �������! ��� �� � ���������...", "��� ������ �� �������!");
					link.l1.go = "exit";
					AddDialogExitQuestFunction("ArenaEtapsTheEnd");
				break;
			
				case 1:
					dialog.text = LinkRandPhrase("��� �� ��! ������ �� ����� ������! �� ������ ���������� ���� �������. ���, ������ ��� " + sti(PChar.Arena.Etaps.Prize) + " ������� �� ����� ����������� ���. ��������� ���.", "��-�, �� ������ � �� ��� ����� �����. �� �� ������� - �� ������ �������� ������ �� ��� � ����� ���������. ��� ��� ������� - " + sti(PChar.Arena.Etaps.Prize) + " �������.", "��� ���� �� ����������� �� ������ ������! ��� ��� ���� ����! ��� ��� ������� - " + sti(PChar.Arena.Etaps.Prize) + " �������.");
					link.l1 = LinkRandPhrase("���. ������ �� �� ����� ������� ����!", "�������� ��� ���� ������ ���� ������. ����������� ��� �����!", "� �� ����� ��� � ���� ����� ������ �������?!");
					link.l1.go = "exit";
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Etaps.Prize));
					AddDialogExitQuestFunction("ArenaEtapsTheEnd");
				break;
			}
		break;
	
		case "FightInArena_5":
			dialog.text = LinkRandPhrase("� ��� � ��, ������� " + PChar.name + " " + PChar.lastname + "! ��� �, �� ��� ��� ������� - ��� ��������� � ����� � ��� ������� ����������� ����, ����� ������ ��� ��� ������.", "����������� ���, ������� " + GetNameLugger(PChar, "f") + ". ��� ���� ����� ������ ������� - ��� � ��� ������. ��, ���� ��, �������, ������ ����� �������. ��-��!", "�������, ��� �� ������ ���� ���� ���������, ������� " + GetNameLugger(PChar, "l") + ".");
			link.l1 = LinkRandPhrase("������� ���� ����������, ��� � ��� ������� ������ � ������� �� ����!", "����� ��� �������� - ��� �� �������� ����-������ �������!", "���� ����� ���� - ���� �� ����������.");
			AddDialogExitQuestFunction("ArenaTournamentTalkWithRandEnemy");
		break;
	
	
		case "FightInArena_7":
			switch(sti(PChar.Arena.Tournament.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("��-�, ������ ������ �� �����! �� �������� ���������, �������! �� ����� ���� �� �� ����� �������. ����� ����� ��� ����� - ���� �����, � ��������� ��� �� ��������� �����������.", "� �������� �� ���, ���, � ��� ���� �� ���� �� ���������! ����.", "��, ��� �� �������. �������� �� ������ �� ���������.");
					link.l1 = LinkRandPhrase("������ � �������, ���, ��������... �� ��������.", "�������� ����������� ����������� ����� - � ���� ����������.", "�� ������, � ��� �������.");
					link.l1.go = "exit";
					AddDialogExitQuestFunction("ArenaTournamentTheEnd");
				break;
			
				case 1:
					dialog.text = LinkRandPhrase("��-�, ������ ������ �� �����. � �� ����� ��� �����������! ��������� ������, � �� ��� �������� ���� �� ����, ��� �� ������������ � �������! ������ ��� " + sti(PChar.Arena.Tournament.Money) + " ������� �� ����� ����������� ���.", "�������, �� - �������! ������ ������ ���������� � ������� �� ������� ���� ����� �������� ���������! �������� ��� ���� - ��� " + sti(PChar.Arena.Tournament.Money) + " �������.", "�� �� �� ���� ���� � ������� �� ���������! ��� ��� ������! ��� " + sti(PChar.Arena.Tournament.Money) + " ������� �� ����� ����.");
					link.l1 = LinkRandPhrase("������� �� �� ��� ����������!", "� ��� �� ��� ������, ��� ����� �������. � ������ - ��������.", "��-��-��, ������ ���������! ����� ���������� � �� �������� ������ ��� �����. ������, ����� ������� ��� ��������.");
					link.l1.go = "exit";
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Tournament.Money));
					
					pchar.questTemp.tournamentcount = sti(pchar.questTemp.tournamentcount) + 1;
					if(sti(pchar.questTemp.tournamentcount) >= 1) UnlockAchievement("AchTurnir", 1);
					if(sti(pchar.questTemp.tournamentcount) >= 3) UnlockAchievement("AchTurnir", 2);
					if(sti(pchar.questTemp.tournamentcount) >= 10) UnlockAchievement("AchTurnir", 3);
					
					AddDialogExitQuestFunction("ArenaTournamentTheEnd");
				break;
			}
		break;
		
		case "FightInArena_8":
			dialog.text = LinkRandPhrase("�-�, ��� � ��, ������� " + PChar.lastname + ". ��� ������ ��� ���. �������, ��� ��� ������� ������.", "�-�, ��� � ��, ������� " + PChar.lastname + ". ���� ������ ������ ���������� �������!", "�-�, ��� � ��, ������� " + PChar.lastname + ". �����, ��� ������� ����� ��������� � ��� �����, � �� ��� � ������� ���...") + " ������� ���� ����� - �������� �-�-�-�-� ���� ...(���������� �����)... � ����������� �� �����.";
			link.l1 = LinkRandPhrase("��� �� ����� - � �������� ������. ��� �������, � �������.", "����� ���� ��� ������� �� ��������.", "����������� ��� �������.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("StartArenaOddsContinue");
		break;
	
		case "FightInArena_9":
			switch(sti(PChar.Arena.Odds.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("��-�, ��� ���� ���-����! ��, � ���������, ���� ������ �� �������.. ����� ����� ��� ����� - ���� �����, � ��������� ��� �� ��������� ����� �������� � �������.", "�� ������� ��� �������, �������. �� ���� ������������! �-�..", "��� ���� ��� ������ � ����, ����� �������� ��� ���� �����. �� �� �������.");
					link.l1 = LinkRandPhrase("� ��� �� �����!! ����� ��� ������!", "��, �� ������. �� �� �����, ��� �� ��� ������, ����� ��� ��� ������...", "�� ������, � ��� ������ ���, ���� ������!");
					link.l1.go = "exit";
					AddDialogExitQuestFunction("ArenaOddsTheEnd");
				break;
			
				case 1:
					dialog.text = LinkRandPhrase("��-�, ��� ���� ���-����! ����� ����, ���� ������ ������� � ������ ��� " + sti(PChar.Arena.Odds.Prize) + " ������� �� ����� ����������� ���. ������� �����, � ��� ������� ������ � ������ ���������, ��, ������, � ��� ������� ���� ���� � ����������� ���...", "��� ��� ��! ����� �� ��������� ������ ���� �������, � �� ������ ����� ������� ����������! �����, �����! ��� ���� " + sti(PChar.Arena.Odds.Prize) + " ������� � �������� ��������.", "�� �� ������� � ������! ��� ����������� � ����������� ��� ���������! ��� ��� ��! ����� �� ��������� ������ ���� �������, � �� ������ ����� ������� ����������! �����, �����! ��� ���� " + sti(PChar.Arena.Odds.Prize) + " �������!");
					link.l1 = LinkRandPhrase("��-��, ����� ���� � ���.", "�� ���, ���������� �� ��������. ������� ������ ������� � ������.", "���������. ����������� ���� �������.");
					link.l1.go = "exit";
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Odds.Prize));
					AddDialogExitQuestFunction("ArenaOddsTheEnd");
				break;
			}
		break;
	
		case "FightInArena_10":
			
			dialog.text = LinkRandPhrase("� ��� � ��, " + PChar.name + " " + PChar.lastname + "! ����� ���������� �� ���� ��������. �������, ��� ���������� ���� �����������.", "�����������, ���. ������� � ��� ���������� ����� ��������� ��������.", "� ������, ��� ���������� ���� �����������.") + " ������� ���� ����� - �������� �-�-�-�-� ���� ...(���������� �����)... � ����������� �� �����.";
			link.l1 = LinkRandPhrase("� ���� ��� ��������� �����. � ������������� ����� ��� �����.", "�������, ����� �������� ��������� ��������, � �� ��������� �����.", "�����, ������� ��� ��� �����������.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("StartArenaOddsContinue");
		break;
	
		case "FightInArena_11":
			dialog.text = LinkRandPhrase("��-�, �������� ���� �������! � �� ������� ����������� ������� ���� ����� ���������� � �������. ����� ���� ��������� �������. � ����, �� ����� ���������!", "��-�, ������ ���� �� �������� - ����� ����� ��������, ����� ������!", "��� �� ���� �� ������������� � ����� ������������.");
			link.l1 = LinkRandPhrase("��� �� ������ ��� ��� ����������� ��������. �������, � �� ��������.", "��, ��� ����� ��� ����. � ������������� ��� ��� ����� ����.", "����! � ��������� ��� ��� ���������� � ���� ������������ - ����� ���������, ��� ����� ��������� ��������.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaOddsTheEnd");
		break;
	
		case "EnemyFightInArena_1":
			dialog.text = LinkRandPhrase("�� ���, ����� ������ ���� ������ ���? ���-�� ������� ������ ���������.", "�� � ����� ���� � ������, ������ ���������!", "����������� ���� �� � ���, ���������!");
			link.l1 = LinkRandPhrase("���. �� ���������, ��� ����. ��������� � ����.", "������ ���� �����, ������ �����. ������ � ���� �� ������ ����.", "��-��, ������ ���������, ��� �� ��� ���� �� � ���.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaDuelStartBattleWithEnemy");
		break;
	
		case "FightInArena_6":
			dialog.text = RandSwear() + " " + LinkRandPhrase("� ������� �� ���� ���� ��� ������ �������!", PChar.name + " " + PChar.lastname + "?! � ����� ���� �� �����, ���� �� ������ � ���� �� ����!", "��, ��! ������ �� ���������, ��� ������ ����!");
			link.l1 = LinkRandPhrase("������ �� ����� ������ �� � ���!", "��-��, ������ ��������� ����� �� ���� �������?", "������ � ����...");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaTournamentGo");
		break;
		// �� ����� <--
		
		//--------------------------------- ����� ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("� ������ ������� �������. ������, � ��� ���� ������� �� ������...", "�� �� �� ����� �� ������� ��� ��������� ������?.. �� ���, �������!!!", "� ���� ������ �� �� �������. ���� ������� ��������� ������ �������� ����� ��� �����!"), 
					LinkRandPhrase("��� ���� �����, �������?! ��������� ������ ��� ����� ���� ����, ������ ���� �� ����, ������� �����!", "������� ������! ������!!!", "� �� ����� ����, ��������! ����� ���� ������� � ����� �����, ������ ���� �� ����..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("������, ���� ���� �������...", "���, � �� ������� �� �������� ������ ��������� " + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("����������� � ��!", "���, ���� ���� �������� ��������� ������..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "� ���� �����������. � ������ ��� ������, ���������� ��� ���...";
					link.l1 = "���!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "��� ���� ���� � ���� ����, �������?! ��� ���� ������ ������, ����� �� ������� ������!";
					link.l1 = LinkRandPhrase("���, � ����� ���� �����!", "����� ��� ���� ������� ����...", "��, �������.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("��� �������������� ��� � ���� ����. �� �� ���� �� ���?", 
						"��� � ���� ��� ������?", 
						"��, ��� � ���� ������� ��� ���?",
						"��������, ���� � ��� �� �����, � ������� ��� ���� �� ����������...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("���, ������ ���������� �����, ���������� � ��������...", 
						"�� ���, ����� ���������...",
						"������...", 
						"������, ��� �������.", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("��������, �� �� ������� ��������� � ���� ���� - ���� �� �����. � ����� ��� �������� ��� ���!", 
						"� ��� �������, ��� ����� �������. ����� ��� ����.", 
						"�� ���� ���������� ������, �� � ���������, ����� �� ���������� �������� ��� ���!",
						"���� ������, ��� ��� �����?! ������, ����!!!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("������, � �������...", 
						"��, ������...",
						"�����, �� ��������.", 
						"��������, ����� ����?!", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "�-�, ��������� ������������� - " + GetFullName(npchar) + ". �� ���� ��� ������, ������ �������������� ��� ������ ������ - �� ������ ����.";
			link.l1 = GetFullName(pchar) + ", � ������ ����������...";
			link.l1.go = "exit_setOwner";
		break;
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("�� �� ���, ��������! ������, ����� ���!!!", "��� ��� ��! ���� � ����������, � �� ����� � ������ � �������! ����� ����!!!", "������! ������!!! ����� ����!!!");
			link.l1 = "�-���, ������!!!";
			link.l1.go = "fight";
			link.l2 = "���� �� ������ ��� ���� ���� - ���� �����!..";
			link.l2.go = "FackYou_1";
			link.l3 = "�.. �.. � �� �����!..";
			link.l3.go = "FackYou_2";
		break;
		
		case "FackYou_1":	
			dialog.text = "���?.. �� �� ��������, � ��������... �������� � �������, ������ ���������!";
			link.l1 = "׸��!..";
			if(NPChar.sex == "man")
			{
				link.l1.go = "fight";
			}
			else
			{
				link.l1.go = "exit_setOwner3";
			}
		break;
		
		case "FackYou_2":			
			dialog.text = "������� ������... ��, ����� " + sti(PChar.StealItemsMoney) +  " ������� ����� ������ � ������ ��������� �� ��� ������ �������. ������ ���� ������, �� ����� ��� ����.";
			if(sti(PChar.money)>= sti(PChar.StealItemsMoney))
			{
				link.l1 = "������.. ��� ���� ������.";
				link.l1.go = "exit_setOwner2";
			}
			else
			{
				link.l2 = "�� � ���� ��� ����� �����... �������� ����..";
				link.l2.go = "FackYou_3";
			}
			link.l3 = "��� ���! � ������ ����� �� ��� ������!";
			
			if(NPChar.sex == "man")
			{
				link.l3.go = "fight";
			}
			else
			{
				link.l3.go = "exit_setOwner3";
			}
		break;
		
		case "FackYou_3":	
			dialog.text = "��� �� ������, ��� ���������?";
			link.l1 = "׸��!..";
			
			if(NPChar.sex == "man")
			{
				link.l1.go = "fight";
			}
			else
			{
				link.l1.go = "exit_setOwner3";
			}
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner2":
			AddMoneyToCharacter(PChar, -sti(PChar.StealItemsMoney));
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner3":
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
