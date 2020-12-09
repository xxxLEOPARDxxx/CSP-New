// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), "������ ������� �� �������� ������ ��� ������, " + GetAddress_Form(NPChar) + "...", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������...",
                          "����� ������� ����� ��������?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� ��, ������������� � ������ ���...", "�� ���, ����� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.RomanticQuest == "SeekInPortoBello")
			{
				link.l1 = "��������, �� �� � �����, ����� �� ���� ����� �������� ����� '������������'?";
				link.l1.go = "Romantic_1";
			}
			
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "��������, �� ����� �� �� ������ �� ����� ������� �������? �� ������� ��� � ����� ������.";
                link.l1.go = "Portobello_rat_1";
            }
			
			if (CheckAttribute(pchar, "questTemp.mushket2x2_stid") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = "������, �������, �� �� ������, ��� ��� ����� �������� ������� - �������� ����� '������'?";
				if (GetQuestPastDayParam("questTemp.mushket2x2_stid") < 11)
				{
					link.l1.go = "Mushket_stid";
				}
				else
				{
					link.l1.go = "Mushket_late";
				}
			}
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("���, �� ����. � ������� �� �� �������, �� � � ������ � ��� �� �����.", "�� ��� "+ GetSexPhrase("���������","����������") +" �� ����, � ���� �������.", "� �� ������ ����, �� ��� "+ GetSexPhrase("���������","����������") +" �� ���� ��������.", "��������, ������ � �� �����! ������ ��� �� ����� �������?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�� ��� ��, ����� ������.", "��, �� ��...", "��, �����, "+ GetSexPhrase("���������","����������") +"...", "������, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			break;
		
		case "Mushket_stid":
			dialog.text = "��� ��� ��!.. A�-��-��! ����� ��� ���� ����������� ��� ������ ����, ���������� ��������� ������� ������?!";
			link.l1 = "�����... � ���� � ���� ����.";
			link.l1.go = "Mushket_stid_1";
			DeleteAttribute(pchar, "questTemp.mushket2x2_stid");
			break;
			
		case "Mushket_stid_1":
			dialog.text = "�� �������?! ����������, � ���� ���� � ���� '����', ����� ��� ����� �����. �� �� � ��� ��� �� ����� - ����-��������, ���� ����������. ������ �������������� ��� ������, ������ ��� ����� ��������� ����������. � ����� �� �� ������� - � ������ ��� ��������� ����. ���� ������ �� ���� ��������... � ����, �������� �� ������� �� ��� ���� ������?";
			link.l1 = "�� ���... ���� � ���� ������, ������� ��� �� �����������, �������� ����...";
			link.l1.go = "Mushket_stid_2";
		break;

		case "Mushket_stid_2":
			dialog.text = "��-��! �� ������� ���� ��� ����������� ����� �� ����������� - ������� ��������, ��� ������, ��� ������ ��� �������. ���� ��� - '������' ����������� ��� ������� - ������ � �������� �� ���� ������, �� ����� ��������.\n������, � �� �� �������� �� ��� �� ���� �������"+ GetSexPhrase("","�") +", �? � �� � ��� ����� - ��� �� '����' � ���� � ����! ������ ���� - ������ ����� �������� ������� ���� �� ���, ������, ��� �� �������� ������. ����� �� � ���� ������ - ������� ��������, ����� �������.";
			link.l1 = "�� �� ����� ��� ��� ����! �� ������ ������ ������� - ��� ��� �����?";
			link.l1.go = "Mushket_stid_3";
		break;		
			
		case "Mushket_stid_3":
			dialog.text = "�� �����-��������, �������� �� ������, ������� ����� �� ������� � �������, �������� ��������, ��� ��� �������� ��� ��������... �� �� ��� �� � ����������� �����, ���� �� �� ����, ���� �� �������! ��� ��� ������ ������, "+ GetSexPhrase("��������","�������") +"!";
			link.l1 = "��-��, �������! � ������� �� ������ �� ��� ����������?";
			link.l1.go = "Mushket_stid_4";
		break;	
			
		case "Mushket_stid_4":
			dialog.text = "��� ����� �������, ��������! ��� ����� ������� - � ����� ������.";
			if(makeint(Pchar.money) >= 100000)
			{
				link.l1 = "�������?? �� �� ���, ������ - ������� ����� ������ �� ��� �����?!";
				link.l1.go = "Mushket_stid_nopay";
				link.l2 = "��� �������, �������. ����� ���� �������.";
				link.l2.go = "Mushket_stid_paymoney";
			}
			link.l3 = "��������, �� � ���� ��� ����� �����!";
			link.l3.go = "Mushket_stid_nomoney";
		break;	
			
		case "Mushket_stid_nopay":
			dialog.text = "�� ������ ���� ����������� - ��� ���� ����� ������� ������. � ���� ����� ��� '������' ������ ������������ ������ �� ������ ����� ������� - ���� ������� ������ ��� ���������� ��������... ���� ������� ��������� ������ - ��� ����������� ���� ������. �, ���� �� ������� - ���������� ������ �� � ����, ��-��-��...";
			link.l1 = "�����, ���� � �����. �����.";
			link.l1.go = "Mushket_stid_paymoney";
			link.l2 = "�� ������. ��������� ��� ������ - ���"+ GetSexPhrase("","�") +" �����.";
			link.l2.go = "Mushket_stid_goaway";
		break;	
			
		case "Mushket_stid_nomoney":
			dialog.text = "�� ��� � - ����� �� ������ ���� ������� '������'. �������, ���� ���� ������ ��������� �������������� ���-�� ����������. � �����, ��� �� ������������, ������ ��� - �� ������� � ����� �����, � ������ � ������... ��� ���, �������� - �������, ���� ������ �������� � ���. � � ���� �� ��������.";
			link.l1 = "�� ���, ������, �������. �� �������� ���� �������� ���������. ��� ���������� ������� ��������, � �� ��������� - ���� �����...";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "5");
			DeleteAttribute(pchar, "pchar.questTemp.Mushket.Shore");
		break;	
			
		case "Mushket_stid_goaway":
			dialog.text = "��� ������. ������ - �����. ������� �������!";
			link.l1 = "������, �������.";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "6");
			AddQuestUserData("SeekDoubleMushket", "sSex", GetSexPhrase("��","���"));
			DeleteAttribute(pchar, "pchar.questTemp.Mushket.Shore");
		break;	
			
		case "Mushket_stid_paymoney":
			AddMoneyToCharacter(Pchar, -100000);
			dialog.text = "�-�, � ���� ������"+ GetSexPhrase("�� ������ ��������","��� ������ ������������") +"! � ���� ���� ���������� - �� ���������� �� �! ��, �� ����� - ���� �� �������� ���� ������������ ������... ������ ������: �� �� ���� ���������� � ����� ��� ��������� " + XI_ConvertString(pchar.questTemp.Mushket.Shore) + ".\n����� �� ��� �� ����� - ����������� � �����, ��� ��� ����������. ������� ��� �� �� �������, �� ������� ��� ����"+ GetSexPhrase("��","��") +" ��� ������. ������, ���� ������ ������ ������� �����, ��-��... ���� ���, �� �������� ����� ������ ����"+ GetSexPhrase("��","�") +". � � ��� ���� ���� ������, � ���� ����� ������, �� �� ��� ���� �������� �� �����������.";
			link.l1 = "�������, ���! ���������� ����������.";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "4");
			AddQuestUserData("SeekDoubleMushket", "sShore", XI_ConvertString(pchar.questTemp.Mushket.Shore));
			DeleteAttribute(pchar, "pchar.questTemp.Mushket.Shore");
		break;
		
		case "Mushket_late":
			dialog.text = "A�-��-��! ����� ��� ���� ����������� ��� ������ ����, ���������� ��������� ������� ������?!";
			link.l1 = "�����... � ���� � ���� ����.";
			link.l1.go = "Mushket_late_1";
			DeleteAttribute(pchar, "questTemp.mushket2x2_stid");
		break;
			
		case "Mushket_late_1":
			dialog.text = "�� ��� � ���� �������... �� ������ ����, "+ GetSexPhrase("��������","�������") +". ����� �� �� ��� ������� �������� - � �� ��������� � ����� �����������, � ����� ����� ����� �������� �������.\n�� ������ ������ - �� ���� ������, � ���� - �� �����. ��� ��� ��� ������ ���"+ GetSexPhrase("","�") +"... �� ����� ����������. �� ����� ���� ��� ������.";
			link.l1 = "��� ������! �����, ��� ��� - ������.";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "7");
			AddQuestUserData("SeekDoubleMushket", "sSex", GetSexPhrase("��","���"));
		break;
		
		case "Romantic_1":
            dialog.text = "���, ���� ����� �� ���������.";
            link.l1 = "�������... �����, � ������� ���-������ ������� � ����?";
			link.l1.go = "Romantic_2";
		break;	
		case "Romantic_2":
            dialog.text = "������ ���, " + GetAddress_Form(pchar) + ", ��� �����.";
            link.l1 = "����... �� ��� ��, ������� ����.";
			link.l1.go = "exit";
			pchar.RomanticQuest = "ToRositaInBeliz";
		break;	
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

