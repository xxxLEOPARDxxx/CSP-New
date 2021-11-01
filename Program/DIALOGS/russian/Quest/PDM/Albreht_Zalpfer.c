
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
		
		case "First time":
			dialog.text = "���? ��� ��? ��� ��� �� ���� �����?";
			link.l1 = "��������, ��� �����������"+ GetSexPhrase("","�") +" ���. �� ��������.";
			link.l1.go = "exit";
			link.l2 = "�������, �������. ��� �� �����?";
			link.l2.go = "Next_1";
			LAi_CharacterPlaySound(NPChar, "GR_Kakovi_Merzavczi");
			DeleteAttribute(npchar, "talker");
		break;
			
		case "Next_1":
            dialog.text = "���� ����� �������� ��������, �� � �� ���� ������� ������������� � ����.";
            link.l1 = "���... ��������, �� ��� ���������, ������, ������ �� ��� �� ����������?";
			link.l1.go = "Next_2";
			link.l2 = "�, �� ���� ���, ����� �� ��������.";
			link.l2.go = "exit";
		break;	
		
		case "Next_2":
            dialog.text = "������ ��� � ���� ��������� ������ � ����� �������, ��� ����� �������� ��������. � - �����, ������� ������ � �������! ����� �� ����� ������� ����, ����� �� ����� �������� � ����� ���, ��!";
            link.l1 = "������, �� ������ �� ���������, ���� ���������� ���, ��� ���������.";
			link.l1.go = "Next_4";
			link.l2 = "� ��� ��� �� ����� �����?";
			link.l2.go = "Next_3";
		break;

		case "Next_3":
            dialog.text = "�� ����� ������� ����� �����, �������� ���������, � �� ��-�� ���� ����������� ��������, � ������� ������������ ������, ����� ��������� ����, ��. � ������ ��������� � ����� �������, � ��� ����� ������. ��� �������� ���� ���������� �����.";
            link.l1 = "��, ����� ����. ׸�� ������, �������� ��������� - �� ������ ���������! ������, �� ������ �� ���������, ���� ���������� ���, ��� ���������.";
			link.l1.go = "Next_4";
		break;
		
		case "Next_4":
			sld = CharacterFromID("Charles_shipyarder")
            dialog.text = "� ������� ��������� ��� �� ����� ����� ������� "+sld.name+"�, � �������� ���������. � �����, �� ������ ���� �� ��, ��� � �������� � ���� �������, ��� ����, ����� ����������� ��� ��������� �����������!\n"+
							"� ������� ���, ��� ��� ����������� ������� ����� ��� � ���������������, ��� ��� ����� ��������� ���������, ��! �� ���� �������� ��� ����� � �� ����� ������, ����� ���������� ���������, ��� � ������� ���������.\n"+
							"�� ��� ����� ���� ���������, �� ����� �� ����� ����� ���� �� ������ - � ���, � ������� ���, ��� ����� � �������.";
            link.l1 = "��, ������, ��� ������������� �� ������. ��� � ��� �� ��������, ������� ���� ��������?";
			link.l1.go = "Next_5";
			link.l2 = "� ���� ���� ����, ������. ���� �� �������� �� �����, �� ������ ����� ���� � ����������� ����. � ������� ��� � �������� ��������, � �� ���������� � ����� �������, ������� ��� ��� �� ��������.";
			link.l2.go = "Next_6";
		break;
		
		case "Next_5":
			npchar.lifeday = 0;
			sld = CharacterFromID("Charles_shipyarder")
            dialog.text = "���! � ����������! � �����������, ��� �� ���� �� ������� ����� ������� �������-�������� "+sld.name+"�! � �� ����� �� ����� ������! �������, �� ������� ���� � ������, � ����� �� ������ ��� � ������� �� �����������? �� ��� ������ ��������! ��������, ��! � �� ����� �������� � ����!";
            link.l1 = "�, ��������, ��� ����������� ������ ������, �������� ������� - �� ����? �������! � ��� ��� ������ � ������ ������������� - � ������ �� ������ � ���������������. � ������ �����"+ GetSexPhrase("","�") +" ������...";
			link.l1.go = "Next_7";
		break;
		
		case "Next_6":
            dialog.text = "�������? ��� � �����, "+ GetSexPhrase("����","����") +" �������? ����, �������� ����������� ������������ ������ ��������, �� ������ ������ � �������� ������� ������������ ������������? �� � ����... ����... � ��������! ��� ����������� ���� ������ ���������� ��������! ���������! � ������ ������ ����, � ������ ���� � ������! � �����, "+ GetSexPhrase("����","����") +" �������! ��� ��� �������?";
            link.l1 = "� ������, ������� ��, ������ ��������. � �������, ��� �� �� �����������, � ������ �� ����� � ������� ��������.";
			link.l1.go = "Next_8";
		break;
		
		case "Next_7":
			sld = CharacterFromID("Charles_shipyarder")
            dialog.text = "�������! �� ������ "+ GetSexPhrase("��������","���������") +", "+ GetSexPhrase("�����","�������") +", ��� � ��� ������ "+sld.name+", ��! ����� ���� ��������� �� ������, � ������ � ����� �������, � ���������� ������� ��� �������. �� �� ���� ��������� ���� ����, � ������, ��� �� ��� ��. ��! �� � ����, ����, ��� �� ������ �� ����, ��, � ������ �� ����� �������� ���� ���� ����� ����������� - �� �� ���! ����� �������� ������! � �� ����� � ���� ������������� ������!";
            link.l1 = "��������, �������� ������������, �� ��� ������� �������� ��� ������������ ����� ������. � ��� ����������� ����-�� �� �������. ����� �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Next_9";
		break;
		
		case "Next_9":
            dialog.text = "��! ��� ��! ��, "+ GetSexPhrase("����","����") +" �����! �� ������ ������� ������ ����� ����������� ����������� - � ������ ��� �� ���� ������������!";
            link.l1 = "�, �������, �������. �� ������-�� � �������� � ����� �������������. ����� �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Next_9";
		break;
		
		case "Next_8":
            dialog.text = "�� ������, � ��������� �������� ��� �������, ��� ������ �� ������� �� ����-�����. ��� ����������� �������, ��� �������� ����������, ������� ����������, � �������� ������� ��� ������������ ����� �����������.";
            link.l1 = "����������, ������ ��������, � ������ ����������� �� ��� �������.";
			link.l1.go = "Cod_1"
			NextDiag.TempNode = "Pl_1";
		break;
		
		case "Cod_1":	
			SetQuestHeader("ColonyBuilding");
			AddQuestRecord("ColonyBuilding", "0.1");
			AddQuestUserData("ColonyBuilding", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("ColonyBuilding", "sSex1", GetSexPhrase("��","���"));
			sld = CharacterFromID("Albreht_Zalpfer")
			DeleteAttribute(sld, "talker");
			sld.loyality = MAX_LOYALITY;
			sld.Payment = true;
			sld.quest.OfficerPrice = sti(pchar.rank)*10;
			sld.OfficerWantToGo.DontGo = true;
			sld.rank = 4;
			SetSelfSkill(sld, 5, 40, 5, 5, 5);
			SetShipSkill(sld, 5, 5, 5, 5, 5, 35, 5, 5, 5);
			Pchar.quest.PDM_Albreht_Vhod.win_condition.l1           = "location";
        	Pchar.quest.PDM_Albreht_Vhod.win_condition.l1.location  = "PortRoyal_town";
        	Pchar.quest.PDM_Albreht_Vhod.win_condition              = "PDM_Albreht_Vhod";
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PDM_Albreht_Saditsya_na_korabl", 5);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();	
		break;
		
		case "Pl_1":
            dialog.text = "� ��������� �������� ��� �������, ��� ������ �� ������� �� ����-�����. ��� ����������� �������, ��� �������� ����������, ������� ����������, � �������� ������� ��� ������������ ����� �����������.";
            link.l1 = "��, ������ ��������, � �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pl_1";
		break;
		
		case "Ja_1":
			sld = CharacterFromID("Charles_shipyarder")
            dialog.text = "������� ���, "+ GetSexPhrase("����","����") +" ������� "+GetFullName(Pchar)+". �� ���� ��� ���� ��������� �� ����� ���������� ������, � � ��� ����� �����������.\n"+
							"� ����� ���� �������������, � ����� ��� ������� �� ���� ��� �������, ������������ ���� ����� �����������. � ��� ������, ���� �� ��� ������ �������� � ���� ������, ��� �� ���� ���� ������� "+sld.name+" ���������� ��������� ���� ����� ����������������, � ����, ����� ��� ������ ���������� ������ � ���, ��. ����� �������, ����-������� ��������� � ��������, ��������� � ���, ��� ��� ��������.";
            link.l1 = "���������, ��������, �  "+ GetSexPhrase("��� ���","���� ����") +" ������� ���� ������. �� ��������.";
			link.l1.go = "Finish";
			AddQuestRecord("ColonyBuilding", "0.2");
			RemovePassenger(pchar, NPChar);
			RemoveCharacterCompanion(pchar, NPChar);
			NextDiag.TempNode = "Ja_2";
		break;
		
		case "Ja_2":
            dialog.text = "�! � �� ���� ��������, "+ GetSexPhrase("����","����") +" �������, ��������� ��� ��� �����! ��� ������ �� ������ ������, ��������� � ��������, �� ���� �������������? ��� ������� ���������� � ������, � ����������� ������� ��������! ��� � ��������� ��������! ���� ��� ���� ����, ��������� �� ����������� ������� ��� ����. ��, ��� ������� ����� � ������. �������� ���� � ������. ����������...";
            link.l1 = "������, ��������, �� � ������ �� "+ GetSexPhrase("�������","��������") +" ����� � ������. � ���� ��� ����� ������������� ���.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Ja_2";
		break;
		
		case "Finish":
			Log_info("�������� ������� �� ��������� ���������.");
			PlaySound("Interface\important_item.wav");
			GiveItem2Character(PChar, "Ship_Print_6");
			AddCharacterSkill(pchar, "Repair", 1);
			Log_SetStringToLog("������� + 1");
			ChangeCharacterReputation(pchar, 3);
			LAi_SetCitizenType(npchar);
			Pchar.quest.PDM_Albreht_Vihod.win_condition.l1           = "ExitFromLocation";
        	Pchar.quest.PDM_Albreht_Vihod.win_condition.l1.location  = "PortRoyal_town";
        	Pchar.quest.PDM_Albreht_Vihod.win_condition              = "PDM_Albreht_Vihod"; 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

	}
}
