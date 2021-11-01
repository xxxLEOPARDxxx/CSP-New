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
			if (CheckAttribute(pchar, "questTemp.PDM_Apt_Markus_v_krovi"))	//����� "��������"
			{
    			link.l1 = "�������� ��� � ��������, ������� ����� �� ���� � ���� � �������. �� �� ������ ����� �� ���� �� ��������.";
				link.l1.go = "PDM_Apt_Markus_v_krovi_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_Apt_Rasskazat_Tavern"))	//����� "��������"
			{
    			link.l1 = "�������� ���� �����, ������ "+npchar.name+". � �� �� ������� ���-���, ��� ���������� ������� ��� ����, ����� �����������. �������� � ���� � ������� ��� ���� ��� ��� ���� � ����. �� ����������, ��� ������ ������.";
				link.l1.go = "PDM_Apt_Rasskazat_Tavern_1";
			}
		break;
		//����� "��������"
		case "PDM_Apt_Markus_v_krovi_1":
			dialog.text = "��� ��� ����� ����� ������� ���������, � � �� �������� �������. ��� ��� ������, ��������. �� ������ '��������', ����� �������� ������ � ���� �����. ����� �������� ������ ��� �� ���� � ����-�����, �������� �������, � �������� �� ���� �����. ������ ����� � ��������� �����, ��� �������� ��� ������ ���� ���� � ���� �������� ����. �� ���������� �����. ��� � ����� �����.";
			link.l1 = "������ ������. ����� ����, �� �������� ��� �������? � ������� �� ��. 100 ����� ������?";
			link.l1.go = "PDM_Apt_Markus_v_krovi_2";
			link.l2 = "�������. ����� ���.";
			link.l2.go = "exit";
		break;
		
		case "PDM_Apt_Markus_v_krovi_2":
			dialog.text = "���������, "+ GetSexPhrase("���","����") +", � ������ �� ������ ��� ������� �� ������ �����. �� �����, �� �� ����� ����� �����.";
			link.l1 = "�� ��, "+npchar.name+". ������ �� ���� �����-�� �������.";
			link.l1.go = "PDM_Apt_Markus_v_krovi_3";
			AddMoneyToCharacter(pchar, -100);
			sld = CharacterFromID("PDM_Markus")
			ChangeCharacterAddressGroup(sld,"CommonRoom_MH3","prison","prison1");
		break;
		
		case "PDM_Apt_Markus_v_krovi_3":
			dialog.text = "����� �����, ��� �� ���-������� ����� ����������� �������� ������ �������, � ����� �� ��� ������, ��� � ���. ��� ����� �� ������ ������ ������ �������, � ������� ����������� ����� �������. ���������� ��� ��� ���, ��� �������� ������� �������� ������� ������ �� ���-�������, � ������ ����� ����������� ����� ���������� �� �������. �� �����, ����������.";
			link.l1 = "��� ����� ���������! ��� ����� ���������� � �������� �� ����������. � �� ���������� � ������� �� ����� �����������.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_Apt_Markus_v_krovi");
			
			sld = GetCharacter(NPC_GenerateCharacter("Doktor_Alumnus", "Alumnus", "man", "man", 10, HOLLAND, -1, false));
			sld.name = "�������";
			sld.lastname = "";
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			LAi_SetBarmanType(sld);
			sld.greeting = "GR_Doctor_Alumnus";
			sld.city = "Marigo";
			sld.dialog.filename   = "Quest/PDM/Aptekar.c";
			sld.dialog.currentnode   = "Alumnus_FT";
			ChangeCharacterAddressGroup(sld,"Farmacia","barmen","stay");
			
			AddQuestRecord("PDM_Aptekar", "2");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("","�"));
		break;
		
		case "PDM_Apt_Rasskazat_Tavern_1":
			dialog.text = "��� ���� � ����� �������, "+pchar.name+". �������, �� �����, "+ GetSexPhrase("���","����") +". � ���������� � ��, ���� ������ ���� ���������, � �������, � ������ �������, �� ����� �� ��������. ������������� ����� ������, "+pchar.name+", � �����, �� ����� � ��������� ���-�� ��������.";
			link.l1 = "����������� ��������, "+npchar.name+". �� ��������.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_Apt_Rasskazat_Tavern");
			
			TakeItemFromCharacter(pchar, "PDM_Heal_Poroshok");
			
			SetTimerCondition("PDM_Apt_Markus_Vizdorovel", 0, 0, 7, false);
			
			AddQuestRecord("PDM_Aptekar", "4");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("","�"));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

