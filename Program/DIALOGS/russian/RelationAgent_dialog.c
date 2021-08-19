#define DIPLOMAT_SUM 80000

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iSumm = 0;
	string s1;
	
	if (!CheckAttribute(npchar, "PatentPrice"))
    {
		if (IsCharacterPerkOn(pchar, "Adventurer")) npchar.PatentPrice = (6000 + rand(4) * 500);
        else npchar.PatentPrice = (8000 + rand(6) * 1000);
    }
    int i;
    string attrLoc;
	ref    sld;
	
    attrLoc   = Dialog.CurrentNode;
    
    if (findsubstr(attrLoc, "SetNationPatent_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.nation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
 	    Dialog.CurrentNode = "patent_2";
 	}
 	
 	if (findsubstr(attrLoc, "SetNationLicence_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceNation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
 	    Dialog.CurrentNode = "NationLicenceType";
 	}

 	if (findsubstr(attrLoc, "NationLicenceType_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceType = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
 	    Dialog.CurrentNode = "NationLicenceType2";
 	}
 	
 	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
        npchar.quest.relation      = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
		// �������� �� ��� �������
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
		    Dialog.CurrentNode = "RelationYet";
		}
		else
		{
 	    	Dialog.CurrentNode = "RelationAny_Done";
 	    	npchar.quest.relation.summ = CalculateRelationSum(sti(npchar.quest.relation));
 	    }
 	}
 	
 	if (findsubstr(attrLoc, "CityPay_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
 	    Dialog.CurrentNode = "CityInfo";
 	}
 	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "��� ������ ��� �����.";
			link.l1 = "��� ����� ����� ���� ������.";
			link.l1.go = "relation";
			link.l2 = "� ��� �����.";
			link.l2.go = "exit";
			//������� ���, ������ �������� -->
			if (pchar.questTemp.LSC == "toLicencer")
			{
				link.l3 = "� ���� ���� � ��� ������ �� ������ ����������� ����-������� ��������.";
				link.l3.go = "SeekHVIC";
			}
			if (pchar.questTemp.LSC == "toLicencer_2")
			{
				link.l3 = "��, ����� �������� �� ���� ������� ������. � ����� �� ������ ����������� ����-������� ��������.";
				link.l3.go = "SeekHVIC_3";
			}
			// ���������  "��������� ���������"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))			
			{
				link.l4 = "���� ���������� ������."
				link.l4.go = "D_ShipLetters_1"; 
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}			
			//<-- ������� ���, ������ ��������
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "��������� �������������, � ������� ��� ���������, ������� ����� ��������� �� ��� �������� ���� ��� ����� �����������. �� �����, �����������, �� ��������, ��� ������ ������ ������� ��������, � �� �� ���������, ���� �������������� ����� ���������.";
				if (CheckAttribute(pchar, "Whisper.BuyDocuments"))
				{
					link.l1 = "��� �������, ��� � ����� � ��� �������� ��������� �� ����������� � ����� �� �����.";
					link.l1.go = "WhisperDocuments";
					break;
				}
				link.l1 = "����� ���������, ���������.";
				link.l1.go = "relation";
				link.l2 = "����� ����, � ������ ���.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			
			NextDiag.TempNode = "First time";
		break;

		//*************************** ������� ������ **************		
		case "WhisperDocuments":
			dialog.text = "��� �����. ��� ������ ��������� ��� � 1000 �����. ��� ����������� �� �� ������ ��������?";
			DeleteAttribute(Pchar, "perks.list.FlagSpa");
			DeleteAttribute(Pchar, "Whisper.BuyDocuments");
			if(makeint(Pchar.money) >= 1000)
            {
				link.l1 = "������.";
				link.l1.go = "WhisperEng";
				link.l2 = "�������.";
				link.l2.go = "WhisperFra";
				link.l3 = "���������.";
				link.l3.go = "WhisperHol";
			}
			link.l4 = "� ������, ����� � ����� ������� ���������.";
			link.l4.go = "Whisper_exit";
		break;
		
		case "WhisperEng":
			dialog.text = "������. �������� ����������� ��� ����� � �� ���������� ��������� ������.";
			Pchar.BaseNation = ENGLAND;
			SetCharacterPerk(Pchar, "FlagEng");
			AddMoneyToCharacter(pchar, -1000);
			Flag_ENGLAND();
			link.l1 = "������.";
			link.l1.go = "Whisper_exit";
		break;
		case "WhisperFra":
			dialog.text = "������. �������� ����������� ��� ����� � �� ���������� ��������� �������.";
			Pchar.BaseNation = FRANCE;
			SetCharacterPerk(Pchar, "FlagFra");
			AddMoneyToCharacter(pchar, -1000);
			Flag_FRANCE();
			link.l1 = "������.";
			link.l1.go = "Whisper_exit";
		break;
		case "WhisperHol":
			dialog.text = "������. �������� ����������� ��� ����� � �� ���������� ��������� ���������.";
			AddMoneyToCharacter(pchar, -1000);
			Pchar.BaseNation = HOLLAND;
			SetCharacterPerk(pchar, "FlagHol");
			Flag_HOLLAND();
			link.l1 = "������.";
			link.l1.go = "Whisper_exit";
		break;
		case "Whisper_exit":
			dialog.text = "��� ���� ������, �� �������. ������� ������� �� �������, ���� �������, � �� �� ����������\n����� ��������.";
			link.l1 = "�� ��������.";
			link.l1.go = "exit";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == PIRATE)
			{
				dialog.text = "� ����� ������ ����� ���� �� ���������.";
				Pchar.BaseNation = PIRATE;
				Flag_PIRATE();
			}
			PChar.quest.WhisperPirateTownGetHat.win_condition.l1 = "location";
			PChar.quest.WhisperPirateTownGetHat.win_condition.l1.location = "PuertoPrincipe_town";
			PChar.quest.WhisperPirateTownGetHat.function = "WhisperPirateTownGetHat";
			PChar.quest.WhisperPirateTownBattle.win_condition.l1 = "location";
			PChar.quest.WhisperPirateTownBattle.win_condition.l1.location = "PuertoPrincipe_ExitTown";
			PChar.quest.WhisperPirateTownBattle.function = "WhisperPirateTownBattle";
			SetLocationCapturedState("PuertoPrincipe_town", true); 	
		break;
		//*************************** ��������� - "��������� ������� ���������" **************		
		case "D_ShipLetters_1":
			dialog.text = "��������� �������.";
			s1 = "� ����, �� ���������� �����������, �������� ��������� ��������� ����� ������� ����������, ��� �� ���������� � ������.";
			s1 = s1 + "����� �� ����� � �� ��������� �� �������, �� ������������. ������ ������-�������� ��������� �������� ��� ������...";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "�����-�� ���������! �������������, ������� ������ ������. ��� ��, ����� ��� ����������, "+ GetSexPhrase("������","��������") +"! ";
			s1 = s1 + "��� ��� ��� ����������� ������ ����� ��������, � �, � ���� ������� ��������� ��� " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " �������. ��� �������?";
			dialog.text = s1;
			link.l1 = "�������� ����������� ��������! ������� �� � "+ GetSexPhrase("��������","��������") +"!";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "�������, ���.";
			link.l2.go = "exit";
		break;
		case "D_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterReputation(pchar, -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //������� ������ 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "relation":
			dialog.text = "������� ���������, ��� � ���� ��� ������.";
            //#20200219-01
			int charNat = sti(pchar.nation);
			bool bCheck = false;
            if(GetNationRelation2MainCharacter(ENGLAND) > GetNationRelation(charNat, ENGLAND))
                bCheck = true;
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 || bCheck)
			{
				link.l3 = "� ���� ���������� � �������.";
				link.l3.go = "RelationTo_0";
			}
			
																							
							  
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 || bCheck)
			{
				link.l1 = "� ���� ���������� � ��������.";
				link.l1.go = "RelationTo_1";
			}
				  
																						  
							  
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 || bCheck)
			{
				link.l2 = "� ���� ���������� � ��������.";
				link.l2.go = "RelationTo_2";
			}

																							  
							  
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 || bCheck)
			{
				link.l4 = "� ���� ���������� � ����������.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "� ���� ���������� � ����������������.";
				Link.l5.go = "Contraband";
            }
            Link.l8 = "��� ����� ��������� ������.";
			Link.l8.go = "patent_0";
			
			Link.l9 = "���� �������� ��������?";
			Link.l9.go = "Licence";
			
			if (isHeroOwnCity(true))
			{
				Link.l10 = "� ���� ������, ��������� � ��������������� ���������.";
				Link.l10.go = "City_Buy";
			}
			
			Link.l11 = "� ����"+GetSexPhrase("���","���")+" ������ ������ ������� � ���� �������� ���� ���������. ������ ��� ��������?";
			Link.l11.go = "PGG_peace";
			
			link.l99 = "������, � �����, ��� �������� ������ ������.";
			link.l99.go = "exit";
		break;
		
		case "PGG_peace":
			dialog.text = "� ����� �������� ��� ����?";
			for(i=1; i<=PsHeroQty; i++)
			{
				sld = CharacterFromID("PsHero_"+i);
				if (PGG_ChangeRelation2MainCharacter(sld, 0) < 41 && !LAi_IsDead(sld) && sld.PGGAi.location != "Dead" && !IsCompanion(sld) && !IsOfficer(sld))
				{
					string attr = sld.ID;
					string linkPGG = "l" + i;
					NPChar.Temp.(attr) = attr;
					Link.(linkPGG) = GetFullName(sld);
					Link.(linkPGG).go = "PGG_make_peace_with_" + attr;
				}
				else
				{
					NPChar.Temp.(attr) = "";
				}
			}
			link.lexit = "�� ���� � ������.";
			link.lexit.go = "exit";
		break;
		
		int nFind = findSubStr(Dialog.CurrentNode, "PGG_make_peace_with_", 0);
		string idxVal;
		string nodName;
		if(nFind == 0) 
		{
            npchar.PGGSelected = strcut(Dialog.CurrentNode, 20, strlen(Dialog.CurrentNode)-1);
			sld = CharacterFromID(npchar.PGGSelected);
			npchar.PGGPeaceMoney = ((sti(sld.rank) + sti(pchar.rank))/4 + (60 - PGG_ChangeRelation2MainCharacter(sld, 0))) * 1000;
			dialog.Text = "��, � ������, ��� "+GetFullName(CharacterFromID(npchar.PGGSelected)) +" ���� ����� ������ ��� ������. �����, � ���� �� ��������� "+ NPCharSexPhrase(sld, "���","��")+ " ���������� �������, ����� ��������� ���������� � ��� ����� ������������. �� ��� ������ �������� ��� � "+ npchar.PGGPeaceMoney +" ��������.";
			if (sti(pchar.money) >= sti(npchar.PGGPeaceMoney))
			{
				
				Link.l1 ="� �����"+GetSexPhrase("���","���")+", �����������.";
				Link.l1.go = "PGG_peace_made";
			}
			Link.l2 = "� ���������"+GetSexPhrase("","�")+", ����� ��������.";
            Link.l2.go = "exit";
            break;
        }
		
		case "PGG_peace_made":
			sld = CharacterFromID(npchar.PGGSelected);
			int addPGGrelation = 60 - PGG_ChangeRelation2MainCharacter(sld, 0);
			PGG_ChangeRelation2MainCharacter(sld, addPGGrelation);
			addMoneyToCharacter(pchar, -sti(npchar.PGGPeaceMoney));
			
			if (CheckAttribute(sld, "PGGAi.Task.SetSail"))
			{
				PGG_Disband_Fleet(sld);
				sld.PGGAi.location.town = PGG_FindRandomTownByNation(sti(sld.nation));
			}
			
			dialog.Text = "��������, ��� �� ��� �������. ����� �����, ������� ���"+ NPCharSexPhrase(sld, "","��")+ " ����� �� ��� "+ GetFullName(sld) +" ������ � ������ ������� ������������."
			Link.l1 ="���� ���������, ��� �� �����.";
			Link.l1.go = "exit";
		break;
		
		case "Licence":
			dialog.text = "������ � �������, �� ������ �����. ����� �������� �������� ����������?";
		    link.l1 = "������";
			link.l1.go = "SetNationLicence_0";
		    link.l2 = "�������";
			link.l2.go = "SetNationLicence_1";
		    link.l3 = "�������";
			link.l3.go = "SetNationLicence_2";
		    link.l4 = "���������";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "������, � �����, ��� �������� ������ ������.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType":
        	dialog.text = "�� ����� ����?";
		    link.l1 = "30 ����";
			link.l1.go = "NationLicenceType_30";
		    link.l2 = "60 ����";
			link.l2.go = "NationLicenceType_60";
		    link.l3 = "90 ����";
			link.l3.go = "NationLicenceType_90";
			link.l9 = "� ���������"+ GetSexPhrase("","�") +".";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType2":
			if (IsCharacterPerkOn(pchar, "Agent")) iSumm = sti(npchar.LicenceType) * MOD_SKILL_ENEMY_RATE * 500 + 200000 + (sti(PChar.rank)*1000) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 1000;
			else iSumm = sti(npchar.LicenceType) * MOD_SKILL_ENEMY_RATE * 1000 + 300000 + (sti(PChar.rank)*2000) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 1000;
        	dialog.text = "����, �������� �������� " + XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name + "Gen") + " ������ �� " + sti(npchar.LicenceType) + " ����, ���� " + FindRussianMoneyString(iSumm) + ".";
		    link.l1 = "���� ����������.";
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "� ���������"+ GetSexPhrase("","�") +".";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType3":
            //iSumm = sti(npchar.LicenceType) * (2000 * MOD_SKILL_ENEMY_RATE) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 2000 + sti(PChar.rank)*10000;
			if (IsCharacterPerkOn(pchar, "Agent"))  iSumm = sti(npchar.LicenceType) * MOD_SKILL_ENEMY_RATE * 500 + 200000 + (sti(PChar.rank)*1000) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 1000;
			else iSumm = sti(npchar.LicenceType) * MOD_SKILL_ENEMY_RATE * 1000 + 300000 + (sti(PChar.rank)*2000) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 1000;
			dialog.text = "��� ��� ��������. ������� � ���� ����� ��� ������������� ������. �������, ������� ����� ���������, �� ���������� �� ��������.";
			link.l9 = "�������.";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;
		
        case "No_money":
			dialog.text = "�������! ���������� �� ���, ����� ����� ������ �����.";
			link.l1 = "������.";
			link.l1.go = "exit";
		break;
		
        case "patent_0":
			dialog.text = "������������! ��� ����� �� ������ �������� ���� ����������� �������" + 
                          " ����������� �������. ������������� � ������ �����������" + //NationNameGenitive(sti(NPChar.nation)) +
                          " � ��������� ��� ��� �������. ����� ����� �� ������ ��� ������.";
			link.l1 = "�������, "+GetAddress_FormToNPC(NPChar) + ", � ����� ���-������ ������ ��� ������������? ";
			link.l1.go = "patent_1";
			link.l2 = "��������, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_1":
			dialog.text = "�� ������ � ���� ������ ������������ ����!? ������, ����� � ����� ��� ������ ���?";
			link.l1 = "������!";
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
            {
			    link.l1.go = "patent_2_give";
			}
			else
			{
                link.l1.go = "patent_2_none";
			}
			link.l2 = "���. ����� ��������, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_2_none":
			dialog.text = "� ������ ������ � �� ���������� ������ �������, ����� ��������� ������ ����� ������� �� ����� �������� � ���������.";
            link.l1 = "����. ��������, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;
		
		case "patent_2_give":
			dialog.text = "������, � ����� ��� ��������. ����� ������ ��� �����?";
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = "������";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = "�������";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = "�������";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = "���������";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "������, � �����, ��� �������� ������ ������.";
			link.l9.go = "exit";
		break;
		
		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			// pchar.PatentPrice = 350000 - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 2000 + 6000 * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
			if (IsCharacterPerkOn(pchar, "Agent")) pchar.PatentPrice = 100000 * MOD_SKILL_ENEMY_RATE - (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 5000 + 35000 + (sti(PChar.rank)*5000);
			else pchar.PatentPrice = 150000 * MOD_SKILL_ENEMY_RATE - (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 5000 + 500000 + (sti(PChar.rank)*5000);
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = "����� ���, ���� ������ - �������� ALexusB";
                    link.l1 = "�������� �����������. � "+ GetSexPhrase("��������","��������") +" �� ���� �������!";
                    break;
                case HOLLAND :
                    dialog.text = "��������� ����� ������ ������, � ��� ������ ����� ������ � ���� ������. � ��� ������ ��������� ��� ����� ���� � "+pchar.PatentPrice+" �������.";
                    link.l1 = "�������� �����������. � "+ GetSexPhrase("��������","��������") +" �� ���� �������!";
                    break;
                case FRANCE :
                    dialog.text = "������ � ����� ������� ������ ������. �� ������� ������ ������� ������. � ��� ������ ��������� ��� ����� ���� � "+pchar.PatentPrice+" �������.";
                    link.l1 = "�������� �����������! ��� �������, ���� �������! ������� � ���������!";
                    break;
                case SPAIN :
                    dialog.text = "� ������� ����� ������ � ��� ��� �� ������ ������! ������� - ����� ������� ������. ������ ��������� ��� ����� ���� � "+pchar.PatentPrice+" �������.";
                    link.l1 = "�� ���� ����������� ��� ���-�� �������! �������� ��� ������ ����� �� ��������� ��������� ��� � ����� ������� ������������������ ����!";
                    break;
                case ENGLAND :
                    dialog.text = "���� ������, ����� ������� �������-���������� ������ �������� ���� ������. � ��� ������ ��������� ��� ����� ���� � "+pchar.PatentPrice+" �������. ";
                    link.l1 = "� "+ GetSexPhrase("��������","��������") +" ������ ��� ���� ������� ������, ������� �����"+ GetSexPhrase("","�") +" ������������ � ����������!!";
                    break;
			}

            if(makeint(Pchar.money) < makeint(pchar.PatentPrice))
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "patent_3";
			}

			link.l2 = "���, ��� �� ��� ����!";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "� ���, ��� �� ������������. �� �����.";
			link.l1 = "��������, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			if (IsCharacterPerkOn(pchar, "Agent")) Pchar.questTemp.Relations.sum = makeint(0.3 * stf(Pchar.rank)/stf(Pchar.reputation)*DIPLOMAT_SUM);
			else Pchar.questTemp.Relations.sum = makeint(0.1 * stf(Pchar.rank)/stf(Pchar.reputation)*DIPLOMAT_SUM);
			dialog.Text = "������. ��� ��������� � " + Pchar.questTemp.Relations.sum + " �������.";
			Link.l1 = "� ������"+ GetSexPhrase("��","��") +".";
			if(makeint(Pchar.money) < makeint(Pchar.questTemp.Relations.sum))
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "�������, � ���������"+ GetSexPhrase("","�") +".";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "������������, � ��� �����. ��� ����� ����� � ���� ����.";
			Link.l99 = "�������.";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, 25);
			AddMoneyToCharacter(pchar, -sti(Pchar.questTemp.Relations.sum));
		break;
        // boal <--
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			dialog.text = "��-�... ���� �� ����, ��� �������. �, �������, ����� ��������� ���� ������� � ���������� � "+ XI_ConvertString(Nations[sti(npchar.quest.relation)].Name + "Abl") +", �� ��� ����� ��� ������ " + FindRussianMoneyString(iSumm) + ".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "�����, � ���� ��� ����� ��� ������. ��� ��� ��� ���� ������.";
				link.l1.go = "relation3";
			}
			link.l2 = "���, ��� ������� ������� �����. ��������.";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "�������! � ���� ����������� ����� ����� ����. ������ ���� ��������, �� ��������� �������� 15 ���� ���� ���� ����� �������.";
			link.l1 = "������.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
		break;
		
		case "RelationYet":
			dialog.Text = "�� ��� ��� ����� �����������. �����, ��� ������ ���� �� ��������.";
			Link.l99 = "�������.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy":
			dialog.Text = "�������������� ������ ��������� �� ������ ��������?";
			for (i=0; i<MAX_COLONIES; i++)
			{
				if (sti(colonies[i].HeroOwn) == true && sti(colonies[i].isBought) == false)
				{
					sld = GetFortCommander(colonies[i].id);
					attrLoc = "l" + i;
					Link.(attrLoc) = GetCityName(colonies[i].id) + " - " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)));
					Link.(attrLoc).go = "CityPay_" + i;
				}
			}
			Link.l99 = "���. ������.";
			Link.l99.go = "exit";
		break;
		
		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "����� " + GetCityName(colonies[i].id) + ", ����������� " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)) + "Gen") + ", ����� ������ ��� ����������� ������� ������ ��������� �������� " + FindRussianMoneyString(iSumm) + ".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = "��, ���� ��� ������ ����������.";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "���, �������. �� ���������.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "������, ���������� � ������ �����. ������� ������� ������ " + GetCityName(colonies[i].id) + " ������ �� �����.";
			Link.l2 = "�������. ����� ��������.";
			Link.l2.go = "exit";
			Link.l3 = "��� ���� ������.";
			Link.l3.go = "relation";
		break;
		//������� ���
		case "SeekHVIC":
			dialog.text = "��-�, ������... �������, � ��� ��� ��� ���������� �������������� ���� ��������?";
			link.l1 = "� �������� ��� ��� ���� �����, � �������� �������.";
			link.l1.go = "SeekHVIC_1";
		break;
		case "SeekHVIC_1":
			dialog.text = "� � ���� �� �����, ��� � ����, ��� ��� ���������?";
			link.l1 = "�����, ������ ������ ������! �������� �� ���� �������� �� ������ ������?";
			link.l1.go = "SeekHVIC_2";
		break;
		case "SeekHVIC_2":
			dialog.text = "� ������������� �������� �����, � ��������� ����. ������, ��� ��� �����? ���� �� ������ � ��� ����, �� ������ ��� �����.";
			Link.l1.edit = 6;
			link.l1 = "";
			link.l1.go = "SeekHVIC_res";
		break;
		case "SeekHVIC_res":
			attrLoc = GetStrSmallRegister(dialogEditStrings[6]);
			if (findsubstr(attrLoc, "������" , 0) != -1 && findsubstr(attrLoc, "�����" , 0) != -1)
			{
				dialog.text = "��, �����... �� �����, �� ������ ����� ��� �� ��� �������, � ������. � ���� ��� ������� � ����������� ����. ������ �� ��������, ��� ��� � ��� � ���� ��������. ���, �� ������ ������...";
				link.l1 = "��� �������.";
				link.l1.go = "exit";
				LAi_group_Delete("EnemyFight");
				pchar.questTemp.LSC = "toOliverTrast";
				AddQuestRecord("ISS_PoorsMurder", "10");
				LocatorReloadEnterDisable("Marigo_town", "houseH2", false);
				sld = GetCharacter(NPC_GenerateCharacter("PoorKillSponsor", "smuggler_boss", "man", "man", 30, PIRATE, -1, true));
				sld.name = "������";
				sld.lastname = "�����";
				FantomMakeCoolFighter(sld, 40, 90, 90, "blade26", "pistol3", 100);
				sld.SaveItemsForDead = true;
				sld.Dialog.Filename = "Quest\ForAll_dialog.c";
				sld.dialog.currentnode = "Begin_PoorKill";
				sld.nation = HOLLAND;
				sld.city = "Marigo_town";
				sld.location = "Marigo_houseH2";
				sld.location.group = "sit";
				sld.location.locator = "sit1";
				sld.dialog.currentnode = "PKInMarigo";
				LAi_CharacterEnableDialog(sld);
				LAi_RemoveLoginTime(sld);
				sld.standUp = true; //�������� � �������� �� �����
				LAi_SetHuberType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				//����� ������ ������
				ChangeItemName("letter_LSC", "itmname_letter_LSC_1");
				ChangeItemDescribe("letter_LSC", "itmdescr_letter_LSC_1");
				ref sldd = ItemsFromID("letter_LSC");
				sldd.shown = true;
				//Boyer change #20170418-01
                pchar.restoreLSCTrustLetter = "letter_LSC";
				sldd.startLocation = "Marigo_houseH2";
				sldd.startLocator = "item1";
			}
			else
			{
				dialog.text = "������ �� �� ������, ��� ��� ����������!";
				link.l1 = "����, �������� �� ������...";
				link.l1.go = "exit";
				pchar.questTemp.LSC = "toLicencer_2";
			}
		break;
		case "SeekHVIC_3":
			dialog.text = "��, � ��� �� ����� �� ���� ������?";
			link.l1 = "� ��������"+ GetSexPhrase("","�") +" ��� ������������� ����������� ����-������� ��������!";
			link.l1.go = "SeekHVIC_4";
		break;
		case "SeekHVIC_4":
			dialog.text = "��?! ��, � ��� ��� �����?";
			Link.l1.edit = 6;
			link.l1 = "";
			link.l1.go = "SeekHVIC_res";
		break;
	}
}

