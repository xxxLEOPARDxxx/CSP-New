#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	int license_price = sti(PChar.rank) * (2500) * (0.01 * (120 - GetSummonSkillFromName(PChar, SKILL_COMMERCE)));;
	int license_expires = rand(2);
	
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// ����� ������� �� ������� <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;

	int i, cn, iOfficer;
	ref chref, compref;
	ref rRealShip;
	string attrL, sTitle, sCapitainId, s1;
	string sColony;
	string offtype = "";
	
	String sLastSpeakDate = LastSpeakDate();
	
	bool ok, ok2;
	int iTest = FindColony(NPChar.City); // ����� ��������
	ref rColony;

	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "OfficerStockManBack_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.OfficerToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // ����� � �����
		Dialog.CurrentNode = "OfficerStockManBack";
	}

	if(HasSubStr(attrL, "OfficerStockSel_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.OfficerToStoreIdx = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // ����� � �����
		Dialog.CurrentNode = "OfficerStock_2";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "First time":
			NextDiag.TempNode = "First time";
			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "����������� ���, " + GetAddress_Form(NPChar) + ". ��, �������, �� �������. � "  + GetFullName(npchar)+ " - ����������� �������� ��������� ��������� ��������� ��������.";
				Link.l1 = "������������, " + GetFullName(NPChar) + ". � " + GetFullName(PChar) + ", ������� ������� '" + PChar.ship.name + "'.";
			}
			else
			{
				dialog.text = LinkRandPhrase("����������� ���, " + GetAddress_Form(NPChar) + ". �� �� ��� �� ����?",
									"������������, " + GetFullName(Pchar) + ". ��� �������� � ����� ��������.",
									"�, ������� " + GetFullName(Pchar) + ". ��� ������� ��� �� ���?");
				Link.l1 = "������������, " + GetFullName(NPChar) + ". � ���� � ���� ����������.";
			}
			if (NPChar.id == "Wh_Jim")
			{
				dialog.text = "�������! ��� ����� ��� ������. � ��� ���������� �������?";
				Link.l1 = "������, " + npchar.name + ". ����� ���-��� ��������.";
				
			}
			Link.l1.go = "node_2";
		break;
		case "node_2":
			// ��������� ��������� 1
		
			dialog.text = "���������. � � ����� �������, " + GetFullName(PChar) + ".";
			
			Link.l3 = "� ���� �������� ����� ������� ��� ��������.";
			Link.l3.go = "ShipStock_1";

			if (sti(NPChar.Portman) > 0)
			{
				Link.l4 = "� ���� ������� ������ ������� �������.";
				Link.l4.go = "OfficerStockReturn_1";
			}
			
			Link.l15 = "���������. �� ��������.";
			Link.l15.go = "exit";
		break;
		case "again":
			dialog.text = "���-�� ���?";
			
			Link.l3 = "� ���� �������� ����� ������� ��� ��������.";
			Link.l3.go = "ShipStock_1";

			if (sti(NPChar.Portman) > 0)
			{
				Link.l4 = "� ���� ������� ������ ������� �������.";
				Link.l4.go = "OfficerStockReturn_1";
			}
			
			Link.l15 = "������ ������. �� ��������.";
			Link.l15.go = "exit";
		break;

		//<--------------------------- ���� �� ���� �������� �����

		case "ShipStock_1":
			dialog.text = "���� ������ �� ������ ��������?";
			for(i=0; i<GetPassengersQuantity(pchar); i++)
			{
				iOfficer = GetPassenger(pchar, i);
				sld = GetCharacter(iOfficer);
				if (!GetRemovable(sld)) continue;
				attrL = "l"+i;
				Link.(attrL)	= "������ " + GetFullName(sld) + ".";
				Link.(attrL).go = "OfficerStockSel_" + i;
			}
			Link.l99 = "�������, �� �����.";
			Link.l99.go = "exit";
		break;

		case "OfficerStock_2":
			chref = GetCharacter(sti(NPChar.OfficerToStoreIdx));
			
			if (!CheckAttribute(chref,"quest.officertype")) offtype = "���������";
			else offtype = XI_ConvertString(chref.quest.officertype);
			dialog.Text = "�� ������� "+GetFullName(chref)+", ������������� - "+offtype+".";
			Link.l1 = "��. ��� ���� ����������.";
			Link.l1.go = "OfficerStock_3";
			Link.l99 = "���, � ���������"+ GetSexPhrase("","�") +".";
			Link.l99.go = "exit";
		break;

		case "OfficerStock_3":
			chref = GetCharacter(sti(NPChar.OfficerToStoreIdx));
			chref.OfficerInStockMan = NPChar.id;
			// Warship 22.03.09 fix �� ����������� � ��� 1.2.3
			chref.OfficerInStockMan.AltDate = GetQuestBookDataDigit(); // ��� ������
			SaveCurrentNpcQuestDateParam(chref, "OfficerInStockMan.Date"); // ��� �������
			RemovePassenger(pchar, chref);

			chref.location = "";
			chref.location.group = "";
			chref.location.locator = "";
			NPChar.Portman	= sti(NPChar.Portman) + 1;
			pchar.OfficerInStock = sti(pchar.OfficerInStock) + 1;//����������� - ��� ���. �� ���� �����, ��� ��� ������������.

			dialog.text = "������. ��������, ����� ����� �����.";
			Link.l1 = "�������.";
			Link.l1.go = "again";
		break;

		case "OfficerStockReturn_1":
			dialog.text = "���� ������ �� ���������?";
			cn = 1;
			for(i=1; i<MAX_CHARACTERS; i++)
			{
				makeref(chref, Characters[i]);
				if (CheckAttribute(chref, "OfficerInStockMan"))
				{
					if (chref.OfficerInStockMan == NPChar.id)
					{
						attrL = "l"+cn;
						if (!CheckAttribute(chref,"quest.officertype")) offtype = "���������";
						else offtype = XI_ConvertString(chref.quest.officertype);
						Link.(attrL)	= "������ " + GetFullName(chref) + ", ������������� - "+offtype+".";
						Link.(attrL).go = "OfficerStockManBack_" + i;
						cn++;
					}
				}
			}

			Link.l99 = "���, � ���������"+ GetSexPhrase("","�") +".";
			Link.l99.go = "exit";
		break;
	  	case "OfficerStockManBack":
			chref = GetCharacter(sti(NPChar.OfficerToStoreIdx));
			dialog.Text = "��������� ������� "+GetFullName(chref)+"?";
			Link.l1 = "��.";
			Link.l1.go = "OfficerStockManBack2";
			Link.l2 = "���, � ���������"+ GetSexPhrase("","�") +".";
			Link.l2.go = "exit";
		break;
		
		case "OfficerStockManBack2":
			chref = GetCharacter(sti(NPChar.OfficerToStoreIdx));
			dialog.text = GetFullName(chref)+" ��� ��������� � ��� �� �������, �������.";
			Link.l1 = "���������.";
			Link.l1.go = "again";
			DeleteAttribute(chref, "OfficerInStockMan");
			AddPassenger(pchar, chref, false);

			NPChar.Portman	= sti(NPChar.Portman) - 1;
			pchar.OfficerInStock = sti(pchar.OfficerInStock) - 1;
			
		break;
		
	}
}

void DelBakSkill(ref _compref)
{
	DelBakSkillAttr(pchar);
	ClearCharacterExpRate(pchar);
	RefreshCharacterSkillExpRate(pchar);
	SetEnergyToCharacter(pchar);

	DelBakSkillAttr(_compref);
	ClearCharacterExpRate(_compref);
	RefreshCharacterSkillExpRate(_compref);
	SetEnergyToCharacter(_compref);
}