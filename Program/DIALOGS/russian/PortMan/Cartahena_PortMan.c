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
			//���, �����
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
    			if (pchar.questTemp.Headhunter == "Rat" && pchar.questTemp.Headhunter.countC == 0)
	    		{
		    		link.l1 = "�������, � ������"+ GetSexPhrase("","�") +", �� ��� �����, �� ������ �� ������ �����, ������� �������� �����. �� ������ ���������� ��� �� ���� ���������?";
			    	link.l1.go = "Rat_portmanC";
	    		}
			}
		break;
		
		//���, �����
		case "Rat_portmanC":
			dialog.text = "� ��� ��� ������������. ���������� � ����� �������� ����� '���������� �������' �������� ��� �������, ����� � ���� - � � ���� ���������� �� ������. � ����� ������� �� ���� ������ ����������� ������, � ���� ��� �� ��������.";
			link.l1 = "�����, ����������, ����� �������, ����� '���������� �������', �������� ������ � �� �� �����?";
			link.l1.go = "Rat_portmanC_1";
		break;
		
		case "Rat_portmanC_1":
			dialog.text = "��������, �������. ������, ��������� ������... ������ '���-����-����������' � ����� '��������'.";
			link.l1 = "�������!";
			link.l1.go = "CheckC";
			pchar.questTemp.Headhunter.count = sti(pchar.questTemp.Headhunter.count) + 1;
			pchar.questTemp.Headhunter.countC = 1;
		break;
		
		case "CheckC":
			if(pchar.questTemp.Headhunter.count == 3)
			{
				pchar.questTemp.Headhunter = "Rat_Tavern";
				pchar.questTemp.Headhunter.Ratrumcity = npchar.city;
				AddQuestRecord("Headhunt", "13");
			}
			else
			{
				AddQuestRecord("Headhunt", "12_1");
			}
			DialogExit();
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}


