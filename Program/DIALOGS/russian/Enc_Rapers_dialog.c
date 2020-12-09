void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;

		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase("�"+ GetSexPhrase("��","��") +" �� �� ����� �������, "+ GetSexPhrase("��������","�������") +". ��� ����� ��� ����������� ��� �����.",
											 "�������� ������! �� ����� ������������ ������������.",
											 "�� ���������� �� � ��� ����, "+ GetSexPhrase("����������","������") +". ���������, �� ���� �����������!");
				link.l1 = LinkRandPhrase("� �� ������� ����� �����������!","������� ��� ������ ����!","� �� ������ �������!");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("�����"+ GetSexPhrase("","�") +", �����. ��������, ��� �������"+ GetSexPhrase("","�") +".","�� ���� ��� ������. ��������, ��� �����������"+ GetSexPhrase("","�") +".");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
					dialog.text = LinkRandPhrase("�"+ GetSexPhrase("��","��") +" �� �� ����� �������, "+ GetSexPhrase("��������","�������") +". ��� ����� ��� ����������� ��� �����.",
											 "�������� ������! �� ����� ������������ ������������.",
											 "�� ���������� �� � ��� ����, "+ GetSexPhrase("����������","������") +". ���������, �� ���� �����������!");
					link.l1 = LinkRandPhrase("� �� ������� ����� �����������!","������� ��� ������ ����!","� �� ������ �������!");
					link.l1.go = "Node_Fight";
					link.l2 = RandPhraseSimple("�����"+ GetSexPhrase("","�") +", �����. ��������, ��� �������"+ GetSexPhrase("","�") +".","�� ���� ��� ������. ��������, ��� �����������"+ GetSexPhrase("","�") +".");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple("��, "+ GetSexPhrase("����������","�������") +", ����� ���� ������������? ��� �� ��������� � ��������� �������. �� � ��� ��� � ������������. � ��� ���� ������� � �������� ������.",
												   "��, "+ GetSexPhrase("��������","�������") +", ��� ����� ������� � �� ����������, ���� ���� �� ������. �� ������ ��� � ����� ��������, �� ��� ������� ������ ���������. ����� ��� �� ��� ������.");
					link.l1 = "������ �� ����, �������� � ����� �� ���!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("��� � ��� ����! � � ���� ���� �� �������"+ GetSexPhrase("","�") +"! �� ��������� ���...","�-�, �� ��� ������ ����. ��� �, �������������, ���� �����.");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{	
					dialog.text = "���, "+ GetSexPhrase("���-�������","�������") +", ����� �������. ��� ���� ���������.";
					link.l1 = "� �� ������ �������!";
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple("��, "+ GetSexPhrase("����������","�������") +", ����� ���� ������������? ��� �� ��������� � ��������� �������. �� � ��� ��� � ������������. � ��� ���� ������� � �������� ������.",
												   "��, "+ GetSexPhrase("��������","�������") +", ��� ����� ������� � �� ����������, ���� ���� �� ������. �� ������ ��� � ����� ��������, �� ��� ������� ������ ���������. ����� ��� �� ��� ������.");
					link.l1 = "������ �� ����, �������� � ����� �� ���!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("��� � ��� ����! � � ���� ���� �� �������"+ GetSexPhrase("","�") +"! �� ��������� ���...","�-�, �� ��� ������ ����. ��� �, �������������, ���� �����.");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("�� � �� ������� �� �� �������� �����...","���, ������ �������������?") +" ���� �"+ GetSexPhrase("��","�") +", ������!","�� �� "+ GetSexPhrase("�������","�����") +"! �� ���� ������ ������ �����������?! ���� �"+ GetSexPhrase("��","�") +"!");
			link.l1 = "� �� ����� ������� ������.";
			link.l1.go = "Exit_Fight";
			ChangeCharacterReputation(pchar, 5);
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = "�� ��� �������� ��� � ����������� �����! ���� �� ���"+ GetSexPhrase("��","��") +" ���������"+ GetSexPhrase("��","��") +", �� ������ �������� � �� " + sti(pchar.GenQuest.EncGirl.price) + " ��������."+ GetSexPhrase(" �������������� �����, ��-��..","") +"";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple("��� ���� ������, � � �������.","�� ����� ����. � ������� ��������, ��� ������.");
				link.l1.go = "Node_4";
			}	
			link.l2 = LinkRandPhrase("�������� ����������?! � ����� ��� ����� �� �������?!",
									 "���� �����������, � �������� �� ������ ��� �� ����� �����!",
									 "�� ���� �������� ���������?! ������ ������!");
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": // ������� ������, ������ �������� - �� �� ������� � ��������
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price))); 
			ChangeCharacterReputation(pchar, 7);
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = "�� ���� �� �� ������?! ����� �������? �� ���� ��� �������, ���� ���� �������� - ������ ������.";
			link.l1 = RandPhraseSimple("��� ���? �� ��� ������ ����. ��������� ���� ��������.","�-�, �� ���������, ���������. � ��� ��� �� ����� �����...");
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple("�� ��� ������ ������ ������ ������������, ���� �������!","�� ���� �������� �����?!");
			link.l2.go = "Node_6";
			link.l3 = "��� � ���"+ GetSexPhrase("","�") +" � ����� � ������, ���� ���� ������� �� �����. ��� � ��������?";
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = "��, �� ���"+ GetSexPhrase("","�") +" �� ��� �����"+ GetSexPhrase("","��") +", ������ �� ��������...";
			link.l1 = "��� �� �������.";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = drand(2);
			else	i = drand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = "������ ��������";
					pchar.GenQuest.EncGirl.FatherGen = "������� ��������";
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = "������ � �������� ����������";
					pchar.GenQuest.EncGirl.FatherGen = "��������� � �������� ����������";
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = "������ ����������� �����";
					pchar.GenQuest.EncGirl.FatherGen = "���������� �����";
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = "������ �����";
					pchar.GenQuest.EncGirl.FatherGen = "������� �����";
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dialog.text = "Ÿ ���� - " + pchar.GenQuest.EncGirl.FatherNom + ", ��� � ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ". ������ �� ������� ���, � �� ���� � ���� ������ ������ - ��� ����� �������...";
			link.l1 = "�� ����������. �������� � ������ ����.";
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterReputation(pchar, 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = "��� � ����� �����������. � ��� ���� ���������?.. �������, ��� ��� ��� ����������, ��� �� �����.";
			link.l1 = "�����������, ��� �������, ���������� ���� ����� ����������, ���� �������� �������� � �����.";
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(drand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(drand(4))
			{
				case 0:
					sTemp = "����";
				break;
				case 1:
					sTemp = "����";
				break;
				case 2:
					sTemp = "���";
				break;
				case 3:
					sTemp = "����";
				break;
				case 4:
					sTemp = "�����";
				break;
			}
			dialog.text = "��� ���� ����� �� ��������� � ����������� " + GetName(pchar.GenQuest.EncGirl.PirateIdx , pchar.GenQuest.EncGirl.PirateName1, NAME_GEN) + "? " +
							"�� ��� ��������� ����, ��� �� ����� ����������� ����� �����, ������ ��� �� ����� ��������� �� �������...\n�� � ��� �������� ���� � ���� ����! "+ 
							GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.PirateName2, NAME_NOM) +" � ����� �� ��������� ������� " + sTemp +"! � ��� ������� ������? " + 
							"������ ������ ��������?! ��� ������ " + GetName(pchar.GenQuest.EncGirl.PirateIdx , pchar.GenQuest.EncGirl.PirateName1, NAME_NOM) + " ��������� � ���� � ������. �� ������ �� �� �������� ���������! ���������, ��� ��� �������!";
			link.l1 = "��, ���� � � �� �������"+ GetSexPhrase("��","���") +" ��������� ��������� ������ ��������, �� �������� ��� ����� �� ����... ������ ��� ���"+ GetSexPhrase("","�") +" ��� �� ����.";
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = "�� �����!!! � ��� �������� ����� ��������, ������� �������� �� ���� ������! ��������� �����, ���� �� ������ ���������!";
			link.l1 = "����, ��� ����� ���� �� �������. �����, ������ ������?";
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = "�� �� "+ GetSexPhrase("���","�����") +"! ����� � ������!...";
			link.l1 = "����...";
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = "����������, �������"+ GetSexPhrase("��","��") +". ������ �� ���� ���������.";
			link.l1 = "�� ���� ������? �� ���� ������?";
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = "�� ������� � ����������! � ���� �������� ������� �� �������! ������� � �������� � ��� ������"+ GetSexPhrase("���","��") +", ����� ���� "+ GetSexPhrase("����� �������������� ����������","�������� � ��������") +".";
			link.l1 = "������, ��������, ��� ����������� �� ��� �����������?";
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = "���. �������� ����� � " + sti(pchar.GenQuest.EncGirl.BerglarSum) + " �������� ����� �������� ���� �� ����� �������������.";
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = "��, ������ ������� ����� ��������� ����������� ��������. �������...";
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = "������� ����� ������� � ���� ����� ����, ���� �� �������� ��� ������ � ������.";
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = "���. �� ���� �������� ��������� �������, �� �� ������ ����!";
				link.l1 = "�������, ��������! �� ��� ���� ��� ������ � ��� �� ������...";
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = "����� ����� ������� � ���� ����� ����, ���� �� �������� ��� ������ � ������.";
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = "��� � ������. ��������� ������.";
			link.l1 = "��������� ����������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = "�������, �� ������, ��� �� ������? ��, ������, "+ GetSexPhrase("�������","�������") +"."+ GetSexPhrase(" � ����� - �� ����� �� ��������, ����� �� ���� ������� � ���� ��������. ������ ������ �����!","") +"";
			link.l1 = ""+ GetSexPhrase("��� �����!..","����� ���, ����������!") +"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = "�� ��� "+ GetSexPhrase("����� ����������� �������","����� ����������� �������") +", � ��� ����������� �����������.";
			link.l1 = "��� ����...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = "��, ����� ����� �� ����! ��������� �"+ GetSexPhrase("��","�") +" ����� ������, ������!";
			Link.l1 = "���������� ����� �������!";
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = "���, ���������� ��������������? "+ GetSexPhrase("��� � ����� - ��� ����� ����","��� ������, ��� ����� ����� ������") +"!";
			Link.l1 = "��� ���, �� ���� ��� ������.";
			Link.l1.go = "Exit_NoFight";
			Link.l2 = "� �� ������� ������� ��������� �� ���� ������!";
			Link.l2.go = "Node_2";
		break;				
	
	}
}
