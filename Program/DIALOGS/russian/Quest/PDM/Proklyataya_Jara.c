
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
			dialog.text = "��, ��! �� ���� ��� ����������! ��-��, ��� ����, "+ GetSexPhrase("������","�������") +"!";
			link.l1 = "���� ����� ������� "+pchar.name+", � � ������������, � �� ��������!";
			link.l1.go = "Mne_Jarko_1";
			PlayVoice("Kopcapkz\Voices\PDM\Hervisse - Town Guard.wav");
		break;
		
		case "Mne_Jarko_1":
			dialog.text = "�, ��������, �������. �� ����� ��� �����. ��� �� ��������� ����.";
			MakeRandomLinkOrderTwo(link,
			"� �������� ���� ���������. ������ ����� ���� ���� �� ������, ��������, �� �����-�� �������. ��� ���� ���� ����������� �� ����� �����?",
			"Mne_Jarko_2",
			
			"���, ����� ������������. �� �������� � ��������� ���������. � ��������� ��� ������ ����������.",
			"exit");
			npchar.dialog.filename   = "Common_Soldier.c";
			npchar.dialog.currentnode   = "First time";
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS");
		break;
		
		case "Mne_Jarko_2":
			dialog.text = "������ �� �������� ���� � ������, ����� �� �������, ������ �� ������... �� ������� �� ����, ���� ������ ����. ������, �� �� ����� �� ������ ����������� ����.";
			link.l1 = "��, ��� ������ �������������... ���� �����, � ���� ������ ��� ���-��?";
			link.l1.go = "Mne_Jarko_3";
		break;
		
		case "Mne_Jarko_3":
			dialog.text = "�, ������� ���, "+ GetSexPhrase("�����","����������") +"! ��, � ��� � ���� ������� ������ - ��� ����� ���� ��������� ������ ����. �������, ��� �� ���������� ���� �� �����, �� �� ��... �� �� ����������� �� �������� ��� ������ ����? � ���� ��� �� ��������� ��� �� ���.";
			MakeRandomLinkOrderTwo(link,
			"� ����, ��� ������ ����� ������ ����... � ������� ��� ������� ����.",
			"Mne_Jarko_4",
			
			"������, �� ����� ������ � ����, ����� ���������� ������� �����. � ������ ����� �� ��� � ������ ������... �� �� ������� ���� �� ���� �����. �� �������.",
			"exit");
			npchar.dialog.filename   = "Common_Soldier.c";
			npchar.dialog.currentnode   = "First time";			
		break;
		
		case "Mne_Jarko_4":
			dialog.text = "������� ���, "+ GetSexPhrase("�����","����������") +"... � � ������ ����� ����� ����. ����� ���, ���������.";
			link.l1 = "�� ������� ��������, ��� � ��� �������.";
			link.l1.go = "Mne_Jarko_5";
			DeleteAttribute(npchar, "talker");
		break;
		
		case "Mne_Jarko_5":
			SetQuestHeader("PDM_Proklyataya_Jara");
			AddQuestRecord("PDM_Proklyataya_Jara", "1");
			DialogExit();
			pchar.questTemp.PDM_PJ_KV = "KupitVino";
			sld = CharacterFromID("PDM_PJ_Strajnik_1")
			sld.Dialog.Filename = "Quest/PDM/Proklyataya_Jara.c";
			sld.dialog.currentnode = "Mne_Jarko_5_EsheRaz";
		break;
		
		case "Mne_Jarko_5_EsheRaz":
			dialog.text = "�� �������� ��� ���� ����?";
			link.l1 = "��� ����, � ������ ����������"+ GetSexPhrase("","�") +" �����. �������"+ GetSexPhrase("��","���") +" �����������������������, ��� �������. �� � ������� � �������, �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Mne_Jarko_5_EsheRaz";
		break;
		
		case "Prines_Vino_1":
			npchar.dialog.filename   = "Common_Soldier.c";
			npchar.dialog.currentnode   = "First time";
			dialog.text = "����������� ��� ��� ���, "+ GetSexPhrase("�����","����������") +" �������! �� �������� ��� ����?";
			link.l1 = "���, ������.";
			link.l1.go = "Prines_Vino_2";
		break;
		
		case "Prines_Vino_2":
			TakeItemFromCharacter(pchar, "PDM_PJ_Vino");
			sld = CharacterFromID("FortFrance_tavernkeeper")
			dialog.text = "� � �� �����, ��� �� ������� ����������� �������� ��� �������. �������, ������� "+pchar.name+". ������� � ������ ��� �� ��� ����?";
			MakeRandomLinkOrderTwo(link,
			"�� �������� ������������ ����� - ��� ���� ������� ������� ��� ��� ����.",
			"Prines_Vino_Drujba_1",
			
			"������ �������. � �������� ���� �� ����� ��������, ��, ������, � ����� ������� ���������� ������ �����, ���� "+sld.name+".",
			"Prines_Vino_Obman_1");
		break;
		
		case "Prines_Vino_Drujba_1":
			dialog.text = "�� ����� ������ �������, "+ GetSexPhrase("�����","����������") +". � ���� ��� ��������� ���, ���� ��� ���-�� �����������.";
			link.l1 = "�������, ������. �� �������.";
			link.l1.go = "A_Eto_eshe_ne_vse";
			ChangeCharacterReputation(pchar, 3);
		break;
		
		case "Prines_Vino_Obman_1":
			dialog.text = "������? ��, �� ��� �� �������� ����� ���������... � ��� ��� ������ ������?";
			MakeRandomLinkOrderTwo(link,
			"���� ��������� �������� �� ���� ������. � ������ �� �����.",
			"Prines_Vino_Obman_2",
			
			"�� ������ �� ��� ���. ����� ������� ��� ��������� ������ ��������.",
			"Prines_Vino_Drujba_1");
		break;
		
		case "Prines_Vino_Obman_2":
			sld = CharacterFromID("FortFrance_tavernkeeper")
			dialog.text = "׸�� ������. ��, �������� ��� ���� "+sld.name+". �����, ������ ������. ��, ��� ����� ������ �� �����, � �� ���� ������������� � ���� ������. �� �������.";
			link.l1 = "�� ��������, ������.";
			link.l1.go = "A_Eto_eshe_ne_vse";
			ChangeCharacterReputation(pchar, -3);
			AddMoneyToCharacter(pchar, 8);
		break;
		
		case "A_Eto_eshe_ne_vse":
			DialogExit();
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			sld.Dialog.Filename = "Quest/PDM/Proklyataya_Jara.c";
			sld.dialog.currentnode = "Ya_Toje_Hochu_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0.5, 0);
		break;
		
		case "Ya_Toje_Hochu_1":
			PlayVoice("Kopcapkz\Voices\PDM\Eustache Heumont.wav");
			dialog.text = "����������� ���, �������, "+ GetSexPhrase("�����","����������") +". ��� ������ ���, "+ GetSexPhrase("�����","����������") +"!";
			link.l1 = "������ �� �� ��� ���� ������ ����, ������? � ��� ��� �� ������� � ��� �� ����������?";
			link.l1.go = "Ya_Toje_Hochu_2";
		break;
		
		case "Ya_Toje_Hochu_2":
			dialog.text = "� ����, "+ GetSexPhrase("�����","����������") +", ��� �� ������ �������. � �����, ��� �� �������� ����� ��������� ������� ����... ������������ ��������, � � ��� ������. � ��� � ����� �������� ���, �������... �� ����� �� �� � ��� ���� ������� ����� ����������? ����������, �������!";
			link.l1 = "���?!? �� ������, ����� � � ��� ����� ����?";
			link.l1.go = "Ya_Toje_Hochu_3";
		break;
		
		case "Ya_Toje_Hochu_3":
			dialog.text = "��� �, ���� �������� ������, "+ GetSexPhrase("�����","����������") +", � �� ������� ��������� ����. �� ��� �������� ���� ��� �� �� ��������, "+ GetSexPhrase("�����","����������") +".";
			MakeRandomLinkOrderTwo(link,
			"��, ��� �� �������� ������������� �����������... ����� ��. ������ ������, � ���"+ GetSexPhrase("","�") +" � �������������� �� ������������ �������������, �� � ����� ��� ����. ��������� ���� �����.",
			"Ya_Toje_Hochu_4",
			
			"��������, ��� ������ ��������� ������ ������� � �����, ��� �� ���������� ���� �� ����������. �������� ����, �����, � ���� � �����, ��� ���-�� �� ������� ���� �� �����, � �������� �� ���� �����������.",
			"Ya_Toje_Hochu_Proval");
		break;
		
		case "Ya_Toje_Hochu_Proval":
			DialogExit();
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			sld.dialog.filename   = "Common_Soldier.c";
			sld.dialog.currentnode   = "First time";
			CloseQuestHeader("PDM_Proklyataya_Jara");
		break;
		
		case "Ya_Toje_Hochu_4":
			dialog.text = "�������,  "+ GetSexPhrase("�����","����������") +". � �� ���� ������ ���� - � �� �����... ������� ��� �������,  "+ GetSexPhrase("�����","����������") +".";
			link.l1 = "� ����� �������.";
			link.l1.go = "Ya_Toje_Hochu_5";
		break;
		
		case "Ya_Toje_Hochu_5":
			DialogExit();
			AddQuestRecord("PDM_Proklyataya_Jara", "3");
			pchar.questTemp.PDM_PJ_KR = "KupitRom";
			sld = CharacterFromID("PDM_PJ_Strajnik_2")
			sld.Dialog.Filename = "Quest/PDM/Proklyataya_Jara.c";
			sld.dialog.currentnode = "Ya_Toje_Hochu_5_EsheRaz";
			LAi_SetGuardianType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		break;
		
		case "Ya_Toje_Hochu_5_EsheRaz":
			dialog.text = "�, �� ��� ���������, �������? ��� ��� ���?";
			link.l1 = "������ �������, �� � �����"+ GetSexPhrase("","�") +" � ����� ��������� ��������. � ����� ������ ����� �� ���.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Ya_Toje_Hochu_5_EsheRaz";
		break;
		
		case "Prines_Rom_1":
			npchar.dialog.filename   = "Common_Soldier.c";
			npchar.dialog.currentnode   = "First time";
			dialog.text = "��, �� ���������, �������? �... ����� ��������, "+ GetSexPhrase("�����","����������") +"... ��... �� �� ����� ����?";
			link.l1 = "���, ��������. �������, ��� ������� ��� ��������� ������� �������� ���������� �������� �������� ��� ����������� �����.";
			link.l1.go = "Prines_Rom_2";
		break;
		
		case "Prines_Rom_2":
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			TakeItemFromCharacter(pchar, "PDM_PJ_Rom");
			dialog.text = "������� �����, "+ GetSexPhrase("�����","����������") +". � ������� ��� ������� �� ���. �� "+ GetSexPhrase("������� � ����������� ����������","������� � ����������� �������") +", �� ��, ��� ��� ���������� �����������. �������� �� ���, ����� � ���� ��� ����� ��������.";
			link.l1 = "������, ������, ��� ����� ��������� �� ����. � ������������ ������ ����, � �� �� ��� ����� ����� ��������� ������� ������� �� ������...";
			link.l1.go = "Prines_Rom_3";
		break;
		
		case "Prines_Rom_3":
			dialog.text = "��� ������, "+ GetSexPhrase("�����","����������") +". � ���� �����������, ������. ������� ���. ����� ��� ��������.";
			link.l1 = "�� �� ���. �� �������.";
			link.l1.go = "Prines_Rom_4";
		break;
		
		case "Prines_Rom_4":
			DialogExit();
			CloseQuestHeader("PDM_Proklyataya_Jara");
			AddQuestRecord("PDM_Proklyataya_Jara", "5");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
	}
}