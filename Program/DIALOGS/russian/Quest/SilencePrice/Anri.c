void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;
    int i;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
    break;
    case "First Time":
        dialog.text = "����, "+GetSexPhrase("��������.","�������.") + " �� ����� ����, ���? ������ �� ��������. ��� ������� � ������� �� ����� ���� ��������. ���" + GetSexPhrase("���.","�.");
        link.l1 = "���... ������, � �����.";
        link.l1.go = "exit";
		AddDialogExitQuest("PirateGoOut");
		NextDiag.TempNode = "Isabella_1";
    break;
	case "Isabella_1":
		Pchar.quest.PirateComeToIsabellaLoose.over = "yes";
		dialog.text = "�, ��� � ��. ��, ����������, ����� ���� ���?";
		link.l1 = "� ��� �� �����, ��� �� � �������" + GetSexPhrase("","�") + " �� ���� �������?";
		link.l1.go = "PrepareFight";
		if (Pchar.Luke.Info == "Peace") 
		{
			link.l2 = "��� ��� ������ ����. � ��������" + GetSexPhrase("","�") + " ��� �������. ����� � ������" + GetSexPhrase("��","����") + " ��� ����� �� ����. ���� ��� �����������."
			link.l2.go = "PeaceDial";
		}
		DeleteAttribute(pchar,"Luke.Info");
	break;
	case "PrepareFight":
		dialog.text = "�� ������, ������ ��� ����� ���? �� �����, � �� ����, ��� � ����� �����. ��� �� �� ��� �������?";
		link.l1 = "�����! � ���� �������� �� ���"+GetSexPhrase(".","��.") + " ����� � ���� � ��� ����?!";
		link.l1.go = "PrepareFight_1";
	break;
	case "PrepareFight_1":
		dialog.text = "���� ��� ��������� ����� �� ��������! ��, ��� ��� ����� �� ����, ��� ���� �������.";
		link.l1 = "� �� �������" + GetSexPhrase("��?!","���?!") + " �� ������ ��� �������?! ����� �� ����?";
		link.l1.go = "PrepareFight_2";
	break;
	case "PrepareFight_2":
		dialog.text = "������, � ���� ����������� � �����, �� �� " + XI_ConvertString("Colony" + Pchar.Luke.City + "Gen") + " ������ �� ���������. ���������!";
		link.l1 = "��������, �� �������!";
		link.l1.go = "exit";
		AddDialogExitQuest("PrepareFightAnri");
	break;
	case "PeaceDial":
		dialog.text = "��... �������. ������ �� � ���� �������. ��� �� ����������� ������?";
		link.l1 = "��� ������ ������� �� ��� �����, � ��� � ��� ���������, ��� ������.";
		link.l1.go = "PeaceDial_1";
	break;
	case "PeaceDial_1":
		dialog.text = "������, � ���� ������. � ����� ����, ��� �� ���������. ������ ��� ��� ����� �� �������, � ���� ��� �������, �� � � ������� " + NationNameGenitive(sti(Colonies[FindColony(Pchar.Luke.City)].nation)) + " ��� ���� �������.";
		link.l1 = "������, � ������" + GetSexPhrase("��.","��.") + " ������ ���, �� ��� ������.";
		link.l1.go = "PeaceDial_2";
	break;
	case "PeaceDial_2":
		dialog.text = "������ �� ��������� � ����� " + XI_ConvertString("Colony" + Pchar.Luke.City + "Gen") + ". ������ ����� �� ���-�� ��������, ��� ����������, � ���� �������" + GetSexPhrase("��","��") + ", �� ����� �����.";
		link.l1 = "";
		link.l1.go = "PeaceDial_3";
	break;
	case "PeaceDial_3":
		dialog.text = "����� ����, � ������ ��� �����. ��� ������� ������������� ��� ������. ������.";
		link.l1 = "������� ����. ������.";
		link.l1.go = "exit";
		AddDialogExitQuest("PirateGoOut1");
	break;
    }
}