
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// ����� ������� �� ������� -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // ����� ������� �� ������� <--
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
			if (npchar.angry.name == "AscoldMerchant") Dialog.CurrentNode = "AngryQuest_AscoldMerchant";
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= ���� angry ===================================
// ============================================================================	   
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------������ ������ - ������ �������
  		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

  		case "First time":
		
			if (CheckChit() == true)
                {
					dialog.text = RandPhraseSimple(RandPhraseSimple("��� �� �� �����, ��� ������� ���� ��� �� ���� �����... ���� ��� ��� ����������: ���� �����������, �� ����� ��������� ��������� �� ��������. ����������!","�-�-�, ���� � ����! �� ��� �� ������� ��� ������! � ��� ��� ������ ������, ��������, �� �� ������ ������!"), RandPhraseSimple("�����, ��� �������, ������ ������: ���� ������� ��������, ��� ������������� ��������? ���� ��������� �� ���� ��������� �� ������, ��� ��� ���������� ������ ������� �������... ��������� ������, ������!","�� ��, �� ��, ����� ��� ���������� ���������� ���������! ��, ���, ��� �� ����������...���! �� ����������, � ���������, ��-��-��! ����������, �����."));
            		link.l1 = LinkRandPhrase("��, �� ���� ������� ���� ��������. ���� ������ �����.","�� ���� �������? � ���� ����-���� ���� �������... �����-�����, �����.","���! � ��� �������� - ������ ���� ��� ������...");
            		link.l1.go = "exit";
					break;
                }
			//������������ ����� -->
			if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
			{
				dialog.text = LinkRandPhrase("� ������ ���� ����� � ����� �� ���� ������� �����. ��� �� ��� ����.", 
					"��-�, �������� � ������, ������...", 
					"�� �����, ��� ��� �������� �������� ���� ��������. ��� ������� ������� ���� ������������.");
				link.l1 = "����.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasPadre" || pchar.questTemp.MC == "toCaracasTavern")
			{
				dialog.text = "�������, ��� �� ����� � ������� � ����� ��������! �� � ��� ���?";
				link.l1 = "�����...";
				link.l1.go = "exit";
				break;
			}
			//<-- ������������ ����� 

			dialog.text = NPCharSexPhrase(npchar, "������ ��������� ���������� ��� ���� ��� ����� ��������, �������? ����� �� ���������� �� ������!", "��, �������, � ��� � �����, ��� �� ��������� ������ �� ���!.. ���� ���������� ���������� ��� ��� � ����� ��������, � ����� ��������� ������ ����������� �����.");
			link.l1 = "������, ��� ��� � ���� ����.";
			link.l1.go = "Trade_exit";
			
   			link.l2 = "� �� ������� ����.";
			link.l2.go = "quests";
			//--> eddy. �������, �������� �� ���������� �����
			if (pchar.questTemp.Ascold == "Seek_powder" && !CheckAttribute(npchar, "quest.answer_2"))
			{
   				link.l4 = LinkRandPhrase("���� �� ����������� ����� ���� - ������� �����?", "� ���� � ������� ���� ������� �����?", "��������, �� �� ������, ��� ����� ������� ������� �����?");
				link.l4.go = "AscoldMerchant";
			}
			//<-- eddy. �������, �������� �� ���������� �����
			link.l3 = "�������, �� ����������.";
			link.l3.go = "exit";

			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar);
		break;
		//=================== ���� ������ ����. ����� ������ �� �����, ����� ��������� ==================
		case "SeekSpy_Checking":
			dialog.text = "��, � �����������, " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], "�� ������������� ������� ������.", "��� ������������� ������� ����������.");
			link.l1 = RandPhraseSimple("� �����"+ GetSexPhrase("","�") +". ������� �� ������.", "��� ����. ������� �� ������.");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		//����� ��������. ������ � �������� ����������
		case "AscoldMerchant": 
			if(npchar.city == pchar.questTemp.Ascold.MerchantColony && npchar.location.locator == "merchant1")
			{
				dialog.text = "�, "+ GetSexPhrase("��������","��������") +", ��� �� �� �� ������. ���� � ��������� ������� ����� ��� ��������, ��� �� ��� ��������...";
				link.l1 = "���, ��� �� �� ������? ����� ������ �� �����, ��� �����, �� �� �������.";
				link.l1.go = "AscoldMerchant_5";
			}
			else
			{
				//BlackThorn: ����� ������� ����� �������.
				if (!CheckAttribute(npchar, "quest.answer_1") && rand(2)==0)
				{
					npchar.quest.answer_1 = "true";
					npchar.quest.answer_2 = "true";
					if (NationNameGenitive(sti(npchar.nation)) != NationNameGenitive(sti(pchar.questTemp.Ascold.dialogNation)))
					{
						dialog.text = "������, �� �� ������ ����� � ���� �� ������. ���� ����� ������������ ���-�� � �������� "+ NationNameGenitive(sti(pchar.questTemp.Ascold.dialogNation))+".";
						link.l2 = "������� �� ����������.";
						link.l2.go = "exit";
					}
					else if (XI_ConvertString("Colony" + pchar.questTemp.Ascold.MerchantColony) != XI_ConvertString("Colony" + npchar.city))
					{
						dialog.text = "� ����� �������� �� ��������� � ������ ������� �� ������, �� �� ������, � ������� "+ XI_ConvertString("Colony" + pchar.questTemp.Ascold.MerchantColony) +" ����� ��� ��� ������ �����, �� ����������� ����� �� ������� �����.";
					}
					else
					{
						dialog.text = "� ���� ���, �� � ������ ����� ���-�� ��� ��������. ����������� ��������� ���������.";
					}
					link.l2 = "������� �� ����������.";
					link.l2.go = "exit";
				}
				else
				{
					npchar.quest.answer_1 = "true";
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase("������� �����? � �� ����, ��� ����� �����.", "������� ����? �����? ��� ��� �����?", "������� �����? ��� �� ������ �����?"),
                     LinkRandPhrase("����� �� ����������� ���� �� ����?", "����� �� ��������� �������� � ��� ��...", "� ����� �� ���� �������?"),
                     LinkRandPhrase(NPCharSexPhrase(npchar, "� �� ������� ���� �� ���� ������! ���� �� ��� ������?", "� �� �������� ���� �� ���� ������! ���� �� ��� ������?"),
                                    NPCharSexPhrase(npchar, "� ��� ������ ���� ���, ��� ������ ������. ����� ��� �������� �������?", "� ��� ������� ���� ���, ��� ������ ������. ����� ��� �������� �������?"),
                                    "����� ��� �������� �������? ��� ������ �������� � ���������� �����!"),
                     LinkRandPhrase("�����?!! �����?!!", "���� ������ ���!!! �����?!", "����� �� �� ���� ��������� �������?!"), "quest", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� ���������������� ���� �������� ����� ����������� ����� ����������.",
                                               "���, ���������. �����, ����������� ���-������?",
                                               "��� ��� ���������, �����, ���������� ���...",
                                               "���, ����� ���������.", npchar, Dialog.CurrentNode);
            link.l1.go = DialogGoNodeRepeat("AscoldMerchant_2", "AscoldMerchant_3", "AscoldMerchant_4", "", npchar, Dialog.CurrentNode);
				}
			}
		break;
		
		case "AscoldMerchant_2":
			dialog.text = LinkRandPhrase("��-�-��, ������ ����� ��� �� ����. �� ���������� ���������. � ������, �� ����"+ GetSexPhrase("��","��") +", ��� ���������� ����� �������� �����. �� �����, ��� �������� ������ ���������� ���������� ������ ������. ���, ������ ��, �� �����...",
                     NPCharSexPhrase(npchar, "���, �� ���� ������ ������. ���� ���� �� ����������, �� �� ���� ��. � ��������� ������� �������, �� �����, ��� ���������� ���������� �������� ������ ������.", "���, �� ���� ������ ������. ���� ���� �� ����������, �� �� ����� ��. � ��������� ����������, �� �����, ��� ���������� ���������� �������� ������ ������."),
                     NPCharSexPhrase(npchar, "�� �������� ������ ���������. �, �������, ��� � �������. ���� ��� ���� ������, �� ����� �� ������� � ������������...", "�� ��������� ������ ���������. �, �������, ��� � �������. ��� ��� �� ����� � �������� �� ����� ���� ��������..."));
			Link.l1 = "��? �� �����, ��� - ��� ���...";
			Link.l1.go = "exit";
		break;
		
		case "AscoldMerchant_3":
			dialog.text = LinkRandPhrase(NPCharSexPhrase(npchar, "������ � �� �����������. �� ���� � ������ �� � ����� ������ � ����� �� �����. � ���� �� ���������� ���� ����������. � �� ����� ������� � ����������, �� ������ �������...", "������ � �� ������������. �� ���� � ������ �� � ����� ������ � ����� �� �����. � ���� �� ���������� ���� ����������. � �� ����� ������� � ����������, �� ������ �������..."),
                                    "��� � ��������� �����. �� � ������ �������� �� ����. ������ ���������� �� ���� ����� ��������...",
                                    NPCharSexPhrase(npchar, "��� � ����� ������. �-��, ����� �� ��� ���� � ����� ������������ - ����� �� ������ ���������� ���������� ����...", "� ��� ����� ������. � �����, ��� ���� �� ���� �������..."));
			Link.l1 = "�����!! �������� ���� ��������. �� �� �����...";
			Link.l1.go = "exit";
		break;
		
		case "AscoldMerchant_4":
			dialog.text = LinkRandPhrase(NPCharSexPhrase(npchar, "������ �� ����������, ������ ������ ������!!! �� ����� � ���������� ���������� �� � �����, �� � ����������� ����!", "������ �� ����������, ������ ������ ������!!! �� ������ � ���������� ���������� �� � �����, �� � ����������� ����!"),
                                    NPCharSexPhrase(npchar, "��������� ������ �� ���������� - ������� ����������� ������ � �� ����� �, �������, �� �����.", "��������� ������ �� ���������� - ������� ����������� ������ � �� ������ �, �������, �� �����. � ������ ���������� � ���������� �������� - ���� ������..."),
                                    NPCharSexPhrase(npchar, "����������?!! ��������, � �� ���� ���������! ������� �� �������, ��� � �����������, ������������ ��� ������, � �� ����������?!!", "����������?!! ����������, � �� ��� ���������� ���� �������! ������� �� �������, ��� � �����������, ������������ ��� ������, � �� ����������?!!"));
			Link.l1 = NPCharSexPhrase(npchar, "�� �� �� ��������� ���. ���������, �� ����� - ��� �� �����...", "�� �� �� ��������� ���. ���������, �� ������ - ��� �� ������...");
			Link.l1.go = "exit";
		break;

		case "AscoldMerchant_5":
			dialog.text = "��-�� � ���... � �� ������ �����. ���������� �� ���� ������� ����������� �� ����� ����� �����. � �� �� ����� � �������. ���� � ����� �� ���� ������� ���� ������ �������?";
			link.l1 = "�-��... � �����, ���������� ����? ����� �����. ���� ������� ����� ������, � � ��� ��� ������� ������� ����� �� ����.";
			link.l1.go = "AscoldMerchant_6";
		break;
		
		case "AscoldMerchant_6":
			dialog.text = "�����, ��������? � �� �������������� �� ������ ���� ��������?";
			link.l1 = "�� ���, �� ������... �������� �������� ��������� ��������. ����� �� ��� ���?!";
			link.l1.go = "AscoldMerchant_7";
		break;
		
		case "AscoldMerchant_7":
			dialog.text = "������������� �� ������... ��� �, ������ � ���� �������. ������ �� ������� ��������� ����. ����, ��� � ���� ����� �� ���� � �� �������� ���� ���������� ����.";
			link.l1 = "��, ��� � ��� �������...";
			link.l1.go = "AscoldMerchant_8";
		break;
		
		case "AscoldMerchant_8":
			dialog.text = "� ���� ������ �����.";
			if (sti(pchar.money) >= 1000)
			{
				Link.l1 = "�������, ������, �� ��� � �� ������������. ���, �����.";
    		    Link.l1.go = "exit";
    		    pchar.questTemp.Ascold = "PowderWasSeek";
    		    AddMoneyToCharacter(pchar, -1000);
    		    GiveItem2Character(Pchar,"Powder_mummie");			
			}
			else
			{
				link.l1 = "��� ����! � ���� � ����� ��� �������. ������ ������ � ����� � ����. ������, �� ������, ���� � ������ ����...";
				link.l1.go = "exit";
			}
		break;
		
// ======================== ���� ��� angry ===============>>>>>>>>>>>>>>>
		case "AngryQuest_AscoldMerchant":
            Dialog.text = RandPhraseSimple("� �� ���� � ����� ������ ����� ����.", "������ � ���� ������ ��������� �� ����.");
			Link.l1 = RandPhraseSimple("��, ��� ������. �� ����� ������, ������ ���� �� �����.", "�������� ������...");
		    Link.l1.go = "AngryExitAgain";
		    //===>> ����� ��������, ������ ������� �����.
            if (pchar.questTemp.Ascold == "Seek_powder" && npchar.city == pchar.questTemp.Ascold.MerchantColony && npchar.location.locator == "merchant1")
            {
                Dialog.text =  "�� ����� ���������"+ GetSexPhrase("","�") +", ������ ���� ������� ���� ������������� �����.";
    			Link.l1 = "������ ���. � ������ � ���� �����, ���� �� �� � ���� �� ����� ����. � �� �����, ��� ��������� ����� ����.";
    		    Link.l1.go = "AngStep_1";
            }
            if (CheckAttribute(npchar, "angry.terms")) //������� �� ������ �������� ����� 10 ����.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms) && pchar.questTemp.Ascold != "Seek_powder")
                {
         			Dialog.text = NPCharSexPhrase(npchar, "����� ����������� �� ��, ��� �� �� ������ ���� �������� ��������� ���������. �������, � ����� ����� ���� � �����.", "����� ������� �� ��, ��� �� �� ������ ���������� �� ��� � ����� �������� �������� ���������. �������, � ������ ��������� � �����.");
        			Link.l1 = RandPhraseSimple("�������!", "�����������!");
        			Link.l1.go = "First time";
        			CharacterDelAngry(npchar);
                }
            }
    	break;
////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

		case "AngStep_1":
            Dialog.text = "����, �� �� ��� ����, ���"+ GetSexPhrase("","�") +" ���������. �� ���� ������. ������ �����, � �� ����.";
            if (sti(pchar.money) >= 1000)
            {
    			Link.l1 = "������, ��� ���� ������.";
    		    Link.l1.go = "AngryExitAgain";
    		    pchar.questTemp.Ascold = "PowderWasSeek";
    		    CharacterDelAngry(npchar);
    		    AddMoneyToCharacter(pchar, -1000);
    		    GiveItem2Character(Pchar,"Powder_mummie");
            }
            else
            {
    			Link.l1 = "������ � ���� � ����� ��� ����� �����. ��� ������ ������ - ����� �� ������ ����.";
    		    Link.l1.go = "AngryExitAgain";
            }
    	break;
// <<<<<<<<<<<<============= ���� ��� angry =============================
	}
}
