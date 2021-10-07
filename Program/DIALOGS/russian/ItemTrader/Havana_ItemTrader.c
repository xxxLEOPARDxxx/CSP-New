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
			if (pchar.questTemp.PDM_ONV_Detectiv_Jiteli_Havana == "Jiteli_Havana")	// ����� "����� �� ������"
            {
    			link.l1 = RandPhraseSimple("��������, �� �� ������ �����?", "� �� �� ������, ��� �����?");
    			link.l1.go = "PDM_ONV_Prodavec";
			}
		break;
		
//**************************����� "����� �� ������"*******************************		
		case "PDM_ONV_Prodavec":
			dialog.text = dialog.text = RandPhraseSimple("� "+ GetSexPhrase("��������","����������") +", � �� ��������� ������.", "�� �������� ������ ��� ������ ������ ������?", "�����? ���, � ������ ������. ������ �����, � ����� ���.");
			link.l1 = "��������.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
