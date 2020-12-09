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
            // ==> ����� �6 ����.�������, ����� � ������
            if (pchar.questTemp.State == "MorrisWillams_SeekSpanishGoods")
            {
    			link.l1 = "��������, � ���� � ����� �� ���� �������� � ��������� �����?";
    			link.l1.go = "Step_E6_1";
            }
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "������ ����. � ��� �� ��������� ������� ������� �������, ��������� �� ����� �����? � ���� ������ �� ����� '" + pchar.questTemp.Slavetrader.ShipName + "'.";
                link.l1.go = "Jamaica_ratPP_1";
            }
			
		break;
//************************************* ������� �� ����.������� *******************************
		case "Step_E6_1":
            dialog.text = "������� ����� ������ �����. �� ���� ������ ������� ����� ������ ����� �����, ������ ��� ������� ������ ���������.";
			link.l1 = "��� ��� ��! � ���� ��� ���������� �������� �������� ��������� �������?";
			link.l1.go = "Step_E6_2";
		break;

		case "Step_E6_2":
            dialog.text = "�� ���� ��� �����, �� �����, ������ �������-�����������.";
			link.l1 = "� ��� ������ ���� �������? � ��� �� �������?";
			link.l1.go = "Step_E6_3";
		break;

		case "Step_E6_3":
            dialog.text = "����� '����� ������', ���� ����� � �������� ������ ������ �� ���-����. � ��� ���� �������?";
			link.l1 = "���� ��������� � ���������, �� ��� ������...";
			link.l1.go = "Step_E6_4";
		break;

		case "Step_E6_4":
            dialog.text = "���, ������... �� �� ����, ��� ����� ����������. ���� �� ������ ������� ����� ������ �� ���-�����, ���� ����� ����� � ���� ����� ������. �� � ��, �������� �� - ������� ������...";
			link.l1 = "���-���� ���������. �� �������� � ���� ������.";
			link.l1.go = "exit";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "9");
			pchar.questTemp.State = "MorrisWillams_CatchUpPinnace";
            SaveCurrentQuestDateParam("questTemp");
			pchar.quest.MorrisWillams_CheckTimeForForward.win_condition.l1 = "location";
			pchar.quest.MorrisWillams_CheckTimeForForward.win_condition.l1.location = "Jamaica";
			pchar.quest.MorrisWillams_CheckTimeForForward.win_condition = "MorrisWillams_CheckTimeForForward";
		break;
		
		case "Jamaica_ratPP_1":
			dialog.text = NPCStringReactionRepeat("���. ������� ������� �� ���������, � ������ '" + pchar.questTemp.Slavetrader.ShipName + "' � ���� ����-����� �� �������.", "�� ��� "+ GetSexPhrase("����������","����������") +" �� ����, � ��� �������.", "� �� ������ ����, �� ��� "+ GetSexPhrase("����������","����������") +" �� ���� ��������.", "� ����� ��� �� ������ ��� ��������!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("����. ����� ������ ������...", "��, �� ��...", "��, �����, "+ GetSexPhrase("���������","����������") +"...", "��������, " + npchar.name + "...", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

