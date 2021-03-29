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
			dialog.text = "��� ���� ���� �������, "+GetSexPhrase("����","����")+" ������� " + sName + "?";
			if(PChar.ColonyBuilding.Stage != "3" && PChar.ColonyBuilding.Action != true)
			{
				link.l1 = "�������, � �������������"+GetSexPhrase("","�")+" � ����� �������.";
				link.l1.go = "Building";
			}
			link.l2 = "������ �����"+GetSexPhrase("","�")+" ��� ��������.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "Hi1":
			dialog.text = "����� ���, "+GetSexPhrase("����","����")+" �������! �� �� ��������, ��� �� ���� ���������!";
			link.l1 = "������������, ������ ��������, �� ������"+GetSexPhrase("","�")+" ��� ����� �������, ��� �� ����� �����������?";
			link.l1.go = "Hi";
			NextDiag.TempNode = "First time";
		break;

		case "Hi":
			dialog.text = "��� �� ������! ��, ������ ��, ������������, ��� �������� ���� � ������� ������������ ���� �����������, ������� ������ ������ �� ����� ������ ������!\n"+
							"������ � ������� ��� ����� ��������, ������� �������� ��� �������� ����� ����� � ���������� �����. �� ������ ����� ��� ��������� ������� ���������� ����������, ��! ����� ��� ������! � ����� � ����� ����, ��� �����..."
			link.l1 = "��� ���? ���������� ���������.";
			link.l1.go = "First time";
		break;

		case "Building":
			dialog.text = "��� ������ �� �� ������?";
			
			if(PChar.ColonyBuilding.Stage == "0")
			{
				link.l1 = "� �����"+GetSexPhrase("","�")+" �� ������ ������������� �������.";
				link.l1.go = "ColonyBuilding";
			}
			
			if(PChar.ColonyBuilding.Stage == "1")
			{
				link.l2 = "� �����"+GetSexPhrase("","�")+" �� ��������� ���� �������, ������� ����� ��� ''" + PChar.ColonyBuilding.ColonyName + "''.";
				link.l2.go = "ColonyModification";
			}
			
			if(PChar.ColonyBuilding.Stage == "2")
			{
				link.l3 = "� �����"+GetSexPhrase("","�")+" �� �������� ���� ������� - �������� ��� � ������ ����.";
				link.l3.go = "ColonyFortBuildingNoNo";
			}
			
			link.l4 = "��������, �� ��� ����. ���� ����.";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "ColonyBuilding":
	    	if(CheckAttribute(pchar, "VedekerDiscount"))//������ �� ��������.
	    	{
				NPChar.NeedMoney = (1500000 * MOD_SKILL_ENEMY_RATE)/2;
	    		dialog.text = "��... ��� ��. �����, ��� ������ ��� ���������� ��������� ����������� ������� ��� ����������� �� ��������� �������. ����� ����, ������ ���, �������, �� ����������, � ������ ����� ���������� "+(1500000*MOD_SKILL_ENEMY_RATE)+" ��������. � ���� ��, � ���� ��������� ��������� ������. ������ � ��� �� ������ ����������� ��������� ������� �� ������� �������� �� "+NPChar.NeedMoney+" ��������, ����, �������, �� ��� �������. ��� �������?";
	    	}
	    	else		
	    	{
				NPChar.NeedMoney = 1500000 * MOD_SKILL_ENEMY_RATE;
		    	dialog.text = "��... ��� ��. �����, ��� ������ ��� ���������� ��������� ����������� ������� ��� ����������� �� ��������� �������. ����� ����, ������ ���, �������, �� ����������, � ������ ����� ���������� "+(1500000*MOD_SKILL_ENEMY_RATE)+" ��������. ��� �������?";
		    }
			
			if(sti(PChar.money) >= sti(NPChar.NeedMoney))
			{
				link.l1 = "� ������"+GetSexPhrase("��","��")+".";
				link.l1.go = "ColonyBuilding_1";
			}
			else
			{
				link.l2 = "���� � �� ���������� ������ ��������.";
				link.l2.go = "exit";
			}
			
			link.l3 = "��������, ��� ����.";
			link.l3.go = "exit";
		break;

		case "ColonyBuilding_1":
			AddMoneyToCharacter(PChar, -sti(NPChar.NeedMoney));
			dialog.text = "����� � ���������� ����� ��� ���������� ������������������ ����������� �������.";
			link.l1 = "���������� ������� ��� ����� �������!";
			link.l1.go = "ColonyBuilding_exit";
			PChar.BuildingColony.Blocks = 500;
			PChar.BuildingColony.Planks = 1000;
			PChar.BuildingColony.Mahogany = 500;
			PChar.BuildingColony.Ebony = 250;
			PChar.BuildingColony.Slaves = 200;
			PChar.BuildingColony.Food = 400;
		break;

		case "ColonyBuilding_2":
			dialog.text = ""+GetSexPhrase("����","����")+" �������. ��������� ���������� ���� ������, � ������ � ������, ��� ��� ������ �� �����, ��� ������� �������� ��������� �������. ���������� ���������� �������� ����� �������������, � ��� ����� ���� ������������ �������� ��� �������, ��. � ���� ��, ����� �������� ����������� ����� �� ���� ���������� ���� ��������.";
			link.l1 = "�� ���, ��������, �������, � ��� ���� ������� � ���� ����������? � ������, � �� ����������!";
			link.l1.go = "ColonyBuilding_2_1";
		break;

		case "ColonyBuilding_2_1":
			dialog.text = "��?! � ��� �� �� ����������� �������� ���������� ��� ������� �������? ���� ����������� �� ����� ������� �� ������������ ���� ��������, ������ ��������? � ����� ������ ��� ���� ���������� � ������, ���� ��� �� ����� ������������� ������� � ����� ����� �� ������!";
			link.l1 = "��-��, ������������, ��������.. �� ���������"+ GetSexPhrase("��","���") +" � ������!";
			link.l1.go = "ColonyBuilding_2_2";
		break;

		case "ColonyBuilding_2_2":
			dialog.text = "� �� �� ����� ���� ����� ����. � �� �� ��� ��� ������ ������.";
			link.l1 = "���.. ��� ������?";
			link.l1.go = "ColonyBuilding_3";
			AddDialogExitQuest("ColonyBuildingCayman");
		break;

		case "ColonyBuilding_3":
			dialog.text = "������ ��� ����������� ��������� ������, ����������� ��� ��������� �������. ������� - " + FloatToString(iBricks,0) + " ��., ����� - " + iPlanks + " ��., ������� ������ - " + iMahogany + " ��., ������ ������ - " + iEbony + " ��., �������� - " + iFood + " ��., � " + iSlaves + " �����. ��� ������ ��� ������ ����� ����������, �� ��������� � �������������, ��!";
			link.l1 = "������.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "ColonyBuilding_4";
		break;

		case "ColonyBuilding_4":
			dialog.text = "��� �� ������, �������?";
			if(sti(PChar.BuildingColony.Blocks) == 0 && sti(PChar.BuildingColony.Planks) == 0 && sti(PChar.BuildingColony.Mahogany) == 0 && sti(PChar.BuildingColony.Ebony) == 0 && sti(PChar.BuildingColony.Slaves) == 0 && sti(PChar.BuildingColony.Food) == 0)
			{
				dialog.text = "� �������� ������� ���, "+ GetSexPhrase("����","����") +" �������, ��� ��� ����������� ������ ����������. �� �������� �������������! �� ���� ��������� ������������� ����� ���� ���� ����� ������.";
				link.l1 = "��� �� ����� �� ��������! ���� � ����������� ����� ��������� �������������.";
				link.l1.go = "exit";
				AddDialogExitQuest("ColonyBuilding_1");
				NextDiag.TempNode = "ColonyBuilding_6";
			}
			else
			{			
				link.l1 = "� �� �����"+GetSexPhrase("","�")+" �������� ��� ����������� ������.";
				link.l1.go = "ColonyBuilding_5";
				NextDiag.TempNode = "ColonyBuilding_4";
			}
		break;

		case "ColonyBuilding_5":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchColonyBuilding(false, false);
		break;

		case "ColonyBuilding_6":
			dialog.text = "�-�, ��� ��, "+GetSexPhrase("����","����")+" �������! ������������� ��� ������ �����, ��!";
			link.l1 = "�� �������.";
			link.l1.go = "exit";
		break;

		case "ColonyBuilding_7":
			dialog.text = "����� ���, "+GetSexPhrase("����","����")+" �������! � ������������� ��� �������, ��� ������������� ����� ������� ���������! ���� ��� ����� ����������� ��� ������, �� ������� ����� ���� � ����� ���������.";
			link.l1 = "�������, ������ ��������. � ������ ����� ���� �������� - ���� ����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ColonyBuilding_8";
			AddDialogExitQuest("ColonyBuilding_3");
		break;

		case "ColonyBuilding_exit":
			AddDialogExitQuest("ColonyBuilding");
			PChar.ColonyBuilding.Architector = NPChar.id;
			NextDiag.TempNode = "ColonyBuilding_8";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ColonyBuilding_8":
			dialog.text = "����� ���, " + sName + ".";
			link.l1 = "�� �������.";
			link.l1.go = "exit";
		break;

		//---------------------------------------------------------------------------------------------------------

		case "ColonyModification":
			dialog.text = "��... ��� ������ �������� ������. �� �� ������ ��������, ��� ����� ������ ��� ������� ������. ������� ��� ���������� ����������� � �����, ��� ���������, � �������� ��� ������ ������������ �������������.";
			link.l1 = "������, �� �������.";
			link.l1.go = "ColonyModification_exit";
		break;

		case "ColonyModification_1":
			dialog.text = "��� � ��, "+GetSexPhrase("����","����")+" �������. ��� ��, ���������. ����� ���, ��� �� ����� ���� �������������, �� ������ ������������ � ������������ �������� ������ � ��� ������.";
			link.l1 = "��... ������� ���������...";
			link.l1.go = "ColonyModification_6";
			NextDiag.TempNode = "ColonyModification_5";
		break;

		case "ColonyModification_2":
			AddQuestRecord("ColonyBuilding", "8");
			dialog.text = "�������, �������. �, ����� ��� ���� ��������, ��� ��� ����������� ��������� ������ ��� ������������� - ������� - " + iBricks + " ��., ����� - " + iPlanks + " ��., ������� ������ - " + iMahogany + " ��., ������ ������ - " + iEbony + " ��., �������� - " + iFood + " ��., � " + iSlaves + " �����. ����� �� ��� ����� ����������, �� ��������� � �������������.";
			link.l1 = "���������� ��������� �� ����������� ��� ����� ������.";
			link.l1.go = "ColonyModification_3";
			LAi_SetPlayerType(PChar);
			LAi_SetStayType(CharacterFromID("Builder"));
		break;

		case "ColonyModification_3":
			dialog.text = "��� �� ������, �������?";
			if(sti(PChar.BuildingColony.Blocks) == 0 && sti(PChar.BuildingColony.Planks) == 0 && sti(PChar.BuildingColony.Mahogany) == 0 && sti(PChar.BuildingColony.Ebony) == 0 && sti(PChar.BuildingColony.Slaves) == 0 && sti(PChar.BuildingColony.Food) == 0)
			{
				dialog.text = "� �������� ������� ���, "+GetSexPhrase("����","����")+" �������, ��� ��� ����������� ������ ���������� � ��� �� �������� �������������. �� ���� ��������� ������������� ����� ���� ���� �����, ��� ������� ������, ��!";
				link.l1 = "���� � ����������� ����� ��������� �������������.";
				link.l1.go = "exit";
				AddDialogExitQuest("ColonyModification_2");
				NextDiag.TempNode = "ColonyBuilding_6";
			}
			else
			{			
				link.l1 = "� �� �����"+GetSexPhrase("","�")+" �������� ��� ����������� ������.";
				link.l1.go = "ColonyBuilding_5";
				NextDiag.TempNode = "ColonyModification_3";
			}
		break;
		
		case "ColonyModification_4":
			dialog.text = "� �������� �������, ��� ���������� ������� ''" + PChar.ColonyBuilding.ColonyName + "'' ���������! � ���� ���� ������� ��������, "+GetSexPhrase("����","����")+" �������. �������, � ������ ��� ��� �����-�� �����. ���� �� �������� ����� ���� ����� - � ���� � �����.";
			link.l1 = "��������� ���, " + NPChar.name + ".";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuest("ColonyModification_4");
		break;

		case "ColonyModification_5":
			dialog.text = "��� ��, "+GetSexPhrase("����","����")+" ������� " + sName + "? ��� ��� ������� ������ �������������?";
			link.l1 = "��, ���� ��� ��� ������������ � ������������ ������ � ������.";
			link.l1.go = "ColonyModification_6";
			link.l2 = "���, ������ ����� ��� ���������.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ColonyModification_5";
		break;

		case "ColonyModification_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchColonyBuilding(true, true);
		break;

		case "ColonyModification_exit":
			PChar.quest.ColonyModification_5.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyModification_5.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyModification_5.win_condition = "ColonyModification_5";
		
			LAi_SetCitizenType(NPChar);
			AddDialogExitQuest("ColonyModification");
			NextDiag.TempNode = "ColonyBuilding_8";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//---------------------------------------------------------------------------------------------------------

		case "ColonyBuilding_Dominica":
			dialog.text = "������� ���������� ���������� ����� ��������� ������� � ������ - ������ �� ������� ����� ������� ����� ������� ������� �����, � �� ��������� ����� ���� �����!";			
			link.l1 = "�������, �� �����. ����� ����������� ������...";
			link.l1.go = "exit";
			AddDialogExitQuest("ColonyBuildingDominica");
		break;

		case "ColonyBuilding_Terks":
			dialog.text = "���, ��� ��, Ҹ��� ��������� ������� ����� � ������ ���������� ��������� �������, � ���� �� �������� ������� ������� � ��� ��� �����, ��!";
			link.l1 = "�������, �� �����. ����� ����������� ������...";
			link.l1.go = "exit";
			AddDialogExitQuest("ColonyBuildingTerks");
		break;

		//---------------------------------------------------------------------------------------------------------

		case "ColonyFortBuildingNoNo":
			dialog.text = "��... �� ������� ��� ��������, "+GetSexPhrase("����","����")+" �������, �� ��������� ������� �� ��������� �������� ������������. ���� ��� ���������� ��������� ������������ �������� ���� - ��� �������� ����� ������������ ��������, ��������� ���� ����� ������ ���������, � ����� ������� ������������� ������� ��� ����������� ������� ������ ��������� �����\n ����� ����, �������� �������� ���� ������� ��� ������� � ������� � ����, ��� ����������� ������ ������ � � ������ ������, �� ���� ��� �������� ��������� ��������� ������� �� ��� ����� � ����. ��� �������, "+GetSexPhrase("����","����")+" �������?";
			link.l1 = "������� ����������� ���������� ��������. ������� ��� ������� ��������� ���������� ������ ��������� �������� ����.";
			link.l1.go = "ColonyFortBuilding";
			link.l2 = "��������, ��� ����.";
			link.l2.go = "exit";
		break;

		case "ColonyFortBuilding":
			if(CheckAttribute(pchar, "VedekerDiscount"))
			{
				NPChar.NeedMoney = (200000 * MOD_SKILL_ENEMY_RATE)/2;
				dialog.text = "� � �������� ������ ���, ��! �� ��� ��� ����� ������ ������� ������. �� ���� ������ � ���� �������� "+Sti(NPChar.NeedMoney)+" �������.";
			}
			else
			{
				NPChar.NeedMoney = 200000 * MOD_SKILL_ENEMY_RATE;
			    dialog.text = "� � �������� ������ ���, ��! �� ��� ��� ����� ������ ������� ������. �� ���� ������ � ���� �������� "+Sti(NPChar.NeedMoney)+" �������.";
			}
			if(sti(PChar.money) >= Sti(NPChar.NeedMoney))
			{
				link.l1 = "� ������"+GetSexPhrase("��","��")+".";
				link.l1.go = "ColonyFortBuilding_1";
			}
			else
			{
				link.l2 = "���� � �� ���������� ������ ��������.";
				link.l2.go = "exit";
			}
			link.l3 = "��������, ��� ����.";
			link.l3.go = "exit";
		break;

		case "ColonyFortBuilding_1":
			dialog.text = "�������, "+GetSexPhrase("����","����")+" �������! ���������� � ����� ��� ��������� ''��������� ����'' - ��� �� � ����� ������� ��������� ������ ��������� ��������.";
			link.l1 = "�� �������.";
			link.l1.go = "ColonyFortBuilding_to_port";
			AddDialogExitQuest("ColonyFortBuilding_1");
		break;

		case "ColonyFortBuilding_2":
			dialog.text = "�������, "+GetSexPhrase("����","����")+" �������! ���������� � ����� ��� ��������� ''��������� ����''.";
			link.l1 = "�� �������.";
			link.l1.go = "ColonyFortBuilding_to_port";
		break;

		case "ColonyFortBuilding_3":
			AddMoneyToCharacter(PChar, -sti(NPChar.NeedMoney));
			dialog.text = "��� ������������� ��� ����������� ��������� ������: ������� - " + iBricks + " ��., ����� - " + iPlanks + " ��., ������� ������ - " + iMahogany + " ��., ������ ������ - " + iEbony + " ��., �������� - " + iFood + " ��., � " + iSlaves + " �����.";
			link.l1 = "���������� ��������� �� ����������� ��� ����� ������.";
			link.l1.go = "ColonyFortBuilding_to_start_transfer_goods";
			AddDialogExitQuest("ColonyFortBuilding_4");
		break;

		case "ColonyFortBuilding_4":
			dialog.text = "��� �� ������, "+GetSexPhrase("����","����")+" �������?";
			if(sti(PChar.BuildingColony.Blocks) == 0 && sti(PChar.BuildingColony.Planks) == 0 && sti(PChar.BuildingColony.Mahogany) == 0 && sti(PChar.BuildingColony.Ebony) == 0 && sti(PChar.BuildingColony.Slaves) == 0 && sti(PChar.BuildingColony.Food) == 0)
			{
				dialog.text = "� �������� ������� ���, �������� �������, ��� ��� ����������� ������ ����������. �� �������� ���������� ����! ���� ������ ������������������� �� ���������, �� ������ ����� ������� �� ���� ����� �� ������� ������ ���� �������, ��.";
				link.l1 = "������, �������� " + NPChar.name + " " + NPChar.lastname + ".";
				link.l1.go = "exit";
				AddDialogExitQuest("ColonyFortBuilding_5");
				NextDiag.TempNode = "ColonyFortBuilding_5";
			}
			else
			{			
				link.l1 = "� �� �����"+GetSexPhrase("","�")+" �������� ��� ����������� ������.";
				link.l1.go = "ColonyBuilding_5";
				NextDiag.TempNode = "ColonyFortBuilding_4";
			}
		break;

		case "ColonyFortBuilding_5":
			dialog.text = "�-�, ��� ��, "+GetSexPhrase("����","����")+" �������! ������������� ��� ������ �����!";
			link.l1 = "�� �������.";
			link.l1.go = "exit";
		break;

		case "ColonyFortBuilding_6":
			dialog.text = "�������� �������� ���� ��� ����� ������� ���������! � ���� ���� ������� ��������, "+GetSexPhrase("����","����")+" �������. � ����������� �����.";
			link.l1 = "������� ��� �� ������, ������ ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
			AddDialogExitQuest("ColonyFortBuilding_7");
		break;
		
		case "ColonyFortBuilding_to_port":
			LAi_SetCitizenType(NPChar);
			NextDiag.TempNode = "ColonyBuilding_8";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ColonyFortBuilding_to_start_transfer_goods":
			NextDiag.TempNode = "ColonyFortBuilding_4";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ForSlave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("� ��� ����� - ������ � ��� ������.", "��� ������ ��� ��� ����!"), RandPhraseSimple("��� ������ ������� ������ ��� ����.", "������������ ��� �� �������� ������ ����� �� ���� �����!"));
			link.l1 = RandPhraseSimple("����������, ��������.", "��� ���� ����.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ForSlave";
		break;
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "����������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.", "������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.");
				link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "��������� �� ���������, "+GetSexPhrase("��������","�������")+", ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� "+GetSexPhrase("�������","�������")+" ����� ������ ���� � ������� �� ���������. ��� ���� ������...");
				link.l1 = RandPhraseSimple("�����"+GetSexPhrase("","�")+".", "������.");
			}
			link.l1.go = "exit";
		break;
		
	}
}
