// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "��������, � ������.";
			link.l1 = "� "+ GetSexPhrase("������","��������") +". ��������.";
			link.l1.go = "Exit";
			if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "true")
            {
                link.l1 = "� ��� ��� ������� ���������� ����� ������, �������� ������� �������. ����� ��� ��������� �� ����?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "commandante")
            {
                link.l1 = "�������, �� ������������� ����������� �������� ����� �������? �� ������� �� ������� ��������� �� ����� ������ �����������?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "pay")
            {
                link.l1 = "��� ����� �, ���������. ������� ������� �������� � ����������� �������. ��� ���.";
                link.l1.go = "Tichingitu_6";
            }
		break;
		
		case "Tichingitu":
			dialog.text = "�-�, ������� � ��� ��������� ���� �������? �� ���� ������ �������������� ���. �� �� ������, ��� �������� �������� �� ����� ������������. ���� ���� ����� ������ �� ���� ������ ������������ ��� ������ ������ ������, ����� �� ��� ������� �������� �� ��������...";
			link.l1 = "��� � ���� ������ � ��������?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "� �� ������ - �� ���� ������� ���������� ���. ���������.";
			link.l1 = "�������!";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			dialog.text = "�� �� ��������� �������� � ����� ��������. ��� ����� �������� ������ ���� ��������� ����������� ��������, ����������� ��������� �� ��������� ���������� ����������. ����� ����, �� ���� ���������� �������, � �� ����� ��������� ������� � ����� ������ � ������� ���� �����������.";
			link.l1 = "������� ����� ������ �������� ���������? � �� ����� ������, ��� ��� ������������ ������...";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "��, ������� �������, �� ���������� � ���������! ���� ��� ��� ����� ���� ������ - ������������� � �������� � ������� �� ������� ������ ���. ���� �� ������� ����������� � ����������� - �� ������������ ���.";
			link.l1 = "� �� �����, ������. �����������.";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Tichingitu = "ascold";
		break;
		
		case "Tichingitu_6":
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(������) ��... �������� ���� �������: ������� ������� ������������� �����, � ������ ������ ��������� �������... �� �� �����, ������, � ���� �������������� ������ �������� �������. ������, ������ ���� � ������ � �������� ����� ������������.";
			link.l1 = "�������������, ������!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			pchar.questTemp.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
