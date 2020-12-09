// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������, "+ GetSexPhrase("��� ���","���� ���") +"?", "���������, � ������ ����..."), "� ������ ����, ������, "+ GetSexPhrase("��� ���","���� ���") +"...", "� � ������ ��� ������ ����, "+ GetSexPhrase("��� ���","���� ���") +": ������� ���� ������.",
                          "������� ������������ � �����������������, � ��� ��� � �� ���������, "+ GetSexPhrase("��� ���","���� ���") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������...", "�� ������, �����..."), "��, ���� ����� � ������ �������...",
                      "�����, �����... ������ �����...", "��������, ������ ����...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//============= �������� ��������� ================
            if (CheckAttribute(Pchar, "RomanticQuest.PriestAsk"))
			{
				link.l2 = "���� � ������, ����� �� ����� � ������� ���� ���� ����������?";
				link.l2.go = "Romantic_1";
			}
		break;

        case "Romantic_1":
			dialog.text = "���������� ��������? ��, ��� ���, �����, ��� ��������� ����������... � � ��� ����?";
			link.l1 = "�� ������ ��� �������, �����. �� ��������...";
			link.l1.go = "exit";
			DeleteAttribute(Pchar, "RomanticQuest.PriestAsk");
		break;

        case "Romantic_2":
			dialog.text = GetFullName(pchar) + ", ������ �� �� � ���� �������� �� ������� � ��������� ���� � ��� � ���� � ��������, ���� ������ �� �������� ���?";
			link.l1 = "��, �����.";
			link.l1.go = "Romantic_3";
		break;
        case "Romantic_3":	
			locCameraToPos(3.64, 3.25, -7.84, false);
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "goto", "goto5");
			dialog.text = "� ��, �������� �� �������, ������ �� �� � ����� " + GetMainCharacterNameGen() + " � ��������� ���� � ��� � ���� � ��������, ���� ������ �� �������� ���?";
			link.l1 = "��, �����.";
			link.l1.go = "Romantic_4";
		break;
        case "Romantic_4":	
			locCameraToPos(-0.75, 3.85, -10.60, false);
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "goto", "goto5");
			dialog.text = "���� ���-�� �� ������������� ����� �������, �� ������� ���� ������� � ��� ������� �� ����� ���� ������ - ����� ������ ��� ����� ������ ��� ������ �����.";
			link.l1 = "...";
			link.l1.go = "Romantic_5";
		break;
        case "Romantic_5":		
			dialog.text = "������ �� ��� � ����!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuest("Romantic_Padre_3");			
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}
