
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
		
		case "First_time":							//����� Sinistra
			if (pchar.rank >= 12 && sti(pchar.items.patent_spa) == 1)
			{
				dialog.text = "����������� ���, "+ GetSexPhrase("���","����")+". ���� ����� ���������� �������. ������, �� �� ������ �����, ������� �� �������? ��� ����-�� �������...";
				link.l1 = "���, � �� ����, ��� ���, � �� ��� ����� - ��� ���. �� �� �������� ��� ���������� - �������, ��� �� ������ ����?";
				link.l1.go = "Bartolom";
				link.l2 = "�� ����. ���� ����� ��� ����� �������� � ������� - ��� ���� �� �������.";
				link.l2.go = "Bartolom";
			}
			if (pchar.rank >= 12 && sti(pchar.items.patent_spa) != 1)
			{
				dialog.text = "�� �������� �� ��������������� ������ �������? ���? ����� ��� � ���� �� � ��� �������������.";
				link.l1 = "�������. ����� � "+ GetSexPhrase("�����","�����")+".";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_time";
				npchar.talker = 7;
			}
			if (pchar.rank >= 1 && pchar.rank <= 11)
			{
				dialog.text = "�������� ����, �� �� ��� ������� "+ GetSexPhrase("������","������")+", ����� � � ���� ������������.";
				link.l1 = "������, � ����� ����� �����, ����� ��������.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_time";	
				npchar.talker = 7;
			}
			PlayVoice("Kopcapkz\Voices\PDM\Bartholomew Olster.wav");
		break;
		
		case "Bartolom":
			dialog.text = "��������, �� ����� ������ � �� ���� � ���� �������������. ��� ����� ����� �����!";
			link.l1 = "� ����� ������, �� �������.";
			link.l1.go = "PoraVTavernu";
		break;
		
		case "PoraVTavernu":
			SetQuestHeader("PDM_Ohota_na_vedmu");
			AddQuestRecord("PDM_Ohota_na_vedmu", "1");							
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
			
			sld = CharacterFromID("PDM_Isp_sekr_guber")
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back", "PDM_ONV_BARTO_Ischezni", -1);
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Carla", "Girl_3", "woman", "woman", 10, SPAIN, -1, false));
			LAi_SetImmortal(sld, true);
			sld.name = "����� ";
			sld.lastname = "";
			sld.city = "Havana";
			ChangeCharacterAddressGroup(sld, "Havana_tavern", "goto", "goto13");
			LAi_SetWaitressType(sld);
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "First_Carla_1";
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First_Carla_1":
			dialog.text = "���� �� ����� �����, ����"+ GetSexPhrase("�","�")+"? ������������, � �������? ���� ����� �����, ��� ������ �����, ��� ���� �������� ����������� ������ � ���� ������. � ��� ���� �����, ������"+ GetSexPhrase("","���")+"?";
			link.l1 = "������ ����� ���� "+pchar.name+", ��������. �� � �������, ��� ��� � ������ ���� ��� ���� �������, ������� ���� ������������. � �����"+ GetSexPhrase("","�")+" ��� �� ������� - ��� ������, �� �������� ����������� � �����.";
			link.l1.go = "First_Carla_2";
			PlayVoice("Kopcapkz\Voices\PDM\Spain\Catalina.wav");
		break;
		
		case "First_Carla_2":
			dialog.text = "���? ����������? �� � ������, ��� ��... �, �������... ������ ���, ����"+ GetSexPhrase("�","�")+" - � ��� ���������, ��� � ������� ������ �������. �� �� ��������� ��, ���� ��� ������� � ������ ��� - ����� � ���� �����������. � ���� ����� �������� ����, ������.";
			link.l1 = "�... �������. � ������� ������� � ���� �������.";
			link.l1.go = "First_Carla_Uhodit";
		break;
		
		case "First_Carla_Uhodit":
			AddQuestRecord("PDM_Ohota_na_vedmu", "2");							
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
			
			bDisableFastReload = true;
			LocatorReloadEnterDisable("Havana_town", "reload3_back", true);
			LocatorReloadEnterDisable("Havana_town", "reload2_back", true);
			LocatorReloadEnterDisable("Havana_town", "reload1_back", true);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload2_back", true);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload3_back", true);
			
			sld = CharacterFromID("PDM_ONV_Carla")
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_ActorRunToLocator(sld, "reload", "reload1_back", "PDM_ONV_Clara_Ischezni", -1);
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Sin", "SpaOfficer1", "man", "man", 100, SPAIN, -1, false));
			sld.name = "�������� ";
			sld.lastname = "";
			sld.greeting = "GR_Spainguard";
			sld.city = "Havana";
			FantomMakeCoolFighter(sld, 100, 100, 100, "blade27", "pistol6", 0);
			LAi_SetHP(sld, 1.0, 1.0);
			LAi_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, "Havana_town", "reload", "reload3_back");
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "OfficerGuard";

			PChar.quest.PDM_ONV_Vzaimno.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_ONV_Vzaimno.win_condition.l1.character = "PDM_ONV_Sin";
			PChar.quest.PDM_ONV_Vzaimno.win_condition = "PDM_ONV_Vzaimno";
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "OfficerGuard":
			dialog.text = "��������, ������, �� ��� �� ������ ������ ��������.";
			link.l1 = "��� �������, ������. �����!";
			link.l1.go = "OfficerGuard_Cod";
			NextDiag.TempNode = "OfficerGuard_Again";
		break;
		
		case "OfficerGuard_Cod":
			AddQuestRecord("PDM_Ohota_na_vedmu", "3");							
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
			
			PChar.quest.PDM_ONV_Vkomnate.win_condition.l1 = "location";
			PChar.quest.PDM_ONV_Vkomnate.win_condition.l1.location = "Havana_TownhallRoom";
			PChar.quest.PDM_ONV_Vkomnate.win_condition = "PDM_ONV_Vkomnate";
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "OfficerGuard_Again":
			dialog.text = "��������, ������"+ GetSexPhrase("","���")+", �� ��� �� ������ ������ ��������.";
			link.l1 = "��� �������, ������. �����!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OfficerGuard_Again";
		break;
		
		case "Soldat15":
			dialog.text = "C�����"+ GetSexPhrase("","���")+", ���������� ���������� � ����� ���������.";
			link.l1 = "�������, ������, � ��� � ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Soldat15";
		break;
		
		case "RazgovorSGuberom":
			dialog.text = "������ ����, ������"+ GetSexPhrase("","���")+" "+pchar.name+". ��-�� ��� � �����!";
			link.l1 = "������ ����, ���� ������������������! ��� � ���� ���� ��� "+ GetSexPhrase("�������","�������")+"?";
			link.l1.go = "RazgovorSGuberom_2";
			PlayVoice("Kopcapkz\Voices\PDM\Francois de Bijou.wav");
		break;
		
		case "RazgovorSGuberom_2":
			dialog.text = "(���������� � ����������) �������� ���.";
			link.l1 = "...";
			link.l1.go = "RazgovorSGuberom_3";
		break;
		
		case "RazgovorSGuberom_3":
			dialog.text = "�������� ���� ����� ��������, �������. ��� ������ ����, ��� ���������, ��� ������ ������ � ����� �������. ���-�� ������� ��� ����� � �������, ��� ���� ���� ����� �� �����, � ����� ��������. �� ��� ������� ������ ������ ��� ������� �� ���. � �� ����, ��� �� ��� ������. ��� ������� ��������.";
			link.l1 = "����� �������� �������. �� ��� ��� ���������, ��� ����� ��������� ���� ����������?";
			link.l1.go = "RazgovorSGuberom_4";
			sld = CharacterFromID("PDM_ONV_SoldatGub_1")
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_ActorGoToLocator(sld, "goto", "goto3", "STRAJIschezni", 3);
			sld = CharacterFromID("PDM_ONV_SoldatGub_2")
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_ActorGoToLocator(sld, "goto", "goto3", "STRAJIschezni", 3);
		break;
		
		case "RazgovorSGuberom_4":
			dialog.text = "���������� ������������� ������� ���. ��� ��������� ������ ���� ��������� ���������. �� ��� ����� ����������� ��������� � ���������� ����������. �� ������������� ���������� ��� ����� � ������. ����� �� ��� ������� ����������, �� ����������� ��� �����. ���� �� ���� ������� �������� � ��� � ����-�����. ��� ��������� �� ����� ����� ����, ��� �������� � �������. �������� ������ ������, �� ���������� ����� ���� ����������.";
			link.l1 = "�������, � �������� ���. ����������, �� ��������? �������, �� �������, �� ����� ������� �� ������� �� ����� �����.";
			link.l1.go = "RazgovorSGuberom_5";
		break;
		
		case "RazgovorSGuberom_5":
			dialog.text = "������� �� �������? ��� ����� �������. �� ��� ������� ���������, ��� � ������, � ���� �� ����� ���� ������ ������ � �������� ����� ���������.";
			link.l1 = "������ �������-����������, ��� �� ������� � ��� ������? ��� ��� ����� ���?";
			link.l1.go = "RazgovorSGuberom_6";
		break;
		
		case "RazgovorSGuberom_6":
			dialog.text = "��� ������� ������ ��������� ������, � �������. �� �� ���� ������� ������ ���������.";
			link.l1 = "�������, ������ �������-����������, ��� ������� ����� ���������. �� � ���� ���� ������ ����, � ���� �� ���� ��������...";
			link.l1.go = "RazgovorSGuberom_7";
		break;
		
		case "RazgovorSGuberom_7":
			dialog.text = "������-��, ��, ������"+ GetSexPhrase("","���")+" "+pchar.name+". �� ��������, ��� ������ ���������� ����� ������� �� ������� �� ����� �����, ��? �� �� �������� � �� ���? � ��� �� ������� �� ���, �� ��� ������� ����� ������. ����� ����, �� �� ����� ������ ��� ���� ����� ���������. � ����� ����� ������������� ��� ������ ��������.";
			link.l1 = "�����, ������ �������-����������, ���� � ����� �, �������, ������� � ����. �����!";
			link.l1.go = "RazgovorSGuberom_COD";
			NextDiag.TempNode = "RazgovorSGuberom_Again";
		break;
		
		case "RazgovorSGuberom_Again":
			dialog.text = "� ��� ��� ��� �������, ������"+ GetSexPhrase("","���")+". ��� �� ������ ��� ��������?";
			link.l1 = "� "+ GetSexPhrase("����������","�����������")+", ���� ������������������. � ��� ������ ������� �����. �� ��������!";
			link.l1.go = "exit";
			NextDiag.TempNode = "RazgovorSGuberom_Again";
		break;
		
		case "RazgovorSGuberom_COD":
			LocatorReloadEnterDisable("Havana_Townhall", "reload1_back", false);
			LocatorReloadEnterDisable("Havana_Townhall", "reload3", true);
			
			PChar.quest.PDM_ONV_SVOBODA_URA.win_condition.l1 = "location";
			PChar.quest.PDM_ONV_SVOBODA_URA.win_condition.l1.location = "Havana_town";
			PChar.quest.PDM_ONV_SVOBODA_URA.win_condition = "PDM_ONV_SVOBODA_URA";
			
			AddQuestRecord("PDM_Ohota_na_vedmu", "5");							
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex1", GetSexPhrase("��","���"));
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex2", GetSexPhrase("��","��"));
			sld = CharacterFromID("PDM_ONV_Sin")
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "RazgovorSViktorom_1":
			dialog.text = "�� ��� ���"+ GetSexPhrase("��","��")+", "+ GetSexPhrase("������","��������")+"? � ���, ���� ���� �������, ���� �����?";
			link.l1 = "� �����"+ GetSexPhrase("","�")+", ��� �� ��������, ��������, ����� ����, ����� �������������... ��, ������, � "+ GetSexPhrase("������","��������")+".";
			link.l1.go = "RazgovorSViktorom_2";
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
		break;
		
		case "RazgovorSViktorom_2":
			dialog.text = "��, "+ GetSexPhrase("��������, �� ������","�����, �� ��������")+". � ������ ������, ����������� ������. ����� ���� ���������� ������� ��������� ��� �������� ����������. ������, ��� � ��� ���������?";
			link.l1 = "�������... �� ����� �� ������� �� ������� ����, � �� ���������� ��� ���� �������.";
			link.l1.go = "RazgovorSViktorom_3";
		break;
		
		case "RazgovorSViktorom_3":
			ChangeCharacterAddressGroup(pchar, PChar.location, "sit", "sit_front2");
			LAi_SetSitType(pchar);
			LAi_SetSitType(npchar);
			locCameraTarget(PChar)
            locCameraFollow();
			dialog.text = "� �������� ����, ��� �� ���� �������� - �� ��� �� ���������� ������, ������� ������������ �����. �� ��������� ��-�� ���� ��������� ������, ������� ������� �������� � ������. ����� � ����, ���� �� �� �� �������� � ���� �������, �� ��� �� ��� ������. �� �� ������ ��� ������� �������. �� ��� ����������� ������ �������, ��� ������ ������ ������.\n"+ 
							"�� ����� ���� ��� ��� ������� ��������� �� �����, �� ���������. ��, �� ���������. �� �����, ������ ������� �����. �� ��������, ����� �� �� ���� ��� ������� � ����� - ����� ������� ���������, ��� ������� �� �����, ��� � ���������... ����� �� ����� �������, ��� �������������.\n"+  
							"� ��� ��-�� ���� �����...";
			link.l1 = "�������! �� ������, � ����� �����? ��� ������� ����������� ��� ���������. �� �������, ��� ��� ����� ���� ��������� � ��������!";
			link.l1.go = "RazgovorSViktorom_4";
		break;
		
		case "RazgovorSViktorom_4":
			dialog.text = "��, �������-���������� ����. ��� ������� ������ ����� ������ ��������. �� ��� ����, ������ ������ ������, ����� �� �������� ��������. �� ������-������ ����� � ����, ����� ����� ��� ������ �� ������. �� ��������� ������ ��������� ������, �� ��� ���������� ������� �������. � ������ � ����������� ������. ������ ������ �������� � �������� �������� ��������� ���� ��������, � ������ ���� �������, � ��� ������ ����������� ������.";
			link.l1 = "��� �� ������ ������� ��� �������! ��� ���������� ��� ����� �����. Ÿ ���������� ����������.";
			link.l1.go = "RazgovorSViktorom_5";
		break;
		
		case "RazgovorSViktorom_5":
			dialog.text = "����� ���� ������� � � �������!";
			link.l1 = "� ����������� � �����. �� �������!";
			link.l1.go = "RazgovorSViktorom_COD";
			NextDiag.TempNode = "RazgovorSViktorom_Again";
		break;
		
		case "RazgovorSViktorom_COD":
			sld = CharacterFromID("PDM_ONV_Viktor_Martos")
			sld.lifeday = 0;
			
			AddQuestRecord("PDM_Ohota_na_vedmu", "11");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
			
			ChangeCharacterAddressGroup(pchar, PChar.location, "tables", "stay2");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Carla", "Girl_3", "woman", "woman", 10, SPAIN, -1, false));
			sld.city = "Santiago";
			ChangeCharacterAddressGroup(sld, "Santiago_tavern", "goto", "goto4");
			LAi_SetWaitressType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.name = "����� ";
			sld.lastname = "";
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "Carla_Final_1";
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "RazgovorSViktorom_Again":
			dialog.text = "����� ���� ������� � � �������!";
			link.l1 = "� ����������� � �����. �� �������!";
			link.l1.go = "exit";
			NextDiag.TempNode = "RazgovorSViktorom_Again";
		break;
		
		case "Carla_Final_1":
			dialog.text = "�, ��������! ��� �� ������� ������� �������? ��� ����� ������?";
			link.l1 = "������ ������! �� ���������� ���� ���������� ���� ���������� ������� � �������� ������� �������� � �������� �������!? ��� ��������� ����������� ���� � ����������!";
			link.l1.go = "Carla_Final_2";
			PlayVoice("Kopcapkz\Voices\PDM\Carla.wav");
		break;
		
		case "Carla_Final_2":
			dialog.text = "�-��� �� ��������, ������"+ GetSexPhrase("","���")+"? � �-�-�� �-���� �� � ����� �������������.";
			link.l1 = "�� �������, ��� ���� ������� �������� ���� ����������, ������� ���������? � ���� ���� ��������� - ������ ������. �� ����� ���� ��������� � ���, ��� �� - ������.";
			link.l1.go = "Carla_Final_5";
			link.l2 = "� ���� ���� ��������� - ������ ������. ������ ������ ���� �� ����� ������� �������� �� ��������! � �� ��� ������, ����� �������������� ���� ��� ����������� ������� � ������� ������ ���������� �������� � ������. �... ���, � ���������"+ GetSexPhrase("","�")+". � ����� �����, � ���� ������ ����� �� ���� ������. ���������� ��������� ���� - � ���� ���� ����� ���������� ��� ����, ����� �������� ����.";
			link.l2.go = "NaKoster_1";
		break;
		
		case "Carla_Final_5":
			dialog.text = "� ����, ��� ������ ������ ���� ���� �����... �� � �� ����� ������ �������� - ��� ���� ���� ���������� �� ����� ������� ����������. �� ����� �� ��-���� ��������� ��� ��������� - � ������, ��� �� �������. ������ ��� �������. � ������ ���...";
			link.l1 = "������. � ������ �� �����"+ GetSexPhrase("","�")+". ����� ��� ���������? ������ ����?";
			link.l1.go = "Carla_Final_6";
		break;
		
		case "Carla_Final_6":
			dialog.text = "���������� ������� ������� ������, ����� �� ������ ��� � �����, ��� ����. � �������� ������ ������ ��� ������ �� ��������, ��... ������. ���� ��� ������ �� ������� ��� ����, ����� ������������� ���� ������������� ���������. � ���� ����� ���� ��������, ������� �� ������� ���� ��������� �������.";
			link.l1 = "��� �� ���������, ��� �� ������?";
			link.l1.go = "Carla_Final_7";
		break;
		
		case "Carla_Final_7":
			dialog.text = "��. ���������� ������� ��� ���� ����������� � ���������� �������. �� ������� �� ��� ���� ���, ����� ��� ���� ����� ������������. ����� � ���� ������ ���������� ��������, ������� �� ��������, ��� ������. � �� ���� ��������, �� �� ��������� ���, ��� �������� ������ ������, � � ����� �����-������� ������� ������������. �� ����������� ���� ��� ����, ����� ���������� ������� � ��������, �� ����� ���� ����� ��� ��������, ������� � ����� ����������. � ������ �� ����� ���� ������ - �� ��� ������� ����...\n"+ 
							"�� ����� � ��������� ������, � ��������, ��� � ���� ��������� �����������...  � �������� ����� ��������� ��������... �� ���������� ������, ��� ���� � ��������� �������, �� �� ��������� �����������, ��� � ������, � ��� ������ ���� �� ������. � ���������� ��� ��� ������. � �� �����, ��� ��� ������� ����� ��������. ��� ��� ��� ������� ����, ����� ���������� � ��� ���������, � � ����� ���� ������ �������. �� ������ ������ � ���� ����.";
			link.l1 = "�� ��� �� ���������� ����� ������?";
			link.l1.go = "Carla_Final_8";
		break;
		
		case "Carla_Final_8":
			dialog.text = "��� ���� ����� �������. � �������� �� ������� ����� � �����... � ��� ������� ��� ��������. ����� �����, �� ���������� � ������� ����� �������� � ������������ ������.  �� �� �� ����, ��� �� ���������. � �����, ��� �� ������� ������� ������ �� �����, ������� � ��������� ���. ������ �������� �� ����, �� ��� ����� ���������� ���������. � � ���� ������ � ������, ��� ��� ��� ������. ��������� �������� ������ ���������, � ��� ���� �������� �������, ������, ��� ��� ����� ������������. ������ ������� � �������� � ������� ��� ��������, � ����� ������.\n"+ 
							"� �������� ������ ������ ��� ������ �� ��������. �� ����� �� ���� ������ �� ������, ��� �������� �������� � �������. ������� ���� � ������ - � ���� ������������ �������� �� �������, ������� ������� � ������� �� �������� �������. ���� �� �����, ��� �����������, ��� ���� ����� �����.";
			link.l1 = "� ��� ��������� �����?";
			link.l1.go = "Carla_Final_10";
		break;
		
		case "Carla_Final_10":
			dialog.text = "� �� �����, ��� ��� ������. ��, ���� � ������ ��� ������� �� ����� ��������. ����� � ������� ����, � ���� �� ���� �����, � � ��������� � ������������� �������, ������� ����... � ������, "+ GetSexPhrase("������ ������","������ ���������")+", ����� ����, ��� � ��� �� ����������, �� ������ ���������� ����, � ����� �� ������, ������ �� ��, ��� � ������ ����, ������, � ���� ���������, ��� �������.";
			link.l1 = "����������� ������ ���� � ���� ��� ������� � ���, ��� �� ������. ������� � ������� ���� � ���� ������.";
			link.l1.go = "NaKoster_2";
			link.l2 = "�������, ��� �� �� ��������� �������� ������������, �����. �� ��������.";
			link.l2.go = "Carla_Final_11";
		break;
		
		case "Carla_Final_11":
			dialog.text = "�, "+ GetSexPhrase("������","���������")+" - �� ����� ����������. � ����� ��� ��� ���. ��� �������, ��� ����������, ��� ������� ��������� ����. �� � ����� ���, ��� ��� ������ ���, ��� ����������, ��� � ����� ������...";
			link.l1 = "";
			link.l1.go = "Carla_Final_12";
		break;
		
		case "NaKoster_2":
			dialog.text = "��� ���������, "+ GetSexPhrase("������","���������")+". ��� ����� ����� ��� ���� ������ �� ������ - � �� ������ ����������, �� ������� ����� - ���� �� ������� ������������ �� ����������.";
			link.l1 = "�� ������� ����������� ����, ��������� ������! �� ������ ������ � ����!";
			link.l1.go = "NaKoster_COD";
			NextDiag.TempNode = "NaKoster_Again";
		break;
		
		case "Carla_Final_12":
			dialog.text = "� ������� ��� ���. ����� ����� ������������� ��� � ����� ���.";
			link.l1 = "����� ��� �����, �����! �� �������.";
			link.l1.go = "Dobro_Final";
			NextDiag.TempNode = "Carla_Final_Again";
			AddBonusEnergyToCharacter(pchar, 25);
			PlaySound("Interface\new_level.wav");
			Log_info("���� ������� ����������� �� 25 ��������.");
		break;
		
		case "Dobro_Final":
			AddQuestRecord("PDM_Ohota_na_vedmu", "12");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("PDM_Ohota_na_vedmu");
			ChangeCharacterReputation(pchar, 3);
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Carla_Final_Again":
			dialog.text = "������� ���, "+ GetSexPhrase("������ ������","������ ���������")+", � �� ������ ������ ������������!";
			link.l1 = "����� ���, �����!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Carla_Final_Again";
			PlayVoice("Kopcapkz\Voices\PDM\Carla.wav");
		break;
		
		case "NaKoster_1":
			dialog.text = "� ����, ��� ������ ������ ���� ���� �����... �� � �� ������� ��� ������ ������� - �� ������ �����... ��! �� �� ����� ��� �� ��������. �������� ����, ������"+ GetSexPhrase("","���")+" ����� - ������ �� ����� - ��� ����� ����� ������ �� ������.";
			link.l1 = "����������� ����� �� ���� ���� ������ ��, ��� �� - ������. � � ������� �������� ���� ������ �����, ����� ��� ��������� ���� ����.";
			link.l1.go = "NaKoster_COD";
			NextDiag.TempNode = "NaKoster_Again";
		break;
		
		case "NaKoster_COD":
			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Inkvizitor", "PGG_Vincento_0", "man", "man", 10, SPAIN, -1, false));
			sld.city = "Santiago";
			ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "sit", "armchair1");
			LAi_SetHuberType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.name = "�������";
			sld.lastname = "�� �����";
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "Inqizitor_1";
			
			AddQuestRecord("PDM_Ohota_na_vedmu", "13");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "NaKoster_Again":
			dialog.text = "��� ����� ������ ������ �� �����... �� � �� ������� ���� ������ �� � ������� �� �������� � ����.";
			link.l1 = "�� ������� � ����, ������� ������!";
			link.l1.go = "exit";
			NextDiag.TempNode = "NaKoster_Again";
		break;
		
		case "Inqizitor_1":
			dialog.text = "���� ����� ������ � �����! �� ����� �� ��������� ����� �� ����� ���� ������ ���� � ����� ������� ������! �-�... ���� �� ������, ��� ���?";
			link.l1 = "������ ����, � ����, ����� ���� ������ �� ����� �����, ������ �������� �����������. ����� ����� ���������� ��� ����� ��� ����� - �������� ������ ������, � ������� ������� ����������, ������� ����, �� ����� ���������. �� ��� ������ ��������� ���� ���������. � ���� ����, ����� ������ ���������� �������� � �� ��������� ������.";
			link.l1.go = "Inqizitor_2";
			PlayVoice("Kopcapkz\Voices\PDM\Zaharia Marlow-02.wav");
		break;
		
		case "Inqizitor_2":
			dialog.text = "��, �� ����� ���� ���� ����� ������������� �� ���� ��������� ��������, ��� ���. �� ����������� �� ���� ������.";
			link.l1 = "� ������� �� ���, ������ ����. ������� ��� ���.";
			link.l1.go = "KAZN";
		break;
		
		case "KAZN":
			DoQuestReloadToLocation("Santiago_town", "officers", "reload8_2", "PDM_ONV_KaznVedmi");
			TavernWaitDate("wait_night");
		break;
		
		case "Inqizitor_Kazn_nachalo_1":
			dialog.text = "������, ��� �� ������, ��� ���. �� ��������.\n"+
							"(���������� � �����������) ������, �������-����������� �������� ����� ���, ������������ ������� �����������, �� ������� ������� ��� �� �����, ��� ���, ����, ��������, ����� ���.";
			link.l1 = "...";
			link.l1.go = "Inqizitor_Kazn_nachalo_2";
			PlaySound("Kopcapkz\Voices\PDM\Witch\Fon.wav");
			
			sld = CharacterFromID("PDM_ONV_Jitel_1")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_2")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_3")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_4")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_5")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_6")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_7")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_8")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_9")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_10")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_11")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_12")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_13")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_14")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Podjigatel")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Carla")
			LAi_ActorTurnToCharacter(CharacterFromID("PDM_ONV_Carla"), pchar);
		break;
		
		case "Inqizitor_Kazn_nachalo_2":
			SetMusic("none");
			sld = CharacterFromID("PDM_ONV_Inkvizitor")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, CharacterFromID("PDM_ONV_Jitel_5"));
			
			PlayVoice("Kopcapkz\Voices\PDM\Witch\Inkvizitor.WAV");
			DoQuestFunctionDelay("PDM_ONV_Kazn", 17.0);
			DoQuestFunctionDelay("PDM_ONV_Kazn_2", 20.0);
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Inqizitor_Kazn_3":
			dialog.text = "(����� ����� � �������� �������� �����. ����� ��������, �������� ��� ��������� ����� � ������ ������������ ��� ���������� ������ ������� ������ �����, �� ����� �� ���� ����������, �������� ������ �, �������, �����...)";
			link.l1 = "...";
			link.l1.go = "Inqizitor_Kazn_4";
			PlaySound("Kopcapkz\Voices\PDM\Witch\fire.wav");
		break;
		
		case "Inqizitor_Kazn_4":
			SetMusic("none");
			PlaySound("Kopcapkz\Voices\PDM\Witch\Music.wav");
			PlaySound("Kopcapkz\Voices\PDM\Witch\scream.WAV");
			CreateLocationParticles("shipfire", "merchant", "mrcActive2", 0, 0, 0, "");
			LAi_SetActorType(pchar);
			sld = CharacterFromID("PDM_ONV_Podjigatel")
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "houseSp2", "PDM_ONV_PodjIschezni", -1);

			DoQuestFunctionDelay("PDM_ONV_Kazn_3", 8.0);
			DoQuestFunctionDelay("PDM_ONV_Kazn_4", 12.0);
		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
	}
}