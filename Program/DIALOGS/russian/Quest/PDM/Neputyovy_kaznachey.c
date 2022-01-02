
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int Plata1 = 14000 * MOD_SKILL_ENEMY_RATE * 0.21;
	int Plata2 = 14000 * MOD_SKILL_ENEMY_RATE * 0.31;
	
	pchar.PDM_NK_Plata2.Money = 14000 * MOD_SKILL_ENEMY_RATE * 0.31;
	
	int Sila = 25 + MOD_SKILL_ENEMY_RATE * 2.8;
	int DopHP = 40 + MOD_SKILL_ENEMY_RATE * 10;
	int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE * 0.9;
	if (Rank < 1) Rank = 1;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":							//����� Sinistra
			dialog.text = "�-��� ��?";
			link.l1 = "������� "+pchar.name+". � ��?";
			link.l1.go = "Fickler_1";
			PlayVoice("Kopcapkz\Voices\PDM\Andreas Fickler.wav");
			DeleteAttribute(npchar, "talker");
		break;
		
		case "Fickler_1":
			dialog.text = "�-�-������� ������, �-� ����� �������.";
			link.l1 = "�� ���� ���� ��������, ��������?";
			link.l1.go = "Fickler_2";
		break;
		
		case "Fickler_2":
			dialog.text = "�-�-�� ���� �-�-�������� ��, ���� �� �-���-������ ��������� ��� �����!";
			link.l1 = "���-�� ����� ���� �����?";
			link.l1.go = "Fickler_3";
		break;
		
		case "Fickler_3":
			dialog.text = "�-��, "+ GetSexPhrase("������","������") +". � �� ���� �����. � �-���� ������. � ��� �� ��-�� ����� �-���������� ������!";
			link.l1 = "������, ��� ���������� �������. ����� ��� ���� ����, ��������.";
			link.l1.go = "Fickler_4";
		break;
		
		case "Fickler_4":
			dialog.text = "��, �-�����, � ���� ��� �-��������. � ��������... � �-��� ��������� �� ��������� '������� �����'. ��� �-�-������� ������� ������� ����� �-������ - ���� � ��������� ��� ����� �� ������! ��� �-�������� ������� ��������� ������� � ���-���������� ������. �� ���, � �������. � ���� �� ����� ���������� �������� ���-�� ��������� �� �����������. � �-�������, ����� ����� �� ����� �-�� ���, �� ���� ����������� ������ ���� ������ ����� �� ������� � ������� �... �...";
			link.l1 = "������� ������?";
			link.l1.go = "Fickler_5";
		break;
		
		case "Fickler_5":
			dialog.text = "�-��... � ����� ������ �... � ���������� �-�������� � ��. ������ � ����, ��������� � ��������� �������. ���-�-����� �������� �����, �� ���� ���� ��� ��� �-�������. � �-������� ������, ��� � �� ������ �� ��������! ������ �� � �������, �������� ���� ����� �����. �� � �-�����, ��� �� �� ����������� �-��������. � �-����� �� ������� ���� �-������ � ����� ���� ����� �����, �� �������!";
			link.l1 = "������������� �������� �������. �� ��������, �������. � ������ ����.";
			link.l1.go = "Fickler_6";
			link.l2 = "��, � ������� ���� ���������� � �������. �����, ��������� ���� ������� ��������� ���������� �����. ������.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Fickler_8";
		break;
		
		case "Fickler_6":
			dialog.text = "�-�-���?";
			link.l1 = "�� ����. ���-������ ��������. ��� ���� �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Fickler_7";
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_NK_Viktor", "officer_52", "man", "man", 10, PIRATE, -1, false));
			sld.name = "������";
			sld.lastname = "������";
			sld.city = "Villemstad";
			sld.location	= "Villemstad_tavern";
			sld.location.group = "sit";
			sld.location.locator = "sit12";
			LAi_SetSitType(sld);
			sld.dialog.filename   = "Quest/PDM/Neputyovy_kaznachey.c";
			sld.dialog.currentnode   = "Viktor";
			
			SetQuestHeader("PDM_Neputyovy_kaznachey");
			AddQuestRecord("PDM_Neputyovy_kaznachey", "1");
		break;
		
		case "Fickler_7":
			PlayVoice("Kopcapkz\Voices\PDM\Andreas Fickler.wav");
			dialog.text = "������� ������! �, ��� ��, ��... �� �-���-���-���� ���� �� ����������. �-�-�� ������ �-�-������?");
			link.l1 = "��� ����. �� �� �������� - � ���������� � ��.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Fickler_7";
		break;
		
		case "Fickler_8":
			PlayVoice("Kopcapkz\Voices\PDM\Andreas Fickler.wav");
			dialog.text = "���! ������! ��������� �� ���� ��������! �... ��� ��. �� ��� �, ����� �� ���� �����...";
			link.l1 = "�� ��������, �������. � ���������� � ��.";
			link.l1.go = "Fickler_6";
			link.l2 = "�����, ��������� ���� ������� ��������� ���������� �����. ������.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Fickler_8";
		break;
		
		case "Viktor":
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
			dialog.text = "��! ��, ��! �� �� ����� ����� ���������, ����������� �������� �� ����� �������? �� ������� � ���, ��� � �� ����! �������! � ���� ���! �� ������� ����!";
			link.l1 = "���-���-���. �� - ������ ������.";
			link.l1.go = "Viktor_2";
		break;
		
		case "Viktor_2":
			dialog.text = "��, � ������. � ���� ������� �� ������ �������� ����� ������� ����� ��������� ��������� � �������! � ����� � ���� ���� ������!";
			link.l1 = "���������, ��������. ������� ��� ���� �������.";
			link.l1.go = "Viktor_3";
		break;
		
		case "Viktor_3":
			dialog.text = "����? ��� ����� �������? �� ��� �� "+ GetSexPhrase("�����","�����") +"?";
			link.l1 = "� - ������� "+pchar.name+". � ���� �� ������� ���� �� ������� �� ��� ������, �� � ����� � ������ �������� ������ �������.";
			link.l1.go = "Viktor_4";
		break;
		
		case "Viktor_4":
			dialog.text = ""+ GetSexPhrase("��������� �����","��������� �������") +"! ��� �� ���� ���������"+ GetSexPhrase("","�") +"? ���� ������ � ���� ���� �� ���� ����������� �������? ��� ���������� ������� ��������� ��� � ����, ��� � �� ����! ��� �� ��������������?";
			link.l1 = "�� ��������� ����� ������ ��������, � ��� �������� � ��������������? � �� �����, ��� ���������� �������� �������� � �������� ��������� ��������, ������������� �� ��� �����.";
			link.l1.go = "Viktor_5";
		break;
		
		case "Viktor_5":
			dialog.text = "���������? ��-�� ����� ������ � ������� ���� �����! " + Plata1 + " �������! ���� �� ������! � �����, ���� �� ���������!";
			link.l1 = "" + Plata1 + " �������? � ��-�� ����� �� ������ ���? ���. � �������� ���� �����, ������ ������ �������� � �����.";
			link.l1.go = "Zaplati";
			link.l2 = "�� ����� � ���� ��������� �� ������ �������, ��� ��� �������� � �����.";
			link.l2.go = "Viktor_Bitva";
			link.l3 = "" + Plata1 + "? � ��-�� ����� �� ������ ���? � ������� ���� ��� " + Plata1 + ". �� ����� - ���� ���� ����� ������� ��������� ��� ������ � ������, ��� ��� �� ������ �������� � �������!";
			link.l3.go = "Zaplati";
			NextDiag.TempNode = "Viktor_VernulsyDengi";
		break;
		
		case "Zaplati":
			dialog.text = "� ������ " + Plata1 + "? ���, � ������! �� ������� ����, " + Plata2 + "!";
			link.l1 = "���, ����� ���� ������. ��������� �������������������, ������.";
			link.l1.go = "Zaplati_2";
			link.l2 = "�� �� ��������, ������! �� ����� � ���� ��������� �� ������ �������, ��� ��� �������� � �����.";
			link.l2.go = "Viktor_Bitva";
			link.l3 = "� ������� ���� ��� " + Plata2 + ". �� ����� - ���� ���� ����� ������� ��������� ��� ������ � ������, ��� ��� �� ������ �������� � �������!";
			link.l3.go = "exit";
			NextDiag.TempNode = "Viktor_VernulsyDengi";
			AddQuestRecord("PDM_Neputyovy_kaznachey", "2");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sMoney", FindRussianMoneyString(sti(pchar.PDM_NK_Plata2.Money)));
		break;
		
		case "Zaplati_2":
			if (sti(pchar.Money) >= Plata2)
			{		
				AddMoneyToCharacter(pchar, -sti(Plata2));
				Log_SetStringToLog("��������� + 1");
				Log_SetStringToLog("�������� + 2");
				Log_SetStringToLog("���������� + 1");
				AddCharacterSkill(pchar, "Leadership", 1);
				AddCharacterSkill(pchar, "Commerce", 2);
				AddCharacterSkill(pchar, "Sneak", 1);
				sld = CharacterFromID("PDM_NK_Viktor")
				sld.dialog.filename   = "Quest/PDM/Neputyovy_kaznachey.c";
				sld.dialog.currentnode   = "Viktor_Poka";
				sld.lifeday = 0;
				sld = CharacterFromID("Andreas_Fickler")
				sld.dialog.filename   = "Quest/PDM/Neputyovy_kaznachey.c";
				sld.dialog.currentnode   = "Fickler_11";
				AddQuestRecord("PDM_Neputyovy_kaznachey", "3");
				AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("","�"));
				DialogExit();
			}
			else
			{
				dialog.text = "";
				link.l1 = "������ � ���� ��� ����� �����, ������, �� � ����� ����� � ������� �� ��������.";
				link.l1.go = "exit";
			}
		break;
		
		case "Viktor_Poka":
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
			dialog.text = "����� ���� ��������! ��� ��� ���� �����?";
			link.l1 = "������. ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Viktor_Poka";
		break;
		
		case "Viktor_VernulsyDengi":
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
			dialog.text = "����� ��? ���� ���� �����?";
			link.l1 = "� ������ ���� ������������ �� ������ ������� ��������, ��������.";
			link.l1.go = "Viktor_VernulsyDengi_2";
		break;
		
		case "Viktor_VernulsyDengi_2":
			dialog.text = "�� ����"+ GetSexPhrase("��","����") +" ������?";
			link.l1 = "" + Plata2 + " �������. ���, �����.";
			link.l1.go = "Zaplati_2";
			link.l2 = "��� ���, �� � ����� ������� �� ����.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Viktor_VernulsyDengi";
		break;
		
		case "Viktor_Bitva":
			dialog.text = "�� ��������� �� ���� ������, �����������!";
			link.l1 = "������ ���� - � ����!";
			link.l1.go = "fight_right_now";
			sld = CharacterFromID("PDM_NK_Viktor")
			if (MOD_SKILL_ENEMY_RATE >= 1 && MOD_SKILL_ENEMY_RATE <= 3) sld.equip.blade = "blade3";
			if (MOD_SKILL_ENEMY_RATE >= 4 && MOD_SKILL_ENEMY_RATE <= 6) sld.equip.blade = "blade18";
			if (MOD_SKILL_ENEMY_RATE >= 7 && MOD_SKILL_ENEMY_RATE <= 10) sld.equip.blade = "blade39";
			if (MOD_SKILL_ENEMY_RATE <= 6) FantomMakeCoolFighter(sld, Rank, Sila, Sila, "", "Pistol1", DopHP);
			if (MOD_SKILL_ENEMY_RATE >= 7) FantomMakeCoolFighter(sld, Rank, Sila, Sila, "", "Pistol2", DopHP);
			sld.SaveItemsForDead = true;
			AddMoneyToCharacter(sld, 15000);
			GiveItem2Character(sld, "Litsenzia");
			
			PChar.quest.PDM_NK_Viktor.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_NK_Viktor.win_condition.l1.character = "PDM_NK_Viktor";
			PChar.quest.PDM_NK_Viktor.win_condition = "PDM_NK_Viktor";
			
			PChar.quest.PDM_NK_Litsenzia.win_condition.l1 = "item";
			PChar.quest.PDM_NK_Litsenzia.win_condition.l1.item = "Litsenzia";
			PChar.quest.PDM_NK_Litsenzia.win_condition = "PDM_NK_Litsenzia";
		break;
		
		case "fight_right_now":
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fickler_11":
			PlayVoice("Kopcapkz\Voices\PDM\Andreas Fickler.wav");
			dialog.text = "�-�-������� "+pchar.name+"! ��, ��� ��, "+ GetSexPhrase("������","������") +"! �� �-�������� ����. �� ��� �������� � �-��������?");
			link.l1 = "��. �� ������ �� ������ ����. ������ �������� ������������ �� ���� '������� �����'.";
			link.l1.go = "Fickler_12";
		break;
		
		case "Fickler_12":
			dialog.text = "�������! �-������ ��� �-�-�������! �-�� ������ ��� �����! �� � �� ���� ��������� �� ���� �������. � ����� �-�-���������� ��� �������. � ��� �������� �� ��, ��� � ������� �-�������� � ������������ ������. � �� ���� �� ��������� ������� ������������ �� '������� �����'. �-�... �����, ��� �� ���������� �-�-��������, �������?");
			link.l1 = "�����, ���������� ��. �� �����. �� ������ ������ ������� � �����-������!";
			link.l1.go = "Fickler_13";
			link.l2 = "������, �� ��� ������ �������� �� �����.";
			link.l2.go = "Fickler_NeNujen";
		break;
		
		case "Fickler_13":
			dialog.text = "�������, �-�������! �� �� �-�-��������� �� ����!");
			link.l1 = "����� ���������� �� ����, �������.";
			link.l1.go = "Fickler_Nanyat";
			sld = CharacterFromID("Andreas_Fickler")
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			ChangeCharacterReputation(sld, 80);
			sld.rank = 10;
			SetSPECIAL(sld, 4, 6, 4, 10, 10, 7, 6);
			SetSelfSkill(sld, 5, 5, 5, 5, 5);
			SetShipSkill(sld, 30, 60, 5, 5, 5, 5, 5, 5, 30);
			sld.loyality = MAX_LOYALITY;
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			sld.greeting = "GR_Andreas_Fickler";
			LAi_SetImmortal(sld, false);
			sld.HalfImmortal = true;
		break;
		
		case "Fickler_NeNujen":
			AddQuestRecord("PDM_Neputyovy_kaznachey", "6");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("��","���"));
			CloseQuestHeader("PDM_Neputyovy_kaznachey");
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			DialogExit(); 
		break;
		
		case "Fickler_Nanyat":
			sld = CharacterFromID("Andreas_Fickler")
			SetCharacterRemovable(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PDM_NK_NaKorabl", 5);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("PDM_Neputyovy_kaznachey", "5");
			AddQuestUserData("PDM_Neputyovy_kaznachey", "sSex", GetSexPhrase("��","���"));
			CloseQuestHeader("PDM_Neputyovy_kaznachey");
			DialogExit(); 
		break;
		
	}
}