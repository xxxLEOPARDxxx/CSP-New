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
			//���, �����
			if (pchar.questTemp.Headhunter == "Rat" && pchar.questTemp.Headhunter.countP == 0)
			{
				link.l1 = "�������, �� ��� �����, �� ������ �� ������ �����, ������� �������� �����. �� ������ ���������� �� ���� �����������?";
				link.l1.go = "Rat_portmanP";
			}
		break;
		
		//���, �����
		case "Rat_portmanP":
			dialog.text = "��, ���������� ������� ����� � ��� ������ �����: ����� �����, ��������� ������� ������� ���� �� ��� �������. ��� ������� ��� ��������� ����� ������� ������ � ����� ����� �������� �������� ����� � ������� � ���������. � ����� ������ �����, ��� �� ��� � �� �������� �� �����, ���� ������ ����. ������� � ��� ����������� �����-�� ������.";
			link.l1 = "�� ��, ���� ���������� � ����� ����� ���� ��������. �������, � �� �� ������ ����������, ����� ������� ���� � ����� ����� ������ � ���� ����������� �������?";
			link.l1.go = "Rat_portmanP_1";
		break;
		
		case "Rat_portmanP_1":
			dialog.text = "������� ���������. ���-�... ���. ���� �������: ����� '������', ������ '�������������' � ����� '��������'.";
			link.l1 = "�������!";
			link.l1.go = "CheckP";
			pchar.questTemp.Headhunter.count = sti(pchar.questTemp.Headhunter.count) + 1;
			pchar.questTemp.Headhunter.countP = 1;
		break;
		
		case "CheckP":
			if(pchar.questTemp.Headhunter.count == 3)
			{
				pchar.questTemp.Headhunter = "Rat_Tavern";
				pchar.questTemp.Headhunter.Ratrumcity = npchar.city;
				AddQuestRecord("Headhunt", "13");
			}
			else
			{
				AddQuestRecord("Headhunt", "12_2");
			}
			DialogExit();
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}


