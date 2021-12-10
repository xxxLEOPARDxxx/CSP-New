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
				break;
			}	
			Link.l1.go = "exit";
            if (pchar.questTemp.Ascold == "ToHavanna") // ����� ��������
            {
    			Link.l1 = "������, � ������ ������� ���������� ��������. ��� �����, ��� ����... � ���� �� ���?";
    			Link.l1.go = "Step_A1";
            }
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "��������, �� ��������� �� � ��� � ������ ������� �������? � ���� ������ '" + pchar.questTemp.Slavetrader.ShipName+ "', ���� ���... ";
                link.l1.go = "Havana_ratT_1";
            }
			if (pchar.questTemp.PDM_ONV_Detectiv_Tavern_1 == "Tevern_NET")	// ����� "����� �� ������"
            {
                link.l1 = "��� ����� �������... �� ����� �����. ��� � ���� ����� �?";
                link.l1.go = "PDM_ONV_Sprashivaem_Pro_Karlu_NeZnaet";
            }
			if (pchar.questTemp.PDM_ONV_Detectiv_Tavern_1 == "Tevern_Da")	// ����� "����� �� ������"
            {
                link.l1 = "��� ����� �������... �� ����� �����. ��� � ���� ����� �?";
                link.l1.go = "PDM_ONV_Sprashivaem_Pro_Karlu";
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
//******************** ����� ��������, ������ � ��������� � �������� ������ ******************
		case "Step_A1":
			dialog.text = "���, �� ��. ���� ����������, ��� � ��� ��� �� ��������� �����. � ��� ���� � ���, ��� ������ ��������� ��������� ������� �������...";
			Link.l1 = "����� �������?";
			Link.l1.go = "Step_A2";
		break;

		case "Step_A2":
			dialog.text = "�� �������, ��������� ������ ��������. ��� �������-���������� ������-�-������ ������ ���� ������� ���������� ���������. ������� ������ �������: �������, �������, ��������� ������ ������ - ����!";
			Link.l1 = "��� ���� ��! � ���-�� �����? ������ ������� ��� ������������ � ������, � ������ ��� �� �����?";
			Link.l1.go = "Step_A3";
		break;

		case "Step_A3":
			dialog.text = "��� �� ��� �������, ��� ���� �������, ��� �����? ���� ���, ������ �� ������...";
			Link.l1 = "������ �������� � ��� �����. � ���� ����� ���� �������?";
			Link.l1.go = "Step_A4";
		break;

		case "Step_A4":
			dialog.text = "�� ������, �� �� �������������, ��������-���� � ��� � ������, � �� ��� "+ GetSexPhrase("�����","�����") +"? � ����� ���� �����, ���� ����� �������?";
			Link.l1 = "�� �������, ������ ��� "+ GetSexPhrase("�������","��������") +"... ������ �� ������ �����, �� "+ GetSexPhrase("�����","������") +" ������ �������.";
			Link.l1.go = "Step_A5";
		break;

		case "Step_A5":
			dialog.text = "��� � �����, ��� �� "+ GetSexPhrase("�����","������") +". �� ������, ��� ���� �� ��� ���� �� ������ - ��������� ��������� �� ��������.";
			Link.l1 = "�����... ��� � ��� ������ "+ GetSexPhrase("������","�������") +"? �����, �������...";
			Link.l1.go = "exit";
			pchar.questTemp.Ascold = "SeekInformatorHavanna";
			AddQuestRecord("Ascold", "6");
            ref sld = GetCharacter(NPC_GenerateCharacter("FernandoGonsales", "off_spa_1", "man", "man", 28, SPAIN, -1, true));
            FantomMakeCoolFighter(sld, 28, 90, 70, BLADE_LONG, "pistol3", 10);
            LAi_SetStayType(sld);
           	sld.name 	= "��������";
			sld.lastname 	= "��������";
			sld.Dialog.Filename = "Quest\AscoldNpc.c";
			ChangeCharacterAddressGroup(sld, "Santiago_houseSp2", "goto", "goto2");
            LAi_LocationFightDisable(&Locations[FindLocation("Santiago_houseSp2")], true);
		break;

		case "Havana_ratT_1":
			dialog.text = "�-�, ���� ������� ���? ��, ������� �� �� ���, ��������������. ����� ���� �� �������: �� ����� �� ����� � ������ ������-�-�������. ������� ����������� �� ��������� �������. �� ���-�� ��� � ���� �� ��������, � �� ������� �����.";
			Link.l1 = "� ���� �� �������, �� � �����? � �� ��� ��� � ������ ����� ����� ������, �� ��� ����� ����� �� ����������.";
			Link.l1.go = "Havana_ratT_2";
		break;
		
		case "Havana_ratT_2":
			dialog.text = "� ����� �� ����? �� ������� ������ - ����� �������� ��� ����, ��� ������ ������������ ���������� - �� ����� ���������. ����� ������ � ������������� ������� ����������. �� �� ���� �� �� ��� ���������?";
			Link.l1 = "�������, �� ��� �� ��� �� ��������� �����! � ���, �����"+ GetSexPhrase("","�") +" �� �����"+ GetSexPhrase("���","��") +" ������? �� ��� ��������, � ����� �������� ��� �������, ������� ��� ������ � ������ ��������, �� � �� ���� ��� ��� ��������� - ����� ��� �� ����.";
			Link.l1.go = "Havana_ratT_3";
		break;
		
		case "Havana_ratT_3":
			dialog.text = "�� ����? ��-��-��! �� ������ �� ���� �� ��� ������� �� ������ � �������� �� ���� ����� ����� ���������� ����������... ��, �� �� ������ ������, ������, �� ����� � ������� ��������. � �� ��������...";
			Link.l1 = "�����. ��������, ������� ������� �� ������ ��� ����������. ��� ������, ������� ������ ������� �� �������� �������. ��� ���� �� ����������?";
			Link.l1.go = "Havana_ratT_4";
		break;
		
		case "Havana_ratT_4":
			dialog.text = "��, ����� ���� ��� ��� ���� � ��� �� ����� �������, �� ������, ��� � ������������, ����� �����������������, ��������. �� ������� �� ����������, � �'�������... ���-�� �� ��� ��� ��������� ���� ��������, �� � ��� � �� ����� ������.";
			Link.l1 = "�� �������, ������? �������! �������, ���� ��� � ��� ������. ������� ����, " + npchar.name + ", �� ��� ������� �����. �����.";
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

//******************** ����� "����� �� ������" ******************
		case "PDM_ONV_Sprashivaem_Pro_Karlu_NeZnaet":
			dialog.text = "�� ���� � ������� �����. � �� ����� �� ��������� ������ ����� - ����� ��� ��� �������. ������� ������?";
			Link.l1 = "���, �������. � �����.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Tavern_1");
			AddQuestRecord("PDM_Ohota_na_vedmu", "6");							
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
			pchar.questTemp.PDM_ONV_Detectiv_Jiteli_Havana = "Jiteli_Havana";
			pchar.questTemp.PDM_ONV_Detectiv_Oficiantka_Havana = "Oficiantka_Havana";
		break;


		case "PDM_ONV_Sprashivaem_Pro_Karlu":
			dialog.text = "�� ���� � ������� �����. � �� ����� �� ��������� ������ ����� - ����� ��� ��� �������. ������� ������?";
			Link.l1 = "Ÿ �������� � ���������! ������ �� ��, ��� ��� ������? ��, ��� ��� ������, � ���� �� ������ ��������� �, �� ������� �� ��� �� ����� ������, ��� � ���. ����? ���� ������, ��� ��� ������������ ������� � ���� �������. �� ��� ��� - ������ ����������, ���..?";
			Link.l1.go = "PDM_ONV_SPKarlu_2";
		break;
		
		case "PDM_ONV_SPKarlu_2":
			dialog.text = "�, �������� ����, ������"+ GetSexPhrase("","���") +" �������! � �� ����� �������� ����� - ������... � ���� ����� ����� � �������... � ���� �� ���� ������� ������, ����� ��� ��������� ������ ������ ���� ��������.";
			Link.l1 = "��, � �������, ��� ���� �������� ����� �������� ���� ����. �� ��� ����� �����, ��� ���.";
			Link.l1.go = "PDM_ONV_SPKarlu_3";
			Link.l2 = "���� ��������� ������ �� ���������� ����. � ����� ���� ���� �����, ��� ���.";
			Link.l2.go = "PDM_ONV_SPKarlu_5";
		break;
		
		case "PDM_ONV_SPKarlu_3":
			dialog.text = "�, ������"+ GetSexPhrase("","���") +" - �� �������� ���� � �� ����! � ������ ��������� �������� ������� � ��������� ������! ��� ������, ��� ������ ����������! �� �������� ��� ������� �� ������, � ������ ������, ����� � ���� �� ������?!";
			Link.l1 = "�� ����� ���� ��������� �������... ��� �, ����� ���, ��� ����� - � � ������� ����. ����� ������� ���� �������.";
			Link.l1.go = "PDM_ONV_SPKarlu_5";
			Link.l2 = "�� ������� ������ �������� � ����� ������� - ��� ��� ���� ������� ���������, ��� ��� �����.";
			Link.l2.go = "PDM_ONV_SPKarlu_4";
		break;
		
		case "PDM_ONV_SPKarlu_4":
			dialog.text = "�, �� ��������� ��� �����! ��, ������ ������ - �� �� ������ �������� ������!";
			Link.l1 = "������� � ����� ������, ��������� �������! ���� �� �� ������� ���, ��� �����, �� ���� ����� �� �������������� ������� ����� ����� ��������� ������� ������.";
			Link.l1.go = "PDM_ONV_SPKarlu_5";
			ChangeCharacterReputation(pchar, -2);
			AddMoneyToCharacter(pchar, 2000);
		break;
		
		case "PDM_ONV_SPKarlu_5":
			dialog.text = "��, ��, ��� ���� �����! �� ��� ������ ������� � ����� ���������. ����� ��� ������� ���, ��� �������, � ����� ����������. ����� ������� ������� ����� �������-�� ���� ������. Ÿ ������� ��� "+ GetSexPhrase("��������� �������, ����� ��� �� - ����� �� ������� � ��������","������� � �������� ���������, ����� ��� ��.") +"...";
			Link.l1 = "��� ��� �����?";
			Link.l1.go = "PDM_ONV_SPKarlu_6";
		break;
		
		case "PDM_ONV_SPKarlu_6":
			dialog.text = "������ ������, ��������� � �����. �� ����� � ���� � ����� �����. �... �������� ����, ������"+ GetSexPhrase("","���") +" - � ����� ��� �� ������������ ��, ��� ��� � ���� �� ��. � �� ����, ����� ��� ����� ���������� �� ���...";
			Link.l1 = "� �� �������� ��. �� �� ������ ������� ���, ���� ��� �����������.";
			Link.l1.go = "PDM_ONV_SPKarlu_7";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Tavern_1");
		break;
		
		case "PDM_ONV_SPKarlu_7":
			int Isp_Coloni
			Isp_Coloni = rand(2);
			if (Isp_Coloni == 0)
			{
				dialog.text = "� ���� ��� ������� ����������� �� ���� ����, ������"+ GetSexPhrase("","���") +" �������. � �����, ��� ��� ���-�� �������� ��� �����-�� ������� - ���������, ����������... � ��� ���� ��� �����: '�' � '�'.";
				Link.l1 = "� ���� ����. �� ����� - �� ������ ���������� ������������ � ����� �������, �� ���, ����������� �������. ����� �������!";
				Link.l1.go = "exit";
				pchar.questTemp.PDM_ONV_Detectiv_PB = "PortoBello";
				AddQuestRecord("PDM_Ohota_na_vedmu", "8");							
				AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
				
				sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Viktor_Martos", "officer_22", "man", "man", 10, SPAIN, -1, false));
				sld.name = "������";
				sld.lastname = "���";
				sld.city = "PortoBello";
				FreeSitLocator("PortoBello_tavern", "sit_base2");
				ChangeCharacterAddressGroup(sld,"PortoBello_tavern","sit","sit_base2");
				LAi_SetSitType(sld);
				sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
				sld.dialog.currentnode   = "RazgovorSViktorom_1";
				pchar.questTemp.PDM_ONV_PortoBello = "PortoBello";
			break;
			}
			if (Isp_Coloni == 1)
			{
				dialog.text = "� ���� ��� ������� ����������� �� ���� ����, ������"+ GetSexPhrase("","���") +" �������. � �����, ��� ��� ���-�� �������� ��� �����-�� ������� - ���������, ����������... � ��� ���� ��� �����: '�' � '�'.";
				Link.l1 = "� ���� ����. �� ����� - �� ������ ���������� ������������ � ����� �������, �� ���, ����������� �������. ����� �������!";
				Link.l1.go = "exit";
				pchar.questTemp.PDM_ONV_Detectiv_MB = "Maracaibo";
				AddQuestRecord("PDM_Ohota_na_vedmu", "9");							
				AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
				
				sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Viktor_Martos", "officer_22", "man", "man", 10, SPAIN, -1, false));
				sld.name = "������";
				sld.lastname = "���";
				sld.city = "Maracaibo";
				FreeSitLocator("Maracaibo_tavern", "sit_base2");
				ChangeCharacterAddressGroup(sld,"Maracaibo_tavern","sit","sit_base2");
				LAi_SetSitType(sld);
				sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
				sld.dialog.currentnode   = "RazgovorSViktorom_1";
				pchar.questTemp.PDM_ONV_Maracaibo = "Maracaibo";
			break;
			}
			if (Isp_Coloni == 2)
			{
				dialog.text = "� ���� ��� ������� ����������� �� ���� ����, ������"+ GetSexPhrase("","���") +" �������. � �����, ��� ��� ���-�� �������� ��� �����-�� ������� - ���������, ����������... � ��� ���� ��� �����: '�' � '�'.";
				Link.l1 = "� ���� ����. �� ����� - �� ������ ���������� ������������ � ����� �������, �� ���, ����������� �������. ����� �������!";
				Link.l1.go = "exit";
				pchar.questTemp.PDM_ONV_Detectiv_SJ = "SanJuan";
				AddQuestRecord("PDM_Ohota_na_vedmu", "10");							
				AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","�"));
				
				sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Viktor_Martos", "officer_22", "man", "man", 10, SPAIN, -1, false));
				sld.name = "������";
				sld.lastname = "���";
				sld.city = "SanJuan";
				FreeSitLocator("SanJuan_tavern", "sit_base2");
				ChangeCharacterAddressGroup(sld,"SanJuan_tavern","sit","sit_base2");
				LAi_SetSitType(sld);
				sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
				sld.dialog.currentnode   = "RazgovorSViktorom_1";
				pchar.questTemp.PDM_ONV_SanJuan = "SanJuan";
			break;
			}
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

