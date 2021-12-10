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
			if (pchar.questTemp.MC == "toMaracaibo")
			{
				link.l1 = "� �� "+ GetSexPhrase("�����","������") +" ������ ���-���.";
				link.l1.go = "MCTavernMar";
			}
			if (pchar.questTemp.PDM_CL_Tavern == "Tavern")		//����� ***���� ��������***
			{
				link.l1 = "� ��� ������� ������� �� ��������, �� ����������, ��� ��� ��� ����� �����?";
				link.l1.go = "PDM_CL_IshemAntonio";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_ONV_Maracaibo"))	//����� "����� �� ������"
            {
                link.l1 = "���� �� � ��� �� ������� ��� �����?";
                link.l1.go = "PDM_ONV_MB_1";
            }
		break;
		//������������ �����
		case "MCTavernMar":
			dialog.text = "��� ������ ��� ����������?";
			link.l1 = "�������, ��� ��������� ����� ��� �����-�� ���������. ��� ����� ���������?";
			link.l1.go = "MCTavernMar_1";
		break;
		case "MCTavernMar_1":
			dialog.text = "���������? � ���, ��� ������, ��� � �������. ����, ������, ��� ���-������, �� ��� ����� ����������, ��� ��� ������� ������ �� ���������. ���� ������� � ������ � ���� � ������� �������� ���-��� ������ ������, � ��� ����� ����� �� ���������.";
			link.l1 = "��� �� ���-������?";
			link.l1.go = "MCTavernMar_2";
		break;
		case "MCTavernMar_2":
			dialog.text = "�������� ������� � ����� ������. � ���� ������ ����� ����� ��� ����������� ������.";
			link.l1 = "��� �, ���������� �������, �� � �� ��� �������.";
			link.l1.go = "exit";
			pchar.questTemp.MC = "toDesMoines";
		break;
		//����� ***���� ��������***
		case "PDM_CL_IshemAntonio":
			dialog.text = "������� ����, ��� �������� ��������� ������ ���������. ��� ������� '��� �������' ����� � �����. ����� �� ��� ����� �� �������� � ���� � �����, �� � 12 �� 4 ����� ��� ��� ����� ��������� � � ������. ������������� �������, ��������� ��� ���� ��������� ���������� ����������� � ����� �����.";
			link.l1 = "������� ���� �� ����������, "+npchar.name+". ��� ����.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_CL_Tavern");
			AddQuestRecord("PDM_Clan_Lambrini", "2");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("","�"));
		break;
		//����� ***����� �� ������***
		case "PDM_ONV_MB_1":
			dialog.text = "��� ��� ��� �� � ��� �� �������. �� ��� �������, ��� ������� �� �������� �� ��� ���������� ��� ���, ����� � ��������� ����� ������ ���.";
			link.l1 = "��� �� �� ���� �������. �������!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Maracaibo");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

