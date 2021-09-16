
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string sName = GetNameLugger(PChar, "f");
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "��� ��� ����?";
			link.l1 = "������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// ����� ����� -->
		case "Fisher_Pedro_1":
			dialog.text = "...(���� �� �����)... � �� ���� ��? ���� ������ ������������ ��� �����? �����, ���� ����?";
			link.l1 = "���������� ������� ��������� � ����� ���������� ����.";
			link.l1.go = "Fisher_Pedro_2";
		break;
		
		case "Fisher_Pedro_2":
			dialog.text = "���? ��� �� ������ ��� ����������?";
			link.l1 = "���������� ������� ��������� � ����� ���������� ����.";
			link.l1.go = "Fisher_Pedro_3";
		break;
		
		case "Fisher_Pedro_3":
			dialog.text = "...(���������)... �������, �� ��� ����� �������, ��� �������� � �����?";
			link.l1 = "��, ��� �. � ���� ���� ���-������ ��� ����?";
			link.l1.go = "Fisher_Pedro_4";
		break;
		
		case "Fisher_Pedro_4":
			TakeNItems(PChar, "Dozor_Mekakhrom", 1);
			dialog.text = "��, ��� �����! ��� ������ ��������.";
			link.l1 = "�������. ����� ����.";
			link.l1.go = "Fisher_Pedro_5";
		break;
		
		case "Fisher_Pedro_5":
			dialog.text = "�-�, �������, ��������! � ��� �������� �� ����� 50 ������� ��� ������� ������?";
			
			if(sti(PChar.money) >= 50)
			{
				link.l1 = "������ ������, ��� ��������� �� � ����, � �� �������� ��� �� ����������, ����?";
				link.l1.go = "Fisher_Pedro_6";
			}
				
			link.l2 = "�������� �� �����. ������.";
			link.l2.go = "Fisher_Pedro_9";
		break;
		
		case "Fisher_Pedro_6":
			dialog.text = "����! ����� �� ������!";
			link.l1 = "��! �� ��� ������������� �����, ��� � ���� �� ���? ����� ������ ����.";
			link.l1.go = "Fisher_Pedro_7";
			link.l2 = "��� ����� � ������. � ���� ��� ������� � ����� ��� �������.";
			link.l2.go = "Fisher_Pedro_8";
		break;
		
		case "Fisher_Pedro_7":
			dialog.text = "�� ��! �� ��, ������ �������! �������" + GetSexPhrase("��","��") +" �������" + GetSexPhrase("����","����") +" " + GetSexPhrase("�������","�����") +"! ��������! ...(������)... ��������!";
			link.l1 = "���������� � ���� ����, �����������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorFisherPedroExit");
		break;
		
		case "Fisher_Pedro_8":
			AddMoneyToCharacter(PChar, -50);
			DozorFisherPedroExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fisher_Pedro_9":
			DozorFisherPedroExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// ����� ����� <--
		
		// ������ ������ � ����� ������ -->
		case "Grot_Agent_Killers_1":
			SetCameraDialogMode(CharacterFromID("Dozor Grot Agent Killer 2"));
			dialog.text = "�������: �� ������ �� ��� ���������, ������, ��� � ����� ��������� �� �����.";
			link.l1 = "";
			link.l1.go = "Grot_Agent_Killers_2";
		break;
		
		case "Grot_Agent_Killers_2":
			SetCameraDialogMode(CharacterFromID("Dozor Grot Agent Killer 1"));
			dialog.text = "������: � � ������, ��� ��� ����� ������ ����. ������ ��� ����� ��������...";
			link.l1 = "";
			link.l1.go = "Grot_Agent_Killers_3";
		break;
		
		case "Grot_Agent_Killers_3":
			SetCameraDialogMode(CharacterFromID("Dozor Grot Agent Killer 2"));
			dialog.text = "�������: ...(���������)... �� �����-�� ��� � ��� ������!";
			link.l1 = "";
			link.l1.go = "Grot_Agent_Killers_4";
			AddDialogExitQuestFunction("DozorBattleInTerksGrot");
		break;
		
		case "Grot_Agent_Killers_4":
			SetCameraDialogMode(CharacterFromID("Dozor Grot Agent Killer 1"));
			dialog.text = "������: ...(������ ����)... ��������� ������. ����� � ��� � ����!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorBattleInTerksGrot");
		break;
		// ������ ������ � ����� ������ <--
		
		// ����� ��� -->
		case "Spanch_Bob_1":
			dialog.text = "�-��? ���� ����?";
			link.l1 = "�������� ������� ������� � ������� � ���������� ��������.";
			link.l1.go = "Spanch_Bob_2";
		break;
		
		case "Spanch_Bob_2":
			dialog.text = "�-�! �������, " + GetSexPhrase("���","���") +" " + GetSexPhrase("����","�������") +"?";
			link.l1 = "�� ��� �����" + GetSexPhrase("","�") +" ���������, �����������.";
			link.l1.go = "Spanch_Bob_3";
		break;
		
		case "Spanch_Bob_3":
			dialog.text = "� ��������� �����" + GetSexPhrase("","�") +"! ��������� � ���� � ��� ���� �����, ������� ���� ������. ��������� ��� ����. �� ������ �� ����� �� ����� ����� �������. �� ����� ���������, �� �� ���� �����, �� ��� �����-������ ������� ������������.";
			link.l1 = "� ��� � ������ ����� ���� �����������?";
			link.l1.go = "Spanch_Bob_4";
		break;
		
		case "Spanch_Bob_4":
			dialog.text = "�������! � �� ����� �� ����" + GetSexPhrase("","�") +"?";
			link.l1 = "�� ����" + GetSexPhrase("","�") +", � ������� ����� �� ����.";
			link.l1.go = "Spanch_Bob_5";
		break;
		
		case "Spanch_Bob_5":
			dialog.text = "��, ������� ��, ���. �� �����, ����� ���� �����... �-��! � �����, ��������, " + GetSexPhrase("����","��������") +"!";
			link.l1 = "��! � ��� �� ��������� ��������?";
			link.l1.go = "Spanch_Bob_6";
		break;
		
		case "Spanch_Bob_6":
			dialog.text = "����-���? ��������?";
			link.l1 = "�� ������ ��� �������� ��� ���, ��� ��������� �������.";
			link.l1.go = "Spanch_Bob_7";
		break;
		
		case "Spanch_Bob_7":
			dialog.text = "�-�, ��� ����������� �����... ������. ������, " + GetSexPhrase("�������","������") +", ������ � ��� �� ����.";
			link.l1 = "���?! ������? ������ � ������� ������, ��������� ������? � ���, ��-������, ���� ���������� ����" + GetSexPhrase("��","��") +", �?!";
			link.l1.go = "Spanch_Bob_8";
		break;
		
		case "Spanch_Bob_8":
			dialog.text = "�� �� �������� �� ���!";
			link.l1 = "� 20 ���� �������" + GetSexPhrase("","�") +" �� ����! �� � ���� ������ ������ ��������, ������!";
			link.l1.go = "Spanch_Bob_10";
		break;
		
		case "Spanch_Bob_10":
			dialog.text = "��! ���� �� ���� �����! �-��! ���� �������� ���, � ������ ����!";
			link.l1 = "� ��� �� ����������� ��� ������?";
			link.l1.go = "Spanch_Bob_11";
		break;
		
		case "Spanch_Bob_11":
			dialog.text = "���� ���� ��� ���� �����, � ���� ������� �����, � � ������ �����.";
			link.l1 = "� ��� � ������ �������� ����� ��� ���������?";
			link.l1.go = "Spanch_Bob_12";
		break;
		
		case "Spanch_Bob_12":
			dialog.text = "� ���� � �����, ���� ������� ����������. � � ������ ��������.";
			link.l1 = "��� ���? ��� ������, �� �������� �� ������� � ���������?";
			link.l1.go = "Spanch_Bob_13";
		break;
		
		case "Spanch_Bob_13":
			dialog.text = "� ���� ��� �����������? ��� � ��������� ������, ��� ����������� �����, ��� ������ ��������, ���� ����������, � ���� ������� ''�������'' ����� �� 5 ����� ���������.";
			link.l1 = "...(����� �������)... ��� �����, �� ��� ����� ������� �������� �����, � ����������� ���� � ���!";
			link.l1.go = "Spanch_Bob_14";
		break;
		
		case "Spanch_Bob_14":
			dialog.text = "�, ��� " + GetSexPhrase("����","��������") +"! ��������� �������� ������ ������ ������, �������! ��� ���� �������. ...(�������� � ������� ������) \n ��� ����������, ������ ��� �����. ���� ����������, � ������ ���� �������� �����, ���� ���... ��� ��, �� ��� � ���� ���. � ������ �� ������ 500 �������! ��� ��� �������� ����� �� �����.";
			link.l1 = "...(����)... �� ������, �������� ������!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorGuadeloupeShoreGetTask");
			NextDiag.TempNode = "Spanch_Bob_15";
		break;
		
		case "Spanch_Bob_15":
			dialog.text = "����" + GetSexPhrase("��","����") +" ������?";
			
			if(sti(PChar.money) >= 500)
			{
				link.l1 = "��� ���� �������, ��������.";
				link.l1.go = "Spanch_Bob_16";
			}
			
			link.l2 = "� ���� �� ������ ���. ������� �����.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Spanch_Bob_15";
		break;
		
		case "Spanch_Bob_16":
			AddMoneyToCharacter(PChar, -500);
			dialog.text = "���, ������ ��������! ����, �������, ����� ������� �� ������ �������? �������� ��� ������ ����� � � ��� ��� �������� �����.";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Spanch_Bob_17";
		break;
		
		case "Spanch_Bob_17":
			string sString = GetStrSmallRegister(dialogEditStrings[1]);
			if(sString == "����� ������")
			{
				dialog.text = "�����! �������� ����� - ''���������� ������� �������� �������''.";
				Link.l1 = "������!";
				Link.l1.go = "exit";
				AddDialogExitQuestFunction("DozorToDeadShoreInMein");
			}
			else
			{
				dialog.text = "���, ������� �� �������. ���������� ���.";
				link.l1 = "׸�� ������!";
				link.l1.go = "exit";
				NextDiag.TempNode = "Spanch_Bob_18";
			}
		break;
		
		case "Spanch_Bob_18":
			NextDiag.TempNode = "Spanch_Bob_18";
			dialog.text = "����, �������, ����� ������� �� ������ �������? �������� ��� ������ ����� � � ��� ��� �������� �����.";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Spanch_Bob_17";
		break;
		// ����� ��� <--
		
		// ������� ������ � ��������� -->
		case "Justin_Butt_1":
			dialog.text = "�� �������" + GetSexPhrase("","�") +", �������" + GetSexPhrase("","�") +"! ������ �������� �� �������, ������ ������ ���� � �����!";
			link.l1 = "������ �� ����� �� ����? �������!";
			link.l1.go = "Justin_Butt_2";
		break;
		
		case "Justin_Butt_2":
			dialog.text = "� ����� ���������, �������?";
			link.l1 = "��� ����� �������? ���� � ���, ��� � ����" + GetSexPhrase("��","��") +" ���" + GetSexPhrase("","�") +" ���� ����� ��������?";
			link.l1.go = "Justin_Butt_3";
		break;
		
		case "Justin_Butt_3":
			dialog.text = "����� ��� � ����� �������? �� ���, �� ���������, ��� ����� ����������?";
			link.l1 = "��, �������, ��, �������, ������!";
			link.l1.go = "Justin_Butt_4";
		break;
		
		case "Justin_Butt_4":
			dialog.text = "�� � ����� ���������, ���������?";
			link.l1 = "���������?";
			link.l1.go = "Justin_Butt_5";
		break;
		
		case "Justin_Butt_5":
			dialog.text = "��! ��-������ ���� ������, ��� �� ������� ������� �� ����. ��� �� ��� �� �� �������" + GetSexPhrase("","�") +" ���� � ������� ���, �������� ����. ���������, �� �� " + GetSexPhrase("����","����") +" � ���� ����, ������ ���� � ����, ���� ��� ��� ��������, ������� ������ � �����. \n ���� ������, ����������� ����, ��������� ������� � ��� ���� ���� ���������, ������� ������� ����� �� ��������, ���� �� ��� ���. � ���� �� ��� �����������.";
			link.l1 = "� � ����� ������ ������������� ��� ��?";
			link.l1.go = "Justin_Butt_6";
		break;
		
		case "Justin_Butt_6":
			dialog.text = "�����. ������ ���, ������, �� ���� ��������, ��� ������ ����, ����� ������ ���-�� ���. �� � ��������� �� ��� � ������� ��� ���, ����� ���� ���� ���, � ���� ��������� �� ���������� ���������.";
			link.l1 = "� ��� � ���� ���������?";
			link.l1.go = "Justin_Butt_7";
		break;
		
		case "Justin_Butt_7":
			dialog.text = "� �������� ���� �����������, ����� ����. ���� ������� � ������, ��� ������ ��� ������� �� ������, ������ ������ � ������-����, �������� ��������� ���� �������. ��� ������ � ����� ���� ��������. \n �� ����� � ��������� ����� ����, ��� �� ������� ����, �� ����� �� ��� �������� ������� �� ������� � ���� ����������. �� ����� �� ��� ������� ��������, ��� ������� ���� ���� ���� ����. � ������ �������� ������� � �� ���� ������� �������� �� ���������.";
			link.l1 = "������ ������� ���������? ����������, ��� � ���������� ������ ���� ���������?";
			link.l1.go = "Justin_Butt_8";
		break;
		
		case "Justin_Butt_8":
			dialog.text = "��, � ������� ������ ���� �� ������ ����������. ��� ������ ���� ������ �� ��������� �������, ��� ������ �� �������� �����.";
			link.l1 = "� ��� �� �����? � ���" + GetSexPhrase("��","��") +" ��� ���� ���� �������� - � ��������, �������, ��-��������, ����� ������.";
			link.l1.go = "Justin_Butt_9";
		break;
		
		case "Justin_Butt_9":
			dialog.text = "���� �� ����, ���� �� ����. � ������� ���� �����, ������� �� ����� ����� ���� � ��������� ��������� ������. ���� �� ���, ���� �� �����, � ��� �������, � ���� ������ ��������� �� ��������, ������� ��� � ����� ������, �������" + GetSexPhrase("","�") +" ��. � ����� ����������������� ��� ��������� ����������� � ������.";
			link.l1 = "� ����? ������ �� �����, ��� � �������� ���� �� ��� ���?";
			link.l1.go = "Justin_Butt_10";
		break;
		
		case "Justin_Butt_10":
			dialog.text = "�� ����� ���� ��� �����, ������ � ���� ���� ������ ������. �� ������ ����, �������� ������ ���� ����� �������� � �������, �� �������� �������. � ���� ��� ��� �����, �� ��� ���� ����, ���, ��� ��� ���� ������ ������, �� ���������� ������ ���� ���������. \n � ������� ����������� � ����� ������. �� ��������� ���, ��� ������ ��� ������� �� ���� � ������������ ���������, ������ ���, ����� ����, ��� ��������� �������� ��� ������.";
			link.l1 = "�� ���� ����� ����, ��� � ���" + GetSexPhrase("��","��") +" ��������, �� ������� �����, ����� �� ��� �����?";
			link.l1.go = "Justin_Butt_11";
		break;
		
		case "Justin_Butt_11":
			dialog.text = "���������, � ����� ����, ��� � ���� ������ ��������, �� ������� ������, �� ��� ��� ��������� ��� ������ �� ��������, �� � ��������, � �����, ���� ����������.";
			link.l1 = "�� ��� ����?";
			link.l1.go = "Justin_Butt_12";
		break;
		
		case "Justin_Butt_12":
			dialog.text = "��, � ����� ��������� ��� � �����? � �������� � ����� ������ ���, ���� ������ ���� �������. ������ � ����� ������� � ���������, ������� � ��������� � ����. ��� ������ ������ ������ �� ��� ������ � ��� �������� �� �� ������. ���� ��������� ������� � ������� � �����.";
			link.l1 = "� ������, � ���� ��� � ������ ��������� ���� � �����, ����� ���� ��� �� ��������. ���������!";
			link.l1.go = "Justin_Butt_13";
		break;
		
		case "Justin_Butt_13":
			TakeNItems(PChar, "Dozor_Mekakhrom", -1);
			dialog.text = "� �� �����"+ GetSexPhrase("","�") +", ��� � ��������� ��������� ���� ��� ��� ������ ����? ׸��� � ���!";
			link.l1 = "��, ��������, �������!";
			link.l1.go = "exit";
			
			PChar.Dozor.CabinID = PChar.location;
			Locations[FindLocation(PChar.location)].box1.items.Dozor_Key = 1;
			Locations[FindLocation(PChar.location)].box1.items.Dozor_Mekakhrom = 1;
		       
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam");
		break;
		// ������� ������ � ��������� <--
		
		// ���������� � ���� -->
		case "NoName_1":
			dialog.text = "�� ����" + GetSexPhrase("��","���") +", ��� �������� �� ���������, ������" + GetSexPhrase("��","��") +". ����������!";
			link.l1 = "��� �� �����?";
			link.l1.go = "NoName_2";
		break;
		
		case "NoName_2":
			dialog.text = "� �� ������� ����������, ������������ ���� ����, ������� ���?";
			link.l1 = "����� ������ �����. �� ������, ��� ������� �����?";
			link.l1.go = "NoName_3";
		break;
		
		case "NoName_3":
			dialog.text = "��� ���?";
			link.l1 = "� ��������� �� ����������� � ����� ���������. �� ��������� ���, ��� �� ���� ����������, ���� ��������� ��������, � ����� ��������� �������. ����� ���������� � ����, �� �� �����.";
			link.l1.go = "NoName_4";
		break;
		
		case "NoName_4":
			dialog.text = "����, ������ ��� �������� ���������, ����������, ������, ��������������.";
			link.l1 = "� ������, ��� �� ������ �� ���, �������� � ��� ����, �� ������, ��� ����� ���������?";
			link.l1.go = "NoName_5";
		break;
		
		case "NoName_5":
			dialog.text = "��� �� �������� ���������� ��� �����, ��� ����, ��� �� ������ ���������� �� ����������� �����������, � ���������� ���� ����� ������.";
			link.l1 = "� � ����� �� ����� �� ������" + GetSexPhrase("���","����") +", ��������.";
			link.l1.go = "NoName_6";
		break;
		
		case "NoName_6":
			dialog.text = "� ��� ������� ������� ���� ��� ������, � ������������� ��� �������� �� ����� ����. ������ ������, � ���, ��� ��� ������� ���������� ��� - �� ����� ������ ���� �����.";
			link.l1 = "� ��� � ��� �� ���� � ����? �� ���� �����?";
			link.l1.go = "NoName_7";
		break;
		
		case "NoName_7":
			dialog.text = "����� � ��� �������. ������-�� � �������� �������, ��� ������ ����. � ������ ��� ����������� ���������� ������ �������� ����, �������� ��� ������� �� ����, ������ � ������ ����� ���� � ��������� ���.";
			link.l1 = "�� ���� ��, ��� ������ ������� ���� ����� ���� ���� �������� �� ����?";
			link.l1.go = "NoName_8";
		break;
		
		case "NoName_8":
			dialog.text = "�����. ����, ��� �����" + GetSexPhrase("��","�") +" " + GetSexPhrase("����������","���������") +", ���������� ����� ������� ���� - 3 ������ ���� � 100.000 �������, ������� � ������ ������� ���� �������. ������� ���������� ��������� ����, ������� �������� 1 ������ ���� � ������� �������� �� ����. \n �������� �� ���������� ����� �� ����, � ��������� ������ ���� ���� �� � ���. �� ��� ��� ����� ����� ���� �� �����, �� ��� ������ ���������.";
			link.l1 = "� ������ ������ ���� ���� �����������? ���� �� ���� ������� ���-�� �������� �� ����?";
			link.l1.go = "NoName_9";
		break;
		
		case "NoName_9":
			dialog.text = "��, ���� ������ ���� ����, ������ ����� �������� ��� 3 �������� �����������..";
			link.l1 = "�������, �� �� ���� ��� ������ ��������� ��� �������, � ������� �� ������" + GetSexPhrase("","�") +" � ������.";
			link.l1.go = "NoName_10";
		break;
		
		case "NoName_10":
			dialog.text = "� ������� �� ���� �� ���" + GetSexPhrase("","��") +". � ����� ����, ��� �������, ������� ���� ���� �������. � �� ������, ��� ��������� ���������� ����-����� - �� ����� ������ ������. ������� �� �� �����, ������ �� ������ ���� ����� � ������������� ����-�����. ��� ������, ����� ������ �� ����� - � ����� �����" + GetSexPhrase("��","���") +" ������ " + GetSexPhrase("����","����") +" ��. ";
			link.l1 = "� ��� � ����� ����� ������. ���� ������� �����, ������, ���� ������ �� ����� �����������?";
			link.l1.go = "NoName_11";
		break;
		
		case "NoName_11":
			dialog.text = "������������� ��� �� ������ ����� �, ��... ���� ������������� ��, ��� ��� ������� ����� ����� ������� ��-�� ���� ����. ������� ������, ������ �����, ����� ������.";
			link.l1 = "�����, ��� ���������� �������.";
			link.l1.go = "NoName_12";
		break;
		
		case "NoName_12":
			dialog.text = "���, ��� �� �� ���� �����������. ������� �� ����. ����� ���!";
			link.l1 = "��������� ����������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorHappyEnd");
		break;
		// <-- ���������� � ����
		
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
