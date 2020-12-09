
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    switch (Dialog.CurrentNode)
    {
        case "First time":
			dialog.text = "�� � ��� ��������.";
			link.l1 = "�����...";
            link.l1.go = "exit";
//>>>>>>>>>>>>========= ������� �������� �� ���������� =====================
            if (pchar.questTemp.Ascold == "SeekInformatorHavanna" || pchar.questTemp.Ascold == "2SeekInformatorHavanna")
            {
            	dialog.text = "������ ����, ��� �� � ��� �� ������?";
        		link.l1 = "���� ����� " + GetFullName(pchar) + ". � ������"+ GetSexPhrase("","�") +" ���� �� ��������� ��������.";
        		link.l1.go = "Step_1";
            }
            if (pchar.questTemp.Ascold == "ReciveInformationManowar")
            {
            	dialog.text = "� �������, ���������� �� ��������� � ����, �� ��� �� ���������, ���� � "+ GetSexPhrase("����","��������") +" ��������.";
        		link.l1 = "�� ��� ������...";
        		link.l1.go = "exit";
            }
        break;
//<<<<<<<<<<<<======== ������� �������� �� ���������� ======================
 		case "Step_1":
        	dialog.text = "������ ��������?";
    		link.l1 = "�������������, ������� �� ��������� �����. ������� �� ������� ���.";
    		link.l1.go = "Step_2";
		break;
 		case "Step_2":
        	dialog.text = "�������� ����, � ��� ��������� �����. ��� ����� ����� ����� ��������?";
    		link.l1 = "���� ���� ��������. �������� ����� ����� �� ������ ���� �������, ��� ������� ��������� ���������� ���������� ������.";
    		link.l1.go = "Step_3";
		break;
 		case "Step_3":
        	dialog.text = "��, ��� ������� - ��� ������ �������. ���� ��� �������� ���������� ������, �� �� ��� �� � �����.\n"+
                          "� ��� �������������� � ������ � ����� �������� ����������� ����������� ������.";
    		link.l1 = "��� ��-�� � ����� ��������, ���� ������.";
    		link.l1.go = "Step_4";
		break;
 		case "Step_4":
        	dialog.text = "���� ��, ��� �� ��� ����� - ������ �� �����. �� � ������ �� ������� ��� � �������� �����.\n"+
                          "������ ���� �� ����, ��� ��� ������.";
    		link.l1 = "� �������. ������������, ��� ��� ����� �����, ��� ���� ���� �������.";
    		link.l1.go = "Step_5";
		break;
 		case "Step_5":
        	dialog.text = "�� ���� � ����� �������, ��� ����� ������. �� ���� ������ ������� ��������� � ������� ������.";
    		link.l1 = "��� ��� ��! �������� �����... � ���, ��� � ���� ����?";
    		link.l1.go = "Step_6";
		break;
 		case "Step_6":
        	dialog.text = "��, ���� ����. ���� � ���, ��� ������ - ����� ����� � ������ �������� � ��������� ������� � �������. �������������, � �������, ������ ������ ����� ����� ����������� ��������� ����, � ������ ��� �������� ����������� ��c�������. � �� ����� ����, ��� ���������� �������� ������, ������� ������ ���� � ������ ����.\n"+
                          "��� ���, ��� � ����.";
    		link.l1 = "����� �������, �������, ����. ������� �� ���� ������ ��������.";
    		link.l1.go = "Step_7";
		break;
 		case "Step_7":
        	dialog.text = "��, "+ GetSexPhrase("����","�������") +", �������! � ������?";
    		link.l1 = "��������, � ���� ����� ����, ������� - ������. � ������ �������� ������ ������. ��� ��� ������, ����� � �� ����� ������!";
    		link.l1.go = "exit";
			npchar.LifeDay = 5;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
            AddQuestRecord("Ascold", "7");
            pchar.questTemp.Ascold = "ReciveInformationManowar";
            Pchar.quest.Ascold_AttackTenManowars.win_condition.l1 = "location";
            Pchar.quest.Ascold_AttackTenManowars.win_condition.l1.location = "Caiman";
            Pchar.quest.Ascold_AttackTenManowars.win_condition = "Ascold_AttackTenManowars";
		break;



        case "Step_":
            dialog.text = "";
            link.l1 = "";
            link.l1.go = "Step_";
        break;
 		case "Exit":
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
    }
}
