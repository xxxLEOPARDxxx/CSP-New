void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string attrLoc = Dialog.CurrentNode;
    
	if (findsubstr(attrLoc, "AndreAbelQuestSetNationLicence_", 0) != -1)
 	{
		i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceNation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
		Dialog.CurrentNode = "Andre_Abel_In_Tavern_Quest_Complete_2";
 	}
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = RandPhraseSimple("����������� ���, �������...", "��� ��� ������, �������.");
			link.l1 = "������, ��������, ��� �� �����. �� ���� ������� ���� ��������.";
			link.l1.go = "exit";
			if(GetCompanionQuantity(PChar) != COMPANION_MAX)
			{
				link.l2 = "��, � ��� ������ �� �����"+ GetSexPhrase("","�") +". �� �������?";
				link.l2.go = "Andre_Abel_1";
			}
		break;
			
		case "Andre_Abel_1":
			dialog.text = "���, �� �������... ���� ����� " + GetFullName(NPChar) + ". � ������� ������� '" + NPChar.ship.name + "'.";
			link.l1 = "� � " + GetFullName(PChar) + ". �� ���-�� ������?";
			link.l1.go = "Andre_Abel_2";
		break;
			
		case "Andre_Abel_2":
			dialog.text = "�������, ���� � ������������ �� ���� ������? ��� ����� ����� ������ �� ����-�-������.";
			link.l1 = "�����-��? � � �� �����"+ GetSexPhrase("","�") +"...";
			link.l1.go = "Andre_Abel_3";
		break;
			
		case "Andre_Abel_3":
			dialog.text = "�� �� ������ � ����� ��������� �� ����� 3000 ��������, � ��� ����� ��������� � 15 ����.";
			link.l1 = "��, � � ��� ������� ����� ������ �������?";
			link.l1.go = "Andre_Abel_5";
			link.l2 = "���, �� ��������. �� ���� ������� ������������� �� �������.";
			link.l2.go = "Andre_Abel_4";
		break;
			
		case "Andre_Abel_4":
			dialog.text = "����� ����...";
			link.l1 = "�� ����������...";
			link.l1.go = "exit";
			NPChar.LifeDay = 0;
			NextDiag.TempNode = "Andre_Abel_No_Quest";
		break;
			
		case "Andre_Abel_No_Quest":
			dialog.text = RandPhraseSimple("����� ����, ��� � ��� ��� ����������� ������ ���...", "��� �, ������� ����� ����������� �����.");
			link.l1 = "�� ����������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_No_Quest";
		break;
			
		case "Andre_Abel_5":
			dialog.text = "���� � ���, ��� � �������� ����� ������� � ������� �� ������ �����. ������ ���������� ������� ��������� � ���������������.";
			link.l1 = "�� ��� �, � ������"+ GetSexPhrase("��","��") +". ��� ������� ��� ����� � ��������?";
			link.l1.go = "Andre_Abel_6";
			link.l2 = "������� ��������... � ���� ���� ������ �����, � ���� ����������� ���-�� �� ����������� �� ������.";
			link.l2.go = "Andre_Abel_4";
		break;
			
		case "Andre_Abel_6":
			dialog.text = "��, ������� ��������� �����. ���� �� ��������� ���� ���� � ������, � ���� ����� ��� �����.";
			link.l1 = "������. �� �������...";
			link.l1.go = "exit";
			SetQuestHeader("Andre_Abel_Quest");
			AddQuestRecord("Andre_Abel_Quest", "1");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("��","���"));
			PChar.Quest.Andre_Abel_Quest_1Day_Left.over = "yes";
			PChar.QuestTemp.Andre_Abel_Quest_In_Progress = true;	// ���� - ����� �����
			SetFunctionTimerCondition("Andre_Abel_Quest_2Days_Left", 0, 0, 2, false);
			NextDiag.TempNode = "Andre_Abel_To_Sea_1";
		break;
			
		case "Andre_Abel_7":
			dialog.text = RandPhraseSimple("��� ������� � ������, ������� " + GetFullName(PChar) + ".", "����-��-����� - ����� ���������, �� �� �� �����, ���� � � ��� ������, �� ����� �������� ��� �� ��������.");
			link.l1 = "�� ����� �� ������ �������...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Andre_Abel_7";
		break;
			
		case "Andre_Abel_To_Sea_1":
			dialog.text = "�� ���, �� ��� �������?";
			link.l1 = "��. ��������� ��������� � �����.";
			link.l1.go = "Andre_Abel_To_Sea_2";
			link.l2 = "���, � ���� ��� �������� ���-����� ����.";
			link.l2.go = "Andre_Abel_To_Sea_1_1";
			NextDiag.TempNode = "Andre_Abel_To_Sea_1";
		break;
			
		case "Andre_Abel_To_Sea_1_1":
			dialog.text = "� ������ �� ������������? ��� �� �������, � ��������� � ������.";
			link.l1 = "� �����. �� �� ������...";
			link.l1.go = "exit";
			//	NextDiag.Tempnode = "Andre_Abel_To_Sea_1";
		break;
			
		case "Andre_Abel_To_Sea_2":
			dialog.text = "�� ��� � �������.";
			link.l1 = "�������, ���� ���� �� ������� ��� ������.";
			link.l1.go = "Andre_Abel_To_Sea_3";
			NextDiag.TempNode = "Andre_Abel_7";
		break;
			
		case "Andre_Abel_To_Sea_3":
			DialogExit();
			NextDiag.CurrentNode = "Andre_Abel_7";
			AddQuestRecord("Andre_Abel_Quest", "3");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","�"));
			PChar.Quest.Andre_Abel_Quest_2Days_Left.over = "yes";
			SetFunctionTimerCondition("Andre_Abel_Quest_15_Days_Is_Left", 0, 0, 15, false);
			SetFunctionNPCDeathCondition("Andre_Abel_Quest_Andre_Is_Dead", "Andre_Abel", false);
			SetFunctionLocationCondition("Andre_Abel_Quest_Battle_With_Pirates_Squadron", "Hispaniola2", false);
			SetFunctionExitFromLocationCondition("Andre_Abel_Quest_Delete_Andre_From_Tavern", PChar.location, false);
		break;
			
		case "Andre_Abel_15Days_Left_1": // ��� �� ������, ���� ����� ����������� �����, ����� ����� ����� ��������� � �� � ����� ����-�-������
			if(PChar.location == "FortFrance_Tavern")	// �� ������� ����� ���� �� �������� fix 
			{
				dialog.text = PChar.Name + ", �� ���� �������! �� �����������, ����� ���� ����� ��������� ���������� �������� ������������ � ���� �������� ����-��-������ ����� ���������!";
				link.l1.go = "Andre_Abel_15Days_Left_In_FortFrance";
				break;
			}
			dialog.text = PChar.Name + ", �� ������� ����! �� �� ������ ��������� �� ����-�-������ �� ���������� ����!";
			link.l1 = "�� ��������, ��������, �� � ���� ���� ���� � ��������, ��� ������ ������ ������, ������ ����� �������.";
			link.l1.go = "Andre_Abel_15Days_Left_2";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_SetImmortal(NPChar, true);
		break;
			
		case "Andre_Abel_15Days_Left_In_FortFrance":
			dialog.text = "������� ������ ��������, ������� � �������� �������!";
			link.l1 = "��, ��� ���� �����...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
			
		case "Andre_Abel_15Days_Left_2":
			dialog.text = "� �����, �� ���������, ��� �� � ����� �������������� � ���� ���� �� �����!";
			link.l1 = "���� � ��� �� ������?..";
			link.l1.go = "Andre_Abel_15Days_Left_3";
		break;
			
		case "Andre_Abel_15Days_Left_3":
			dialog.text = "�������, �� ������ �� ����������.";
			link.l1 = "��� �����, ��� �����...";
			link.l1.go = "Andre_Abel_15Days_Left_4";
		break;
			
		case "Andre_Abel_15Days_Left_4":
			DialogExit();
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
//			LAi_ActorGoToLocatorFunc(NPChar, "reload", "reload6_back", "Andre_Abel_Quest_Delete_Andre", 15);
			LAi_ActorGoToLocator(NPChar, "reload", "reload6_back", "", 15);
		break;
			
		case "Andre_Abel_In_PortPax":
			dialog.text = "�������, �������, �� ���� ����� ��������. � ������ ���� 3000 ����������� �������� - �� ����������?";
			link.l1 = "���, �������... ��������, � ����� ��� ������������ �������������? ���� �� ���� �����, �� ���������� ����� ������ �������� �� ������������.";
			link.l1.go = "Andre_Abel_In_PortPax_2";
			Group_DeleteGroup("Andre_Abel_Quest_Pirates_Ships"); // �� ������ ������
			//AddMoneyToCharacter(PChar, 3000);
			TakeNItems(pchar, "jewelry17", 33);
			Log_Info("�� �������� ���������� ������");
			PlaySound("interface\important_item.wav");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_SetImmortal(NPChar, true);
			PChar.Quest.Andre_Abel_Quest_15_Days_Is_Left.over = "yes";
		break;
			
		case "Andre_Abel_In_PortPax_2":
			dialog.text = "��, � ��������� ������� ����� ��������� ��� �� � ��� �� �������?";
			link.l1 = "��� ��� ���! � � ���� � ����� �� �������� ������� ��� ����� � ����� ������������ � �������.";
			link.l1.go = "Andre_Abel_In_PortPax_3";
			link.l2 = "��� �� �� ��� �������� �������, ��� ��� ������� ��������� ��� ������ � ������ ��������� �����?";
			link.l2.go = "Andre_Abel_In_PortPax_5";
		break;
			
		case "Andre_Abel_In_PortPax_3":
			dialog.text = "��, ��� ������� ������� ��������...";
			link.l1 = "�������... ��, ��������� ����������!";
			link.l1.go = "Andre_Abel_In_PortPax_4";
		break;
			
		case "Andre_Abel_In_PortPax_4":
			DialogExit();
			AddQuestRecord("Andre_Abel_Quest", "9");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("Andre_Abel_Quest");
			DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
			PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead.over = "yes";
			NPChar.LifeDay = 0;
			LAi_ActorGoToLocator(NPChar, "reload", "reload6_back", "", 15);
//			LAi_ActorGoToLocatorFunc(NPChar, "reload", "reload6_back", "Andre_Abel_Quest_Delete_Andre", 15);
		break;
			
		case "Andre_Abel_In_PortPax_5":
			dialog.text = "��� �������� ������� �������... ��������� ����� � �������, � ���, �� ������� ����, � ��� � ��������.";
			link.l1 = "��� �, �����...";
			link.l1.go = "Andre_Abel_In_PortPax_6";
		break;
        
        case "Andre_Abel_In_PortPax_6":
			DialogExit();
			LAi_ActorSetSitMode(NPChar);
			LAi_SetSitType(PChar);
			FreeSitLocator("PortPax_tavern", "sit_front2");
			FreeSitLocator("PortPax_tavern", "sit_base2");
			ChangeCharacterAddressGroup(NPChar, "PortPax_tavern", "sit", "sit_front2");
			DoFunctionReloadToLocation("PortPax_tavern", "sit", "sit_base2", "Andre_Abel_Quest_Dialog_In_PortPax_Tavern");
		break;
			
		case "Andre_Abel_In_Tavern_1":
			dialog.text = "� ����� ���... ������ ������ ����� �, ��� �� ����� ������������� ���������������, ���������� � ���������...";
			link.l1 = "������! �� � ��� �� �������� �� ��������, ������� ���������� ����������� ��������?";
			link.l1.go = "Andre_Abel_In_Tavern_2";
		break;
			
		case "Andre_Abel_In_Tavern_2":
			dialog.text = "������ � ��... ��� ���, �������, ��������� ���������, ��������� ��� ���� ������ � ����� �� 50 ��������� �� ���� ���� �������. � ���������. ��-������: ������ ��� ��� ��������� �����, � ��-������: � �� �����, ��� ������� ��� ������ �������������� ��� ��������. �� � ������...\n"
                          + "�������� ����� ����� ���� ��������� �� ��� ������ ������ ��� ����� ��� ��������� ������. ��� ����� ������� ����, ������, �������� �������� ����� �����, ����� ��������� ���. ������ ��, ��� ���� ���-���� ������� ��� ������� � ������ �����...\n"
                          + "��� ����� ���� ������� � �������� ��������� ������� ����� ������� ������... ���� �� �� ���������� ���������� ������, ��������������� ���������� ����, �� �� ����� � ����� ��� �� �������������...\n"
                          + "�������� ��� ������ ������, � � ������� ���������� ��������� �������� ������ � ����-��-�����. ��� ��������� ���� ����������� ������ � ������ ��� � ������� ����� ����� �������� � �����... ����� ����� � �������� �����, ���� ����� �� ����-�-������ � ���� ����� ���������. �� ����� �� ������ ��������� ���� ������ ������...\n" 
                          + "� ������ �� � ���"+ GetSexPhrase("","�") +" �� ������...";
			link.l1 = "�� ��, ��������, ���� �� � �������...";
			link.l1.go = "Andre_Abel_In_Tavern_3";
		break;
			
		case "Andre_Abel_In_Tavern_3":
			dialog.text = "� ����� ��� �����, ������ �� ����� ����������� �� ������� ��������. � ������, ��� � ���� �����?.. � ��� � ����� �� ����� �� ��������, ������ ����� ��� ������ ����� ��������� � ���, ��� ������ ������� � �������� ������...\n" 
                          + "������, ������, �?.. ����� �� ������� � ��������.";
			link.l1 = "� ��� � ��� �����?!";
			link.l1.go = "Andre_Abel_In_Tavern_4";
		break;
			
		case "Andre_Abel_In_Tavern_4":
			dialog.text = "�����: ���, ���, � ���, ����� ����� ����� ��������, ��� �� ������ ������ �����������, ������������... �����, ��� ������ ��� ����������� ���������� � �������� ��� ���� � ��� �� �����������...\n" 
                          + "�����, �?.. ���-�� ���� ���� ������� - ��� ������ ������.";
			link.l1 = "��������, �����, �� ���� ��������� � ��� �������? �� � � �� ������"+ GetSexPhrase("","�") +" � ��� �����, � � ��� ���� ������ - ������ �����.";
			link.l1.go = "Andre_Abel_In_Tavern_5";
			link.l2 = "�����������, �������, �����, �� �� ������� ��������� ����, � � ���� ���� ������ ������ �����...";
			link.l2.go = "Andre_Abel_In_Tavern_7";
		break;
			
		case "Andre_Abel_In_Tavern_5":
			dialog.text = "�� ����... �� ��, ��������, ����"+ GetSexPhrase("","�") +". ���, ��� ���... ������.";
			link.l1 = "������� ��� ��������, ����� ������, ��� �� �� ����... �� �� ���������� �� ���.";
			link.l1.go = "Andre_Abel_In_Tavern_6";
		break;
			
		case "Andre_Abel_In_Tavern_6":
			DialogExit();
			NPChar.greeting = "pirat_common";
			NPChar.LifeDay = 0;
			NextDiag.CurrentNode = "Andre_Abel_In_PortPax_Tavern_No_Quest";
			CloseQuestHeader("Andre_Abel_Quest");
			DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
			LAi_SetSitType(NPChar);
			LAi_SetPlayerType(PChar);
			DoFunctionReloadToLocation("PortPax_tavern", "tables", "stay3", "");
		break;
			
		case "Andre_Abel_In_PortPax_Tavern_No_Quest":
			dialog.text = LinkRandPhrase("����, ��� �� �� ������ ������ ���...", "���-�� ��� ������ ������?..", "���� ��� ������ ����� ������...");
			link.l1 = "�����, �� ��������, �� �� �������� ������������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_In_PortPax_Tavern_No_Quest";
		break;
			
		case "Andre_Abel_In_Tavern_7":
			dialog.text = "������, �?.. �� ��� � ��� ���� �������� �������� �� ������������. ����� ������ ����, �� ���"+ GetSexPhrase("","�") +" ������. � ��� ��������� ��������������. �� ���, ����������?";
			link.l1 = "� ����, ���� �� ����! �����, ����� � ��������, ����� ���-�� ���������.";
			link.l1.go = "Andre_Abel_In_Tavern_8";
			link.l2 = "���, ����� ���� � ��������� �� ����� ������������ �������������� - ��� �� �� ���.";
			link.l2.go = "Andre_Abel_In_Tavern_5";
		break;
			
		case "Andre_Abel_In_Tavern_8":
			dialog.text = "��� � �������!.. � ���� ����� ���� ����� � �������. �� ����� ���� ��� ���� ������ ������� ������.";
			link.l1 = "���... ���������� �� �������������.";
			link.l1.go = "Andre_Abel_In_Tavern_9";
		break;
			
		case "Andre_Abel_In_Tavern_9":
			dialog.text = "�� ���� �� �������������, ��� � ���� ����������.";
			link.l1 = "����� �������� �� ����. � ����������� ������, ����� ������� � ������.";
			link.l1.go = "Andre_Abel_In_Tavern_10";
		break;
			
		case "Andre_Abel_In_Tavern_10":
			ref rChar = CharacterFromID("Jackman");
			DialogExit();
			AddQuestRecord("Andre_Abel_Quest", "10");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("��","���"));
			NextDiag.CurrentNode = "Andre_Abel_In_Tavern_Continue_Quest";
			LAi_SetSitType(NPChar);
			LAi_SetPlayerType(PChar);
			QuestSetCurrentNode("Jackman", "Andre_Abel_Quest_Jackman_Dialog_1");
			DoFunctionReloadToLocation("PortPax_tavern", "tables", "stay3", "");
		break;
			
		case "Andre_Abel_In_Tavern_Continue_Quest":
			dialog.text = "�� ���, �������"+ GetSexPhrase("","�") +" � ���������? �� ����������?";
			if(!CheckAttribute(PChar, "QuestTemp.Andre_Abel_Quest_Complete"))
			{
				link.l1 = LinkRandPhrase("��� ���.", "�� �� �������� �� ���. �� � ��� ���������...", "�����, ����������... �������, �����������, �� ����� �� ���� ������ ������ �� �������.");
				link.l1.go = "exit";
				NextDiag.TempNode = "Andre_Abel_In_Tavern_Continue_Quest";
			}
			else
			{
				link.l1 = "��, �� ����������. ������� ���� ������ �� ��������.";
				link.l1.go = "Andre_Abel_In_Tavern_Quest_Complete_1";
			}
			break;
			
		case "Andre_Abel_In_Tavern_Quest_Complete_1":
			dialog.text = "��, ����� ����! �� ��� � �� ���� ��� ��������... ��� ���� ��������� ��������������, �����... ���, ����� �������� �������� ���� �����?";
			link.l1 = "������� ������ ����������.";
			link.l1.go = "AndreAbelQuestSetNationLicence_0";
			link.l2 = "� �� �� ����������� �� �������"+ GetSexPhrase("��","���") +".";
			link.l2.go = "AndreAbelQuestSetNationLicence_1";
			link.l3 = "� ����� ����� � ��������� ����������, ��� ���, ��������� ������ �����.";
			link.l3.go = "AndreAbelQuestSetNationLicence_2";
			link.l4 = "����������� �������! � ��� ����������� � ����� ���� ����� �����.";
			link.l4.go = "AndreAbelQuestSetNationLicence_3";
			TakeNItems(pchar, "icollection", 1);
			Log_Info("�� �������� ���������");
			PlaySound("interface\important_item.wav");
		break;
			
		case "Andre_Abel_In_Tavern_Quest_Complete_2":
			dialog.text = "��� � ������. �������� �������� " + XI_ConvertString(Nations[sti(NPChar.LicenceNation)].Name + "Gen") + " � ���� ���� ������ �� 40 ����. �� ������, ��� ������� � ���� ����� ��� ������������� ������... �� �� � ��� ��� ��������� ������.";
			link.l1 = "���� �������! �������... ������, � ������ � ���� �������� ���� ����������?";
			link.l1.go = "Andre_Abel_In_Tavern_Quest_Complete_3";
		break;
			
		case "Andre_Abel_In_Tavern_Quest_Complete_3":
			dialog.text = "��, � �� �������, � ����� ������� ������� �� ���� �� ���� ������� �������?..\n" 
                          + "��, ������ �� � �������. ������� ���� � ������...";
			link.l1 = "��, � ���� ��������� ����������...";
			link.l1.go = "Andre_Abel_In_Tavern_Quest_Complete_4";
		break;
			
		case "Andre_Abel_In_Tavern_Quest_Complete_4":
			DialogExit();
			NPChar.LifeDay = 0;
			GiveNationLicence(sti(NPChar.LicenceNation), 40);
			SetCharacterShipLocation(NPChar, "none");	// ������ ������� �� �����
			NextDiag.CurrentNode = "Andre_Abel_In_Tavern_Quest_Complete_5";
			AddQuestRecord("Andre_Abel_Quest", "23");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Andre_Abel_Quest", "sNation", XI_ConvertString(Nations[sti(NPChar.LicenceNation)].Name + "Gen"));
			CloseQuestHeader("Andre_Abel_Quest");
			DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
		break;
			
		case "Andre_Abel_In_Tavern_Quest_Complete_5":
			dialog.text = LinkRandPhrase("�������, "+ GetSexPhrase("��������","�������") +", �� ���� ����� �������"+ GetSexPhrase("","�") +".", "� ���, ��� �� ����"+ GetSexPhrase("","��") +" ��� ������.", "�������-�� ����� �������� �������� �����.");
			link.l1 = "����� ����!.. �� �����, �� ��������� ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_In_Tavern_Quest_Complete_5";
		break;
        
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}