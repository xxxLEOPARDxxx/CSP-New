
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
		
		case "First time":							//����� Sinistra
			dialog.text = "�� �� ������ �� ������, "+ GetSexPhrase("�����","�����������") +"?";
			link.l1 = "����� ��������, �����?";
			link.l1.go = "Starshka_1";
			PlayVoice("Kopcapkz\Voices\PDM\Old Woman.wav");
		break;
		
		case "Starshka_1":
			dialog.text = "� �������� ������... �� ��� �� ������?";
			link.l1 = "� �� ������ ������"+ GetSexPhrase("","�") +"... ��� ��� ���� �� ������?";
			link.l1.go = "Starshka_2";
		break;
		
		case "Starshka_2":
			dialog.text = "�, "+ GetSexPhrase("�����","�����������") +", ��� ���� ����� ������ ������... ��� ���� ����� �������... ��� ��� ����, ��� � ��� ��������...";
			link.l1 = "�������, ��������? � �� ��� ����������� ������ ��� ���-������ � ���� ����?";
			link.l1.go = "Starshka_3";
		break;
		
		case "Starshka_3":
			dialog.text = "��-��-��!!! �������! ��� ��� ������! �����! ��, ��� ��� �����. ���, ����� ����, �����... ���, ���, ��� - ��� ��� �������... �����, �������, �� ������� ������... ��� ��� ��� �����... ��-��-��!";
			link.l1 = "�����, � �� ����� ����� ���� ������ ��� ������� ��������... ����� �������.";
			link.l1.go = "Starshka_4";
			NextDiag.TempNode = "Starshka_5";
			DeleteAttribute(npchar, "talker");
		break;
		
		case "Starshka_4":
			SetQuestHeader("PDM_Poteryanoe_Koltso");
			AddQuestRecord("PDM_Poteryanoe_Koltso", "1");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("","�"));
			
			pchar.questTemp.PDM_PK_UznatLichnost = "UznatLichnost";
		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Starshka_5":
			dialog.text = "�� �� ������ �� ������, "+ GetSexPhrase("�����","�����������") +"?";
			link.l1 = "�, ���, �����. � ���� ��� �� "+ GetSexPhrase("�����","�����") +" ���.";
			link.l1.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\Old Woman.wav");
		break;
		
		case "Francheska":
			dialog.text = "��, "+ GetSexPhrase("�����","�������") +"? � ���������. ������, �� � ����� ���������, � �� ���������� ��� � ����� ������������ � ������� ��������? (��������) � ��������...";
			link.l1 = "����... � ���"+ GetSexPhrase("","��") +" ��. ��, � �����, ������ �� ���������� ��� � ���� ������.";
			link.l1.go = "SrazuProKoltso";
			link.l2 = "��, � ������ ���� ������������ � ���� ������������. �����, ��� ������� ���� ����������, ���������. � ����� ������� ���� �������. �������� ����� ��� �������� ������ ����...";
			link.l2.go = "Istoria";
			PlayVoice("Kopcapkz\Voices\PDM\Francesca.wav");
			pchar.questTemp.PDM_PK_UvestiNaVerh = "UvestiNaVerh";
		break;
		
		case "SrazuProKoltso":
			dialog.text = "����� ������? ��� � ���� ������� �����! �����, �����!";
			link.l1 = "������, � �����.";
			link.l1.go = "exit";
			link.l2 = "��� ��� ������, � �� �� � ��������� ��� ����������� ������ ���� �������!";
			link.l2.go = "Krik";
			link.l3 = "�����, ��� ������ ��� ����� ��� ������ �������, �������...";
			link.l3.go = "Krik";
			NextDiag.TempNode = "Uhodi";
		break;
		
		case "Krik":
			dialog.text = "Aaaaaaaaaaaa!!!! (������� ����)";
			link.l1 = "������! ������! ������ ������ ��������... ������, � �����.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);
		break;
		
		case "Uhodi":
			dialog.text = "������ �� ������? ��� � ���� ������� �����! ����� �����, �����!";
			link.l1 = "������, � �����.";
			link.l1.go = "exit";
			link.l2 = "� ���"+ GetSexPhrase("","��") +" �� ������ � ���� ������.";
			link.l2.go = "Kupit_Posle";
		break;

		case "Kupit_Posle":
			dialog.text = "�������� ����� ���������! � �� �������� ������!";
			link.l1 = "��� - (���� �� ��������).";
			link.l1.go = "Kupit_20";
			link.l2 = "��� - (���� �� �������� �����).";
			link.l2.go = "Kupit_20000";
			link.l3 = "��� - (���� �� �������� ���������).";
			link.l3.go = "Kupit_20000000";
			link.l4 = "��������, � ���� ������ ��� ��� ���� ����� ����� - �� � ������� �� ���� �������..";
			link.l4.go = "exit";
		break;
		
		case "Istoria":
			dialog.text = "��� �������� �������! �������� ������� ��� �� ��������, "+ GetSexPhrase("�����","�����") +". ����� �������� ��� ���-������ �������!";
			link.l1 = "���, ���������, ������� � ������� ���. �� �������, ��� � ��� ������"+ GetSexPhrase("","�") +", �������� ������ ����, � ����� ������ �������� � ��� ������, ��� ����� � ���. ��� �������� ������ �������� �� ������ ���� �������. � ��� � ���� ������� ��� ����������, ��� �������� ���� ��������... ������ ��������, � �� ����. ��� �� �������� ������� �� ��� ����. � �����, ��� ��� ������������ ��������...";
			link.l1.go = "Istoria_2";
		break;
		
		case "Istoria_2":
			dialog.text = "(������) ��� ���������� ��� ��� ����! ��� ���� ������ ������ ���� � ��������� �������� - � ���� ����� ��������� (������). � ��� ��� �� ��������? �, ��������� ����! ��������! ��� ��� ��� �� ��������?";
			link.l1 = "��� ���� ������. �� ���� ������, ������ ����� ������������ ��� ���������.";
			link.l1.go = "Istoria_3";
		break;
		
		case "Istoria_3":
			dialog.text = "��! ��������, � ���� ���� ���� ������. �����, ��� ���������? ��� ��� ��� ������, ������� �������. ���. �����, ��� ��������� ������?";
			link.l1 = "�, ����! ����������! ��� �� ����� ������, ������� �������� �������! ������, ������� ����� � ������ � ��������� ����! ���� �� ������ ��� ������, � ������ ��� �������.";
			link.l1.go = "Volshebnoe";
			link.l2 = "��� ��, ���, ������� ���, ���������. ������� ����, ��� ��� ����� ������������ ������. �� ������, ���������, � ���"+ GetSexPhrase("","��") +" �� ������ � ���� ��� ������. �������?";
			link.l2.go = "Obichnoe";
		break;
		
		case "Obichnoe":
			dialog.text = "� �� ���� ������ ������� ��������. ���, ������ ���.";
			link.l1 = "�������. �� ����� ������� �������, ���������! � ������ ����, ��� � ���� ���������� ���� � ������� � �������� ���� ������� ������� � ���� ������������. � ������ ��� ���� ����.";
			link.l1.go = "Pomenyt";
			Log_SetStringToLog("��������� + 2");
			Log_SetStringToLog("���������� + 2");
			AddCharacterSkill(pchar, "Leadership", 2);
			AddCharacterSkill(pchar, "Sneak", 2);
			ChangeCharacterReputation(pchar, 2);
			sld = CharacterFromID("PDM_PK_Francheska")
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			DeleteAttribute(pchar, "questTemp.PDM_PK_UvestiNaVerh");
			GiveItem2Character(PChar, "PDM_PK_Koltso");
			AddQuestRecord("PDM_Poteryanoe_Koltso", "4");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("","�"));
		break;
		
		case "Volshebnoe":
			dialog.text = "��� ������? �� ��� ��������� ������! ��� � ���� ��� ���� ������?";
			link.l1 = "��� ������ ����������� ����� ������ ������ �������, ������� �������� ������ ������������� ����, ������ �������, ������� ����� � ��� � ������� ���������� ���� ���� ����. � ��� ������ ������� � ������� ���� �� ����. � ������ ���� ������� ��� ��������� ���������. ���� �������, ����� ����� ��������� ������ ������� ���� �������?";
			link.l1.go = "Kupit";
		break;
		
		case "Kupit":
			dialog.text = "�������� ����� ���������! � �� ������, �� ���������-�� ������! ������ ���������! ��� ������"+ GetSexPhrase("","�") +" ��� �����"+ GetSexPhrase("��","��") +" "+GetFullName(pchar)+", � ����������!";
			link.l1 = "��� - (���� �� ��������).";
			link.l1.go = "Kupit_20";
			link.l2 = "��� - (���� �� �������� �����).";
			link.l2.go = "Kupit_20000";
			link.l3 = "��� - (���� �� �������� ���������).";
			link.l3.go = "Kupit_20000000";
			link.l4 = "��������, � ���� ������ ��� ��� ���� ����� ����� - �� � ������� �� ���� �������..";
			link.l4.go = "exit";
			NextDiag.TempNode = "Popitka_Vtoraya";
		break;
		
		case "Kupit_20":
			dialog.text = "�������� ����� ���������! � ���� ���� �������� ����� ���������!!! ���, ������ ������.";
			link.l1 = "�������. � ������"+ GetSexPhrase("","�") +", ��� ������ �� ������� ������ ������ �����������. �� ��������.";
			link.l1.go = "Pomenyt";
			AddMoneyToCharacter(pchar, -20);
			ChangeCharacterReputation(pchar, 2);
			NextDiag.TempNode = "UNasKoltso";
			
			DeleteAttribute(pchar, "questTemp.PDM_PK_UvestiNaVerh");
			GiveItem2Character(PChar, "PDM_PK_Koltso");
			AddQuestRecord("PDM_Poteryanoe_Koltso", "4");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("","�"));
		break;
		
		case "Kupit_20000":
			if (sti(pchar.Money) >= 20000)
			{		
				dialog.text = "��� ������ ������! ������ ���� ��������!!! Aaaaaaaaaaaa!!!! (������� ����)";
				link.l1 = "������! ������! ������ ������ �����... �����, � �����.";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
				dialog.text = "";
				link.l1 = "��������, � ���� ������ ��� ��� ���� ����� ����� - �� � ������� �� ���� �������..";
				link.l1.go = "exit";
			}
		break;
		
		case "Kupit_20000000":
			if (sti(pchar.Money) >= 20000000)
			{		
				dialog.text = "��� ������ �������! ������ ���� ��������!!! Aaaaaaaaaaaa!!!! (������� ����)";
				link.l1 = "������! ������! ������ ������ �����... �����, � �����.";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
				dialog.text = "";
				link.l1 = "��������, � ���� ������ ��� ��� ���� ����� ����� - �� � ������� �� ���� �������..";
				link.l1.go = "exit";
			}
		break;
		
		case "Popitka_Vtoraya":
			dialog.text = "��, ��� ��. ���������� ��� �������?";
			link.l1 = "���. � ���� ������ ��� ������.";
			link.l1.go = "Popitka_Vtoraya_2";
		break;
		
		case "Popitka_Vtoraya_2":
			dialog.text = "�� ������"+ GetSexPhrase("","��") +" ��� �������� ����� ��������� �� ��������� ������?";
			link.l1 = "��� - (���� �� ��������).";
			link.l1.go = "Kupit_20";
			link.l2 = "��� - (���� �� �������� �����).";
			link.l2.go = "Kupit_20000";
			link.l3 = "��� - (���� �� �������� ���������).";
			link.l3.go = "Kupit_20000000";
			link.l4 = "��������, � ���� ������ ��� ��� ���� ����� ����� - �� � ������� �� ���� �������..";
			link.l4.go = "exit";
		break;
		
		case "UNasKoltso":
			dialog.text = "��, ����"+ GetSexPhrase("�","���") +"! � ���� ���� �������� ����� ���������! ������, ������ ��� � ����??";
			link.l1 = "�������! � �� ���� ���"+ GetSexPhrase("","�") +".";
			link.l1.go = "UNasKoltso_2";
			link.l2 = "���� ������ ���� �� ����������.";
			link.l2.go = "UNasKoltso_3";
		break;
		
		case "UNasKoltso_2":
			dialog.text = "��, ��� ���"+ GetSexPhrase("","�") +" ��! ������ � ����� ������ �����������! � � ��������� ���� � �����!";
			link.l1 = "�������, ���������, �� �� ������.";
			link.l1.go = "exit";
			sld = CharacterFromID("PDM_PK_Francheska")
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
		break;
		
		case "UNasKoltso_3":
			dialog.text = "����� �����! � ���� �� ��������, ��� � ������� �� ������ ��������� �������� ���������!";
			link.l1 = "�� �������, ���������.";
			link.l1.go = "exit";
			sld = CharacterFromID("PDM_PK_Francheska")
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
		break;
		
		case "Pomenyt":
			sld = CharacterFromID("Josephine_Lodet")
			sld.dialog.currentnode   = "Konets";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();  
		break;
		
		case "NaVerhuSFrancheska":
			dialog.text = "�������, �� ���������, �������� ���� ��� ���� �� ��������� ��� ����.";
			link.l1 = "���, ���������, ���� ������ �� ���� �����.";
			link.l1.go = "UbitEE";
			link.l2 = "��� �� ���, ��� �����.";
			link.l2.go = "TrahEE";
			PlayVoice("Kopcapkz\Voices\PDM\Francesca.wav");
			npchar.lifeday = 0;	
		break;
		
		case "TrahEE":
			AddDialogExitQuest("PlaySex_1");
			GiveItem2Character(pchar, "PDM_PK_Koltso");
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("Josephine_Lodet")
			sld.dialog.currentnode   = "Konets";
			sld = CharacterFromID("PDM_PK_Francheska")
			sld.dialog.currentnode   = "PosleTraha";
			
			Log_SetStringToLog("���������� + 3");
			Log_SetStringToLog("������� + 1");
			AddCharacterSkill(pchar, "Sneak", 3);
			AddCharacterSkill(pchar, "Fortune", 1);
			AddCharacterHealth(pchar, 10);
			
			AddQuestRecord("PDM_Poteryanoe_Koltso", "5");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("","�"));
			DialogExit();
		break;
		
		case "PosleTraha":
			dialog.text = "��� �� ������� ���� ���������, "+ GetSexPhrase("���","���") +" "+ GetSexPhrase("������","���������") +".";
			link.l1 = "������, ���������.";
			link.l1.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\Francesca.wav");
			LAi_CharacterDisableDialog(sld);
		break;
		
		case "UbitEE":
			LAi_LocationFightDisable(loadedLocation, false);
			Lai_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PDM_PK_Francheska")
			LAi_SetHP(sld, 20.0, 20.0);
			LAi_SetImmortal(sld, false);
			sld.SaveItemsForDead = true
			RemoveAllCharacterItems(sld, true);
			GiveItem2Character(sld, "PDM_PK_Koltso");
			
			PChar.quest.PDM_PK_Ubita.win_condition.l1 = "item";
			PChar.quest.PDM_PK_Ubita.win_condition.l1.item = "PDM_PK_Koltso";
			PChar.quest.PDM_PK_Ubita.win_condition = "PDM_PK_Ubita";
			
			DialogExit();
		break;
		
		case "Konets":
			dialog.text = "�� �� ������ �� ������, "+ GetSexPhrase("�����","�����������") +"? � �������� ������. ��� ������ ���� ���-�� �����. ��� ��� �������, � � ������ ���� ���������... ������ ��� �������, ��� � �������� ���-�� ���... ���-��, ��� � ������...";
			link.l1 = "��, � ����, ��� �� ��������. � �����"+ GetSexPhrase("","��") +" ��� ���� ������, �����. ��� ����� � ���� ������ ���� - ������� ����� �� ����� �������� � ���� �����-�������. ���, �������� ���� ������.";
			link.l1.go = "Konets_2";
			
			PlayVoice("Kopcapkz\Voices\PDM\Josephine Lodet.wav");	
		break;
		
		case "Konets_2":
			CloseQuestHeader("PDM_Poteryanoe_Koltso");
			TakeItemFromCharacter(pchar, "PDM_PK_Koltso");
			dialog.text = "�� ������... � ����� ��� ������... � ������ ��� ����-��, ��� ������ ��� ��� �������. �� ������ ��� ���������... ��� ���... �...";
			link.l1 = "����� �� ���������, �����. � �����, ��� ���� ����� ����� �������������, � ������, ��� ��� ����� �� ��� �������. �� ��������.";
			link.l1.go = "Nagrada";			
		break;
		
		case "Nagrada":
			Log_SetStringToLog("��������� + 1");
			Log_SetStringToLog("���������� + 1");
			Log_SetStringToLog("��������� + 1");
			AddCharacterSkill(pchar, "Leadership", 1);
			AddCharacterSkill(pchar, "Sneak", 1);
			AddCharacterSkill(pchar, "Leadership", 1);
			ChangeCharacterReputation(pchar, 2);
			sld = CharacterFromID("Josephine_Lodet")
			sld.dialog.filename   = "Common_citizen.c";
			sld.dialog.currentnode   = "First time";
		
			DialogExit(); 
		break;
		
		
	}
}