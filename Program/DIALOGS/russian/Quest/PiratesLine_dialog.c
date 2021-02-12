
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "��� �� � ��� � ����� ��������, ������...";
			link.l1 = "�������.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// -------------------------------------- ����� �1 -------------------------------------------------
		//������ ������� � ��������� ������� � ������ ��������
		case "PiratesMan1":
			if (pchar.questTemp.State == "" || sti(pchar.questTemp.CurQuestNumber) > 8 || sti(pchar.questTemp.NationQuest) == SPAIN)
			{
				if(CheckAttribute(pchar, "QuestTemp.AndreAbelQuest"))
				{
					dialog.text = RandPhraseSimple("���� ����? ������� ����.", "������ ������������ ������, ������.");
					link.l1 = RandPhraseSimple("������ ���? �� ������!", "������� ���� ���. �� �� ������ ������ ���!"); 
					link.l1.go = "exit";
					NextDiag.TempNode = "PiratesMan1";
				}
				else
				{
					dialog.text = "�������, "+ GetSexPhrase("������","������") +"! � ������, �������� � ���� �������... ������������� ������?";
					link.l1 = "����� � ������, � ��� �����?";
					link.l1.go = "PiratesMan1_1";
				}	
			}
			else
			{
				dialog.text = "�������, "+ GetSexPhrase("������","������") +". ��, ������!! ����, ��� �� ���� ���� ����������, ����� ����...";
				link.l1 = "� � ��� ����-��? � ���-�� ��������"+ GetSexPhrase("","�") +" ���� � ������ ���������� ��������?";
				link.l1.go = "PiratesManNot_1";
				npchar.talker = 2; //������ ������
				NextDiag.TempNode = "PiratesManNew1";
			}
		break;
		case "PiratesMan1_1":
			dialog.text = "����� ������� ���� ������ ����� �������. ���� ���������, ������� � �������, ��� ���������.";
			link.l1 = "��, �� ������.";
			link.l1.go = "PiratesMan1_2";
		break;
		case "PiratesMan1_2":
			DialogExit();
			NextDiag.CurrentNode = "Tavern_1"; 
			//LockQuestLine(characterFromId("eng_guber")); // ����� ���������� �������
			chrDisableReloadToLocation = true; 
			bDisableFastReload = true; 
			FreeSitLocator("PuertoPrincipe_tavern", "sit3");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5", "PuertoPrincipe_tavern", "sit", "sit3", "PiratesLine_toTavern", -1);
		break;

		case "PiratesManNot_1":
			dialog.text = "�� ���, ���� �� � ����. �� �����"+ GetSexPhrase("","�") +" ������� �� �������-����������� " + NationNameGenitive(sti(pchar.questTemp.NationQuest)) + ". ������ ��� ���� ��� ��������.";
			link.l1 = "������������� ����...";
			link.l1.go = "PiratesManNot_2";
		break;
		case "PiratesManNot_2":
			dialog.text = "��������, �� ������� �� ��� �����, ����� ���� ������ ����� ��������� � �����. �����, ��� ����� ����� ���� � ����� �����������.";
			link.l1 = "������. ���� ����� �����.";
			link.l1.go = "exit";
            SetQuestHeader("Pir_Line_0_Waiting");
            AddQuestRecord("Pir_Line_0_Waiting", "1");
			AddQuestUserData("Pir_Line_0_Waiting", "sNation", NationNameAblative(sti(pchar.questTemp.NationQuest)));
		break;

		case "PiratesManNew1":
			if (pchar.questTemp.State == "" || sti(pchar.questTemp.CurQuestNumber) > 8 || sti(pchar.questTemp.NationQuest) == SPAIN)
			{
				dialog.text = "�������, "+ GetSexPhrase("������","������") +"! � ������, �������� � ���� �������... ������������� ������?";
				link.l1 = "� ��� ����� ������?";
				link.l1.go = "PiratesMan1_1";
			}
			else
			{
				dialog.text = "�-�, ����� �� � ����� �����������. �� ���� �� �����, "+ GetSexPhrase("��������","�������") +". �����...";
				link.l1 = "����� � ������, � ��� �����?";
				link.l1.go = "exit";
				npchar.talker = 2; //������ ������
				NextDiag.TempNode = "PiratesManNew1";
			}
		break;
		//�������� � ������� ������ ��������
		case "Tavern_1":
			LAi_SetSitType(pchar);
			dialog.text = "��, ��� �������? �����"+ GetSexPhrase("","�") +" ������ ������ �������?";
			link.l1 = "�������?!  ���� ��� ��� ����� ������ � ������� ���������� ��������, �� �����"+ GetSexPhrase("","�") +"... � ��� ������-�� �����?";
			link.l1.go = "Tavern_2";
			npchar.lifeDay = 0;
		break;
		case "Tavern_2":
			dialog.text = "��, ��� ������. ������ � ���� �� ���� ������ ���������, ������ ��� ��� ��������, � � � ����-�����. � ��� �� ������ ��� ��������... � ����������� ��� ��. ��� ������, ������ ��������. � �� �������, ���� �� ������� ������� ������� ������. �� ���, ������"+ GetSexPhrase("��","��") +"?";
			link.l1 = "��, �������� ������... � ��� �� �������?";
			link.l1.go = "Tavern_3";
			link.l2 = "������, �������, ��������� �����, �� � ���� ���� ������ ����, � � �� �������"+ GetSexPhrase("","�") +" ��� �������. � ������, � �� ��� ����������� �������!";
			link.l2.go = "Tavern_over";
		break;
		case "Tavern_3":
			dialog.text = "�� ������ ����������. ����� ���� ������, ����� ����� ���� � �����. �� ������ ������� �� ������!";
			link.l1 = "� �� �� ���������. ��� ������� ����-�� ���������?";
			link.l1.go = "Tavern_4";
		break;
		case "Tavern_4":
			dialog.text = "���������? �� ���. ������ ������ ����� �� �����... �� ���, ������"+ GetSexPhrase("��","��") +"?";
			link.l1 = "������"+ GetSexPhrase("��","��") +".";
			link.l1.go = "Tavern_5";
		break;
		case "Tavern_5":
			dialog.text = "��� � �������! ��, ��������� ����, "+ GetSexPhrase("��������","�������") +". ���� ������"+ GetSexPhrase("","�") +"!";
			link.l1 = "� ���� ���� ��...";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			NextDiag.TempNode = "Tavern_again";
            SetQuestHeader("Pir_Line_1_JohnBolton");
            AddQuestRecord("Pir_Line_1_JohnBolton", "1");
			CloseQuestHeader("Pir_Line_0_Waiting");
			pchar.questTemp.piratesLine = "toJohnBolton";
			sld = GetCharacter(NPC_GenerateCharacter("QuestPirate2", "officer_4", "man", "man", 20, PIRATE, -1, true));
			sld.name = "����";
			sld.lastname = "������";
			sld.rank = 20;
			sld.city = "PuertoPrincipe";
			sld.location	= "PuertoPrincipe_port";
			sld.location.group = "goto";
			sld.location.locator = "goto14";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "JohnBolton";
			sld.greeting = "Gr_MiddPirate";
			sld.talker = 8; //������ ������
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddDialogExitQuestFunction("PiratesLine_q1_tavernEnd");
		break;

		case "Tavern_again":
			dialog.text = "���� ���� ���� � ����� ������-��������. �� ���� � ����!";
			link.l1 = "������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tavern_again";
		break;
		case "Tavern_over":
			dialog.text = "��... ��, ��� ������, "+ GetSexPhrase("��������","�������") +". ���� ���� ����������, ���� ���� - ����������. �����...";
			link.l1 = "������.";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			pchar.questTemp.piratesLine = "over";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("PiratesLine_q1_tavernEnd");
		break;
		//����� � ������ �������� � ����� ������ ��������
		case "JohnBolton":
			dialog.text = "������ ����. �������, �� ������� " + GetFullName(pchar) + "?";
			link.l1 = "��. � �� ������ ���� ���� ������?";
			link.l1.go = "JohnBolton_1";
		break;
		case "JohnBolton_1":
			dialog.text = "��-��. � ��� ���������� ��������� �� ����-�����, � ���������� ���������.";
			link.l1 = "����, �������� � ������, ����� ������.";
			link.l1.go = "JohnBolton_2";
		break;
		case "JohnBolton_2":
			AddQuestRecord("Pir_Line_1_JohnBolton", "2");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1 = "locator";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.location = "PortRoyal_town";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.locator_group = "quest";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.locator = "detector_PQ1";
			pchar.quest.PiratesLine_q1_arrest.function = "PiratesLine_q1_arrest";
			NextDiag.TempNode = "JohnBolton_inWay";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "", 5.0);	
		break;
		case "JohnBolton_inWay":
			dialog.text = "�� ��� �� ��������� �� ���� �����, � � �����, "+ GetSexPhrase("��������","�������") +"...";
			link.l1 = "�� ���� ����, �� ����������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnBolton_inWay";
		break;
		//����� � ��������������� ���������
		case "ArrestInPR":
			dialog.text = "�������� �����, ��� � ��� �� ����� ��������� ���������� ���� ������... ��! �� ��� ��! �� ����������!";
			link.l1 = "��, ��������, � �� �� ������? � ������"+ GetSexPhrase("","��") +" ����� �������� �� ��������� ����� �������!";
			link.l1.go = "ArrestInPR_1";
		break;
		case "ArrestInPR_1":
			dialog.text = "��������� ����������, ��� ������, � ��� ���. �������� �� ����!";
			link.l1 = "��� ����...";
			link.l1.go = "ArrestInPR_2";
		break;
		case "ArrestInPR_2":
			AddQuestRecord("Pir_Line_1_JohnBolton", "3");
			chrDisableReloadToLocation = false; 
			bDisableFastReload = false; 
			LocatorReloadEnterDisable("Portroyal_town", "houseS1", false); //������� ��� �������
			DialogExit();
			AddDialogExitQuestFunction("PiratesLine_q1_toPrison");
		break;
		// -------------------------------------- ����� �2 -------------------------------------------------
		case "EdwardLoy":
			dialog.text = "�� �� ���, "+ GetSexPhrase("��������","�������") +"? ��� ������?";
			link.l1 = "���� ������ �� ����� �������.";
			link.l1.go = "EdwardLoy_1";
		break;
		case "EdwardLoy_1":
			dialog.text = "...�� ����� �������? � ��� ������������ �� ���� ����� �������?";
			link.l1 = "����� ����� �� ���� ����������, ������ ��������� ��� ������.";
			link.l1.go = "EdwardLoy_2";
		break;
		case "EdwardLoy_2":
			dialog.text = "...����� ���?";
			link.l1 = "�� ����. ����� ����� �������� ���� � ��� ���������. � ����� �� �� ���������� � ��� �����������, ����� �������� ���� ���� ������. ������, ��� �� � ����� �����������, �� ��� ���-�� ������� ���� ��������� � ���������� ����.";
			link.l1.go = "EdwardLoy_3";
			RemoveItems(PChar, "BlackLabel", 1);
		break;
		case "EdwardLoy_3":
			dialog.text = "������! ������ �����. � ��� � ����... � ���� � � �� ������?";
			link.l1 = "� ���� �� � �� �������, �� � ������ � ���� � ������.";
			link.l1.go = "EdwardLoy_4";
		break;
		case "EdwardLoy_4":
			dialog.text = "���! ����������! �� ������"+ GetSexPhrase("","�") +" ���� ������ ����, ������ �������� ������!";
			link.l1 = "�������� ���� ���, ���... � ���� ������ ����, ������� � �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "EdwardLoy_again";
			QuestSetCurrentNode("Henry Morgan", "PL_Q2_away_1");
			AddQuestRecord("Pir_Line_2_BlackLabel", "3");
			AddQuestUserData("Pir_Line_2_BlackLabel", "sSex", GetSexPhrase("","�"));
		break;
		case "EdwardLoy_again":
			dialog.text = "�� ��� �����?";
			link.l1 = "��� �����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "EdwardLoy_again";
		break;
		// -------------------------------------- ����� �3 -------------------------------------------------
		case "CapGoodly":
			dialog.text = "��! �������, "+ GetSexPhrase("������","������") +"! ���, ����� ���������. ������������, ��������� �� ����������.";
			link.l1 = "�������, �����! ��������� ������, ��� �� ������������ � ���.";
			link.l1.go = "CapGoodly_1";
		break;
		case "CapGoodly_1":
			dialog.text = "�����, ������������. ������� �� ���, ��� �������� �� ���������� ��������� �������.";
			link.l1 = "���, �� ������ ����������, ��� ������ ��� �� ���� ������� ����... �� ������� ���� ����������?";
			link.l1.go = "CapGoodly_2";
		break;
		case "CapGoodly_2":
			dialog.text = "������, ��������, ����?  �� ���, ������ ������ �� �� �������... ������ �������� � � ����� �������������.";
			link.l1 = "������� ���, ���� �����, ��� ��, ��� � ������� � ��������, ����� ����-�� ���������������. ������ ��� ������������, ������� ������ �������� �� ������ ���? ��� ��� ���� � � ���� ���� �� ����� �� �����. � ����� �� �������� ���� �� ���, � ����� ���� �������, ���� ��� ������ �� �������.";
			link.l1.go = "CapGoodly_3";
		break;
		case "CapGoodly_3":
			dialog.text = "�� �����! ����� ����� �������� ����� ���� ����������?\n� ������ �� ������ ��������, �������� ������� ��������. ��, �� ������� ���� ���... �� � �� ������. ";
			link.l1 = "�����, �� ��������, �������"+ GetSexPhrase("","�") +" �. �� ��� �, ���� ���. ����� ��� � �������� � �����, �����.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "13");
			pchar.questTemp.piratesLine = "KillLoy_toCumana";
			npchar.lifeDay = 0;
			pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1 = "location";
			pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1.location = "Cumana";
			pchar.quest.PiratesLine_q3_loginSeaWolf.function = "PiratesLine_q3_loginSeaWolf";	
		break;
		//������ ��� � ����� �������� �����
		case "SeaWolf":
			dialog.text = "������! �� ���-���� ������"+ GetSexPhrase("��","���") +" �� ����!";
			link.l1 = "� ����� ����� ���� �����?!";
			link.l1.go = "SeaWolf_1";
		break;
		case "SeaWolf_1":
			dialog.text = "�� ��� �� � ���� ��������"+ GetSexPhrase("","�") +"?! �������, �� ���"+ GetSexPhrase("��","��") +" ��������"+ GetSexPhrase("��","��") +"?! �� �����"+ GetSexPhrase("�� ���������","�� ��������") +" �������, �� ����� ����!";
			link.l1 = "�� ���, ������� ������ ��� �������, � ��� ���������� ��������� ��������. � ������� �� � ��� ������.";
			link.l1.go = "SeaWolf_2";
		break;
		case "SeaWolf_2":
			dialog.text = "�� �������! ������� ������ �������� ���� �� ����? � ������� �����... �����!";
			link.l1 = "���� ��� ����� �������� ��� ��������� ����� �������, �� ������ �������� �� ���� ��������� �����.";
			link.l1.go = "SeaWolf_3";
		break;
		case "SeaWolf_3":
			dialog.text = "��������, " + GetFullName(PChar) + ", � ��� ���� ������ �����, ������ ������� ��� ����.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +", ���, ������ ������ ����� �� ���� ���. �� ����� ������ ������� �� ������ ������, ��� ������ ����� ������� ����� ��������� �������� �������� ������ ������.";
			link.l1.go = "SeaWolf_4";
		break;
		case "SeaWolf_4":
			dialog.text = "����-�?! � ������� �� ���� ���?! �� �� ������, ������� ������� ����� ��� �� ���� ������?! ��� ��� �������?! ��?!\n" +
				"� ������� �� ���� ���! ��-��-��! �� � ��������� ���, ��� �����! ��� ���� �� �� ����� ��� ��������! ����� ���������� �����, ��� � ������ ��� �������, ��� ��� ����� �� �������, ��� � �� ���� ������ ��� �����, ��� ������� ��� ��!\n� ���� �� ���������, ������ ������, ��� ������ � ������ ����� �� ����, ��� ������ ���������� � ���� ������!";
			link.l1 = "��������, ���! � ����� ����� � �������� � ��������� ���"+ GetSexPhrase("","�") +", ����� ����� �����. � �� ����� �� �� ��������� �����. �� ����� �� ���� ��������. ������� ������ ���� ������� ��� ���������... � ���� ���� �����-������ ������� �������� ���� �����?";
			link.l1.go = "SeaWolf_5";
		break;
		case "SeaWolf_5":
			dialog.text = "��! ����������� ���� ��������, ����� �� �����, ��� ���� ��� - ��-��...";
			link.l1 = "����������? ��, ����� � �����...";
			link.l1.go = "SeaWolf_6";
		break;
		case "SeaWolf_6":
			LAi_SetCurHPMax(npchar);
            QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");			
		break;
		// -------------------------------------- ����� �5 -------------------------------------------------
		case "PQ5CapGoodly":
			dialog.text = "�������, "+ GetSexPhrase("��������","�������") +"! ����� ������, ��� � ���� ������! ���� �� ����������, ����� ���������. � ���� � ���� ����� ����, �������.";
			link.l1 = "�������. ����� ������� ����� - ��� ������ ��������. ��� �, ����������, ��� �� ����?";
			link.l1.go = "PQ5CapGoodly_1";
		break;
		case "PQ5CapGoodly_1":
			dialog.text = "�� ���� ������ ������ �� �����, ���� � ���� ��� �����.\n��� �� ���������, � ������� �� �������. �� ������ ���� ������ � ���� ���� � ������, ��������. � - ������� �� ��������. �� ��� ���� ��� ��������� ��������� ���� ������� � �������� ������, �� ������, ���, �� ����������. �� ��� � ������� ��������� �������, �������� � �� ���� ��������...";
			link.l1 = "� ���, ������ ��������, ���������? ��� �� ������ �����? �������, � ������� �� ����� ��� �������, ��-��-��...";
			link.l1.go = "PQ5CapGoodly_3";
		break;
		// Warship 13.07.09 ���� �����
		/*case "PQ5CapGoodly_2":
			dialog.text = "�������� � ���, ��� ������� � ������ ����� � ����-�����, � �� �� ����� ���� ���������. ��������� ����� ��� ������� �����������... ������, �������� ��� �����?";
			link.l1 = "� ���������� �� �� ������?";
			link.l1.go = "PQ5CapGoodly_3";
		break;*/
		case "PQ5CapGoodly_3":
			dialog.text = "���� � ��� �������� ��� ������, � �� ���� �� ������. �������. ��� ������� �� ��������� �������� ����.";
			link.l1 = "��, �������� ������. �������, ����� �����������. �����-�� �����������, ��� �� �����?";
			link.l1.go = "PQ5CapGoodly_4";
		break;
		case "PQ5CapGoodly_4":
			dialog.text = "����� ������ �������� �� ����� ���� ������. �� �����������, �������� ����� ��� �����������. ������� ����, ������� ��������. ������ �������, ���, �������, �� ������ ��� �������� ��������\n"+
				"��������� ��� ��� ������ � �����������. �� ����, ��� �� ��������� ������� ���������, �� ��� �������� ������� �� ������ ����� 15 �����.";
			link.l1 = "�����, �� ��� �������, � �� ����� ����� ���� ��������� ����� ������?! ��� �� ����� ������������ ������� �������� ��������, ��� ���� �������� ������ �������. ����� ��� ��� ��, � � ����� �� ���� ������ �������.";
			link.l1.go = "PQ5CapGoodly_5";
		break;
		case "PQ5CapGoodly_5":
			dialog.text = "������, "+ GetSexPhrase("�������","�������") +", ��� ����� � ���� �� �����. ��������� ��� �� ����������.";
			link.l1 = "��� ����� ���, �����, ��� � ���� �� ������ �����? ����� �����-�� '�������', '�� ���� ��������', '��������� �� ����������'... �� ���, ���� �� ������ �������?";
			link.l1.go = "PQ5CapGoodly_6";
		break;
		case "PQ5CapGoodly_6":
			dialog.text = "�� �� �������� �� �����! ���� ������ �����, �� ��� �������� ������� ������ ��� ������, ���� � �� �������� �� ��� �������� �������. �� �������� �������� �����... � ��� �����, �����... ��, ��� ���, ������� ��� �����?";
			link.l1 = "� �� ������ �������������. �� ���� � ������ ���� ����, � ������ �� ��������� �����. ";
			link.l1.go = "PQ5CapGoodly_7";
		break;
		case "PQ5CapGoodly_7":
			dialog.text = "���� � �����. � ������� ������ ��������. ������ � �� ���� �������� ����� ��������.\n ����� ���� �����. � ���� ����� � ������.";
			link.l1 = "���. ���, ����� ����� �������: " + PChar.Name + ", ��� ��� ���� ���� ������ ������. ��� ��� ��, ������� ������-�� ���������. �, �����: ���� ���������� ���� ������ �  ��������� ������� ���... ��������� ����������!";
			link.l1.go = "PQ5CapGoodly_8";
		break;
		case "PQ5CapGoodly_8":
			chrDisableReloadToLocation = false;
			pchar.questTemp.piratesLine = "PL5Hunter_toVillemstad";
			SetQuestHeader("Pir_Line_5_Hunter");
			AddQuestRecord("Pir_Line_5_Hunter", "1");
			AddQuestUserData("Pir_Line_5_Hunter", "sSex", GetSexPhrase("�","��"));
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "houseS1", "none", "", "", "", -1.0);
			DialogExit();
		break;
		//������ ������ ��
		case "PQ5Hero":
			dialog.text = "...������! � ����� ��-��������, � �� �� ��� ����� ��������� ���� ����� �� ����!";
			link.l1 = "��! ������ �������?!! ��� ����! ��� ��� ������!!!";
			link.l1.go = "PQ5Hero_1";
		break;
		case "PQ5Hero_1":
            DialogExit();
			AddDialogExitQuestFunction("PQ5_afterChangeMainHero");
		break;
		//������ � ���� �� ��������
		case "PQ5Aivory":
			dialog.text = "���� �� �����! ���� ������, ���� ��������!";
			link.l1 = "�����������, �������� �� ������ ��������, �� � ���� ����� �� ��� �����. ��� ��� ���������� ���� ���������.";
			link.l1.go = "PQ5Aivory_1";
		break;
		case "PQ5Aivory_1":
			dialog.text = "��!! � ��� �������, ��� � ������. ��, �������� ������, ��� �� ����...";
			link.l1 = "��������...";
			link.l1.go = "PQ5Aivory_2";
		break;
		case "PQ5Aivory_2":
            DialogExit();
			AddDialogExitQuestFunction("PQ5_afterChangeMainHero2");
		break;
		//����� � ������� ���� �����
		case "PQ5CapGoodlyEnd":
			dialog.text = "���� � ����, " + GetFullName(pchar) + "! ���-���� ������"+ GetSexPhrase("��","���") +"! � � ���, ����������, ��������...";
			link.l1 = "��, ������ ���������� ��������� ������, ��� � ������"+ GetSexPhrase("","�") +". ���� ����������� �������!";
			link.l1.go = "PQ5CapGoodlyEnd_1";
		break;
		case "PQ5CapGoodlyEnd_1":
			dialog.text = "��! �� ���������� ���� ���������"+ GetSexPhrase("","�") +"! ���� � ���� ���������.\n������, ��� ����� ��� �� ������, ���� ������ 15 �����, ��������� ������� ���� �����... ���� ������"+ GetSexPhrase("","�") +", �� ������, ��� �� ����� ���� � ����� ����.";
			link.l1 = "������, ��� �� ��� ���������. �����, ����� ��� ����, � ������� ���������.";
			link.l1.go = "PQ5CapGoodlyEnd_2";
			AddMoneyToCharacter(pchar, 15000);
		break;
		case "PQ5CapGoodlyEnd_2":
			dialog.text = "������, �� ���������. � ���� ����� ���� ������� �������� ���� ������������ ����� �������, ��-��...";
			link.l1 = "��, � ���� �� ���? � ������, �����, � ����� ����� ���� ��� ����������?";
			link.l1.go = "PQ5CapGoodlyEnd_3";
		break;
		case "PQ5CapGoodlyEnd_3":
			dialog.text = "� ����? �������� ������ �����, ��� ������ - ������ ���������. � ���� ��� �� ����������, ���� ����� ��� ��������.\n��, ���� �� �����: ���� ������ ������ �����. ��� ��� ����������.";
			link.l1 = "������? � ����� � ��� ���������"+ GetSexPhrase("��","���") +", �� � �����?";
			link.l1.go = "PQ5CapGoodlyEnd_4";
		break;
		case "PQ5CapGoodlyEnd_4":
			dialog.text = "���, �� � �����. ��� �� ������ �� ����. ��� ���, �� ����� �������� � ����.";
			link.l1 = "��, �� ������, ������ �����... � ���� ��� �� ����� ����������, ����� � ���� �� ��� ����?";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "12");
			sld = characterFromId("Henry Morgan");
			LAi_SetHuberTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
			QuestSetCurrentNode("Henry Morgan", "PL_Q5_begin");
		break;
		// -------------------------------------- ����� �6 -------------------------------------------------
		case "JohnLids":
			dialog.text = "����������� ����� ���������� ��������! ��� ������ ������������ ������ ��� �� ���� ������?";
			link.l1 = "����������, ����. ���� ������ � ���� �������.";
			link.l1.go = "JohnLids_1";
		break;
		case "JohnLids_1":
			dialog.text = "����� ������. � ��� ���� ������ ���?";
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "JohnLids_2";
		break;
		case "JohnLids_2":
			dialog.text = "��!! �� ����� ����! � ����� ���� �� ������� � ���� �����?";
			link.l1 = "������� �� ����. ������ � � ���� " + GetFullName(PChar) +  ". �� ��� �� ������� �� ������ �� �����? ����������� � ��� ����. ���� �� �������?";
			link.l1.go = "JohnLids_3";
		break;
		case "JohnLids_3":
			dialog.text = "�������� ��� � ����, ��� ����� ������� ���� ������� ��������"+ GetSexPhrase("","�") +" �� ������� ����� ����� �� ����� " + GetFullName(pchar) + ". �����, "+ GetSexPhrase("���� ���� ����������","���� ������ ����������") +", �� ����\n"+
				"������� ��"+ GetSexPhrase("","�") +" ����"+ GetSexPhrase("","�") +" ��������, � �� ��� �� �������� ��� �� ��������� ������� ������. � �����, ��������� ����� ��� ������, ������ �� ���������...";
			link.l1 = "�� � ������, ��� ��� � ��"+ GetSexPhrase("�� �������������","�� �������������") +"?";
			link.l1.go = "JohnLids_4";
		break;
		case "JohnLids_4":
			dialog.text = "�� ������� �"+ GetSexPhrase("��","�") +" ����� �����. ������ ������� �� ���, �� ������� � �������� ������� ������ ���������� �� �����.\n������ ���� ������������� ��� ������ �� ������: ��� ����� ������ ��������� � �������������, � ������� ���� �������� � ���� ����� ����� ��������. �� � ��� ������ �� ������� ������ � ��� - ���� ��� �� ������, � ���������� � ���� ���������� �� ����� �����. ������ ��, �������� ������� ������ �� �����.";
			link.l1 = "� ��� �� �����������?";
			link.l1.go = "JohnLids_5";
		break;
		case "JohnLids_5":
			dialog.text = "��, ��� �������, ��� ������ ���� ����"+ GetSexPhrase("��","�") +" ���� ����������� �� ���"+ GetSexPhrase("��","��") +" ����������"+ GetSexPhrase("���","���") +". �����, ���"+ GetSexPhrase("","�") +" ���������, ������� � ���� ����� ��� ������, ��� ������.\n"+"���� � ���, ��� � ���� ������� ���� ����, ������� ����� ���� � ����. ��� ���, ��� ������ �������, ��� �� ������� ������ �� � ����... ��� ���-��, "+ GetSexPhrase("��������","�������") +"!";
			link.l1 = "�� ��, ��� �� ���� �� �����. �� ����� ����, ���-���� �������� ��� ������?";
			link.l1.go = "JohnLids_6";
		break;
		case "JohnLids_6":
			dialog.text = "������ ���, ��� ��������� ����� ��� ������, ���� ���� ����� ����-�� ����������.";
			link.l1 = "�� �����, ��������, ������, ����"+ GetSexPhrase("��","�") +" ������������� �� ���"+ GetSexPhrase("��","��") +" ����������"+ GetSexPhrase("����","���") +".";
			link.l1.go = "JohnLids_7";
		break;
		case "JohnLids_7":
			dialog.text = "��, ��� � ������. ���������, "+ GetSexPhrase("�������","�������") +". ��� ����� ���������, ��� ��� ����������...";
			link.l1 = "��-�, �� ������ ��������, �� ��� ����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnLids_again";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "3");
			AddQuestUserData("Pir_Line_6_Jackman", "sSex", GetSexPhrase("��� �����������","��� ������������"));
			AddQuestUserData("Pir_Line_6_Jackman", "sSex1", GetSexPhrase("��","��"));
			Pchar.quest.PQ6_ShoreBattle.win_condition.l1 = "location";
			Pchar.quest.PQ6_ShoreBattle.win_condition.l1.location = "Shore7";
			Pchar.quest.PQ6_ShoreBattle.function = "PQ6_ShoreBattle";
		break;
		case "JohnLids_again":
			dialog.text = "�� ��� �� ��������"+ GetSexPhrase("","�") +" �� ���"+ GetSexPhrase("��","��") +" "+ GetSexPhrase("'������'","'�������'") +", � � ����� ����� ���� �� ����...";
			link.l1 = "� �����"+ GetSexPhrase("","�") +", ����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnLids_again";
		break;
		//������� ��
		case "QuestPirateHead":
			dialog.text = "��, ��� �� � ���� " + GetFullName(pchar) + "! ���"+ GetSexPhrase("","�") +" ���� ������, "+ GetSexPhrase("��������","���������") +"...";
			link.l1 = "���"+ GetSexPhrase("��","��") +" � ���� "+ GetSexPhrase("��������","���������") +"?!";
			link.l1.go = "QuestPirateHead_1";
		break;
		case "QuestPirateHead_1":
			dialog.text = "��, ��� � ���, ��-��������... ��� ���? �� ��-���� �����"+ GetSexPhrase("","�") +" �� ���� ����������?";
			link.l1 = "�����, �����������. ��� ��, ������...";
			link.l1.go = "QuestPirateHead_2";
		break;
		case "QuestPirateHead_2":
			dialog.text = "� �� ���� ��� ����?";
			link.l1 = "�������! ��� ���� �� ���� � ����� � "+ GetSexPhrase("��� �����-��������!","��� ������ - ��� ��������!") +"";
			link.l1.go = "QuestPirateHead_3";
		break;
		case "QuestPirateHead_3":
			dialog.text = "��, � �� �����"+ GetSexPhrase("�","��") +". ����� ����� ����� ���������?";
			link.l1 = "����!! ��, ��� �� ����������...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PQ6_JungleBattle");
		break;
		// -------------------------------------- ����� �7 -------------------------------------------------
		case "FriendLinney":
			dialog.text = "��� ������ ��� � ���� �� ������.";
			link.l1 = "� ��� ����� ������, �������, �� � ��� ��������, ��� ������ ������ � �������.";
			link.l1.go = "FriendLinney_1";
		break;
		case "FriendLinney_1":
			dialog.text = "��, ����� � ��������";
			link.l1 = "���� ����� " + GetFullName(pchar) + ", � �������� ��������� �������. ���� ����� �� �����������, � ��������� �� ������� �������� ��� �������, ����� ������ ���� �������� ��� ������.";
			link.l1.go = "FriendLinney_2";
		break;
		case "FriendLinney_2":
			dialog.text = "�-�, �� ��� �� ����� � ������"+ GetSexPhrase("","�") +". � ����� ���� �����, � ������ �� ��������� ��� � ��������� �������. � �����, � �� ���� �� ������ �� ��������. �� ������ ��� ����� ����������� � ����� ���������, ������� ����� ���-�� �����, �� ������� �� ������� �� ������. ���� ���������� ��� ������� � ������ �����, �� ������� � ���� ������� ��� ����������� ��� ��������. ��� ������������, � ���� ���� � ����.\n"+"���������, � ��� �� ������. ���� ��, �����, �� ����� ������������ �����, �� ����� � �������� �����, ��� ��� ����� '��������' ��������� �� ����� �����-�������. � ���� ���� '��������' ����� ����� � ��� �� �� �� ��� �� ������. ��� � � �������, ��� ���� ������� � �� ���� �� ����� ��������. ����� ����� ���������, ��� � �� ���� ������.";
			link.l1 = "�������. �����, ���-���� ������? ����, ������� ��� ���...";
			link.l1.go = "FriendLinney_3";
		break;
		case "FriendLinney_3":
			dialog.text = "���, �� ������ ��. �� ��� ������ �� ������... � �������� ��� ��������, �� ������ �� � �� ����, ��� ������."; 
			link.l1 = "������, � �����"+ GetSexPhrase("","�") +". ������� �� ����������, �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendLinney_again";
			pchar.questTemp.piratesLine = "Soukins_toSantoDomingo";
			AddQuestRecord("Pir_Line_7_Soukins", "5");
		break;
		case "FriendLinney_again":
			dialog.text = "���������� ��� � �����, ������ � ������ �� ����...";
			link.l1 = "��-��, �������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendLinney_again";
		break;
		//���, ��������� ���� ��������
		case "LeonCapitain":
			dialog.text = "��� ���� ����� �� ����?";
			link.l1 = "��� ������� '��������'?!";
			link.l1.go = "LeonCapitain_1";
		break;
		case "LeonCapitain_1":
			dialog.text = "������� '��������' ��� �� ���, ������ ���������� ���. ��-��-��!";
			link.l1 = "������!!! �� ���� �� ���������?! ��� �������� ���� ������ ������?!";
			link.l1.go = "LeonCapitain_2";
		break;
		case "LeonCapitain_2":
			dialog.text = "� ������� �� �������� ���������� ��������. �� �� ����� ���������� �������, � �� ������ �������� ������� ��������! ������������� � ���, ���� �� ������ ����������� �� �������.";
			link.l1 = "� ���� ��� ������ �� ������� ����� ������� ���������.";
			link.l1.go = "LeonCapitain_3";
		break;
		case "LeonCapitain_3":
			dialog.text = "� ��� ��� �������? �����, ��?!";
			link.l1 = "�� ������ �������� ������ � ���� �� �������"+ GetSexPhrase("","�") +"!";
			link.l1.go = "LeonCapitain_4";
		break;
		case "LeonCapitain_4":
			dialog.text = "�� ��� - ������, � �� ���� �� ��� �� ������� ������� ���������. ������� ��� ����. � ������ � ������� �����, ��� ���� �� ������ �� ��� ������ � ����, ��� �� ���� ������� ������.";
			link.l1 = "�� ��� ������� �� ���� �����������! ���� ������� �������, ��� ������ ������� ���� ������ ������ ������! � ����� �����, ��� � ��� �� �� �����, ����� ����������? �� �� ������� �����, ������ ��������, ����������� ���� ���������!";
			link.l1.go = "LeonCapitain_5";
		break;
		case "LeonCapitain_5":
			dialog.text = ""+ GetSexPhrase("�����","����") +"! �� ��� ��������� � ����� ��������...";
			link.l1 = "�� ���� ������ � ���� ��������!..";
			link.l1.go = "LeonCapitain_6";
		break;
		case "LeonCapitain_6":
			Map_ReleaseQuestEncounter("LeonCapitain");
			pchar.questTemp.piratesLine = "Soukins_toMorgan";
			QuestSetCurrentNode("Henry Morgan", "PL_Q7_afterLeon");
			AddQuestRecord("Pir_Line_7_Soukins", "7");
			AddQuestUserData("Pir_Line_7_Soukins", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Pir_Line_7_Soukins", "sSex1", GetSexPhrase("��","���"));
			LAi_SetCurHPMax(npchar);
            QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//����� �� ������, ������ � ������
		case "PQ8_PirInPan":
			dialog.text = "������, " + pchar.name + ", �� ��� � ����� � ���� � �������. � ����� � ���, �� ��� � ����������� ������! ��� �� ��� ��������?..";
			link.l1 = "�� ��, �� ���� ���� �� ������ �������� ����������.";
			link.l1.go = "PQ8_PirInPan_1";
		break;
		case "PQ8_PirInPan_1":
			dialog.text = "��� ����, ��� �� ����������!";
			link.l1 = "� ��� ���������.";
			link.l1.go = "exit";
		break;
		case "PQ8_RsPirInPan":
			dialog.text = "��, ���� ��� ������� �����! ������� ��� ������� ������ �������...";
			link.l1 = "�� �������?";
			link.l1.go = "PQ8_RsPirInPan_1";
		break;
		case "PQ8_RsPirInPan_1":
			dialog.text = "�������! � ��������� ��� ��� ������� ������ ����. �� ��� ������������ ���������!";
			link.l1 = "��, �������...";
			link.l1.go = "exit";
		break;
		case "PQ8_MPirInPan":
			dialog.text = "� ������, ��� ���� ��������� �� �����! �� � �������� ��� � ������ �� ����� �����.";
			link.l1 = "�� ��, �� ������ ���� ��� ����� ������ ��������.";
			link.l1.go = "PQ8_MPirInPan_1";
		break;
		case "PQ8_MPirInPan_1":
			dialog.text = "� ��� ���� �� �� �����, ��������� ��...";
			link.l1 = "�� �������, ��� �� ���������� � ���� � ����. ��� ���, �� ����� ���!";
			link.l1.go = "exit";
		break;
		//������ ���� ������
		case "PQ8_Mayor":
			dialog.text = "��� ������ �� ����?";
			link.l1 = "������������, ���������. ��������� � �������, �� ��������� ������������ ������...";
			link.l1.go = "PQ8_Mayor_1";
		break;
		case "PQ8_Mayor_1":
			dialog.text = "������ ���.";
			link.l1 = "� ����, ����� �� ������ ��� ������ ���������. � ����, ��� ��� � ���.";
			link.l1.go = "PQ8_Mayor_2";
		break;
		case "PQ8_Mayor_2":
			dialog.text = "��, �� �������...";
			link.l1 = "�� ������� � �����! ������ ���� ����� ������, ����� ������ �������� ���� ���� ���������� ���������. �� ������������� ����, ��� � ���� �����?";
			link.l1.go = "PQ8_Mayor_3";
		break;
		case "PQ8_Mayor_3":
			dialog.text = "�����������. �� � ����� �� ���� ������ � ����� ������. ��� ���� � ���, ��� � ���� ��� ����� �� �������, � �������, ��������, � ��������� ���-���... � ������ �� ����� �� ��������, ����������� � ���� ��������.";
			link.l1 = "� ��� ���� ����?";
			link.l1.go = "PQ8_Mayor_4";
		break;
		case "PQ8_Mayor_4":
			dialog.text = "�� ������ ��������� � ����������. ���� ������ ������ ��� ��� ��������� �������, � �� ����������� ������� ������.";
			link.l1 = "��� ��������� ������?";
			link.l1.go = "PQ8_Mayor_5";
		break;
		case "PQ8_Mayor_5":
			dialog.text = "������� �� ����. �� ��������� �������� ������. ��������� ��� ��������, �� ������ ��� ��������� �������� �� ������� �����. ���������� ���� �� ��������� ������� ������, ������� ���� ����� �� �������.\n"+
				"��� ���, ����� ����, �� ����, �, ����� ����, ��������� � ���� � �����.";
			link.l1 = "������ � ����, ��� �� ��������� �������� ����� ������� ������� ���� �����.";
			link.l1.go = "PQ8_Mayor_6";
		break;
		case "PQ8_Mayor_6":
			dialog.text = "� �������. �� ��� �������� ��������� ������ �� �����.";
			link.l1 = "� ����� ����. � ��� � ���������� ������� ������ - �������� �� ��� ���-������ ���������...";
			link.l1.go = "PQ8_Mayor_7";
		break;
		case "PQ8_Mayor_7":
			dialog.text = "���� ���� ���-���� ������, �� �� ������� �� ���� ����������. ��� � ���� ���������.";
			link.l1 = "������.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_8_Panama", "11");
			pchar.quest.PQ8_MorganInPanama_1.win_condition.l1 = "location";
			pchar.quest.PQ8_MorganInPanama_1.win_condition.l1.location = "Panama_town";
			pchar.quest.PQ8_MorganInPanama_1.function = "PQ8_MorganInPanama_1";
		break;
		//��������� �������� � ������
		case "PQ8_FackMorgan":
			dialog.text = LinkRandPhrase("������, ����� ������� ���!", "�� ������"+ GetSexPhrase("","�") +", ��� ������ ������?! ��� ������ ��� �����������...", "������ ��� ����� �����, ���� ���������� ������ ���-������. ������ ������ ��� �� ����...");
			link.l1 = LinkRandPhrase("��, � ������"+ GetSexPhrase("","�") +"...", "����!!!", "������� ���� ����!");
			link.l1.go = "exit";
		break;
		//������ ����������� �����
		case "PL_Q8_QFackMorgan":
			dialog.text = "�� ��� ������ �������, �������! ����, ��� ���� ��� �� ���� ���� ������...";
			link.l1 = "��� ���������?";
			link.l1.go = "PL_Q8_QFackMorgan_1";
		break;
		case "PL_Q8_QFackMorgan_1":
			dialog.text = "��!! � ���� ������ ��� �������, ��� �� �� ������� � ��� �������!";
			link.l1 = "������ �� ��������, �� ����.";
			link.l1.go = "PL_Q8_QFackMorgan_2";
		break;
		case "PL_Q8_QFackMorgan_2":
			dialog.text = "��� �������, ����� ������, ������ �� ���� ��� ������! �� �������� ������� � ������ ������� ���� ������� � ����� �����!";
			link.l1 = "�� � ���, ��� ��� ���� ��������. ��� � ���� �������������?";
			link.l1.go = "PL_Q8_QFackMorgan_3";
		break;
		case "PL_Q8_QFackMorgan_3":
			dialog.text = "� ���� - ������, �� ������ ��� ��� �� ��� �������... �� ��� �������� ���������� ����� ��������� � ����� ���������� ������ ������ � ��������, ����� ����� ��� ������� �� ������ ���������� ��������. � � ��� ����� ��� ���������� � ���������� ������� ���� ���������� � ��������� ������ � ����� �����.";
			link.l1 = "���?.. � ������?!";
			link.l1.go = "PL_Q8_QFackMorgan_4";
		break;
		case "PL_Q8_QFackMorgan_4":
			dialog.text = "���� ������ ���� ������ ����� ������ � ��������! � �� ���� � ��� � ������ - ����� ��������� ��� ������ � ������ ��� �����, � ���� �������� ������!";
			link.l1 = "�� ����� ����... �� ����� ������ �� ����� ����!..";
			link.l1.go = "PL_Q8_QFackMorgan_5";
		break;
		case "PL_Q8_QFackMorgan_5":
			dialog.text = "��! ��� ����, �������! ��� ������ ������?";
			link.l1 = "������!! � ������� ����������"+ GetSexPhrase("","�") +", ��� ������ �� ����� �������, ����� ����� ��������, �� ����� ��� ��� ������� ���� ����� � ������ ������ ��� ������ � ��������������!..";
			link.l1.go = "PL_Q8_QFackMorgan_6";
		break;
		case "PL_Q8_QFackMorgan_6":
			dialog.text = "��, ��� �� ������� ��� - ������ ��������� �� ���� �� �����! ����� ��� �������, ��������� �������!\n������, ������� ��� ������ �������, ��� ������ ��� �������. � �� ��� �� �������, �������...";
			link.l1 = "��� ������ - �������?";
			link.l1.go = "PL_Q8_QFackMorgan_7";
		break;
		case "PL_Q8_QFackMorgan_7":
			dialog.text = "�� � ������! ������� ����������� �� ��������� �������� ���������� ��������, �� �� ��������� ��� �� ���������� � ��������. ��������, ��� �� �� ���������!";
			link.l1 = "��� ��� �������, ��� ��� ������, ���� ������� �����...";
			link.l1.go = "PL_Q8_QFackMorgan_8";
		break;
		case "PL_Q8_QFackMorgan_8":
			dialog.text = "�� ��, �� � �������� ���� ���� � ����. �� �����, ��� �� � ���� ������ �����...";
			link.l1 = "�� ��� �� ��� ���������!! ��� ��������� ������, �� ������� ���� ������?";
			link.l1.go = "PL_Q8_QFackMorgan_9";
		break;
		case "PL_Q8_QFackMorgan_9":
			dialog.text = "�� ����� �����. �� �� '�������', �� �� '������ �������'... �� ����� ��, �� ����� ���� ���. �� ����� � ������ �������, � �� � � �����...\n��, ��� ��������! ���, �� ���� �����!";
			link.l1 = "��������!! �� ����� ������� ����� ��� �����. ����� ������� �����, �������� �����, ���� � ��������, � ���� ����� ������� � ���������� ����� � ����� ��������.";
			link.l1.go = "PL_Q8_QFackMorgan_10";
		break;
		case "PL_Q8_QFackMorgan_10":
			dialog.text = "����� ����� �������? ��� ��, ������� ������ ������ � �� ��������. � � ����� ����� � �� ������: "+ GetSexPhrase("�� �� � �������� ������!","��� �������, ��� �� �������... ���... ��, �������.") +" � ���� �� ���������� � ���, ����� ���-�� ������� � ������, ��� ����� �������� ���� � ���! ������ ������ ��� �� ����, �������... �� �����, ������� ��� ��� � ����� ���� ������. ����� � �������, �������, ��� ��� ������� ���...";
			link.l1 = "�� ���, ���. � ��� ����� ������� ������ ���.";
			link.l1.go = "PL_Q8_QFackMorgan_11";
		break;
		case "PL_Q8_QFackMorgan_11":
			chrDisableReloadToLocation = false;	
			LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_houseS1")], true);
			SetTimerFunction("PQ8_openPanama_2", 0, 0, 30);
			pchar.questTemp.piratesLine = "Panama_backToShip";
			AddQuestRecord("Pir_Line_8_Panama", "13");
			Pchar.quest.PL_Q8_backFight_1.win_condition.l1 = "location";
			Pchar.quest.PL_Q8_backFight_1.win_condition.l1.location = "Panama_jungle_04";
			Pchar.quest.PL_Q8_backFight_1.function = "PL_Q8_backFight_1";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload4", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
