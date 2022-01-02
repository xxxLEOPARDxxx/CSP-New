// ������� �� ��������
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================================================================
// ============================= ���� angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //������� ������� ������������
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //���� ����������� ������� �����. � npchar.angry.name ������� �������!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
					if (npchar.angry.name == "BlueBird_1") Dialog.CurrentNode = "AngryRepeat_1";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= ���� angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- ������ ������ - ������ �������
		case "First time":
            dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("� ���� ���� �� ���? ���? ����� ���� ������!","��, " + pchar.name + "! � ���� ���� �� ���? ���? ����� �� �������� ����.") +"",
                         "� ������� ���� ���������.", "���� � ��������� � ����, �� �� ����������� ��������� ����!",
                         "��-�-��, ��� ��� ������ �� ��������, ���� ��� �������.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� �����.",
                                               "�������, �������...",
                                               "������, �������...",
                                               "��...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			//������ ������ ����� �����
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = "������, �������, ��� ����� ����... � �����, �� �������� �� � ���� � ����� ������ '����� �����'?";
				link.l1.go = "BlueBird_1";
			}
			if (pchar.questTemp.BlueBird == "weWon")
			{
				link.l1 = "�������������, � ���� �������"+ GetSexPhrase("","�") +" ��� ������ '����� �����'!";
				link.l1.go = "BlueBird_6";
			}
			//��������� ������� ������
			if (pchar.questTemp.piratesLine == "begin" && !CheckAttribute(pchar, "QuestTemp.AndreAbelQuest"))
			{
				link.l1 = "�������, � ��� ������ ��� �����-������...";
				link.l1.go = "PL_Q1_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toJackman")
			{
				link.l1 = "� ��� ������ ����� ������� ���, ������� ������, ��� �� � ����.";
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toTavernAgain")
			{				
				dialog.text = ""+ GetSexPhrase("��� ����?! � �� � ���������� �������� �� ���� �������!","��� ����, " + pchar.name + "? � ������ ����� �����...") +"";
				link.l1 = "�������, � ��� � ����� ���� ����� ���� - ������ ���.";
				link.l1.go = "PL_Q3_2";
			}
			if (CheckAttribute(pchar,"questTemp.piratesLine.T1") && pchar.questTemp.piratesLine.T1 == "KillLoy_GoodWork" && !CheckAttribute(npchar, "quest.PQ3"))
			{
				dialog.text = "������"+ GetSexPhrase("��","���") +"! �� �� � ������� ������!";
				link.l1 = "�����"+ GetSexPhrase("","�") +" ��������, ��� ������ ��� ���� � ������ � ������ � ����� ������ � ����.";
				link.l1.go = "PL_SEAWOLF";				
			}
			if (pchar.questTemp.piratesLine == "Panama_backToShip")
			{
				dialog.text = "�, ��� ���� ������, " + pchar.name + ". ��, ��� �������?";
				link.l1 = "�� ������ � ���, ��� ������ ������ � ������?";
				link.l1.go = "PL_Q8";				
			}
			//��������� ��������� �����
			if (pchar.questTemp.Sharp == "begin")
			{
				link.l1 = "��������, ����� ����� � �������� ������ ������� � ��������� ����. �� ������ �� ������ �� ����?";
				link.l1.go = "SharpPearl_1";
			}
			//������ �����-�������
			if (CheckAttribute(pchar, "questTemp.mushket2x2") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l2 = "������, �������, ���� �� � ��� �� ������� ����� '������'? ����� ����, ������ �� ����� ������ ��� ������, ��� ����� ��������� ��� ����������?";
				link.l2.go = "Mushket";
			}
			//��������� �������� - �����
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "� �� ������ ������ ��������.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "���������� �������, � �� ������ ������ ���������.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "� �� ������ ������ ��������.";
					link.l1.go = "CapComission6";
				}
			}
			if(sti(pchar.rank) >= 10 && !CheckAttribute(PChar, "questTemp.pirateVikingQuest"))
			{
				link.l3 = "���� �����-������ ���������� ���� ��� ����?";
				link.l3.go = "pirateVikingQuest";
			}
			else
			{
				if(CheckAttribute(PChar, "questTemp.pirateVikingQuest") && pchar.questTemp.pirateVikingQuest == "7" && npchar.city == pchar.questTemp.pirateVikingQuest.City)
				{
					dialog.text = "���� �� � ���������?"
					link.l1 = "��, �������"+ GetSexPhrase("","�") +" ���� ����������, �� � ����� �� ���. ������ ��� ��������� ������� ��� ������ ������, � ���� ����� ������ �� ���� ��� ��� ���.";
					link.l1.go = "pirateVikingQuest_final";
				}
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		//Blackthorn. ����� �������
		case "pirateVikingQuest":
			dialog.text = "��� ���� ������� ��������. �� �� ������ ������ "+ GetSexPhrase("����","�����") +", �� � ����, ��� ��� ������������. ������ ����. �������� ���� ��� ����� � ����� ����� ��������� ����� ��, �� �� ��������, �� �� ����, �������, �������� ��������. ������� � ���� ������ ���������� � ������� ���������� �� �������� �������. � ����� ���, �� ������, ����������� ����������, ����� �� ���� ������������, ��� ������ ���� � ����� ���� �� ������, ������������ ������, ����� ������ ���������� ��� �������. �������� � ���� ��������?";
			link.l1 = "������, �������� ��� �����, ��� ���� �������� ����. ��� ������ ��� �� �� ������� ���������� �������� ��� ��. ��, �������� �����, ��� ����� ������ ��� ������� ��� �� �������. � � ���, ������� �������� ������� ���������, ����� �� ���������.";
			link.l1.go = "pirateVikingQuest_1";
			link.l2 = "���-�� �� �������� ��� ���� ��������. ������...";
			link.l2.go = "exit";
			pchar.questTemp.pirateVikingQuest = "0";
		break;
		case "pirateVikingQuest_1":
			dialog.text = "������ ��������, ������, ��������� ������ ��� ������� ������� ���. �� ��� ���������� �������, ������� ���� ��������� �������. ��-��! ��� � ��� ������ ��� ����������, ������ ��������� ����� �� ���� �������, ���� �� �� �������� �� ������. � ����� � ������ ��� ��������? ��� � ������� �������, � ��� ������ ������ � ���� ��� ������������� ������. � ��������� ����������� �������. ��� � ����� ������. � ����� ��������, ��� ���� ������, ��������� ��� ���� ������. ��������?";
			link.l1 = "�����"+ GetSexPhrase("","�") +", ��� �� ��� ���� ��� �����������. ��� ������ ����� �������?";
			link.l1.go = "pirateVikingQuest_2";
		break;
		case "pirateVikingQuest_2":
			dialog.text = "��� ��. ���� �� ��� �������, ��� �� � ���� �����, �� ��������� �� �� ������ ���� � �������. �� � ��� ���������"+ GetSexPhrase("��","��") +", ����������. ���� ������� � ������ ���� � ��� ��� ������� �� ���� ����� ����� ������, � ���������� � �� �����.";
			link.l1 = "��� ��������. �� � ��� ����� ��������, ���� ������� �����, ��� �����. �����, "+GetFullName(npchar)+".";
			link.l1.go = "exit";
			
			pchar.questTemp.pirateVikingQuest = "1";
			pchar.questTemp.pirateVikingQuest.City = npchar.city;
			pchar.questTemp.pirateVikingQuest.Areal = GetArealByCityName(pchar.questTemp.pirateVikingQuest.City);
			pchar.questTemp.pirateVikingQuest.Name = GetFullName(npchar);
			pchar.LastHearedViking = npchar.city;
			AddQuestRecord("pirateVikingQuest", "1");
			AddQuestUserData("pirateVikingQuest", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateVikingQuest.City + "Gen"));
			AddQuestUserData("pirateVikingQuest", "sName", pchar.questTemp.pirateVikingQuest.Name);
		break;
		case "pirateVikingQuest_final":
			CloseQuestHeader("pirateVikingQuest");
			TakeNItems(pchar, "chest", 5);
			Log_Info("�� �������� ��������� �������");
			dialog.text = "���, ����� ��� ��. ������� ������. ����� ������� ��������. ���, ����� �������, ��������"+ GetSexPhrase("","�") +".";
			pchar.questTemp.pirateVikingQuest = "end";
			link.l1 = "�������.";
			link.l1.go = "exit";
		break;
		
        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", ��� ���� ������! ����� ���������"+ GetSexPhrase("","�") +" �� ���� ���?",
                         "�� ��� ���� ���?", "����� ��� ����� ������������? ���� ���� ������ ������, �� �������� ������!",
                         "�� "+ GetSexPhrase("������� �����","������� �������") +", ������� ���� ����. �� �������� � ������������� � ����� � ������ �� �����.", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��, ����������, ������ ��� ��������"+ GetSexPhrase("","�") +", ���������. ������ �� ���� ���.",
                                               "������, ������ ���...",
                                               "������, �������, ������...",
                                               "��� ���� ������, �������"+ GetSexPhrase("��","���") +"!!!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			//������ ������ ����� �����
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = "������, �������, ��� ����� ����... � �����, �� �������� �� � ���� � ����� ������ '����� �����'?";
				link.l1.go = "BlueBird_1";
			}
			if (pchar.questTemp.BlueBird == "weWon")
			{
				link.l1 = "�������������, � ���� �������"+ GetSexPhrase("","�") +" ��� ������ '����� �����'!";
				link.l1.go = "BlueBird_6";
			}
			if (pchar.questTemp.Sharp == "begin" && rand(1))
			{
				link.l1 = "��������, ����� ����� � �������� ������ ������� � ��������� ����. �� ������ �� ������ �� ����?";
				link.l1.go = "SharpPearl_1";
			}
			//��������� ������� ������
			if (pchar.questTemp.piratesLine == "KillLoy_toJackman")
			{
				link.l1 = "� ��� ������ ����� ������� ���, ������� ������, ��� �� � ����.";
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toTavernAgain")
			{				
				dialog.text = ""+ GetSexPhrase("��� ����?! � �� � ���������� �������� �� ���� �������!","��� ����, " + pchar.name + "? � ����� �����...") +"";
				link.l1 = "�������, � ��� ���� � ����� ����� ����. ������ ���.";
				link.l1.go = "PL_Q3_2";
			}
			if (CheckAttribute(pchar,"pchar.questTemp.piratesLine.T1") && pchar.questTemp.piratesLine.T1 == "KillLoy_GoodWork" && !CheckAttribute(npchar, "quest.PQ3"))
			{
				dialog.text = "������"+ GetSexPhrase("��","���") +"! �� �� � ������� ������!";
				link.l1 = "�����"+ GetSexPhrase("","�") +" ��������, ��� ������ ��� ���� � ������ � ������ � ����� ������ � ����.";
				link.l1.go = "PL_SEAWOLF";				
			}
			if (pchar.questTemp.piratesLine == "Panama_backToShip")
			{
				dialog.text = "�, ��� ���� ������, " + pchar.name + ". ��, ��� �������?";
				link.l1 = "�� ������ � ���, ��� ������ ������ � ������?";
				link.l1.go = "PL_Q8";				
			}
			//������ �����-�������
			if (CheckAttribute(pchar, "questTemp.mushket2x2") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = "������, �������, ���� �� � ��� �� ������� ����� '������'? ����� ����, ������ �� ����� ������ ��� ������, ��� ����� ��������� ��� ����������?";
				link.l1.go = "Mushket";
			}
			//��������� �������� - �����
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "� �� ������ ������ ��������.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}
			if(sti(pchar.rank) >= 10 && !CheckAttribute(PChar, "questTemp.pirateVikingQuest"))
			{
				link.l3 = "���� �����-������ ���������� ���� ��� ����?";
				link.l3.go = "pirateVikingQuest";
			}
			else
			{
				if(CheckAttribute(PChar, "questTemp.pirateVikingQuest") && pchar.questTemp.pirateVikingQuest == "7" && npchar.city == pchar.questTemp.pirateVikingQuest.City)
				{
					dialog.text = "���� �� � ���������?"
					link.l1 = "��, �������"+ GetSexPhrase("","�") +" ���� ����������, �� � ����� �� ���. ������ ��� ��������� ������� ��� ������ ������, � ���� ����� ������ �� ���� ��� ��� ���.";
					link.l1.go = "pirateVikingQuest_final";
				}
			}			
		break;
		//********************* �������, ����������� �� ����� �1 *********************
		case "PL_Q1_1":
			if(CheckAttribute(NPChar, "notQuestLine")) 
			{
				dialog.text = "������������, ��� �� � ���������� ������� � ������� ������. ������� ��������� ������ �������� ��������� �����?! �� ����� � � ����� ������������, ������� ����� ���� ��������� �� �������� � ���������� ����� ������. �� �����...";
				link.l1 = "����... �� �, ����������, ������ ��� �������"+ GetSexPhrase("","�") +". �� ������ ������...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "� ���� ������ ���. �� ���� �� ����� �� �����"+ GetSexPhrase("","�") +", �� ����������� � ������-�������� -  ����� ��� �������� �����. � ���� ������ ������ ���-�� ����.";
				link.l1 = "� ��� �� ������ � ���� ������?";
				link.l1.go = "PL_Q1_2";
				//LockQuestLine(characterFromId("eng_guber")); // ����� ���������� �������
			}	
		break;
		case "PL_Q1_2":
			dialog.text = "�� ����� ���. ���"+ GetSexPhrase("","�") +" � ���� ��������.";
			link.l1 = "�������...";
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "toFirstQuest";
			AddQuestRecord("Pir_Line_0_Waiting", "2");
		break;
		//********************* �������, ����� �3, ������ ��� *********************
		case "PL_Q3_1":
			dialog.text = "�����?! ��! �� ������ ���"+ GetSexPhrase("��, ��������","��") +", . ��, ������! � �� ���� �"+ GetSexPhrase("��","�") +"!!!";
			link.l1 = "�� �����"+ GetSexPhrase("","�") +"!..";
			link.l1.go = "PL_Q3_fight";
		break;
		case "PL_Q3_fight":
			LAi_LocationFightDisable(&Locations[FindLocation("Pirates_townhall")], false);
			chrDisableReloadToLocation = true; // ������� ����� �� �������.
            for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("QuestPir_"+i, "pirate_"+i, "man", "man", 100, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 100, 100, 100, "topor2", "pistol3", 100);
            	LAi_SetWarriorType(sld);
				LAi_SetImmortal(sld, true);
            	sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
                LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
               	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
            }
            LAi_group_SetLookRadius("PIRATE_CITIZENS", 100);
            LAi_group_SetRelation("PIRATE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("PIRATE_CITIZENS", LAI_GROUP_PLAYER, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "PL_Q3_2":
			dialog.text = "���?! ����� � ���� ���� � ���?";
			link.l1 = "� ���� ��� ��� � ���. �� ���-�� ������� �������, � ��� �������� ���� �������� �������. ������ ���������, ����� � ��� ���?";
			link.l1.go = "PL_Q3_3";	
		break;
		case "PL_Q3_3":
			dialog.text = "��. �� � ������� ����� ���������? ������ �������, ��� � ���� ������ ���������. �� ���� ���������� ����� ��� ����!";
			link.l1 = "��, � ����, ������ �� ����� ��� �� ���������.";
			link.l1.go = "PL_Q3_4";
		break;
		case "PL_Q3_4":
			dialog.text = "�� ��, ��� ��� ����! � ���� ��� ����� �������� �����������! ��� � ���� ����������, ��� � ��� ������ ���� ������! �� �� ���� ���������� �� ��� ������ ���� � ��� ������ ��������! � �� ���������� �� ��������� ����! ������� ������� ��������, �� ��, ��� ���� ���������.\n����� ��� ������� ���������� ����� ������������ �� �����, � ��� ��� � ������: �� �������� '������� ����' - ����� ������ ����� � ������ � ��� �������! ���� ����� ����� ����.";;
			link.l1 = "�� ���� �� ����� �������� ������, ������ ���������� ������...";
			link.l1.go = "PL_Q3_5";
		break;
		case "PL_Q3_5":
			dialog.text = "�� ��� � ���, �������. �� ���� � ��� �������, ����� � ������� ��� ������ ��������� �� ��������������. �� � ������ � ������ ������, ��� � ���� ������ �������! � ������� ����� �������� ��������, ����� � ��������� ��� �����.\n" +
				"������, ��������, ����� ������� ��� ������. ��� �� �����"+ GetSexPhrase("","�") +", � ���� ����� �����. � ����, ���� ��� ����, �� ��� �������... ����� �� ���� - �� �������� ������������ �� ������! � ���� ��� ��� �����! ���!!! ������� ���� ���� ���������, ����� ��� �����, ��� ������ � ���� ������ �� ����, �� �� �������, � �� ����! � ����� �� ���� ���������.";
			link.l1 = "������, ����� ������� �� ��� �������. �������, ������ ��� �� ���� ������.";
			link.l1.go = "PL_Q3_6";
		break;
		case "PL_Q3_6":
			dialog.text = "�����?";
			link.l1 = "������ �� ��� � ������� ���������? �� �� ����� ������.";
			link.l1.go = "PL_Q3_7";
		break;
		case "PL_Q3_7":
			dialog.text = "��, ������... ��� � ������, ���� �������... ��������� ��������, ����������� �����, ���������, �������, �����!  �������� �����, ������? ����� �� ��� � ������, ��������� ���� ���� ����� ���, ��� ��������� ����� ����� �����... � �� �������� ����� ��� ���������.\n" +
				"�� ���� ��� ������, ���-�� �� ��� ������ �����, �� ������� ������������, ���-�� ������� � ����� �����, ���-�� ����������� �������, �� ��������� ����� ���. � ���-��, ��� ����� ������, ��� ������, � ���� ���� �������������, � ����� ��� �� ����� �����, ������� �� ������. ��, � ������, �� �� ��������� � ��� �... ������"+ GetSexPhrase("","�") +", ��������, ���������: '������� �������� ����'? ��� ���, ��� �� - ������ ����...\n"+"���� ������� ������ ������� �������, ��� ����-��������. �� ���� ����� �����, �������� ������ �������� ����� ������ ������ � ������� �����. ��� ����� ��� �����������, �� ����... ����, ����� �� ��������! ������ ��� ������ ���� ����� ����� ������ �������� � ������� �������... ��� ����� ���������.";
			link.l1 = "���-��, ����� �� � �� ���������"+ GetSexPhrase("","�") +". ��������, �����... ��� ������� - ��� � ����. � ���"+ GetSexPhrase("","�") +" � �������� ���"+ GetSexPhrase("���","�����") +"-���������. � ����� � ������ ������, ��� ����, ���� "+ GetSexPhrase("������� ���� ������, ����� ��� ������","���� ������ ��, ��� ���� ����") +".";
			link.l1.go = "PL_Q3_8";
		break;
		case "PL_Q3_8":
			dialog.text = "��-��-��, �� ����, ���"+ GetSexPhrase("�","����") +"-��������! � ����������� � �������!";
			link.l1 = "���, ����� ����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Pir_Line_3_KillLoy", "12");
			pchar.questTemp.piratesLine = "KillLoy_2toTavernAgain";
		break;
		//����� ������� ���
		case "PL_SEAWOLF":
			NextDiag.TempNode = "I_know_you_good";
			npchar.quest.PQ3 = true;
			int chComp;
			bool bOk = false;
			for (int i=0; i<=COMPANION_MAX; i++)
        	{
				chComp = GetCompanionIndex(pchar, i);
                if(chComp != -1 && RealShips[sti(characters[chComp].ship.type)].Name == "BrigSW1")
        		{	
					bOk = true;
					break;
				}
			}
			if (bOk)
			{
				dialog.text = "������ ���� ���� � � ����. ����, ��� ��� � ��� ���� �����"+ GetSexPhrase("","�") +" ����������! �������. �� �������"+ GetSexPhrase("","�") +", ��� �� � ���"+ GetSexPhrase("�","����") +"! ������� � ������ ������� ����� ���� '�������� �����', ������ �� �����! ����� �� � ����� "+ GetSexPhrase("������ �����","����� ����� ������") +", ��� ��, � ����� �������!";
				link.l1 = "� - ��������� �������, �������. �� ���� ����� - ����� ��� ����!";
				link.l1.go = "exit";
				AddQuestRecord("Pir_Line_3_KillLoy", "19");	
			}
			else
			{
				dialog.text = "������ ���� ���� � � ����. �� ��� ��, ������� ����, "+ GetSexPhrase("��������","�������") +". � ������� �� ����� ��� ���� 20 ����� ��������!";
				link.l1 = "�������, �������! ��� ������ ��� ����������.";
				link.l1.go = "exit";
				AddMoneyToCharacter(pchar, 20000);
				AddQuestRecord("Pir_Line_3_KillLoy", "20");	
				AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("","�"));	
			}
		break;
		//********************* �������, ����� �6. ������� *********************
		case "PL_Q6":
			dialog.text = "�-�-�, ���� � ����?! ������ �� ����!";
			link.l1 = "������ ������ � ���� �������, ��� ������� ����� �����.";
			link.l1.go = "PL_Q6_1";
		break;
		case "PL_Q6_1":
			dialog.text = "��� ���, ������... ������� �� �� ��������... � ��� ��� ���������?";
			link.l1 = "� ����"+ GetSexPhrase("","�") +" ��� � ���������� �������... ���������, ��� ������� ����� ����������. � �� ��� ��������� �����"+ GetSexPhrase("","�") +" ����� ������, � ���������, ��� ��� ���������� ���� �������.";
			link.l1.go = "PL_Q6_2";
		break;
		case "PL_Q6_2":
			dialog.text = "������ ���, ���� �����?";
			link.l1 = "���... � �����, � ����� ����� �� ����� ������ � ������� ��������� ��������, ��� ��� �� ������� ���� �� ������. ������, ��� ����� �������������� ���-��� �������, � ��� �� �������� ����������, ��� � �� �������.";
			link.l1.go = "PL_Q6_3";
		break;
		case "PL_Q6_3":
			dialog.text = "��, �� ����! � �� �� � �����, ��� �� ��� ��������"+ GetSexPhrase("","�") +" ���� ������� - ������ �� ���� �����, � ����"+ GetSexPhrase("","�") +" ��� ��������?";
			link.l1 = "�?!!";
			link.l1.go = "PL_Q6_4";
		break;
		case "PL_Q6_4":
			dialog.text = "��, ������ ����� ����� �����. ������� � ������ ������ �� ����, ��� ������ ���� �����.";
			link.l1 = "������!! ����� ��� �� �������!";
			link.l1.go = "PL_Q6_5";
		break;
		case "PL_Q6_5":
			dialog.text = "����������� � ������ ��������, ��� �������� ������. ��� � ����� �� ������� '���������' ����� ���� ����, � ���� ��� �������� � ��������. ��� �������, ���� ����� ����� ��������� ��� ���������...";
			link.l1 = "������, �������, ��� � ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "2");
			AddQuestUserData("Pir_Line_6_Jackman", "sSex", GetSexPhrase("","�"));
			pchar.questTemp.piratesLine = "PL6Brother_toSantaCatalina";
			//������ ����� ����� � ����� ��������
			sld = GetCharacter(NPC_GenerateCharacter("JohnLids", "officer_10", "man", "man", 30, sti(pchar.nation), -1, true));	
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, "���������", CANNON_TYPE_CULVERINE_LBS24, 80, 60, 60);
			sld.name = "����";
			sld.lastname = "����";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "First time";	        
			sld.DeckDialogNode = "JohnLids";		
			sld.Abordage.Enable = false;
			sld.AnalizeShips = true; 
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable = true;
			sld.Ship.Mode = "Pirate";
			sld.greeting = "Gr_MiddPirate";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			Group_AddCharacter("LidsGroup", "JohnLids");
			Group_SetGroupCommander("LidsGroup", "JohnLids");			
			Group_SetAddress("LidsGroup", "Beliz", "quest_ships", "Quest_ship_11");
			Group_SetTaskNone("LidsGroup");
		break;

		case "PL_Q6_after":
			dialog.text = "���� ��� ��������� ��� � ����� �������� � "+ GetSexPhrase("���������","'��c�������'") +". ���� ������� ������ ���-������ ����������?";
			link.l1 = "���������� �������, �� � ������. ��"+ GetSexPhrase("","�") +" ������� �������"+ GetSexPhrase("��","���") +", ������, ����"+ GetSexPhrase("��","���") +" ��������� ���-�� ������.";
			link.l1.go = "PL_Q6_after_1";
		break;
		case "PL_Q6_after_1":
			dialog.text = "��� �����. �� ����� ����� �����-�� �������, �������� �������. ���� ����� �� ����� �������, �� ����� ���� ���������� - � ����� �����! ������ ���� �� �������.";
			link.l1 = "� �������. "+ GetSexPhrase("�������","'���������'") +" ���� ���-�� ����"+ GetSexPhrase("","�") +"... ���� �������� ��������, ��� �� ���� ���� �����.";
			link.l1.go = "PL_Q6_after_2";
		break;
		case "PL_Q6_after_2":
			dialog.text = "�����. �� ��� ��, ������, ��� �� �� ��� ��������"+ GetSexPhrase("","�") +", ��������� ��������� ������ ������, ��� �������. ������ ����������� � �������, ������� ��� � ����"+ GetSexPhrase("� ��������","� '���������'") +".";
			link.l1 = "��, ���� �� �������... �����, �������, � ��� �� �������, ����� �������, ��� � ����"+ GetSexPhrase("","�") +" �������� ���� �������?";
			link.l1.go = "PL_Q6_after_3";
		break;
		case "PL_Q6_after_3":
			dialog.text = "��, � ��� ����� ���� ����� �� �����... ���� ������ �������, ��� ���� ����� "+ GetSexPhrase("��������","'���������'") +" � ������, � "+ GetSexPhrase("��� �������","�� �����") +", ��� ����"+ GetSexPhrase("","�") +" �������, �� ���"+ GetSexPhrase("","��") +" ��������� ����� ��� �����, ��� ������"+ GetSexPhrase("��","���") +" ��.";
			link.l1 = "�������. ������ ������������� �������.";
			link.l1.go = "exit";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "5");
			QuestSetCurrentNode("Henry Morgan", "PL_Q7_begin");
			sld = characterFromId("Henry Morgan");
			LAi_SetHuberTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
		break;


		//********************* ������� ���� *********************
		case "SharpPearl_1":
			dialog.text = "������, ������ ������ �� ���� ������ �� ����. ���������������� �� ���� ��������� ��� ����� ������� � ��������� ������� ����! ��� �� � ��� ������� �������� �������, ��-��-��!";
			link.l1 = "� ��� ��� ����� ���������, ����� �����?";
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
		break;
		case "SharpPearl_2":
			dialog.text = "�� ����. ������� ���� - ��� ���������� ���. ���� ���� �� �� �����������.\n� ������ ������ ��� ����� � ��������.";
			link.l1 = "�������, �������.";
			link.l1.go = "exit";
		break;

        //********************** ������ ����� ����� ***********************
        case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat("�-��, ���������� ����� ������, ��� � ��������... � ����-�� ����� ������������ ��� ������?", 
				"�� ��� �������� �� ���� ������.", 
				"����� ��� �� ��?",
                "���?! �����?! �� � ���� ������...", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�� ������ ��, ����� �� ������������ ���� ������ ���������...", 
				"��, �������, �����.",
                "��, ���� �������"+ GetSexPhrase("","�") +", ������...", 
				"��-��!..", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
  		break;
		case "BlueBird_2":
			dialog.text = "��-��, �� �� �������� ��? � �� ������ �, ��� ������� �� ��������� �� ���� '����� �����'.";
			link.l1 = "�������� ������������� ������������ ���� �������. ��, ������, ��� � ����"+ GetSexPhrase("��","�") +" ��������� �� ����, ��� �� �������� �����, �� �������� ���� ������. ��� ��� �� �������� ��������� �������� �� ���� �����!";
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = "��, ��� ���! �� �� ������, ��� �� ��� ������� �� ���������� ��������, �� ��� ����� ��� �� �������. ��� �� ����, �� ����� ��� ��� '�����' �� ��������� - ������ ���� ��� ��������� ���.";
			link.l1 = "�������, ��� �� ������, ��� ������?";
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = "���, �������. ������ - ����� � ��������� �����, �� � ���� �� ��������.";
			link.l1 = "�����, ���������� �������������, ��� ������?";
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = "���, ����� ��� �� ����. �� ����� ������� �����.";
			link.l1 = "�������. �� ��� �, ������� � �� ����, ��������.";
			link.l1.go = "exit";
		break;

		case "BlueBird_6":
			dialog.text = NPCStringReactionRepeat("��, ����������. ������� �����, ���� ������! �������.", 
				"���������� ��� ���.", 
				"��� � ��� ������...",
                "��, �� �� �������"+ GetSexPhrase("","����") +", "+ GetSexPhrase("��������","�������") +", ����� ������ ��� �� ������!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������, �������. ������ ����� � ����� �������...", 
				"��� ��� �������, �������.",
                "�, �� ��...", 
				"������� ����!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
        //********************** ���������� ������� ***********************
 		case "EngLine_quests":
			dialog.text = "��� ������ ����������� ������ �� ���� �������. ��� ���� �����, ������.";
			link.l1 = "� ���� ���� ��� ���� ������. �������� - �������-���������� ������.";
			link.l1.go = "Step_1";
  		break;

 		case "Step_1":
			dialog.text = "����� ���������, ���������.";
			link.l1 = "��������� ����� ����� �� �������, � ��� �� �������� ��������� ����������� ����� ������. � ������� ������ ����� �������������� ������, ������� ���������� ��������� �������������� '��������� �������' � ������� �� ������� � ���������� � ���������. � ��� ����������, ��� ����� ������. ��������� ���������� �������� � ��������.";
			link.l1.go = "Step_2";
  		break;
  		
 		case "Step_2":
			dialog.text = "���... ������ ���������, �� ��������.";
			link.l1 = "� � ��� ������� ������?";
			link.l1.go = "Step_3";
  		break;
  		
 		case "Step_3":
			dialog.text = "� ���, ��� ����� ����������� � �� �������, � ������� ����� ����������� ������ � �� ��������� � ������� � ���������� �����.";
			link.l1 = "��������� ������� ���� �� ������ ������...";
			link.l1.go = "Step_4";
  		break;
  		
 		case "Step_4":
			dialog.text = "���� ������ ������ ��������� ����� ������. ��, ������ �� � ��� ����, �������� ����� ������� - ���� ������, � ������� ����� ��������� - �� ��� � ����� ����� �� ������. ��� ��� ��� ����.";
			link.l1 = "�����, ���������?";
			link.l1.go = "Step_5";
  		break;
  		
 		case "Step_5":
			dialog.text = "���� ����� � ������. � ��������� ��������� �� ���� ������.";
			link.l1 = "��� ������. ����� ��������.";
			link.l1.go = "exit";
			
            AddQuestRecord("Eng_Line_2_Talking", "4");
            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")   {pchar.questTemp.State = "after_talks_with_pirates";}
            NextDiag.TempNode = "First time";
  		break;

 		case "Lets_go_bussines":
			dialog.text = "��� ���� ������, " + pchar.name + ". ������ �������� �� ��������?";
			link.l1 = "� �� ����. �� � �������� ������� �����, �� ������� ������� � ����?";
			link.l1.go = "Step_6";
  		break;

 		case "Step_6":
            if (GetCompanionQuantity(pchar) != 4)
            {
    			dialog.text = "���, ��� ������ ����� �� �����, ������� ��������������, � �����.";
    			link.l1 = "����� ��������� ����������!";
    			link.l1.go = "Step_7";
            }
            else
            {
    			dialog.text = "� ��� � ��� ���� ��������, ��� ��� ��� ���� �� ���� ���.";
    			link.l1 = "�� ��� �, ��� ������, ���� ������.";
    			link.l1.go = "exit";
                NextDiag.TempNode = "First time";
            }
  		break;

 		case "Step_7":
			AddQuestRecord("Eng_Line_3_Morgan", "4");
            LAi_SetActorType(npchar);
            LAi_ActorSetStayMode(npchar);
            ChangeCharacterAddressGroup(npchar, "Pirates_townhall", "goto", "governor1");
            CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 10, false);
            Fantom_SetBalls(npchar, "pirate");
            npchar.CompanionEnemyEnable = false;  // ��� ������ ��� ��������
            pchar.questTemp.CompanionQuantity = makeint(sti(pchar.questTemp.CompanionQuantity) + 1);
            pchar.questTemp.CompanionQuantity.Jackman = true;
            NextDiag.TempNode = "Have_hot_bussines";
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

  		break;

	 	case "Have_hot_bussines":   // ���� ������� ����� ��������� ��� ����������, �� ����, ������ ��. �� �� ������ ������.
			dialog.text = "���� ������, ����� �������� ������ ���!";
            link.l1 = "��������!";
			link.l1.go = "exit";
            NextDiag.TempNode = "Have_hot_bussines";
  		break;

	 	case "Gold_found_in_fort":    // ���� ��������� � ����� ������
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman") && !IsCompanion(characterFromID("Jackman")))
    		{
            	dialog.text = "�� ��� �����"+ GetSexPhrase("","�") +" - ��� ������ ��� �������� ���������� ���������! �� ��� �� ����, ������� ����� � ������ ������� ����� ����� �� ���� � �� ���������� ������� ��� �� ����."+
                              "� ������������ �� ����� ��� ����� ������. ���, ������� �������, ���������� �������� ������. �� �� ���"+ GetSexPhrase("","�") +" ����"+ GetSexPhrase("","�") +", ������ ���� �����. ��� � ������ ����� ������ ����!!!"+
                              "������ ���, � ���� ����. ��� �� ����� ����� �������.";
            }
            else
            {
    			dialog.text = "������� �������, ���������� �������� ������. �� �� ���"+ GetSexPhrase("","�") +" ����"+ GetSexPhrase("","�") +", ������ ���� �����. ��� � ������ ����� ������ ����!!!"+
                              "������ ���, � ���� ����. ��� �� ����� ����� �������.";
            }
            link.l1 = "� � ��� �� ������"+ GetSexPhrase("","�") +"!";
			link.l1.go = "Step_8";
        break;

	 	case "Step_8":
			dialog.text = "��-��... �� - ������� ������, " + pchar.name + " " + pchar.lastname + ". � ����� ���� �����, "+ GetSexPhrase("����","�������") +".\n"+
                          "��� ���������� ������ ����� ����� ������� ������. ����, ��� �� �������� ������ ���� ���� ������.";
			link.l1 = "��� ��������!";
			link.l1.go = "Step_9";
        break;

	 	case "Step_9":
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15.0);
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
        break;
        //********************** ����������� ������� ***********************
 		case "HolLine8_quest":
			dialog.text = "������ ����, ����� ���������"+ GetSexPhrase("","�") +" �� ���?";
			link.l1 = "� ������"+ GetSexPhrase("","�") +" ���� �� ����, ��� ������ ������, ������� ������� ������� ��������� ������.";
			link.l1.go = "Step_H8_1";
  		break;
 		case "Step_H8_1":
			dialog.text = "����, ���� ���-��... ��������� �� ����... �� ���-�� ����� ���������� ������ ������, �������, ��� ������������...";
			link.l1 = "� ���?";
			link.l1.go = "Step_H8_2";
  		break;
 		case "Step_H8_2":
			dialog.text = "�� ������. �� �����, �������� ������� ���... �� � �� �� ������ ��� ���� - � ������� ������������, ���-�����!";
			link.l1 = "��, � � ����� �������?";
			link.l1.go = "Step_H8_3";
  		break;
 		case "Step_H8_3":
			dialog.text = "��� � ����-��-������.";
			link.l1 = "�������... �������, �������.";
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_8_SeekBible", "3");
			pchar.questTemp.State = "SeekBible_toFFBrothel";
			NextDiag.TempNode = "First time";
  		break;
		//********************* ����������� ������� *********************
        case "FraLine8_talk":
            dialog.text = "���� ��, ������� " + GetFullName(pchar) + " ���������"+ GetSexPhrase("","�") +"! ������ ���! ���������� � � �� ����, ��� ���� �� �������� �������� ���-�� ����������.";
            link.l1 = "� �����, ������ �������� ����������� � �� ��������. ����� ������ ���������� �� ������� � �������� ����� ����� ������� � ����������.";
            link.l1.go = "Step_F8_1";
        break;
        case "Step_F8_1":
            dialog.text = "�� ��, ������������� ������ �����������. ��� �����, ��� � � ��� �� ��������� ����������� � ��� ����. ��������� ������� - ��������, �� ������� ������ ������ ������ �����. ��� ��� ���� ����������� ��������� ���� ������� ������ ����.";
            link.l1 = "�� ������. �� ������� ����, � �����"+ GetSexPhrase("","�") +" � ����� ������������ �� ���� �����, � �� �� ������� ���.";
            link.l1.go = "exit";
			pchar.questTemp.Count = makeint(pchar.questTemp.Count)+1;
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "5");
        break;
		//********************* ��������� ������� *********************
		case "PL_Q8_deck":
			dialog.text = "�� ��� ������� ����� � ���� �� ������. ��� ����� ������ ���� �� ����� �����!";
			link.l1 = "��, � �����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;
		case "PL_Q8_deck_1":
			dialog.text = "��, ����� �� ����� �������, �� ����� � ����...";
			link.l1 = "��� � �������, �� ���������, �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;

		case "PL_Q8":
			dialog.text = "����, �������...";
			link.l1 = "��� ������� �� ����� ������?";
			link.l1.go = "PL_Q8_1";
		break;
		case "PL_Q8_1":
			dialog.text = "������ �� �����. �� � ������, � ��������� � ����������. ��� ��� � ����� ������ �� ��� ������ �� ����.";
			link.l1 = "����, ��� �� ���?!";
			link.l1.go = "PL_Q8_2";
		break;
		case "PL_Q8_2":
			dialog.text = "� ��� ���! � �����, � ���� ����� ���� ������!";
			link.l1 = "��, ����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Panama_inEngland";
		break;
		//������ �����-�������
		case "Mushket":
			dialog.text = "��, ���� ����� ����� - ����� �������� ����, �������, ������ �� ����������. ������ ����� ��� �� ��� �������, � ���� �� ����� ������� ������. ���� �� � ��� ����� �������� - �� �� ��� �� �� �������� ������� �������� ������� ��� ���� ����� ��������.";
			link.l1 = "��� ��� �� ���� �� ������? ��� ��� ����� �����.";
			link.l1.go = "Mushket_1";
			DeleteAttribute(pchar, "questTemp.mushket2x2");
		break;
		case "Mushket_1":
			dialog.text = "����� � �� �������� - �� ��� �� ����. ������������ - ����� ������, ���� ��������� � ������. � ����� ��� ���������� � ����, �� �� ������ �� ��� ���� ���� ���������, � � �������� ��� ������. � ��, �����������, �������� �������� �� �������.\n�� � � ������ ����� ���� - ������� �������� � ���� ����, ��� � ������� �� ����� ����� �� ������, � ���� ����� ������ �� ������ � ���������������. ��� ���, ����� �� ���� � ��� �� ��������, ���� ����� - ����� �� ����� ��������.";
			link.l1 = "�� ��... �����, ����������� ���?";
			link.l1.go = "Mushket_2";
		break;
		case "Mushket_2":
			dialog.text = "������, ����� ������ ������ � ����. ������ ����������� �� ����������� ��������� - ���� ���� �� ����� �� ����������...";
			link.l1 = "����. �� ��� �, ������� ����, �������.";
			link.l1.go = "exit";
			SetMushketCapitainInWorld();
			AddQuestRecord("SeekDoubleMushket", "2");
		break;
		
		//*************************** ����� "������������� ������ "�����"" **********************
        case "Andre_Abel_Quest_Jackman_Dialog_1":
			dialog.text = "��� ���� �� ���� �����, " + pchar.name + "?";
			link.l1 = "� �� ����, �������...";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_2";
		break;
			
		case "Andre_Abel_Quest_Jackman_Dialog_2":
			dialog.text = "����������, ��� � ���� �� ����.";
			link.l1 = "���� �� ���� ��� ������... � �����, � �����, �� ������� �������� �� ����� ����� �����?";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_3";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_3":
			dialog.text = "�����?! ��-��... �� ���, �������� ���� ��������?! ����� �� ��� �����"+ GetSexPhrase("","��") +" �� ���� ��� ����?";
			link.l1 = "���, �� �����"+ GetSexPhrase("","��") +". ��������� ����� ���������, �� ������ ��������� �� ����, � ������ ���������� ��� ������������. ���� ���������� ������ �������� ����.";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_4";
		break;
			
		case "Andre_Abel_Quest_Jackman_Dialog_4":
			dialog.text = "� ��� ��� �������� ��� ������������? ��?! �������, � �� ����, ��� �� ������ ������� � ������ ������ � ����-�-������?! �����, ��� ����� ���� ������?!\n������, ����� ���� �� �������� ��������. � �� ���������, ���� �� ������ ��, ��� ��� �����������.";
			link.l1 = "�� ��� �, ������, �������, ����."+ GetSexPhrase(" ������ �� �������, ��� ����� �������, � ���� �������...","") +"";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_5";
		break;
			
		case "Andre_Abel_Quest_Jackman_Dialog_5":
			dialog.text = ""+ GetSexPhrase("��� �� ������?! �� ���, ��������� ��� �������� � ���� �� ����������?!\n������, � ��-�� ���������� ����� ��������� � �������� ������ ������!","�� ������� �� ���, � ���� ���! � ���� ���, ��� ��� ��� ������� ������?") +"";
			link.l1 = ""+ GetSexPhrase("��� ��, �������? ����� ������? ������ ��������, ��� �� �� ���� ����������.","���. �����, �������.") +"";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_6";
		break;
			
		case "Andre_Abel_Quest_Jackman_Dialog_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoFunctionReloadToLocation("Pirates_town", "reload", "reload3", "Andre_Abel_Quest_After_First_Jackman_Dialog");
		break;
			
		case "Andre_Abel_Quest_Jackman_Dialog_7":
			dialog.text = "����� ��? ���� �� �����"+ GetSexPhrase("","��") +" ����� �� �����, �� ����� ����� �������������� �������� � �� ��� ����.";
			link.l1 = "����� �� �����"+ GetSexPhrase("","��") +", ���� �����"+ GetSexPhrase("","��") +" ������ �� �������.";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_8";
		break;
			
		case "Andre_Abel_Quest_Jackman_Dialog_8":
			dialog.text = "��, ������ �� �������? �� ��� ����� ��� ����!";
			link.l1 = "�����...";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_9";
		break;
			
		case "Andre_Abel_Quest_Jackman_Dialog_9":
			dialog.text = "������! ����� ���� �����?! \n�����, ����� ���� ��������, � ���� ��������� ���� ��������.";
			link.l1 = "��� � �������.";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_10";
			TakeItemFromCharacter(PChar, "letter_1");	
		break;
			
		case "Andre_Abel_Quest_Jackman_Dialog_10":
			dialog.text = "������ ������� "+ GetSexPhrase("������ ������","���") +", ��� � ���� �� ������! ��� ��� ����� �� ���������� ��� �� �����, ���� ���� �����..."+ GetSexPhrase(" � ������ ����������, ������ �� ����� ������!","") +"";
			link.l1 = "�� �������, ��� ����. "+ GetSexPhrase("��������� ����������","����, �������") +".";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_11";
		break;
			
		case "Andre_Abel_Quest_Jackman_Dialog_11":
			DialogExit();
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("Andre_Abel_Quest", "22");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","�"));
			PChar.QuestTemp.Andre_Abel_Quest_Complete = true;
		break;

		//*************************** ��������� "��������� �������� - �����" **********************
		case "CapComission1":
			dialog.text = "��-��. �� �������, � ���� ������ ���� �������? �������, ���� ��������� ������ � ����?";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". ���� �����?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "���. � ��� ������ � �������� ������ ����� ���������� � ��������� - ���������� ������, �� ������� �� ������� ������.";
				link.l1 = "��� ����...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "�-�, �� �������-��. � �� ���� ��������� ������� ��� � �������� ������ ����� ���������� � ���������, �� ������ ��������� � ���� ����� ������-������... �� ����� ������"+ GetSexPhrase("","��") +"?";
				link.l1 = "������, �������, ��� ����� ����... � �����, � ���� ��� ����� �����. �� � �����"+ GetSexPhrase("","�") +" ����������.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "������, ��� �� ������. ��� ������ - 150000 �������. ��� � ���� ��� �������?"
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "����� �� �����"+ GetSexPhrase("��","���") +"... � ������, ���� ��������� � ���� ����� �����? �, ��������, ��� ������������� ����� ��������.";
			link.l1 = "�� � �� ��������� ���� ������������� � �������"+ GetSexPhrase("","�") +".";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "��, �������"+ GetSexPhrase("","�") +" �� - ��� � ���� ��������?";
			link.l1 = "������, � �� ������� ������, ���� �� ������?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "�-�, �� ������, �������, �� � ���� �� �����. � �� �������� ������, ��-��-��-��... ��, �����.";
			link.l1 = "���������.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "���-���... ���� � ���� ���� ����... ���� �� ����, ��� ������... � �����, ����� ������� �� ��� ������ ������������ ������.";
				link.l1 = "� ����� ������ ������ ��� � ��������?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "��, " + pchar.name + ", �� �� ������, ��� ��� ���� �� ��������. ������� � �������� � �������� ������ ��������, ��-��.";
				link.l1 = "�� �����, �� �������.";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "��, ��������� ��, ��� ��������� ���� �� ��������... ��� �� ������ ��� �����, ��� ����� ������ ����� � ������� ������� �������� ��� �� ��� ����� ������. ����, ���� �� ���������� � ���������� - � �� ��������.";
			link.l1 = "� ������ ���� �� ������� �� ��� ����� �����?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "��... � ����� ����� " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " ������ ����� �������, ��� � ����� ������� ���� " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + " ���� � �� ����. ������� ��� ������� � ����� � �� ���� ����� '" + pchar.GenQuest.CaptainComission.ShipName1 + "' � '" + pchar.GenQuest.CaptainComission.ShipName2 + "' ���� � " + sLoc + ". ��������� ������, ������ � �� ���� �������� ��� ���� ����� �����?";
			link.l1 = "�������. � ������� � ���� ���� �������?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "�����, ���� 12-15, �� ������. ��� �����, ���� ��� �� ������ ��������� �� �������, ����� ������ �� � ������ ������ �� ����� �� ����� ������. �� ����� ����� ����� ��� ����.";
			link.l1 = "������, � ������ �� ��� ����. ���������� ������.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "�� ���������. ��� ���� �������� ��� � ���� �� ����. � �� ���� ���?";
			link.l1 = "�����. � �������� ��������� ��� ������������.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "�-�, ��� ������. � �� � �� ���� �����������, ��� ����������, �������� ����� ������ ���� �� ������ ��������. ��-��-��-��... ��, �����.";
			link.l1 = "���������.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "�� ���, " + GetFullName(pchar) + ", ������"+ GetSexPhrase("","�") +" �� ��� ����� ��������?.. ��-��-��...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "���. � �� �����"+ GetSexPhrase("","�") +" �� �������. � �� �������� ���� ��� ��� �� ����������.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "��, ��� � �������������� - ��������"+ GetSexPhrase("","�") +" ������� ����.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "׸��! ���������� - �� ����������, ����� ������ �������?.. ��, � ��� �� ���������� ������?";
			link.l1 = "�����, � ���� ���� �����-������ ��������� �������?";
			link.l1.go = "CapComission4_1";
			link.l2 = "������, �������, ������ ��� ����� �������� ���������...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "���.";
			link.l1 = "...��, ����� ��������� ����������...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "���������?!! ������ ��� ��-�� ����� ��������������� � ������� ������ �������! � ������ � ���� �������� ��� ��������! ������� �� 200000, ���� ������.";
			link.l1 = "������ ���... ������...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "� ����, ����� ���� ������.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","��"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "������ ������� ��������...";
			link.l1 = "��������� ����������.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "��-��! ��� ��� ������! ������� ������ �������� � ����� ������"+ GetSexPhrase("","�") +".";
			link.l1 = "�������. ��������� ����������.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = "�� ����� ������"+ GetSexPhrase("","��") +"? ���� � �� �����, ����� ������, ��� ������ ��� �����������.";			
			link.l1 = "������, "+ NPChar.name +", ��� ����� ����... � �����, � ���� ��� ����� �����. �� � �����"+ GetSexPhrase("","�") +" ����������.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "������, ��� �� ������. ��� ������ - 150000 �������. ��� � ���� ��� �������?"
				link.l2.go = "CapComission2_3";
			}			
		break;
		
		// ============== ������ ����� ���� ���, ������� ������� � ������� =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("������ ����� ���� ���!!! ��� ��� �� ����� ��������?! ��, ������, "+ GetSexPhrase("��������","�������") +"...", "��, �� ���� ��� ��� ���������?! �����, �������"+ GetSexPhrase("","�") +" �������� ����? ��, ����� ���� �����...", "������, �� ���� ��� �����"+ GetSexPhrase("","��") +"? �� �� ���"+ GetSexPhrase("","����") +", �����������! ��, ������, ��� �� �������"+ GetSexPhrase("","�") +", ����"+ GetSexPhrase("��","��") +"...");
			link.l1 = LinkRandPhrase("������!!", "��������!!", "�-���, ����!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== ���� ��� angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("����� ���","��������") +" ������!", "��� �� ����� ����!");
			link.l1 = "��...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //����������� � ��������� ����� 10 ����.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "���� �� ����� ��������� ���� �� ���� ������� �����������. ������ ��������� ����� ���� ����� ���������...";
        			link.l1 = "� �����"+ GetSexPhrase("","�") +".";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("�� ���� ������� ������"+ GetSexPhrase("","�") +", �������� �������.", "� �� ���� � ����� ��������, ��� ��� ���� ����� ���� �� ����������.");
			link.l1 = RandPhraseSimple("�� ��� ������...", "��, �� ��� ��...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //����������� � ��������� ����� 10 ����.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "�������, ������ �� �� ������ �������� ���� ������� �����������, ����� ��� �������� ���� �����. ���������, ��� ��� ����� ����� ���������.";
        			link.l1 = "�������, �� ������ ���� ������ - �� ����...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Pirates_town","reload","reload3");
		break;
		// <<<<<<<<<<<<============= ���� ��� angry =============================
	}
}
void SetMushketCapitainInWorld()
{
	//������� �����
	int Rank = sti(pchar.rank) + 15;
	if (Rank > 30) Rank = 30;
	if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) ref sld = GetCharacter(NPC_GenerateCharacter("MushketCap", "officer_17", "man", "spy", Rank, PIRATE, -1, true));
	else sld = GetCharacter(NPC_GenerateCharacter("MushketCap", "officer_17", "man", "man_fast", Rank, PIRATE, -1, true));
	sld.name = "�������";
	sld.lastname = "������";
 	SetCaptanModelByEncType(sld, "pirate");
	FantomMakeCoolSailor(sld, SHIP_BRIGQEEN, "������", CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade34", "pistol2", 50);
	sld.Ship.Mode = "pirate";	
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
	sld.DontRansackCaptain = true; //�� ���������
	sld.WatchFort = true; //������ �����
	if (bHardBoss) sld.AlwaysReload = true;//����������� ���������� �� ���������
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//� ������� ������ ����
	string sGroup = "MushketCapShip";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	sld.quest = "InMap"; //������ ���� �������� ����
	sld.city = "PortRoyal"; //��������� �������, �� ����� ������� � �������� ������
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //��������� �������, � ����� ������� �� ������
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	pchar.questTemp.Mushket.Shore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("��� � �������� ����� ��: " + sld.city + " � ���������� �: " + sld.quest.targetShore);
	//==> �� �����
	sld.mapEnc.type = "trade";
	//����� ���� ��������� �� �����
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "���� '������'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //���� ������� ���� � �������
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//������� Id ���� � ���� ���-�����
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "mushket"; //������������� ������
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //�������� Id ������������ ��� ������� � ������ ����
	NullCharacter.capitainBase.(sTemp).Tilte1 = "SeekDoubleMushket"; //��������� ���������
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SeekDoubleMushket"; //��� ������ � ���������
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}