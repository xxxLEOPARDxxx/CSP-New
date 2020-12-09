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
			if (pchar.questTemp.State == "Fr4SoleiRoyal_GoodWork")
			{
				dialog.text = "� ������ ���, �������.";
				link.l1 = "������, �������-������������ ������� ��� �������� ����������� �������� ������� ������� ������ '����� ������' �� ������� ��������. ��� ���� ������ ���� ������� ������� ���������, �� �� �� ��������� �� �����. �� ������ ���-�� ��������� ��������?";
				link.l1.go = "Step_F4_1";		
			}
		break;
		//************************** ��.��������, ����� �4. ����� ������ ************************
		case "Step_F4_1":
            dialog.text = "���� � ���, ��� � ������� ������������ � ���������� ������� � �������� ������ ����� - ������ ������ �������. ����� �������, � �� ����� ����������� �������. � �������, ��� �� ��� ��� �� ��������...";
			link.l1 = "�����. ��� �������� ������� ��� � ��������� �������� ������� ����� ������. �� �������� � ������� ��������� '����� ������'.";
            link.l1.go = "Step_F4_2";
        break;
		case "Step_F4_2":
            dialog.text = "� ��� ������ ���� ���� ������ � ��� ��������?";
			link.l1 = "�� ���, �����...";
            link.l1.go = "Step_F4_3";
        break;
		case "Step_F4_3":
			if (CheckCompanionInCharacter(pchar, "SoleiRoyalCaptain"))
			{
				dialog.text = "��-��, ���������� ������! �� ��� ��, ���� ������ ��������� - �� ������ ��������� '����� ������' �� ����� ���������� � � ������ ���������� � ��������� ���������. ���������� ������, �������. ������ � �������� � ��� ������������ '����� �������'.";
				link.l1 = "���������, ������. �� ���� ��� ����������� - ����... ��������, �����.";
				link.l1.go = "exit";
				RemoveCharacterCompanion(pchar, characterFromId("SoleiRoyalCaptain"));
				pchar.questTemp.State = "Fr4SoleiRoyal_backTortuga";
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "6");
			}
			else
			{
				dialog.text = "�� �� �� ������ ��������� '����� ������'! ��� �����, �����"+ GetSexPhrase("�","���") +", ����� �����... ������ ��� �������� ������� � �������-����������� ������� � �������� � ������� ����� ������. ��������.";
				link.l1 = "��������, �����...";
				link.l1.go = "exit";
				pchar.questTemp.State = "Fr4SoleiRoyal_SoleiRoyalSunk";
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "7");
			}
        break;
		//************************** ��������� ������ ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("�� ��� ��� �������. ��� ��� ��� �����?", "������� �������� ��� ���-��, ��� �� �� ����������?");
            link.l1 = RandPhraseSimple("������������ ����������...", "��������, ����� �����"+ GetSexPhrase("","�") +" ��� �������...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		//����� ��������, ����� � ������� �����
        case "Ascold_MummyAttack":         
			dialog.text = "�-�-�-�!!!";
			Link.l1 = "������ �����, �����. � ����� �� ���� � �� ������� ���� �����.";
			Link.l1.go = "Step_Asc1";
			AfterTownBattle();
        break;
        case "Step_Asc1":
            dialog.text = "����� �������!!! �-�-�-�!!!";
			Link.l1 = "������ ����, ���������� ����. � ����, ��� � ���� ���� ������ ��������: ��� ����������� ������ ��������� ������� ����� � �������� ��������� �������, ������� �� ����������. ����� ��� ��� �������� � �� �������� �� ������.";
			Link.l1.go = "Step_Asc2";
        break;
        case "Step_Asc2":
            dialog.text = "��� � ����� ����� �� ����, � ����� �� �������� ������. ��� ����, ������ ��� ��������...";
			Link.l1 = "��� �� �� ��� ��������, ������...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
			Locations[FindLocation(pchar.location)].box1.items.sculMa1 = 1;
            Locations[FindLocation(pchar.location)].box1.items.sculMa2 = 1;
            Locations[FindLocation(pchar.location)].box1.items.sculMa3 = 1;
            Locations[FindLocation(pchar.location)].box1.items.indian22 = 1;
            pchar.questTemp.Ascold = "Ascold_MummyFoundItems"; 
			chrDisableReloadToLocation = false;
			SetReturn_Gover_Dialog_Exit(NPChar);
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

