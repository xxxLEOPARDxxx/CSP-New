
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
		case "First":
			dialog.text = RandPhraseSimple("����� ���, ������ ������, � ��� ������� �����...","� ���� �����"+GetSexPhrase("�� ����? ����������� ����, � ������ ���������, � �� ������� ��� ����� �������.","���� ����? ����������� ����, � ������ ���������, � ��� ������� ��� �������."));
			link.l1 = "O__O";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
