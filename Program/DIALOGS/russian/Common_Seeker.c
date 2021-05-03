void ProcessDialogEvent()
{
	ref NPChar;
    ref Pchar = GetMainCharacter();
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "FirstTime":
			dialog.text = "������������. � ������� �� ����� ����������� � ��� ���������� ��������� � ������. ��� �� "+GetSexPhrase("�����","�����") + "?";
			link.l1 = "������������. � �� ���� � ���� ������, �� � �� �����. ����� ����� � �����������, �� ����������.";
			link.l1.go = "TryNotBeCut";
			if (CheckNationLicence(sti(npchar.nation)))
				{
					link.l1 = "� ���� ������� " + GetRusNameNationLicence(sti(npchar.nation)) + ", ��� ���, � �������� ����� �� �������� ����������. ����� ������������...";
					link.l1.go = "LicenceOk";
				}
		break;
		case "TryNotBeCut":
			if(pchar.SpySeeker == "Enemy" && (10 + rand(50) + rand(50)) > sti(pchar.skill.sneak))
			{
				dialog.text = "������ ���, ��� �� ���� �����������. �� ������, ����� ������� � �����������.";
				link.l1 = "������ � � ����� �� �����! ���������!";
				link.l1.go = "exit";
				AddDialogExitQuest("SeekerFight");
			}
			else
			{
				dialog.text = "������, �� �����. � ��� ����. �����!";
				link.l1 = "��� � ������. �����!";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				AddCharacterExpToSkill(pchar, "Sneak", 100);
				AddDialogExitQuest("SpySeekerGood");
			}
		break;
		case "LicenceOk":
			dialog.text = "������. �� ���� ������ ��� �����������."
			link.l1 = "�������, ��������.";
			link.l1.go = "exit";
			AddDialogExitQuest("SpySeekerGood");
		break;
	}
}
