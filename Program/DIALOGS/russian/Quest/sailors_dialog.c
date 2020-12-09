// ������� ������ �� ������ ��� ��������� � ����
// ����-������ � ��������� �����
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
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
        case "First time":
			dialog.text = "���������� � ����� ���������. ��� ������ ��� �������";
			Link.l1 = "������.";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  �� ������ -->
		case "On_Deck":
			dialog.text = "���������� � ����� ���������. ��� ������ ��� �������";
			Link.l1 = "������.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// ������ ��������� ���������
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "�����"+ GetSexPhrase("���","��") +", �� ����-�� �����?";
					Link.l1 = "��, ������. ���� � ������ �������� ����� �����?";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "�� ���� �������� ����������� � ��������. �� ������� ����� �� �����.";
					Link.l1 = "������-������";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy. ����� ����, ��������� ����� � ������ � ���� ���� ������
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("���� ��, ���"+ GetSexPhrase("","�") +" � ��� ����"+ GetSexPhrase("��","��") +"... ��, ��� ����"+ GetSexPhrase("��","��") +", �� ��� � ����. ���������� � ����� ����� ��������...",
	                                           "���, �� �� �����, "+ GetSexPhrase("��������","�������") +"! ������ � ��� �� �����... ������� � ��������, �� � ����� ����� ��������.");
				Link.l1 = "����...";
				Link.l1.go = "exit";
			}
			//<-- eddy. ����� ����, ��������� ����� � ������
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "��� ����� �������� ��� � �����.";
			Link.l1 = "�������, ��������.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // �� ���������� �������
		break;
*/		
        //  �� ������ <--
				
		// ugeen --> �������� � �������� �� ���������� "����� ��� ������"
		case "On_MyShip_Deck":
			dialog.text = "�� � ������ �� �� ������, �������! �� � �������� ������ �������� ��� �� ����������, ��� �������� ����� �� �����. �������� �� ������� � �����, ��� ��� �������� ����������, �� ������ ������ ����� � ������� �� ���� ��������������� ������.";
			link.l1 = "�� ��, � ��������� ����� �������� ��������� ��������������.";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// ����� �� ����
				dialog.text = "�������! ������� ����������! ��� �� �� ����� ���� ����� �� ����, � �������� �� ������ ��������� � �������� ���������� � ������ ��������� ��� �������. ��� ���� ���� - " + sti(pchar.questTemp.ReasonToFast.p9) + " ��������...";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// ����� ��������
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "�������! ������� ����������! ��� �� �� ����� ���� ����� �� ����, � �������� �� ������ ��������� � �������� ���������� � ������ ��������� ��� �������. �� ��� � ������ ��������� ���������� �� ����������� �����. ��� ���� ���� - " + sti(pchar.questTemp.ReasonToFast.p9) + " �������� � ������...";
			}		
			link.l1 = "������ ������. �������!";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));			
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // ������� �����
			AddQuestRecord("ReasonToFast", "17");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("��","���"));		
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;
		
		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		// �������� � �������� �� ���������� '�������� ������'
		case "CapComission_OnShipDeck":
			dialog.text = "�������, ��� �������� ������.";
			link.l1 = "����� ��������?";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "�� ����, �������� �� �� ������ ��������.";
			link.l1 = "�� ��� �� �� ����� ��� �����������?!!";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "�� ��-�� ����? �� ����� ����� ��������� ������ �������, ����� �� �����, � ��� ��������� �� �������� ������ � ������... �� ��������, �� ����� ����...";
			link.l1 = "׸��!!! ������ ������������! ���� �� ����� �����, ������ �������� �� ���������� ���������! ����� ������ ����� ��������!..";
			link.l1.go = "CapComission_OnShipDeck3";
		break;
		
		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // ������� �����
			AddQuestRecord("CaptainComission2", "25");	
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));			
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputationABS(pchar, 4);
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();		
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// <-- ugeen
		
		// �������� � �������� �� ��������� � �����
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "�������, ��������, �� ��������� - ������� ������.";
			link.l1 = "��� �� �������? ��� ������?";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "�� ����, ��� ���, " + pchar.GenQuest.Hold_GenQuest.CapName + " ��� ��.";
			link.l1 = "��� ����! ���� �� �� ��������?!";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "�� �� �� ����� ��������, ������� ����� ��������� � ��� �����. �� �������� �� �����, ���� ���� �� ���������, � ���� �������� ������, ��� ��� ������ ���������.";
			link.l1 = "�� ��� � ��� ������ ��������� �����! �������� ����� ������ � ������ ��������� ����� ����. ��� �� ������! ��������� � �����...";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // ������� �����
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);			
			CloseQuestHeader("HoldQuest");	
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();					
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = "�����������, �������. �� ����� ������ ���������� �� ����� ������� ������������ ��...";
			link.l1 = "�����-�����, �������... � ��� � ����� ������� �����, " + pchar.GenQuest.Hold_GenQuest.CapName + " �����. ������ ������� ��������� ��� � ����. �� ��������.";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "���, ������ ��� �� ���������? �� ������ ��� �� ���������?";
			link.l1 = "�� ��������... � ��-����� ��������� ���� ���������. � ����� ��������������! ����� ������� � ������ � ������ ������.";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 ����� � ����� �������� �� ������ ���� ������ -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "�������, �� ������� ��� �� ������� ��������! ����� ���-�� �������... ����� �������, � ������� ����� �����, � ������ �� ����� ����� ����...";
			Link.l1 = "������, � ����� ��� ����. ������ ����� � ������ �� ���... ���� ������ ��� �����-������... � ����� �������� ��������? ��� ����� ������� ������.";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "�� ���������, �� �������, �� ������������� �������� ���. ��� ����� �������� ������...";
			Link.l1 = "������ ������� �������?..";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "���, �������, ������ ������� �����... � ���... �� ����� ����� �� ���� � �������. �� �� �������������, �� �� ������. ��� ���������...";
			Link.l1 = "�� ��� �� ���� ��� ������ �����?! ��������� ���� � ������... ��, ���-�� �� �������� ��� �� ���...";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // ���� �� ������ �����
			
			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // ������ �������������, ��� ����������
			
			chrDisableReloadToLocation = false; // ������� �����
			
			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;
		
		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
					Dialog.text = "�������, ��������� ����� ���-��... ����� ���� ��� �������?";
					Link.l1 = "��... �������� � ������.";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "�������, ���� �� ���������� ����� ��� �������� ����� � ����, �� � �� �� �� ��������. �� ����� ����� �� ����.";
					Link.l1 = "������ � �� ��������... ����"+ GetSexPhrase("��","�") +" ���������.";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "����� �������� ���, � �������?";
					Link.l1 = "����� ����� ������� ����� ���� ��������� ������� �������� ��� � ������ ��������?..";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "����� ���, �������... ��� �� ����� ��������!..";
			Link.l1 = "�� ������� ���, ���� �... �������� � ������.";
			Link.l1.go = "exit";
		break;
		// <-- ����� � ����� �������� �� ������ ���� ������
		
        //  �� ������ <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("���������� � �����������. ��� ������ ��� �������.", "� �� �����. �� ����� ��������� - � ���������� �����.");
			Link.l1 = "������.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("� ������ ������� �����. �������� ���� � �����.",
                                           "�� ������� ��� ��������. ��� �� � ��� ��������.");
			Link.l1 = "����...";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;
		
		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple("������ ����� ���� ������� '���� ��������'... �� ���-�� �����, �� ������.",
                                           "���, ����� �������. ���� ���� ���������� �������...");
			Link.l1 = "������.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
