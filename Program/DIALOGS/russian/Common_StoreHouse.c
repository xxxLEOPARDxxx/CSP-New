
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			dialog.text = LinkRandPhrase("���������� ���! ���� ����������� ��������...", "��, ����� ��� ��������!", "��, ���� ������, ��� �� ��������?..");
			link.l1 = LinkRandPhrase("�������!", "�������...", "��, �������� � ���� ���������...");
			link.l1.go = "exit";
			link.l2 = "����������, " + NPChar.name + ". � ������ ���������������� ������ ������, � �������� � ���-��� �������� �� ��������.";
			link.l2.go = "StoreHouse_Details";
			
		break;

		case "StoreHouse_Details":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStoreHouse(STORE_HOUSE);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
