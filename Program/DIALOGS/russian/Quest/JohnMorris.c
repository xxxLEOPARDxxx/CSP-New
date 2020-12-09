// ���� ������, ������������ ������ �� ���������� �������
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
		// ----------------------------------- ������ ������ - ������ �������
		case "First time":
			dialog.text = "����� �������� ��� ���. � �����, � � ���� ��� ������� ������������� � ����.";
			link.l1 = "� ��� �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (pchar.questTemp.Sharp == "begin" && rand(1))
			{
				link.l1 = "����, � ������"+ GetSexPhrase("","�") +" � ������ �������, ��� ���������� � ����� �����. �� �� � ����� ����� �������?";
				link.l1.go = "SharpPearl_1";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			dialog.text = LinkRandPhrase(GetFullName(pchar) + ", ��� ���� ������! ����� ���������"+ GetSexPhrase("","�") +" �� ���� ���?",
                                         RandSwear() + " ���� � ����?! �� ��� ��� ���� " + GetFullName(pchar) + ". ������ �������� �� �������?",
                                         "���-���, "+ GetFullName(pchar)+ " � ���� � ������. ����� �� � ��� ��� �������, ��� �� ������������ � �������... �� ���, ����� �������, "+ GetSexPhrase("����","�������") +"?");
			link.l1 = RandPhraseSimple("������ ��������"+ GetSexPhrase("","�") +" ��������� ����.", "������ ����, ������ �������������.");
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (pchar.questTemp.Sharp == "begin" && rand(1))
			{
				link.l1 = "����, � ������"+ GetSexPhrase("","�") +" � ������ �������, ��� ���������� � ����� �����. �� �� � ����� ����� �������?";
				link.l1.go = "SharpPearl_1";
			}
		break;

		//********************* ������� ���� *********************
		case "SharpPearl_1":
			dialog.text = "���, �� � �����. ��� - � �����, "+ GetSexPhrase("��������","�������") +". ���� �� �������������� ������� ��� ���������...";
			link.l1 = "� �� �� ������, ��� ��� ����� �����?";
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
		break;
		case "SharpPearl_2":
			dialog.text = "������� �� ����. ���� ��������� ���� �� ����������. ����, �� ����� ����� � �� ������� ��� � ��������. ���� ��� ������ �� ��� ��� ���������...";
			link.l1 = "����, ����, �������.";
			link.l1.go = "exit";
		break;
		//********************* ���������� ������� *********************
 		case "EngLine_quests":
            dialog.text = "����� �������� ��� ���. � �����, � � ���� ��� ������� ������������� � ����.";
			link.l1 = "� ��� �����.";
			link.l1.go = "exit";
			switch (pchar.questTemp.State)   // ������ � �������
            {
	     		case "go_talks_with_pirates":
	    			dialog.text = "������, ����� ����"+ GetSexPhrase("��","��") +"?";
	    			link.l1 = "� ����"+ GetSexPhrase("��","��") +" � ���� �� ��������� �������-����������� ������, ���� ������ ���������.";
	    			link.l1.go = "Step_1";
	      		break;
            }
		break;

 		case "Step_1":
			dialog.text = "��� ���������! �������� ���� �� ������, ��� �� ��� ��������� ������� �� ��� "+ GetSexPhrase("������","������ ��������") +"?";
			link.l1 = "�������� �������� ������� ��� ����� �������.";
			link.l1.go = "Step_2";
  		break;
  		
 		case "Step_2":
			dialog.text = "��� ����.";
			link.l1 = "������?";
			link.l1.go = "Step_3";
  		break;
  		
 		case "Step_3":
			dialog.text = "�������-���������� ������ ��������� �� ���, ����� ������, �� ����������. ������� ��� ����������� ������������� � ���� �������� � ���� ��������� ��������. ���-�� ����� �� ���.";
			link.l1 = "��������, �������� ������ ���� �� �������.";
			link.l1.go = "Step_4";
  		break;
  		
 		case "Step_4":
			dialog.text = "����� �� ������ ���������. ���, � �� ��� ����, ���-�� ����� �� ��. ��������, ��������� �������� ����, � ��� ���-�� �� ������� ��������� ������ ���� �������-����������� ������. ��� ��� ��� ����, � ����� ����, "+ GetSexPhrase("������","�������") +".";
			link.l1 = "�������. � ���� �����, ����.";
			link.l1.go = "exit";
			
            AddQuestRecord("Eng_Line_2_Talking", "5");
            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")   {pchar.questTemp.State = "after_talks_with_pirates";}
            NextDiag.TempNode = "First time";
  		break;

 		case "Lets_go_bussines":
			dialog.text = "���, ��� � �� �����. ��� ������ �������?";
			link.l1 = "� �������� � ���� � ��������. �� ����� � ������ ������?";
			link.l1.go = "Step_5";
  		break;

 		case "Step_5":
            if (GetCompanionQuantity(pchar) != 4)
            {
    			dialog.text = "� ����� ��������� ����������.";
    			link.l1 = "����� ������!";
    			link.l1.go = "Step_6";
            }
            else
            {
    			dialog.text = "� ����� �� ����� ������ �������. ���� ��� � � ����� � ����, �� ��� ������ �� ����� ������ ������ ���� �����. ��� ��� ��� ���� �� ���� ���.";
    			link.l1 = "�� ��� �, ��� ������, ���� ������.";
    			link.l1.go = "exit";
                NextDiag.TempNode = "First time";
            }
            
  		break;

 		case "Step_6":
			AddQuestRecord("Eng_Line_3_Morgan", "5");
            LAi_SetActorType(NPChar);
            LAi_ActorSetStayMode(NPChar);
            ChangeCharacterAddressGroup(NPChar, "PortSpein_houseF2", "goto", "goto3");
            CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 6, false);
            Fantom_SetBalls(npchar, "pirate");
            npchar.CompanionEnemyEnable = false;  // ��� ������ ��� ��������
            pchar.questTemp.CompanionQuantity = makeint(sti(pchar.questTemp.CompanionQuantity) + 1);
            pchar.questTemp.CompanionQuantity.Morris = true;
            NextDiag.TempNode = "Have_hot_bussines";
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

  		break;

	 	case "Have_hot_bussines":   // ���� ������� ����� ��������� ��� ����������, �� ����, ������ ��. �� �� ������ ������.
			dialog.text = "�� ������ ������������, ����� �� ����.";
			link.l1 = "�� ��� ������.";
			link.l1.go = "exit";
            NextDiag.TempNode = "Have_hot_bussines";
  		break;

	 	case "Gold_found_in_fort":    // ���� ��������� � ����� ������
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris") && !IsCompanion(characterFromID("John Morris")))
    		{
            	dialog.text = "���������, ��� ������ ����� �� ���! � ������� ������� � ������ �������� �������. ���� ������� ������..."+
                              " ��, ��� ����, ��� ���������� � ����� ����� ������������, � �������� ��� ����� ������ ������. �� ����� ������ � ���� ������� ��� �������, �������� ������ ���. �� - ��������� ������"+ GetSexPhrase("",", ���� � �������") +".";
            }
            else
            {
            	dialog.text = "����� ������ �� ��������, ���� ������! �� ����� ������ � ���� ������� ��� �������, �������� ������ ���. �� - ��������� ������"+ GetSexPhrase("",", ���� � �������") +".";
            }
			link.l1 = "�������. ���"+ GetSexPhrase("","�") +" ������� ��� �� ����.";
			link.l1.go = "Step_7";
        break;

	 	case "Step_7":
			dialog.text = "� ����� � ���� �� ��������. �� ������ ������� ����� ���� ���.";
			link.l1 = "����� ��������, ����. ��� ����������!";
			link.l1.go = "Step_8";
        break;
        
	 	case "Step_8":
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15.0);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
        break;

		//********************* ����������� ������� *********************
        case "FraLine8_talk":
            dialog.text = "��� �� ���"+ GetSexPhrase("��","��") +" � ��� ���� �����?";
            link.l1 = "� ������� " + GetFullName(pchar) + ". � ����� ��� ������. � ���� ��������� �������� ����� �� �������-����������� ���������...";
            link.l1.go = "Step_F8_1";
        break;
        case "Step_F8_1":
            dialog.text = "��� �� �����? ������ �����, �� ���� ��� ��� ��������!";
            link.l1 = "������, ����. ������ �� ���� ��������� - �������� ������� ��������� �� ���������� � ����� ���������� � ����� ���� ��������� ��������.";
            link.l1.go = "Step_F8_2";
        break;
        case "Step_F8_2":
            dialog.text = "�� � ���?";
            link.l1 = "��� �����, ����� �� �� ���������� � ���� ��������.";
            link.l1.go = "Step_F8_3";
        break;
        case "Step_F8_3":
            dialog.text = "���, ��� �� �������� ���� �������� �� ���������� � �, �������, ��������� �� ���� �����������. �� ���� �������� ���-��� ������� ��� ����.";
            link.l1 = "��� ������?";
            link.l1.go = "Step_F8_4";
        break;
        case "Step_F8_4":
            dialog.text = "�� ����, ������"+ GetSexPhrase("","�") +" �� �� � ���� ��������... ��, � �����, ���� � ���������: ����� ���������, ������� ���, ������� �������� �� ����, �� ��������, ��� ����, ��� �����, ������ �� ���� ���� ���������� ������, � ����� ������� �������, ������ ��� �� ����. � ����� ���� ��� � ������, � � ��������� ����� ���� �������� ���� �����������. � �����, � ���� ����� ��� ������� ������ ���.";
            link.l1 = "� ��� �� �����������?";
            link.l1.go = "Step_F8_5";
        break;
        case "Step_F8_5":
            dialog.text = "���������, ��� ��� ���� ������� ��� ��� ���������. ���� �������� �������� ���� �� ���������, ��, �������, ��������� � ���� �����. ��, � ���� �� ������� ��������� ���������, ������������, ��� �� � ������� ��� ���������, � ������� ���� �������� - ���� ������. ������ ������� ��� ����������������, ��� ��� � ����������� � ������� ��������� �� ����.";
            link.l1 = "��� �, ������ �� ������. ���������� ������ ��������, ������������� ����. ��� �������������� �������?";
            link.l1.go = "Step_F8_6";
        break;
        case "Step_F8_6":
            dialog.text = "�������� � ���������� �������� ���, ��� ����� ��� ������� ������.";
            link.l1 = "�� ��� ��, � ��� �����"+ GetSexPhrase("","�") +". ���� �����������, � �� ���� ������ �� ������������ �� ����� �����������.";
            link.l1.go = "Step_F8_7";
        break;
        case "Step_F8_7":
            dialog.text = "����������...";
            link.l1 = "�������������!";
            link.l1.go = "exit";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "6");
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex", GetSexPhrase("��","��"));
			NextDiag.TempNode = "Step_F8_Result";
			// ==> ��������� ����� ������� ���� ����� - ��� ��� ���.
			LocatorReloadEnterDisable("PortRoyal_tavern", "reload2_back", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_tavern_upstairs")], false);
            ref sld = GetCharacter(NPC_GenerateCharacter("CaptainGay", "bocman", "man", "man", 40, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 40, 100, 90, "blade34", "pistol5", 150);
            sld.Dialog.Filename    = "Quest\FraLineNpc_2.c";
        	sld.name 	= "�������";
        	sld.lastname 	= "���";
			sld.items.ShipsJournal = 1;
			sld.money = 65720;
			sld.items.potion4 = 4;
			sld.items.potionrum = 1;
			sld.items.potionwine = 2;
			sld.items.sculMa2 = 1;
			sld.items.jewelry17 = 30;
			sld.items.jewelry18 = 15;
			sld.SaveItemsForDead = true; // ��������� �� ����� ����
			sld.DontClearDead = true; // �� ������� ���� ����� 200�
			LAi_NoRebirthEnable(sld);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetStayType(sld); 
			ChangeCharacterAddressGroup(sld, "PortRoyal_tavern_upstairs", "goto", "goto1");
		break;
        case "Step_F8_Result":
            dialog.text = "��, ��� ������, �������? ��������"+ GetSexPhrase("","�") +" ������� ������ ����� �������� ���?";
			if (CheckCharacterItem(pchar, "ShipsJournal"))
			{
				link.l1 = "�������� ���, � ��� �������, ��� ������ �������. ��� ���������� � ��������. � ��� ������ - �����, ��� ��.";
				link.l1.go = "Step_F8_8";
			}
			else
			{
				link.l1 = "��� ���... �� � ������� ��� ����, ��� �����...";
				link.l1.go = "exit";
			}
        break;
        case "Step_F8_8":
            dialog.text = "���-���... ��, � �����������, ��� ���� ������ �� ���� ������� �������� ���� �������. �� ��� �, ��� �������� � ���������� � ��������� ������ ���������, � ������, ������ �� ���� ������������� �� �����. � �� ������ ��������� ���������� - �� � ������� �� �����!";
            link.l1 = "�������, ������. ��, � ������ ��� ����, ������...";
            link.l1.go = "exit";
			pchar.questTemp.Count = makeint(pchar.questTemp.Count)+1;
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "7");
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex", GetSexPhrase("","�"));
            TakeItemFromCharacter(pchar, "ShipsJournal");
        break;

		//********************* ��������� ������� *********************
		case "PL_Q8_deck":
			dialog.text = "� ��� �� ������� � ���� �� ������? ���� ���� �� ����� �����!";
			link.l1 = "��, � �����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;
		case "PL_Q8_deck_1":
			dialog.text = "���� �� ����� ������ �����, �� �� ������ ���.";
			link.l1 = "��, � ����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;


	}
}
