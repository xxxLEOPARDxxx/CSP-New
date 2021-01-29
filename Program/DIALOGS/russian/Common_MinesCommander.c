void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref PChar = GetMainCharacter();
	string sName = PChar.name + " " + PChar.lastname;
	
	int iBricks = sti(PChar.BuildingColony.Blocks);
	int iPlanks = sti(PChar.BuildingColony.Planks);
	int iMahogany = sti(PChar.BuildingColony.Mahogany);
	int iEbony = sti(PChar.BuildingColony.Ebony);
	int iSlaves = sti(PChar.BuildingColony.Slaves);
	int iFood = sti(PChar.BuildingColony.Food);
			
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "��� ���� ���� �������, �������� ������� " + sName + "?";
			if(PChar.ColonyBuilding.Stage != "2" && PChar.ColonyBuilding.Action != true)
			{
				link.l1 = "�������, � ������������� � ����� �������.";
				link.l1.go = "Building";
			}
			link.l2 = "������ ����� ��� ��������.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "Hi1":
			dialog.text = "�����������, �������! ���������� � ���� �������?";
			link.l1 = "������������. � ����� �������?";
			link.l1.go = "Hi";
			NextDiag.TempNode = "First time";
		break;

		case "Hi":
			dialog.text = "��, �� �������� �� ������. � - ��������� � ���� ���������� ����������. � ���� ������ ������������� ������� �� ����� �� ����������� ��������. �� ����� ������� ����� ������� ����, ��������.";
			link.l1 = "��� ���? ���������� ���������.";
			link.l1.go = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
