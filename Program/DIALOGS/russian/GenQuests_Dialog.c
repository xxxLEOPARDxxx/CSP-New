void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods;
	String sTitle, sGroup, sTemp;
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "����� ���. ��� �� ����� ��������? �������� � ��� Warship'� � �������� ����������, ��� �� ��� ��������.";
					link.l1 = RandSwear() + "����������� ������!";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // ������� �� ������ "������� � �����"
			{
				dialog.text = "� �� ����������� � ���� �������������. ���������� � ������ �������.";
					link.l1 = LinkRandPhrase("�������...", "����.", "�����������!");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // ������ �� ������ "������� � �����"
			{
				dialog.text = "�������������, � ���� �����, � ��� ������������!";
					link.l1 = "���� ����� " + GetFullName(PChar) + ". ��� ����� ����������?";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // ��������� ��� �� ������ "������� � �����" 
			{
				dialog.text = "���, ���� �����" + GetFullName(PChar) + ", �� ���-��?";
					link.l1 = "��, ��� ���...";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "���. �� ���� � ���-�� �������...";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // � ������� ������� ����� �������� ���������
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name + ", ������� ��� �������! ���� �� �� ��, ��� ������ ���� �� ����������... ��� � ���� ��� �������������?";
					link.l1 = "��� ������ �� �����...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "� �� �� �������"+ GetSexPhrase("��","���") +" �� ���������� ��������������.";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // ������� � ������� �� ������ "������� � �����"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // ������ ������ ������
				{
					dialog.text = "...��, � �������, ��� ��... �������, "+ GetSexPhrase("������","������") +", ��� ����� ������ ��� �������� �� ���� - ��� ���� �� ����� ��� ��������. ���, ����� " + FindRussianMoneyString(iMoney) + " � ������ �����������. � �� ������ ���������� � ����� ���������...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...��, � �������, ��� ��... �������, "+ GetSexPhrase("������","������") +", ��� ����� ������ ��� �������� �� ���� - ��� ���� �� ����� ��� ��������. ���, ����� " + FindRussianMoneyString(iMoney) + " � ����������. �� ����� ��� ��������� ����� ����� ���������!...";
						link.l1 = "�������. �� �������, �������...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "���?! ���, � �� ������� ����������� ��������, ��� �� �� �� ���... � �� ����� ��� ���� �������� ������!";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // ������ � �������
			{
				dialog.text = "���-���-���... ��� ��� � ���?! ������?! ��� �������� ������ � ���� � ����������� ��� ���������������...";
					link.l1 = "�� ����� �� ������! � ����� �������� ���� �� ����! �� ������ ��� ������ � ��� �������, � � ������ �� �����"+ GetSexPhrase("","�") +" �� ����������!";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "��� ��� �� ��� �������"+ GetSexPhrase("","�") +"? �������� ��� ����"+ GetSexPhrase("��","��") +" ��������?! �� ��� �����!";
					link.l1 = "�����...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "�� ��! ��, ��. ����, �� "+ GetSexPhrase("�������","�������") +" �������"+ GetSexPhrase("��","��") +", �� ����"+ GetSexPhrase("��","��") +".";
					link.l1 = "� �� ��������"+ GetSexPhrase("","�") +" ��� ��� ����������, ���� �� �� ��������� �� �� ������ ����������, ��� ��.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "����! ��-��, "+ GetSexPhrase("��������","�������") +", ������, �� ������� �� ���� ���� ������!";
					link.l1 = "� ���, ��������� ������� ��� ����������?..";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "��-��, � �����! ������ ��������, ��� � �������� ����������� �����...";
					link.l1 = "�� ���� ��������, ��������. �����-��, ��������.";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "��, ���! ������ �����, ��������...";
					link.l1 = "� � ���� ��� � ����"+ GetSexPhrase("��","��") +"....";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "�� ���� ������!?";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("����������� ���! �������-�� ��� ������� ���� ������� � �������� ��������� �������� ���������� �� ���� �����.",
					"����� ����������! ������ ���� ������ ����� �� ���������� ������� �����������!");
				link.l1 = "������������, ��������, � ������� " + GetFullName(PChar) + ". ���� � ��� ��������� ������������...";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "��������, � ������"+ GetSexPhrase("","�") +" ���� �� ����� �����, � � ���� ���������� ��� ������� ������ ���� ��������.";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("��, �������! ����� �������, ��� ��� ������ ��� �������� ����� � ����� � ��� ��������� �����!",
					"�������! ����� ����������, ��� �� ������ ���������� �� ���� �����!");
				link.l1 = "������������, ��������, � ������� " + GetFullName(pchar) + ". ���� � ��� ��������� ������������.";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "��������, � ������"+ GetSexPhrase("","�") +" ���� �� ����� ����� � � ���� ���������� ��� ������� ������ ���� ��������.";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("��������, "+ GetAddress_Form(pchar) +"! �� ������� ������� ������ ������������ ��������?","�� ���������� �� ���������"+ GetSexPhrase("��","��") +" �����"+ GetSexPhrase("���","��") +" ��������� �������� ������� ����� ����������� ������������?","���������"+ GetSexPhrase("��","��") +" �����"+ GetSexPhrase("���","��") +", ������� ���� ����� ������ ������������ ������� �� �������� � �������������.");
				link.l1 = LinkRandPhrase("������� ���.", "����� � ������, � ��� ��� ����� �������.", "����������. �� �� ���.");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("��� ����?", "���� �� ������?", "� ��� ����?");
				link.l2.go = "Convict_Begin";
			}
		break;
		
		// ��������� "�������� � ����� -�����"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "������ ���, �������. �� �� ����?";
			link.l1 = "� ���������� ������� ��������� " + pchar.GenQuest.Hold_GenQuest.Name + "?";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("� � ���� " + pchar.GenQuest.Hold_GenQuest.Name + ". � ��� ���� �����, ��������?","�� ��� �����. ��� ���� �������?");
			link.l1 = "� ������� " + GetFullName(pchar) + ", � ���� � ��� ���� ������������ " + pchar.GenQuest.Hold_GenQuest.CapName + ".";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(drand(3))
			{
				case 0:
					dialog.text = "� ��� ���?";
					link.l1 = "��������, �� - " + pchar.GenQuest.Hold_GenQuest.Name + ", � �� �� ������ ��� ����� " + pchar.GenQuest.Hold_GenQuest.CapName + "?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "�-�, ��������� ������ �� ���� ������ �� ����� ������� �����? ��� � ��� ��������� �� ���� ���?";
					link.l1 = "�� ���� ��� � ���� ��������� ������������... �� ����� � ���� � ������ ����� ������.";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "���, ������ ��� �����������.";
					link.l1 = "��� ����� ����������� ��������� �������, � ��� �� ����� � ���� � ��������� ��� ���������� � ��� �� �������.";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "��, ��� ������� � ������ ��������. ��� �� ��������?";
					link.l1 = "�� � ����� ������ ���������, ��� � ����������� ������.";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			dialog.text = "���������� �����, � - " + pchar.GenQuest.Hold_GenQuest.Name + "! �� ������ � ������ ����� ������-�� " + pchar.GenQuest.Hold_GenQuest.CapName + "?!";
			link.l1 = "��������, �������� ��������� ������...";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "���! � ��� �� � ��� ������? �� ���������� �� ��� ������� ���� �����������, ��-��-��?";
			link.l1 = "���, ����� �� �����������... ����� ������ �������� " + pchar.GenQuest.Hold_GenQuest.RansomSum + " ������� � �������� ������.";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "��� ��� ���������������! � ����� ��� ����� � ������ ������� �� ���� �����?! ��� �� ���, ����������, �����?!";
			link.l1 = "��, � ��� �� ������, ��� �� ��� ��������� �������. � ��� �� �����-�� ������ �������...";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("��, ����� �����! �� ��� �������� ��� ����������� �����! �� ��� �� �� ����� ������� �� ���� ��� � ����� � �������, ��� �� ����� ��� �����.",
				"�� �� �������� ��?! ���� ����, ��� �������� ����, ����� �� ������ ������, ��� ��� ������� ������� ������� � ������!",
				"��� �� ���! � ����� ����� � ���� ���� ���� ���������������?! �� �� ��� ������ �������.");
			link.l1 = "������ ��� ��� � ��������, ��� ����� ������� �� ������������� � ����� ������ �� ��������?";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "�������! �� ����� ����?! � �� �� ��� ��� ��������! � ������, ���� ����� ���� ������ ������� � ��� ������ ��� ��������, �� ��������� �����������.";
			link.l1 = "�� ��� �, � ��� �������� ������ ���... ���� ��������� ��������� �������� � ������ ��������...";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "��, � ��, ������, � ���� �"+ GetSexPhrase("��","�") +", ��� ��� ����������... ��� �, � � ������������� ��� ������.";
			link.l1 = "��� � �����������. ����� ������ ���������� " + pchar.GenQuest.Hold_GenQuest.RansomSum + " �������.";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "�� ���� ����������� ������: ����� ���� - ���� ���������� ������ �� ������� �� ����������� ������.\n" + 
				"������!!! ������! ���������� "+ GetSexPhrase("����� ��������","��") +" �� ���������� � ������������ � ��������� ��������� �� ���� " + NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation)) + "!";
			link.l1 = "��, '�������', �������� � �� ����...";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "�� ��� �� ��������?! � ���� ��� ���-�� ������?";
			link.l1 = "�� ����� � ���� � ������ ���� ���������� � ���� � ������.";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "�������-�������. � ������ ��, ��� ����. ��� ���? � ����� ����� ��� ����?";
			link.l1 = "������ ������� " + pchar.GenQuest.Hold_GenQuest.RansomSum + " �������. � ����"+ GetSexPhrase("��","��") +" ��������� ������ � ����, � ����� ��� ���� ����� ��������.";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "��� ������. � ������� � ���� ��������� � ����� ����������.";
			link.l1 = "��, ������������� ������ ����������. �������� � ����, ����� �� ������� ������� ������ ��������.";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// ��������� "�������� � ����� -�����"
		
		// ��������� "�������� � ����� -���������"
		case "Hold_GenQuest80":
			dialog.text = "������������, �������, �� ���� ����� ���� ��������������. ��� �������, ��� �� ���� �����.";
			link.l1 = "���������� �����, ���� �� � ���� �������� " + pchar.GenQuest.Hold_GenQuest.Name + ". � ������� " + GetFullName(pchar) + ", �����"+ GetSexPhrase("","�") +" ���������� �� ������ ����.";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "� ��� ��� �� ����, ������� " + GetFullName(pchar) + "?";
			link.l1 = "����� �� ���� �����, ��� ������ � ��� ����, �� ������� �� �� ����� ����������.";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "�� ��� ��� �� ���������?";
			link.l1 = "�� �����������, ��������, ��� ����� �������� � � ����� ����� �������, � � ����� �����������, ��� ����� ����� " + GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC) + " �������.";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "�� �� ����! ��� ���� �� �, ��� ���� ������ " + pchar.GenQuest.Hold_GenQuest.CapName + " ���� ��� ������ �� ���������! � ������ �� ���� �� ����, ���������� ��� ��� ����!";
			link.l1 = "�����, ������ ���������. � �� �� ����... �������� ��� ��� ����� � ������ ������, ��� ����.";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "��, ������ ��, ���� ���... � ������� �� �� ������? ����, ������, ������ � ������� ���� �������� - ������� ��� � ����� ������... ������ ������� �� ����...";
			link.l1 = "�� ���� " + GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_NOM) + " ��� ��� ��������� ��� ����... � ������ �������...";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "� �� ���� ������... ��, ���� �� ���� - �� " + pchar.GenQuest.Hold_GenQuest.Sum + " ������� � �����. �� ���� ��� �� ������ ���������� ���������.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "��� � ����, �� �����...";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "���, ���������, �� ����� ��� ������ ������ ����� �����. ��������...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// ��������� "�������� � ����� -���������"
		
		// ��������� "����������� ���������������"
		case "ShipWreck_1":
			dialog.text = "�������� �� �����, �������?! ��� ��� ����� �� �������.";
			link.l1 = "��� ��� ��� ����� ������.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("������������, � " + pchar.GenQuest.ShipWreck.Name + ", ������� " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")) + " '" + pchar.GenQuest.ShipWreck.ShipTypeName + "', �� ����� ��������� � ���� �������� �� ������. " + 
					"�� ���� ������� ������� �������� ���� ��������. ��� ������� �������� �� ���� ��������� ����. �� �������� � �������� �� ����� ��� ��� " + (5 + dRand(7)) + " ������",
					"������������, � " + pchar.GenQuest.ShipWreck.Name + ", ������� " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")) + " '" + pchar.GenQuest.ShipWreck.ShipTypeName + "'. ���� ����� ��������� �������� �������� ������. " + 
					"�� ��� �������� ��� ������� ��������� �� ����� ������, �� �� �������� ���������. �� ��������� ���� �������� ���������� � ���������� ������� �� ���������� " + (5 + dRand(7)) + " ������.");
				link.l1 = RandPhraseSimple("� ������� �� ��� ��������?", "� �������� �� ��� ��������������� ������?");
				link.l1.go = "ShipWreck_3";
			}
			else
			{			
				pchar.GenQuest.ShipWreck.Mutiny = true;
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "��, �������, ����� ���������, ��� �  ����� �� ���������... ������������, � " + pchar.GenQuest.ShipWreck.Name + ", ������� � �������� " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")) + " '" + pchar.GenQuest.ShipWreck.ShipTypeName + "'. ������ ������ ������� � ��������. " + 
					"���� ������� " + pchar.GenQuest.ShipWreck.BadName + ", �������� � ����� " + LinkRandPhrase(RandPhraseSimple("������� ����������","������� ������"), RandPhraseSimple("���������","��������"), RandPhraseSimple("�����","������� ���������")) + " � " + XI_ConvertString("Colony" + pchar.GenQuest.ShipWreck.City + "Dat") + ", ������ ������� �� ����. � ����� ��� �������� � ���� ��������� �����. ��� ��������� " + (5 + dRand(7)) + " ������ �����.";
				link.l1 = "� ���, ��� ������� ��������� � �����������?";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("�� ���� ������� ��������������� ������ ������ " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + ". ��������� ������� ��������� ��� ����� - �� ��� � ���������",
				"��������������� ���� " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + ". ��������� ��������, ��� � ������� ������, ��� � �������� ����� ����� �����...");
			link.l1 = LinkRandPhrase("��� �� �����������. �� ������ ����� ������ - ����� �� ��� ��� ��������� �� ����� �����",
				"�������... ��� �� � ����� �������, �� � ���� ������ ������� ����� �����, ����� ������� � ������.",
				"�� ��. ������� ������������, � ������� �����������...");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "���, �������! ������������ ��������� � ���������� ���� ���������� �����, �� ������� ��������� �������, � ������ ���, ��� ��� ������� �������� �� ��������� �������������. ������ ������ ��� ����� �� ��������� � �������� ���������,  ������ ��������������� ���� " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + ". �� ������-�� �� ���� ������� �����������... ";
			link.l1 = RandPhraseSimple("�� ��, ������ �� � ���������...","�� ��, ���� ������ �� ��������� � ���� ����� ������� �����...");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "�� ����������, ��������. � ������ � ����"+ GetSexPhrase("��","��") +" ������, ��� ��� �������� �� ��� ���������� �����?";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("�������, � ����� �������, ��� �� ����� ������� ������� ��������� ��������� ��������. ���� � ������� �� ��� �������� �����, ������� ��������� ��� ���������� ���� ������. �� ���� �� ����� ��� ����������.",
				"�������, �� � ������ ��������, ��� ������ �� �� ���� ���������. �� �������� � ������, �������� ��� �� ����� �������� ����� �����.");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "�� ��... � ���� ��������� ��� ���������?";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("���, ��� ����� ����, �� �� ������� ��� �� ������ ���������� ������, �� ������ ��� � ������. ������� ���� �� ������, �� ���� ����������� ������������ ���� ����� ������ �����...",
				"��� �� ����� �� �������� ��� ��������������, �� �� ������� ������� � ����������, ���� ���� ��� �������� �����. ����� ��������� �������, � � ������� �������� �������."), 
				RandPhraseSimple("����� ����, �� ������� �� ������� �����������. ������� ����� � �������, � � ���� ��� ������� ����������� ����� ��� � ����������.",
				"��������"+ GetSexPhrase("","�") +" ��� ������������, �� �� ������� ������� � ����������. � �������� ������� ��������."));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "��� ��, �������� ������, �� �����, ��� ����������� �� ����� ������������ ��������������� - ��� ������ �������? ��� ������� ������ �������� ���� ��� �� ����.";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "��� ��, " + GetAddress_Form(npchar) + " " + pchar.lastname + "?! ��������� ����! � ���������� ��������� �� ������� ���������! ...��� ��������� �����������. ������ �� � �� ����... ��� �����, ��� �������...";
			link.l1 = "��� ��... ������ ���� �� ������� ������� ��� �������������. ��� � ��������� ��� �������.";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "�� ����� �������� ���� ��� " + pchar.GenQuest.ShipWreck.BadName + "! ������� �� ������ �������� ��� ��� � ��� � ��� ��� �������� ��������� �� ����� �������?";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "� ����� ��������� " + NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)) + ".";
					link.l1 = "��� �, � ��������, � ������� �� ����� ����������. ������������ � ������.";
					link.l1.go = "ShipWreck_10";
					link.l2 = "��.  ��� ��������... ��� ��������� ������ ���, � ��� ���������� ��� �� ������ � ������� ������������ - � ���� �� ����� ��� � ���� ������ ������.";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "� �������!.. � ���� ��� ����...";
					link.l1 = "�� � ���� ���?! ��������, �� ����� �������� �� ������ ���������� �������...";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // �������� ����� �� ���� :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "�� �� ����� ����! ���� ��� ����� ���� � ���� ������������...";
				link.l1 = "��� �, � ��������, � ������� �� ����� ����������. ������������ � ������.";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "��.  ��� ��������... ��� ��������� ������ ���, � ��� ���������� ��� �� ������ � ������� ������������ - � ���� �� ����� ��� � ���� ������ ������.";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "�� ����� ������� �� ��������� ��� �� ������ ������! �� �������� ����������� �� ����� � ����, ���� ���� ��� ����� ������ ��� �����!";
					link.l1 = "� ����� ��� �� ��������? � ��� ���� �������� ����, ���� ��������� �� �����...";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "����������...";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "�� �� �� ������ � ���� ��� ���������! ��� ����� ������ ��� ����� ����� �� ������...";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "�����������, ��� � ���� ��� ������, ��� �������� ��������� � ��������, � ���� ������. �� ������ � ����� �� �����, � �������� ���� ��� ����� �� �����...";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "�����������, ��� � ���� ��� ������, ��� �������� ��������� � ��������, � ���� ������. �� ������ � ����� �� �����, � �������� ���� ��� ����� �� �����...";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "� ���� �������� ��� ��������, ������, ���� � ��������� �� �����. �� ��� ����� ��� ���"+ GetSexPhrase("","�") +" �������, ��� ������ ����-��.";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation) <= REPUTATION_NEUTRAL) // ������
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "�� ����� ������� �� ��������� ��� �� ������ ������! �� �������� ����������� �� ����� � ����, ���� ���� ��� ����� ������ ��� �����!";
						link.l1 = "� ����� ��� �� ��������? � ��� ���� �������� ����, ���� ��������� �� �����...";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "����������...";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "�����������, ��� � ���� ��� ������, ��� �������� ��������� � ��������, � ���� ������. �� ������ � ����� �� �����, � �������� ���� ��� ����� �� �����...";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // ���������
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "�� ����� ������� �� ��������� ��� �� ������ ������! �� �������� ����������� �� ����� � ����, ���� ���� ��� ����� ������ ��� �����!";
							link.l1 = "� ����� ��� �� ��������? � ��� ���� �������� ����, ���� ��������� �� �����...";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "����������...";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "�� ��� �� ������ ��� ���������?!.. �� �� ������ ������ ������� �����! �� ���������� ���� �����!";
							link.l1 = "�� ���� ������ � ���� �����, �������!!!";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "�����������, ��� � ���� ��� ������, ��� �������� ��������� � ��������, � ���� ������. �� ������ � ����� �� �����, � �������� ���� ��� ����� �� �����...";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "�� �����, � ��� ��� ������... ��� �, ��� ��� �����. �� ������� �� ������� �� ����� ���...";
			link.l1 = "��, � ���� � �� ���-������ ���" + GetSexPhrase("","�") + " ���������...";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "��� �... �� �� ���������� ��� ������... ����� ��������, ����� ������ � ����� �� ������ ���� ����� ������, ��� �� �������� �� ������� ����...";
			link.l1 = "��������. �� ����� ��� �������...";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterReputation(pchar, -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("�� ��������� " + pchar.GenQuest.ShipWreck.FoodQty + " ������ ���������.");
			Log_SetStringToLog("�� ��������� " + pchar.GenQuest.ShipWreck.MedicamentQty + " ������ ��������.");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "������, � ��� ��� ������... �� ������ ���, �������, ������������� ������ ��� �������� �������������� �����.";
			link.l1 = "� ���-������ ��������. �����...";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("�� ��������� " + pchar.GenQuest.ShipWreck.FoodQty + " ������ ���������.");
			Log_SetStringToLog("�� ��������� " + pchar.GenQuest.ShipWreck.MedicamentQty + " ������ ��������.");		
			Log_SetStringToLog("�� ��������� " + pchar.GenQuest.ShipWreck.AmunitionQty + " ������ ������.");
			Log_SetStringToLog("�� ��������� " + pchar.GenQuest.ShipWreck.RumQty + " ������ ����.");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","�"));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","�"));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("�������, �������, ��� ��������� ��� ������ �� �� ����...","���� �� �� �������? ��� ��� ������ ������ ���������� ����� ����������...");
			link.l1 = "������ ��, ��� �����. ��������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("��������, �������... ��� ����� ���������� � ��������.","��������... � ��������� ������ �� �������� ����� ���..");
			link.l1 = "��������. �� ����� ��� �������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			dialog.text = "�� ��� �� ������ ��� ���������?!.. �� �� ������ ������ ������� �����! �� ���������� ���� �����!";
			link.l1 = "�� ���� ������ � ���� �����, �������!!!";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "�������, �������! �������� �� ����� ����� �������. ��� �� ��� ��������, ����� ���� ������ �������� ������...";
			link.l1 = "�� ��� � ���������. ����� ���� ������� ����������.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")));
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "�������, �������! �������� �� ����� ����� �������. ��� �� ��� ��������, ����� ���� ������ �������� ������...";
			link.l1 = "�� ��� � ���������. ����� ���� ������� ����������.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")));
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "��� ��!.. ��� ��, �������! ��� �� ������� ������?! �� � ��� ��� ��������, ������� ���. ������ �� ������� ��� �������� ������������ � ������. ������ ��� �����, ����� �� ����� � ������� ������� �����������...\n�� �� � �������� ����� � ��� � ������� � � ����� ������� ������� �������� ���������... ������ �� �������� ��� �����...";
			link.l1 = "� ����, �� ������ ����� �� ��, ���� �� �������� ������. �� ���������� �� ����: ����� �� ��� �������?";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "� ��� �������� �����. �������, � �����"+ GetSexPhrase("","�") +" ��� ������.";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "���-���, � �� ����! ������� ���� �� ���� ��������� ���������... �� ����� ���! ���� � �����... � ����� �����. � ���� ������� ������, ��� ���� �������� � �� �������... � ������ ��� �������...";
			link.l1 = "���� ��! ��� �� ������� �����?.. �������� � ������.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Acc")));
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;							

		case "ShipWreck_13": // ����� �����������
			pchar.GenQuest.ShipWreck = "SailorsSaved";			
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterReputation(pchar, 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterReputation(pchar, 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("���� �� �� �������, �������? ��������� ��������� � �����.","��������, �������, ��� ����� ���������� � ��������.","�����, ��� �� ������ ����� ����������!");
			link.l1 = "������������. ����� ������ ����� �� �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "�������, ��� ������ ������. ������ ��� �������� �� ����... ��� ����� ������� �� ������ � ���, ��� �� ������� ����� ������.";
			link.l1 = "���! ��� �����?! ��� ������� �������� ��� ����"+ GetSexPhrase(", ��� �������� ��������","") +"!";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "�������, �������, �� �� ���������! �� ����� ������� ��������� �� ��� ����������.";
			link.l1 = "��� � �������! ��������� � ������...";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterReputation(pchar, -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
				LAi_SetImmortal(rChar, false);
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight")
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // ��������� � �������
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterReputation(pchar, 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterReputation(pchar, 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			Log_Info("���� ������� ����������� �� " + pchar.GenQuest.ShipWreck.Qty + " �������.");
			pchar.quest.ShipWreck_LocExit.over = "yes"; // ������� ���������� �� ����� �� �������			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("�������, �������, �� �� ���������.", "�� ����� ��������� �������, �������.", "�������, ������ �������, ��� ��� ������� �� ������ ������!");
			link.l1 = RandPhraseSimple("������� � ��� ������.", "������������. ����� ������ ����� �� �����.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "�������, ����� �� ������� ���������� ������� �����? �� ������� �� ��� ���� - ����� � ��� ������ �� ��������?..";
			link.l1 = "� ��� �� ��� � ���� ��������� ������?";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "� ��� � ���� �������?.. �� ������� ���� ������. � ���������� ����, ��� ���� ��� �������! ��, ���� �� �������� ��� ������� ������� � ��������� �� ��������, �� � ����� ������ ��� �� ���������� �����, ������� ������ ��������� ���� �������.";
			link.l1 = "�� ������, ��������, ��� �� ������������.";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Dat")));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "�� �� ���� ��� �����������? ���� ����, ������ � ��������� ���������, ������ � ������� ��������.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "������, ������� � �������. ������ ����� ���, - �� ��������! � ���� � ���� ������!";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "�� ������ � ��� ������. � ���� � ������� � ����� ����������� �������.";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "�����, �������� � ������, ������ ��� ����-������.";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "��� �... �� �� ���������� ��� ������... ����� ��������, ����� ���������� ��������� ��� ���� � ��������� ��������� �� ����� ���������� �����. �������, � ������ ������� ��� ��-���� ������� ��������� �� ������� �����...";
			link.l1 = "��������. �� ����� ��� �������...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "������� ��� ��������, ������� " + GetFullName(pchar) + "! �� ��� ��� ������� �������, ��� ����� ������������� ����� ������������� � ���� ��� ���� ������� � ��������� ����� �� �����, ��������� �������� ��� ���� ������. �� ����� ���� ����� ������� ��������, ����� ����������� � ������� ���.";
				link.l1 = "������� �� �������. ���� ������������� ����� ������!.. �������� ������� " + pchar.GenQuest.ShipWreck.Name + " � �� ����������� ��� ����� � ������� �������.";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "�������, ������� ��� �������. �� ��� ��� ������� �������, ��� ����� �������������� ����� ������ �������������, ������� �� ����������. �� �����������, �������� ���� �������� ������� � ���� ����� ���������������.";
				link.l1 = "����� �� �� ������... ��� ������ ������ ���� ������. �� �� ����� �������. ������� � ��������.";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+drand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "�������, ������, ��� �� ����� ���� ����, ������� ������� ��� ��� ��. ����, ��� ��� ����� ��� �������������. ����... ��� �������� ���� �������, � ����� ��� � ��� ����������� �����. ����� �� ������� ��� �����.";
			link.l1 = "�� ��� ����� ��� �������� �� ������. ����� �������.";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString(pchar.location + "Acc"));
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("�������, ��� ��� �������?","������� �� � ��������, �������?"),RandPhraseSimple("�������, ��� ������?","�� ��� ������ ��������� �� ������?"));
			bTemp = !GetCharacterItem(pchar, "map_part1") || !GetCharacterItem(pchar, "map_part2");
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "���...";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("��� ���...","����� �������, ����� ������? ���������� ������...","�, �������!..");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("��, �������, �� ��� �������!","��� �� ����� �� �������� �����, �������?","� ����� ����� ������?");
			if(rand(100) < 70)
			{
				link.l1 = "���. ���������, ������� ����� ����� � ������� � ���� �� ��� ������ �������. � �� �������"+ GetSexPhrase("","�") +" � ����� ��������� �����!";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("� �� �������, ��� ��� ����� ������ � �������?","�� ����� �� ������������� ��� ������������������ ���������.","�������, ��� ��� �� ������� ������?"), 
					LinkRandPhrase("�� � ���� ���������� ������ �����...","������ ��� ��� ������...","�� ������ ����������, ����� ����� �������... � ������ ����� ���..."));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "�� ��� �� ������?.. �� ��� �� �������?! ����� �����������!.. ������ � ����� ��� ������� �����!";
			link.l1 = "��, �� ��� ����������...";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("���! ��� ����� ������ �������.","������ ����, ����� ����� ���� ���������, ����� ��������� ��� ��������!"), 
				RandPhraseSimple("� ������ �� ����� �������! �� ������� ��������� ���� � ������!","���, �������, ��� �� �����. �� ��� � ������."),"� �� ������� ��������� � ���� ���� �����!");
			link.l1 = "� ��� �� ����, �������� �� ��� �����-������...";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, true);
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.CrazyRec"))
			{
				pchar.GenQuest.CaptainComission.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.CrazyRec")) DeleteAttribute(pchar,"GenQuest.CaptainComission.CrazyRec");
			dialog.text = "���! ��� ����� ����� ����������� ��������!.. �� ������! �������� ������... � ��� ���������... ��-��-��\n��! �� ��������� ��� ��������, � �, ��� ����������, ������ ��������� ���. ����� ��������� �����, ������ �������� ���� � ����� ����������, �� �� ������ � ��� ����������� ����, ����� �� ���������... ����� ����� ��� ����� �����... ��� ����? ��, �� �����. ������� ����� �������� ��������� ���� ������������ ��� ���������� �����������.";
			link.l1 = "���������, ��� �� �� �����? ��������� ��� ��� ��������?";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "�������!.. �� ������� �� ���! �� ���� �� - � �� �����. ��� ����� �� ���� ���������� ������, ����� �� ����� ������� ������ �� ������. ����� � ������ ������������ ������ � �������� ���� � ������... �� ������� ����������� ����� ����, �� ������� ����������� ������ ��! ����� ���������� �� ������� �����, � ��������...";
			link.l1 = "��� �� ���� ���� ��� �������� �������� �����...";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "��� �� ��������?.. �� ��, �� ����������... ����������, � ��� ����� �������? �������� ������, ����� �����-�� ������� � ����� �� ���, � ��� �� ����������\n� �����, ��� �����, ������ � ��������. �� ��� �������� ����� �������: �� ��� ������� ������ ����� - ���� � ������! ������, �� ���� �� ����� �������, ��� ���� �� ������ ���������. �� ��-��, ��� �����"+ GetSexPhrase("��","��") +" ����"+ GetSexPhrase("�","���") +", ��������� �� ����������, ��� ��� �� ������... � ����������, ��� � ���� ����� ��������� ��������� ������ �-�-�...";
			link.l1 = "�������, ��������. ���� ��� ��� ��������, � �� ����������. ��������, � ����� �������, ��� �� ������ �� ��������...";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			if (!GetCharacterItem(pchar, "map_part1")) 	GiveItem2Character(pchar, "map_part1");
			else 										GiveItem2Character(pchar, "map_part2");
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("�������, ��� �����-�� ���� �� ������� ���������. ������������, ��� ������� ��������� � �������� �������� ��������� �� ������� �� ��������...",
				"������������, ��� �� ������� ��������� �����-�� ������. ����� � ����� ������ � ���� ��� �� ���������� ��������..."),
				RandPhraseSimple("�������������, ������� �����-�� ������� �������� � ����������� ������� ������� ���������� �� ���� � �����������. ������, ��� ��� ������ ����� ������� ����������� ��������.",
				"������� � ������ ��� �������: ������� ������-�� �������, ������� ��������� ��� ����� ������ � ������������ ��������."),
				"��� ������� �����-�� ���� �����, �������, ��� ����� �� ��� ����� ������..."), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("�������, ����� �������, ��� �� � ��� �� ������! ��� �� ��� �������� �� ���!..","�������, ������� ���� �������� ������? ��� �� ��������, ����� ��� ������� ���������! ��������� ��� ����� �����������...");
			link.l1 = "����������� " + pchar.GenQuest.ShipWreck.Name + "! �� ��� � ���"+ GetSexPhrase("","��") +" ������� ����� ������ � ����� ���������?.. ���� �� ��� ���������?";
			link.l1.go = "ShipWreck_45";
			link.l2 = "����������� " + pchar.GenQuest.ShipWreck.Name + "! �����, � ���� ������ �������. �������������� ����������, � � �� ����� ����� ��� �� ����.";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "��� �� ����� ���� ����, ���� �� �������� �� ����� ���������� �����... ��������� ������ ��������?";
			link.l1 = "������������. ����� ���� ������� ����������.";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterReputation(pchar, 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian15");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "������� ���, �������. �� �� ���� ���������, �� �� ����� ������� ��� � �����.";
			link.l1 = "�� ����� �������������... ��������.";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "������ ����� ���� �����?";
			link.l1 = "� ����"+ GetSexPhrase("��","��") +" �������� ���� ������ �� " + pchar.GenQuest.ShipWreck.Name + ". ������ ������?";
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "���� � �� ������ ��� ������� ������... ������ ������ ����� �������������� �� ��� ����������...";
			link.l1 = "���... � ��� ����� ��� �������...";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // ������ �����
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "�������� ������, �������! �� ��� � ��������������, ������� ��� - ���� ���.";
			link.l1 = "��, �� �����. ��������� � ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "����������� ���, ������� " + GetFullName(pchar) + ".";
			link.l1 = "��, ��� ���� ���� �������?";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "��-�, �� ���� ����� �� ���������, ��� � �. ������ ��� ������� ��� ����� ��������� ��� ����..";
			link.l1 = "�� ���������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// ��������� "����������� ���������������"
		
		// ��������� "���������"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterReputation(pchar, -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "�������, �������� ��������� �������� - ������ ��� �������, ��� �� �����. �� ���� ������������� �� ��������� �������� ��� ��������������� �����, � ��������� � ��������� ����� ������.";
					link.l1 = "� ��� � ��� �� �������������� �����?";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "�������, �� �������� ��������� ����� ��������? �� �� � �� �������, �� ����� ���������.";
					link.l1 = "����� ��������? ������ ��� ���������� - ��� � ��� �����.";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "�������, �� �������� � ���������� - ���������� ���� �������� �������� �� ����� " + XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen") + ".";
					link.l1 = "���-�� �� ������� �� ����� ����������� ������ ����������.";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("� �� �������� �� �����.","��� � ���� ������� �� ������ ������.","� �� ����� �������� ������� ����.");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "������ ��... � " + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")) + ". ���� � �����, ������ ������ ����������� - ����� �� ����� �� ��������...";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "��� �� � �������� ����������� ������?";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "� �������������� ��� �����������?";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "�� �� ���� ��� �����. ��, �������, ������, ��� � " + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")) + " ������, ������ ��� �� �������� ��������, � ������ �� �� ��������...";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "�� �������, ��� � ��� �����, � ������-�� ���? ��� � ������ ���������, ���� ������� �� ��������?";
				link.l1.go = "Convict_12_1";		
				link.l2 = "������, ������� �������?";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "� ���� � ������ ��� �� �������� �������� - ������ �� ����� � �������� � ����������.";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(drand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "� ��� �� ��� ������ ���������? �� �� � �� ����� ��������� ��������, ������ ��� �� ��� ������ ������?";
				link.l1 = "� ������, ���� � ������� ������� � �� ���� ������ �� �������.";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "�� �� ��� � �������� �������� ������������. ��� ����� ��� ������ ��������, ���� �������� ������.";
				link.l1 = "������� ���� ��� ������, ���� ��� ������������� �������.";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "��, �� ����... ��� ���� ��������, ������� �� ���-������ ��� ����.";
			link.l2.go = "Convict_12_1_End"; // ����� �� ���� � ��������� ������
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "��������, ������� - �� ���������! �� ��� � " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " � ��������� �������������, ���� ��� �� ��������, � ��� " + pchar.GenQuest.Convict.ConvictQty + " ������� ���� �� �������.";
			link.l1 = "��� � ������. ����� ��������� ���� ���� ��������, " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + " ����������. ����� � �������� � ��� ��� �������. ��� �� �����������.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = drand(3);
			if(iTmp <= 1)
			{
				dialog.text = "������� �������! ������� � �������, ���� ����� �������� � ������ �� ��������. ��������������, �������, �� ������ ��� �������...";
				link.l1 = "� ��� �������� ����������.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "��� ��� �����! �� � �� ����� ��� ������ ����� ���������. ���������, �������, �� ������� ������ ������������ ��� ������, ��� �� � ������� ������� �������. �������� ��� � ��� ������� �����.";
				link.l1 = "�������, ������� ������. ����� ���.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "��� ����� ����� ������� ��������, ������� �� ������ ������������ � ��������, ������ ��� �����, ��� �� ����� ��������!\n������� ����� �� ������, ��� �������������� ������� � ����� ���� " + MerPrm.QuestGoodsIdx + ". ���� �����, �� �� ����� ����� �� ����� ������� �������� �������� ����� - '" + MerPrm.ShipName + "'... ������� ���� ��� ������ " + MerPrm.nation + ". ��������, ��� ����� ��� �����������, ��-��.";			
				link.l1 = "�-��? ����� � ����������... ��, ��������, ���������.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "�� ���������, ��� �� ������� �������? ������� �� ������ - �� �� ���������� �����.";
			link.l1 = "300 �������.";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000 �������.";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3000 �������.";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "��������������, �������, �� ������ ��� �������...";
			link.l1 = "� ��� �����.";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(drand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "��� ��� �����! �� � �� ����� ��� ������ ����� ���������. ���������, �������, �� ������� ������ ������������ ��� ������, ��� �� � ������� ������� �������. �������� ��� � ��� ������� �����.";
				link.l1 = "�������, ������� ������. ����� ���.";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "��������������, �������, �� ������ ��� �������...";
				link.l1 = "� ��� �����.";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(drand(1) == 0)
			{
				dialog.text = "��� ��� �����! �� � �� ����� ��� ������ ����� ���������. ���������, �������, �� ������� ������ ������������ ��� ������, ��� �� � ������� ������� �������. �������� ��� � ��� ������� �����.";
				link.l1 = "�������, ������� ������. ����� ���.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "��� ����� ����� ������� ��������, ������� �� ������ ������������ � ��������, ������ ��� �����, ��� �� ����� ��������!\n������� ����� �� ������, ��� �������������� ������� � ����� ���� " + MerPrm.QuestGoodsIdx + ". ���� �����, �� �� ����� ����� �� ����� ������� �������� �������� ����� - '" + MerPrm.ShipName + "'... ������� ���� ��� ������ " + MerPrm.nation + ". ��������, ��� ����� ��� �����������, ��-��.";
				link.l1 = "�-��? ����� � ����������... ��, ��������, ���������.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterReputation(pchar, -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(drand(1) == 0)
			{
				dialog.text = "�� ����, �������! ������ � ��� ���� ��������� - ������ ��� �����, �� � ������� �������-���������...";
				link.l1 = "������� ���� ������ � ������������, ���� ����.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "��� � ��� ������ - ���� ������� �� ������, � ����� �� ��������. ��, ��������� ����������!";
				link.l1 = "��� ������ ��������! � �� ��� - ����������� ��������!";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "��, �� ������� �� ������, �� � ��������� �� �������� ��� �� � ����... ������ ��, ��� �� �������� ������ ��������.";
			link.l1 = "���� ��� �� ����� �������?";
			link.l1.go = "Convict_13_1";		
			link.l2 = "��� ��� ���... �� � ���� ��� ��������� ��-�� ��� ������. ��������.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "� ��� �� ��� �����? �� � � ��������� ���������. ������� ��� ���� � �������� " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " ������� ������ � ������ �������, ������ ��� ����� ��������, � ��� - " + pchar.GenQuest.Convict.ConvictQty + " ������� � ������� �������.";
			link.l1 = "� �� ��� � ������� �� �������? � �������� � �� ����"+ GetSexPhrase("","�") +", �� � ��������� ����� �� ������.";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "�� �� ���������� ���-��� � " + GetStrSmallRegister(XI_ConvertString("MineType" + pchar.GenQuest.Convict.MineType + "Dat")) + ", ���� �� ������ ����� �� �����������, ��� ��� �������� �������. ������ ������ ����� �� �����. � �� ��������� �������� ������. �� ���� �� �������...";
			link.l1 = "�� ������, ����� ���� " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat") + ". ����� � �������� ����� ��� ��������... � �� ��������� ���� ��������!";
			link.l1.go = "Convict_11_4";
			link.l2 = "���, ������� �������, � ����� � ��� �������� - � �� ��� ������ ��� �����? ������ - �� �������"+ GetSexPhrase("�","��") +" � ��� � ���� ����.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "� ���������� �������������, �����"+ GetSexPhrase("���","��") +" �������. ��� ���� ��� �������, � � ����������� ���� ��� ��� ������ �������� - � ������-�� ��������������, ��-��.";
			link.l1 = "��� � ������. ����� ��������� ���� ���� ��������, " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + " ����������. ����� �������� � ��� ��� �������. ��� �� �����������.";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "��, �����"+ GetSexPhrase("���","��") +" �������, ��-�� ������� ������� ������. � ����� �� ������ �������� ����������?";
			link.l1 = "� �� �����... ���� �� �������� � ���� - ������ ������ ����������.";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation) < 11 || makeint(pchar.reputation) > 79) //����. ���������� 90
			{
				dialog.text = "��, �������, � �� ��� ���������...";
				link.l1 = "������. ���� ������ ����, �� �������� �������. ��������.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterReputation(pchar, -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "� ��, ������� - ����"+ GetSexPhrase("��","���, ��� � ��������") +". ������ �������� � ����������� ��������. �������, ������� ��� ������ ��������?";
				link.l1 = "�� ��, �����, ��� �������� ������?! ��, ����� ���������!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", pchar.GenQuest.Convict.ConvictQty);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));							
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","�"));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "���� ���-���. �� � ������� � �������� �������� ��������, ������ ���� ��-�� ����� ����� ��������� - �������� ����������� � ����. ������ " + PChar.GenQuest.Convict.ConvictQty + " ������� ������ � ���������.";
			link.l1 = "�������� ��������������, �������, ��� �� " + FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum)) + " � ���� �� ������.";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "� ��, � ����, �� �� ������� �������. � ������� �� ��� ������?";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "� ����� � ��� ���� �����? ���� �� " + FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum)) + "...";
			link.l1 = "����� ������� " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc") + ". ����� �������� ������ �� ���� ������.";
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "���� �� �� �����? ��� ���� ��� �������, �� ��� � " + GetName( NAMETYPE_NICK, pchar.GenQuest.Convict.PirateName, NAME_ABL) + " � " + RandPhraseSimple("����������","��-�����") + " ����������, ���� ���� �� �������.";
			link.l1 = "��� � ������. ����� ��������� ���� ���� ��������, " + XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation) + " ����������. ����� � �������� � ��� ��� �������. ��� �� �����������. ";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("��","���"));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", pchar.GenQuest.Convict.ConvictQty);
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));			
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("��, �������, ������ ���"+ GetSexPhrase("","�") +" ������� � ������ ������� �����"+ GetSexPhrase("","�") +", � ��� � �������� ��������� - ��� �� �������� ���� ��������.","�������, ������ ��� � �������� ������ ����������. ��� ��� ����� ����� �����."), 
											RandPhraseSimple("��-��, ������ ����� ����� ����������. �����, ����� ��� ��� ���� ��������.","����� �����, ��� ������� �� ������ - �� �������� ��� ������ ����� ����������� �������."));
			link.l1 = LinkRandPhrase("�� �� ����� ��������� ���� ��������?! ��� � ���� ������ ���� �������!","�� �� ��� �������� �������?! ��, �������!!!","������� ��� ��? ������ � ���� �����-�� ��������!");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(pchar.location, true);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("�� ���, �������? �������� ��������?","������������ ���, �������. �� ���, ���� �������?","������������ �������, � �� �� ��������������. �� ������ ������?");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "��, �������� ���� ���������. � ��� ������ �� ��������. � �������"+ GetSexPhrase("","�") +" �� �� " + pchar.GenQuest.Convict.ShipPrice + " �����, ��� ��� � ��� " + sti(pchar.GenQuest.Convict.ShipPrice) * 2 + ", ��� � ������������.";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "���, � ���������"+ GetSexPhrase("","�") +". ������� ���� ������� ���������. ��������� ����������...";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "� ��� ��������?! � ��� �������� �������, �� �� ������� - �������� ������ � ���� ��������� �������������. �� ��� ����� ��������. �� ������������ � ���� ����������� �������� - �� �� ������?";
					link.l1 = "���, �������. �������� ��� ��������. ������ �� ����������� � �������� ���� - ��� � ���� �������� ��������.";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry17", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "�������, �� ��� ��������, ��� ������ � ���� ����� �� �������. � ��������� ��� ��� ������ ������. � ���� � ��� ���� ������, ��� �� � ������� ������� �������, �������� ��� ������������ ��� ������ ����� �����. ��� ���������...";
					link.l1 = "��, �� �����. ���� ������������� ����������. ��, �������, � ��������.";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "����� ��� ������� �����, �������? �� � ��� ���� �� ����������. � ��� ��� ���� ����� - ������ ������. ��� ��� �� ����������. �� �������� - ����, �����... ��������, ������.";
					link.l1 = "��� ��� �� ������������. ��� ����� �� ����� ���� ������, � ������ ���������� ����� ��������.";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterReputation(pchar, -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("�� ���, �������? ����� ���������?","�������-��, � �� �� ������������� - ������, ��� �� ����������.");
			link.l1 = "� ���� ���������� �����. ������� ��� ������ ������� ��������.";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "��������� � ������, � ���� ���� �������.";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "��������� � ������, � ���� ���� �������.";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "�, ���� ����!.. ������ ��� � ������� �� ���� ������"+ GetSexPhrase("","�") +"?! ��� ���� ����� �� �������!";
				link.l1 = "��� �� ������?! ���� �������?!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "��� � ��, �������"+ GetSexPhrase(", ��� ������ �������?","?") +" ���� ������ �� ������...";
				link.l1 = "��-��, �������� � ����...";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterReputation(pchar, -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("��� �������, "+ GetSexPhrase("������ �������","����� �������") +".","������� ����, ������� - ������, �� ����� �������"+ GetSexPhrase("","�") +".","�������������� �� �������� �����������.");
			link.l1 = LinkRandPhrase("�� ��� ������, �� � ��� �������.","���� �� � ������������.","������ �� �����, ��� ��������������.");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "�������-�������! ����� ����� ���� �������! ���, ������� ����������� ����� � ������� ������� � ���� ��������� �������������.";
					link.l1 = "����� � ���... ��������� ����������.";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "�������, �� ��� ��������, ��� ������ � ���� ����� �� �������. � ��������� ��� ��� ������ ������. � ���� � ��� ���� ������, ��� �� � ������� ������� �������, �������� ��� ������������ ��� ������ ����� �����. ��� ���������...";
					link.l1 = "��, �� �����. ���� ������������� ����������. ��, �������, � ��������.";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "����� ��� ������� �����? �� � ��� ���� �� ����������. �� ��� �������� - ����� ������, � �� ��� �������.";
					link.l1 = "�� �����. ��������, �������, � ������ �� ������.";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Abl"));		
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Abl"));		
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// <-- ��������� "���������"
		
		// ��������� "����� ��� ������" -->
		// ������� � ��� �� ������
		case "ReasonToFast_Hunter1":
			dialog.text = "�� ���� ���� ��� "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " �������...";
			link.l1 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " ���� ��� ���� ���, ��� � ������� ����������. ���, ���� ������ ������.";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "� ����� �� ����� � ���������� ���, ������ ������ �� ����"+ GetSexPhrase("��","��") +".";
			link.l1 = "� ��� � ����?";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "������-�� �����, ����� �� ���������� ����� �������� ������?";
			link.l1 = "��� ����!...";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "�� �� ��� � ������ - ������� �����...";
			link.l1 = "���-���... � ����� "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ", ��� �� � �������� ��������.";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //��� �� �����������
			pchar.GenQuest.ReputationNotChange = 1; //��������� �� ������
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// ��� � ����� ���������� �������
		case "ReasonToFast_FightCap": 
			dialog.text = "� �� ������"+ GetSexPhrase("�� ������� �����","��� ������� �����") +". ���� ����, ���� � ����� ��������� �� �������� " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
			link.l1 = "�� ���������, ���� �� ��� �� ����������... � �� ����� �� ��������, ������?";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "�� ���� ��?! � ��� ������ � ������� �������������!";
			link.l1 = "�� ���� �� ����� �������. �� ��������, ������� �� ���������. ��� ��� �� ����� �������, � � ������ ���� ���������� �� ��������.";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "��... ����� �������?";
			link.l1 = "� �������� ���� ���"+ GetSexPhrase("","�") +"...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// ������� � ������ � ����������
		case "ReasonToFast_Lakey":
			dialog.text = "�� �� ����, "+ GetSexPhrase("�����","�����������") +"?";
			link.l1 = "���, � �� ����������� �������������� ������� �����������, ���������� ��� �������� ��������� ����������.";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "� ������"+ GetSexPhrase("","��") +" �������� �� ��������� ���� �����.";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "��. ���� �������� ���� � ���� ����������!";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "� ��, ��� ������� ������� � ����� �������� ����.";
			link.l1 = "�������������...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "�� �������� ��������� �� ��� ���!";
			link.l1 = "�������, ��������!";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "���... " + pchar.questTemp.ReasonToFast.password + "?";
			link.l1.edit = 1;			
			link.l1 = ""; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "���� ��� �� �������, ����!";
			link.l1 = "����, ��������!!!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "������, ��������� ��������, � �������!";
				link.l1 = "� �����, ���� ���� ���� ������� ����.";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "�-�, ��������, ��� ����� ������ ���������.";
				link.l1 = "����, ��������!!!";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //������� ������
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("�� �� "+ GetSexPhrase("���, ��������! ������, ����� ���","�������! ������, ����� ��") +"!!!", "��� ��� ��! ���� � ����������, � �� ����� � ������ � �������! ����� "+ GetSexPhrase("����","�������") +"!!!", "������! ������!!! ����� "+ GetSexPhrase("����","�������") +"!!!");
			link.l1 = "�-���, ������!!!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// ��������� "����� ��� ������" <--
		
		// �������� � ��������� ������������ �������
		// ����� �� �������
		case "ShipSituation11": // ������ ��� ��
			dialog.text = RandPhraseSimple("������, "+ GetSexPhrase("��������","�������") +"! � ���������� ���� ������� - ����� ����, ������� � �����-������. ������ ����� ����� �����, ��� ����� � ��� �������!","���� ������?! � �����-������ �����! ������ ����� ��������� ����� - � ������ ������!");
			link.l1 = RandPhraseSimple("�� ��, �������! ���� ���� �� ��������. ������, ����!","����, ����� ����� � �������, � �� � ������ �����?!");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("���� � ��, ���� ���� ������... �����, ������� ��� - ������ ���. � ���� ������� �������!","������� ��� � ������������ ������ - ������ � ������ ����� �� �����. ������� ���� �������, ����������"+ GetSexPhrase("","����") +"!");
			link.l1 = RandPhraseSimple("�� �� ����!!!.. ���� ������!!! ������!","��� �� ���� ��� ���������!.. ������� ���������! ����������!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // ������� ������� (�� �������)
			dialog.text = "���?! �������, �������"+ GetSexPhrase("","�") +" ��������?! ���� ���������. � ����� ����, ������� � �����-������ - ��� ��� ���" +GetSexPhrase("��","��") + " ���� � ����� ������� �� ����.";
			link.l1 = RandPhraseSimple("�� ��, �������! ���� ���� �� ��������. ������, ����!","����, ����� ����� � �������, � �� � ������ �����?!");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("� �������� �������, �� ��� �� ��������� ���� ��� �������� �������. ������, ����� � ������ �� ���������, ����� - ������� �� ������.","������� ������ ��������� � ��������, ��� ��� ���� ������ ������. ������, ������ ���...");
			link.l1 = RandPhraseSimple("�� �� ����!!!.. ���� ������!!! ������!","��� �� ���� ��� ���������!.. ������� ���������! ����������!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // ���
			dialog.text = RandPhraseSimple("�� ���, ����������"+ GetSexPhrase("","����") +"?! ����� ���������� � �����������! � ����� ����, ������� � �����-������.","��� ��, �����"+ GetSexPhrase("���","����") +", � �����"+ GetSexPhrase("��","���") +"! ������ ��� ���� �� ����������� - � ����� �����-������.");
			link.l1 = RandPhraseSimple("�� ��, �������! ���� ���� �� ��������. ������, ����!","����, ����� ����� � �������, � �� � ������ �����?!");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("� ����� ���� ����������. ����, ������� ���������� ��������. �� ������, �� ���� ������ ���� �������, ��� ���� ����� �����. ������� �������!","������ ��� ���������� ���� �������? � ������������, ��� �������"+ GetSexPhrase("���","��") +" �����"+ GetSexPhrase("�","����") +". ��, �� �����, � �� � �������. ���� ������ ����� ������ ����� ���������. ������, ������ ����� �� �����...");
			link.l1 = RandPhraseSimple("�� �� ����!!!.. ���� ������!!! ������!","��� �� ���� ��� ���������!.. ������� ���������! ����������!");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// ��������
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("����, �������! ���� ������� ���� ���� ����.","�������, �������! �����, ���� ��������� ����� ��� ������.");
			link.l1 = LinkRandPhrase("��� �� ������ �� ����� ���?!","� ��� � ����"+ GetSexPhrase("��","��") +" �������� � ����������?","� ��� ����?! ������ ��������� �� �� ��� ��������?");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "�� ����� ��������. � ��� �� ����� �������� ������� �������� �������. ��� ��� ��� �� ��������...";
			link.l1 = RandPhraseSimple("�� ��, ������ �����! ������ �� ������� ������, ��� �� ������� ��������?!","��� �� �� ������� ����� �����? �� ����� ������ ���� ������, ��� �� ������� ��������!");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "� ��� �� ���� �������� ����. ������� � ��������� �� �����, ���� ���� � ����� ����������� �� ��� ���� �������!.. ��� ������ � �����������. ������ ����������� ��� ������� ����.";
			link.l1 = RandPhraseSimple("��, �� ��� �� ��� ��������!..","� ���� ������������"+ GetSexPhrase("","�") +", ��� �� ��������� ������. � � ��� �����...");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("�� ����� � ������ ������� � ���� ������� ����� - ����... ���� ����� ���� ���? � ����� ������� � ����� ������� ������.","�� ����� ���������� ��������, �� ���� ��� ��� �� �����������. � ����� �����... �������, ������� ���� ��������.");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // ��������� ��� �� ������� �� ������ �� ����������� ����� � ������ � ���������
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // ��������� ��� ������� � �����
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// �������� � ��������� ������������ �������
		
		// ��������� "������ � ��������"
		case "EncGirl_Lover":
			dialog.text = "������������, �������, ��� �������, ��� �� ���� �����.";
			link.l1 = "����, ���� �� � ���� " + pchar.GenQuest.EncGirl.sLoverId + ".";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "��, ��� �. � ��� ���-�� ������?";
			link.l1 = "�� ����, ��������� ��� ����� ��� ����, �� � ������"+ GetSexPhrase("","�") +" " + pchar.GenQuest.EncGirl.name +". ��� ������� �� ���� � ������ ��� ���� �������� �� �������.";
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "�������, � ����, ��� �� ���� � ����������... � ������ ��� �������, �� ��������?";
			link.l1 = "Ÿ ����� ������, �� ���� ����������.";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "��, ���, ����� ��������� ������! �������, � � ����� �������� ���������... � �����, ���� ������� ������� ��� �� " + XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland + "Acc") + " � ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity) + ", �� � ���� ������ ���������� ��� ����� - � ��� � �� ����� ������. � � ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity) + " � ���� ������������� �������� � ���� �� ������...\n������ ���, �������� ����� ���� ������ ���� � ������� �������� � ����� ��� ������������. �� ���, �������?";
			link.l1 = "...��������, � ���� ������ ������ ������ �����. ���� ������������ ���� �������� �������� �� ����� �����, � ������ ��������� ����� ����� ������� �����. ���� �� ������ ��� ����������, � �� ������ ��������� - ������ �� ���� �������.";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "��, ���������! ��, ���� ���������, � ��� �������? ������ ���� �� ��������� ��� �������������?.. ������ �������!";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("�� �������, " + pchar.GenQuest.EncGirl.name + " ������� � ���������� ��-��� �����. �� �������� ���� ����� � ��������� ���������. � �� ��� �������� � �������� - ������������ �� ������ ������, ������� ���� ����� ��������� �� ����� �������.",  
				"�������? " + pchar.GenQuest.EncGirl.name + " �������� � ����� � ������ ������ � ��������������� ������. �������, ��� ���� ����������� ������� ����� �� � ���������� ������ �� ������ ������, ��� ����� �������� � �������������... ��, ���� ���� ����, ������� ��� �� ������ ��� ����� �������!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "������� ���, �������. �� �� ����� ����� �� ������� ���� ������.";
			link.l1 = "�� ����� �������������. �������, ���� � ��� ������ �� ������ ���������.";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "� �������";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "�� �����";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "� �������� ����������";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "� �������";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "� ����";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "� ������ ����������� ��� � ����������. ����� ������������, ������� " + sTemp + ", ��� �������� ��� ����, � �������� ���, ��� �� ��� ��� �������. ������, �� ����� ��� ��� ������.";
			link.l1 = "������-������, �����. ������ ���������...";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // ������� ������ �������� �� ���� :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // ������� ������ �������� �� �� ��� ��� �������� � ��� ������ :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// ��������� "������ � ��������"
		
		// ��������� "��������� ��������"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("����!.. ����, �������! �������.","�������, �������, ������...");
			link.l1 = LinkRandPhrase("���, ������ ��������?","������� ������! ����.","� ��� ����?! ����� ��������� ��������?");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "���������, � ����� � ������ �� � ����� ��������������... ������ �� �����, �� � ���� �������� ������������� ���� ����. ����������, ��� �� �������� ����������.";
			link.l1 = RandPhraseSimple("�� ������ ��������, �������, ������� ������, ��� �������!..","�������, ����� ����������? ������ �������� ���. � ������� �������� �������� �������.");
			link.l1.go = "CaptainComission_21";
			link.l2 = "���������, ������ ���������. ";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterReputation(pchar, -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) // "�����"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "��������� " + pchar.GenQuest.CaptainComission.Name + " �� ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City) + ", ��� � �� ���� ��������� ��� ���������... ������, �� �����. ����� ���� �������...";
				link.l1 = RandPhraseSimple("� �����-��?! ������, � ��� ������. �-�, ��������...","������, �������, ���� ����� �����. �-�, ��������...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "�� �����, ��� ����� ���������� ��������� ����������. � ������� �������� �������� �������.";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "�������� '������'"
			{			
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "��������� �������� ����������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " '" + pchar.GenQuest.CaptainComission.ShipTypeName + "' " + pchar.GenQuest.CaptainComission.Name + ", ��� ��� ������ ���������� � " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Dat") + "... " +
							"������� ����� �������� �������������� ������ " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Acc")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "'... ����� ������, ��� ��� �����... " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name"))) + " ��� � " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc") + " �� " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") + " � ���� ����� 15 ������ ����� � �����... ����� ����������� �����������...";
				link.l1 = RandPhraseSimple("������ �� ������, �� ��� ������ �������. �-�, ��������... ","������, �������, ���� �����. �-�, ��������... ");
				link.l1.go = "CaptainComission_300";
			}						
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "����� ����������! �������, �� ��� ����� ��� ��� �������.";
			link.l1 = "� �� ������ ���..";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterReputation(pchar, -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("������ ���, " + GetAddress_Form(pchar) + ".","��� �� ������?","��� ���� �������?");
			link.l1 = "�� " + pchar.GenQuest.CaptainComission.Name + "? � ���� � ��� ���������. ������� " + pchar.GenQuest.CaptainComission.CapName + " ������ �������� ��� ������ ����������.";
			link.l1.go = "CaptainComission_4";
		break;
		
		case "CaptainComission_4":
			dialog.text = "��? �� ������� ���������. ��� � ��� ��� ������ ������� " + pchar.GenQuest.CaptainComission.CapName + "?";
			link.l1 = "�� ������ ��������, ��� �� ������ ��������� ���� ���������.";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "�� ��� �� ����� ��������?! � ��� ����� ����, ��� ���������� ������� - �� �� ��� ��� ���������!";
			link.l1 = "������ ���, ��� �������� ��������������. ����� ������� - �� �����.";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "��, ��� ��� �� ��������! ������� ������� �������...\n"
					+ "�������, � ����� ������, � �������� ������� ������ � ���. ������ � " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Gen") + " ��������� ����� " + GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")) + " " + pchar.GenQuest.CaptainComission.SlaveName + " � ������� �� ���� �����. �� �� ����������� �� ����� ��� ������ �� ����? �������������� ����� ������.";
				link.l1 = "� ���������, � ���� ��������� ������ �����.";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "��������� ��� ������, ���� �������� ���� ���� ���������.";
				link.l2.go = "CaptainComission_6_2";
			}
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "��, ��� ��� �� ��������! ������� ������� �������...\n� ��� �������?";
				link.l1 = "�-�... ����� �������?";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "����� ����, �������... ����� ����, ��� �� �� ������ ��� ������.";
			link.l1 = "��� �� � ������� ����, ���������. �� �� ���� ���������... �� ��������.";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2":
			dialog.text = "����� � ������� ������ �� " + pchar.GenQuest.CaptainComission.PirateName + ", � ������� �� �������, ��� �������� ����� ������ � �������� ������� �������� � �������. �������� ������� ������ ��� ��������� " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_ACC) + ", ��� � �������� �� ������� �������, � ������ �����. �� ������ ��� �������, ������ ������ �������� ������.";
			link.l1 = "� ��� �� �����������?";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "�-�, "+ GetSexPhrase("��������","�������") +", ������ ���, ���-�� ������ ��������� ����. ������������ ����� - ��� ������ � ������� ��������������. � �������� " + pchar.GenQuest.CaptainComission.CapName + " ���� ��� ������� ������, ������� �� ������ ��� �������� " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT) + " �� " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc") + " � �������� ������ �� ������ �������� - " + pchar.GenQuest.CaptainComission.SlaveName + ". ��� �� ������� ���� ��������� � ����, �� �� ��� �� ������� � ��������.";
			link.l1 = "����� �� ������ �� �����?";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("c�","���"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterReputation(pchar, -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "��� �� ��������� ������... ������ ����� - 150 000 �������, � ��� ������. ���� ������� ��� ��������� � � " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc") + " � �������� " + GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")) + " ����. �� ������ ����� ��������� 40 000, ������� �� �������� �� �����������.";
			link.l1 = "������, � �����"+ GetSexPhrase("","�") +" ���� ��������.";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "� ���������, � ���� ��������� ������ �����.";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "����� ������� ������, � ���������� ��� �������... ������ ����� ���������� - �����, ��� " + ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM) + " �� ������ ����� � ������� ������� � �������.";
			link.l1 = "����� ���� �����. �����, ��� �� ����� ����� �������.";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "��� �� �������... ��� ���� �� ������.\n����, ������� �������� �����, ���� �������������� �� ������. �� ����� ��������� - ����� � ���������� " + pchar.GenQuest.CaptainComission.SlaveName + ". ������� �� ����� �������.";
			link.l1 = "� ���� � �� ���������?";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "� ��� � �� ����� ������ ��������. � ������ ������ ���� � �����������, ��� ���� ����� �������� ���� �� �� ��������� � ��� ������� ������ " + pchar.GenQuest.CaptainComission.SlaveName + ", �� � �������� �� ������ ����� ��������� �� ��������...";
			link.l1 = "��, ������ ��... � ���� ��������?";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "� ��� ����� � ���������...";
			link.l1 = "�� �����... ���������, ��� ��� ��������.";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","��"));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("������������, ������� " + GetFullName(pchar) + ". ���� �����-������ �������?","�� ���, �������, �� ��� ��������� �����?","������������, � �������, �� �������� ������� ��������?");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "� ���������, � ���� ���������� �����, � ��������"+ GetSexPhrase("","�") +" ��������� ��� �������.";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "��� ���. � ���� ���������.";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("�-�, ����������� ���, ������� " + GetFullName(pchar) + ". ��� ������?","�� ���, �������, ��������� ������ ����������?","��� ��� ������, �������, � ������ �������. ��� ������������ ���� ����� ����?");
					link.l1 = "�������� ���� �������, �� � ���� ���������.";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "����������, ���������, � �� ����� ��������� �� ���� ���������� ���������� ���� ��������?";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("������������, ������� " + GetFullName(pchar) + ". ���� �����-������ �������?","�� ���, �������, �� ��� ��������� �����?","������������, � �������, �� �������� ������� ��������?");
					link.l1 = "��. ���� ��������� ���������, " + pchar.GenQuest.CaptainComission.SlaveName + " � ���� �� ����� � ��������� ����� �� �����.";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("�-�, ����������� ���, ������� " + GetFullName(pchar) + ". ��� ������?","�� ���, �������, ��������� ������ ����������?","��� ��� ������, �������, � ������ �������. ��� ������������ ���� ����� ����?");	
					link.l1 = "� ������"+ GetSexPhrase("","��") +" ��������, � ������� �� ��������. �� � ���� �� �����.";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("������������, ������� " + GetFullName(pchar) + ". ���� �����-������ �������?","�� ���, �������, �� ��� ��������� �����?","������������, � �������, �� �������� ������� ��������?");
					link.l1 = "������������ " + pchar.GenQuest.CaptainComission.Name + ", � ��������"+ GetSexPhrase("","�") +" ��� ��������.";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("�-�, ����������� ���, ������� " + GetFullName(pchar) + ". ��� ������?","�� ���, �������, ��������� ������ ����������?","��� ��� ������, �������, � ������ �������. ��� ������������ ���� ����� ����?");
					link.l1 = "�������, � ������� �� �������, �����.";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "�������, �������, �� ������� ���������� ������ ���� ����� �����. ��� ���� ��������������... ����� ��� ������� - ��� ��� ��� 40 000 ��������. ��������, �� � ������� ��� ���������.";
			link.l1 = "�������-�������, ���������� ������� � ����� ����������.";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "��� ������� ���� ����������, �� �������� ��������������, ������� ��������� ���� ������� �������������� �����.";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("�� �������� ��������� �������");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterReputation(pchar, 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("�� �������� ��������� �������");
			PlaySound("interface\important_item.wav");
			dialog.text = "� ��� �� �������... �� �� ������� ��������� ����� ��������������.";
			link.l1 = "��, �� ������ 150000 �������, ��� �������� �������� 200000. � ��� �� �������� ��������.";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "�������, ��� ����� ���� ��������� ����� ���������������. ������� �������������� ������� �� ������� � �� �������. ��� �� �������� ������ - �������� ������ ��������� �� ����� �������������?!";
			link.l1 = "����, ��� ���������� ���-���� ���������...";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "��� � �����������! � �� �����������, ��� �� �����������.";
			link.l1 = "�� ��� �������� ������� ����������� �� ��� �����������.";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "����-����... �� ������� �� ���� ��������. ��� ����� ���� ������� ����� ��� ������� ������, ������� �� � ����� ������ �������� �� �����, ����� " + NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)) + " ����� ���������� ����� ����������� " + pchar.GenQuest.CaptainComission.SlaveSpeciality + "?";
			link.l1 = "������ � ����, ��� � �� �������"+ GetSexPhrase("","�") +" �������� ��� ��� ��� ��������� �����������.";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "��, ��, ��� "+ GetSexPhrase("������� ��������","������� ��������") +", ������ ��������, ��� ����������� ��� ������. �� ����� �� ������ ���������� ���� ����� ������ �� ���� ��������.\n�� ����������� ���� ������������� �������... ����, �� ����� ������������� " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + " ��������� ��� ���������� � �������� ����������� �������� � ������� ���� ������ ������� � ��������� ������������ ��������������.";
			link.l1 = "���-���... ������� � �� ����. ��������� ������ ������� �����������.";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "��, ����� ������! � � ��� ���� ������� ������� ����� �������. �� ���� ����� �������, �������!";
			link.l1 = "�������, �� �������������� ��������� �������. ��� ���� ������.";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterReputation(pchar, -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "������ �� ������������? � �����, ��� ������ ����� ������� �������.";
			link.l1 = "�� ����������, �� �� ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "�������, �� ���������, ��� ����� �������� ������ ���?";
			link.l1 = "� ��������, ��� ��������� ����� ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "���� �����! ������� ������������ - ������������� ������ ���������� �� ������������ �������...\n������ ���� ����� �� � ��� ����. �� ����"+ GetSexPhrase("","�") +" �������� " + pchar.GenQuest.CaptainComission.CapName + ", ������"+ GetSexPhrase("","�") +" ��� ����� ������� ��������, �� ��� ������ ���� ����������"+ GetSexPhrase("","�") +". �������"+ GetSexPhrase("","�") +" ���� - ������ ����������. � �� �������, ��� ��� ���� ����� � ���...";
			link.l1 = "׸�� �� ��� ������..";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// ������� � ����������� �� ���������
		case "CaptainComission_10":
			dialog.text = "������������, �� ���-�� ������?";
			link.l1 = "���� � ������ ������� ���������?";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "�� � �������, ���� ������-�� ������� ���� - �� �� ������, �� �� �����. � � ������� ����������� " + npchar.name + " � ����������� ������ ��� ������� � ���������� �������.";
			link.l1 = "��� ���? ��� ������... � ������� � ������� ����� ���� ������ � ���� �����������?";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "����������. � ��� ������� ������?";
			link.l1 = "���, � ���� ������ ������ ������ ����������.";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "�-�, � �� �������, ��� ��� ����� ������ ���� ���?";
			link.l1 = "�� ������� ������"+ GetSexPhrase("","�") +" - ��� ��� " + pchar.GenQuest.CaptainComission.SlaveName + ".";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "��, �� �� ���������, ��� ��������� ������ ���������� ������ ����� ����, ��� �������� ���� ���������� ��� ������� ������� ������?";
				link.l1 = "�� ������, � ���� � ����� ������ ��� ���� ��������?";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "��, � �������, �� ������, �� ���� �������?";
					link.l1 = "� ����� ������?";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "�-�, ���� ��������. � �� �� ���� � �������� ����� �� ���. � ��� ���, ��� ��� ��������, �� ��� ����� � ����� �� ������. � ����� ������ ��������� ������ ������ �� ���� �����������? ������ ���� ����� - ��� ��� ���������! ������� � ������ � ��� � �����. � ��������, �� ��������� �� ����� ����� ������ ���������! ������ - �� �������� �� �������, ������ - ����� �����������...";
					link.l1 = "��, ��������, ��� �� ����� �����, ��� ����� ��� ������, � ������� �� ��������.";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "�������-�������, ��� �����������...\n���!!! 150000 �������... ";
			link.l1 = "������...";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "��� ������� � ������������, ��� ���������. ��� �� �����... �� ��������� ����� ���� ����������, � �� ����� ��������� ������-�� �������� ����� ���������..";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "�������, � ����������� � ��� ����� ����... ��� ������, � ��� �������.";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "��... �� � �� �� ��������� ����������, � ����� ���� ������� ����. �� �� ��������, ��� �� ����� ������ ����� ������� ������ � ������ ������ ����������.";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "��� �� ������� ���������. ��������� ����� ������-�������� �������� ������� �� ��� � ���, ���� ������ ��������� ���������.";
			link.l1 = "��� ��� ��, ��� � ������ ������?";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "������ �� ������? ��������� �������� �� ���� ���� � 200000 �������, �������� ������������.";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "���! �������, ��������� �����, ��� �� ������� ����� � ���� � ����... ";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "��... �� � �� �� ��������� ����������, � ����� ���� ������� ����. �� �� ��������, ��� �� ����� ������ ����� ������� ������ � ������ ������ ����������.";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "�� ��, ��������. ���-�� ����� ����� ������� �����������. \n���, ���. ��-�... ���!.. 150000!..";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "�������� ����� �����-�� ������. �����������, ��� ����� ����� ����� �� ����� ��������������� ���� ������ ����������. � �������, ��� ��������� ������ ����� � ����� ������ ���� 15000. �� � �� ��������� �� ������ ��������.";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "��... �� � �� �� ��������� ����������, � ����� ���� ������� ����. �� �� ��������, ��� �� ����� ������ ����� ������� ������ � ������ ������ ����������.";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "��� � ������! ��� � �����������! ��� ������ ��������... �-�, ����� �� �������?";
			link.l1 = "���, �������... ��������� ������ ���������� ������.";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "� �� ����, ��������?";
			link.l1 = "��... �� ���, �� �����. �� ��������. ";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "���, � ���������, ������ �� ���� ��������... ��� �����������...";
			link.l1 = "�� ��� �� ������� - �����������, �����������... ��� ������ � ���� ������� �� ������. ������� ���... � ������� �� ���� ������.";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "��� �� �� ������ �������� ����� ����������?";
			link.l1 = "���. �� ��������.";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "��� �� ���� ������ �� ��������. � ���� ���� ������ ���������� �� ������ ��� �������.";
			link.l1 = "׸�� �����, ��� �����... ��� ������. ��������� �������� ����������.";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "��, �������. �� ������ �� ����� ���������.";
			link.l1 = "��������.";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "��-�, �� �������� �����. ������ ������.";
			link.l1 = "��, ��� �� ������������ � �����, � ���� ��� �������?";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "��, �������. ��� ������ ��������.";
			link.l1 = "��� � ������. ��� ���� ������... �� ��������.";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "����� ���� �����, �������?";
			link.l1 = "���. �������.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "�� ��-���� ������ ��� ������?";
			link.l1 = "���. �� ��������.";
			link.l1.go = "exit";
		break;
		
		// ������� � �����
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "������������, �������. ��� � ���� ��� �����������? ���� �� �������, ��� ���������� ���� ��.";
				link.l1 = "��� �� ���� ����� �����������, � ������ ������������ " + pchar.GenQuest.CaptainComission.Name + " �� " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". �� ������ �� ��� �����.";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "������������ �������. ��� �������, ��� ��� �� ������ �����. ��������� ���, ���� � �������, ��� �� ���� ������.";
				link.l1 = "� �� �� ��������� ���������� �� ����� ������������ �������. ��� ���-�� �������?";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "����� ��� �����, ���� ��� �� ������� ���� �����, �������� ���� � ���� ����������. � ������ ��� �������������.";
			link.l1 = "������� ������. �����, � ������� ��� �� ����.";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "���� ���� ���������, � ����� �������, ��� ����� ����� ����� ���, ��� �� �� ��������.";
			link.l1 = "��, �������, ��������"+ GetSexPhrase("","�") +" �� �� �, ���� � ������"+ GetSexPhrase("","�") +" ��� �� �� ����� ����.";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "����, ��� �������� ��������������. ��� ��������� ��� ������� " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)) + "?";
			link.l1 = "��, ��� " + pchar.GenQuest.CaptainComission.Name + " �� " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ".";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2Nation(sti(pchar.GenQuest.CaptainComission.Nation));	
			if(iNation == -1) iNation(rand(3));
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			dialog.text = "����... �� ����, ��� ��� ��� ���������, �� ��������� ������: �� ���� ��������� � ������� " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen") + ", ��� � ���� ������������� � ������������, � � �������� � ���� ������ ����������, ������� �������.";
			link.l1 = "�������. ��� �����, ��� ��� ������ � �� �������. ����� �� ����, � ������� ��� �� �������.";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "� �� ����� ��������� �������� ������������ ��-�� �����-�� ���������� ������������� �����.";
			link.l2.go = "CaptainComission_203";
		break;
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", ""); 
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("��","���"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "� ���������, � �� ���� ��� ������� � �������� ������. ��� ����� ��������� ��� �����.";
			link.l1 = "��� �����... �������� �� ���� � �� ��������� ������. ��������, ��� �� ����� ��� �������.";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "���?! ������ ����� �������� �������? �� � �� � ��������� ������ ������� ������ �� �������. ����� �� �� ���� ����� ������!";
			link.l1 = "���... ��� ����������� ����� �� ���������� ��������� ��� ��������� ������� ������.";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterReputation(pchar, -3);
			dialog.text = "��... � ������ ���������... ��� �� ��� ���������?";
			link.l1 = "������, �� ���������� ������ ������� ��� � �������. � ���"+ GetSexPhrase("��","��") +" �� ��� �� ��������, �� ������ �� �����"+ GetSexPhrase("","�") +"...";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "�������! ��� �� ��� ��������?..\n������, �������, ������� �� �������... � �������, ����������, ������, ������� �� ������� �� ���� ��� ������.";
			link.l1 = "��� ������� ��������� ��� ��������, ������� ���� ������ � �������� � ����... ��������.";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "��, ������� ��������... ��������, ��� �� �����"+ GetSexPhrase("","�") +" ��� ������... ��������.";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterReputation(pchar, -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "��� �������... �� ���� �� ������������� ����, ��������� ��� �������..";
			link.l1 = "����� �� ���� ������... � ���� ���"+ GetSexPhrase("","�") +", ��� ��� ����������. ��������.";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// ������ � ����� � ��������
		case "CaptainComission_70":
			dialog.text = "����... �������, ��������� ����...";
			link.l1 = "��, ��������, �� �� �� ������ " + pchar.GenQuest.CaptainComission.SlaveName + "?";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "��... ��� �...";
			link.l1 = "������, ���� �� ������ ��������� �����, ��� ������� �� ���������� - ��������� �������� � ��������� ����. �� ������, ��� �� ��������� ����?";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "����...";
			link.l1 = "��� ������ � ���� �������� �����������, ���� ����. � � ���������� ��� ����������� ������������.";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// ������ ���������� ����
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("�����������, �������, ������ ������� - � �� ������.","��������, ������ �� ����, � �� ���� ����������� �� �������.");
			link.l1 = RandPhraseSimple("�� ����������, ��� ��� ����� ������ ����? ��� ��� " + pchar.GenQuest.CaptainComission.SlaveName + ".","���-�� �� ��������� ������ �������� ��������� �� ����� " + pchar.GenQuest.CaptainComission.SlaveName + ". �� ����������, ��� � ���� � ��� ������������?");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "�� ������� ������� � ��������� ��� �������.";
			link.l1 = "�������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "�������... �������, �� ������ ��� �����...";
			link.l1 = "���� � ����� ��������� � ��� ���� ���.";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "�������, ��� � ���� ��� �����������? ���� �� �������, ��� ���������� ���� ��.";
				link.l1 = "���� ��� ������������ ���� ����������� " + pchar.GenQuest.CaptainComission.Name + " �� " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". � �������� �� ��� ���������.";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "��������� ���, �������. �� ����, �� ����� ����� �� ����������, �� ������ ������� ������ ����� �������� �������.";
				link.l1 = "� ��� ��� ��?";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "���� ��� �� ������� ���� �����, �������� ���� � ���� ����������. � ������� ����� �� ����� �����.";
			link.l1 = "������� ������, ���� ������� ��������� ������ ������.";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "���� � ������ ����� �����, ������� ��������� ��� �� �� ������������?";
			link.l1 = "��, �������, ��� ����� ������ �� ������... ��� ������ �� �������� ������.";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "����, ��� �������� ��������������. ��� ��������� ��� ������� " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation)) + "?";
			link.l1 = "��, ��� " + pchar.GenQuest.CaptainComission.Name + " �� " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ".";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2Nation(sti(pchar.GenQuest.CaptainComission.Nation));	
			if(iNation == -1) iNation(rand(3));
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			dialog.text = "����... �� ����, ��� ��� ��� ���������, �� ��������� ������: �� ���� ��������� � ������� " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Gen") + ", ��� � ���� ������������� � ������������, � � �������� � ���� ������ ����������, ������� �������.";
			link.l1 = "�������. ��� �����, ��� ��� ������ � �� �������. ����� �� ����, � ������� ��� �� �������.";
			link.l1.go = "CaptainComission_95";
			link.l2 = "� �� ����� ��������� �������� ������������ ��-�� �����-�� ���������� ������������� �����.";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "� ���������, � �� ���� ��� ������� � �������� ������. ��� ����� ��������� ��� �����.";
			link.l1 = "��� �����... �������� �� ���� � �� ��������� ������. ��������, ��� �� ����� ��� �������.";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "������� ���, �������. ��� ������ � ������������� � ������������. �� ��������� ��� �����, ��� ��� ������, ��� ������ � �� ������ ������������� ����� ������� ������, ��� ���� ������� ������.";
			link.l1 = "��� ��������� ����������.";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "���� � ���, ��� � ������, ���������� " + pchar.GenQuest.CaptainComission.SlaveSpeciality + " � " + NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation)) + " ����� ���������� ��� ��������������," + 
				"�� �, ��� ������� �������, ��������� ����� �������. ����� ���� ���������� ��������. �� ��� ���� ��� �������, ��������� ������ �������, ����� ������������ ������� ������ � �������� ���� �������.\n"+
				"� ����� ������ �� ������� ���� ��������, �� ��� ������� ������, � ������ ��� �� ���� �� � ����. ���������������� ������� - ��� ��� ��������, ��� � ����������, ������-�� ������ � �������, ��� � �������� �� ����������... �� � ������ �� ������.";
			link.l1 = "�� �� - ���� �� ���, ����� � �� �������.";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "�������� ����� � ������� �� ����� ���.";
				break;	
				case 1:
					sTemp = "������ �������� ������ � ����� ���������� �������������� ����� � �������� ������� �����.";
				break;					
				case 2:
					sTemp = "������ ���������� � �������� � ������������� ������ �� ����� ���.";
				break;					
			}
			dialog.text = "��, ����� ���������� � ���. ���� �� ���� ����������� ����������, �� ������� �� ������ ���� ����� ����������� � ������ " + sTemp;
			link.l1 = "��������� ���, ���������� ���������� ������������� ����� �������.";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "�� ��� �, �� �������� � ������� ��� �� ��.";
			link.l1 = "� ��� �������. �������� � ������ �� �����������.";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// � ������ ������� ������ !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(drand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(drand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// ��������� "��������� ��������"
		
		// ��������� "�������� ������"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Dat"));
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// ������ � ����� �� ������
		case "CaptainComission_301":
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("������������, � ������� " + GetFullName(NPChar) + ", ��� ������� ��� �� ������ ����� ������� '" + pchar.GenQuest.CaptainComission.ShipTypeName + "'?","������������, � ������ ��� ������ �� ����� ������ �����. ������� " + GetFullName(NPChar) + " � ����� �������.");
			link.l1 = "������������, � ������� " + GetFullName(pchar) +", �������� �� ��������� ������� �������� " + pchar.GenQuest.CaptainComission.CapName +". �� ������ ��������, ��� � " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Dat") + " ��� ��� �����. ������� ����� �������� ���������� ������ ������-�� �����, ���� �� �������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + ".";
			link.l1.go = "CaptainComission_302";
		break;
		
		case "CaptainComission_302":
			dialog.text = "��, ����� �������! ��������, ����� ��������...\n� ��� ��� ������� " + pchar.GenQuest.CaptainComission.CapName + "?";
			link.l1 = "�� �����.";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "׸��! ��� �� ���� �� �����... ����������, " + GetFullName(pchar) + ", � ������ �� ����� � ������ �������� �������. �� � ��������� " + pchar.GenQuest.CaptainComission.CapName + " ���������� ����������� � " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Dat") + ", ����� ��������� � ���� �� ���� ���-����� �����. ������ �� ����������, ��� ������� �����, � � �� ���� ���� ��������� � ���������, ���� ������������ �����.\n������, � ���� ������ ��� ������� ������, ����� ��� ������� ������ � ���.";
			link.l1 = "�� �������� ����� �������� �� ����, ������ ���� ������ ��� �����.";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "�������� ��� ������ � ��������, ����� ������� ���� �� " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen") + ", � �� ��� ������� ��, ��� �� ����� � ��� ����.";
			link.l1 = "��, ������ �� �������� ������� ������� ����� � ������ �� ������ ��� ����������.";
			link.l1.go = "CaptainComission_305";
			link.l2 = "� ���������, �������������� �� ��������� ��� ������� �� ��� �����.";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "�� ������, ���� �� ������ ��� �� ���, �������� �� �� �������.\n" +
				"�� ����� ������ �� ���������� ������ ��� ������������� �����, ������ ��� ������ " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + ". ������ ���� � ����� ��� ��������������. " +
				"����� ����� �������� ������ �� �������� " + sTemp + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "', ������� ������� ��������� ����. ��������� ���� ���� ��� ������ �� �����, �������� ��������� ��� � ��������. ��� ��������� ��������, ������� �������� �������� �� �������.\n" + 
				"�� ��� ������������� ���� � ������, ��, ��������� ��������� ���� ����� � ������ ���������, ��� ������� �������� �������. ������ �� ���� ���� ���������, ����� ������������, ��� ���� " + sTemp + " ��� ������� ����� " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Abl")) + ". " +
				"�� ������, ��� ��� ���� ����� � ��������� ����������� �� ���� ���� � ������ ���������...\n� ���� ������� ��� ���������� �������. �� ������ " + sTemp +" � ��������� �����, ���������� ����� ������� �� ����� � ������ ��������, � " + sTemp + " �������� �������� � ���� � ��������. ������ � ������������ �� ������ � ���������� ���������� �����, �� �� ����� �� �������� � ���������� �����.";
			link.l1 = "�� ������, ���-�� ��-���� �����������...";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "����� ����, �������... ����� ����, ��� �� �� ������ ��� ������.";
			link.l1 = "��� �� � ������� ����, ���������. �� �� ���� ���������... �� ��������...";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "� �� �����, ��� ��� ��� ����. ������ �����, ��� �������� ����� �������� ���������� �� ���� �������.\n�� ��� ���? ���� � ������������ �� ���� ������?";
			link.l1 = "�� �������, ��� ��� ���������.";
			link.l1.go = "CaptainComission_308";
			link.l2 = "���, ���������. ��-������: � �� ����, ������� ������ �������� �� ��� ����, � ��-������: ��� ��������, ��� ������ ��� �� ����� � �� �������, � � ������� �� �������� ������.";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "����� ������� ���������� " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat") + " ����� ����� ��������, � �� ��� ��� �������� ��������� ������� �� ����� ������� ������. ��� �� ��� �� ��������� �������.";
			link.l1 = "������, ����� ���� ���.";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "����� ����, �� �� �� ���������� ��� ������. ������ " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " ������������, ���� ������� ���� ����, ���� �������� � ����������� �������� �������� � ������ ������. �� � ���� �������, � ������� �� ���, ��������� ����� �� ������ ������ ��� ������ �� ���� ����.";
			link.l1 = "� ��� �� �����������?";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "� ������ ���� �����, � ��� ������� " + XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat") + ".";
			link.l1 = "���� �� ��� � ��� ���������. � ������� � ���� �� ����, ���� ���� ��� ����� ��� ������� �������� ��� ���� �������.";
			link.l1.go = "CaptainComission_311";
			link.l2 = "������, �� ���� �� ���������� ��� ������. ��� �, ��������"+ GetSexPhrase("","�") +" ����������� �������...";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //����� ����� �� ������ - ����� � ����		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313":			
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "�������, ��� ����� ����������. � �����, ��� �� ��� �� ��������� �������.";
			link.l1 = "������, ������� �����������.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "�������, ��������� �������� ��� ������. ������� ������� �� ���� �����, � � �����, ��� � ����� ����� ����� �������.";
			link.l1 = "�� ����������, �� ����� � ������ ����. ������ ��� �������� � ������.";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "��, ����! � ��� � ����� ����������...";
			link.l1 = "�� ����� � ������ ������� - ������� ������, � �� ��������...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// ������ � �������� �� ������
		case "CaptainComission_317":
			dialog.text = "�������, �� ����������� �������� ����������� " + pchar.GenQuest.CaptainComission.Name + ", ��������� �� ������� ������ ����. ���������� ���� ���������.";
			link.l1 = "������, ����� ���������? �� ���������� ��� ���������� ������� ������� ����.";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "� ���, ������, � �� ����������� ��������. ����� ������ � �������� �� ����... ���.";
			link.l1 = "��, ������, ��� �� �� �� �������...";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
			sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
		break;
		
		case "CaptainComission_320":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "��� ����� �������, ���� ���� �� ��������� ������������. �������� ��� �������� � �����, �� ���� ���� �������� " + pchar.GenQuest.CaptainComission.GoodsQty + " ��. " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) +".";
			link.l1 = "�����������. ���� �������. ������� ���� ����� � ���� ����.";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "��� ���� �������. ������ ��������� ���������� ������, �� �� ����� �� ����������� �� ����� �� " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + ", ��� �� " + XI_ConvertString(GetIslandByCityName(sTemp) + "Dat") + "?";
			link.l1 = "���, ���������, ������ ������ ��� �� ����. ��������...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "������� ���"+ GetSexPhrase("","��") +" ��, ���� �������������� ����� ���������������.";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// ��������
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + cRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + cRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// ��������
			dialog.text = "��� ���� ����� ����������. �� ������ � ����� ��������� " + pchar.GenQuest.CaptainComission.ConvoyMoney + " �������. �� ��� �������, ��� �� �������� �� ����� " + pchar.GenQuest.CaptainComission.iDay + " ����. ��� �����.";	
			link.l1 = "�� �����. ������ ����������.";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // ����� ��������� ������ 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Dat"));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("�������, �� ������ �����. ��� � ����� ������ ����� ����������.","�������, ����� ������ ������ ���. �� ���������, ��� ���� ����.","�������, ����������� �����������. ��� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))) + " ������� �������� ��� �������.");
			link.l1 = LinkRandPhrase("��, �� �����, ����� �������...","��� ��������� � ������ ��� ������ ����������.","��... ��������� ����� �����. ������.");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "�������, ��� ���������� ���������� � ����� ������.";
			link.l1 = "��������.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "����������� ���, ������� " + pchar.CaptainComission.Name + ". �� ���, ���� ���� ��������? � ��� ������� " + pchar.CaptainComission.CapName + "?";
			link.l1 = pchar.CaptainComission.CapName + " �����. �������� ��������������� �������� ���"+ NPCharSexPhrase(sld, "�� �����������","� ����") +". ��������� �����������, ������� " + pchar.CaptainComission.FullName + ".";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "� "+ NPCharSexPhrase(sld, "��� �� �� ���? ��","��� ��� �����? ���") +" � ����� ����� ���?";
			link.l1 = "� ����� ������, ��. �� ���� ����� - "+ NPCharSexPhrase(sld, "�� ������","��� �������") +", ��� �������� ����� ����������� "+ NPCharSexPhrase(sld, "���","��") +". ����� ������� "+ NPCharSexPhrase(sld, "���","��") +", ��� ��� �� ������ ���.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "�������"+ GetSexPhrase("��","��") +" " + GetFullName(pchar) +", ��, ��� ��� ��������� �����, �� ��� ��������. ��� ����� ������ � ������ �����.";
			link.l1 = "�� �������, ��� ������ ����� �������� ��������, ��� �����-�� ���������� ������ �� ����?";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "���� �����. �������� �����, ������ " + pchar.GenQuest.CaptainComission.GoodsSum + " �������, ������� ��� �� ������������� ������������� � ����� ��������. �������� �������� - ��� ��������� �������� ������ ������, ��� ��� �� �����������... ������������, � ����� �� ����������.";
			link.l1 = "� ���� � ��������?";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "����� ������� �������� �� �������. �� �� ������� ������ ������� � ������� ����� � ���� ������ �����, � ������� ������ ����� ������ �� ������ ������ ��� �� ������... ��� ��� ����� �����������?";
			link.l1 = "�� �� ���������� ��� ������. � ��������"+ GetSexPhrase("","�") +" ������� ���.";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "������ � ���� ��� ������. ��� ���� ������.";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "��� �, ������� ��������� "+ GetSexPhrase("������������ �����������","�������� ����") +".";
			link.l1 = "������ ���������������! ������� ����� � ����!";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "�������� �������. ����� ��� ����������.";
			link.l1 = "���� �� ����������...";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "������� " + GetFullName(pchar) + ", �� ��������. � �����, �� ���������, ��� � �������������� �� ����� ���� � ����.";
			link.l1 = "������� �������. � � ��� ������ ���������"+ GetSexPhrase("","�") +" ��������� ���. ��������...";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("��","���"));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "�� �������� ����� ������� �����, ������������� � �������� ������� ��������� �� ����� ������?";
			link.l1 = "���� ���, ����������!..";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "��� �������, " + GetAddress_Form(pchar) + ", ��� ������� ��������, ����������� ������...";
			link.l1 = "��� �� � �����������?";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "�������, �����"+ GetSexPhrase("���","��") +" ������� - ��� ������ �������. ������ �� �����, ������ ��������, ������� ����� ��� � ������. ���, ���������, ����� �� ����� � ���� ����� ������. ����� ��, ��������, ��� ������ �� ������ � �������.";
			link.l1 = "��������, ��������� ���� ��������������� ������� ��� ���������� ����������. � �����"+ GetSexPhrase("","�") +" ����� ����� ������� ��������� �������, � ��� ������ ������� ������ � �������. � �� ���� ����� �������� ��������... �����-�� ����� ��������� � �������� " + pchar.GenQuest.CaptainComission.Name +".";
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "�� ��� � ���, ����� �� ���-�� �� ����� ������������... � ������ �������� " + pchar.GenQuest.CaptainComission.Name + " ��� ��������� �� � ����. ���� �� � �� ������ ������ � �� ���� 100 �����, �� ��� ���� �� ������� ������, ������� ���������� �� ��� �� ����� ��������� �� ��������...";
			link.l1 = "� ����, ������������ ���������, ������� �� �������?";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "��� ����� ������ ���������?! �� ����� � �������� �������� " + pchar.GenQuest.CaptainComission.Name + "! ��� �� ������� - ����������, � ������� �������! ���� ��� ����?!";
			link.l1 = "�����-�����, �� ��������. ��� ����� ����... � �����, �������"+ GetSexPhrase("","�") +" �. ������� " + pchar.GenQuest.CaptainComission.CapName + " ������ ���� ������������, ���� " + pchar.GenQuest.CaptainComission.Name + " �� ����� � ��� ���������, ��� ������� ����� �������� �������������� ������ " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "', � ��� ��� �����.";
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "����-��. ��� �� ����� � ��������, � �� ������ ������ �� �����... ��� � ������ �������� " + pchar.GenQuest.CaptainComission.CapName + " ����������� ��� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))) + ", ����� �� ����� ������������ �� �������� " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") + ". " +
				"��� ���� �� ������ ������������� ����� ����� ������������ ���... ��� ���� ����� ������ ������ � ��� " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Abl")) + "?! ������� ����� ��-�� ���� ������ �������, ���� � ���, ������ �� �����.";
			link.l1 = "� ��-�� ��� ������?";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "�� ������. �� ����� �� ������ ������ - ������ ������. � ���� � �����-������ " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + " ������� �������, ��� � �� ������ ������ ������ ������, ����� ����� ������. � ���� ������ ���� �������� ������ � ��������, �� ��� � ��������� �������� ����������... ������ � ������� �� �����, � ��� �� ������ �������� - ������������� �� �����.";
			link.l1 = "� �� �������� ��� ����������?";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "� � ������, ��� ���� ��������� ��� �� ����� ��������, ������� �� � ����� ����� �� ���� - �� �����. ��� � ���������� ����������, � ���� ������ ������� �� ���� �����, ����� ����� �������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + ". �� ����� ��������� ��������� �� ���, ����������� ���������� �� ��������.";
			link.l1 = "������, � ��� ��-���� ����������� ��� ����-��?";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "������ ������ ����������� ���������, ����� �� ������������ �����. ������ ��������� �������� �� �������������. ���� ���� �� �� ��� ���������, �� �� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + " �� �������... �� � ��� �� ������� ������� - ������ �������.";
			link.l1 = "� ��� �� � ���� ������� �����������-��?";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "�� ���� ��� �����... ������� ��������������, ������� ����� ������ ��� ������ " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + ". ���� ������� ����� ��� ���������� - �� ����, ������ �� ����������������� ������� ����� �� �������������, � ����� �� ��� ��������, ������ ������� ׸����� �������. " +
				"�� ��� ������ ������ �� �����, ������� �������� ��������. ����� ���� ���������� ������... �� ��� ��� �� �����, ��� ��� ������� �������� ����.\n" + 
				"��, � ����� ���������� � ���� � �������, ��� ��� ����� " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + ", ��� � �������� ��� ��� ������������. �� ����� ��� ���� �������� ��� ��� ������... ����� �������� ��������� �� �����, � " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + " �������� - ���� ��� ����� �� ����������, �� � ������� ������ ���������...";
			link.l1 = "�� �������, ��� ��� ���� ������ � ������ �������� ����������, ���� ���� ����������� ������ ������?";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "�� ������. � ���� � ������ ������� ���, ��� ����� �� ��������, � ���� ������ ���������� �� ���� �������. ���� ��� � ����� - ������ ��������������, ��� ������ ���� �� ������� �����...\n" + 
				"������, � ����� ������ �����, ��� � ���� ������ ������, �������� ����� ����� �������. � �������� ��� ��� �� �������, �� �������, ��� �����, ��� ��������� ��� � ���������� ����� ������ �� �����... � �� ���� ������������� �� ������ ���������, �� �� " + pchar.GenQuest.CaptainComission.Sum + " ������� ����� �������� ��� ������, ��� �������, ��� ����� �������� �� ��������� ���� � ��������� " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity) + ".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "� ������"+ GetSexPhrase("��","��") +". ��� ������. ������ ��� �����.";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "��� ����! ���� �����, ������ ������� ������.";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "������� ������ �������, ��������. �� � �������� ���������� � ���� ���. ����� ���� � ������...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "��� � ������. ����������� ������� ����� �������� " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat") + ". � ������������, ���� � ����� ����� ���� ����� ��� " + pchar.GenQuest.CaptainComission.GoodsQty + " ��. " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + ". ����� ���� ������� � ����� ������ �������...";
			link.l1 = "���������� �����������. �� ������� � �����...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc"));			
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "��� ������� � ��. � ��, ����, ����� �����������. �������, ��� ������� ���� ������� �� ����� ���������.";
				link.l1 = "� ��� �� ���"+ GetSexPhrase("��","��") +" � ���. ��� ������. ������ ��� �����.";
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "�� � ��� ������ ?";	
				link.l1 = "��� ����! ���� �����, ������ �������.";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "�������, ������, �� ��������. �������������� ��-���� ��������� �� �������.";
			link.l1 = "� �� �������"+ GetSexPhrase("","�") +" �������� ���� ������, ���� ���� �� ��� ����� ��� ������.";
			link.l1.go = "CaptainComission_351";
			link.l2 = "��� ����! � ������ ����, ���������� ���"+ GetSexPhrase("","�") +" �� ������ ������������.";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
		break;
		
		case "CaptainComission_360":
			dialog.text = "�������, � ��� ����� ��������� �����������, �� �� ����� ���� ������� �� ����� ��������, ���� �� ������� ���� ���� ��� ��������.";
			link.l1 = "�����������, ������, �� ��������� ����� ��, ��� ��� �� �����������.";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "���! ��� �� � ��� ������ ��������������?";
			link.l1 = "� �����, ��������. � ������, ������� �� �������� ��������� ���� ��������, �������� �������� � � ������ ������ �����������.";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "�� ���� �� ���� ������� ������ ������� ����, �� �� �������� �������� � ���� ����! ������ ��������, ���� ����� ������!";
			link.l1 = "���� ���, �� ����, ��� ���� ����� ���, � � ��� ���� �� ����?";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "׸�� �� ���� ������! ����� �� ���������� ����� ��������!..";
			link.l1 = "������ �������, ��� ����� ���������!..";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "�������, ��������� ������������, ���� � ����� ������ ����� ���������� �������. �� � �������������� ���� ����� ��������� ��� ��������.";
			link.l1 = "������� �����������... ������ ������ ����� � ����� � ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "������� ��� ������� " + GetFullName(pchar) + ". ���� �� �� ��, �������� �� ��� ���� ���������������, ����� ���� �� ���� ����� ��������, ������� �� ���� ������ �������...";
			link.l1 = "��� ���� �������, ��� �������.";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "���� � ���� ���� ������, ��������� ������� � ����� ���� � ���-�� �������. ���� �������� � ���, ��� ������. ������� � ��������.";
			link.l1 = "������� �� �������, �� ������"+ GetSexPhrase("","�") +". �� �� �������� ��������, ���� ������ �� ���������.";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "������, � ���� ������� ������� ����. �� �� ���?";
			link.l1 = "���� �� � ���� ������� " + pchar.GenQuest.CaptainComission.Name + ", �� � ���.";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "...������ ������� " + pchar.GenQuest.CaptainComission.Name + "...";
			link.l1 = "� " + GetFullName(pchar) + ", � ���� ���� ���� ��������.";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "� ������ �� �������, ��� � ����� �� ��� ��������?";
			link.l1 = "������� " + pchar.GenQuest.CaptainComission.CapName + " ������ ������������ ��� � ���, ��� �������������� ������ " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "' ����� �������� �������, " +
				"�� � �� �����"+ GetSexPhrase("","�") +" ����������� ��� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))) + " �� �������� �� " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen") + ".";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "� ��� ��� ������� " + pchar.GenQuest.CaptainComission.CapName + "?";
			link.l1 = "�� �����.";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "���... ���, ������, � ��� ����. ��, ������ ������ �����������... ����, ���-�� �����������, ��� �� ����������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")) + ". " +
				"���� ��� ������ ���� ������, � ����� ���� �������. ������� " + pchar.GenQuest.CaptainComission.CapName + " ����, ������ ������ ������ ����� �� �� ����...\n�����, ��� �� ���...\n������� " + GetFullName(pchar) + ", �������� ���� ������, � � ����� ��� �����������.";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "�� ��� ����������� ��������� ��������� �� ��������� �����. ��� ���������� ������������ �����.";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "�� �� �� �� �������, ��� � ����� �������� �������?";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "�� ��� ����������� ��������� ��������� �� ��������� �����. ��� ���������� ������������ �����.";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "� ������� ����� �����, ��� �� ������� � ����������������...";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "����, ������� ���������� ��� �� �� �������, ���� � ��� �� ���������� �������� �� ��� ����.\n" +
				"�� ����� ������ �� ���������� ������ ��� ������������� �����, ������ ��� ������ " + NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation)) + ". ������ ���� � ����� ��� ��������������. " +
				"����� ����� �������� ������ �� �������� " + sTemp + " '" + pchar.GenQuest.CaptainComission.VictimShipName + "', ������� ������� ��������� ����. ��������� ���� ���� ��� ������ �� �����, �������� ��������� ��� � ��������. ��� ��������� ��������, ������� �������� �������� �� �������.\n" + 
				"�� ��� ������������� ���� � ������, ��, ��������� ��������� ���� ����� � ������ ���������, ��� ������� �������� �������. ������ �� ���� ���� ���������, ����� ������������, ��� ���� " + sTemp + " ��� ������� ����� " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Abl")) + ". " +
				"�� ������, ��� ��� ���� ����� � ��������� ����������� �� ���� ���� � ������ ���������...\n� ���� ������� ��� ���������� �������. �� ������ " + sTemp +" � ��������� �����, ���������� ����� ������� �� ����� � ������ ��������, � " + sTemp + " �������� �������� � ���� � ��������. ������ � ������������ �� ������ � ���������� ���������� �����, �� �� ����� �� �������� � ���������� �����.";		
			link.l1 = "�����, ��� ��� ������ ���� ����������... ����, ��������� ������ - �� ����������� ��� ������, � � ��������� ��� � ����� ����� ����������, ������� �� �������.";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "��-��-��... ��-��, �������, ��� ����� ���� � ��������� �� �������, ���� ���� ��� ������� ��������� �� ��������.";
			link.l1 = "������. �� �������� ���� ��������.";
			link.l1.go = "CaptainComission_377";
			link.l2 = "��... � �� ����� ��������� ����� ������� ���� ������ ������������. ��������...";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "��� ������ ����. ������ � ����� ���� � ����� � ����.\n������ ����� �� ������ ������ ���� �� ����� ������ �����. ��� � ����� �����, � ������� ��������� ������.";
			link.l1 = "����� ��������� ������ � �������: � �������� ������, � �� �������� �� ����. �� ��������� � ��� �� ���������, ���� �� ��������� �� �����.";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterReputation(pchar, -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "��������� �� ��������. ������ ��� ����� ������������ " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc") + ", ��� � ����� ����� �������. ������ ����� ���������� ���� �� ���� �� ��������� ������.";			
			link.l1 = "�� �������, ��� �� ������ ������� ���� �����?";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "��, �� �����, ����� ������������, ���� � ����� ������ ������� ����� ��� " + pchar.GenQuest.CaptainComission.GoodsQty + " ��. " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) + ". ������ ��������� ��������, � ����� ������ ������ ����, ����������� ����� �������� ������. � ������� ����� ������� ����� ��� ��� �� �����.";
			link.l1 = "����������� ����������.";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // ������� �����
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "�������, ��� �� ����� ���������. ���������� ���������� ���� ����� �� �����.";
			link.l1 = "������, ������ �������...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "�������, �� ������� ��������� ����� ��� �������. ���� ��� ��� �����.";
			link.l1 = "�����������, � ����"+ GetSexPhrase("��","��") +" ���� �� ������������� ����������. � ���� ����� ����.";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "�� ����� ���� �� ����� ����� - ������������ ���� ������� � ����� �� �����.";
			link.l1 = "� ���� ��� �� �������, �� ������� ��� �����������. ��� �� ������� � ����� ����� � ���������, ��� �������� �����, �� ��� ��������.";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "� ����, ���� �� �� ���������. ��, ����� �������...";
			link.l1 = "��� ��� ������ ��������...";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "��� �� � ������. ������ � ���� ��� ��� �����. ���� ������� �������. � ������� " + pchar.GenQuest.CaptainComission.GoodsQty +" ��. " + GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")) +". �� �� ������, ��� �������� ���?";
			link.l1 = "�� �����"+ GetSexPhrase("","�") +". ���� ��� ���� �������� ���������, ������� �������, ���� ���������� ��������� ��� � ��� ����.";
			link.l1.go = "CaptainComission_388";
			link.l2 = "��� � ������. � ������ �������, ����� ������� ����� ��������� ���� �������� � ����?";
			link.l2.go = "CaptainComission_389";
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "������� " + pchar.GenQuest.CaptainComission.Name + ", � ��������"+ GetSexPhrase("","�") +" ��� ��������. � ������������� ������� �� ������� �����������. � �������"+ GetSexPhrase("","�") +" �������� ��� ���� ������� ���� ����. � ��� ������� ��������� � ������ � ���������� ��� ����� ������.";
				link.l3.go = "CaptainComission_389";
			}	
		break;
		
		case "CaptainComission_388":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + cRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// ��������
			dialog.text = "��� ����� ��������� �� " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + ", ��� �� " + XI_ConvertString(GetIslandByCityName(sTemp) + "Dat") + " �� " + pchar.GenQuest.CaptainComission.iDay + " ����. ��� ��� ���� ������ ���� ����������� ���� ������.";
			link.l1 = "������. ���� �������.";
			link.l1.go = "CaptainComission_391";
		break;
		
		case "CaptainComission_389":
			dialog.text = "�� ��... '���� �� ����� ��� �� �����, � ������ ����� � ������...' ������, � �� ��������.\n���� � � �� ������ ������ ��������, �� � ��� ����� ������. ��� ������� �������� �� ��� �����������.";
			link.l1 = "� � ����� �������...";
			link.l1.go = "CaptainComission_390";
		break;
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			AddQuestRecord("CaptainComission2", "26");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Acc"))
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Dat"));
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterReputation(pchar, -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "������, �� ��������... ���������� �� ���������, � � ���� ��� ������� ����������� � �������� ������������ �������� � ���� ������...";
			link.l1 = "�� ������ �����-�� ���������� ����������� �� ���� ����?";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "������� " + GetFullName(pchar) + ", ��� ��������� ������� ����� ����������, �� �� ����� �� �� ������ ��� ���� �������? � �����, " + pchar.GenQuest.CaptainComission.GoodsPrice + " ������� ����� ��������� ������������.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "��, ��� ������� ����. � �� ��������. �������� ���� ������ � ��������.";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "�, ���, ���������, �� ��� �� ��������������. � �� ���� ��������� � ���� �����. ���� �� ������ �������� ����, �� � � ������ �������� ������� ��� ����. � �� ����� ������������ ��� �������� � ����.";
			link.l2.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "��������, �������. � ���� ������������� ��� �� ��������. � ���� ��� �� �� ��� �� ��������... ��� ������, ������� ��� ����� ���������� �� ������ ���������... � ������ ��������.";
			link.l1 = "�������. �� ������"+ GetSexPhrase("","�") +". ������� ���� ����� � ���� ����.";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_395":
			dialog.text = "�� ������ � �� ��� ������ ��������... ������, � ���� ��� ������� ������, ����� ��� ���������� ��� �����.";
			link.l1 = "� � ����� �������...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("��","���"));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "�������, ��� ���������� ���������� � ����� ������.";
			link.l1 = "��������.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "����������� ���, ������� " + GetFullName(pchar) + ". �� ���, ���� ���� ��������? � ��� ������� " + pchar.CaptainComission.CapName + "?";
			link.l1 =  pchar.CaptainComission.CapName + " �����, � � ��� ��������� �� ������. � �����, ���� �� ��� �� �����"+ NPCharSexPhrase(sld, "","��") +" ������� " + pchar.CaptainComission.FullName + ", �� ������ �� ��� �� ����, �� ������.";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "� "+ NPCharSexPhrase(sld, "��� �� �� ���? ��","��� ��� �����? ���") +" � ����� ����� ���?";
			link.l1 = "����� ���. "+ NPCharSexPhrase(sld, "�� �������","��� ��������") +" ���� �� ������ � ����"+ NPCharSexPhrase(sld, "��","���") +" ��������� ���� �������� �����, ������ �������� � �������� "+ NPCharSexPhrase(sld, "���","��") +" � ������ �� �������.";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "�, ���, �������, ��� ��� ���� ��������! ���� � ����� ��������� ������� " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.CaptainComission.ShipTypeVictim),"Name"))) + " � �������� �����, � �� �� �� ���� ������� ��������. ��� � ��������, ���� ���� ������� ���������� �� ��� ���� � ������." +
				" � ���� ���� � ���� ���� ���� ���� ������ ��������, ��� �� �� � ������������! � �� ���� ������ ��� ������� ����������� �� ��� ����, ����� "+ NPCharSexPhrase(sld, "�����-�� ���� ���","�����-�� ����� �����") +" ��� ������ ������������ ���� ����� ��������!";
			link.l1 = "��������, ������, �� ����� ����� ��� � " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.CaptainComission.ShipTypeVictim),"Name") + "Acc")) + " ��� ������ ����? � ��� ���� �� ������ ���������� �� ���� �����? � �� ���� ���������, ���, ���� �� � �� ����� "+ NPCharSexPhrase(sld, "����� ��������","��") +" ��������, �� �� ������ �� ����� ��������, ��� ������?";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "������ �������, �� ���� �� ��������! ������ ��� �����, ��� �� �� �����������? �����, �������� ������ � �� ����?! �����, �������� ���� ��������� �� ���������� ����� ����������? ��� �� �������, ��� �� ���������� ����������� �� ������ ��������?!";
			link.l1 = "����, �� ������ ������� ������, �������� ���� �������� ��� ����� � ����� ����.";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "������! ��������, ��� ����� ��� �������! ��� ��� ������ � ������ ��������. �� ������ ���� ���� "+ NPCharSexPhrase(sld, "����������","������������") +"!!";
			link.l1 = "������ ���� ������� ���! ��� � �������� ���� ���������� �������!..";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "��������, �������, ��� ��� �������� ����� ���������� � ���������� ���� ������� �����. ������ ���� ��������, ��� ��� �����-�� ����� ����� �� ���� ������ ��������, � ������� ������ ����� ��� ����� ������ �� ��������.";
			link.l1 = "���������, ���� ��� ������� �������� �� � ����� ����������� ��� �������.";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "� ���������, � ���� ������ ��� ������� ����������� � �������� ������������ �������� � ���� ������...";
			link.l1 = "�� ������ �����-�� ���������� ����������� �� ���� ����?";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "������� " + GetFullName(pchar) + ", ��� ��������� ������� ����� ����������, �� �� ����� �� �� ������ ��� ���� �������? � �����, " + pchar.GenQuest.CaptainComission.GoodsPrice + " ������� ����� ��������� ������������.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "������� ���. �� ��������. �������� ���� ������ � ��������.";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "���, ����� ����������� ���� �� ����������. �� ������ ������� ���� ��� �������� � �����, �� ����� � ��� �� ���.";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(drand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "���������, � ���� ������������� ��� �� ��������. � ���� ��� �� �� ��� �� ��������... ��� ������, ������� ��� ����� ���������� �� ������ ���������... � ������ ��������.";
				link.l1 = "�������. �� ������"+ GetSexPhrase("","�") +". ������� ���� ����� � ���� ����.";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "���������... � ��� �������, ��� ������� ��� �� ����� �������, ������� �� ��������, � ���� �� ������ � �����. � ��� ��������� ����� ������ ����, ������� ������� ������ � ����� � ���� �� ������. �������� ���� � ������� - �� ���������.";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "����������, � ����� ����"+ GetSexPhrase("","�") +", ����� �� �� ��� ��������. ���� �������. ���������� �� �����.";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "��... ��� �������, �� ������� ����� �������, ���� ������� ��� ����-�� �������. ��������...";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "�� ��, ������, ������� �� ��� ����... �������, ������� ������� ������ � �������� �� ���� �����...";
			link.l1 = "� � ����� �������...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("��","���"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_407":
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			SetCharacterRemovable(Npchar, true);
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			DeleteAttribute(NPChar, "LifeDay");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // ��� �������
            Npchar.Fellows.Passengers.id0 = Npchar.index; // ���� ��������

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1"; 
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// ��������� "�������� ������"
		
		// ����� "������� � �����" -->
		// ������
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "��� ��� �� ��������. ���������� ������, ��� �� ����� �����������! �� �� ���� �� �� �������� �����, �������� �� ������ ��� ���������?!";
				link.l1 = "��������?! ��-�...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "� ��� ������... ��� ����... ����� �����"+ GetSexPhrase("","�") +" �� �� � ������ ������ � ���. ������ �� ������� � ��� ��� ������, ����"+ GetSexPhrase("�","���") +". � �� ���� ������ ��������� ����!...";
				link.l1 = "��, � ����� �����...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // ����� ������ �� ������
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // �������� ��������
			ContraMeetManQuest_DeletePatrolFromShore(); // �� ������ ������ ���� �� �������
			break;
			
		// ��� ���
		case "ContraMeetManQuest_1":
			dialog.text = "�������! ��� ����� ���������� ����������� � ������� � �������������� - ��� �� ����� �� �������� �������������!";
				link.l1 = "�� ���� ������� �������. ������...";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // �������� ��������
			break;
		
		// �������� � ������� �������	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterReputation(PChar, -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "��-��... ������, "+ GetSexPhrase("������","������") +", �� ������ ����������� � �� ������ � ���... ��, �������, ����� ������� �� ������!";
				link.l1 = "�� �� ������� ������! ���������!";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "������� ��� ��� ���, " + PChar.name + ". ��������...";
				link.l1 = "...";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "��������������?! �� ��, �������... ���, �������� " + FindRussianMoneyString(iMoney) + " � ��������...";
				link.l1 = "�� �������...";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterReputation(PChar, 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- ����� "������� � �����"
			
		// ����� �� �������� ������ �������� -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "���, � �� �������, �� ������� ���� ������?! �-��, �������, ��������� ���� ����� �����������!";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // ������� ����������
			//{
				link.l1 = "������, ��������, �� ���������� �������� ������ � ��������� ���������� �� � ��� �� �������� �����. ��������, � ������ �� ���� ����� �������� �, ����� ����, �� ����� ��� �����."
				+ " � �����, ��� ��������� ����� ����� ���������, ���� �� ��������� ���� ��������������� �������...";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // ������
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "���, ��, ��, �������, �����. ��������� ����� ����� ���������. ������ ���, ������� ������ ������� �� ���� ��������� �������������.";
				link.l1 = "�������, ������, �� ���������� ��� �����. ������ ������� ��� ���� ����� ������������, ���� �� �� �� ������ �������� ����� �������� ������ - ������?!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "����� ���, ����� � �� �����. ������ ������� ��� ���������. ����� ����...";
				link.l1 = "��� ��� �� �����!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // ����� �� ����
			{
				dialog.text = "�������. ������ ������ �����������!";
					link.l1 = "���?! � ��� �� ������? �� �� ��������������...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // ������ ��� �������
			{
				if(rand(2) == 1) // �������
				{
					dialog.text = "������� �� ��������. ������ ������ �����... ��, ���-�� ����...";
						link.l1 = "���?!";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // ������ ������ ������
				{
					dialog.text = "�������. ������� �� ��������. ���, ����� " + FindRussianMoneyString(iMoney) ". � ����� - �������������� ������� ����� �� ��������...";
					link.l1 = "����� �� ��� �������. ��������.";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // ������ ��������� - �������� ��������� � ���������
			ChangeCharacterReputation(PChar, -5); // ������� ��������� - ���� ��������
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // ���� �� ��������� ����-����
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "������ ���� - �� � ����� �� � ��� �� ��������������. ��� ���, ��� � ����� ������������� - ��� ���� ������ � ������ ����.";
				link.l1 = "��������� � ���� ������� ����, ��� ��� ��� ����� �������?! �����, ������...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear() + "�� �� ��� ��������! ����������� � ������!";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // ������ ��� �����
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "�� �������"+ GetSexPhrase("��","���") +" ������� ��� �����, "+ GetSexPhrase("�����","�����") +"? ��� �, ���� �� ����. ������ � ������ ���� �����!";
				link.l1 = "...";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // ���
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // ������ � ��������
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // ����� ������� - �������� ������
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- ����� �� �������� ������ ��������
			
		// ��������� ���������. ����� � 1. ������ ����, �������� ���� -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // ���� ���� � �������
				{
					dialog.text = RandPhraseSimple("������� ����-��! � ���-��! ��������!.. ��!", "���-��! ������ ���� ������ ��... ��! �-�����.");
						link.l1 = "�-�-�... �-��. ����������� ���, �������� " + GetFullname(NPChar) + ".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // �� ������ ������ ����
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "���, ��� � ��� ���... ��� ����� �������� � ����� �� �������, ��� ������� �������� � ����� �� ������...";
							link.l1 = "����������� ���, �������� " + GetFullName(NPChar) + ". � - ������� " + PChar.name + ".";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("���������� � ����� ����� - � ���� � ��� ��� ��� �� �����!", "�� �������� �����, ���� ��� ��� ����?!", "� ������, ��� �� ������, ������ ��� ��� �����?!");
							link.l1 = "�� ���������� ���, �� �� ��� ���� ������!";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("����, ����! ����� ��� ����... ��!", "��������� �... ��! ��� �� ���������...");
					link.l1 = "��, ���� ��� ��� �������, �� ���� �� � ������?";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("��������������, ���-��-��! ��� ����� ����?", "�������� � �����, ���! ��� ������ ����... ��!");
					link.l1 = "���������, �� � �� �������"+ GetSexPhrase("��","��") +" �������� ������ � ������� ���������.";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "������� ������-��?.. ��� �� ���� ������� �� ������ ��������� � ��������. ������ �������, ���������� ���������! ���, ��� ����, ����������, � ��� ��� - ������! �������. ������������, ������ ��� � ������!";
				link.l1 = "����������, � ����"+ GetSexPhrase("","�") +" � ���� ���. � ������������ �����"+ GetSexPhrase("","�") +" ������ � ����. � ��� ��� ������� �����������-��������, � �� ��� ���...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = "�����"+ GetSexPhrase("�","���") +"! ������"+ GetSexPhrase("��","��") +"! ���, �� �������, ��� �����? � ���� ������! ��� �� ���� ���� �� �������� ������� �������� ����� �������� � ��������! �� � ����!.. �� � ��� ����!.. �� � ���� ��!.. �� ���������� ����!.. ��-�, �����... ������� ���������. ���� ������ ���������. ������ ��� ���� ���, ���������� ��������� ����� �����, ���� ��� ������� ����� � ��� ������� ��������!";
				link.l1 = "�-� �������... �����, ������� ������? ��� ��������, � ��� �������... ��� ��� ��������� �����-�� ������...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "��-��! ������� ��� ����� � ����, �� ���� ��� � ���� ���. ������ � ������ ��� ���� " + PChar.GenQuest.ChurchQuest_1.ToName + ", � �� �� � " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ". � ��� � ������ ����� � � ������� �������, �� � ������� ��� ��� �������. �������� ����� ����� ���������� �� ��� ��������� ���� ����� ������. ���� ������, ��� ������ ������ �� ����� - ��� �������� ��� ����� ������ � �����������. ��, � �������� ���� �� �������, ���� �������� ��� �������� � ���� ����������. ���� ����, ����� � ��� � ���� �����������, �������� �������, �� ��� �� ������� ����������. �������� ����� ���������, ���� ������ � �����, � ����� � � ������ ��� �����...";
				link.l1 = "�� ����, �� ������� ���������� ��� ����������� " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + " �������� � ������?..";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "����, ������ ��� � �����, ������ ��� ������ �� ���� �� ����� ���������� �� ���� �����, ��� ��������� ���, �� ����, �������� �� ��� ������, �� ��������... ��� � ������� ��� ����? � �����, ���� � �� ������ �������? �-�-�, ���� ���... ������ ��... ";
				link.l1 = "��-��, �� ���������� ���. ��������� �� ������ � ������������, ������ � �����"+ GetSexPhrase("","�") +" ������ ���. � ������ ��� ���� ���������� � ������� ��� ����... ��� ��������. ����� ����, ��������� � ������"+ GetSexPhrase("","�") +" � ������ ����������� ������������ � ����������� �������� � " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ", � � ������� � ����������� �������� ��� ����� �� ������. �� ��������?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "���������! ����� �����... �� ��� �� �� ��������. ��������!.. ����� ������ �����, �� �����... ������ ������ �� ���...";
				link.l1 = "� ��� ��� ��������... �������, �����. �����, �������� � ���������� � ������ ��� ������� ����.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...� �����! ����� �������� �����!.. �, �� - ����������� � �� �����. �� ������� �� ��������, �-"+ GetSexPhrase("�","��") +" ���-���-���, �� � ������ ������ � ������ �����, � ������ �� ��� ����� ������� �������� ���� ���������, ������� ������� ��� �� ���� ����� �����.";
				link.l1 = "���. ����������, ���� � ������ ���������. ��������� ��� ��������, � " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Dat") + " �� �������� �� ���� " + PChar.GenQuest.ChurchQuest_1.ToName + " ��������� ������������ �����, ������� ������� ��������� � " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + ", ��������� ������������ � �� �������.";
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "� �����������, ��! �� ���� ��������� �����, ���� ���, ���� �� ��������� ��� ������ ��������, � ������ � ������� ����� ���� ����� �� �������! ������ ��� ��� ��������� � ����� ��� � ������� �������� ������ ������� ������� � �������� �������, ������� ����� ������ � ������, � ������ ������� �������� ������ ������, �� ������� ������� ��� �� ����������.";
				link.l1 = "�-�... ������, � ������ ��� � � ������������� �������� ���� ������ � ���������� ������� �������, �� ������ � �����"+ GetSexPhrase("","�") +" �� ������ ������ ���� � ���������, ������� �� �������� � " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Dat") + ".";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "����� - �����, �������?! ����� �� ����� �������� ���� � ���, ��� � ������� ���������� � ��������� ���� ��������� �������!";
				link.l1 = "����� �������, ��� �� �������?! ������ � �����"+ GetSexPhrase("","�") +" �������� ��� �� ��������� ������������. ���� � ���, ��� ���� " + PChar.GenQuest.ChurchQuest_1.ToName + " ������ �������� ���, ����� ����� � �������� ���� ���������� �� ���������� � ����� �������� �����, � � ��� ��� ����������� �������� � " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + "...";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "������ ���, �����"+ GetSexPhrase("�","���") +", � ������ ����� ��� ��������� ����� ��������� �������� ���������. �������, ��� �� �� ����. ���� ��� �� ����� ������ ������������ ��� �������, ������ ���� ������ � ������������. ��������� �����!";
				link.l1 = "���������, �-� �������, � ����� �������� �������.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // ������ �� ������
		{
			dialog.text = "����� �������� �� ��������� ������������ ���� ���"+ GetSexPhrase("���","�") +", �����"+ GetSexPhrase("�","���") +", � ������������� � " +  XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + " �������, ������ ��� � ������ ��������� ��� ������ � � �� ��������, ���� �� ��� ��� �� ������, ��� �� ������� ��� ��� ���������, ������� ������� �������, ��� ������� " + NPChar.name + " �� ������ �����!";
				link.l1 = "��, �������� �������, ���� �� � ���...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// ���� ��������
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// ������ ���. ����� �������� �������!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // ������ ��������. ����� �������� �������!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // ����������. ����� �������!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // ����� ��������
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // ���� ����� ����
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "���� � ���, ��� ���������� � ���� � ���� ��� ������� ���. � ���� ��������� �� ������� ���� - ������� ����� � " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown) + " � ������� �� ��������� �����. ��� ��� ��? ���� ��� ������� �����. ����� ��������.";
//				link.l1 = "��� �. �� ������� �������������, �� ��� ���� ������������ �������� �����. ����� ��������, ��� ���������� ����.";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // ���������, �������� ���
				link.l2 = "� ���������� ����� ������"+ GetSexPhrase("","�") +" ���� ������� ���������, �� ��� ������� ��������� � �������� �������� ������� �� ���� ���� ������, �� ������ �� ��� ���, ������"+ GetSexPhrase("�","�") +". � ����"+ GetSexPhrase("��","��") +" ��������� ��������� ����� ���������, � ���� �� �� ������� ����������� ������ ��, ��� ��� �� �����������, ��� ������� �������� ������!";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // ����� �������� ��� ������������
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // ���� ����� ����
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "����, ����, ������� " + PChar.name + "! �� ��� ���������. ������ � ������, ���� �� �������� ������, �� ���������� ��� ��� ������� �� ���� ����� �������� �����, �� � ���� �������� ��� �������. ������ ���� ������������ ������������� � �������� � �����.";
				link.l1 = "� ���"+ GetSexPhrase("","�") +", ��� �� �� ������ ����� � �� ���������, �� � ��������� �� ���. ������� ��� ������ ��������� ��� ������ ���, ��� ��� ������ �������� ����� ������ ���������� �� ��������� ������ ��������.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // ���������, �������� ���
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// ���� ��������
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// ������ ���. ����� �������� �������!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // ������ ��������. ����� �������� �������!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // ����������. ����� �������!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Dat"));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // ����� ��������
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // ���� ����� ����
			break;
			
		// <-- ��������� ���������. ����� � 1. ������ ����, �������� ����
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("���������� ������...", "�� ����� ���!");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear() + "� ��� ����� �������� �� ������... ������ ������� ��������� ���� � �������, ���������� ��� �����!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear() + "� ��� ����� �������� �� ������... ������ ������� ��������� ���� � �������, ���������� ���� �����!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear() + "� ��� ����� �������� �� ������... ������ ������� ��������� ���� � �������, ���������� ����� ��� ���� �����!";
			}
			
				link.l1 = "�� ��� ��, ��������. ����� �������� ������ ����� �������� �� ����!";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "� �� �� ��������� ����� ���, � ���� � ��� ����, ����� ����.";
				link.l1 = "��� �������! � ���� � ������, ��� ��, �������� ��������.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "� � � ���� ����� ���������� � �� ���������. ���������� ����� - �����, ������ ���� ����������? �������� �������...";
				link.l1 = "��-������ � �����"+ GetSexPhrase("","�") +" �� ������"+ GetSexPhrase("��","��") +" ���������?!!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "�������, �������"+ GetSexPhrase("��","��") +", ����� ��� ��� �����! ��� ���� �� �������� �� ������� ������. ���, �������, ������ ������, � �������� ��������. ������ ���-�� ��� ��� ����������. ����� ������� � ��-�������� ��������� ������.";
					link.l1 = "���-�� ���������� �������... ��! �� ��� �� ���� ��� ���������!!! ��� �� � ���� �� ����������, ��� �������� ������� " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "?! ��� � ��� � ��������"+ GetSexPhrase("","�") +"!";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "������, �����"+ GetSexPhrase("���","��") +" �����! �� ������ ������������� � ����������� � ������ ������� ���-���. ���, ������� �� ��� ����: ������ ������, � �������� ��������. �������� �������� ������� ��������... ������, �� ������ �����.";
				link.l1 = "���-�� ���������� �������... ��! �� ��� �� ���� ��� ���������!!! ��� �� � ���� �� ����������, ��� �������� ������� " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + "?! ��� � ��� � ��������"+ GetSexPhrase("","�") +"!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "��, ������� �� ���������, �����"+ GetSexPhrase("�","���") +"!.. ����, � �� ������ ����� ����� �� ��������� ���� ������ �������...";
				link.l1 = "��� �� ��� ���������?! �������: ��� ����������� ������ ��������, ��� � ���� ������.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "����������, "+ GetSexPhrase("��� �������","�������") +", ��� �� ����� �����... ������� ����� ��� ��-������. ��� ������� �������� - ������� �� �� �������, � ����� � ��� ���. ��, �� �������� ��������� �������� � ������� ����� �� ��, ��� ���������� ����������. ��� ������� ����� - ������������, ��� �������� ����� ����, ��� �� ������������ � ����������������...";
				link.l1 = "� �� ������ �������, ���...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "��������� ��������� ��� ����� ���! ������ ����� ���� ������ ���������?! ��, �� ������-�� �� � �������... �������� ���� � �������� � �������, ��� � ���� �������, ��� �� ������ ����������, ��� ������� �� ����������!..";
				link.l1 = "����� ���� ���� � ������������, ���� � �� ���������"+ GetSexPhrase("","�") +".";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "������� ����. �� � �� ��� ��������"+ GetSexPhrase("��","��") +". ������ ������� ���� - ����� ������� ��� ������.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// ��� ������ ����, ���� �����
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// �������� ��������� �����������, ������� ������
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear() + "������� � ���� ��������: ���������� ���� ���������� ����, �� ������ � ���� ������, ����� �����!";
			}
			else
			{
				dialog.text = RandSwear() + "������� � ���, ������� ����������: ���������� ���� ���������� ����, �� ������ � ���� ������, ����� �����!";
			}
			
					link.l1 = "��� �� ��� ���������?! �������: ��� ����������� ������ ��� ��������, ��� � ���� ������.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "� ������� ������ - �� ���������� ���� ��������� ��� � ������ ��� ���������� ������ ������, � � ���� ���� �����.";
				link.l1 = "������ � ������ ���� ��������� � ��������!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "��� � ����, � ��� ���� �����, �� ���� �� ����������� ����������. ����� �� � ���� �������� ����� ������ ������� �����. � �� ���������� �� ���������� ������.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "�-�... ����� ������� ���� ����������� � ������� � ������ ���������. ��� ������� �� ����� �� ��� �������?";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// �� ������ ����!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("��","��"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("","�"));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // �������� �������� �����
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // ��������� ����������� �������. �������� �� � ���
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("��","���"));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "��� ������ �������� ���� �� �����, " + GetAddress_Form(pchar) + ", �� ������ ���� ����������. �� ��� ��������� ���� � ������ ��, ��� � ���� ����.";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "������ �� �������!.. � ���� � ����� ������" + FindRussianMoneyString(iMoney) + ". ������ � ������������!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "� ��� ����� �� �����������, ������ ����� - �� ��� ���� ���������� �� �������!"+ GetSexPhrase(" � ������� �����, ������� - �����, ������ - ���, ������� ���, ������ �����...","") +"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// ���� ����
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // ������ �� ������ ��������.
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","�"));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "�� �� ������ �� �� �������, ��� ������ ������� "+ GetSexPhrase("�� ���","� ���� ��� �����") +"?!";
				link.l1 = "� ��, ��� ������ ������ ����! � ������ ��������� �������������. � ������ ����"+ GetSexPhrase("��","��") +" �����������, ���� ���� ������� ����.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "����! ������ �� ��� ��������, �, ���� �� ������"+ GetSexPhrase("","�") +", �� � ������ ���� ������ ���� � ����������!";
				link.l1 = "����� ����� ���� ���� �� ����!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// ����� ���� ���� - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// �� ���-�� ����� �������� ������� � ������� ��� �������...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("��� �������� ����������, � ������","� ������"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ����� "������ �� ����������� �������"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "� ������ ������ � �� �����. �� ���� �� �����. ������ ������ ���� ��������, ���� �������� ������.";
			link.l1 = "��� ����� �������: ������� �������� ��� ������...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			iTemp=sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty);
			sTemp="PirateOnUninhabited_";
			for(i = 0; i < iTemp; i++)
			{
				rChar=CharacterFromID(sTemp + i);
				LAi_SetImmortal(rChar, false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(dRand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "������������ �������! �� ����� ��� ��� ������� ��� �� ������� " + PChar.GenQuest.PiratesOnUninhabited.MainPirateName + " � ��� �����... �� � ���������� ��������� � ����� ��������������� ���������. " +
					"��� " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name)) + " ������� ������� � ������� ����, � ������ ����� ������� ������� �� ���� ��������� ����. " +
					"����� " + (5 + dRand(7)) + " ������ �� �� ���� � ������ ������������� � ��������, ������� ������� ����� ���� ������-�� ��������.";
				link.l1 = RandPhraseSimple(RandPhraseSimple("��� �� �����������. �� ������ ����� ������ - ����� �� ��� ��� ��������� �� ����� �����", "�������... ��� �� � ����� �������, �� � ���� ������ ������� ����� �����, ����� ������� � ������..."),
					RandPhraseSimple("�� ��. ������� ������������, � ������� �����������.", "�� ��, ������ �� � ���������..."));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "���� �� ���������! ���� ������� " + PChar.GenQuest.PiratesOnUninhabited.BadPirateName + " �� �������� ������� ���������, ��� ��������� " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC) + " �� ����������� ������, ��� ��������� ������! " +
					"�� ��������, ��� ������ � ����� ������� ���, ��� ������� �������� �� �������� ���������! �� � ����� �� ����������� - ���������� ��������� �� ����� �������, ������ �������� � ����� ����...";
				link.l1 = RandPhraseSimple("�� ��� �����, ��������. ��������� � ���� ������ - �� ������������� ��������� ���������, � ��������� ����� �� ��������.", "�� ���� �� �������� � ��������? � ��� �����"+ GetSexPhrase("","�") +", ��� ����� �� ��������� �� ������, ��� �������, �������.");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + dRand(5);
			
			dialog.text = RandPhraseSimple("�������, �� �������� � ����������, �������� " + PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount)) + " ������������. ���� ��� ������ �� �� ���� ���������, �����, ��� �� ��� �� ������� ����.",
				"�������, �� ������� �� �� ����� ������� ��������� �������� " + PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount)) + " ������������?");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "�� ��... � ���� ��������� ��� ���������?";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("���, ��� ����� ����, �� �� ������� ��� �� ������ ���������� ������, �� ������ ��� � ������. ������� ���� �� ������, �� ���� ����������� ������������ ���� ����� ������ �����...",
				"��� �� ����� �� �������� ��� ��������������, �� �� ������� ������� � ����������, ���� ���� ��� �������� �����. ����� ��������� �������, � � ������� �������� �������..."),
				RandPhraseSimple("����� ����, �� ������� �� ������� �����������. ������� ����� � �������, � � ���� ��� ������� ����������� ����� ��� � ����������...", "��������"+ GetSexPhrase("","�") +" ��� ������������, �� �� ������� ������� � ����������. � �������� ������� ��������..."));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "��� ��, �������� ������, �� �����, ��� ����������� �� ����� ������������ ��������������� - ��� ������ �������? ��� ������� ������ �������� ���� ��� �� ����.";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "�-�, �� ���� ������ ��� �� �� �������� ���������� �� ����� �������������� ������... ��������� ��� � �����-������ ������ ����� �� ������� ������� ��� �����. � ������ �� �� ���� ����� ����������.";
			link.l1 = "��� �, � ��������, � ������� �� ����� ����������. ������������ � ������.";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "��. ��� ��������... ��� ��������� ������ ���, � ��� ���������� ��� �� ������ � ������� ������������ - � ���� �� ����� ��� � ���� ������ ������.";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "�-�, �������! � ���� ����� ���� ��� ������� � ���� ����� �� ����� ����������� ���� � ������������. � �� � ���� � �������... ��������� �� ���� �����������, ������� � ������ ��������� ����� �� �������������� �������. ����� �� ������ � �� ����� ���������� � ���� � ������������?..";
			link.l1 = "� ���� � �� ����� ���������� ��� ������ ������� ������ �������� ��� � ����� ����������� �����������.";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "��, � ���� ��� �������� �����. �����-�� ��������, � ������ �� ���� ���������� ����� �� ��� � �������?";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "����, �������... � ���� ��-�������� ��� �� ������������. ��� �, ������� ��������� ��� ������� �����. �� ������ - ��� �� ������� ����� ���� ���������...";
			link.l1 = "��� ������ � ����, ��� �� ���� �� ����� ����...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterReputation(PChar, -3.0);
		break;
		
		// ����� �� � �������
		case "PiratesOnUninhabited_8":
			dialog.text = "���-��! ��� � �����! �������, ��� ������ �� ��� ���� � ����� ���� � ������� ����� ���������� �������! � ������� ������� ����� ������ ����� �������� ������������� ��.";
			link.l1 = "��� � �� �����! ��������� � ������...";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("���� ������� ����������� �� " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " �������.");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // ������� ���������� �� ����� �� �������
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// ����� ������
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "�������, �������! �������� �� ����� ����� �������. ��� �� ��� ��������, ����� ���� ������ �������� ������...";
			link.l1 = "�� ��� � ���������.";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// ����� �� � ����������� - ������� ���� �� ���������� ������
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("���� ������� ����������� �� " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " �������.");
			
			ChangeCharacterReputation(PChar, 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // ������� ���������� �� ����� �� �������
			
			AddPassenger(PChar, NPChar, false); // �������� � ���������
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Dat");
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Acc")));
			}
			else
			{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Acc")));
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("���� �� �� �������, �������? ��������� ��������� � �����...", "��������, �������, ��� ����� ���������� � ��������.", "����� �����, ��� �� ������ ����� ����������!");
			link.l1 = "������������. ����� ������ ����� �� �����...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// ����� � �������� ��� � ������ ����� �� ��������� �������
		case "PiratesOnUninhabited_12":
			if(dRand(1) == 0)
			{
				// �������� ���������� ������ - ���� �������
				dialog.text = "������� ���, �������. �� ��� �� ������ � ���� �����... ��� �������� �������, � ����� ��� � ��� ����������� �����. ����� �� ������� ����� � ���.";
				link.l1 = "����� �� ������"+ GetSexPhrase("","�") +" �������� ����� �������. ������� � ����� ���... ��������.";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// ������� �����
				dialog.text = "�������, �� ������� �� ��������, �� �� ��������� �������������. ����� �� �������� ��. �� ����� �� �� ������� ��� ���� ������� �������� �� ������ �����? �� ����������� �� �����... ��� ������...";
				link.l1 = "���! �� ������ �������� ������������ �����������. ������������, ��� � ���� �������� � ��� ���������� - ��� �� �������� � ��� �������.";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "������ ��... � ������� �� ������ ��������?";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// ����� ������
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("������� ���, �������.", "�������, �� ��� ����� ����������.", "�� ����� �������� �� ���, ������� " + PChar.name + "!");
			link.l1 = "����� ���. ��������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "��, �������... � ���� �� �� ����� ��� ������ ������. ���� ����� ��� �������...";
			link.l1 = "��� �, ����������!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterReputation(PChar, 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// ����� ������
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "�� ������, �� " + iMoney + " ������� ����� �� �����, ��� �� ������ ��������... ���� ������� ������� �� �������, ��� ��� ������� ����� �����������, �� �� �������, ������� ������ �� ���� ����... ��-��...";
			link.l1 = RandPhraseSimple("��� ��� ��������! � ������, ��� ��� ������� �����... ������� �� ����� �� ��� - ��� ��� ���� �� � ����� ���!", "�� �� ����� ������ � ���"+ GetSexPhrase("","�") +" �������� ���, ��� ������� �� �������!");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "��� �, ��������... ������� ������ � ��� ������ �� ����"+ GetSexPhrase("��","��") +"?";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "��, ����� ��������! � � �����, �� ��� ������ ���������, ��� �� ������ �������� ��������. � � ���� ��� �������� �� ��������...";
			link.l1 = "��� �, ����������!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "��, ��� ��, �������, ��� �����?! �� ����������� �������� �� ��� ������... ���� �����-������ �������� �� ������...";
			link.l1 = "����� ���������...";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterReputation(PChar, 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("��","���"));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // ��������� �� ����� ����
			NPChar.DontClearDead = true;  // �� ������� ���� ����� 200�
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// ����� ������
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// ����� ���� - ��������� ����� ����
				dialog.text = "��, ��� ��, �������, ��� �����?! �� ����������� �������� �� ��� ������... ���� �����-������ �������� �� ������...";
				link.l1 = "����� ���������...";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "��-�, �������, � ���� ��� ����� ���������. � �� ������ ��������� ����� ���������� � ������� ������� �� ���� ������� �� �� �����������...";
				link.l1 = "��... ��� ������, ��� ������...";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "� ��� ������ � ����. ��� ����� ��� ������! � � ������ �������, � ������ �������� ��� ���!";
			link.l1 = "��� ������ � ����, ��� �� ���� �� ����� ����...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "� ������� ���, �������. � ��� ��������� �������... ���� ����� �������� � ������� ��������, �� ������� ����� ����� ������?.. � ���� � �������� ��� �����? �� ����������� ��� � ����� ����� �� ������� ������� ��� �����, � � ��� �� ��� ��� ����� �����... ���?";
			link.l1 = "��... � ��� ��������, ��� ��� ����� - �� ���������?";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "��-�, ������"+ GetSexPhrase("","�") +", ��� ���� ����� ����� �� ������, ��� ������ ������ �� ������� ��� ���������...";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "��� �... �� �� ���������� ��� ������... �� � ����� ������ �������� �������� �� ����� �����. � ������ �������� ��� ���...";
			link.l1 = "��� ������ � ����, ��� �� ���� �� ����� ����...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "� ��� ��������, ��� �� �� ������� ��� ������� � ������ �� �����?.. ��� ������ ������...";
			link.l1 = "�� ������, ��������, ��� �� ������������.";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// ����� � �������� ��� � ������ ����� �� ��������� �������. �������, ����� ��� ������� ����� ��������
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - ��� � ����������� ������
			
			dialog.text = "������� ����, ������� " + PChar.name + ". �� ��������"+ GetSexPhrase("","�") +" ��� ��������, ������ ����� " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_DAT) + " ��������� ���. ����� � ���� � ����� ���, �� � ���� �������� ��� ���������. ����������� � �����...";
			link.l1 = "��� ��� �� �����! ������ ��-���� ����� ���� ������...";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "� ���� � ����� ���� �� �������"+ GetSexPhrase("","�") +"... ����, �� ����"+ GetSexPhrase("","�") +" ������� - ���� ���-�� �� ���������"+ GetSexPhrase("","�") +".";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "��� ��� � ���� �������. ��� � �� �� ���� �����? ������ ������� �� �����...";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "�� �������... � ������� �� ������, �� ����� ��� �����!";
			link.l1 = "�� ������� � ������ ���� ��� ���?! ����� ������ ���� ���� ��������� ���� ���������?!";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "���... �� ����� ������, - ������� ������ �� ���������. �� ����� ���, � ����� �� �����...";
			link.l1 = "������� ���� ������! ����� ��� ������� ������ ��������� ����, ��� �����!";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// ����� ������
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "� ��� ��� ���������� ������? ������ � ��� ������� ���� ������ � ����� ������? ����� �������� �� �����... " + XI_ConvertString(sTitle + "Dat") + " � �������� " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + " ���� ������, � ������� �� ������ ���� ������. �� ���� �������"+ GetSexPhrase("��","��") +", �� ���� ��������� ������������. ����� ������ ��������, ���� �� � ������� �������...";
			link.l1 = "�� ������� � ������ ���� ��� ���?! ����� ������ ���� ���� ��������� ���� ���������?!";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "��, �����. ���� � �� ���� ��� ������� - ��-��� ����� �������.";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Acc")));
			
			// ������ ��� �����. �� ���������� 10 ���� � ����� ����� ������ ������� � �.�.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition = "PiratesOnUninhabited_TreasureLose";
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// ���� � �����, ������� ������ �����. � ��� ����� 10 ����, ����� ���� ��������
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("���������� " + sTemp + ", �� ���� �������.", "�� ���������� �� " + sTemp + ", � ���� �� ���� ������� ������.", "������� ���, �������.");
			link.l1 = "��������� ����������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "� ��� ��� ���������� ������? ������ � ��� ������� ���� ������ � ����� ������? ����� �������� �� �����... " + XI_ConvertString(sTitle + "Dat") + " � �������� " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + " ���� ������, � ������� �� ������ ���� ������. �� ���� �������"+ GetSexPhrase("��","��") +", �� ���� ��������� ������������. ����� ������ ��������, ���� �� � ������� �������...";
			link.l1 = "�� ������� � ������ ���� ��� ���?! ����� ������ ���� ���� ��������� ���� ���������?!";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// ������ � ����� � ����������
		case "PiratesOnUninhabited_34":
			dialog.text = "�� ��� ���"+ GetSexPhrase("��, ��������","��, �������") +",? � ��� ������� ���� � ��� ��������� �����?";
			link.l1 = "� ���������"+ GetSexPhrase("��","���") +" ��������� ������ ������� ����.";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "� ����� �� ��������� " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_GEN) + ".";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "��������� �� ����� ������"+ GetSexPhrase("","�") +"... �� �� �����, ��������, ������ �� ������������...";
			link.l1 = "���...";
			link.l1.go = "exit";
			link.l2 = "� ������ �� �����, ��� ������ ��� ���������?";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "������ ��� � ���� ����� ��������. � ��� ������� ����� - ��� ����� ��������� �� ������.";
			link.l1 = "������� ��������� ���� ����.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "� ���� �� �� ��� �� ������?";
			link.l1 = "�� �������, ������� " + LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat")) + " ���� ����������.";
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "�� ������ �������! ����� ����� ��� ������! ��, ��� � ���� �� ������. �������, ��� ������ �� ������ ������� ������ ������ � ����!";
			link.l1 = "�� ����� ��� ������ �� ������������ � �� ���� ������ �� �����...";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "��� �� �� ��� ��� ������, �� ������ ���������� �����. � �� ������ ���� �������, ��������� ������ � ���������� " + LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Acc")) + ". ��� ����� ������� ��������� � ���� " + PChar.GenQuest.PiratesOnUninhabited.MainPirateName + ".";
			link.l1 = "���� �� ��� �� ���� ����������� - ������ ������������ ������... � ������ ��������� �����.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// ����� �� PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + dRand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "� �� �������������� �������. �� ������ ���, ��� ��� �������� � ��������� " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL) + " ������ ������������� �� ����� ������� �����������. � ������������, ��� ��� �������� ������� �� ��������� ��������������, � ������ ��� � " + iBanditsCount + "-� ���� ���������������� ���������� �������� �� ���� ������ � ���� � ��������������...";
			link.l1 = "��� ��... ������ ���� �� ������� ������� ��� �������������. ��� � ��������� ��� �������.";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "���... ���� �� ��� ������� ������ ������ ������ �������� " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_GEN) + " �� ������ ����� �����������.";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "�������, ����� �� ������� ���������� ������� �����? �� ������� �� ��� ����, - ����� � ��� ������ �� ��������?.. ��� ������ �������� �� �����... �� �� ������ ����, �� ��� ������ ������� - � ����� ������ �� �� �����! ������� �� �������.";
			link.l1 = "� ��� �� ��� � ���� ��������� ������?";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "� ��� ������, �� � �����. ������ - � ����� ������� �������, ������ - � ������� ������.";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "������, ������� � �������. ������ ����� ���, - �� ��������! � ���� � ���� ������!";
				link.l1.go = "PiratesOnUninhabited_9"; // ����� � �������
			}
			
			link.l2 = "�� ������ � ��� ������. � ���� � ������� � ����� ����������� �������.";
			link.l2.go = "PiratesOnUninhabited_24"; // �������� � ����� ������
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "�����, �������� � ������, ������ ��� ����-������.";
				link.l3.go = "PiratesOnUninhabited_11"; // � ��������� � �� ������
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("�������, �������, �� �� ���������.", "�� ����� ��������� �������, �������.", "�������, ������ �������, ��� ��� ������� �� ������ ������!");
			link.l1 = RandPhraseSimple("������� � ��� ������.", "������������. ����� ������ ����� �� �����.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "� ��� ����� ����� ��������. �� ����� �� " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name + "Dat")) + " '" + sTitle + "' � ���������� �������������... ����� ���: ���� ��� ����� - ���� ����, � ������� ���. ������ � �������������, ����� �� �� " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC) + ". ������ �����, ���� �� � ����� �� �������, ����� ��� ��� �������, ���� �� ����� �� ��� �������...";
			link.l1 = "�� ������, ��������, ��� �� ������������.";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				NPChar.location = "none"; // ������� �� ������� ��� ������
				NPChar.location.locator = "";
			}
			
			Log_Info("���� ������� ����������� �� " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " �������.");
			
			ChangeCharacterReputation(PChar, 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // �������� � ���������
			SetCharacterRemovable(NPChar, false);
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // ������� ���������� �� ����� �� �������
			
			sTemp = XI_ConvertString(PChar.location + "Dat");
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Dat")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // ������ ������� �� �����
			
			DialogExit();
		break;
		
		// ������ � ����� � �����
		case "PiratesOnUninhabited_46":
			dialog.text = "������ ����� ���� �����?";
			link.l1 = "� ����"+ GetSexPhrase("��","��") +" �������� ���� ������ �� " + ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_GEN) + ". ������ ������?";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // ������� � ��������
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "���� � �� ������ ��� ������� ������... ������ ������ ����� �������������� �� ��� ����������...";
			link.l1 = "���... � ��� ����� ��� �������...";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // ������ �����
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "�������� ������, �������! ��, ��� � ��������������: ������� ���, ���� ���.";
			link.l1 = "��, �� �����. ��������� � ��������.";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // ������� �� �����
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// �� ������, ����� ������� � ����� ������� ���������
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "����������� ���, ������� " + PChar.name + ".";
			link.l1 = "��, ��� ���� ���� �������?";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "��-�, �� ���� ����� �� ���������, ��� � �. ������, ��� ������� ��� ����� ��������� ��� ����...";
			link.l1 = "�� ���������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// � �����, �������, ����� �������, ������� ����� ���� ���������, �������
		case "PiratesOnUninhabited_51":
			dialog.text = "�� ����� ��� ������� ������"+ GetSexPhrase("","�") +"?! �� � ��� ��������������?";
			link.l1 = "���� �� �����, ���� �� �� ������ ����? ������, ���"+ GetSexPhrase("","�") +" ��� ����� ����"+ GetSexPhrase("","��") +"?";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(dRand(1) == 1)
			{
				dialog.text = "��� ��� �����? ����� �������� �������"+ GetSexPhrase("","�") +"! � ��� ������ ���� ���� ���"+ GetSexPhrase("���","�") +" �������� ���������?";
				link.l1 = "������� ��������� ���� ����.";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + dRand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "��� ��� �����? ����� �������� �������"+ GetSexPhrase("","�") +"! �� ������ �� ������� �� ��� ��������? � �� ���� ����� " + FindRussianMoneyString(iMoney) + " �����! ��� ��� � ���� ������...";
				link.l1 = "� �� ����� �� �����? �� �������, ��� ���� ������ � ���� ��� ������"+ GetSexPhrase("","�") +".";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "׸�� �� ���� ������ � ����� ������� ������! ����� ���� ������� � �� ��������� ��� ������ �� �����!..";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "��� ��� ���� ������?! ���� ������� " + ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM) + " ��� �� ��� ������ � ���� ��������! �� ���� � ���� �������� �� ����, �� ������� ��������!.. ��� ������ ������ � �������� - �������� ��� �������, ��� ������ �������!!!";
			link.l1 = "����� �� ��� �������? � ���� ���� ������ �������� ������������. ����� �����, ���� �� ����������...";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","�"));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		case "Greedy":
			dialog.text = "�, �� ��� ������� ����������� ���"+ GetSexPhrase("��","��") +"? ����� ��� ����������. � ���� �� ������, � ��� ������� ����� ����������.";
			link.l1 = "���, ���. � �� ��� ���� ��� �����"+ GetSexPhrase("","�") +", ����� ��������� ����� ���� ��������.";
			link.l1.go = "Greedy_no";
			link.l2 = "� ���������� � ��� �����? � �� ��������"+ GetSexPhrase("��","���") +" ������ �����.";
			link.l2.go = "Greedy_3";
		break;
		
		case "Greedy_no":
			dialog.text = "��"+ GetSexPhrase("��","��") +" ��. � � ���� � ������� � ��������� ������... ����� ������� ���� ������� �������. ���������!";
			link.l1 = "� ������ �� ������ ������������� ������...";
			link.l1.go = "Greedy_end";
		break;
		
		case "Greedy_3":
			dialog.text = "�� �����. �� ���� ��� ����������. �� ���� � ������ ���� ����� � ������� ������, � ���� ������ �� ����� ������� �� ����������. ������ ����, ��������� ��� - ��� ����� ��������.";
			link.l1 = "����� ��. �������, ����������. �����, ��� ��� � �� ���"+ GetSexPhrase("��","��") +" ���.";
			link.l1.go = "Greedy_4";
			link.l2 = "�������, ��-���� ���. ������ � ��� �� �����!";
			link.l2.go = "Greedy_no";
		break;
		
		case "Greedy_4":
			if (!CheckAttribute(pchar,"GemGiven")) pchar.GemGiven = 1;
			else pchar.GemGiven = sti(pchar.GemGiven) + 1;
			TakeItemFromCharacter(pchar, "UsurersJew");
			ChangeCharacterReputation(pchar, 3);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			if (sti(pchar.GemGiven)>=5)
			{
				bool ok = (GetCharacterItem(Pchar, "map_part1")>0)  && (GetCharacterItem(Pchar, "map_part2")>0);
				if (GetCharacterItem(Pchar, "map_full") > 0 || ok)
				{
					
					dialog.text = "������� ���, �������. �� ����������� ��������� ��� �� ��������, ���� ��������� �����������. �� �������!";
					AddQuestRecordEx(loadedLocation.townsack + "UsurersJewel", "SeekUsurersJewel", "3");
				}
				else
				{
					if (GetCharacterItem(Pchar, "map_part1") > 0 && GetCharacterItem(Pchar, "map_part2") == 0 && GetCharacterItem(Pchar, "map_full") == 0)
					{
						dialog.text = "������� ���, �������. �� ��� ������� ����� ����� �����. ��� �� ����������, �� ����� ��� ����������. ������� ��� ��� �������.";
						AddQuestRecordEx(loadedLocation.townsack + "UsurersJewel", "SeekUsurersJewel", "4");
						GiveItem2Character(pchar, "map_part2");
						DeleteAttribute(pchar,"GemGiven");
					}
					if (GetCharacterItem(Pchar, "map_part1") == 0 && GetCharacterItem(Pchar, "map_part2") > 0 && GetCharacterItem(Pchar, "map_full") == 0)
					{
						dialog.text = "������� ���, �������. �� ��� ������� ����� ����� �����. ��� �� ����������, �� ����� ��� ����������. ������� ��� ��� �������.";
						AddQuestRecordEx(loadedLocation.townsack + "UsurersJewel", "SeekUsurersJewel", "4");
						GiveItem2Character(pchar, "map_part1");
						DeleteAttribute(pchar,"GemGiven");
					}
					if (GetCharacterItem(Pchar, "map_part1") == 0 && GetCharacterItem(Pchar, "map_part2") == 0 && GetCharacterItem(Pchar, "map_full") == 0)
					{
						aref item;
						Items_FindItem("map_full", &item);
						FillMapForTreasure(item);
						GiveItem2Character(pchar, "map_full");
						DeleteAttribute(pchar,"GemGiven");
						AddQuestRecordEx(loadedLocation.townsack + "UsurersJewel", "SeekUsurersJewel", "5");
						dialog.text = "������� ���, �������. ������� ��� ���� � �������. �� �� ���� �� ������ ���������������, �� ����� ��� ��� ����������...";
					}
				}
			}
			else 
			{
				AddQuestRecordEx(loadedLocation.townsack + "UsurersJewel", "SeekUsurersJewel", "3");
				dialog.text = "������� ���, �������. �� ����������� ��������� ��� �� ��������, ���� ��������� �����������. �� �������!";
			}
			link.l1 = "�������!";
			link.l1.go = "Greedy_good_end";
		break;
		
		case "Greedy_end":
			LAi_group_SetRelation("greedybastard", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("greedybastard", LAI_GROUP_PLAYER, true);
			LAi_SetFightMode(pchar, true);
			LAi_SetFightMode(npchar, true);
			for(i = 0; i < sti(npchar.quant); i++)
			{
				sld = CharacterFromID("GreedyBastard_"+pchar.location+"_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			DialogExit();
		break;
		
		case "Greedy_good_end":
			DialogExit();
			for(i = 0; i < sti(npchar.quant); i++)
			{
				sld = CharacterFromID("GreedyBastard_"+pchar.location+"_"+i);
				sld.lifeDay = 0;
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "OpenTheDoors", -1);
			}
		break;
		
		// �����
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 8; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_5"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// ��� ������ "������ �� ����������� �������"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "�������"; break;
		case 6: retValue = "��������"; break;
		case 7: retValue = "�������"; break;
		case 8: retValue = "���������"; break;
		case 9: retValue = "���������"; break;
		case 10: retValue = "���������"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(dRand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(dRand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BARQUE; break;
			case 2: retShipType = SHIP_FLEUT; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(dRand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_PINNACE; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(dRand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // ������ ����� ���������� � ��� �/�
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // ������ ����� ���������� � ��� �/�
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // ������ ����� ���������� � ��� �/�
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // ������ ����� ���������� � ��� �/�
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true));
	
 	SetCaptanModelByEncType(character, "pirate");
	
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
	character.DontRansackCaptain = true; //�� ���������
	
	SelAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // �������, �� ����� ������� ������
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // �������, � ����� ������� ������
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // ������� ������ �����
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + dRand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("������ �� ����������: ��� ����� �� " + character.fromCity + " � ���������� �: " + character.toShore);
}
