// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), "������ ������� �� �������� ������ ��� ������, " + GetAddress_Form(NPChar) + "...", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������...",
                          "����� ������� ����� ��������?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� ��, ������������� � ������ ���...", "�� ���, ����� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = "����� �����, ��� ������� �������� ����� ��� ������-�� ����. �� �� � �����?";
				link.l1.go = "PL_Q7_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_Novaya_Rodina.IshemHugo"))
			{
				link.l2 = "�� �� ����� ����� ����� ���������?";
				link.l2.go = "PDM_Gde_Lesopilka";
			}
		break;
		//�������, ����� �7, ������� ������ � ������ ��������
		case "PL_Q7_1":
			dialog.text = NPCStringReactionRepeat("��, ���-�� ���������. ��������, ����� ������ �������� �������� ��������.",
				"�� ��� �������� �� ��� ����.", 
				"����� �� �� ������ �������?",
                "�������� ������ ������ � ���� �� ���.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������... � ����� � ��� �� ������?",
				"��, �����.",
                "���, �����...", 
				"��, ������� � �� ����...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q7_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q7_2":
			dialog.text = "��, �� �� �����! ������ ����� ����� ������� �� ���������, �� ������ ���������� �������, ���� ��� ����� ���������. � �� ���� �����������...";
			link.l1 = "�� ���� ��. ���������, ������ ��� ����������, ����� �� ��� ����������� �� ��� ����. ��� �������?";
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = "�� ����, "+ GetSexPhrase("���","����") +" �����. � �������� ��������� ���������� ����. �� ����� � �� ����� � ���, �� ������ ������ ��������� � ����� ��������� - ������ ����� ����� � ���������� � ������� � ����� ������� ����-��...";
			link.l1 = "��, �������... �� ��� ��, ������� ���� �� �����.";
			link.l1.go = "exit";
		break;
		//����� "����� ������", ���� ���������
		case "PDM_Gde_Lesopilka":
			dialog.text = "�� ��� �����, �� ��� ������ ���������� �������� �� ��������, �� ������� ���������� ����� ������ ���.";
			link.l1 = "��, �? ���� �� ����������?";
			link.l1.go = "PDM_Gde_Lesopilka_2";
		break;
		
		case "PDM_Gde_Lesopilka_2":
			dialog.text = "���... �� 1000 ������� � ��� �������� ������.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "���, ����� ���� ������. ��� ���� �� ����������?";
				link.l1.go = "PDM_Gde_Lesopilka_3";
				link.l2 = "� ���� ��� ��� ������� �����.";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "� ���� ��� ��� ������� �����.";
				link.l1.go = "exit";
			}
		break;
		
		case "PDM_Gde_Lesopilka_3":
			DeleteAttribute(pchar, "questTemp.PDM_Novaya_Rodina.IshemHugo");
			dialog.text = "�� ���� ���� �� �� ����, ��� ��� ���.";
			link.l1 = "�������, �� �������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"LaVega_Tavern","sit","sit10");
			AddQuestRecord("PDM_Novaya_Rodina", "3");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

