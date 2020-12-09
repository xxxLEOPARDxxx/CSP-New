// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), "������ ������� �� �������� ������ ��� ������ " + GetAddress_Form(NPChar) + "...", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������...",
                          "����������, ���� �� �� �� ����� �����, �� �� ����� ���� ��������� ��������.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� ��, ������������� � ������ ���...", "��������, �� �������� ���� ���� ������ �� ����������.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "������������. � �� �����"+ GetSexPhrase("","�") +" ������, �� �������������� �� � ����� ����� ������ '" + pchar.questTemp.Slavetrader.ShipName + "', ��� ������������� ������� ��������?";
                link.l1.go = "Havana_ratP_1";
			}
			
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("��, ��������������. �� ��� ���� �� ���. �������� � ��� ������ �����������, ������� ������� ������ � ���� ������� � �������.", "�� ��� "+ GetSexPhrase("����������","����������") +" �� ����, � ��� �������.", "� �� ������ ���, �� ��� "+ GetSexPhrase("����������","����������") +" �� ���� ��������.", "� ����� �� ������ ��� ��������!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������! ��� � ��������.", "��, �� ��...", "��, �����, "+ GetSexPhrase("���������","����������") +"...", "��������, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
