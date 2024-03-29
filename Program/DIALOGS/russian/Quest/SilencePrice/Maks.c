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
        dialog.text = "�� ��� ���" + GetSexPhrase("��", "��") + "? ��� ������, ���� ���" + GetSexPhrase("", "�") + ", � �� � ���������� �������������.";
        link.l1 = "����, ����, ��������, � ������" + GetSexPhrase("", "��") + " ���� ������ �� ���� ������.";
        link.l1.go = "GiveLetter1";
		Map_CreateFastWarriorTreasure();
		DeleteAttribute(Pchar,"Luke.SpawnMaks");
    break;
    case "GiveLetter1":
        dialog.text = "��? � ��� �� ���?";
        link.l1 = "��, ��������.";
        NextDiag.CurrentNode = "Plata";
        AddDialogExitQuest("GiveLetter");
    break;
    case "Plata":
        dialog.text = "��� ��, ��� �����. ��, ���� �� �����, ��� ���� ������. � �� �����, ������� �� ���� ��������.";
        link.l1 = "�������. � �������� ������ ��� ��������.";
        AddQuestRecord("Silence_Price", "2");
        AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
        PlaySound("Interface\notebook_01");
        link.l1.go = "exit";
        AddDialogExitQuest("Plata1");
		NextDiag.TempNode="Bye";
        Characters[GetCharacterIndex("Old Friend")].Dialog.CurrentNode = "SecondQuest_1";
		ChangeCharacterAddressGroup(CharacterFromID("Old Friend"),"none","none","none");
		Pchar.Quest.Luke = "1";
		
    break;
	case "Bye":
		dialog.text="����������, � �� � ���������� �������������.";
		link.l1="�� �����-�� � ��������.";
		link.l1.go="exit";
	break;
	case "Guardians":
		dialog.text = "��� ����� ����������?! ��������� �����?! ����� ���!";
		link.l1 = "�� ����������...";
		link.l1.go = "exit";
		AddDialogExitQuest("FightGuardians");
		LAi_group_MoveCharacter(NPChar, "Maks1");
	break;
    }
}