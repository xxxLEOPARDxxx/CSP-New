// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), "����� �������, " + GetAddress_Form(NPChar) + "...", "�������, �������... ����� ��������� ��������, " + GetAddress_Form(NPChar) + "?",
                          "����������, �� ������� ����� ������ ��������� �����?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("��� ��������...", "������ ��� �� � ��� ��������"), "��, �����...",
                      "��, ������������� ����� �����������...", "��, ������, ��������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.PDM_PK_UznatLichnost == "UznatLichnost")	// ����� "���������� ������"
            {
                link.l1 = "���������� ��� � �������� �������, ������� �������� ��� ������. �� � ������?";
                link.l1.go = "PDM_PK_UznatLichnost";
            }
		break;
		
//**************************����� "���������� ������"*******************************
		case "PDM_PK_UznatLichnost":
			int Phrase;
                Phrase = rand(4);
                if (Phrase == 0)
                { 
					dialog.text = "��� ������ ������������, �� ��������� �� �� ��������.";
					link.l1 = "�����.";
					link.l1.go = "exit";
				break;
				}
                if (Phrase == 1)
                { 
					dialog.text = "� ����� ��� ������� ��� �������� �������? ����� ������ � ���� ���-������.";
					link.l1 = "��������.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 2)
                { 
					dialog.text = "� "+ GetSexPhrase("��������","����������") +", � �� ��������� ������.";
					link.l1 = "��������.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 3)
                { 
					dialog.text = "� �� ���� �, ��������.";
					link.l1 = "�����, ������ ����-������ �������.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 4)
                { 
					dialog.text = "��� �������� �� ������ ������. ������� �������. � ���� ������ �����������, ����� � � �����������. Ÿ ����� �������� �����. ��� �������� ������ ���� ������������ ������ � ���� �������� ��� ������� �����������. �� �������, ������� ���. �� ���������� � ��������� �� �����-������� � ��� ���� � ������ �� �������. ����� ����� � ��� ������ �������� ����� �������, ���������� ��������... ��� �, � ��� ���� �����, ��� ��� �� ������, ��� � ��� ���������.";
					link.l1 = "��� ��� ���� �� ������?";
					link.l1.go = "PDM_PK_UznatLichnost_2";
				break;
				}
        break;
		
		case "PDM_PK_UznatLichnost_2":
			dialog.text = "����� �������� � ����� ������� ���������. ����� �������� ������ �� ����, ������� � �����-���� �����"+ NPCharSexPhrase(NPChar,"","�") +", ����������� � ������. Ÿ ������� ����� ��� ���� �� ������. � �� ������, �� ��� ����� ���� ������� � ������... ��� � �������� �����? ��, ������� �������! �����, ����� ���!";
			Link.l1 = "������� ���, "+npchar.name+". �� ��� ����� �������. �� ��������.";
			Link.l1.go = "exit";
			
			sld = CharacterFromID("Josephine_Lodet")
			sld.name = "��������";
			sld.lastname = "�����";
			
			AddQuestRecord("PDM_Poteryanoe_Koltso", "2");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("","�"));
			
			pchar.questTemp.PDM_PK_IshemKoltso = "IshemKoltso";
			DeleteAttribute(pchar, "questTemp.PDM_PK_UznatLichnost");
		break;		
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

