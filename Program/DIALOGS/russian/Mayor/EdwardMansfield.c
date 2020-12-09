// ������ ��������, ����� ���������� � ������������ �����, ���������� �������
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= ���� angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
            	if (NPChar.quest.meeting == "0")
				{
					dialog.Text = TimeGreeting() + "! � "+ GetFullName(NPChar) + ", ����� ��������� � ���� ����. � ���������, �������� � ������� ������� ����� �������� ������, �� ������ �� ��� ��� ��������� ������� ������ �� �����.";
					Link.l1 = "���"+ GetSexPhrase("","�") +" ����������. � ������� " + GetFullName(Pchar) + ". ��� ��� ����.";
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = TimeGreeting() + ". � �����, ����� ����� ���, ����� �������������� ���������� ������� �������, ���� ������� ������ �������� �������.";
					Link.l1 = "�� ���� ������.";
					Link.l1.go = "exit";
				}
            }
            else
            {
				dialog.text = NPCStringReactionRepeat("� ���� �� ��� ����? ���? ����� "+ GetSexPhrase("��������� ������!","������� �� ��������� ����.") +"",
	                         "�, �������, ���� ���������...", "���� � ��������� � ����, �� �� ����������� ��������� ����!",
	                         "��, �� �� �� � ���� "+ GetSexPhrase("�������, ��� ���","�����, ������") +"...", "repeat", 30, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("��� �����.",
	                                               "��, " + npchar.name + ", ���������� ����.",
	                                               "������, " + npchar.name + "...",
	                                               "��, ��...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}


					if (Pchar.BaseNation == PIRATE)
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "����� ����� ��������� ��� ���� ��������?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many") && npchar.city == pchar.questTemp.pirateStartQuest.City)
							{
								link.l2 = "� ���"+ GetSexPhrase("��","��") +" �� ����, �� ��� ����� ������ - 30 000 ��������, ����� �������� ����� �� ����.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0 && npchar.city == pchar.questTemp.pirateStartQuest.City)
							{
								link.l2 = "��������, ��� �� ������ � ���"+ GetSexPhrase("��","��") +" �� ����� ������ �� ���������������.";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5" && npchar.city == pchar.questTemp.pirateStartQuest.City)
							{
								link.l2 = "���� �������. ������ ���� ������ �� ����� �������� ���������� � �������� �������.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		//zagolski. ��������� ����� �� ������ ===================================
		case "pirateStartQuest":
			dialog.text = "��... ���������, ��������? � ��� ���� ����� ������, ��� �� �� ��� �������"+ GetSexPhrase("��","���") +". ��� ��� ��� ����� ������� �� �������. ���������� ���-��� ��������� � �������� ���������, � ���� ����� ��� �����, ��� �����������. ����� ����� �� ������, �� ���-��� ���������.";
			link.l1 = "��� � ������. � ��� �� ����?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "������, �� ������� � ��������� �� ����. ������...";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "� ���� � ��������� - � ����� ����� ���������� � � ��������� ����� '�������' � �������� 200 �����, ����� ������� �� ������ ���������� �� ��������� ���������. ��� � ����� ��������� �����, � �������� ����������, � ��� ����� ��� ��������, ��� ��� ����� ������ � ��������� �������. ��!.. ������� � ���� �� ��������. � ������� ��������� ���������� ������� ������� � ������, ��� ����� ��� ���������� � ������ ����� - ���� � ������, �� ��� ������ � �����.";
			link.l1 = "� ���? � ����"+ GetSexPhrase("��","��") +" � ��������� ��� ��������� 200 �����, ���� �� �� ������� �������? � ��� ��� �� �������?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "���, �������. ����� � ����� �� ������? ������� � �� ����� � ����� ������. �� ��� ����� ��������������, ��� ����, ������� ��� ����������� - ��� � ���� ��� ������. � �� ������ ������� ���, ��� ��������� ��� ����� ������, � �������� ���� 10 000 ��������. ��������� ��� ������. �� ���, ��������?";
			link.l1 = "������! � ��� ��� ����� ����? ���� �����-�� �����������?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "���. ������ ��������� ����, ��������� ��� � ����� �� 10 000 - ������, �� ��������.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "���� �� � ���� ��� ���� �����, � �������� �� � ��� ����� �����. ��� �� ��� � ���� ������ ��������� �� �����. �� ���� ������ ���������� ������ - ��� ��� ������ � ����� '�������' � � ���� ���������? �� ����� ��� ������ � ��� ��������. ��������?";
			link.l1 = "��, ���� ���-�� �������������� ����������.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "���! ��� ��� � ���. ������� ���� ��������� ����������� � ������� ����� - � ���� ���� �� �������. ��� ����� ����������, � ������ - ��� ������ �� �������. ������ �� ���������, ������ ����� �� ���� �� ���� ������� ����� �� ������? ���� � �� ������, ��� ������� ���������� - ����������� ���� �������. � ��� ����� ����� �� �������...";
			link.l1 = "�������... ������, ����� ����������� ���� � �� ��������� �����. ����������� �� ������.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "�������� �����, ��������? ��� ������� �����... ���� ���� ������ 5000 ��������, ������ � ���� ������ ���. �� ���� ��������� ������� � ���� - ����� � ������ �� ��������� ������! �� ���� ����� ����� �� �������.";
			link.l1 = "����� ���� �����...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "���, �����. ��� ���������� ������.";
			link.l1 = "��� ����� � �������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "��! �������� �������! � ��� ������, ��� �� � ���� ����������. �� ��� ������ ������ ���������� ����������.";
			link.l1 = "� ������ ���� ��������"+ GetSexPhrase("","�") +". ���� �������� ���� ������ �����.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "�������, ��� ��������� �������. �� �� �� �����, � ���� �������� ���� ��� ���� ����\n������� - ��� ������� �� ������� ������� ����, ������� ����� �� ������� '�������'. � ������, ��� ������ ���� � ���� ����������, ���� �� � �� �����. ��� ������� ������ � ��������� �������, ���� ������ - ��������� ����� � �������� �������. � ������ ��� �� ���� �� ������"+ GetSexPhrase("","�") +", ������� � ������ ���� �������� ��� ���� ����. ������� 15 000 ��������. ������"+ GetSexPhrase("��","��") +"?";
			link.l1 = "������! ������, ��� ��������� ������ ���� ��� ��������.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "������ ���, ������� ��� � ��� �����������... �� � �������. ������, �� � ���.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "�����-�����. ��� ���� ��������� ��� � ��� �������� ���, ��� �� ������� �������"+ GetSexPhrase("��","���") +". �� ��� �, ���� ���� �� �������� ������"+ GetSexPhrase("","�") +", ��� ��������� ������� � 15 000 ��������. � ������� ����, ������� �� ��� �����"+ GetSexPhrase("","��") +".";
			link.l1 = "��� � �������, ���"+ GetSexPhrase(" ���","� ����") +" ������! � ������ ���� ���� ����, � � ��� ����� ��������"+ GetSexPhrase("��","���") +". �� �������!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;
		
		//********************* ���������� ������� *********************
 		case "EngLine_quests":
			dialog.text = "� ������ ���, �������.";
			link.l1 = "� ������"+ GetSexPhrase("","�") +" � ��� �� ��������� �������-����������� ������ ���� ������ ���������.";
			link.l1.go = "Step_1";
  		break;
 		case "Step_1":
			dialog.text = "������ �����������.";
			link.l1 = "��� ����� �������� ������ ��� ������� ��������� �������, ���������� �� � ��������� ����������� ������� � ��������� ���� - ����� �������.";
			link.l1.go = "Step_2";
  		break;
 		case "Step_2":
			dialog.text = "��... � � ��� ������� ������ �������? ���������, ��� �������� ��������. ��������� �� �������� �� ����������. ��, � ���������� ���� ������������ � �������� ���������, �� ��� ���������������� �� ��������� �����. ����� �� - ����� ����.";
			link.l1 = "���, ����� ������� � ���������� ����������� ��������� �������� �����. ����� ����, ���������� ������� ���� �������� ��������� �� ���������� � ������� ������, �� ��� �����.";
			link.l1.go = "Step_3";
  		break;
 		case "Step_3":
			dialog.text = "�������. ��������� �� ����������. � ����� �� ����.";
			link.l1 = "����, � ��� ������ �������� �� ����������.";
			link.l1.go = "Step_4";
  		break;
 		case "Step_4":
			dialog.text = ""+ GetSexPhrase("���� ���, �","�") +" �� ���� ��� ���� �������������� ������ �� ������� �������-����������� ������.";
			link.l1 = "������ ��� ������� ��� ����� ������ ��������.";
			link.l1.go = "Step_5";
  		break;
 		case "Step_5":
			dialog.text = "������ ���������. ��� ��������� ������� - ������ ���������. � - ���������.";
			link.l1 = "�� �� - ���������� �����, � ����������� ���������������� ���� ������ ���������. ��� ������� ���������� ����� ������������ ����� �� ��� �������.";
			link.l1.go = "Step_6";
  		break;
 		case "Step_6":
			dialog.text = "��� ����� �������� ���, ��� ������. � ������������� ���� ���������� ��������� ������, �� ��� ������ �� �������� ����, ��� � ���� ������ ������ ���� �����������������. ����� ������ �������� ������ �� ����. � ������� ���, ����� ��� ������ �������. ��������.";
			link.l1 = "��� �, ���� ��� ������ ������ �������, �� ��������.";
			link.l1.go = "exit";
            NextDiag.TempNode = "First time";
            AddQuestRecord("Eng_Line_2_Talking", "3");

            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")
			{
				pchar.questTemp.State = "after_talks_with_pirates";
			}
  		break;
 		case "No_Mansfield_first_time":
			dialog.text = "������ ����, ���� ����� ������� ���. ����� ������ ��������� � ������ ������ ����������.";
			link.l1 = "����� �������, �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = "��� ������ ������� � ����� �������������. ����� �����.";
			link.l1 = "� ��� �����.";
			link.l1.go = "exit";
  		break;
		//********************* ����������� ������� *********************
  		case "HolLine3_WormEngPlans":
			dialog.text = "��� ������� ���� �� ���?";
			link.l1 = "� ������"+ GetSexPhrase("","�") +" � ��� �� ��������� �������-����������� ������� ������ ����������.";
			link.l1.go = "Step_H3_1";
        break;
 		case "Step_H3_1":
			dialog.text = "����� ������. ��� ����� �� ���� �������-����������� ����������?";
			link.l1 = "������, ��������� ������ �� ����������, �������� ��������� �������� �����.";
			link.l1.go = "Step_H3_2";
  		break;
 		case "Step_H3_2":
			dialog.text = "��������� �������, � ���� ���� � ���� �����...";
			link.l1 = "��� ����� �� ����������, ����� ������������.";
			link.l1.go = "Step_H3_3";
  		break;
 		case "Step_H3_3":
			dialog.text = "���, �� ����� ���������... ��, �� ������ ���� ������������� ��� � ���, ��� ����� ����������� �������� �� ������� � ������ ������� � �����.";
			link.l1 = "���������� �����. ����� ��� - ��������� ������������� ��� ����������� ���������.";
			link.l1.go = "Step_H3_4";
            TakeItemFromCharacter(pchar, "letter_1");
            BackItemDescribe("letter_1");
  		break;
 		case "Step_H3_4":
			dialog.text = "��� ���� � ���, ��� � �� ���� ������ � ������ ��������� �� ���� �����. � ���� � ��� ���� ������� �������, �������� ����� �� ��� ���.";
			link.l1 = "� ��� ��� �������� ����������? ��� �� ������ �� ������ � ����� �� ������� ������ ����� ������ � ������� ���?";
			link.l1.go = "Step_H3_5";
  		break;
 		case "Step_H3_5":
			dialog.text = "�� ���� �������� ���������, "+ GetSexPhrase("������� �������","�������") +", � ����, ��� � �����. �� � ������������� ������ �� ����� � ������ ���������. ������, ��� ��� � ���� ��������.\n"+
                          "��������� �� ������� ������ �� ��� �������� ����� �������� �� ���������, ������� ���������� ���� ������������ ���������� �� �������. �, �����������, ���������. ���������� ����� ������, ������� � ���� ������.\n"+
                          "����� ����������, ��� ��������� �������� ����� �������� ������� ������� ������ �������� ������ ����������� � ������� �������. �����, ��� ��� ��� �������...";
			link.l1 = "����������, ��� �������� ��������� ������� �� �������?";
			link.l1.go = "Step_H3_6";
  		break;
 		case "Step_H3_6":
			dialog.text = "����������� ��������� �� ������� �� �����, � ��� ��������� ������ ����������� - ���� ��. � ���� ������������ ��� ��� ����� ��������, �� �� ������� ����� �� ������� �������� ����������.\n"+
                          "�� � ������, ����� �������� ������� ���� ����� �� ��� �� �������� �������� ���������� ����������� ���������� ���������� ������� �� ����� ������. ��� ��� ���, ������� ������ ��� �� �� �����.";
			link.l1 = "�� ��� ��, ��� ����, ��������� ����� �� ���������...";
			link.l1.go = "Step_H3_7";
  		break;
 		case "Step_H3_7":
			dialog.text = "� �� ��� ����������� �� ������. ���� � ���, ��� ��� ������� ����������� �������� � ��������� ����, ������ �������� ���-���� ����� ������ ������� ������ ��������. ��� ��� ���� ����� ����� ������� � ���������� �� ����� �����.\n"+
                          "��� ��� � ���� �������� ������� - ����������� ���������� � ���� ����� � ����� �������.";
			link.l1 = "� ����� �������, �������� ��������?";
			link.l1.go = "Step_H3_8";
  		break;
 		case "Step_H3_8":
			dialog.text = "��, ������ ���. � �� ����������, ��������� �� ���� �� ��� ����� �������. ���� ���� ������, �� ���� ����� ������ � ��� � �������. ��������� ��� �� ����� ����� ������ ����.";
			link.l1 = "� �� �������?";
			link.l1.go = "Step_H3_9";
  		break;
 		case "Step_H3_9":
			dialog.text = "���� ������ ������, �� ������� ���.";
			link.l1 = "������, �� �� �������� ��� ������ ��� �������, ����� �� ������� ���� ������?";
			link.l1.go = "Step_H3_10";
  		break;
 		case "Step_H3_10":
			dialog.text = "���, ��� �� �����������. ���� �� ���-�� � ����� ��� ����� ������� � ����������� �������, ����� ������� ����� �� ��������. �� ���� �������.";
			link.l1 = "������ ���������, �� ��������� ��� ������ ���������. ������� ��� �� ������!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
    		pchar.questTemp.State = "WormEnglPlans_toMorgan";
    		AddQuestRecord("Hol_Line_3_WormEnglishPlans", "2");
    		QuestSetCurrentNode("Henry Morgan", "HolLine3_fromMansfield");
            ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "SentJons_HouseF3", "goto", "goto1");
            LAi_SetHuberStayType(characterFromId("Henry Morgan"));
          break;


// ======================== ���� ��� angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("����� ���","��������") +" ������!", "��� �� ����� ����!");
			link.l1 = "��-��-��...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //����������� � ���������� ����� 30 ����.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "���� �� ����� ��������� ����, ������� ���.";
        			link.l1 = "� �����"+ GetSexPhrase("","�") +", ������, ������ �� ����.";
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
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= ���� ��� angry =============================
	}
}
