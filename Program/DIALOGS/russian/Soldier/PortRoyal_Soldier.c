// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� ������ ������� � �������?", "� ������� ����� ��������� - �������, �������... ��� ��� ������, " + GetAddress_Form(NPChar) + "?"), "�� �������� ���������� � ������� � ������� ���������, " + GetAddress_Form(NPChar) + "...", "������ ��� �� ������� �� ��������� ������ ������...",
                          "���������� ���� � ��� ���� ��������, � ��� ��� � ��,"+ GetSexPhrase(" ���������, "," ") +"�������� �� ����...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "������ ��� �� � ��� ��������"), "�� ��������...",
                      "�� ��, ������������� � ������ ���...", "���������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			/*sld = characterFromId("eng_guber");
			if (npchar.location == "PortRoyal_townhall" && pchar.questTemp.State == "" && CheckAttribute(sld, "notQuestLine"))
			{
                dialog.text = "����! ��� ��� ����!!!";
				link.l1.edit = 7;
				link.l1 = "";
				link.l1.go = "ELOpenKey_1";
			}*/
		break;

		case "ELOpenKey_1":
			
			if (dialogEditStrings[7] == KEY_ENG_LINE)
			{
				dialog.text = "�� ������, � ��� ����, ���� ���� ������. � �������� �� ���� �������� ���������...";
				Link.l1 = "������, �������. ������� ����...";
				Link.l1.go = "exit";
				sld = characterFromId("eng_guber");
				DeleteAttribute(sld, "notQuestLine");
			}
			else
			{
				dialog.text = "�� �� ������, � ��� ����. �����, �� ����� ��� ����� ������.";
				Link.l1 = "��, �� �����...";
				Link.l1.go = "exit";	
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

