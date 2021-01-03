// BOAL ����� ������ ������� � ���������� 21/06/06
													  
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    sld;
	string attr, attrLoc;
	int    iTemp, iTax, iFortValue;
	
	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("���, �������, �� ����� ��� �������� ��������� ��������. ������ ���� �� ����� ���� � ���� � �������!", "����������� � ���� ����������� �� �������? ��� ��, � ������ ���, ���...");
				link.l1 = RandPhraseSimple("�� ��� ������...", "�� � � �� "+ GetSexPhrase("���������","����������") +" ���� ��������."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "������ �� �����, �������?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "������? � �� ��� �� �����?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "���, � ���� ������ ��������.";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "�������, ��� �� ��������! ������� ������, ���� ��� �� ��������!";
			link.l1 = LinkRandPhrase("������.", "�����.", "�� ���������, ��� ������...");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// ������ ������ -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "������� �� ����� ������ � ����!";
				link.l2 = "��... � ���� ���"+ GetSexPhrase("","�") +".";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "������ � �����, �������, � ���������� �� ����. �� �������� ������������ - � ����� �� ��������.";
				Link.l1 = "������. ��������� - �������� ������ ������!";
				Link.l1.go = "Exit";
				break;
			}
			// ������ ������ <--
   			dialog.text = "��� �� ������, �������?";
			// ������ ���������� �� �������.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "� ���� ���� ��� ���� ��������� ��������.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			if (isOfficer(Npchar)) // �������� ��� �������, ��� �������� ���
			{
	            Link.l2 = "������ ��� ������!";
	            Link.l2.go = "stay_follow";
            }

			//aw013 --> ���� �� ��������� 
			if (!CheckAttribute(NPChar, "OfficerWantToGo.DontGo")) 
			{ 
				Link.l3 = "� ���� � ���� �����������."; 
				Link.l3.go = "contract"; 
			} 
			//aw013 <-- ���� �� ���������
           		// boal ����� � �������
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "��� ��� ������ ����� � �������, " + GetStrSmallRegister(XI_ConvertString("treasurer")) + ".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. ����������� ������
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "� ����, �����, �� ����� ������� � �������, �� ������� ������.";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "������, �������� ������ � �������� �� �����.";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			Link.l4 = "������, � ����� �� �������� � ����� �������.";
			Link.l4.go = "AsYouWish";
			
			
            // �� ��� ������� ��������� ����� �� ��� ���������  -->
            if (IsEntity(loadedLocation))
            {
                if (CheckAttribute(loadedLocation, "fastreload"))
                {
                    iTemp = FindColony(loadedLocation.fastreload);
                    if (iTemp != -1)
                    {
                        sld = GetColonyByIndex(iTemp);
                        if (sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
                        {
                            NPChar.ColonyIdx = iTemp;
							Link.l7 = "� �������� ���� ����������� ����� ������!";
                            Link.l7.go = "Gover_Hire";
                        }
                    }
                }
            }
            Link.l9 = "������. ������.";
            Link.l9.go = "Exit";
        break;

		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "�������, ����� ������?! ����� ������� ������� ���-������ ���������!";
				Link.l1 = "��, �� ����.";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "����� ���������, "+ GetSexPhrase("��������","�������") +" �������!";
			Link.l1 = "������.";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // ��������� ����������� �������
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "����� ���������, "+ GetSexPhrase("��������","�������") +" �������.";
			Link.l1 = "������.";
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;

        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.CanTakeMushket = true;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		//aw013 --> ���� �� ��������� 
		case "contract": 
			dialog.text = "������ ��� �����������, �������."; 
			Link.l1 = "�� ������� ������ � ��������� ��� ���������. ���� ���������� ���� ����� �� ��� �� ������ �� ���������."; 
			Link.l1.go = "contract2"; 
		break; 

		case "contract2": 
			dialog.text = "������� �� ������ �����, �������. � ����� ������� �� ���������?"; 
			Link.l1 = "������� ������������ ������. ���������� �������, "+ GetSexPhrase("���","����") +" ���������. ���� ��������� 10 ���. �������� ������ �� ��������� �����, � ���� ��� ����� ���������� ��� �����, ���������� ������."; 
			Link.l1.go = "contract3"; 
		break; 

		case "contract3":
			NPChar.contractMoney = makeint(sti(NPChar.rank)*MOD_SKILL_ENEMY_RATE*1000);
			dialog.text = "���������� �����������, ������ �� �������. �� ��������� �������� ���������� �������. � ��� ������ ��������� ��������� ��� ����������� �������?"; 
			if (sti(Pchar.money) >= sti(NPChar.contractMoney))
			{ 
				Link.l1 = "������ ������ �� ����, " + sti(NPChar.contractMoney) + " ������� ����� ������ �� ���� ���� �������?";
				Link.l1.go = "contract4";
			} 
			Link.l2 = "������ ������ �� ����, �� ����� �������� � ����� ��������� �����."; 
			Link.l2.go = "Exit"; 
		break;
 
		case "contract4": 
			dialog.text = "������, �������. � ��������."; 
			AddMoneyToCharacter(Pchar, -sti(NPChar.contractMoney));
			SetCharacterPerk(NPChar, "EnergyPlus"); 
			SetCharacterPerk(NPChar, "HPPlus"); 
			NPChar.OfficerWantToGo.DontGo = true; 
			NPChar.loyality = MAX_LOYALITY; 
			NPChar.Reputation = 50; 
			DeleteAttribute(NPChar, "alignment"); 
			// DeleteAttribute(NPChar, "contractMoney");//Mett: ��� ����� ������������� �� �������, �� ����� ������������ ��� ����������� ����� ���������
			Link.l1 = "��� � �������! ������������"; 
			Link.l1.go = "Exit"; 
		break; 
		//aw013 <-- ���� �� ���������
		// boal 29.05.04 ������ ����� ������� -->
        case "WantToGo":
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("�������, ��� ����� ����... � �����, ����� ��������. ��� �� ����� �������� ����, ����� ������� � ����� ������ �� ������� �������, � � �� ����� ���� �� ������. ��� �� �������� ��� � ���� ������ ����� ������.","�������, ����� ��� ��������, � �� � ������� ��� �� ����� ���� �������, � ������ ������ � �� �����. ���� ������� ������ �����, ����� �������, �� �� ��� ������� ������� ����������.","�������, ������� ������ ���, �������, ������� - ��������� � ����������� ������, �� ���� � � ���� ��������. ������� ����� � ����� ������, ������� ������ �� ����� �������. �� �� ��������� ����."), LinkRandPhrase("�������, � ������� ���������, �� ��� ������ � ������� �� ������������ ��� ��������, ��� ������ �����. ���� ��������� ����� �������� ������� ������. �������, ��� ����� �� ������, ������� ����� ��������.","�������, ��� ��� �������� �� ������ ������������. �����-�� ���� ����� � ����� ����� ������������. ��������� �� ������� ����� - ����� ��������.","�������, ��� ��� ����� � ����� ����������. � ���� ����� ������ ����� ������� �� ������ �����������. ����� �������� - ����� ��� ����� ������ ����������."), LinkRandPhrase("�������, ���� �� ���� ��� � ���� �������. ������� ������� - �������������. ���������, ���� ������, ����� �����-������ �� ������� - �� ���� ������.","�������, ������ ������ ��� ���� ������������ �� ����������� ����� �����. ������� ���� ������ �����, ����� ������ ��������� ���� ���������, ����� ����� ��������... � ��������������� �� ����� ��� � ��������� - �� ������ ������... ����� ��������, ������ ���������.","�������, ������ ���� ���� - ��� ���, �� � �������� �������� ����� �� ���. ��� ������� � �� ���� ���� ��������, ��� ����� �� ������ ������? ����� �������� - ��������� �� ���� ������ ����� �����������."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("��, ���� ��� ����������... �� �������� �� ����� - ���, ���� �����.","�� ��� �, ������� �������. ���� ��� ������ �� �������������. ���... �� �� ��������, ���� ������"+ GetSexPhrase("","�") +" �����.","�� ��� �� �����! ��� � ������� �������� � ����� ������������ ������!.. ���, ����� �� ���� ������ �����..."), LinkRandPhrase("� ������ �������. ����-�� �� �� �������������... �� �� �����, ������ �� ������ � � ���� �� ��������"+ GetSexPhrase("","�") +", ��� ��� ����� � ������ ��������.","��� �� �� ����"+ GetSexPhrase("","�") +" �� ���� ��� ��������! ������� ������� ��� � ���... ������ ���"+ GetSexPhrase("","��") +" �����������, ������ �� ����. ����� �� ����� ���������������� � �����... ������� ���� � �� ��������� ��� ������ �� �����.","��� ���� ��������� - ���������� �� �����... ���� ��� ���� ����� ����� �� �������."));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("��-�, ��� ������, ��� �� ����������... � � ���� �� ���� �����������... ��, ��� ������� ������� - ����� ������������. ��� ���� "+sti(NPChar.rank)*250+" ������� �� ������ ������. � �� ����� ���, ���� ����� ������.", "�� ��� �, � ��� �� ����� � ������ �� �����. ��� ����� - ���. �� ����� "+sti(NPChar.rank)*250+" ������� �� �������. ��� ������ ����������.", "����... ���� ��� ������ ��� ������ ���� ���������. ��������� ���� "+sti(NPChar.rank)*250+" ������� �� ������������ ������ �����. �� �������� �������, ������� ������ ��� �� ����� - �� ��� ����� ���� ���������..."); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("���, ������, ���. � �� ���� ���������, ��� ������ ���� ���� ��� ����, ��� ��� � �����? �� ���� ������ � ���� ��������� - ���� �� ����� � �� �����.", "��� ��� �������! � ����� ����� ������� ������������� �������. ��� ��� � ������ ����� ���� ������. ����� ����� �����, � ���"+ GetSexPhrase("","�") +" �������� ���� ��������.", "������� ��������. � ���� ������ ������� �� �����. �� ���� �, �� ������ ������� �������, �������� ��������������. �����, ���� � ���"+ GetSexPhrase("","�") +" �� ����� �������.");																																
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "������� ���, �������! ����� ����������� ��������. � ���� ��� �������� ���-��� �� ����� �����, ����� ������� �� �������?";
			Link.l1 = "�� �������... ������ ����� ������� ������ �� ��� ��������...";
			Link.l1.go = "Get_out_�2_chang";
			Link.l2 = "�� �����. ������ ���� � ������ � ������ ��� ���� �������...";
			Link.l2.go = "WantToGo_free";
		break;
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("�� ��� �� ���? �����������, � ��� �� ����� ���������. � � �� �� �� ��� � ������ ������ ���� ������!", "�������, ������� � �� �� ��� ������� �� �������� ����� �������������� ������ ���� ������?");
			Link.l1 = LinkRandPhrase("����, ��� ������ ���� �� ��������. ��� ������ ���������� ���������? ����� ���� ������ ���������� - � �������� � ����� ������ ������������, � �������� ���������...", "�����, ������ �������� ��-�������. �� ����� ����� �� �� ����� ��������?", "��� �� ����. � ��� ������ ������������� ��������� �������?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(	
				RandPhraseSimple("�-� ���, ��� �� ����������... ���� �� �������� ����� � �������, ����� ���� ������ ���� ������ ���������... �� ��� ������ ������ �� ���� ����� ����� - ��... ������ � ������ ���� �...", "��, ��� ��������� ���������. ������, ��� �� �������, ��� � ���� ���"+ GetSexPhrase("��","��") +" - � ������� ������� ��� ����� � �������. �� ���� ���� �������� ������ ������ ���������� - ��� ����� � ��� ������������, � ���� �� - '������ ���� ������'."),
				LinkRandPhrase("���� �� � ���� �� ������, ������� ���� ��������� �. ������ ��������� � ����� ������������, ���� �� ������ ������������ ��������� �� ���� ���������!", "��. ��� ��������� ���������. �� �� ��� �� ��������� ���� ���������� ���� �����. ������� ���� ������ � ������ �����������, ��� ������� �������.", "�������...� �����-�� �������� ������� �����. ����� ������ ������: '���� ��� �������� ������... �� ����� ������� �� ��������� ������ � ������ ������, ������ ����, ����� ������ � ������.' �� ��� ���� ����� �������?"));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("��, ��� ������ ����. "+sti(NPChar.rank)*500+" ������� �� ���� � � �������.", "��, ������� �� "+sti(NPChar.rank)*500+" ������� � �� �������.", "��, ��� ����� ����� ��������, �� �� "+sti(NPChar.rank)*500+" ������� ����� � ��������� ���.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("��� � ������������.", "������. ���� ��� �� ���� ����������...", "���� � ���� ��������! ��, ��� ������ - �����.");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("��, ��� �� ���������. �� ����� ������ ����� ���� �������� ������. �������, ����� ���� ���������.", "������ �� �� ���� ������. �������, ������ �� ������� �����. �� ������� - ��� ���� �� ���� ��������.", "� �� �����"+ GetSexPhrase("","�") +" ������� ����� ������. ������ ����, �� ����� �� ������� - � ����� �� ������.");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "�� �����, ��� ����� ���� - �������... �� ������, ��� � �������� ������ ����� ����...";
		Link.l1 = LinkRandPhrase("��� � ������. ����������� � ����� ������������, � ���� �������� �� ��������� �����.", "������ ����������� �� ����. � � ��������� ��� ���������� �������, ������, ��� ������� �� ��������.", "���-���. ������ - ���� ������, � ������ �������� ����� ���������.");
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
            Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
		break;
		
		case "WantToGo_free":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				Diag.CurrentNode = Diag.TempNode;
				DialogExit();			
				break;
			}
			//navy <--
            Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;
		
		case "WantToGo_free_Yet":
            Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase ("�� �� ��������, ������� - ����� ���� � ���� ���������.", "�������, �������, ��� �� ����� ����������. ������� ��� ����-�� � ����� �����������.", "��, ���� ��������� � �������. ������ ������ �������, ��� ���������� �������� ������.");	
		Link.l1 = RandPhraseSimple("��, ��������� ���� �������...", "�����. ����������� ���� ������.");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 ������ ����� ������� <--
		
	// �������� �������� ������� � ��������� -->
	case "WantToRemove":
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("�������, � �� ���� ���� ������ ���������� ���� ������� � ���������� �������.","�������, � ����� �� ����� ��������� ������� � ����� �����������. � �� ������, � ������.","�������, ���� ���������� ������� ������ ����������� �� ���������� ���������� � �������."), LinkRandPhrase("�������, ����� ��������, ��� ��� ��� � ��� �� ������ ��� �������� �������. � ���������� �� ����� ���� ����� ���������� ����� ������� ������.","�������, �� ����� ����� ��������� ���������� �� ����� ������ �����, ���������� �������� � ����-�������� ����� ��������. � ������ �� ����� ������� � ����� �������.","�������, �� ������� � ������� ����� ����������� - �� � ��� ������ ������ �����������. ���� ���������� �� ����� � ����� ������.")) + " ��������.";
			Link.l1 = "���?!! � ���� ������ �����, � �� ����������� �������! ������ ��������� �� ���� ������!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "� ����� ����"+ GetSexPhrase("","�") +", ��� �� �����... ����� ������ �� ��� ����. �� ��������� ��� ���� �� � ���. ��� "+sti(NPChar.rank)*500+" ������� - ����������, ���� ������ ������ �� ����.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("���. ���, ������, ��� �� ������. � ����, ������� ���� ������������� � ������� �������, ���� �� ���? ��� �� �������� ������ � ��������� �������� - ����� ����������? ����� �� � �� ��� �������� �������! ��-��-��-��...", "��, ��� ��������� ���������. � ���� �� �������� ���� ����������� �������, ����� �� ������ ������� ������? ��� � �������� �����������? ������ �������� ����� ��������, ���� �� �������� ��������� � ������ ��������...", "�� ��� �����!.. ������, ��� �� �������, ��� � ���� ���"+ GetSexPhrase("��","��") +" - � ������� ������� ��� ����� � �������. �� ����, ��� ������� - ���� ����, � ���� �� - �� ������� �����.");
			Link.l3.go = "WantToGo_stop";
			}
			else
			{
            dialog.text = RandPhraseSimple(LinkRandPhrase("�������, ���� ���� � ������������ ��� ������ �� �� ����. � �� ����� ���� ������ ��������� ����������� ������ ���� ��������. ��������.","�������, � �� ���� ����� ���������� � ��� �� ������. ������� ������� ��������� ��� ����� - ��� ������� ���������� ����� ���� ��������� ����� ���������. � �����.","�������, ���� � ���� ������� �� ����� �����������. � ����-�������� ���� �� ������ - ��� �� ������ ���� ���������� �����, ���� ������ �� � ���. � �����."), LinkRandPhrase("�������, � ������ ������, � ��� ������� ����� ����� �� �������� �����. ����� ������ �� �� ���, � �����. ��������.","�������, �� ������� � ������� ����� ���������� - �� � ��� ���� ������ �� ������ �����������. ���� ���������� �� ����� � ����� ������, ������� ��������.","�������, ��� ��������, ��� � ����� ���������� �������. � �� ��� ����������? �������� �������������������! � �� ���� ������ ����� � �����."));
			Link.l1 = RandPhraseSimple("�-��. � ����� ���������� � ������ ���� ��� ������ ��� ������ ���� ���������. ��� �, ���������� �� �����.", "����� ��������� �� ����� ��� ���� ��������������. ��� ��������� � ������ ���� ����� �� ����������.") + " ����� �������.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "� ����"+ GetSexPhrase("","�") +", ��� �� �����... ����� ������ �� ��� ����. �� ��������� ��� ���� �� � ���. ��� "+sti(NPChar.rank)*500+" ������� - ����������, ���� ������ ������ ����� �����.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("��. ��� ��������� ���������. �� �� ��� �� ��������� ���� ���������� ���� �����. ������� ���� ������ � ������ �����������, ��� �������.", "�������...� �����-�� �������� ������� �����. ����� ������ ������: '���� ��� �������� ������... �� ����� ������� �� ��������� ������ � ������ ������, ������ ����, ����� ������ � ������.' �� ��� ���� ����� �������?");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("�� ��������� ���� ���������! �, ��� � ���, ����� �� ������, �� ������ �������� ������ �� ����.", "� ��������� �������! � ������ ������� ������, ����� �������� ������.", "� �� ���, ����� ������� ���� �� ���, ������� ��� ������� �����! �� � �� ��������� � ����� ����������� � ���� ������!");
				Link.l1 = "�-� ���, ��� ��� �� ����������... ���� �� �������� ������ � ������� - ��, ����� ���� �������� ����� ������... �� ����� ����, ��� ������ �� ���� ����� ����� - ��... ������� ����� - ������ � ����� �� ���, ��-��... �� ������ ��� ���������, ���� �� ��� ����� �������� �� ��������, ���� �� �������...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "��, �����. ���... �� �� ������� ���� ������� ��������� ���� � �������� ����. �������, �� ���������, ��� �� ������� �� ���� �������.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("�� ��������� ���� ��������! �, ��� � ���, ����� �� ������, � ������ �������� ������ �� ����.", "� ��������� �������! � ������ ������� ������, ����� �������� ������.", "� ��� �� ���! � � �� ������� � ����� ��������� �� ����� ������!");
				Link.l1 = "�-� ���, ��� ��� �� ����������... ���� �� �������� ������ � ������� - ��, ����� ���� �������� ����� ������... �� ����� ����, ��� ������ �� ���� ����� ����� - ��... ������� ����� - ������ � ����� �� ���, ��-��... �� ������ ��� ���������, ���� �� ��� ����� �������� �� ��������, ���� �� �������...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "��, �����. ���... �� �� ������� ���� ������� ��������� ���� � �������� ����. �������, �� ���������, ��� �� ������� �� ���� �������.";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("���� ���� ��������� ����� ������, �� � �������� - � ���� ������ ��� ������� ������. �� ������, ��� � ��� ����� �� �� ����������� ����...", "�� �����, ��� ����� ���� - �������... �� ������, ��� � �������� ������ ����� ����...");
			Link.l1 = RandPhraseSimple("��� � �����... �������, ���� � ���"+ GetSexPhrase("","�") +" �� ����, ����� ���� ����������.", "��� � ������ - ������� ����... � � ���"+ GetSexPhrase("","�") +" ����, ����� ���� ���������.");
			Link.l1.go = "WantToGo_Munity"; //���� ���� ����� � �������
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar, "��� ������� �� ��������� ���� �������� �������! �� �� ���� ������!", "�� �������� �������, ��� ������� �������� ������� �������?! ��� �� ������� ����������� ������ � �����. � ���� �� �� �����, ����� ������� � ������� ���, ��� �� ����� ������� �������!");
			Link.l1 = NPCharRepPhrase(NPChar, "�� ��� �... ������ ��� �������� ���� ������. �������, �� ��������� ����� ������� �� ���.", "���� �� � ����"+ GetSexPhrase("","�") +", �� ���� �����"+ GetSexPhrase("","�") +", ����� ��������"+ GetSexPhrase("","�") +" ���� � ������� ��� ����� � ��� ����� � ������� - �������, ��������"+ GetSexPhrase("","�") +" �� ���� ����� �� �����. � ������ ��� �� ������ ��� ��������...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar, "��, ��� �, ������, ��� ���� ��� ����� �������. �� ���� - ������������ �� ���� �� �� ��������.", "��, �����. ���... �� �� ������� ���� ������� ��������� ��� � �������� ����. �������, �� ���������, ��� �� ������� �� ���� �������.");
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputation(pchar, -1);
			dialog.text = NPCharRepPhrase(NPChar, "������ �� ����� ���� ������! ��� �� ����� ����������� �������� ������� ������ ���� �����?! �� ���� � ��������� - ��� �� ����������� ���! � �� �������... ����������������, � ������ �������, ���� ������� �� ��� ������� �� �������������?!", "������� ���� �������, ��� ���� �� ��������! ��������.");
			Link.l1 = NPCharRepPhrase(NPChar, "���, ��������, �� ������� ���� �� ������. ����� ������� �� ��� ����...", "�� ��� ������, ��������, � ���� ��� �� ���"+ GetSexPhrase("","�") +" �������...");
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. ������� ������� �������
			Diag.TempNode = "Hired";
			if (sti(Pchar.questTemp.MunityOfficerIDX) != GetCharacterIndex(Npchar.id))
			{
				Pchar.questTemp.MunityOfficerIDX = GetCharacterIndex(Npchar.id);
				Pchar.questTemp.MunityOfficerIDX.begin = "1";
				SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
			}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// �������� �������� ������� � ��������� <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar, RandSwear() + "�� � ������ "+ XI_ConvertString(Npchar.quest.officertype) + " � ���� �����. " + Npchar.quest.officertype_2 + "����� ������� ��� ������, ����� �� ������.",
                                    "��, �������, ��� � �������� " + XI_ConvertString(Npchar.quest.officertype) + ". " + Npchar.quest.officertype_2 + "�������� ���� �� ���� �����, ������� - ��������� � ���� ����.");
			Link.l1 = "������� �� ������?";
			Link.l1.go = "price";
			Link.l2 = "� ��� �� �� ���� ������������� ��� ����������?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "���, � ���� ��� ���� " + XI_ConvertString(Npchar.quest.officertype) + ".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("���, �������, �� ����� ��� �������� ��������� ��������. ������ ���� �� ����� ���� � ���� � �������!", "����������� � ���� ����������� �� �������? ��� ��, � ������ ���, ���...");
				link.l1 = RandPhraseSimple("�� ��� ������...", "�� � � �� "+ GetSexPhrase("���������","����������") +" ���� ��������."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "������� ����������, �������? ������, ��� ����� " + XI_ConvertString(Npchar.quest.officertype) + " ��� �� ��������?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "�������, ���. ������� �� ������?";
                Link.l1.go = "price";
			}
			Link.l2 = "����� �� ������ � ����?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "� ���� ������ ��������. ��������� ����������.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "�����, �� � ���� �������� �� " + Npchar.quest.OfficerPrice + " ��������.";
			Link.l1 = "�� ������� �� �� ����� ������?";
			Link.l1.go = "trade";
			Link.l2 = "� "+ GetSexPhrase("��������","��������") +". ������ ���� ����������� � �������.";
			Link.l2.go = "hire";
			Link.l3 = "�� �� ������ ���� �����. ������.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // ����� ����� ��������� ����� �����
				dialog.text = "������... �������, � ����� ����������� ���� �� " + Npchar.quest.OfficerPrice + " ��������. �� ���?";
				Link.l1 = "��� ��� ��� �����. �� ������.";
				Link.l1.go = "hire";				
				Link.l2 = "� ��-�������� ������, ��� ��� ��������. ������.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "���, �������, � ���� ������ �������, ������� ��������. ���� ��� ������� ������ ��� ��� - ������� ����-������ �������.";
				Link.l1 = "�� �����, � "+ GetSexPhrase("��������","��������") +". � ���� ����.";
				Link.l1.go = "hire";				
				Link.l2 = "��� � � ��������. ����� ��������.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			if(makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "��������� ���, �������. �� �� ���������, ��� ������ ��� ��� ������.";
				Link.l1 = "������� � ��� ������.";
				Link.l1.go = "Exit_hire";								
			}
			else
			{
				dialog.text = "��, ������, � ��� �������� � �����������! ��������, �������, �� � �� ������� � ������.";
				Link.l1 = "�� ��, ����!";
				Link.l1.go = "Exit";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "������ � �����, �������, � ���������� �� ����. �� �������� ������������ - � ����� �� ��������.";
			Link.l1 = "������. ��������� - �������� ������ ������!";
			Link.l1.go = "Exit";											
		break;
        
        case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "�������, �� � ��� ���� ���� �������!";
				Link.l1 = "�������, ��������...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
            dialog.text = "������������ ���������� ���� � ����� " +
                     FloatToString(50.0 / (2.0+GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)), 1) +
                     "% �� ���������� �����. �� "+GetCrewQuantity(PChar) + " �������� ����� " + makeint((GetCrewQuantity(PChar)+6) / 10) + " ��������� � ����. ��� ��� ����� ����������� �����.";
            Link.l1 = "�������.";
            Link.l1.go = "Exit";
            Diag.TempNode = "Hired";
        break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "����� ����� ����������?";
            Link.l1 = "���� �����!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "������ �� ���� � �� ��������!";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "� ����, ����� �� �������� �� ������������ ���������� �� ����.";
				Link.l3.go = "TargetDistance";
			}
		break;

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
			if (makeint(PChar.reputation) >= 41 && makeint(NPChar.reputation) < 41) //����� ������ ������
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("��� ��� �������!","� ����� ��� �������?!","� ���� ��� �����?!"), RandPhraseSimple("�������, �� � ���� ���? �������� ����� ������� �� � ����, �� � ����!","���! � ��� ��� � ��� �� ������?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("� �����"+ GetSexPhrase("","�") +" ������� ������� � �������. �, ��������� ��� �� �������� ���� ��������������� � ���������,","���� ����������� ��������� �� ��� ������, ��� ������������� ��� �����, �������","����������� � ����������� � ���� ������� �� �����! �������"), LinkRandPhrase("��� ����� ��������, ��� �� ������ �������� ��� � ��������� �������, ��� ����� �������� � ������ ���. �������","��� ��������� ������� ���� ����������� �������, � �� �������"+ GetSexPhrase("","�") +" ������� �� ����������. ��� ���,","�� ��������� ��������� ����� � ����-�������� �� ����� � ����� ��� �����, �������� ������ �������� �� ������� ������. ��� �� ����� ������������ ����������, �������")) + " ��������� � ������ �����.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation) >= 41 && makeint(NPChar.reputation) >= 41) // ����� ������ �����
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("���� � ������ ������� ������ �������?","��������� ����� ������� ����� ������ �������?"), RandPhraseSimple("����� �����������, �������","������ ����������. �� �������� �� ����� ���������."));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("���� ������������� �� ���������� ��� ��������� � ����� ������������.","� ���������, �� ���� �� ����� ��������� �������, � �������� ��� �� ������...","�� ������� ������, � �������� �� ������, �� ����� ���� ���� ����������. � �� ��������� ���� ������."), LinkRandPhrase("� ������������"+ GetSexPhrase("","�") +", ��� ������� � ���� ���� �������. ��� � ���� ���������� � ��� ��������, ������� ������ � ����� ������� �� �����?","������ �� ����, ������ �����, �� �����... �����, �� ������ �� ��������� ��������.","���� ����� �� ���������� ���� ������������, �� ������ � �������-�� ���"+ GetSexPhrase("��","��") +" ��������� ������."));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation) < 41 && makeint(NPChar.reputation) >= 41) // ������ ������ ����� 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("��. ���� � ������ �������?","��� ��������� ���������. ���� � ������, ��� ��������� ��� �� ����������?"), RandPhraseSimple("����� �����������, �������.","�������, � ������ ��������� ������� ������ ���������?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("���� ���������� �� ���������� ���� ������������, �������","� ���������, �� ���� �� ����� ��������� �������. ��� ���,","��� ��������� ������� ���� ����������� ������. � �� �������"+ GetSexPhrase("","�") +" ������� �� ����������, ��� ���,"), LinkRandPhrase("�� ���� ����� �����, ��� ������ �� ���������� ������� � �������������. ����������� �� ��� ����� �� �����! � �� ����� �����������, ��� � ������ �� ���������"+ GetSexPhrase("","�") +" ���� �� ����... ��� ���,","���� ����������� �������� ������ ���� �����, �� ��� ���� ������� � ��������� ������ �������� ������. ��� ���,","���� ������������� �� ���������� ��� ��������� � ����� ������������. �������")) + " ��������� � ������ �����.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation) < 41 && makeint(NPChar.reputation) < 41) // ������ ������ ������
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase("�������, � ����� �� ������ ������ ��������! ����� ���������, ��� ���������?","�������, ��� �� ���� ��� �������?!","��� ��������� ��� ��������, �������?!"), RandPhraseSimple("��� �� ���, �������?! ��� ����� �� ���� ���������, � ��� - �� ����...","���! �����, �� ������ ���� ���� ��� ����������?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("�� ���������� ������� � ������� - ���� �� ����� � ���������� ��������. � � ��� ������� ����� ������"+ GetSexPhrase("","�") +". ��� ���,","�� ����� ���� �� �����������, �� ������ � �������-�� ���"+ GetSexPhrase("��","��") +" ��������� ������. ��� ���,","��� ����� ��������, ��� �� ������ �������� ��� � ��������� �������, ��� ����� �������� � ������ ���. �������"), LinkRandPhrase("��� ����� �� ����������, ��� ������� ������� �� ����� �� ��� �����, � �� ������� �������� ������������ ����������, ��� ���","� ������������"+ GetSexPhrase("","�") +", ��� ��� �������� ����� ��������. ������ � ����"+ GetSexPhrase("��","��") +" �� �� ���� ������ ���"+ GetSexPhrase("","�") +"? ��� ���,","������ ������� ������, �� ��������� ������� � ����-�������� �� ����� � ����� ��� �����. �������, �� �� �����, ��� ��� ����� ������������ ����������? ��� ���,")) + " ��������� � ����������.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("��� ������ ���! �� �����, ���� ����. �� ������: � ��� � ������ �� �������. ��� ������� ������...","����������, ���� ���� � ������������ ��� ���� ���-�� �� �� ����. ��� ��� - ��������...", "�� � ���� � ����! ����������� �� ������ �����������. ���� ��� - '�����'!"), LinkRandPhrase("�� ��� � ��� ������� � �� ���������, �� �����, � �������� �����. ������� ����������� �������...","�� ���� ������ � ���� ������� �� ����� �����������. � ����-�������� ���� �� ������, ��� �� ������ - ���� ���������� �����...","������, �������, ���� ��-������. ��, ����� ���, � ���� �� ������ �����..."));
			Link.l1 = "����. ������ � �� ���� �������� ����� ��� �������. �� ������� �� ��� �������� � ����� ���������.";
			Link.l1.go = "exit_bad";
			Link.l2 = "��� � ������ � �����.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "�� ��������. � ����������"+ GetSexPhrase("","�") +" ���� �������� ������� "+sti(NPChar.rank)*500+" �������. �������, ��� ������ ��� �������.";
				Link.l3.go = "Get_out_�1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("���������! ��� ������ '������ �����'?! �� ��� ���� � ���� ������ ��� ������� ����������, ���� �� ����� ���� ����������, ����� ����������!", "��! '������ �����'! �� �������, � ������� ���������� ����, ��� ������?!", "�������, �������, � ��������� �������� ��� ���� �� ��������. � �� ������� ���������� � �����, ��� � �������.");
			Link.l1 = "������, ���������. �� ���� ���� � �� ����� ��������� ������." ;
			Link.l1.go = "exit_bad";
			Link.l2 = "� �������� - ���� ������ ���������. ������ �������� ����.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "�� ��������. � ����������"+ GetSexPhrase("","�") +" ���� �������� ������� "+sti(NPChar.rank)*500+" �������. �������, ��� ������ ��� �������.";
				Link.l3.go = "Get_out_�1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("�� � � �� ���� �������� � ��� �������������. ������ ��� ����������� �������� ����� �� ���������!", "�� � ������ � ��� �� �������� �� ����� ������. ������ �������� ������� ��������� �����������!") + " "+sti(NPChar.rank)*1000+" �������, � �� ������� ���� � �����.";
			Link.l1 = "� ���������"+ GetSexPhrase("��","���") +"... ����� ��� ���������, � ����������� �� ����.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "� ����� ������� ����� ���� ����, ���� �� ��������� ������� ���� ����? �� ��� ������� ��������� �� ��������������!";
			Link.l2.go = "Get_out_�1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "�����. ���� ���������� � �������� ��, � ��� �������.";
				Link.l3.go = "Get_out_�1_chang";
			}
		break;

		case "Get_out_�1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "��, ��� ������ ������ ����. ��������!";
			Link.l1 = "�������, ���� ������ ������ �� �����������.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_�1_strife_battle":
			dialog.text = LinkRandPhrase("�������� ��� ������������ ��������� ��������. � ������ �� ������� ��� � ����� ����������! � ��� �������, ��� ����� �������� �� ����!", "��� �� ��������������, � ����������� �������� ������������ �������! � � � ������, ���� �� ��� ��� �� ������!", "� �������� ������� ����� ������� �� ������ � ���"+ GetSexPhrase("��� ���������","�� �����������") +" ��� ��. �� ��� ����� ����� ���� ����������� �������� ���������. ������ ���� �������������� ��������� ������.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "�����. ��� ���� ������... � ������ �������� ������!";
				Link.l1.go = "Get_out_�1_ForMoney_angry";
			}
			Link.l2 = "�� �����������! � �� ������� ������ ��������� �������� �� ���� �����!";
			Link.l2.go = "Get_out_�1_strife_death";
		break;

		case "Get_out_�1_strife_death":
			ChangeCharacterReputation(pchar, 1);
			OfficersReaction("good");
			dialog.text = "�����-�����, �������! ������, �����"+ GetSexPhrase("","�") +" �� ������ ���������� ���������!";
			Link.l1 = "����� ���, � ����� �� �����"+ GetSexPhrase("","�") +"!";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_�1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			dialog.text = "��, ��� ������ ������ ����. ��������!";
			Link.l1 = "�������, ���� ������ ������ �� �����������.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("�� ��� �, ������ �� ������. ��������, �������, �� ��������� �����...","����� ����, �������. ��, ����� ���, � ��������. ��������.","��, �������, ��� �� �������!.. ��������� ����������."), LinkRandPhrase("����, �������. ��� ����� ��������� ������� � ���.","��� ���� ��� ������... �� � ��� �� �����, ��������.","�� ������������� �� ���, �������. �� � ������ ���� �������. ��������."));
			Link.l1 = "����, � ���������"+ GetSexPhrase("","�") +". ����� ����� � ����� ��������� �����.";
			Link.l1.go = "exit_good";
			Link.l2 = "�� ���������. ����� ����...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "������... � ���� ������� ����������"+ GetSexPhrase("","�") +". ����� �� ������� ������� - ��� ��� ����� ����� ��������� �����...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "������... �� ���� ��������� ���� � ������� ������. ��� ����� "+sti(NPChar.rank)*500+" �������, ����������, ���� ������ ������ ����� ������.";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "�� � ��� ����, ������� ���������...";
			Link.l1 = "� ����"+ GetSexPhrase("","�") +", ��� �� ���� ��������� ������...";
			Link.l1.go = "Get_out_�2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "������� ���, �������! ����� ����������� ��������. � ���� ��� �������� ���-��� �� ����� �����, ����� ������� �� �������?";
			Link.l1 = "�� �������... ������ ����� ������� ������ �� ��� ��������...";
			Link.l1.go = "Get_out_�2_chang";
			Link.l2 = "�� �����. ������ ���� � ������ � ������ ��� ���� �������...";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("�� ��� �, ���� ����. �� ������: � ��� � ������ �� �������, ���� ���� ������� �������� � ������.","����������, ���� ���������� ������� ��� ���� �� �� ����. ��� ���, ��� ���� ��� ������ ������ ���� ���������... � �� ����� ���������� ������� ������.","�� � ����������� �� ������ ������������. �� ����� ����� ���������� �������� � ����-�������� ����� ������. ������� �������, ������ ���� �������!"), LinkRandPhrase("����������, � ���� ���� ���� �� ����� � ����� ������. ������� � ������� ����� ����������� - �� � ��� ������ ������ �����������.","��, ���� �� ������ ��� ���������� � ������� ������� - �� ��� ��� ���� ����������. ������� ������ ���������� �� �������.","���� ������� ��, ��� ���� ��������� �������. ��������� ����������."));
			Link.l1 = "����. ������ �� ����� ������� ������ ���� ���������. �� ��� ��������� �������� � ����.";
			Link.l1.go = "exit_bad";
			Link.l2 = "���-���. �������� ��� ����� �����������.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "�������. ��� ���� �� ������ "+sti(NPChar.rank)*500+" �������. � �� ������ ��� �������, � ��� ����� ����� ����� ��������.";
				Link.l3.go = "Get_out_�3_ForMoney";
			}
		break;

		case "Get_out_�3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterReputation(pchar, 1);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("� �� ��� �������. ��������...", "��������� �� ���������. ��������� ����������.", "��� ������ �� � �������. ����� ��������...");
			Link.l1 = "� ����"+ GetSexPhrase("","�") +", ��� �� ���� ��������� ������...";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("��, �������, ��� ����� �������� � ������� ������ �� ����. �� �� �� ������ ��������� ���� � ������� ����� �� �������?", "�� ������������� �� ���, �������. �� � ����� ������ �����, ���� ������ ��������� �����������.", "� ��� ���� ������������� �� ��� ��� ������ �������? �����, ��� �������� ����������� ��� �� ��������.");
			Link.l1 = "�����, � ���������"+ GetSexPhrase("","�") +". ���� ���������, �� �� ��� ������� � ����� ���������.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "��, �� ���� ������ �� ����������. ����� "+sti(NPChar.rank)*500+" �������. �����, �� ������ ����� ������.";
				Link.l2.go = "Get_out_�3_ForMoney";
				Link.l3 = "� ��� ���� �����. ��, ��������� ���, �� ������� ���������� - ������� ����� �� �������.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "���! � ��� �� ��������� ���������� ����� ����?! � ��� � ����"+ GetSexPhrase("","�") +", ��� �� ���������� ������ � ������������� �������.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "� ����, ��� �� ��� �������, �� ���������� ������� ������� ������, ����� � ������ "+sti(NPChar.rank)*1000+" �������. ��� ��� ������� ������� � � �����.";
			Link.l1 = "������, ����� ���� ������.";
			Link.l1.go = "Get_out_�3_chang";
			Link.l2 = "�� � ���� �� �� ���?! ��������� ����� ����� �� ��, ��� � ��� ���� ���������! ������, ����� ������ ��������, ��� ��������, ��-���� �������� ���� ��� ����� ��������� ������������.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "�� �� ������ ���� ����������! �, ����� � �� ����� ������ �� �����, �� �� �� ������ ������. � �������� ������� ����, ���� ���"+ GetSexPhrase("���","��") +" ������ ��� ��!";
			Link.l1 = "���� ���� ��� �� ����, �� ������� - ������ �� ��������, �� ����� ������ �� ��������.";
			Link.l1.go = "Get_out_�3_strife_death";
		break;

		case "Get_out_�3_strife_death":
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			dialog.text = "��, �� ��������������-�� � ������ � ����� ������!!";
			Link.l1 = "�� ��� �����! ��, ��� �, ��� ���������...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("��� ��� ������! ��� ���� �� ������ ������, � ���� - ���, � ��� ��������� �������!","�� ��� � ��� �� ������� �����?! �� ������� ��������, ��� ���� ��� �� �������� ��� ���. �� � �� ����, ���� ������ �������...","��� �� ��! ��� ������ ���������� �� ��� - � �� �� �������������. ���� ��������� ���� �� ����� � �������� �� �����������!"), LinkRandPhrase("�� �����, ����� ���. ������ �� ������� ������� ��� ������ �����������.","�� ��� �, ���� ����. �� ������: ������� ������� ��� �� ����� �� �����.","������, �������, ���� ��-������. ��, ����� ��� - � ���� �� ������ �����..."));
			Link.l1 = "����. ������ �� ����� ������� ������ ���� ���������. �� ��� ��������� �������� � ����.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("�����-�����. � ��������� ����, ��� � ������� � ������� ����������.", "�����-�����. �� ����� �� ���� ������, ��� �� ������ ����.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "�������. ��� ���� �� ������ "+sti(NPChar.rank)*500+" �������. � �� ������ ��� �������, � ��� ����� ����� ����� ��������.";
				Link.l3.go = "Get_out_�4_ForMoney";
			}
			Link.l4 = "������... � ���� ������� ����������"+ GetSexPhrase("","�") +" - ������� ����� �� �������.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_�4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterReputation(pchar, 1);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("��� �������, �������! ��� ��� �������...", "��������� �� ���������. ��������� ����������.", "��� ������ �� � �������. ����� ��������...");
			Link.l1 = "���������. ������ �� ������ �� ��� � ��������� �������.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("��� ������ ��� � ���������� ���������! �� ������� ��� �� ��������! ��-���� � ������ �������...", "����, �� ���� ������� ������� ������. ��� �, ���������. ���� ������ ������ - �� �������...", "��������� �������! ������ ��� � ��������� ������. ��, ��������!.. ���������, ���� ��� �� �������...");
				Link.l1 = "�����-�����. �� ����� �� ���� ������, ��� �� ������ ����.";
				Link.l1.go = "Get_out_�4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("���� ��-������, �������, ������ ������� ������� ��� "+sti(NPChar.rank)*1000+" �������. ����� ������� ��� ������������ ��������� ��������.", "������. ������ �� ��� � ���� �������� "+sti(NPChar.rank)*1000+" ������� � �������� ����������� �� ������� ������.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "��� ��������! �����, ����� ���� ������.";
					Link.l1.go = "Get_out_�4_chang";
				}
				Link.l2 = "�� �� ����� ��������?! ������ ������� ������� ����� �� ��, ��� � ���"+ GetSexPhrase("","�") +" �� ���� ���"+ GetSexPhrase("","�") +"!";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "��-��! �� � �������"+ GetSexPhrase("","�") +"! ����� � ���� ���������� ������� �����, ��� ������� ������!";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterReputation(pchar, -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "��, ����� ������ � �� ��������! � � ����� �� �������, ���� �� ������, ��� ������ �� ������!";
			Link.l1 = RandPhraseSimple("������ �� ��������, ��� ������ ��� ������!", "������, ���� ������ ����� ������!");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_�1_chang": // ��������� ������
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_�2_chang": // ��������� ������
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_�3_chang": // ��������� ������
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_�4_chang_1": // ��������� ������
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterReputation(pchar, -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_�4_chang": // ��������� ������
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputation(pchar, -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = "�� ���� ���? ��, �������, ��� �� ������! ���� ���� ������ �� ����� ����� �� �����.";
			Link.l1 = RandPhraseSimple("������-������. �������� ������.", "���-���. ���������� �� �����.");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "���-�� ���, �������? ��� ��������, ��� �� ��� �� ������...";
			Link.l1 = "���, ������. ������ ����������� �����"+ GetSexPhrase("","�") +"...";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "�������, ��� ������� ������, ��������� ���������. �� ������ �� �� ����� ����� ����� �������, ��� ����������.";
			Link.l1 = "���-���. �������� ������.";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "�������, �� ����� ��� ����� ���� �������? �, ������� �� �������, ����� �� ��� ������, � �������� ������� ������������ �� ����...";
			Link.l1 = "���-���. ����� �� ��� ������, ������ ������ ������.";	 
			Link.l1.go = "Exit";
		break;
        // boal 05.09.03 offecer need to go to abordage -->
	      case "Boal_Stay":
             //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
             //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
              Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
              AddDialogExitQuestFunction("LandEnc_OfficerStay");
		      Diag.TempNode = "Hired";
		      dialog.text = "���� �������� ����������!";
		      Link.l1 = "������.";
		      Link.l1.go = "Exit";
		      Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	      break;
	      case "Boal_Follow":
		      SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		      Diag.TempNode = "Hired";
		      dialog.text = "���� �������� ����������!";
		      Link.l1 = "������.";
		      Link.l1.go = "Exit";
	      break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    ������-��������� -->
		case "Gover_Hire":
            dialog.Text = "����� �� �����!";
            Link.l1 = "����� �� �������� � ������������ ������, � ���� ������ ���������� �� ��������� ��������.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "� ���������"+ GetSexPhrase("","�") +".";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
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
			Diag.CurrentNode = "Gover_Main";
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
            Diag.TempNode = "Gover_Main";
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

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "������������! ���� ���������� ������ �� ��� ����.";
            Link.l8 = "��� � ������.";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
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
	
		// ��������������� �������� ���������� -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // ���� ��� ����� ��������
			{
				dialog.Text = "�������, � �� ����� �� ������� ����� �������, ��� ��� �� � ��� ��� ��������� ��� �������.";
					Link.l1 = "��, ������� �� ����.";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = "��� ������, ���. � ����� ������ �� ����������?";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = "� " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "� ���������. ������ �� �����.";
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = "�������, �� � �� �� c���� ����� ��� � �������, ������� � ��� ���������!";
				Link.l1 = "������, ������ ��� ��� ��� �����������...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "���, �� ������� �� ����� ���� ��������! ����� ��������?!";
				Link.l1 = "��, �����. ������� ����� ����...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "���, ��� ������ ����������� � ���� �� ����� �������� ���������.";
				Link.l1 = "��, �� ����. ����������� ��������, ����-���...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "���, �� ��� ������� � ������ ���������. ��� �� ������� �������� � ���� ������ ��� ����� ���������������!";
				Link.l1 = "��, �� ����. ���� ������� ��������� � �������.";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = "��� �������. �� " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen") + " ��� ���� " + sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days) + " ����, ��� ��� ������ �� ��������?";
				Link.l1 = "��� ���� �� ����� ������� �����.";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "������, � ���������. ��������� �� ����, ����-���...";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "��� �������, �������. ����������� ����������.";
				Link.l1 = "��, �����������.";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("������� � ����� ����� � ����...",
			"�� �������� ��� ���� � ���� ������� � " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Dat") + ".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "� ���� ����� �����. ������ ��� ������� ����� ��� ����� ����������������, ���.";
					Link.l1 = "������.";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // ������ ������
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // ����� ���������� ����� ������� � �������
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = "���, � ��� �� � ��� ������� �� ���� �������, ����-�� ������ ���? � �����, � ���� ����� ��� ���, �� ����� ������� - ��� ��� ���� ����� ���������� �� ������� - �� ����� ����� ����� ������ �� ��� � �� �� ���� ���������.";
					Link.l1 = "��, ����� �� ������. ���� �� ���������, � ��������� ����� ����!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ������ ����� ��� ����
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "�-�, �������. ��� �� � ���������, ��� � � �������. �� ���, ����� � ������� ������������?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "��, " + NPChar.name + ", ������������. ����� ���������� � ������ �������.";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // ����� ���������� ����� ������� � �������
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = "��� ���, � ���������.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- ��������������� �������� ����������
	}
}