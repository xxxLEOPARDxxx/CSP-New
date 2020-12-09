
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	float   locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "prisonerHead":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "������������. � ��� �������, ��� ��� �� - "+ GetSexPhrase("��������� ��������� ���������","��������� ��������� ���������") +"?";
				link.l1 = "������ ���. ���� ����� " + GetFullName(pchar) + ".";
				link.l1.go = "FTH_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "������������. ��� ��� ����� � ������?";
				link.l1 = "�� ������ ����������. ������ ��� ��������"+ GetSexPhrase("","�") +".";
				link.l1.go = "Exit";
				//����� �� �������� ��������
				if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && !CheckAttribute(npchar, "quest.decster"))
				{
					if (pchar.questTemp.LSC.lostDecster == "seekBox" || pchar.questTemp.LSC.lostDecster == "toAdmiral")
					{
						link.l6 = "� �� �� ������, ��� ��� ����������� ������ �� ���?";
						link.l6.go = "LostDecsterHead";
					}
				}
				//��� ���� ������
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElis")
				{
					link.l7 = "�� ����������, � �� ��� ���� ����� ������ ������?";
					link.l7.go = "ELTHusb_begin";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "seekFreeMotod")
				{
					link.l7 = "����������, � ����� ���-������ ������������� ������������ ����� ������� � �������� ������� �������?";
					link.l7.go = "ELTHusb_SF";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiral")
				{
					link.l7 = "����������, � ����� ���-������ ������������� ������������ ����� ������� � �������� ������� �������?";
					link.l7.go = "ELTHusb_SF";
				}
				//������ ������� �� ������
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "����������, ���� ��������� ��������. � ������� �������.";
					link.l8.go = "SeekCrew";
				}
			}			
			NextDiag.TempNode = "prisonerHead";
		break;
		case "FTH_1":
			dialog.text = "�� ��� ��, ������� ��� ������������. � - ��������� ������ ������, ���������� ��������������� ��������. � �� ������ ��������� ��������� � ��� �� �� �� ����, �� ������, ��� ���� ��������� �� �������� - ������ �����.";
			link.l1 = "��-��, � �������. � ����� ����� ��� ������ ��������?";
			link.l1.go = "FTH_2";
		break;
		case "FTH_2":
			dialog.text = "���, � ���������, ����� ��� ������ �� ����. ����� ����� ����� ������, �� ������������. � �������� ������������ �� ����������.";
			link.l1 = "����. �� ��� ��, ����� ��� � �������� ����� ���������������.";
			link.l1.go = "FTH_3";
		break;
		case "FTH_3":
			dialog.text = "� �� ��������! �����, �� ����� �� ���� ���� �����...";
			link.l1 = "�������... ��, ����� �������.";
			link.l1.go = "Exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "prisoner":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "�����������. � ���, ��� �� �����"+ GetSexPhrase("","�") +" � ������ ���������� ����� ���. � ��������, ���� ����� " + GetFullName(npchar) + ".";
				link.l1 = "����� �������. � � - ������� " + GetFullName(pchar) + ".";
				link.l1.go = "FTP_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "���� �� ����� �� ����, �� � ����� ������������� � �����������.";
				//����� �� �������� ��������
				if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && npchar.chr_ai.type == LAI_TYPE_SIT && !CheckAttribute(npchar, "quest.decster"))
				{
					if (pchar.questTemp.LSC.lostDecster == "seekBox" || pchar.questTemp.LSC.lostDecster == "toAdmiral")
					{				
						link.l1 = "������, � �� �� � �����, ��� ����� ������ �������?";
						link.l1.go = "LostDecster";
					}
				}	
				//����� � ����� �� �������� �����
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toTomasBoil" && CheckCharacterItem(pchar, "potionwine"))
				{
					link.l2 = "��������, � ������"+ GetSexPhrase("","��") +" ���� ��������� ���� �� ������ ����� �������� �����. �����, ����������, � �� ������ ��� ����������...";
					link.l2.go = "WineLogro";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toSecondToPrison")
				{
					link.l2 = "��������, ��� ����� �. � ����� �� ������ �������� �����.";
					link.l2.go = "SecondLogro";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "to3ToPrison")
				{
					link.l2 = "�������, ������, ��� ������� ������ ����������������� � ��������� ���� �� �����.";
					link.l2.go = "LastLegro";
				}
				//������ ��������� � ������ �� ��������, ���� ���� �����
				iTemp = GetCharacterIndex("LSCwaitress");
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "over" && CheckAttribute(pchar, "questTemp.LSC.LegroHelp.Armo") && iTemp != -1 && characters[iTemp].name != "����" && pchar.questTemp.LSC == "toSeekMechanik")
				{
					link.l3 = "�������, �� ������, ��� ���� �����?";
					link.l3.go = "ArmoIsDead";
				}
				link.l10 = "������, � �����"+ GetSexPhrase("","�") +".";
				link.l10.go = "Exit";
			}			
			NextDiag.TempNode = "prisoner";
		break;
		case "FTP_1":
			dialog.text = "�� ��� ��, ��� � �������������. ���� �� ����� �� ����, �� ���� ����� ������������� � ���� �����.";
			link.l1 = "����.";
			link.l1.go = "exit";
		break;

		//���� �������
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("����� �������?", 
				"�� ��� �������� �� ����.", 
				"��� ��� ���������, ������ ��� ��������.",
                "������, ������"+ GetSexPhrase("","�") +"...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������� �� �������. � ����� �� ������.", 
				"��... ������, �����������"+ GetSexPhrase("","�") +".",
                "��� ������...", 
				"��, �����...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "�� ���, � ��� �����? ������� ������ �� ������?";
			link.l1 = "� ������ ���� �����, ������ � �����. ��������� ��� ������ ������ � ����. ���� � ���, ��� ����� ����� �������� ���� �������.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "� ��� �� ����.";
			link.l1 = "����� ���.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "���, �����"+ GetSexPhrase("","�") +" "+ GetSexPhrase("��������","�����������������") +", ������ ������� �����! � ������������ ��� ������� �����.";
			link.l1 = "��, ��� ���� ����������...";
			link.l1.go = "exit";
		break;

		//���������� ���� ���� ������
		case "ELTHusb_begin":
			dialog.text = NPCStringReactionRepeat("�� �� ��������! ���� ������ ��������� � ������� � ����� � ���������� � �������� ����� ������.", 
				"� ��� ������� �� ��� ������.", 
				"�� ��� �������� �� ����!",
                "����������, ���������� ����������!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�-��-��... � ��� �� ���������� �� ������� ����������?", 
				"��-��, � �����.",
                "�������.", 
				"������-������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_begin_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_begin_1":
			dialog.text = "�� ��� ��� �����. ������-��, ������ - ��� ������������ ���������, �� � �������� �� � ������ ��� ��������. � ����� ���, ����� � ���. ����� ����, �� ��� ��-���� ������ ���������...";
			link.l1 = "� ��� ����� ��������� � ��������� ��������?";
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = "��, ������� �� ������ �������������� ����������.";
			link.l1 = "� �����, �������...";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "3");
		break;

		case "ELTHusb_SF":
			dialog.text = NPCStringReactionRepeat("� ���� �������� � ������ �� ��� ���������� � ��������. �� ��� ���� �������, �� �� ����� � ��������� ������� � ��� ���������� ������.", 
				"�� ��� �������� �� ��� ����.", 
				"��� ��� �������, ��� �� ��� �������� �� ��� ����.",
                "�� �����?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("� � ���� � ���� ���-������ ������������?", 
				"��, �����"+ GetSexPhrase("","�") +"...",
                "����� �����"+ GetSexPhrase("","�") +".", 
				"����� �� ������ �� ��...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_SF_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_SF_1":
			dialog.text = "�� �� � ��� �����! ����� � �������, ��� ��� �����.";
			link.l1 = "�� ����� �������.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "4");
		break;

		case "LostDecsterHead":
			dialog.text = "���, �� ����. � ��� �� ������� �����.";
			link.l1 = "� ����� ������?";
			link.l1.go = "LostDecsterHead_1";
		break;
		case "LostDecsterHead_1":
			dialog.text = "� ������. � �� ������� ��� �����, ��� ��� ����������� ������ �� ����.";
			link.l1 = "� ����� ����, ��� ������ �������.";
			link.l1.go = "LostDecsterHead_2";
		break;
		case "LostDecsterHead_2":
			dialog.text = "��� ����� ����... � � ���� ��� ���������?";
			link.l1 = "�� �� � ����, ������ �����������.";
			link.l1.go = "LostDecsterHead_3";
		break;
		case "LostDecsterHead_3":
			dialog.text = "�� ���������� ��� �����. �����������, ������ ��, ������ ������� �������� ���������...";
			link.l1 = "��... ��-��, � �������.";
			link.l1.go = "exit";
			npchar.quest.decster = true; //�� ��������� �����
		break;

		case "LostDecster":
			dialog.text = "������ ��������� '���������'.";
			link.l1 = "� ��� �� ������?";
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = "��-��... �� ��-�-�� ��� ������, ��� ����� �� ��������� ������ � ������ ����. �� ������ ������ �� �����!..";
			link.l1 = "�������!";
			link.l1.go = "exit";
			AddQuestRecord("LSC_findDekster", "4");	
			npchar.quest.decster = true; //�� ��������� �����
		break;
		//���� �� �������� �����
		case "WineLogro":
			dialog.text = "��������� ���� �� �������� �����?!\n���� � ������, ��� �� � ����. �� ����� ���������� �������, � ��� � ��� �����������!";
			link.l1 = "�� �����"+ GetSexPhrase("","�") +"...";
			link.l1.go = "WineLogro_1";
		break;
		case "WineLogro_1":
			dialog.text = "� ���� � ������ ��������. ������ �������, ��� � ��� ��� �� ���� ������.";
			link.l1 = "�� �����, �������... � �������-�� �����, ��� �� �����������.";
			link.l1.go = "WineLogro_2";
			TakeItemFromCharacter(pchar, "potionwine");
		break;
		case "WineLogro_2":
			dialog.text = "� ����� ���... �� �����, ������� ��� ��� ���������� ���������. �� ���� �������, � �������� ������� ��� �����.";
			link.l1 = "������, �������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toFackDominic";
			AddQuestRecord("TakeVineToPrisoner", "2");
			AddQuestUserData("TakeVineToPrisoner", "sSex", GetSexPhrase("","��"));
		break;

		case "SecondLogro":
			dialog.text = "��� �������?";
			link.l1 = "�������"+ GetSexPhrase("","�") +" � ��� ���� �����. �� ����� �������� � ��������, ��� ���������� �� � ����� ����, ��� ����������.";
			link.l1.go = "SecondLogro_1";
		break;
		case "SecondLogro_1":
			dialog.text = "�������?";
			link.l1 = "�� ��������.";
			link.l1.go = "SecondLogro_2";
		break;
		case "SecondLogro_2":
			iTemp = GetCharacterIndex("LSCwaitress");
			if (iTemp != -1 && characters[iTemp].name == "����")
			{
				dialog.text = "� ����� �� ������, ��, ��������, �� ��������� � ���, ��� ������� ��������� � ���� �����, ����������� �� �������?";
				link.l1 = "������� �� ����.";
				link.l1.go = "SecondLogro_3";
				pchar.questTemp.LSC.LegroHelp.Armo = true; //���� �� ��, ��� ����� ����� � �������� ����
			}
			else
			{
				dialog.text = "���� ���?.. ��, �� ��� ��, �����, �������, ��� ����� ����������.";
				link.l1 = "��� ������� � ����� � �� �������.";
				link.l1.go = "LastLegroAdd";
			}
		break;
		case "SecondLogro_3":
			dialog.text = "��, ��� �� ������ ���.";
			link.l1 = "�����...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toArmoDominic";
			AddQuestRecord("TakeVineToPrisoner", "4");
		break;

		case "LastLegro":
			dialog.text = "��� ���?";
			link.l1 = "�� �������, ��� ������ ������������ � ����, �� ������ ������� �� ������� � ���.";
			link.l1.go = "LastLegro_1";
		break;
		case "LastLegro_1":
			dialog.text = "�� ��� �������...";
			link.l1 = "�� ����� ����������������� ��������� � ���������� � ��������.";
			link.l1.go = "LastLegro_2";
		break;
		case "LastLegro_2":
			dialog.text = "��, �� ����"+ GetSexPhrase("","�") +"\n�� ��� ��, � ���� ��������. ������� ���, ��� � ����� � ���� ��������. ������, ��� � ���������� ���� ���.";
			link.l1 = "�� ��, �������������, ������ �� ��.";
			link.l1.go = "LastLegro_3";
		break;
		case "LastLegro_3":
			dialog.text = "������� ����, "+ GetSexPhrase("����","" + pchar.name + "") +", �� ������� � ����� � ��������� �����.";
			link.l1 = "������ ���"+ GetSexPhrase("","�") +" ������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toKeyDominic";
			AddQuestRecord("TakeVineToPrisoner", "6");
		break;

		case "LastLegroAdd":
			dialog.text = "��, �� ����"+ GetSexPhrase("","�") +"... ������, ������� ��������, ��� ��� ���������. � �� ������� �� ����.";
			link.l1 = "��, �������! ��� ��, ����� �, �������, �����...";
			link.l1.go = "LastLegro_3";
		break;
		//���� ���� �����, �� �������� ����� ������ � ������ �� ��������
		case "ArmoIsDead":
			dialog.text = "��� ��� ��������.";
			link.l1 = "� �� ������, ��� ��� ������?";
			link.l1.go = "ArmoIsDead_1";
		break;
		case "ArmoIsDead_1":
			dialog.text = "������� ������. ��� ����� - ������ ������.";
			link.l1 = "��� ������ ���� ����, ���� �� '��������'.";
			link.l1.go = "ArmoIsDead_2";
		break;
		case "ArmoIsDead_2":
			dialog.text = "������ �� ������?";
			link.l1 = "�� ��� ��� ��� ������. �� ������� ���� ������, � ��� ���������"+ GetSexPhrase("","�") +" ���.";
			link.l1.go = "ArmoIsDead_3";
		break;
		case "ArmoIsDead_3":
			dialog.text = "����...";
			link.l1 = "��, � �� ��� �� ������"+ GetSexPhrase("","�") +".";
			link.l1.go = "ArmoIsDead_4";
		break;
		case "ArmoIsDead_4":
			dialog.text = "��� �� ������ � ����?";
			link.l1 = "� ��������� ���� �� ����������������� �����, � ��������� ����� �����, ���� ���� ��� ������ ������������. �� �� ���� ���� ������, ��� ��� � ���� �� ������� ��� ������ ������� �����.";
			link.l1.go = "ArmoIsDead_5";
		break;
		case "ArmoIsDead_5":
			dialog.text = "��� ���...";
			link.l1 = "� ��������� ����������� �� '��� ��������'. �� ������ ����� �� ����.";
			link.l1.go = "ArmoIsDead_6";
		break;
		case "ArmoIsDead_6":
			dialog.text = "� �����.";
			link.l1 = "����� ������, �� ����� ����������� ��� ����.";
			link.l1.go = "ArmoIsDead_7";
		break;
		case "ArmoIsDead_7":			
			if (npchar.chr_ai.type == LAI_TYPE_SIT)
			{
				GetCharacterPos(npchar, &locx, &locy, &locz);	
				ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			}
			sld.dialog.currentnode = "AfterFightCasper";
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("ISS_MainLine", "70");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","�"));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "AfterFightCasper":
			dialog.text = "�� ���, ������, ��� �� ����������.";
			link.l1 = "�����. ������� �� ������, �������. �� ������ � ������ ����������� �� ���� � ���������� ������ ����?";
			link.l1.go = "AfterFightCasper_1";
		break;
		case "AfterFightCasper_1":
			dialog.text = "���. ��� ���� �����, � �� ����� �����������. �, �������, ����� �������. ����� ��� ����...";
			link.l1 = "� ��� �� ������?";
			link.l1.go = "AfterFightCasper_2";
		break;
		case "AfterFightCasper_2":
			dialog.text = "������� �� ������, �� ��������, �� � ������ �� ���� ���� ��������� �����! ��, ��� ���� ��� ����� �� ����...";
			link.l1 = "�������, �������.";
			link.l1.go = "AfterFightCasper_3";
		break;
		case "AfterFightCasper_3":
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

	}
}
