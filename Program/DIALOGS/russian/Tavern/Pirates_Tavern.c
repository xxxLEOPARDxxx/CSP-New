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
			// ==> ��������� ���� ��������� �������.
            if (pchar.questTemp.State == "SeekBible_toBermudes") 
			{				
                link.l1 = HeroStringReactionRepeat("��������, � ��� ������, ������� �������� ����� ������ �����-�� ��������. �� ������ �� ���� ����?",
                "� ��� ������ "+ GetSexPhrase("�����","������") +" ��������... ��� ��������, ������.", "�� ��, �����...", "�-�-�, ����������� ���, ������...", npchar, Dialog.CurrentNode);
                link.l1.go = DialogGoNodeRepeat("Step_H8_1", "", "", "", npchar, Dialog.CurrentNode);
            }
            if (pchar.RomanticQuest == "BrotherIsDead") 
			{				
                link.l1 = HeroStringReactionRepeat("������, �� �� � �����, ��� ������ ������ ����������?",
                "��, ��, ��� ������ ��������...", "�� ��, �����...", "�-�-�, ����������� ���, ������...", npchar, Dialog.CurrentNode);
                link.l1.go = DialogGoNodeRepeat("Step_Romantic_1", "", "", "", npchar, Dialog.CurrentNode);
            }
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = "��������, ��������, ������ �� ������ � ������� ����������� ��� ������ '����� �����'?";
				link.l1.go = "BlueBird_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toBermudes")
			{
				link.l1 = "�����, ��������, �� ��������� ������ ���?";
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toTavernAgain" || pchar.questTemp.piratesLine == "KillLoy_2toTavernAgain")
			{
				link.l1 = "� ��� ������� ���.";
				link.l1.go = "PL_Q3_2";
			}
			if (pchar.questTemp.piratesLine == "PL5Hunter_toBermudes")
			{
				link.l1 = "� ���� � �������, ���� ������ �� �������?";
				link.l1.go = "StepPL5Berm_1";
			}
            // <== ��������� ���� ��������� �������.
		break;
		//������ ����� �����
		case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat("������-�� ����� �������. � �������� �������, ��� ������� ����� �������. ������� ��������, �� ���� ���...", 
				"�� ��� �������� �� ����.", 
				"�����? ��� ��� ��������.",
                "��������, ���� ��� ������ ������ �� ����, ��, �������, ������� ������� ���������.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("� ��� ������� �������?", 
				"��, �����...",
                "��, �����.", 
				"������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;

		case "BlueBird_2":
			dialog.text = "������ ��������, �� ����������, ��-��!!";
			link.l1 = "� ���-������ ������ ���� ��������? ��� �� ����� �����, � �������.";
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = "��� ����� � �����, � ������. �� �������� � ����� ����� '����� �����' ������ ���, �� ��� � ������ �� ��� ������� �� ������� ������ - � �������� �� ���!";
			link.l1 = "��� ������ ���... �� ��� ��, ����� ������. ������, � ������ �������� �������, �� ��� �� �������?";
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = "������������ ������, ��������� ����� ���������.";
			link.l1 = "�������... � ���� �������, ������� � ��� �� � ����� ������� ����������?";
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = "����������� ������ � ���� ���. �� ��� ������ ������ ��������, �����, ��� �� ���� �����, ��-��...";
			link.l1 = "�� ������ �� �� �������, ��������, ������� ��� ��� ���.";
			link.l1.go = "BlueBird_6";
		break;
		case "BlueBird_6":
			dialog.text = "��� ����� ���� ������. �� �������� �� ��� ��� �� �������. ������ �, ��� �� ���������� � ������-��������, ������� ��� ���� ���������� � ������ �� ������������.";
			link.l1 = "������� ���� �������, ��������. �� - ������� ����������.";
			link.l1.go = "BlueBird_7";
		break;
		case "BlueBird_7":
			dialog.text = "������� �� ����������, " + GetAddress_Form(NPChar) + ". ����� ���!";
			link.l1 = "� ���� ����� ��������, ��������.";
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "3");
			pchar.questTemp.BlueBird = "toPuertoPrincipe";
		break;

		//����. �������, ����� �8
 		case "Step_H8_1":
    		dialog.text = "���, �� ������.";
    		link.l1 = "����� ������� ���������, ��� �� ������� �� ����������.";
    		link.l1.go = "Step_H8_2";
 		break;
 		case "Step_H8_2":
    		dialog.text = "������ �� ���� �� ����, � ���� � ������� ������ �� ����.";
    		link.l1 = "������� �� ������.";
    		link.l1.go = "exit";
 		break;
		//��������, ���� ������
 		case "Step_Romantic_1":
    		dialog.text = "����, �� ��� ����� �����, � ������. ��� ��� ��� � ������ ����.";
    		link.l1 = "�������, ��������...";
    		link.l1.go = "exit";
 		break;
		//�������, ����� �3, ������ ���
		case "PL_Q3_1":
			dialog.text = "���������. ��� �����, ����-�� ���������. �� � ������ ��������, �� � �������... �������, �� ������������� ����� ������.";
			link.l1 = "���������.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "9");
			pchar.questTemp.piratesLine = "KillLoy_toAlexus";			
		break;

		case "PL_Q3_2":
			dialog.text = "��� �� ��� ��� ���� ����������.";
			link.l1 = "�����, �� ���� ��������?";
			link.l1.go = "PL_Q3_3";
		break;
		case "PL_Q3_3":
			dialog.text = "��, ���� ��� ����������, �� ��� ��� ����� �����������, � ����� ������ ������������. ���, ������, ������� ����� �����, �� � ��� ������������.";
			link.l1 = "������� �����?! �������, ��� ���-���.";
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "KillLoy_toGoogly";
		break;
		//�������, ����� �5, ���
		case "StepPL5Berm_1":
			dialog.text = "�� ���, ������ ��� � �������. �������, ��� ����� ���� ����, � ����. ";
			link.l1 = "� ��� �� ���� ���� ���� �������?";
			link.l1.go = "StepPL5Berm_2";
		break;
		case "StepPL5Berm_2":
			dialog.text = "���, � ����������� ���� � �������� ������� �� �����. ��� ������� �� �������, ������ ������ ���. ��� � �������...";
			link.l1 = "�������, �� ��� ������� �����!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "10");
			pchar.questTemp.piratesLine = "PL5Hunter_toOrryHouse";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

