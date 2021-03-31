void ProcessDialogEvent()
{	
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iRank, iMassive;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{		
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = LinkRandPhrase("�������, ��� ������, ��� � ��� ���������!",
				"�������-�� ���� ���-�� �������� �����!!",
				"���� ���, ��� � ���� ��� ������!");
			Link.l1 = LinkRandPhrase("��� ���������, ������?",
				"����� ��������, ��������?",
				"�� ���� ��� �����������, ��� ������ ��� �������� ���������. ��������-�� ��� ����������, ��� ��� � ���� ���������?");
			Link.l1.go = "Step_1";			
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("��� ������� - ����� �����������, ��� ������� � ����������� �������!",
				"��� ������� ������� � ����������� �������, � ��� ��������� ����� �� ���!",
				"��� ������� ������� � ����������� �������!");
			Link.l1 = "������ ����� ��� ������� ����?!";
			Link.l1.go = "Step_2";			
		break;
		case "Step_2":
			dialog.text = "��, ��� ������ �� ������! ��� �������� ���-��, ��� ��� ����� ���� ����������, � ������� ����� �������� ������, ��� � �������. �� � �� ����� ����, � ���� �� �����...";
			Link.l1 = "� ��� ���������, ������ ���� ��� ������.";
			Link.l1.go = "Step_3";			
		break;		
		case "Step_3":
			dialog.text = "��� �� ��� ������ ������? ����� ���, ���� ����� �������, �������� ��!";
			Link.l1 = "������, � ��������� � ����. � �� ��� �����, ������ ��� ������������� �����.";
			Link.l1.go = "Step_agree";
			Link.l2 = "��� ���� ��������, ��� �� ��� ���� ���. ������...";
			Link.l2.go = "Step_disAgree";
		break;

		case "Step_agree":
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			if (rand(1))
			{ //���������
				LAi_LocationDisableMonGenTimer(pchar.GenQuest.EncGirl.locationId, 1); //�������� �� �������� 1 ����
				LAi_LocationDisableOffGenTimer(pchar.GenQuest.EncGirl.locationId, 1); //�������� �� ������� 1 ����
				LocatorReloadEnterDisable(pchar.GenQuest.EncGirl.locationId, "reload2", true);
				pchar.GenQuest.OpenTheRopeExit = pchar.GenQuest.EncGirl.locationId; //���� ��� �������� �������
				string model[10];
				model[0] = "pirate_1";
				model[1] = "pirate_2";
				model[2] = "pirate_3";
				model[3] = "pirate_4";
				model[4] = "pirate_5";
				model[5] = "pirate_6";
				model[6] = "pirate_7";
				model[7] = "pirate_8";
				model[8] = "pirate_9";
				model[9] = "pirate_10";
				i = 0;
				while(i < 3)
				{
					iMassive = rand(9);
					if (model[iMassive] != "")
					{
						iRank = sti(pchar.rank) - rand(5) + rand(5);
						if (iRank < 1) iRank = 1; 
						sld = GetCharacter(NPC_GenerateCharacter("CaveGandMan" + i, model[iMassive], "man", "man", iRank, PIRATE, 1, true));
						SetFantomParamFromRank(sld, iRank, true);
						sld.SaveItemsForDead = true;
						sld.DontClearDead = true; 
						sld.money = iRank*200+1000+rand(500);
						LAi_SetWarriorType(sld);
						LAi_warrior_SetStay(sld, true);
						//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
						LAi_group_MoveCharacter(sld, LAI_GROUP_ENEMY);// ������ ������� ������ ����� ���� ����� ������� ����� ����
						LAi_group_Attack(sld, Pchar);// ������ ������� ����� �� ����� � �� � ��������� ��� ��� ��� �� ��������.
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirl.locationId, "quest", "quest" + i);
						i++;
						model[iMassive] = "";	
					}
				}
				pchar.quest.Enc_FriendGirl_afterGang.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Enc_FriendGirl_afterGang.win_condition.l1.location = pchar.location;
				pchar.quest.Enc_FriendGirl_afterGang.win_condition = "Enc_FriendGirl_afterGang";
			}
			else
			{ //� ������ ����� 
				sld = GetCharacter(NPC_GenerateCharacter("UndergroundGirl", "girl_"+(rand(7)+1), "woman", "towngirl", 5, PIRATE, 1, false));
				sld.dialog.filename = "Enc_FriendGirl_dialog.c";
				int iTemp = rand(1);
				sld.dialog.currentnode = "Underground1";//+ iTemp; //����� ������ ��������� �����: 0-��������, 1-���� ������
				sld.greeting = "Enc_RapersGirl_" + (iTemp+1); //�����. �������
				LAi_SetStayType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirl.locationId, "monsters", "monster"+(rand(9)+1));
			}
			LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_disAgree":
			ChangeCharacterReputation(pchar, -3);
			LAi_SetCitizenTypeNoGroup(npchar);
			//#20200315-01
            npchar.chr_ai.type.checkFight = 999999.0;
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			NextDiag.CurrentNode = "FackYou";
			DeleteAttribute(pchar, "GenQuest.EncGirl"); 
			DialogExit();
		break;			
		//#20200315-01
		case "CitizenNotBlade ":
		    npchar.chr_ai.type.checkFight = 999999.0;
            NextDiag.TempNode = "FackYou";
            dialog.text = "�� ���� ������������� � "+ GetSexPhrase("����� ��������� ��������","����� ��������� ������") +". ���������� ������!";
			Link.l1 = "���, ������...";
			Link.l1.go = "exit";
		break;
		case "FackYou":
            NextDiag.TempNode = "FackYou";
            dialog.text = "�� ���� ������������� � "+ GetSexPhrase("����� ��������� ��������","����� ��������� ������") +". ���������� ������!";
			Link.l1 = "���, ������...";
			Link.l1.go = "exit";
		break;

		case "Underground0": //����� ������� �����������
            dialog.text = "���� ���, ��� � ���� ��� ������!!";
			Link.l1 = "��� ���������, ���������?";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = "� ����������� �����! �������, ��� �� ��� ���� �������!!!";
			Link.l1 = "��, ������-�� ��� � �������. ��� �� ����, � ������ ����. ��� ��������� �� ����������� - ������ �����, � ����� ������ � ���� �� "+ GetSexPhrase("�����","������") +"!";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = "��� �������, " + GetAddress_Form(NPChar) + ".";
			Link.l1 = "������.";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterReputation(pchar, 4);
			DeleteAttribute(pchar, "GenQuest.EncGirl"); 
		break;

		case "Underground1": //������ �������
            dialog.text = "���� ��, ��� ����-�� ���� ���� �� ����� ����������!";
			Link.l1 = "���������, �� ��� ��� �������?";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = "�� ���� ����!";
			Link.l1 = "���, ����� �� ������� ��������...";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = "�� ��� ��������... "+ GetSexPhrase("���","���") +" �� �� ������ ����� �������, �� ���� ��� ���� ���.";
			Link.l1 = "���, � ��� �� ���� ����, ����������, �� ��� ������ ������� ���� ������ ������� �������...";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = "��� ���� ������! ���� �� ������ ���������� ������, � ������, ��� � ����� ��.";
			Link.l1 = "�� ��, �� ���� �� ����� ��. ���� � ����!";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = "������� � ���������! �� � ������, ���������� � ���� � ������.";
			Link.l1 = "�� �����, ��� ���� ��� ������ �� �����...";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = "�� �����!";
			Link.l1 = "����� ������ � ���� �������.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
			DeleteAttribute(pchar, "GenQuest.EncGirl"); 
		break;
		case "Underground1_again": 
            dialog.text = "����� ��? ����������, ������"+ GetSexPhrase("","�") +" ���...";
			Link.l1 = "��...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}
