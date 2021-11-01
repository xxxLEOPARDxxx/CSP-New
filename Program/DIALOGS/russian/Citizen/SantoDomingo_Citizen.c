// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("����� �������?", "��� ��� ������?");
			link.l1 = RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������");
		    link.l1.go = "exit";
			if (pchar.questTemp.PDM_PK_IshemKoltso == "IshemKoltso")	// ����� "���������� ������"
            {
                link.l1 = "� ���������� ������, ������� ������������... ������ �� ���� ��������. �������� ������ ������. � ��� ������ ��������� ���-�� � ���� ������. ���� �����, �� ���-�� ������"+ NPCharSexPhrase(NPChar,"","�") +" � ��? ������� ������, � ������� ������.";
                link.l1.go = "IshemKoltso";
            }
		break;
		
		case "info":
        // �������� �� �������� ����� ���, �� �������
			dialog.text = "� ���, ������� �� ������ ���������� ���� ��� "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "�� �����... ����� ����.";
			link.l1.go = "exit";
			link.l2 = "����� ������ ������";
			link.l2.go = "new question";
		break;
		
		case "town":
        // �������� �� �������� ��� ������, �� �������
			dialog.text = "� ��� ��� ����������? �� ����. ������ �� �����.";

            link.l1 = "��� ���������! ����.";
			link.l1.go = "exit";
			link.l2 = "����� ������ ������";
			link.l2.go = "new question";
		break;
		
//******************** ����� "���������� ������" ******************		
		case "IshemKoltso":
			int Phrase;
                Phrase = rand(4);
                if (Phrase == 0)
                { 
					dialog.text = "� ��� �� ������, ������? ���� ������ ����� �� �� ���.";
					link.l1 = "��������.";
					link.l1.go = "exit";
				break;
				}
                if (Phrase == 1)
                { 
					dialog.text = "� ���� ���� ������, �� ��� � " + LinkRandPhrase("�������", "���������", "�������") + ".";
					link.l1 = "����� ���"+ GetSexPhrase("","�") +" �� ���.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 2)
                { 
					dialog.text = "� ���� ���� ����� ������ ����, ��� �������� �� ����� ������.";
					link.l1 = "��������.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 3)
                { 
					dialog.text = "� ���� ��� �����, ��������.";
					link.l1 = "�����, ������ ����-������ �������.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 4)
                { 
					dialog.text = "����... �� �������� - ������? ��, � �����, ��� �����"+ NPCharSexPhrase(NPChar,"","�") +" ������, ����� ����, � ������� �� ��������. ��� � ����� ����� - ����� ����, �� ���� ������ � - �� ������� ����, ����������� ������� ��� ������� �������. �� ����� ���������. � ��� ������� �� �������� �������� �����, ���� ������. �����-�� ������ ������� �� ��� ������ ���� ��� �����. ���� ����� �� ��� ��� ����� ����, ��� ��� - ��������� ��� ������ ����� �������� �����. ��, ��� �������� �� ������, ������� �� �����.";
					link.l1 = "�������, "+npchar.name+", �� �� �������������, ��� �� ���� ��������. �� �������.";
					link.l1.go = "exit";
					
					AddQuestRecord("PDM_Poteryanoe_Koltso", "3");
					AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("","�"));
					DeleteAttribute(pchar, "questTemp.PDM_PK_IshemKoltso");
					
					sld = GetCharacter(NPC_GenerateCharacter("PDM_PK_Francheska", "BaynesDaughterSTOK", "woman", "woman", 10, SPAIN, -1, false));
					sld.name = "���������";
					sld.lastname = "";
					sld.city = "SantoDomingo";
					sld.location	= "SantoDomingo_Brothel";
					sld.location.group = "goto";
					sld.location.locator = "goto3";
					sld.dialog.filename   = "Quest/PDM/Poteryanoe_Koltso.c";
					sld.dialog.currentnode   = "Francheska";
					LAi_SetCitizenType(sld);
					LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
					LAi_SetImmortal(sld, true);
				break;
				}
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

