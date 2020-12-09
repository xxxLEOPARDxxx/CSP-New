// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), "������ ������� �� �������� ������ ��� ������ " + GetAddress_Form(NPChar) + "...", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������...",
                          "����������, ���� �� �� �� ����� �����, �� �� ����� ���� ��������� ��������.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� ��, ������������� � ������ ���...", "��������, �� �������� ���� ���� ������ �� ����������.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = "� ��� ������� ���, �� � ��� �� �������?";
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_noMoney")
			{
				link.l1 = "� ���"+ GetSexPhrase("��","��") +" ������!";
				link.l1.go = "PL_Q3_7";
			}
		break;
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat("������ ���? �������, � ��� ����� � ���� ���� ����������� ����� ���, ��� �� � ����, ����������, ����������.", 
				"�� ��� �������� �� ��� ����!", 
				"���������� ���������� ��������� ���� � �� ��.",
                "��, ������"+ GetSexPhrase("","�") +"...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("� �� ������, ���� ���� ����� �����������?", 
				"��, � �����.",
                "������...", 
				"�������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = "�����-�� ����, �� �� ���������, - ���������� ����� �������� � �� ���� �����...";
			link.l1 = "�� ��� ����� ����� ��� �����! � ���� � ���� ���� ������� ��������!";
			link.l1.go = "PL_Q3_out";
			link.l2 = "���� � ���, ��� � �����"+ GetSexPhrase("��","��") +" ����������"+ GetSexPhrase("�","��") +" ������� ���, � ����� �������� ��� � ������� ������. �� ��, ��� ���������� �������, �� ���������, ����� ��-�� ��������������� ����� ��� �� ����� ���������� � ���������...";
			link.l2.go = "PL_Q3_3";
		break;

		case "PL_Q3_out":
			dialog.text = "�����...";
			link.l1 = "�-�-���, ������!..";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "6");
			AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("","�"));
			pchar.questTemp.piratesLine = "KillLoy_notFound";
			QuestSetCurrentNode("Henry Morgan", "PL_Q3_notFound");
		break;
		case "PL_Q3_3":
			if (GetCharacterSkill(pchar, "Sneak") >= 60 || GetCharacterSPECIAL(pchar, "Charisma") > 6)
			{
				dialog.text = "��, ��� ������� ��������, � ��� ������. ����� ����������� �� �������.";
				link.l1 = "�������� ��� �������! �� ���� �� �������������, ��� ��� ���� �������! �������.";
				link.l1.go = "exit";
				AddQuestRecord("Pir_Line_3_KillLoy", "7");
				pchar.questTemp.piratesLine = "KillLoy_toBermudes";
			}
			else
			{
				dialog.text = "�� ��, �������. ��� ��� ��� ������������ ������ ��� ������ �������������, ��� ��������� �������, � � ������ ���� ������! ��� ��, ���������� ���-������ ������.";
				link.l1 = "����� ����, ��������� ������������� � ���� ������������� ������ ��������� ���������� ������� ��� ������ ���� ���������� ����� � ����� ������?";
				link.l1.go = "PL_Q3_4";
			}
		break;
		case "PL_Q3_4":
			dialog.text = "�-�-�... �� ��� �, ��� �� �� �����������, �� ����� � 15 ����� ����� �� �������������� ��� ��������� �������� �� ��������� ������...";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "����� ��������?! ��� ��� �������.";
				link.l1.go = "PL_Q3_5";
			}
			else
			{
				link.l1 = "��, � ���� ��� ������ � ����� ����� �����!";
				link.l1.go = "PL_Q3_6";
			}
		break;
		case "PL_Q3_5":
			dialog.text = "��� ����� ���������� �� �������...";
			link.l1 = "�����"+ GetSexPhrase("","�") +". ������� �� ��������� ������� � ����� �������� ���������. ��������.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "7_1");
			pchar.questTemp.piratesLine = "KillLoy_toBermudes";
			AddMoneyToCharacter(pchar, -15000);
		break;
		case "PL_Q3_6":
			dialog.text = "������, ��� �������� �� ���������. �� ����������, � �������...";
			link.l1 = "��, �� �����. � ��������� ������!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "8");
			pchar.questTemp.piratesLine = "KillLoy_noMoney";
		break;
		case "PL_Q3_7":
			if (sti(pchar.money) >= 15000)
			{
				dialog.text = "����� ������!";
				link.l1 = "��� ���� 15 �����. ������� ���, ��� ������.";
				link.l1.go = "PL_Q3_5";
			}
			else
			{
				dialog.text = "��, �� ���, ���� �� ������ �������? �������� �� ��������!";
				link.l1 = "������!!";
				link.l1.go = "exit";
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

