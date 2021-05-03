
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int Rank = sti(pchar.rank) - 4 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	int Sila = 70 + MOD_SKILL_ENEMY_RATE * 3;
	int DopHP = 60 + MOD_SKILL_ENEMY_RATE * 12;
	int Bonus = sti(pchar.rank);
	if (Bonus <= 6) Bonus = 1;
	if (Bonus >= 7 && Bonus <= 12) Bonus = 1.2;
	if (Bonus >= 13) Bonus = 1.5;
	int Plata1 = 10000 + 1800 * sti(pchar.rank) * Bonus;
	int Plata2 = 20000 + 2000 * sti(pchar.rank) * Bonus;
	pchar.PDM_NK_Plata1.Money = 10000 + 1800 * sti(pchar.rank) * Bonus;
	pchar.PDM_NK_Plata2.Money = 20000 + 2000 * sti(pchar.rank) * Bonus;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":							//����� Sinistra
			dialog.text = "��, "+ GetSexPhrase("������","������") +"! ��� ��� ������, � � �� ��� ��������.";
			link.l1 = "�� �� � ��� �����. ��� ��� ����� ���������.";
			link.l1.go = "Octavio_1_1";
			link.l2 = "� �� ���� ���������� ����. ������.";
			link.l2.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\Octavio Lambrini.wav");
		break;
		
		case "Octavio_1_1":
			dialog.text = "���? �� ������������� ���������� ������� ��������? ��� �� �� ���� ��������"+ GetSexPhrase("","�") +"?";
			if (pchar.name == "�����" && pchar.lastname == "����")
			{
				link.l1 = "�� ����� ����� ��� "+GetFullName(pchar)+". �������, ����������� ���������, ���� � ��������� ���������� �� ��������. � ��� '��������' ��� ������ �� �������.";
				link.l1.go = "Octavio_1_2";
			}
			if (pchar.name == "������")
			{
				link.l2 = "�� ����� ����� ���� "+pchar.name+". �������, ����������� ����������, ��������������� �� ������� � ���������� � ����� ������ ����������. � ��� '��������' ��� ������ �� �������.";
				link.l2.go = "Octavio_1_2";
			}
			if (pchar.name == "��������")
			{
				link.l2 = "�� ����� ����� ���� "+pchar.name+". ������ ������� �� ������ �������, ��� � ��������, ������ ������ �� ������, ������� � ������� ��� ���������� ���� ������ � ���, �� ����������, ������� �� ������ ���������, ������� ������������� �������, ��� ��� �� ���� ����� �� ���������, ��� ��� ����� ������� �� �������. � ��� '��������' ��� ������ �� �������.";
				link.l2.go = "Octavio_1_2";
			}
			if (pchar.lastname == "����")
			{
				link.l3 = "�� ��� "+GetFullName(pchar)+" - � "+ GetSexPhrase("���","����") +" ���������� ������, �������� �����. � ��� '��������' ��� ������ �� �������.";
				link.l3.go = "Octavio_1_2";
			}
			if (pchar.name == "�����" && pchar.lastname == "�� ���")
			{
				link.l4 = "�� ����� ����� ��� "+GetFullName(pchar)+". ��������, �������, ��������� ���� �� ��������� ����������. � ��� '��������' ��� ������ �� �������.";
				link.l4.go = "Octavio_1_2";
			}
			if (pchar.lastname == "����")
			{
				link.l6 = "�� ����� ����� ���"+ GetSexPhrase("","�") +" "+GetFullName(pchar)+". �������, "+ GetSexPhrase("����������� ���������","����������� ����������") +" � "+ GetSexPhrase("���","��") +", ��� ��������"+ GetSexPhrase("","�") +" ׸���� ��������� �� ���. � ��� '��������' ��� ������ �� �������.";
				link.l6.go = "Octavio_1_2";
			}
			if (pchar.lastname == "������")
			{
				link.l7 = "�� ��� "+GetFullName(pchar)+" - � ������� ���������� ������������ ����������������, ������ �������. � ��� '��������' ��� ������ �� �������.";
				link.l7.go = "Octavio_1_2";
			}
			if (pchar.reputation >= 75)
			{
				link.l8 = "���� ����� "+GetFullName(pchar)+". ��� �����, ��� � ������� �����, � ��� ����� ��������. � ��� '��������' ��� ������ �� �������.";
				link.l8.go = "Octavio_1_2_DB";
			}
			if (pchar.reputation <= 25)
			{
				link.l8 = "���� ����� "+GetFullName(pchar)+". � �� ������ ������ ���������� ����� ����� ��� �������� ������� � ����������� � ������ �������. � ��� '��������' ��� ������ �� �������.";
				link.l8.go = "Octavio_1_2_DB";
			}
			if (pchar.reputation >= 0 && pchar.reputation <= 100)
			{
				link.l9 = "� "+pchar.name+", ������� � "+ GetSexPhrase("������","�������") +". � ���� � ���-�� �� ����������.";
				link.l9.go = "Octavio_1_2_ostalnoe";
			}
		break;
		
		case "Octavio_1_2":
			if (pchar.name == "�����" && pchar.lastname == "����")
			{	
				dialog.text = "��� ��� �� ��� ����� ����, ��� ���� ���� ����� �� ���� ��������! ����������! ���� �� ������������� ��� �����, ��� � ���� �������, �� ����� � ������������.";
			}
			if (pchar.name == "������")
			{
				dialog.text = "��� ��� �� �������� �� �����, ��� ���� �������� ����� �� ����! �������! ���� �� ������������� ��� ������, ��� � ���� �������, �� ����� � ������������.";
			}
			if (pchar.name == "��������")
			{
				dialog.text = "�� ������� ���������� ���� ������? �������! ���� �� ������������� ��� ������, ��� � ���� �������, �� ����� � ������������.";
			}
			if (pchar.lastname == "����")
			{
				dialog.text = ""+ GetSexPhrase("���","����") +" �������� �����? �������! � ���� ������ ����, ������-�����, ����� �������� ������ ��� ���������� �� ���� �������. ���� ���� ��� ������� ���������. ���� �� ���� ��������� ��� �� �����"+ GetSexPhrase("","�") +" ��� ��, �� ����� � ������������.";
			}
			if (pchar.name == "�����" && pchar.lastname == "�� ���")
			{
				dialog.text = "�� ����� � ������������ � ������� ������ ����? ����������! ���� �� ������������� ��� �����, ��� � ���� �������, �� ����� � ������������.";
			}
			if (pchar.lastname == "����")
			{
				dialog.text = "���"+ GetSexPhrase("","�") +" "+GetFullName(pchar)+"? �����, �� ���������? ����� ��� � ������! ���� �� ������������� ��� �����"+ GetSexPhrase("","�") +", ��� � ���� �������, �� ����� � ������������.";
			}
			if (pchar.lastname == "������")
			{
				dialog.text = "������ ����� ������ �������? �������! ���� ������ ��� ������� ���������, � ���� �� ���� ��������� ��� �� �����"+ GetSexPhrase("","�") +" ��� ��, �� ����� � ������������. ";
			}
			link.l1 = "��� �� �����������?";
			link.l1.go = "Octavio_1_3";
		break;
		
		case "Octavio_1_2_ostalnoe":
			dialog.text = "��� ���� ��������, "+ GetSexPhrase("�������","�������") +". ����� �������� ������ �������� �� ���� ��������. ����� ���� ��������� �� ��� ��������.";
			link.l1 = "�����, ����� �����, ����� ����� ����� "+ GetSexPhrase("��������","��������") +". (��������� ������ ��� ������� ���������)";
			link.l1.go = "exit";
		break;
		
		case "Octavio_1_2_DB":
			dialog.text = ""+GetFullName(pchar)+"? ��, � � ���� ��������. ���� �� ������������� ��� �����"+ GetSexPhrase("","�") +", ��� � ���� �������, �� ����� � ������������.";
			link.l1 = "��� �� �����������?";
			link.l1.go = "Octavio_1_3";
		break;
		
		case "Octavio_1_3":
			dialog.text = "� � ��� ����� ���������� ���� �� ����� ���������� ����������. ���� ������� ������, ��������� �� �������� ������� ��������������� ������ �� ���� �����. ��������� �������� ��� ����������������.";
			link.l1 = "�� �������� ���� ����� - ��� ���?";
			link.l1.go = "Octavio_1_4";
		break;
		
		case "Octavio_1_4":
			dialog.text = "�! ����� - ��� ����� ������ ������ ��� ��������. �� ������ � ����� ���� � ������� ����� ��� �����. ����� ��� ���� ������������ ������ ���������� �����. ����� ����, ��� �� ����, � ���� ������ �����. ������ � ������� �� ������ ��������� - ����� � ������, � ���� �����������, �������.";
			link.l1 = "� ��� ������. � ���� ���� �����������?";
			link.l1.go = "Octavio_1_5";
		break;
		
		case "Octavio_1_5":
			dialog.text = "��. ���� ��������, � ������� �� ������ ��� ������.";
			link.l1 = "� ������.";
			link.l1.go = "Octavio_1_6";
		break;
		
		case "Octavio_1_6":
			dialog.text = "�� ��������������. � ���� ������� ����� ��������� ������ �� ������ ����� � ���� ����, ������� ������� ����� ��� ����� ��������� ������ �������������. ��, � ������������ �� ��� ������ ����� ������������. �� ���� - ����������. ���� ������, ������� �� �������, �������� ���������� ������� ��� ��������� '��� �������'. � ���� ������� �� ���� ������! ��� ��� �� �� ����� ���������� ����� ����� ����� � ���������.";
			link.l1 = "� �� ������, ����� � "+ GetSexPhrase("���������","����������") +" �� ����?";
			link.l1.go = "Octavio_1_7";
			link.l2 = "���� ��� �� ����������, �������. ���� �� ���� ��������� ��� ����, ��� �����������, �� � ��� ���������� � ���� ������. ������.";
			link.l2.go = "exit";
		break;
		
		case "Octavio_1_7":
			if (pchar.name == "�����" && pchar.lastname == "����")
			{
				dialog.text = "��� �� ����� �����. ���� ���, ��������� � ������ ��������, ������ ������, ������ ����������, ��� ������� ��� - ��� �������. �� �� �� ����� ������������ ����� ������� �������, ��� ���������. ������ �������������� �������� ���������. ��� ������ �������� - � �� ��� ���������. ���� �� � ������� ������� �������� �� ����������, �� � ���� ������ �� ��� ����� ����� ������������.";
			}
			if (pchar.name == "������")
			{
				dialog.text = "��� �� ����� �����. ���� ���, ��������� � ������ ��������, ������ ������, ������ ����������, ��� ������� ��� - ��� �������. �� �� �� ����� ������������ ����� ������� �������, ��� ���������. ������ �������������� �������� ���������. ��� ������ �������� - � �� ��� ���������. ���� �� � ������� ������ �������� �� �����, �� � ���� ������ �� ��� ����� ����� ������������.";
			}
			if (pchar.name == "��������")
			{
				dialog.text = "��� �� ����� �����. ���� ���, ��������� � ������ ��������, ������ ������, ������ ����������, ��� ������� ��� - ��� �������. �� �� �� ����� ������������ ����� ������� �������, ��� ���������. ������ �������������� �������� ���������. ��� ������ �������� - � �� ��� ���������. ���� �� � ������� �������� ���������� ���� ������, �� � ���� ������ �� ��� ����� ����� ������������.";
			}
			if (pchar.lastname == "����")
			{
				dialog.text = "��� �� ����� �����. ���� ���, ��������� � ������ ��������, ������ ������, ������ ����������, ��� ������� ��� - ��� �������. �� �� �� ����� ������������ ����� ������� �������, ��� ���������. ������ �������������� �������� ���������. ��� ������ �������� - � �� ��� ���������. �� ���� �� ���� ��������� ��� "+ GetSexPhrase("����","�����") +", ����� ��� ���� ���� - �� � ��� ����������.";
			}
			if (pchar.name == "�����" && pchar.lastname == "�� ���")
			{
				dialog.text = "��� �� ����� �����. ���� ���, ��������� � ������ ��������, ������ ������, ������ ����������, ��� ������� ��� - ��� �������. �� �� �� ����� ������������ ����� ������� �������, ��� ���������. ������ �������������� �������� ���������. ��� ������ �������� - � �� ��� ���������. ���� �� � ������� ���� �������� ����������, �� � ���� ������ �� ��� ����� ����� ������������.";
			}
			if (pchar.lastname == "����")
			{
				dialog.text = "��� �� ����� �����. ���� ���, ��������� � ������ ��������, ������ ������, ������ ����������, ��� ������� ��� - ��� �������. �� �� �� ����� ������������ ����� ������� �������, ��� ���������. ������ �������������� �������� ���������. ��� ������ �������� - � �� ��� ���������. ���� �� � ������� �������"+ GetSexPhrase("","�") +" ׸���� ���������, �� � ���� ������ �� ��� ����� ����� ������������.";
			}
			if (pchar.lastname == "������")
			{
				dialog.text = "��� �� ����� �����. ���� ���, ��������� � ������ ��������, ������ ������, ����� �� ������, ��� ������� ��� - ��� �������. �� �� �� ����� ������������ ����� ������� �������, ��� ���������. ������ �������������� �������� ���������. ��� ������ �������� - � �� ��� ���������. � ���� ������ ����� �������� ������������, ���� �� ���� ��������� ����� "+ GetSexPhrase("����","�����") +" ��� � ��, �� � ���� ������ �� ��� ����� ����� ������������.";
			}
			if (pchar.reputation >= 75)
			{
				dialog.text = "��� �� ����� �����. ���� ���, ��������� � ������ ��������, ������ ������, ������ ����������, ��� ������� ��� - ��� �������. �� �� �� ����� ������������ ����� ������� �������, ��� ���������. ������ �������������� �������� ���������. ��� ������ �������� - � �� ��� ���������. ���� ���� � ������� ����� "+GetFullName(pchar)+", �� � ���� ������ �� ��� ����� ����� ������������.";
			}
			if (pchar.reputation <= 25)
			{
				dialog.text = "��� �� ����� �����. ���� ���, ��������� � ������ ��������, ������ ������, ������ ����������, ��� ������� ��� - ��� �������. �� �� �� ����� ������������ ����� ������� �������, ��� ���������. ������ �������������� �������� ���������. ��� ������ �������� - � �� ��� ���������. ���� ���� � ������� ����� "+GetFullName(pchar)+", �� � ���� ������ �� ��� ����� ����� ������������.";
			}
			link.l1 = "�������?";
			link.l1.go = "Octavio_1_8";
			link.l2 = "���� ��� �� ����������, �������. ���� �� ���� ��������� ��� ����, ��� �����������, �� � ��� ���������� � ���� ������. ������.";
			link.l2.go = "exit";
		break;
		
		case "Octavio_1_8":
			dialog.text = "" + Plata1 + " �������. � ���� - ����� �� ��������� � ��������!";
			link.l1 = ""+ GetSexPhrase("��������","��������") +".";
			link.l1.go = "Octavio_1_9";
			link.l2 = "���� ��� �� ����������, �������. ���� �� ���� ��������� ��� ����, ��� �����������, �� � ��� ���������� � ���� ������. ������.";
			link.l2.go = "exit";
		break;
		
		case "Octavio_1_9":
			if (pchar.name == "�����" && pchar.lastname == "����")
			{
				dialog.text = "��-��, �������! ��������, ��� �������� ����. ���� ����, ����� ����. ������ � �� ��� � ������� �� ����� ����� �� ��������. ��� - � �����������, ����� ������������ � ��.";
			}
			if (pchar.name == "������")
			{
				dialog.text = "��-��, ������� � ����������� ��������! ��������, ��� �������� ������. ���� ����, ����� ����. ������ � �� ��� � ������� �� ����� ����� �� ��������. ��� - � �����������, ����� ������������ � ��.";
			}
			if (pchar.name == "��������")
			{
				dialog.text = "��-��, �����������! ��������, ��� �������� ����������� ��������. ���� ����, ����� ����. ������ � �� ��� � ������� �� ����� ����� �� ��������. ��� - � �����������, ����� ������������ � ��.";
			}
			if (pchar.lastname == "����")
			{
				dialog.text = "��-��, "+ GetSexPhrase("�������","�������") +"! �� �� ��� ����������� ������ ����, ��������� �����. ���� ����, ����� ����. ������ � �� ��� � ������� �� ����� ����� �� ��������. ��� - � �����������, ����� ������������ � ��.";
			}
			if (pchar.name == "�����" && pchar.lastname == "�� ���")
			{
				dialog.text = "��-��, "+ GetSexPhrase("�������","�������") +"! ��������, ��� �������� ��������. ���� ����, ����� ����. ������ � �� ��� � ������� �� ����� ����� �� ��������. ��� - � �����������, ����� ������������ � ��.";
			}
			if (pchar.lastname == "����")
			{
				dialog.text = "��-��, "+ GetSexPhrase("�������","�������") +"! ��������, ��� �������� ����������� ����. ���� ����, ����� ����. ������ � �� ��� � ������� �� ����� ����� �� ��������. ��� - � �����������, ����� ������������ � ��.";
			}
			if (pchar.lastname == "������")
			{
				dialog.text = "��-��, "+ GetSexPhrase("�������","�������") +"! ��������, ��� �������� ����� ������. ���� ����, ����� ����. ������ � �� ��� � ������� �� ����� ����� �� ��������. ��� - � �����������, ����� ������������ � ��.";
			}
			if (pchar.reputation >= 75)
			{
				dialog.text = "��-��, "+ GetSexPhrase("�������","�������") +"! ��������, ��� "+ GetSexPhrase("��������","��������") +" "+GetFullName(pchar)+". ���� ����, ����� ����. ������ � �� ��� � ������� �� ����� ����� �� ��������. ��� - � �����������, ����� ������������ � ��.";
			}
			if (pchar.reputation <= 25)
			{
				dialog.text = "��-��, "+ GetSexPhrase("�������","�������") +"! ��������, ��� "+ GetSexPhrase("��������","��������") +" "+GetFullName(pchar)+". ���� ����, ����� ����. ������ � �� ��� � ������� �� ����� ����� �� ��������. ��� - � �����������, ����� ������������ � ��.";
			}
			link.l1 = "�� �������, �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_1_10_EsheRaz";
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Antonio", "SpaOfficer2", "man", "man", Rank, SPAIN, -1, false));
			sld.name = "�������";
			sld.lastname = "�� �������";
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Antonio_1_1";
			sld.greeting = "GR_Spainguard";
			FantomMakeCoolFighter(sld, Rank, Sila, Sila, "", "pistol2", DopHP);
			sld.equip.blade = "blade39";
			LAi_SetWarriorType(sld);
			LAi_SetLoginTime(sld, 12.0, 16.00);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.city = "Maracaibo";
			ChangeCharacterAddressGroup(sld,"Maracaibo_town","goto","goto13");
			if (pchar.rank <= 9)
			{
				FantomMakeCoolSailor(sld, SHIP_BRIGHEAVY, "��� �������", CANNON_TYPE_CULVERINE_LBS16, 100, 100, 100);
			}
			if (pchar.rank >= 10 && pchar.rank <= 14)
			{
				FantomMakeCoolSailor(sld, SHIP_FRIGATEMEDIUM, "��� �������", CANNON_TYPE_CULVERINE_LBS16, 100, 100, 100);
			}
			if (pchar.rank >= 15 && pchar.rank <= 19)
			{
				FantomMakeCoolSailor(sld, SHIP_DUTCHPINNACE, "��� �������", CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
			}
			if (pchar.rank >= 20 && pchar.rank <= 25)
			{
				FantomMakeCoolSailor(sld, SHIP_FRIGATE_SAT, "��� �������", CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
			}
			if (pchar.rank >= 26 && pchar.rank <= 32)
			{
				FantomMakeCoolSailor(sld, SHIP_LINESHIPHEAVY, "��� �������", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
			}
			if (pchar.rank >= 33)
			{
				FantomMakeCoolSailor(sld, SHIP_SHARK, "��� �������", CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
			}
			sld.ship.Crew.Morale = Sila;								//������
			ChangeCrewExp(sld, "Sailors", Sila);						//�������
			ChangeCrewExp(sld, "Cannoners", Sila);					//��������
			ChangeCrewExp(sld, "Soldiers", Sila);						//�������
			sld.DontRansackCaptain = true; 							//��������� �� �������
			sld.SinkTenPercent = false; 								//������ � �������������
			sld.SaveItemsForDead = true;							//��������� �������� ����� ������
			sld.DontClearDead = true;								//�� ������� ���� ����� 200�
			sld.AnalizeShips = true;
			Group_FindOrCreateGroup("PDM_el_tib");					//�������� ������
			Group_SetType("PDM_el_tib", "war");						//��� ���������
			Group_AddCharacter("PDM_el_tib", "PDM_CL_Antonio");		//�������� ��������
			
			Group_SetGroupCommander("PDM_el_tib", "PDM_CL_Antonio");
			Group_SetTaskAttack("PDM_el_tib", PLAYER_GROUP);
			Group_SetAddress("PDM_el_tib", "Maracaibo", "quest_ships", "reload_fort1");	//���������� ��������������
			Group_LockTask("PDM_el_tib");
			
			PChar.quest.PDM_CL_Antonio_Ubit.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_CL_Antonio_Ubit.win_condition.l1.character = "PDM_CL_Antonio";
			PChar.quest.PDM_CL_Antonio_Ubit.win_condition = "PDM_CL_Antonio_Ubit";
			
			pchar.questTemp.PDM_CL_Ishem = "Ishem";
			pchar.questTemp.PDM_CL_Tavern = "Tavern";
		break;
		
		case "Octavio_1_10_EsheRaz":
			dialog.text = "��, "+ GetSexPhrase("�������","�������") +" - �� ���������"+ GetSexPhrase("","�") +" ����� �������, �� ��������?";
			link.l1 = "� ����� ��� �����, �� ����������. �� ����� ��� �����.";
			link.l1.go = "Octavio_1_11_EsheRaz";
		break;
		
		case "Octavio_1_11_EsheRaz":
			dialog.text = "����� � ��� ���� �����, "+ GetSexPhrase("�������","�������") +", �� ����� - �������� �� ���������� ���������.";
			link.l1 = "���� ������ - � �� �������� ���� ����� �����. ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_1_10_EsheRaz";
		break;
		
		case "Antonio_1_1":
			dialog.text = "��� �� ������, ������"+ GetSexPhrase("","���") +"?";
			link.l1 = "��� ����� ������� �� ������� - � �� �� ��������� ������?";
			link.l1.go = "Antonio_1_2";
		break;
		
		case "Antonio_1_2":
			dialog.text = "��. � �� ��� ���"+ GetSexPhrase("��","��") +"?";
			link.l1 = "�� ��� "+GetFullName(pchar)+".";
			link.l1.go = "Antonio_1_3";
		break;
		
		case "Antonio_1_3":
			dialog.text = "��, ��, � ���-�� � ��� ������... ����� �� �����?";
			link.l1 = "����� �������� ������� ��� ������! (�������)";
			link.l1.go = "Antonio_Bitva";
			link.l2 = "���-��� ����� ����� ���. (������� ��������)";
			link.l2.go = "Antonio_1_4";
			link.l3 = "��� ����.";
			link.l3.go = "exit";
		break;
		
		case "Antonio_Bitva":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("SPAIN_CITIZENS", LAI_GROUP_PLAYER, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Octavio_2_1":
			dialog.text = "��, "+ GetSexPhrase("�������","�������") +" - �������, �� ���������"+ GetSexPhrase("","�") +" ����� �������, �� ��������?";
			link.l1 = "��. ���������� ������� ������ ���� � ����������, �� ��� ������ ���� ������.";
			link.l1.go = "Octavio_2_2";
		break;
		
		case "Octavio_2_2":
			if (pchar.name == "�����" && pchar.lastname == "����")
			{
				dialog.text = "��, �������! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� �� ��������� ���������� �� ��������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.name == "������")
			{
				dialog.text = "��, �������! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� �� ����������� ������ �� �����. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.name == "��������")
			{
				dialog.text = "��, �������! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� �� �������� ������ ���� ������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.lastname == "����")
			{
				dialog.text = "��, "+ GetSexPhrase("�������","�������") +"! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� �� "+ GetSexPhrase("���","����") +" �������� �����, �������� ������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.name == "�����" && pchar.lastname == "�� ���")
			{
				dialog.text = "��, �������! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� �� ������� ������ ����������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.lastname == "����")
			{
				dialog.text = "��, "+ GetSexPhrase("�������","�������") +"! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� �� "+ GetSexPhrase("���","��") +", ��� �������"+ GetSexPhrase("","�") +" ׸���� ���������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.lastname == "������")
			{
				dialog.text = "��, "+ GetSexPhrase("�������","�������") +"! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� � ���� ����� ����� ������ �������, �������� ������������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.reputation >= 75)
			{
				dialog.text = "��, "+ GetSexPhrase("�������","�������") +"! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� � ���� ��� ������� ��� � ������� ��������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.reputation <= 25)
			{
				dialog.text = "��, "+ GetSexPhrase("�������","�������") +"! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� � ���� ��� ������� ��� � ������������ ��������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			link.l1 = "��, ������ ����� �� �������� ���� ��������� � ���������, �������. ������.";
			link.l1.go = "exit";
			sld = CharacterFromID("PDM_Octavio_Lambrini")
			sld.lifeday = 0;
			AddMoneyToCharacter(pchar, sti(Plata1));
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, SPAIN, -6);
			AddCharacterExpToSkill(pchar, "Leadership", 130);
			AddCharacterExpToSkill(pchar, "FencingLight", 130);
			AddCharacterExpToSkill(pchar, "Fencing", 130);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 130);
			AddCharacterExpToSkill(pchar, "Pistol", 130);
			AddCharacterExpToSkill(pchar, "Fortune", 130);
			AddCharacterExpToSkill(pchar, "Sneak", 130);
			AddCharacterExpToSkill(pchar, "Sailing", 130);
			AddCharacterExpToSkill(pchar, "Accuracy", 130);
			AddCharacterExpToSkill(pchar, "Cannons", 130);
			AddCharacterExpToSkill(pchar, "Grappling", 130);
			AddCharacterExpToSkill(pchar, "Defence", 130);
			AddCharacterExpToSkill(pchar, "Repair", 130);
			NextDiag.TempNode = "Octavio_2_3_EsheRaz";
		break;
		
		case "Octavio_2_3_EsheRaz":
			dialog.text = "�, "+pchar.name+"! � ���������� ���� � ����������� ��� �� ����� �������, �� ��������! � ������ ������� � ����������� � ���������, ����� ��������� ��������� � ��������� ���������.";
			link.l1 = "�����!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_2_3_EsheRaz";
		break;
		
		case "Antonio_1_4":
			dialog.text = "� ��� �� �����? ���� �� ������ ������� ��� �������, �� �� �� ������. �������� ����� ���� �����, �������, ��� � ��������� �������������� ���� �� �� �����.";
			link.l1 = "� "+ GetSexPhrase("������","������") +" � ��� � ������������.";
			link.l1.go = "Antonio_1_5";
		break;
		
		case "Antonio_1_5":
			dialog.text = "� ���, � �� ���� ������ �� ���������. � � ����������� ������ � ��� ������� ���������!";
			link.l1 = "�������� ��� ���� �� ���� ���! (�������)";
			link.l1.go = "Antonio_Bitva";
			link.l2 = "��� �� ������� ��, ���� �� � ����������� ��� ����������� ������� ��� �������� ������� ��������?";
			link.l2.go = "Antonio_1_6";
			link.l3 = "��� ��, ����� ��������.";
			link.l3.go = "exit";
		break;
		
		case "Antonio_1_6":
			dialog.text = "� �� ����� �� ��� ��� ������ ����. �� ��� ����������, ���. �� ��� ��������, �������, ������� ����������� �� �������. ��� � ���� ������� � ��������?";
			link.l1 = "�������� ��������� ��� ������ ��� ���������� �� ���. �� ������, ��� ��� � �������� � ���� �� ����������, �� � ��� �� ������� ���.";
			link.l1.go = "Antonio_1_7";
		break;
		
		case "Antonio_1_7":
			dialog.text = "���� �� ��������� �� ���������������, �� ��� � ���� ������������� �� � ���, ������. ��������.";
			link.l1 = "�, �������� - �� ���� ���� �� ���������. � ���� ������� ��������, ��� ������"+ GetSexPhrase("","�") +" ��� �������. ����� �����, �� ���� ��� ������ �������� ����, �����, ��� ��� ������ ������ �� ������. � �� ������� ���������� ��� � �����, ��� ����� � ���.";
			link.l1.go = "Antonio_1_8";
			link.l2 = "�� ����� ��������.";
			link.l2.go = "exit";
		break;
		
		case "Antonio_1_8":
			dialog.text = "���������... ���� ���� ����� ���������, ������"+ GetSexPhrase("","���") +" "+pchar.name+". � ���� �� ���������, � �������, ����� ������ �������� ����� ����������� ���!";
			link.l1 = "� �������, ��-������, ����� ��� ������������������ ��������� �� ������ ��������?";
			link.l1.go = "Antonio_1_9";
		break;
		
		case "Antonio_1_9":
			dialog.text = "��, �� ���� ����� �������� � ��� ������������������. � �������, �������� " + Plata2 + ". ���� ������ � ��������� ����� ����� ��������� ��-�� ���������������.";
			link.l1 = "�����, ��� " + Plata2 + " - ��� ����������� �����. ����, � ����� ������� ��������, ��� � ���� ���������... ����� �� �������� ����, �� ��� ����� �������. ��� ����� ���� �����?";
			link.l1.go = "Antonio_1_10";
		break;
		
		case "Antonio_1_10":
			dialog.text = "��� ������ �������� �������� � ���� ������ - ����� �� ������������� �� ���, � ���� ����� ��� � ������ � 9 ���� �� ���� ���. �� ���������, ��� ������ ������.";
			link.l1 = "�������� ����, ������. �����!";
			link.l1.go = "Antonio_1_11";
			NextDiag.TempNode = "Antonio_1_12";
		break;
		
		case "Antonio_1_11":
			sld = CharacterFromID("PDM_Octavio_Lambrini")
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Octavio_3_1";
			DeleteAttribute(pchar, "questTemp.PDM_CL_Tavern");
			DeleteAttribute(pchar, "questTemp.PDM_CL_Ishem");
			PChar.quest.PDM_CL_Antonio_Ubit.over = "yes";
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Antonio_1_12":
			dialog.text = "��� ������ �������� �������� � ���� ������ - ����� �� ������������� �� ���, � ���� ����� ��� � ������ � 9 ���� �� 2 ����� ���. �� ���������, ��� ������ ������.";
			link.l1 = "�������� ����, ������. �����!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_1_12";
		break;
		
		case "Octavio_3_1":
			dialog.text = "��, "+ GetSexPhrase("�������","�������") +" - �������, �� ���������"+ GetSexPhrase("","�") +" ����� �������, �� ��������?";
			link.l1 = "��. ���������� ������� ������ ���� � ����������, �� ��� ������ ���� ������.";
			link.l1.go = "Octavio_3_2";
		break;
		
		case "Octavio_3_2":
			if (pchar.name == "�����" && pchar.lastname == "����")
			{
				dialog.text = "��, �������! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� �� ��������� ���������� �� ��������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.name == "������")
			{
				dialog.text = "��, �������! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� �� ����������� ������ �� �����. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.lastname == "����")
			{
				dialog.text = "��, "+ GetSexPhrase("�������","�������") +"! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� �� "+ GetSexPhrase("���","����") +" �������� �����, �������� ������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.name == "�����" && pchar.lastname == "�� ���")
			{
				dialog.text = "��, �������! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� �� ������� ������ ����������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.lastname == "����")
			{
				dialog.text = "��, "+ GetSexPhrase("�������","�������") +"! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� �� "+ GetSexPhrase("���","��") +", ��� �������"+ GetSexPhrase("","�") +" ׸���� ���������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.lastname == "������")
			{
				dialog.text = "��, "+ GetSexPhrase("�������","�������") +"! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� � ���� ����� ����� ������ �������, �������� ������������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.reputation >= 75)
			{
				dialog.text = "��, "+ GetSexPhrase("�������","�������") +"! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� � ���� ��� ������� ��� � ������� ��������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			if (pchar.reputation <= 25)
			{
				dialog.text = "��, "+ GetSexPhrase("�������","�������") +"! ���� ��������� �� �������� ��� ������ � ��������������. ��� ��� �� ������� �������. �� � ���� ���� � ��� - ����������, ���� � ���� ��� ������� ��� � ������������ ��������. ��� ���� " + Plata1 + ". � ��� ��� �������� ������.";
			}
			link.l1 = "��, ������ ����� �� �������� ���� ��������� � ���������, �������. ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_3_3_EsheRaz";
			sld = CharacterFromID("PDM_Octavio_Lambrini")
			sld.lifeday = 0;
			AddMoneyToCharacter(pchar, sti(Plata1));
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, SPAIN, 6);
			AddCharacterExpToSkill(pchar, "Sneak", 160);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			
			sld = CharacterFromID("PDM_CL_Antonio")
			sld.nonTable = true;
			LAi_SetSitType(sld);
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Antonio_2_1";
			ChangeCharacterAddressGroup(sld, "Maracaibo_church", "sit", "sit16");
			LAi_SetLoginTime(sld, 9.0, 13.00);
		break;
		
		case "Octavio_3_3_EsheRaz":
			dialog.text = "�, "+pchar.name+"! � ���������� ���� � ����������� ��� �� ����� �������, �� ��������! � ������ ������� � ����������� � ���������, ����� ��������� ��������� � ��������� ���������.";
			link.l1 = "�����!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_3_3_EsheRaz";
		break;
		
		case "Antonio_2_1":
			dialog.text = "���, ������"+ GetSexPhrase("","���") +" "+pchar.name+", ��� �� ������?";
			link.l1 = "������� �������� ������� � ���� ������, ������ ����� �� ��� ����� ����, � ���������.";
			link.l1.go = "Antonio_2_2";
		break;
		
		case "Antonio_2_2":
			dialog.text = "�������. �������������� ����� ��������� � �������, ��� ����� ����� ���� � ����������, ��������� �� �� ���.";
			link.l1 = "������, � ����� ��� � �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_2_3_EsheRaz";
			
			PChar.quest.PDM_CL_PVT.win_condition.l1 = "location";		//���� � �������
			PChar.quest.PDM_CL_PVT.win_condition.l1.location = "Maracaibo_tavern";
			PChar.quest.PDM_CL_PVT.win_condition = "PDM_CL_PVT";
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Octavio_Lambrini", "barmen_3", "man", "man", 10, PIRATE, -1, false));
			sld.name	= "�������";
			sld.lastname	= "��������";
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Octavio_4_1";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "sit", "sit_front2");
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Pokupatel", "PGG_Barrows_0", "man", "man", 10, PIRATE, -1, false));
			sld.name	= "��������";
			sld.lastname	= "�������";
				
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_1_1";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "sit", "sit_base2");
		break;
		
		case "Antonio_2_3_EsheRaz":
			dialog.text = "�� ���, ������"+ GetSexPhrase("","���") +", �� ������ �������� � �������?";
			link.l1 = "��� ���, � ��� ��� ���� � �������"+ GetSexPhrase("��","���") +".";
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_2_3_EsheRaz";
		break;
		
		case "Pokupatel_1_1":
			dialog.text = "���� ����? �� ������, � �����"+ NPCharSexPhrase(NPChar,"","�") +"?";
			link.l1 = "����� ��������, �� �����"+ GetSexPhrase("","�") +" ���� ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pokupatel_1_1";
		break;
		
		case "Octavio_4_1":
			dialog.text = "(������������ �������. �� � ������ ������ ���� ������ �� ����� �������������� ��������) ...����� ��?";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_1";
		break;
		
		case "Pokupatel_2_1":
			sld = characterFromID("PDM_CL_Pokupatel");
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 0.0);
			DoQuestFunctionDelay("PDM_CL_Sadis_Pokupatel", 0.06);
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_2_2";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Pokupatel_2_2":
			npchar.lifeday = 0;
			dialog.text = "(���������� � �������) ���� ������� ��, ��� �� ����� �� ���� �������� �� ���� �������. � ��� ����� ����� ����� �����! ���� �������, ������ �������, �.";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_3";
		break;
		
		case "Pokupatel_2_3":
			sld = characterFromID("PDM_Octavio_Lambrini");
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 0.0);
			DoQuestFunctionDelay("PDM_CL_Sadis_Octavio", 0.06);
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_2_4";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Pokupatel_2_4":
			npchar.lifeday = 0;
			dialog.text = "(���������� � �������) � ����, � ����� ����� ����� ����. �� ����� ����� ���� � �����, ������������ ����� �������.";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_5";
		break;
		
		case "Pokupatel_2_5":
			sld = characterFromID("PDM_CL_Pokupatel");
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 0.0);
			DoQuestFunctionDelay("PDM_CL_Sadis_Pokupatel", 0.06);
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_2_6";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Pokupatel_2_6":
			if (npchar.sex == "woman")
			{
				dialog.text = "(���������� � �������) � ����������� �����, ������.";
				link.l1 = "";
				link.l1.go = "Pokupatel_2_7";
			}
			if (npchar.sex == "man")
			{
				dialog.text = "(���������� � �������) � ����� ������� ���� �������, ��� ����� ������ ��� ����.";
				link.l1 = "";
				link.l1.go = "Pokupatel_2_7";
			}
		break;
		
		case "Pokupatel_2_7":
			sld = characterFromID("PDM_Octavio_Lambrini");
			LAi_CharacterDisableDialog(sld);
			sld = characterFromID("PDM_CL_Pokupatel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "tables", "stay3");
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			sld = CharacterFromID("PDM_CL_Antonio")
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Antonio_5_1";
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		
		case "Antonio_5_1":
			dialog.text = "������"+ GetSexPhrase("","���") +" "+pchar.name+", �� ����� ������ ���������. ������ ���-������ ����������?";
			link.l1 = "��, �������� ��� � ������ � ��������� ���� ����� ���������. � �����"+ GetSexPhrase("","�") +" ���������� ��� �������� � ���������, ������� ���������� ������� ����������� � ������� ����� - ������. ����� ����� ����������� � ������� � �������� ��������, ����������?";
			link.l1.go = "Antonio_5_2";
		break;
		
		case "Antonio_5_2":
			dialog.text = "���! �� ����� ��� �������� ������. ��� ��� ��������� � �����, ������ � ������ �������, �����, ��� �� ������ �� ��������. ���-�� ���������� �� � ������������ ����. � �� ������ ������, ��� ��� ���������� ������� ���� ����� ����?";
			link.l1 = "��� ���������� � ����� �������.";
			link.l1.go = "Antonio_5_3";
		break;
		
		case "Antonio_5_3":
			dialog.text = "�������! �������� ������������, �� ������� ������ �� ������� �������� � �������� �� ��������, ��� �� ����� ����� � ������ �� ������� �� �������?";
			link.l1 = "����� ����� �������.";
			link.l1.go = "Antonio_J_1";
			link.l2 = "����� �� ��������, ��� ����� �������.";
			link.l2.go = "Antonio_M_1";
		break;
		
		case "Antonio_J_1":
			dialog.text = "(����������� �������...)";
			link.l1 = "�����!";
			link.l1.go = "exit";
		break;
		
		case "Antonio_M_1":
			dialog.text = "����� �� ����� �������. ������ ���� � ����� �������! (����������� �������...)";
			link.l1 = "�����!";
			link.l1.go = "exit";
		break;
		
		
	}
}