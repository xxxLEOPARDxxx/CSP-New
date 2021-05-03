// �������
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Tichingitu_11":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "�������! ��� ��� ����! ������ � ������ ������� � ������� ���� ������, ������� �������... ���, �����. ������� ��� ���������� � ������ �������� ������ �������. ��� ������ ����� �� ���� ����������� - ��� �� �������. ����� ��� �� �������� �� ������ ����������, ��-��!";
			link.l1 = "��� �� �����, �������. ������ ����� �������� - ������ ����.";
			npchar.quest.Tichingitu = "paid"
			link.l1.go = "Tichingitu_12";
		break;
		
		if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "ascold")
		{
			dialog.text = "��, ��� �������? ������"+GetSexPhrase("","�")+" ���������� �� ��� ��������� ������?";
			link.l1 = "������"+GetSexPhrase("","�")+"... ������� � ����"+GetSexPhrase("��","��")+" ����� � ����.";
			link.l1.go = "Tichingitu_7";
			if (!CheckAttribute(npchar, "quest.Tichingitu")) 
			{
				npchar.quest.Tichingitu = true;
				break;
			}
		}
		if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "money")
		{
			dialog.text = "�, ��� ����� ��! �� ���, ����"+GetSexPhrase("��","����")+" ������ �� �������?";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "��. ���, �����.";
				link.l1.go = "Tichingitu_11";
			}
			if (CheckAttribute(npchar, "quest.Tichingitu") && npchar.quest.Tichingitu != "paid") 
			{
				link.l2 = "���, � ��� �� ������"+GetSexPhrase("","�")+" ��������� �����.";
				link.l2.go = "exit";
				break;
			}
		}
		// ----------------------------------- ������ ������ - ������ �������
		case "First time":
            if (npchar.quest.meeting == "0")
            {
            	dialog.text = "�����������. ���� ����� �������. � � ��� ���� ����� �������������?";
        		link.l1 = "���� ����� " + GetFullName(pchar) + ".";
        		link.l1.go = "Step_1";
                npchar.quest.meeting = "1";
            }
            else
            {
            	dialog.text = "� �� �����, ����� ����, ������� � �� ����, ��������� ����.";
        		link.l1 = "�����"+ GetSexPhrase("","�") +", ��� �����...";
        		link.l1.go = "exit";
        		link.l2 = "������ ��������, ������?";
        		link.l2.go = "Step_3";
                NextDiag.TempNode = "First time";
            }
		break;

 		case "Step_1":
        	dialog.text = "��� �� � ��� �� �����������?";
    		link.l1 = "� - �����.";
    		link.l1.go = "Step_2";
		break;

 		case "Step_2":
        	dialog.text = "������, �����...";
    		link.l1 = "��?";
    		link.l1.go = "First time";
		break;

 		case "Step_3":
            if (npchar.quest.meeting == "1")
            {
            	dialog.text = "�-�-�, �� �� �� ������ �����, � ������� �����... ���"+ GetSexPhrase("��","��") +" ��� ������!";
        		link.l1 = "...";
        		npchar.quest.meeting = "2";
            }
            else
            {
            	dialog.text = RandPhraseSimple("����� ������� � ���� ����� ������� ������ ��������?! �������� ����� ����...", "����� � ������� �����"+ GetSexPhrase("","��") +"... ���� ��������� ����.");
        		link.l1 = RandPhraseSimple("�� � ���� ������...", "���������, ��� ���� ������� �� ���� �� ���� ���...");
            }
            link.l1.go = "Step_4";
		break;

 		case "Step_4":
            DoReloadCharacterToLocation("BasTer_town", "reload", "houseSp1");
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

 		case "HaveRecomendation":
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
            if (npchar.quest.meeting == "0")
            {
            	dialog.text = "�����������. ���� ����� �������. � � ��� ���� �����...";
				link.l1 = "���� ����� " + GetFullName(pchar) + ". � ������� ���� � ���� " + GetFullName(sld) + ", ������ ��������, ��� ��������� �� " + XI_ConvertString("Colony" + sld.City + "Dat") + ".";
                npchar.quest.meeting = "1";
            }
            else
            {
            	dialog.text = "����� �� ��������� "+ GetSexPhrase("�������� ��� ������� ������","��������� ���� ������� �������-������") +". ��� ���� ����� �� ���� ���?";
        		link.l1 = "�� ���� ��� ���� ������� � ���� " + GetFullName(sld) + ", ������ ��������, ��� ��������� �� " + XI_ConvertString("Colony" + sld.City + "Dat") + ".";
            }
            link.l1.go = "Step_5";
		break;
		
 		case "Step_5":
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
        	dialog.text = "���, ����� �������� � ����. ��� �, �������, ������, ����� ������ �����.\n"+
                          "(������������) � ���� ����� ������� ����� - ������� �������. ���� ��������� - ���� �������, �� �� ��������� � ������, ��� - ������ ����.\n"+
                          "� �����, ������, ����� � ���� ���� �� ���?";
    		link.l1 = sld.lastname + " ������, ��� �� ����� ������� �����. � ���� �� ����.";
    		link.l1.go = "Step_6";
		break;

 		case "Step_6":
        	dialog.text = "����� ������. ����� 30000 �� ���� �������.";
    		link.l1 = "������� ����. �� �����.";
            if (CheckCharacterItem(pchar, "Powder_mummie"))
            {
        		link.l1.go = "Step_7";
        		TakeItemFromCharacter(pchar, "Powder_mummie");
        		AddMoneyToCharacter(pchar, 30000);
            }
            else
            {
        		link.l1.go = "No_Powder";
            }
		break;

 		case "No_Powder":
        	dialog.text = "��, "+ GetSexPhrase("����","���������") +", ������! ��� � ���� �������. �����, ������� �������� ���� ��������, � �� ������� ������.\n"+
                          "��� ���, ���"+ GetSexPhrase("��","��") +" ��� ������!";
    		link.l1 = "�� �� ���! � �� �������"+ GetSexPhrase("","�") +"! � ���� � � ������ �� ����...";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_7":
        	dialog.text = "���� �������, ������ ����� � ������...";
    		link.l1 = "��, ���� � ������ �� ����. �� ��� ����� ����� ���, ����� ���� ��� �����? ������� ������ �����"+ GetSexPhrase("","�") +" ��� ����, � ������ �� ����"+ GetSexPhrase("","��") +". ��������� ����������� � ������� ������.";
    		link.l1.go = "Step_8";
		break;

 		case "Step_8":
        	dialog.text = "��, ��� ��� �������. ���� ������� � �������� �������� ������ �������� ���������� ��� ��������� � ������ ������ ���� �� �� ������.\n"+
                          "� �������� ����� � �������� ��� ����������� ����. � ��������, ������� ������. �� �� ������ ���������� ������ ���� � ��� ����������.\n"+
                          "� �� ������ ����� ������, ������� � ���������� ����� ��� �� �����, �� ������������ ����� � ����� �������.";
    		link.l1 = "�������.";
    		link.l1.go = "Step_9";
		break;

 		case "Step_9":
        	dialog.text = "������, ��� ����� ����� ����� � �� � ����� �����������, �� ��������� ���� ��� ������.\n"+
                          "� ���� ��� ��� �������� ����� ����� �� ��� ��������� ���������.";
    		link.l1 = "��������, �������. � ������"+ GetSexPhrase("��","��") +".";
    		link.l1.go = "Step_10";
    		link.l2 = "���, �� ��������. � ���� ������ ��� �� �����.";
    		link.l2.go = "No_Work";
		break;

 		case "No_Work":
        	dialog.text = "��? � �� �����, ����� ��� ����������, ����� � ����� ����� �� �����. ������� - ���"+ GetSexPhrase("��","��") +" ��� �� ����� ����!";
    		link.l1 = "��, ��! �� ��� �������?!!";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
    		group_DeleteGroup("Ascold_Spa_Attack");
    		DeleteAttribute(PChar, "questTemp.Ascold.Ship");
		break;

 		case "Step_10":
        	dialog.text = "������. ������ ������, ��� ��� ����� ���������.\n"+
                          "��� ����� ��������� �������, ���������� ���� ����� � �����, �������������� ����� ������� ������� � �������������� ��� ����.";
    		link.l1 = "�����"+ GetSexPhrase("","�") +". ��� �, ���� �������� �� ��������. ������ ��� ��� ���� - ���� � ����.";
    		link.l1.go = "exit";
			if (!CheckAttribute(pchar, "questTemp.Tichingitu") && !CheckAttribute(npchar, "quest.Tichingitu"))
			{
				link.l2 = "������� ���, ���� ��������� ���-�� ���, �� ��� ��?";
				link.l2.go = "Tichingitu_1";
			}
    	    pchar.questTemp.Ascold = "SeekThreeObject";
    	    NextDiag.TempNode = "ResultOfSeek";
            AddQuestRecord("Ascold", "3");
	    AddQuestUserData("Ascold", "sSex", GetSexPhrase("��","���"));
		break;
		
		case "Tichingitu_1":
			dialog.text = "� ���� �� ��������� ������� �����. ���-�, ��������. �� ���� �� ��� ��������� � ��� ��������� ��������. ���� ������ ������ ��������...";
			link.l1 = "��������, ���� ������ ����� ����, ���� ���� ����. ��� ������?";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "�� � ���� ������� � �������� ��. ���� ���� ������. �� ������ ��� ������� �����, ��������� ���� ��, ��� ���������. �� ������ ���� �������� ��� � ��� ���� � ����������, ���� ��� �� �������� ���������!";
			link.l1 = "� �� ��� �� ���������?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "���� ���, ����� ������ � ������������ � �������. � �� ��� ��� �� ������. �����, ��� �� ������ �� ��������. � ������� ����� ��������, ����� ��������� ������, �� ���������� � ���� ��� � ���� �������.";
			link.l1 = "������ ����� ���������. ����� ������� ����...";
			link.l1.go = "Tichingitu_4";
		break;

		case "Tichingitu_4":
			dialog.text = "��� ��� ��� ����� - ��� �� ��. ��������� �� ���� - �������������, �� ��� ����� ����� �������\n�� ��� �� �������! �� ��� �� �� ���� �� ����: � ������ ���, ����� ������� ������� � ���� ����������. �����, ��� ����� �������. � ������� ���!";
			link.l1 = "�� �������, ��� �����������?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "����� ����. �� ��� �� �������� ���������� ���. ����� ������ �� ������ �������������. � ��� ������������ ������ ������. �� � ���� �����... �����, �������������, ������ ������� �� ��� � ������� � �������� �� ��������\n������ �� �����-�� ������ ��������, ������ ����. ���� � ������, ������������... ������ ������� � ���� �������� � ���������� �� ����� ���� ��������, ���� ��� ���������, ���� �� ��� ���.";
			link.l1 = "��... �����, � �������.";
			link.l1.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "�������-�������, ���������� �� ������� ������� ��������...";
			link.l1 = "����� �������.";
			link.l1.go = "exit";
			pchar.questTemp.Tichingitu = "true";
			AddDialogExitQuestFunction("SetTichingituJail");
			SetFunctionTimerCondition("FreeTichingituOver", 0, 0, 10, false);
		break;
		
		case "Tichingitu_7":
			dialog.text = "��, ��� ���?";
			link.l1 = "�������, � �������"+GetSexPhrase("","�")+" � ���� ��������. � � ����"+GetSexPhrase("��","��")+" ������� �� ����. ���� ���������� ������ ����� ����...";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			dialog.text = "��� ����� ������. ��� �� ���, ��������� ��� ������?";
			link.l1 = "��� ���� ������� ����������, � ��� �� ����� � ���������� �� �������...";
			link.l1.go = "Tichingitu_9";
		break;
		
		case "Tichingitu_9":
			dialog.text = "��� �� ����� ����, �� �����, �� ������ ��� ��������. ���� ������� ����������� � 10000 ��������.";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "������, ��� ������.";
				link.l1.go = "Tichingitu_11";
			}		
			link.l2 = "�������, ����� ����� �������.";
			link.l2.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "� ����������! ���� ����� ������ ��� ��� �� �����������...";
			link.l1 = "����� � ��������. �� ��������!";
			link.l1.go = "exit";
			pchar.questTemp.Tichingitu = "money";
		break;
		
		case "Tichingitu_12":
			GiveItem2Character(pchar, "letter_A");
			PlaySound("interface\important_item.wav");
			dialog.text = "��� ������� ������. � ���� �� �������� ������ ��� ����������? ������� ������� �� �������? � ����� ��� ������ � ����������, ���� ������ ������������ ����� �� �������� �� ��������...";
			link.l1 = "��� � ����, ��������.";
			link.l1.go = "exit_vodka";
			pchar.questTemp.Tichingitu = "pay";
		break;
		
		case "exit_vodka":
			LAi_MethodDelay("FrameAscoldVodka",0.1);
			DialogExit();
		break;

 		case "ResultOfSeek":
        	dialog.text = "������� ��������� ��������� ����������? ��� ����� ��� ��� �����, �� ����� ������ �� �������.";
    		link.l1 = "��� ���, �� � ���� ���������.";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "ResultOfSeek";
            if (CheckCharacterItem(pchar, "indian19") && CheckCharacterItem(pchar, "indian20") && CheckCharacterItem(pchar, "indian21"))
            {
                link.l2 = "��, ��������"+ GetSexPhrase("","�") +". � ��� ��� ������?";
                link.l2.go = "Step_11";
            }
		break;

 		case "Step_11":
        	dialog.text = "���, �� ������ ������� � ����� �������� �� 30000. ����� - 90000 �����. ������"+ GetSexPhrase("��","��") +"?";
            link.l1 = "���� ���������� ����. �� �����.";
            if (pchar.questTemp.Ascold == "SoughtThreeObject")
            {
               link.l1 = "���� �� �� ����, �������, ������� � ��������"+ GetSexPhrase("","�") +" �� ��� ���������... �� � �������, ��� ��������� �� ���� �������� ���� ����� - ������ ���������, �� � ��� ����������� ���� � ����� ��� ������... � ������"+ GetSexPhrase("��","��") +".";
            }
    		link.l1.go = "Step_12";
            link.l2 = "���, ����� ������ �����.";
    		link.l2.go = "WantMoreMoney";
		break;

 		case "WantMoreMoney":
        	dialog.text = "��� ��� ��. ������ � � ���� �������� - �� ����� ������ ���� "+ GetSexPhrase("������ �������","������ �����") +". ����� ���� ��� ���� �����, � �� �� ����. � ���� ����� ����� �� �����.\n"+
                          "���"+ GetSexPhrase("��","��") +" ���!";
        	link.l1 = "��, �������, �������! �� �� ���������� ����, ����� �����������, �����������...";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_12":
        	dialog.text = "����, ��� ���� 90000, � �������� ������ ����.";
        	link.l1 = "�������.";
    		link.l1.go = "Step_13";
		break;

 		case "Step_13":
        	dialog.text = "������, ����� �������, ������� �� ��� ����� �����-������. �����, ��� ��������� �����������.";
    		link.l1 = "���� ��������� ����� - ���������� ������ ����. ��������� ������������ �� �������, � ������� ���������.";
    		link.l1.go = "exit";
    		TakeItemFromCharacter(pchar, "indian19");
    		TakeItemFromCharacter(pchar, "indian20");
    		TakeItemFromCharacter(pchar, "indian21");
    		AddMoneyToCharacter(pchar, 90000);
			pchar.questTemp.Ascold = "TakenThreeObject";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		NextDiag.TempNode = "WalkTwoMounth";
    		AddQuestRecord("Ascold", "4");
		break;

		case "WalkTwoMounth":
		    if (GetQuestPastDayParam("questTemp.Ascold") > 62)
		    {
            	dialog.text = "�-�-�, �������-��! � � ���� ���. ��� ����� ���� ������, " + GetFullName(pchar) + ".";
            	link.l1 = "��� ���� ����� ��������� �� ���� ���?";
        		link.l1.go = "Step_14";
		    }
            else
            {
            	dialog.text = "�-�-�, ���� � ����?! "+ GetSexPhrase("��� ����","��� �������") +" " + GetFullName(pchar) + ", ��� ������. ���� �� �� ������ ������, �� ���������� ���� ����� �� ����, ��� ���� ��� ����� � �������. � �� ���������� ���-������ �����.";
            	link.l1 = "������, �������. ���� � ���� ����� - �������.";
        		link.l1.go = "exit";
        		NextDiag.TempNode = "WalkTwoMounth";
            }
		break;
		
 		case "Step_14":
        	dialog.text = "�� ������, �� ���� ��� ���� �� � �������, ������ ����������� �����.";
        	link.l1 = "�-�-�, ����� �� ����... ��� ����� ������� �����! �����, ������� ���� ��������.";
    		link.l1.go = "Step_15";
		break;

 		case "Step_15":
        	dialog.text = "�������� ���������. �������, ��� ��� ����� ��� ����������� ������������ ��������������� �������� � ������������ �� ���������� ��������, ����� ����������� ������ ��������� ���� ����� ��������� ��������.\n"+
                          "���� � ���, ��� ��� ����� ��������, ������ �� ��������, �������� �������� ���� �� �������� ���������� ������. � ������ ������� ������� ����� � �������� ���������, ������� ��� ����� �������. � ������������ �������� � ������ ����. ��� ������ ��������, � � � ���� �� ��������.\n"+
                          "� �����, ��� ������� ������, ��� � ������ ������� ������� ������ ��������� ������ ������� ���������� �� ��� ���� ��������. � ���� �������� ��� ��������, �������, ��� ��� ������� �� ��������, �� ���� ���-������.\n"+
                          "� ���, ���, ����� ������... � ���� �������� ����������� ����� ���������� ��������� ���������� �����. �� �� ������� ����� ����� ��������� �� ��� ���������.";
        	link.l1 = "� �����-�� �����? �� ��� �������. ��� � ���� �����. � �� ����� ������, ��� ����� ����� ����?";
    		link.l1.go = "Step_16";
        	link.l2 = "������, �� �� ��������, �� ������ ����� �� ����. ������� ���.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_16":
        	dialog.text = "��, �����. ������� ��� ��� ������ �� ��������������� ������... ����� ����������� � �����, ������� ��� ���������, ��� � �����.";
        	link.l1 = "�������. ��, � ���������. ��� �������, ��� ���� � � �������.";
    		link.l1.go = "exit";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		NextDiag.TempNode = "AfterManowarsBattle";
    		pchar.questTemp.Ascold = "ToHavanna";
    		AddQuestRecord("Ascold", "5");
		break;
		
 		case "AfterManowarsBattle":
        	dialog.text = "��������"+ GetSexPhrase("","�") +" ���-������, ��������"+ GetSexPhrase("","�") +" ���������?";
        	link.l1 = "���� ���, �� � ���� ���������.";
    		link.l1.go = "exit";
        	link.l2 = "� ���� ��� ������ ������� ��������� ������ ����������. ������.";
    		link.l2.go = "No_Work";
            if (pchar.questTemp.Ascold == "SeekInformatorHavanna")
            {
             	link.l1 = "������, �� � ������� ��� �������� ���-�� ��� ������ ��� ������ �����, ������� ���� ������ � ��� ������, ��� � ����������.";
        		link.l1.go = "Step_17";
            }
            if (pchar.questTemp.Ascold == "ReciveInformationManowar")
            {
             	link.l1 = "�������! � ���"+ GetSexPhrase("��","��") +" ������ �����-�����������! ��� ��������� ������ �� ����� �������� �������� � ��������. ������, �� ��������� ���� ������...";
        		link.l1.go = "Step_20";
            }
            if (pchar.questTemp.Ascold == "ILookedThisAss" && !CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "�������! ��� ��������� ������� �� ����� �������� � ��������� �� �����!!!";
        		link.l1.go = "Step_24";
            }
            if (pchar.questTemp.Ascold == "ILookedThisAss" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "�������! ������ � ����, �� ��� ��� �������� ������������� �������.";
        		link.l1.go = "Step_25";
            }
            if (pchar.questTemp.Ascold == "2ILookedThisAss" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "�������! ������ � ����, �� ��� ��� �������� ������������� �������.";
        		link.l1.go = "Step_25";
            }
            if (pchar.questTemp.Ascold == "Ascold_ManowarsDead" && !CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "� �������"+ GetSexPhrase("","�") +" ��� �������, �� ������������ ������ ��� ����� ��� � �� �������.";
        		link.l1.go = "NoFoundList";
            }
    		if (CheckCharacterItem(pchar, "ShipsJournal") && pchar.questTemp.Ascold == "ILookedThisAss")
    		{
            	link.l1 = "��, ���� ���� ������! � ����"+ GetSexPhrase("��","��") +" ���� ������ ���, �� �����"+ GetSexPhrase("","�") +" ��� ���� ���� ������. ��� ��.";
        		link.l1.go = "Step_26";
    		}
    		if (CheckCharacterItem(pchar, "ShipsJournal") && pchar.questTemp.Ascold == "2ILookedThisAss")
    		{
            	link.l1 = "��, ���� ���� ������! � ����"+ GetSexPhrase("��","��") +" ���� ������ ���, �� �����"+ GetSexPhrase("","�") +" ��� ���� ���� ������. ��� ��.";
        		link.l1.go = "Step_26";
    		}
            if (CheckCharacterItem(pchar, "ShipsJournal") && pchar.questTemp.Ascold == "Ascold_ManowarsDead")
            {
             	link.l1 = "� ���������"+ GetSexPhrase("","�") +" ��������� �������, ����������� ������ ���� � ����.";
        		link.l1.go = "ManowarGoodWork";
            }
            if (pchar.questTemp.Ascold == "Ascold_ManowarsDead" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "������� � ��������"+ GetSexPhrase("","�") +" �� ���!";
        		link.l1.go = "ManowarGoodWork";
            }
			if (pchar.questTemp.Ascold == "Ascold_ManowarsNoDead")
            {
             	link.l1 = "��������, ��� �� ������� �������� ��������� �������. � � ����� ������� ���������� ��� ���������� �� �������.";
        		link.l1.go = "ManowarNoGoodWork";
            }
		break;

 		case "Step_17":
        	dialog.text = "� ���?";
        	link.l1 = "��� ����� ���� ������, ���� � ���, ��� ��������"+ GetSexPhrase("��","���") +" � ��������� � ������. ����� �� ���� ���������, ���� ���� �������, �� ������� ��������� ��������� ���������. ����� ���� ���� �������.";
    		link.l1.go = "Step_18";
		break;

 		case "Step_18":
        	dialog.text = "���, �� ������. � �� ��������� ��������� �� ���� ������� � ����� ������.";
        	link.l1 = "�� � �� �������� � ����� ���������, � �����-�� ������!!!";
    		link.l1.go = "Step_19";
		break;

 		case "Step_19":
        	dialog.text = "��� ���, �� �������� ��������������. �� ��� ������ �� ����������.";
        	link.l1 = "�� ��� �, ������� ����, ���� �������...";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "2SeekInformatorHavanna";
    		NextDiag.TempNode = "AfterManowarsBattle";
		break;

 		case "Step_20":
        	dialog.text = "���-������ ��������� � ������� ��� ������ ��������������... � ���, �����"+ GetSexPhrase("","�") +" ���-����?";
        	link.l1 = "��, ������� ����� ���� ����� �������, ��� ����� ������, ��������� ���� � ������ ��� �������� ����� ��c�������. � � ����� ����� �� ����� ������ ����� ����������� ��������� �������.";
    		link.l1.go = "Step_21";
		break;

 		case "Step_21":
        	dialog.text = "�����?";
        	link.l1 = "�������, ��������� ��������� ���� � ����� �� ���� ���� � �������.";
    		link.l1.go = "Step_22";
		break;

 		case "Step_22":
        	dialog.text = "��������� �������. ����� � ���� � ���� ������� - �� ����"+ GetSexPhrase("��","��") +" ���������� ���� ��������, ����������� ���� ����� �������. ��� ������� ������ ����� �� ���, � ���� ���������� � ����� ������ ���� ����������.\n"+
                          "� ��� ����� ���������� ������ ��������.";
        	link.l1 = "� �����"+ GetSexPhrase("","�") +". ���� ���������� ���� ������.";
    		link.l1.go = "Step_23";
        	link.l2 = "�� ������� �� ����� �� ������ �� ����, ��������? ����� ������ � ������ �����.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_23":
        	dialog.text = "��� ������, ���� �� ����, ��� ���� ����������� �� ������...";
        	link.l1 = "����� ������������, ���� �������.";
    		link.l1.go = "exit";
    		AddQuestRecord("Ascold", "8");
    		pchar.questTemp.Ascold = "IMustKillAll";
    		NextDiag.TempNode = "AfterManowarsBattle";
		break;

 		case "Step_24":
        	dialog.text = "����� ������, ��� ������ ���� ��������. �� ������ ��� ������? �������� ���� �������� � ������� ��� ���� ������ ����������� ������.";
        	link.l1 = "��, �������. � ������ ���. ����������� ������ ����� � ���� � ������� ����� ����������.";
    		link.l1.go = "Step_25";
            link.l2 = "��� ��� ����. ��� ������!";
    		link.l2.go = "No_Work";
		break;

 		case "Step_25":
        	dialog.text = "��, ��� ��� �� ������! ���, ���������.";
        	link.l1 = "��� ���.";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "2ILookedThisAss";
    		NextDiag.TempNode = "AfterManowarsBattle";
		break;

 		case "NoFoundList":
        	dialog.text = "� ��� ���� ��, ��������� � �������� ��������� ���������� ��������, � �����-�� ������ ����� �� ����"+ GetSexPhrase("","��") +". � ������ ��������� ������ � ���� �� ����.\n"+
                      "��� ���, ���"+ GetSexPhrase("��","��") +" ��� ������!";
    		link.l1 = "�� ��, � ��� ����� �����, ��� ��� �������� �������� ��-�� ����...";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_26":
        	dialog.text = "������ ��� ������, �� �������. �� ��� �����, ����� �� �������"+ GetSexPhrase("","�") +" ��� ������� ��������, � ����� �������"+ GetSexPhrase("","�") +" ����. ����� �� ������ ���� ������ �����.";
        	link.l1 = "������ ��� ������� �������, ������� �� ���� ��������������...";
    		link.l1.go = "Step_27";
            link.l2 = "��, �������, �������, ���-�� ��� �� ������� ������ ������ ��������.";
    		link.l2.go = "No_Work";
            link.l3 = "�������, ��� ����� ������. � ���� ��������"+ GetSexPhrase("","�") +" ���� ������, �����"+ GetSexPhrase("","�") +" �� �������� �������.";
    		link.l3.go = "WantMoreMoney";
            BackItemDescribe("ShipsJournal");
            TakeItemFromCharacter(pchar, "ShipsJournal");
            pchar.questTemp.Ascold.list = 1;
		break;

 		case "Step_27":
        	dialog.text = "� ��� ����� �� ����� �������, ���� �� �� �������. ������� � ������� ���� ������.";
        	link.l1 = "������, � �������� ��������. �������, � ���� �����"+ GetSexPhrase("��","���") +" �������� �������.";
    		link.l1.go = "exit";
            AddQuestRecord("Ascold", "10");
	    AddQuestUserData("Ascold", "sSex", GetSexPhrase("","�"));
		break;

 		case "ManowarGoodWork":
        	dialog.text = "�� �� ���������"+ GetSexPhrase("","�") +" �������� �� ����� �������. ��� �������, ������� ������ � �����, ������ ���� ����������.";
        	link.l1 = "������, ������� ������.";
    		link.l1.go = "exit";
            link.l2 = "��, �������, �������, ���-�� ��� ������ �� ������� ������ ������ ��������.";
    		link.l2.go = "Step_28";
    		NextDiag.TempNode = "ManowarGoodWork";
		break;

		case "ManowarNoGoodWork":
        	dialog.text = "� ��� ���� ��! � ��� ������� �������"+ GetSexPhrase("��","���") +". � ������ ��������� ������ � ���� �� ����.\n"+
                      "��� ���, ���"+ GetSexPhrase("��","��") +" ��� ������!";
    		link.l1 = "�� ��, � ��� ����� �����, ��� ��� �������� �������� ��-�� ����...";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_28":
        	dialog.text = "�� ���, ������� ���� �� �������� ����?";
        	link.l1 = "���, �����, ������ ��� �� ���� ������.";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
    		pchar.quest.Ascold_FightNearTemple.over = "yes";
		break;

 		case "Ascold_KilledTemple":
        	dialog.text = "��� �� � ������"+ GetSexPhrase("��","���") +". ��� ���������?";
        	link.l1 = "�������, ��������� ���������� � ����� ����� ��������� ����������. �� ��� ����� �� ������� ����� ������ ����������� ������.";
    		link.l1.go = "NoFoundList";
            if (CheckCharacterItem(pchar, "ShipsJournal") || CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
            	link.l1 = "�������, ��������� ���������� � ����� ����� ��������� ����������.";
        		link.l1.go = "Step_29";
                BackItemDescribe("ShipsJournal");
                TakeItemFromCharacter(pchar, "ShipsJournal");
                DeleteAttribute(PChar, "questTemp.Ascold.List");
            }
		break;
		
 		case "Step_29":
        	dialog.text = "�������! � ����, ��� �� ���� ����� ����������.";
        	link.l1 = "� �����"+ GetSexPhrase("","�") +" �� ���������� � ��������������.";
    		link.l1.go = "Step_30";
		break;

 		case "Step_30":
        	dialog.text = "��, �������... ��������, ��� ����� ���� ���������, � ��� �� ������� ������ �� �������. ���� ����� ������� ���������.";
        	link.l1 = "�-��, ���� ���... ���� �� ��, ��� ��� �������� ��������...";
    		link.l1.go = "Step_31";
		break;

 		case "Step_31":
        	dialog.text = "�������, �� � ���� ������ ��� �����. ��� ����� ��������� �� ������� ����������� ������, ������� �� ��������"+ GetSexPhrase("","�") +". �������, ��� ������� ����. ���������� �� ��� ����� �� �������...";
        	link.l1 = "�� ��� �, ���� �� ������. ���� �������� � ���� �� ���� �����������.";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Mummie_begin";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		AddQuestRecord("Ascold", "12");
	        AddQuestUserData("Ascold", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Ascold", "sSex1", GetSexPhrase("��","���"));
		break;

 		case "Mummie_begin":
        	dialog.text = "��� ������ ����, "+ GetFullName(pchar) + ". �� �������� ���� � ���� ���. ������ ��� �� ������...";
        	link.l1 = "����... �� ��� �, ��������.";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Mummie_begin";
		    if (GetQuestPastDayParam("questTemp.Ascold") > 40)
            {
            	dialog.text = "�-�-�, ���� � ����, "+ GetSexPhrase("��� ����","��� �������") +" "+ GetFullName(pchar) + "...";
            	link.l1 = "���� �������?";
        		link.l1.go = "Step_31A";
            }
		break;

 		case "Step_31A":
        	dialog.text = "����, �� ��� ���� �� ����������. ���� � ���, ��� � ������� �������� �� �� �� �������.";
        	link.l1 = "�� ���, ������-�� �� �������?";
    		link.l1.go = "Step_32";
		break;

 		case "Step_32":
        	dialog.text = "������� �������. �� ����������� ����� ������ ��� �� ��������������. ����������� ������ �������� �����������, � ����������� ��������� ����������, �� ��� ������, ������������ ��������� �� ����������� ����� � �����.";
        	link.l1 = "��� ��� ��...";
    		link.l1.go = "Step_33";
        break;

        case "Step_33":
        	dialog.text = "� ���� ����, ������ ������, ��� ����. �� ����� ������������. � ���� � ���� ���� ����.";
        	link.l1 = "� ��� �� ���� ���?";
    		link.l1.go = "Step_34";
            link.l2 = "������, ��� �� �� �� ����� ����� ����-������ ��������.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_34":
        	dialog.text = "�� �� ������ �������� � ������ �����-�� ��������� ���������, � ������� ����� �� ���������, ��� �� ����� ������� ���� ��������� �����-�� �������� ��������� ����.\n"+
                          "���� ����������� �������� ������ ��� ������� � ����������� ����� ��� �����, ���� ��� ������������� ����������.";
        	link.l1 = "������, ������. �� ���� ��� ��� ���� ����� �������?";
    		link.l1.go = "Step_35";
        	link.l2 = "������, �������, � ���, �����"+ GetSexPhrase("","�") +" �� ������������"+ GetSexPhrase("�","�����") +"? � ������� ������ �� ���������.";
    		link.l2.go = "No_Work";
		break;
		
 		case "Step_35":
        	dialog.text = "���� �� ����������. ��� ������ ��������� �������, ��� ��� � ������ ������ ������ �����.";
        	link.l1 = "������, � �����"+ GetSexPhrase("","�") +". ���� ������.";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Seek_Grave";
    		AddQuestRecord("Ascold", "13");
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "Ascold_SeekGrave";
		break;

 		case "Seek_Grave":
        	dialog.text = "���"+ GetSexPhrase("��","��") +" ���-������?";
        	link.l1 = "���� ���, ����...";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Seek_Grave";
            if (pchar.questTemp.Ascold == "Ascold_SeekGrave")
            {
            	dialog.text = "�, ������ ����, "+ GetSexPhrase("���� ���","������� ���") +". ��� ����, ��� ���������?";
            	link.l1 = "���� ������, �������, � �������"+ GetSexPhrase("","�") +" ��� � ������, �� ������ �� ���"+ GetSexPhrase("��","��") +". ��������� ������.";
        		link.l1.go = "Step_36";
            }
            if (pchar.questTemp.Ascold == "Ascold_CantSeekGrave")
            {
            	dialog.text = "��� ������� �� ���� ���? ���"+ GetSexPhrase("��","��") +" ���-������?";
            	link.l1 = "���, �� ���"+ GetSexPhrase("��","��") +". ��� ����� ������� ��������, ����� ��� ���...";
        		link.l1.go = "Step_37";
            }
            if (pchar.questTemp.Ascold == "Ascold_NotEnterFoundGrave")
            {
            	dialog.text = "��� ���������� ������? ���� ���-������ ���������?";
            	link.l1 = "�� ���� �����, ��� ���, �� � ���"+ GetSexPhrase("��","��") +" � ������ ���� ����-��, �� �� ������.";
        		link.l1.go = "Step_38";
            }
            if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" && !CheckCharacterItem(pchar, "Rock_letter"))
            {
            	dialog.text = "���"+ GetSexPhrase("��","��") +" ��������?";
            	link.l1 = "��� ����, �� � ���� ���������.";
        		link.l1.go = "exit";
            }
            if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" && CheckCharacterItem(pchar, "Rock_letter"))
            {
            	dialog.text = "�-�-�, ���� �� ������� ������, ��� �������� ����� �������.";
            	link.l1 = "�����, � ���"+ GetSexPhrase("��","��") +" ��, ��������!";
        		link.l1.go = "Step_45";
            }
            if (pchar.questTemp.Ascold == "Ascold_EnterGrave")
            {
            	dialog.text = "������� ������� � ��������?";
            	link.l1 = "��� ���, �� � ��� ���� �������.";
        		link.l1.go = "exit";
            }
		break;
		
 		case "Step_36":
        	dialog.text = "��, ���� �� ����, ��� �������.\n"+
                          "����� � ������� �������� � ���, �� ����... �� ��� ��, ���� ���� ��������� ����� � �� ���-���� ������� - ���� ��� ���� ������.";
        	link.l1 = "�� ��� ��, ��������� ��� ���.";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_CantSeekGrave";
		break;
		
 		case "Step_37":
        	dialog.text = "����� � ���, � ����� � ����... ��������� ������.";
        	link.l1 = "������.";
    		link.l1.go = "exit";
		break;

 		case "Step_38":
        	dialog.text = "���, ������� �� ���"+ GetSexPhrase("��","��") +" ��, ��� ���� �� �� ������.\n"+
                          "���� ������, � ������, ��� ������ ��� � ��������� ������� ��������. ���� ���������� ����� ����� ���������� ������.";
        	link.l1 = "����� �������. � ��� �������? �����, ��� ���� ����, �� �� �������� ����������� ������.";
    		link.l1.go = "Step_40";
		break;
		
 		case "Step_40":
        	dialog.text = "��, ��� ���... ��������, ������ ��� ������ �����������, ������ ������� ��������� � ������ �������, ����� �������� ���� ������ �� ����������� ������.\n"+
                          "�� ����� ������ � �� �� ��������, � �� ��������� ���������, ���� �������, ��� ���-�� ����� ���� ��������, ������� ��������� ����.\n"+
                          "��� ������� ��� ����� �������, ������� ����� ����-�� ���������.";
        	link.l1 = "� ��� ��� �� �������? � ���� ���������?";
    		link.l1.go = "Step_41";
		break;

 		case "Step_41":
        	dialog.text = "��, ����� � ����� ����� �� ����. ���� �������.\n"+
                          "�� �� ������ � ����� ������, � ������� �� ���� ������� ����� ��������, ����� ��� ���� ���������� � �����-�� �������� ��������. � ����� �������� �� ������, �� ������, ��� �����.\n"+
                          "��� ���, ��� �����������, ��� ���� � ����� ����������� ��������� ����� ��������. ��-��������, ��� � ���� ������� �������.";
        	link.l1 = "� ��� ����� ���� ����������?";
    		link.l1.go = "Step_42";
		break;

 		case "Step_42":
        	dialog.text = "� � ���� ���, �� ������? ��� ��� �������� �� �����.";
        	link.l1 = "��, ����... �� ��� ��� �� ����������? ��� �� ������ � ���� �� ��������?";
    		link.l1.go = "Step_43";
		break;
		
 		case "Step_43":
        	dialog.text = "������ �� ����� ����� ��, � ��������� ����. �� ������, ��� ����� ������ �������, �� �� � ����� ��������� � ���� � �� ������. ��� ���, �������� ���, ������ ���� �� ����������� �������� ��� �� �������� ��������� �����, ����� � ���������� ����������. � �����, ��� ��������� �����, ������� ������� �����. ����� ��� �������� ����� �� ����� � �������� ��� �� �������.\n"+
                          "��������� ���� � �� ����, �� ����� ���-�� ����� �� ������ ���� ����� ��� ��� ��� �����. ������ ����.";
        	link.l1 = "���������. ��� �, �������, ������� �������� ���� ���������. �������, ��� ���� ���� ������������� ����� ���� ����.";
    		link.l1.go = "Step_44";
        	link.l2 = "������� ���� ��� ������� ��� ���������� ����. ������ � ������ ������ �� ����.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_44":
        	dialog.text = "����� �� ��� �����������. ��� �, ����� ���� � ������!";
        	link.l1 = "������� �� ���������.";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_SeekRockLetter";
            // ==> ������ �������� ��������, ������ �� ����� �����.
            sld = ItemsFromID("Rock_letter");
            sld.shown = 1;
		break;

 		case "Step_45":
        	dialog.text = "���������� �� � ��������� ������� � ��������.";
        	link.l1 = "����� �������, ��� ��� ��������� � ��� ���� �� �������� ���.";
    		link.l1.go = "exit";
			bDisableLandEncounters = true; //������� �����������, ����� ������, ��� ����.
    		pchar.questTemp.Ascold = "Ascold_EnterGrave";
		break;
		
 		case "Found_Grave":
            if (pchar.questTemp.Ascold == "Ascold_FoundMummy")
            {
            	dialog.text = "�, ��� � ��, " + GetFullName(pchar) + "! ����������� �������, ��� �� ���"+ GetSexPhrase("��","��") +".";
            	link.l1 = "� �����"+ GetSexPhrase("","�") +" ������� ���� � ������. � ������, � ����� �� ����������� ��� ���� � ��������. � ���"+ GetSexPhrase("��","��") +" ��.";
        		link.l1.go = "Step_46";
            }
		break;
		
 		case "Step_46":
        	dialog.text = "������ ������! ��� ��� ��! ���-������ ���"+ GetSexPhrase("��","��") +" ������?";
        	link.l1 = "��� ��������� �������� ����� �������� ��������, �������� ��������� ������. ���������� ����� � �� �����"+ GetSexPhrase("","�") +", ��� ������ ����������� ��� ������ �����������.";
    		link.l1.go = "Step_47";
		break;
		
 		case "Step_47":
        	dialog.text = "��, ������� ���������, ��������� ���������� � ������ ������ �� ����?";
        	link.l1 = "������ ���������� �� ����.";
    		link.l1.go = "Step_48";
		break;
		
 		case "Step_48":
        	dialog.text = "��... ������, ��� ������.\n"+
                          "��� ���, ������-�� ��� ���� �����, ��������� ��� ��� ����� � �� ������� �������� ����� � ���������.";
        	link.l1 = "��, �� ������"+ GetSexPhrase("","�") +" �, ��� ����� ��������� ��������, ��� ��� �����...";
    		link.l1.go = "Step_49";
		break;
		
 		case "Step_49":
        	dialog.text = "���, �� � ��! �������, ��� ����� ���� ��������� �����. �� �� ������, ���� �� ������ ������?";
        	link.l1 = "������ � �� �����. ������ ����� ��� ���� �� ���������, ���� � ���� � ������ �����-������ ������������� ��������� ��� �������.";
    		link.l1.go = "Step_50";
		break;

 		case "Step_50":
        	dialog.text = "��� �������� ��� ���?";
        	link.l1 = "������, ���� ��. ���"+ GetSexPhrase("���","��") +" ���������, ��� ���...";
    		link.l1.go = "Step_51";
		break;

 		case "Step_51":
        	dialog.text = "�� ��� � �����. ������� ���� ���. �� � ��� ���� � �����������.";
           	link.l1 = "������, �������.";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_WateringMummy";
    		GiveItem2Character(Pchar,"Ascold_rabble");
		break;

 		case "AfterAttackMummy":
        	dialog.text = "�, ��� � ��. �� ���� ����������� �� ������, ��� ��������� � ������! ����� ����� ������� ������� �������!!!";
        	link.l1 = "�������?! �� ����� ����!";
    		link.l1.go = "Step_52";
            if (pchar.questTemp.Ascold == "Ascold_SaveWorld")
            {
            	dialog.text = "�� ���, ��������"+ GetSexPhrase("","�") +" �������?";
            	link.l1 = "��� ����, �������� � �������� �����������.";
        		link.l1.go = "exit";
                NextDiag.TempNode = "AfterAttackMummy";
            }
            if (GetCharacterIndex("LeifEricson") == -1)
            {
            	dialog.text = "��, ��� ������ �� �������� ����?";
            	link.l1 = "�� ��� � �������, ��� ������, ���� ����� ����� ��������.";
        		link.l1.go = "Step_60";
				
				// ���������� ����� ������ - ���������� ����� ������� � ��������� ��������   - ugeen fix
				locations[FindLocation("Guadeloupe_CaveEntrance")].reload.l1.name = "reload1_back";
				locations[FindLocation("Guadeloupe_CaveEntrance")].reload.l1.emerge = "reload1";
				
				locations[FindLocation("Guadeloupe_Cave")].reload.l1.name = "reload1_back";
				locations[FindLocation("Guadeloupe_Cave")].reload.l1.emerge = "reload1";
				LocatorReloadEnterDisable("Guadeloupe_Cave", "reload1_back", false);
				
				RestoreOfficers_Ascold(pchar);
				Log_Info("������ � �������� ��������");
            }
		break;

 		case "Step_52":
        	dialog.text = "�� �����?! ��� �������� �������� ���������, � ����������� ������ �������� ���, ��� ��� ������ ������� ���� � �����!\n"+
                          "�� ����� ������ � ������������������ �� ������ ����� � ����� ������� ������� �������. �� ���� ���� ������� ������ ��������� ���� ��������...";
        	link.l1 = "���"+ GetSexPhrase("","�") +" �� ����... ������, �� �� ������� ������, ��� ��� ���� � ������?";
    		link.l1.go = "Step_53";
		break;

 		case "Step_53":
        	dialog.text = "� ����� ������?.. �, ��� �� ������"+ GetSexPhrase("","�") +" ���?";
        	link.l1 = "���, ������"+ GetSexPhrase("","�") +". ���� ������� �����������.";
    		link.l1.go = "Step_54";
		break;

 		case "Step_54":
        	dialog.text = "������! ��� ������ �� ��"+ GetSexPhrase("��","��") +", � ������� ������ �� �� �� �������. �� �������, ��� ����� ������������ ��������� ������� �����������.\n"+
                          "B ��� �������, ��� ���� ������� �������� ����, �� ��� �������� ������-�� �������� ���������� �������.";
        	link.l1 = "��� � ���������. ���� ������ � ���� �� ����� ��������� �����, ������� � ��� ����� �����"+ GetSexPhrase("","�") +".";
    		link.l1.go = "Step_55";
		break;

 		case "Step_55":
        	dialog.text = "� ��� ���� ������?";
        	link.l1 = "������ �... ��, � �����, ��������� �� ����� �������� - ��� ��� ����.";
    		link.l1.go = "Step_56";
		break;

 		case "Step_56":
        	dialog.text = "���� ������! ���������� �� � �����.\n"+
                          "��� ��� ������ ������? ���� ������������� ������ ��������� ���� �� �������.";
        	link.l1 = "�� ������ �� �������. �� ���������� ����� �������� ����. ��� � ������ ���� ����...";
    		link.l1.go = "Step_57";
		break;

 		case "Step_57":
        	dialog.text = "��� ��� ��... ��������, ������ �����, �� �� ����"+ GetSexPhrase("��","��") +" ������ ���.";
        	link.l1 = "� ������ �-��? ��, � �������, �� ������ ������ ���? ���� ��� �� ���� ���� ��������, �� �� � ��������� ���� ������.";
    		link.l1.go = "Step_58";
		break;

 		case "Step_58":
        	dialog.text = "���������, �� �����. � ���� � �������� ����������, � ��� ����� - ��� �� ���.\n"+
                          "�� ��� ������ �������"+ GetSexPhrase("","�") +", ��� �������� ����. � ��� � ���� � ���������� ������������ ��������-�� ������? �� ������ � ����.";
        	link.l1 = "��, �����, �� ������ � ��������... �� ��� �, ����� ���"+ GetSexPhrase("","�") +" ������� ���. �������� ������.";
    		link.l1.go = "Step_59";
		break;

 		case "Step_59":
        	dialog.text = "��, �������, ��� �� ��������"+ GetSexPhrase("��","���") +". ����� ���� � ���� �������� ����, "+ GetSexPhrase("����","�������") +".";
        	link.l1 = "������� �� ���������, �������. ��� ��� ������� �������.";
    		link.l1.go = "exit";
			LocatorReloadEnterDisable("Guadeloupe_Cave", "reload3_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_Cave")], false);
			pchar.quest.Ascold_LeifIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.Ascold_LeifIsDead.win_condition.l1.character = "LeifEricson";
			pchar.quest.Ascold_LeifIsDead.function = "Ascold_LeifIsDead";
			NextDiag.TempNode = "AfterAttackMummy";
    		pchar.questTemp.Ascold = "Ascold_SaveWorld";
			sld = characterFromId("LeifEricson");
            LAi_SetImmortal(sld, false);
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_group_MoveCharacter(sld, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;

 		case "Step_60":
        	dialog.text = "�������. ��-�-�, ������� ���� ����, �� ���� ���������.\n"+
                          "������, � �� ������ ����������� �� �������"+ GetSexPhrase("","�") +" ���? ����� �� �� ������ ������� �� ������, ����� ������� ��� ���-������ ��������.";
        	link.l1 = "���, ������ �� �������.";
    		link.l1.go = "Step_61";
            if (CheckCharacterItem(pchar, "Azzy_bottle"))
            {
            	link.l2 = "����� �����-�� ���"+ GetSexPhrase("��","��") +" ��������� � ����� �����. �� ����, ��� ��� �����.";
        		link.l2.go = "Step_63";				
            }
		break;

 		case "Step_61":
        	dialog.text = "��, ����... ��������, � ����� ��� ��� ��� ����������.\n"+
                          "��������, ������ ��� ���-�� ���� �������� ��� �� �� �������. �� ���������� ������� ����� ������� ����� ��������...";
        	link.l1 = "� ������ �������� ����, �������. � ������� �������"+ GetSexPhrase("","�") +", �������� ���� ���������, ��� ����������� ������ �� ������� ������. ���, ������, � ������ �� ������� � �����.";
    		link.l1.go = "Step_62";
		break;

 		case "Step_62":
        	dialog.text = "��, ����. �� � ����, ��� ����������� ���� ����������. ��� �, ���������� ��������.";
        	link.l1 = "���, ����� ����� ���.";
    		link.l1.go = "exit";
            NextDiag.TempNode = "GoodFriends";
            pchar.questTemp.Ascold = "Ascold_OverBusiness";
			UnlockAchievement("Mummydust_quest", 3);
		break;

 		case "GoodFriends":
        	dialog.text = "�-�-�, ���� � ����! "+ GetSexPhrase("�������","���������") +" " + GetFullName(pchar) + "! ��� ������ ���� �����. �� ���� ��� ������ ���"+ GetSexPhrase("��","��") +"?";
        	link.l1 = "������ �����"+ GetSexPhrase("","�") +" ���������.";
    		link.l1.go = "exit";
            NextDiag.TempNode = "GoodFriends";
            if (pchar.questTemp.Azzy == "HowToKnowAzzy")
            {
            	link.l1 = "��������, � ���� � ���� ���� ����. �� ������� �� ������, ��� � ���� ��������� ������?";
        		link.l1.go = "Step_64";
            }
		break;

 		case "Step_63":
        	dialog.text = "�� ��� ������ ��� ��. 50000 ��� �� ��� �������.";
        	link.l1 = "������ ��� ������ ���, �� ������ ��� ������... �����, �������, ��� ��� �� �����.";
    		link.l1.go = "BuyAzzy";
        	link.l2 = "���, �������, ������� �� �������, �������� �����, ��� �� ��� ��������� ��������� ��� �������� �����. ��������, ��� ��� ������.";
    		link.l2.go = "Step_62";
		break;

 		case "BuyAzzy":
        	dialog.text = "������ ���� - ������� ����. �����, ���������� ��� ������? ����� ���� ��� ����...";
        	link.l1 = "���, �������. � ���� ������ ����������� ������ ����.";
    		link.l1.go = "Step_62";
            TakeItemFromCharacter(pchar, "Azzy_bottle");
            AddMoneyToCharacter(pchar, 50000);
		break;
		
 		case "Step_64":
        	dialog.text = "����?!!";
        	link.l1 = "����� ��� ���� �����, ����� ��� ����� �� ����. � ������ �������� ������.";
    		link.l1.go = "Step_65";
		break;
		
 		case "Step_65":
        	dialog.text = "�� ���, ��� � �������� ������� �������"+ GetSexPhrase("","�") +"?!";
        	link.l1 = "��� ��������� ����, ������, ����� ����������! ������, ����� ������� ����� ���� ������ �������, �������� ����� ����� �����.";
    		link.l1.go = "Step_66";
		break;

 		case "Step_66":
        	dialog.text = "���� � ��� ������, ���� ���� �����. �������� �� ���� ����, ��� ���������, �� ����������� �����.";
        	link.l1 = "��� �� ������? �����������!!!";
    		link.l1.go = "Step_67";
		break;

 		case "Step_67":
        	dialog.text = "� �����, ��� ����������� ������ ��������� �����. � ������ ����������� ��� ����, �� �������, ����� ������� �� ����� ������, ����� � ������ �� ������� ��� ������.";
        	link.l1 = "�� ���, ��� ���� ��� ����� ���� �����... ����. � ������ ���?";
    		link.l1.go = "Step_68";
		break;

 		case "Step_68":
        	dialog.text = "��� ����� �������� �������, ���� �������� ��������. ��������� ��� ��� �������� - � ����� ��������, ��� ������ �������� �����. �����-������ ������ ������� ������ ��������.";
        	link.l1 = "������ �����? ���� ���� ����� ����...";
    		link.l1.go = "Step_69";
		break;

 		case "Step_69":
        	dialog.text = "��� � �������. ������ ������ �������� - � ������. �������, ��� � ������� ���� ������ �������, ��� ��� ������.";
        	link.l1 = "�������, ��� ��. ������, � � ���� ������ ��� �� ���� ���������? � �� �����"+ GetSexPhrase("","�") +".";
    		link.l1.go = "Step_70";
		break;

 		case "Step_70":
           	dialog.text = "���, ������ ���. ��� ��� ���������� ���"+ GetSexPhrase("","�") +".";
        	link.l1 = "�� ��� ��, ������� � �� ����. ���� ������.";
    		link.l1.go = "exit";
            pchar.questTemp.Azzy = "DestrContract";
        	if (sti(pchar.questTemp.Azzy.Immortal.Penalty) >= 15 && GetQuestPastDayParam("questTemp.Azzy") > 90)
        	{
                dialog.text = "����. ��� ��� ��� � ������ �� ����� �������������� ������. ������� �� � �������, ������ ��������...";
                link.l1 = "� �����"+ GetSexPhrase("","�") +" �� � ���� ������ �� ����� ����. ������� �� ������?";
                link.l1.go = "Step_71";
            }
		break;
		
 		case "Step_71":
        	dialog.text = "� ���� � ����� �� ������. �� ���� � �� �� �������� ������ ���� ���, ������� �� ������"+ GetSexPhrase("","�") +" ��� ���, ������ �������. ����� �������, ��� �� � �������. � ������ �������.";
        	link.l1 = "�������� ���� �������, �������. ������, � �������� ����, ����� ��������, �� �������?";
    		link.l1.go = "Step_72";
            GiveItem2Character(pchar, "sculMa1");
            GiveItem2Character(pchar, "sculMa2");
            GiveItem2Character(pchar, "sculMa3");
            GiveItem2Character(pchar, "indian22");
		break;

 		case "Step_72":
        	dialog.text = "�� ��� ��, �������. ������� � ��, ����� ��������?";
        	link.l1 = "������, ����� ������. ������ � �����"+ GetSexPhrase("","�") +" ������� ���� ���������� �����. ������� ����, �������.";
    		link.l1.go = "exit";
		break;
	}
}


