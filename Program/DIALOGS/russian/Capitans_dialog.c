// �������� � ��������� �� ������  Boal
//homo 25/06/06
#include "DIALOGS\russian\Rumours\Common_rumours.c"

string coolstory1[6] = {"���������","��������","���������","����������","����������","���������"};
string coolstory2[4] = {"���������","����������","�����������","����������"};

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
    //homo �����
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap, sGroup;
    string fort;
	string coolstories = "";
	int questionsstate = 0;

    if (CheckAttribute(aData, "nation"))
    {
	    sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
	    sGroup = "Sea_"+sCap+"1";
	    
	   // string myships  = GetCompanionQuantity(PChar);
       // string escships = Group_GetCharactersNum(sGroup);
        
        switch(sti(aData.conation))
        {
            case 0:  fort = "���������� ������"; break;
            case 1:  fort = "����������� ������"; break;
            case 2:  fort = "��������� ������"; break;
            case 3:  fort = "����������� ������"; break;
            case 4:  fort = "��������� ������"; break;
        }
        int ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
        int fortDamage = CheckFortInjuri();
        int SquadronDamage = CheckSquadronInjuri();
        
    }

    int iMoney;
	ref sld;
    
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 3000 + rand(10) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
    //homo 26/06/06
	ProcessCommonDialogRumors(NPChar, Link, Diag);
	if (npchar.id == "BlackBeardNPC" && CheckAttribute(npchar,"met") && Dialog.CurrentNode == "First time") Dialog.CurrentNode = "Titch_7";
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			DialogExit();
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "First time":
			if (!bDisableMapEnter)
			{
				if (npchar.id == "BlackBeardNPC")
				{
					dialog.text = "������ ������� ���� ����� ����? (������ ��������)";
					link.l1 = "��������, ������! ���� ����� " + GetFullName(Pchar) + ". � ���"+ GetSexPhrase("���","����")+", ��� �� ����� ���������� ��������.";
					link.l1.go = "Titch_1";
					link.l2 = "��-��! � ��� �����, ��������!";
					link.l2.go = "exit";
					break;
				}
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+"! � "+ GetFullName(NPChar) +" - ������� ������� ����� "+NationKingsName(NPChar)+". ��� ������� ��� �� ��� �� ����?";
    			}
    			else
                {
    			    Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+"! � ������� "+ GetFullName(NPChar) +". ��� ������� ��� �� ���� ����� �������?";
    			}
    			link.l1 = "���� ����� " + GetFullName(Pchar) + ". � ���� ����  � ��� ����!";
    			link.l1.go = "quests";
                link.l2 = "������ ����������, ������ "+ GetSexPhrase("�����","�����") +" ���������������� ���!";
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = "�� ��������, " + GetAddress_Form(NPChar) + ", ���� �����? ��� ������ �� �� ����������!";
    			link.l1 = "�� �����! ������� �� ���� �������.";
    			link.l1.go = "exit";
            }
			Diag.TempNode = "first time";
 		break;

        case "quests":
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = "� ��� ����������� ������, " + GetAddress_Form(NPChar)+".";
                link.l1 = "� �����"+ GetSexPhrase("","�") +" �� ������ ��������� ������� ����������.";
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //
                if (CheckAttribute(NPChar, "EncGroupName")) // ������ ��� �������� ������
                {
                    link.l2 = RandPhraseSimple("�� � �����, ��� �? �����, ����, ��� ��� ����������� ������ ����� ������� ������ �� ������ ������. ������� ����� ��� �����. ����� ������ ���� �������.",
                                               "����... � �� ����... ��� ������ ����, ����� � ����� ����� ������������ ������� ��������� ���� �����?.");
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = "������ �� �����?";
	    			link.l3.go = "price_1";
	    			link.l4 = "���������?";
	    			link.l4.go = "Trade_1";
    			}
				//--> ����� ����, ������ ������
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = "� ���������� ��������� �������, ��������� � ������� �����. �� ������ �� ������ ���������������?";
	    			link.l6.go = "MQ_step_1";
				}
				//<-- ����� ����, ������ ������
				//--> ����� ***���� ��������*** Sinistra
				if (CheckAttribute(pchar, "questTemp.PDM_CL_Ishem") && npchar.name == "�������" && npchar.lastname == "�� �������")
				{
	    			link.l10 = "����� �������� ������� ��� ������! (�������)";
	    			link.l10.go = "Antonio_Bitva";
					link.l11 = "���-��� ����� ����� ���. (������� ��������)";
	    			link.l11.go = "Antonio_1_4";
				}
				//<-- ����� ***���� ��������*** Sinistra
    			link.l5 = "������� ����������?";
			    link.l5.go = "Play_Game";
                link.l9 = "�����, ��� ����!";
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = "� �� ����������� ������ ���� � ����, ���������� � ������������ ����� �������. ��� ��� " + GetFullName(characterFromID(NPChar.MainCaptanId))+
                              ", �� ��������� �� ������� " + XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName) + " '" + characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name + "'.";
                link.l1 = "�������. ��� � ��������.";
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
		//--> ����� ***���� ��������*** Sinistra
		case "Antonio_Bitva":
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(loadedLocation, false);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_SetRelation("", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("", "PDM_CL_Lodka");
			DialogExit();
		break;
		
		case "Antonio_1_4":
			dialog.text = "� ��� �� �����? ���� �� ������ ������� ��� �������, �� �� �� ������. �������� ����� ���� �����, �������, ��� � ��������� �������������� ���� �� �� �����.";
			link.l1 = "� "+ GetSexPhrase("������","������") +" � ��� � ������������.";
			link.l1.go = "Antonio_1_5";
		break;
		
		case "Antonio_1_5":
			dialog.text = "� ���, � �� ���� ������ �� ���������. � � ����������� ������ � ��� ������� ���������!";
			link.l1 = "�������� ��� ���� �� ���� ���! (�������)";
			link.l1.go = "Antonio_Bitva";
			link.l2 = "��� �� ������� ��, ���� �� � �����������"+ GetSexPhrase("","�") +" ��� ����������� ������� ��� �������� ������� ��������?";
			link.l2.go = "Antonio_1_6";
			link.l3 = "��� ��, ����� ��������.";
			link.l3.go = "exit";
		break;
		
		case "Antonio_1_6":
			dialog.text = "� �� ����� �� ��� ��� ������ ����. �� ��� ����������, ���. �� ��� ��������, �������, ������� ����������� �� �������. ��� � ���� ������� � ��������?";
			link.l1 = "�������� ��������� ��� ������ ��� ���������� �� ���. �� ������, ��� ��� � �������� � ���� �� ����������, �� � ���"+ GetSexPhrase("","��") +" �� ������� ���.";
			link.l1.go = "Antonio_1_7";
		break;
		
		case "Antonio_1_7":
			dialog.text = "���� �� ��������� �� ���������������, �� ��� � ���� ������������� �� � ���, ������"+ GetSexPhrase("","���") +". ��������.";
			link.l1 = "�, �������� - �� ���� ���� �� ���������. � ���� ������� ��������, ��� ������"+ GetSexPhrase("","�") +" ��� �������. ����� �����, �� ���� ��� ������ �������� ����, �����, ��� ��� ������ ������ �� ������. � �� ������� ���������� ��� � �����, ��� ����� � ���.";
			link.l1.go = "Antonio_1_8";
			link.l2 = "�� ����� ��������.";
			link.l2.go = "exit";
		break;
		
		case "Antonio_1_8":
			dialog.text = "���������... ���� ���� ����� ���������, ������"+ GetSexPhrase("","���") +" "+pchar.name+". � ���� �� ���������, � �������, ����� ������ �������� ����� ����������� ���!";
			link.l1 = "� �������, ��-������, ����� ��� ������������������ ��������� �� ������ ��������?";
			link.l1.go = "Antonio_1_9";
		break;
		
		case "Antonio_1_9":
			int Bonus = sti(pchar.rank);
			if (Bonus <= 6) Bonus = 1;
			if (Bonus >= 7 && Bonus <= 12) Bonus = 1.2;
			if (Bonus >= 13) Bonus = 1.5;
			int Plata2 = 20000 + 2000 * sti(pchar.rank) * Bonus;
			dialog.text = "��, �� ���� ����� �������� � ��� ������������������. � �������, �������� " + Plata2 + ". ���� ������ � ��������� ����� ����� ��������� ��-�� ���������������.";
			link.l1 = "�����, ��� " + Plata2 + " - ��� ����������� �����. ����, � ����� ������� ��������, ��� � ���� ���������... ����� �� �������� ����, �� ��� ����� �������. ��� ����� ���� �����?";
			link.l1.go = "Antonio_1_10";
		break;
		
		case "Antonio_1_10":
			dialog.text = "��� ������ �������� �������� � ���� ������ - ����� �� ������������� �� ���, � ���� ����� ��� � ������ � 9 ���� �� ���� ���. �� ���������, ��� ������ ������.";
			link.l1 = "�������� ����, ������. �����!";
			link.l1.go = "Antonio_1_11";
		break;
		
		case "Antonio_1_11":
			sld = CharacterFromID("PDM_Octavio_Lambrini")
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Octavio_3_1";
			DeleteAttribute(pchar, "questTemp.PDM_CL_Tavern");
			DeleteAttribute(pchar, "questTemp.PDM_CL_Ishem");
			PChar.quest.PDM_CL_Antonio_Ubit.over = "yes";
			sld = CharacterFromID("PDM_CL_Antonio")
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Antonio_1_12";
			AddQuestRecord("PDM_Clan_Lambrini", "4");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("PDM_Clan_Lambrini", "sSex2", GetSexPhrase("��","���"));
			
			DialogExit();
		break;
		//<-- ����� ***���� ��������*** Sinistra
        case "Trade_1":
			dialog.text = "������ �� � ���?";
			link.l1 = "�������� �������� ������.";
			link.l1.go = "Trade_2";
			link.l2 = "� ���������"+ GetSexPhrase("","�") +".";
			link.l2.go = "exit";
		break;
		
		case "Trade_2":
			FillShipStore(NPChar);
	    	pchar.shiptrade.character = NPChar.id;
   			Diag.CurrentNode = Diag.TempNode;
		    DialogExit();
		    DeleteAttribute(pchar, "PriceList.StoreManIdx"); // �� ����� ��� �� ��������
		    LaunchStore(SHIP_STORE);
		break;
		
        case "Play_Game":
			dialog.text = "��� �� �����������?";
			link.l1 = "����������� � ����� �� �������� �������?";
			link.l1.go = "Card_Game";
   			link.l2 = "�������� ������� � �����-������?";
			link.l2.go = "Dice_Game";
			link.l10 = "����� ��������, �� ���� ���� ����.";
			link.l10.go = "exit";
		break;
        // ����� -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "� �� ���� ������ � �������� ���� � ������� ������������!";
    			link.l1 = "��� ��� ����� ������.";
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = "�������! ������� ��������� �� ����������� ���...";
    			link.l1 = "������������.";
    			link.l1.go = "Cards_begin";
    			link.l2 = "�� ����� �������� ������?";
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "��� �, ������� ������!";
			link.l1.go = "Cards_begin";
			link.l3 = "���, ��� �� ��� ����...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = "������� ����������� �� �������.";
			link.l1 = "������ �� 100 �����.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "������� �� 500 �������.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "�������, ��� ����.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = "������ ��������? � ��� ��� �����!";
                link.l1 = "������.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "������ � ����, � �� �� ���������� ������� �� ���������...";
                link.l1 = "����.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "������, ������ �� 100 �����.";
			link.l1 = "������!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "������ ��������? � ��� ��� 1500 �������!";
                link.l1 = "�����!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "���, ����� ������ �� ������� �� �����.";
                link.l1 = "��� ������.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "������, ������ �� 500 �����.";
			link.l1 = "������!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 500;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // ����� <--
	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = "� �� ���� ������ � �������� ���� � ������� ������������!";
    			link.l1 = "��� ��� ����� ������.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "�������! ����� ������� �� ������ ��������... ������ ��������...";
	    			link.l1 = "������������.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "�� ����� �������� ����?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "���, � ���� �������� �� �������. ���� ����.";
	    			link.l1 = "��� ��� ����� ������.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "��� �, ������� ������!";
			link.l1.go = "Dice_begin";
			link.l3 = "���, ��� �� ��� ����...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = "������� ����������� �� �������.";
			link.l1 = "������ �� 50 ����� �� �����.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "������� �� 200 ������� �� �����.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "�������, ��� ����.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "� ���� ����� ����� �������������"+ GetSexPhrase("��� ������","�� ������") +". � �� ���� � ����� ������ � ����� ������.";
                link.l1 = "��� ����! �� � �� �����.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "������ ��������? � ��� ��� �����!";
                link.l1 = "������.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "���! ����� ���������� � ������, � �� ������� � ����������� � ������ �� �����...";
                link.l1 = "����.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "������, ������ �� 50 �����.";
			link.l1 = "������!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 50;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
            if (!CheckDiceGameSmallRate())
		    {
                dialog.text = "� ���� ����� ����� �������������"+ GetSexPhrase("��� ������","�� ������") +". � �� ���� � ����� ������ � ����� ������.";
                link.l1 = "��� ����! �� � �� �����.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "� ������, ��� �� ����� ������ �������. � �� ���� ������ � ����� �� ����� ������� �������.";
                link.l1 = "������� �� ����� ������ �������?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "��������, ��� ����.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "������ ��������? � ��� ��� 1500 �������!";
                link.l1 = "�����!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "���, ����� ������ �� ������� �� �����.";
                link.l1 = "��� ������.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "������, ������ �� 200 ����� �� �����.";
			link.l1 = "������!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 200;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
        case "price_1":
			if (CheckNPCQuestDate(npchar, "trade_date"))
			{
                SetNPCQuestDate(npchar, "trade_date");
				iMoney = findPriceStoreMan(NPChar);
	            if (iMoney == -1)
	            {
	                Dialog.Text = "����� ��� ��� �����? ��� ��� ������ ����.";
					Link.l1 = "��� ��� ����� ������.";
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = "� ��� �� ������ " + GetCityName(sld.City) + ".";
					Link.l1 = "����� ���� �� ������ � ������� ��������?";
					Link.l1.go = "price_2";
					Link.l9 = "��� ��� ����.";
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = "� �� ��� ��� ��� ������. �� ���������� ���� �� ��������.";
				Link.l1 = "��, �� �����. ��������.";
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = "��� �����... (�� �������� ������ ��� �� ������).";
			Link.l1 = "������� �������!";
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            {
                Dialog.text = "��-��! ������� �����. ��� �����, ��� � ���� ������ ��������. ���������� �� ���� ������� � ������ ������ � ���.";
                link.l1 = "������ - �� ������ ������...";
                link.l1.go = "Boarding";
            }
            else
            {
                if(rand(21) > (GetSummonSkillFromNameToOld(PChar, SKILL_GRAPPLING) + GetSummonSkillFromNameToOld(PChar, SKILL_LEADERSHIP)) )
                {
                    Dialog.text = "�������� �� ������� ���� ������� ����, �������, �� ����� ����� �������. � ������� ���������� � ������� ��� ��������� �� ���� ������� � ������� ������ � ���.";
                    link.l1 = "�� ��� ���������, ��� ������� ������ �� ���� ������!";
                    link.l1.go = "Boarding";
                }
                else
                {
                    Pchar.GenQuest.MoneyForCaptureShip = makeint(100 + (Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName))*(7 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
                    Dialog.text = RandSwear() + "��, � �������� � ����� �����������. ���� ��-������, �� ������� " +
                                  XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter") + " �� ������� ��� �������������!";
                    link.l1 = "������������. ����� � "+Pchar.GenQuest.MoneyForCaptureShip+" ������� ���� ������ �������, "+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = "��. �� �����. � �������"+ GetSexPhrase("","�") +"!";
                    link.l2.go = "exit";
                }
            }
            // ��� ����� ���� ������� ���������� ������
            Diag.TempNode = "Go_away";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away =  lastspeakdate(); // boal ������������� :)
        break;

        case "rumours":
			Dialog.Text = SelectRumour(); // to_do
			Link.l1 = RandPhraseSimple(RandSwear() + "��� ����� ���������. ������ ������?",
                                     "��� ���� ����.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("�������, ������ �����������.",
                                     "����� ��������.");
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = "���������� � ����� �������!";
			Link.l1 = "��� �����.";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = "��� �������� ��� �������. ������ ������ � ��� �� �����, "+GetAddress_Form(NPChar)+".";
			Link.l1 = "����. �� ������� � ����!";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = "��������! � ������ ���������� ���!";
			Link.l1 = "������������!";
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterReputation(pchar, -5);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 7 + rand(10));
        break;

        case "Boarding":
            if (CheckAttribute(NPChar, "MainCaptanId"))
            {
                PChar.StartBattleAfterDeck = true;
                PChar.StartBattleMainCaptanId = NPChar.MainCaptanId;
                PChar.StartBattleEncGroupName = NPChar.EncGroupName;
            }
            DialogExit();
            Diag.CurrentNode = Diag.TempNode;
        break;
        
        case "QuestAboardCabinDialog":  // �������� ������, � ���� �� ��������, ��� ������ SetQuestAboardCabinDialog
			Diag.TempNode = "QuestAboardCabinDialog";
            Dialog.Text = "����, ��� � ����� �����. ��� �� ������ �� ����?";
			Link.l1 = "�����!";
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = "����� � ����.";
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = "����� ��� �����, ����� (c)";  // �������, ����� �� ���� ���  QuestAboardCabinDialog_1 ��� QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // ����� �������� ��������� �������, �� ������ ��� ������� � ��...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = "��, ��� �� ��� ���������!";
			Link.l1 = "� ��� ��� ��������?";
			Link.l1.go = "exit";
			// ��� ����� ������������ �� ���������� (NPChar) ��� �������� ������� ������ ������ ��
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // ��� ������ �������
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = "������, ���� �����!";
			Link.l1 = "��� �� �����!";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = "�� �������!";
			Link.l1 = "��� � ������, ������ �������� � ����.";
			if (rand(1) == 1)  // ������!!!
			{
				Link.l1.go = "QuestAboardCabinDialog_2";
			}
			else
			{
			    Link.l1.go = "QuestAboardCabinDialog_3_1";
			}
			TakeNItems(NPChar, "Chest", -1);
			TakeNItems(pchar, "Chest", 1);
		break;
		
		case "QuestAboardCabinDialog_3_1":
			Dialog.Text = ""+ GetSexPhrase("������","������") +", ��������"+ GetSexPhrase("","�") +", ��� �����"+ GetSexPhrase("","�") +" � ��� ���� � ����? ���!";
			Link.l1 = "����� ����� ����� ������.";
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. ����� ����, ������ ������
		case "MQ_step_1":
			Dialog.Text = "���, �������� ��������������� �������, �������� �� ���������, � �� �����.";
			Link.l1 = "�������.";
			Link.l1.go = "exit";
		break;
		
		//homo ������� �� �����
		case "MerchantTrap_Abordage":

			Dialog.Text = "������ "+NationKingsName(NPChar)+" ��������, "+ GetSexPhrase("������ �����","������ ��������") +"! � ���� �������� ����� �� ������������� ����, ��� �� ��������, �� ��� "+NationNameSK(sti(NPChar.nation))+"�� �������, ������� �� �������"+ GetSexPhrase("","�") +".";
			Link.l1 = "��� �� �� ��� - ��� ��������.";
			Link.l1.go = "exit";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam"); // ��� ������ �������
		break;
		
		case "Siegehelp":
		
            ref rchar = Group_GetGroupCommander(sGroup);
            if (NPChar.id == rchar.id)
            {
    			
    			dialog.text = "� ��� ������, �� ������� �������� ������������ ���� ������ ������, � ��� ���� ��� � " + fort +
                          " � ��� ����� ���������� ����� ��������.";
                link.l1 = "������ ������� � �����, " + GetAddress_FormToNPC(NPChar) + ".";
                link.l1.go = "attack_fort";

                link.l2 = "� ����� ������ �� ���� ��� ������ �����������. ��������, "+ GetAddress_FormToNPC(NPChar) + ".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = "� �� ����������� ������ ���� � ����, ���������� � ������������ ����� �������. ��� ��� " + GetFullName(rchar)+
                              ", �� ��������� �� ������� " + XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName) + " ''" + rchar.Ship.Name + "''.";
                link.l1 = "�������. ��� � ��������.";
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = "� � ��� �� ���� ����?";
                link.l1 = "� ���� ������ ��� ���������� ���� ������� " +GetConvertStr(aData.Colony+" Town", "LocLables.txt")+ " � ��������� �����, � ������, ���������� � ������ ������ ������, �� ������� ����� �����.";
                link.l1.go = "Siegehelp_1";
                link.l2 = "����������, ��� ���� ���� �� ����������� ������ ��������. ��������, "+ GetAddress_FormToNPC(NPChar) + ".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = "��� ����� ��? ��� ��������, �� ��� ��� ��������?";
            link.l1 = "�� ����� - �����"+ GetSexPhrase("","�") +".";
			link.l1.go = "exit";
			NPChar.DeckDialogNode = "Siegehelp_0";
            Diag.TempNode = "Siegehelp_0";

		break;
		
		case "Siegehelp_1":
            SiegeResult("");
            if (sti(aData.win)==0)
            {
                dialog.text = "� ����� �� ����� ������ �� ������������� ��������?";
                link.l1 = "��������.";
                link.l1.go = "Big_part";
                link.l2 = "���� �����.";
                link.l2.go = "Middle_part";
                link.l3 = "��������� �����.";
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = "��� �� ��������� ���� ������, �������! � �� �������� �� � ���� ������, ��� ��� � ����� ������ ������� ��� �������.";
                link.l1 = "������ ����� �����������, " + GetAddress_FormToNPC(NPChar) + ", ������� ����� ���������� ������.";
                link.l1.go = "attack_fort_03";
                link.l2 = "� ����� ������ �� ���� ��� ������ �����������, " + GetAddress_FormToNPC(NPChar) + ". ��������!";
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":


            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = "� ������ �������, ��� ������� ��� ������� ��������� � ���� ��������, � ������������ ��� �� �� ��������. ���� �� �������� �� " + GetPart(4) + ", ��, � �����, �� ������ ������������.";
                link.l1 = "���� ��� ����������, " + GetAddress_FormToNPC(NPChar) + ". � ��������� ����� ���� �������, � �� �� ����� ������� ���������� ��� ����� ����������� ������.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "� ���� �� ��� ������, " + GetAddress_FormToNPC(NPChar) + ". ����� ��������, ��� �������"+ GetSexPhrase("","�") +" ��� �� �������� ���. ��������.";
                link.l2.go = "exit";
            }else{
                dialog.text = "� ���� ������� ���������� ��������, ����� �������� ���� ���� � ��� � ����, ��� ������ ������ �������. � ������ ���������� �������� ��� �������, ������� ���� ������� ������!";
                link.l1 = "�� ��� �, � ����� ������, " + GetAddress_FormToNPC(NPChar) + ", ��������� �����������. ��������!";
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = "������ ����� ������ ��������� ������� ���� �������, � ����� ����� �������� ����� ���������� �� � ���� ������. � �������� �� ���� ������� � �������� ���� ������.";
                link.l1 = "�������, " + GetAddress_FormToNPC(NPChar) + ", � ����� ������ �� ������� ���� �������, � �� �� ���������� ��� ����� ����������� �����.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 2;
            }
            else
            {
                dialog.text = "�� ��������� ��, �������? � ��� " + GetNumShips(GetCompanionQuantity(PChar)) +
                              ", � ���� ������� " + GetNumShips(Group_GetCharactersNum(sGroup)) + ". � ���� ��� ���������� " + GetPart(4) +
                              ". � � �����, ��� ���������.";
                aData.PartAttaksFort = 4;
                link.l1 = "� ������"+ GetSexPhrase("��","��") +", " + GetAddress_FormToNPC(NPChar) + ", � ����� ������, � ���� �� ���� ������ �����, � �� �� ���������� ��� ����� ����������� ������.";
                link.l1.go = "attack_fort_04";
                link.l2 = "� ���������, � ��� �� �����, " + GetAddress_FormToNPC(NPChar) + ". ��� ������ �� � ��� �������������. ��������.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = "��� ������ ���� ����� ��������, �� ���������� �������� ������� ��������� ����� �� �����, � ������ ��� ��������� ��� � ����� ������, ���, � �������, �� � ���������� � ����.";
            link.l1 = "�� ���� � �������. �� �������, " + GetAddress_FormToNPC(NPChar) + "!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = "�������, � ��������� �� ���� �������. ���������� �������� ����������� ��� ����� �� ������������� ����� ����� ��������. � ������ ��������� ���������� ���� �� �������� ���� ����� ������.";
                link.l1 = "�� ��� � ������, ��� �� ������������, " + GetAddress_FormToNPC(NPChar) + ". � ���������� ����� ������ ����� ����� ��������� ����.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
                dialog.text = "�� ��������� ��, �������? � ��� " + GetNumShips(GetCompanionQuantity(PChar)) + ", � ���� ������� " + GetNumShips(Group_GetCharactersNum(sGroup)) + ". � ���� ��� ���������� " + GetPart(4) + ". � � �����, ��� ���������.";
                link.l1 = "� "+ GetSexPhrase("��������","��������") +", " + GetAddress_FormToNPC(NPChar) + ", � ����� ������ � ���� �� ���� ����� �����, � �� ���������� ��� ����� ����������� ������.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "� ���������, � ��� �� �����, " + GetAddress_FormToNPC(NPChar) + ". ��� ������ �� � ��� �������������. ��������.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = "������� ���� ������� �������� ���������, ��� ��� ������ ���� ��� �� ��������. � �������� �� ��� ������� � �������� ���� �����������.";
            link.l1 = "� ���"+ GetSexPhrase("","�") +", ��� �� ������ ������������, " + GetAddress_FormToNPC(NPChar) + ". � ���������� ����� ������ ����� ����� �������� � ��� � ������ ����� �����.";
            link.l1.go = "attack_fort_04";
            aData.PartAttaksFort = 4;
            Diag.TempNode = "Siegehelp_0";
        break;
		
		case "Talk_Capture_City":
            AfterTownBattle();  // ���, ��� ��������
            LAi_LoginInCaptureTown(NPChar, false);
            aData.win = 1;
            EndOfTheSiege("End");
            NPChar.location = "";
            int ilt = makeint(sti(aData.loot)/sti(aData.PartAttaksFort));
            dialog.text = "������������, �������! ���� ����� � ���� ������, �� ���-���� ��� ������� ������� �������� ������������� ���������� ������. ������ ���������� " + sti(aData.loot)+
                          " �������. � �� ������ �������� �� ��������� "+ilt+
                          ". ��� ���� ������, �� ��, ����������, ���������. � ������ ����� ���� ��������, �� ���� ���� ����.";
            link.l1 = "� ����� ������ ��������� �����������, " + GetAddress_FormToNPC(NPChar) + ". ��������!";
            link.l1.go = "exit";
            //AddDialogExitQuest("End_Siege_and_Attaks_City");

            Diag.TempNode = "no_return_02";
            AddMoneyToCharacter(PChar, ilt);
            ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
            ChangeCharacterReputation(PChar, 10);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
            AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Defence", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Fortune", 80);
            aData.loot = sti(aData.loot) - ilt;
            if (CheckAttribute(PChar, "quest.LeaveTown")) Pchar.quest.LeaveTown.over = "yes";
            //--> �����
            SiegeRumour("������ ����, ��� �� ������� ����� ������� ��� ������ "+NationNameSK(sti(aData.conation))+"�� ������� - "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+"! �� ��� ���������� ���, "+ GetAddress_Form(NPChar)+".", "", sti(aData.nation), -1, 30, 3);
            //<-- �����
		break;

        case "no_return_02":
            dialog.text = "����������� ���, �������! � ��� �� ��� ����?";
            link.l1 = "�������, " + GetAddress_FormToNPC(NPChar) + ". ��������!";
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = "� ��� ������, �� ������� �������� ������������ ���� ������ ������, � ����� �����. �� ���� ��������� ������ ������ ���������� ���������, � � ���� �� ��� ���������� ������ ��� �������������� ������� � �������� ����, ������� ����� ������������ ��������� ������ ������.";
                          
                link.l1 = "� ����� ������ �� ���� ��� ������ �����������. ��������, "+ GetAddress_FormToNPC(NPChar) + ".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = "� �� ����������� ������ ���� � ����, ���������� � ������������ ����� �������. ��� ��� " + GetFullName(rch)+
                              ", �� ��������� �� ������� " + XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName) + " ''" + rch.Ship.Name + "''.";
                link.l1 = "�������. ��� � ��������.";
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "Titch_1":
			Dialog.text = "���� �����. ��� ��� ���� �������� ���� �� ����� � �������� ��� ������, � ������ ���������. �� � ������ ���������, ��� �� ����� �����������.";
			link.l1 = "���� ��������? � ��� �� �������� ��� �������� �����������?";
			link.l1.go = "Titch_2";
		break;
		
		case "Titch_2":
			Dialog.text = "� ��� ������ ����, ���, ��� ������, �� ���� ������ � ������� ��� �������� ������ ���� �� ����.";
			link.l1 = "� ������...";
			link.l1.go = "Titch_3";
		break;
		
		case "Titch_3":
			Dialog.text = "���� ��������� ����� �� ������� 5 �������� �������� � ��������� �� �������, ����� �������� ������� ���� �������� ��. ���� ������� ��� ������, ���������� ������ ��������� ��� ���. �� ������ ������ ����� ����, ��� � ���� ����� �������� � ���� �����.";
			link.l1 = "��� ����� ������, ��� ����� ��������. ��� �� �����, � �������� ����������� ������ � ������! ��� �������!";
			link.l1.go = "Titch_4";
		break;
		
		case "Titch_4":
			Dialog.text = "��� ���������� ��������� ���� ������� ����������, ���� ��� ������ ������ ���������� ���� ������ ��� �������. ���� ����� ������� ���� �� �������, �� � ���� ����� ��������� - ��� �� ���. ��������� ������� � �������� ����. ���� �� ����������, �� ��� ��� �������� ������ ���� ��...";
			link.l1 = "�����, �����... ���� � ������ ��� �� ������ �� �������. ������ ���������? � ���������� ��... �� � ������� ������! �� ������ � ������� �����. �������, ��� ����� �������.";
			link.l1.go = "Titch_5";
		break;
		
		case "Titch_5":
			Dialog.text = "����� � ���� ������� �������, �� ������ ��� ����� ������� ��. � ����� �������, ��� �� ��� ��� ������. � ���������� ������� ������ ���� �� ���������� ������ �� � ������� ������.";
			link.l1 = "��... � ����� ������ � ����. ��� ���, ��� ���, ��� � ��������, �� ��� ��� �����������.";
			link.l1.go = "Titch_6";
		break;
		
		case "Titch_6":
			Dialog.text = "�� � ����������, ������� �����. ����� ���� ����� �� ������� � �� ����� �� ������. ������ ����� ��������!";
			link.l1 = "� ���� ����� ������������ ������... ��� ���������� �� ������ ��� ���-�� �������.";
			link.l1.go = "Titch_7";
		break;
		
		case "Titch_7":
			npchar.met = true;
			if (!CheckAttribute(pchar,"ShipsSurr")) pchar.ShipsSurr = 0;
			Dialog.text = "��?! � ��� �������?";
			if (!CheckAttribute(npchar,"Duel"))
			{
				link.l1 = "�����, � ���� ������ ��� �������� ������� ������� � ������ �� ���� ����. ��� � ����� ����� �������?";
				link.l1.go = "Titch_duel";
			}
			if (!CheckAttribute(npchar,"Cards"))
			{
				link.l2 = "������� � �����?";
				link.l2.go = "Titch_cards";
			}
			if (!CheckAttribute(npchar,"questions"))
			{
				link.l3 = "������� ���� �� ������ � ����. ���� ��� �� ������� �������.";
				link.l3.go = "Titch_questions";
			}
			if (!CheckAttribute(npchar,"ships_sur") && CheckAttribute(pchar,"ShipsSurr") && sti(pchar.ShipsSurr) >= 5)
			{
				link.l4 = "� ��������"+ GetSexPhrase("","�") +" ������ � ������ 5 �������� ��������.";
				link.l4.go = "Titch_ships_sur";
			}
			if (CheckAttribute(npchar,"Duel") && CheckAttribute(npchar,"Cards") && CheckAttribute(npchar,"questions") && CheckAttribute(npchar,"ships_sur") && !CheckAttribute(pchar,"Titch_seabattle"))
			{
				link.l5 = "�������� ������ �������� � ����. � �����"+ GetSexPhrase("","�") +"!";
				link.l5.go = "Titch_seabattle";
			}
			link.l6 = "���� ������.";
			link.l6.go = "exit";
			if (bBettaTestMode)
			{
				link.l7 = "[����] ������� ��������";
				link.l7.go = "Titch_seabattle";
			}
		break;
		
		case "Titch_seabattle":
			Dialog.text = "��, � ����� �� ��� � �� ��������� �� ����� ������. �������� �� ������ �������!";
			link.l1 = "�� ���������, ������ ������. ��� �������� �� ������ ������� - �����!";
			link.l1.go = "Titch_seabattle_exit";
		break;
		
		case "Titch_seabattle_exit":
			DialogExit();
			Diag.CurrentNode = Diag.TempNode;
			DeleteAttribute(npchar,"AlwaysFriend");
			Group_SetEnemyToCharacter("BlackBeardGroup", GetMainCharacterIndex());
			SetCharacterRelationBoth(nMainCharacterIndex, sti(npchar.index), RELATION_ENEMY);
			Group_SetTaskAttack("BlackBeardGroup", PLAYER_GROUP);
			Group_LockTask("BlackBeardGroup");
			pchar.Titch_seabattle = true;
		break;
		
		case "Titch_Seabattle_won":
			Dialog.text = "���-�, �������, ��� �����. �� �������"+ GetSexPhrase("��","���") +" � ����� ����� ��������. ������ �� ��� ��������.";
			link.l1 = "� ��� �� �����?";
			link.l1.go = "Titch_Seabattle_won_2";
		break;
		
		case "Titch_Seabattle_won_2":
			Dialog.text = "��� ���� ������������ � ��� ����. ���� ������� ������ ����, ����� ��� � ������� ���� ���.";
			link.l1 = "������� ���? � ��� ��?";
			link.l1.go = "Titch_Seabattle_won_3";
		break;
		
		case "Titch_Seabattle_won_3":
			Dialog.text = "������ ������ ��� ���� �� �������������, �� ������� ������ ��������.";
			if (AddSPECIALValue(pchar, SPECIAL_S, 0) != SPECIAL_MAX)
			{
				Link.l1 = "����";
				Link.l1.go = "Strength";
			}
			if (AddSPECIALValue(pchar, SPECIAL_P, 0) != SPECIAL_MAX)
			{
				Link.l2 = "����������";
				Link.l2.go = "Perception";
			}
			if (AddSPECIALValue(pchar, SPECIAL_A, 0) != SPECIAL_MAX)
			{
				Link.l3 = "�������";
				Link.l3.go = "Agility";
			}
			if (AddSPECIALValue(pchar, SPECIAL_C, 0) != SPECIAL_MAX)
			{
				Link.l4 = "���������";
				Link.l4.go = "Charisma";
			}
			if (AddSPECIALValue(pchar, SPECIAL_I, 0) != SPECIAL_MAX)
			{
				Link.l5 = "�����������";
				Link.l5.go = "Intellect";
			}
			if (AddSPECIALValue(pchar, SPECIAL_E, 0) != SPECIAL_MAX)
			{
			Link.l6 = "������������";
			Link.l6.go = "Endurance";
			}
			if (AddSPECIALValue(pchar, SPECIAL_L, 0) != SPECIAL_MAX)
			{
				Link.l7 = "�����";
				Link.l7.go = "Luck";
			}
			Link.l8 = "���� �� � ��� ����������. ��� ������?";
			Link.l8.go = "Titch_Seabattle_won_4";
		break;
		
		case "Strength":
			dialog.text =  "����, ������� �����. ������! ������ �� �������� �������.";
			Link.l1 = "� ��� ������?";
			Link.l1.go = "Titch_Seabattle_won_4";
			AddSPECIALValue(pchar, SPECIAL_S, 1);
		break;
        case "Perception":
			dialog.text =  "����������, ����� ������. ������! ������ �� �������� �������.";
			Link.l1 = "� ��� ������?";
			Link.l1.go = "Titch_Seabattle_won_4";
			AddSPECIALValue(pchar, SPECIAL_P, 1);
		break;
        case "Endurance":
			dialog.text =  "�������������, ������. ������! ������ �� �������� �������.";
			Link.l1 = "� ��� ������?";
			Link.l1.go = "Titch_Seabattle_won_4";
			AddSPECIALValue(pchar, SPECIAL_E, 1);
		break;
        case "Charisma":
			dialog.text =  "�������? ��, ������� �����. ������! ������ �� �������� �������.";
			Link.l1 = "� ��� ������?";
			Link.l1.go = "Titch_Seabattle_won_4";
			AddSPECIALValue(pchar, SPECIAL_C, 1);
		break;
        case "Intellect":
			dialog.text =  "���������, ������� �����. ������! ������ �� �������� �������.";
			Link.l1 = "� ��� ������?";
			Link.l1.go = "Titch_Seabattle_won_4";
			AddSPECIALValue(pchar, SPECIAL_I, 1);
		break;
        case "Agility":
			dialog.text =  "��������, ������. ������! ������ �� �������� �������.";
			Link.l1 = "� ��� ������?";
			Link.l1.go = "Titch_Seabattle_won_4";
			AddSPECIALValue(pchar, SPECIAL_A, 1);
		break;
        case "Luck":
			dialog.text =  "������ ���� "+ GetSexPhrase("���������, �����","���������, �������") +"? � ���������. ������! ������ �� �������� �������.";
			Link.l1 = "� ��� ������?";
			Link.l1.go = "Titch_Seabattle_won_4";
			AddSPECIALValue(pchar, SPECIAL_L, 1);
		break;
		
		case "Titch_Seabattle_won_4":
			Dialog.text = "��� ���� - ����� �������������. � ��� ��� ����. ������ - ������ ��������! (�� ���� � ���, ��� ���� ���������! �������� �� ������ � �������, ���� �������. � ������ �������� � ���� ���������� ���.)";
			link.l1 = "� ������ �� �����"+ GetSexPhrase("","�") +", �� ������, ������ ���!";
			link.l1.go = "Titch_Seabattle_won_exit";
		break;
		
		case "Titch_Seabattle_won_exit":
			LAi_LocationFightDisable(loadedLocation, false);
			DeleteAttribute(NullCharacter, "capitainBase.BlackBeardNPC");
			PostEvent("csmEvent_RefreshReload", 100);
			BattleInterface.LAi_ActivateReload = true;
			SetEventHandler("Control Activation","LAi_ActivateReload",1);
			Log_SetActiveAction("Reload");
			ChangeCharacterAddress(npchar, "none", "");
            DialogExit();
			UnlockAchievement("AchTich", 3);
		break;
		
		case "Titch_duel":
			Dialog.text = "��-��! �� �� ���� "+ GetSexPhrase("������� �������","������� ������") +"! ����� � ������! �� ����� ������ ������������� � ��������.";
			link.l1 = "�� �������, ������..!";
			link.l1.go = "Titch_duel_start";
		break;
		
		case "Titch_duel_start":
			DialogExit();
			Diag.CurrentNode = Diag.TempNode;
			LAi_group_MoveCharacter(npchar, "EnemyFight");				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_LocationFightDisable(loadedLocation, false);
			
			for(int i=0;i<MAX_CHARACTERS;i++)
			{
				sld = &characters[i];
				if (CheckAttribute(sld,"location") && sld.location == loadedLocation.id && sld.id != "BlackBeardNPC" && sld.id != "Blaze")
				{
					LAi_SetActorType(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
				}
			}
			
			LAi_SetCheckMinHP(npchar, 5.0, true, "Titch_duel");
		break;
		
		case "DuelWon":
			Dialog.text = "���"+ GetSexPhrase("��","��") +"! ������"+ GetSexPhrase("","�") +" �������, �������.";
			link.l1 = "����� ������ - ��� ���� ��������, (��� �� ������, ������� �����, �����... ��-��...). ��� ������?";
			link.l1.go = "Titch_7";
			npchar.Duel = true;
			DeleteAttribute(npchar,"chr_ai.poison");
			DeleteAttribute(npchar,"chr_ai.Blooding");
			LAi_SetImmortal(npchar,false);
			LAi_SetCitizenType(npchar);
		break;
		
		case "Titch_cards":
			Dialog.text = "� �����? ����, ������ - 50000 �������� � �� ������. ��� ��� ���� � ���� ������� ��������, ��� �����. ������ ��� � 500000 ���� �� �������. ��, �����"+ GetSexPhrase("","�") +"?";
			if (sti(pchar.money) >= 500000)
			{
				link.l1 = "�����"+ GetSexPhrase("","�") +" �� �? ��� �� ������ ������, �������!";
				link.l1.go = "Titch_cards_go";
			}
			link.l2 = "�������.";
			link.l2.go = "exit";
		break;

		case "Titch_cards_go":
			npchar.money = 1000000;
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 50000;
            pchar.GenQuest.Cards.SitType   = false;
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
		
		case "Titch_questions":
			npchar.coolstories = "���������";
			npchar.questionsstate = 1;
			Dialog.text = "�� �����, ������ ��. ��� �� �� �����"+ GetSexPhrase("","�") +" ��� ���� � ����"+ GetSexPhrase("","��") +" ���������, �� �� ��������� ������ � ��� ����� ������� ����. ����� ����� � ������ � �������� ��������� ��� ������� �����?";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Titch_check";	
			link.l2 = "�������.";
			link.l2.go = "exit";
		break;
		case "Titch_check":
			if (npchar.questionsstate == 1)
			{
				bool check1 = false;
				for(int x=0;x<=5;x++)
				{
					if (coolstory1[x] == GetStrSmallRegister(dialogEditStrings[1])) check1 = true;
				}
				if (check1)
				{
					npchar.coolstories = "���������";
					npchar.questionsstate = 2;
					Dialog.text = "�����! �������� ��������������, ������. ������ ��������� ������! (� ������ ����, ����� ���� �������...)";
					Link.l1 = "�����.";
					Link.l1.go = "Titch_q2";
					break;
				}
			}
			if (npchar.questionsstate == 2)
			{
				bool check2 = false;
				for(int y=0;y<=3;y++)
				{
					if (coolstory2[y] == GetStrSmallRegister(dialogEditStrings[1])) check2 = true;
				}
				if (check2)
				{
					npchar.coolstories = "�������";
					npchar.questionsstate = 3;
					Dialog.text = "�����! �� ��� ��������� ��������� ����� ��������. � ��� � ��������� ������.";
					Link.l1 = "�?";
					Link.l1.go = "Titch_q3";
					break;
				}
			}
			if (npchar.questionsstate == 3 && npchar.coolstories == GetStrSmallRegister(dialogEditStrings[1]))
			{
				Dialog.text = "����������, �� � �� ����� �������"+ GetSexPhrase("��","���") +"! ������ �������� � ���� �� ����.";
				Link.l1 = "�������!";
				Link.l1.go = "Titch_7";	
				npchar.questions = true;
				break;
			}
			else
			{
				Dialog.text = "�������, �������� ���.";
				if (npchar.questionsstate == 1)
				{
					Link.l1 = "��� ���.";
					Link.l1.go = "Titch_questions";
				}
				if (npchar.questionsstate == 2)
				{
					Link.l1 = "��� ���.";
					Link.l1.go = "Titch_q2";
				}
				if (npchar.questionsstate == 3)
				{
					Link.l1 = "��� ���.";
					Link.l1.go = "Titch_q3";
				}
				link.l2 = "�������.";
				link.l2.go = "exit";
			}
		break;
		case "Titch_q2":
			Dialog.text = "��� ���� �������� � ������ �� ��� ���, ���� �� ���� ��������, ��� ׸���� ������?";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Titch_check";	
			link.l2 = "�������.";
			link.l2.go = "exit";
		break;
		case "Titch_q3":
			Dialog.text = "����� �������� ����� ������� ''����� �������� ����'' ������?";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Titch_check";	
			link.l2 = "�������.";
			link.l2.go = "exit";
		break;
		
		case "Titch_ships_sur":
			Dialog.text = "��� ������! ��������� ��� ������ ������������. (������� ���� ������, ������ ������ ����� �� ������������� �����, � ��� ������ �� ������, ���� ������ ���� � ������.)";
			Link.l1 = "���������!";
			Link.l1.go = "Titch_7";
			npchar.ships_sur = true;
		break;
	}
}

string GetNumShips(int ship)
{
    string numships;
    switch(ship)
    {
       case 0: numships = "�� ������ �������"; break;
       case 1: numships = "���� �������";      break;
       case 2: numships = "��� �������";       break;
       case 3: numships = "��� �������";       break;
       case 4: numships = "������ �������";    break;
       case 5: numships = "���� ��������";     break;
       case 6: numships = "����� ��������";    break;
    }
    return numships;
}

string GetPart(int part)
{
    string numpart;
    switch(part)
    {
       case 0: numpart = ""; break;
       case 1: numpart = "��� ������"; break;
       case 2: numpart = "�������� ������"; break;
       case 3: numpart = "����� ������"; break;
       case 4: numpart = "�������� ������";      break;

    }
    return numpart;
}

int findPriceStoreMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[40];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // �������
		{
            //if (sti(ch.nation) !=  sti(NPChar.nation)) continue;
            if (ch.location == "none") continue;
			if (ch.City == "Caiman") continue;			// ���� ��� �����, ��������� �� ���� ��������
            storeArray[howStore] = n;
            howStore++;
            
            // homo 05/09/06
            if ( CheckAttribute(NPChar, "FromColony") && NPChar.FromColony == ch.City ) return n;
            //
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}
