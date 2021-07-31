// ������ ������ ���� (��������) 03.10.06 boal
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref sld;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Finish_2":
            DoQuestFunctionDelay("Tut_locCamera_2", 0.1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_RemoveCheckMinHP(Pchar); // ������ ��������
			LAi_SetImmortal(pchar, false);
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		break;
		
		case "ChangePIRATES":
            LAi_SetCitizenTypeNoGroup(NPChar);
            LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Node_5";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;
		
		case "ChangePIRATES_Jess":
            LAi_SetCitizenTypeNoGroup(NPChar);
            LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Node_5_Jess";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;
		
		case "Teach_battle_1":
		    LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Teach_6";
			AddDialogExitQuestFunction("Tut_TeachBattle");
			DialogExit();
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LockFightMode(Pchar, false);
			LAi_SetActorTypeNoGroup(Pchar);
			LAi_ActorTurnToCharacter(Pchar, NPChar);
			if (pchar.name == "��������")
			{
				dialog.text = "�������-�� �� ����� �� �����, �������. ����� ����������, � �� �� �� � �� �����, ��� ������.";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - ���������� � ������ ����";
					link.l0.go = "Finish_2";
				}
				link.l1 = "������? ���� ������, ��� ���������? � ������ ��� ����� ����� ������?..";
				link.l1.go = "Node_1_Jess";
			}
			else
			{
				dialog.text = "���, �������, ������ �� ���� �� ���� ����� ������. ��� ���� ����������?";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - ���������� � ������ ����";
					link.l0.go = "Finish_2";
				}
				link.l1 = "��... � ������ �� ���� ���"+ GetSexPhrase("","�") +" �����"+ GetSexPhrase("","�") +"?";
				link.l1.go = "Node_1";
			}
		break;

        case "Node_1":
			dialog.text = "�� �� ����������� ���� �����������, ���� �� �� ����� ��������.";
			link.l1     = "������! ������, ��� �� ������?!";
			link.l1.go  = "Node_2";
		break;
		
		case "Node_1_Jess":
			dialog.text = "��� �� ������ �� �������? �� � ���������, ������ �� �� ����� �������� ����� ��������, ��� ��� ���������� ����� �������� � ����� ������, � �� ��������� ������� �������. ������, ������� �����, ��� �� ����� ��������� - ����� �� ������� ��� �������� ��� ��������.";
			link.l1     = "�������� ������, ��� �� �������� - ������, �� ����� ������.";
			link.l1.go  = "Node_2_Jess";
		break;
		
		case "Node_2":
			dialog.text = "�� �� �� ����������, ������ ��� �����������. �� �������� ��������, �� ���� ����������, ��� ������ � ����������. ������ ��� � �������, - ���� � ���� ������ - ������ ������� �� �����, - ��� �� � �� �������, � ������� ���.";
			link.l1     = "���������� ���� - �, ���� �� ������?";
			link.l1.go  = "Node_3";
		break;
		
		case "Node_2_Jess":
			dialog.text = "��, �� ��� ����� ������������... �������� �� ��� - � �, � �������, - �������� �� ����� ��������, ������ �� ��� �� ���������. ��� ��!.. ��� � ����������, ���� ���� ��� � ����� �� ������ ��� ���� � �������! �� ����������� ������� � ���� ������ ��������, ��� ���� ����� ������. ������ ����� ����������, � � ������ �� ��������, ����� �� ���� �� ���\n��� ����� ����� ����, � �������� �������� - ��� ���� ������ - ����� �����, ��� � ���� ��� �������. ���� �� �������, �� ��� ������ �������� ��� �� �������� ��� ������ ������.";
			link.l1     = "���������! ����� ������� ���� �����... ������ ������ ������... � ��� � ���������? �� ���?";
			link.l1.go  = "Node_3_Jess";
		break;
		
		case "Node_3":
			dialog.text = "�, ���� �� ������, �������, �� ���, ������ � ����� ��� �������������� � ���� �� ������������. ��� �� �� ��� ��� - ���������� ������... � �� � ��������� ������ - ��� �� �� ��"+ GetSexPhrase("","�") +", ����� ��"+ GetSexPhrase("","�") +"! ������, �����, � �������� ��������, � ��� ��������� �������, � ���� �����������, � ���� �� ����� �������� �������. �������, ������� ��� � ���� � �������������, � ����� ��� � �������� �������������. ������ ������ ������ �� ����� ��������, � ������ ���� �� ����� ������...";
			link.l1     = "��� �� ���� �� ����� - ������� �� ��� �� ���� ����?";
			link.l1.go  = "Node_4";
		break;
		
		case "Node_3_Jess":
			dialog.text = "���, ����� ����. ��, ��������... �������� ���, ����� �������� ��������. � ������ �����, ������������, ����� �������. � �� ��� - ��� ���� �� ����� � ������. ��� ����� ����� ������ - �������. ������� ����� ��� ���������, ��������!";
			link.l1     = "�������� ��� � ��������... �� � ������ ��� �� ��������. ��� �� �����... ������� ���, ������, ��� �� ������ ��������, � ����� �� ������.";
			link.l1.go  = "Node_4_Jess";
		break;
		
		case "Node_4":
			dialog.text = "��� ��� �����. �� � ���� ���������� - � �� ��� � ���� �� �������, ��� ������ �����? � ��� ������ ��� ���������� ����������� ��� ������, ���������! ��, - ����� ����, - �� ��� ����������. ������-�� ��� ���� ����������?";
			link.l1     = "������, ��������... ����� �� �� ������ - �� ����� ������������... ���-�� � � ������� ��������, �� � ���� �����. (�������� ������ ���� �����).";
			link.l1.go  = "ChangePIRATES";
			link.l2     = "�� ����� ��������� ���� ��������. ������ ������ ���� ��������, ����� � ��������...";
			link.l2.go  = "Node_5";
		break;
		
		case "Node_4_Jess":
			dialog.text = "��� ��� ����, �������! �� � ��������� ��������� ��� �� ����� �, ��� �����, ���������� �����. ����� � ������� ��������� - �� ��� ������ ������� �����, �� �� �� ���������. �� ������, ��� �� ��� ����������, ���� �� ���� ���� ��������\n�� �� �������� - ��� �� ��� � �� ���� ������. ��� ���� ����������?";
			link.l1     = "��... ��� �������, �������� � �������...(�������� ������ ���� �����).";
			link.l1.go  = "ChangePIRATES_Jess";
			link.l2     = "�� ����� ��� ������. ������� �� ������, ������.";
			link.l2.go  = "Node_5_Jess";
		break;
		
		case "Node_5":
			dialog.text = "��, ��������� ��� ������, � ��, �� ����� ���, ����� ���������� ��������. � ��� �� ������ ������������� �� �������� ��. ��, ������, ��� � ������, � ������ ����� �� ������� �����.";
			link.l1     = "� �� ������, ��� ���������. ��, ����� ���������, � �� �������� ���� - "+ GetSexPhrase("������� ��������","����������") +".";
			link.l1.go  = "Teach_1";
			link.l2     = "�� ��������, � ���� �� � ������� �������� ����, � �� � ������. �����-�� � � ����, � �� ������"+ GetSexPhrase("","�") +" ������.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Node_5_Jess":
			dialog.text = "�� ��� ������, � ����, ��� �� ����� � �������... �� ������� � ������ ��������� �� ��������, ����������� ����� � ��������, ���� ������������ ���� ���� � ������. �� ������� ���� ������� - � ���������� �������������?";
			link.l1     = "������� ����. �����-�� ���������, �� ������ �� � �����������.";
			link.l1.go  = "Teach_1_Jess";
			link.l2     = "���, �� ����. � ������� � ����� �����.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Finish_1":
			if (pchar.name == "��������")
			{
				dialog.text = "�� ������ � ����� " + XI_ConvertString("Colony" + pchar.HeroParam.ToCityId + "Gen") + ". ����� ���-�� �������� ����� ����� ��� ���� ���� ����� � ���������, ���� ��� �������... �� ����, ����� ����� �� ����� �����, � ����� �������... � �� �� ��� �� �������, �������. ���� ������� ��������� � ���� �� �����.";
				link.l1     = "�� ��� �, ������ - � ����� �����! � ��� �� ������� � �� ���������. ���, � �� �����.";
				link.l1.go  = "Finish_2";
				link.l2     = "�� ����� ����� ��������� �������� ������ - ������ �����, ������. ���� ��� ���� �������, ����� ��� ��� � ����� �� �����?";
				link.l2.go  = "Advice_1";
			}
			else
			{
				dialog.text = "�� ������ � ����� ��������� " + XI_ConvertString("Colony" + pchar.HeroParam.ToCityId + "Gen") + ", ������������, �� �������������. �� �� ����������� �� ���������� ���� - ������ ������� ������� ��������, � �� ���� ����� �� ��������. ���, ������������ � �������� ������ �������������. � ����� � ��� �����, ����� �� ����������� �����...";
				link.l1     = "������������. ���, � �� �����... �� �� �������� �� ���, ��� �� �������"+ GetSexPhrase("��","��") +" - �� ���������.";
				link.l1.go  = "Finish_2";
				link.l2     = "���� ��������, ��� � ��� �� �����"+ GetSexPhrase("","�") +" - ������. ������� ����� ������ �� �����.";
				link.l2.go  = "Advice_1";
			}
		break;
		
		case "Advice_1":
			dialog.text = "�� ��� ��, ���... ����� �������� �������, ��������� ������ �� ��������� ���������. � ������, �� ������ �����������! �����, �������, �������� ��������� ������ - ����� �� �� ����� ��� ������, ���� �������� ����������, � ������ ����� ������ ������ �������, ��� ������ ���� - ������ ��������. � �� ����� ������� ������� �������� ������� � ���������� ���� ���.";
			link.l1     = "��� ��� ����� �����?";
			link.l1.go  = "Advice_2";
			link.l2     = "������������. ���, � �� �����.";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_2":
			dialog.text = "����� ��������� � �������, ����� �����, ������ ������� ���� �� ������ � ��������� ����������. ������ �� �����, ������� �������� �����, � ����� �������� � ��������� ������ � ���� ��� ��������� �����.";
			link.l1     = "������.";
			link.l1.go  = "Advice_3";
			link.l2     = "������������. ���, � �� �����.";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_3":
			dialog.text = "������ �� ������� ����� ����� �� �����, � ����� �� �������� ��������. ����� ����� ����� ����� ������ � ���������� �������������� ����� ��� ����.";
			link.l1     = "������.";
			link.l1.go  = "Advice_4";
			link.l2     = "������������. ���, � �� �����.";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_4":
			dialog.text = "���� �� ���-���� ������ ��������, �� ������, ��� �������, ����������� � ����, ��������� �� ����� �� �������� �����, ����� ��� ������ ��������� ����� ������� �� ������ ����� � �������� �������.";
			link.l1     = "������.";
			link.l1.go  = "Advice_5";
			link.l2     = "������������. ���, � �� �����.";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_5":
			dialog.text = "�� ����� ������� ��������� � ���������������� ����� ��� - ��� ������������ ������� �����, ����� � � ������ ��� ��������.";
			link.l1     = "������.";
			link.l1.go  = "Advice_6";
			link.l2     = "������������. ���, � �� �����.";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_6":
			dialog.text = "������� ��������, � ��� ������ ������ ���. ���� ��������� ��� �������, �� �� ������� ������ ����� ��������. � ���� ������ ��������� ���, ��� ������ �������� �� ���-��� ��������� �����. ���� ����� �������� ������� ��� ��� ���������.";
			link.l1     = "������.";
			link.l1.go  = "Advice_7";
			link.l2     = "������������. ���, � �� �����.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_7":
			dialog.text = "��������� - ����� ������������, �� ����� ��������� ���, ��� ��� ����� ����� ����� ��������� ������ � �����-������ ����, ����� ��� ��������. ������������ ���������, ����� ������ ����������, � ������ ����� ������ � ������. � ������� - ���� ������ �������� ��������� � ������, ��� �� � ��� ������ �������, �� ���� ����. ��� ��� ����� ����� ���� ���������!";
			link.l1     = "������.";
			link.l1.go  = "Advice_8";
			link.l2     = "������������. ���, � �� �����.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_8":
			dialog.text = "��������, ��� ����������� ���������� �� ��������� �����. ��������� ���������� ��, ��� � ��� ������ ����� - ������ � ����� � �� �������, ������� ��������� ���� �������� � �����, ����� ���! ��� ��� �������� �� ��������� ����� ����� �����, � ��� ��� ���� - �� ��������� �������. ���������� �������, ������, ���� �� ������� �� ����� � ����� ������ ������� ���� � �� �����. ����� �� ��������� ������ ������������ � �������, ����������� ��� �� ����, � ��� ���� ������� ���� ����. �� ��� ������������� �� ������ ��������� �� ������ ��������.";
			link.l1     = "������.";
			link.l1.go  = "Advice_9";
			link.l2     = "������������. ���, � �� �����.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_9":
			dialog.text = "��� ����� ������� �� ������� ���������� ����, ���� �� � ��� ����, � ������� �� ���� ����� � ����������. ��, � ����� �������� ������ ������������ ���������� �� ��������� ����� - ������ �������� ������������ �������� ��������, � ���� ������ ��� ����� �� ��������. ������, �� ������ ���� �� ������� ������� ���������������. ���� ���������, ����� �������� ���������� ��������� ��������, ���� ���� �� ����� - ����������.";
			link.l1     = "������.";
			link.l1.go  = "Advice_10";
			link.l2     = "������������. ���, � �� �����.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_10":
			dialog.text = "������, ��� �������� ��������� � ������, � ������� �� �� �����.";
			link.l1     = "�������. ��� ���� �� �����.";
			link.l1.go  = "Finish_2";
		break;
		/////   ���� 
		case "Teach_1":
			dialog.text = "�� ��� ��, ������, �������. � ��� ��� ������ ������� ����������, �� � �������. ���� ��� ��������� �����: ������� ����, ����� � ��������� ����. �������� �������� ���� ���: ����, ����������� � ����. ���� ��� �������-��������� �������� ����. �, ������� ��, ��������, ����� ���������� �������� ��������� ������� ��������.";
			link.l1     = "������-������, ����� ����� � ����.";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_1_Jess":
			dialog.text = "�� ��� ��, ������, �������. � ��� ��� ������ ������� ����������, �� � �������. ���� ��� ��������� �����: ������� ����, ����� � ��������� ����. �������� �������� ���� ���: ����, ����������� � ����. ���� ��� �������-��������� �������� ����. �, ������� ��, ��������, ����� ���������� �������� ��������� ������� ��������.";
			link.l1     = "��� ����. ��� ������?";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_2":
			dialog.text = "����� ��������� �������� ������� ������� �������, �� �������� �������� ������� �� �����������. ����� ����� ���������� �� ������, ���������� ����� � � �������. �� ��� ����� � ���� ��������, ���� ���������� ����������, � ��������� - �� �����.";
			link.l1     = "������.";
			link.l1.go  = "Teach_3";
			link.l2     = "��� ����� �������?";
			link.l2.go  = "Teach_2_1";
		break;
		
		case "Teach_2_1":
			dialog.text = "������� - ��� ���������� ������ ��� ��������� � ���������� �������. ��� ��������� �������� ������� ������ �������. ������� �������, � �������� ������� �������� ������, � ��� ����������� ��� ��� ��������� ���������. "+
						  "������������ �������� ������� ������� �� ������� �������� ������� ���������.";
			link.l1     = "������.";
			link.l1.go  = "Teach_3";
		break;
		
		case "Teach_3":
			dialog.text = "�� ����� ������� ��������� ��������� ������� ����������� �����������, ����� ��� ������ ������� �� ���������. ������������� ����� ��� �����, � ��� ����� � ����� ����� ������� - ��� ������. ����� ������� ����������� ��������, ��� ������ ����� �� ����������� ���������. ��������, �� ����������� - ������ ���������� ��� ������.";
			link.l1     = "������.";
			link.l1.go  = "Teach_4";
		break;
		
		case "Teach_4":
			dialog.text = "���� �������� ������� �� ��� ���� - �� ������� �������� ����, �������, ��� �� �������� �����. ���� �� ��������� �� �����������, �� ����� � ��� ������� ��������. ������ � ����� - � ���� ���.";
			link.l1     = "������.";
			link.l1.go  = "Teach_5";
		break;
		
		case "Teach_5":
			dialog.text = "������ � ���� ������, ������� �� ���� �� ������, ������� � �������. ��� ������ ���������� ������ �������. ��������� �������� ����� ��� ������ ���������, ���� ������� ������� ����� ����� �������� ������ ���������� ����������� �� ��� �� ��� ���� ���������.";
			link.l1     = "������.";
			link.l1.go  = "Teach_6";
		break;
		
		case "Teach_6":
			pchar.HeroParam.Teach_battle = 1;
			Tut_RestoreState();
			dialog.text = "�� ���, �������� � ��������? ��������� ������� ��������. ������ ����� ��-����������, �� �� �� ������. ����� � ��� ����� ����������, ������� ��� ����� ������������, �� ������ �� �� ����� ���������� - ����� �������������.";
			link.l1     = "�����, ������ �� ���!";
			link.l1.go  = "Teach_battle_1";
			link.l2     = "���, �������. � ��� ��� �����"+ GetSexPhrase("","�") +".";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_lose":
			Tut_RestoreState();
			dialog.text = LinkRandPhrase("��-�... ���-�� ������ �� ��������. ������ ������������, ������ ���������� � ���������. ��������� �� ������� - �� ���� ���� �� �������, ����������� ����, ����������� ��� ������.",
			                             "�� ������� ���� �������, �������������� ���� ���������� ������� ��� ���������. �� ������ ���������, ���� ���������� �� ���� - ���������� ��� �������, �� ��� � ���� �������.",
										 "���� ������� �������� - �������� ��� ������������, � ���������� ���������� ������. ������, ������ ���� ��� ������ �� ������, �� ����� ���������� ��������. � �� ���� ��������� �� �� ���� ������, �� ���������� �� ��� �������� ����� ������ �������� - ��� �� �� ������ ��� ������ �� ���� ��������, �� � ���� ��� �������� ����.") +
										 " �� ���, ��� ���?";
			if (sti(pchar.rank) < 3) // ���� �� �������� �� �����
			{
				link.l1     = "��� ���!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2     = "���, ����������. � ��� �����"+ GetSexPhrase("","�") +".";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win":
			pchar.HeroParam.Teach_battle = 2;
			Tut_RestoreState();
			dialog.text = "������. �������! ������, � ������ ������, �� � ������ ����� ���� �������� ����� ����, ����� ��� ����� �� ��� ����� ��������. " +
						  "�� ���, �������� ������. ������� ������ ����� �����������?";
			link.l1     = "��� ��, �����. ��, �������! ������ ���� ����� � ����� �� ������!";
			link.l1.go  = "Teach_battle_1";
			link.l2     = "���, �������. � ���������� "+ GetSexPhrase("��������������","���������������") +".";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_2":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			if (pchar.name == "��������")
			{
				dialog.text = "���������, �������! ����� �������� �� ������ ���������, ��� �� �� ������� ��� ������. � ��������� �����: ��� ������ �� �������� ������� ������ ����, ��� ������ ������ ���� ������. ������ ������������ ���������� �������� ����� ������ - ���� ������� ��� ������.";
			}
			else
			{
				dialog.text = "��, � ������ � ��� ��� � ������� - �� �������� �� ������ �������. � ��������� �����: ��� ������ �� �������� ������� ������ ����, ��� ������ ������ ���� ������. ������ ���� �������� �� ���� ����� - ���� ������� ��� �������.";
			}
			link.l1     = "�������!";
			link.l1.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_3":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			dialog.text = "��� ��, �������. ������ ���������� �� �������, �� ���� - �� ����. ��� �������� �����. ����� ����� ���� ������ ��� ��������� ��������. ��������?";
   			if (sti(pchar.rank) < 3) // ���� �� �������� �� �����
			{
				link.l1     = "��� ���!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2     = "���, � ��� ��� �����"+ GetSexPhrase("","�") +".";
			link.l2.go  = "Finish_1";
		break;
		
		//�������������� ������
		case "Alt_start":
			EndQuestMovie();
			LAi_LockFightMode(Pchar, false);
			LAi_SetActorTypeNoGroup(Pchar);
			LAi_ActorTurnToCharacter(Pchar, NPChar);
			dialog.text = "�, �����-�� ��� ���������! � �� �������, ��� �� "+ GetSexPhrase("����!","������!");
			link.l = "������ ����� ����������, �� ��� ���?";
			link.l.go = "Alt_start_2";
		break;
		
		case "Alt_start_2":
			if (pchar.sex != woman) PlaySound("Interface\Welcome_Fucking_Event2_"+rand(2)+".wav");
			else PlaySound("Interface\Welcome_Fucking_Event1_"+rand(2)+".wav");
			dialog.text = "����� ���������� �� ������, " + GetSexPhrase("����� ������!","�������� �����!")+" � ��� �? �� ������ ��� ����! ���� ���� �.";
			link.l = "������ �� �����... ����� ��� ������?";
			link.l.go = "Alt_start_3";
		break;
		
		case "Alt_start_3":
			dialog.text = "�������, � "+GetSexPhrase("����� �� �������","����� �� �����")+" � �������� �� ���� ������... ������� ����� � ����, ������!";
			link.l = "(�������� ������ ���� �����)";
			link.l.go = "ChangePIRATES_Alt";
		break;
		
		case "ChangePIRATES_Alt":
            LAi_SetCitizenTypeNoGroup(NPChar);
            LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Alt_start_4";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;
		
		case "Alt_start_4":
			dialog.text = "�������! � ������ ���������� � ����, ����������!";
			link.l = "(��������)�� �� � �����!";
			link.l.go = "Finish_2";
		break;
		
		case "Alt_start2":
			EndQuestMovie();
			LAi_LockFightMode(Pchar, false);
			LAi_SetActorTypeNoGroup(Pchar);
			LAi_ActorTurnToCharacter(Pchar, NPChar);
			dialog.text = "����������� ����, �����! ���� ������ '������� ����������', ������ � ����������.";
			link.l = "��� ����� ����������?! ����� ������? ��� �� �����?";
			link.l.go = "Alt_start2_2";
		break;
		
		case "Alt_start2_2":
			dialog.text = "�������... ��������... ��� ������! ������. �������� ����, �������� �� ���������! ����������!";
			link.l = "����! ��� ��� ��������? � ��� �� ��������? ������������� PIRATES?";
			link.l.go = "Alt_start2_3";
		break;
		
		case "Alt_start2_3":
			dialog.text = "�� �����, �����. ��� �� �� �����?";
			link.l = "(�������� ������ ���� �����)";
			link.l.go = "ChangePIRATES_Alt2";
		break;
		
		case "ChangePIRATES_Alt2":
            LAi_SetCitizenTypeNoGroup(NPChar);
            LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Alt_start2_4";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;
		
		case "Alt_start2_4":
			dialog.text = "���������"+GetSexPhrase("��","���")+"? ��, ����������� � ����, ������� � ����. ����� ��������!";
			link.l = "������ �� �������. �� �����...";
			link.l.go = "Finish_2";
		break;
	}
}
