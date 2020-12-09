//#include "DIALOGS\convoy_traider.h"
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "prepare_convoy_quest":
			if (isBadReputation(pchar, 40)) 
			{
				dialog.text = RandPhraseSimple("�-�-�, ����!! � ����, ��� �� "+ GetSexPhrase("�����","�����") +"! ������ ����������� ������ ����� ������ ���� � ������������� ������ �������. ������!", "�-�, � ����, ��� �� ����! ���� ������ � �������� ���������������?! ��� ������...");
				link.l1 = RandPhraseSimple("���, ��������� �����...", "�������� ����� ����� �����!");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + "! � "+ GetFullName(NPChar) + ", ��������. � ������, ��� �� ����� ������?";
				link.l1 = "���-�� ����� ����. � ��, ��� � ������"+ GetSexPhrase("","�") +", ����� ��������, ������� �� ���������� ��� � ���� ����� � ����� ����������?";
				link.l1.go = "prepare_convoy_quest_2";
			}
		break;
		
		case "prepare_convoy_quest_2":
			dialog.text = "���������� �����. ����� ����, �����, ��� �� ��� ��������� � �������� ���������������. ��� �������?";
			link.l1 = "� ����� - ������ ��� ����� �, ��������, �� �����������.";
			link.l1.go = "prepare_convoy_quest_3";
		break;
		
		case "prepare_convoy_quest_3":
			LookShipConvoy();
			GenerateConvoyQuest(npchar);
			dialog.text = "��� �����, ����� ���� ����������� �� " + XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + ", ��� �� " + XI_ConvertString(GetIslandByCityName(pchar.quest.destination) + "Dat") +
				", �� " + FindRussianDaysString(sti(pchar.ConvoyQuest.iDay)) +", � �� ��� � ������� ��� " + FindRussianMoneyString(sti(pchar.ConvoyQuest.convoymoney)) + ". ��� �������?";
			link.l1 = "� "+ GetSexPhrase("��������","��������") +".";
			link.l1.go = "convoy_agreeded";
			link.l2 = "�� �����, ��� ��� ��� ���������.";
			link.l2.go = "convoy_refused";
		break;
		
		case "convoy_refused":
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_refused");
		break;
		
		case "convoy_agreeded":
			chrDisableReloadToLocation = false;
		    pchar.convoy_quest = pchar.quest.destination;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_agreeded");
		break;
		
		case "complete_convoy_quest":
			dialog.text = "�! ������� ���. ��� ����� ������� � ���������� ���� ��� ������� ��������. ��� ���� �������.";
			Link.l1 = "��������� ���.";
			link.l1.go = "exit";
			//�����
			AddSimpleRumour(LinkRandPhrase("����� �������� ��� �� ����� " + GetFullName(npchar) + " �������, ��� ����� �������� " + GetMainCharacterNameDat() + " � ����� ������������� �������� �����.", 
				"��������� �� ����� " + GetFullName(npchar) + " �������, ��� �������� " + GetMainCharacterNameDat() + " ����� ������. "+ GetSexPhrase("��� �������","�� ��������") +" ��� ������� ��������� ������� ��� ������������� �� " + XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + ".", 
				"� ������, ��� �� ������� ����� �� ������������� ��������, ������ �������� ���������. ����� �������� �� ����� " + GetFullName(npchar) + " ����� ������ � ��� ����������."), sti(npchar.nation), 40, 1);
			pchar.quest.generate_convoy_quest_progress = "completed";
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			AddDialogExitQuest("convoy_refused");
		break;
	}
} 

// boal 03.05.04 ����� ����������� �������� -->
void GenerateConvoyQuest(ref npchar)
{
	int iTradeMoney, iNation;

	DeleteAttribute(NPChar, "Ship");
    SetShipToFantom(NPChar, "trade", true);

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //���� �������� ����� �� ��������� �����
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.ConvoyQuest.City), GetArealByCityName(pchar.quest.destination));
	if (sti(daysQty) > 14) daysQty = 14;
	pchar.ConvoyQuest.iDay = makeint(sti(daysQty)*(frand(1.3)+0.7));
	iTradeMoney = (sti(daysQty)*600*sti(pchar.GenQuest.Convoy.Shipmod)+rand(100))*sti(daysQty)/sti(pchar.ConvoyQuest.iDay);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.4); //�� ������ ������� �������������
	pchar.ConvoyQuest.convoymoney = iTradeMoney;

	//Log_Info(FindRussianDaysString(sti(daysQty)));
	//Log_Info(pchar.quest.destination);
	//Log_Info(pchar.ConvoyQuest.City);
	SetTimerCondition("generate_convoy_quest_timer", 0, 0, sti(pchar.ConvoyQuest.iDay), false);

	pchar.quest.generate_convoy_quest_progress = "begin";

	pchar.quest.generate_convoy_quest_failed.win_condition.l1 = "NPC_Death";
	pchar.quest.generate_convoy_quest_failed.win_condition.l1.character = "QuestTrader";
	pchar.quest.generate_convoy_quest_failed.win_condition = "generate_convoy_quest_failed";
}

void LookShipConvoy()
{
	switch(makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
		case 0:
			pchar.GenQuest.Convoy.Shipmod = 0.7;
		break;
		case 1:
			pchar.GenQuest.Convoy.Shipmod = 1;
		break;
		case 2:
			pchar.GenQuest.Convoy.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.Convoy.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.Convoy.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.Convoy.Shipmod = 3;
		break;
		case 6:
			pchar.GenQuest.Convoy.Shipmod = 4.5;
		break;
	}
}