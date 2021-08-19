
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
		
		//������� � �������� ������� ���� � ���������, ����� ���. � �� ��������� ����. ����� ���� � �������. ���� ����� ������ �� ����� �����.
		//���� ��������. ��, �����, �������, ����. ������ �������, ��������� ����.
		
		case "BS_KS_1":	//�����
			dialog.text = "����������, �� ������������.";
			link.l1 = "���? �, �� ��� ��������? ��, ������ ��� � ���� ����� �� ��������.";
			link.l1.go = "BS_KS_2";
		break;
			
		case "BS_KS_2":
            dialog.text = "���� � ���� �����, ������ ���� �������, �� ������������� - ����� ���������. ������ �������, �� ������������� � ��������� "+GetFullName(pchar)+" � ���� �� �����. ������ � ������ ������ ����� ����. ����� �����. ������ �������?";
            link.l1 = "";
			link.l1.go = "BS_KS_3_1";
		break;
		
		case "BS_KS_3_1":
			sld = CharacterFromID("BS_Silver");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_3";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;
		
		case "BS_KS_3":	//�������
            dialog.text = "�������. ����� ��� ������ �������? � �����, �� ��� ������.";
            link.l1 = "";
			link.l1.go = "BS_KS_4_1";
		break;

		case "BS_KS_4_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.currentnode = "BS_KS_4";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		case "BS_KS_4":	//�����	
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorTypeNoGroup(npchar);
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorTurnToCharacter(sld, npchar);
            dialog.text = "(������� �� ����� �� ��������)";
            link.l1 = "";
			link.l1.go = "BS_KS_5_1";
		break;
		
		case "BS_KS_5_1":
			sld = CharacterFromID("BS_Silver");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.currentnode = "BS_KS_5";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;
		
		case "BS_KS_5":	//�������
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorTypeNoGroup(npchar);
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorTurnToCharacter(sld, npchar);
            dialog.text = "���� �� ��, �� ��� �������, �������.";
            link.l1 = "";
			link.l1.go = "BS_KS_6_1";
		break;
		
		case "BS_KS_6_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.currentnode = "BS_KS_6";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		case "BS_KS_6":	
			SetQuestHeader("BSCourtlyPassions");
			AddQuestRecord("BSCourtlyPassions", "1");
		
            dialog.text = "��� ������ ���������� � �����, � ���� ����� ��� �� ��������. �����.";
            link.l1 = "� ��� �� �������. �������, �� ����.";
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "BSCPFlint_talk");
			DeleteAttribute(npchar, "curtown");
			pchar.BSCPSailor_talk = true;
			pchar.BSCPSilver_talk = true;
			link.l1.go = "BS_KS_6_exit";
		break;
		
		case "BS_KS_6_exit":	
			DialogExit();
			RemoveCharacterCompanion(PChar, npchar);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "Pirates_store", "", "", "", -1);
			//��������� �������.
			if(pchar.location == "LeFransua_port" || pchar.location == "FortFrance_town" ||  pchar.location == "Shore38" ||   pchar.location == "Shore39")
			{
				BSCourtlyPassions_sailor();
			}
			else
			{
				SetFunctionExitFromLocationCondition("BSCourtlyPassions_sailor_begin_again", pchar.location, true);
			}
			
		break;
		
		//������ �������� �� ��������� ����. ����� ����� � ��������, ���� ��������.
		
		case "BS_KS_7":	//���������� � �������
            dialog.text = "�������?";
			string order1, order2, order3;
			if (pchar.nation != FRANCE)
			{
				order1 = "����������� �� ���� � ������� ����������� ����. ";
				Flag_FRANCE();
			}
			else order1 = "";
			if (pchar.location != "Shore39") 
			{
				order2 = "�������� ������� � ����� �� �����. ";
				pchar.location.from_sea = "Shore39";
			}
			else order2 = "";
			if (order1 == "" && order2 == "") order3 = "������� �� ������� � ���� ������. ���� ����� �������, �����, ��� ���� ���������, �� ����� �� �����.";
			else order3 = "���� ����� �������, �����, ��� ���� ���������, �� ����� �� �����.";
            link.l1 = order1+order2+order3;
			link.l1.go = "BS_KS_7_1";
		break;
		
		case "BS_KS_7_1":	//���������� � �������
			AddQuestRecord("BSCourtlyPassions", "2");
			dialog.text = "��������, �������!";
            link.l1 = "������� �� �����, ������, � ���� �� ������ ���� � ���� �������. ��������� � ��� �� ����, � �����, ������� ������� ���� �� �������.";
			link.l1.go = "BS_KS_7_2";
		break;
		
		case "BS_KS_7_2":	//���������� � �������
            dialog.text = "�� ��� ���, �������. ����� ���������������, �� � ������������. � ������� ������ � �� ���� ����� ������.";
            link.l1 = "��� ������. �����, �����, �������� ������.";
			link.l1.go = "BS_KS_7_2_exit";
		break;
		
		case "BS_KS_7_2_exit":	//���������� � �������
			DialogExit();
			DeleteAttribute(pchar, "BSCPSailor_talk");
			LocatorReloadEnterDisable(pchar.location.from_sea, "boat", true);
			chrDisableReloadToLocation = false;
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", Get_My_Cabin(), "", "", "", 10);
			sld = CharacterFromID("Flint");
			DeleteAttribute(sld, "curtown");
			//��������� ��������.
			if(pchar.location == "FortFrance_town")
			{
				BSCourtlyPassions_sailor();
			}
			else
			{
				SetFunctionExitFromLocationCondition("BSCourtlyPassions_sailor_begin_again", pchar.location, true);
			}
		break;
		
		//����������� ������� � �� �����
		
		//������ � ��: ������� ������� � ��������� ����. ������ ������� ��� ������ ���������� �������? �� �� �����, ���� �������� ������� �����, ��� ������ � ������ ����� ���� � ������� �����
		
		//�������� ����� � ����. ������ � ���� �� ����� �������.
		
		//�� ��������� ����, ������� ������� ������.
		
		case "BS_KS_8":	//�������
            for (i = 1; i < 7; i++)
			{
				sld = CharacterFromID("BSOnTheHorizon_enemyfleet"+i);
				sld.LifeDay = 0;
			}
			dialog.text = "���������� � ��� �������, � ������� � ���� ����!";
            link.l1 = "�������. ��� ��� ��� �� ������� � ����� �� ���� �������? ������ �������, ����� ����. � �� � ���������� ��� �������.";
			link.l1.go = "BS_KS_9";
		break;
		
		case "BS_KS_9":
            dialog.text = "���, ���������, ��� ����� ����� � ������� ���������� ��� ��������� �����������: ������ ������!!! ���-����� ��������!!! ���� ����!!!";
            link.l1 = "��. � �� ��������. ������ � ���� ���, ���� ����� ������� �������� ������. �������, ��� ������ ��� ������� ����.";
			link.l1.go = "BS_KS_10";
		break;
		
		case "BS_KS_10":
            dialog.text = "� ����� ������� ����� ����� �������! � ����� �������� �� ����� ������ ������� �����!";
			link.l1 = "��������. �� ���, ��������� ���, ����� ��� � ������� ������ ��� ����������. � �����. � ����� �� ������, �� �����. ���� ���������? ���� �. �����.";
			link.l1.go = "BS_KS_11"
		break;
		
		case "BS_KS_11":
            dialog.text = "��-��. �����, � ����. � ������� ���� ������ ����, ������ �����. ������� �� ��������. ������ ����� ��������. ��� � ����� ���������... ���� ��� �������. �� �� ������ �� ������� �������, �� � � ������� �� � �������. �� ���� �������. ������ ���� ������� � ���������� ������� ��� �������� � ����� �������� � �����.";
            link.l1 = "������� � ����� ������, ���� �� �������� ��� ��������� ��������� �� ������ ��.";
			link.l1.go = "BS_KS_12";
		break;
		
		case "BS_KS_12":
            dialog.text = "��������. �������� � ������ ���������� ��������, ������� ����� �� ����, ���"+ GetSexPhrase("","�") +" ���������. � � ��� � ��� �������� � ���, �� ����� ����� � � ������ ������ � �� ��� � �����������. �������� �� ������������ ����� � ������� ���� ��� ����-������ �� ������� ��� �������. ��� � ����� ��� ������ ������.";
            link.l1 = "���, � ������ ���?";
			link.l1.go = "BS_KS_13";
		break;
		
		case "BS_KS_13":
            dialog.text = "�� � ����� ��� �� �������� ������� �����. ����� �������. ���� � ������ �������, �������������, ���"+ GetSexPhrase("","�") +" ������, � ����� �� ��� ����� ������� ����������. �� ������ ��� ������� ��� � ���������� � ��������� �� ���. ���-�� ���-�� �������, � �� ����� ������ ����� �����. ���� ����� ����� �������, ������ � � �������, �������� � ����� �������� ���� � ���.";
            link.l1 = "� ����� ��� � ������� ����, ���� ����� � �������� � �������? ��� �� �������? � �� �������?";
			link.l1.go = "BS_KS_14";
		break;
		
		case "BS_KS_14":
            dialog.text = "�� ������ ������, ��� ���� � ���� � ��������, � ���� ������� ��������� ���� � ������� ��������. ������ ��� ����� �� �� ������.";
            link.l1 = "��������� ����� ������... ����� ��� ������ �������� � �������� �����������. ���� ����������� ����������� ��� ��� ������.";
			link.l1.go = "BS_KS_14_1";
		break;	
		
		case "BS_KS_14_1":
			AddQuestRecord("BSCourtlyPassions", "3");
			dialog.text = "� ������� ��� � �������. �� ����� �������.";
            link.l1 = "��-�� ��.";
			link.l1.go = "BS_KS_14_2";
		break;
		
		case "BS_KS_14_2":
            DialogExit();
			DeleteAttribute(pchar, "BSCPSilver_talk")
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = CharacterFromID("FortFrance_tavernkeeper");
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_15";
		break;
		
		//������ � �� ��������� � �����, ����� � �������, ������ � �����, ����� �� ����... ������ �� �������, �� ������ ����� � �������, ��������� ��� ��� ������.
		
		//���� �� �����. � ������� ������������ ������
		
		case "BS_KS_15":	//������
            dialog.text = "����������� ��� � ����� �������� ���������, �������. ��� ���� ������?";
            link.l1 = "� ��� � ��� � ������ � ������� ���������? ������"+ GetSexPhrase("","�") +" �, ��� ���� ���������� � ��� ����, �������.";
			link.l1.go = "BS_KS_16";
		break;
		
		case "BS_KS_16":
            dialog.text = "� ���������� ������ � ��������������� ������ �������������, "+ GetSexPhrase("�����","�����������") +". � ���� ��������� ���������.";
            link.l1 = "�������. ������� �������� ������� ������� ���� �������������?";
			link.l1.go = "BS_KS_17";
		break;
		
		case "BS_KS_17":
            dialog.text = "�������? � ��� ����� �� ����������? ���� ����� ����, � � �� ��������.";
			NextDiag.TempNode = "BS_KS_15";
			if (sti(pchar.money >= 5000))
			{
				link.l1 = "� ������.";
				link.l1.go = "BS_KS_18";
			}
			link.l2 = "���������, ���� ����� ��� ������?";
			link.l2.go = "exit";
		break;
		
		case "BS_KS_18":
			AddMoneyToCharacter(pchar, -5000);
            dialog.text = "���� ����� ������, ��� �������� � ������� �������. ����� ����������� � ��� � �������, ��� ����������� ���� ����� ����.";
            link.l1 = "� �� ��� � ���� ��������"+ GetSexPhrase("","�") +" ���� �����? ��� ���� �������� ����� � ����� �� ������?";
			link.l1.go = "BS_KS_19";
		break;
		
		case "BS_KS_19":
			AddQuestRecord("BSCourtlyPassions", "4");
            dialog.text = "����������! �� ��� � ������, ��� ��� �������� �� ���������, ������ � ������ �� ����� ������������. ������� ������� ������ �����... ���, ���� ��� �������. ��� ��� ��� ������, ��� ����� �� ����� ���� �������. ������, ����������, ���������� �� ������. �������� ���.";
            link.l1 = "� ����� � ������ ��������. �����, ����. � ��� ���� � ������ ����������?";
			link.l1.go = "BS_KS_19_1";
		break;
		
		case "BS_KS_19_1":
            dialog.text = "� � �������� ��� �� ����. ����� ��� �������. ��� ��� � ��� �� �� ���.";
            link.l1 = "�� �����.";
			link.l1.go = "BS_KS_19_1exit";
		break;
		
		case "BS_KS_19_1exit":
			DialogExit();
			npchar.dialog.filename = "Common_tavern.c";
			NPChar.Dialog.CurrentNode = "First time";
			sld = CharacterFromID("FortFrance_hostess");
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_20";
		break;
		//������ � ��. ���� �������� ������ � �������.
		
		//��� � �������, ���������� � ������ � �������.
		
		case "BS_KS_20":
            dialog.text = "����������, "+GetSexPhrase("�����","�����������")+". ������ ��������?";
            link.l1 = "� ���� �������� ����� � ����� �� ����� ��������. �������, ��� ������������ ������.";
			link.l1.go = "BS_KS_21";
		break;
		
		case "BS_KS_21":
            dialog.text = "��� ������ �� � ��� �����, ����� ��������� ��������. �� �� ��������� ����� �� � ��� ����� ������� ����������.";
            NextDiag.TempNode = "BS_KS_20";
			if (sti(pchar.money >= 50000))
			{
				link.l1 = "���������, �����������, � ��� ������ �� ����������.";	//��� �� 10000
				link.l1.go = "BS_KS_21_exit";
			}
			link.l2 = "���������, ���� ����� ��� ������?";
			link.l2.go = "exit";
		break;
		
		case "BS_KS_21_exit":
			DialogExit();
			npchar.Dialog.Filename = "Common_Brothel.c";
			NPChar.Dialog.CurrentNode = "First time";
			LocatorReloadEnterDisable("FortFrance_Brothel", "reload2_back", false);
            AddMoneyToCharacter(pchar, -50000);
			
			sld = GetCharacter(NPC_GenerateCharacter("BS_Maks", "BS_Maks", "woman", "woman", 1, PIRATE, -1, false));
			sld.name 	= "����";
			sld.lastname 	= "";
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto3");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_22";
		break;
		
		//������� ������� �����
		
		case "BS_KS_22":	//������
            dialog.text = "� ����� ����, "+ GetSexPhrase("�����","�������") +". � �� ��� ����� �������, ����?";
            link.l1 = "�����, �� ����������, ��� �� ���� �� �� ������� ������.";
			link.l1.go = "BS_KS_22_1";
		break;	
		
		case "BS_KS_22_1":	//������
            dialog.text = "����� �����?";
            link.l1 = "��� ��� �������� � ����� ������������. ������� � ����. ��� ����� ��, ��� �� �������� ������� �������� �����. ����� ���, ��� �������� ��� ��������� ������ � � ������ �� �����, ���� ��� ���� ������.";
			link.l1.go = "BS_KS_23";
		break;
		
		case "BS_KS_23":
			AddQuestRecord("BSCourtlyPassions", "5");
            dialog.text = "�� ��� �����"+ GetSexPhrase("","�") +" �� �������� ������! ����� �� ����� � ������. ��� � ���� �������? � ������� ��� ����� ������� ����� ����� � ����������, ����� � ������. �����, ����� �� ����� �������, ������ ���� � ���� �����?";
            WaitDate("",0,0,0,24 - sti(environment.time),5);
			link.l1 = "������������. �� ��������, ��� ���� � ����� �� �����.";
			link.l1.go = "BS_KS_24_1";
		break;
		
		case "BS_KS_24_1":
			sld = CharacterFromID("BS_Silver");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.currentnode = "BS_KS_25";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;
		//�� ������ �� ������� ������ � ���������
		
		case "BS_KS_24":	//�������
            dialog.text = "��� ���� ������?";
            link.l1 = "������ ������������ � ���������� � �������.";
			link.l1.go = "BS_KS_25";
		break;
		
		case "BS_KS_25":
            dialog.text = "���, � �� ����. � ������ ������ ����, ��� ������.";
            link.l1 = "� �������"+ GetSexPhrase("","�") +". ���� ����� � ������� ���� ������� ������, ����� ��������� � �� �����.";
			link.l1.go = "BS_KS_26";
		break;
		
		case "BS_KS_26":
            dialog.text = "� ���������� �������������.";
            link.l1 = "��������.";
			link.l1.go = "exit";
			LAi_LockFightMode(PChar, true);
			PChar.quest.BSCourtlyPassions_wait.win_condition.l1 = "location";
			PChar.quest.BSCourtlyPassions_wait.win_condition.l1.location = "FortFrance_town";
			PChar.quest.BSCourtlyPassions_wait.function = "BSCourtlyPassions_wait";
		break;
		
		//������ � �� ���������� ����� ����������� � ���������� ���� �� �����. ��� ��������� ������, ����� �������������. �� ��. � �� ������ ����� ������ ��������� � ���� ������
		
		//����� �� ��������� ��������. ��� � ��������. ��� �� ������ �������, ���� ���� ����. ���� ����� ���, �� �����������.
		
		case "BS_KS_27":	//������ ����
            ref _location = &locations[reload_location_index];
			LAi_LocationFightDisable(_location, false);
		    dialog.text = "������ ������� �� ��� ������������?";
            link.l1 = "���� ��������, ������. � ��������, ������� �� �������� ����.";
			link.l1.go = "BS_KS_28";
		break;
		
		case "BS_KS_28":
			AddQuestRecord("BSCourtlyPassions", "6");
			LAi_LockFightMode(PChar, false);
            dialog.text = "��� ������ ��� ������? ����� �� ����!";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "", "", "", 10);
			//chrDisableReloadToLocation = false;
            link.l1 = "���� ��� �� ���������?";
			link.l1.go = "BS_KS_28_exit";
			chrDisableReloadToLocation = false;
			//BSCourtlyPassions_spawn_podsos();
			
			PChar.quest.BSCourtlyPassions_fleeng.win_condition.l1 = "location";
			PChar.quest.BSCourtlyPassions_fleeng.win_condition.l1.location = "FortFrance_town";
			PChar.quest.BSCourtlyPassions_fleeng.function = "BSCourtlyPassions_fleeng";
		break;
		
		case "BS_KS_28_exit":
			DialogExit();
			LAi_group_SetHearRadius("EnemyFight", 100.0);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "", "", "", 10);
		break;
		
		//����. ��� ������ �������� ��� �������� � ���� �������.  ���� �� �����, ���� ���� ������ � ������ ����. ����� � �� �������� � � �.�. ���� �� �� �����. � ����� ����� ������� � ��� �������, ����� ���� ������. ���� � ������� ����� �� ������ � ����. ������� � ����. ��������� - ������� ����� �������� ����. ������� ���� � �������. ����� ������ ������ � ����� � ������.
		
		case "BS_KS_29":
            dialog.text = "��� ��, ������ ����� �������� ������� �����. �� ������ ��� � �� ������!";
            link.l1 = "����� ������ ���������?";
			link.l1.go = "BS_KS_30";
			
			PChar.quest.BSCourtlyPassions_final.win_condition.l1 = "location";
			PChar.quest.BSCourtlyPassions_final.win_condition.l1.location = "Shore39";
			PChar.quest.BSCourtlyPassions_final.function = "BSCourtlyPassions_final";
			DeleteAttribute(pchar, "BSCourtlyPassionsFail");
		break;
		
		case "BS_KS_30":
            dialog.text = "��-��-��. �� ����������� ���� ����!";
            link.l1 = "�������� � �����. ��� ����� ���� ��������. � ��� ���� ������ �����. ��������� ������? ������ '����' �� ���� ������.";
			link.l1.go = "BS_KS_31";
			//link.l2 = "�� �� ��������, ����, � ���� ��� ������� ������, ����� ��� ������ ���� ������.";
			//link.l2.go = "BITVA";
		break;
		
		case "BS_KS_31":
            dialog.text = "� ���� ���, '� ���'? �� �� � ������� �� ������?";
            link.l1 = "��, � � ���. � ���� � ��� ���������, �� ��� ��������� ���������, ������, ������� �� ����!";
			link.l1.go = "BS_KS_32";
		break;
		
		case "BS_KS_32":
			AddQuestRecord("BSCourtlyPassions", "7");
			sld = CharacterFromID("BS_Vein");
			LAi_SetImmortal(sld, true);
            dialog.text = "�����, � ��������. ������ �� � ���. �� � ������ ������� � ��������� �����, �� �������� � ����� ����� ������. ����� ������� ���������� � ��� ����� ����� ��� ����.";
            link.l1 = "��� � �����. �������� �� ��������. � ���� ��� ���� ������������� ����.";
			link.l1.go = "BS_KS_32exit";
		break;
		
		case "BS_KS_32exit":
            QuestAboardCabinDialogSurrender();
			//SetEnemyToKilled();
            DialogExit();
		break;
		
		//������������ � �������, ��� ���� � �������.
		
		case "BS_KS_33":	//�������
            dialog.text = "�������?";
            link.l1 = "���� �������, ������������.";
			link.l1.go = "BS_KS_34";
		break;
		
		case "BS_KS_34":	//�������
			npchar.LifeDay = 0;
            dialog.text = "� � ��� �� �� ������� �� ����������!";
            link.l1 = "���, ����� ������ �� ������������.";
			link.l1.go = "BS_KS_35exit";
		break;

		
		case "BS_KS_35exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", Get_My_Cabin(), "", "", "", 10);
			sld = CharacterFromID("BS_Maks");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_35";
			DialogExit();
			DoQuestFunctionDelay("MaksSpeech", 0);
		break;
		
		case "BS_KS_35":
            dialog.text = "��� ��� ������?";
            link.l1 = "������� �����.";
			link.l1.go = "BS_KS_36_1";
		break;
		
		case "BS_KS_36_1":
			npchar.LifeDay = 0;
            dialog.text = "������ �� �������� ���� � ���� �����?";
            link.l1 = "� �� ������"+ GetSexPhrase("","�") +". ����� �� ����!";
			link.l1.go = "BS_KS_36_exit";
			PChar.quest.BSCourtlyPassions_finalRoyal.win_condition.l1 = "location";
			PChar.quest.BSCourtlyPassions_finalRoyal.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.BSCourtlyPassions_finalRoyal.function = "BSCourtlyPassions_finalRoyal";
		break;
		
		case "BS_KS_36_exit":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", Get_My_Cabin(), "", "", "", 10);
		break;
		
		case "BS_KS_36":
			chrDisableReloadToLocation = false;
            dialog.text = "��������� ���, �������! ��� ��� ��� ����� ��� �� ���������.";
            link.l1 = "��� �����-�� ������ � ������ ���.";
			link.l1.go = "BS_KS_37";
		break;
		
		case "BS_KS_37":
			npchar.LifeDay = 0;
            dialog.text = "�������, �� ��� ����������?";
            link.l1 = "��� �����? ��������. ������ ����.";
			link.l1.go = "BS_KS_37exit";
		break;
		
		case "BS_KS_37exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload9_back", Get_My_Cabin(), "", "", "", 10);
			CloseQuestHeader("BSCourtlyPassions");
			SetQuestHeader("BSChaseBegun");
			AddQuestRecord("BSChaseBegun", "1");
			
			BSChaseBegun();
		break;
		
		//������� ����� � ��, ��� ������ � �������. ������������ �� �������.
		
		//������ � �� ����� �������, ������ ����� ����������� �� �������.�
		
	}
}
