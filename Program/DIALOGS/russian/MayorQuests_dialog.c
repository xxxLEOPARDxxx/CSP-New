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
		//----------------- ����������� ����� ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //������ �����
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //���������� ����� 
			for(i = 1; i <= 29; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("������ �� ����� "+ GetSexPhrase("��������","�������") +"! ���� ����� " + GetFullName(npchar) + ", � � �� ������ ���������� � ���� �����...",
				"������-�� ��� ���������� ������ ��������, "+ GetSexPhrase("��������","�������") +", � ���������! ���� ����� " + GetFullName(npchar) + ", �, � �������, �� ������"+ GetSexPhrase("","�") +" ��� ���...",
				"���������� ��� ������, ��� � ���� ����, � ���������� ���������� ������ ��������. � ���������, ��� ��� �, " + GetFullName(npchar) + ", �� ����� ��������. �� ���� ������� ����������!");
			Link.l1 = LinkRandPhrase("���, ��� �� � ���� ��� ����� " + GetFullName(npchar) + ", � ������� ������� ���������� " + sTemp + " ������ � �������?",
				"�-�, ��� �� � ���� ��� ����� ������, �� ������� �������� ������� ���������� " + sTemp + " ?!", 
				"���"+ GetSexPhrase("","�") +" ������ ����, " + GetFullName(npchar) + ". ������� ����������, " + sTemp + ", ������ � ���� � �������...");
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("��, � �������� � ���� �����, ��-��... ����, � �� �� "+ GetSexPhrase("��������� �� ���","��������� �� �����") +" �����������, "+ GetSexPhrase("��������","�������") +" �� �������� ��������� �� ����?",
				"���������� - ��� ������� ����, ���� ��������? ��, � �� "+ GetSexPhrase("��������� �� �� �����, ������������","�� ��������� �� �� �������, ������������") +", �� �� ���� �������?",
				"'���������' ������������ ����������� �� ��� - ����, ��-��. � �� ������ �� ���� ������? �����, �� ������ ���� �� ��� ����?");
			Link.l1 = LinkRandPhrase("����� ���, ��������. �������� � ������!", "���� ��, ����� �� ����������. �� ��� ��, ���� ���������� � ����� ����������. ����������, ������ ���...", "��, ��� � � ����. �������� ������, ��������! ���������, ������ ����� � ���� �����.");
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase("�� ���, ��� ��! ��� ��� �������� ���������� �� � ����...", "���, � �� ����� ���� �� ������, �� ����������, � �����...", "���-���, �� � ���� ����! ��� �������� �� � ����...");
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("���-�� �����, "+ GetSexPhrase("�������","�������") +"... � ������ ����������!",
				"� ��� ���������� �������, ����"+ GetSexPhrase("","�") +" �� ��, ������� ������ � �������� �� ��� ����... �����, ������ ������. ���� ������, "+ GetSexPhrase("����� � �������","�����") +"!",
				"�������, �����! ����� ������ ��������� ������� - �� ����� ���� �� ������... �����, ����������, "+ GetSexPhrase("��������","�������") +".");
			Link.l1 = "�� ��������, ����� �������������...";
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //���� �����, �� �������
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 30; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 30; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//----------------- ������ ��������� � �������� ----------------------
		case "SeekSpy_house":
			chrDisableReloadToLocation = false;
			dialog.text = "��� ��� �����, " + GetAddress_Form(PChar) + "?";
			Link.l1 = "��� ����� ������, ��� �� �����. ���������� ������, ��� �� � ��� �� ����� �������?";
			Link.l1.go = "SeekSpy_1";	
		break;
		case "SeekSpy_1":
			dialog.text = "��, � ���"+ GetSexPhrase("","�") +"-�� �� ��� "+ GetSexPhrase("�����","�����") +", ����� � ������� �� ���� �������?";
			Link.l1 = "� �������� �� ��������� �����������, ��� ���������� ���������!";
			Link.l1.go = "SeekSpy_2";	
		break;
		case "SeekSpy_2":
			dialog.text = "�� � � ����� ��� ���?";
			Link.l1 = "�����, � �� ��� ���, �� �����-��, ��� ������, ������� � �����������. ��� ����������...";
			Link.l1.go = "SeekSpy_3";	
		break;
		case "SeekSpy_3":
			dialog.text = "���, � ����������� � �� �����. ������, ��� "+ GetSexPhrase("�����","�����") +" ���������. �� � ������ �������� ����� ������ "+ GetSexPhrase("�����","�����") +".";
			Link.l1 = "���, �� �� ����� ���-������...";
			Link.l1.go = "SeekSpy_fight";	
		break;
		case "SeekSpy_fight":
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SeekSpy_Afrer");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "CitizenNotBlade":
			dialog.text = "�� ��� �����?! ������� ������, ������!";
			link.l1 = "������ ������������ �����...";
			link.l1.go = "SeekSpy_house";
		break;
		//----------------- ������ ��������� �� ����� ----------------------
		case "SeekSpy_street":
			Diag.TempNode = "SeekSpy_street";
            dialog.Text = NPCharRepPhrase(npchar,
		            PCharRepPhrase(LinkRandPhrase("�, ��� ��, "+GetFullName(Pchar)
                    +", "+ GetSexPhrase("������ ��������","��������� ������") +"", ""+ GetSexPhrase("��� ���� ������, �������","��� ���� ������, ���������") +""
                    + Pchar.name, "�, �� ��� �� ���"+ GetSexPhrase("","�") +" ������� "
                        +GetFullName(Pchar))
                                    +LinkRandPhrase(". �����, ���� ��� ��� �� ���� �����!", ". �, ��������, ��� ������, "+ GetSexPhrase("����","�������") +".", ". �, ��� ����, ��� �� �������!")
                                    +LinkRandPhrase(" ��, ������, ���� ���� �����?", " ���� ���� �� ���� ���?", " ����� ��������� ���� �� ��������?"),
                                    LinkRandPhrase(TimeGreeting() + ", ������� ", "������������ "+GetAddress_Form(NPChar)+" ", "����������� ���, ������� ")+GetFullName(Pchar)
                                    +LinkRandPhrase(". ��� ����� ���� ����� "+ GetSexPhrase("������ ���������� ��������","������ �������") +", ��� ��, �� ����?", ". ����� �� ������?", ". ��� �� ���� ��� �� ������ ������?")
                                    ),
                                    
                    PCharRepPhrase(LinkRandPhrase("������������ ������� ", "�����������, ��, ��� �� "+GetAddress_Form(NPChar)+" ", "�, ������� ")
                                    +GetFullName(Pchar)
                                    +LinkRandPhrase(" � �����"+NPCharSexPhrase(NPChar, " ", "� ")+"�� ������ � ���� �� ����������,",
                                                        " �� �����, ��� ���"+NPCharSexPhrase(NPChar, " ", "� ")+"��� ������, ��", " ����, �� ��� ����, ��� ��� �� ����������. �")
                                    +LinkRandPhrase(" ��� ��� �����?", " ����� �� ������?", " ��� ���� ���� "+NPCharSexPhrase(NPChar, "�������?", "�������?")),
                                    LinkRandPhrase(TimeGreeting() + ", ������� " + GetFullName(Pchar) + ". ��� ���� ������?",
                                    "�, �� ��� �� ��� ������� " + GetFullName(Pchar) + "! ��� �� ������ ������ �� ���� ���?",
                                    "������������, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + ". �� ���-�� ������?"))
                                    );                  
                        
	   		link.l1 = PCharRepPhrase(RandPhraseSimple("���� �����������, � �����.", "���, ������ - ������ "+ GetSexPhrase("���","���") +" � �������."),
                                    RandPhraseSimple("�����, ������. �����!", "������ ���������� �����. �� ��������."));
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("� ���� ���� ������ � ����.", "��� ����� ����������.");
			link.l2.go = "exit";//(���������� � ���� ������)
			// --> ��������� ��������� ����, ����� ����� �� �����. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase("������! ���������� ������� ���, ��� �� �����?! � ��� ���������� ��������� �� ��������� ����������� " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!", 
					"���������� ����! � �������� � ��������� ������ " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " �� ��������� �����������. ��� � ������ ���������� ������.", 
					"������, ��������! ������� ���������� " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " ����� ����� ��������� ������ � ������."), 
					LinkRandPhrase("�������, ������! ���������� ������� ���, ��� �� �����?! � ��� ���������� ��������� �� ��������� ����������� " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!", 
					"�������, � ����"+ GetSexPhrase("��","��") +" ��� ���������! � �������� � ��������� ������ " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + " �� ��������� �����������. ��� � ������ ���������� ������.", 
					"������, ���������! ������� ���������� " + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + " ����� ����� ��������� ������ � ������..."));
				link.l4.go = "SitySpy";
			}
			// <-- ��������� ��������� ����, ����� ����� �� �����
			link.l5 = PCharRepPhrase("�����"+ GetSexPhrase("","�") +" ���-��� ������ �� ���� ���������!", "�����"+ GetSexPhrase("","�") +" ������ ���-��� � ������.");
			link.l5.go = "new question";
		break;

		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("�, ��, � ���"+NPCharSexPhrase(NPChar, " ", "� ")+" ���� ��� �������, ���������, ���� ������.", "������ ���������, �������? ��� �, � ����... �������� �� ��������� ����.", "��, " + PChar.name + "?"),
                                        LinkRandPhrase("��, ���� ���� ���?", "����, ������� "+PChar.name+", �� "+ GetSexPhrase("�������","��������") +" ���������? ", "�������"+ GetSexPhrase("","�") +" ���������, �������, ����� �� ������� �����.")),
		                PCharRepPhrase(LinkRandPhrase("��� �� ������ ������ "+ GetAddress_Form(NPChar) + "?", "� ��� ������ �������.", "��� ����� ����, ������� ����������� ������, �������."),
                                        LinkRandPhrase("������ ���"+NPCharSexPhrase(NPChar, " ", "� ")+" ��������� �����������, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". ��������.",
                                                        "��, " + GetAddress_Form(NPChar) + "?",
                                                        "������ ���������, �������? ��� �, � ����..."))
                            );

            // homo 25/06/06
			link.l1 = LinkRandPhrase ("����� ����� � ���� � ������� �������?",
                                    "��� ���������� � ���� �����?",
                                    "��� ����� ����� �� ����?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("�� ��������� ��� ������?", "���-�� � ����� �� ����� ������ ���-����...", "���������� ������...");
			link.l2.go = "exit";  //(���������� � ���� ������)
			link.l3 = "���������� ��� � ����� �������.";
			link.l3.go = "colony";
            link.l4 = RandPhraseSimple("���� ������ ����!", "� ���� � ��� ����.");
			link.l4.go = "exit";  //(���������� � ���� ������)
			link.l5 = PCharRepPhrase(RandPhraseSimple("���� �����������, � �����.", "���, ������ - ������ "+ GetSexPhrase("���","���") +" � �������."),
                                        RandPhraseSimple("�����, ������. �����!", "������ ���������� �����. �� ��������."));
			link.l5.go = "exit";
		break;
		
		case "colony":
			dialog.text = LinkRandPhrase("������ ������, � �� �������-�� ���������� � ����. �� ���-��� ���� ����������.",
                           "��� �� ��� ���������� � ����� �������?", "������ ����������. � ��� �� ������ ��������?");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "��� ��� �� �����?";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "��� �� ������ � �����, ���������� �����?";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "��������� � ���-������ ������.";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "�, �� �� �����������? ��� ������? ���������� � ������ ������� ���� ������.";
			link.l1 = "�����, �����.";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "������ ��� ��� �� ����.";
			link.l1 = "����.";
		    link.l1.go = "exit";
		break;
		//==> ������ ��������
		case "SitySpy":
			dialog.text = "��, � � ����� ��� ���? � ������� ������!";
			link.l1 = "��� ����� ����������� ���� �����?";
		    link.l1.go = "SitySpy_1";
		break;
		case "SitySpy_1":
			dialog.text = "��� ����� �����������, ���!!!",
			link.l1 = "��� - ��� ���? ������ ��� ���� �� ������ ���������� " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!";
			link.l1.go = "SitySpy_3";
		break;
		case "SitySpy_3":
            dialog.text = "���... ������... ���..";
			link.l1 = "��� ����, ��������, ����-�� � � ���! ������ �� ����, ����� � �������� ���� �� �����. ���� ��� �������?!";
		    link.l1.go = "SitySpy_4";
		break;
		case "SitySpy_4":
            dialog.text = "����! ���� �� ���� ��� ����� ���������!.. ��� ����, ���� ��������� �� ����� - ��� ��� ����� ��� ������...";
			link.l1 = "��, ��� � ������. �� ���� �����������, �� ����� ���� ������...";
		    link.l1.go = "SitySpy_5";
		break;
		case "SitySpy_5":
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)]);
			AddQuestRecord("MayorsQuestsList", "5");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", sTemp);
			// �����
			AddSimpleRumour(RandPhraseSimple("�� ������, ���������� " + sTemp + " ������� "+ GetSexPhrase("������� ��������","����� �������-��������") +" " + GetMainCharacterNameGen() + " ����� � ������ ���������� ���������. � �� ������, "+ GetSexPhrase("�� ��� �����","��� ��� �����") +" ����� �� ������!", 
				"��� ���������� ��� ������� �������� " + GetMainCharacterNameGen() + " ��������� � ������ ���������� ������. � "+ GetSexPhrase("���� ������� �����","��� ������� �����") +" ��������� ����� �������!"), sti(characters[sti(pchar.GenQuest.SeekSpy.MayorId)].nation), 5, 1);			
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //������� ����� ������
			pchar.GenQuest.SeekSpy = "FoundSpy"; //���� ����� ������
			DeleteAttribute(pchar, "GenQuest.SeekSpy.City"); //�� ���������� ����� � ������
			LocatorReloadEnterDisable(pchar.location, "gate_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload1_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
		//----------------- ����� � ���������� ������ � ���� ----------------------
		case "DestroyPirate_Abordage": //�������
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate.wasTalkInDeck"))
			{
				dialog.text = "�� ���-���� �����"+ GetSexPhrase("","�") +" ���������...";
				Link.l1 = "��, �����"+ GetSexPhrase("","�") +" ���-���...";
				Link.l1.go = "DP_Abordage_1";
			}
			else
			{
				dialog.text = "��� �� ���"+ GetSexPhrase("��","��") +", ���� ���� ����?!";
				Link.l1 = "� "+ GetSexPhrase("������","������") +" �� ����� �������, ��������. ���������� " + XI_ConvertString("Colony"+pchar.GenQuest.DestroyPirate.MayorId+"Gen") + " ����� ������ �� �������� � ��������� �������.";
				Link.l1.go = "DP_Abordage_2";
			}
		break;
		case "DP_Abordage_1":
			dialog.text = "������, ���������� � ���� �����.\n�� ���, ���������, �������?..";
			Link.l1 = "���������, ��������!";
			Link.l1.go = "DP_Abordage_fight";	
		break;
		case "DP_Abordage_2":
			dialog.text = "���, �������... ��, � �� ���������� �� ��������� ��� ������ ������������!";
			Link.l1 = "����������...";
			Link.l1.go = "DP_Abordage_fight";	
		break;
 		case "DP_Abordage_fight":
			LAi_SetCurHP(npchar, rand(sti(npchar.chr_ai.hp_max)) + 5);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
		break;
		//�������� �� ������
		case "DestroyPirate_Deck":
			pchar.GenQuest.DestroyPirate.wasTalkInDeck = true; //���� �� �������� �����
			dialog.text = "��� ������ ���� �� ���� �������, "+ GetSexPhrase("��������","�������") +". ����� ���������"+ GetSexPhrase("","�") +"?";
			Link.l1 = "� �������� �� ��������� ����������� " + XI_ConvertString("Colony"+pchar.GenQuest.DestroyPirate.MayorId+"Gen") + ", ���������� ������, ���������� � ������� ����� � ��������� �����.";
			Link.l1.go = "DestroyPirate_1";	
		break;
		case "DestroyPirate_1":
			dialog.text = "�� ���� �������, ��� ��� ��������� ������� ��� ��������...";
			Link.l1 = "��� ��� ������?!";
			Link.l1.go = "DestroyPirate_2";	
		break;
		case "DestroyPirate_2":
			dialog.text = "����� ��, ��� � ������ ���� ������. ������ ��������� ��������, ����� ����� ������� ���������� ������ ������ ������� ����������� ������ - �������, ����������� �������� �������.";
			Link.l1 = "��� �� � ���� �� ����� ������...";
			Link.l1.go = "DestroyPirate_3";	
		break;
		case "DestroyPirate_3":
			dialog.text = "������ ���, �������������� ��������.\n�� ��, ����������� � ���� ���������� - "+ GetSexPhrase("����","����") +", �� ���� �������...";
			Link.l1 = "��, � ��� �� ����������� ������ ������?";
			Link.l1.go = "DestroyPirate_4";	
		break;
		case "DestroyPirate_4":
			int lngFileID;
			if (pchar.GenQuest.DestroyPirate.fortPlace == "1")
			{
				pchar.GenQuest.DestroyPirate.outShoreId = GetIslandRandomShoreId(pchar.GenQuest.DestroyPirate.Areal);
				sld = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
				lngFileID = LanguageOpenFile("LocLables.txt");
				sTemp = LanguageConvertString(lngFileID, pchar.GenQuest.DestroyPirate.outShoreId);
				dialog.text = "��, ������... � ������� ������ ������� � �����, ������� �� ���� ��������� � �������� ���� �� ����� �����. ����� �� �������, ��� ������� �� ���� ������� �� �����, ��� ��������� " + sTemp + ", � ��� ����� ���� ���� � " + XI_ConvertString("Colony"+sld.city+"Dat") + 
					". � ���� ������ � ������� ���� �����. ����� ���� ������� ����� ����� �����, �� ������.\n��� ����������� �� �������?";
				Link.l1 = "�� �����, ��� ����������. ������ ��� �����, ��� �� �������� �����, ����� ���� ���� �� ��������?";
				Link.l1.go = "DestroyPirate_5";					
				break;
			}
			if (GetCompanionQuantity(pchar) == 1 && makeint(pchar.GenQuest.DestroyPirate.shipState) > 1)
			{
				dialog.text = "�������, � ������ ����, "+ GetSexPhrase("�������������� ���","�������������� �����") +". ��������� �� ��� ����������� ����� �����������.\n� �����, ����������, ���� � ������...";
				Link.l1 = "������� � �� ����. ������...";
				Link.l1.go = "DP_WithoutFight";	
				Link.l2 = "������ ���, �, �������, �������� ���� ������, ���� ��� ���� ������� �� ���������...";
				Link.l2.go = "DP_FightInDeck";	
			}
			else
			{
				pchar.GenQuest.DestroyPirate.outShoreId = GetIslandRandomShoreId(pchar.GenQuest.DestroyPirate.Areal);
				sld = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
				lngFileID = LanguageOpenFile("LocLables.txt");
				sTemp = LanguageConvertString(lngFileID, pchar.GenQuest.DestroyPirate.outShoreId);
				dialog.text = "� ������ �� ������� �����, ��� ������� �� ���� ������� �� �����, ��� ��������� " + sTemp + ", � ��� ����� ���� ���� � " + XI_ConvertString("Colony"+sld.city+"Dat") + 
					". � ���� ������ � ������� ���� �����. ����� ���� ������� ����� ����� �����, �� ������.\n��� ����������� �� �������?";
				Link.l1 = "�� �����, ��� ����������. ������ ��� �����, ��� �� �������� �����, ����� � ���� ������ "+ GetSexPhrase("����","����") +"?";
				Link.l1.go = "DestroyPirate_5";	
			}
		break;
		case "DestroyPirate_5":
			dialog.text = "���, ����� �� �� ������, �� � ���� ����� ��� �����. � ��� ���� ���� ������ ����� ������. ��� �������, ����� ��������...";
			Link.l1 = "��, �� ��� ��, � "+ GetSexPhrase("��������","��������") +". �������, �� �������� �����...";
			Link.l1.go = "DP_toShore";	
			Link.l2 = "�� ���, ��� ��� � ����. � ����� ���� - ���� ���, ����� � ����� ������. � ������, ��������!";
			Link.l2.go = "DP_FightInDeck";	
		break;

		case "DP_toShore":
			dialog.text = "������, �� �����.";
			Link.l1 = "����� � �����"+ GetSexPhrase("","�") +". �� ����.";
			Link.l1.go = "exit";
			AddDialogExitQuest("DestroyPirate_toShore");
		break;

		case "DP_WithoutFight":
			dialog.text = "��� ��� ����� ���� - ������ ��������� �� ���, ���� � ����...";
			Link.l1 = "�������...";
			Link.l1.go = "exit";
			Diag.TempNode = "DP_WithoutFight_again";
			AddDialogExitQuest("DestroyPirate_WithoutFight");
		break;
		case "DP_WithoutFight_again":
			dialog.text = "�� ��� �����? � �� �� ����� ����� �� ���� ����� �������������...";
			Link.l1 = "�����.";
			Link.l1.go = "exit";
			Diag.TempNode = "DP_WithoutFight_again";
		break;

		case "DP_FightInDeck":
			dialog.text = "���� ��, "+ GetSexPhrase("����� �������","����� �������� �����") +"! ���� ��������, ���� ����� ���� �������...\n��, �� ������, ������ "+ GetSexPhrase("�����","���") +" �������� ���������, � ���� ���������� ������� � ���. ������ ��� ������� ����!";
			Link.l1 = "����, ��� �� ��� ���������...";
			Link.l1.go = "DP_FightInDeck_1";
		break;
		case "DP_FightInDeck_1":
			pchar.GenQuest.DestroyPirate.FightAfterDeck = true; //����� ����� �� ������ - ����� � ����
			float locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "DestroyPirate_FightInDeck", 3.5);
			DialogExit();			
		break;


	}
}
