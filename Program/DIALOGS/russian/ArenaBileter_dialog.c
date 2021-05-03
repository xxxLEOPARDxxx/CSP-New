
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
			if(CheckAttribute(PChar, "Arena.Mode"))
			{
				if(PChar.Arena.Mode == "Duel")
				{
					if(sti(PChar.Arena.Duel.BiletCount) == 1)
					{
						dialog.text = "�-�, ��� ��, ������� " + PChar.name + " " + PChar.lastname + "? ���������!";
						link.l1 = "...";
						link.l1.go = "exit";
						AddDialogExitQuestFunction("PrepareArenaDuelEnd");
						NextDiag.TempNode = "Second Time";
						break;
					}
				}
				
				if(PChar.Arena.Mode == "Etaps")
				{
					if(sti(PChar.Arena.Etaps.BiletCount) == 1)
					{
						dialog.text = "�-�, ��� ��, ������� " + PChar.name + " " + PChar.lastname + "? ������ ��������� �� �������� ������?";
						link.l1 = "���... �����, ���������.";
						link.l1.go = "exit";
						AddDialogExitQuestFunction("PrepareArenaEtapsEnd");
						NextDiag.TempNode = "Second Time";
						break;
					}
				}
				
				if(PChar.Arena.Mode == "Tournament")
				{
					if(sti(PChar.Arena.Tournament.BiletCount) == 1)
					{
						dialog.text = "�-�, ��� ��, ������� " + PChar.name + " " + PChar.lastname + "? ��� ��������� ������� ��� � �����! ������� ��������� ����� ���������. ����� ���, �������...";
						link.l1 = "�������...";
						link.l1.go = "exit";
						AddDialogExitQuestFunction("PrepareArenaTournamentEnd");
						NextDiag.TempNode = "Second Time";
						break;
					}
				}
				
				if(PChar.Arena.Mode == "Odds")
				{
					if(sti(PChar.Arena.Odds.BiletCount) == 1)
					{
						dialog.text = "�-�, ��� ��, ������� " + PChar.name + " " + PChar.lastname + "? ������, �� ��������� ���� � ������ �������� �������, �������� �� ������ �� ���������? ����� ��� �����!";
						link.l1 = "�������...";
						link.l1.go = "exit";
						AddDialogExitQuestFunction("PrepareArenaOddsEnd");
						NextDiag.TempNode = "Second Time";
						break;
					}
				}
				
				if(PChar.Arena.Mode.NotOdd == true)
				{				
					dialog.text = "����! �� ��� �����? ��������� �����, ����� � ������ ������!";
				
					if(GetCharacterItem(PChar, "ArenaBilet"))
					{
						link.l1 = "��� ��� �����. � ������ ��������!";
						link.l1.go = "Bilet_Action";
					}
					link.l2 = "�-�-�... � ������� �������.";
					link.l2.go = "exit";
					AddDialogExitQuestFunction("PrepareArenaOddsBilet");
				}
			}
			
			NextDiag.TempNode = "First time";
		break;
		
		case "Bilet_Action":
			TakeItemFromCharacter(PChar, "ArenaBilet");
			dialog.text = "�-�.. ���-���.. ������ �� ������ ������.";
			link.l1 = "���-�� �����.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PrepareArenaOddsEnd");
			NextDiag.TempNode = "Second Time";
		break;
		
		
		case "Second Time":
			dialog.text = "�� ������� �� ���������� �������� � ���? � ��� ����� ���� ����������!";
			link.l1 = "��.";
			link.l1.go = "Trade_exit";
			link.l2 = "���.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Second Time";
		break;
		
		case "Trade_exit":
            		if(CheckNPCQuestDate(NPChar, "Item_date"))
			{
				SetNPCQuestDate(NPChar, "Item_date");
				ArenaBileterGiveItems(NPChar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar);
		break;
		

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "":
			dialog.text = NPCStringReactionRepeat("", 
				"", 
				"",
                "", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("", 
				"",
                "", 
				"", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_1";
		break;
		case "_1":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_2";
		break;
		case "_2":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_3";
		break;
		case "_4":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_5";
		break;
	}
}
