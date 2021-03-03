// ������ ������ - �������������
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	bool hungry = true;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "(����� ���� ������� �������-�����������, ������������ ������� �� ���������� ��������� ��������� �����. ���� �����, ��� ��� ������ �������, �� ����� �� ����� �� ���������� ��� ������.)";
				npchar.quest.meeting = "1";
				link.l1 = "������ ��������, �� � ���� �� ���� ������� ������. �� ���� ������ ���� ��� �����, ���� ��.";
				link.l1.go = "crab_meat";

				link.l2 = "���� ��, ���������" + GetSexPhrase("","�") + " ������. ������, �����!";
				link.l2.go = "crab_fight";
				//link.l3 = "�ire";
				//link.l3.go = "crab_hire";

				
				NextDiag.TempNode = "First time";
				break;	
			}
			else
			{
				if (!CheckAttribute(npchar, "quest.answer_1"))
				{
					dialog.text = "(���� ������� �� ���, ������ ���� ����-��.)";
					link.l1 = "������������?";
					link.l1.go = "crab_meat_1";
					link.l2 = "������, �� � ���� ������ ���� ���� ��������.";
					link.l2.go = "exit";
					
					
				}
				else
				{
					dialog.text = "(���� ������� ������� � ���� �����������.)";
					link.l1 = "� ���� ������, �������.";
					link.l1.go = "exit";
					
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "crab_fight": // ������ ������� 
            DialogExit();
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			sld.SaveItemsForDead = true;	
		break;
		
		case "crab_meat":
			dialog.text = "(���� � �������� ���������� �������� ������ �� ������ �������.)";
			link.l1 = "���� �� ����, ����� �� � ���-�� ���� �������... ��� ����, ������ �� ������ ������ � ���� ����������. ����� ���� �� �������?";
			link.l1.go = "crab_meat_1";
			
		break;
		
		case "crab_meat_1":
			dialog.text = "(���� ������������ ������� �������, ���������� ���� ��������.)";
			
			if (CheckCharacterItem(pchar, "food1") || CheckCharacterItem(pchar, "food2") || CheckCharacterItem(pchar, "food3") || CheckCharacterItem(pchar, "food4") || CheckCharacterItem(pchar, "food5"))
			{
				link.l1 = "���, �����!";
				link.l1.go = "crab_meat_2";
			}
			link.l2 = "��� �����, ������ ���-������ �������.";
			link.l2.go = "exit";
		break;
		
		case "crab_meat_2":
			dialog.text = "(���� ����� ��������� ��� �� ���������� ����, � ����� ������������ ����� � ���� ����� � ������� ��� ��������� �������.)";
			RemoveItems(PChar, "food1", 100);
			RemoveItems(PChar, "food2", 100);
			RemoveItems(PChar, "food3", 100);
			RemoveItems(PChar, "food4", 100);
			RemoveItems(PChar, "food5", 100);
			npchar.quest.answer_1 = "true";
			link.l1 = "�������, �������! �� ��� �����! �����, ��� ����. ����� ��� � ���� ���-������ �������.";
			link.l1.go = "exit";
		break;
		
		case "crab_hire":
			dialog.text = "(� ��� ������������ �������� �������� ����. ������������ ���� ���� ������� � ������, ������ �� ������������ ����. ������-�� ��� �������, ��� � ����� �������� ����������� ���������.)";
			link.l1 = "������, �� ��� ��? �� � �������! �� ���� ��� ����� ����� ������? ��� �� ����-��... �������, ��� ����� �� �����. ��� �� ����� �������?";
			link.l1.go = "crab_hire_1";
		break;
		case "crab_hire_1":
			dialog.text = "(���� ������ ����� ��������� ������)";
			link.l1 = "��� ����. � ���� �� �������, �� ������� ��� �� ���� �������. �� ����� ��������� � �� ����� ����, ��� ���� ��������. �� ������ ������� ������ ������ �� ����?";
			link.l1.go = "crab_hire_2";
		break;
		case "crab_hire_2":
			dialog.text = "(�������� ������ ����, ������� �� ������������� ��� ��������)";
			link.l1 = "� ���� ���� ���� ������� ����, � �� ���� �������� ��� �� ���� �������, ����� ���� �������.";
			link.l1.go = "exit_hire";
		break;
		case "exit_hire":
			DeleteAttribute(npchar, "city");
			chrDisableReloadToLocation = false;
		/*	
			npchar.OfficerWantToGo.DontGo = true; //�� �������� ����
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.dialog.CurrentNode = "First time";
			NPChar.quest.meeting = true;
			*/
		
		

			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.loyality = MAX_LOYALITY;
			
			npchar.Dialog.Filename = "Enc_OfficerCrab.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Npchar.cirassId = Items_FindItemIdx("cirass5");  // �������� ���, �� �������� ����
			NextDiag.CurrentNode = NextDiag.TempNode;
			npchar.OfficerWantToGo.DontGo = true;

			DialogExit();
		break;
		

// <-- ����������� �������
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetWarriorType(npchar);
			DialogExit();
		break;
	}
}
