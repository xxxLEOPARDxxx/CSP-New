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
			if (pchar.questTemp.piratesLine == "BlackLabel_toLaVega")
			{
				link.l1 = "��������, �� �� � �����, � ����� ������ ��������� ����� ������ ���?";
				link.l1.go = "PL_Q2_1";
			}
			if (pchar.questTemp.PDM_PJ_KV == "KupitVino")	//����� ***��������� ����***		(����)
			{
				link.l1 = "� ��� ��� ���������"+ GetSexPhrase("","�") +", ��� ���� ������� ������ ������� ����.";
				link.l1.go = "PDM_PJ_1";
			}
			if (pchar.questTemp.PDM_PJ_KR == "KupitRom")	//����� ***��������� ����***		(���)
			{
				link.l1 = "��� ����� ������ ������� ����.";
				link.l1.go = "PDM_PJ_Rom_1";
			}
		break;
		case "PL_Q2_1":
			dialog.text = NPCStringReactionRepeat("���, ������� �����. � ��� � ������ ������ ���.", 
				"�� ��� "+ GetSexPhrase("���������","����������") +" �� ���, ��� ���� � ���.", 
				"� ��� �������, ��� ������� ��� � ��� ��� � ������.",
                "������...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������... ������� ����.", 
				"��-��, � "+ GetSexPhrase("�����","������") +"...",
                "�����...", 
				"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "PDM_PJ_1":
			dialog.text = "��� ��� �� �� ��������, "+ GetSexPhrase("�����","����������") +"! ��-��-��-��! �� ������ ��� ��� ���� ����, � �������� ��� ��� � ���, ��� ��� �����! ������ ��������� ����? ������ ������ �����! ������ ���� �� ���� ����������!", 
			link.l1 = "��� �, ��� ������ ������������, �� ��� ����� ����� ���� �������. ������� �� �� �� ������?", 
			link.l1.go = "PDM_PJ_2";
		break;
		
		case "PDM_PJ_2":
			dialog.text = "��, "+ GetSexPhrase("�����","����������") +", ������, ��� �� ������������ �������� �������� ����� ������������� �������! �� �������� ������� ����� ����������� ������� ���� ����� �� ���� ������� �����!",
			MakeRandomLinkOrderThree(link,
			"� ������ ����, "+npchar.name+". �� � ������ ������ � ���� ���� �� �������� ����� �����������.",
			"PDM_PJ_Beru_1",
			
			"�� ��� �� �����! �� ����� ���� � ���� ������ ������������� ������������ �� �������! �� ��������� ������ ����, �������!",
			"PDM_PJ_Beru_2",
			
			"�������� �� ����. �������� �������� ��� ����� ������� ����.",
			"exit");			
		break;
		
		case "PDM_PJ_Beru_1":
			dialog.text = "��� ���� �������... ����������� ���� ��� ������������ ��������, ��-��-��. �� �� ������ ������������, "+ GetSexPhrase("�����","����������") +". ������ ���-������ ���?", 
			link.l1 = "���, �� ����. � �������, ��� ����� ������ ���������, ��� ��, ������ ������� ������ ������������� - � ������� ��� ������� ����������� �������� ���� ��� �������� ������������ �������. ��������, "+npchar.name+".", 
			link.l1.go = "PDM_PJ_Beru_3";
		break;
		
		case "PDM_PJ_Beru_2":
			dialog.text = "������? ��-��-��, "+ GetSexPhrase("�����","����������") +", ��, �������, ������. ��, �� ������� �� ������ ������ ������� ������������ �� ���� �������. �� ��������� ���� ��������� �� �� �������, �����? ��-��-��!", 
			link.l1 = "����� ��� ��� ��������� ����, � �� ��� �������, ���������� ��� ���������!", 
			link.l1.go = "PDM_PJ_Beru_3";
		break;
		
		case "PDM_PJ_Beru_3":
			DialogExit();
			
			AddQuestRecord("PDM_Proklyataya_Jara", "2");
			GiveItem2Character(PChar, "PDM_PJ_Vino");
			AddMoneyToCharacter(pchar, -5);
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KV");
			sld = CharacterFromID("PDM_PJ_Strajnik_1")
			sld.Dialog.Filename = "Quest/PDM/Proklyataya_Jara.c";
			sld.dialog.currentnode = "Prines_Vino_1";
		break;
		
		case "PDM_PJ_Rom_1":
			dialog.text = "������� ����� ����� ���� � �����, ��� ��, �� ��, "+ GetSexPhrase("�����","����������") +"! ��� ����� ������� �������, ����� �� ������ ������ � ����������, ��, "+ GetSexPhrase("�����","����������") +", � ������� �� ������ ���������� ���� ������� ������ �����! ��-��-��! ����� �� ��������� ��� �� ��������! ��-��-��!", 
			link.l1 = "��, �����, "+npchar.name+"! ������ ��������� ���� ��� � ����� ������� � �� �������� ��� �������...", 
			link.l1.go = "PDM_PJ_Rom_2";
		break;
		
		case "PDM_PJ_Rom_2":
			dialog.text = "��, "+ GetSexPhrase("�����","����������") +", �� "+ GetSexPhrase("����� ��������������","����� ��������������") +", ��� ����, �� ����. ������... ��� ���� ��� �� ������, � � �������� ������ �� �����. �������, � ���� ������� ��� ������ ����... ��, "+ GetSexPhrase("�����","����������") +", �� �� �� ������ �� ����� � ������� � ����, ������? ��-��-��! ��, ��� ������ ����� ��������!", 
			link.l1 = "��� ����� �������� ������... ���������! �� ������ ��������� ��� ������ ������ ������� ����� �� �����! ��� � ��! ��� ������� �������...", 
			link.l1.go = "PDM_PJ_Rom_3";
		break;
		
		case "PDM_PJ_Rom_3":
			dialog.text = "��������, �� ����� ��� �����, �������. �� ���������� �����, � ���� ��� �������... �� � �������, �� ��������� ��� ��� ������������, ������ ������... ������� ������ � �������� �������, ���� ���������...  � ���� ������� ������ ������� �������� �� �������� ��� ��... ���� ������� �����! ��-��-��!",
			MakeRandomLinkOrderTwo(link,
			"�� ������ ���������, "+npchar.name+". ���� ������� ����� �� ������� ���? ���! �� ��������!",
			"exit",
			
			"��, ������! �� ������������� ���������� ����, ��������. ��� ���� ������. ����� ���� ���. ��, ����������, �������� ��� ������.",
			"PDM_PJ_Rom_4");
		break;
		
		case "PDM_PJ_Rom_4":
			dialog.text = "�������, "+ GetSexPhrase("�����","����������") +". ��������� ����� ���� �������... ��� ��� ������ �������� �� �������� ������� ����, �������. ����� ��� ��� � ��������� ��� �������� ����������... ��, ��-��-��...", 
			link.l1 = "���������, "+npchar.name+", �����-������ ������ ���������� �� ������. �����, ���� � �� ���� ������, �� ������ ��� � ���������. �� ��������.", 
			link.l1.go = "PDM_PJ_Rom_5";
		break;
		
		case "PDM_PJ_Rom_5":
			DialogExit();
			
			Log_info("�� �������� ������� � ������� ���������");
			GiveItem2Character(PChar, "PDM_PJ_Rom");
			GiveItem2Character(PChar, "PDM_PJ_BsRL");
			AddMoneyToCharacter(pchar, -5);
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KR");
			sld = CharacterFromID("PDM_PJ_Strajnik_2")
			sld.Dialog.Filename = "Quest/PDM/Proklyataya_Jara.c";
			sld.dialog.currentnode = "Prines_Rom_1";
			AddQuestRecord("PDM_Proklyataya_Jara", "4");
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

