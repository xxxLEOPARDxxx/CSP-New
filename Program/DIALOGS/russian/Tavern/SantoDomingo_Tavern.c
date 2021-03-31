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
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
			{
				dialog.text = "��������� ���� �������, "+ GetSexPhrase("������","���������") +".";
				link.l1 = "� "+ GetSexPhrase("������","�������") +", ������� �� ������ ��������� ���� ���������, ���� ������ ������!";
				link.l1.go = "Step_F7_1";
			}
			if (pchar.questTemp.PDM_PK_IshemKoltso == "IshemKoltso")	// ����� "���������� ������"
            {
                link.l1 = "� ���������� ������, ������� ������������... ������ �� ���� ��������. �������� ������ ������. � ��� ������ ���������, ���-�� � ���� ������. ���� �����, �� ���-�� ������ � ��? ������� ������, � ������� ������.";
                link.l1.go = "IshemKoltso";
            }
		break;
//******************** ��.�������, ����� �7. �������� ���� ��������� ******************
 	 	case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat("��, �����, ���� ����. ����������� �����, ����� � ���, "+ GetSexPhrase("������","���������") +".", "�� ��� ���������� ���� � ���������.", 
				          "����� � ���������?", "�� ������� ����� �� ���� �������, ������� � ������ ���������...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� ����� - �� �����... � ��� � ��� �������? ������ ������� ��� ��.", ""+ GetSexPhrase("���������","����������") +"? �� ��, ��������...", "��, �����, "+ GetSexPhrase("���������","����������") +", ������...", "����� � � ������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F7_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_F7_2":
			dialog.text = "��� ��, "+ GetSexPhrase("������","���������") +". �������� � �������� ���� ��������. � ����� ��� ������ ������ �����...";
			link.l1 = "� ������ �����-�� �� �����?";
			link.l1.go = "Step_F7_3";
        break;
 	 	case "Step_F7_3":
			dialog.text = "���, "+ GetSexPhrase("������","���������") +", ��� �� �� �����������. �� ������ ���� - ������������ ������! ����������...";
			link.l1 = "�-�-�, ���� �����. �� ��� ��, ������� ����, ����.";
			link.l1.go = "exit";
        break;
//******************** ����� "���������� ������" ******************		
		case "IshemKoltso":
			dialog.text = "����... �� �������� - ������? ��, � �����, ��� ����� ������, ����� ����, � ������� �� ��������. ��� � ����� ����� - ����� ����, �� ���� ������ � - �� ������� ����, ����������� ������� ��� ������� �������, ��-��. �� ����� ���������. � ��� ������� �� �������� �������� �����, ���� ������. �����-�� ������ ������� �� ��� ������ ���� ��� �����. ���� ����� �� ��� ��� ����� ����, ��� ��� - ��������� ��� ������ ����� �������� �����. ��, ��� �������� �� ������, ������� �� �����. �� ��� ��� - ������� �������� ������������ � ������ ���������, ��� ������ ���� ������?";
			link.l1 = "�������� �����! �, �������, ������� �������. ��� ���� �����, ������ �� ����� - � ����� �������.";
			link.l1.go = "exit";
			
			AddQuestRecord("PDM_Poteryanoe_Koltso", "3");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("","�"));
			DeleteAttribute(pchar, "questTemp.PDM_PK_IshemKoltso");
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_PK_Francheska", "BaynesDaughterSTOK", "woman", "woman", 10, SPAIN, -1, false));
			sld.name = "���������";
			sld.lastname = "";
			sld.city = "SantoDomingo";
			sld.location	= "SantoDomingo_Brothel";
			sld.location.group = "goto";
			sld.location.locator = "goto3";
			sld.dialog.filename   = "Quest/PDM/Poteryanoe_Koltso.c";
			sld.dialog.currentnode   = "Francheska";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			LAi_SetImmortal(sld, true);
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

