
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
		
		case "Jackman_Defeated":
			dialog.text = "����"+ GetSexPhrase("��","��") +" ����������� ���� ����?";
			link.l1 = "����� ���. ��� ������ ���������, ������ ����� �������� ���� � �����?";
			link.l1.go = "Jackman_Defeated_1";
		break;
		case "Jackman_Defeated_1":
			dialog.text = "��� ������ ���� ����� ������������ ���� ��� ���������-����������. ��� �����, ��� ��������� �������� ����������, ������� � ���� ������, ���� ��� �� ����� �� ������ �� �����"+ GetSexPhrase(".","... ��� ����.") +" ����� � ����� �������, ��� �����. �� ��� ��� ������ ���� ���������, ����� ����.";
			link.l1 = "� ���� ���������� ���� �������?";
			link.l1.go = "Jackman_Defeated_2";
		break;
		case "Jackman_Defeated_2":
			dialog.text = "�����������! �� � �� ������ ��� ����� ������� ��� ������ �� �����������! �� �� �����, ��� ������� ������, � ��� ����� ���.";
			link.l1 = "������� �������� ������, � �� ����� ��� ���� ����� ���������. �� �����, �����.";
			link.l1.go = "Jackman_Defeated_exit";
		break;
		case "Jackman_Defeated_exit":
			npchar.Dialog.Filename = "Mayor\Jackman.c";
			NextDiag.CurrentNode = "I_know_you_good";
            DialogExit();
		break;
		
		//�������� ������� ������� � �� �� ������. ������� �� �������� ���������� ��������� (���������) 2-3 ���������������.
		
		//������� � ��. ��� � ������� � �����. ���, �������. ��� ���� (���������)
		
		case "BS_NU_1":	//������
			dialog.text = "...";
			link.l1 = "���������� � ��������� ������! ����������, ������.";
			link.l1.go = "BS_NU_2";
		break;
			
		case "BS_NU_2":
            dialog.text = "�����������, "+pchar.name+". �����"+ GetSexPhrase("","�") +" ������������ ��� �������� �������?";
            link.l1 = "����� ���� ������. � ����, ��� ������� �� �������� ����� ���� ����� � ������, � ����� ������ � ���� ���-����� ����������.";
			link.l1.go = "BS_NU_3";
		break;	
		
		case "BS_NU_3":
            dialog.text = "����� ������� �� ������ ������? �� ����� ������ �������, �������� �� ����������, �� �� � ���� �������.";
            link.l1 = "����� �� �������, ����� ����� ������� � ����� ������ ������, ����� ������ ����� ����������! �� ���������, � ��� �?";
			link.l1.go = "BS_NU_4";
		break;

		case "BS_NU_4":
            dialog.text = "'���� �� ����'! ����� �� ������������� �� ��������. � ���� ������, �� ��� �� ���������, ������.";
            link.l1 = "������ ����.";
			link.l1.go = "BS_NU_5";
		break;
		
		case "BS_NU_5":
            dialog.text = "������ ����, ��� ����������. � ���-��� ��������� �� ����. ��� ���������� ��������.";
            link.l1 = "�� ���������, ��� � ����� ����� �������������� �� ����� ����������� �����������? ��� �� ������ ���� �� ���� ����?";
			link.l1.go = "BS_NU_6";
		break;
		
		case "BS_NU_6":
            dialog.text = "� �������, � ������� � ����������� � �����. � ������������ � ���������� ������������, ��, �������, ����� � ����������, ��������������� ��� ���� ������.";
            link.l1 = "���������, ������������ ������ ��!";
			link.l1.go = "BS_NU_7";
		break;
		
		case "BS_NU_7":
            dialog.text = "������� �������. ���-��� ��� ��������. �� ������ ������� ������� �� ����� � ������� ������� ���������. ������������, ��� ��� ������� �������� ��������������. � ���������� ����� ��� �� �������, ����� ������������� �� ������������. ��� ����� ������� � ������� ������� ��� �����. � ��������� ������, �� ��� ������ ���, ��� ��� �� ��, �� ���� �� ���������. ���-�� �������� ����������.";
            link.l1 = "� ��� ��������� ��� ���������"+ GetSexPhrase("��","���") +" � ��������� ��� ����������� �������. ������ ����������. ������ �� ����� ����������� ��� ��������. ��������������� �����������.";
			link.l1.go = "BS_NU_8";
		break;
		
		case "BS_NU_8":
            dialog.text = "��� ��, ��� � � ��� ����. � ������ ������������.";
            link.l1 = "���. ����, ����. �� ��� ������� ����� ���-������ �������? �� ���������� �� �� � ��������?";
			link.l1.go = "BS_NU_9";
		break;
		
		case "BS_NU_9":
            dialog.text = "������� '���������' �������� ������ � ���� ������. ��� ������ ������� � ������ �� �������.";
            link.l1 = "���� ���-��. ����� ����� ���������. � ����.";
			AddQuestRecord("BSUrka", "1");
			SetQuestHeader("BSUrka");
			CloseQuestHeader("BSChaseBegun");
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_NU_9_exit";
			PChar.quest.BSUrka_Negril.win_condition.l1 = "location";
			PChar.quest.BSUrka_Negril.win_condition.l1.location = "Shore35";
			PChar.quest.BSUrka_Negril.function = "BSUrka_Negril";
		break;
		
		case "BS_NU_9_exit":
            dialog.text = "�������� �� �������, �������.";
            link.l1 = "��, ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_NU_9_exit";
		break;
		//������ � ��: ������������� ���������� �������, ��������� ���� � ����� ��������� � ����� ������ �� ��� ��������� ���������. ����� ��������� ���������� � ����������� '���������' � ����������� �� �������. ��� �� �� �������� �������� ������.
		
		//������� �� ������, � ����� ������ � ��: ���������� �����, ����� �������, ������ ������� � ������ �����. ����� ����������� ������� � ������������
		
		//� ���� ����� � ������� � ������� ������. �������� � ������� � �����
		
		case "BS_NU_10":	//���������
            dialog.text = "�� ��� ��������! ��, ����� ���. �����"+ GetSexPhrase("","�") +" �� ��, ��� ���� ���� ����� ��� � ����� ���������! ��������� ����, ���� �������������, � �������� ��� � �������-�������� ��� ��� ���� ��������� ��������. � ���, ������ �� ��������, ��-�� ���� ��� ������ �� ��������! ������� ������ �� ����� ���� ����� � �� ������� �� ���������. ���� ������ �� ���� �� ����� �����������, ����� ����! �� � ����� �������! ��� ���, ������������� ����� �� ���� ���������, � ������ �����, � ��� ������, ���� ���������, ����� � ���� �������� ������. � ���� ���, ������� �� �������� ������, ����� �������, ����� ����� �� ������ ����� � ������ ���� �������� ������ ������, �����, ��� ����� �� �������. � ����� � ����� �� ������ ��������. � �����, �������� ��� ������ ������ ��������� � �������� ���������. ���, ����� ���������.";
            link.l1 = "���, ������ ���. ��� ��� ������-�� ����? ��������� �������������! � ���� ���� ���� ��� �����!";
			link.l1.go = "BS_NU_11";
		break;
		
		case "BS_NU_11":
            dialog.text = "��. ������ �����, ���������������. ��� ���. �����, �� ��������� �������, �������, ��� ���� �����, ���� �� ����� � �� ���� ������� �� �������� �����! � �� �����, ���� ������� �������� � ������ �� ������ ����������. �� �������, ����� ����, �����. � ������� - ���� ��������! ������ ������ ���� ������, ��� ���� �� ����� ����������� � ����, ���� - �� �� �����. ����� ������� ����, ���� �� �������! ��������� �� ��������� �������.";
            link.l1 = "������� �� �������. ���� �� ����� ������ � ����� ��������!";
			link.l1.go = "exit";
		break;
		
		//������ � ��: ����� ���, �������� ����� ������� � �������� ���� ����� �� ���������� �������������. ����� ������! �������, �������� �� ���������
		
		//������� � ����, ������� ���������� ���� (���������). ����. ��� �������, ��� �������� � ����� ����. ���� �� �������. ���� � �����, ����� ��������� - ������.
		
		case "BS_NU_12":	//����� ����
            dialog.text = "����! ����� ����������!";
            link.l1 = "���, ���, ���. ������� ������ ������ � ����� ���������� �������. ��� ��� ��������?";
			link.l1.go = "BS_NU_13";
		break;
		
		case "BS_NU_13":
            dialog.text = "� � ��� ���������� ���������. �������� ��������������, ��������� ������ �������, � ����� �������.";
            link.l1 = "� ������ ����� �������� �������������� �������� �� ����? ��� ��� �������, ������� � �������"+ GetSexPhrase("","�") +", ���� ����?";
			link.l1.go = "BS_NU_14";
		break;
		
		case "BS_NU_14":
            dialog.text = "������, ������, ���������� ����������� � ���������� �� ������ ��� ����������. ������ �����, ������, � ���������, ����.";
            link.l1 = "�������. ��������� ��������. ��� ��� ����� ������� �� ���� �����?";
			link.l1.go = "BS_NU_15";
		break;
		
		case "BS_NU_15":
            dialog.text = "�����. ������ ������� ������ �������, ��������, ���, ������. ������ ������ ����� ��� ����������, ������� � �������� ����� ����������, ��� ���� � ����� ������ ������������. ��� ��� ������� ���������� ��� ����� ����� �������� � �����������, � � ��������� ���, ��� ��� ����������� ����������, ������ ������ ���������� ��� ���������� ���������!";
            link.l1 = "� ����� ������� ��� ������ ���?";
			link.l1.go = "BS_NU_16";
		break;
		
		case "BS_NU_16":	//��� �����
            dialog.text = "����������� ����������� ��� � ����� ����������, ��������� ����� ������ �������� � ����������� ������� ��������� ������� � ��������������. � ��� �� ������������� ����� ���������, � ��� ��������, ������� �����!";
            link.l1 = "������ �� � �������, �����, �� ����� ��������� � ��� �����������! � ������ �� ������! � ������ �� ���� ������ � ����� ������ ������! ����� ����������? ������!";
			link.l1.go = "Fight_Billi_Bons";
			//link.l2 = "� ������� ��� ����. ��� ��� ��������� � �����?";
			//link.l2.go = "BS_NU_17";
		break;
		
		case "Fight_Billi_Bons":
			AddQuestRecord("BSUrka", "4");
			pchar.BSBonsKilled = true;
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BS_NU_17":
            dialog.text = "�� �������, � �������, ����� ����� ��� �������. ������: �������� �������� ����. ���� � ����������.";
            link.l1 = "�� �������, ��� ������.";
			link.l1.go = "BS_NU_18";
		break;
		
		//���������� �����. � ������� ������� �������� ������ �� ����.
		
		//������ � �� ���� ����� �����: ��������� � ����������� ��������� �����������. ���� ��. �������� ��������������! ����� ������������ ������. ���-�� �� ��� �������� ��������� � � ����, ����� ���-�� ������. � ����. �� ��������.
		
		//������ � �� ���� ������� ������� �����: �� ������(��) �������� ����������� �����, �� ���� ��������. �� ������� '����'! ����� ������ ������ ��������. ����� �������� ������ ��� ������� �� ������� �� �������. �������� �������� ����. ���� � ���������廻
		
		//��� ����� �������� � ��������, �� �������� ���������.
		
		//������� �� �������. �� ������ ������ ����� � ������. ������ ������ � �������� ��� ��� ���������.
		
		//� ���������� �����, �������, �����, ����. � ���� �������� ����. ���� ����������� ������ �� ������ � ��� ��������� ��� �����.
		
		case "BS_NU_18":	//�����
            dialog.text = "������� ��� � �����. ��� ���� ��������, "+pchar.name+"?";
            link.l1 = "����������� � ��� ������. ���... ��� ������� ������� � ���� �����.";
			link.l1.go = "BS_NU_18_1";
		break;
		
		case "BS_NU_18_1":
			DialogExit();
			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_19";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		
		case "BS_NU_19":	//����
            dialog.text = "�� ���� ��, ����! ������ ��������! �����, ��� ������ ������, ����� ������!";
            link.l1 = "";
			link.l1.go = "BS_NU_19_1";
		break;
		
		case "BS_NU_19_1":
			DialogExit();
			sld = CharacterFromID("BS_Maks");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_20";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		
		case "BS_NU_20":	//������
            dialog.text = "� �������, ������� ������. �������, � ���� ���� ����������� ��� ���������� � �������� �������, � � ��������� ������� � ��� �� ������ ���� � ������.";
            link.l1 = "";
			link.l1.go = "BS_NU_20_1";
		break;
		case "BS_NU_20_1":
			DialogExit();
			sld = CharacterFromID("Gatri_temp");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_21";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_21":	//�����
            dialog.text = "���� ��������, �����? ������� �������? ���-�� ��� ��� ������� � ������ ����� � �������� �� �����, � ��� �� ������ ������!";
            link.l1 = "";
			link.l1.go = "BS_NU_21_1";
		break;
		case "BS_NU_21_1":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_21_2";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_21_2":	//�����
            dialog.text = "������� ����, ��������! ������ ����, ���� ������, ������������� ������ ������� � �����. �������, ���� ���������� ���� �����. ��������, � �� �������� ���� ������� � ����� ����������.";
            link.l1 = "";
			link.l1.go = "BS_NU_21_3";
		break;
		case "BS_NU_21_3":
			DialogExit();
			sld = CharacterFromID("BS_Maks");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_22";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_22":	//������
            dialog.text = "��������� � ����, ���� ����� �� '�����' ���������. ���� � ���, ��� ��� ���� ������ ���������, �� ������ � ������, �� ��� ���� ����������� �������. � � ����, ���� ���� �������!";
            link.l1 = "����������! ������? ������� �� ����� ��������?";
			link.l1.go = "BS_NU_23";
		break;
		case "BS_NU_23":
            dialog.text = "'����' �������� ���������� ������ �� �������� � ����� �����, � ������������ �������� ����������� ��������� ��� ���������� ������� � ��������� �����. ���� �� ���� ��������� ����� ������������� �����, � ������ �� ��������� ����� �� �������������. ���� ������� � �� ����� ������� �����, ��� ��� ����� ������, ������������� ��� ������������ �� �����, ��� �� �����.";
            link.l1 = "";
			link.l1.go = "BS_NU_23_1";
		break;
		case "BS_NU_23_1":
			DialogExit();
			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_24";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_24":	//����
            dialog.text = "����� ����� �����?";
            link.l1 = "";
			link.l1.go = "BS_NU_24_1";
		break;
		case "BS_NU_24_1":
			DialogExit();
			sld = CharacterFromID("BS_Maks");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_25";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_25":	//������
            dialog.text = "����� ��� ��������� ������. ��� ���, '���� �� ����' �������� ����� ��������� ��������� ����� � ������� �� ����� �������� �� ��������� ��������� �������, ��� ����� ������� ������� ��������� ������� �� ������ � ��� ������ �������� � ������, ����� �������� � ��������. � ��������� ���� ����, �������?";
            link.l1 = "";
			link.l1.go = "BS_NU_25_1";
		break;
		case "BS_NU_25_1":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_26";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		case "BS_NU_26":	//�����
            dialog.text = "������. �� ������� ��� ��������� ��������, ���� �����, ����� �� �������. � ��� ����� �������� ������� � �� ����� �������� � ����!";
            link.l1 = "";
			link.l1.go = "BS_NU_26_exit";
			AddQuestRecord("BSUrka", "6");
		break;
		
		case "BS_NU_26_exit":
			DialogExit();
			NextDiag.CurrentNode = "BS_NU_28";
			
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", -1);
			
			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", -1);
			
			sld = CharacterFromID("BS_Maks");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", -1);
			
			sld = CharacterFromID("BS_Rakham");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", -1);
			
			sld = CharacterFromID("BS_Vein");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", -1);
			
			sld = CharacterFromID("gatri_temp");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "officers", "reload1_3", "reload1_2", "", "", "", -1);
		break;
		//������ � ��: ����� ���� ������ ����������. ������� ���������� ����� �� �������� � �������� �����. �� ��������� � ���������� ������� ����� ����� ����� � ��������� ����� �����. ������� ����: ��� ������� � ��������!��
		
		//��� ��������� �� ����������. ������� �� � �����.
		
		case "BS_NU_28":	//�����
			pchar.quest.BSUrka_Fail1.win_condition.c1 = "NPC_Death";
			pchar.quest.BSUrka_Fail1.win_condition.c1.character ="Flint";
			PChar.quest.BSUrka_Fail1.function = "BSUrka_Fail";
			
			pchar.quest.BSUrka_Fail2.win_condition.c1 = "NPC_Death";
			pchar.quest.BSUrka_Fail2.win_condition.c1.character ="BS_Vein";
			PChar.quest.BSUrka_Fail2.function = "BSUrka_Fail";
			
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//����� �������������� � �������
			LAi_SetImmortal(npchar, false);
			ProcessHullRepair(npchar, 100.0);
			ProcessSailRepair(npchar, 100.0);
			DeleteAttribute(npchar, "ship.blots");
			DeleteAttribute(npchar, "ship.sails");
			DeleteAttribute(npchar, "ship.masts");
			SetShipRemovable(npchar, false);
			Fantom_SetBalls(npchar, "war");
			SetCharacterGoods(npchar,GOOD_FOOD,1000);
		
            dialog.text = "";
            link.l1 = "��������� �����?";
			link.l1.go = "BS_NU_29_Ya_Ne_Krisa";
		break;
		
		//���� �� �������� ����� ������, �� ��������� ������:
		
		case "BS_NU_29_Ya_Ne_Krisa":
            dialog.text = "����������, ��� �� ���������.";
			
			link.l1 = "�� ��� ������ �������� ������. ������ �� ���� ������������, ��� �� �� ���������.";
			link.l1.go = "BS_NU_32_Ya_Ne_Krisa";
			if(CheckAttribute(pchar, "BSBonsKilled"))
			{
				link.l1 = "� ��������"+ GetSexPhrase("","�") +" � ������ ������ ��������. ���������� ������� ��������. �����. ����� �����.";
				link.l1.go = "BS_NU_30_Ya_Ne_Krisa";
			}
		break;
		
		case "BS_NU_30_Ya_Ne_Krisa":
            dialog.text = "����������? ��... � ����������, ��� �� �����, �� �������� �� ��������. �� ��������������...";
            link.l1 = "�� ����� ���� ������, �� �������� ����� ���������� � ������, ������, ������. ������� ���� �����.";
			link.l1.go = "BS_NU_31_Ya_Ne_Krisa";
		break;
		
		case "BS_NU_31_Ya_Ne_Krisa":
            dialog.text = "�� �� �� ����"+ GetSexPhrase("","�") +" ���? ������?";
            link.l1 = "��� ��������� ��������� ��������� ������, ���� ������! � � �� ������ ������.";
			link.l1.go = "BS_NU_32_Ya_Ne_Krisa";
		break;
		
		case "BS_NU_32_Ya_Ne_Krisa":
            dialog.text = "�� ���������� ��� �����, ��������� ���� ������. � �������� �������� �. ��� ��� ����.";
            link.l1 = "� ��� ���. �� ���? ���� ���������, ��� ��� ���������� '����'!";
			link.l1.go = "BS_NU_32_exit";
		break;
		
		case "BS_NU_32_exit":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "reload1_3", "reload1_2", "", "", "", -1);
			chrDisableReloadToLocation = false;
			DialogExit();
			
			PChar.quest.BSUrka_Pirates_town_Vein.win_condition.l1 = "location";
			PChar.quest.BSUrka_Pirates_town_Vein.win_condition.l1.location = "Pirates_town";
			PChar.quest.BSUrka_Pirates_town_Vein.function = "BSUrka_Pirates_town_Vein";
		break;
		
		//���� �� ������ ������, �� ��������� ������:
		
		case "BS_NU_29_Ya_Shpion":
            dialog.text = "����������, ��� �� ���������.";
            link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		//������ ����� � ����� �� �� ��������� � �������. �� ������ �� ���������� ������� � ������.
		
		//���� �� �������� ����� ������, �� ��������� ������:
		
		case "BS_NU_33_Ya_Ne_Krisa":
			FantomMakeCoolestSailor(npchar, SHIP_FRIGATE_H, "��������", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//���� �������������� � �������
			ProcessHullRepair(npchar, 100.0);
			ProcessSailRepair(npchar, 100.0);
			DeleteAttribute(npchar, "ship.blots");
			DeleteAttribute(npchar, "ship.sails");
			DeleteAttribute(npchar, "ship.masts");
			SetShipRemovable(npchar, false);
			Fantom_SetBalls(npchar, "war");
			SetCharacterGoods(npchar,GOOD_FOOD,1000);
			chrDisableReloadToLocation = false;
			LAi_SetImmortal(npchar, false);
            dialog.text = "� ��� �������� � �������?";
            link.l1 = "����������� �����. ������"+ GetSexPhrase("","�") +" � ���� ��� � ���������! � ������� ������ � ���� �����. ��� �� ���� ����� ����������! ��� �� ������ ������?";
			link.l1.go = "BS_NU_34_Ya_Ne_Krisa";
		break;
		
		case "BS_NU_34_Ya_Ne_Krisa":
            dialog.text = "� ��������� �������, ������� ���������� � ��� �� ����.";
            link.l1 = "��� �� ���� ����� ����� �����. ��� �, ���� �����������.";
			link.l1.go = "BS_NU_34_exit";
			
			//Sea_CabinStartNow();
			//Set_My_Cabin();
			//Sea_DeckBoatStartNow(pchar);
			//BSUrka_Curacao_SeaBattle(1);
			//DoReloadCharacterToLocation(Get_My_Cabin(),"goto","goto4");
			
			//setCharacterShipLocation(pchar, "Shore23");
			//pchar.location.from_sea = "Shore23";
			//setWDMPointXZ("Shore23");  // ����� �� �����
		break;
		
		//���� �� ������ ������, �� ��������� ������:
		
		case "BS_NU_33_Ya_Shpion":
            dialog.text = "� ��� �������� � �������?";
            link.l1 = "���� ���-���, ��� ����� ��������. �� �� ���� ����� '����'";
			link.l1.go = "BS_NU_34_Ya_Shpion";
		break;
		
		case "BS_NU_33_Ya_Shpion":
            dialog.text = "��� �������. � ����.";
            link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "BS_NU_34_exit":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "reload1_2", "", "", "", -1);
			BSUrka_Curacao_SeaBattle();
            pchar.quest.BSUrka_Curacao_SeaBattle.win_condition.l1 = "EnterToSea";
			pchar.quest.BSUrka_Curacao_SeaBattle.function    = "BSUrka_Curacao_SeaBattle";
			DialogExit();
			SetTimerFunction("BSUrka_Curacao_SeaBattle", 0, 0, 2);
		break;
		
		//������� � ����, ����� �� �������. � �������� ������� ������� �� �������. ��������. ���� ����! ���� ���� 6-8 ��������� �������� � ����������. ������ ��������. ����� ���, �� �� ������ ������.
		
		case "BS_NU_35":
            dialog.text = "";
            link.l1 = "����� �� �������, �� ��� '����'?";
			link.l1.go = "BS_NU_36";
		break;
		
		case "BS_NU_36":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "LockSeaReload");
            dialog.text = "��������, �� �������� ��������� �������� �� ����, �� ������ �����������. ������ �� ����� � ���� ������������. ��������� �� ������.";
            link.l1 = "";
			link.l1.go = "exit";
			
			pchar.quest.BSUrka_Curacao_Shore.win_condition.l1          = "location";
			pchar.quest.BSUrka_Curacao_Shore.win_condition.l1.location = "Shore23";
			pchar.quest.BSUrka_Curacao_Shore.function             = "BSUrka_Curacao_Shore";	
		break;
		/*
		case "BS_NU_36_exit":
			DialogExit();
			DoReloadCharacterToLocation("Shore23","reload","sea");
		break;
		*/
		//��������� �� ���� ������������, ������� �� �����. �� ������ ��������� ������, �����, ����, �����.
		
		case "BS_NU_37":	//�����
            dialog.text = "�� �� �������, ��� ��������, �� �������� �����, ���� �� ������� ������������ ��� ����������. �����, ��� �������� ��� ���������! � �� ������ � ��������.";
            link.l1 = "";
			link.l1.go = "BS_NU_381";
		break;
		
		case "BS_NU_381":
			DialogExit();
			sld = CharacterFromID("BSUrka_Prisoner");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_38";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		
		case "BS_NU_38":	//��������� ������
			sld = CharacterFromId("Flint");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorTurnToCharacter(sld, npchar);
            dialog.text = "��������� �������! ��� ���� ��� �����������! �� � �������� ���� �������! ������������ ��� ������� ������ ������� � ����������� �����. �� ������� ������� � ������� �� ������ � �����-������ �� ����. ��� ��, ��� � ���� ��� �������.";
            link.l1 = "";
			link.l1.go = "BS_NU_391";
		break;
		
		case "BS_NU_391":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_39";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		
		case "BS_NU_39":	//�����
            dialog.text = "���������, �� ������ ����.";
            link.l1 = "";
			link.l1.go = "BS_NU_401";
		break;
		
		case "BS_NU_401":
			DialogExit();
			sld = CharacterFromID("BS_Bony");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_40";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		
		case "BS_NU_40":	//����� ������� �������
            dialog.text = "����� � ��� �� ����� ����!";
            link.l1 = "";
			link.l1.go = "exit";
			DoQuestFunctionDelay("BSUrka_BonyHits", 0.3);
		break;
		
		case "BS_NU_41":	//����
            dialog.text = "������ ����� ���? ��� �� ���� �����?";
            link.l1 = "";
			link.l1.go = "BS_NU_421";
		break;
		
		case "BS_NU_421":
			DialogExit();
			sld = CharacterFromID("BS_Bony");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_42";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		
		case "BS_NU_42":	//�����
            dialog.text = "������ ���������� � ������� ����� ��������� ���� ���, ���� ��������� ����� ��������, ������� ������ �� ��� ��������� �������.";
            link.l1 = "";
			link.l1.go = "BS_NU_431";
		break;
		
		case "BS_NU_431":
			DialogExit();
			sld = CharacterFromID("Flint");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_43";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		
		case "BS_NU_43":	//�����
            dialog.text = "������ ����, ������� �� ������ �����������! ��� ��������� �������, ������� � ��������.";
            link.l1 = "";
			link.l1.go = "BS_NU_44";
		break;
		
		case "BS_NU_44":	//�����
			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			sld = CharacterFromID("BS_Vein");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
            dialog.text = "���, � ������! �����! ����� ���������.";
            link.l1 = "���� �������� ���� ����. �� ������!";
			link.l1.go = "BS_NU_44_exit";
		break;
		
		case "BS_NU_44_exit":
			AddQuestRecord("BSUrka", "7");
			DialogExit();
			sld = CharacterFromID("Flint");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			BSUrka_PlaceUrka();
			pchar.quest.BSUrka_Found.win_condition.l1          = "location";
			pchar.quest.BSUrka_Found.win_condition.l1.location = "Cumana";
			pchar.quest.BSUrka_Found.function             = "BSUrka_Found";	
		break;
		
		//������ � ��: ������ ����������, � ����� �������� �������. ����� ����������� � ���� ��������, ���� �� �� ������������
		
		//������� � ����. ���� �� ������ �����. ����� � ��� �����. � ����� ������ ����������� ��������� ������ ��� ��������� ����� �� ����. ����������������� � ��� ������. ��� ������ ���������. �� ����� � ��������� �������. ����.
		
		//����� ���������� ��������, ������ � ��: �������� ��! ��� ��� '����'. Ÿ ������ ��������� ������� � ������� �� ����� �� �����. ������������ �� �����!�
		
		//�� ������ � ������ ����. �������� ����� ������� �������, ���� �� ������ �� � ����� ���� �� 30 � ��� ���� ���. ������, �����, �������� � ����� ������� ���� ������������, ���� ����� �������� �� ������ �����. 
		
		//����� ������ ������ � ��: ����� �������, ������� ����� � ������� �� ��������(��) �� ���� ���. ��� ���, ���� ��������. ������ ������� �� ������� � ����������, ���� �� ��� �� �������� ��������� ������.
		
		//������ �������� ������� 3 ����, ������� ��������� �� �������
		
		//�������� �����
		
		case "BS_NU_45":	//�����
            dialog.text = "���� �������, ������� ������� �� ��������. ���� �������.";
            link.l1 = "";
			link.l1.go = "BS_NU_45_exit";
		break;
		
		case "BS_NU_45_exit":
			RemoveCharacterCompanion(PChar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", -1);
			DialogExit();
			
			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			sld = CharacterFromID("BS_Rakham");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", -1);
			
			sld = CharacterFromID("BS_Vein");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode   = "BS_NU_46_Ya_Ne_Krisa";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;
		
		//����� ������ �� �������. ������� ����. 
		
		//���� �� �������� ����� ������, �� ��������� ������:
		
		case "BS_NU_46_Ya_Ne_Krisa":	//����
            chrDisableReloadToLocation = false;
			RemoveCharacterCompanion(PChar, npchar);
			AddQuestRecord("BSUrka", "9");
			dialog.text = "� ��� ����� �������� ������ � ��, ��� ���� ������ ������. � �� ������ �������. ����� ���� ����� �����, �������� �������� ��������� ��� ������!";
            link.l1 = "� ����� ������� ����� �� ��������� ����! ��� ���������, �� �� ����������� �������! �� ���� ��������� ������� ������!";
			link.l1.go = "BS_NU_47_Ya_Ne_Krisa";
		break;
		
		case "BS_NU_47_Ya_Ne_Krisa":
            dialog.text = "� �����. ��������, ���� �� ��������. �� ����� ��������.";
            link.l1 = "���� �� �������. �����.";
			link.l1.go = "BS_NU_47_Ya_Ne_Krisaexit";
		break;
		
		case "BS_NU_47_Ya_Ne_Krisaexit":
			RemoveCharacterCompanion(PChar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", -1);
			DialogExit();
			
			pchar.BSBonsSpawned = true;
			BSBons_SeaBattle(true);
			BSChaseBegun_unlock_townhall();
		break;
		
		//���� �� ������ ������, �� ��������� ������:
		
		case "BS_NU_46_Ya_Shpion":	//����
            dialog.text = "�� � ���-�� ���������� �����"+ GetSexPhrase("","�") +"? ��� �� ��������.";
            link.l1 = "��, ���� ���-���. ����� ������ � ��������"+ GetSexPhrase("��","���") +" � ����� ������, ������� �� ���� �����, � ������ ���������� ������� ��������. �� ���������! �� ����� ������ ������ � ����� �� ���������� ������������ ������� � ��������������. ��������� ����� ������ ��������. � ������� ������ � ��� �� ��� � ��������� �������� �� �������, ���� �� � ����. ��� �������?";
			link.l1.go = "BS_NU_47_Ya_Shpion";
		break;
		
		case "BS_NU_47_Ya_Shpion":
            dialog.text = "������� ����� �� ���� ���� ��������� ��������� � ������� �� ���������� ������? � ����� �� ������ ����� ����������� ������ ����? ��� �� ������� ���������� �� ���?";
            link.l1 = "������ �� ��� � ����, ����� ������ � ��� ���� �� ������� ������� �� ����. ����� ������ ��� ��� �������! ����� ������ � ������, ����� ��� �������, ����� ��� � �������. �� ������ ����� ����� ��� ������� �������.";
			link.l1.go = "BS_NU_48_Ya_Shpion";
		break;
		
		case "BS_NU_48_Ya_Shpion":
            dialog.text = "� � ����, ���� �� ����� ���� ���� �������, �� ���������� � ��� �����, ����� �� �����, ��� ��� ������� � ��� ���� �����!";
            link.l1 = "������ �����, ����� ������. ��, �� ��� ��� �������. � ����.";
			link.l1.go = "exit";
		break;
		
		//���� �� �������� ����� ������, �� ��������� ������ � ��: ��������� ����� ���������� � ������ ������! ���� ������������ �� ��������
		
		//���� �� ������ ������, �� ��������� ������ � ��: ����� � ����, ����� ������ � ����� ������. ���� ����������� �������� ��� � �����. ���� �� ��������
		
		//���� ������ �� ��������� ��������� � �� �������� �������� ���������� ����. ��������� �������� ������� ����. � ��� ���� ��������. ������� ��������, ������ ����� � ����. �� ��������� � ������ � �� ��������� �� ���. ������� ������ �������
		
		//���� ������ �������, �������� ����, �������� ��� �� ������.
		
		//� ����� ��������� � ��� ������ �� ������� ������ � ������� ������� ��������. ������� �� ��������. ���-���. ���������� �������� ���� � ���������. ������
		
		case "BS_NU_49":	//�������
            dialog.text = "�� ���� ���� ����� �����! ��� � ���� �� �������� � �� ���� ����������� ������!";
            link.l1 = "� ���� �� ������� ���? ��-�� �����? ��-��. ��� ���� � ��� �������� ����� �������, � �� ��, ��������� ������ �������!";
			link.l1.go = "exit";
		break;
		
		case "BS_NU_49":
            dialog.text = "�� � ���� ������� �������� � ����� ��� ������!";
            link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//����. �� ����� �������� �������� ����� - ������ �����. � ������ � ����� 300� � �������� ���� �� 50 �������. ������ � ��: ��� ������� � ��������, �� ���� ��������� �������� ��������. ���������� ����� ��� �� ���� ��������� � ����� ������� ����� ���� �����. ��������� ������ ������, ������ �������!�
		
		//����� ����� � ���� � ����������, � ����� � ���������� ������.
		
		//������������, ��� � ����������. ��, �����, ����, �����, ����
		
		case "BS_NU_50":	//�����
            dialog.text = "���� �������, ������ ��������� � �������� �� ����� ���� �����, ��������� � ������� ������� ����� �� ��������� ��������. � ���� ��������� ������ �� �������� ��������� ����! �� ������ �������, � ������� ��� ����������� ����� ����. �� ���! �� ���!";
            link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//���� ���� � ������� � ��� ���, ����� ������, ����� ������ �� ����������. ��� ��������.
		
	}
}
