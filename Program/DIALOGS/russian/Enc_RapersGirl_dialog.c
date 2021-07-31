void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(npchar);
			//#20200315-01
            npchar.chr_ai.type.checkFight = 999999.0;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("�������","�������") +"! ������ ����������, �������� ����! ����� ���!","�� ������! "+ GetSexPhrase("����������","�������") +", ������� ����, ������!");
			link.l1 = LinkRandPhrase("��� ���������?","��� ���������?",RandPhraseSimple("� ��� ����?","��� ����������?"));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("�������! �������","�������! �������") +", ��������!","��������, "+ GetSexPhrase("�������","�������") +"! ����� ���.");
			link.l1 = LinkRandPhrase("��� ���������?","��� ���������?",RandPhraseSimple("� ��� ����?","��� ����������?"));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "��, ��������"+ GetSexPhrase("��","��") +"! �������� ������ �������, ����� ���! ��� ���� ��������� ���-�� ��������!";
			link.l1 = LinkRandPhrase("��� ���������?","��� ���������?",RandPhraseSimple("� ��� ����?","��� ����������?"));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple("��� ������� ����� ����������� ���� ����! ���� ����� �������, �� ���������� �� �����!","������ ����, �������� ���� �� ���� �������! ��� ����� ����������� ����!");
			link.l1 = "�� �������"+ GetSexPhrase(", ���������","") +". ������ ���������.";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("�� ���� ������� ����������!"+ GetSexPhrase(" �� ����� �� �� ����������� �� ����� ����?","") +"","�������, "+ GetSexPhrase("������ ��������","�� �� �������") +" - ������� ������� �� ���������!");
			link.l1 = "�� �������"+ GetSexPhrase(", ���������","") +". ������ ���������.";
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = "�� ���� �������... �� ���� ������� �������! ������� ��, ����� �������� ���� � �����!";
			link.l1 = "�� �������"+ GetSexPhrase(", ���������","") +". ������ ���������.";
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("��������! ��������! ��� ���� ���������� ����! �������!",
				"�-�! �� ������, "+ GetSexPhrase("����������","�������") +"! ������� ���� �� ���� ���������!",
				"������ ����������, �������� ���� �� ���� ��������! ����� ���!");
			Link.l1 = LinkRandPhrase("��� ����������?", "� ��� ����?", "��� ���������?");
						  
								  
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase("���... ��� ����� ����������� ���� ����! ������ ���, �� ���������� �� �����! ������� ����!",
				"��� �����... ��� ����� ������� ���-�� �������... �������� ���� �� ���, ����������!",
				"�� ��� ������� ������ - �������� ���� �� ���� ���������� �������! ��� ����� ����������� ����!");
			Link.l1 = "���, ������ ����������.";
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("������� ���, "+ GetSexPhrase("�������","�������") +". � ��� ����������!","�������, ��� ������ ����! � ��� ��� ����������!");
					link.l1 = "�� ��, "+ GetSexPhrase("���������","�������") +", ��������� - ������ ��� �� ������.";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "��, �������, "+ GetSexPhrase("����������� �������! �� ��������� ����������!","�������! �� ���� ������!") +"";
					link.l1 = "� �� ���"+ GetSexPhrase("","��") +" ��������� �����.";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "��, �������, "+ GetSexPhrase("����������� �������! �� ��������� ����������!","����������! �� ���� ������!") +"";
					link.l1 = "� �� ���"+ GetSexPhrase("","��") +" ��������� �����.";
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = "��� �� �� ��������?! ����� �� �� �����?! ������ ���� ����� ������! �������, �� �� ��� ��� ����� ���������?!";
					link.l1 = "��� ��� �������������!";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "�� ��� �� ��������, "+ GetSexPhrase("�������","�������") +"?! ����� �� �� �����?! �� ������������� ������ ��� ����!.. ����! �� ���� ������ �����...";
				link.l1 = "�� � ����! � ��� �� ������, ����� �������, ��� �� ����� ������� �������?!";
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "ThanksAgain";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "� ���� � ����� ���� ������� �����, �� ����������� - �������� �� � ���� �������������. � ������ ���� ��������, "+ GetSexPhrase("����� �� ����������� � ������� �������","����� �� ����������� � ������� �������") +".";
			link.l1 = "������-������, ����������. �������... � ������ ��� �����.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = "� �� ��� ��� �� ���� ������ � ����. �� ��������� "+ GetSexPhrase("����","����") +" �� ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? � �� ��� ������ �� ������ ������ ���������� ���������.";
			link.l1 = RandPhraseSimple("�� �� �������� �� ���... �� �����, �����.","��� � �� ������� �����? �����, �������.");
			link.l1.go = "Node_121Next";
			link.l2 = "������, �����, ������� ��� - ���� ����.";
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = "� �� ������, ��� �� �� ������ ���������!.. �� ������ ������� ���� � ������� ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", ��� ������ �� � ���� ������� ������.";
			link.l1 = "�, ����! �����. ������ �� ��������.";
			link.l1.go = "Node_122Next";
			link.l2 = "�� �� ���, "+ GetSexPhrase("���������","�������") +"! �� ������� ��������� ����������. ��� ���� ������� ���������.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = "� ��� ��� ���������� ������?! ���� ���� ����� ������ ����� �� ���� ���������� - ����� �������... ������ ��� � ��� ������ � �������� ����� ��������. � � ����� �������! �������� ���� � ����, ����� ���.";
			link.l1 = "��� ���������� �� ��� ������! �����, ���� ���� ������ ������... � ��� ����� ������ ����������, ���� �����-��?";
			link.l1.go = "Node_32";
			link.l2 = "�� �� ���, "+ GetSexPhrase("���������","�������") +"! �� ������� ��������� ����������. ��� ���� ������� ���������.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "��� ����� " + pchar.GenQuest.EncGirl.sLoverId + ", �� ��������. ������ ���� � ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", ����� ��� ������, �� � ��� � ���� ����. ��� ������� - ������... � ����� ��� �� ����� ������ ���� ���.";
			link.l1 = "������, ��������? ��-��... ��� ���������� ������ ������ - ��� ����� �� ��������� �������, � � ���� ������ �����... ";
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeathSimple.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathSimple.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathSimple.function = "EncGirl_DeathSimple";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeathSimple.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathSimple.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathSimple.function = "EncGirl_DeathSimple";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("�� ������, "+ GetSexPhrase("�������","�������") +"? � � ��� ����������, ��� �� ��� ��� ������� ������.","�� � ����������� �� � ������. ������, ��� ��� ������� ��� ������.");
			link.l1 = RandPhraseSimple("��������� ����, ��� ���� ��������.","�� ���� ������ � ������. ������, ��� �� ��� ��������.");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple("������� ���, "+ GetSexPhrase("�������","�������") +", ��� ���. �� � �� ����, ��� �����������.","������� ��� �������, "+ GetSexPhrase("�������","�������") +". ���� �� �����������, ��� �� � ������, �� �������� �� �� �������.");
			link.l1 = RandPhraseSimple("������ ����� ���� �����. ��, ��������� ����������...","� ��������� ��� ������ ����������... ��, ��� �����, ���� ���� ����.");
			link.l1.go = "Node_1End";
			link.l2 = "����� ����� ���� ����� ���������? ���� ���� ���� � ������� �������?";
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterReputation(pchar, -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("������� �� ����������?","�������, ��� ������, ��� �� ����������!");
			link.l1 = RandPhraseSimple("���-���, ��������, ��� ����.","���� �� �������...");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "��, ��������, ������ ��������... � ����� ����������� ��������... ���� ������� �������, ��� ���� ����� ������, ������� � �������� ����� ��������.";
						link.l1 = "�������! � ��� "+ GetSexPhrase("��� ������� ������","�� ������ ������") +"?! ������, ����� �������, ��� �� ����� ����� ����� ������� ��������� - ������ �����"+ GetSexPhrase("","�") +". ��-��-��-��... ��, ����� �������.";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "������ �������� ������, �������� ������, ����� ��������... �� ������, �� � ������ ��� �����.";
						link.l1 = "��� �� �����������?! ��������� ����, ��� �� ��� ����������... ��, ����� ��������.";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "������� ��� ���-�� ����� ��������� �������� ���������, ����� �������������. ����� ������ - ������������, � ���� ������� ������. �������: '���� ��������� �� ������� - ����� �� �������'... � � ���� ����� ������ �� ����. �� � ��� �� �������� - ����������� ��������� � ����� �����? ���, ����� ������ - �� ����, ��� � ������.";
					link.l1 = "� ��� �� ��������? ����� ������� ������ ����� ������, ��� �� �������� ��������� ������� ���?.. ����� � �� ������� ����?";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "��� �� ��������� ���� ����� ���������, � ��� ������ ������ ������. ���� ���� ��� ���, ��� ����� ��� �������, � ��� ���������� - ������ ����� �� �����. ������� �������� ����� ��������, � ����� ��������, �������� ������. ";
					link.l1 = "� ��� �� �� �������? ���� � ���� ����� ������, ��� ������ �� ��� ������ ������� �����?";
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "��� ������ ��� ��������. ����� ������� �� ������. � �� ���� " + sti(pchar.GenQuest.EncGirl.BigCoins) + " ������� �������� � " + sti(pchar.GenQuest.EncGirl.SmallCoins) + " ������. ���� �� ����� ��������� ������� ���������, �� ����� ���� �� ���������� �������� �������� �� ������.";
			link.l1 = "��, ������� ������ ���� ������� ������... ��� �, ���, ��� ��������. ��������� ����������.";
			link.l1.go = "Node_131End";
			link.l2 = "���������� ��� �������... ������ ������ � ����� ����� - �� �����, ��� ������ � ����� ����. ��� �����, ������� ����� �� �� ������...";
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterReputation(pchar, -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = "���� �� ��� ����� �������, ��� ���� ��������� �������. �� �� ������� � ���������� ������ " + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_VOC) + "?";
			link.l1 = "���, ������ �� ������"+ GetSexPhrase("","�") +".";
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = "��� ��� " + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_NOM) + " � ��� ��� ����. ��� ��� �������, ���� ������� ����� �� ����. ������, �������, ���������. ����� � ����� ������� ����������, �������, ��� �� ���� � ���� ����� ���� ����. � ����� �������� ������, � ��� ���������...";
			link.l1 = "��� ���� � �������? ������� ����� � ����� - ������� ���� ���������. ����� ��� �� �������� ���� �� �����������?";
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = "����� �������. � ���� ����� �� ����� ���, �� � ����� �... ��� � �� ��� ���� ����������, �������������... � ����� ����? ����� ���� �� ������ �������, ��� � ����� �����...";
			link.l1 = "�� � �� �����... �� ��� �, ��� - ����� ���� �����. ������ ����� ����� �� ������.";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "��, ����� ��������. ��� ��� �����, ��������� ���� ����.";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "� ��������� ����� �� ���������?";
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = "�����... ���� ��� �����������, ������� �� ��� ����� �������. ��� �� ��� ������� ��������?";
			link.l1 = "������, �� ���������. ����� ������ �� ����� ����, ���� ��-�� ���� ������ �������. �� � ����� � ���� ������� - ����� ������ � ����� � ���������...";
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "��������� �������... � ������� �� ������ �� �� ����?";
			link.l1 = "�� �����, ��� ��� ����� ������ ������ " + sti(pchar.GenQuest.EncGirl.mapPrice) + " ��������.";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "��, ������� ����... � ��������. ��������� ������� �� ����� �������... �� ����� ����� ��� ����� ���������� ���"+ GetSexPhrase(" - ������������ �����������","") +", ��� �����-�� �����������.";
				link.l1 = "��� � �������. ����� ������, ������ �� ����� ��� �����.";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "���, "+ GetSexPhrase("�������","�������") +". �� ����� � � ���������. ��� ����� �����, �� � ����� ���� � �������... ";
				link.l1 = "��, ���� ������. �� �����, �� ���� ������� ����� ������ �� ����.";
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = "��� �� �� ������? �� ������� ������� ������� - ��� ����� ��� ���� �����, �� � ��������� �� �����. � ������ � �����, ��� ��� ������� ���� ����������, ��� ����� ������ - �� ������, ���� �� ��� �����.";
			link.l1 = "��-��-��... � �� ���� �� ������ �������?";
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = "� ����?! � �����? ������ �� ����� ���� ����� ���� ��������, � ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", �����?!";
			link.l1 = "�������, ���� ������� ����.";
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "���� ������� � ������ �� " + XI_ConvertString(pchar.GenQuest.EncGirl.islandId + "Acc") + ", ��� ����� ��������� � " + XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen") + ", � ����� ������ ����... ������, ���, ������ ������� �����!";
			link.l1 = "������-������, �� �����. ��� �� ���� � �� ��������.";
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = "�������, ������ �� ������ ����� ������.";
			link.l1 = "�� ��� �, ����� ������.";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "�������, �� ������ ����� ������.";
			link.l1 = "�� ��� �, ����� ������.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = "���. � ��� �����!.. ��� ������� ���� - ����� ����� ���� ��������������! ���� �������� - ��� � ��������������.";
			link.l1 = "��� ������, ��� �� ������ ���������? � �� �������.";
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = "��-��-��!.. ������ � ������! ���� ���� ������� ������?";
			link.l1 = "�������.";
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = "����� ������� � �������� ��� ������� ��������� �� �������. �� �� ������, ��� ������� ������� ���� �����?";
			link.l1 = "�� �����"+ GetSexPhrase("","�") +". ������ �����������.";
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("�� �������� ���� ���� �����");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+drand(1));
			TakeNItems(pchar, "chest", 2+drand(6));
			TakeNItems(pchar, "jewelry1", 30+drand(15));
			TakeNItems(pchar, "jewelry2", 30+drand(15));
			TakeNItems(pchar, "jewelry3", 30+drand(15));
			TakeNItems(pchar, "jewelry11", 30+drand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry15", 10+rand(10));
			TakeNItems(pchar, "jewelry18", 20+rand(10));
			TakeNItems(pchar, "jewelry14", 30+rand(10));
			TakeNItems(pchar, "jewelry7", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));			
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "��� ������� ���� �������! � ���� �������� ������ ���������."; 
			link.l1 = "� ���"+ GetSexPhrase("","�") +" �� ����.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = "�� ��, �������. �� ����������� ���������. ������� ��� �� ������.";
			link.l1 = "����������... ��� ������� ������ �� ����� ����������? ������ ��������� ������, ����� �������...";
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = "�� ����, �� ������ ���... �����, � ������ ����...";
			link.l1 = "��, ��������� ����������.";
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = "��������... � ����� ���� ���� ��� ��� ������. ��� ��� �� � ����, � ��� ����� �����������. �������� �, ��� ������� �� ��, ��� �� ��� ���� �������... ��� �� ���� ����, ��-��-��...";
			link.l1 = "��-��, ����� �������. �������"+ GetSexPhrase(", ���������","") +". ������ ���� ��������...";
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_133":
			dialog.text = "�� ��� �� ��� ������? � �� �� ���� ���������� �������! ��� � ���� ��� ����� �������.";
			link.l1 = "��� ���� � ������ ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", ������� � ���� ������� ��� ��������.";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "���, ����� 15000 ��������, �� ��� ������ �����, ���� �� ����� �������� ������, �� ��������� � ���� ��������� - �� ���������.";
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","�")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("�������","�������") +", ��� � ���� ��� ����� ������! ��� ������� ������� ������ ��� ��������?","������������, �������! �� ���, �������� ���������? � �� ������� ����� ����������.");
			if (GetCharacterItem(pchar, "jewelry11") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry12") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "��. ����� ���� ���������. ����� �� ������� � �������, ����� � ��������� ��� ����� �������� ������, ��� �������� ���������.";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "��� ���. ��� ��������� �� ��� ������... ���, � ����������� �������.";
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry11", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry12", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "��, "+ GetSexPhrase("�������","�������") +", ��� � ���������, ��� ��������� ���! � ���� ������������� �� ��, ��� �� ��� ���� �������, ���� �������� ���� ������ � ��� �������. �������, ��� ��� ��� ����� ����������. ";
			link.l1 = "���! ������� � ����"+ GetSexPhrase(", ���������","") +", ����� �� ������"+ GetSexPhrase("","�") +"... ������, � ���� ���������.";
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "��, "+ GetSexPhrase("�������","�������") +", � �� ��� ����� �������.";
			link.l1 = "� ��������� �������...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+drand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterReputation(pchar, 10);
			dialog.text = "��, "+ GetSexPhrase("�������","�������") +", �� ������� ��� ������ ��� ���� ���������. ������� ��� ��������. � ������� �� ������ ����� �������.";
			link.l1 = "����������. ��������� ������ �������...";
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("�������� �� �� ������ ������. ���� ���.","�� ������ ��. ���� ��� ��... ��� � ������ ������.");
					link.l1 = "���� ���� �� �����?";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "��, ����� ����������� ��������! ����� ����� "+ GetSexPhrase("���������� �����������","����������� ����") +"! ������� ��� ��������� �������������... � �������, �� �� �������� ����, ��� ������� ��� ����������?";
					link.l1 = "��� �� ����� ��������. ������� � ������ ����������� � �������� - ��� ������ �����������... ";
					link.l1.go = "Node_210";
					link.l2 = "�� ��� ��, "+ GetSexPhrase("���������","�������") +"? ��� �����?";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "������� ���, �������. ��������, ��� ������� � ����� ���������� �������, �� � ���� �� ���� ������� ������.";
					link.l1 = "��, � ����, �� � ���� ������� ������. ��� ��� ���� ����������?";
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "����� � ���... ��� ���� �� ����� � ����� �� �������.";
				link.l1 = "������� ����. ��� �����, ���� ������ ������ �������.";
				link.l1.go = "Node_200End";
				link.l2 = "���! ������ ����� ��������� � ��������?";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "���, �������! ������ ��� �� ����� �� ��������. ��������� ���� �� ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", ����������.";
				link.l1 = "��� �����, ��� ���� ��� �� ������. ��� ������ � ������� ������, �������� ������� �������.";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("�� �� �������� �� ���... �� �����, �����.","��� � �� ������� �����? �����, �������.");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = "�� ���, ��� ��? ������ ���� �������� � ������ ����. ��� ������ ������ ����� ����. ��� ����������� �����, ��� ���� ������������� ������.";
			link.l1 = "� ��� � �����?";
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = "�� ��� ��������� ���������� �������. ���� �������... �� ��������� ��� ��� ����� �������� ����, � ��� ����� ������ - � ��� ���� ������ � ��� �������... ������, ��� � �� ��������. ��� ������ ��� ������ ��� ����, ��� ������ �� ����...";
			link.l1 = "��, �������� �������. � ��� �� ��, ��� � ������ �� ��� ���������?";
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = "� �� ���� ������� �������� ����, ���� ������ ��������. ��� ��� � ���� �� ����� � ������, ����� ������ �������������...\n��������� ����, ����������, �� ������, � � ����� ��� ������, ������� �� �� ������... �����, ������ �� ������� ���� �� ���� ���� �� �� ����.";
			link.l1 = "������, ��������, � ���� ������ ������ �����. � ��������� ��� ������� ���� ���������.";
			link.l1.go = "Node_200End";
			link.l2 = "�� �����, ���� �� ���� �� �������.";
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = "��� ������-�� �� �����...";
			link.l1 = "�� � ��������� �������.";
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "�������, �� ������� ��������� ���� �� ������.";
			link.l1 = "�����...";
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = "��, �������, � ����� ������� �����. ����� ������������.";
			link.l1 = "����� �� ����� ����� ���������.";
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = "�� � ����� ����. ������ ������������� �����... ���, �������� ��� ������, ��� ������ ������� ���� �������. �������� ��"+ GetSexPhrase("��","��") +", � ����� ������ �������...";
			link.l1 = "�� ���������, ���� �� �������.";
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			sGems = makeint(sti(pchar.GenQuest.EncGirl.price))/100;
			TakeNItems(pchar, "jewelry17", sGems);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "��, "+ GetSexPhrase("�������","�������") +", ��� �� �������� ���� ������.";
			link.l1 = "��������, "+ GetSexPhrase("��������","�������") +". ����� ������� � �����, ���� ��� ����� �� ����� �� ���������.";
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = "� ��� ��������������! �� ��������� ���� � ������� ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? �� ��, �����, ��� ����� �� ���� ��������.";
			link.l1 = "�������, �� �����. �����...";
			link.l1.go = "Node_122Next";
			ChangeCharacterReputation(pchar, 1);
		break;
		
		case "Node_220":
			dialog.text = "��, ������� - ��� ������� �������, �� �����, ��� ��� ����� ��� ���������. ����... ��� �� ����� ������ ��� ����� ������ �� ��������. �� ����������� �� ��������� �� ������� ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? � ��, �����, ��� �� ���������.";
			link.l1 = "������, �����, ������� ���, ���� ����.";
			link.l1.go = "Node_221";
			link.l2 = "���� � �� ����� ��������?";
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterReputation(pchar, -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = "��� �� ��� �� ���� ��������, ���� ������ ������� �� ���� ��������� ��������?";
			link.l1 = "�� �����...";
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");	
		break;
		
		case "Node_224":
			chrDisableReloadToLocation = false;
			if (PChar.sex != "woman")
			{
				dialog.text = "����� ������� �����. ������� ������ � �������, ��� ����� ��� ���-��� ����������.";
				link.l1 = LinkRandPhrase("� � ��� ��� ���� ����� ������, ��� ��� ������.","�� ����� �������������� ���� �������������. �� ��������, ��������.","��� ���� ��������� �������������. ������ ���������� ����.");
				link.l1.go = "Node_226";
				link.l2 = "��, �� ������. ������ ������ ����� � �������.";
				link.l2.go = "Node_227";
			}
			else
			{
				dialog.text = "������� ������� �� ���� ������, ����� �������. � ������� �� ������ ����� �������.";
				link.l1 = "�� ����� ����. ����� ���� ���������� ������.";
				link.l1.go = "Node_226_1";
			}
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (PChar.sex != "woman")
			{
				dialog.text = "����� ������� �����. ������� ������ � �������, ��� ����� ��� ���-��� ����������.";
				link.l1 = LinkRandPhrase("� � ��� ��� ���� ����� ������, ��� ��� ������.","�� ����� �������������� ���� �������������. �� ��������, ��������.","��� ���� ��������� �������������. ������ ���������� ����.");
				link.l1.go = "Node_226";
				link.l2 = "��, �� ������. ������ ������ ����� � �������.";
				link.l2.go = "Node_227";
			}
			else
			{
				dialog.text = "������� ������� �� ���� ������, ����� �������. � ������� �� ������ ����� �������.";
				link.l1 = "�� ����� ����. ����� ���� ���������� ������.";
				link.l1.go = "Node_226_1";
			}
		break;
		
		case "Node_226":
			ChangeCharacterReputation(pchar, -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterReputation(pchar, 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
//			chrDisableReloadToLocation = true;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // ��������������� ������� � �������� ������� �������� � �������
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "�� ��� ������ �������� ��� �������?";
				link.l1 = "���, �������, ��� ��� ����. ��������� ����������.";
				link.l1.go = "Node_232";
				link.l2 = "�����������, ��� ������.";
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = "��, ��� ����������� ���������, �������-�� � ���� ��� ������������� ���, ��� ��� ����� ������ ������ �������.\n ����� � ������� ��� � ��������, �� ��� �� ��� � �������������. � ������ � � �����������, � �� ������ ��������� �������, ��� �������� ���� �� �����. ������ ���� ����, ����� ����... � ������ ������ ���. � ������ ������ ���... � ����� ����, ��� �� ��� ���� �������...";
				link.l1 = "���! ��� ��� �����������! ���� �������������� �����, �� ��� ����� ������...";
				link.l1.go = "Node_229"; // �� ���������� - ��� ��� �������� �������
				link.l2 = "��������, ��������, ��� ������� ���� ���������, �� ������ ���� ����������� ��� ����.";
				link.l2.go = "Node_230"; // ������ � ����� ����������� �����������
			}
		break;
		
		case "Node_229":
			dialog.text = "��, ��� �� �� ���, ��� �����...";
			link.l1 = "��, ���������...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = "��! �� ��� ��!.. �� ��� �� ������?! ������! ������� � ���� �� ���� ����� � �����, � ��!..";
			link.l1 = "���� � �� �������� ������� �������, �� �� ��� ������� ���������� ��������, � ���� � ������� �� �������� ����. � �� ������� ����, � ����� ������ �� �� ��������...";
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = "�� ������ � ��� �� �� ���� �� �������! � ������ ������� �� ��������! ��������� ��� ��� �����!";
			link.l1 = "�����-�����. � ����� �������, � �� ����� ������� �������... ";
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			LAi_LockFightMode(pchar, true);
			ChangeCharacterReputation(pchar, 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterReputation(pchar, -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "��� ����� ���� � ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City) + ". ���� � ������ ���������� �������� - �����, �� ������� ����� �� ����, � ����� ���������, ��������� ������. ������� �������, � ���������� �������� � ����� �������� ������. ��� ����� ����� �� ����� ��������, � � ������ �������� �� ����� �������� �� ��������.\n�������� ���� ������� �������� �������, � ����� � ������ �� ����, ��� ����������� ���������� �������� ����������� �� �������. �� ����� �� ���� �� ����������, � �����-�������, ����� ���� ���-�� ����������, ������� ���� �����-�� ��������. ��������� �� ������.";
			link.l1 = "��� ������ �� ��� � ����� �����! ���� �� ���������� ���������� � �����, ��� � �������?!";
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = "�� ���� �! ��� ��� ���� - ��������� ������, ������, ��������� - �������� � ������� � �������� ��������. � ��� �������� � ������� ��������. � � ����� ������ ��� ������� � ����� ������� �� �����, �� ������ ��� � �����������. �� � ��� ���� �� ���� ������ ��� ����� � ����������? � ������ � � ������ ��������� �� ����... ���� � ������ �������...";
			link.l1 = "��� �������� ���������! ���������, �������. � ���� ������.";
			link.l1.go = "Node_235";
			link.l2 = "��� �����. � ������� ���� �������...";
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = "�� ���� ��������� ���� ���������? ������� ���� ����� �����, ���� ��������� �����?";
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = "��� ������� ���, �������... �� ��� ���� ����� � ���� ������������.";
			link.l1 = "����� ��������?! �����, ���� ���� �� ���������...";
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("��","���"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = "��, �������, � � �� ����� ���� ������� �� ����.";
			link.l1 = "�� �����. � ����� �����.";
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("��","���"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "��, � �� ������, � ���� ���-�� ���������.";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "��� �� ���� ����� ���������? ���, ����� ���� ����.";
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = "������, � ������ ��� �� ���"+ GetSexPhrase("��","��") +". �� �������, ��� ��������� ������� � ������� ��������?";
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "������� ���, "+ GetSexPhrase("����������� �������","����������� �������") +". � ������� �� ������ ����, ��� �� ��� ���� �������. � ���� � ���� ������ ���, ��������� �������� ��� ���� ������, ����� ���� ������ ��������� ��� � �������� ���� ����� ����� �������.";
			link.l1 = "������� ����. ������ ���������. ������...";
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = "������� ��� ������ �����?..";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "������� ���� ����� �����, ���� ��������� �����?";
				link.l1.go = "Node_237";
			}
			link.l2 = "�������� �����. ������ ������ ���� ���� ����������. ������!";
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","��"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("","�"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterReputation(pchar, 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterReputation(pchar, -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = "������� ���, �������. ���� �� �������, ��� � ����. ����� ���, �� ��������, �������, � ��� ���������� � ����������.";
			link.l1 = "������, "+ GetSexPhrase("���������","�������") +", ��� ������������� �������. ����� ���-������ � ��������� ���...";
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = "����� ����... �� ��� �, ����� ��������, � �� ������ ��� ���. � ���� � ���� ������ ���, ��������� �������� ��� ���� ������.";
			link.l1 = "�������! ����-����, ������� ���������...";
			link.l1.go = "Node_247";
//			link.l2 = "�� ������������� �������, ��� ��� ����������?";
//			link.l2.go = "Node_248"
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = "��, � �� ����... ����� ����, �����-�� ����� ������� ����� ��������� �����. �� � �� ���� ������� � ��� �����.";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "�������. ���, ����� 5000 ��������. ����� ������ �������.";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "�������. ���, ����� 25000 ��������. � ����������� �����.";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "�������. ���, ����� 35000 ��������. ������� ���� ����� '����'.";
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterReputation(pchar, -5);
			dialog.text = "������� ���, "+ GetSexPhrase("����������� �������","����������� �������") +". � ������� �� ������ ����, ��� �� ��� ���� �������.";
			link.l1 = "������ ���� ���������. ������...";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "������� ���, "+ GetSexPhrase("����������� �������","����������� �������") +". � ������� �� ������ ����, ��� �� ��� ���� �������.";
			link.l1 = "������ ���� ���������. ������...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterReputation(pchar, 2);
			dialog.text = "������� ���, "+ GetSexPhrase("����������� �������","����������� �������") +". � ������� �� ������ ����, ��� �� ��� ���� �������.";
			link.l1 = "������ ���� ���������. ������...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple("�� �������, �����-�� ����� �������� ��� ���������� ���������� �� �������? Ÿ ������� � ������ ����� � �������. �������, ��� ��������� ������� ����������� �����.",  
				"�������? � ��� � ����� ������� �����-�� ����� ��� ����������. �������, �� ������� �������, �������������� �������� ������� �������� �������. ����� �� ��������� �������� ���� ��������� ������ � ���������. ���� ���� ���� �� ��� �����, ���� ��� ����� ���������?"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = "�� ������, �������! ���� ���� ����� ������ ����� �� ���� ���������� - ����� ���������... ������ ��� � ��� ������ � �������� ����� ��������! ����� � � �������� ��������, �� �������� ����� ������! �� ����������� � ����������� ������, ������!";
			link.l1 = "�� ���� ��, "+ GetSexPhrase("���������","�������") +", �� ���������� �������? ��� �� ����, ��� �������, ���� �����. ������ ����� - � ����� ��������� ���� ������, �� �� ������ ���...";
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "���!.. ���, �������, � ����� �������� �� ����� " + pchar.GenQuest.EncGirl.sLoverId + " �, ����� ����, ������ �� ���� �����! � ���� ������! �������, ��� �� � ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + " �������� � ������� �� ����� ����� ������, ���-��� �� ���� ����� � ���� �� ����� ������. � ��� ���� �� ���� ����� ���� �� � ��� �����... �������� ���� � ����, ����� ���.";
			link.l1 = "�����, �����. �� ������ �������, ���� ���� ������...";
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "�������, �� ������� ��������� ���� � ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) +".";
			link.l1 = RandPhraseSimple("����� �, �����.","�� �������� - �������.");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":		
			chrDisableReloadToLocation = false;
			if(rand(2) > 0)
			{
				dialog.text = RandPhraseSimple("������� ���, "+ GetSexPhrase("������","�������") +", ��� ���. �� � �� ����, ��� �����������.","������� ��� �������, "+ GetSexPhrase("�������","�������") +". ���� �� �����������, ��� �� � ������, �� �������� �� �� �������.");
				link.l1 = RandPhraseSimple("������ ����� ���� �����. ��, ��������� ����������...","� ��������� ��� ������ ����������... ��, ��� �����, ���� ���� ����.");
				link.l1.go = "Node_1End";
				link.l2 = "����� ����� ���� ����� ���������? ���� ���� ���� � ������� �������?";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "��, "+ GetSexPhrase("�������","�������") +", � �� � �� ����, ��� ��� �����������.";
				link.l1 = "�� ����� �������������. ������ ���"+ GetSexPhrase("","�") +" ������...";
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_261":
			dialog.text = "�� ������� ���� � �������? ��� ����� ��������� ���� ���� � ���������, � ��� ���������������...";
			link.l1 = "���, "+ GetSexPhrase("���������","�������") +", ������ ��� ����. � ���� � ��� ��� �� �����.";
			link.l1.go = "Node_262";
			link.l2 = ""+ GetSexPhrase("�� ��� �������! ���� ��� ������� ������� �� �����!","� ���� �� ����� �����������?") +" �����...";
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation) >= 80)
			{
				dialog.text = "� ���� ���� ������� �����. �������� �� � ���� ���� �������������!";
				Link.l1 = "�������. ������ ���������� � ��������� ���.";
				Link.l1.go = "exit";
			}
			else 
			{
				if(drand(1) == 0)
				{
					dialog.text = "� ���� ��������, ��� �� ���� ������! ����� ��� �����, "+ GetSexPhrase("����� �� ������� � ������ �������","����� �� ������� � ������") +"!";
					Link.l1 = "�������. ������ ��� ����� ������������ �����.";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "� ���� ���� ������� �����. �������� �� � ���� ���� �������������!";
					Link.l1 = "�������. ������ ���������� � ��������� ���.";
					Link.l1.go = "exit";
				}
			}
		break;
        //#20200315-01
        case "CitizenNotBlade":
            npchar.chr_ai.type.checkFight = 999999.0;
            Diag.TempNode = "ThanksAgain";
			dialog.text = "� ���� ���� ������� �����. �������� �� � ���� ���� �������������!";
			Link.l1 = "�������. ������ ���������� � ��������� ���.";
			Link.l1.go = "exit";
		break;
		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "� ���� ��������, ��� �� ���� ������! ����� ��� �����, "+ GetSexPhrase("����� �� ������� � ������ �������","����� �� ������� � ������") +"!";
			Link.l1 = "�������. ������ ��� ����� ������������ �����.";
			Link.l1.go = "exit";
		break;
	}
}
