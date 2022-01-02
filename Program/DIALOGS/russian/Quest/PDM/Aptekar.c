
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int i, iOfficer;
	string attrL, offtype;
	ref chref;
	
	attrL = Dialog.CurrentNode;

	if(HasSubStr(attrL, "OfficerConfusedSel_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.OfficerToHealConfuse = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // ����� � �����
		Dialog.CurrentNode = "OfficerConfused";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":							//����� Sinistra
			dialog.text = "(������� �����, ���� ����������� � ����� � ������������� �������, � ������) �-�-�... �-�-�... �-�-�...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.PDM_Apt_Markus_v_krovi = "PDM_Apt_Markus_v_krovi";
			NextDiag.TempNode = "Markus_v_krovi";
			
			SetQuestHeader("PDM_Aptekar");
			AddQuestRecord("PDM_Aptekar", "1");
		break;
		
		case "Markus_v_krovi":
			dialog.text = LinkRandPhrase("�-�-�...", "�-�-�-�...", "�-�-�...");
			link.l1 = "...";
			link.l1.go = "exit";
		break;	
		
		case "Alumnus_FT":
			dialog.text = "����������� ���, � ������ ������� � ��������. �� ��� �������. � ��� ����� ���, "+ GetSexPhrase("������� �������","�������") +"?";
			link.l1 = "������ ����� ���� "+pchar.name+", ������� "+pchar.name+". ������ �������, � ������"+ GetSexPhrase("","�") +", ��� ��� ������� �������� ���� �����������, ����� ��� ������ ������� ���������� ������ �. ��� �� ���?";
			link.l1.go = "Alumnus_1";
		break;
		
		case "Alumnus_1":
			dialog.text = "�, ��. �������� ����������� ������. ������ ������� �������� �������. ������ �� ������ ������ � ��������� ��� ��������, ��� �������� ������ �������� ���������� ��������� ������� � ����� ���������� ���� � ����. � ������ ������� ������ ����������, ��� ������ ���������� �� �� ���������� ���������, � �� ���������� ���������������� ��������� � ������� ������ ��������. � �� �� ����� ������� �������, ��� ������ ���������� �� ������� ������� �� ���������, ��� ������� ��� ����� �������...";
			link.l1 = "��. ����� ��������, ������, �� � ���� ��� ������� ����������� ����, ����������, ������������� �����������. ������� ��� ������. ��� �������� �������� ��� ������ � ��������� ����� ����� ��� ���� � ����. �� �� �������� � �������� � ��� ���� ������ �����. ��� � ����"+ GetSexPhrase("��","��") +" ������� � ���?";
			link.l1.go = "Alumnus_2";
		break;
		
		case "Alumnus_2":
			dialog.text = "�, ���������� ������. ���� ������� ������ �������� �� ����������� ���������� ����� ������������. ��� �� ������� ���� � ����� - ���, ����������, ��� ����������, ������� ������ ������������� - �������� ���������, ��� ��������� �� ����������� � ����� ������� �������� ���������� �������� ����. ���� ��� ���� ���������� �� ����������� ��� ��� �����. ������ ��������, ��� � ����� �� �������� �������� � �����, ������ �������� ������ ��������. ������������!";
			link.l1 = "� ���� ��� ������� �� ������� ����������. ������� �� ���, ��� � ����"+ GetSexPhrase("��","��") +" �������, ����� ������ ����� ��������, ��� ��� ������� �������� ��� �� ����?";
			link.l1.go = "Alumnus_3";
		break;
		
		case "Alumnus_3":
			dialog.text = "��, ��� �� �����, "+ GetSexPhrase("������� �������","�������") +"! ��� ������� ������� ���, ��� ������ � ������ ���. ��� ����� ���-���� ���������, ���� � ����������, ��� �� �� ��� ��������. ���, �������� ��� ��������. ���������� ������� � ���� � ������� ������ �������� ��� ���� � ����. ���� �� �� � ��������� ����, �� �� ������ ��������� ��� ���� ���� ���������. � ������� ������ ��� ����� ����, � ������� �������������, �� ������ ������ � ����. ������, �� ��������, "+ GetSexPhrase("������� �������","�������") +".";
			link.l1 = "�� ��������, ������ �������. � ������� ���.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_4";
			
			sld = CharacterFromID("PDM_Markus")
			sld.dialog.filename   = "Quest/PDM/Aptekar.c";
			sld.dialog.currentnode   = "Markus_Dat_Lekarstvo";
			pchar.questTemp.PDM_Apt_Markus_lekarstvo = "PDM_Apt_Markus_lekarstvo";
			
			GiveItem2Character(PChar, "PDM_Heal_Poroshok");
			AddQuestRecord("PDM_Aptekar", "3");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("��","���"));
		break;
		
		case "Alumnus_4":
			dialog.text = LinkRandPhrase("� ���� ��� ��� ��, ��� ��� ���� ����������! ������� ������ �� ��������� ���� �� ���� �����������.", "...�� ����� ������� ���� ����������� �������� ������, ��� ������������� ���������������� �������... ���, ����������, �� ������� ���! � �������� �� ����� ������ ����� ����� ������.", "� ���� ��� ��� ��, ��� ��� ���� ����������! ������� ������ �� ��������� ���� �� ���� �����������.", "...�� ����� ������� ���� ����������� �������� ������, ��� ������������� ���������������� �������... ���, ����������, �� ������� ���! � �������� �� ����� ������ ����� ����� ������.");
			link.l1 = "��������, ������. � �����.";
			link.l1.go = "exit";
		break;
		
		case "Markus_Dat_Lekarstvo":
			dialog.text = "";
			link.l1 = "(�� ����������� ������� � ���� � ���� ������� ������ �� ������)";
			link.l1.go = "Markus_Dat_Lekarstvo_2";
		break;
		
		case "Markus_Dat_Lekarstvo_2":
			dialog.text = "(������ ����������, ������ �� ��������� ������ �������� ������... � ����� ����� �� ������� � ������)";
			link.l1 = "(������� ���������� ���������� � ���, ��� �� ������ ��� �������)";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_Apt_Markus_lekarstvo");
			pchar.questTemp.PDM_Apt_Rasskazat_Tavern = "PDM_Apt_Rasskazat_Tavern";
			NextDiag.TempNode = "Markus_Dat_Lekarstvo_3";
		break;
		
		case "Markus_Dat_Lekarstvo_3":
			dialog.text = "(����)";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Markus_Dat_Lekarstvo_3";
		break;
		
		case "Markus_Vizdorovel":
			sld = CharacterFromID("SentJons_tavernkeeper")
			dialog.text = "��, �� ������ ����, ������� "+pchar.name+"! � ������ ������������� ��� �� �� ���������. "+sld.name+" ��������� ��� ��� ���, ��� �� ��� ���� �������.";
			link.l1 = "� ���"+ GetSexPhrase("","�") +", ��� �� ����������, � ������ �� ����������, ��� �� � ����� ���������. "+sld.name+" ������, ��� �������� �������� ���� �������.";
			link.l1.go = "Markus_Vizdorovel_2";
			AddCharacterSkillDontClearExp(pchar, "Leadership", 1);
			AddCharacterSkillDontClearExp(pchar, "Defence", 1);
			Log_SetStringToLog("��������� + 1");
			Log_SetStringToLog("������ + 1");
			DeleteAttribute(pchar, "questTemp.PDM_Apt_Vizdorovel");
		break;
		
		case "Markus_Vizdorovel_2":
			dialog.text = "��, ��� ������. �������� ������������� ����� ������, ������� ��� ��� ������ ��������. � ����� ������� �������, ���������� ������� � �������� ��������. ����� � ��������� �� ���� ��������, ������ �� ������, ������ ��! ��� ������ ��� ������� �� ���� ������. � �������� �������� ����� ������� ��� ������ �� ����-������, ��� ��� ������ ���������, �������.";
			link.l1 = "������� �� ���������������, ������, � ���� �������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "Markus_Vizdorovel_3";
		break;
		
		case "Markus_Vizdorovel_3":
			dialog.text = "� ��� ��� ���. �������� ��� ������ � ��������� �� �������, ������������� ��� �� ����.";
			link.l1 = "������, � ��� ��� �������"+ GetSexPhrase("��","���") +" ��������� ��������.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddMoneyToCharacter(pchar, 5000);
			
			sld = GetCharacter(NPC_GenerateCharacter("Ropfleik", "officer_58", "man", "man", sti(PChar.rank) + 6, PIRATE, 15, false));
			SetShipHunter(sld);
			sld.name = "��������";
			sld.lastname = "";
			SetFantomParamHunter(sld);
			SetCaptanModelByEncType(sld, "war");
			sld.AlwaysEnemy = true;
			sld.DontRansackCaptain = true;
			sld.mapEnc.type = "war";
			sld.mapEnc.Name = "��� ����� ��������";
			sld.hunter = "pirate";
			Group_AddCharacter("Ropf_Ship", "Ropfleik");
			
			Group_SetGroupCommander("Ropf_Ship", "Ropfleik");
			Group_SetTaskAttackInMap("Ropf_Ship", PLAYER_GROUP);
			Group_LockTask("Ropf_Ship");
			Map_CreateFastWarrior("", "Ropfleik", 30);
			
			sld = CharacterFromID("Doktor_Alumnus")
			sld.dialog.filename   = "Quest/PDM/Aptekar.c";
			sld.dialog.currentnode   = "Alumnus_Novoe_Zadanie";
			
			AddQuestRecord("PDM_Aptekar", "5");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("��","����"));
		break;	
		
		case "Alumnus_Novoe_Zadanie":
			dialog.text = "�-�, ��� ��, "+ GetSexPhrase("��� ���� � ������������ �������","��� ���� � ������������ ��������") +"! ��� ��� ������ �� ����?";
			link.l1 = "�����"+ GetSexPhrase("","�") +" ������������� ���, ������. �� � ������� ������� ������. ��� �������, ��� �� ��� ����, �������� �� ���� ����� �����. � � ������"+ GetSexPhrase("��","���") +", ����� �������� ��� ���� ����������� ���������������.";
			link.l1.go = "Alumnus_Novoe_Zadanie_2";
			AddMoneyToCharacter(pchar, -5000);
		break;
		
		case "Alumnus_Novoe_Zadanie_2":
			dialog.text = "�����������, � ����� ���, ��� � ����� �������� � �����. �������, �������, �� �� ��� �� ����������, ��� ��� ���������� � ������ ���\n�� ������� ���, ���������� �� ������ ������������ ���� �������������, ����� � ��� ��������� ��� �� ����� ������? ��� ���������� ��������� ���������� ����� ������ �����, ��� ������������ �� ��������� ��������. ��� �� � �� ���� �������� ���� ��������������� �������� ������. ���� �� �� ������� ��� ���� ��� �����, � �� ��� ������ ��� � ����� �������� �� ����� ������� � ��������. ������� � ������� ������� ���� ����� �... ��� �� ��� �����? �� ��, � ����� ����.";
			link.l1 = "� � ����� � ���, ������. ���������� ��� �� ���� ����� ���� - ����� �������� ���.";
			link.l1.go = "Alumnus_Novoe_Zadanie_3";
		break;		
		
		case "Alumnus_Novoe_Zadanie_3":
			dialog.text = "�� � ������� ��������... ��������, � ������� ��� ����� '����'. �� ����� ������� �� ������� �� ������ ������� � �������, ������� ������ ������ ����� � ��������, � ����� ������ �� ��������, ��������� � ����������� ������. �� ��� �������, ��� �� ����� �������, �������� �� ��� �������� - �� ��� ��� ���� ����� �������� ������� ������ ������� �������� � ���������� ��������. �� ���� ����������� �� �����, � � ��������� ��� ��� ������ ���-�� �� ���������. ��� ��� � ���� ���� �����, �� ���� �� ���-�� �������� �� ����.";
			link.l1 = "� ������� ��� ��� ������. � ��� ��� ����������?";
			link.l1.go = "Alumnus_Novoe_Zadanie_4";
		break;
		
		case "Alumnus_Novoe_Zadanie_4":
			dialog.text = "�-�. ��� ����� ��������� ��������. � �� ���� � �������� ���������� � ��������. � ������, ��� ���� ������� ��� ��� ����� ��� �������, �� � ������ ����� ��������, ��� ������ ������ ������� ��� ����� ���������, ������ ��.";
			link.l1 = "� ��� �� � ����"+ GetSexPhrase("��","��") +" ������ ��� �����, ����� �� ����, ��� ��� ����������?";
			link.l1.go = "Alumnus_Novoe_Zadanie_5";
		break;
		
		case "Alumnus_Novoe_Zadanie_5":
			dialog.text = "��, � ����� ���, ��� �������� ��� �����. Ÿ ����� ���������� ������������ ������ ������ � �����. ���������� ������� �����, ���� �������. � �����, ��� ��� ���������� ��-�� ������� ������� � ������ �� ������� ���������� ���� �����. ���������� ������� ����� ���� � ������� ������� ������ �� ���������� ���� � ������ ��������� �������������. �������, � ����������.";
			link.l1 = "��, �� ������������. ������� �� ������. � ���������� ����� ��� ��� ��� �����. �� �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_Novoe_Zadanie_6";
			
			sld = GetCharacter(NPC_GenerateCharacter("Pablo_Loco", "indsar1", "man", "man", 10, PIRATE, -1, false));
			sld.name = "�����";
			sld.lastname = "����";
			sld.greeting = "GR_Pablo_Loco";
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetCitizenType(sld);
			sld.dialog.filename   = "Quest/PDM/Aptekar.c";
			sld.dialog.currentnode   = "Pablo_Loco_FT";
			ChangeCharacterAddressGroup(sld,"Shore34","goto","goto1");
			
			AddQuestRecord("PDM_Aptekar", "6");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("","�"));
		break;
		
		case "Alumnus_Novoe_Zadanie_6":
			dialog.text = "����� ���������� �����! ������� �� ��� ����� ����������� ��� ��������?";
			link.l1 = "��� ���, ������. ��������� ������.";
			link.l1.go = "exit";
			link.l2 = "������, ��������� ���, ��� �������� ��� �����.";
			link.l2.go = "Alumnus_Novoe_Kak_Opoznat";
			NextDiag.TempNode = "Alumnus_Novoe_Zadanie_6";
		break;
		
		case "Alumnus_Novoe_Kak_Opoznat":
			dialog.text = "�����������: ��� ������ ����� ������������ �� ��������� ��������, � ����� ���������� ������������ ������ � �����. � �����, ��� ��� ���������� ��-�� ������� ������� � ������ �� ������� ���������� ���� �����. ���������� ������� ����� ���� � ������� ������� ������ �� ���������� ���� � ������ ��������� �������������...";
			link.l1 = "�����, ������, ����� ����������, � �������"+ GetSexPhrase("","�") +".";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_Novoe_Zadanie_6";
		break;
		
		case "Pablo_Loco_FT":
			dialog.text = "�! �� ������� ������, ��? �� ������� ����� ������. ����"+ GetSexPhrase("�� �����","�� ����") +"! ������� �� �� ���������� � ��������� ����� ����?";
			link.l1 = "� ��� �� ��������? ��� ��?";
			link.l1.go = "Pablo_Loco_1";
			//link.l1.go = "Pablo_Loco_8";
			NextDiag.TempNode = "Pablo_Loco_ER_1";
		break;
		
		case "Pablo_Loco_ER_1":
			dialog.text = "�� ��������"+ GetSexPhrase("","�") +" ���� �������� � ����?";
			link.l1 = "� ��� �� ��������?";
			link.l1.go = "Pablo_Loco_ER_2";
		break;
		
		case "Pablo_Loco_ER_2":
			dialog.text = "�������� ������ ��� ������ �������, ��� ���� ������. �� ����"+ GetSexPhrase("��","��") +" ��������� � � ����, ����� ����������.";
			link.l1 = "�������� ��� ���� �������.";
			link.l1.go = "Pablo_Loco_2";
		break;
		
		case "Pablo_Loco_1":
			dialog.text = "� �����. ���, ��� ��� ������� �� �������� ����� � ������� �������, �� ������ ���� ����� � �����. ���, ��� ��� ������� �� ����������� ������ � ������� ����, �� ��������� ���� ������� ������ �����.";
			link.l1 = "��, ����������, ���������� �������. �������� ��� ���� �������.";
			link.l1.go = "Pablo_Loco_2";
			link.l2 = "���� ����� ���� ����� ��������, � � ���� ����� ���� ���������� ����. �� ��������.";
			link.l2.go = "exit";
		break;
		
		case "Pablo_Loco_2":
			dialog.text = "� ��� � ��������. � ��� ������ � �����, ���������� � ������, ����� ����, ����� ����� ��������� ���������. � ����� �������. � ���������� ��� ����� �������, � � ���������� ��� ����. ��� ������ �������� � ���� �� ��������� ������. ��� ������� ����� �� ����. �� ����� ���� �������� �� ������.";
			link.l1 = "��� �� ������ � ����?";
			link.l1.go = "Pablo_Loco_3";
		break;
		
		case "Pablo_Loco_3":
			dialog.text = "������� ��� ������ ������� �������� ������� �� ����. ��� ������� �� ������ ����� ������� ��������, � ��� ��������, ��� ��� �������� �������� �����, ��������� ������. ��� ����������� � ���� ��������, ����� � ���������� ������ ��������� � ��������� �����������. �� ��� �� ���� ������� �����. ��� ���� ������� ����� �����. ����������� ���������� ���� ������� � ��������, ��� �� ��� ��������. ��� ��� ��� ����� ���� �������, � ����� ����� � ��� ������� � ����� ����, ��� ��� ��� - ����, ����� ����, ����� ����������� ����� ����� ���������. ��� ��� ������ � ������� ������������, ��� ��������� ��� ������� � ����. ��� ��� �������.";
			link.l1 = "� ������� � ����� ������.";
			link.l1.go = "Pablo_Loco_4";
		break;
		
		case "Pablo_Loco_4":
			dialog.text = "";
			link.l1 = "�������� ��� ��� � ����� ������.";
			link.l1.go = "Pablo_Loco_Plemya_Ushlo";
			link.l2 = "��� �� �����, �������?";
			link.l2.go = "Pablo_Loco_Trava";
		break;
		
		case "Pablo_Loco_Plemya_Ushlo":
			dialog.text = "�� ����� ����. � �� ���� �������� �� ����.";
			link.l1 = "��� �� �����, �������?";
			link.l1.go = "Pablo_Loco_Trava";
		break;
		
		case "Pablo_Loco_Trava":
			dialog.text = "��, ��� �. ��� �������� ���� '����� ����' - �����������, �� ����. ��� ������, ��� � �����������, ������ ��� � �������� ���� �������: ��� ����, ����� �����, ���� ������. ����� ����: ��� ��� � �����.";
			link.l1 = "�������������. '���� ������', �? ���, �-�, ����� �� ���������. ��, �����, ��� ����� �����, ������� ������, ���...";
			link.l1.go = "Pablo_Loco_5";
		break;
		
		case "Pablo_Loco_5":
			dialog.text = "����� ����� � ���� �����?";
			Link.l1.edit = 1;
			Link.l1 = "";
			link.l1.go = "Pablo_Loco_Pravilno";
			NextDiag.TempNode = "Pablo_Loco_5";
		break;
		
		case "Pablo_Loco_Pravilno":
			if ("������ � �����" == GetStrSmallRegister(dialogEditStrings[1]) || "������ � ����" == GetStrSmallRegister(dialogEditStrings[1]) || "����� ������ � �����" == GetStrSmallRegister(dialogEditStrings[1]) || "������ ������ � �����" == GetStrSmallRegister(dialogEditStrings[1]) || "���� � ������" == GetStrSmallRegister(dialogEditStrings[1]) || "����� � ������" == GetStrSmallRegister(dialogEditStrings[1]) || "����� ����� � ������" == GetStrSmallRegister(dialogEditStrings[1]) || "������ ����� � ������" == GetStrSmallRegister(dialogEditStrings[1]))
			{
				Dialog.text = "������ ������� � ������? � ���� ����� �����. ��� ����� ������, � ����� �����. ����� ���, ����� ���� ����� ��� �����?";
				Link.l1 = "������ ������� ������ ���� �� ���.";
				Link.l1.go = "Pablo_Loco_6";
				break;
			}
			else
			{
				Dialog.text = "�� ���� ����� ����� � ����� �������.";
				{
					Link.l1 = "��� ��� ��� ��������.";
					Link.l1.go = "Pablo_Loco_5";
				}
				link.l2 = "��� ���� ��������.";
				link.l2.go = "exit";
			}
		break;
		
		case "Pablo_Loco_6":
			dialog.text = "���, �������, �� ������"+ GetSexPhrase("","�") +"? � ���� ����� �������� - ������ �����. ��� ������, ������ ���������� ����� � ���� '�������� ������'. �� � ����, ��� �� �� ����� ������������ �����, ����� ��������� ����� ������� - ��� �� ��� �������. ����� ������. ����� ����� ��� �����, ��� ����� �����, ������ ��� � ������ ����� ����, ��� ��� �����. ����� �� ������ ��� � ����� �����, �������.";
			link.l1 = "� ����� � ����.";
			link.l1.go = "Pablo_Loco_7";
		break;
		
		case "Pablo_Loco_7":
			dialog.text = "���, ���! ����� ������ '��������'! ������� ������ �������� ��� �����! �� ������ ��������� ����� ������ ������������ ������ � ����� ����������� �������, � �� �������� � ������� ����!";
			link.l1 = "�� ������� �������, �����, �� ������ �� ����? �� �����: ��� � ����"+ GetSexPhrase("��","��") +" �������, ����� ������ ���� ��������� �����?";
			link.l1.go = "Pablo_Loco_8";
		break;
		
		case "Pablo_Loco_8":
			dialog.text = "��� ����� ��������� ������. ��� ������ ���������� ���������. ���� �� ������, ����� � ������ ��� ���� ���� �����, �� ����"+ GetSexPhrase("��","��") +" ��������� ��� ������ ���������. ��� ����� �� ���������� � ��������, ����� � ������� ���������.";
			link.l1 = "������ ���������? � �����"+ GetSexPhrase("","�") +" � �� ������. �� ��������, �����. � �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_9";
			
			PChar.quest.PDM_Apt_Prihov_v_buhtu.win_condition.l1 = "location";
			PChar.quest.PDM_Apt_Prihov_v_buhtu.win_condition.l1.location = "Shore10";
			PChar.quest.PDM_Apt_Prihov_v_buhtu.win_condition = "PDM_Apt_Prihov_v_buhtu";
			
			AddQuestRecord("PDM_Aptekar", "7");
		break;
		
		case "Pablo_Loco_9":
			dialog.text = "����� �� ��������� ���? ������������, ��� ��� ����� �� ����, ��� ������ ���������. ����� �� �������� ��� ���, � ������� ���� ����� �����. � ����� �� �������� ���������� �����. ��� ��, ��� � ���� �������.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +". �� ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_9";
		break;
		
		case "Nashel_Derevo":
			dialog.text = "�� �����? �� ��������"+ GetSexPhrase("","�") +" ������ ���������?";
			link.l1 = "� ���� ���� ������, ������� ���� �����. ��� ���. ������ �����, ����� ���� �����, ����� �� ��� �������� ��� ��� ������... ���.. ��... �����... ��� ��� ��� ���������� ��� ������� ������.";
			link.l1.go = "Nashel_Derevo_2";
		break;
		
		case "Nashel_Derevo_2":
			TakeItemFromCharacter(pchar, "PDM_Derevo_Teshkali");
			dialog.text = "������� ����� ������, � ��� ����� ������ ���� ����� ����� ��� � ����.";
			link.l1 = "����� � ������ ����� ��������, ������ � ���� �� �������� ����� � ���� ��� �������.";
			link.l1.go = "Nashel_Derevo_3";
		break;
		
		case "Nashel_Derevo_3":
			dialog.text = "(������� �� ��� �������� ��������)";
			link.l1 = "�����, �����, �� ���� ������. �������� ����� ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_Stroit_lodku";
			
			SetTimerCondition("PDM_Apt_Lodka_Postroena", 0, 0, 7, false);
			
			AddQuestRecord("PDM_Aptekar", "10");
		break;
		
		case "Pablo_Loco_Stroit_lodku":
			dialog.text = "����� ��� �� ������, ������� �����.";
			link.l1 = "������, �����, ����� ��� ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_Stroit_lodku";
		break;
		
		case "Pablo_Loco_Lodka_Postroena":
			dialog.text = "����� �������, � ����� ���� �����.";
			link.l1 = "���������, ����� ����. �� ��������, ��� ����� �� ������� ������, � ����� ������� ��������. ������.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			AddCharacterSkill(pchar, "Sailing", 1);
			AddCharacterSkill(pchar, "Repair", 1);
			Log_SetStringToLog("��������� + 1");
			Log_SetStringToLog("������ + 1");
			
			GiveItem2Character(PChar, "PDM_Trava_Tzes_Umrat");
			AddQuestRecord("PDM_Aptekar", "11");
			
			sld = CharacterFromID("Doktor_Alumnus")
			sld.dialog.filename   = "Quest/PDM/Aptekar.c";
			sld.dialog.currentnode   = "Alumnus_Finish_Zadanie";
		break;
		
		case "Alumnus_Finish_Zadanie":
			dialog.text = "�� ���������. ����������. �� �������� ��� �����, ��� � � ��� ������, "+ GetSexPhrase("��� ���� �������","�������") +"?";
			link.l1 = "���������� �����?";
			link.l1.go = "Alumnus_Finish_Zadanie_2";
		break;
		
		case "Alumnus_Finish_Zadanie_2":
			dialog.text = "��������, ���?";
			link.l1 = "��� ���.";
			link.l1.go = "Alumnus_Finish_Zadanie_3";
		break;
		
		case "Alumnus_Finish_Zadanie_3":
			dialog.text = "�-�! �� �������� �! ����� �����! � ����� ������ �������� ���� �������� ������, � ����� ���������� ���� ������������� ������������!";
			link.l1 = "�������, ������, ���� ��� �� ������ - ����� ��� ��� ������� �����?";
			link.l1.go = "A_pravda_ZACHEM???";
			TakeItemFromCharacter(pchar, "PDM_Trava_Tzes_Umrat");
		break;
		
		case "A_pravda_ZACHEM???":
			dialog.text = "������ ��, "+ GetSexPhrase("��� ���� �������","��������") +", � ��������� ��������� ������� ������� ����������� ��������� - ������ ����������! � ������� ���� ������ � ����������� ������� �����, ������� �������� ��� ���� �����!";
			link.l1 = "����. �����, ���� ����� ����, ��� �� ���������� ��� �����, �� ����� ����������, ��� �� ��� ����������� ���� - �������� ���, ����������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_Lechenie_s_voprosom";
			
			CloseQuestHeader("PDM_Aptekar"); 
		break;
		
		case "Alumnus_Lechenie_s_voprosom":	//��� ������
			dialog.text = "...�� ����� ������� ���� ����������� �������� ������, ��� ������������� ���������������� �������... �������, ��� ����� ��, ��� � ���� ���� ��� �������?";
			link.l1 = "������������, ������ �������, � �� �����"+ GetSexPhrase("","�") +", ����� �� ��������� ���� �������� ��������.";
			link.l1.go = "CheckForConfuse";
			link.l2 = "���� ��� � ��� ������� ����� � �����? �������� ���������.";
			link.l2.go = "Alumnus_Lechenie_s_voprosom_2";
			link.l3 = "�����"+ GetSexPhrase("","�") +" ��������� ���. �� ��������.";
			link.l3.go = "exit";	//��� ������
			if(CheckAttribute(PChar,"Luke.BadPoison"))	
			{
				link.l4 = "������, ��� ����� ����� ���� ������, ���� �������� ����� ������� ����!";
				link.l4.go = "LukePoison";
			}
		break;
		
		case "Alumnus_Lechenie_s_voprosom_2":
			dialog.text = "��������� ��, ��� ��� ���������� ������� ����� ������ � ��������, ���� � ����� ����� ��������, ���� ��������� ������������ ��������� ����������, ������� ��� � ������� ���������� ���� �� ���� �������. ������ ������ '�����' ��� ����� �������� ��������� � ������� ����� ������, � ���������� � �������� � ����� �� ���������, ��� ����� � ������ ����� ��� �������, �� ����������� �� ��������� ��������.";
			link.l1 = "�����, � �����"+ GetSexPhrase("","�") +". �� ������ ��������� ���� �������� ��������?";
			link.l1.go = "CheckForConfuse";
			link.l2 = "��� ���� ����� ���������. �� ��������.";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "Alumnus_Lechenie";
		break;
		
		case "Alumnus_Lechenie":
			dialog.text = "...�� ����� ������� ���� ����������� �������� ������, ��� ������������� ���������������� �������... �������, ��� ����� ��, ��� � ���� ���� ��� �������?";
			link.l1 = "������������, ������ �������, � �� �����"+ GetSexPhrase("","�") +", ����� �� ��������� ���� �������� ��������.";
			link.l1.go = "CheckForConfuse";
			link.l2 = "�����"+ GetSexPhrase("","�") +" ��������� ���. �� ��������.";
			link.l2.go = "exit";
			if(CheckAttribute(PChar,"Luke.BadPoison"))	
			{
				link.l3 = "������, ��� ����� ����� ���� ������, ���� �������� ����� ������� ����!";
				link.l3.go = "LukePoison";
			}
		break;
		
		case "CheckForConfuse":
			dialog.text = "���� ������ ��������� ����������� ������, �������?";
			for(i=0; i<GetPassengersQuantity(pchar); i++)
			{
				iOfficer = GetPassenger(pchar, i);
				sld = GetCharacter(iOfficer);
				if (!GetRemovable(sld)) continue;
				if (!CheckAttribute(sld, "HPminusDaysNeedtoRestore") || CheckAttribute(sld, "Doctored")) continue;
				attrL = "l"+i;
				Link.(attrL)	= "������ " + GetFullName(sld) + ".";
				Link.(attrL).go = "OfficerConfusedSel_" + i;
			}
			Link.l99 = "� ������ ������ ������.";
			Link.l99.go = "exit";
		break;
		
		case "OfficerConfused":
			chref = GetCharacter(sti(NPChar.OfficerToHealConfuse));
			
			if (!CheckAttribute(chref,"quest.officertype")) offtype = "���������";
			else offtype = XI_ConvertString(chref.quest.officertype);
			dialog.Text = "�� ������ � ���� "+GetFullName(chref)+", ������������� - "+offtype+".";
			Link.l1 = "��, ������.";
			Link.l1.go = "OfficerConfused_2";
			Link.l99 = "���, � ���������"+ GetSexPhrase("","�") +".";
			Link.l99.go = "exit";
		break;
		
		case "OfficerConfused_2":
			chref = GetCharacter(sti(NPChar.OfficerToHealConfuse));
			if (CheckAttribute(chref,"chr_ai.max_hp")) npchar.HealPrice = (makeint(chref.chr_ai.max_hp)*100)+makeint((sti(chref.rank)*500)*(MOD_SKILL_ENEMY_RATE/2));
			else npchar.HealPrice = (makeint(chref.health.maxhp)*100)+makeint((sti(chref.rank)*500)*(MOD_SKILL_ENEMY_RATE/2));
			dialog.Text = "�� ���������, ����� ������� �� ������� ��������� ������������ ���� ��� ���� ���..."+(sti(chref.HPminusDaysNeedtoRestore)-sti(chref.HPminusDays))+". � ��� �� ����������� �������� ������� �������������, �� ��� �������� ��� �... "+FindRussianMoneyString(sti(npchar.HealPrice));
			if (sti(pchar.money)>=sti(npchar.HealPrice))
			{
				Link.l1 = "������, � ����"+ GetSexPhrase("�","��")+" ���������.";
				Link.l1.go = "OfficerConfused_3";
			}
			Link.l99 = "������� ���, � ���� ��������� �����"+ GetSexPhrase("��","���") +" � ���������.";
			Link.l99.go = "exit";
		break;
		
		case "OfficerConfused_3":
			chref = GetCharacter(sti(NPChar.OfficerToHealConfuse));
			AddMoneyToCharacter(pchar,-sti(npchar.HealPrice));
			LAi_Fade("", "");
			WaitDate("",0,0,0, 0, 60);
			int plusdays = makeint(sti(chref.HPminusDaysNeedtoRestore)/4*3);
			if (plusdays > 30) plusdays = 39;
			chref.HPminusDays = sti(chref.HPminusDays) + plusdays;
			if(sti(chref.HPminusDays) >= sti(chref.HPminusDaysNeedtoRestore))
			{
				DeleteAttribute(chref, "HPminusDays");
				DeleteAttribute(chref, "HPminusDaysNeedtoRestore");
				Log_Info("������ " + GetFullName(chref) + " ����������.");
				dialog.Text = "��� ������� ��������� �������� " + GetFullName(chref) + ". ���� ���� ��������, ��� ��� ���� ������ ��������...  � ��� �� ��� ����-�� ��� ��������� ��� ������?";
			}
			else 
			{
				chref.Doctored = true;
				dialog.Text = "� ������ ��, �� ��� � ��������. ������ ����� ��� � ��������� ��� " + GetFullName(chref) + " ����� � ������ �������. � ��� �� ��� ����-�� ��� ��������� ��� ������?";
			}
			Link.l1 = "���, ���� ��� �����������.";
			Link.l1.go = "CheckForConfuse";
			Link.l99 = "���� ��. ��������� ��� �� ������.";
			Link.l99.go = "exit";
		break;
		
		case "LukePoison":
			dialog.text = "�������, ����� ��� ��� ���������... ��, ���� �� ��� ����������� �� ����� ������ � ����������� ����! �� �� ����������, � ����, ��� ��� ������. � ������, "+pchar.name+", �������� � �������, � ����� ���� �������.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("HealingPoison");
		break;
	}
}