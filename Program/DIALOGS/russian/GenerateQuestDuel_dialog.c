
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string sName = PChar.name + " " + PChar.lastname;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "��� ��� ����?";
			link.l1 = "������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		// ������ ������� -->
		case "Duelist_1_1":
			dialog.text = "������������, ������� " + sName + ". �������, � ��� ������� ��������� ����� ��� ���������?";
			link.l1 = "�����������, ������. � ��� ���������?";
			link.l1.go = "Duelist_1_2";
            PlayVoice("Voice\Russian\cit_quest_" +(1 + rand(3))+".wav");
		break;

		case "Duelist_1_2":
			dialog.text = "���� � ���, ��� �� ������� � ���� ��������� �����, � ����� ���������...";
			link.l1 = "� � ��� �� ���� ��������?";
			link.l1.go = "Duelist_1_3";
		break;

		case "Duelist_1_3":
			dialog.text = "���������... ��� �� �� �������� ������ ������� � ���. � ������ ������������, �� �� ���� ��� ����� � �� ����� � ���������� �� ����. � �������, ���...";
			link.l1 = "��� � ���� ��������� ������ ���?";
			link.l1.go = "Duelist_1_4";
		break;

		case "Duelist_1_4":
			dialog.text = "���������� �����. � ������� ���.";
			link.l1 = "� �������?";
			link.l1.go = "Duelist_1_5";
		break;

		case "Duelist_1_5":
			dialog.text = sti(PChar.GenerateQuestDuel.Money) + " ��������.";
			link.l1 = "� � ����� �������.";
			link.l1.go = "Duelist_1_7";
			link.l2 = "��-��-��! �� ���� ����� ���������� ����.";
			link.l2.go = "Duelist_1_6";
		break;

		case "Duelist_1_6":
			dialog.text = "�� �������!";
			link.l1 = "�����. ��� ��� ������������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelManCancel");
		break;

		case "Duelist_1_7":
			dialog.text = "�������� �������, �������. ����� ��������� �� ���������� ��������. ����� ������ - �����.";
			link.l1 = "�����.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelAgree");
		break;

		case "Duelist_1_8":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Wife));
			dialog.text = PChar.GenerateQuestDuel.WifeName + ", ��� ��� �����?";
			link.l1 = PChar.GenerateQuestDuel.WifeName + ": "+ GetSexPhrase("�������, ���� ������� ���������� ������ ���.","�������, ��� ���� ����������� ������ ���.") +"";
			link.l1.go = "Duelist_1_9";
		break;

		case "Duelist_1_9":
			SetCameraDialogMode(NPChar);
			dialog.text = "������ � ���?!";
			link.l1 = "������, � ������ ����� ������� ���������� ��� �� �����.";
			link.l1.go = "Duelist_1_10";
		break;

		case "Duelist_1_10":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Wife));
			dialog.text = "�� ���� �� ����� ���� � ����. ����� ���������, ���� ���� ���� ������� �������� ��������� ������ ����. ������ ���� �����, �������, � � ������ ����� ����� ������!";
			link.l1 = PChar.GenerateQuestDuel.WifeName + ": " + PChar.GenerateQuestDuel.DuelistName + ", ����� ����, ���� ���� ������, �������� � ����� �� �������!..";
			link.l1.go = "Duelist_1_11";
		break;

		case "Duelist_1_11":
			SetCameraDialogMode(NPChar);
			dialog.text = "� ���� ������� ���� ���� � ���� ����� ����. �� ���� � ������!";
			link.l1 = "�� ����. � ����, ��� ����� ������ �������������. � ������� ��������� ��� ���� ������������ ������.";
			link.l1.go = "Duelist_1_12";
		break;

		case "Duelist_1_12":
			dialog.text = PChar.GenerateQuestDuel.WifeName + ": ��� �� �����! " + PChar.GenerateQuestDuel.DuelistName + ", ����������! \n � ����������� ��������������� ��� ������������ �����. � ������ ����, � ���� �� ������ ����, �� �������� � � ����� ��������� ����������.";
			link.l1 = "���� ������. ����, �� " + sti(PChar.GenerateQuestDuel.Money) + " �������� � � ����� �������. ��� ��������� �����?";
			link.l1.go = "Duelist_1_13";
		break;

		case "Duelist_1_13":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Wife));
			dialog.text = "�� ���������� ��������. �����, �������, ����� ������. " + PChar.GenerateQuestDuel.WifeName + ", �� ���������� ����. \n " + PChar.GenerateQuestDuel.WifeName + ": ����� ��� �������, �������...";
			link.l1 = "��� ����.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelWoman2Agree");
		break;

		case "Duelist_1_14":
			dialog.text = "�������, �� ���� ��� ��� � �����������! �� ������ ��� �����. ���� ������ �� ������� �� ��� � �����!";
			link.l1 = "��������� �������, ���� ����� �������� � "+ GetSexPhrase("��������","���������") +"?";
			link.l1.go = "Duelist_1_15";
		break;

		case "Duelist_1_15":
			dialog.text = "���, �������� ��� ������. ��� ��� ��������� ���, �������!";
			link.l1 = "�� �������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithMercenaryHappyEnd");
		break;

		case "Duelist_1_16":
			dialog.text = "�� ����, ��� � ����������� ���, �������! �������� ������ �... �������, ����� �� ������ ������ �����?";
			link.l1 = "�� ������������, � �� �� ���������. �� �������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithDuelistHappyEnd");
		break;
		// ������ ������� <--
		
		// ���� ������� �������� -->
		case "Wife_1":
			dialog.text = "�������! ������ ���, ��������!";
			link.l1 = "��������, ����� ���, �����������. ��� ���������?";
			link.l1.go = "Wife_2";
            PlayVoice("Kopcapkz\Voices\Events\Jungle_woman_hlp_0" +rand(9)+".wav");
		break;
		
		case "Wife_2":
			dialog.text = "��� ��� ��������� � ������� � ����� ����� ��� ������, ��� ��� ������ ��������� � �� �����. " + PChar.GenerateQuestDuel.DuelistName + " ����� ������� ������. ��� �����, � �������!";
			link.l1 = "�������. �� ������, ��� �� � �������"+ GetSexPhrase("","�") +" ������ ���� � �������?";
			link.l1.go = "Wife_3";
		break;
		
		case "Wife_3":
			dialog.text = "��! � ������� ��� " + sti(PChar.GenerateQuestDuel.Money) + " ��������, ������ ���������� ��� �� �����.";
			link.l1 = "� ��������. ������ ���� � ������ ����.";
			link.l1.go = "Wife_5";
			link.l2 = "��������, �� ��� �� �� ���. ������� ������� �����������.";
			link.l2.go = "Wife_4";
		break;
		
		case "Wife_4":
			dialog.text = "�� �������� �������!";
			link.l1 = "��.. ��� ��������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelWomanCancel");
		break;
		
		case "Wife_5":
			QuestDuelWomanAgree();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// ���� ������� �������� <--
		
		
		// ������ ������� -->
		case "Duelist_2_1":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
			dialog.text = "���, ������! ���!";
			link.l1 = PChar.GenerateQuestDuel.DuelistFullName + ": � ������ �����������!";
			link.l1.go = "Duelist_2_2";
		break;
		
		case "Duelist_2_2":
			SetCameraDialogMode(NPChar);
			dialog.text = "�� ������ �������������. ��� ��� � ����?";
			link.l1 = PChar.GenerateQuestDuel.DuelistFullName + ": ���� ������� ����� ������� ������ ����.";
			link.l1.go = "Duelist_2_3";
		break;
		
		case "Duelist_2_3":
			dialog.text = "��� ���� �����. �� � ������ ���� �������� "+ GetSexPhrase("��� ����������","��� �������") +". ����� �� ������� - "+ GetSexPhrase("�������� ������������","�������� �������������") +". \n " + PChar.GenerateQuestDuel.DuelistFullName + ": � ����� �����. �������, �� ������?";
			link.l1 = "� �����, �������, �������.";
			link.l1.go = "Duelist_2_4";
		break;
		
		case "Duelist_2_4":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Mercenary));
			dialog.text = "������: ��� ��, ������������� � ������. �����!";
			link.l1 = "�����!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithMercenary");
		break;
		
		case "Duelist_2_5":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
			dialog.text = "׸�� ������!!! ������� �� �������������?";
			link.l1 = PChar.GenerateQuestDuel.DuelistFullName + ": ������. � ������ ����������. � �� ������� ������ �������� �� ���.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithMercenaryEnd");
		break;
		
		case "Duelist_2_6":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
			dialog.text = "�����������, �������! " + PChar.GenerateQuestDuel.DuelistName + ", � ��� ��� � ����?";
			link.l1 = PChar.GenerateQuestDuel.DuelistName + ": "+ GetSexPhrase("���� �������","��� �������") +" ����� ������� ������ ����.";
			link.l1.go = "Duelist_2_7";
		break;
		
		case "Duelist_2_7":
			dialog.text = "���� ���! � �� ���������� ����, " + PChar.GenerateQuestDuel.DuelistName + ". �� ����, �� ����...";
			link.l1 = PChar.GenerateQuestDuel.DuelistName + ": �������� ������ �������! ������� ��������� ������������ �������� ���������� ���.";
			link.l1.go = "Duelist_2_8";
		break;
		
		case "Duelist_2_8":
			SetCameraDialogMode(NPChar);
			dialog.text = "��� ��, ����� � �������� "+ GetSexPhrase("������ �����������","���� ���������") +", ���� ����� ������ � ����� ��������. �����?";
			link.l1 = "� ����� �������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithDuelist");
		break;
		// ������ ������� <--
		
		// ������������ -->
		case "Relative_1":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Relative_1));
			dialog.text = "��� ����� ���������?";
			link.l1 = "��� �� �����?";
			link.l1.go = "Relative_2";
            PlayVoice("Kopcapkz\Voices\Events\Captive_0"+(1 + rand(9))+".wav");
		break;
		
		case "Relative_2":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Relative_2));
			dialog.text = "�� �� ������! ��� ���� ����! "+ GetSexPhrase("��������!!! ��� �� ��������?","��������!!! ��� �� ���������?") +"";
			link.l1 = "��������, � ������ �� �������...";
			link.l1.go = "Relative_3";
		break;
		
		case "Relative_3":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Relative_1));
			dialog.text = "� ����� � ���� �����!!!";
			link.l1 = "�� ��� �� �� ��� ���� ����� ������...";
			link.l1.go = "Relative_4";
		break;
		
		case "Relative_4":
			SetCameraDialogMode(CharacterFromID(PChar.GenerateQuestDuel.Characters.Relative_2));
			dialog.text = "���������, ������!";
			link.l1 = "׸��!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestDuelBattleWithRelativeRevenge");
		break;
		// ������������ <--
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
