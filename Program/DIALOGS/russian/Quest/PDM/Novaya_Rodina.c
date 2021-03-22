
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
			dialog.text = "����� �������, ����� �������. �, ���� ������!";
			link.l1 = "���� �� �� ��� ��������� ���� ��� ���?";
			link.l1.go = "Nachalo_1";
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
		break;
			
		case "Nachalo_1":
            dialog.text = "���� ����� �����. ����� ���������. � ����, ��� �� ���� �������. �� ��������� �� �����, ����� ��������� ��� �������?";
            link.l1 = "� �� ������.";
			link.l1.go = "Slushau_1";
			link.l2 = "��, ���, ������-��. � ����� ��� ���-������ ����� �������.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;	
		
		case "Slushau_1":
            dialog.text = "�� ���� ������"+ GetSexPhrase("","��") +", �� ��� ��?";
            if (CheckCharacterItem(Pchar, "patent_spa") || CheckCharacterItem(Pchar, "patent_fra") || CheckCharacterItem(Pchar, "patent_hol") || CheckCharacterItem(Pchar, "patent_eng"))
			{
				link.l1 = "��, � ������"+ GetSexPhrase("","��") +".";
				link.l1.go = "Korsar_1";
			}
			else
			{
				link.l1 = "�� ���, ������ ���� ���������? � "+ GetSexPhrase("��������� �����","��������� �������") +"!";
				link.l1.go = "Nelzya_Pomoch";
			}
		break;

		case "Nelzya_Pomoch":
            dialog.text = "�, ����� �� ��� ����� �� ��������. ����� ���� �����, ������.";
			link.l1 = "�-��, ������������ ������, ������ �������. �� �������.";
			link.l1.go = "exit";
            link.l2 = "��, �� ������, �� ������� ����, �������� ��� ���� �������.";
			link.l2.go = "Istoria_1";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;
		
		case "Istoria_1":
            dialog.text = "�� ������. ���, ������: � ���� ������� ����, ����� ����� ����� ������. ����� � ����� - ���� ��� �������, ���������? � � �� ���� ������ ��������� ����� ������, � ���� ������� ��������, �� ���������� ��� ���� ������ ��������. �� �������� � ���, ��� ��� ������ ����. ��� ����� �������� ����, ���������? �� � �������� ���� �����, "+ GetSexPhrase("������","�������") +".\n"+ 
							"� ����� ������ ���� ��������� �������������, ���������� ��������� � ��������� ���� ����������, �� ��������� ����� ��������� ������, ��� ������ � ������� � ������-���� �����, � � �� ���� ��������� �� �����������, ����� ������� ��� �����������. ��������� ��� �������� ������� ����, ���� � ������� � ��� � �����: � ��� ������ ����� ����, ��� ������ � ������ ���. � �����, ��� � ��� �� ��������� �� ������ � ��������, �� � �� ���� ����� � �� ������� �����, ��� ��� �� ������� �� ��� �����!";
			link.l1 = "��� ����� ����, �����, �� � ����� �� ���� ������ ����. � ����� ���� �����. ���������.";
			link.l1.go = "exit";
			link.l2 = "�� ��� � ���� ���� ������?";
			link.l2.go = "Davai_Pomogu_NET";
			link.l3 = "� ��� ������ ��������?";
			link.l3.go = "Davai_Pomogu_Bratstvo";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;
		
		case "Davai_Pomogu_NET":
            dialog.text = "�� �� ������� ��� ������, "+ GetSexPhrase("������","�������") +". �� ���� �����"+ GetSexPhrase("","��") +", �� ��� ��? ���� ������� �����, ��� ������ �� ������������ � ���������� ������ �� ���������� ����.";
            link.l1 = "������ ���������. ����� �� �������. � ����� ���� �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;
		
		case "Davai_Pomogu_Bratstvo":
            dialog.text = "��������! � �� ����� � ����, � ������� �� �����! ��� ������������� ������� ��������� - �������, ������"+ GetSexPhrase("","�") +"? ������� ��� �������! � ������� �� ������ �������� ����. � ���� ������ �����, "+ GetSexPhrase("������","�������") +", �������� - ��� ����� ���� ����� ���������� ��������, ����������� ������, ����� �������� � ���, ��������� �������, ��� ������.";
            link.l1 = "���. � ����� ������, ��� ��� ������. �� �����, ����� � �����, ��� ������ ������ �� ����� ���� ����������. �� �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;
		
		case "Podhodim_SNOVA_Reactia":
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
			if (CheckCharacterItem(Pchar, "patent_spa"))
			{
				dialog.text = "(���� ���)";
				link.l1 = "������, �����. � ������ "+ GetSexPhrase("��������� ������","��������� ��������") +", ���� � ���� ���-�� ������?";
				link.l1.go = "Ya_Ispania_1";
			}
			else
			{
				dialog.text = "���� �� �� ��������� �����, �� ��� �� � ��� � ����� �������������.";
				link.l1 = "����� ���������.";
				link.l1.go = "exit";
			}
		break;
		
		case "Korsar_1":
			if (CheckCharacterItem(Pchar, "patent_eng"))
			{
				dialog.text = "� ��� � �����. � ��� ����� ������ �� ��������?";
				link.l1 = "� ������ ��� ������ ������.";
				link.l1.go = "Nelzya_Pomoch_Korsar_2";
			}
			if (CheckCharacterItem(Pchar, "patent_fra"))
			{
				dialog.text = "� ��� � �����. � ��� ����� ������ �� ��������?";
				link.l1 = "� ������ ��� ������ �������.";
				link.l1.go = "Nelzya_Pomoch_Korsar_2";
			}
			if (CheckCharacterItem(Pchar, "patent_spa"))
			{
				dialog.text = "� ��� � �����. � ��� ����� ������ �� ��������?";
				link.l1 = "� ������ ��� ������ �������.";
				link.l1.go = "Ya_Ispania_1";
			}
			if (CheckCharacterItem(Pchar, "patent_hol"))
			{
				dialog.text = "� ��� � �����. � ��� ����� ������ �� ��������?";
				link.l1 = "� ������ ��� ������ ���������.";
				link.l1.go = "Nelzya_Pomoch_Korsar_2";
			}
		break;
		
		case "Nelzya_Pomoch_Korsar_2":
            dialog.text = "�, ����� �� ��� ����� �� ��������. ����� ���� �����, ������.";
			link.l1 = "�-��, ������������ ������, ������ �������. �� �������.";
			link.l1.go = "exit";
            link.l2 = "��, �� ������, �� ������� ����, �������� ��� ���� �������.";
			link.l2.go = "Istoria_Korsar_2";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;
		
		case "Istoria_Korsar_2":
            dialog.text = "�� ������. ���, ������: � ���� ������� ����, ����� ����� ����� ������. ����� � ����� - ���� ��� �������, ���������? � � �� ���� ������ ��������� ����� ������, � ���� ������� ��������, �� ���������� ��� ���� ������ ��������. �� �������� � ���, ��� ��� ������ ����. ��� ����� �������� ����, ���������? �� � �������� ���� �����, "+ GetSexPhrase("������","�������") +".\n"+ 
							"� ����� ������ ���� ��������� �������������, ���������� ��������� � ��������� ���� ����������, �� ��������� ����� ��������� ������, ��� ������ � ������� � ������-���� �����, � � �� ���� ��������� �� �����������, ����� ������� ��� �����������. ��������� ��� �������� ������� ����, ���� � ������� � ��� � �����: � ��� ������ ����� ����, ��� ������ � ������ ���. � �����, ��� � ��� �� ��������� �� ������ � ��������, �� � �� ���� ����� � �� ������� �����, ��� ��� �� ������� �� ��� �����!";
			link.l1 = "��� ����� ����, �����, �� � ����� �� ���� ������ ����. � ����� ���� �����. ���������.";
			link.l1.go = "exit";
			link.l2 = "�� ��� � ���� ���� ������?";
			link.l2.go = "Davai_Pomogu_KORSAR_NET_2";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;
		
		case "Davai_Pomogu_KORSAR_NET_2":
            dialog.text = "�� �� ������� ��� ������, "+ GetSexPhrase("������","�������") +". �� ���� ������� ������ �������, �� ��� ��? ���� ������� �����, ��� ������ �� ������������ � ���������� ������ �� ���������� ����.";
            link.l1 = "������ ���������. ����� �� �������. � ����� ���� �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Podhodim_SNOVA_Reactia";
		break;
		
		case "Ya_Ispania_1":
            dialog.text = "�, ��� �� � ���������! �� � ����� ���� ���"+ GetSexPhrase("","��") +" �� ��� ������!";
            link.l1 = "� ��� � ���� ���������?";
			link.l1.go = "Ya_Ispania_2"
		break;
		
		case "Ya_Ispania_2":
            dialog.text = "�� ������. ���, ������: � ���� ������� ����, ����� ����� ����� ������. ����� � ����� - ���� ��� �������, ���������? � � �� ���� ������ ��������� ����� ������, � ���� ������� ��������, �� ���������� ��� ���� ������ ��������. �� �������� � ���, ��� ��� ������ ����. ��� ����� �������� ����, ���������? �� � �������� ���� �����, "+ GetSexPhrase("������","�������") +".\n"+ 
							"� ����� ������ ���� ��������� �������������, ���������� ��������� � ��������� ���� ����������, �� ��������� ����� ��������� ������, ��� ������ � ������� � ������-���� �����, � � �� ���� ��������� �� �����������, ����� ������� ��� �����������. ��������� ��� �������� ������� ����, ���� � ������� � ��� � �����: � ��� ������ ����� ����, ��� ������ � ������ ���. � �����, ��� � ��� �� ��������� �� ������ � ��������, �� � �� ���� ����� � �� ������� �����, ��� ��� �� ������� �� ��� �����!";
            link.l1 = "� ��� ��� ����� �������?";
			link.l1.go = "Ya_Ispania_3";
		break;
		
		case "Ya_Ispania_3":
            dialog.text = "�� ������"+ GetSexPhrase("","��") +", �� ��� ��? �� ������ ����� � ��������� ����, � ������ ����� �� ������ ���� ������ �� ���, ���� ������? ����� �� ������ ��������� �� ���� �������� ����� �������-������������, ��� �� ������, ���? ������ ����� ���, ��� � ����� �� ��������� ������������� �� ������ ����� �������, � ����� ���������� ����� ������� ���.";
            link.l1 = "� ���������� ����, �����, �� � ���� ������ ��� �� ��� �������. �� �������.";
			link.l1.go = "Otkazal";
			link.l2 = "������-�� � ���"+ GetSexPhrase("","��") +" �� ������� ���, ��, ���� �������� ���������, ��� � � ����� ���� �����?";
			link.l2.go = "Ya_Ispania_4";
		break;
		
		case "Otkazal":
            dialog.text = "��� �������, "+ GetSexPhrase("������","�������") +". � ����� ��� ����-������ ��� ���� ������.";
            link.l1 = "�� �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Obida";
		break;
		
		case "Obida":
            dialog.text = "��, "+ GetSexPhrase("��������","�������") +", � ��� �� �����. �� ���� ��� "+ GetSexPhrase("���������","����������") +" ��� ������, � ������� ����� � ���� �� �����������.";
            link.l1 = "��� ���� ��������, �������. ����� ���������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Obida";
		break;
		
		case "Ya_Ispania_4":
            dialog.text = "������, ����� ����! � ���� ��������� ���� 8000 �������. ��� �������?";
            link.l1 = "��� ���� ����������. � ��������. � ������� ���� ��������� ��������� ������������� � ����� �� ������.";
			link.l1.go = "Ya_Ispania_5";
			link.l2 = "��, ������ ����, ������. 8000 ������� �� ����� ������� � ������� ����? �� �����.";
			link.l2.go = "Otkazal";
		break;
		
		case "Ya_Ispania_5":
            dialog.text = "��� ������ �������! ��������� ����� ����, �������. � ���� ��������� ���� ����� ������ ���� �������. ���� �� � ���� ������� �� ��������, ��, ��������, � ��� ���� ��������� �� ����������� ��� ���������� ��������.";
            link.l1 = "�� �������.";
			link.l1.go = "Havana_Cod_1";
			NextDiag.TempNode = "Jugo_PodhodimSnova";
		break;
		
		case "Jugo_PodhodimSnova":
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
            dialog.text = "���, "+pchar.name+" - � ��� �� ��� ��������� �������������, ������� �� ������"+ GetSexPhrase("","�") +" �������� ���?";
            link.l1 = "������ ����, �����, �� � ���� ��� ��� ���.";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_Novaya_Rodina.Patent") && pchar.questTemp.PDM_Novaya_Rodina.Patent == "Patent")
			{
				link.l2 = "� ��, �� ����������! ��� ��������� ������, ��� ���������� ���� �������� ��� � ��� ���������� ��� ����� ������ - ������ � ������ ������� ��������, �������. � ������, � �������, �� � ��� ����� ������ 8000?";
				link.l2.go = "Ya_Ispania_Patent_1";
			}
		break;
		
		case "Havana_Cod_1":
            SetQuestHeader("PDM_Novaya_Rodina");					
			AddQuestRecord("PDM_Novaya_Rodina", "1");							
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","�"));
			pchar.questTemp.PDM_Novaya_Rodina.Guber = "HugoLesopilka";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Ya_Ispania_Patent_1":
            dialog.text = "��� ����������� �������, "+ GetSexPhrase("������","�������") +"! �����������! ��� - ��� ��� ������, � � ��� ����� � ��� �������������. ��� ���������, �� ������"+ GetSexPhrase("","�") +"? � ���������� ������� ������� � ��� �����������!";
            link.l1 = "������, �����.";
			link.l1.go = "Ya_Ispania_Patent_�od_1";
			AddMoneyToCharacter(pchar, 8001);
			TakeItemFromCharacter(pchar, "Patent_Espa_Lesopilka");
			NextDiag.TempNode = "Podhodim_SNOVA_vipemromu";
		break;
		
		case "Ya_Ispania_Patent_�od_1":
			AddQuestRecord("PDM_Novaya_Rodina", "4");							
			AddQuestUserData("PDM_Novaya_Rodina", "sSex", GetSexPhrase("","�"));
			PChar.quest.PDM_HugoSeaHavana.win_condition.l1 = "EnterToSea"
			Pchar.quest.PDM_HugoSeaHavana.win_condition = "PDM_HugoSeaHavana";
			pchar.questTemp.PDM_Novaya_Rodina.Guber = "Lubopitno";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Podhodim_SNOVA_vipemromu":
            dialog.text = "�, "+ GetSexPhrase("������","�������") +"! "+ GetSexPhrase("��������","���������") +" �����, �? ��, � ��� ���� ���� � ���� ���������... ��, ����� ����, ��� � ����� ���� ������ �� ���� � ��� ����� ���, �������!";
            link.l1 = "������� �� ������ �����, �����. � �������� ���� ����������� ��� ����������.";
			link.l1.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
			NextDiag.TempNode = "Podhodim_SNOVA_vipemromu";
		break;
		
		case "Novoe_Zadanie_1":
			PlayVoice("Kopcapkz\Voices\PDM\Timothy - Town Guard.wav");
            dialog.text = "�, ��� ����� ��, ������� "+pchar.name+"! ��� ���� ������!";
            link.l1 = "�, ������ ���������! � ��� ���� ������� �����?";
			link.l1.go = "Novoe_Zadanie_2";
		break;
		
		case "Novoe_Zadanie_2":
            dialog.text = "����� ������, �������. ����� ����, ��� ������ ��������� �������� ������� � ����������� �� ��� ���������, �� � ������� �� ���� ������ ������, � ������ �� ��� ������ ������.\n"+ 
							"��!  ������, "+pchar.name+", � ������������� �� ��, ��� �� ��� ���� ������"+ GetSexPhrase("","�") +", � ���� ���� ��� ���� ������� �����. ������� ������� � ������.\n"+ 
							"� ����, ��� �� ������ �������� ������� �����, ����� ������� �����. ������ ��, "+pchar.name+", ���� �� ���� ������, �-�, ���������, ������������� � �������, ��������� ��... ��, �� ������ ���, ��� ���������� ������ ������, ������� �������� � ����������� ��������, ����� � ������� ����� � ������ ������� ����� � ���������.";
            link.l1 = "� ���?";
			link.l1.go = "Novoe_Zadanie_3";
		break;
		
		case "Novoe_Zadanie_3":
            dialog.text = "���? �� ����, ����� ��������, "+pchar.name+"? �� � ���� ������� ����� ���������!";
            link.l1 = "�-�. � �����"+ GetSexPhrase("","�") +". �...?";
			link.l1.go = "Novoe_Zadanie_4";
		break;
		
		case "Novoe_Zadanie_4":
            dialog.text = "��, ������� ����� �� ����� ����� � ��������� - �� ��� ����� ������: ��������� ������ ����� ���������� � ����������. ��� ���� ������, ��� �� �����, ��� ���� ������ ����� ����� �������� ���� - � ���� ���� ���������� ��������, ���� ��� ����� ������� ������ � ����������, � ������ ��� ���� ��������. �� ������, ��� ������� ����� ��� �� ����� ���������. ��� ����� �������, ������, ����� ��������� �����, ��� ��� �� ���, ����� �������, ������� � ��� ������ ��������, ������� ����� � ��� ��������.";
            link.l1 = "� ������ �� ��� ��� �� ���������?";
			link.l1.go = "Novoe_Zadanie_5";
		break;
		
		case "Novoe_Zadanie_5":
            dialog.text = "�, �� �������, � ��������� ���� � �������, �? ��, "+ GetSexPhrase("������","�������") +": � ���� ������� �� ��������� ����, ����� ��������� ������ ������, �� � � ������� ����, ����� ������ �������. � �� ����� '�������' ���� ������ ������ � ������ ������, � �� ���� � �������. ��� ���, "+ GetSexPhrase("������","�������") +", �� ����, ���� �� ������ ��������� ����� ���!";
            link.l1 = "����. ������ ��, � �����, ����� ����� ��������� �� ����. �� ����� �� ����� � ��������, ��������? ��, ������� �� �����, �����. �� ��������!";
			link.l1.go = "Novoe_Zadanie_Cod_1";
			NextDiag.TempNode = "Novoe_Zadanie_PodhodimSnova_1";
		break;
		
		case "Novoe_Zadanie_Cod_1":
			CloseQuestHeader("PDM_Novaya_Rodina");
			SetQuestHeader("PDM_Zoloto_ne_tonet");
			AddQuestRecord("PDM_Zoloto_ne_tonet", "1");							
			AddQuestUserData("PDM_Zoloto_ne_tonet", "sSex", GetSexPhrase("","�"));
			
			int Rank = sti(pchar.rank) - 3 + MOD_SKILL_ENEMY_RATE;
			if (Rank < 1) Rank = 1;
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Lesopilka_Galeon", "off_eng_1", "man", "man", Rank, ENGLAND, -1, true));
			FantomMakeCoolSailor(sld, SHIP_GALEON_H, "����������", CANNON_TYPE_CANNON_LBS32, 20, 20, 50);
			FantomMakeCoolFighter(sld, Rank, 55, 55, "blade22", "pistol2", 120);
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "EnergyPlus");
			sld.equip.blade = "blade22";
			sld.equip.gun = "pistol2";
			AddItems(sld, "bullet", 10);
			AddItems(sld, "GunPowder", 10);
			EquipCharacterByItem(Pchar, "cirass1");
			AddCharacterGoodsSimple(sld, GOOD_GOLD, 500 + rand(100));
			AddCharacterGoodsSimple(sld, GOOD_SILVER, 400 + rand(400));
			AddCharacterGoodsSimple(sld, GOOD_WEAPON, 500);
			SetShipSkill(sld, 100, 80, 80, 80, 80, 80, 80, 80, 80);
			sld.ship.Crew.Morale = 100;
			sld.ship.masts.mast4 = 1;
			sld.ship.masts.mast3 = 1;
			sld.ship.masts.mast1 = 1;
			sld.ship.HP = sti(sld.ship.HP) / 3.5;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("PDM_HUGO_GAL");
			Group_SetType("PDM_HUGO_GAL", "war");
			Group_AddCharacter("PDM_HUGO_GAL", "PDM_Lesopilka_Galeon");
			
			Group_SetGroupCommander("PDM_HUGO_GAL", "PDM_Lesopilka_Galeon");
			Group_SetTaskAttack("PDM_HUGO_GAL", PLAYER_GROUP);
			Group_SetAddress("PDM_HUGO_GAL", "Dominica", "quest_ships", "Quest_ship_2");
			Group_LockTask("PDM_HUGO_GAL");
			
			SetTimerCondition("PDM_Lesopilka_Vremy", 0, 0, 30, false);
			
			PChar.quest.PDM_Lesopilka_SJ.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_Lesopilka_SJ.win_condition.l1.character = "PDM_Lesopilka_Galeon";
			PChar.quest.PDM_Lesopilka_SJ.win_condition = "PDM_Lesopilka_SJ";
			
			PChar.quest.PDM_Lesopilka_SJNashel.win_condition.l1 = "item";
			PChar.quest.PDM_Lesopilka_SJNashel.win_condition.l1.item = "PDM_SJ_Angl_Gal";
			PChar.quest.PDM_Lesopilka_SJNashel.win_condition = "PDM_Lesopilka_SJNashel";
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Novoe_Zadanie_PodhodimSnova_1":
            dialog.text = "�! �� ������� �� ������ �� ����, "+pchar.name+"?";
            link.l1 = "�� ������, �����. �� �������!";
			link.l1.go = "Novoe_Zadanie_PodhodimSnova_2";
			PlayVoice("Kopcapkz\Voices\PDM\Hugo Lumbermill.wav");
		break;
		
		case "Novoe_Zadanie_PodhodimSnova_2":
            dialog.text = "����� ���� �� �� ������� ��� �����, "+ GetSexPhrase("������","�������") +"? ��� � ������ ���� ������, ���� �� �� �����!";
            link.l1 = "�� ����, �����. � �����. ������!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Novoe_Zadanie_PodhodimSnova_1";
		break;
		
		case "Novoe_Zadanie_ZaIspaniu":
            dialog.text = LinkRandPhrase("�� ������!", "�� �������!", "�� ������ ��������!");
            link.l1 = LinkRandPhrase("��� �������, ������!", "�������!", "������!");
			link.l1.go = "exit";
			NextDiag.TempNode = "Novoe_Zadanie_ZaIspaniu";
		break;
		
		case "Final_1":
            dialog.text = "��, "+ GetSexPhrase("������","�������")+", � ����, ��� � ���� �� ���������!";
            link.l1 = "�������, �����. ��� ��� ��������� � ���������"+ GetSexPhrase("","�")+" ������ ��������� ����.";
			link.l1.go = "Final_2";
			PlayVoice("Kopcapkz\Voices\PDM\William Shakesbeer.wav");
		break;
		
		case "Final_2":
			dialog.text = "...";
			if (sti(pchar.Money) >= 15000)
			{
				link.l1 = "� � �������"+ GetSexPhrase("","�")+", ��� �� �������� ��� 15000 �������.";
				link.l1.go = "Final_3";
				link.l2 = "�����, �����, � ���� ���� ����. �� �������.";
				link.l2.go = "FinalPL_3";
				NextDiag.TempNode = "Final_Again";
			}
			else
			{
				link.l2 = "�����, �����, � ���� ���� ����. �� �������.";
				link.l2.go = "FinalPL_3";
				NextDiag.TempNode = "Final_Again";
			}
		break;
		
		case "Final_3":
            dialog.text = "�-�-�! "+ GetSexPhrase("������","�������")+", �� ����� ����"+ GetSexPhrase("","�")+" �� ���, ������� � ������ ��� ������! �����, ����� ������?";
            link.l1 = "������, �����, � ���� ���� ������������� ����, ����� ���� � ������ ���. �����!";
			link.l1.go = "Final_4";
			ChangeCharacterReputation(pchar, 8);
			NextDiag.TempNode = "Final_Again";
			AddMoneyToCharacter(pchar, -15000);
		break;
		
		case "Final_4":
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Isp_sekr_guber", "trader_16", "man", "man", 10, SPAIN, -1, false));
			LAi_SetImmortal(sld, true);
			sld.name = "����������";
			sld.lastname = "�������";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Havana_town", "reload", "reload3_back");
			sld.lifeday = 0;
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "First time";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "FinalPL_3":
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Isp_sekr_guber", "trader_16", "man", "man", 10, SPAIN, -1, false));
			LAi_SetImmortal(sld, true);
			sld.name = "����������";
			sld.lastname = "�������";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Havana_town", "reload", "reload3_back");
			sld.lifeday = 0;
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "First time";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
            sld = CharacterFromID("Hugo_Lesopilka")
			sld.lifeday = 0;
			ChangeCharacterReputation(pchar, -8);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Final_Again":
            dialog.text = "�! �� ������� �� ������ �� ����, "+pchar.name+"?";
            link.l1 = "������, �����, � ���� ���� ������������� ����, ����� ���� � ������ ���. �����!";
			link.l1.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\William Shakesbeer.wav");
			NextDiag.TempNode = "Final_Again";
		break;
		
		
	}
}