// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("��� �� ������? �����������.", "� ������ ���, ��� �� ������?"), "������ ��� �� ���� �� ��������� ������ ������...", "� ������ ��� �� ���� �� ����� ��������� ������ ������...",
                          "�� ����� �� ��� ��������?! � ���� ��� ����� �� ���������� ������ ������, � �� ��� ������� ��������� ������!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "�� ������, �� ����� � �� �����..."), "��, �����... �� �� ������, �����...",
                      "�����, �����... ������ �����...", "��������, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> ��������� ���� ��������� �������.
			switch(pchar.questTemp.State)
            {
                case "TakeFoodCuracao_toOrangeMayor": //����������� �������, ����� �2, �������� �������������� �� ����� �����.
                    link.l2 = "� ������"+ GetSexPhrase("","�") +" ���� �� ������������ ������ ����������. � ��� ��� ������� ������������ ������ ������, � ����"+ GetSexPhrase("��","��") +" ������ � ��������� ��. ����� ��� ������������ � ����������� �� �������������� ����������� ���.";
                    link.l2.go = "Step_H2_1";
                break;
                
            }
             // <== ��������� ���� ��������� �������.
		break;
		
        case "Step_H2_1":
			dialog.text = "���, ������� �������... �� ��� ��, � �������� ��� � �������. ��� ������ ������ �� ������ �������� � ������� ��������, � ���������� ����������� ������ �� ���.\n"+
                          "������ ������� �� ����, �������, �������� � ����������� ������. ����� ��� ������ ������, ��������������� � �������� - 5600 ���������. ������������� � �������� - � ������ ���������� � ��������.";
			link.l1 = "����� ������.";
			link.l1.go = "exit";
            TakeItemFromCharacter(pchar, "Trust");
            BackItemDescribe("Trust");
            AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "2");
			pchar.questTemp.State = "TakeFoodCuracao_toOrangeStore";
        	pchar.GenQuest.StoreGoods.StoreIdx = FortOrange_STORE;
        	pchar.GenQuest.StoreGoods.HL2_DiscountPrices = true;
		break;

        case "DefenceOrange": //����������� �������, ����� �4, ������ ����� �����.
            dialog.text = "��� �� � ��� ��� ������, ��� �� ���!...";
            link.l2 = "� ����� �� ��������� ����������. �������, �� ������...";
            link.l2.go = "Step_H4_1";
        break;
        
        case "Step_H4_1":
			dialog.text = "���� ������, �� �� ������ ������, �� ������ ������ ���! ���� ����� ���������� ��� �� ���� ����! ��� �������� ������ ����������.";
			link.l1 = "����������� �������. ����� ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

