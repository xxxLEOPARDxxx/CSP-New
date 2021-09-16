void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	int iMoney;
	
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
			//int iMoney = makeint(makeint(Pchar.money)/20)*10;
			iMoney = sti(NPChar.moneyfee);
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
			bool bRape = GetOfficersQuantity(pchar) == 0 || rand(4) == 0;
			if (pchar.sex == "woman" && bRape)
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("�� ���� ��, ����� �������� ������ �� ��������! ", 
				"��� ��� ��� ������� �������, �������-�� � ����� ��������! ", 
				"�� ��� ������, ��������, ���� ���� � ���� ����! ")+
				LinkRandPhrase("�������, �� �� ������, ���� �� � ����� ������� �����������? ����� �����, ������� � �� ��������.", 
				"����� ��-��������: ����������, ������� ���� � ������ ���� ������.",
				"�� �� �� ������, ��� ������� ������ ��� ���� ���� ������? ������� ���� ������� ������������� � ���� ��������� ������!"),
				
				LinkRandPhrase("������� ��� �����! �������, � ��� ��������, ��� �� ������� �������� �����?  �������� � ���������...",
				"����, ������, ���������� ������ �� ����, ���� ������ �� ��� �����. ����� ������ �� �����������, ���� ������� �� ������ ����������� � ��� ����... ������ ��������, ������ ����������� �������, �����.",
				"�� ���, ����, �� ����� ��� �� � ��� ��������? �� �������� �����! ��� ��������� ��� � ����, �����!"))

				Link.l1 = "�����, ����� ��� ����, �������."
				Link.l1.go = "Rape";
				if (GetOfficersQuantity(pchar) > 0)
				{
					Link.l1 = LinkRandPhrase("�� �� ���, ���������� � ���� �� �����, �� � ��� ������ ����� �� ��������. ", 
					"�� �� ������� � ����� �������� ����������, ��� ����������� ��� ����� � ����� ���� �� �����. ", 
					"�� ��� �� ����������� ���� �����, �� �������, ����� �� ��������� ���� ������ ����� ������ � ��� � ����� ���������? ")+
					LinkRandPhrase("����� ����� � ������� ����, ��������, � �� ��������� ��� �������������.",
					"������, ��� ������ ��������� �������� �����, ���� �� ��������� �����?",
					"������� ����� �� ������ ����� ���������� ���?")
					Link.l1.go = "Node_2_woman";
				}
				Link.l2 = RandPhraseSimple("�� �� �� �����, �����. � ���� �� ������� ��������, ���� � �������� �� ����.", 
				"�������-�� ��� � ���� ����� ���������, ���������� ������!", 
				"�� �� ����� �������� ����� �����, �� ���-��� ������? �� �������, ��� ������ ��� ����� ��������.");
				Link.l2.go = "CheckSkills";
				break;
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
			iMoney = 100*MOD_SKILL_ENEMY_RATE*sti(NPChar.EncQty)+makeint(100 * sti(PChar.rank))+makeint(100 * sti(NPChar.rank)*sti(NPChar.EncQty));
			NPChar.moneyfee = iMoney;
			dialog.text = LinkRandPhrase(LinkRandPhrase("�� ������������ �����������! ���������� ��� ������, �����, �����, � ������!",
				"�� ���, � �������� ��������� �� ������"+ GetSexPhrase("","�") +"? �� ������������ �� ����� ������� - ������������ � �������!",
				"���, ��� ������������ �������� �����������, ������� ����� ������ ���� ��������... ���, ���� � �� ����������."),
				RandPhraseSimple("�� ����� ������ - �� ����������� ������ ��� ������ � �������, ��� �� �������� �����, � �� ������ � ����� �������, �� ������ ������� ���� ���� �� ����������, ��-��.",
				"� �� ����� �� ��������. ������ ���������! ���� �� ������, ����� � ��� � ������ ����� ������!"),
				"�������, ��� �� ���"+ GetSexPhrase("��","��") +" ����������"+ GetSexPhrase("��","��") +" - ���������� ��� ������, ���� ���� ������!");
				dialog.text = dialog.text+ "\n����� �� �� ���������, ����� "+iMoney+" ��������. �������� �� "+makeint(iMoney/sti(NPChar.EncQty))+" �� �����.";
			//Link.l1 = "���������! ��������! � ���� � ����� ������ " + makeint(makeint(Pchar.money)/20)*10 + " ��������.";
			if(sti(pchar.money) >= sti(NPChar.moneyfee))
			{
				Link.l1 = "���������! ��������! ������� ���� ������!";
			}
			else
			{
				Link.l1 = "� ���� ��� ������� �����.";
			}
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
		
		case "Node_2_woman":
			iMoney = 100*MOD_SKILL_ENEMY_RATE*sti(NPChar.EncQty)+makeint(100 * sti(PChar.rank))+makeint(100 * sti(NPChar.rank)*sti(NPChar.EncQty));
			NPChar.moneyfee = iMoney;
			dialog.text = "����� �� �� ���������, ����� "+iMoney+" ��������. �������� �� "+makeint(iMoney/sti(NPChar.EncQty))+" �� �����.";
			//Link.l1 = "���������! ��������! � ���� � ����� ������ " + makeint(makeint(Pchar.money)/20)*10 + " ��������.";
			if(sti(pchar.money) >= sti(NPChar.moneyfee))
			{
				Link.l1 = "���������! ��������! ������� ���� ������!";
			}
			else
			{
				Link.l1 = "� ���� ��� ������� �����.";
			}
			Link.l1.go = "CheckMoney";
			Link.l2 = RandPhraseSimple("�������? �� ��� ��� ��������, ��� �������� ���� �� ��� ��������.",
				"� � ���� ��������� �� ���� ������������. � ������ ���������� ��� ������� ����� ���� �����!");
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation) < 11 || makeint(pchar.reputation) > 90;  
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckOfficersPerk(pchar, "SeaDogProfessional"))
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
			if (z_ok || CheckOfficersPerk(pchar, "SeaDogProfessional"))
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
			if(sti(pchar.money) >= sti(NPChar.moneyfee))
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
		
		case "Rape":
			AddCharacterExpToSkill(pchar, "Leadership", -100);
            AddCharacterExpToSkill(pchar, "Fencing", 50);
            AddCharacterExpToSkill(pchar, "Pistol", 50);
            AddCharacterHealth(pchar, -10);
			Diag.TempNode = "OnceAgainRape";
			AddDialogExitQuest("PlaySex_1");
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgainRape";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();
		break;

		case "OnceAgainRape":
			Diag.TempNode = "OnceAgainRape";
			dialog.text = LinkRandPhrase("�� ���������, ������ ����, ���� ���.",
				"�������, �� ������ ��� ��������, ��-��. � ����, ������ ����.",
				"���� �� ������ �� ������ �����, ����� ���� �������-���������.");
			Link.l1 = "��� �����.";
			Link.l1.go = "Exit";
			Link.l2 = "�� �� ���, � ���� ������ ����� ����, ��� �� ��������, �����!";
			Link.l2.go = "Exit_Fight";
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
