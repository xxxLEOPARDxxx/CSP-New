// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), "������ ������� �� �������� ������ ��� ������ " + GetAddress_Form(NPChar) + "...", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������...",
                          "����������, ���� �� �� �� ����� �����, �� �� ����� ���� ��������� ��������.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� ��, ������������� � ������ ���...", "��������, �� �������� ���� ���� ������ �� ����������.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> ����� �7 ����.�������, ������� ����������� ������
            if (pchar.questTemp.State == "DelivLettTortuga_toPortMan")
            {
    			link.l1 = "�'������ �������� ���� � ����, ����� �� ���������� ������ ���, ��� �� ����� �������� ���� ������� � ������� ��������� ���� �����!";
    			link.l1.go = "Step_H7_1";
            }
            if (pchar.questTemp.State == "Sp6TakeMess_toTotuga")
            {
                link.l1 = "� �����������"+ GetSexPhrase("","�") +" ������������������� ��� ���� �������� � ���������� � ����� �����������. �������� �������� ��� �������� ������������ ����������� ���-������� ��������.";
                link.l1.go = "Step_S6_1";
            }
            if (pchar.questTemp.State == "Sp6TakeMess_waitMessanger")
            {
                link.l1 = "����������, �� ���� ��� ���������� ���� ������������ �������?";
                link.l1.go = "Step_S6_6";
            }
            if (pchar.questTemp.State == "Fr4SoleiRoyal_toPortMan")
            {
                link.l1 = "�������� ����������� �'������� ��� ����� �������� � ��� ������������ �������� ������� ������� ������ '����� ������'.";
                link.l1.go = "Step_F4_1";
            }
			
			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
            {
                link.l1 = "������ ����. � ��� ������� ��������. ��� ������ '" + pchar.questTemp.Slavetrader.ShipName + "', ������ ��� ������� ����� � ����� ������.";
                link.l1.go = "Tortuga_ratP_1";
            }
			
		break;

//************************************* ����. �������, ����� �7, �������� ������ *******************************
		case "Step_H7_1":
            dialog.text = "������ ���� - ���� '�� ������'. �� ���� �� ������-���� �� ����������� � ���-�����. � ��� ���� � �������� ������������� ����������� ���-������� ��������.";
			link.l1 = "����� �������������?!";
			link.l1.go = "Step_H7_2";
		break;
		case "Step_H7_2":
            dialog.text = "� �� ������: ������������� ����������� ���-������� ��������. �� ������ ���� ��������� ���� ����� � ����� ��������� ������������ ��������. ���� ���� �� ������ � ����� ����������� ������ ����� � ���, �� �������, ��� ���� ����� �������� �����. � � �������� ��� � ���.\n"+
                          "�� � ��������� ������ ����� � ����, ������, ����������, � �� ���� � ������, �� ������� � ������ �� �������, ����������.";
			link.l1 = "���� ������, ������, ��� ��� � ���� �������...";
			link.l1.go = "Step_H7_3";
		break;
		case "Step_H7_3":
            dialog.text = "���������� ���������, ������ ��... ��... �� ������� ���.";
			link.l1 = "� ����"+ GetSexPhrase("��","��") +" ���������� ������� ���� ��������� ����. ��� ������ ����� � ������.";
			link.l1.go = "Step_H7_4";
		break;
		case "Step_H7_4":
            dialog.text = "�������? ��� ��, ��� ��������. � ����� ������ �� ������� �������.";
			link.l1 = "������� ���� �� ���������, ���� ������� ������������� �� ������� � ������� � ���� � ���� ���...";
			link.l1.go = "exit";
            AddQuestRecord("Hol_Line_7_DelivLettTortuga", "5");
			pchar.questTemp.State = "DelivLettTortuga_NotFoundLetter";
            Pchar.quest.DelivLettTortuga_AttackBrig.win_condition.l1 = "location";
            Pchar.quest.DelivLettTortuga_AttackBrig.win_condition.l1.location = "PuertoRico";
            Pchar.quest.DelivLettTortuga_AttackBrig.win_condition = "DelivLettTortuga_AttackBrig";
            SetTimerCondition("DelivLettTortuga_BrigTimeOver", 0, 0, 5, false);
		break;
//************************************* ��������� �������, ����� �6, �������� ��������� *******************************
		case "Step_S6_1":
            dialog.text = NPCStringReactionRepeat("��, ����. �� ����� ��� ��������� ����� �� ���? � �� ��������� ��������� ����������...",
                          "��, ��, � ���� ���...", "���? ����� ��?", "�� ������� �����? ���������� �� ��� ���� ������...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("� ��� ����. � ���� � ��� ������� ������� ��������... ���� � ���, ��� � ����������� ��������"+ GetSexPhrase("","�") +" ����� ����, �� ������� ������"+ GetSexPhrase("","�") +". ����� � ����"+ GetSexPhrase("��","��") +" ������� � ����������, ��� �� ������� �������. ��� ���, � �� �����"+ GetSexPhrase("","�") +" ������� ��� �� �������� �����. ����� �� ���������� ���, ��� �� � ��� � ����� ���������� ������������ �����, ������ �� �������?",
                     "�-�-�, �� �����...", "��, �...", "��? �� ������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S6_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
 		case "Step_S6_2":
            dialog.text = "��, ���� ���. ��, �������, � ������ ������� �������� - ��������� �� ����������� ����� �������� ����� ������.";
			link.l1 = "��������?";
			link.l1.go = "Step_S6_3";
		break;
 		case "Step_S6_3":
            dialog.text = "������ � ��������, �� � �� ��� �������������� ��������� ������� � �������� �� �������. ��� ������� �� ������������� ����� �������, ���-��� � ���������� � ������ �������-����������� - � ����� ������� � ����������. � ��� �������-���������� �� ��� ����� ������ �� ���������...";
			link.l1 = "�, ��� ���������, ��������� ������� ��� ����. �� ������ �� �� ��� ������� �������� ���, ����� ����� ������� ������ � ���� �������?";
			link.l1.go = "Step_S6_4";
		break;
 		case "Step_S6_4":
            dialog.text = "������. ��� �� ������������, "+ GetSexPhrase("�����","�����������") +"?";
			link.l1 = "� ����"+ GetSexPhrase("","�") +" ������� � �������.";
			link.l1.go = "Step_S6_5";
		break;
 		case "Step_S6_5":
            dialog.text = "���������. ��� ������ ����������� ������� ������ ����� � ��� � �����, � ���������� ������ � ��� � ������� ���������� � ���� �����������.";
			link.l1 = "����� ������. �������� ��� �������, �����. �� ������� ������ ����� ��������, �� ����� �� �������.";
			link.l1.go = "exit";
            AddQuestRecord("Spa_Line_6_TakeMessangeer", "2");
            pchar.questTemp.State = "Sp6TakeMess_waitMessanger";
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
 		case "Step_S6_6":
            dialog.text = "���, ��� �� ����. � �� ������ ���, ��� �������� ����������. �� ������������, � ����� � ���.";
			link.l1 = "�������, �����. � �������� �� ������������...";
			link.l1.go = "exit";
		break;
//************************************* ����������� �������, ����� �4, ����� ������ *******************************
 		case "Step_F4_1":
    		if (GetCompanionQuantity(pchar) == 1)
            {
                dialog.text = "��, � ��� ���������, "+ GetSexPhrase("�����","�����������") +". ���������� ������������. �� ����� �������, ����������� ����� �������� - ������� ���� ��� ��������...";
    			link.l1 = "��������� ������"+ GetSexPhrase("��","��") +" � ���� ������������, ������... � ������ ��������� ����������� - ����.";
    			link.l1.go = "Step_F4_2";
            }
            else
            {
                dialog.text = "��� ���������� ��������� �� �������������� ����� � ����� �������. ����� �� ������ ��������� ����� ����, ������� �������� �������, ������ �� ������ �������� ������� �� ������ ���� ���������� �� ��������� ������������.";
    			link.l1 = "������, � ��� ������.";
    			link.l1.go = "exit";
            }
		break;	
 		case "Step_F4_2":
    		pchar.questTemp.State = "Fr4SoleiRoyal_toBasTer";
			SaveCurrentQuestDateParam("questTemp");
			AddQuestRecord("Fra_Line_4_SoleiRoyal", "2");
			ref sld = GetCharacter(NPC_GenerateCharacter("SoleiRoyalCaptain", "off_fra_2", "man", "man", 35, FRANCE, -1, true));
			sld.Ship.Name = "����� ������";
			sld.Ship.Type = CreateBaseShip(SHIP_SOLEYRU);
			ResetShipCannonsDamages(sld);
			SetBaseShipData(sld);			
			SetCrewQuantityFull(sld);
			Fantom_SetBalls(sld, "pirate");	
			FantomMakeCoolFighter(sld, 35, 80, 70, BLADE_LONG, "pistol3", 100);	
			
			sld.CompanionEnemyEnable = false;
			sld.Abordage.Enable = false; // ������!
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetShipRemovable(sld, false);
			
            Pchar.quest.Fr4SoleiRoyal_Fight.win_condition.l1 = "location";
            Pchar.quest.Fr4SoleiRoyal_Fight.win_condition.l1.location = "Dominica";
            Pchar.quest.Fr4SoleiRoyal_Fight.win_condition = "Fr4SoleiRoyal_Fight";
			DialogExit();
		break;	

		case "Tortuga_ratP_1":
			dialog.text = NPCStringReactionRepeat("��... �������� ��� ��������. ������ '" + pchar.questTemp.Slavetrader.ShipName + "' � ��� � ���� �� �������, � ������� ������� �� ���������.", "�� ��� "+ GetSexPhrase("����������","����������") +" �� ����, � ��� �������.", "� �� ������ ���, �� ��� "+ GetSexPhrase("����������","����������") +" �� ���� ��������.", "� ����� �� ������ ��� ��������!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� ��� ��... � ���� �� �� �����? �����, ����� ����������� � ������.", "��, �� ��...", "��, �����, "+ GetSexPhrase("���������","����������") +"...", "��������, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

