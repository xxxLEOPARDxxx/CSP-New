// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("����� �������?", "��� ��� ������?");
			link.l1 = RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������");
		    link.l1.go = "exit";
			if (pchar.questTemp.PDM_ONV_Detectiv_Jiteli_Havana == "Jiteli_Havana" && npchar.sex == "man")	// ����� "����� �� ������"
			{
				link.l1 = RandPhraseSimple("��������, �� �� ������ �����?", "� �� �� ������, ��� �����?");
				link.l1.go = "PDM_ONV_MAN";
			}
			if (pchar.questTemp.PDM_ONV_Detectiv_Jiteli_Havana == "Jiteli_Havana" && npchar.sex == "woman")	// ����� "����� �� ������"
			{
				link.l1 = RandPhraseSimple("��������, �� �� ������ �����?", "� �� �� ������, ��� �����?");
				link.l1.go = "PDM_ONV_WOMAN";
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
		
//**************************����� "����� �� ������"*******************************		
		
		case "PDM_ONV_WOMAN":
			dialog.text = RandPhraseSimple("�� ���� � ������� �����.", "����� ��� �����?", "�� ����, � ��� ��.", "���, ���? ������� ����� � ����� �������.", "������� � ��� ����� ������� �� ����.");
			link.l1 = "��������.";
			link.l1.go = "exit";
		break;
		
		case "PDM_ONV_MAN":
				int Phrase;
                Phrase = rand(4);
                if (Phrase == 0)
                { 
					dialog.text = "��������, �� � �����.";
					link.l1 = "��������.";
					link.l1.go = "exit";
				break;
				}
                if (Phrase == 1)
                { 
					dialog.text = "��������� �� ����, ������"+ GetSexPhrase("","���") +".";
					link.l1 = "��������.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 2)
                { 
					dialog.text = "��� ����� �������, ����"+ GetSexPhrase("�","�") +".";
					link.l1 = "��������.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 3)
                { 
					dialog.text = "�� ������, � �����?";
					link.l1 = "��������.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 4)
                { 
					dialog.text = "������ ���, ������"+ GetSexPhrase("","���") +" - ��� ������ ����� ���������� ���� � ���� ������! ��� ��������������� ���� ������ ����� �������� � ����������� � ������� ���, ��� ��� ���� ������, � � ������� ����� �� ��������� ����!";
					link.l1 = "�����? ��� �� � ��� ������?";
					link.l1.go = "PDM_ONV_MAN_2";
				break;
				}
		break;
		
		case "PDM_ONV_MAN_2":
			dialog.text = "�? � ����, ��� ��� �������� ��������� ����� ��� ������ ������� � ���� ������! �� ������ �������� ����� ����� ��������!");
			link.l1 = "���. ������ �� ������������ ������� � ������, ������� �� ���������� �������� �����? ��, �������! ������ �������, ������ � ��� ����������� ������� �����. ��-��. �� � ��������"+ GetSexPhrase("","�") +" �������� ���� ������ - �� ��������.";
			link.l1.go = "exit";
			link.l2 = "��� ��������� �������� ��� �������� ��� ������ - �� ����� ����� ��������� �. �� ������, ��� � ���� � �����?";
			link.l2.go = "PDM_ONV_MAN_3";
		break;
		
		case "PDM_ONV_MAN_3":
			dialog.text = "��� ������ �������� ����� ����� � �������. ��� �� ����������� ���, "+ GetSexPhrase("��� ���","���� ���") +"! �������� ���� � �������� ��� ���� �� � ������! �� "+ GetSexPhrase("������ �������, ������","������, ���������") +". ��, ��� ��� ������ ����������� ��� � ������ ��, ��� �� ��������� - ��� ����� ��� ������ ������!");
			link.l1 = "�� ������� ���� �������, �� ������������.";
			link.l1.go = "exit";
			AddQuestRecord("PDM_Ohota_na_vedmu", "7");							
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Jiteli_Havana");
			pchar.questTemp.PDM_ONV_Detectiv_Tavern_1 = "Tevern_Da";
		break;		
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

