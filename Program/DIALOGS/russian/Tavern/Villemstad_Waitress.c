// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("�������, " + GetAddress_Form(NPChar) + "?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("��, �� �� ��������� �� �� �� ���, " + GetAddress_Form(NPChar) + "? ","����� �� ��������� ���������? �������, ������ �� �� ����, ��� ��...") +"", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������..."+ GetSexPhrase(" ��� ����� ��������?","") +"",
                          "����� ������� ������ ��������, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� ���������"+ GetSexPhrase("","�") +"...", "������ ��� �� � ��� ��������"), "�� ���, ��� ��, ���������...",
                      "����� ���, ��������, �������...", "�� ���, ����� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//==> ��������� ���� ��������� �������
            if (CheckAttribute(pchar, "questTemp.State.Usurer"))
            {
                dialog.text = "�� ���-�� ������ ��� �������?";
    			link.l1 = ""+ GetSexPhrase("��. � ���� �������, ��� �� ������������ ���������, ���������. ���� �������� �� ������ � ������.","��� �� ����� ������������, �������? ����� �������?") +"";
    			link.l1.go = "Step_S2_1";
            }
            //<== ��������� ���� ��������� �������
		break;
//*************************** ����� �2 �������, ������� ���������� ***************************
 		case "Step_S2_1":
    		dialog.text = NPCStringReactionRepeat("��...", "��, ���������� �� ��� �� ����...", "����������, �� ���������� - � ���...", "��� ��� �� ��������� � ������ �������. "+ GetSexPhrase("�������, ��� ���� � ���� - � �� ��� ��� ���, �������?","") +"", "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("��� ��� �� ��, ���� �������? �����, � ����� ������?", "��, �����.", "������, ������...", ""+ GetSexPhrase("�� ������ � �� �����, ���������. ��� ���������...","�����...") +"", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
 		break;
 		case "Step_S2_2":
    		dialog.text = "��� ��� ���������� - �����! ��... ��...";
    		link.l1 = "(����� �����!) � ��� ��� ��� ����� ��������. ��� �� �� ���� ������? � ��� � ���� ��� �����?";
    		link.l1.go = "Step_S2_3";
 		break;
 		case "Step_S2_3":
    		dialog.text = "�� ������� ����. �������� ������� ����, �������� ������, � ��� �������! ������ ����� � �������� �� ������� � ���� �����!";
    		link.l1 = "��� �������! ������� - ����� ������.";
    		link.l1.go = "Step_S2_4";
 		break;
 		case "Step_S2_4":
    		dialog.text = "� ����� �� �� ����� �����? ����� ��������� ���, ��� �� �� �� ��������� � �������. ����� � ��� ����� ���������!";
    		link.l1 = "�� ������, �������.";
    		link.l1.go = "exit";
            AddQuestRecord("Spa_Line_2_Inquisition", "6");
            Pchar.quest.Inquisition_AttackLugger.win_condition.l1 = "location";
            Pchar.quest.Inquisition_AttackLugger.win_condition.l1.location = "Jamaica";
            Pchar.quest.Inquisition_AttackLugger.win_condition = "Inquisition_AttackLugger";
            SetTimerCondition("Inquisition_LuggerTimeOver", 0, 0, 20, false);
 		break;



	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

