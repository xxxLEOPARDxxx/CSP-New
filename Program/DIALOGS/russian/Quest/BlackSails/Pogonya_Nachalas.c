
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int z;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//�������. �� ������ � �������� ������ � �� ������ � ��������� ����� �� ����� ����� ��������� ������, ����������� ���� ��. ���������� ��������� ���� ����� � ���������. �� ������ ��� ������ ���� ����� ���� �� ����� � ������ ������.
		//������������. �������, �����, ����, ������, �����, ��������� �������� � ����������� �� ������ 12 � �����.
		
		case "BS_PN_shipF":	//�����
			NextDiag.TempNode = "BS_PN_shipF";
			dialog.text = "�������-�� �� ������. ��������� � ����� ��������� ������, ��� ��������� �������� .";
			link.l1 = "������������.";
			link.l1.go = "exit";
		break;
		
		case "BS_PN_shipV":	//����
			NextDiag.TempNode = "BS_PN_shipV";
			dialog.text = "����, �� ��� �����. ����� ������� ������ � ��������� ������, ���������� ���.";
			link.l1 = "������.";
			link.l1.go = "exit";
		break;
		
		case "BS_PN_1":	//�����
			dialog.text = "������ ���� ������� ��������� � ����� ������������.";
			link.l1 = "��, ���������� ����� ������!";
			link.l1.go = "BS_PN_1_1";
		break;
		
		case "BS_PN_1_1":	//�����
			dialog.text = "����, ���������� �� ����������, ����� ������.";
			link.l1 = "...";
			link.l1.go = "BS_PN_2exit";
		break;
			
		case "BS_PN_2exit":
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", Get_My_Cabin(), "", "", "", 10);
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_2";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;
		//������� ������ �� ���� � ������� �������.
		
		case "BS_PN_2":	//����
			dialog.text = "���������. ��� ��� ����������. ���� ������ � ��� �����. ����������� �������. ���� ������ ����������, � � ��������� �� ���, ����� �� ����� ������� �������� � ������������. �������� ��� � � ������� ������� � ����.";
			link.l1 = "...";
			link.l1.go = "BS_PN_3exit";
		break;
		
		case "BS_PN_3exit":
			sld = CharacterFromID("BS_Bony");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_3";
			DialogExit();
			DoQuestFunctionDelay("BonySpeech", 0);
		break;
		
		case "BS_PN_3":	//���
			dialog.text = "������ ���� ��������� ��� ���, ������, � ����� �� ���������, ���� ���������� ��� � ���� � �����.";
			link.l1 = "...";
			link.l1.go = "BS_PN_4exit";
		break;
		
		case "BS_PN_4exit":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_4";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;
		
		case "BS_PN_4":	//����
			dialog.text = "�� ��������, �����. ������ � �����.";
			link.l1 = "...";
			link.l1.go = "BS_PN_5exit";
		break;
		
		case "BS_PN_5exit":
			sld = CharacterFromID("BS_Rakham");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_5";
			DialogExit();
			DoQuestFunctionDelay("RakhamSpeech", 0);
		break;
		
		case "BS_PN_5":	//������
			dialog.text = "��, �� ���� ���, ���� ���� �� �����.";
			link.l1 = "...";
			link.l1.go = "BS_PN_6exit";
		break;
		
		case "BS_PN_6exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", Get_My_Cabin(), "", "", "", 10);
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_6";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		//������ ������ � ��������.
		
		case "BS_PN_6":	//�����
			dialog.text = "������� � ���������� ������� � ������ � �� �����������. � ��� ��� ������ �������� ����������� ��������, ���� �������� ����.";
			link.l1 = "...";
			link.l1.go = "BS_PN_7exit";
		break;
		
		case "BS_PN_7exit":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_7";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;
		
		case "BS_PN_7":	//����
			dialog.text = "�� ���� ���� �������� ������ �������� �� ��������, �� ��������� ����� ���� �� ����.";
			link.l1 = "��� ��������� �� ����������.";
			link.l1.go = "BS_PN_8exit";
		break;
		
		case "BS_PN_8exit":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_8";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		case "BS_PN_8":	//�����
			dialog.text = "����������, ��� ��������� ��������, ��� �� ��� ������� � ����� ����, �� �� �������� ������� ������ �� ����� ����� �����.";
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_17_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
			else
			{
				link.l1 = "��� ��?!...";
				link.l1.go = "BS_PN_9exit";
			}
		break;
		
		case "BS_PN_8_1":	//�����
			link.l1 = "��� ��?!...";
			link.l1.go = "BS_PN_9exit";
		break;
		
		//����� �� ������!� �������� ����� ������� �� �������� � ���� ����. ����
		
		//�� ���������
		
		case "BS_PN_9exit":
			DialogExit();
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			sld = CharacterFromID("BS_Vein");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = CharacterFromID("BS_Bony");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			BSChaseBegun_shore_fight();
			
			LAi_group_SetHearRadius("BSChaseBegun_shore_fight", 100.0);
			LAi_group_SetRelation("BSChaseBegun_shore_fight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("BSChaseBegun_shore_fight", LAI_GROUP_PLAYER, true);
			
			//pchar.quest.BSChaseBegun_shore_fight_end.win_condition.l1 = "Group_Death";//������� ������
			//pchar.quest.BSChaseBegun_shore_fight_end.win_condition.l1.group = "BSChaseBegun_shore_fight";//����� ������ ����������
			//pchar.quest.BSChaseBegun_shore_fight_end.function = "BSChaseBegun_shore_fight_end";
		break;
		
		case "BS_PN_9":	//����
			dialog.text = "������ �����? ��� ���� ��������!";
			link.l1 = "...";
			link.l1.go = "BS_PN_10exit";
		break;
		
		case "BS_PN_10exit":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_10";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		case "BS_PN_10":	//�����
			dialog.text = "��������! ����� ������ ������� � ���������.";
			link.l1 = "...";
			link.l1.go = "BS_PN_11exit";
		break;
		
		case "BS_PN_11exit":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_11";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;
		
		case "BS_PN_11":	//����
			dialog.text = "��� �����? �����, �� �� �����������. �������� �������� �������.";
			link.l1 = "����� ���������. ����� ������, ������ ����� ��� ����������.";
			link.l1.go = "BS_PN_12exit";
			NextDiag.TempNode = "BS_PN_11_loop";
			NextDiag.CurrentNode = "BS_PN_11_loop";
		break;
		
		case "BS_PN_12exit":
			NextDiag.TempNode = "BS_PN_11_loop";
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_12";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		case "BS_PN_12":	//�����
			chrDisableReloadToLocation = false;
			AddQuestRecord("BSChaseBegun", "2");
			dialog.text = "� �� '�����' ���������� ����. ����, ���� ����� ����� � ����� ������� ���������� � ���������.\n"+ 
							""+pchar.name+", �� ������ ������� �������, � ������ ����, ���� ���� � ����������, ���������� ����, ��� ���� �������� ������, � �� ��� ������ � ����� ����. ����� ����� ��� ������ � ��� ������ � ������ �� ��� ��������.";
			link.l1 = "��� �����, ����������!";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_12_loop";
		break;
		
		case "BS_PN_12_loop":	//�����
			dialog.text = "������� ������. ��� ����� ������� � ������ ����. �� �� ������ ����� �������. ������ ������� ����� ������ � ������� ���� � ����������.";
			link.l1 = "�����, ���.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_12_loop";
		break;
		
		case "BS_PN_11_loop":	//�����
			dialog.text = "������, ������� ��������, ������ ����� � �����.";
			link.l1 = "� ����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_11_loop";
		break;
		
		//������ � �� �������� ����������� ����������� �����. ���� �������� ��������� ��� �� ������. ����� ����� �������� ���� �� ������� ���������. ���������� � ����� ���� � ����� ���������� ���������� ���������� �� �����. �� ����!
		
		//��������. ������ ����. ������� �� �������� �� ��� ����. �����������, ������� �� �����. ������� � ���������.
				
		case "BS_PN_13_1":
			dialog.text = RandPhraseSimple("���� ����? ������� ����.", "������ ������������ ������, ������.");
			link.l1 = RandPhraseSimple("������ ���? �� ������!", "������� ���� ���. �� �� ������ ������ ���!"); 
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_13_1";
		break;
		
		case "BS_PN_13":	//�������
			dialog.text = "�������! �� ����� ������! ����������, � �������� ����� ������ ��������� ��������! ��� ����� ��������!";
			link.l1 = "�������� ������, �� �� ��������� ������. ��� � ��� ��� ����������? ���� �������� �������� �� ��, ��� ��������!";
			link.l1.go = "BS_PN_14";
		break;
		
		case "BS_PN_14":
			AddQuestRecord("BSChaseBegun", "3");
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			dialog.text = "� ��� ����������? ��� ��������� ���-�� � ����-�� ��������. ������ ��� ����� �������! ���������, � ���� ���������� ������� ������ ��� ������, � �� ����� ����� ��������� ��������� ����� �����!";
			link.l1 = "������� �����, ������. �� ����� ��� ������!";
			link.l1.go = "BS_PN_14_1";
			
			NPChar.Dialog.Filename = "Common_Shipyard.c";
			NPChar.Dialog.CurrentNode = "Second time";
			
			PChar.quest.BSChaseBegun_town.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_town.win_condition.l1.location = "Pirates_Town";
			PChar.quest.BSChaseBegun_town.function = "BSChaseBegun_town";
			
		break;
		
		case "BS_PN_14_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_19_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;
		
		//������ � ��: ������� ���������� � ���� ������. � ���� �� ������ �������� � ��������. ������� ��� ������ �� ����� �����. ���� � ���������, �� ������� ��� ��� �������. �����!�
		
		//������� � ���������. ��� �������. �� ����� ���� ������. �����, ����, �����, ������ ��������� ������� �������.
		
		case "BS_PN_15":	//����
			chrDisableReloadToLocation = false
			sld = CharacterFromID("Atilla");
			sld.dialog.currentnode = sld.AtillaNode;
			sld.Dialog.Filename = "Quest\Isabella\Atilla.c";
			dialog.text = "��� ��� ����! ��� ��� �� ���!";
			link.l1 = "...";
			link.l1.go = "BS_PN_15_1";
		break;
		
		case "BS_PN_15_1":	
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_16";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		case "BS_PN_16":	//�����
			dialog.text = "���������� �����������������, ��������� � ������.";
			link.l1 = "...";
			link.l1.go = "BS_PN_16_1";
		break;
		
		case "BS_PN_16_1":	
			sld = CharacterFromID("BS_Bony");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_16_2";
			DialogExit();
			DoQuestFunctionDelay("BonySpeech", 0);
		break;
		
		case "BS_PN_16_2":	
			dialog.text = "������, �������, ��� ��������� �����.";
			link.l1 = "...";
			link.l1.go = "BS_PN_16exit";
		break;
		
		case "BS_PN_16exit":	
			sld = CharacterFromID("gatri_grunt2");
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload3_back");
			sld.LifeDay = 0;
			
			sld = GetCharacter(NPC_GenerateCharacter("Gatri_temp", "BS_Gatry", "woman", "woman", 1, PIRATE, -1, true));
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload3_back");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.name = "��������";
			sld.lastname = "�����";
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_17";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;
		
		//��� � ����������, �� �� ������� ����� � ��������� �����������.
		
		case "BS_PN_17":	//�����
			dialog.text = "������! � ������... ��� ��, �� ����� �������. ������� ����� ��������� ���� � ������� � ���������� ����. ��� ��� �����, �������� � �����.\n�� ������ ���� ��� �� ������� �����, ��� ���������� ������������� ���������� � ������ ��� ������ ������.";
			link.l1 = "...";
			link.l1.go = "BS_PN_17_1";
		break;
		
		case "BS_PN_17_1":	
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_18";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		case "BS_PN_18":	//�����
			dialog.text = "��� ����� ���� � ���, � ������� � �������� ������ ������ ������������. ��� ����� ������ ������� ��������. ��������� ���������� ����� � ���� ����, ����� ���� ��������.";
			link.l1 = "...";
			link.l1.go = "BS_PN_18_1";
		break;
		
		case "BS_PN_18_1":	
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_19";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;
		
		case "BS_PN_19":	//����
			dialog.text = "� ���� �������� ��� ������, '� ������������'.";
			link.l1 = "...";
			link.l1.go = "BS_PN_19_1";
		break;
		
		case "BS_PN_19_1":	
			sld = CharacterFromID("gatri_temp");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_20";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;
		
		case "BS_PN_20":	//�����
			dialog.text = "��� �������. ����� ������� ��� �������. ��������� ����� � ����������.";
			link.l1 = "...";
			link.l1.go = "BS_PN_20exit";
		break;
		
		case "BS_PN_20exit":	//�����
			DialogExit();
			LAi_MethodDelay("BSChaseBegun_FewDeaysLater",0.1);
			PChar.quest.BSChaseBegun_townhall.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_townhall.win_condition.l1.location = "Pirates_townhall";
			PChar.quest.BSChaseBegun_townhall.function = "BSChaseBegun_townhall";
		break;
		
		//�������� ��� ��������� ����� ������� �����, ���������� ��, ������, �����, �����, �������� � ������� � ����������.
		
		case "BS_PN_21":	//�������
			dialog.text = "���� �������, '���� �� ����', ���� �� �����������, ��� � ������. ��� ��� ������ �� ���� ��� ���� ������� ������ � � ������������� ������ ������� �������� ���������� � ������-����, ��� � ������� ������������� ��� ��� ������� ���������. ����� ����, ��� ������ ���������� � ������.";
			link.l1 = "...";
			link.l1.go = "BS_PN_21_1";
		break;
		
		case "BS_PN_21_1":	
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_22";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		case "BS_PN_22":	//�����
			dialog.text = "����� ��������� ����� ������� �� ������?";
			link.l1 = "...";
			link.l1.go = "BS_PN_22_1";
		break;
		
		case "BS_PN_22_1":	
			sld = CharacterFromID("BS_Silver");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_23";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;
		
		case "BS_PN_23":	//�������
			dialog.text = "�����. � ���� ��� ������� � ������ �� ������, ������� ����������� ���. � �����-������� ������� �� �����������, �� ��������� � ������. ��� � ������ ���� ������� �� ����. �� ������ ������ ��� ��� ����� ��������. ����� � ��������, ����� ��� ������ � � �����.";
			link.l1 = "...";
			link.l1.go = "BS_PN_23_1";
		break;
		
		case "BS_PN_23_1":	
			sld = CharacterFromID("gatri_temp");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_24";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;
		
		case "BS_PN_24":	//�����
			dialog.text = "�������������� ��������, ��� � �����-������� ����, ������ ����� ��������� ������� ������ ���� ������ ��� ���������.";
			link.l1 = "...";
			link.l1.go = "BS_PN_24_1";
		break;
		
		case "BS_PN_24_1":	
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_25";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		case "BS_PN_25":	//�����
			dialog.text = "������ ������ ����� � �������. ����, ���� ��� ���� ������. ����� ��� �� �������� ����������� ����������� �� ����-������ ������, � �� ����� �� ������ ������������ � ��������� ��������� �������. ������: ����������� ��������� �� ���� ��� ������� �, ������� �������� �������, ��������� ������� �������������. � ��� �� �����������, � ������� �� ���� �������.";
			link.l1 = "...";
			link.l1.go = "BS_PN_25_1";
		break;
		
		case "BS_PN_25_1":	
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_26";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;
		
		case "BS_PN_26":	//����
			dialog.text = "�������. ������������ ������� ����� ����� �������� � ��������� �� ����.";
			link.l1 = "...";
			link.l1.go = "BS_PN_26_1";
		break;
		
		case "BS_PN_26_1":	
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_27";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		case "BS_PN_27":	//�����
			dialog.text = "���������, � �� ������� ������ �� ��� �������, ��� �� ������� �������� �� ����, ����� ���� ����� ������� � ������ �� ������.";
			link.l1 = "� �� � ��� ����� ������� '����'? ���?";
			link.l1.go = "BS_PN_27_2";
		break;
		
		case "BS_PN_27_2":	//�����
			npchar.nation = PIRATE;
			dialog.text = "���� �� ������ ��������� �����-�������, �� ��� ������������ ��� �����! ��-�� ��������� ��� �� ������ ����� ������ '����'.";
			link.l1 = "...";
			link.l1.go = "BS_PN_27_1";
		break;
		
		case "BS_PN_27_1":	
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_28";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;
		
		case "BS_PN_28":	//����
			AddQuestRecord("BSChaseBegun", "4");
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(pchar.location.from_sea, "boat", false);
			LocatorReloadEnterDisable("Bermudes_Cavern", "reload2_back", false);
			pchar.location.from_sea = "Pirates_town";
			dialog.text = "� ���� ���. ����� ���� ��� ������ ������������ �� ����.";
			link.l1 = "������, �� ����!";
			link.l1.go = "BS_PN_28exit";
		break;
		
		case "BS_PN_28exit":
			PChar.quest.BSChaseBegun_lock_townhall.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_lock_townhall.win_condition.l1.location = "Pirates_town";
			PChar.quest.BSChaseBegun_lock_townhall.function = "BSChaseBegun_lock_townhall";
			
			DialogExit();
			sld = CharacterFromID("Flint");
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, false);
			ProcessHullRepair(sld, 100.0);
			ProcessSailRepair(sld, 100.0);
			DeleteAttribute(sld, "ship.blots");
			DeleteAttribute(sld, "ship.sails");
			DeleteAttribute(sld, "ship.masts");

			sld = CharacterFromID("BS_Silver");
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("BS_Rakham");
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("BS_Vein");
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);

			sld = CharacterFromID("gatri_temp");
			LAi_SetActorType(sld);
			
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;
		//������ � ��: ����������������� ����, ��� �� ���. �� ������ ������������ ����� ��������� �� �����. ����������, ��� ������ ���� �����(��). ���� ������� ������������ ������, ����� ���������� ������ � ������ ��� ��������� ����� �� �����. ���� �� ����.
		
		//������� � ������� �����-�������. ���� ��� ��� ������ �� �����. �� ������ ������ �������� ������� � ������, ���� �� ���� �������. �������� � �����, ����� ��������. ���� ����� ��� ���. ���� 8 �������. ����.
		
		//������ � ��: ���� ������ ������? ����� ���������� � ������� �� ��� �������! ����� ���� �������, ����� ����� �� ���.�
		
		//�������� ����� �� �����. ������� � �������
		
		case "BS_PN_30_seabattle":	//�����
			PChar.quest.BSChaseBegun_EndQuest.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_EndQuest.win_condition.l1.location = "Pirates_Town";
			PChar.quest.BSChaseBegun_EndQuest.function = "BSChaseBegun_EndQuest";
			
			dialog.text = "����� ������� ������ ����������. ��������� �� ��������.";
			link.l1 = "�� �����. �������� �� ���� ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_30_seabattle";
			DeleteAttribute(pchar, "LockMapReload");
			DeleteAttribute(pchar, "LockShoreReload");
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//����� �������������� � �������
			Flag_PIRATE();
			
			for (z = 1; z < 9; z++)
			{
				sld CharacterFromID("BSChaseBegun_SeaBattle"+z);
				sld.LifeDay = 0;
			}
		break;
		
		case "BS_PN_30":	//�����
			dialog.text = "...";
			link.l1 = "������ ���� ����������! ��� ������� ������, ��� ������� ��������� ������!";
			link.l1.go = "BS_PN_31";
		break;
		
		case "BS_PN_31":
			AddQuestRecord("BSChaseBegun", "6");
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(Colonies[FindColony("SantoDomingo")], "DontSetShipInPort");
			DeleteAttribute(Colonies[FindColony("SantoDomingo")], "BSChaseBegun");
			Group_SetAddress("Flint_Group", "Bermudes", "Quest_ships", "quest_ship_8");	
		
			dialog.text = "� ��������� � ��������. ���� ��� ����� ������ �� ���. ���������� ����� ������ �� ��������. ��� �� ����� ������� ����� �������, � ����� �� �����. ������ ���, '����' ��� �� �������. ������ � ���?";
			link.l1 = "���� � ���� ���� ������ �� �������, ��������, ��� ��� ������.";
			link.l1.go = "BS_PN_32";
		break;
		
		case "BS_PN_32":
			chrDisableReloadToLocation = false;
			LAi_SetActorTypeNoGroup(npchar);
			dialog.text = "���� ��� ����� ���������, ��������� �����.";
			link.l1 = "�����������.";
			link.l1.go = "BS_PN_32exit";
		break;
		
		case "BS_PN_32exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 20);
			BS_ReplaceHostessWithMaks();
			sld = CharacterFromID("PortRoyal_hostess");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode = "BS_NU_1";
			BSBons_SeaBattle(false);
			
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_1_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;
		
		//������ � ��: ������ ���� ����� � ������, ��� ������ ��������� �� ��� ����������. �� ��� �� �� ���������! ������-�� � ������ � ���� �����, �������� ����� ����� ���� �����, � ��� ��� �������. ���� - �������� ������.
		
	}
}
