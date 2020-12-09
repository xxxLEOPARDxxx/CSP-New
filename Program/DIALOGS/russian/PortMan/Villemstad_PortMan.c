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
            // ==> ����� �5 ����.�������, ������� ��� ������.
            if (pchar.questTemp.State == "ThreeFleutes_toPortMan")
            {
    			link.l1 = "� � ��� �� ��������� ����������. ��� ���������� ������� ������������ ��� ����� ��������.";
    			link.l1.go = "Step_H5_1";
            }
			//������������
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
            {
    			link.l1 = "� �� �����"+ GetSexPhrase("","�") +" ������ �� ������ �����, ���������� � ���� ����� ��������� �����.";
    			link.l1.go = "EscapeSlave_Villemstad_P1";
            }
			//���, �����
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
    			if (pchar.questTemp.Headhunter == "Rat" && pchar.questTemp.Headhunter.countV == 0)
    			{
    				link.l1 = "������"+ GetSexPhrase("","�") +", �������, �� ������ �� ������ �����, ������� �������� �����. �� ������ ���������� �� ���� �����������?";
	    			link.l1.go = "Rat_portmanV";
	    		}
			}
		break;

//************************************* ������� �� ����.������� *******************************
		case "Step_H5_1":
    		if (GetCompanionQuantity(pchar) == 1)
            {
                dialog.text = "����������, ����������. ��� ������ ��������� � ���� ������������.";
    			link.l1 = "�����������.";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("HL5_portManGiveFleuts");
            }
            else
            {
                dialog.text = "��, � � ����� ������� �������. ������, ����� ������� ������������ ��� ��������, ��� ���������� ����������� �� ����� �������. ����� ��� ������� ��� � ����� ����� ���������� �� ���.";
    			link.l1 = "������, � ��� � ������.";
    			link.l1.go = "exit";
            }
		break;
		//������������
		case "EscapeSlave_Villemstad_P1":
				dialog.text = "��... � � ����� ����� ����� ��� ��� ��������������?";
				link.l1 = "� �������� �� ��������� ������ ����������, ������-�����������. ���� ��������� ��������, ��� � ������������ ������� ��������� ������ ����. ������� � ����� ��� ������� ��� ��� ��������� ���������� � ��������.";
				link.l1.go = "EscapeSlave_Villemstad_P2";
		break;
		
		case "EscapeSlave_Villemstad_P2":
				dialog.text = "�������. ��, � ���������, � ���� ��� ���� ��� ������. ���� � ������ " + pchar.questTemp.Slavetrader.ShipName + ", ������ �����, ����� ������ �� ����� � �� ������. ��������� ����� ���������\n������ ������� �� ������� ������ ������ �� ���, ����������, ������ ��� ������� ������ �� ����. ����� ��� �����������, ��� ������� ��������� �����, ���������� � �������...";
				link.l1 = "�� ��, ������������� ���������� �������. �� ������� � �� ����. �� ��������.";
				link.l1.go = "exit";
				AddQuestRecord("Slavetrader", "22_3");
				AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
				pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
		break;
		
		//���, �����
		case "Rat_portmanV":
			dialog.text = "��, ���� ������ �����, ��� ����� ����, ������� ������ '����� ����' ����� �� ������, �, ��� �������, �� ������ � ��������� �����. ������ ��� ����� �� �����, � ������ ��� ��� ���������?";
			link.l1 = "���, ������ ���, ������� �������. ������� ������������ �� ����������?";
			link.l1.go = "Rat_portmanV_1";
		break;
		
		case "Rat_portmanV_1":
			dialog.text = "��� � ���� ����������, �������� �������... ��, ��� ����� ������ � ������� ������ '����� ����' ������ � ������ ������� ������ �� �����, ����� �������� ������. ���... � ���� ���������� �� ������. ����� �� � ���.";
			link.l1 = "�������, � ����� ������� ����� �� ������ � ��� �� ����, ��� ���� ����� ����� �������?";
			link.l1.go = "Rat_portmanV_2";
		break;
		
		case "Rat_portmanV_2":
			dialog.text = "������� ���������. � ��� ���� �������� ���� �������: ����� '��������', ������ '����������' � ������ '�������'.";
			link.l1 = "�������!";
			link.l1.go = "CheckV";
			pchar.questTemp.Headhunter.count = sti(pchar.questTemp.Headhunter.count) + 1;
			pchar.questTemp.Headhunter.countV = 1;
		break;
		
		case "CheckV":
			if(pchar.questTemp.Headhunter.count == 3)
			{
				pchar.questTemp.Headhunter = "Rat_Tavern";
				pchar.questTemp.Headhunter.Ratrumcity = npchar.city;
				AddQuestRecord("Headhunt", "13");
			}
			else
			{
				AddQuestRecord("Headhunt", "12_3");
			}
			DialogExit();
		break;
		
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

