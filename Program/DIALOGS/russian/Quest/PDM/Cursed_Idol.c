
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
		
		case "First time":								//����� Sinistra
			dialog.text = "����������-�� ��� �����! "+ GetSexPhrase("������� �����","������� �������") +", ���� ����� � �������! ������, ���� ������, � ����� ��� ���! ������, ��� �? � ������ ������! � ������� ��������� ������� ��� ���� � ���� �� ������� ������� ����������� �������! ����� � �� ��������? �� �� ������� ��� ���� ����?";
			link.l1 = "�� ���. � � "+ GetSexPhrase("��� �� ������","���� �� ������") +", � ��� ���� ��������� ���-���� ��������� � ��� �����.";
			link.l1.go = "Vstrecha_2";
			link.l2 = "������ ������, �� ����� ���� � "+ GetSexPhrase("������� � ������","������� � ������") +". ��������, �� � �� "+ GetSexPhrase("���������","���������") +" ��������� ���������� � ���������� �������.";
			link.l2.go = "exit";
			LAi_CharacterPlaySound(NPChar, "GR_Jamescallow_FirstTime");
		break;
		
		case "Vstrecha_2":
            dialog.text = "�������! ������, "+ GetSexPhrase("�����","������") +", ��� "+ GetSexPhrase("����� ����� �������","����� �����") +", ��� ��. � ������� ��������, � ������� �� ������� ����������� ������. �� ����, ��� � � ���� ������, � ����� �����, ��� ��� ��� ��-�� ��� � "+ GetSexPhrase("�����","�����") +". ��� �������, "+ pchar.name +"?";
            link.l1 = "� ��� �� �������� �� ����������, ������?";
			link.l1.go = "Vstrecha_3";
		break;

		case "Vstrecha_3":
            dialog.text = "�� ������ � ����������, "+ GetSexPhrase("��������","�������") +"? ������ � ���� �����, ��� �������� ���������?";
			link.l1 = "� �� ���� � ��� ������. ������ ���� � ������� �������, ��� ���� ����� ����������� � ������������ �����.";
			link.l1.go = "Ne_Veru_1";
            link.l2 = "��� ����������� ������� �������� � ����� � �����������. (����� �� ����)";
			link.l2.go = "Vstrecha_4";
		break;
		
		case "Ne_Veru_1":
            dialog.text = "�� ������� �����"+ GetSexPhrase("","�") +", ����� �������� �������� ����, "+ GetSexPhrase("�����","�������") +". ���� �� �������� ���������� �����, ����� �� �� �����"+ GetSexPhrase("","�") +", ��� ������ �������, ������� ������������ � ��������, ��� �� ������ ������� � �����������. � ��������� ������� ��� ������ ���� ������� ����������.";
			link.l1 = "������, ������, ��� � ���� � ������� �� �� � �������, ������. ����� � ������� ���� �����. ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "VstrechNetAgain_1";
			npchar.lifeday = 0;
		break;
		
		case "Vstrecha_4":
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "sit", "sit_front3");
			LAi_SetSitType(pchar);
			LAi_SetSitType(npchar);
			locCameraTarget(PChar)
            locCameraFollow();
            dialog.text = "��� �, � � ����� ����: ��� ��� ������� - ������ ������. ���� ����, ������� � ����� ����� �� ���� ���������. � ����� ���� ���������, � ����� ����������, ��� ��� ��������!";
            link.l1 = "������? � ��� ���������� ���� ������ � ���? �� ������ �������� ����� ����? ��� ��� ��������� �������� ���� �� ����� � ������� � ����������� ������������?";
			link.l1.go = "Vstrecha_5";
		break;
		
		case "Vstrecha_5":
            dialog.text = "��� �� ����� ��� �������, "+ pchar.name +". � ��� ���, ��� � �������� ����� ���������� �����, ����� ���� ��������. ������� � ����� � ����� ���������� �� ����. ����� � ���� �� ������� ��������� ������. � ������, ��� � ����� � �����? �����. ������ �����. �� ������, �� �������, ������ ��� ��������� �����! ������ ����� ������!";
            link.l1 = "��! ��������� ����. � ��� �����?";
			link.l1.go = "Vstrecha_6";
		break;
		
		case "Vstrecha_6":
            dialog.text = "��� ����� ������� �� ������, ��������� ������� �� ��������, ������� ��� ������� � ��������� ��������� ���� � ����. ��� ���� ��� ��� ��������� ���� �� ���� �����, �� ��� ������� ��� ������ �������� � �����. � ���������� �� �������, ����� ��������������� �����, �� ������� ��-�������� ������������ ����.\n"+ 
							"� ����������� ��������� ��������� ������ �������� �� ��������� ��� �����, � ��� �������� ������ �� �� ������ �������� �����, ����� �������� ���� �������. ������ ����� � �����, ��� ���� �������� ���� ���� ������.";
            link.l1 = "� ��� �� ���?";
			link.l1.go = "Vstrecha_7";
		break;
		
		case "Vstrecha_7":
            dialog.text = "����� ����� � �������� ������� ������� �������. �� ����� ������ ���� �� ��������� �� ����� ��������� ��������. ��� ������ ��������� ��-�� ��������. �� �������� ���-�� ������ ����������� �������� ������������������ � �����, ������� �� ���� ������������ ���������. �������, �� ���������� ���� ��������� ������.\n"+ 
							"����� � ������, ��� ������ ������� �� ������� ������ � �������� ������� ���������, � ������ � �� ��� �������.\n"+  
							"���, � �� ��� ����, ��� �� �������... � ��� ��� ������ ��������� �����. �� �� �� �� ����. �� ������, ��� ���� ����� ���� ������ �������. ����� �� ������, ��� ����� ��� ����� '������ �� ���� � ��� ������' � � ��� ����� �����.\n"+ 
							"������ ������, ��� ��� �� ��� ��� ������� �������� ����� �����, �� �� ������ ���� ��������, � � ������� �� ����� ���������� �� ����. � ���������� ��� � ���� � ������� ��� ������. � �� ����� �� ����, �� �����, �� ������ � �������, "+ GetSexPhrase("��������","�������") +".";
            link.l1 = "��, ���������� ����� ������ ��������? �� �������? �����, �������� �������� ��� ������! ��! ������ ����� ��� ����� � ����!";
			link.l1.go = "Vstrecha_8";
		break;
		
		case "Vstrecha_8":
            dialog.text = "��������, "+ GetSexPhrase("��������","�������") +". � ������� ������� ���. � ������� �������� ���. ������ �� �������. ��������� ���� ������������ � ��� �����, ��� �����, ��� ���� - ������������ �� ���, ��� �� � �� ���. ׸����� ��������� ���������� ����! ��� �����-�� ���������! �� ��������, ��� �� ������ � ��������� - ��� ����� �� �������� ���?";
            link.l1 = "����... ����� ����. � ������ �� ���� ������ �� ������ � ����-������? ������ �������, ���� ����� ���� ������ �������.";
			link.l1.go = "Vstrecha_9";
		break;
		
		case "Vstrecha_9":
            dialog.text = "������ ��� � �� ���� ������ ���! � ���� ��� �������� ������, ��... ���� ��������� ����� �����-�� �������... �� ������ ��� ��������... � ������... �� ����. � �����, ��� ����� ���� ������� ���������. � �� ���� ������ ���! �������� � ���, ��� � ����� ����� ���� � �� ������ �������... ��� ������... ������������! ��� �������, � ������ ��������, ���� ������ ���. �� � ���� ���� ����...";
            link.l1 = "��� �� ����?";
			link.l1.go = "Vstrecha_10"
		break;
		
		case "Vstrecha_10":
            dialog.text = "� ���� ��������, ������� ������� �������� ����� �����, ���� �� ������ ���. ��� ��� ����� ������� ����. � ���, ������� ��, �� ����� ������������� �����! ���� � ���� �����, ��� ��� ����� � ����� � ��������, ��� ����� ���������� ������� � ���� �����. �� � �� ���� ������� ��� ���. ������� ������� ������ ���� �����. �� ����������, ��� �� ������ �� ����������, ���� ������� ����� �������� �� ����.";
            link.l1 = "� ��� � �� ��� ������?";
			link.l1.go = "Vstrecha_11";
		break;
		
		case "Vstrecha_11":
            dialog.text = "��� �������������. � � ���� ������������ ���� �� ���� ����� ������������... �� ������� ����, ��������� �����. ����, ���� �� ����"+ GetSexPhrase("��","��") +" ������ �����, ����� ���������� �������, �� ������� ��������� �� �������, ��� �� ���������. �� �������� ���, "+ GetSexPhrase("��������","�������") +"?";
            link.l1 = "���, ��� ����� ������ ������ �������.";
			link.l1.go = "VstrechaNet_1";
			link.l2 = "��. � ������ ����.";
			link.l2.go = "VstrechaDa_1";
		break;
		
		case "VstrechaDa_1":
            dialog.text = "������� ����, "+ GetSexPhrase("����","������") +". ���, ������ ����� �����, �� ��� ���, �, ��������, � ����� �� ��� �������� �������� ��� ����� �������� �����, ���������� ��������. ����... �������, ��� ��������� � ������ � �� ����� ����� � ���� ��� ��������. ������� ������ ��� ��������, ����� - ��� �����? - ����� �� ����� ��������� ���� � ����.";
            link.l1 = "�� �������, ����.";
			link.l1.go = "CodDa_1";
			GiveItem2Character(PChar, "Cursed_idol");
			PlaySound("Interface\important_item.wav");
			Log_info("������ ����� ��� �����");
			NextDiag.TempNode = "VstrechDaAgain_1";
		break;
		
		case "VstrechaNet_1":
			dialog.text = "� ����� ������, ���� �� �������"+ GetSexPhrase("","�") +". ����� ���� ��� ���������� ������, � ���� - �������!";
            link.l1 = "��� ���� ��. �����, �� ������. � ������, ���������� ���������� � ���� ��������� �����. �� ��������.";
			link.l1.go = "CodNet_1";
			NextDiag.TempNode = "VstrechNetAgain_1";
			npchar.lifeday = 0;
		break;
		
		case "CodDa_1":
            ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "tables", "stay1");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();
			SetQuestHeader("PDM_Cursed_Idol");
			AddQuestRecord("PDM_Cursed_Idol", "1");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("PDM_Cursed_Idol", "sSex1", GetSexPhrase("��","��"));
			
			sld = CharacterFromID("LeFransua_Mayor")   //��������� �� ���������
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "none", "");
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_LeFransua_Mayor_Klon", "huber_fra", "man", "man", 30, PIRATE, -1, false));   //��������� �� �����
			sld.name	= "����������";
			sld.lastname	= "�������";
			sld.nation = PIRATE;
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetImmortal(sld, true);
			GiveItem2Character(sld, GUN_COMMON);
			GiveItem2Character(sld, BLADE_LONG);
			LAi_SetHuberType(sld);
			SetRandSPECIAL(sld);
			SetSelfSkill(sld, 90, 90, 90, 60, 70);
			sld.standUp = true; //�������� � �������� �� �����
			ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "sit", "sit1");			
			sld.Dialog.Filename = "Quest/PDM/Cursed_Idol.c";
			sld.dialog.currentnode = "Rodjer_1";
			pchar.questTemp.PDM_PI_Skelety_v_more = "PDM_PI_Skelety_v_more";
			SetTimerFunction("PDM_PI_Skelety_v_more", 0, 0, 5);
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CodNet_1":
            ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "tables", "stay1");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "VstrechDaAgain_1":
			dialog.text = "�����! ������ �� ����� ������� �����? ������ ����� ��������, ���� �� �� ����� ���� ���������. � �� ���� ����� �������� ����� ������.";
            link.l1 = "�� ��������, ����. ���� ��������� ������� ����� ����� ����� � ��������.";
			link.l1.go = "exit";
		break;
		
		case "VstrechNetAgain_1":
			dialog.text = "�����! ��� ��! �������� ������, ���� � �� ������� ���� ������!";
            link.l1 = "��������, ��������, ������. �� ������ ��� ���� �������� �� ����������.";
			link.l1.go = "exit";
		break;
		
		case "Rodjer_1":
			dialog.text = "��! �� �� ���� ����������, "+ GetSexPhrase("���������","��������") +", ��� ��� ���������� �����, �� �� ��������� ������. �� ���� �����"+ GetSexPhrase("","�") +"?";
            link.l1 = "�������� ���� �����, �������. � ����, ��� � ��������.";
			link.l1.go = "Rodjer_2";
			LAi_CharacterPlaySound(NPChar, "GR_Prikusi_Yazik");
		break;
		
		case "Rodjer_2":
			dialog.text = "���������, �� ������� �� ����. ��� ���� �����, �������?";
            link.l1 = "� ���� ���� ��� ���� �������.";
			link.l1.go = "Rodjer_3";
		break;
		
		case "Rodjer_3":
			dialog.text = "�������? ������-�� ��� ���.";
            link.l1 = "��� ��������� ����. ���, �������. ����� ����������, ������?";
			link.l1.go = "Rodjer_4";
		break;
		
		case "Rodjer_4":
			dialog.text = "��� ���� ������?";
            link.l1 = "�����. � ������ �����"+ GetSexPhrase("","�") +" ������� ������� ����, �� ��� ���� � �� �������.";
			link.l1.go = "RodjerDa_1";
			link.l2 = "���� ������ ����. �� ����� ���������� ���� ���� ��������.";
			link.l2.go = "RodjerPodozren_1";
		break;
		
		case "RodjerPodozren_1":
			dialog.text = "� �� ���� ����, "+ GetSexPhrase("������","��������") +". � ���� ��� ������, ������� ����� �������� ��� �������. �� ���� � ���� ���� ������, ������� ������ �������� ��� ���-������ �������. ��� �� ��-���� �����������, ��� ��� ������� ��� �� ������� �����?";
            link.l1 = "��, ������, ��� ��� ������.";
			link.l1.go = "RodjerPodozren_2";
			link.l2 = "���... �� � ����, ����� �� ���� ��� ����������.";
			link.l2.go = "RodjerDa_2";
		break;
		
		case "RodjerPodozren_2":
			dialog.text = "�� "+ GetSexPhrase("�������","��������") +", "+ GetSexPhrase("�������","�������") +". �������� ������ � �������� � ����� ���� ���������. ������ ������ ��� ������ � �������. ����������� �� ���, ����� ��������� ������������� � ���������, �������� ���� ����� � ���� ������.";
            link.l1 = "...";
			link.l1.go = "RodjerCod_2";
			NextDiag.TempNode = "RodjerPokapoka_1";
			ChangeCharacterReputation(pchar, -4);
		break;
		
		case "RodjerDa_1":
			dialog.text = "��! �� �������"+ GetSexPhrase("","�") +", ��� ��������� ���� ������ ����������. � �� �����"+ GetSexPhrase("","�") +" ������������� �� ��� � ������� ����� �������... ��� ��� ��������!";
            link.l1 = "��! �� ��������� ������� ��� �����. �� ����������� �� �� ������� �� ���� ���?";
			link.l1.go = "RodjerDa_2";
		break;
		
		case "RodjerDa_2":
			dialog.text = "����� ����... ������! ����� �������� �����! ��, ��� ��� �� �����! ��� �� ������ � ����� �� ���� �������? ������, � � ������ ���! �� ������ ��� �������, ������� ��� �������.";
			//link.l1 = "� ����, ��� ������ ����� ��������� ����� ����������� �������. � ���� ������� ���� �� ���, � ��� ����� ��� ����������. ������, �����, ����������, ����� �� ��� ��������� � ��������� ���������?";
			//link.l1.go = "RodjerVar_1";
			link.l1 = "��� ������ �� �����.";
			link.l1.go = "RodjerVar_2";
			Log_info("�� ������ ����� ��������");
			TakeItemFromCharacter(pchar, "Cursed_idol");
		break;
		
		/*case "RodjerVar_1":
			dialog.text = "� ���������, "+ GetSexPhrase("������","��������") +", ��� ������ ���� ����������. �� � ������ ���� ����������. ������, �� ��������.";
			link.l1 = "�-�... �� �������.";
			link.l1.go = "RodjerCod_1";
			NextDiag.TempNode = "RodjerPokapoka_1";
			ChangeCharacterReputation(pchar, -2);
		break;*/
		
		case "RodjerVar_2":
			dialog.text = "� �� ���� ����, "+ GetSexPhrase("������","��������") +". �������� ������� �� �������� ������ ���... ������� ��� ������� � �������� ������. �� ������� "+ GetSexPhrase("����","�����") +", ����� �������� ����. ����������!";
			link.l1 = "��...";
			link.l1.go = "RodjerCod_2";
			GiveItem2Character(PChar, "Cursed_idol");
			Log_info("������� ������ ��� �����");
			NextDiag.TempNode = "RodjerPokapoka_1";
			ChangeCharacterReputation(pchar, 4);
		break;
		
		case "RodjerPokapoka_1":
			dialog.text = "��� ���� �����?";
			link.l1 = "������, � �����";
			link.l1.go = "exit";
			NextDiag.TempNode = "RodjerPokapoka_1";
		break;
		
		/*case "RodjerCod_1":
			Pchar.quest.PDM_Callow_RodjerFin.win_condition.l1           = "Location";
        	Pchar.quest.PDM_Callow_RodjerFin.win_condition.l1.location  = "LaVega_Tavern";
        	Pchar.quest.PDM_Callow_RodjerFin.win_condition              = "PDM_Callow_RodjerFin";
			Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition.l1           = "ExitFromLocation";
        	Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition.l1.location  = PChar.location;
        	Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition              = "PDM_Callow_RodjerVozvrat";
			AddQuestRecord("PDM_Cursed_Idol", "2");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("","�"));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;*/
		
		case "RodjerCod_2":
			Pchar.quest.PDM_Callow_RodjerProdolg.win_condition.l1           = "Location";
			Pchar.quest.PDM_Callow_RodjerProdolg.win_condition.l1.location  = "LeFransua_ExitTown";
			pchar.quest.PDM_Callow_RodjerProdolg.function = "PDM_Callow_RodjerProdolg";
			Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition.l1           = "ExitFromLocation";
			Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition.l1.location  = PChar.location;
			Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition              = "PDM_Callow_RodjerVozvrat";
			AddQuestRecord("PDM_Cursed_Idol", "4");
			AddQuestUserData("PDM_Cursed_Idol", "sSex1", GetSexPhrase("��","��"));
			bDisableFastReload = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("Pablo_Loco_Idol", "indsar1", "man", "man", 10, PIRATE, -1, false));
			sld.name = "�����";
			sld.lastname = "����";
			sld.talker = 7;
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetStayType(sld);
			sld.dialog.filename   = "Quest/PDM/Cursed_Idol.c";
			sld.dialog.currentnode   = "Pablo_Loco_Idol";
			ChangeCharacterAddressGroup(sld,"LeFransua_town","goto","goto10");
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Pablo_Loco_Idol":
			dialog.text = "� �������� � ���� ���� �����...";
			link.l1 = "� ����� �� ��� ���. ��� �� ��� ��� ���������. (�������� ����)";
			link.l1.go = "Pablo_Loco_Idol_2";
		break;
		
		case "Pablo_Loco_Idol_2":
			dialog.text = "������� ���! �������! ������� �� ������ ��� ����, �������! ��� ����������������, ���, ������� ���� �� ����� - ��� ������� ��� ����! ������� �� ������� �! ���� ������������������ �����, ��� ��� ��������� ����. ��, ��������� ����� �� ������ ����� �� �����, ��������� � ���� ����. �������� �� ���� ���� ����, ���� �� �� ���� ����!";
			link.l1 = "������ �����... �� ��� � ����"+ GetSexPhrase("","��") +".";
			link.l1.go = "Pablo_Loco_Idol_3";
			npchar.lifeday = 0;
		break;
		
		case "Pablo_Loco_Idol_3":
			sld = CharacterFromID("Pablo_Loco_Idol")
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload5", "none", "", "", "", -1);
		
			DialogExit();
		break;
		
		case "FraOff_1":
			dialog.text = "�� ����� ����������� � ������� �����. ��������, ����� ��� ���� �������� �������� ��������.";
			link.l1 = "�� �������� ������, ������.";
			link.l1.go = "FraOff_Bitva_1";
		break;
		
		case "FraOff_Bitva_1":
			LAi_LocationFightDisable(loadedLocation, false); //��������� ������
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("PDM_Pinki_Skelet")
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			int j;
			j = (GetOfficersQuantity(Pchar) + 1) * 2 + 1;
			for (i=1; i<=j; i++)
				{
				sld = CharacterFromID("PDM_PI_skel_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");	
				}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);		//�����������
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PDM_FraOff_Bitva_1_Posle");
			DialogExit();
		break;
		
		/*case "CollowRad_1":
			dialog.text = "��! �������-�� �� ������"+ GetSexPhrase("��","���") +". ��� ���� ����? �� �� ������"+ GetSexPhrase("","�") +"?";
			link.l1 = "�������. ������ �������� ��� ���� ������ ������� ��������� ������� ������.";
			link.l1.go = "CollowRad_2";
			LAi_CharacterPlaySound(NPChar, "GR_Jamescallow_FirstTime");
		break;
		
		case "CollowRad_2":
			dialog.text = "�����! ����� ����������! �� � ����������� ���� �� ������, ����� ������ ������ ��� ���� ��� ����.";
			link.l1 = "������ �� �������� �� ��� �������. ��, � ���������, ��� �� ������ ����� ���� ��������... ��� ������ �����?";
			link.l1.go = "CollowRad_3";
		break;
		
		case "CollowRad_3":
			dialog.text = "������� �� �����... � ������ ����, ����� ������� ���� ������ ���. ����� ����, "+ GetSexPhrase("����","������") +", �� � �� ��������� ����������� ����� ��������. ������ ���� 10000 ��������, � ������ �� ���� ������...  � �������, �� ���� ������ ������� ������������� ��������. ������, "+ GetSexPhrase("����","������") +".";
			link.l1 = "������-�� ���� ��� �� ��������. �� ��� �� - ��������� ���� �����, ������.";
			link.l1.go = "CollowRadCod_1";
			NextDiag.TempNode = "CollowRadPoka_1";
			AddMoneyToCharacter(pchar, 10000);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			AddCharacterExpToSkill(pchar, "Sneak", 40);
		break;
		
		case "CollowRadPoka_1":
			dialog.text = "��� ��� �������, "+ GetSexPhrase("����","������") +".";
			link.l1 = "�� �������, ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CollowRadPoka_1";
		break;
		
		case "CollowRadCod_1":
			Pchar.quest.PDM_Callow_RadPoka.win_condition.l1           = "ExitFromLocation";
        	Pchar.quest.PDM_Callow_RadPoka.win_condition.l1.location  = "LaVega_Tavern";
        	Pchar.quest.PDM_Callow_RadPoka.win_condition              = "PDM_Callow_RadPoka";
			AddQuestRecord("PDM_Cursed_Idol", "3");
			CloseQuestHeader("PDM_Cursed_Idol");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;*/
		
		case "CollowNeRad_1":
			dialog.text = "��! �������-�� �� "+ GetSexPhrase("��������","���������") +". ��� ����? �� ������"+ GetSexPhrase("","�") +" ���?";
			link.l1 = "� ���� ��� ���� ������ �������. ������� ��������� ����� �����.";
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "sit", "sit_front3");
			LAi_SetSitType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();
			LAi_CharacterPlaySound(NPChar, "GR_Jamescallow_FirstTime");
			link.l1.go = "CollowNeRad_2";
		break;
		
		case "CollowNeRad_2":
			dialog.text = "������! ������ ��� �������! ������ �� ��������� ����� ���? � ����, ��� �� ������� �������� ��� ���� "+ GetSexPhrase("������ ����������","����� ����") +", ��� ��! �� ��� ��-�� ����� ��������, "+ GetSexPhrase("������","������") +"!";
			link.l1 = "� �� ��������� ������� �����������, ������. � � �� �������� � ���������� �����.";
			link.l1.go = "CollowNeRad_3";
		break;
		
		case "CollowNeRad_3":
			dialog.text = "�����! �� ����"+ GetSexPhrase("","�") +". ��� �� ������ ����������� ������? � ��� ��������� ���� ����� �� ������. ��� ���� �� ������� ����� ����-������ �������?";
			link.l1 = "������� ����... �� ���� �� ������� � �������� ������?";
			link.l1.go = "CollowNeRad_4";
		break;
		
		case "CollowNeRad_4":
			dialog.text = "���� �������, ��� ��������� �� ������� � ��� ������ �� ������ � ����������� ������... �����, ��� ���������� ���� ������? ��� �� �������?";
			//link.l1 = "���, � ���� ���� ������� - �� ������ ��������� ������ �������� ����� � ���������� ���� � �����. ���� ��� ������ �� ���� ������!";
			//link.l1.go = "CollowOchenNeRad_1";
			link.l1 = "�������! ������ �������� ��� ��� ��������� ���������.";
			link.l1.go = "CollowNeRad_5";
		break;
		
		case "CollowNeRad_5":
			dialog.text = "���� ������� ����� ���������� � � ���... �������, �� ����� �����, ��� �������. �����, ��� �� ��������� ��������.";
			link.l1 = "�� ��������, �� ���� ��� �� ����� ������. ������� � ��� ��� ������� ������, � ������ ����� �������� � ��� � ����. ����� ������ ������� ���. ����� ����� �� ����� ����� �� ����� ������";
			link.l1.go = "CollowNeRad_6";
		break;
		
		case "CollowNeRad_6":
			if (CheckCharacterItem(Pchar, "patent_fra"))
			{
				dialog.text = "������ ��� ��� ��� � ��������������. �� ���� "+ GetSexPhrase("���������","���������") +". ���� ���-������ ����� �� ���, ���� ������� ����������� ����� ����� ������, ����� ��������� ������.";
				link.l1 = "� �������, �� ����� �� �����.";
				link.l1.go = "CollowNeRad_7";
			}
			else
			{
				dialog.text = "������ ��� ��� ��� � ��������������. �� ���� "+ GetSexPhrase("���������","���������") +". ���� ���-������ ����� �� ���, ���� ������� ����������� ����� ����� ������, ����� ��������� ������.";
				link.l1 = "� ���������� �� ����. � ���� ������� ����� ������ ��� ���� ����������, ��� ���� �� � ������ �� ���.";
				link.l1.go = "CollowNeRad_7";
			}
		break;
		
		case "CollowNeRad_7":
			dialog.text = "����� ������, "+ GetSexPhrase("����","������") +". ����� ����.";
			link.l1 = "�� �������, ����. � ����� �������.";
			link.l1.go = "CollowNeRad_8";
			NextDiag.TempNode = "VstrechEsheAgain_2";
		break;
		
		case "CollowNeRad_8":
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "tables", "stay1");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();
			
			pchar.questTemp.PDM_PI_Rostov = "PDM_PI_Rostov";
			
			AddQuestRecord("PDM_Cursed_Idol", "8");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("���","����"));
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		/*case "CollowOchenNeRad_1":
			dialog.text = "���? �� ��� ������"+ GetSexPhrase("","�") +", "+ GetSexPhrase("��������","��������") +"? � ��-�� �������! �������, � ������!";
			link.l1 = "����� �� ����� ������. � ���� �������� ��������, ��� ��� �� �� ������. �� ��������� ������ �������� ����� � ���������� ���� � �����! ��� ���� ���������. ������� ���. � ������ ����!";
			link.l1.go = "CollowOchenNeRad_2";
		break;
		
		case "CollowOchenNeRad_2":
			dialog.text = "�� ������� ������� ������, "+ GetSexPhrase("������","������") +"! ����� ����� �� ����� ����������! ����� �����! ��, "+ GetSexPhrase("��������� ��������� �����","��������� ��������� ����") +"!";
			link.l1 = "� ���� ����� ����� ��������� �������. ������"+ GetSexPhrase("","�") +", ��� �� ������� �� ��... ���� ����� ���� �� �������. ��-��-��-��!";
			link.l1.go = "CollowOchenNeRad_3";
			Log_info("�� ������ ����� �������");
			TakeItemFromCharacter(pchar, "Cursed_idol");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
			AddCharacterExpToSkill(pchar, "Sneak", -150); 
			ChangeCharacterReputation(pchar, 5);
		break;
		
		case "CollowOchenNeRad_3":
			dialog.text = "...";
			link.l1 = "(�������� ���)";
			link.l1.go = "CollowOchenNeRad_4";
			sld = CharacterFromID("James_Callow")
			LAi_SetActorType(npchar);   //������ ��� ������
			ChangeCharacterAddressGroup(npchar, "LaVega_tavern", "tables", "stay1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3);  // ��� � ����������� �������.
		break;
		
		case "CollowOchenNeRad_4":
			AddQuestRecord("PDM_Cursed_Idol", "5");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("���","����"));
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "tables", "stay1");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
			locCameraFollow();
			ChangeCharacterAddressGroup(sld, "LaVega_town", "none", "");
			pchar.quest.PDM_Callow_Voina.win_condition.l1 = "location";
			pchar.quest.PDM_Callow_Voina.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PDM_Callow_Voina.function = "PDM_Callow_Voina";
			DialogExit();
		break;*/
		
		case "VstrechEsheAgain_2":
			dialog.text = "�����! ������ �� ����� ������� �����? ������ ����� ���������� �� �������, ���� �� �� ����� ���� ���������. � �� ���� ����� �������� ����� ������.";
            link.l1 = "�� ��������, ����. ���� ��������� ������� ����� ����� ����� �� �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "VstrechEsheAgain_2";
		break;
		
		case "Rostovshik_Fra_Off_1":
			dialog.text = "����� �������, � ��� ��������� �� ��� �� �����, ��� ��� �����!";
			link.l1 = "";
			link.l1.go = "Rostovshik_Fra_Off_1a";
		break;
		
		case "Rostovshik_Fra_Off_1a":
			DialogExit();
			StartInstantDialog("Tortuga_usurer", "Rostovshik_Fra_Off_1b", "Quest/PDM/Cursed_Idol.c");
		break;
		
		case "Rostovshik_Fra_Off_1b":
			dialog.text = "� �� �����, �� ��������� ������ ����� ������. ����� �������!";
            link.l1 = "��, ���� ���� ���� �� ��������.";
			link.l1.go = "Rostovshik_Fra_Off_1�";
		break;
		
		case "Rostovshik_Fra_Off_1�":
			DialogExit();
			StartInstantDialog("PDM_PI_Bandit_1", "Rostovshik_Fra_Off_1_1", "Quest/PDM/Cursed_Idol.c");
		break;
		
		case "Rostovshik_Fra_Off_1_1":
			dialog.text = "������! ����� �� �����. ���� �� �� ����������� ������ ��������, �� �� ��� ������ ����. ��, ������, ���� ����.";
            link.l1 = "��� �� ��� ���������!";
			link.l1.go = "Rostovshik_Mochilovo_1";
		break;
		
		case "Rostovshik_Fra_Off_2":
			dialog.text = "������, �� ����������! � ����� ������ ��������� �������� ���������� ������������. �� ��� �� ����� ��������� ���, ������... �� 45000 �������. ��-��.";
			link.l1 = "�� ���, � �������?";
			link.l1.go = "Rostovshik_Fra_Off_2_2";
		break;
		
		case "Rostovshik_Fra_Off_2_2":
			DialogExit();
			StartInstantDialog("Tortuga_usurer", "Rostovshik_Fra_Off_2_3", "Quest/PDM/Cursed_Idol.c");
		break;
		
		case "Rostovshik_Fra_Off_2_3":
			dialog.text = "";
			link.l1 = "�� ��� � ������ ����� �� ������, ����� ���������.";
			link.l1.go = "Rostovshik_Fra_Off_2_4";
		break;
		
		case "Rostovshik_Fra_Off_2_4":
			dialog.text = "�� ���� �� �� ������, ��������� ���!";
			link.l1 = "";
			link.l1.go = "Rostovshik_Fra_Off_2_5";
		break;
		
		case "Rostovshik_Fra_Off_2_5":
			DialogExit();
			StartInstantDialog("PDM_PI_Bandit_1", "Rostovshik_Fra_Off_2_6", "Quest/PDM/Cursed_Idol.c");
		break;
		
		case "Rostovshik_Fra_Off_2_6":
			dialog.text = "������! ����� ���!";
			link.l1 = "�� ��, ���������. ��� ���������� ����?";
			link.l1.go = "Rostovshik_Mochilovo_2";
			
			sld = characterFromID("Tortuga_usurer");
			sld.Dialog.Filename = "Usurer_dialog.c";
		break;
		
		case "Rostovshik_Fra_Off_3":
			dialog.text = "� �� ���� ����������.";
			link.l1 = "������???";
			link.l1.go = "Rostovshik_Fra_Off_3_1";
		break;
		
		case "Rostovshik_Fra_Off_3_1":
			sld = characterFromID("Tortuga_usurer");
			ChangeCharacterAddressGroup(sld, "Tortuga_Town", "none", "");

			sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Skel_Rostov", "skel_2", "skeleton", "skeleton", 10, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, sti(pchar.rank), 15 + MOD_SKILL_ENEMY_RATE * 4, 15 + MOD_SKILL_ENEMY_RATE * 4, "blade10", "pistol1", 0);
			sld.name = "���������";
			sld.lastname = "";
			ChangeCharacterAddressGroup(sld, "Tortuga_Bank", "barmen", "stay");
			
			DialogExit();
			StartInstantDialog("PDM_PI_Skel_Rostov", "Rostovshik_Fra_Off_3_2", "Quest/PDM/Cursed_Idol.c");
		break;
		
		case "Rostovshik_Fra_Off_3_2":
			dialog.text = "�� ���������� ����� �� �������.";
			link.l1 = "�����!!!";
			link.l1.go = "Rostovshik_Mochilovo_3";
		break;
		
		case "Rostovshik_Mochilovo_1":
			LAi_LocationFightDisable(loadedLocation, false); //��������� ������
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("PDM_PI_Bandit_1")
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sTemp = "pirate_"+(rand(24)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandity_"+i, sTemp, "man", "man", 10, PIRATE, -1, true));
				FantomMakeCoolFighter(sld, sti(pchar.rank), 15 + MOD_SKILL_ENEMY_RATE * 2, 15 + MOD_SKILL_ENEMY_RATE * 2, "blade7", "", 0 + MOD_SKILL_ENEMY_RATE * 2);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);		//�����������
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PDM_Callow_poradomoy");
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, true);
			DialogExit();
		break;
		
		case "Rostovshik_Mochilovo_2":
			LAi_LocationFightDisable(loadedLocation, false); //��������� ������
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("PDM_PI_Bandit_1")
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sTemp = "sold_fra_"+(rand(7)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandity_"+i, sTemp, "man", "man", 10, PIRATE, -1, true));
				FantomMakeCoolFighter(sld, sti(pchar.rank), 15 + MOD_SKILL_ENEMY_RATE * 2, 15 + MOD_SKILL_ENEMY_RATE * 2, "blade7", "", 0 + MOD_SKILL_ENEMY_RATE * 2);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);		//�����������
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PDM_Callow_poradomoy");
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, true);
			DialogExit();
		break;
		
		case "Rostovshik_Mochilovo_3":
			LAi_LocationFightDisable(loadedLocation, false); //��������� ������
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("PDM_PI_Bandit_1")
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PDM_PI_Skel_Rostov")
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);		//�����������
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PDM_Callow_poradomoy");
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, true);
			DialogExit();
		break;
		
		case "Callow_POBEDA_1":
			dialog.text = "��! �������-�� �� "+ GetSexPhrase("��������","���������") +". ��� ����? �� ��� ������"+ GetSexPhrase("","�") +"?";
            link.l1 = "�� ���� ��� �� ������ ������. ��������� ���� �����.";
			link.l1.go = "Callow_POBEDA_2";
			LAi_CharacterPlaySound(NPChar, "GR_Jamescallow_FirstTime");
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "sit", "sit_front3");
			LAi_SetSitType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();
		break;
		
		case "Callow_POBEDA_2":
			dialog.text = "�����! ����� ����������! �� � ����������� ���� �� ������, ����� ������ ������ ��� ���� ��� ����.";
            link.l1 = "������ �� �������� �� ��� �������. ��, � ���������, ��� �� ������ ����� ���� ��������... ��� ������ �����?";
			link.l1.go = "Callow_POBEDA_3";
			AddCharacterExpToSkill(pchar, "Leadership", 50);   	//�������� ���� � ����������
			AddCharacterExpToSkill(pchar, "FencingLight", 50);     //�������� ���� � ������ ������
			AddCharacterExpToSkill(pchar, "FencingHeavy", 50);     //�������� ���� � ������� ������
			AddCharacterExpToSkill(pchar, "Fencing", 50);    	    //�������� ���� � �������� ������
			AddCharacterExpToSkill(pchar, "Pistol", 50);			//�������� ���� � ����������
			AddCharacterExpToSkill(pchar, "Fortune", 50);			//�������� ���� � �����
			AddCharacterExpToSkill(pchar, "Sneak", 50);     	    //�������� ���� � ����������
			sld = CharacterFromID("Tortuga_usurer")   //���������� ����������, ���� �� �������� �����
			ChangeCharacterAddressGroup(sld, "Tortuga_Bank", "barmen", "stay");
		break;
		
		case "Callow_POBEDA_3":
			dialog.text = "� �������� ��, ��� ������. ������ � ���� ������� ������ � �����, "+ GetSexPhrase("����","������") +"";
            link.l1 = "�������� � ����, ����.";
			link.l1.go = "Callow_POBEDA_4";
			NextDiag.TempNode = "Callow_Officer_1";
		break;
		
		case "Callow_POBEDA_4":
			dialog.text = "...";
			link.l1 = "(�������� ���)";
			link.l1.go = "FINAL";
			sld = CharacterFromID("James_Callow")
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.rank = 15;
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "ByWorker");
			GiveItem2Character(sld, BLADE_LONG);
			LAi_SetHP(sld, 270.0, 270.0);
			SetSPECIAL(sld, 9,8,10,4,6,7,9);		//(����, �����, ������, �����, ����, ����, �����)
			SetSelfSkill(sld, 52, 60, 46, 38, 57);		//(��, ��, ��, ���������, �������)
			SetShipSkill(sld, 20, 10, 45, 40, 32, 10, 15, 16, 43);	//(�����, ����, ����, �����, �����, ������, �����, ������, �����)
			sld.greeting = "GR_Jamescallow";
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Payment = true;										//������ �����
			sld.quest.OfficerPrice = sti(pchar.rank)*500
			sld.OfficerWantToGo.DontGo = true;
			sld.reputation = -3;
			LAi_SetImmortal(sld, false);
			sld.HalfImmortal = true; 							    //��������
			sld.loyality = MAX_LOYALITY;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			LAi_SetActorType(npchar);   //������ ��� ������
			ChangeCharacterAddressGroup(npchar, "LaVega_tavern", "tables", "stay1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3);  // ��� � ����������� �������.
		break;
		
		case "FINAL":
			AddQuestRecord("PDM_Cursed_Idol", "10");
			CloseQuestHeader("PDM_Cursed_Idol");
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "tables", "stay1");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
			locCameraFollow();
			ChangeCharacterAddressGroup(sld, "LaVega_town", "none", "");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Callow_Officer_1":
			dialog.text = "��, �������?";
            link.l1 = "�� ����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Callow_Officer_1";
		break;
		
	}
}