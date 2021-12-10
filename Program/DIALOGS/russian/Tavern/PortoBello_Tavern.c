// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������, " + GetAddress_Form(NPChar) + "?"), "������ ������� �� �������� ������ ��� ������, " + GetAddress_Form(NPChar) + "...", "� ������� ����� ��� �� ��� ������ ��� �������� � �����-�� �������...",
                          "����� ������� ����� ��������?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� ��, ������������� � ������ ���...", "�� ���, ����� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.RomanticQuest == "SeekInPortoBello")
			{
				link.l1 = "��������, �� �� � �����, ����� �� ���� ����� �������� ����� '������������'?";
				link.l1.go = "Romantic_1";
			}
			
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "��������, �� ����� �� �� ������ �� ����� ������� �������? �� ������� ��� � ����� ������.";
                link.l1.go = "Portobello_rat_1";
            }
			
			if (CheckAttribute(pchar, "questTemp.mushket2x2_stid") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = "������, �������, �� �� ������, ��� ��� ����� �������� ������� - �������� ����� '������'?";
				if (GetQuestPastDayParam("questTemp.mushket2x2_stid") < 11 || GetQuestPastDayParam("questTemp.mushket2x2_stid") > 60)
				{
					link.l1.go = "Mushket_stid";
				}
				else
				{
					link.l1.go = "Mushket_late";
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.PDM_ONV_PortoBello"))	//����� "����� �� ������"
            {
                link.l1 = "���� �� � ��� �� ������� ��� �����?";
                link.l1.go = "PDM_ONV_PB_1";
            }
		break;
		
		case "PDM_ONV_PB_1":	//����� "����� �� ������"
			dialog.text = "��� ��� ��� �� � ��� �� �������. �� ��� �������, ��� ������� �� �������� �� ��� ���������� ��� ���, ����� � ��������� ����� ������ ���.";
			link.l1 = "��� �� �� ���� �������. �������!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_PortoBello");
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("���, �� ����. � ������� �� �� �������, �� � � ������ � ��� �� �����.", "�� ��� "+ GetSexPhrase("���������","����������") +" �� ����, � ���� �������.", "� �� ������ ����, �� ��� "+ GetSexPhrase("���������","����������") +" �� ���� ��������.", "��������, ������ � �� �����! ������ ��� �� ����� �������?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�� ��� ��, ����� ������.", "��, �� ��...", "��, �����, "+ GetSexPhrase("���������","����������") +"...", "������, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			break;
		
		case "Mushket_stid":
			dialog.text = "��� ��� ��!.. A�-��-��! ����� ��� ���� ����������� ��� ������ ����, ���������� ��������� ������� ������?!";
			link.l1 = "�����... � ���� � ���� ����.";
			link.l1.go = "Mushket_stid_1";
			break;
			
		case "Mushket_stid_1":
			dialog.text = "�� �������?! ����������, � ���� ���� � ���� '����', ����� ��� ����� �����. �� �� � ��� ��� �� ����� - ����-��������, ���� ����������. ������ �������������� ��� ������, ������ ��� ����� ��������� ����������. � ����� �� �� ������� - � ������ ��� ��������� ����. ���� ������ �� ���� ��������... � ����, �������� �� ������� �� ��� ���� ������?";
			link.l1 = "�� ���... ���� � ���� ������, ������� ��� �� �����������, �������� ����...";
			link.l1.go = "Mushket_stid_2";
		break;

		case "Mushket_stid_2":
			dialog.text = "��-��! �� ������� ���� ��� ����������� ����� �� ����������� - ������� ��������, ��� ������, ��� ������ ��� �������. ���� ��� - '������' ����������� ��� ������� - ������ � �������� �� ���� ������, �� ����� ��������.\n������, � �� �� �������� �� ��� �� ���� �������"+ GetSexPhrase("","�") +", �? � �� � ��� ����� - ��� �� '����' � ���� � ����! ������ ���� - ������ ����� �������� ������� ���� �� ���, ������, ��� �� �������� ������. ����� �� � ���� ������ - ������� ��������, ����� �������.";
			link.l1 = "�� �� ����� ��� ��� ����! �� ������ ������ ������� - ��� ��� �����?";
			link.l1.go = "Mushket_stid_3";
		break;		
			
		case "Mushket_stid_3":
			dialog.text = "�� �����-��������, �������� �� ������, ������� ����� �� ������� � �������, �������� ��������, ��� ��� �������� ��� ��������... �� �� ��� �� � ����������� �����, ���� �� �� ����, ���� �� �������! ��� ��� ������ ������, "+ GetSexPhrase("��������","�������") +"!";
			link.l1 = "��-��, �������! � ������� �� ������ �� ��� ����������?";
			link.l1.go = "Mushket_stid_4";
		break;	
			
		case "Mushket_stid_4":
			dialog.text = "��� ����� �������, ��������! ��� ����� ������� - � ����� ������.";
			if(makeint(Pchar.money) >= 100000)
			{
				link.l1 = "�������?? �� �� ���, ������ - ������� ����� ������ �� ��� �����?!";
				link.l1.go = "Mushket_stid_nopay";
				link.l2 = "��� �������, �������. ����� ���� �������.";
				link.l2.go = "Mushket_stid_paymoney";
			}
			link.l3 = "��������, �� � ���� ��� ����� �����!";
			link.l3.go = "Mushket_stid_nomoney";
		break;	
			
		case "Mushket_stid_nopay":
			dialog.text = "�� ������ ���� ����������� - ��� ���� ����� ������� ������. � ���� ����� ��� '������' ������ ������������ ������ �� ������ ����� ������� - ���� ������� ������ ��� ���������� ��������... ���� ������� ��������� ������ - ��� ����������� ���� ������. �, ���� �� ������� - ���������� ������ �� � ����, ��-��-��...";
			link.l1 = "�����, ���� � �����. �����.";
			link.l1.go = "Mushket_stid_paymoney";
			link.l2 = "�� ������. ��������� ��� ������ - ���"+ GetSexPhrase("","�") +" �����.";
			link.l2.go = "Mushket_stid_goaway";
		break;	
			
		case "Mushket_stid_nomoney":
			dialog.text = "�� ��� � - ����� �� ������ ���� ������� '������'. �������, ���� ���� ������ ��������� �������������� ���-�� ����������. � �����, ��� �� ������������, ������ ��� - �� ������� � ����� �����, � ������ � ������... ��� ���, �������� - �������, ���� ������ �������� � ���. � � ���� �� ��������.";
			link.l1 = "�� ���, ������, �������. �� �������� ���� �������� ���������. ��� ���������� ������� ��������, � �� ��������� - ���� �����...";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "5");
		break;	
			
		case "Mushket_stid_goaway":
			dialog.text = "��� ������. ������ - �����. ������� �������!";
			link.l1 = "������, �������.";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "6");
			AddQuestUserData("SeekDoubleMushket", "sSex", GetSexPhrase("��","���"));
		break;	
			
		case "Mushket_stid_paymoney":
			AddMoneyToCharacter(Pchar, -100000);
			SetMushketCapitainInWorld();
			dialog.text = "�-�, � ���� ������"+ GetSexPhrase("�� ������ ��������","��� ������ ������������") +"! � ���� ���� ���������� - �� ���������� �� �! ��, �� ����� - ���� �� �������� ���� ������������ ������... ������ ������: �� �� ���� ���������� � ����� ��� ��������� " + XI_ConvertString(pchar.questTemp.Mushket.Shore) + ".\n����� �� ��� �� ����� - ����������� � �����, ��� ��� ����������. ������� ��� �� �� �������, �� ������� ��� ����"+ GetSexPhrase("��","��") +" ��� ������. ������, ���� ������ ������ ������� �����, ��-��... ���� ���, �� �������� ����� ������ ����"+ GetSexPhrase("��","�") +". � � ��� ���� ���� ������, � ���� ����� ������, �� �� ��� ���� �������� �� �����������.";
			link.l1 = "�������, ���! ���������� ����������.";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "4");
			AddQuestUserData("SeekDoubleMushket","sShore", XI_ConvertString(pchar.questTemp.Mushket.Shore));
			DeleteAttribute(pchar, "questTemp.mushket2x2_stid");
		break;
		
		case "Mushket_late":
			dialog.text = "A�-��-��! ����� ��� ���� ����������� ��� ������ ����, ���������� ��������� ������� ������?!";
			link.l1 = "�����... � ���� � ���� ����.";
			link.l1.go = "Mushket_late_1";
		break;
			
		case "Mushket_late_1":
			dialog.text = "�� ��� � ���� �������... �� ������ ����, "+ GetSexPhrase("��������","�������") +". ����� �� �� ��� ������� �������� - � �� ��������� � ����� �����������, � ����� ����� ����� �������� �������.\n�� ������ ������ - �� ���� ������, � ���� - �� �����. ��� ��� ��� ������ ���"+ GetSexPhrase("","�") +"... �� ����� ����������. �� ����� ���� ��� ������. ���� ������ ����������� ��������� �������, ����� �����?";
			link.l1 = "��� ������! �����, ��� ��� - ������.";
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "7");
			AddQuestUserData("SeekDoubleMushket", "sSex", GetSexPhrase("��","���"));
		break;
		
		case "Romantic_1":
            dialog.text = "���, ���� ����� �� ���������.";
            link.l1 = "�������... �����, � ������� ���-������ ������� � ����?";
			link.l1.go = "Romantic_2";
		break;	
		case "Romantic_2":
            dialog.text = "������ ���, " + GetAddress_Form(pchar) + ", ��� �����.";
            link.l1 = "����... �� ��� ��, ������� ����.";
			link.l1.go = "exit";
			pchar.RomanticQuest = "ToRositaInBeliz";
		break;	
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

void SetMushketCapitainInWorld()
{
	//������� �����
	int Rank = sti(pchar.rank) + 15;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("MushketCap", "officer_17", "man", "man", Rank, PIRATE, -1, true));
	sld.name = "�������";
	sld.lastname = "������";
 	SetCaptanModelByEncType(sld, "pirate");
	FantomMakeCoolSailor(sld, SHIP_BRIGQEEN, "������", CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade34", "pistol2", 50);
	sld.Ship.Mode = "pirate";	
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //������������� ��������� ������� ��� ������ �����
	sld.DontRansackCaptain = true; //�� ���������
	sld.WatchFort = true; //������ �����
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//� ������� ������ ����
	string sGroup = "MushketCapShip";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	sld.quest = "InMap"; //������ ���� �������� ����
	sld.city = "Shore47"; //��������� �������, �� ����� ������� � �������� ������
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //��������� �������, � ����� ������� �� ������
	sld.quest.targetShore = "Shore58";
	pchar.questTemp.Mushket.Shore = sld.city;
	Log_TestInfo("��� � �������� ����� ��: " + sld.city + " � ���������� �: " + sld.quest.targetShore);
	//==> �� �����
	sld.mapEnc.type = "trade";
	//����� ���� ��������� �� �����
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "���� '������'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //���� ������� ���� � �������
	Map_CreateTrader(sld.city, sld.quest.targetShore, sld.id, daysQty);
	//������� Id ���� � ���� ���-�����
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "mushket"; //������������� ������
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //�������� Id ������������ ��� ������� � ������ ����
	NullCharacter.capitainBase.(sTemp).Tilte1 = "SeekDoubleMushket"; //��������� ���������
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SeekDoubleMushket"; //��� ������ � ���������
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}