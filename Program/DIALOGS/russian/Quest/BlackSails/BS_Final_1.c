

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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//������� � ���������� ��� ���. �� �������� � ���� � ������� �������. ������ � ��: �����������. �� ������������. ����� ������ ��� ����. ��� �� ��� ��������. ������, ��� ���(��) �������(����)! ����� ����������� � ������������. ������, ��� �� ����� ��!
		
		//�����, ���� ������������ ������� ������ ��� �������� � ����� ��� �� ��������. ���� �� �������������� � �� � ������� �� ������ ����������.
		
		//���������� � �������. ������� ��� �����. �������� ����
		
		case "BS_F1_1":	//������
			dialog.text = "�����"+ GetSexPhrase("��","���") +" �������, �� ������ ���� � �������� ���"+ GetSexPhrase("","�") +"";
			link.l1 = "��� ����? ��� ������?";
			link.l1.go = "BS_F1_2";
		break;
		
		case "BS_F1_2": //������
			dialog.text = "��� ����, �� �������� ���������� � ����. ������ ������� �������� ��� ����, ����� �� ������ �� ���������� ���� � ��� ����� ���� ���. ��������� ��� ����������, �� ������.";
			link.l1 = "����������� ����� ��� ���-������ �����������. ��� ����� �������? �����? ������?";
			link.l1.go = "BS_F1_3";
		break;
		
		case "BS_F1_3":	//������
			dialog.text = "�� ������, �� ������. �� ������ ������ ���� ������ � ���������, ��� �������� �� ��������� ����� �� ����. � �������. ���������, �������� ��� � �������� ��� '����' � ������. ��� �����. �� ����� ��� �� ������. �.�";
			link.l1 = "������ �����! � � ����� �������"+ GetSexPhrase("","�") +" � ��� '������'. ��� ���������?";
			link.l1.go = "BS_F1_4";
		break;
		
		case "BS_F1_4":	//������
			dialog.text = "�������� � ����������, � ��� ������ � �����, ��� ���� ���� ��� �����. ��������� ����� ���� � ���� ���� �� �����. ���� ��� ������ ����� �� ����, ������ ������ � ������� ����-��";
			link.l1 = "�����, � ���������� ���� ����� �� ��������. �����, ������ ��������.";
			link.l1.go = "exit";
		break;
		
		//������ � ��: ������� ������, ����� ���� ��������� ������. �� ����� ���-�� ������. �������� ���������� ��������. ����� ��� ������? �� �������! � �����.
		
		//������� � ������
		
		//�������� ����
		
		case "BS_F1_5":	//������
			LAi_SetActorType(npchar);
			dialog.text = "�����"+ GetSexPhrase("��","���") +" �������, �� ������ ���� � �������� ���"+ GetSexPhrase("","�") +".";
			link.l1 = "��� ����? ��� ������?";
			link.l1.go = "BS_F1_6";
		break;
		
		case "BS_F1_6": //������
			dialog.text = "��� ����, �� �������� ���������� � ����. ������ ������� �������� ��� ����, ����� �� ������ �� ���������� ���� � ��� ����� ���� ���. ��������� ��� ����������, �� ������.";
			link.l1 = "����������� ����� ��� ���-������ �����������. ��� ����� �������? �����? ������?";
			link.l1.go = "BS_F1_7";
		break;
		
		case "BS_F1_7":	//������
			dialog.text = "�� ������, �� ������. �� ������ ������ ���� ������ � ���������, ��� �������� �� ��������� ����� �� ����. � �������: \n'��������, �������� ��� � �������� ��� '����' � ������. ��� �����. �� ����� ��� �� ������. �.'";
			link.l1 = "������ �����! � � ����� �������"+ GetSexPhrase("��","���") +" � ��� '������'. ��� ���������?";
			link.l1.go = "BS_F1_8";
			AddMoneyToCharacter(PChar, 50000);
		break;
		
		case "BS_F1_8":	//������
			dialog.text = "� ���������� ������ � �������� ��������, � ���� �� ��� ���� ������. ��������� ���� � ���� ���-��, ����� ��������. ��� ��� �������� ���� ����� ��� ���������. ��� � ��, � ������.";
			link.l1 = "��� �� ���� ������ ������? ��. ������ �� ��������. ���� ����� �� �������?";
			link.l1.go = "BS_F1_9";
		break;
		
		case "BS_F1_9":	//������
			dialog.text = "��� ����� ��������� � ���� �����, �������� ������� ���-�� �������.";
			link.l1 = "��, � ����� ������ � ����� ���������� �� ����! ������� �������� �������� ���������. �������, ��� ��-���� ���������, � �� ��������� ���� �����.";
			link.l1.go = "BS_F1_9exit";
		break;
		
		case "BS_F1_9exit":	//������
			DialogExit();
			PChar.quest.BSHangover_PortRoyal.win_condition.l1 = "location";
			PChar.quest.BSHangover_PortRoyal.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.BSHangover_PortRoyal.function = "BSHangover_PortRoyal";
			AddQuestRecord("BSHangover", "2");
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_7_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;
		case "BS_F1_8_MaksRoyal":	//������
			chrDisableReloadToLocation = false;
			dialog.text = "���������. ��� ����������� �����-�� �����, ����� ������� ����������. ������ ��������� � ������� ��������� ����.";
			link.l1 = "�����, ����� � ����� ������ ����� � �����. �����, ��� ��� �����������.";
			link.l1.go = "BS_F1_8_MaksRoyal_exit";
		break;
		
		case "BS_F1_8_MaksRoyal_exit":
			DialogExit();
			BS_ReplaceHostessWithMaks();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload9_back", "none", "", "", "", -1);
			DeleteAttribute(npchar, "LifeDay");
			AddQuestRecord("BSHangover", "3");
			//npchar.location = "none";
			sld = CharacterFromID("BS_Silver");
			sld.location = "none";
			sld = CharacterFromID("BS_Rakham");
			sld.location = "none";
			sld = CharacterFromID("BS_Vein");
			sld.location = "none";
			sld = CharacterFromID("BS_Bony");
			sld.location = "none";
			sld = CharacterFromID("Flint");
			sld.location = "none";
			
			ref jackman = CharacterFromID("Jackman");
			ChangeCharacterAddressGroup(jackman,"Pirates_townhall", "sit", "sit1");
			
			sld = CharacterFromID("gatri_temp");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_10";
			if(jackman.dialog.currentnode == "Jackman_Defeated")
			{
				sld.location.locator = "goto4";
			}
			
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
			LocatorReloadEnterDisable("Pirates_townhall", "reload2", false);
			LocatorReloadEnterDisable("Pirates_portoffice", "reload1", false);
		break;
		
		//������ � ��: ������ �� ��� ���������� ��������� � � ������, ��� ���� �������. ��������� ������ ���-�� � ������� ������ ����. � ���� �����!�
		
		//����� ������� ������� ������, ��� �������� � ������
		
		//������� ���� � ���� �����. ��� �������� �������. �������� ����� �� ����.
		
		//������ � ��: ������� ���� ������� ������ ������, � � �������� ����� � ���� �����
		
		//������� �� �������. � ���������� �����. ����� ���� ����� ���, ����� �������, ������ ��� � ������� �������.
		
		case "BS_F1_10": //�����
			dialog.text = "";
			link.l1 = "������ ����? ����� �������"+ GetSexPhrase("","�") +" ��� ������, ��� �� ����� �������� � ����� ������ �������� ������!";
			link.l1.go = "BS_F1_11";
		break;
		
		case "BS_F1_11": //�����
			dialog.text = "���� �������, �������������, ���������� ������! �� ��� �� ����! ������ ��� ������ �� �����! �� ��������� ��� � ��! � ����� ���������� ����� �� ���! � ������ ��������!";
			link.l1 = "";
			LAi_SetActorTypeNoGroup(npchar);
			link.l1.go = "exit";
			
			sld = CharacterFromID("Pirates_tavernkeeper");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_12";
			
		break;
		
		//���������� ��� �� �����. ����� �������.
		
		//��� � �������. ������ ����� � �������.
		
		//�������� � �������.
		
		case "BS_F1_12": //�
			dialog.text = "";
			link.l1 = "���� �������?";
			link.l1.go = "BS_F1_13";
		break;
		
		case "BS_F1_13": //�
			dialog.text = "������ ���� ���. ������ ��� � ������� ���� � ��� �������.";
			link.l1 = "������� ���� � �����, ����������� �����.";
			link.l1.go = "BS_F1_13exit";
		break;
		
		case "BS_F1_13exit": //�
			DialogExit();
			RestoreOldDialog(npchar);
			
			DoReloadCharacterToLocation("Pirates_tavern_upstairs","goto","goto1");
			pchar.quest.BSHangover_Vein.win_condition.l1          = "location";
			pchar.quest.BSHangover_Vein.win_condition.l1.location = "Pirates_tavern_upstairs";
			pchar.quest.BSHangover_Vein.function             = "BSHangover_Vein";
		break;
		
		//��� ������
		
		case "BS_F1_14": //����
			dialog.text = "����������!";
			link.l1 = "�� � ����! �� ��� ������� �����? ������� ����� � ����. �������� ���� ������� �� ������! �� �� ����?";
			link.l1.go = "BS_F1_15";
		break;
		
		case "BS_F1_15": //����
			dialog.text = "�������? ��, ���� ������, � � �����! � ���� ��� ���� ��������� ������� ����� ��������!";
			link.l1 = "��� � �����. � ���� ��������� ������� �� ����. ��������� � �������, ���� � ���� �����!";
			link.l1.go = "BS_F1_15exit";
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));
			BSRepairShip(npchar);
			AddQuestRecord("BSHangover", "4");
			npchar.location = "none";
			pchar.quest.BSHangover_RoyalVein.win_condition.l1          = "location";
			pchar.quest.BSHangover_RoyalVein.win_condition.l1.location = "PortRoyal_SecBrRoom";
			pchar.quest.BSHangover_RoyalVein.function             = "BSHangover_RoyalVein";
		break;
		
		case "BS_F1_15exit": //����
			DialogExit();
			npchar.dialog.currentnode = "BS_F1_15Vein";
		break;
		
		case "BS_F1_15Vein": //����
			npchar.dialog.currentnode = "BS_F1_15Vein"
			dialog.text = "����� ��������!";
			link.l1 = "�� ��� ��� �� ����.";
			link.l1.go = "BS_F1_15exit";
		break;
		//������ � ��: ������ � ���� �����������. ������ ������. ������� �� ����� � ����. ���� ��������� ����
		
		//��� ����������� ����� � ���� �����. ��� � ������� ����. ���� ��������.
		
		case "BS_F1_16": //������
			dialog.text = "";
			link.l1 = "����� �������, �����?";
			link.l1.go = "BS_F1_17";
		break;
		
		case "BS_F1_17": //������
			dialog.text = "� ��� �� �������. ������� �����������. � ��� ����� ������� �� ����������, ��� ��� ��� ����������, ��� � �� ��������� ����� ���������� ����� �����. ������ �������� �����������, �� ����� ������ ������� ������������, ��� ��� ������ ���� � ������� ������. � �� ���, ��� ���� ������� �����. � ����� � ��� �� ����. � ����� ����� ������ � ���� �������.";
			link.l1 = "";
			link.l1.go = "BS_F1_17exit";
		break;
		
		case "BS_F1_17exit": //������
			RestoreOldDialog(npchar);
			StartInstantDialogNoType("BS_Vein", "BS_F1_18", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_18": //����
			chrDisableReloadToLocation = false;
			npchar.location = "none";
			AddQuestRecord("BSHangover", "5");
			dialog.text = "�������?! �� ��� �� ��������, ��� ��� ����� ����� ��������!";
			link.l1 = "����� ���������. �� ���� �, ��� ����� ������ ��� ��� � ������� ������!";
			link.l1.go = "BS_F1_15exit";
			
			pchar.quest.BSHangover_VeinFollows.win_condition.l1          = "location";
			pchar.quest.BSHangover_VeinFollows.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.BSHangover_VeinFollows.function             = "BSHangover_VeinFollows"
			
			pchar.BSSearchStinger = 0;
			
			sld = CharacterFromID("Bridgetown_tavernkeeper");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";
			
			sld = CharacterFromID("Bridgetown_shipyarder");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";
			
			sld = CharacterFromID("Bridgetown_trader");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";
			
			sld = CharacterFromID("Bridgetown_hostess");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";
			
			sld = CharacterFromID("Bridgetown_usurer");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";
			
			sld = CharacterFromID("Bridgetown_priest");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";
			
			sld = CharacterFromID("Bridgetown_portman");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";
		break;
		
		case "BS_F1_SearchStinger":
			dialog.text = "";
			link.l1 = "������. � ���-���� ���. � ���� �� ������� ����� ���� �������? ���, ���� �����, ���� �������? �� ��� ����� ��������� ������ ����. ���� ������� ��������� �� ����������.";
			if(npchar.id == "BridgetownJailOff")
			{
				link.l1 = "������������. ��������� �� ���������� ������, �� ����� ����� '����������' �������� ��� �������� �� ����� ���� �������? ���, ���� �����, ���� �������?  �� ��� ����� ��������� ������ ����. ";
			}
			link.l1.go = "BS_F1_SearchStinger_1";
		break;
		
		case "BS_F1_SearchStinger_1":
			dialog.text = "��������, �� � ������� ����� ��� ���. ����� �� ���� ������.";
			link.l1 = "����.";
			link.l1.go = "BS_F1_SearchStinger_2";
		break;
		
		case "BS_F1_SearchStinger_2":
			pchar.BSSearchStinger = sti(pchar.BSSearchStinger)+1;
			Log_TestInfo(pchar.BSSearchStinger);
			RestoreOldDialog(npchar);
			DialogExit();
			if(npchar.id == "BridgetownJailOff")
			{
				chrDisableReloadToLocation = false;
				InterfaceStates.DisFastTravel = true;
				
				pchar.quest.BSHangover_StingerFound.win_condition.l1          = "location";
				pchar.quest.BSHangover_StingerFound.win_condition.l1.location = "Bridgetown_fort";
				pchar.quest.BSHangover_StingerFound.function             = "BSHangover_StingerFound";
			}
			else
			{
				BSHangover_SearchStingerCheck();
			}
			
		break;
		
		//������ � ��: ����� �������, � ������� �� ���������, ����� �������� � �������� �� ����� ���� �������. ����� ������ ���� ������ ������ � ����������� ������!�
		
		//����� �� ��������. � ������� ����� ������ ��� ��������-�������� �� �����. �������� �� ��� �����. ����� ����, ��� �������� ���� (������, ��, �����, �������, �������, ����) �����! ������ � ��: ������ �� ����� ��� �� ����� �������� � �������� ��� ��������, ��� ���-�� ������� �� ����. ������� ��������� ������!�
		
		//��� � �������. ���������, ���� ��� �����. � ������������ �������� ������. �� �������� ����-��� ������, � ������� �����, �������� ��� �������.
		
		case "BS_F1_19": //�������
			dialog.text = "��� ������ ��� ����������! ����������� � ��� �������� ��������� �����������!";
			link.l1 = "�� ���������� ����������� ����, ��� �� ���� � ���������� �������� �������� ����� �� ������? ����������� ���. ����� ��� �� ��������� �� �� ������!";
			link.l1.go = "BS_F1_19exit";
		break;
		
		case "BS_F1_19exit":
			StartInstantDialog("BS_Vein", "BS_F1_20", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_20": //����
			dialog.text = "���� � ����! ������! ���� ����� ����� ��� ��, ��� �� � ��� � ���������!";
			link.l1 = "";
			link.l1.go = "BS_F1_20exit";
		break;
		
		case "BS_F1_20exit":
			StartInstantDialogNoType("BS_Silver", "BS_F1_21", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_21": //�������
			dialog.text = "�, ���� ���� �� ���� �������� �����. ��� ��� �� ��, ������ ������ �� ��������, ������� ������� � ������� ��� � �������.";
			link.l1 = "� ��� �� �����, � ��������, ��� ��� � ����. ����� ��������� � ���� �����.";
			link.l1.go = "BS_F1_22";
		break;
		
		case "BS_F1_22": //�������
			dialog.text = "��� ��������� ��� �������. ��� ������ �� ������� �����? ������� ������, � � ��������. ����������, ��������� �������.";
			link.l1 = "";
			link.l1.go = "BS_F1_22exit";
		break;
		
		case "BS_F1_22exit":
			StartInstantDialogNoType("BS_Vein", "BS_F1_23", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_23": //����
			dialog.text = "������ ���� �������. �� ��� ��� ������ ��������? �� ������� �����������?";
			link.l1 = "";
			link.l1.go = "BS_F1_23exit";
		break;
		
		case "BS_F1_23exit":
			StartInstantDialogNoType("BS_Silver", "BS_F1_24", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_24": //�������
			dialog.text = "�����. ����� ��������� �� '�����' � ����� ����������� ���������. '��������� ����� ����, �����, �� �� ������', ������ � ������� ��� �� ����������, �� ��������. ��, �� ������. � ��� ���� ������� ��. ������, � �� ������ �� ���� ����������, ����� �� ����� ������� �������? ������� ��� ���-��, �����.";
			link.l1 = "��� ������ ����? �� ���� � ��� �������������, ����������!";
			link.l1.go = "BS_F1_25";
		break;
		
		case "BS_F1_25": //�������
			dialog.text = "�������� �� �� ������ ���� �� ������, � ��� ������� ��� ����� ������� ������� � ���� ���������, � �������� ������ ���� ����� � ������������! ������ ��� ������ ������, � ��� � �������� �������� ��������. ��, � � �� ���� ��� � ������ �������, ������� ���� � ���������� ������������, ������ ������� �� ��� ���� � �� ����. ������� ���� � ��� ������� �������, ��� ����� �������, ��� ���� ����������� ��������. � ����� ������, ���� ���.";
			link.l1 = "�������, ����� ������ �� ��� ������� ����������� � �������� �� � ��� �� ���������.";
			link.l1.go = "BS_F1_25exit";
		break;
		
		case "BS_F1_25exit":
			StartInstantDialogNoType("BS_Vein", "BS_F1_27", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_26": //����
			dialog.text = "�� � ��� ��� ������ � ������ ���������� �����, ���� ����� �� ���������!";
			link.l1 = "";
			link.l1.go = "BS_F1_27";
		break;
		
		case "BS_F1_27": //����
			dialog.text = "�� � ��� ��� ������ � ������ ���������� �����, ���� ����� �� ���������!";
			link.l1 = "";
			link.l1.go = "BS_F1_27exit";
		break;
		
		case "BS_F1_27exit":
			StartInstantDialogNoType("BS_Silver", "BS_F1_28", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_28": //�������
			dialog.text = "�� ���? � � �������, ���� ������ ���������� ������������ ��������, � �� ��������� ��� � ������� � ����� ������ ����� ����������. �, ���... ��... ������� �� ������� �� ���������? ������������ � ���.";
			link.l1 = "�����. ��� ������� ��� ���������� �����, ��� ��� ����� �� ���� �������.";	//- 32000
			link.l1.go = "BS_F1_28exit";
		break;
		
		case "BS_F1_28exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.location = "none";
			AddMoneyToCharacter(PChar, -32000 - rand(500));
			StartInstantDialogNoType("BS_Vein", "BS_F1_27_1", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_27_1": //����
			dialog.text = "������ ������. � ������� ���������, � �� ���� ����� ������� � �������, ������ ����� �� ��� ����������.";
			link.l1 = "�����.";
			link.l1.go = "BS_F1_27_2";
		break;
		
		case "BS_F1_27_2": //����
			DialogExit();
			UnLockWeapons("");
			InterfaceStates.DisFastTravel = false;
			chrDisableReloadToLocation = false;
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.location = "none";
			pchar.location.from_sea = "Shore5";
			
			sld = CharacterFromID("Bridgetown_tavernkeeper");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_RentRoom";
		break;
		
		case "BS_F1_RentRoom":
			dialog.text = "";
			link.l1 = "�����������. ���� ����� ������� �� ������.";
			link.l1.go = "BS_F1_RentRoom_1";
		break;
		
		case "BS_F1_RentRoom_1":
			dialog.text = "� ��� ����� �����.";
			if (sti(pchar.money) >= 100)
			{
				link.l1 = "���, �����.";
				link.l1.go = "BS_F1_RentRoom_2";
			}
			link.l2 = "��... � ��� �������.";
			link.l2.go = "BS_F1_RentRoom_exit";
		break;
		
		case "BS_F1_RentRoom_2":
			dialog.text = "������� ����. ��� ����.";
			AddMoneyToCharacter(PChar, -100);
			link.l1 = "���������";
			link.l1.go = "BS_F1_RentRoom_3";
		break;
		
		case "BS_F1_RentRoom_3":
			DialogExit();
			RestoreOldDialog(npchar);
			BSHangover_FewDaysLater();
		break;
		
		case "BS_F1_RentRoom_exit":
			DialogExit();
			npchar.dialog.currentnode = "BS_F1_RentRoom";
		break;
		
		//������ ������� � �����. ������� ������ � ����� � ������ ����� ��� ��� ��� �������. ����� ��� ���, �� �����, �������� �����
		
		case "BS_F1_29": //�����
			dialog.text = "��������� ������ ������, ����� �� ���� ������. ����� ����� �� �����. �� ������� �������� � ������, ��� �� �������.";
			link.l1 = "�������, �����.";
			link.l1.go = "BS_F1_30";
		break;
		
		case "BS_F1_30": //�����
			dialog.text = "� �������?";
			link.l1 = "��, ��. ��� ���� ��������� �������."; //- 32000
			link.l1.go = "BS_F1_30exit";
		break;
		
		case "BS_F1_30exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			StartInstantDialog("BS_Vein", "BS_F1_31", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_31": //����
			AddMoneyToCharacter(PChar, -500);
			dialog.text = "��� �� ������ �� �����. �� �������� ��� ���!";
			AddQuestRecord("BSHangover", "7");
			link.l1 = "��� ����. ����� ����������. ���� ����� � ��������� ������� ������ ����� � ������. � ����� ������. �������� �������� � ������ ���������, ������ �� �������, ������ � ������. ���������, ��� �� ��������.";
			link.l1.go = "BS_F1_31_1";
			
		break;
		case "BS_F1_31_1": //����
			npchar.dialog.currentnode = "BS_F1_15Vein";
			DialogExit();
			npchar.location = "none";
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_8_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;
		
		//���� ������. ������ � ��: ��� ��� ��, ���������, ����� ���� ��������� �������!�
		
		//��� � ������. ����� � ����������� ����� � � ���� ������ 60 ���. ����� � ����, ����� ��������� �� �������!� � ��� ���� � ����. ����� � ����� ������� ���������. ���, ����� ����� ������, ������� � ���������� ��������. � ������ 10-12 �����, ���������� �����. ������� ����� � ������ ������, �������������� � ����� ������. ������� ����� � ����������.
		
		case "BS_F1_32": //�������
			dialog.text = "";
			link.l1 = "��� ��� ������! ���������!";
			link.l1.go = "BS_F1_33";
		break;
		
		case "BS_F1_32_beaten": //�������
			dialog.text = "��, �������, ���� ��������� ��������...";
			link.l1 = "������ ���������� � �� ����, ���� ������.";
			link.l1.go = "BS_F1_32_beaten_1";
		break;
		
		case "BS_F1_32_beaten_1": //�������
			dialog.text = "�� ������"+ GetSexPhrase("","�") +"? �������� � ���� ������� ����.";
			link.l1 = "��� ��� ������! ���������!";
			link.l1.go = "BS_F1_33";
		break;
		
		case "BS_F1_33": //�������
			dialog.text = "�����, �� �������"+ GetSexPhrase("","�") +"? ��� �� ����, � ������� � �������. ��� ����� �� �������, � ����� ���� ������ ����� ��� ����. � ��� ����?";
			link.l1 = "�������, � ������. �� ����� ������ �����, � ����� � ��������� ����� �� ������� �������!";
			link.l1.go = "BS_F1_33_2";
		break;
		
		case "BS_F1_33_2":
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "BS_F1_33_1";
			DialogExit();
		break;
		case "BS_F1_33_1":
			dialog.text = "� ��� ������� ������ �����, � ����� ����� �� ����.";
			link.l1 = "�����, �� ������������, ��������.";
			link.l1.go = "BS_F1_33_2";
		break;
		
		//����� � ������. ������� ��� �����. ����� ���� (��������), ����, �����, ������ � ���� � ������ �� �������� ������ ������� ��������. ����� �� �� �������, ���� ��� �� �� �������� ������ ������ � ����� ����� ������. �������� ����. ������� � ������.
		
		case "BS_F1_34": //����
			dialog.text = "���, (������ ����� ����), ������� �� ��������, ��� ������ �� � ������ ���"+ GetSexPhrase("��","��") +", �������� ���������.";
			link.l1 = "������ ���� ����� ����! ������ ����� ������ ���! ����� ������ �� ������� � ���������� ����� �������. �� ����!";
			link.l1.go = "BS_F1_34exit";
			BSHangover_IsEveryoneOkay();
		break;
		case "BS_F1_34exit": //����
			DialogExit();
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));
			LocatorReloadEnterDisable("Shore5", "boat", false);
			chrDisableReloadToLocation = false;
			
			for (int i = 1; i <= 4; i++)
			{
				if(i == 1)	sld = CharacterFromID("BS_Vein");
				if(i == 2)	sld = CharacterFromID("BS_Silver");
				if(i == 3)	sld = CharacterFromID("BS_Rakham");
				if(i == 4)	sld = CharacterFromID("BS_Bony");
				Lai_SetActorTypeNoGroup(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.location = "none";
			}
		break;
		
		//������ � ��: ��� ������� ������� ����� ���� �����! �� �������� ������, ����� ��� �� ����. ����� �� ��� �� �����, ����� ����� ��� �� ������� � ������, ���� ����������� �� ������ ����������, ��� ��� ����� �� �����.
		
		//������ � ������ �����, ������� �� ������� ���� ����� �� �������. � ����� ������� � �������. ������� �� ������ ����� � ����� ������ ���������� ������. �����, ������ � �� �� ������. ��������. ������� ������
		
		case "BS_F1_35": //�����
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (int z = 1; z <= 6; z++)
			{
				sld = CharacterFromID("FlintOff"+z);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			PChar.quest.BSHangover_Fail1.over = "yes";
			PChar.quest.BSHangover_Fail2.over = "yes";
			
			dialog.text = "�� ������ ���� ����� ������ �� ���! ��� ����. �� �������� ����!";
			link.l1 = "�� ���?! �� �� ������ ���� ������? �� � ����"+ GetSexPhrase("�","") +", �����"+ GetSexPhrase("","�") +", ��� �� ��� ����! ׸�� ������, �� ����� ���� ����� �� ������ �������������! ����� �� ���?";
			link.l1.go = "BS_F1_36";
		break;
		
		case "BS_F1_36": //�����
			dialog.text = "�� ����� ��������, �������. �� ����� �� ������, �� �������� � �� ������ �����... �� ���� �� ��-�������. ����� �� ���� �� ���������. � �� ��������! �����, ��� ��. ��� ������ ����� �� ��� �����, ��� ������ ������� ������, ���������� �����������. ����������! ��� ������� � �� ����, ������, ��� ��������� ����, ������ ���� �� �������, �� ������ �� �������� �������� ��� ������������! ��� ����� ����, ��� ����� �� ������ ������� ������, ������� ����! �� ���������?!";
			link.l1 = "� ��� ��? ����� ����������? ���� ��� �������, ����� ����. ��� �� �����������? ������. ������ ��� ����� ��������� �����, ��� ������� �� ����� ��� �������� �������! ��� ���� ���� ���������? ��� ��?";
			link.l1.go = "BS_F1_37";
		break;
		
		case "BS_F1_37": //�����
			dialog.text = "��� �� ����� ��� ����������� ��������. ����� �������� �� ��� � ��������� ��� �������������� ����.";
			link.l1 = "׸��� � ���. ������ �� ����������� � ����. � ��������. � ��������� �� ��� ������. ������ � ����, ���� �� �������� �������! � ���� ���� �����, ������� ������, ��� �� ��� ������� ������� ����� �� ��������� ���� ��� �����.";
			link.l1.go = "BS_F1_38";
		break;
		
		case "BS_F1_38": //�����
			dialog.text = "� � �����, ��� ���� ���� � �������. ������, ��� �� ������. ������.";
			TakeNItems(PChar, "blade43", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("�� �������� ������!");
			link.l1 = "";
			link.l1.go = "BS_F1_38exit";
		break;
		
		case "BS_F1_38exit": //�����
			for (int k = 1; k <= 6; k++)
			{
				sld = CharacterFromID("FlintOff"+k);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			
			
			DialogExit();
			
			QuestAboardCabinDialogFree(); // ������ �����
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "");
			
			LAi_KillCharacter(npchar);
			DeleteCharacter(npchar);
			SetLaunchFrameFormParam("���� ���� ������ ������. ��, ��� ��������, ����������� ��� �����. � ����� �� �������� �� �������� ��� � ��������� �������� ����. ����� ���� �������� ���������� ����� - ���� ������� '�����������'. �� ��������� �, ������ � ������� �������� ������.", "", 0.1, 15.0);
			LaunchFrameForm();
			AddMoneyToCharacter(PChar, 2500000);
			AddQuestRecord("BSHangover", "9");
			sld = CharacterFromID("PortRoyal_hostess");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_39";
			
			DeleteAttribute(pchar, "LockMapReload");
			
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				sld = CharacterFromID(pchar.WhisperPGG);
				sld.dialog.filename = "Quest\WhisperLine\Whisper_cabin_dialog.c";
				sld.dialog.currentnode = "BS_21_WhisperIsHere";
				LAi_SetActorType(pchar);
				LAi_SetActorTypeNoGroup(sld);
				SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
				LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);
			}
		break;
		
		//����� ���� �����. �����! �� ������ ������ ����� �����, ����� ���� �������� �����. � ������� � 2.5�� �����, ����������. ������� ������ ������ � ����� - ���� ������� �������������. ����� ����� ������ ��� ���� ������� � �����. (!) �������� ����������� ������� � ������� � �����, �� ��������� �����. �������� ����� ������ ���������.
		
		//������ � ��: ������ ������! ������� ����� ����� -  �� ������ ��� ���������� � ��������� �����. ���� �� �������, ��� �� ���������� ���������, ��� ����������, � ������� � ��� ��� ��������� ��������� ������ ��������� � ��� ��������! ��, ��! � ����� ��������� ���� � ���� �����. ��������� ��� � �����.
		
		//����� � ��, �������� ���� �� �������. � ��� �� �������.
		
		//������ � �������� �����.
		
		case "BS_F1_39": //������
			dialog.text = "";
			link.l1 = "� � ���������! ����� � ��������, � �����. �� � ����? ���� ������, ��� ��� ���� �������� ��������!";
			link.l1.go = "BS_F1_40";
		break;
		
		case "BS_F1_40": //������
			dialog.text = "������� � � ����! ��� ����� ���������, ����� �� ������� ����, ���� �� �������. �� ���� ���������.";
			link.l1 = "���������, ������� �� ����.";
			link.l1.go = "BS_F1_40_1";
			pchar.quest.BSHangover_MaksOnShip.win_condition.l1          = "location";
			pchar.quest.BSHangover_MaksOnShip.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.BSHangover_MaksOnShip.function             = "BSHangover_MaksOnShip";	
		break;
		
		case "BS_F1_40_1":
			npchar.dialog.currentnode = "BS_F1_40_2";
			DialogExit();
		break;
		
		case "BS_F1_40_2": //������
			dialog.text = "�������, � ������ ����.";
			link.l1 = "�����, ����� ��������.";
			link.l1.go = "BS_F1_40_1";
		break;
		
		//����� �� �������. ������� ������ �� ���������. ������ �� �����, ��������� ������.
		
		case "BS_F1_41": //������
			dialog.text = "�������! ������� ������! ������� �������!";
			link.l1 = "";
			link.l1.go = "BS_F1_41exit";
		break;
		
		case "BS_F1_41exit":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10);
			StartInstantDialog("BS_Vein", "BS_F1_42", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_42": //����
			dialog.text = "���� � ����! ���?";
			link.l1 = "��������� ��� ������ ������, ������ ������! ���� ������? �����!";
			link.l1.go = "BS_F1_42exit";
		break;
		
		case "BS_F1_42exit":
			DialogExit();
			SetLaunchFrameFormParam("������ 12 ����� �������.", "", 0.1, 2.0);
			LaunchFrameForm();
			StartInstantDialogNoType("BS_Vein", "BS_F1_43", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		//�������� ������� 12 ����� �������
		
		//�������. �������� ����.
		
		case "BS_F1_43": //����
			dialog.text = "";
			link.l1 = "������� ������?";
			link.l1.go = "BS_F1_44";
		break;
		
		case "BS_F1_44": //����
			dialog.text = "��� ������ ����� ����������. ��� �� �������? ������, ��� �� ���� ������?";
			link.l1 = "��� ��� ����� �������� ��� ��� ���-�� �����.";
			link.l1.go = "BS_F1_45";
		break;
		
		case "BS_F1_45": //����
			dialog.text = "�������? ��� ���, � �� �������. � ��� �� �������!";
			link.l1 = "��������, �� ������� ������ �� ����� � �������� ��� ����. � ����� ������� � ���"+ GetSexPhrase("��","��") +" ������� ������ ������ � ����� ����� �������.";
			link.l1.go = "BS_F1_46";
		break;
		
		case "BS_F1_46": //����
			dialog.text = "� ����� ��� ������. �� �����������.";
			link.l1 = "��� �������, �� �� ����� �� � ��� ����������� ������� ��������, � ����� � ��� ��������� ��������� � �������.";
			link.l1.go = "BS_F1_47";
		break;
		
		case "BS_F1_47": //����
			dialog.text = "������ ����� �� �����? ����... � �����. �����!";
			link.l1 = "�����. ��� � ���������, � ����������.";
			link.l1.go = "BS_F1_47exit";
		break;
		case "BS_F1_47exit": //����
			AddQuestRecord("BSHangover", "10");
			BSChaseBegun_unlock_townhall();
			chrDisableReloadToLocation = false;
			DialogExit();
			Lai_SetActorTypeNoGroup(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			RemoveCharacterCompanion(PChar, npchar);
			pchar.quest.BSHangover_TownHall.win_condition.l1          = "location";
			pchar.quest.BSHangover_TownHall.win_condition.l1.location = "pirates_townhall";
			pchar.quest.BSHangover_TownHall.function             = "BSHangover_TownHall";
		break;
		
		//������ � ��: ������, ��� ����� ����������� �� ����� � ����������� ���������� ���. ������� ������ ��� ������� ������ � ������, ���������� �����, �� ���������� �������� ����������. ����� ��������� ��������, ������ � ������������. � �� ������ �� ����. ������ ���, ��� ��� �������, ����� ������ �� ���������.
		
		//��� � ����������. �����, ����, ����, ��, �����, ������, �������.
		
		case "BS_F1_48": //�� ����
			dialog.text = "";
			link.l1 = "����, ���, ��� �� �����. ����� ������ � �������, ����� �� ����� ������ �������. ������ �� �����, � ������, �� ������ �������� ����. ��������, � ����-�� �� ������� �� ������������� ����� � ������ ������������ � ����� � ���� ��������. � ���� � ���! ���� ��� ������, �� ��������. ������� �������, � ���, ��� � ��� ���� ��� ������� ������, �������������. � ������ � �����, ������ �����, �������� ��� �����.";
			link.l1.go = "BS_F1_49";
		break;
		
		case "BS_F1_49": //�����
			dialog.text = "� ������ ������� ��������� ���������� ����� �����, ����� ��� � �����!";
			link.l1 = "";
			link.l1.go = "BS_F1_49_1";
		break;
		
		case "BS_F1_49_1": //�����
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Silver", "BS_F1_50", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_50": //�������
			dialog.text = "���� �� � �������� ������, ��, ������, � ����� �� ������! � � ����������� �������, � � ������������� ������. �� ���� � ���������. ����� � �� ������. �� �����?";
			link.l1 = "";
			link.l1.go = "BS_F1_50_1";
		break;
		
		case "BS_F1_50_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Vein", "BS_F1_51", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_51": //����
			dialog.text = "�� �����. ��� ������ ������������ �� �������� ��� ���������� ��� � ���� �������� �� �������� ���� �����.";
			link.l1 = "";
			link.l1.go = "BS_F1_51_1";
		break;
		
		case "BS_F1_51_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Silver", "BS_F1_52", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_52": //�������
			dialog.text = "��� ��, � ����� ����������. ��������� ��������� �� ������ � �����?";
			link.l1 = "���, �������������. � ������� ����� ��������� �����.";
			PlaySound("interface\important_item.wav");
			Log_Info("�� ������ ����� � ������ ������");
			link.l1.go = "BS_F1_52exit";
		break;
		
		case "BS_F1_52exit": //�������
			DialogExit();
			Lai_SetActorTypeNoGroup(npchar);
			AddQuestRecord("BSHangover", "11");
			pchar.quest.BSHangover_Cutscene.win_condition.l1          = "location";
			pchar.quest.BSHangover_Cutscene.win_condition.l1.location = "pirates_tavern";
			pchar.quest.BSHangover_Cutscene.function             = "BSHangover_Cutscene";
		break;
		
		//������� �� � ������.
		
		//������ � ��: �������� ����� ������������. �����, ��� �� ������? ��� ������ ������? ������� �������, ��������� ������ ��� �������, ����� ������ ���� � ������, ���� � �������� �����. ��� ���� � ��� � �������. �� - ���� ����� �������, ��� ��, ����������� ����. ��, ���� ������� ��� �����, �� ��������. ����� �����!�
		
		//��� � �������, ����� �� �� ������, ������. ���� ��� ����� (������ ��� ��� �����!) ���������� �������� ������� ��� ���� ����������� � ���������.
		
		//������ � ��: ����� ��������� ������ �����������!�
		
		//��� � ����������. ������� �� ������, �����, �����, ����.
		
		case "BS_F1_53": //�������
			dialog.text = "";
			link.l1 = "���� ����������?";
			link.l1.go = "BS_F1_54";
		break;
		
		case "BS_F1_54": //�������
			dialog.text = "��. ��� ������������.";
			link.l1 = "21�3N, 80�00W. 15 25 N, 61 20 W. 12�07N61�40W. 72� 25'N 19� 00'W. 19�30N 80�30W.";
			link.l1.go = "BS_F1_55_1";
		break;
		
		case "BS_F1_55_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Vein", "BS_F1_55", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_55": //����
			dialog.text = "����������? ���� �� ���?";
			link.l1 = "��� ��� ��� �������� ���������... � ������� �������? � ������� ����������� �����-������ ������? ������ ���� ��� ��?!";
			link.l1.go = "BS_F1_56_1";
		break;
		
		case "BS_F1_56_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Vein", "BS_F1_56", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_56": //�������
			dialog.text = "����� ������ �������. ����� ������� �����, ������ �������, ������� � ������������!";
			link.l1 = "����������� ���� ����. ����� ��� ������ � ������ ������������ �� ������ ��� ��������� �����������! ����? �� ���� ������! ����� ����� �������� � �����. ׸��, ����, ����!!!";
			link.l1.go = "BS_F1_57_1";
		break;
		
		case "BS_F1_57_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Vein", "BS_F1_57", "Quest\BlackSails\BS_Final_1.c");
		break;
		
		case "BS_F1_57": //����
			dialog.text = "�� ������ ��� �������? � ��� � ���� ������� ������!";
			link.l1 = "���, ������, ��� ���� � ����� ������. ������"+ GetSexPhrase("","�") +", ��� ��� ����� ������ ����. �� ������� ����� �� �������. ���� ����� �������� � ������������, ����� �����. � ������ ����!";
			if(sti(pchar.money) < 2000000)	link.l1 = "���, ������, ��� ���� � ����� ������. ������"+ GetSexPhrase("","�") +", ��� ��� ����� ������ ����. �� ������� ����� �� �������. ��, ��������, � ��� ��������"+ GetSexPhrase("","�") +" ��. �������� ������� ����, ��������� ���� "+ GetSexPhrase("������","������") +". ���� ����� �������� � ������������, ����� �����. � ������ ����!";
			link.l1.go = "BS_F1_57exit";	//����� 2��.
		break;
		
		case "BS_F1_57exit": //����
			Lai_SetActorTypeNoGroup(npchar);
			AddMoneyToCharacter(pchar, -2000000);
			AddQuestRecord("BSHangover", "13");
			CloseQuestHeader("BSHangover");
			DialogExit();
			sld = CharacterFromID("BS_Silver");
			sld.location = "none";
			sld = CharacterFromID("BS_Rakham");
			sld.location = "none";
			sld = CharacterFromID("BS_Vein");
			sld.location = "none";
			sld = CharacterFromID("BS_Bony");
			sld.location = "none";
			sld = CharacterFromID("BS_Maks");
			sld.location = "none";
			BS_ReplaceHostessWithMaks();
			
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_14_WhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
			}
		break;
		
		//������ � ��: ���������� ����� ��������� ����. ���� �������, ����������� ����� �� ���. ��� �� ��� ���� ��� ������ ����, �����, ������ �������, ����� � ����� ������! ������� ��������� ����� ������� ��� ����� ������ �����. �� �������� ������� �������� �������, ���� ��� ������ � ��� ��������� ��������� ������ ��� ���������� ��� ������. �������� ����� ��������������! ����� ������ ��� �������.
		
		//���������. ���� ������ ����� � �� �� ������������ ���������. ����� � ���������� ������. ��� ����� ����� ������� ���� �� �������, ��� �� ������ �� ������ � �������� � ����� � ������������� ��������. �������? � �� ��. ������ ������ ��������. 
		
		
	}
}
