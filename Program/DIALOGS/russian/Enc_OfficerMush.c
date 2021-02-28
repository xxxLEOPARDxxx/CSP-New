void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref    sld;
	string attr, attrLoc;
	int    iTemp, iTax, iFortValue;
	
    Pchar.quest.FreeRandomOfficerIdx = NPChar.index;
	
	switch(Dialog.CurrentNode)
	{
		case "CitizenNotBlade":
			dialog.text = "�������, ��� �� ��������! ������� ������, ���� ��� �� ��������!";
			link.l1 = LinkRandPhrase("������.", "�����.", "�� ���������, ��� ������...");
			link.l1.go = "exit";
		break;
		
		//--> ��������-��������
		case "Saxon":
			if (sti(PChar.reputation) >= 51)//��� ������ ��������� - � ���
			{
				dialog.text = "����������� ���, �������! � ��� ��� ��� ��� ����� ����...";
				link.l1 = "����? ����!? � �� ����������, ����� �� ���� �������.";
				link.l1.go = "Saxon_1";
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("����� ����! ��������, ������, �� ��������, � �� � �������� ����������� ���","��������! � �� �������� ��� �� �������� �� ���� ����������") +". ���� � � � ��������, �� ������� �����...";
				link.l1 = "����� �� ������! ������, �������, ����� ������.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Saxon";
			}
		break;

		case "Saxon_1":
			dialog.text = "��� ������� �� ������ ����������. ��������� ������������� � ������ ��� ������-�����. � ������ ������ ������� � ��������, ������� ���� �����. � ������ ���� ����������� � ����������� �����, �������� ������� ��������� ������... �� �������� ���\n�� � ����������� �������� ����������, ���� �� �������! � � ���� ���� �������� ������� ���������� ���. ��� ��� ������ � ��������� ������ ����� ���������, �� ������ ����� ��������, ��� ������ �� ������ ������������ �����, ���� �� ������ ����, ������� ��!";
			link.l1 = "������������, ������. �� �� ��� � �� ��������, ������ ����� ������ ����?";
			link.l1.go = "Saxon_2";
		break;
		
		case "Saxon_2":
			dialog.text = "������ ���� � ������� �� ���� � ��������� � ����������� ���������, �� ����� �� �� ����� ���������� ����. ������ ���������� ������������� ���, ��� ������ �������������, ����������, �������� � ��������� ���������"+ GetSexPhrase(".",", �������� �� ��, ��� �� �������.") +" �� ���� � �������� ��� ������� ��� ������� ������� ��� ��������� � ������������ �����.";
			link.l1 = "��������, �� ���� ��������?..";
			link.l1.go = "Saxon_3";
		break;
		
		case "Saxon_3":
			dialog.text = "��� ������ '���'? �������, � �� ���, � ����. ��� �. � ������, � ���� ��, ��������� ���. ���� ��� ����� ������� � ����� � ������ ����� � ��� � ������������ ����, ���� ������� � ����. � ������� �� ������. ����� �������, ������� ������ ���, ����� ����������� � ������ � ������� �����.";
			link.l1 = "�� ������� �� � ���������� ��� ��������� ���� ������ ����, ������� ����, ������� ����� � ������ ����������� ���� ���������� ������?";
			link.l1.go = "Saxon_4";
		break;
		
		case "Saxon_4":
			dialog.text = "����� ����� ��������������� ������� � ��������� ��������� � ����������. ������ ����� �� ������, ���� ����� ��� � ������, �������� ����� �� ����������� �����. �� ��� �� ������� ���� � ������. ��� ������ �� ������������, ��� ������ ��������� ������ ��� ������ � ������������, ��-��!";
			if(sti(Pchar.money) >= 40000)
			{
				link.l1 = "�������! ��� ���� ������, ���������� ���� ���� � �������� �� �����, � ����������, ����� ��� ����������� ������.";
				link.l1.go = "Saxon_check";
			}
			link.l2 = "��� ��� �������! ������� ���� �������������, ���� ������, �� � ������"+ GetSexPhrase("","��") +" ������ �������� ������� ������, ��� ������ ������� �� ����� ������.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OnceAgain";
		break;

        case "OnceAgain":
            NextDiag.TempNode = "OnceAgain";
			dialog.text = "��� ��� �������, �������! �� ���-���� ������ ������� ���� ������� ������ ����������?";
			link.l1 = "�� �����, ���� ������, ���������� �����. ���������, �� ������� �� ������� ���� ������ �� ���� �������?";
			link.l1.go = "Saxon_4";
            link.l2 = "���, �� �����"+ GetSexPhrase("","�") +". ��������� ����������, ���� ������.";
			link.l2.go = "exit";
		break;

		case "Saxon_check":
            if (FindFreeRandomOfficer() == -1)//���� ������� � ���������
            {
                dialog.text = "��. � ��� ������ �������� ��������, �������. �������������, ����� �� ������� ���� ��� ������.";
    			link.l1 = "������.";
    			link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgain";
    			break;
            }
			if (sti(PChar.reputation) < 51)//��������� �������� ���������, ��� ������� � ����� �������
			{
				dialog.text = "��... ������, ���, ���� �� ������ ������� ���������� � ���. � �� �������, ��� �� ����� ������� � ������������ �����!";
				link.l1 = "����� �� ������! ������, �������, ����� ������.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgain";
			break;
			}
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 21 + MOD_SKILL_ENEMY_RATE)//��� ������ ���������� - � ���
			{
                dialog.text = "��. ������ �������, �������, �� ���� ��� � ������� ������, �� ���� ���� ���� �� ������� ������� �� ���. ���� ���� ������, ��� ��� �� ������ � ��������� ��������. ��� ��� �, �������, ��������� ���������� � ���.";
    			link.l1 = "��� ��, � �� ����� �� ����������, � �� �� ������� �� �������, ������ ����. �� ����� ��� ��� ��������, �� ������������. ���� �� ����� �������������...";
    			link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgain";
    			break;
            }
			dialog.text = "��� � �������. ������� ������� ����� � �������. �� �� ��������� � ����������� �� ���� �������.";
			link.l1 = "�������, � �� ��������"+ GetSexPhrase("","�") +".";
			link.l1.go = "Exit_hire_Saxon";
		break;
		//<-- ��������-��������
		
		//--> ������-�����
		case "Lostpirate":
			if (sti(PChar.reputation) < 36)//��� ���������� ��������� - � ���
			{
				dialog.text = "�����������, ���! ����� ������� ����� ������ ������������ ���� � ������� ����� ������, � �� �������������� ����� �������� ������.";
				link.l1 = "��� �� ������� ���� � ���� ��������� ���? �������� ������� ������� ����?";
				link.l1.go = "Lostpirate_1";
			}
			else
			{
				dialog.text = "� �� ��������"+ GetSexPhrase("���","���") +", ���! � ���� ���� �� ���������, ������ �� ������ ��������, ��-��!";
				link.l1 = "����������, ���� ������� ������. �� ���� ��� � ������������. � � ������ �����"+ GetSexPhrase("","�") +" ���� ������.";
				link.l1.go = "exit_Rep";
			}
		break;
		
		case "exit_Rep":
			NextDiag.TempNode = "Lostpirate";
			dialog.text = "� ������� �� ������������. ���� ������� � ���� ����. � �� � ���, ��� �������. ��� ��� �� ������� ������ ������ ������������ ����������� ��� ���, ������ �������.";
			link.l1 = "�� ��� ���� ����������, ����������. � �, �������, �������� ������ ������.";
			link.l1.go = "exit";
		break;

		case "Lostpirate_1":
			dialog.text = "�� �������. � ������ ����, � �� ����������. ��������������� ��������� ��� ����, � ���������� ������� ������. �������� ����� ������������ ��� ������ ������ ������� � ��������. ��� ���� �, ������ �������, �������� ����. ����\n�� �������� ���������, ��� �������� �������. ��� �������, ������ ����������� ��� � ������� ������. ���� ������� ���������, �� ��������� �� ���.";
			link.l1 = "��, � ��� �� ����� ������������ ������ �������� � ����� ������������ ������� ��� �����, �������� � �����������?";
			link.l1.go = "Lostpirate_2";
		break;
		
		case "Lostpirate_2":
			dialog.text = "(���)������ ������ � ���� ����, ��� ��������� �������, ����� ��� ����� ���-�� - �� �� �����, � �� �����\n��� ������� ����� ���������� �������, �� ����� ����� ����������� ����, ������� � �������� �� ���� ������ �� ������� ����������. �� ���� �������� �������� ���� � ���, ��� ���������� ������� ��������� � ������� ������, ������ ��� �� ������� �������, � ���� �������� ���� � ��� � ���������, �� ����� ������� ���� � ������ ����. ����� ��������, � ��������� ����� ������� �������\n� ���� ���, ����� �������� ���� ����������, � ������ ��� ������� � ������������ ������. ����� ���������� ���� ����, ������� �������� ��������, �� �������� ������ �� ����. ����� � ���� �� ����������\n���� �������� ��� ����� � ����������� ����� ������ � �������. ����������, ��� ���� � �������. ��� �������� ���. ������, ������� � �������� ����, �������� �� �������� ����� ��������, ��������. � � ��� ���, � ������ � ���� � �������� � �����, ��� � �������� � ����������\n����� ����, � ��������� � ������������. ��� � ���� ����. ��� ��� � ��������� ��������� ���, ��� ��� ���� �� �������, ���� � ����.";
			link.l1 = "�������� �������. � ��� �� ������ ����������� ������?";
			link.l1.go = "Lostpirate_check";
		break;
		
        case "OnceAgainLP":
            NextDiag.TempNode = "OnceAgainLP";
			dialog.text = "�� ���, ���, ���� ���������"+ GetSexPhrase("��","���") +" ���� �������� ��������? ��� ����������? � �� ������, ��� �� ����������� - � �� ��� ��� ���!";
			link.l1 = "�� � ���� �� � ����, ��� � �������. ��, �����, ����� �������� �� �����?";
			link.l1.go = "Lostpirate_check";
            link.l2 = "����� ����� �������, ��� ������ �� ���� ������� �� ���� ������� ������� �� ��� ��� �� ������������ ���� �����. ��������, ���-�� � ������� � ���� ���������, �� � ������� ������� �����"+ GetSexPhrase("","�") +" ��� �����.";
			link.l2.go = "exit";
		break;

		case "Lostpirate_check":
            if (FindFreeRandomOfficer() == -1)//���� ������� � ���������
            {
                dialog.text = "��. � ����� �� ����� � ��� �� ������... �� ����, � ��� ������ �������� ��������, ���. � ��������� � ������� � ��������� � �� �������. ��� ��� �������� ��� �������� � ���� ������ �����.";
    			link.l1 = "��, �������� � ���� ���. ��������, ������ ���� �����.";
    			link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgainLP";
    			break;
            }
			if (sti(PChar.reputation) >= 36)//��������� �������� ���������, ��� ������� � ����� �������
			{
				dialog.text = "��... ������, ���, ���-�� �� ��� �� ���������. ��� ������� �������, ���� �������... �� ������ ����� ���� ������ �����. ����� � �������� �����, � ���� ������ �����.";
				link.l1 = "�����, ��������� ����! ������, �� ������ ���...";
				link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgainLP";
				break;
			}
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 31)//��� ������ ������� - � ���
			{
                dialog.text = "��� ����� ���������� ����, ������ �� ������, � �� ���������� � ������ ��������� ����. � � �����, ������, ������ �� ����� ��������, � ������.";
    			link.l1 = "��� ��, ���� ���� �� ������� ���� � ������������ ����, ��� ������ �� �������, �� ��� ����������. �����, ������ �����.";
    			link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgainLP";
    			break;
            }
			dialog.text = "�������� ���� � ���� ��������, �� ���������! � ���� ����� ��������� ����� � ����������� ���� - ����� ��� ������, ��� ��� ��������� ������ ������ �� �����!";
			link.l1 = "������ �� � ���? �������, � ���� ������� �� �� � ��� �� ������� �������.";
			link.l1.go = "Exit_hire_Lostpirate";
			link.l2 = "� ������"+ GetSexPhrase("","�") +" ���� ������� � ������ ��������. �� ������ ���� �� ������ ��������, ����� ��� ��������� ������, ����� �� ����� ���������� ���� �� ������� ������. ��� �������� ��������� ������ ����� ����, �� � �� ���� ��������� ���� �������� �� ����������� �����.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OnceAgainLP";
		break;
		//<-- ������-�����

		//--> �������
        case "hired":
			NextDiag.TempNode = "Hired";
			dialog.text = "����� ����� ������������?";
			link.l2 = "�� ������. � �������� ��� ����� �����!";
			link.l2.go = "AsYouWish";
            Link.l5 = "������ ��� ������!";
            Link.l5.go = "stay_follow";
			Link.l3 = "� ����, ����� �� �������� �� ������������ ���������� �� ����.";
			Link.l3.go = "TargetDistance";
			
			// �� ��� ������� ��������� ����� �� ��� ���������  -->
			if(IsEntity(loadedLocation))
			{
				if(CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if(iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if(sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = "� �������� ���� ����������� ����� ������!";
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
            link.l9 = "������. ������.";
			link.l9.go = "exit";
        break;
		//<-- �������
		
		//--> ������ ��������� ��������
		case "TargetDistance":
			dialog.text = "�� ����� ������, �������? ������� � ������, �� �� ����� 20-��.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "�������, ��� �� ������ ���!";
				link.l1 = "������, �������� �����...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "� ���� ������ �� �����, ������ �� ��������. ��� ��� ����������, �������?";
				link.l1 = "��, ������ ��� �� ���� � ���������.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "� ������� �������, ��� ����� 20 ������ �� ���� ��� ��������� ������.";
				link.l1 = "������, ������� �� ���������� � 20 ������.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "������ �����, �������� � ��������.";
			link.l1 = "������.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- ������ ��������� ��������

		//--> ����
        case "Exit_hire_Saxon":
			AddMoneyToCharacter(Pchar, -40000);
			npchar.MusketerDistance = 10;
			TakeNItems(npchar, "Mineral7", 1);
			TakeNItems(npchar, "indian17", 1);
			TakeNItems(npchar, "potionwine", 1);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit_hire_Lostpirate":
			TakeNItems(pchar, "Mineral4", 5);
			Log_Info("�� �������� ��������");
			PlaySound("interface\important_item.wav");
			npchar.MusketerDistance = 10;
			TakeNItems(npchar, "Mineral2", 1);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			locations[FindLocation("Shore59")].DisableEncounters = false; //��������� � ����� �������
		break;
		//<-- ����
		
		//--> ����������
		 case "AsYouWish":
			// �������� �� ���� -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "�������, ���� ��� � ��������� ������� ������ ��������� - ������� ������� � ����� ������� �� ������. ��� �� ������ ������ ��������� ���� �� ����?";
					Link.l1 = "��... ���, � �� ��� ����"+ GetSexPhrase("","�") +" � ����. ���������, ���� �� ����� � ����.";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// �������� �� ���� <--
			dialog.text = "��� �������, �������, ������ ���. ������� ������ ��������� ��� �� �����.";
			link.l1 = "�������, � ���������"+ GetSexPhrase("","�") +". �� ��� ��� �����.";
			link.l1.go = "exit";								
			link.l2 = "� �� ����. ������ �����������, ���� ��������.";
			link.l2.go = "Exit_Fire";		
		break;

		case "exit_fire":
   			NextDiag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Fired":
		      NextDiag.TempNode = "Fired";
		      dialog.text = "� �� ������������ ���, ��� �� ������� �� ��� �������. �����, ������� � ������� ��������.";
		      Link.l1 = "�� �� ��� � �� �����.";
		      Link.l1.go = "Exit";
	    break;
		//<-- ����������
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		//--> ������-���������
		case "stay_follow":
            dialog.Text = "����� ����� ����������?";
            Link.l1 = "���� �����!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "������ �� ���� � �� ��������!";
            Link.l2.go = "Boal_Follow";
        break;
        
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "���� �������� ����������!";
            Link.l1 = "������.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "���� �������� ����������!";
            Link.l1 = "������.";
            Link.l1.go = "Exit";
        break;
		//<-- ������-���������
		
		//////////////////////////////    ������-��������� -->
		case "Gover_Hire":
            dialog.Text = "����� �� �����!";
            Link.l1 = "����� �� �������� � ������������ ������, � ���� ������ ���������� �� ��������� ��������.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "� ���������"+ GetSexPhrase("","�") +".";
            Link.l2.go = "Exit";
            NextDiag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // ������ ��������� -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// ������ ��������� <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  �� -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  �� <--
			NextDiag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "����� ����� ����������? ��������� ��� ����� ��� " + FindRussianDaysString(iTemp) + " �����.";
			}
			else
			{
			    dialog.Text = "����� ����� ����������?";
			}

            Link.l1 = "����� ����� ������� �� " + NPCharSexPhrase(NPChar, "������", "�������") + " �� ������ ������?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "�� " + NPCharSexPhrase(NPChar, "�����", "�����") + " ��� �� �������, � ������ ���� � ��������� ������.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "����� ��������.";
            Link.l9.go = "Exit";
            NextDiag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "��� ������ ��������� ��� �������� " + FindRussianMoneyString(iFortValue*iTax) + " � ����. �� " + FindRussianDaysString(iTemp) + " � " + NPCharSexPhrase(NPChar, "������", "�������") + " " + FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum)) + ".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "� ���� ������� ��� ����� �������.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "��������� �� ������!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			NextDiag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "������������! ���� ���������� ������ �� ��� ����.";
            Link.l8 = "��� � ������.";
            Link.l8.go = "exit_hire";
            NextDiag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  �� -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  �� <--
        break;
        //////////////////////////////    ������-��������� <--

		//�������� ��� ���������� 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "����������� ������.";
			Link.l1 = "��� �������� ��������.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "��� �������� ������ �������.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // ������ ��� ����-�����
			{
			    Link.l3 = "� ����, ����� �� �� ����� ����� �� ������� ���� ������� � ������� ����� ��������������.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "���� ������.";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "��� �� �� �������?";
			Link.l1 = "� ���� ����� �� �� ���� ������� �� �������. �������� ���� � ���� �������.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "��� ����� ����� �� ���� ��������� ������� �� �������.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "��� �� �� �������?";
			Link.l1 = "� ���� ����� �� �� ����� ���� ������� ����� ��������. �� ������� �����.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "����� ������ ����� ������ �� �������, ��������, ����� �������� ��������� �����, ����� ���� ����.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "��� �����.";
			Link.l1 = "������.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "����� ���������.";
			Link.l1 = "������.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "��� �����.";
			Link.l1 = "������.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "����� ���������.";
			Link.l1 = "������.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	}
}