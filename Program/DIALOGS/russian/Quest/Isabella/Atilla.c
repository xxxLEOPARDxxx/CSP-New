
void ProcessDialogEvent()
{
	ref NPChar, sld;
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
	if (PChar.sex != "woman")
	{
		dialog.text = "���� ��� �������! ������� " + GetFullName(PChar) + "!";
		link.l1 = "������! �������, ������ ������� ����!";
		link.l1.go = "port_1";		
	}
	else
	{
		dialog.text = "��������� " + GetFullName(PChar) + "! ��� � ��� ���� ������!";
		link.l1 = "���� � ���� �� ����, ������. ��� �� � ��� �������������. ��� �������, � ������, ��� �� ��������� ���� � ��������? ����������.";
		link.l1.go = "W_exit";
		if (startherotype == 2)
		{
			dialog.text = RandPhraseSimple("���� ����? ������� ����.", "������ ������������ ������, ������.");
			link.l1 = RandPhraseSimple("������ ���? �� ������!", "������� ���� ���. �� �� ������ ������ ���!"); 
			link.l1.go = "exit";
			NextDiag.TempNode = "W_exit";
		}
	}
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "talker"); //������� ���������
		break;

	case "W_exit":
		npchar.lifeDay = 1;
	LAi_CharacterDisableDialog(npchar);
    DialogExit();
	break;
	
	case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = "" + PChar.name + ", �� ��� �� ��������? ���������� ����� ������!";
				link.l1 = LinkRandPhrase("������.", "�����.", "�� ���������, ��� ������...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "��������� �� ���������, "+ GetSexPhrase("��������","�������") +", ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� "+ GetSexPhrase("�������","������ ���") +" ����� ������ ���� � ������� �� ���������. ��� ���� ������...");
				link.l1 = LinkRandPhrase("������.", "�����.", "�� ���������, ��� ������...");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		
		case "port_1":
		    sld = characterFromID("Atilla");
			dialog.text = "�� �����, ���������, ��� ���� ���!  ������, � � �������� ����� �� ������! �� ���������� ������� ������� ���������?";
			if (pchar.RomanticQuest == "")
			{
			    link.l1 = "� ��������� ��� ���� ������, �� ������ �� ����, �������. � ������ ���...";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "��-��-��! �� ����� ������� ���� �� ���������� �� ������ ������� ��������� ����!";
				link.l1.go = "port_1_1";
			}
		break;

		case "port_1_1":
			dialog.text = "����� ��� ��������, �� ����� ������� ������ ����! ���������� � �������...";
			link.l1 = "�������� - � �������!";
			link.l1.go = "port_toTavern";
		break;

		case "port_toTavern":
			DialogExit();
			NextDiag.CurrentNode = "Tavern_1"; 
			chrDisableReloadToLocation = true; 
			bDisableFastReload = true; 
			FreeSitLocator("Pirates_tavern", "sit3");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Pirates_tavern", "sit", "sit3", "Romantic_Pirat_toTavern", -1);
		break;

		case "Tavern_1":
			LAi_SetSitType(Pchar);
			dialog.text = "���� ������, "+GetFullName(PChar)+"! ������� ������ �� � ����� ���������� ����� � ��������, ������� ���� ����!";
			link.l1 = "�� ��... ������ ����������� �������� �� �������� � �������� � ��� ���. �� �� ����� ����� ���� � ���� ��� �������� - ������... � ��� ��� ����, � ����, �� ����� ��������� �����.";
			link.l1.go = "Tavern_2";
		break;
		
		case "Tavern_2":
			dialog.text = "������! ��� ��� � ���� ����� - ������� �� ���� ���� ����������� �����! ����� � � �����. ����� ���-�� ��� ����������� ��������. ����� ���������� ������ ��������.  �� ������� ��� - �������� ������ - ��� ���� ���, � � �����������-�� � ���� ����. ������ �����, ������ ��� �������, ��� ����� ���� ������ �������� ��������� � �������������� ��� � ����� ������������ ��������. ��, �������� ��� ����� �� �����, ����� � ����� ���� �������� ����, �������� �� ��������...";
			link.l1 = "���, �� ��� ������...";
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			dialog.text = "���-�� ��� ���, �� ��� ������ ���������, ��� �������� ��� �� ����� ���. ������� ����� ����, ��������� ��� ����� � ��� �����.";
			link.l1 = "� �� ������� ��� ��� � ���? ���� ���� ����� ����������! �� � ��...";
			link.l1.go = "Tavern_4";
		break;
		
		case "Tavern_4":
			dialog.text = "��� �� ��, ������?! �����-�� �� �� ��������� ������. � ��� ���� ���� ��������. ��, �� ��� � ���. ��� ���� ������ ������ ���, ����� �������, ���������� - � ����� �� ����� �� ������.";
			link.l1 = "��, ���-�� �� ���� ������ ������������, �������.";
			link.l1.go = "Tavern_5";
		break;
		
		case "Tavern_5":
			dialog.text = "����� ����, �� � � ������. �� ��� ������ ��� ��� ��������� �������� �� ��� ����...  � ���������, �������, �� ��� ������� �������� ������. ����� ������ � ���-�����...";
			link.l1 = "���� ���� ������!  ������, �������, � �� ��������� �� ��� ��� ����� �������� ���������? �������, � ������� �������� ���� ���������� ��������, �?";
			link.l1.go = "Tavern_6";
		break;
		
		case "Tavern_6":
			dialog.text = "��-��-��! ������� ���, �� �� ���� ���������� � �� ������� ���������� �������!  �� ���, ��������, ��� ������ ������ �� ���� ��� - �����, ��� ���� � ����... ��, ���� ���. ���� ��� - ��� ��������.";
			link.l1 = "������, ������.";
			link.l1.go = "Tavern_Out";
		break;
		
		case "Tavern_Out":
			NextDiag.CurrentNode = "Tavern_Bye";
			DialogExit();
			AddDialogExitQuest("Romantic_Pirat_toTavern_end");			
		break;

		case "Tavern_Bye":
            NextDiag.TempNode = "Tavern_Bye";
			dialog.text = "������ ����� � ����� �� �������...";
			link.l1 = "�� ���� ������.";
			link.l1.go = "exit";
		break;
		//������� ������� �� �������� ������
		case "TalkingNews":
			dialog.text = "��, ���� � ����! " + GetFullName(pchar) + " ����������� ��������!";
			link.l1 = "�������, ������! ���� � ����, ������, ������������ ���������� - ��� �����...";
			link.l1.go = "TalkingNews_1";
		break;
		case "TalkingNews_1":
			dialog.text = "��������� ��������, ��� � ����� ������� � ������������. ����, �� ����� �������, ��� ����� - ��� ������ �� ��� �� �������...";
			link.l1 = "��, ���� �����.";
			link.l1.go = "TalkingNews_2";
		break;
		case "TalkingNews_2":
			dialog.text = "��, �����! ��, ������, ����� ��������� �� ���?";
			link.l1 = "�� �� ������, ��� ����� ����, ��� � ���� ������ �� ����������... � �����, �������� � ������ �������� ���������� ���������.";
			link.l1.go = "TalkingNews_3";
		break;
		case "TalkingNews_3":
			dialog.text = "���, ��� ��� �������! ��� �������� ���� ����������? ������ �������� - �������?";
			link.l1 = "��, ������. ���� ���, �������� - ����� �������� �������... � ����������, � ���� ��.";
			link.l1.go = "TalkingNews_4";
		break;
		case "TalkingNews_4":
			dialog.text = "���, ��� � ���� �� ��� �����? ������� - ����� ��������, �� ������� �������� ����� ���������� ������� ���.";
			link.l1 = "��� - ��� ���������! � ���� �� ��������� � �����������, ��� ��� ��������.";
			link.l1.go = "TalkingNews_5";
		break;
		case "TalkingNews_5":
			dialog.text = "� �������������...";
			link.l1 = "� �����, ������ � �� ���-���� ����� ��������� � ����� � ����� ��������, ��� � ����. ����� ���� ��� ���������, �� � ����� ���������, ��� ��������� ������� ���� ���� � � ���� �� ������ ���� �� �����.";
			link.l1.go = "TalkingNews_6";
		break;
		case "TalkingNews_6":
			dialog.text = "�� ��, ���������, ��������...";
			link.l1 = "�� ���� ��������� � ���� �������� ����������... ����� ��� ������� �������� ������������� ���-�� - ��������� ��� � ���� �����. � �������� � ���� ���������, ������ �� �������...";
			link.l1.go = "TalkingNews_7";
		break;
		case "TalkingNews_7":
			dialog.text = "�� ��� ��, ����, ������� ���� �� ������� ������������ ��������������. ��� ������� ������ ������?";
			link.l1 = "����� ����� ���������� � ��������� ��� �����. ��� � ��������� ����� �����������... ��� ������, ��� ��� � ���� �� �����.";
			link.l1.go = "TalkingNews_8";
		break;
		case "TalkingNews_8":
			dialog.text = "�-�-�, ��������, � ���� �� ��� �����?";
			link.l1 = "���, ������, ��� ���...";
			link.l1.go = "TalkingNews_9";
		break;
		case "TalkingNews_9":
			dialog.text = "L'amour... Qu'ici faire?..";
			link.l1 = "����?..";
			link.l1.go = "TalkingNews_10";
		break;
		case "TalkingNews_10":
			dialog.text = "��� �����������... ������, ��� � �������..\n"+
				          "� ��� ������-�� �������?";
			link.l1 = "�� ����, ��� ������ �� �������.";
			link.l1.go = "TalkingNews_11";
		break;
		case "TalkingNews_11":
			dialog.text = "��������, �� ������� ���������� �� ���-�����, � ��� ����� ������. ������ � ���� ������������ � �������.";
			link.l1 = "� �� ������� ����� ���?";
			link.l1.go = "TalkingNews_12";
		break;
		case "TalkingNews_12":
			dialog.text = "�����, ��. �� �� ���� � ��������� ���������� � ������, ���� � ��� � ����� ������ ������...";
			link.l1 = "�� ��� ��, ���� �� �������. � ��� ��� ������?";
			link.l1.go = "TalkingNews_13";
		break;
		case "TalkingNews_13":
			dialog.text = "��������� ������ ������ ����, �� � � ����� ������ ������� ��������. ������ �� ��� ����� �� �������, ������ ���������. ����� ��� ������ ���������� �����, � ���� � ����. ����� � �������� ���� ���, ��� ����� ������.";
			link.l1 = "������, ������. �� ��� ��, ����� ����.";
			link.l1.go = "TalkingNews_14";
		break;
		case "TalkingNews_14":
			SetTimerCondition("Romantic_AtillaToHouse", 0, 2, 0, false);
			AddQuestRecord("Romantic_Line", "11");
            LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			//��������� ��� ���������� � ������� ��������, ������ ������� ����� � ���.
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", false);
			ChangeCharacterAddress(characterFromId("Isabella"), "none", "");
            Pchar.quest.Romantic_AmbushInHouse.win_condition.l1 = "location";
            Pchar.quest.Romantic_AmbushInHouse.win_condition.l1.location = "SanJuan_houseSp6";
            Pchar.quest.Romantic_AmbushInHouse.win_condition = "Romantic_AmbushInHouse";
			DialogExit();
		break;
		//����� ��� ������ �� ���������� �������
		case "AtillaInHouse":
			dialog.text = "�, ��� � ��, " + GetFullName(pchar) + ". �������, ��� ���� ������.";
			link.l1 = "������, �� ��� � ���� ����? ����� ���-������ ����� � ����� ������� �����?";
			link.l1.go = "AtillaInHouse_1";
		break;
		case "AtillaInHouse_1":
			dialog.text = "�����, " + pchar.name + ", ��� �� �����?.. � �����, ���������� �� ������� �����������. ��� �� ����� ������ �� ����� �����, ��������� ������������.";
			link.l1 = "� ��� �� ��� ������ ��������?";
			link.l1.go = "AtillaInHouse_2";
		break;
		case "AtillaInHouse_2":
			dialog.text = "�������� ����...";
			link.l1 = "��������, � ��� �������� ���-������ ��������?";
			link.l1.go = "AtillaInHouse_3";
		break;
		case "AtillaInHouse_3":
			dialog.text = "��������, ��������. ������, ��� ��������� ������� �� �� ���-�����. �� ������� �� ��� ��������� ���� '������������' �, �� ������, ��� ���� ���� �� ����� �����.";
			link.l1 = "� ����� ��� ���? �� ��� ������� ��...";
			link.l1.go = "AtillaInHouse_4";
		break;
		case "AtillaInHouse_4":
			dialog.text = "�������, ����� �������� ����� � ����, ��������. �� ���� ����� ��������, ���� ��� ������� � ���� ����������.";
			link.l1 = "����, ����� ���� ����� �� ���-�����? � ������ ������ ����������� ���!";
			link.l1.go = "AtillaInHouse_5";
		break;
		case "AtillaInHouse_5":
			dialog.text = "���� ������ ������� �������� ����� - �� ��. ���� ����� �� ���-����� ��� ��� ���� �����. �� ���� ��������, �� ����� � ����� ����� ���� ����� ����������-�����������, �� �����.";
			link.l1 = "������, ��� ���� ���������... ������� ����, ������!";
			link.l1.go = "AtillaInHouse_6";
		break;
		case "AtillaInHouse_6":
			dialog.text = "��������, �� �� ������ ��-�-������� ������ - ���-�� � ����� ����� ������ ���������� � ��� ���������. �� ���� ��� ��������.";
			link.l1 = "���, � ���� �����! ������, � ������ �������. ���� ��� �������� ���������, �� � ����� ���� ���������� �������������.";
			link.l1.go = "AtillaInHouse_7";
		break;
		case "AtillaInHouse_7":
			dialog.text = "������, " + pchar.name + ". ����� ����!";
			link.l1 = "�������, ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AtillaInHouse_Again";
			AddQuestRecord("Romantic_Line", "13");
			pchar.RomanticQuest = "AttackBrig"; //���� ��� ���� �� �������� �����
            Pchar.quest.Romantic_AttackBrig.win_condition.l1 = "location";
            Pchar.quest.Romantic_AttackBrig.win_condition.l1.location = "PortoBello";
            Pchar.quest.Romantic_AttackBrig.win_condition = "Romantic_AttackBrig";
			SetTimerCondition("Romantic_BrigTimeOver", 0, 0, 16, false);
		break;
		case "AtillaInHouse_Again":
			dialog.text = "��, ��� ������?";
			link.l1 = "���� �����...";
			link.l1.go = "exit";
		break;
		// ����� ������ �� ������ ������������, ���� �� ������ ��� ������
		case "Brig_Late":
			dialog.text = "��, �����������, ��� � ���� ����?";
			link.l1 = "���� �������... �� ����� � ������� ���� ����, ���� ����� �� �����...";
			link.l1.go = "Brig_Late_1";
		break;
		case "Brig_Late_1":
			dialog.text = "��, �����... ������, ��� �������� ��� ��� � �����...";
			link.l1 = "��������, �� ����. ��� ������� �� ���� - ������ ����������� �� �����...";
			link.l1.go = "Brig_Late_2";
		break;
		case "Brig_Late_2":
			dialog.text = "������� ���� �� ������, ���� �� ������-�� ���������? ��� ����������� ��� ���� ���������, ���� ���� ������.";
			link.l1 = "�� ����, ������. ������� ���� �� ���������. ������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Last_Talk";
			CloseQuestHeader("Romantic_Line");
			DeleteAttribute(pchar, "RomanticQuest");
		break;
		case "Last_Talk":
			dialog.text = "����� � � ������ ���� ����� � ���� - ���� �� ���-�� ����...";
			link.l1 = "����� ����, ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Last_Talk";
		break;
		// ���� ������ ���� ������ ��� �� ���� �� �����
		case "Brig_DieHard":
			dialog.text = "��, ���, ��������, ����� �������?";
			link.l1 = "������� ������. � ����� ����� ������ � ����, �� ����� ��� �� ������� �� �����...";
			link.l1.go = "Brig_DieHard_1";
		break;
		case "Brig_DieHard_1":
			dialog.text = "�-��, ��� ����� �����. ��������, ����, ��� � ��� � �����...";
			link.l1 = "��������! �� ���� ���������, ��� ��� � ����... �� ���� �� ���� ������ ��� ����...";
			link.l1.go = "Brig_Late_2";
		break;
		// ���� ������ ����, �� ������ ���
		case "Brig_Sunk":
			dialog.text = "��, �����������, ��� � ���� ����?";
			link.l1 = "���� �������... � ����� ����� ������ � ����, �� ����� ��� �� ������� �� ����� - ��� ����� �� ��� �� ����� ���. ����� �� �����...";
			link.l1.go = "Brig_Sunk_1";
		break;
		case "Brig_Sunk_1":
			dialog.text = "�� ��, ��������, ����� ����... �� ����������� ���� - ������� �������, ������� ���� ���������...";
			link.l1 = "�� ���� �� ���� �������� - ������ ����������� �� �����...";
			link.l1.go = "Brig_Late_2";
		break;
		// ���� �������� ������� � ������, ��� ��������
		case "Isabella_Sink":
			dialog.text = "��, �����������, ��� � ���� ����?";
			link.l1 = "���� �������... � ����� ����� ������ � ����, � ���� ��� �� �������.";
			link.l1.go = "Isabella_Sink_1";
		break;
		case "Isabella_Sink_1":
			dialog.text = "���, ����� �������� ��� �� ����?";
			link.l1 = "����, ��� ������ �� �������� ��� ���. � ������� �� � �������� ������� �� ����, ��� ��������� ����� �� ��� ������ � ������. ��� ���, ������...";
			link.l1.go = "Brig_Late_2";
		break;
		// ������ ���-������ ����� � ����������
		case "SalvatorNews":
			dialog.text = "���� � ����? " + GetFullName(pchar) + " ����������� ��������!";
			link.l1 = "����������, ������! ��� ����, ��������?";
			link.l1.go = "SalvatorNews_1";
		break;
		case "SalvatorNews_1":
			dialog.text = "� ���� ��� � �������. ��� � ���� ���� ���������?";
			link.l1 = "� ���������� �������. �� ���� ����� ����������, ������ �� ��������� ��� ���������.";
			link.l1.go = "SalvatorNews_2";
		break;
		case "SalvatorNews_2":
			dialog.text = "�������...";
			link.l1 = "������, �� ��� ������ � ��� �� ������?";
			link.l1.go = "SalvatorNews_3";
		break;
		case "SalvatorNews_3":
			dialog.text = "����������� ����. �������� ������ ����� �� ��������, ������ �� �� ������, �� � ��� ��������. ������ ��� ��������.";
			link.l1 = "��, �� ��... ��� �� �������, ��� ������?";
			link.l1.go = "SalvatorNews_4";
		break;
		case "SalvatorNews_4":
			dialog.text = "���� � ������ � ������ ��� ���.";
			link.l1 = "� ������ � ������?";
			link.l1.go = "SalvatorNews_5";
		break;
		case "SalvatorNews_5":
			dialog.text = "������, ��� ��������� ���� ����������. ��� ���������, ��� � � ��� ������ ��������� ���� ���� �����.";
			link.l1 = "������! � �� ����� � ����� ��������!!!";
			link.l1.go = "SalvatorNews_6";
		break;
		case "SalvatorNews_6":
			dialog.text = "�-�-�, �� ������ �������, ��� ��� ��� ������������. � �� �� ����� ����� ������� ����� �� �����...";
			link.l1 = "� � � �� ����... ������, ������, ������� �� ������!";
			link.l1.go = "exit";
			NextDiag.TempNode = "AtillaInHouse_Again";
			AddQuestRecord("Romantic_Line", "20");
			ChangeCharacterAddress(characterFromId("Isabella"), "none", "");
			QuestSetCurrentNode("Rosita", "BackRosita");
			//�������� � �����
			sld = characterFromId("Isabella");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_Cave_2", "goto", "goto5");
			sld.dialog.currentnode = "IsabellaInCave";
		break;
		//�������� ����� � ������.
		case "IsabellaIsDead":
			dialog.text = "�-�-�, ������� " + GetFullName(pchar) + ". �� ��� ����, ��������?";
			link.l1 = "������, � ������� ��������...";
			link.l1.go = "IsabellaIsDead_1";
		break;
		case "IsabellaIsDead_1":
			dialog.text = "��� ���������?";
			link.l1 = "� ���� ���������� � �� ������ ���� ����������� � ��������� � ���-�����. �� ��������� � ������� �������� ����� �����������, � ��� ����� ��... �� ����� ���������, ����� ��� ��� ���.";
			link.l1.go = "IsabellaIsDead_2";
		break;
		case "IsabellaIsDead_2":
			dialog.text = "�-��, ����������. �� ��� ��������? ���� ���-�� ���� ������...";
			link.l1 = "��, ������, �����...";
			link.l1.go = "exit";
			npchar.LifeDay = 0;
			NextDiag.TempNode = "IsabellaIsDead_after";
			CloseQuestHeader("Romantic_Line");
		break;
		case "IsabellaIsDead_after":
			dialog.text = "��, ������, ��� ��� �����...";
			link.l1 = "�������, ��������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsDead_after";
			npchar.lifeDay = 0;
		break;
		//���� �� ������� � ������
		case "IsabellaIsMyWife":
			dialog.text = "�������, ��������! ��� �����?";
			link.l1 = "����� ���������, ������! ��� �����������! �� ����������� � ���������, ������ � �����.";
			link.l1.go = "IsabellaIsMyWife_1";
			npchar.lifeDay = 0;
		break;
		case "IsabellaIsMyWife_1":
			dialog.text = "���� ����������, ��� ���� �������. � �� ���� ����� ������ �� ����� ������, ���� ������� ������������...";
			link.l1 = "��, ��� �����. �������� ����� ����� ��� �������, ��� � ������ � ����������.";
			link.l1.go = "IsabellaIsMyWife_2";
		break;
		case "IsabellaIsMyWife_2":
			dialog.text = "��, ����� ��� � �����, ��������...";
			link.l1 = "��������, ��, ������. ��, ������...";
			link.l1.go = "exit";
			link.l2 = "������, ��� ����� ����... � ���� ������������� ���� �� ���.";
			link.l2.go = "IsabellaIsMyWife_3";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
			pchar.RomanticQuest.Atilla = "YouAreBaster";
			npchar.LifeDay = 0;
		break;
		case "IsabellaIsMyWife_after":
			dialog.text = "����� ��� " + pchar.name + " ���������. ��� ���� ����� �� ������ �� ���� ���?";
			link.l1 = "������ ����������, ������ ��� ��������, ��������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "IsabellaIsMyWife_after";
		break;
		case "IsabellaIsMyWife_3":
			dialog.text = "�� ��� ������?";
			link.l1 = "�� ���, �� ���� ������, ������� ��� �� ���� �������! �� � ������, � � ��������� ������������ �� ���� �������, ��� �������...";
			link.l1.go = "IsabellaIsMyWife_4";
		break;
		case "IsabellaIsMyWife_4":
			dialog.text = "���, ������������ �� ����, ��������...";
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = "��, ����� ����� ������ �����, ������!";
				link.l1.go = "AddRepa_1";
			}
			if (sti(pchar.money) >= 70000)
			{
				link.l2 = "� ���������� ��� ���� 70 ����� �����.";
				link.l2.go = "AddRepa_2";
			}
			if (sti(pchar.money) >= 150000)
			{
				link.l3 = "���� ���� � ���� ���� ���������� 150 ����� �����.";
				link.l3.go = "AddRepa_3";
			}
			if (sti(pchar.money) >= 300000)
			{
				link.l4 = "���� ���� � ���� ���� ���������� 300 ����� �����.";
				link.l4.go = "AddRepa_4";
			}
		break;
		case "AddRepa_1":
			dialog.text = "������, " + pchar.name + "... �� ��� ��, ������� � �� ����. �������� ����, ��� �������, � ���� �� ������...";
			link.l1 = "�� �� �� ���, ��������! ���� ������...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			ChangeCharacterReputation(pchar, -10);
		break;	
		case "AddRepa_2":
			dialog.text = "��, �������! � ���������� ����, " + GetFullName(pchar) + ".";
			link.l1 = "��� ���������, ������. ���� ������...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -70000);
			pchar.RomanticQuest.Atilla = "YouAreNormal";
			ChangeCharacterReputation(pchar, 5);
		break;	
		case "AddRepa_3":
			dialog.text = "�� ��, �������! ���� � ����� � �� ����������...";
			link.l1 = "������, ��, �����, � �� ����� ����������, ���� ��� ���� ������ ���� ����� ���� �� ����! ���� ������...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -150000);
			pchar.RomanticQuest.Atilla = "YouAreNormal";
			ChangeCharacterReputation(pchar, 15);
		break;
		case "AddRepa_4":
			dialog.text = "��, ���� ���� ����!! ��� � ����� ��������!\n"+
				          "��, �������, ��������, ������� - ��� �������. ����� ������ ���� ������ �����������... �� ���, ��������, � ������ ���� �������, ��������� �����...";
			link.l1 = "�����, ��� ������, ��������! ���� ������...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -300000);
			pchar.RomanticQuest.Atilla = "YouAreGood";
			ChangeCharacterReputation(pchar, 30);
		break;	
	}
}
