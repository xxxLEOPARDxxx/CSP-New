// ��������� ������� � ����� ��� ������� �������� � ����������.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    sld = characterFromID("Henry Morgan");
    
	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- ������ ������ - ������ �������
		case "First time":
            if (sld.location == pchar.location && bWorldAlivePause)
            {
    			dialog.text = "���� �� � ��������, �� ������ ���� ������. �� ������ � ����������.";
    			link.l1 = "������, ����� �������� � ���.";
            }
            else
            {
    			if (pchar.questTemp.piratesLine == "Panama_inEngland" || pchar.questTemp.piratesLine == "Panama_backToShip")
				{
					dialog.text = "������� ���������� � ������. �� ����� ����� �� ������, ��� ����� ���.";
    				link.l1 = "�������...";
				}
				else
				{
					dialog.text = "�������� ��� �� ����� - ����������� �� �����. � ������ �� �������� ����, � ����� �����.";
    				link.l1 = "���� ������� ���, �� ��� � ���� ���� ������ ������.";
				}
            }
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "���� ����� " + GetFullName(npchar) + ". � ��������� ����� �������.";
				link.l1 = "��� ��� " + GetFullName(pchar) + ".";
				link.l1.go = "First time";
				npchar.quest.meeting = "1";
			}
            //============>>>>>>>>> �������� ��������� ��������
            if (pchar.questTemp.State == "WormEnglPlans_toMorgan")  // HolLine_3, ������������� � �������.
            {
    			link.l1 = "��������, ��� ����� ������, � ����� ������.";
    			link.l1.go = "Step_H3_1";
            }
            if (pchar.questTemp.State == "Fr8ThreeCorsairs_toSeek")  // FraLine_8, ������������� � �������.
            {
    			link.l1 = "�����, � �����"+ GetSexPhrase("","�") +" �� ���������� � ����� ��������. ��� � ���� ��� �������?";
    			link.l1.go = "Step_F8_1";
            }
            // ����� ��������. �������� �� ��������� ��������� ���������.
            if (pchar.questTemp.Ascold == "SeekThreeObject" && !CheckAttribute(pchar, "questTemp.Ascold.Oliver"))
            {
    			link.l2 = "��������, �� ���� ������� ������. �� ����������� �� ���� � �������� ������������� ������� ��������� ��������� ��������?";
    			link.l2.go = "Step_As_1";
            }
            if (pchar.questTemp.Ascold == "SeekThreeObject" && CheckAttribute(pchar, "questTemp.Ascold.Oliver"))
            {
    			link.l2 = "������, �����, �� ����������� ������ ���� ��� ��������� ���������, � ������� � ���� �������"+ GetSexPhrase("","�") +"?";
    			link.l2.go = "Step_As_7";
            }
            if (pchar.questTemp.Azzy == "DestrContract" || pchar.questTemp.Azzy == "2DestrContract")
            {
                if (!CheckAttribute(pchar, "questTemp.Azzy.Oliver"))
                {
        			link.l2 = "������, ��������, ���� � ���� ��������� ������. ��� ������� ����� ��������� ����������. ���� ���� � ���� ����������� ������� ��������� � �������� ����, ������� �� ����������.";
        			link.l2.go = "Step_As_9";
        		}
            }
            //============>>>>>>>>> �������� ��������� ��������
        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
		//********************* ����������� ������� *********************
        case "Step_H3_1":
            dialog.text = "� ��� �� ���"+ GetSexPhrase("��","��") +" � ����� ���� ����������� �����?";
            link.l1 = "���� ����� " + GetFullName(pchar) + ", � ������� ���� �������� ������ ��������.";
            link.l1.go = "Step_H3_2";
        break;
        case "Step_H3_2":
            dialog.text = "�������"+ GetSexPhrase("��","��") +"?... �� - �������"+ GetSexPhrase("��","��") +"?";
            link.l1 = "����� ���� ����, ����� � �����? � ���� ���� � ������� �� ���������, ���� ���� ��� �� ����?";
            link.l1.go = "Step_H3_3";
        break;
        case "Step_H3_3":
            dialog.text = "�� ��������, "+ GetSexPhrase("������","�������") +", ��� ���������. ���������� ����� ������� �����, � ��� � ���� ����� ���� ������ ���������� �����������.\n"+
                          "������� ��� ��� � ���� �����: ������ �� �������, � ����� ����. ��� ���� ���� ���������� - ���� � � ���� ������� �������"+ GetSexPhrase("��","��") +", �� ��� �� ����� ������ � ��� ������.\n"+
                          "� ��� - � ��� � ������� ��� ������ �� �������, ����� �������� ������ �� �����, ��-��... ��� ���������� ��� ����-�������, ��� �������� ���� � �����...";
            link.l1 = "�������, ������.";
            link.l1.go = "exit";
            pchar.questTemp.State = "WormEnglPlans_toMorganAntigua";
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "3");
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("","�"));
        break;
		//********************* ����������� ������� *********************
 	 	case "Step_F8_1":
			dialog.text = NPCStringReactionRepeat("��� �� ���"+ GetSexPhrase("��, ���","��, ����") +"?", "� ��� ������� ���...", 
				          "��������, � ��� ������� ��� �� ���� ������.", "��� �� ����� ��������� ���, � ����� ������ �� �����.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("���� ����� " + GetFullName(pchar) + ", � �������� �� ��������� ������������ �������������.", "��, �����...", "��, � �����...", "������.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F8_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;  
        case "Step_F8_2":
            dialog.text = "� �� ������ ���� ������������ ������������� ����������� ����� ������?";
            link.l1 = "��������, ��������, ���� �� �������, ��� ��� ��������� �� ������� �����������?";
            link.l1.go = "Step_F8_3";
        break;
        case "Step_F8_3":
            dialog.text = "�����, �����, "+ GetSexPhrase("�����","�����������") +"... ������ ������ ��������� � ����� ���� �� �������.";
            link.l1 = "�� ��� � ������. ���������� ����������� ����!";
            link.l1.go = "Step_F8_4";
        break;
        case "Step_F8_4":
            dialog.text = ""+ GetSexPhrase("�����","�����������") +", ������ � ����, ��� � ��� � ������� � ����-������ ��� ������ �� �������, ����� ��� ������ �� �����. ���� - ����� ����������...";
            link.l1 = "����������...";
            link.l1.go = "exit";
        break;
		//********************* ����� �������� *********************
   		case "Step_As_1":
			dialog.text = "��� �� ������� ����� ��������?! �����, � ����������, � ������ � ���� �� ���� ������ ��������?";
			link.l1 = "�� �� ��������. ��� ���� � ���, ��� � ��� ��� �������� ���������� ������. ��� �������. ��� ���� - �� ���� ������������ ��� �����, ���� �������� �� ��������. � �����"+ GetSexPhrase("","�") +" ��������� ����� �� ��� ����, ���� ��� � ��� ����.";
			link.l1.go = "Step_As_2";
		break;
   		case "Step_As_2":
			dialog.text = "� ��� �� ����?";
			link.l1 = "��������� ��������� �������, �������������� ����� � �������������� ���.";
			link.l1.go = "Step_As_3";
		break;
   		case "Step_As_3":
			dialog.text = "���, ��� ��� ���� - �� ����������� ��������. �� ������������� �� � ������ � ���������� � ������ �������� ��� ������. ������� �����, ������ ��, ������� ����...";
			link.l1 = "� �������. � �����"+ GetSexPhrase("","�") +" ��������� ��� ���� �� ��� ��������� ����������, ������ � ���������������� ����, ��� �������... � ������, ��� ���� � ���� ����? ��� �� ����������� �������� �����?";
			link.l1.go = "Step_As_4";
		break;
   		case "Step_As_4":
			dialog.text = "��� ���� � ���� ����. �, � ��������, � ����� ���� ���� �� �������. �� ������ ��� ���� - �� ������� ��� ���������� ���������. ������� ����.";
			link.l1 = "� ������� �� ������?";
			link.l1.go = "Step_As_5";
		break;
   		case "Step_As_5":
			dialog.text = "�������.";
			link.l1 = "���?!!! �� ��������?!";
			link.l1.go = "Step_As_6";
		break;
   		case "Step_As_6":
			dialog.text = "���������. �� ��� �������, �� �����-�� ��� ����, �������� � ��� ������, � ���� �� ����� ������� ������� ���-��? ��� �� ������"+ GetSexPhrase("��","���") +", "+ GetSexPhrase("���� ���","�������") +", ���� �� ������, ��� ��� ����� ��� ���� ���������. �� �������� - ��� � ��������, �������� ��� ������.";
			link.l1 = "���� ������, ������!";
			link.l1.go = "Step_As_7";
			pchar.questTemp.Ascold.Oliver = 1;
		break;
   		case "Step_As_7":
			dialog.text = "�����, ������ �������. ������ ��� ���?";
			link.l1 = RandPhraseSimple("�� �� �� ���! �� ����� ������ � ���� ���� ����� �����!", "�� �������? �� �� ��� ��! ���, �������.");
			link.l1.go = "exit";
            if (sti(pchar.money) >= 1000000)
            {
    			link.l2 = "��, ����! � ������� ��� ��� � ���������� ��������!";
    			link.l2.go = "Step_As_8";
            }
            else
            {
    			link.l2 = "� �� ����"+ GetSexPhrase("","�") +", �� ����� ����� ���. �����, ����� ��������� ���...";
    			link.l2.go = "exit";
            }
		break;
   		case "Step_As_8":
			dialog.text = GetFullName(pchar) + ", � ����� ������� ����� ����. ������� ���� ��������� ���������! �������, ��� �������� ���� �����, ��� �� �����"+ GetSexPhrase("","�") +" ������� �� ��� ����� ������...";
			link.l1 = "� ���� �������, ������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			DeleteAttribute(pchar, "questTemp.Ascold.Oliver");
			pchar.questTemp.Ascold = "SoughtThreeObject";
    		GiveItem2Character(pchar, "indian19");
    		GiveItem2Character(pchar, "indian20");
    		GiveItem2Character(pchar, "indian21");
		break;
   		case "Step_As_9":
			dialog.text = "���� � ���� ����� ��������. ���� ��������� - � ��� ����.";
			link.l1 = RandPhraseSimple("���� ���������?!!", "���� ���������... ������� �����!");
			link.l1.go = "exit";
            if (sti(pchar.money) >= 5000000)
            {
    			link.l2 = "������, ��� � ���� ��� ������� ������. ���� �����. ������� ������ � ����� �������� ��������!";
    			link.l2.go = "Step_As_10";
            }
            else
            {
    			link.l2 = "��� ��� ����� �����, �� ����� ����� � ���� ���...";
    			link.l2.go = "exit";
            }
		break;		
   		case "Step_As_10":
			dialog.text = GetFullName(pchar) + ", � ����� ������� ����� ����. ������� ���� ��������� ���������!";
			link.l1 = "�������, ������! �� ��� ��������� ����� ����...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000000);
    		GiveItem2Character(pchar, "sculMa1");
    		GiveItem2Character(pchar, "sculMa2");
    		GiveItem2Character(pchar, "sculMa3");
    		GiveItem2Character(pchar, "indian22");
    		pchar.questTemp.Azzy.Oliver = 1;
		break;

		case "PL_Q8_over":
			dialog.text = "����������� �������� " + GetFullName(pchar) + ".";
			link.l1 = "������, ������, ��� ������ ������!";
			link.l1.go = "PL_Q8_over_1";
		break;
		case "PL_Q8_over_1":
			dialog.text = "� ��� ���, �� ���� �� ������ ��� ����. � ���� ������ ��������, ��� �� ������ �������� �� ������.";
			link.l1 = "����?!";
			link.l1.go = "PL_Q8_over_2";
		break;
		case "PL_Q8_over_2":
			dialog.text = "����! �������� ���������� ��� ����. �� �� �����"+ GetSexPhrase("","�") +" � �����, � ������ �� �� ���"+ GetSexPhrase("��","��") +". ������...";
			link.l1 = "������!!! �� �����, ��� �������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
	}
}


