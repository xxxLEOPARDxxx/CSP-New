// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("���������, ���� �� ������?",
                          "�� ������ ��� ��������� ��� ����. ��, ��������, ������������...", "������� �� ��� ������ ��� �������� � �����-�� �������...",
                          "��������, ��� �������, ����� ���� �������� ���-��. �� �������� ����!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������, " + NPChar.name + ", ���-������ � ��������� ���.", "�����, "+ GetSexPhrase("�����","������") +" ���-��...",
                      "�� ��, ������������� � ������ ���...", "��, �� ����...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = "���������, � ��� ���� ��������� �������, ������ '����� �����'. ������ � ��� �� �������? �� ����� ���������� � ��� � "+ GetSexPhrase("�����","������") +" ���������...";
				link.l1.go = "BlueBird_1";
			}
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
				bOk = pchar.questTemp.Headhunter == "end_quest_full" || pchar.questTemp.BlueBird == "weWon" || pchar.questTemp.BlueBird == "returnMoney" || pchar.questTemp.BlueBird == "over"; 
	    		if (bOk && !CheckAttribute(pchar,"questTemp.BlueBird.speakWon"))
    			{
		    		link.l1 = "� ��� ������� ������?";
	    			link.l1.go = "BlueBird_3";
    			}
			}
		break;
		case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat("� ������ �� ���� �� ���� �������. ���� ��� ���, ��� �� ������, �� �������.", 
				"�����? � ��� ��� ������.", 
				"���, ����� ��� �� ��?",
                "�� ����� �� ��� ��������?! ����� ���, �� ���������� ���� �� ������!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("���-�� �� ����� �� �������, ��������!", 
				"��-��, � �����...",
                "���.", 
				"������, ������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;
		case "BlueBird_2":
			dialog.text = "� ��� �� ��������, ��� �������� � ��� ������� � ���� �������� �� ���� ������������.";
			link.l1 = "� ���! �� � ������ "+ GetSexPhrase("�������","��������") +". �� �����, ������� � �� ����...";
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "2");
			AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("��","���"));
		break;

		case "BlueBird_3":
			if ( sti(pchar.Ship.Type) == SHIP_NOTUSED || pchar.location.from_sea != "Pirates_town")
			{
				dialog.text = "�� ����� � ������� ��� ���������� ������. ������������, ��� �� ��� ������� � ������� � ������� '����� �����'.";
				link.l1 = "� ���� �� ���� �������.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "�� ����� � ������� ��� ���������� ������. ������������, ��� �� ��� ������� � ������� � ������� '����� �����'. � ���� � ��� ���� ���� ���������� �����������. ��������, ��� ��� ������������.";
				link.l1 = "��� ���? �� ��� �, ��������� ���� ���������� �����������.";
				link.l1.go = "storage_rent";		
			}
			pchar.questTemp.BlueBird.speakWon = true;
		break;		
		
		case "storage_rent":
			dialog.text = "����� ��������� ������� � ��� ������������ �������, ��������� ��� �����. �� ������ ���������� �� ��������� �����? ����������� ����������� ���������...";
			link.l1 = "���������, ��������? ���������... � ������� ��? � ������� ��������� �� ������?";
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "�� ���������� ���������� ���� ��� ������������ �������� - ����������� 50000 �. �� " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + " � ����� � ����� ���������� ����������� ����� �������. "+
				"��� �������� ������ �� ������, ������ �� ����������� � ������ � ���������. �� ���, �������?.. ��, � ������������������, �������� ����, ����������.";
			link.l1 = "�������. ���� � ��� ���������?";	
			link.l1.go = "storage_rent2";
			link.l2 = "������� ������ �������. ���, ������, ���� �� ������ � ����� ����� ������.";
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = "�������-�������. ������ ��-�... ������ �� ����� ������� �����.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "���� ��... �������������. ������� ���� ������ - � ������� ���� �����.";
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 = "���� ��... �������������. ������ ������ �������.";
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = "��, ��� ������. ���� ��������� - �����������. ������ ������, ��� ����� ��������� ����� ��������� �� �����. ��� �� �� ��������.";
			link.l1 = "�� ����������. ���� ����������� - ������.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

