
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;
	ref shTo;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "����������� ����, "+ GetSexPhrase("����","������") +"!";
			link.l1 = "���"+ GetSexPhrase("��","��") +" � ���� "+ GetSexPhrase("����","������") +"? �� �� ���� ����������-������. � ��� ��� �� � ����� ���������?";
			link.l1.go = "Meeting_1";
			NextDiag.TempNode = "First time";
		break;

        case "Meeting_1":
			dialog.text = "��� ������? �� ����� �������, � �����, ��� ��� ���� '����� �������'. ������ - ������ � �������, � ������ ��, ��� ����� �����, �����.";
			link.l1 = "�� ��, �� ������� �����, ������ ��� ���� ���� ��� �� �������� ����������, � ��� ��� � ���. ����� ��� ����� ������ � ���������?";
			link.l1.go = "Meeting_2";
		break;
		
		case "Meeting_2":
			dialog.text = "���� �� �������. � ��� ������ ������� ����� � ����� ������� ������� �������. � ������ ���, ���� ���� �� ������ ���� � �� ������� � ����.";
			link.l1 = "� �����, ��������� ��������, ���� ���. �� �������� ������?";
			link.l1.go = "Meeting_3";
		break;
		
		case "Meeting_3":
			dialog.text = "������ � ��������.";
			link.l1 = "�������� ��� ���������? � ���� ����?";
			link.l1.go = "Meeting_4";
		break;
		
		case "Meeting_4":
			dialog.text = "���, ������ ���, � �����.";
			link.l1 = "������� �� ����, ����� ��������. ������.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "AfterMeet";
			ReOpenQuestHeader("GhostShipQuest");
        	AddQuestRecord("GhostShipQuest", "4");
		break;
		
		case "AfterMeet":
			dialog.text = "����� "+ GetSexPhrase("����","������") +" ��������. ���� ��� �������?";
			link.l1 = "���, ��� �� � ��� ��������.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "AfterMeet";
			bOk = (sti(PChar.GenQuest.GhostShip.KillMe) > 0) || (sti(PChar.GenQuest.GhostShip.DeadByMe) > 0);
			if (bOk && !CheckAttribute(pchar , "GenQuest.GhostShip.NeedCoins"))
            {
    			Link.l3 = "��� �� ������ � �������-��������?";
    			Link.l3.go = "GhostCapt";
			}
			if (GetCharacterItem(Pchar, "Coins") >= 666 && CheckAttribute(pchar , "GenQuest.GhostShip.NeedCoins"))
			{
                Link.l4 = "� ������"+ GetSexPhrase("","��") +" ���� ���������.";
    			Link.l4.go = "quest_coin_2";
			}
		break;
		
		// �������
		case "GhostCapt":
			NextDiag.TempNode = "AfterMeet";
			dialog.Text = "������� �������? ������� �����-����� ������, ������ ���� �������, ����� ����� ������� � ������ �������.";
			Link.l1 = "����� � ��� �� ��������?";
			Link.l1.go = "GhostCapt_1";
		break;
		
		case "GhostCapt_1":
			dialog.Text = "������, � �����, ���� ��� �������� �������. ��� ���� ��� 40 ��� �����, ���� � ��������� � ����. ������� ������ ������� �����, ����� ��� ���� �����, ���������� ���, �������� ��������� ������ ������.";
			Link.l1 = "��... ���������� ����, ��, � �������-������� ��� ������?";
			Link.l1.go = "GhostCapt_2";
		break;
		
		case "GhostCapt_2":
			dialog.Text = "� ��� ��������� ���. �� �� �������? ��� ����� ���������� ����� �������� � ���� ����������, ������� ���������� �������� � ������� ������ ������, ������. ����� ����� ������ ������ ������� �������� � �������.";
			Link.l1 = "��������� �������� ��� ���-�� ������. ��� ��� ������ ���������� � ����������?";
			Link.l1.go = "GhostCapt_3";
		break;
		
		case "GhostCapt_3":
			dialog.Text = "��� � ��������, ������ ��������. ���������� ��� �� ���, ���������� ��������� �������� �������� ��, ��� ����� ��������, ���� �� �������� ��� �������. � ������ ����� � �������� � �������� ������� ��� ������, ������ �� �����, ��� ���������, � ������.";
			Link.l1 = "��-�����, �������� �� ����� ��������� ������ ������ ����. �������� �� �� ������ ����� - � ���� ���. ��� ����� � ��� ����������?";
			Link.l1.go = "GhostCapt_4";
		break;
		
		case "GhostCapt_4":
			dialog.Text = "�������� ����, ��� ��� ����� ��� ���������, � ������� ���, ��� ����, �������� ������ ����, ����� 666 ������ �������� � �� �������. ����� ��������� ��������� ���������� ��������.";
			Link.l1 = "������, ��� ���� � � �������!";
			Link.l1.go = "Exit";
			AddQuestRecord("GhostShipQuest", "5");
			PChar.GenQuest.GhostShip.NeedCoins = true;
		break;
		
		case "quest_coin_2":
            dialog.Text = "������������. �� ������ ���� ���! ������ ����� ��. ���� �������� ������ ��� ��� ��������� ������� � ������� ��� ��� ����� ����. �� ���� �� ���� �����. ������ ��� ����� ������ ������, ��� ������� ������.";
			Link.l1 = "������. ������� ��.";
			Link.l1.go = "Exit";
			TakeNItems(pchar, "Coins", -666);
			AddQuestRecord("GhostShipQuest", "6");
			AddQuestUserData("GhostShipQuest", "sSex", GetSexPhrase("","�"));
			PChar.GenQuest.GhostShip.LastBattle = true;
			NPChar.location = "none";
			NPChar.LifeDay = 0;
            NextDiag.TempNode = "temp_coins";
		break;
		
		case "temp_coins":
            dialog.Text = "�������, ����.";
			Link.l1 = "�������, ��� �����, ��� �� ������.";
			Link.l1.go = "Exit";
			NextDiag.TempNode = "temp_coins";
		break;
		
		case "GhostCapt_Prize":
			dialog.text = "����������� ����, " + GetSexPhrase("�����","����") + "! ��������� � ����� ������ �� ���������� ����� �������� � ������ ��������."
			link.l1 = "�� ���?! � ������ ����� ������?";
			link.l1.go = "GhostCapt_Prize1";
		break;
		
		case "GhostCapt_Prize1":
			dialog.text = "��... ��������, ���� �� ���, ��� ����� ���� �����, ������ �� ������ ������� ����� ������...";
			link.l1 = "��� �� � ���� ����������� ������� '�������� ���������' ����� �����?!";
			link.l1.go = "GhostCapt_Prize2";
		break;
		
		case "GhostCapt_Prize2":
			dialog.text = "��-��! ���, "+ GetSexPhrase("�����","����") +", � ��� ������ �������, ������ - ��, ��� �� ���� ��������...\n " +
				"��, �� �����, ����� � ���� - ��� ��� �� �� �������"+ GetSexPhrase("��","���") +" ����� ��������? �� ��� �������"+ GetSexPhrase("��","���") +" �������� � �� ������� �����, ��� ��������"+ GetSexPhrase("","�") +" � ����� ���������, ��-��... " + 
				"�����, � �� � ����� - ������ � ��� �� ���������, ������ ����� �� ����� �����. ����, �������, ��� ���� ������� �������, ���� �� �� �� ���� ��� ���������� - ��������"+ GetSexPhrase("��","���") +" �� �� ������, ��� �������� �� ����������, ��-��-��... " + 
				"� ��� ������ �������"+ GetSexPhrase("�","��") +" �������� ���� �������. � � �� � ������������� ���� ���� � ������� - ������ ����������. �� �������?";
			link.l1 = "��� ��, �� ��� ���� � ��� ������"+ GetSexPhrase("��","���") +", ���� ����� ��� ����������� �� ��� ����. � ���� ����� ��� ��� �� �����.";	
			link.l1.go = "GhostCapt_Prize3";
		break;
		
		case "GhostCapt_Prize3":
			dialog.text = "��, ��� ����� ���� ������ - ����... ����. �, ������� - � ���� ���� ������� �������, ��-��-��... " + 
				"��, ���� �� �� �� ���� ��� ����� ����������... � ���� ��� �� �� ����� ������� ������? ��� ��� � ���, ������ ���������� ������� ������� �������? "+ GetSexPhrase("����� ������ � ��������� �������, ������������","����� ������ � ��������� �������, ������������") +" ���������� � ����� �������-���������, �����"+ GetSexPhrase("��","���") +" ��������� ������ ������ �� ��� ����������! ������, � ��� ���� ��������?";
			link.l1 = "���? ������ '���������' ���������� ������?";	
			link.l1.go = "GhostCapt_Prize4";
		break;
		
		case "GhostCapt_Prize4":
			dialog.text = "��-��-��! �� �� � ���"+ GetSexPhrase("","�") +" ��� �� �������, �� �� ����� �� ����... ��� �� - ��� ��� �����... � �, � �������� ������� �� ������, ���� �������� ������� �������������� ������ �����. �������, ��� ���������.";
			link.l1 = "��� ���� ������� ��� ��������. ��� �� ����� �������, ��� �������� ������.";
			link.l1.go = "GhostCapt_upgrade1";
			link.l2 = "������������ � ������� - ����� ������. � ��� �� ������ ��������� ����� ���������� �����.";
			link.l2.go = "GhostCapt_upgrade2";
			link.l3 = "�� ���, ��� �������� � ��������� ��� ������� ������� ������������. ��� ������� ���� � ��������� ��� �������� ��� ������� �����, ��� ���� �������.";
			link.l3.go = "GhostCapt_upgrade3";
			link.l4 = "���������, �� ��� �������� ���� ������ ����������! ������� �� �� ������ �������� '���������'.";
			link.l4.go = "GhostCapt_noupgrade";
		break;
		
		case "GhostCapt_upgrade1":
			dialog.text = "��, ��� ���������, �������� - ��� ��������.\n�����, ���� ���. � � ��� � ���� ���������. �����, ������ ��, ��������� ��� ��� � ����� ��������� ����������... � ���... ���� ������ �� �������� �����, ����� ���, � ��������� ������ ������� ������ �������� - ������� ������...";
			link.l1 = "��� ��� � �������, ��� ������ ���� �� ��������� �������� '�������� ���������', ������� ����� ������?";
			link.l1.go = "GhostCapt_Prize5";	
			shTo = &RealShips[sti(pchar.Ship.Type)];
			shTo.Tuning.GhostShip = true;
			GetBaseShipParam_ToUpgrade(shTo, "SpeedRate");
		break;

		case "GhostCapt_upgrade2":
			dialog.text = "��, ��� ���������, ������������ - ��� ������������.\n�����, ���� ���. � � ��� � ���� ���������. �����, ������ ��, ��������� ��� ��� � ����� ��������� ����������... � ���... ���� ������ �� �������� �����, ����� ���, � ��������� ������ ������� ������ �������� - ������� ������...";
			link.l1 = "��� ��� � �������, ��� ������ ���� �� ��������� �������� '�������� ���������', ������� ����� ������?";
			link.l1.go = "GhostCapt_Prize5";				
			shTo = &RealShips[sti(pchar.Ship.Type)];			
			shTo.Tuning.GhostShip = true;
			GetBaseShipParam_ToUpgrade(shTo, "TurnRate");
		break;		
		
		case "GhostCapt_upgrade3":
			dialog.text = "��, ��� ���������, ��������� - ��� ���������.\n�����, ���� ���. � � ��� � ���� ���������. �����, ������ ��, ��������� ��� ��� � ����� ��������� ����������... � ���... ���� ������ �� �������� �����, ����� ���, � ��������� ������ ������� ������ �������� - ������� ������...";
			link.l1 = "��� ��� � �������, ��� ������ ���� �� ��������� �������� '�������� ���������', ������� ����� ������?";
			link.l1.go = "GhostCapt_Prize5";					
			shTo = &RealShips[sti(pchar.Ship.Type)];
			shTo.Tuning.GhostShip = true;
			GetBaseShipParam_ToUpgrade(shTo, "WindAgainstSpeed");
		break;		
		
		case "GhostCapt_noupgrade":
			dialog.text = "��� ���"+ GetSexPhrase("��","��") +"! ����������"+ GetSexPhrase("��","���") +". ������ �� - ������� ����, "+ GetSexPhrase("�������","��������") +". � ��� ����� ���������-�� ������ ���������, � ������ ��� ����� �������� �� ��� ��������!..\n�����, ���� ���. � � ��� � ���� ���������. �����, ������ ��, ��������� ��� ��� � ����� ��������� ����������... "+
				"� ���... ���� ������ �� �������� �����, ����� ���, � ��������� ������ ������� ������ �������� - ������� ������...";
			link.l1 = "��� ��� � �������, ��� ������ ���� �� ��������� �������� '�������� ���������', ������� ���-���-������?";	
			link.l1.go = "GhostCapt_Prize5";
		break;
		
		case "GhostCapt_Prize5":
			dialog.text = "��, �������������... �����, �� ����� ������... ���� ������� �������, �� � ��� ������� ��������... ������... �� �� ��������� ��� ������ - � ������ ��� �� �����...";
			link.l1 = "���" + GetSexPhrase("","�") + " ���"+ GetSexPhrase("","�") +" ���������� � ����������� ���������.";
			link.l1.go = "GhostCapt_PrizeExit";
		break;
		
		case "GhostCapt_PrizeExit":
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "GhostShipCapInCabinDied", -1);
			LAi_LockFightMode(pchar, false);	
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true;
			DialogExit();
			AddDialogExitQuest("CanEnterToMap"); 
		break;
		
		case "GhostCapt_LastDialog":
			dialog.text = "�-�, " + GetSexPhrase("������ ��������","������ ��������") + "! � ���� � ���� ���� - ����, ��� ������ ��������...";
			link.l1 = " � " + GetSexPhrase("������","������") + " ���������� ���� � ����� ����� �� ���������. ��� ����� ����� - ���� �� �����, ����� ����� � ������� �������� ����� �����.";
			link.l1.go = "GhostCapt_LastDialog1";
		break;
		
		case "GhostCapt_LastDialog1":
			dialog.text = "����, ����... ����� �������, ��� ��, ������ ������ ����������. ��� �����-�� ����� ���... " + 
				"������ �� ����� ���������� ���� ��������"+ GetSexPhrase("��","������") +". � ������ ����, ��� ��� ���� ������ ��������, � ������������ � ��������������, ����� ����������, � �� ���������. ������� � �� �����, ��� � ������ ��� ������!";
			link.l1 = "� � ����� �����"+ GetSexPhrase("","�") + ". �� � �������� ���� ��� ������ �� �����������.";	
			link.l1.go = "GhostCapt_LastDialog2";
		break;
		
		case "GhostCapt_LastDialog2":
			dialog.text = "��� ����� ���� ������, � �� "+ GetSexPhrase("''������ ����������''","''������ ����������''") + " - ���, �����������"+ GetSexPhrase("","����") + ". ������ ����� ���� ��������� �������-�������� ����� ��� ���������. ���� � ��� �������, � ���� �������� ���� �������, ��� ��� ���������� �������� ����... ����... ���� ��������, �� �������������� �� �����...";
			link.l1 = "�������� � ���������� ���, ������ ������! �� ������� ����� ���� ������� ����...";
			link.l1.go = "GhostCapt_LastDialog3";
		break;
		
		case "GhostCapt_LastDialog3":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;	
	}
}

void GetBaseShipParam_ToUpgrade(ref shTo, string param)
{
	string sAttr = "Bonus_"+param;
	int iRealShipType = sti(shTo.basetype);
	string sParam =	GetBaseShipParamFromType(iRealShipType, param);
	float paramValue = 1.1 * frandSmall(stf(sParam)/5.0);
	if(CheckAttribute(shTo, sAttr))
	{
		shTo.(param) = stf(shTo.(param)) - stf(shTo.(sAttr));
		shTo.(sAttr) = stf(shTo.(sAttr)) + paramValue; 
		shTo.(param) = stf(shTo.(param)) + stf(shTo.(sAttr));
	}
	else
	{
		shTo.(sAttr) = paramValue; 
		shTo.(param) = stf(shTo.(param)) + stf(shTo.(sAttr));
	}	
}