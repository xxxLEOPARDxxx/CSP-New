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
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

