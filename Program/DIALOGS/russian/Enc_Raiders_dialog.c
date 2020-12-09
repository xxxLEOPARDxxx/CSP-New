void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			ChangeCharacterReputation(pchar, -1);
			int iMoney = makeint(makeint(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // ��������� �� ����� ����
			npchar.DontClearDead = true;  // �� ������� ���� ����� 200�
			AddSimpleRumour(LinkRandPhrase("�� �������, � �������� ��������� " + GetFullName(npchar) + " ��������� ��������� ������. ���� ������� ������� � ���������. �� ������ ������� " + FindRussianMoneyString(iMoney) + ", ��-��... ", 
				"��, ������� " + GetFullName(pchar) + ", � ��� ������, ��� ��� �������� ������ " + FindRussianMoneyString(iMoney) + ", ����� ���������� �� �������� ������� " + GetFullName(npchar) + ". ��, ��� � ���� ������� - �� �������! ��-��-��!", 
				"�� �� ������� � ���, ��� ������� ��������� ������ �� ������-�� ��������? ��� ���, ��� �������� �� ����� " + FindRussianMoneyString(iMoney) + "!"), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("�� �������, �������-�� � �� ����� ������� " + GetFullName(npchar) + "������ �������. �� � �������� ����� �������� "+ GetSexPhrase("������-�� ��������, �� ��� ��������","�����-�� �������, �� �� ���������") +" �� �� �� �����. � ����� ��� �������� ��������� ��� ������� � �����, ��-��! ��� � �������, ��� ��� �� �� ������� �������� ������ �����������.", 
				"��� ������� ���, ������� " + GetFullName(pchar) + ", ��� �� �������-�� ��������� ����� ����� ������� " + GetFullName(npchar) + ". � �� ������ ����� �� ����� �� ���� �����������. ���� ��� ������� ���������� �� ����� �� ������� ���������, ���� � ����� - �������� �� ������ � �������."), 
				"�� �������, "+ GetSexPhrase("�������-�� �����-�� ������� ���","�����-�� ������� ����") +" ��������� ����� ����� ���������� " + GetFullName(npchar) + ", ��� �������� � �������� � ������� ����� �� ������� ��������. ���������, ������� �� ��� ������� � ��� ����� ������������.", 
				"�� �� ������� � ���, ��� ������� ������ " + GetFullName(npchar) + " �� ������ ������������ ������� �������� "+ GetSexPhrase("������-�� ��������","�����-�� �������-��������") +"? ��� ���, �� ��� �� ���� - ������� ������"+ GetSexPhrase("��","���") +" ������� �������. �������, ��"+ GetSexPhrase("","�") +" �����"+ GetSexPhrase("","�") +" ���� ����-���������� �� ��������, ��� ����� ���� ������. ������� �������, ��� ���� ��� ����, ��������� �������� �� ��� � ����� �����, ����� ������ ������������, ������� ������� ������ ���������..."), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_SetCitizenTypeNoGroup(sld);
				//#20200315-01
                sld.chr_ai.type.checkFight = 999999.0;
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("����! ������ ������! ���������� ������, ��� ��������� �� �����!",
				"�� � �����, "+ GetSexPhrase("������","��������") +"! ������ �� ������ � �� ������� ������, ���� ����� ������!",
				"����, "+ GetSexPhrase("������","��������") +"! ��� ������� ������! ������ ������ - ����� �������."),
				LinkRandPhrase("��, "+ GetSexPhrase("��������","�������") +"! �� ��� ������! ���� ���������, �� ������� �� ���� ���� ������.",
				"�������-�� �������, ������"+ GetSexPhrase("��","��") +". ���� ��������, ��� ����������� ������ � ���� ������.",
				"������-��, "+ GetSexPhrase("��������","�������") +". �� ��� � �������� ���������, ����� �� ������ ������ � ���� ������. ������ ����� �� ���������, ���� �� ����� �� �����."),
				"�� ��������, "+ GetSexPhrase("��������","��������") +"! ���� ����������� � ����� �� �����.");				
			Link.l1 = LinkRandPhrase(LinkRandPhrase("��� �� �����?","� ��� ����?", "� ��� ��� ��?"), "��� �� ������ � ����?", "� ���� ��� ��?");
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("����� ����������?! ��� ������ � ���������!", 
				"����������, ��� ��?! ������, �� ���������� �������? � ��� ���������� � ��� ���� ������...",
				"� ����� ���� �� �����, ��� �������� ���������� � "+ GetSexPhrase("����������","��������") +" � ������� ����������? ������� ��������� ����..."),
				LinkRandPhrase("�� ��, ������! �������, ���� ������ ����� �� ����, ��� � ����.",
				"����, ���� � ���� ������. �������, ������� �������� ��� �� ���������?",
				"�-�, �����������! ������ ���, ������, � �� �� �� ����������..."),
				LinkRandPhrase(RandPhraseSimple("�-�, ����������! � ���� � ������, ��� �� �������� ��������!",
				"��, ������! �� ���� ������ �� ������, � �� � ��������"+ GetSexPhrase("�� ��������","� �������") +" � ����������� ������."),
				"� ������ ��� ��, ������ ������� ��� ��������!",
				"����� ����������! ��, �������� � ��� �� ������, � �� ���� ����� � ����� ��������� ����!"));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase("� ���� ��������, ��� �� ���� �� ����� ��� ���������� �����? ����� ��� ������ ���������, � �� ���������.", 
				RandPhraseSimple("�� �������, ��� � ������� ������? ��� ��� ��� ����� ��������� ��� ����.", 
				"�� ���� ��� ���������� ����� �������, �� � ������ �� ������ ����� �����, ��� ��� �� ����� ��������."),
				RandPhraseSimple("��� �� ����� ��������� ������� ����. ���� ������������ ���������� �����, � ������ ��� ������������"+ GetSexPhrase("","�") +" � �� ��������.",
				"� �� � �������� ���������"+ GetSexPhrase("","�") +" ��������, �� �����, ���������� �����, ������� � ������ ��� ��������"+ GetSexPhrase("","�") +", �� ���� ��������� ������ ���������� � ������ ������."));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase("�� ������������ �����������! ���������� ��� ������, �����, �����, � ������!",
				"�� ���, � �������� ��������� �� ������"+ GetSexPhrase("","�") +"? �� ������������ �� ����� ������� - ������������ � �������!",
				"���, ��� ������������ �������� �����������, ������� ����� ������ ���� ��������... ���, ���� � �� ����������."),
				RandPhraseSimple("�� ����� ������ - �� ����������� ������ ��� ������ � �������, ��� �� �������� �����, � �� ������ � ����� �������, �� ������ ������� ���� ���� �� ����������, ��-��.",
				"� �� ����� �� ��������. ������ ���������! ���� �� ������, ����� � ��� � ������ ����� ������!"),
				"�������, ��� �� ���"+ GetSexPhrase("��","��") +" ����������"+ GetSexPhrase("��","��") +" - ���������� ��� ������, ���� ���� ������!");
			Link.l1 = "���������! ��������! � ���� � ����� ������ " + makeint(makeint(Pchar.money)/20)*10 + " ��������.";
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("����� �������? ��� ������� � ������, � � �������, ������� ������ �� ������.",
				"�� ��� �� ������, ������! �������� ���� ���� ���� ������� �����!",
				"����� ���������������! ��� �, ��������, �� ����� �� ���������� ������ �����"+ GetSexPhrase("�� ������","�� �������") +"!"),
				LinkRandPhrase("�� ��� �� ������� �������� �� ����� ��������!",
				"�� �� �������! ��, ����� �������� ����� ������!",
				"���, �����������, ��������� �� �������� �� �������! �� ������ ������� ����� ������!"),
				RandPhraseSimple("� � ���� �� �����, ��� � ����� ����� ����� ������� ������?",
				"� ���� �� �������, ��� � ������� ��������"+ GetSexPhrase("","�") +" � � ������� �� ��������� �������"+ GetSexPhrase("","�") +"?"));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation) < 11 || makeint(pchar.reputation) > 90;  
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("��� ����! �����, �����. � �� ������� ��� ���������.", 
					"�� ���� ��� ���� �������, �� � ��������� - ������ ����"+ GetSexPhrase("��","��") +" �������! �� ������ ���������, ��-��.");
				Link.l1 = RandPhraseSimple("��, ��� �����?", "�����-�����, ����, ���� ���.");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk1 = makeint(pchar.reputation) < 51 && makeint(pchar.reputation) > 41;
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("� �� ���� �������� ��������, ���� ������� �� �������.", 
						"��� ����! ������� ��������� ���� ��-��������, ���� ���� �� ������"+ GetSexPhrase("","�") +".");
					Link.l1 = "��, ��� ������. � ��� �����������"+ GetSexPhrase("","�") +".";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("� ��� ��� ���� �������? � ���� ����� �� �������� � �� �� ���������. ��� ��� ����������� ������ � �������� ������ �������.", 
						"�� ���� �������� �����"+ GetSexPhrase("","�") +"?! � � ���� ���� ��� ������� ��� �����, ��� ��. ��� �� ���� ��� ������� �� ����!");
					Link.l1 = "���������! ��������! � ���� � ����� ������ " + makeint(makeint(Pchar.money)/20)*10 + " ��������.";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase("��, �� �� ���� ���� ���� �����������.", 
						"�� �������� �������� � ������ � ����� ����� ���� �����. ���� ����� ������������.",
						"����� �������� �� ����� �������� �������������!"),
						"��, �� �� ��� ���� �� ������...");
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
			bool z_ok = (GetCharacterSkillToOld(Pchar, "Fencing") >= 7) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation) <= 30);
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("��, �� ��������� ���, "+ GetSexPhrase("��������","�������") +"! � �������! ��� ����� �������!",
					"�����, � ���������. ������ ����, ��� ���"+ GetSexPhrase("�� �������","�� �������") +"."),
					"���, ����� "+ GetSexPhrase("'�������� �������'","'���������� �����'") +"? �����, ��� � �����...",
					"������, "+ GetSexPhrase("��������","�������") +". �� ������, ���������� ��"+ GetSexPhrase(" - �� ����� ���� �������","") +". ��� �� ����� ��������.");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("�� ��� ��, ����� �� �������!",
					"������ �� �� ��� ����, ���� ����� ����.",
					"�� ��������, �� ����������� ��� ������."),
					RandPhraseSimple("� ��������� ��� ������, �� ���� ��� ����������.",
					"����������� ����, ��� � ������� ����"+ GetSexPhrase("��","��") +"."),	
					RandPhraseSimple("����� �������� ��� �� ����� �� ������. ��������.",
					"��� �, ��� ������ �������. ��������� ����������!"));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("��� ��, ��������. ������� ������� ���� ������� �������.",
					"����� �������?! �� �� ���� �������� ����� ��������! �� ������ ��?",
					"��� ��! ������ � �� ���������, ���� �� ������� ���� �����.");
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase("� ���� ���"+ GetSexPhrase("","��") +" �� ���� � �����! ������ ����� �� ����!",
								"��� �� ��� ������"+ GetSexPhrase("","�") +", �������! ������ ���������, ��� ������!",
								"�� ���! � ����� ���� �� �����! ������ ������ � ������� �������!");
				Link.l1 = RandPhraseSimple("� ������ ��� ����� ���� � ������!","�� ���� ���������, �������?!");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(makeint(makeint(Pchar.money)/20)*10 >= makeint(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("������! ����� �� ���� � ����������!",
					"�������, �� �����, ��� ������. ������� ����� ���� � ����� ���������! ������ ����."),
					"��� - ��� ������ ����! ��� ������� ���� ��� �������� - ������� ��������� ������ ��������, � � ������� ����� � ����������, - ��-��.",
					"� ����� �� ���� ������ ��� ����� - �� ����� ������� �� ��������, "+ GetSexPhrase("���� �� ����� ������! ���� � �������� �������, � ��� ���� ��� - ����� ������","�������. � �� ���� �� ������ �������� �����") +".");
				Link.l1 = "��������� ����������!";
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = "�������, �� ������ ���� ������! �� ������, ������ � ���� �������� - �������, ���� � ���������.";
				Link.l1 = "���������!";
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("����� ��? �����, ���� �����, � ����! � �� ���� � ���� � ������������.",
				"���? �� �� ������ �����"+ GetSexPhrase("","�") +"? ��-��-��!",
				"������, "+ GetSexPhrase("��������","�������") +", �� ��� ������"+ GetSexPhrase("","�") +"! �������� � ���� �����, ���� ���"+ GetSexPhrase("","�") +"!");
			Link.l1 = "��, � ��� �����.";
			Link.l1.go = "Exit";
			Link.l2 = "� �������"+ GetSexPhrase("","�") +", ��� ��� ����� �������������. ���, �����"+ GetSexPhrase("","�") +" �������� ��������...";
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("��� ���� �����? �� �� ������������, ��� �� �������!",
				"������� �� ����, "+ GetSexPhrase("������","������") +". � ���� ���� ����, � ���� ����, ��� �� ����� ���������� ����������!",
				"�����, "+ GetSexPhrase("��������","�������") +"! ���� ������, ������� �� ���-���� ������ ������ ���� ������?");
			Link.l1 = "��, � ��� �����.";
			Link.l1.go = "Exit";
			Link.l2 = "� ��������"+ GetSexPhrase("","�") +", ��� �� �� �����������! ��� ��� �������... ����������!";
			Link.l2.go = "Exit_Fight";
		break;
        //#20200315-01
        case "CitizenNotBlade":
            npchar.chr_ai.type.checkFight = 999999.0;
            Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("� ��-���� �����"+ GetSexPhrase("","�") +" �������� ��� �� ���� ���� ����!",
				"�������! ��������! � ���� ����!",
				"��������! "+ GetSexPhrase("�� ������","��� ��������") +"! �� ������ ����!");
			Link.l1 = "������! � ����� ���� �������� ���������! � ������� �����, ����� �������!";
			Link.l1.go = "Exit";
        break;
		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("�������! ��������! � ���� ����!",
				"��������! "+ GetSexPhrase("�� ������","��� ��������") +"! �� ������ ����!",
				"������! � ����� ���� �������� ���������! � ������� �����, ����� �������!");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("����� �� ���� - ��� �� ������!",
				"������ ����� ���� ������!",
				"�� ����, �� ��� ����!"),
				"���� ��� ������ ��� ������ ���� ���������.",
				"������ �������, �����������!");
			Link.l1.go = "exit_Fight";			
		break;
	}
}
