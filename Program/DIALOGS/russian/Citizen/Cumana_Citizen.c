// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("����� �������?", "��� ��� ������?");
			link.l1 = RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������");
		    link.l1.go = "exit";
			// ����� ��������, ������ ���� ����� "����"
			if (CheckAttribute(pchar, "RomanticQuest.ShipToCumana"))
			{
                dialog.Text = "� ��� ������.";
    			link.l1 = "�� �������� �� � ���� ����� '���� ��� ���������'?";
    			Link.l1.go = "RomanticQuest_1";
			}			
		break;
		// ==> ����� ��������, ������ ���� ����� "����"
		case "RomanticQuest_1":
			dialog.Text = "��� ��, ������, ��������. ��� ������ � �����, �������� ����-�����, �������� �� ��������� ����.";
			link.l1 = "� ��� ��� ����� ��������?.";
			Link.l1.go = "RomanticQuest_2";
		break;		
		case "RomanticQuest_2":
			dialog.Text = "��� ����������, �� ���� � ������� ������ �������";
			link.l1 = "�������.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "RomanticQuest.ShipToCumana");
			Pchar.RomanticQuest.ShipToCumanaTavenrn = true;			
			ref rChar = GetCharacter(NPC_GenerateCharacter("BrigCaptain", "shipowner_13", "man", "man", 20, SPAIN, -1, false));
            rChar.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
            FreeSitLocator("Cumana_tavern", "sit3");  // ������� ����
			ChangeCharacterAddressGroup(rChar, "Cumana_tavern", "sit", "sit3");
            LAi_SetSitType(rChar);
		break;
		// <== ����� ��������, ������ ���� ����� "����"
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
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
