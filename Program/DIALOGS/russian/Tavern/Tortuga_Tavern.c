// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("��� ������� ������ "+ GetCityName(npchar.city) +" � ����� �������. ��� �� �� ������ ������?",
                          "�� ������ ��� ��������� ��� ����. ��, ��������, ������������...", "������� �� ��� ������ ��� �������� � �����-�� �������...",
                          "��� �� "+ GetSexPhrase("�������","��������") +" ��� ������� ���� � �� ��...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������, " + NPChar.name + ", ���-������ � ��������� ���.", "�����, "+ GetSexPhrase("�����","������") +" ���-��...",
                      "�� ��, ������������� � ������ ���...", "�� ��...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
            {
                link.l1 = "��������, ��� ��� ����� ������� ��������? �� ������ ��� ��� ������� �� �������.";
                link.l1.go = "Tortuga_ratT_1";
            }
            // ==> ��������� ���� ��������� �������.
            switch(pchar.questTemp.State)
            {
                case "WormEnglPlans_WormPicarder": //����������� �������, ����� �3. ������ � ������ ����������.
                    link.l1 = "��������, �� �� ������ ����������� ����� ����������?";
                    link.l1.go = "Step_H3_1";
                break;
                case "DelivLettTortuga_toStranger": //����������� �������, ����� �7. ������ � ��������� �� ��������.
                    link.l1 = "������, �� �� � ����� ����? ���� ��� ����, � "+ GetSexPhrase("������","�������") +" �� �������...";
                    link.l1.go = "Step_H7_1";
                break;
                case "DelivLettTortuga_AfterRape": //����������� �������, ����� �7. �������� ������, ��� ��� ���������.
                    link.l1 = "��� ���� �������, ��� ���� ���� � ������� �������?";
                    link.l1.go = "Step_H7_2";
                break;
                case "SeekBible_toTavern": //����������� �������, ����� �8. ������, ��� ����� �� ����.
                    link.l1 = "�� �� ������, ��� ��� ����� ����������� ������ �� �����?";
                    link.l1.go = "Step_H8_1";
                break;
                case "TakeRockBras_toTortuga": //��������� �������, ����� �3. ������, ��� ��� ��������.
                    link.l1 = "��������, �� ����������, ��� ��� ����� ���� ���������?";
                    link.l1.go = "Step_S3_1";
                break;
                case "Sp4Detection_toTortuga": //��������� �������, ����� �4. ������ � ����� ����.
                    link.l1 = "��� ������ �� �������?";
                    link.l1.go = "Step_S4_1";
                break;
                case "Sp6TakeMess_toTotuga": //��������� �������, ����� �6. ������ � ��������
                    link.l1 = "��������, ��������� � ������� �� ����� � ��� ������?";
                    link.l1.go = "Step_S6_1";
                break;
                case "Sp6TakeMess_waitMessanger": //��������� �������, ����� �6. ������ � ��������
                    link.l1 = "��������, ��������� � ������� �� ����� � ��� ������?";
                    link.l1.go = "Step_S6_1";
                break;
				if(PChar.Dozor == "8")
              	{
                    link.l2 = "�������� ������� ����� �� ���� ���������� �������.";
                    link.l2.go = "Dozor_1";
              	}
            }
            // <== ��������� ���� ��������� �������.
        break;
//===================================== ����. �������, ����� �3 =========================================
 	 	case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat("����, ��� �� �����. �� ���� � ���� ������� � �������� �� ��� ������!", "���, �� �� �� ��� "+ GetSexPhrase("���������","����������") +" ���� �� ����?", 
				          "��, �� �������� ��� � �����...", "����� �� �� ������ ���� ���������? � ���� ������� �� ������, ���� �� ��� ������� ��� ������.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� ��� ��! ������, � �������� � ���� ��� � �������...", ""+ GetSexPhrase("���������","����������") +"? �� ��, ��������...", "��, �����, ��������, ������...", "�� ���, �� �����. "+ GetSexPhrase("���","����") +" ��� �����...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H3_2":
			dialog.text = "��� ��! ������� ������ ��������� ��� ����������� � ��������� �� ��������� ���������� �������. �� ����� ������, ������� ��� ��� ���������.";
			link.l1 = "�������, ��� ��� �������...";
			link.l1.go = "Step_H3_3";
        break;
 	 	case "Step_H3_3":
			dialog.text = "�� ������ ��� ��� � ����� �������, ������� �������, ����� ������� ��� �������.";
			link.l1 = "�������, ��� � ������.";
			link.l1.go = "exit";
            pchar.questTemp.Talks.Tavern = true;
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "7");
        break;
//============================ ����. �������, ����� �7. ������ � ��������� �� ���� =======================
 	 	case "Step_H7_1":
			dialog.text = NPCStringReactionRepeat("� �����. ������ � ������� �������, ��� ���� ���� �����-�� ���.", "�� ��� "+ GetSexPhrase("�������","��������") +" ��� ���� ������ �������.", "�����?", "����� �� �� ������ ���� ��������� �� ������?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������, �������.", "�����, "+ GetSexPhrase("�������","��������") +"...", "��, ������...", "������, �� ����. ������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H7_2":
			dialog.text = NPCStringReactionRepeat("� ��� ����� ����, ������, ��� �� ��� �����������...", "�� ��� "+ GetSexPhrase("�������","��������") +" ��� ���� ������ �������.", "�����?", "����� �� �� ������ ���� ��������� �� ������?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("���� ������! ��� �� � ���� �� ����, �� ������?", "�����, "+ GetSexPhrase("�������","��������") +"...", "��, ������...", "������, �� ����. ������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H7_3", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
  	 	case "Step_H7_3":
			dialog.text = "�������� �� ����� ���������, ����� ������, ��� ���� ������ ��������. ������������� ��������� �� �������. �������, ���� � ����. � ���� �� ���� - ��� ��������.";
			link.l1 = "� �� ������ ������ �� ������ � ���?";
			link.l1.go = "Step_H7_4";
        break;
  	 	case "Step_H7_4":
			dialog.text = "������ � ��� �� �����, � ��������� �� �������, �������� ��� ���� �� �������. ����� ������ ���� ������� �� ����.";
			link.l1 = "�� ��� ��, ������� � �� ����...";
			link.l1.go = "exit";
        break;
//============================ ����. �������, ����� �8. ������ � ������ �� ����� =======================
  	 	case "Step_H8_1":
			dialog.text = "�� ������� �� ������ ��� �� �������. ���� ������ ����� �� ���� �� ������. �����, ������, �������� ���������...";
			link.l1 = "� ���� �� ����, ����� �� �� ������?";
			link.l1.go = "Step_H8_2";
        break;
  	 	case "Step_H8_2":
			dialog.text = "� ����� ������ ���-�� �� ������� ���������������� �����������.";
			link.l1 = "�������... � � ���� ����� ������?";
			link.l1.go = "Step_H8_3";
        break;
  	 	case "Step_H8_3":
			dialog.text = "� ����� ����?";
			link.l1 = "�� ��� ����� ������ �� ����� ������� ����. "+ GetSexPhrase("�����","������") +" ��� �� ��������, ������ ��� �����. � "+ GetSexPhrase("��� ���������","���� ���������") +", ��� � �����...";
			link.l1.go = "Step_H8_4";
        break;
   	 	case "Step_H8_4":
			dialog.text = "�����, ����� ����, ��� ��� ����. ������ �, ��� �� ��������� ����� � ����������. �� ���� ����� � ����� ������������ ������ '�������'.";
			link.l1 = "�������. ������� ����, �������.";
			link.l1.go = "exit";
            pchar.questTemp.State = "SeekBible_toDeGraf";
            AddQuestRecord("Hol_Line_8_SeekBible", "5");
            Pchar.quest.SeekBible_SaveDeGraf.win_condition.l1 = "location";
            Pchar.quest.SeekBible_SaveDeGraf.win_condition.l1.location = "Cartahena";
            Pchar.quest.SeekBible_SaveDeGraf.win_condition = "SeekBible_SaveDeGraf";
        break;
//============================ ���. �������, ����� �3. ������ � ���� ��������� =======================
  	 	case "Step_S3_1":
			dialog.text = "������ ����� �� ���� �����. ��� ������?";
			link.l1 = "�� ��� ����� ������, � ���� � ���� ��������� ����.";
			link.l1.go = "Step_S3_2";
        break;
  	 	case "Step_S3_2":
			dialog.text = "����� ��� ��������. ��� ���� � ����� � ��������� �� ����� �������, ����� ����������� �����, ���� �� �������� ������ � ��������� �������.";
			link.l1 = "��� ���! �� ��� �� ������ �������, ��� ��� ��� ���� ����� ������� � ���� ������. �������, ��� ������� ��� ���. ������� ����.";
			link.l1.go = "Step_S3_3";
        break;
  	 	case "Step_S3_3":
			dialog.text = "�� �� �� ���...";
			link.l1 = "���� ������, �������.";
			link.l1.go = "exit";
            pchar.questTemp.State = "TakeRockBras_toNearestMaracaibo";
            AddQuestRecord("Spa_Line_3_RockBrasilian", "2");
			pchar.quest.TakeRockBras_toRock.win_condition.l1 = "location";
			pchar.quest.TakeRockBras_toRock.win_condition.l1.location = "Maracaibo";
			pchar.quest.TakeRockBras_toRock.win_condition = "TakeRockBras_toRock";
        break;
//============================ ��������� �������, ����� �4. ������ � ����� ����. =======================
  	 	case "Step_S4_1":
			dialog.text = "�� ��� �� �������, ����� � ���������� ���������.";
			link.l1 = "�-�-�, ��� ���� �������. � ��� ��������, ���� � ��� � ������? �������, �������, �������...";
			link.l1.go = "Step_S4_2";
        break;
  	 	case "Step_S4_2":
			dialog.text = "�� ��������� ������� �� ���� �� �����. �� ������ � ������ ���������� �������-����������� �'������� ���� ��������� �������, �-�-����� ��������. �������-���������� ������ �������� � ��� � ���� �� ���� � ���� �� �������� ������. �� ����, ��� �����, ��-��...";
			link.l1 = "��� ���! � ��� ���, ��� �������� �������?";
			link.l1.go = "Step_S4_3";
        break;
  	 	case "Step_S4_3":
			dialog.text = "����� ���� - ��� �� ����� ���. ������ �, ��� ��� �� ������.";
			link.l1 = "�� ������ ����������� ��� �� ����������. ��� ��� ������ � �'�������, ��������� �� ��������� �������?";
			link.l1.go = "Step_S4_4";
        break;
  	 	case "Step_S4_4":
			dialog.text = "��-�-��, ����� �������� �������. ����� ���� ��� �� ����� ������ �������-�����������, ��� � �� ��. ������ �, ��� ��� ������������� ��� � ������ �����. ������ �� �� ������� ���� �� ���������� �������� �������-����������� - ���� �'�����, � ��� �� �� ����� - ����� �� �����.";
			link.l1 = "�������... � ��� ������ ���� ���� �'�����?";
			link.l1.go = "Step_S4_5";
        break;
  	 	case "Step_S4_5":
			dialog.text = "� ����, ��������. � ���� ��� ����� �� �������.";
			link.l1 = "����, ��� ������� ���������� � � ����� ������ � ������ "+ GetSexPhrase("���","����") +". ���� ������, ��������.";
			link.l1.go = "exit";
            pchar.questTemp.State = "Sp4Detection_toDEstre";
            AddQuestRecord("Spa_Line_4_MirderDetection", "5");
        break;
//============================ ��������� �������, ����� �6. ����������� ���������. =======================
  	 	case "Step_S6_1":
			dialog.text = NPCStringReactionRepeat("������, � ��� ���� �� ���?",
                          "��������� ��? ������, ������...", "�������� �� �� � ���������� �������...",
                          "� ������ �� ���� �������� � ����������...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("� ��� ��� ������ �������� �� �����������. ��� ��� �������� � ���� ����� ������� �� ��������.",
                      "�������!", "��������, �����...", "������, ��� �������...", npchar, Dialog.CurrentNode);
			link.l1.go =  DialogGoNodeRepeat("Step_S6_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
  	 	case "Step_S6_2":
			dialog.text = "��� �������, ������� ��������. ����� 35 ����� �� ������ - � ����.";
			link.l1 = "� ���� ����� ����� ������� �� ������, ��� ����� 35 �����? �����...";
			link.l1.go = "Step_S6_3";
        break;
  	 	case "Step_S6_3":
			dialog.text = "���, �� ������� ����, "+ GetSexPhrase("������ �������","������ �������") +". �� ����� �� ��������. � ������� ������ �������� ���� ����� ������, ��� �������.";
			link.l1 = "�������.";
			link.l1.go = "exit";
			pchar.questTemp.State.Open = 1;
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false);
            AddMoneyToCharacter(pchar, -100);
            if (CheckAttribute(pchar, "questTemp.State.Sp6Ok"))
            {
                SetTimerCondition("Sp6TakeMess_waitingBoy", 0, 0, rand(7)+1, false);
                DeleteAttribute(pchar, "questTemp.State.Sp6Ok");
            }
            else
            {
                pchar.questTemp.State.Sp6Ok = 1;
            }
        break;
        
		case "Tortuga_ratT_1":
			dialog.text = "������� �������? � ��� ��� �����? � �� ���� �������� � ����� ������.";
			link.l1 = "��, �� ������� ������� '" + pchar.questTemp.Slavetrader.ShipName + "'.";
			link.l1.go = "Tortuga_ratT_2";
        break;
		
		case "Tortuga_ratT_2":
			dialog.text = "�� ���� �� ��������� �������������, "+ GetSexPhrase("�������","���") +". � ������ � ����� ��������� � ��� � ����� �� ����������, � ���������� ����� ����.";
			link.l1 = "�� ������, � ������� � ������ � ��������� ����� �� �����?";
			link.l1.go = "Tortuga_ratT_3";
        break;
		
		case "Tortuga_ratT_3":
			dialog.text = "��, �������"+ GetSexPhrase("","�") +"! ��� �� �������� �����, � �� �������. ��� ������ ������ ���� ����������... ����, ������ � ��� �����-�� �������� �����, ������� ������������ � ���\n����� ������ ������, ��������, � �� ����� ������ ��������, ������ �� ��������� �������. �� ��� � ������� �������� - ���, ��� � �������. �� ������� ��� ����� �� �� ������� - �� � �����, �� �� ����� - �� ������ �������, ��������?";
			link.l1 = "��... �� ��� ��, �������. �������, " + npchar.name + ".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//�������
        break;
        
            // DOZOR -->
		case "Dozor_1":
			TakeNItems(PChar, "Dozor_Mekakhrom", 1);
			dialog.text = "�-�! ��� ��� ��, ��������? ����� ����, ������� ��� ��� �������, �������! ��� ���� �������� � �������� ��������. ����� ���� ���������� � ���, ��� ����� ��������� ��������� �����.";
			link.l1 = "�����.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorTortugaTavernGetItem");
		break;
			// DOZOR <--
        
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

