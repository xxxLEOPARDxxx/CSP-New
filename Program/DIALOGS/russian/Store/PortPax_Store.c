// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("���������, ���� �� ������?",
                          "�� ������ ��� ��������� ��� ����. ��, ��������, ������������...", "������� �� ��� ������ ��� �������� � �����-�� �������...",
                          "��������, ��� �������, ����� ���� �������� ���-��. �� �������� ����!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������, " + NPChar.name + ", ���-������ � ��������� ���.", "�����, "+ GetSexPhrase("�����","������") +" ���-��...",
                      "�� ��, ������������� � ������ ���...", "��, �� ����...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            if (CheckAttribute(pchar, "questTemp.Azzy.GiveRum"))
            {
        		Link.l1 = "�������� ��������, ���� ������� � ���� ����� ����.";
        	    Link.l1.go = "Step_Az6";
                if (pchar.questTemp.Azzy.GiveRum == "OK")
                {
            		Link.l1 = "� ���� ������� ���������� ��� ���.";
            	    Link.l1.go = "Step_Az8";
                }
            }
            if (pchar.questTemp.Azzy == "HowToKnowAzzy")
            {
    			Link.l2 = "��������, ��� ������ ����� ����� ����!";
    			Link.l2.go = "Step_Az10";
            }
		break;
		//============================== ����� ���� ===============================
 		case "Step_Az6":
        	dialog.text = "�-�-�, C�� ���� ������� ���� �� ���?! ����� ��� ������� � ��� - ����� �������� � ������� �������! � ��� �� �� ���� ������?";
    		link.l1 = "�������?! ��, �� �����... �� ������ ���, ��� � ���� ����� � ���� ��� ��������� � ������� ������.";
    		link.l1.go = "Step_Az7";
		break;

 		case "Step_Az7":
        	dialog.text = "��, �� ������ ���. �� ������ ����� � ���� 300 � ���� ���� ��� � ����. �, ����������, ���������.";
    		link.l1 = "���������, ��� ���� ����������. ��������� � ���������?";
    		link.l1.go = "Step_Az8";
    		pchar.questTemp.Azzy.GiveRum = "OK";
		break;

 		case "Step_Az8":
        	dialog.text = NPCStringReactionRepeat("� ���� ���� ���� 300�. ����.",
                       "�� ��� "+ GetSexPhrase("����","�����") +" ������� ���������� ���� ���.",
                       "� �� ������ ����, ��� ���� ��� �� ������� �� "+ GetSexPhrase("������","�������") +". ������� ������.",
                       "������, ������� ������...", "block", 1, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("������, ���� ���!!!", "�����, "+ GetSexPhrase("����","�����") +"...", "������...", "��, ����� �� ������.", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_Az9", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;

 		case "Step_Az9":
        	dialog.text = "�������� �������� �������� � �����. ��� ��� �����.";
    		link.l1 = "��� ������. �������, �������.";
    		link.l1.go = "exit";
            AddCharacterGoods(Pchar, GOOD_RUM, 300);
		break;

 		case "Step_Az10":
        	dialog.text = NPCStringReactionRepeat("� �� ����, ��� ����. ������� �� ���� ������.",
                                    "������� ���, �� ����, ��� ��.",
                                    "��������, �� ���� �, ��� ����.",
                                    "��� ��� ������, ��� �� ����, ��� ����. �� � ����� �� �����.", "block", 0, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat("�� �� �� ��������� �� ���� ���, ������� � � ���� ����.", "��, �����, �������", "��������� �� ����, ����� �.", "����, ����� ����...", npchar, Dialog.CurrentNode);
    		link.l1.go = DialogGoNodeRepeat("Step_Az11", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;

 		case "Step_Az11":
        	dialog.text = "��� ��� � ������ �� ����, ��� ��� ��������. � ������ �� ���� �������� ����� �� ������ ����� ��������, � ����� ��� ��� ���. ������ ����� � �������� ����, ��� ����� ������ ����. ������ ���� ������ ������������ ������.";
    		link.l1 = "��� ����... ������ ���� ������������ ����� ���, ��� ������� ���� ���!";
    		link.l1.go = "Step_Az12";
		break;

 		case "Step_Az12":
        	dialog.text = "� ��� ����� � �� ������ �� ����. ��� �������� ���������������� ���, ��������� ���� � �����, ����������� �����. ������ ����� ����� ��� ����� � ����� ��������, ������ ����� ������ �����, ����� ������� � �����.\n"+
                          "� �� ����, ��� ����� ���� ����, �� ����� ��� �� ��� ��������� ����. ������� �� ����, ������ ��.\n"+
                          "� ������� �� ��� ���� ������ �� �������. ������� � ��� �����, ��������, �����, ��� ����. � ��� ����� ����� �� �����. ��� ���, "+ GetSexPhrase("�������","�������") +".";
    		link.l1 = "�� ��, �������, ��� ����� ���� � �� �����.";
    		link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

