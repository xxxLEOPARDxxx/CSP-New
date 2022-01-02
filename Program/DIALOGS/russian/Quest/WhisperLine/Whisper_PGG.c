void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;
	ref shTo;
	string cnd;
	DeleteAttribute(&Dialog,"Links");
	int i;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Quest_Whisper_1":
			dialog.text = "����, ������ ���������, �� ���, ������� �� ������ ������, ����� �����.";
			link.l1 = "��� � ��� �����"+ GetSexPhrase("","�")+". ���� ����� ������.";
			link.l1.go = "Quest_Whisper_2";
		break;
		
		case "Quest_Whisper_2":
			dialog.text = "������, �������, ���� ���-�� ����. � ����� �����.";
			link.l1 = "...";
			link.l1.go = "Quest_Whisper_2_exit";
			pchar.WhisperPGG = npchar.id;
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			for (i = 1; i < 4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PGG_Whisper_Incquisitor"+i, "PGG_Vincento_"+(2+i), "man", "man", sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, PIRATE, 0, true));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
				cnd = "l"+i;
				pchar.quest.QuestWhisper_RoomFight.win_condition.(cnd) = "NPC_Death";
				pchar.quest.QuestWhisper_RoomFight.win_condition.(cnd).character = sld.id;
				LAi_group_MoveCharacter(sld, "Quest_Whisper_Enemy");
			}
			pchar.quest.QuestWhisper_RoomFight.function = "QuestWhisper_RoomFight";
		break;

		case "Quest_Whisper_2_exit":
			DialogExit();
			sld = CharacterFromId("PGG_Whisper_Incquisitor3");
			sld.Dialog.Filename = "Quest\WhisperLine\Whisper_PGG.c";
			sld.dialog.currentnode   = "Quest_Whisper_3";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		
		case "Quest_Whisper_3":
			dialog.text = "����� �� ��� ��������� ����������!";
			link.l1 = "���?";
			link.l1.go = "Quest_Whisper_3_exit";
		break;
		
		case "Quest_Whisper_3_exit":
			DialogExit();
			sld = CharacterFromId(pchar.WhisperPGG);
			sld.Dialog.Filename = "Quest\WhisperLine\Whisper_PGG.c";
			sld.dialog.currentnode   = "Quest_Whisper_4";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		
		case "Quest_Whisper_4":
			dialog.text = "���������! ��� �� �� ���� ����"+ GetSexPhrase("��","���")+" �� ��� ����?";
			link.l1 = "�� � ������� ���� ���� �����!";
			link.l1.go = "Quest_Whisper_4_exit";
		break;
		
		case "Quest_Whisper_4_exit":
			StartInstantDialog("PGG_Whisper_Incquisitor3", "Quest_Whisper_5", "Quest\WhisperLine\Whisper_PGG.c");
		break;
		
		case "Quest_Whisper_5":
			dialog.text = "������! �������-�� �� ��������� ����, ������! ������ �� ����������� �� ���� ���������!";
			link.l1.go = "Quest_Whisper_5_exit";
		break;
		
		case "Quest_Whisper_5_exit":
			StartInstantDialog(pchar.WhisperPGG, "Quest_Whisper_6", "Quest\WhisperLine\Whisper_PGG.c");
		break;
		
		case "Quest_Whisper_6":
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_SetImmortal(npchar, true);
			dialog.text = "��� �� �� ��� ��� �������!";
			link.l1.go = "Quest_Whisper_6_exit";
			pchar.WhisperId = npchar.id;
		break;
		
		case "Quest_Whisper_6_exit":
			npchar.dialog.CurrentNode = "Quest_Whisper_8";
			StartInstantDialog("PGG_Whisper_Incquisitor3", "Quest_Whisper_7", "Quest\WhisperLine\Whisper_PGG.c");
		break;
		
		case "Quest_Whisper_7":
			dialog.text = "����������� ����������� � ��, ������ �� ���"+ GetSexPhrase("�� ������������!","�� ������������!");
			link.l1 = "�� �������� ��� ����������� � ���� � ��� ����, �� ����� "+ GetSexPhrase("'����������'","'�����������'")+" ���������� �������� ������.";
			link.l1.go = "Quest_Whisper_7_fight";
			link.l2 = "�� �����, � ��������!";
			link.l2.go = "Quest_Whisper_7_flee";
		break;
		case "Quest_Whisper_7_fight":
			sld = CharacterFromId(pchar.WhisperId);
			LAi_SetWarriorTypeNoGroup(sld);
			for (i = 1; i < 4; i++)
			{
				sld = CharacterFromId("PGG_Whisper_Incquisitor"+i);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			
			DialogExit();
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "Quest_Whisper_7_flee":
			DialogExit();
			sld = CharacterFromId(pchar.WhisperId);
			DoReloadCharacterToLocation(sld.PGGAi.location.town + "_tavern","goto","goto1");
			chrDisableReloadToLocation = false;
		break;
		
		case "Quest_Whisper_8":
			if (HasSubStr(pchar.location,"upstairs"))
			{
				dialog.text = "�� ���, ���"+ GetSexPhrase("","�")+"?";
				link.l1 = "�� ���� �� � �������. ����� �����, ������ ����� ����� ����������?!";
				link.l1.go = "Quest_Whisper_9";
			}
			else
			{
				dialog.text = "� ���� ������� �������� ���������� �� ���, ����� ����, ��� �� ������"+ GetSexPhrase("","�")+" ���� �������? � ������ �� ���� ����� � ����� ���.";
				link.l1 = "�� � �� �����!";
				link.l1.go = "Quest_Whisper_end";
			}
		break;

		case "Quest_Whisper_9":
			dialog.text = "��� ������, � ���� ������� ������ �� ���� ����������. � ���� ���� ��� ���� ����?";
			link.l1 = "��, �� �� �����! ��� ���� ���������� ��������� ����������?";
			link.l1.go = "Quest_Whisper_10";
		break;
		
		case "Quest_Whisper_10":
			dialog.text = "��� ������ �������. �� ���� ���� �������, ��� ���������� �� ������ �����, ������� ������� � ���������. �� ����� ���� ��� �� ��������� ����������� � ��������, �� � � ����� ��� ����� �������� � ��������� � ���. � �� ������ �������� ������ �������� � �����, �����, � ��������� - �������� � ������ ����������� �����, � ��� �� ������������ ���� ������������. ������� ��� ������� ����� �������� � �� ����, �� ��� ������� ������� � ��������� ������. � ��� ���, ���������� �� ���� ��������.";
			link.l1 = "��� �������, ��� �� ������� �� �������������... �� ��, ����� � ������� ����������, �� �� � ������ ���������� �� ������. �� ���������� ��� ��� �����?";
			link.l1.go = "Quest_Whisper_11";
		break;
		
		case "Quest_Whisper_11":
			dialog.text = "���� �����, � ������ ��� ��������, ����� ����� ���� �������. � ���� ��� ����� ��������� � ����. �� ���� ������ ����������?";
			link.l1 = "�� �����, �����������.";
			link.l1.go = "Quest_Whisper_12";
		break;
		
		case "Quest_Whisper_12":
			dialog.text = "���� ������� - � ��������� ��� ������ ���������� ���� ��������� �����. ";
			link.l1 = "��� ����� �����-�� ��������� � ����� �������� '������'?";
			link.l1.go = "Quest_Whisper_13";
		break;
		
		case "Quest_Whisper_13":
			dialog.text = "��� �� ������, � ������ �� ��������� ���, ����� ��� �� ���� ��������. ����� �������� ����� �����\n� ��������� ������� �� ������ �������� ��� ���������� - �������. � ����� � ��� ������. ���� ������, ��� ��� ������������ � ������������ ��������� ������� �� ����� ���\n����� ����� ��� ������������� ������� ���������, ��� ��� ����������� �� ���� ���� �����, ��� �������� �� ����� ������ �������� ��������. � ������ ��������, �� ��� ������ ������ ��� ���� � �������� ��� �������. ��������, ��� � ��������� �����, ������ �� ������� ��� ����������� �����, ��� ��� ��� ���������� ������ ����-��, ����� ����.";
			link.l1 = "��� �� ������ ��������� ��... � ��� ��������� �� �����? � ��������?";
			link.l1.go = "Quest_Whisper_14";
		break;


		case "Quest_Whisper_14":
			dialog.text = "��. ���, ��� �������� ��������� �� ������� ���������� �� �������. ������� ���������� � �������� �� �� ��������� - ��������� ��� �� �� ���� ������. �� ���� �� ������� �� �� ����� �������� ����� �� ����� � ���� - ��� ������ �� ������ ������� �� �������, ������ ��� ������� �� ����� ��������. ��� - ������� ����� ����� � ����, ������� ��������� ����.";
			link.l1 = "�� ���������������� �� ��� ����? � ��������� ����� ��������� - ������ ������, � ���� �� ����� �������� ������� ������� ��������. ����� �� �� ���� ��� �����, ���� �� ��� ���� �����.";
			link.l1.go = "Quest_Whisper_15";
		break;
		
		case "Quest_Whisper_15":
			dialog.text = "�� �������, �� ������� �� ������ ����� ����������, �� � ������ �� ������������ ������. � � ������� � ���� ������.";
			link.l1 = "����� ������� ��������?";
			link.l1.go = "Quest_Whisper_16";
		break;
		
		case "Quest_Whisper_16":
			dialog.text = "� ����, ��� ��������� ����������� ������ ������� � ����� ������ �� �����. ���� �� ������ ���, ��� ���� ������ � ������ ��������, �� ����������, �� �������� ��� ���� �� ��� ������. ���� ��� ����� ����������� �� ���� �������.";
			link.l1 = "�� ������� �� ������ ��� ��� �������?";
			link.l1.go = "Quest_Whisper_18";
		break;
		
		case "Quest_Whisper_18":
			dialog.text = "���� ��. �����, ��� ������� ���� �������� ��������� ��������� ��� ���������, ����� ��������� � �������, � ��� ����� ������������ ��� �����.";
			link.l1 = "���������?";
			link.l1.go = "Quest_Whisper_19";
		break;
		
		case "Quest_Whisper_19":
			dialog.text = "�����, ��� ������, ����� � ���� ���������� ����� �������� � ����� ����������� � ����������\n��� ������ ��� ��������, ���� �����"+ GetSexPhrase("","�")+" ����� � ���� � ����� ���������� ���� ������ ������, ���� �� ����� ����� ��������� ������� ������.";
			link.l1 = "�����, ������. ��� � ����� ���� �����, ����� ������� ���������� �����������?";
			link.l1.go = "Quest_Whisper_20";
			link.l2 = "������, �� ���� � � ��� �����������. �� ����������, ����� ������ ������� �������� ������� �� ��� ������.";
			link.l2.go = "Quest_Whisper_19_1";
		break;
		
		case "Quest_Whisper_19_1":
			dialog.text = "������"+ GetSexPhrase("","�")+"? ������ � ��� ���� ���� �� ��������. �� ���� �����������, �� � ����������� � ������ �� �������, ���� �������, ��� ���� ����� ����� ������������ ������������� � ������.";
			link.l1 = "������"+ GetSexPhrase("","�")+".";
			link.l1.go = "Quest_Whisper_end";
			link.l2 = "�����, ������. ��� � ����� ���� �����, ����� ������� ���������� �����������?";
			link.l2.go = "Quest_Whisper_20";
		break;
		
		case "Quest_Whisper_20":
			dialog.text = "��� ��� �� ����������, � ���� ��������� �� ����. ��� ������ �������� ���� ����� ����� - � ���� ���� �����.";
			pchar.PGGWhisperLetter = true;
			link.l1 = "��� �, ����� �� ����.";
			link.l1.go = "Quest_Whisper_accept";
		break;

		case "Quest_Whisper_end":
			LocatorReloadEnterDisable("Santiago_Town", "basement1", false);
			npchar.dialog.filename = "pgg_dialog_town.c";
			npchar.dialog.currentnode = "First time";
			npchar.PGGWhisperQuestEnd = true;
			DialogExit();
			CloseQuestHeader("PGGWhisper");
			DeleteAttribute(npchar, "PGGAi.DontUpdate");
			DeleteAttribute(pchar, "PGGWhisperQuest");
			DeleteAttribute(pchar, "PGGWhisperLetter");
			DeleteAttribute(pchar, "PGGWhisperLetterSent");
			DeleteAttribute(pchar, "PGGWhisperLetterSentFail");
			DeleteAttribute( Colonies[FindColony("Santiago")], "DontSetShipInPort");
		break;
		
		case "Quest_Whisper_accept":
			npchar.PGGAi.DontUpdate = true;
			if (!CheckAttribute(pchar, "PGGWhisperQuest"))
			{
				SetQuestHeader("PGGWhisper");
				AddQuestRecord("PGGWhisper", "1");
				pchar.PGGWhisperQuest = true;
			}
			npchar.dialog.currentnode = "Quest_Whisper_report";
			LocatorReloadEnterDisable("Santiago_Town", "basement1", true);
			DialogExit();
		break;
		
		case "Quest_Whisper_report":
			dialog.text = "�� ����� �����! �������� �����-�� �������?";
			
			if (CheckAttribute(pchar, "PGGWhisperLetterSentFail"))
			{
				DeleteAttribute(pchar, "PGGWhisperLetterSentFail");
				link.l1 = link.l1 + " �� �� ��� �� �������. ������, ������ �� �����.";
				link.l1.go = "Quest_Whisper_report_fail";
				break;
			}
			
			link.l1 = "�� ���, ������ ���� �������.";
			link.l1.go = "Quest_Whisper_accept";
			link.l2 = "��. � ���� �� ������ ��������. �������, ��� � ��� � ����� �� ����?";
			link.l2.go = "Quest_Whisper_report_1";
			link.l3 = "� ��� �������"+ GetSexPhrase("","�")+", �� �������� ��� ��� ����. ������, �� � ���.";
			link.l3.go = "Quest_Whisper_report_fail";
		break;
		
		case "Quest_Whisper_report_1":
			dialog.text = "���?! �����������? ���� � ���� ���� ������ �� ������, �� �� ����������� ����� ���� � ���� ������. � ������ ���, ��� �� ������� ������ �������.";
			link.l1 = "�� ���� �.";
			link.l1.go = "Quest_Whisper_accept";
		break;
		
		case "Quest_Whisper_report_fail":
			dialog.text = "����. ������, ��� ������� ������ ������ ������. ������� ��� ������"+ GetSexPhrase("","�")+". �����.";
			link.l1 = "�����.";
			link.l1.go = "Quest_Whisper_end";
			//�� ������ �������� ������
		break;
		case "Quest_Whisper_ToSiege":
			chrDisableReloadToLocation = false;
			dialog.text = "������� � ������ ��������� � �����, ������ ��� ���� ��������.";
			link.l1 = "��� �� ����� �������? ����� ���� ������� �� ������ ������ ��������� �������?";
			link.l1.go = "Quest_Whisper_ToSiege_1";
		break;
		case "Quest_Whisper_ToSiege_1":
			dialog.text = "��� ������� ��� � ���� ���������. �� �� �� �����"+ GetSexPhrase("","�")+", ��� � ������� ���� �� �������?";
			link.l1 = "� ��� ��� �� ���������� � ����? ������� ������ �� �����"+ GetSexPhrase("","�")+".";
			link.l1.go = "Quest_Whisper_ToSiege_2";
		break;
		case "Quest_Whisper_ToSiege_2":
			dialog.text = "� ���� �� ��� ���-���� �������. �����, ������ ���������. ����� � ������, ���� ������ ���� �� ������. �������, ������ ����� ������, ����� ����� ���� �����.";
			link.l1 = "�����, ��������.";
			link.l1.go = "exit";
			LAi_LoginInCaptureTown(npchar, true);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("PGGWhisper", "4");
		break;
		case "Quest_Whisper_AfterSiege":
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Santiago_Town", "basement1", false);
			dialog.text = "�� ��� �������! ������� ��������� ����� - ���������� ����������. ���� ��������� ��� ��������� � �������. ������, ��� ������ �����"+ GetSexPhrase("","�")+". ���� ������, ������ ����� ��������� �����������, � �������.";
			link.l1 = "�����.";
			link.l1.go = "exit";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollow(npchar, PChar, "", -1);
			
			PChar.quest.QuestWhisper_Incq.win_condition.l1 = "location";
			PChar.quest.QuestWhisper_Incq.win_condition.l1.location = "Santiago_Incquisitio";
			PChar.quest.QuestWhisper_Incq.function = "QuestWhisper_Incq";
		break;
		
		case "Quest_Whisper_Incq_fall":
			dialog.text = "��, ������ �������������\n����, �� ��-���� ��������?";
			link.l1 = "�� ������? ����� � ������"+ GetSexPhrase("","�")+", ��� �� �����, � ��������� �������.";
			link.l1.go = "Quest_Whisper_Incq";
		break;
		
		case "Quest_Whisper_Incq":
			//chrDisableReloadToLocation = false;
			
			dialog.text = "�����, �� ��������� ������ ���� ���-�� �����.";
			if (!CheckAttribute(npchar, "FailedRecruitment"))	dialog.text = "��������� ������� �����, ��� � ������. " + dialog.text;
			link.l1 = "������, ������ ����� ������� ��� ��������.";
			link.l1.go = "exit";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollow(npchar, PChar, "", -1);
			
			PChar.quest.QuestWhisper_Incq_4.win_condition.l1 = "locator";
			PChar.quest.QuestWhisper_Incq_4.win_condition.l1.location = "Santiago_Incquisitio";
			PChar.quest.QuestWhisper_Incq_4.win_condition.l1.locator_group = "box";
			PChar.quest.QuestWhisper_Incq_4.win_condition.l1.locator = "box2";
			PChar.quest.QuestWhisper_Incq_4.function = "QuestWhisper_Incq_4";
			
			ref _location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box2.money = 250000;
			_location.box2.items.icollection = 5;
			_location.box2.items.chest = 10;
			_location.box2.items.jewelry1 = 20+rand(5);
			_location.box2.items.jewelry2 = 20+rand(5);
			_location.box2.items.jewelry3 = 20+rand(5);
			_location.box2.items.jewelry4 = 11+rand(5);
			_location.box2.items.BackPack5 = 1;
			_location.box2.items.DeSouzaCross = 1;
			ChangeItemName("DeSouzaCross", "itmname_DeSouzaCross_DH");
		break;
		
		case "Quest_Whisper_Incq_1":
			dialog.text = "� ��� ��? ";
			link.l1 = "��, ���� �������� �������� �����������.";
			link.l1.go = "Quest_Whisper_Incq_2";
		break;
		
		case "Quest_Whisper_Incq_2":
			dialog.text = "������ ���� ������� ������. ������������ ����� ���� ��������� ��������. � �� ���, ��� ���� - ������ �� �����������\n���������, � ���-�� ��������! ������ ����, � ���������� ��������� ������ ����������, � ������� � �� �������.";
			link.l1 = "����� � ���, �� ������ ���� ����������. ��� ����� ������?";
			link.l1.go = "Quest_Whisper_Incq_3";
		break;
		
		case "Quest_Whisper_Incq_3":
			dialog.text = "� ������ ������ ���� ��������, ��� � ���� �������� ����� �� ����� ����� ����������� '������'\n������ �������� �� ��������� ����. � ������ �� ������������ ������ ����. � ������ ���� ���� ���������� �� ������� � ����������� �����, � �� ���� ���� ������� �������� �����.";
			link.l1 = "�� ��� �������? ������� �������� �������, ������ ��.";
			link.l1.go = "Quest_Whisper_Incq_4";
		break;
		
		case "Quest_Whisper_Incq_4":
			dialog.text = "�� ����� �������������. � ����� ������ � ����� ����� ��������� ���������� ���� ��������.";
			link.l1 = "��� �������.";
			link.l1.go = "Quest_Whisper_Incq_5";
		break;
		
		case "Quest_Whisper_Incq_5":
			AddQuestRecord("PGGWhisper", "5");
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			
			PChar.quest.QuestWhisper_Incq_5.win_condition.l1 = "location";
			PChar.quest.QuestWhisper_Incq_5.win_condition.l1.location = "Santiago_Town";
			PChar.quest.QuestWhisper_Incq_5.function = "QuestWhisper_Incq_5";
		break;
		
		case "Quest_Whisper_Finish":
			pchar.PGGWhisperComplete = true;
			DeleteAttribute(npchar, "PGGAi.DontUpdate");
			CloseQuestHeader("PGGWhisper");
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "LockMapReload");
			DeleteAttribute(pchar, "PGGWhisperLetter");
			DeleteAttribute(pchar, "PGGWhisperLetterSent");
			DeleteAttribute( Colonies[FindColony("Santiago")], "DontSetShipInPort");
			
			dialog.text = "��� ������� ��� ����� � ������. �� ����, ��� ����� �� ��� ���������� �������, �� ��������� �� �����. ���� ���� �� ������� ����� �������������.";
			link.l1 = "��� �, �����.";
			link.l1.go = "Quest_Whisper_Finish_NoHire";
			link.l2 = "�������, ����������... ������ ���� ����� - ��� �����. ���� �����, ����������� � ��������� �������� ������ ��� ������? ��� �����, ����� �� ��� �������� ����������...";
			link.l2.go = "Quest_Whisper_Finish_Hire";
		break;
		
		case "Quest_Whisper_Finish_NoHire":
			npchar.dialog.filename = "pgg_dialog_town.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();
		break;
		
		case "Quest_Whisper_Finish_Hire_1":
			npchar.dialog.filename = "Enc_Officer_dialog.c";
			npchar.dialog.currentnode = "hired";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();
		break;
		
		case "Quest_Whisper_Finish_Hire":
			if (CheckAttribute(npchar, "FailedRecruitment"))
			{
				dialog.text = "������, �� � �����, ��� ��� ����� ���������� � ��������.";
				link.l1 = "��� ������.";
				link.l1.go = "Quest_Whisper_Finish_NoHire";
			}
			else
			{
				if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
				{
					Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
							RandPhraseSimple("���������� �����������! ������! � �������� ��������!", "� �� �� ������, �������... �����, �� �����������!"), 
							LinkRandPhrase("���� ����������� ��� ��������. � ��������.", 
							"����... � ���� �����, ��� ������ �� ������ ������!", "�������, ��� ����� ������. ������������."));
					link.l1 = RandPhraseSimple("�������, ��� ���� � ����!", "��� � ���������! �� ����� �������� ��������.");
					link.l1.go = "Quest_Whisper_Finish_Hire_1";
					
					if (CheckAttribute(NPChar, "PGGAi.Task.SetSail"))
					{
						PGG_Disband_Fleet(npchar);
					}
					
					NPChar.PGGAi.IsPGG = false;
					NPChar.PGGAi.location.town = "none";
					if (NPChar.model.animation == "man" || NPChar.model.animation == "YokoDias" || NPChar.model.animation == "Milenace") Npchar.CanTakeMushket = true;
					if(npchar.model == "PGG_Whisper_6") EquipCharacterByItem(NPChar, "suit_1");
					NPChar.Payment = true;
					NPChar.Money   = 0;
					SetBaseShipData(NPChar);
					DeleteAttribute(NPChar,"ship.sails");
					DeleteAttribute(NPChar,"ship.masts");
					DeleteAttribute(NPChar,"ship.blots");
					
					Fantom_SetCannons(NPChar, "pirate");
					Fantom_SetBalls(NPChar, "pirate");
			
					DeleteAttribute(NPChar, "PGGAi.Task");
					DeleteAttribute(NPChar, "PGGAi.LockService");
					SetCharacterRemovable(NPChar, true);
					SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
					
					NPChar.HalfImmortal = true;  // ��������
					NPChar.OfficerWantToGo.DontGo = true; //�� �������� ����
					NPChar.loyality = MAX_LOYALITY;
					
					LAi_SetActorTypeNoGroup(npchar);
					LAi_ActorFollow(npchar, PChar, "", -1);
				}
				else
				{
					Dialog.Text = RandPhraseSimple("������ � ���� ��� ���������� �����������.", "� ���� � ��� ����� ��������. ����� ���� ��� ����?");
					link.l1 = "��... ������� �� �����.";
					link.l1.go = "Quest_Whisper_Finish_NoHire";
				}
			}
		break;
	}
}