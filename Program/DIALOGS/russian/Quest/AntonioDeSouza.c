// ���������� ���� �1 �� ���������
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	float locx, locy, locz;

    switch (Dialog.CurrentNode)
    {
        case "First time":
            dialog.text = NPCStringReactionRepeat("��� ����, "+ GetSexPhrase("��� ���","���� ���") +"?",
                         "����� ��? ���-�� ����� �������?", ""+ GetSexPhrase("��� ���","���� ���") +", ��� ���� ������, ������ �� � ������� ��� �� ������� ��������� �� ��� � ������ �� ��������?",
                         "��������, " + GetFullName(pchar) + ", ���� ���� ������ �������, �� � �� ���� ���� ������.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�� ������ ����������, �����...",
                                               "�� ���, ������ ���...",
                                               "������� ������, �����...",
                                               "������, �����...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
//>>>>>>>>>>>>========= ������� �������� =====================
			if (pchar.questTemp.State == "Inquisition_toDeSouza")//����� �2, ����� � ��.������������
			{
                dialog.text = "����� ���������� � ���� ������, "+ GetSexPhrase("��� ���","���� ���") +".";
    			link.l1 = "�����, � � ��� �� ������� ������� �������-�����������...";
    			link.l1.go = "Step_S2_1";
            }
			if (pchar.questTemp.State == "Inquisition_toCuracao")
			{
                if (CheckAttribute(pchar, "questTemp.State.Store") || CheckAttribute(pchar, "questTemp.State.Usurer"))
                {
                    dialog.text = "��� ������ ����, " + GetFullName(pchar) + ". �� �����"+ GetSexPhrase("","�") +" ���������� �� �������?";
        			link.l1 = "�����, � ��������"+ GetSexPhrase("","�") +" ����, ��������� ���� �����.";
        			link.l1.go = "Step_S2_12";
        			link.l2 = "�������, ��� ���, ���������. � ��� ��������� ��� ����...";
        			link.l2.go = "exit";
                }
                else
                {
                    dialog.text = "�� �������"+ GetSexPhrase("","�") +" �������, "+ GetSexPhrase("��� ���","���� ���") +". ��������� � ����������.";
        			link.l1 = "������, ���������...";
        			link.l1.go = "exit";
                }
            }
			if (pchar.questTemp.State == "Inquisition_afterFrancisco")
			{
                if (CheckAttribute(pchar, "questTemp.State.Store") || CheckAttribute(pchar, "questTemp.State.Usurer"))
                {
                    dialog.text = "��� ������ ����, " + GetFullName(pchar) + ". �� �����"+ GetSexPhrase("","�") +" ���������� �� ������?";
        			link.l1 = "���������, � ��������"+ GetSexPhrase("","�") +" ���� ��������� ���� �����.";
        			link.l1.go = "Step_S2_12";
        			link.l2 = "�������, ��� ���, ���������. � ��� ��������� ��� ����...";
        			link.l2.go = "exit";
                }
                else
                {
                    dialog.text = "��� ���������, "+ GetSexPhrase("��� ���","���� ���") +"? �� ���������� � ���������� ������?";
        			link.l1 = "���, ���������. � ������"+ GetSexPhrase("��","���") +" �� �� ����. ������ �� ��� ������� ����� ��������� �� ���-��������� � ����������� ������� ����� �������� ��� ������ ������ �������. �� �����, ���� � ���, ����� ���. �� �� �������� ��� ��������?";
        			link.l1.go = "Step_S2_11";
                }
            }
			if (pchar.questTemp.State == "Inquisition_backAllGood" || pchar.questTemp.State == "Inquisition_backPartGood" || pchar.questTemp.State == "Inquisition_backBad")
			{
                dialog.text = ""+ GetSexPhrase("��� ���","���� ���") +", �� ������ ������������ � ������. ��� �� ������ �� ���"+ GetSexPhrase("��","��") +"...";
    			link.l1 = "������, ���������.";
    			link.l1.go = "exit";
            }
			if (pchar.questTemp.State == "TakeRockBras_RockTaken")
			{
                dialog.text = "������ ����, "+ GetSexPhrase("��� ���","���� ���") +". ����� ���������"+ GetSexPhrase("","�") +"?";
    			link.l1 = "���������, �������� ����������� ������������ �������-����������� ������ ���� ��������� ������-�-�������, � ������� ������ ���������� ���������� ������� ���� ���������, ����������� ���� � ������ ����� � ���������.";
    			link.l1.go = "Step_S3_1";
            }

        break;

//<<<<<<<<<<<<===== ������� ��������  =====================
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

//********************************* ������� ����������. ����� �2 **********************************
 		case "Step_S2_1":
			dialog.text = "� ����, "+ GetSexPhrase("��� ���","���� ���") +", ����. � ���� ����. ����, � ����� ������.\n"+
                          "���� ��������� �����, ������� � �������, � �� ���� �� � ����� ������ �� ��������. ��� ������������� ���������� ����� �������, ����� ����� �� ��������, � ���� ����� �� �������. ��� ������� ��������, ��� ��� ������ ��� ������� ������������ ������ �������.\n"+
                          "���� ������������ ����� ���������� �� ����������� �� ���������� �� ����� �������� �� ��� �� ������. �� ��� �� ����� �����, �� ����� �������� ����� ����, ������� �� �� ����...";
			link.l1 = "��������, ���������, � ���� ���� ������. ���� ��, �������, ��������� ��� ������.";
			link.l1.go = "Step_S2_2";
		break;
 		case "Step_S2_2":
			dialog.text = "���������, "+ GetSexPhrase("��� ���","���� ���") +".";
			link.l1 = "� ������"+ GetSexPhrase("","�") +", ��� ��������� ������ �� ������ ����� ��� ��, ��� � ��������. ����� �� �� �������, ���� ��� ����� �� ���������?";
			link.l1.go = "Step_S2_3";
		break;
 		case "Step_S2_3":
			dialog.text = "������� �������� ����� ������, �� ����� ����������� � ������� ���������� ������������� ��������� ������������ ���� � ������������� ������������ ���������, ��� ������� ������� ���������� �������� ��������.";
			link.l1 = "� ������ � ��������, �� ���� ��������� ����������� ����� �����������, ����� �� �������?";
			link.l1.go = "Step_S2_4";
		break;
 		case "Step_S2_4":
			dialog.text = "��� ����������, "+ GetSexPhrase("��� ���","���� ���") +". ����� ������ ������ � ���� ����, ����� ������ ��������� ���� �� ������� ������. ������ �� ��������� ���������� ��������� ������������ ���� �����������, � ��� ����� ���������� �� ��������. ������!\n"+
                          "� ���� ��, ��������� ��������� ���� �������������, �������� ������� �� ����� ��������. ����� �������� ��� �����, ���� �� ������ �������������� ���� ����� ������� ������ ������ ������� ��������� ��������� �� ����� ������� � �������!";
			link.l1 = "��� ��� ��! ������ �������"+ GetSexPhrase("","�") +", ��� ������ ���������� ����������. ��� �� ����� ����� ���������?";
			link.l1.go = "Step_S2_5";
		break;
 		case "Step_S2_5":
			dialog.text = "� ������� ����� ���� �������������, "+ GetSexPhrase("��� ���","���� ���") +"! �� ������������ ��� ������ ������ ������, �� ����� �� ���������� ���� ��� ���-�� �� ����� �������. ��� ��������� � � ���� ���, ��� ���������� ���������� ��� ������� ��������� ����� - ��������...";
			link.l1 = "�� �� ���� ��������?";
			link.l1.go = "Step_S2_6";
		break;
 		case "Step_S2_6":
			dialog.text = "��������, ��������� � ������� ���� ����, ��� �� �����? �� ����, ��� ������ ������ ���. ������, ��� ������� ������ ��� ����...";
			link.l1 = "�����... ��� � ��� �� ����� ����������� ��� �������?";
			link.l1.go = "Step_S2_7";
		break;
 		case "Step_S2_7":
			dialog.text = "��� ����� ��������� �������� ����������� � ������������ �����.";
			link.l1 = "� ��� ��������, ��� ��� ������ ���������?";
			link.l1.go = "Step_S2_8";
		break;
 		case "Step_S2_8":
			dialog.text = "�������, "+ GetSexPhrase("��� ���","���� ���") +". ������� ��� ������ � ����������, �� ��� �� ��������� - ����� ������������ ����� ������� � ������ �����.\n"+
                          "����� ��� ������� � ����� ����, � ������ ������������ ����������� ������ �� ������� �������. ���� ������ ����������� � ���, ����� ������ ����������, ������, ����� ������� ����, ������ �������� ����.\n"+
                          "������������ ����� ������ 50 ����� � �������. � ���� ��� ���������, �� ���� ����� ����� ������, � ��� ���������� �� ������� ����.";
			link.l1 = "� ������� �� 50 �����, � � ������ ������������� � ���� ������ � ���� ���, ��� ������. � ��������� �����"+ GetSexPhrase("","�") +"?";
			link.l1.go = "Step_S2_9";
		break;
 		case "Step_S2_9":
			dialog.text = "��, "+ GetSexPhrase("��� ���","���� ���") +", �� ��� ��������� �����"+ GetSexPhrase("","�") +"...";
			link.l1 = "�� ����� 50 ����� �������� �������� ����� ���������� ����� ��������?";
			link.l1.go = "Step_S2_10";
		break;
 		case "Step_S2_10":
			dialog.text = "���, �������. �� �� ������ � ����-�� ��������. ��� ����� �������� �� ���� � �������, ���� �� � ���������. ��� ��� �������, �� ������ � ���������� ������?";
			link.l1 = "��, ���������, ��������� ����������!!";
			link.l1.go = "exit";
    		pchar.questTemp.State = "Inquisition_toCuracao";
            AddQuestRecord("Spa_Line_2_Inquisition", "2");
            Pchar.quest.Inquisition_MeetFrancisco.win_condition.l1 = "location";
            Pchar.quest.Inquisition_MeetFrancisco.win_condition.l1.location = "Santiago_town";
            Pchar.quest.Inquisition_MeetFrancisco.win_condition = "Inquisition_MeetFrancisco";
		break;
 		case "Step_S2_11":
			dialog.text = "������� �� ��������������, "+ GetSexPhrase("��� ���","���� ���") +". �������� ������������ �� ��������� � �������� �������� ������ � ���������� ��������� �� ���. � ���������� � ���������, �� ������ �� ����� ���� ��������. ������ ��� � ���� ���������������. �������, ���� ��� ����������...";
			link.l1 = "�������, ������ ����.";
			link.l1.go = "exit";
			pchar.questTemp.State = "Inquisition_toCuracao";
            GiveItem2Character(pchar,"DeSouzaCross");
		break;
 		case "Step_S2_12":
			dialog.text = "� ������ ����������, "+ GetSexPhrase("��� ���","���� ���") +"?";
			link.l1 = "��� �� ������� �������� ������ �� � ������ �� ���� �����.";
			link.l1.go = "Step_S2_NotMoney";
            if (pchar.questTemp.State.Usurer == "Ok")
            {
    			link.l1 = "������ ��� ������� �������� ������ � ������ ������ �� ��������, ���������� �������.";
    			link.l1.go = "Step_S2_OnlyUsurer";
            }
            if (pchar.questTemp.State.Store == "Ok")
            {
    			link.l1 = "������ ��� ������� �������� ������ � ����� �������, ������� �������� � �������, � ��� ���������� ����� ����� �� �������.";
    			link.l1.go = "Step_S2_OnlyStore";
            }
            if (pchar.questTemp.State.Store == "Ok" && pchar.questTemp.State.Usurer == "Ok")
            {
    			link.l1 = "������ ��������� ���������, ������ ����. ������ ��� ������� �������� �� ���� ����� ��������� ���� ����������.";
    			link.l1.go = "Step_S2_All";
            }
		break;
 		case "Step_S2_NotMoney":
			dialog.text = "���� ����� ������� � ������ ��� ����... �� �� ����"+ GetSexPhrase("","��") +" ��������� ����������� �������.";
			link.l1 = "������ ����, � ������"+ GetSexPhrase("��","���") +" ��� ���� ���...";
			link.l1.go = "Step_S2_13";
		break;
 		case "Step_S2_13":
			dialog.text = "� �������, �������� - ��������� ����������� �������... ������ � ������, "+ GetSexPhrase("��� ���","���� ���") +", �� ��� ������ �� ���"+ GetSexPhrase("��","��") +"...";
			link.l1 = "������, ���������. ��������...";
			link.l1.go = "exit";
            pchar.questTemp.State = "Inquisition_backBad";
            AddQuestRecord("Spa_Line_2_Inquisition", "15");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
		break;
 		case "Step_S2_OnlyUsurer":
            if (sti(pchar.money) >= 50000)
            {
                dialog.text = "�� ��� ��, �������� ����������� ������� - ��� ������, "+ GetSexPhrase("��� ���","���� ���") +"... �� ����� ���� � �����.";
    			link.l1 = "������ ����, � ������"+ GetSexPhrase("��","���") +" ��� ���� ���...";
    			link.l1.go = "Step_S2_14";
            }
            else
            {
                dialog.text = "�-�-�, ������� ���������, � ��� �� 50 �����? ������, "+ GetSexPhrase("��� ���","���� ���") +", � ������� � �������� ��� ������ �� �������.";
    			link.l1 = "����� ��������, ���������, �����"+ GetSexPhrase("","�") +" �� �������. � �����...";
    			link.l1.go = "exit";
                NextDiag.TempNode = "Step_S2_OnlyUsurer";
            }
		break;
 		case "Step_S2_14":
			dialog.text = "��, �����, �����... ����, ����� ���������. �������� ������������ ������� ����������, ��������� ����� � �������� �������������� � ���������� �����. ��������� ���� ����������� �� 20 �� 30 ��������� �� ��� ��������� �� �������� ����, � ����������� �� �������� �����.\n"+
                          "� ���������� ����� ��������� ��������� �������� - 10 ���������, ������ ������� ��� ��������� � ����������, ��-��. ����� ���� ������� ����������... ����������... 9 ����� ��������. ������, "+ GetSexPhrase("��� ���","���� ���") +", ��������� - � ������ ���� ������"+ GetSexPhrase("��","��") +".";
			link.l1 = "�������, ���������. ��������...";
			link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
    			link.l2 = "���������, ���������. � ���� ��� ���-��� ���� ��� ���...";
    			link.l2.go = "Step_S2_17";
            }
			pchar.questTemp.State = "Inquisition_backPartGood";
			AddMoneyToCharacter(pchar, -41000);
			AddQuestRecord("Spa_Line_2_Inquisition", "16");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
		break;
 		case "Step_S2_OnlyStore":
            if (sti(pchar.money) >= 100000)
            {
                dialog.text = "�� ��� ��, �������� ����������� ������� - ��� ������, "+ GetSexPhrase("��� ���","���� ���") +"... �� ����� ���� � �����.";
    			link.l1 = "������ ����, � ������"+ GetSexPhrase("��","���") +" ��� ���� ���...";
    			link.l1.go = "Step_S2_15";
            }
            else
            {
                dialog.text = "�-�-�, ������� ���������, � ��� �� 100 �����? ������, "+ GetSexPhrase("��� ���","���� ���") +", � ������� � �������� ��� ������ �� �������.";
    			link.l1 = "����� ��������, ���������, �����"+ GetSexPhrase("","�") +" �� �������. � �����...";
    			link.l1.go = "exit";
                NextDiag.TempNode = "Step_S2_OnlyStore";
            }
		break;
 		case "Step_S2_15":
			dialog.text = "��, �����, �����... ����, ����� ���������. �������� ������������ ������� ����������, ��������� ����� � �������� �������������� � ���������� �����. ��������� ���� ����������� �� 20 �� 30 ��������� �� ��� ��������� �� �������� ����, � ����������� �� �������� �����.\n"+
                          "� ���������� ����� ��������� ��������� �������� - 10 ���������, ������ ������� ��� ��������� � ����������, ��-��. ����� ���� ������� ����������... ����������... 18 ����� ��������. ������, "+ GetSexPhrase("��� ���","���� ���") +", ��������� - � ������ ���� ������"+ GetSexPhrase("��","��") +".";
			link.l1 = "�������, ���������. ��������...";
			link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
    			link.l2 = "���������, �����. � ���� ��� ���-��� ���� ��� ���...";
    			link.l2.go = "Step_S2_17";
            }
			pchar.questTemp.State = "Inquisition_backPartGood";
			AddMoneyToCharacter(pchar, -82000);
			AddQuestRecord("Spa_Line_2_Inquisition", "16");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
		break;
 		case "Step_S2_All":
            if (sti(pchar.money) >= 150000)
            {
                dialog.text = "���������, "+ GetSexPhrase("��� ���","���� ���") +"! 150 ����� - ������������ ����� � ���� ������ ������. �� ���������� ����...";
    			link.l1 = "������ ����, � ������"+ GetSexPhrase("��","���") +" ��� ���� ���...";
    			link.l1.go = "Step_S2_16";
            }
            else
            {
                dialog.text = "�-�-�, ������� ���������, � ��� �� 150 �����? ������, "+ GetSexPhrase("��� ���","���� ���") +", � ������� � �������� ��� ������ �� �������.";
    			link.l1 = "����� ��������, ����������, �����"+ GetSexPhrase("","�") +" �� �������. � �����...";
    			link.l1.go = "exit";
                NextDiag.TempNode = "Step_S2_All";
            }
		break;
 		case "Step_S2_16":
			dialog.text = "��, �����, �����... ����, ����� ���������. �������� ������������ ������� ����������, ��������� ����� � �������� �������������� � ���������� �����. ��������� ���� ����������� �� 20 �� 30 ��������� �� ��� ��������� �� �������� ����, � ����������� �� �������� �����.\n"+
                          "� ���������� ����� ��������� ��������� �������� - 10 ���������, ������ ������� ��� ��������� � ����������, ��-��. ����� ���� ������� ����������... ����������... 27 ����� ��������. ������, "+ GetSexPhrase("��� ���","���� ���") +", ��������� - � ������ ���� ������"+ GetSexPhrase("��","��") +".";
			link.l1 = "�������, ���������. ��������...";
			link.l1.go = "exit";
            if (CheckCharacterItem(pchar, "Bible"))
            {
    			link.l2 = "���������, ���������. � ���� ��� ���-��� ���� ��� ���...";
    			link.l2.go = "Step_S2_17";
            }
			pchar.questTemp.State = "Inquisition_backAllGood";
			AddMoneyToCharacter(pchar, -123000);
			AddQuestRecord("Spa_Line_2_Inquisition", "17");
            DeleteAttribute(pchar, "questTemp.State.Store");
            DeleteAttribute(pchar, "questTemp.State.Usurer");
            DeleteAttribute(pchar, "questTemp.State.SeekBible");
			NextDiag.TempNode = "First time";
		break;
 		case "Step_S2_17":
			dialog.text = "� ��� �� ��� �����, "+ GetSexPhrase("��� ���","���� ���") +"?";
			link.l1 = "������ ����, ��������, �� ��� ������������ � ����� ������� ������, ������� ������ ������� ��������� ��������� �� ����� ������� � �������...";
			link.l1.go = "Step_S2_18";
		break;
 		case "Step_S2_18":
			dialog.text = "���� �����, � ���?";
			link.l1 = "� �� ������ �� �� ����� ��������� ������ �� ���������������� ���������, �� �� ������ ����������, ������ ��������...";
			link.l1.go = "Step_S2_19";
		break;
 		case "Step_S2_19":
			dialog.text = "�� ���� ��������� ���� ��������! �� �� ���������, "+ GetSexPhrase("��� ���","���� ���") +", ��� ����� ���� ������"+ GetSexPhrase("","�") +"...";
			link.l1 = "��� ���, ���������, � ���"+ GetSexPhrase("��","��") +" ��� �����. ��� ���.";
			link.l1.go = "Step_S2_20";
		break;
 		case "Step_S2_20":
			dialog.text = "������ ����������, ������ �����!!! � ����� ����� �� ���� � ������� �� �����! ������ � ������ � ���, ��� �������� ���� ����������� �������� � ��� ����� ������������� � ����� � ����.\n"+
                          "����� ���� � ���� �����!.. "+ GetSexPhrase("��� ���","���� ���") +", � ������� �� ����� �������� � �������� ���� ��� ����� � ��� ��� �������!";
			link.l1 = "� �������� ���"+ GetSexPhrase("","�") +", ��� �����"+ GetSexPhrase("","�") +" ������ ���, ������ ����...";
			link.l1.go = "Step_S2_21";
			TakeItemFromCharacter(pchar, "Bible");
		break;
 		case "Step_S2_21":
			dialog.text = "��� ��� �� ���, "+ GetSexPhrase("��� ���","���� ���") +". � ���� ��������������� �� ��������� ������� ������ ���������� ������ ���� ��� ���� ������������ �������� ������, ���������������� �������.\n"+
                          "������ �������� ���� ������ - �� � �����������. �� �������� �������� - � ���������� ����������, ��� ���� � ����� ����� �����, ��� � �������...";
			link.l1 = "������ ���, �����. ����� ������ � ���-�� ������... �� ��� ��, ������� � �� ���. � ������ ��������� �����������, ������ ����.";
			link.l1.go = "Step_S2_22";
		break;
 		case "Step_S2_22":
			dialog.text = "��, ��, �������. � ���� ������, ������ � ��������� ������� � �������!";
			link.l1 = "��������, ���������.";
			link.l1.go = "exit";
            GiveItem2Character(pchar, "cirass5");
		break;
//********************************* ������ ���� ���������. ����� �3 **********************************
 		case "Step_S3_1":
            if (CheckPassengerInCharacter(pchar, "RockBrasilian"))
            {
    			dialog.text = "������������ ������, "+ GetSexPhrase("��� ���","���� ���") +"! � � ����������!";
    			link.l1 = "���� ������� ��� ������ ���������� - �������� �������� ���� �������. ��� ����� ��� �������� ����� �� ������� ������, ������ ������� ��������� ������� �� �������.";
    			link.l1.go = "Step_S3_2";
            }
            else
            {
    			dialog.text = "������, � ���� � ����� ��� ���! "+ GetSexPhrase("��� ���","���� ���") +", ��� � ������� ��� ���� ���������.";
    			link.l1 = "������, ���������...";
    			link.l1.go = "exit";
            }
		break;
 		case "Step_S3_2":
			dialog.text = "�� ��� ��, ��������� ��������� ����� ������� �� ��� ����������, ��� �� �������� ������ ���������. � ����� ��� ����� ����� � �������-�����������.";
			link.l1 = "������, ���������.";
			link.l1.go = "exit";
			NPChar.LifeDay = 10;
    	    SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			AddQuestRecord("Spa_Line_3_RockBrasilian", "6");
			pchar.questTemp.State = "TakeRockBras_RockGiven";
			sld = characterFromId("RockBrasilian");
			ReleasePrisoner(sld);
     	    sld.LifeDay = 0; // ������ ���
		break;

    }
}
