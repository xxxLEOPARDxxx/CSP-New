
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
			link.l1 = "�-�... ���� ����� " + GetFullName(pchar) + " , � - ������� ����� ''" + PChar.Ship.Name + "''.";
			link.l1.go = "talk_1";
			if (bBettaTestMode && !CheckAttribute(pchar,"ScamFanActive"))
			{
				link.l2 = "������� �������";
				link.l2.go = "Kraken";
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			dialog.text = "��� ������, ������� " + GetFullName(pchar) + " ?";
			link.l1 = "�������� �� ������ ������ ����������� ���������.";
			link.l1.go = "ArenaBattle_1";
			link.l2 = "�������� �� ���������������.";
			link.l2.go = "academy";
			if (CheckAttribute(pchar,"ScamFanActive") && !CheckAttribute(pchar,"KnowScam"))
			{
				link.l3 = "�� �������� �� ������ ���-������ �� ���� ''������'' ��������?";
				link.l3.go = "legend";
			}
			link.l99 = "�������� ������ �������� ���, " + NPChar.name + " " + NPChar.lastname + ". �� �������.";
			link.l99.go = "exit";
			if (bBettaTestMode && !CheckAttribute(pchar,"ScamFanActive"))
			{
				link.l4 = "������� �������";
				link.l4.go = "Kraken";
			}
			NextDiag.TempNode = "meeting";
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////
		/////////// ��� �� ����� - ����������� ������� ������ ��� ������ ����������� ////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		case "ArenaBattle_1":
			if(GetCharacterItem(PChar, "ArenaBilet") > 0)
			{
				dialog.text = "�������, �� ���������� ����� � ���������� ������������.";
				link.l1 = "��-��, � ������.";
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
							dialog.text = "� ���������, ������� " + GetFullName(pchar) + ", ���� ��������� �� ���������.";
							link.l1 = "����. �����, �� �������!";
							link.l1.go = "exit";
						}
					}
				}
			}
			else
			{
				dialog.text = "� ���������, ������� " + GetFullName(pchar) + ", ���� ��������� �� ���������.";
				link.l1 = "����. �����, �� �������!";
				link.l1.go = "exit";
			}
		
		break;

		case "ArenaBattle_2":
			dialog.text = "������� ������� ������� � �������� ��� ���������� ���������� ������� �����?";
			link.l1 = "� �� � ������������� �����"+ GetSexPhrase("�","��") +" ������� ��� ����"+ GetSexPhrase("��","���") +" �� ������.";
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
				link.l1 = "� ������"+ GetSexPhrase("��","��") +". ��� ���, ���� " + iMoney + " �������.";
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
				link.l1 = "��-��, � ������.";
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
			link.l1 = "��, ��� �������. ��� ����������� ����������� ����� ���������� ����������. ������ ������� � ���"+ GetSexPhrase("��","��") +" ���� ��������� �����. ��, ��� ��� �� ���������?";
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
			link.l1 = "����� ���������! �����, � ���"+ GetSexPhrase("�","���") +" �� ��������������� ������ ��������.";
			link.l1.go = "meeting";
			NextDiag.TempNode = "meeting";
		break;
		// ������� ��� ������ ������� <--

		// �� ����� -->
		case "FightInArena_1":
			dialog.text = "����������� ����, ������� " + GetFullName(pchar) + ". ���� ��������� ��������� � ��������� ����������\n ����� �������� � ��������� �������: �� ��� ����� ������ �� ����������. ����� �����!";
			link.l1 = "��������� �� ����������, " + NPChar.lastname + ".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaDuelTalkWithEnemy");
		break;
	
		case "FightInArena_2":
			switch(sti(PChar.Arena.Duel.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("�� ���������, ������� " + GetNameLugger(PChar, "f") + "! ��������, � ��������� ��� �� ��������� �������!", "����� ����, ��� �� ��������� �������, ������� " + GetNameLugger(PChar, "l") + ".", "��, ��� ������ ����-���� �� ������� �� ������! �� ��� �, �������� � ��������� ��� ��� ������ ������.");
					link.l1 = LinkRandPhrase("��.. �� �������.", "�� �� ����� ��� � ��� ����� ������"+ GetSexPhrase("�","��") +"?!", "�������� - ��� ���� �����!");
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
			dialog.text = LinkRandPhrase("��-��-��! ����� ���������� � ��, ������� " + GetFullName(pchar) + "! ���� �������� �������� �����������, ����� ����� �� ���� ������� � ������������ ������� �����������.", "�� ���, ����"+ GetSexPhrase("�","��") +" � ������� � ��������� �������?", "��, ��� � ��, �������. ��-��, �� ��� � - ������� ����.");
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
					link.l1 = LinkRandPhrase("���. ������ �� �� ����� ������� ����!", "�������� ��� ���� ������ ���� ������. ����������� ��� �����!", "� �� ����� ��� � ���� ����� ������ ������"+ GetSexPhrase("�","��") +"?!");
					link.l1.go = "exit";
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Etaps.Prize));
					AddDialogExitQuestFunction("ArenaEtapsTheEnd");
				break;
			}
		break;
	
		case "FightInArena_5":
			dialog.text = LinkRandPhrase("� ��� � ��, ������� " + GetFullName(pchar) + "! ��� �, �� ��� ��� ������� - ��� ��������� � ����� � ��� ������� ����������� ����, ����� ������ ��� ��� ������.", "����������� ���, ������� " + GetNameLugger(PChar, "f") + ". ��� ���� ����� ������ ������� - ��� � ��� ������. ��, ���� ��, �������, ������ ����� �������. ��-��!", "�������, ��� �� ������ ���� ���� ���������, ������� " + GetNameLugger(PChar, "l") + ".");
            PlayVoice("Kopcapkz\Voices\Arena\ArenaHead_"+rand(7)+".wav");
			link.l1 = LinkRandPhrase("������� ���� ����������, ��� � ��� ������� ������ � ������� �� ����!", "����� ��� �������� - ��� �� �������� ����-������ �������!", "���� ����� ���� - ���� �� ����������.");
			AddDialogExitQuestFunction("ArenaTournamentTalkWithRandEnemy");
		break;
	
	
		case "FightInArena_7":
			switch(sti(PChar.Arena.Tournament.Win))
			{
				case 0:
					dialog.text = LinkRandPhrase("��-�, ������ ������ �� �����! �� �������� ���������, �������! �� ����� ���� �� �� ����� �������. ����� ����� ��� ����� - ���� �����, � ��������� ��� �� ��������� �����������.", "� �������� �� ���, ���, � ��� ���� �� ���� �� ���������! ����.", "��, ��� �� �������. �������� �� ������ �� ���������.");
					link.l1 = LinkRandPhrase("������ � �������, ���, �������"+ GetSexPhrase("�","��") +"... �� ��������.", "�������� ����������� ����������� ����� - � ���� ����������.", "�� ������, � ��� �������.");
					link.l1.go = "exit";
					AddDialogExitQuestFunction("ArenaTournamentTheEnd");
				break;
			
				case 1:
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Tournament.Money));
			
					pchar.questTemp.tournamentcount = sti(pchar.questTemp.tournamentcount) + 1;
					if(sti(pchar.questTemp.tournamentcount) >= 1) UnlockAchievement("AchTurnir", 1);
					if(sti(pchar.questTemp.tournamentcount) >= 3) UnlockAchievement("AchTurnir", 2);
					if(sti(pchar.questTemp.tournamentcount) >= 7) UnlockAchievement("AchTurnir", 3);
					
					if (rand(3) == 0 && !CheckAttribute(pchar,"ScamFanActive"))
					{
						pchar.quest.SpawnScamFan.win_condition.l1 = "Location";
						pchar.quest.SpawnScamFan.win_condition.l1.location = "FencingTown_ExitTown";
						pchar.quest.SpawnScamFan.win_condition = "SpawnScamFan";
						pchar.ScamFanActive = true;
					}
					
					bool nopirate = false;
					if (!CheckAttribute(pchar,"questTemp.UniquePirate.Barbarigo") || !CheckAttribute(pchar,"questTemp.UniquePirate.BlackBeard") || !CheckAttribute(pchar,"questTemp.UniquePirate.Levasser")) nopirate = true;
					if (sti(pchar.questTemp.tournamentcount) == 3 && nopirate)
					{
						aref item;
						Items_FindItem("map_full", &item);
						string type = GetUniquePirateName();
						FillMapForUniqueTreasure(item, type);
						type = GetUniquePirateNameString(type);
						GiveItem2Character(pchar, "map_full");
						dialog.text = LinkRandPhrase("��-�, ������ ������ �� �����. � �� ����� ��� �����������! ��������� ������, � �� ��� �������� ���� �� ����, ��� �� ������������ � �������! ������ ��� " + sti(PChar.Arena.Tournament.Money) + " ������� �� ����� ����������� ���.", "�������, �� - �������! ������ ������ ���������� � ������� �� ������� ���� ����� �������� ���������! �������� ��� ���� - ��� " + sti(PChar.Arena.Tournament.Money) + " �������.", "�� �� �� ���� ���� � ������� �� ���������! ��� ��� ������! ��� " + sti(PChar.Arena.Tournament.Money) + " ������� �� ����� ����.");
						dialog.text = dialog.text + "\n��� ��� �� ����� ��� ���������� ����������� �������, �� ������ ����������� ���-��� ���������... ��� ����� ����� ��������, ��� �� ������, ��� ������������ ����������� "+type+". �������, ��� ����� �� ����� ��������� ��, ��� ������� ���� ������.";
						link.l1 = "��� ��� �������� ����������� ������� � ����� �������! �������� ��������"+GetSexPhrase("��!","��!");
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = LinkRandPhrase("��-�, ������ ������ �� �����. � �� ����� ��� �����������! ��������� ������, � �� ��� �������� ���� �� ����, ��� �� ������������ � �������! ������ ��� " + sti(PChar.Arena.Tournament.Money) + " ������� �� ����� ����������� ���.", "�������, �� - �������! ������ ������ ���������� � ������� �� ������� ���� ����� �������� ���������! �������� ��� ���� - ��� " + sti(PChar.Arena.Tournament.Money) + " �������.", "�� �� �� ���� ���� � ������� �� ���������! ��� ��� ������! ��� " + sti(PChar.Arena.Tournament.Money) + " ������� �� ����� ����.");
						int randreward = drand2(100);
						string reward;
						if (randreward < 6)
						{
							int quality = 1;
							if (pchar.rank <= 6) quality = 1;
							if (pchar.rank >= 12) quality = 2;
							if (pchar.rank >= 18) quality = 3;
							if (pchar.rank > 24) quality = 4;
							reward = "book"+quality+"_"+sti(drand(13)+1);
						}
						if (randreward >5 && randreward < 17)
						{
							switch (drand(11))
							{
								case 0: reward = "blade19"; break;
								case 1: reward = "blade22"; break;
								case 2: reward = "blade36"; break;
								case 3: reward = "blade37"; break;
								case 4: reward = "blade31"; break;
								case 5: reward = "blade34"; break;
								case 6: reward = "blade40"; break;
								case 7: reward = "blade46"; break;
								case 8: reward = "blade15"; break;
								case 9: reward = "blade21"; break;
								case 10: reward = "blade42"; break;
								case 11: reward = "topor2"; break;
							}
						}
						if (randreward >16 && randreward < 28)
						{
							switch (drand(4))
							{
								case 0: reward = "pistol6"; break;
								case 1: reward = "pistol_grapebok"; break;
								case 2: reward = "pistol9"; break;
								case 3: reward = "mushket"; break;
								case 4: reward = "mushket_drob"; break;
							}
						}
						if (randreward >17 && randreward < 39)
						{
							switch (drand(2))
							{
								case 0: reward = "cirass2"; break;
								case 1: reward = "cirass3"; break;
								case 2: reward = "cirass4"; break;
							}
						}
						if (randreward >38 && randreward < 50)
						{
							switch (drand(7))
							{
								case 0: reward = "indian1"; break;
								case 1: reward = "indian10"; break;
								case 2: reward = "indian15"; break;
								case 3: reward = "indian18"; break;
								case 4: reward = "indian19"; break;
								case 5: reward = "indian20"; break;
								case 6: reward = "indian21"; break;
								case 7: reward = "indian22"; break;
							}
						}
						if (randreward > 49)
						{
							GiveItem2Character(pchar,"Chest");
							reward = "icollection";
						}
						GiveItem2Character(pchar,reward);
						
						int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
						aref item1;
						Items_FindItem(reward, &item1);
						dialog.text = dialog.text + "\n������ ��������� �����, �� ����� ������ ������� ��� ������ ������� �� ������. ��� "+LanguageConvertString(idLngFile, item1.name)+".";
						LanguageCloseFile(idLngFile);
						link.l1 = LinkRandPhrase("������� �� �� ��� ����������!", "� ��� �� ��� ������, ��� ����� �������. � ������ - ��������.", "��-��-��, ������ ���������! ����� ���������� � �� �������� ������ ��� �����. ������, ����� ������� ��� ��������.");
						link.l1.go = "exit";
					}
					AddDialogExitQuestFunction("ArenaTournamentTheEnd");
				break;
			}
		break;
		
		case "FightInArena_8":
			dialog.text = LinkRandPhrase("�-�, ��� � ��, ������� " + GetFullName(pchar) + ". ��� ������ ��� ���. �������, ��� ��� ������� ������.", "�-�, ��� � ��, ������� " + PChar.lastname + ". ���� ������ ������ ���������� �������!", "�-�, ��� � ��, ������� " + PChar.lastname + ". �����, ��� ������� ����� ��������� � ��� �����, � �� ��� � ������� ���...") + " ������� ���� ����� - �������� �-�-�-�-� ���� ...(���������� �����)... � ����������� �� �����.";
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
					link.l1 = LinkRandPhrase("��-��, ����� ���� � ��"+ GetSexPhrase("�","��") +".", "�� ���, ���������� �� ��������. ������� ������ ������� � ������.", "���������. ����������� ���� �������.");
					link.l1.go = "exit";
					AddMoneyToCharacter(PChar, sti(PChar.Arena.Odds.Prize));
					AddDialogExitQuestFunction("ArenaOddsTheEnd");
				break;
			}
		break;
	
		case "FightInArena_10":
			
			dialog.text = LinkRandPhrase("� ��� � ��, " + GetFullName(pchar) + "! ����� ���������� �� ���� ��������. �������, ��� ���������� ���� �����������.", "�����������, ���. ������� � ��� ���������� ����� ��������� ��������.", "� ������, ��� ���������� ���� �����������.") + " ������� ���� ����� - �������� �-�-�-�-� ���� ...(���������� �����)... � ����������� �� �����.";
			link.l1 = LinkRandPhrase("� ���� ��"+ GetSexPhrase("�","��") +" ��������� �����. � ������������� ����� ��� �����.", "�������, ����� �������� ��������� ��������, � �� ��������� �����.", "�����, ������� ��� ��� �����������.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("StartArenaOddsContinue");
		break;
	
		case "FightInArena_11":
			dialog.text = LinkRandPhrase("��-�, �������� ���� �������! � �� ������� ����������� ������� ���� ����� ���������� � �������. ����� ���� ��������� �������. � ����, �� ����� ���������!", "��-�, ������ ���� �� �������� - ����� ����� ��������, ����� ������!", "��� �� ���� �� ������������� � ����� ������������.");
			link.l1 = LinkRandPhrase("��� �� ������ ��� ��� ����������� ��������. �������, � �� ��������.", "��, ��� ����� ��� ����. � ������������� ��� ��� ����� ����.", "����! � ��������� ��� ��"+ GetSexPhrase("�","��") +" ���������� � ���� ������������ - ����� ���������, ��� ����� ��������� ��������.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaOddsTheEnd");
		break;
	
		case "EnemyFightInArena_1":
			dialog.text = LinkRandPhrase("�� ���, ���"+ GetSexPhrase("��","���") +" ������ ���� ������ ���? ���-�� ������� ������ ���������.", "�� � ����� ���� � ������, ���������!", "����������� ���� �� � ���, �����������!");
			link.l1 = LinkRandPhrase("���. �� ���������, ��� ����. ��������� � ����.", "������ ���� �����, ������ �����. ������ � ���� �� ������ ����.", "��-��, ������ ���������, ��� �� ��� ���� �� � ���.");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ArenaDuelStartBattleWithEnemy");
		break;
	
		case "FightInArena_6":
			dialog.text = RandSwear() + " " + LinkRandPhrase("� ������� �� ���� ���� ��� ������ �������!",+ GetFullName(pchar) + "?! � ����� ���� �� �����, ���� �� ������ � ���� �� ����!", "��, ��! ������ �� ���������, ��� ����"+ GetSexPhrase("��","��") +" ����!");
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
		
		case "legend":
			dialog.text = "�, �� �������� ��� ����� ������? ������� ��������� �� �������, ��� �� ������� � ���?";
			link.l1 = "��� �� ������ �����?";
			link.l1.go = "legend_1";
		break;
		
		case "legend_1":
			dialog.text = "�� ������, �� - ������� ��������� �������, ������� �� ���������� ������� �� ������������ �����������. ������� � ��� ���-�� ��������� � � ��� ��� �� �� ���, �� ���� � �� �������� ��������� �������� ����� �� ���� ������. �� ��������, ����� ����� �� �������� ���������� �� ����.";
			link.l1 = "�� ������� ���������� ����������... �� ���� �� ��������� ��� ���� ���� - �� ��������� ���� ��� ������.";
			link.l1.go = "legend_2";
		break;
		
		case "legend_2":
			dialog.text = "����� ��� ������, � �� ������ ������ ���������� �� ���� �� ������� ���������. ��� ��� ���������� ''������'' �������� � ������ � � ��� ������ ������ �� �������.";
			link.l1 = "���� ���� �����-������ ����� �� ���� ����?";
			link.l1.go = "legend_3";
		break;
		
		case "legend_3":
			dialog.text = "���� �� ����, ��� ������� �� ���� ����. ��� ����� ��� ���� ������ �� ������. ��� ��������� � ����������� ������� ���������� �� ���� �� ��� ����������.";
			link.l1 = "����, ������... ��, ������ ���������� ���������������, �� ������� ���� �� ����.";
			link.l1.go = "exit";
			pchar.quest.RidScamFan.win_condition.l1 = "Location";
			pchar.quest.RidScamFan.win_condition.l1.location = "Temple_skulls";
			pchar.quest.RidScamFan.win_condition = "RidScamFan";
			pchar.KnowScam = true;
		break;
		
		case "Kraken":
			dialog.text = "������ ������.";
			link.l1 = "��� ���������.";
			link.l1.go = "exit";
			pchar.quest.SpawnScamFan.win_condition.l1 = "Location";
			pchar.quest.SpawnScamFan.win_condition.l1.location = "FencingTown_ExitTown";
			pchar.quest.SpawnScamFan.win_condition = "SpawnScamFan";
			pchar.ScamFanActive = true;
			AddDialogExitQuestFunction("ArenaTournamentTheEnd");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
