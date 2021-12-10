//Jason ����� ������ ������� ��������
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// ����� ������� �� ������� -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // ����� ������� �� ������� <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
            if (Pchar.questTemp.CapBloodLine == true)
            {
                dialog.Text = "������������, ������.";
                Link.l1 = "� ��� �� �������.";
				Link.l1.go = "exit";
				break;
    		}
			
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//���� � �������
				{
					dialog.text = "������������, "+GetAddress_Form(NPChar)+". ��� ��� ��������, �� - ������� ������������ �������. � ���� � ��� ������� ��������.";
					link.l1 = "������ ��� �����������, "+GetAddress_FormToNPC(NPChar)+". � ��� ����?";
					link.l1.go = "crew";
					link.l2 = "��������, "+GetAddress_FormToNPC(NPChar)+", �� � ����� �����.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //������� ���������
					break;
				}
				dialog.text = LinkRandPhrase("�����������, �������! ��� ��� ������ �� �������� �������?","������������, ����"+ GetSexPhrase("��","����") +". ��� ���� ���� ��� �������?","������� ���, �������"+ GetSexPhrase("��","��") +". �� ���-�� ������?");
				link.l1 = "��� �������, ���������! ��� ��� - "+GetFullName(pchar)+". �� �������� ������� ���������?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("� ���� ���� ������ � ����.", "��� ����� ���������� � ����� � ���� �������.");
				link.l2.go = "quests";//(���������� � ���� ������)
				link.l3 = "������ �����"+ GetSexPhrase("","�")+" �������������. �����!";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "��� ����� ��, "+ GetSexPhrase("������","��������") +"? �� ��� ���-�� ������?";
				link.l1 = "�� �������� �� ������� ��������� � ���, � ���?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("� ���� ���� ������ � ����.", "��� ����� ���������� � ����� � ���� �������.");
				link.l2.go = "quests";//(���������� � ���� ������)
				link.l3 = "���, ��������, ������. �����!";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" � ����� �������, ������"+ GetSexPhrase("��","��") +"! ��� �� ������ ������?", 
				"��� ���������, �������!", 
				"��, �������, � ���� ���� ��� �����...",
                "� ���������, ��� ���� ����. ����� �������!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�����, ���������� ��� ����������?", 
				"�����, ���������� ��� ����������?",
                "�����, ���������� ��� ����������?", 
				"��, �������. ����� ���!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

		case "crew":
			switch (drand(2))
			{
				case 0: sTemp = "� � ��������� ���� ������ ���� ������� �� ����� ����� ���������� �������. ������ �� ����������� � ����� ����� �������� �� ������ ���������. �� ������� �� ��������� ���� �������?"; break;
				case 1: sTemp = "���� � ���������� ����� ������� ������� �� ����� � ����������� ����� - ���������� ���� �������� ������� � ��������. �� ��� ������� ���� �� ���� � ����� �������� ���������. ��� �� � ��� ����� � ������� ������� ��� ����� �������?"; break;
				case 2: sTemp = "�� � �������� ��� ������ ����� ��������� �� �����, ������ ��� ���������, � �� ������� ������������ ��� �������. ������ ����� ������ � ���������� ������� - ������, ����� ���� � ����. �� ������� �� ��� �� ���� �����, �������?"; break;
			}
			dialog.text = sTemp;
			link.l1 = "�� ��� ��, � �����"+ GetSexPhrase("","�")+" ����������� ���� �����������. ������� ��� �������, � ��� �� ������ ������ �� �����?";
			link.l1.go = "crew_1";
			link.l2 = "�������, ������, �� ��� ������� ��������� ��������������. ��� ��� �������� ���� �������� ������� ��������.";
			link.l2.go = "exit";
		break;
		
		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "���� ����� ����� ������� �� ����� ���������� � �������� � ��������. ��� ������ ���������� �����: �� �� ���� ���� ������ �����, ��� ��� �� �������� ���� � ����� �������� �����!"; break;
				case 1: sTemp = "������ ������ ����� ��� �� ���� �������� ������. �� ����� ���������� � �������� ���, ��� ����� ������ � ����� �������, ������. �� ����� ������ ������� ������ ��� ������ ���������� �� ���!"; break;
				case 2: sTemp = "�� ���� ������ - ��� ���������� �������. ����� ������, ����� ������ � ����� - ��� ���� ���������. � ��� � ���� ������� ���������, ��� ��� � ������ ��������� ���� ������ ������� ���, �������!"; break;
			}
			dialog.text = "��� "+sti(npchar.quest.crew.qty)+" �������, � ������ �� �� ������ ������ ��� ������. ����� �� ��, ��� �������� �������. "+sTemp+"";
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "������ ������ ���������. ������� �� ������ ������?";
				link.l1.go = "crew_2";
				link.l2 = "�������, ������, �� � ����������� �� ���������... ����. �������� ��� �������� ������� ��������.";
				link.l2.go = "exit";
			}
			else
			{
				if(GetCompanionQuantity(PChar) > 1)
				{
					ref rChar;
					for(int i = 1; i<GetCompanionQuantity(PChar); i++)
					{
						if (GetCompanionIndex(PChar,i)>-1)
						{
							rChar = &characters[GetCompanionIndex(PChar,i)];
							if(sti(rChar.index) != -1 && GetFreeCrewQuantity(rChar) >= sti(npchar.quest.crew.qty))
							{
								link.l1 = "�������, ������, �� ��� ���� ��� � ���� ��� ���� �� �������. �������� ��� ����� � ����� ����������, ��� ����� "+ rChar.name + " " + rChar.lastname + ".";
								link.l1.go = "crew_comp";
								pchar.addcrew.character = rChar.id;
								break;
							}
						}
						else
						{	
							link.l1 = "�������, ������, �� ��� ���� ��� � ���� ��� ���� �� �� ����� �������. �������� ��� �������� ������� ��������.";
							link.l1.go = "exit";
						}

					}
				}
				else
				{
					link.l1 = "�������, ������, �� ��� ���� ��� � ���� ��� ���� �� �� ����� �������. �������� ��� �������� ������� ��������.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "crew_comp":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" �� �����. ����� - ������� ���������� ���������. �� ������� �� ��������, ���.";
			if (sti(pchar.money) >= iTemp)
			{
				rChar = CharacterFromID(pchar.addcrew.character);
				link.l1 = "������������! ��� ����� ��� �����. ������������� �� �������, �� ���������� '"+rChar.ship.name+"', ����� �� �����. ������ ������� ��� ����� � ������� � ���� ������.";
				link.l1.go = "crew_comp1";
			}
			link.l2 = "� ���������, � �� ���� ���� ��������� �������� ���� ������. �������� ��� �������� ������� ��������.";
			link.l2.go = "exit";
		break;
		
		case "crew_comp1":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "��� ����, �������! � ������ �����, � �� ���������� �� ���� ����������!";
			link.l1 = "��������, ����������������, � ����� ������������� ��� �� ��������.";
			link.l1.go = "crew_comp2";
		break;
		
		case "crew_comp2":
			DialogExit();
			rChar = CharacterFromID(pchar.addcrew.character);
			AddCharacterCrew(rChar, sti(npchar.quest.crew.qty));
			//����������� ����
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(rChar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(rChar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(rChar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(rChar, "Soldiers", iTemp); break;
			}
			//����������� ������
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(rChar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" �� �����. ����� - ������� ���������� ���������. �� ������� �� ��������, ���.";
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "������������! ��� ����� ��� �����. ������������� �� ��� �������, �� ���������� '"+pchar.ship.name+"', ����� �� �����. ������ ������� ��� ����� � ������� � ���� ������.";
				link.l1.go = "crew_3";
			}
			link.l2 = "� ���������, � �� ���� ���� ��������� �������� ���� ������. �������� ��� �������� ������� ��������.";
			link.l2.go = "exit";
		break;
		
		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "��� ����, �������! � ������ �����, � �� ���������� �� ���� ����������!";
			link.l1 = "��������, ����������������, � ����� ������������� ��� �� ��������.";
			link.l1.go = "crew_4";
		break;
		
		case "crew_4":
			DialogExit();
			AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
			//����������� ����
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(pchar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(pchar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(pchar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(pchar, "Soldiers", iTemp); break;
			}
			//����������� ������
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(pchar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;

		//��������� �� ����������� ������ �� ���������� ���� citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "����������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.", "������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.");
			link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//Korsar Maxim - ����������
		case "SeekSpy_Checking":
			dialog.text = "��, � �����������, " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], "�� ������������� ������� ������.", "��� ������������� ������� ����������.");
			link.l1 = RandPhraseSimple("� �����"+ GetSexPhrase("","�") +". ������� �� ������.", "��� ����. ������� �� ������.");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
	}
}
