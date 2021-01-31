
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string sName = GetNameLugger(PChar, "f");
	string sCharacter = "";
	
	int iShip = 0;
	int iCrew = 0;
	int iShipSP = 0;
	int iShipHP = 0;
	
	string sShipName = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "��� ��� ��������� �� ��������� ������.";
			link.l1 = "�� ����� �������������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "1":
			dialog.text = "�������, �������!!!";
			link.l1 = "��� ��� " + GetNameLugger(PChar, "f") + "! � ������� ������� ''" + PChar.Ship.Name + "''. ��� � ���� ���������?";
			link.l1.go = "2";
		break;
		
		case "2":
			dialog.text = "� - ������� " + GetNameLugger(NPChar, "f") + ". ������ ����� �� ������ � �����.";
			link.l1 = "���� ��� ������� - �������� ��� ���� �������!";
			link.l1.go = "3";
		break;
		
		case "3":
			dialog.text = "��� ��� ����� ������� � ������� �����, ������� � �����-���� ����� �� ���� ����������. � � ����� �������, �������� ���. ��� ��� ��� ������ � ���� ��������, � �� ������ ���������� ���, ����� ����� ��� ����� �� ����� - �������� ����� ��� �����. ������� ���� �� ������ ��������� �� - �� ��������� ����� �� ����. ����� ���� ���� ����������, ��� ������� ������������ ������ �������� ����� �������! ��������� ���� �� �������� � ���� �����. �� ������, ���� �� �����������.";
			link.l1 = "�������� ���������� ���! ���� � ���� ���-�� ������...";
			link.l1.go = "4";
		break;
		
		case "4":
			dialog.text = "���������, �������. �� ����� �� ������ � ���� - � ����� ����� �� ����� ������� ������� ��. �� ���� � ���, ��� � ����� ����� ������� ���������� ����, ������� � ������ ��������� �� ����������. � �� ���� ������� ���������, � ����� ���� ����� � ����� �������� � �������� �� ��������� �������...";
			link.l1 = "�������.";
			link.l1.go = "YesYes";
			link.l2 = "��������, �� ����� �� ����� ������...";
			link.l2.go = "NotNot";
		break;
		
		case "YesYes":
			ShipWreckInSeaWait();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "NotNot":
			ShipWreckInSeaCancel();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "5":
			sCharacter = PChar.GenerateShipWreck.CharacterID;
			SetCameraDialogMode(CharacterFromID(sCharacter));
			dialog.text = GetNameLugger(CharacterFromID(sCharacter), "f") + ": " + GetNameLugger(NPChar, "n") + ", ���� ����� �� �������� �� �������� �� �����. �� �� ������. ��� �������������� ����������.";
			link.l1 = GetNameLugger(NPChar, "f") + ": �����, �������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckInSeaWaitEnd");
		break;
		
		case "6":
			dialog.text = "�� ����� � ���������?";
			link.l1 = "�, ��� ������ �������.";
			link.l1.go = "7";
		break;
		
		case "7":
			dialog.text = "����� �� ���������, ��� � ������ ���������. ���������� ��� � ������ �� ���� ������� � �� ����� �� ��� ��� �� ����������� � ���������� �������. ��� �� ��������� ����� ��������������� ���. ����� �� ���� �������� �����, ��� �������� �������� ���� �������. � �� �������� �����...";
			link.l1 = "���������, " + GetAddress_FormToNPC(NPChar) + ". � ����� ��������� ���� ������� ����.";
			link.l1.go = "8";
		break;
		
		case "8":
			dialog.text = "�� ��� ��, ������ ������. �� �������� � ����� ���������� ��� ������� �������� ��� " + sti(PChar.GenerateShipWreck.Money) + " �������. ��� ��, ��� � ���� ������������ ��� �� ������.";
			link.l1 = "�����, �� ������!";
			link.l1.go = "9";
		break;
		
		case "9":
			dialog.text = "������������� � ����. �����, " + GetNameLugger(PChar, "f") + "!";
			link.l1 = "�� ��������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckInSeaWaitEndToSea");
		break;
		
		case "10":
			dialog.text = "�-�, �������. ��� ��� �������, ��� ����� ��� �� ����.";
			link.l1 = "�� ����� �������������.";
			link.l1.go = "11";
		break;
		
		case "11":
			dialog.text = "��������� ������, ���� �� ������?";
			link.l1 = "� �� ����... ׸��, � �� ����!!!";
			link.l1.go = "12";
			link.l2 = "� ���� � ���� ����. � ������ � ����� ������ ������� ���� ����� ����...";
			link.l2.go = "14";
		break;
		
		case "12":
			dialog.text = "�� � �������? ���-�� ���������?";
			link.l1 = "��� ������� �������� ��� � ����� �����. ���� ����� � �������. ��� �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "13";
		break;
		
		case "13":
			dialog.text = "�-�, �������. ��� ��� �������, ��� ����� ��� �� ����.";
			link.l1 = "�� ����� �������������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "13";
		break;
		
		case "14":
			dialog.text = "�� ��� ��� �� ���������?!";
			link.l1 = "� �� ����� ������, ��� ��� �� ����. � �� ��� � ���� ��������. ����...";
			link.l1.go = "15";
		break;
		
		case "15":
			dialog.text = "����?";
			link.l1 = "���� ������, ����� ����� � ������.";
			link.l1.go = "16";
		break;
		
		case "16":
			dialog.text = "��������� �������! ���������, ������!";
			link.l1 = "��...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBattleWithSailor");
		break;
		
		case "17":
			dialog.text = "��������! ��� ���� �����?";
			link.l1 = "����� ���� ���� ������, " + GetAddress_FormToNPC(NPChar) + " " + GetNameLugger(NPChar, "f") + ".";
			link.l1.go = "18";
		break;
		
		case "18":
			dialog.text = "������� ���. � ���������� � ������!";
			link.l1 = "� ����� ������ ���� �����, ���� �� ������, ��� ������� ������?";
			link.l1.go = "19";
		break;
		
		case "19":
			dialog.text = "����� ���� � �������� �� ���� �������!";
			link.l1 = "...";
			link.l1.go = "exit";
			PChar.GenerateShipWreck.State = "none";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam");
		break;
		
		case "20":
			dialog.text = "��� �� � �������. �������, �������, ������ � ���.";
			link.l1 = "�� ��� �. ����� ����.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckInTownSuccess");
		break;
		
		case "21":
			dialog.text = "��� �� �����?";
			link.l1 = "� ���� ����� ����� �� ������.";
			link.l1.go = "22";
		break;
		
		case "22":
			dialog.text = "� �� ����� �����.";
			link.l1 = "������. � ������� " + GetNameLugger(PChar, "f") + ".";
			link.l1.go = "23";
		break;
		
		case "23":
			dialog.text = "� ��� ���� ���� �� ����� ����� �������?";
			link.l1 = "� ���� �� ����� �����. ������ ���������� ����� ������������, ������� ���� ������� �������� ��� ���� �������.";
			link.l1.go = "24";
		break;
		
		case "24":
			dialog.text = "����� ��� � ������. � ������� ����� ������� - " + GetNameLugger(NPChar, "f") + ". ��� ��� ���� ����� �����?";
			link.l1 = "���� ���������� � ���������.";
			link.l1.go = "25";
		break;
		
		case "25":
			dialog.text = "������� �������. �� ����� ������ ��� ������ ������� ���������. ������ � ��� �������.";
			link.l1 = "�������? � ��� ��� �� ����� �� ������?";
			link.l1.go = "26";
		break;
		
		case "26":
			dialog.text = "������ � ������ ����. �� ����� ������ ���� ����� �� ������, ����� ������ ��������.";
			link.l1 = "�������. �� ��� ��, �������, �� ���� ��� �����������. �������� ��� ��������.";
			link.l1.go = "27";
			link.l2 = "�������� ����, ������ ���������...";
			link.l2.go = "36";
			link.l3 = "�� ��� ���� �� ������ �������?";
			link.l3.go = "45";
			link.l4 = "� �� ������� �������, �� � �������� ����������. ������� ����� ��� ������� - ����� � ����� ������� �������� ��� �� ��� �����. � ������, �������!";
			link.l4.go = "41";
		break;
		
		case "27":
			dialog.text = "������. ��� ������, ������� ��� ����� � �����. ������� �������� � ������� ����� ��� �� �� �������. ��� �������?";
			
			if(GetCargoGoods(PChar, GOOD_PLANKS) > 0 || GetCargoGoods(PChar, GOOD_SAILCLOTH) > 0)
			{
				link.l1 = "��������� - ������ � ���.";
				link.l1.go = "28";
			}	
			
			link.l2 = "� �� ������ - �� ��������.";
			link.l2.go = "35";
		break;
		
		case "28":
			sCharacter = PChar.GenerateShipWreck.ValodyaID;
			SetCameraDialogMode(CharacterFromID(sCharacter));
			dialog.text = GetNameLugger(CharacterFromID(sCharacter), "n") + ", ������ � ��������, ������ � ���� �������.";
			link.l1 = "...";
			link.l1.go = "29";
			ShipWreckBandValodyaToMoney();
		break;
		
		case "29":
			SetCameraDialogMode(NPChar);
			dialog.text = "�� ������� ����� �� ������? � ��� � ����� ��� ��� ���� ���� ������ ������������� ������.";
			link.l1 = "����������� ������� ������.";
			link.l1.go = "30";
		break;
		
		case "30":
			dialog.text = "��-��.";
			link.l1 = "...";
			link.l1.go = "31";
		break;
		
		case "31":
			ShipWreckBandValodyaReturnWithMoney();
			dialog.text = "������ ��� ������. ������� ������ ��������?";
			link.l1 = "����� ���������.";
			link.l1.go = "32";
		break;
		
		case "32":
			PChar.GenerateShipWreck.GoodsChange = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchQuicklyTrade();
		break;
		
		case "33":
			dialog.text = "��������?";
			link.l1 = "������. ���� ����� ��������� �� �������. �, �������, � �� ��������� ���� �������� ���� ������ �� �������, � ���� �������� �� �������. ������� ������� ��� ���������� ����� �� ������.";
			link.l1.go = "34";
		break;
		
		case "34":
			PChar.GenerateShipWreck.GoodsChange.Yes = true;
			dialog.text = "��-��.";
			link.l1 = "�������� ��������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsOneTypeEnd");
		break;
		
		case "35":
			PChar.GenerateShipWreck.GoodsChange.Yes = false;
			ShipWreckBanditsOneTypeEnd();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "36":
			dialog.text = "��� �� �� ���� ��������, ������?";
			link.l1 = "� ��� ��� ���� �������� ����� ��������. �� � ����� ����� �� �� ��������. �� ����, ��� �� ��� ����� ����� � ���� ������. � ����� �������� ��� ������� � �������, �� �� ���� ��� �� � ����� ���. ��, ��� ��� ������� ��������, ���������� �������� �������, ������� ������� ��� �� ������� � ���������� ��� �����������, �� ��� ��� ������������ �����. ��� ���, ������� �����, �� ������ ����?";
			link.l1.go = "37";
		break;
		
		case "37":
			sCharacter = PChar.GenerateShipWreck.ValodyaID;
			dialog.text = "�� ����� ����� � ����� ������ ���� �������.";
			
			if(sti(PChar.GenerateShipWreck.ToSquadron) == 1)
			{
				SetCameraDialogMode(CharacterFromID(sCharacter));
				link.l1 = GetNameLugger(CharacterFromID(sCharacter), "f") + ": ������, " + GetNameLugger(NPChar, "n") + ". � ���� ������ ����� � ����� �������.";
				link.l1.go = "38";
			}
			else
			{
				link.l1 = "�� ��������, " + LinkRandPhrase("�����", "���������", "������") + "!";
				link.l1.go = "41";
			}	
		break;
		
		case "38":
			SetCameraDialogMode(NPChar);
			dialog.text = RandSwear();
			link.l1 = "� ������ ���� �� ������ ���, ����� ������. �� ���� ������ ������ ���-���� �������� - ����� �� ���� ������.";
			link.l1.go = "39";
		break;
		
		case "39":
			dialog.text = "��� ���� �����?";
			link.l1 = "�� ������ ������� ��� ���� �������?";
			link.l1.go = "40";
		break;
		
		case "40":
			dialog.text = "���� ������, �������! � ������ � ����.";
			link.l1 = "� ���� ��� �������. ������, �� ��������� ����� �� ���������� ��� ��� ������. � ������, �� ���������� ���� ��������� �� ������ �������.";
			link.l1.go = "42";
			link.l2 = "�� ������ ���������� ���� ��������� �� ������ �������.";
			link.l2.go = "43";
			link.l3 = "��-��, � �������. �������� ��������!";
			link.l3.go = "35";
		break;
		
		case "41":
			ShipWreckBanditsStartBattle();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "42":
			if(sti(PChar.GenerateShipWreck.ToSquadronWithMoney) == 1)
			{
				sCharacter = PChar.GenerateShipWreck.ValodyaID;
				PChar.GenerateShipWreck.ValodyaToMoney = true;
				SetCameraDialogMode(CharacterFromID(sCharacter));
				dialog.text = "�� ��������. " + GetNameLugger(CharacterFromID(sCharacter), "n") + ", �� ������ ��� ������.";
				link.l1 = "�����.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ShipWreckBandValodyaToMoney");
			}
			else
			{
				dialog.text = "�� � ��� ��� �����.";
				link.l1 = "� ����� ������ �������� ��������. ����� ��������.";
				link.l1.go = "35";
				link.l2 = "����� ������������ � ������, " + LinkRandPhrase("�����", "�����", "������") + "!";
				link.l2.go = "41";
				link.l3 = "��� � ���� - � ������ ���.";
				link.l3.go = "43";
			}
		break;
		
		case "43":
			PChar.GenerateShipWreck.AddBandaShip = true;
			sCharacter = PChar.GenerateShipWreck.ValodyaID;
			dialog.text = "�� ��������. " + GetNameLugger(CharacterFromID(sCharacter), "n") + ", �� ������ ��� ������.";
			link.l1 = "��� � ������������. � ������ �� ������!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsOneTypeEnd");
		break;
		
		case "44":
			PChar.GenerateShipWreck.AddBandaShip = true;
			AddMoneyToCharacter(PChar, sti(PChar.GenerateShipWreck.Money));
			dialog.text = "�������, ��� ������. ����� ����� " + sti(PChar.GenerateShipWreck.Money) + " ��������.";
			link.l1 = "��������, ��� �� � ���� �������. � ������ ������� ������� �� ���� �������! �, ����!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsOneTypeEnd");
		break;
		
		case "45":
			dialog.text = "�� ��� � ���?";
			link.l1 = "������ ��� ��� �������? ��� ���, ������� �� �������, ��� �� ������ ��� ������� � ���� ��������, ���� �� ���� ���-�� ��������. � ������ ������ ����, ����� ������. �� ��������� � �� ������ ���� �������� �� ��� ��� �����. � ��� ������� ��������. ��� ���, ��� �� ������ ���� ������ �������, �� ��������� ���. ���� ����� ���� ����� � �� ����� ���� �����, �� ������ ������ ������ ������� ���� � ������. �� � ��� �� ������ ���� �� ��������. ����� �����.";
			link.l1.go = "46";
		break;
		
		case "46":
			dialog.text = "�� �����, ��� ���������� �����, � �� � ����� ������ �������. � �������� ������� ���� ��������.";
			link.l1 = "� ���� �� ������ �������������� �� ���� ����������. � �� ���� ���������� ������� ���������� ������. ������ ����� �������� �� �������, ��� ���� ������ ����� �������� �� ������. ����?";
			link.l1.go = "48";
		break;
		
		case "47":
			sCharacter = PChar.GenerateShipWreck.ValodyaID;
			dialog.text = "�� ����� ����� � ����� ������ ���� �������.";
			
			if(sti(PChar.GenerateShipWreck.ToSquadronWithMoney) == 1)
			{
				SetCameraDialogMode(CharacterFromID(sCharacter));
				link.l1 = GetNameLugger(CharacterFromID(sCharacter), "f") + ": ��� ������, " + GetNameLugger(NPChar, "n") + ", � ��� ��� ������.";
				link.l1.go = "49";
			}
			else
			{
				link.l1 = "�� ��������, " + LinkRandPhrase("�����", "���������", "������") + "!";
				link.l1.go = "41";
			}
		break;
		
		case "48":
			dialog.text = "...";
			link.l1 = "������ ��� ������. � ���.";
			link.l1.go = "47";
		break;
		
		case "49":
			AddQuestRecord("ShipWreck", "8");
			AddMoneyToCharacter(PChar, sti(PChar.GenerateShipWreck.Money));
			SetCameraDialogMode(NPChar);
			dialog.text = "...";
			link.l1 = "� ���, ��� �� ������ ���� �����. ������� �������� ����� ����������, �� �������� �� ���� �����. ��������. � �������� ����, ���� � ��� ��� ��� �����.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsOneTypeEnd");
		break;
		
		case "NewCap_1":
			dialog.text = "�� ������ ���!";
			link.l1 = "��� ����� ���������?";
			link.l1.go = "NewCap_2";
			
			iShip = sti(PChar.GenerateShipWreck.ShipWreckIdx);
			iCrew = sti(PChar.GenerateShipWreck.PrisonedCrew);
			
			sShipName = PChar.GenerateShipWreck.ShipWreckName;
			NPChar.Ship.Type = iShip;
			NPChar.Ship.Name = sShipName;
			SetCrewQuantity(NPChar, iCrew);
			
			iShipHP = sti(PChar.GenerateShipWreck.ShipHP);
			
			SetBaseShipData(NPChar);
			NPChar.ship.HP = iShipHP;
			MakeSailDmg(GetCharacterIndex(NPChar.id), 90);
		break;
		
		case "NewCap_2":
			dialog.text = "���� ����� " + GetNameLugger(NPChar, "f") + " - � ��������� ������� �������. ����� ������ ����� ���� ������������ ��������� �����. � �� �� ������������ � ���� ������, ���� �� ������� �� �������� ������� �������. �� ��� ��� ��������, � ��������� ������� �� ���� ������� �����. \n ������� ��� ������� �� �������. � ��������, ��������� �������� ������. � ����� �� ������ ��� �������� ������ ����� �������. �� ������ ������ �������� �� ������ ��������... � ������ ��� �������� ����� " + sti(PChar.GenerateShipWreck.PrisonedCrew) + " �������. ������ ����� � �����, ��� ����� ������� ��������. \n � ���� �� �����, ����������� �����, ��� ����� ����� �� �������� � ������������, ������ ������� �������, ������� ������ ���� ��� �� �����������. �� ����, ��� ��� ����������, �� ��� ���� ������� ����� � ��������� ��������� ������� � �������. ������, ��� �������� ���� ���������. ����������, ��� ������� ��� � ��� �����. ��� ���� ������, �� ��������� ����.";
			link.l1 = "��, ���� ����� ������� ��� ���� ����, ���� ����� ����.";
			link.l1.go = "NewCap_3";
		break;
		
		case "NewCap_3":
			dialog.text = "��� ��� �����?";
			link.l1 = GetNameLugger(PChar, "f") + ", ������� ������� ''" + PChar.Ship.Name + "''.";
			link.l1.go = "NewCap_4";
		break;
		
		case "NewCap_4":
			AddMoneyToCharacter(PChar, sti(PChar.GenerateShipWreck.Money));
			dialog.text = GetNameLugger(PChar, "n") + ", � ��������� ��� �� ��������. �������� ��� " + sti(PChar.GenerateShipWreck.Money) + " �������, � ���� �������� ��������.";
			link.l1 = "� ������ ��� �� ����������� ����������. �������, ��� �� ����������� ������ ������?";
			link.l1.go = "NewCap_5";
		break;
		
		case "NewCap_5":
			if(sti(PChar.GenerateShipWreck.ToSquadron) == 1)
			{
				dialog.text = "� ��������� ��� ����� ��� ������� � �������. �� �������� ���� ���������.";
				
				if(GetCompanionQuantity(PChar) < 5)
				{
					link.l1 = "������ �� � ���. � �������������.";
					link.l1.go = "NewCap_6";
				}
				
				link.l2 = "� ���������, � �� ���� ����� ��� � ���� �������. ����� ���.";
				link.l2.go = "NewCap_7";
			}
			else
			{
				dialog.text = "�� ��������� ������� �� ��� ������ - �� ������� ����. ��� ��� ������� ���, �������.";
				link.l1 = "�� ��������.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ShipWreckBanditsNewCapNoAdd");
			}
		break;
		
		case "NewCap_6":
			dialog.text = "��������� ���, �������. �������, �� � ���� �����������.";
			link.l1 = "�� ����������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsNewCapAdd");
		break;
		
		case "NewCap_7":
			dialog.text = "����� ����. ������� ���������� ����� ������.";
			link.l1 = "�� ��������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreckBanditsNewCapNoAdd");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
