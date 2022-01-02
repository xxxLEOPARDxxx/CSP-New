
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
		
		case "BS_CPNG_1":	//������
			dialog.text = "��, � �� ���� �� ����������� ���� ������� � �����, ����������� ���� �����?";
			link.l1 = "� ����! ��� �� ���� ���?";
			link.l1.go = "BS_CPNG_2";
		break;
			
		case "BS_CPNG_2":
            dialog.text = "������� �� ����. �� � ��������� ����� ����������� ������ �������� �������� "+pchar.name+", ��� "+ GetSexPhrase("���","�") +" ���� � �������� ������. � �� ����� ����� ��������, � �� �� ���� �������.";
            link.l1 = "������, � �����"+ GetSexPhrase("","�") +".";
			link.l1.go = "exit";
		break;

		//�� ��������, ����� ��������� ������. ����� ��� �� ����� ��������� �����. (���� 5-6 ������� �����)
		
		case "BS_CPNG_3":	//�����
            dialog.text = "������ ����! ����� �����, ����� �� �������� �����! ���� �� ��� ��� ������� �� ����� ���������� ���������� ���������� �� �������, �� � ����� ���� ����� ��� ������!";
            link.l1 = "";
			link.l1.go = "BS_CPNG_4_1";
		break;
		
		case "BS_CPNG_4_1":
            npchar.name = "����";
			npchar.lastname = "";
			NextDiag.CurrentNode = "BS_CPNG_4";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_CPNG_4":	//����		
            dialog.text = "���� �����! ��� ��� ��������, ��� ��� ������� � �...";
            link.l1 = "";
			link.l1.go = "BS_CPNG_5_1";
		break;
		
		case "BS_CPNG_5_1":
            npchar.name = "��������";
			npchar.lastname = "�����";
			NextDiag.CurrentNode = "BS_CPNG_5";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;
		
		case "BS_CPNG_5":	//�����
            dialog.text = "������! ������ �� ������� ��������. ���������� ������������!";
            link.l1 = "";
			link.l1.go = "BS_CPNG_6_1";
		break;
		
		case "BS_CPNG_6_1":
            npchar.name = "����";
			npchar.lastname = "";
			NextDiag.CurrentNode = "BS_CPNG_6";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;
		
		case "BS_CPNG_6":	//����
            dialog.text = "�� �... �� ��� �� �... � ��� � ��������!�";	//������ � ����������
            link.l1 = "";
			link.l1.go = "BS_CPNG_7_1";
		break;
		
		case "BS_CPNG_7_1":
            npchar.name = "��������";
			npchar.lastname = "�����";
			NextDiag.CurrentNode = "BS_CPNG_7";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;
		
		case "BS_CPNG_7":	//�����
            dialog.text = "�, ��� � ��. ��� ��� �������. ���, �������, ��������� �������. ��������� �����.";	//��������� ������
            link.l1 = "";
			link.l1.go = "BS_CPNG_8";
			for (i = 1; i < 4; i++)
			{
				sld = CharacterFromID("Gatri_temp"+i);
				sld.LifeDay = 0;
			}
		break;
		
		case "BS_CPNG_8":	//�����
			chrDisableReloadToLocation = false;
            dialog.text = "���� ����. ��������������, ����� � �������.";	//������� � �������. ������ � ������� �������.
            link.l1 = "�� �����.";
			link.l1.go = "BS_CPNG_9_1";
		break;
		
		case "BS_CPNG_9_1":	//�����
			PChar.quest.Gatri_upstairs.win_condition.l1 = "location";
			PChar.quest.Gatri_upstairs.win_condition.l1.location = "Pirates_tavern_upstairs";
			PChar.quest.Gatri_upstairs.function = "Gatri_upstairs";
			NextDiag.CurrentNode = "BS_CPNG_9";
			DialogExit();
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
            DoReloadCharacterToLocation("Pirates_tavern_upstairs","goto", "goto1");
		break;
		
		case "BS_CPNG_9":	//�����
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
            dialog.text = "������ �����������!";
            link.l1 = "�������. � � ���� ��� ����� �� �������� �����?";
			link.l1.go = "BS_CPNG_10";
		break;
		
		case "BS_CPNG_10":
            dialog.text = "��� ����� ����, ����� ������ ���������� �������� ��� �������. �������� ��� �������. ��������� �� ������?";
			link.l1 = ""+ GetSexPhrase("����","���") +" �� ��������.";
			link.l1.go = "BS_CPNG_11"
		break;
		
		case "BS_CPNG_11":
            dialog.text = "������. � ���� ���� ����. ������ ��� ����. ����� ��� ����... ������� �����. "+ GetSexPhrase("������","�������") +" � �����?";
            link.l1 = "�����. ������ ����. �� ��� ������ ����� ������ ���� � ����.";
			link.l1.go = "BS_CPNG_12";
		break;
		
		case "BS_CPNG_12":
            dialog.text = "���� ������� ������. � ��������� ��� ������ ��������� � ��� ����� �������� � ������������ �������, �� ������������ � ������� ������.\n"+ 
							"��� ���. �� �������� � ��������, ������� ����� ��������� ���� ���������� ��� �������� � ��������. � � ����, ��� �� ������� ����� �� ������� �������� � �������� � ���� �������� ������.";
            link.l1 = "� ������ ��� ���� � ���� ��������?";
			link.l1.go = "BS_CPNG_13";
		break;
		
		case "BS_CPNG_13":
            dialog.text = "����� ��� � ����. �������, ����� ����� � ���� ��� ������ ������ � ������ �������! ����� ���������, ������� ���, ��� �� ���� ����"+ GetSexPhrase("�","��")+" ����� �������. ��� ������. �� ��������� �� ��� ���������.";
            link.l1 = "� ��� ������ ������?";
			link.l1.go = "BS_CPNG_14";
		break;
		
		case "BS_CPNG_14":
            dialog.text = "������ �������. �� ������ � ��������� ����� ������� � �� ���������. ��� ��� � ����.";
            link.l1 = "�� �������.";
			AddQuestRecord("BSOnTheHorizon", "2");
			BSOnTheHorizon_Flint();
			link.l1.go = "exit";
		break;
		
		//����� ������� ��������� �� �������� �������� ������� ���������( ��� ���������� ���������), ������� ��������� ����� ���������� �������.  
		//��� ��������� ������ � �� ��. ��� ����� ������ � ���� � ������ ������.
		//����� �� ������� ������� ������ �����. �������� ������. �������.
		
		case "BS_CPNG_15":	//�����
            dialog.text = "��� ������ ���� �������, �� �������� � ���� �������. �������������.";
            link.l1 = "� "+GetFullName(pchar)+", ���� ����� ������� ��������� ���, ������� �����.";
			link.l1.go = "BS_CPNG_16";
		break;
		
		case "BS_CPNG_16":
            dialog.text = "� ������ � ���� ����� � � �����, �� ����� ������� �� ������� � ���� � �� ����?";
            
			//��� ����� ������.. ����� ������ ����� :)
			MakeRandomLinkOrderThree(link,
			"� ���� �����"+ GetSexPhrase("","�") +" ����� ������� � ������� �����"+ GetSexPhrase("��","��") +" ��������"+ GetSexPhrase("���","���") +" ��� ����� � �����"+ GetSexPhrase("","�") +" ������� ��������� ��������� � ������ ���������������.",
			"BS_CPNG_17_Horosho",
			
			"� ���� �����"+ GetSexPhrase("","�") +" ����� ������� � ������� �����"+ GetSexPhrase("��","��") +" ��������"+ GetSexPhrase("���","���") +" ��� ����� � �����"+ GetSexPhrase("","�") +" ������� ��������� ��������� � ������ ���������������.",
			"BS_CPNG_17_Ploho",
			
			"� ������"+ GetSexPhrase("","�") +", ��� ������������ ������ ����� ������ � ������� ��������. � ��� � �����!",
			"BS_CPNG_17_Ploho"
			);
		break;
		
		case "BS_CPNG_17_Ploho":	
            DeleteAttribute (npchar, "AlwaysFriend");
			npchar.AlwaysEnemy = true;
			dialog.text = "� ����� �� ����, ��� �� ���"+ GetSexPhrase("��","��") +" � ��������� �������� ��� �������.";
            link.l1 = "���... �� ��������.";
			NextDiag.TempNode = "BS_CPNG_17_Ploho_end";
			link.l1.go = "exit";
		break;
		
		case "BS_CPNG_17_Ploho_end":	
            dialog.text = "����������� �������� ��� �������!";
            link.l1 = "������� ��� �������, � ��� �����.";
			NextDiag.TempNode = "BS_CPNG_17_Ploho_end";
			link.l1.go = "exit";
		break;
		
		case "BS_CPNG_17_Horosho":
			PChar.quest.MeetFlintCrew.win_condition.l1 = "location";
			PChar.quest.MeetFlintCrew.win_condition.l1.location = "Pirates_town";
			PChar.quest.MeetFlintCrew.function = "MeetFlintCrew";
            dialog.text = "�� ���� ����� �������� ��� ������ ����. � ����� ���-����� ���� � ���������� �� �������, ��������� ��� � �������.";
			npchar.StopSailing = true;
			AddQuestRecord("BSOnTheHorizon", "3");
            link.l1 = "������, �� �������.";
			NextDiag.TempNode = "BS_CPNG_17_Horosho_end";
			link.l1.go = "exit";
		break;
		
		case "BS_CPNG_17_Horosho_end":
            dialog.text = "������������� �� ���� �������, ������� �� ����� ������ ����� ����������.";
            link.l1 = "�� �����, ����� �.";
			NextDiag.TempNode = "BS_CPNG_17_Horosho_end";
			link.l1.go = "exit";
		break;
		
		//�������. �� ������ �����, �������, ����.
		
		case "BS_CPNG_18":	//�����
			//chrDisableReloadToLocation = false;
            dialog.text = "�����������. ������ �������� ����� ����, ����������� ���� �������.";
			BS_ReplaceTraderWithGatri();
            link.l1 = "���"+ GetSexPhrase("","�") +" �������. � "+GetFullName(pchar)+". ��� � �������?";
			link.l1.go = "BS_CPNG_19";
		break;
		
		case "BS_CPNG_19":
			
            dialog.text = "�����. ������ � �������. � ����� ����� ��������.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_19_exit";	//������� � �����. �����, �����, ��.
		break;
		
		case "BS_CPNG_19_exit":
			NextDiag.CurrentNode = "BS_CPNG_9";
			sld = CharacterFromID("gatri_grunt3");
			sld.LifeDay = 0;
			sld = CharacterFromID("Pirates_trader");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.dialog.currentnode = "BS_CPNG_20";
			sld.talker = 10;
			sld.LifeDay = 0;
			DialogExit();
			ChangeCharacterAddressGroup(npchar, "Pirates_store", "goto", "goto3");
            DoReloadCharacterToLocation("Pirates_store","reload", "reload1_back");
		break;
		
		case "BS_CPNG_20":	//�����
            dialog.text = "������, ��� � ��������� "+ GetSexPhrase("���","�") +" � ����. ��"+ GetSexPhrase("","�") +" �� ������ ��������, "+ GetSexPhrase("���� ������� �����","��� ������� ������") +" �� ����, ���� �� ���� ���������.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_21_1";
		break;
		
		case "BS_CPNG_21_1":
            npchar.name = "������";
			npchar.lastname = "�����";
			NextDiag.CurrentNode = "BS_CPNG_21";
			DialogExit();
			DoQuestFunctionDelay("GatriStoreSpeech", 0);
		break;
		
		case "BS_CPNG_21":	//�����
            dialog.text = "� ���� �����������, �������� �������� � ���������� ������� � ����������� ��������. � ����� ����� ��������, ��������, �� �� ������. �� ��������� �� "+ GetSexPhrase("����","��") +"?";
            link.l1 = "";
			link.l1.go = "BS_CPNG_22_1";
		break;
		
		case "BS_CPNG_22_1":
            npchar.name = "��������";
			npchar.lastname = "�����";
			NextDiag.CurrentNode = "BS_CPNG_22";
			DialogExit();
			DoQuestFunctionDelay("GatriStoreSpeech", 0);
		break;
		
		case "BS_CPNG_22":	//�����
            dialog.text = "� ��� ���� �����������, �� �� �����������. ��, � ������� �� ����� ��������.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_23_1";
		break;
		
		case "BS_CPNG_23_1":
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_23";
			//NPChar.Dialog.Filename = "Common_store.c";
			//NPChar.Dialog.CurrentNode = "Second time";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		case "BS_CPNG_23":	//�����
            dialog.text = "��� ��, ��������� � �������.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_23_exit";	//������� � �������. ������� �������.
		break;
		
		case "BS_CPNG_23_exit":
			PChar.quest.Flint_upstairs.win_condition.l1 = "location";
			PChar.quest.Flint_upstairs.win_condition.l1.location = "Pirates_tavern_upstairs";
			PChar.quest.Flint_upstairs.function = "Flint_upstairs";
			NextDiag.CurrentNode = "BS_CPNG_24";
			DialogExit();
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
            DoReloadCharacterToLocation("Pirates_tavern_upstairs","goto", "goto1");
		break;
		
		case "BS_CPNG_24":	//�����
            dialog.text = "����, ������� "+GetFullName(pchar)+". �� ������� �� '���� �� ����'? ��������� �������� �������, ����������� �� ������� ����, � ������������ ������� �������?";
            link.l1 = "��� ���������, � ������"+ GetSexPhrase("","�") +" ����� �� ���� �������� ��������. �� �������, ���� ������ ����� ������ ����������!";
			link.l1.go = "BS_CPNG_25";
		break;
		
		case "BS_CPNG_25":
			BS_RestoreGatriTrader("q");
            dialog.text = "'���� �� ����' - ��� ����� ������� ������, ��. � � ���� ���� ����������, ��� � ����� ���� ������ ����� ��������� ������ ���� � ��������� ��� ����������� � �������. � ��� ��������� ���� ��������� ���� ����.";
            link.l1 = "������ ���� �������?";
			link.l1.go = "BS_CPNG_26";
		break;
		
		case "BS_CPNG_26":
            dialog.text = "��� ��������� ��������� ����!";
            link.l1 = "������ �����!";
			link.l1.go = "BS_CPNG_27";
		break;
		
		case "BS_CPNG_27":
            dialog.text = "�� � ����? �� ��� ���? ����� � �� ���� ���������, ��� ���������� ��� �������.";
            link.l1 = "������� � � ����! ���, ��� � �����?!";
			link.l1.go = "BS_CPNG_28";
		break;
		
		case "BS_CPNG_28":
			chrDisableReloadToLocation = false;
            dialog.text = "� �� ���� ������� ������� ��������, ���� �� ��� �� ������ �� ��������.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_28_exit";	//���������� ����. �� ������ ���� � �������.
		break;
		
		case "BS_CPNG_28_exit":
			PChar.quest.Silver_Downstairs.win_condition.l1 = "location";
			PChar.quest.Silver_Downstairs.win_condition.l1.location = "Pirates_tavern";
			PChar.quest.Silver_Downstairs.function = "Silver_Downstairs";
			NextDiag.CurrentNode = "BS_CPNG_24";
			DialogExit();
            DoReloadCharacterToLocation("Pirates_tavern","sit", "sit_front4");
			FreeSitLocator("Pirates_tavern", "sit_front4");  // ������� ����
			FreeSitLocator("Pirates_tavern", "sit_front1");  // ������� ����
			FreeSitLocator("Pirates_tavern", "sit_base4");  // ������� ����
			FreeSitLocator("Pirates_tavern", "sit_base1");  // ������� ����
			
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern", "sit", "sit_base4");
			LAi_SetSitType(npchar);
			LAi_SetSitType(pchar);
			sld = CharacterFromID("BS_Billy");
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			sld = CharacterFromID("BS_Silver");
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.dialog.currentnode = "BS_CPNG_29";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "sit", "sit_base1");
			LAi_SetSitType(sld);
			sld = GetCharacter(NPC_GenerateCharacter("Gatri_temp", "BS_Gatry", "woman", "woman", 1, PIRATE, -1, true));
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay1");
			sld.name = "��������";
			sld.lastname = "�����";
		break;
		
		case "BS_CPNG_29":	//�������
            dialog.text = "...";
            link.l1 = "������ �������? � ����� ��������� �������� ������, ����� ����� ���������� �����������!";
			link.l1.go = "BS_CPNG_30";
		break;
		
		case "BS_CPNG_30":
            dialog.text = "����������� �������! ��� ��� �������, ������������ �������?";
            link.l1 = "...";
			link.l1.go = "BS_CPNG_30_flint_1";
		break;
		
		case "BS_CPNG_30_flint_1":
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_30_flint";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		case "BS_CPNG_30_flint":
            dialog.text = "����� ��� �����!";
            link.l1 = "...";
			link.l1.go = "BS_CPNG_31_1";
		break;
		
		case "BS_CPNG_31_1":
			sld = CharacterFromID("BS_Silver");
			sld.dialog.currentnode = "BS_CPNG_31";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;
		
		case "BS_CPNG_31":
            dialog.text = "� �������� ��� �������! � ���� ������ ����� ���� �� �������������� ��������! ��������� � �������� �����.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_32_1";
		break;
		
		case "BS_CPNG_32_1":
			sld = CharacterFromID("Gatri_temp");
			sld.dialog.currentnode = "BS_CPNG_32_gatri";
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.talker = 10;
			DialogExit();
			//DoQuestFunctionDelay("GatriSpeech", 0);
		break;
		
		case "BS_CPNG_32_gatri":
            dialog.text = "������ ����! ���������! ���!!! ����..!!";
            link.l1 = "";
			link.l1.go = "BS_CPNG_32_flint_1";
		break;
		
		case "BS_CPNG_32_flint_1":
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_32_flint";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;
		
		case "BS_CPNG_32_flint":
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//����� �������������� � �������
			Flag_PIRATE();
			BSRepairShip(npchar);
			SetShipRemovable(npchar, false);
			Fantom_SetBalls(npchar, "war");
			SetCharacterGoods(npchar,GOOD_FOOD,1000);
            dialog.text = "��������� ��������. ������ �������, ��� �� �������� � ������ � ��������� ���?";
            link.l1 = "";
			link.l1.go = "BS_CPNG_32_silver_1";
		break;
		
		case "BS_CPNG_32_silver_1":
			sld = CharacterFromID("BS_Silver");
			sld.dialog.currentnode = "BS_CPNG_32_silver";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;
		
		case "BS_CPNG_32_silver":
            dialog.text = "���. � ��� ������, �� �� �� �������. � ������� �� ���������.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_33";
		break;
		
		case "BS_CPNG_33":
			npchar.LifeDay = 0;
			npchar.dialog.currentnode = "BS_CPNG_Final";
			sld = CharacterFromID("BS_Billy");
			sld.dialog.currentnode = "BS_CPNG_Final";
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.LifeDay = 0;
			sld = CharacterFromID("Gatri_temp");
			sld.LifeDay = 0;
			sld.dialog.currentnode = "BS_CPNG_Final";
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_Final";
			
            dialog.text = "";
            link.l1 = "��� ��� �������� ������ �����������! � ����!";
			link.l1.go = "BS_CPNG_33_exit";
			//DoReloadCharacterToLocation("Pirates_tavern","goto", "goto2");
		break;
		
		case "BS_CPNG_33_exit":
			PChar.quest.BSOnTheHorizon_End.win_condition.l1 = "location";
			PChar.quest.BSOnTheHorizon_End.win_condition.l1.location = "Bermudes";
			PChar.quest.BSOnTheHorizon_End.function = "BSOnTheHorizon_End";
			BSOnTheHorizon_SeaBattle();
			AddQuestRecord("BSOnTheHorizon", "4");
			ChangeCharacterAddressGroup(pchar, "Pirates_tavern", "goto", "goto2");
			LAi_SetPlayerType(pchar);
			DialogExit();
		break;
		
		case "BS_CPNG_Final":
			dialog.text = "�� ��� ��������� ���� ������ ����� ���������.";
			NextDiag.TempNode = "BS_CPNG_Final";
            link.l1 = "�������� �� ���������.";
			link.l1.go = "exit";
			if (npchar.id == "Gatri_temp")
			{
				dialog.text = "��������� ��� �����, �������.";
				link.l1 = "���������.";
				link.l1.go = "exit";
			}
			if (npchar.id == "Flint")
			{
				dialog.text = "�� ����� �������.";
				link.l1 = "���������.";
				link.l1.go = "exit";
			}
		break;
		
		//������� � ����. � ������� � ����� �� ������. 
		//�� ��������, �� ������� � ��������� � ���� ���������� �������. 
		//����. (4-6 ���������������). ����� ������ � ����� (��: ��� ������� � ��������� ��������� �� ������� ��������. ���� ��� �����, �����. �� ��.)
		
	}
}
