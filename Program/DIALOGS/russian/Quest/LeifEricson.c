// ��������� ��������� ����, 10 ���� � ���������.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- ������ ������ - ������ �������
		case "First time":
            if (pchar.questTemp.Ascold == "Ascold_MummyIsLive")
            {
            	dialog.text = "�� �������"+ GetSexPhrase("��","���") +" � ����� �������, ��� ������. � ������ ����� ���, ����� ������ ���?";
        		link.l1 = environment.date.year + "-�... ���� ������, ��� ����������?!!";
        		link.l1.go = "Step_8";
            }
            if (pchar.questTemp.Ascold == "Ascold_BodyChange")
            {
            	dialog.text = "�� ���, ������ ��� � �������. �� �����"+ GetSexPhrase("","�") +" ��������� ���� ��������������?";
        		link.l1 = "��� �� ��������?!! ������, ����, ���� ���� �������, ��� �� ��� ����� ������� ���������. ����� ����� ����� ������ ����� �����.";
        		link.l1.go = "Step_25";
            }
            if (pchar.questTemp.Ascold == "Ascold_SkelSlave")
            {
            	dialog.text = "������ �� �����"+ GetSexPhrase("","�") +". � �������� ���� �������� ��������.";
        		link.l1 = "� ��� ����� � ���� �����?";
        		link.l1.go = "Step_27";
            }
            if (pchar.questTemp.Ascold == "Ascold_ImMummy")
            {
            	dialog.text = "�������� ���� ������, �����.";
        		link.l1 = "������, ����.";
        		link.l1.go = "exit";
            }
            if (pchar.questTemp.Ascold == "Ascold_MummyFoundItems")
            {
            	dialog.text = "�-�-�, ��� � ��, �������! ��� ��������, �� �������� � ���� �������?";
                if  (CheckCharacterItem(pchar, "sculMa1") && CheckCharacterItem(pchar, "sculMa2") && CheckCharacterItem(pchar, "sculMa3") && CheckCharacterItem(pchar, "indian22"))
                {
                	link.l1 = "��� � ����. ������� � ����� ��� ��� ����!";
            		link.l1.go = "Step_29";
                }
                else
                {
                	link.l1 = "�� ��� � ����, � �� �� ���"+ GetSexPhrase("��","��") +"...";
            		link.l1.go = "Step_30";
                }
            }
            if (pchar.questTemp.Ascold == "Ascold_BackMyBody")
            {
            	dialog.text = "������ � ���������� ����. �� ������ ����, ����� ��������.";
        		link.l1 = "�������. �������, ������ �� ��������.";
        		link.l1.go = "Step_31";
            }
            if (pchar.questTemp.Ascold == "Ascold_ReturnToAscold")
            {
            	dialog.text = "������, �����...";
        		link.l1 = "������, ����.";
        		link.l1.go = "exit";
            }
		break;

 		case "Exit":
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Step_8":
        	dialog.text = "������ ���������� ��������� - �� � ����� �������������.\n"+
                          "� ��� ��������� ������� �������, ��������� ���� �� ���������� ����� �������� - � ������� ��� ���.";
    		link.l1 = "(��� ����) ���� ���� ���������! (�����) � ������, ��� � ���� ��������"+ GetSexPhrase("","�") +"...";
    		link.l1.go = "Step_9";
		break;

        case "Step_9":
        	dialog.text = "��� ���� ����� � ��� ��? �������, � ������ ����.";
    		link.l1 = "���� ����� " + GetFullName(pchar) + ". � - �����.";
    		link.l1.go = "Step_10";
    		link.l2 = "�� ������� �� ������� ��� ��� �������� ���������?";
    		link.l2.go = "ToDeath";
		break;

        case "ToDeath":
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
    		LAi_SetPlayerType(pchar);
		    LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_Cave")], false);
			LAi_SetFightMode(pchar, true);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Step_10":
        	dialog.text = "��� ������ '�����'?";
    		link.l1 = "����� - ��� ������... ����������, �����...";
    		link.l1.go = "Step_11";
		break;

        case "Step_11":
        	dialog.text = "��� ����� '����������', '�����'?";
    		link.l1 = "��, ��� ���� ���������... � �������"+ GetSexPhrase("�� ����� � ��������� ����","�� ������� � ������� �����") +". � ���� ���� ������� � � ����� ��, ��� ������ ������.";
    		link.l1.go = "Step_12";
		break;

        case "Step_12":
        	dialog.text = "��-��! �� �� � ����� "+ GetSexPhrase("������ �� �����","����� �����") +"! � ��������, ��� ��� ������� ����������� ����������� ����. ��� ���� ������� ����� ��� ����...";
    		link.l1 = "����� �������?";
    		link.l1.go = "Step_13";
		break;

        case "Step_13":
        	dialog.text = "����� �������? ��-��-��.... �� ����� � �������������� �� ����, � ���������, ������� ����� ����� �������� �����!\n"+
                          "� ���� � ����������� ��� �������. ������, ��� �������� �������� ���� �������...";
    		link.l1 = "���... ��� ��?";
    		link.l1.go = "Step_14";
		break;

        case "Step_14":
        	dialog.text = "���� ����� ���� �������. �, ��� �� ��� � ��, ����� � ����, ��� ���� ������.\n"+
                          "������ � �������� ���� �������� ����� �����.";
    		link.l1 = "����� � ���������"+ GetSexPhrase("��","���") +" ����, � ������"+ GetSexPhrase("","�") +", ��� ����� ��������� ���� ����������. ��� � ���� ��?";
    		link.l1.go = "Step_15";
		break;

        case "Step_15":
        	dialog.text = "��. � - ���� ����������, ��� ����� ������, ������� ������� �������, ������ � �������������.";
    		link.l1 = "��� �� ������, ���� �� ����� ��������, ��� �������� ������ �������� ��� �����?";
    		link.l1.go = "Step_16";
		break;

        case "Step_16":
        	dialog.text = "������ - ��� �� �����, ������. ������ - ��� ����� �����, ��������� ������ � �����.\n"+
                          "� ��, "+ GetSexPhrase("��������� ����","��������� �������") +", ��������� ��� ���������? �������� ��� ����� �� ���� ������� ������� � �������� �� �����. � ��� � ��������� � ���������� � ������ �� ���, � ��� ���� ������ ����������!";
    		link.l1 = "�� ��� �� �������� � �������? ������� �� ������ ��������� ������ 150 ��� �����!";
    		link.l1.go = "Step_17";
		break;

        case "Step_17":
        	dialog.text = "�������� �� ��������� ��� ������� �����? ��-��-��. ������ ����, "+ GetSexPhrase("��������� ������","�������-����") +".\n"+
                          "����� 986 ���� �� �� ���������� ������ ������ �����������, �������������� � ����������, ��� ������� � ����� ��������� �����, �� �� ������� � ���.\n"+
                          "� 1000 ���� �, ���� �������, ���������� �� ������ ���� �����. � ����� ������ ��������� (��������� �����), ����� �������� (��������) � ������� (������������). �� �������� � ������� ���������.\n"+
                          "����� ��� ���� � ���������� ������ � ����� ��� ������� �����. � ������� � ��� ������� ��������.";
    		link.l1 = "�� ����� ����! ��� ������� ���� ������� ��� ����� �������� �����...";
    		link.l1.go = "Step_18";
		break;

        case "Step_18":
        	dialog.text = "��� ����� ���� ������� ���� � 1002 ����.\n"+
                          "����� � ����� ������ ����� � ������, ��� ����� ��� ���������� � �������� ������������ ������.";
    		link.l1 = "�������...";
    		link.l1.go = "Step_19";
		break;

        case "Step_19":
        	dialog.text = "���, ������ ����� �������� ���� ��-�������.\n"+
                          "�������� ��� � ������ � ������� ���������, ������� �������� ����, ������ ��������, �� ��������. ����� �������� ��� � �������� � ���������� ���� ��������� �� �������� � ������� ��� ��������� ��������.\n"+
                          "����� �������� ��� ��� ���� ���������. ��������� �����.";
    		link.l1 = "�������! ��, � ���"+ GetSexPhrase("��","��") +"?";
    		link.l1.go = "Step_20";
		break;

        case "Step_20":
        	dialog.text = "�� ��������, ������� � ������ ���� ��������� ������� �� ���� ������������.";
    		link.l1 = "�-�-�, ��� ���� � �����. � ��� ��� �� �������?";
    		link.l1.go = "Step_21";
		break;

        case "Step_21":
        	dialog.text = "���� �����. � ���� �� ���� � �������� �������������.";
    		link.l1 = "�������... ��, � ���"+ GetSexPhrase("��","��") +"?";
    		link.l1.go = "Step_22";
		break;

        case "Step_22":
        	dialog.text = "�� ��������. �� ��� ������� �� ���-��� �������� ��� ����.";
    		link.l1 = "��, � ��� � ����"+ GetSexPhrase("��","��") +" �������?";
    		link.l1.go = "Step_23";
    		link.l2 = "����� � ���, ������ ��������! �������-�� ����� ���� �����...";
    		link.l2.go = "ToDeath";
		break;

        case "Step_23":
        	dialog.text = "� ��������, ��� ����� ����� ����� ������� �����. ���, � ������ �������� �������� � ������, ��������� ������ ��� ����, � ������ �� �����������.\n"+
                          "�� ����"+ GetSexPhrase("��","��") +" ��������� ��� ��� ����������� ������ ��������� - �����, ������� � �������, � ����� ������� �������, ��������� �������� �����. ����� � ����� ������� � ����� ������������ ���� ����. ��� ���� ������ ����������...";
    		link.l1 = "(��� ����) ��� �� ������ ��������� �� ����� ������, � �� ������� ���� � ������ �� ����, ��� ������... (�����) ������, � ���� ����?";
    		link.l1.go = "Step_24";
		break;

        case "Step_24":
        	dialog.text = "� �����, ��. ������ ��� ���� ��-�-�������� ������, ��� ����, ����� �� ��������� ���������"+ GetSexPhrase("��","���") +".\n"+
                          "�� ����� � ���� ���� ����, � ���� ��� ����. ���� �� �����.";
    		link.l1 = "���?!!!";
    		link.l1.go = "Body_Change";
		break;

        case "Body_Change":
			LAi_SetPlayerType(pchar);
            bDisableCharacterMenu = true; //��������� �2
            // ==> ������ ������
            Pchar.questTemp.Ascold.heroFaceId    = pchar.FaceId;
            Pchar.questTemp.Ascold.heroAnimation = pchar.model.animation;
			Pchar.questTemp.Ascold.reputation    = pchar.reputation;
			Pchar.questTemp.Ascold.nation		 = pchar.nation;
			Pchar.questTemp.Ascold.relation      = GetNationRelation2MainCharacter(FRANCE);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
            npchar.model = pchar.model;
			npchar.model.animation = pchar.model.animation;			
            FaceMaker(npchar);
            SetNewModelToChar(npchar);
            pchar.model = "Mummy";
            pchar.model.animation = "man";
            pchar.FaceId = 207; //�����
            FaceMaker(pchar);
            SetNewModelToChar(pchar);
            pchar.questTemp.Ascold = "Ascold_BodyChange";
    		LAi_SetCitizenType(npchar);
            
            //==> ������� ��������
			StoreOfficers_Ascold(pchar);  // �������� �������� �� ��������� ���������			
            for (i=1; i<=MAX_NUM_FIGHTERS; i++)
            {
                string officers = "Fellows.Passengers.Officers."+"id"+i;
                if(CheckAttribute(pchar, officers))
                {
                     RemoveOfficersIndex(pchar, sti(pchar.(officers)));						 
                }
            }
			 
            //<== ������� ��������
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Step_25":
        	dialog.text = "�� � ���?";
    		link.l1 = "� ��, ��� ����� �� ������� - �����������, � �� ���������, ������� � ������ ����������� ������. � � �� ���� ����������� �� ������������ ������ � ����� ����!";
    		link.l1.go = "Step_26";
		break;

        case "Step_26":
        	dialog.text = "����������� �� ����, ����� ����� ���������. � � ������ � ���� ��� ����� ����, �� ����� ����������, ����� ����� �����.";
    		link.l1 = "...";
    		link.l1.go = "exit";
            for (i=1; i<=6; i++)
            {
				sld = GetCharacter(NPC_GenerateCharacter("MySkel"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", 30, PIRATE, 0, true));	
				FantomMakeCoolFighter(sld, 20, 70, 70, "topor2", "pistol3", 50);  
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+(rand(2)+1));
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
            }
            pchar.questTemp.Ascold = "Ascold_SkelSlave";
		break;
		
        case "Step_27":
        	dialog.text = "�� ��� �� ��������, � ���� ��� ����� � �������. ���� ���� ��� �� �����, ��� ��� �� ��������.\n"+
                          "���, �� ������ ����.";
    		link.l1 = "������, ��� ��� � ������� ����. � �� ���� ���� ����� ���������.";
    		link.l1.go = "Step_28";
		break;

        case "Step_28":
            PChar.GenQuest.CrewSkelMode = true; //������� - ������� 
  		    chrDisableReloadToLocation = false; // ������� ����� �� �������.
            pchar.questTemp.Ascold = "Ascold_ImMummy";
            //==> ����� �������
            Pchar.location.from_sea.save = Pchar.location.from_sea;
            Pchar.location.from_sea = "none";
            Pchar.Ship.Crew.Quantity.save = Pchar.Ship.Crew.Quantity;
            Pchar.Ship.Crew.Quantity = 1000;
            Pchar.GenQuest.HunterScore2Pause = 1; //��� �� �����������
			Pchar.GenQuest.ReputationNotChange = 1; //��������� �� ������
            ChangeCharacterAddress(characterFromID("Ascold"), "None", "");
            //<== ����� �������
            Pchar.quest.Ascold_MummyFightTown.win_condition.l1 = "location";
            Pchar.quest.Ascold_MummyFightTown.win_condition.l1.location = "BasTer_ExitTown";
            Pchar.quest.Ascold_MummyFightTown.win_condition = "Ascold_MummyFightTown";

            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Step_29":
            DeleteAttribute(PChar, "GenQuest.CrewSkelMode"); // �������-������� � ���������� ����.
            bDisableCharacterMenu = false; //��������� �2
            bDisableLandEncounters = false;
            TakeItemFromCharacter(pchar, "sculMa1");
            TakeItemFromCharacter(pchar, "sculMa2");
            TakeItemFromCharacter(pchar, "sculMa3");
            TakeItemFromCharacter(pchar, "indian22");
            //==> �������
            Pchar.location.from_sea = Pchar.location.from_sea.save;
            DeleteAttribute(PChar, "location.from_sea.save");
            Pchar.Ship.Crew.Quantity = Pchar.Ship.Crew.Quantity.save;
            DeleteAttribute(PChar, "Ship.Crew.Quantity.save");

            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Ascold")], "BasTer_houseSp1", "goto", "goto1");
           	LAi_SetStayTypeNoGroup(characterFromID("Ascold"));
           	SetLocationCapturedState("BasTer_town", false);
            // ==> ���������� ������
            pchar.model = npchar.model;
            pchar.model.animation = Pchar.questTemp.Ascold.heroAnimation;
            pchar.FaceId          = Pchar.questTemp.Ascold.heroFaceId;
			pchar.reputation	  = Pchar.questTemp.Ascold.reputation;
			pchar.nation		  = Pchar.questTemp.Ascold.nation;
			SetNationRelation2MainCharacter(FRANCE, sti(Pchar.questTemp.Ascold.relation));
            FaceMaker(pchar);
            SetNewModelToChar(pchar);
            npchar.model = "Mummy";
			npchar.model.animation = "man";
            FaceMaker(npchar);
            SetNewModelToChar(npchar);
            DeleteAttribute(PChar, "questTemp.Ascold.heroFaceId");
            DeleteAttribute(PChar, "questTemp.Ascold.heroAnimation");
            DeleteAttribute(PChar, "questTemp.Ascold.reputation");
			DeleteAttribute(PChar, "questTemp.Ascold.relation");
			DeleteAttribute(PChar, "GenQuest.HunterScore2Pause"); //������� ���������� ���
			DeleteAttribute(PChar, "GenQuest.ReputationNotChange"); //������� ����� ����
            chrDisableReloadToLocation = true; // ������� ����� �� �������.
            pchar.questTemp.Ascold = "Ascold_BackMyBody";
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Step_30":
        	dialog.text = "���� �� �������, ������ ���� ������� �� ��������.";
    		link.l1 = "� ���� ������...";
    		link.l1.go = "exit";
		break;

        case "Step_31":
        	dialog.text = "��� � ����� ���������. ������ ��������� �������� � ���� ������ �� �������.";
    		link.l1 = "�����"+ GetSexPhrase("","�") +". ��, ���� ������, ���� ����� ��� �������...";
    		link.l1.go = "exit";
    		chrDisableReloadToLocation = false; // ������� ����� �� �������.
			bDisableFastReload = false; 
    		pchar.questTemp.Ascold = "Ascold_ReturnToAscold";
    		characters[GetCharacterIndex("Ascold")].dialog.currentnode = "AfterAttackMummy";
		break;
	}
}


