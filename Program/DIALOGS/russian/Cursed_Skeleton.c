// ������������ ������-���� �� ������
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
	
	//ref itm;
	int skullgen = drand(2)+1;
	string cursed_artifact = "sculMa"+sti(skullgen); // ��������� �������
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "��� �� ������ �������� ����� � ���� ��������, ������"+ GetSexPhrase("��","��")+"? �� ��� � ������� � ���� �����! ����� ��������� ���� ����.";
				npchar.quest.meeting = "1";
				link.l1 = "��� ����, � �����" +GetSexPhrase("","�")+" ��� ����� ����� �� �����. ����� ��������, � ������ �� ����.";
				link.l1.go = "meeting_1";

				//���� �� ������ �� ���������� ������
				if (CheckAttribute(pchar.location, "DestroyGhost"))
				{
					link.l1 = "� ���" + GetSexPhrase("���","���") + " �������� ��� ����� �� �������! �����, ��������! ������ �������, � ��������...";
					link.l1.go = "meeting_2";
				}
				
				
				link.l3 = "����, �������!";
				link.l3.go = "skel_fight";

				
				NextDiag.TempNode = "First time";
				break;	
			}
			else if (npchar.quest.meeting == "2")
			{
				dialog.text = "� ����� ���� ���� ��������� ���� ������ �����, �� �� �� �� ������������"+GetSexPhrase("��","���")+". ";
				DeleteAttribute(pchar, "cursed.waitingSkull");
				LAi_SetPlayerType(PChar);
				
				
				
				link.l1 = "������, ��� �� ����� ��������? ������, � ��� ����� �����  ���� �����!";
				link.l1.go = "end_quest_battle";
				link.l2 = "����� ��� �..!";
				link.l2.go = "skel_fight";
				if(CheckCharacterItem(pchar, pchar.questTemp.Cursed.Item) && CheckAttribute(pchar,"cursed.Skullbought"))
				{
					dialog.text = "� ����, ��� ����� � ����. ����� ��� ����.";
					link.l1 = "������� � ������ ���� � ����� �������!";
					link.l1.go = "end_quest";
					link.l2 = "��� ����. ������ ����� ���. ������� �� �������, ��� ���� � �� ��� �� ���"+GetSexPhrase("��","��")+".";
					link.l2.go = "end_quest_battle";
				}
				
			}
			else
			{
				dialog.text = "���� �������?";
				npchar.quest.meeting = "1";

				link.l1 = "����� � ����� ���� �����, ��� ����������� ������? ����������� �������� � ������� ������?";
				link.l1.go = "question";
				link.l2 = "� �����" + GetSexPhrase("","�") + " ��������� ���� �� ����� ������, ����� ����������� ��������!";
				link.l2.go = "skel_fight";
				link.l3 = "���.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "question":
			dialog.text = "� ����� ����� �� ����. � ������� � ����� ������� ���� ������� �����, ���� ����. ����� ���� ���� ��������� ������� � ����� ���� ������ �����. ���, ������� � �� ����� ���������.";
			link.l1 = "�����, ����� ������.";
			link.l1.go = "question";
			link.l2 = "���� ���� ��� ����� ����� ����������� ����� ����� ������� ������? �� �� ���, � ������" + GetSexPhrase("","�") + " ���� ����������!";
			link.l2.go = "skel_fight";
		break;
		case "end_quest_battle":
			dialog.text = "������� ������, � ������ ���� ����� ������������ ��������.";
			link.l1 = "��������!";
			link.l1.go = "skel_fight";
			if(CheckCharacterItem(pchar, pchar.questTemp.Cursed.Item) && CheckAttribute(pchar,"cursed.Skullbought"))
				{
					dialog.text = "��� �� ��� ������" + GetSexPhrase("","�") + ", ��� ������ �� ������� ������� ���� � ����� �����.";
					link.l1 = "� ����� ����" + GetSexPhrase("��","��") + "!";
					link.l1.go = "skel_fight";
				}
		
		break;
		
		case "end_quest":
			dialog.text = "���������. ��� � � ������, �� ������" + GetSexPhrase("��","��") + ". � ������� �� �������� � ���� ������ ���� ���� ���������. �� ������ ���� ��� � �������� � ������, �������� ���� ����� �����, ��� ��� � �� ��� �� �����������. ������ ����������, ������ �������� �����. � ��������� ��� ������ ��������� �������� ��� ���� ���-�� �����.";
			TakeItemFromCharacter(pchar, pchar.questTemp.Cursed.Item);
			string book = PickAbook();
			GiveItem2Character(pchar, book);
			LAi_SetImmortal(npchar, true);
			link.l1 = "�� ��, �������!";
			CloseQuestHeader("CursedSkeleton");
			link.l1.go = "Exit_1";
		break;
		
		case "skel_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			npchar.SaveItemsForDead = true;	
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			ref locLoad = &locations[reload_location_index];
			SetSkeletonsToLocation(locLoad);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			npchar.quest.meeting = "0";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DeleteAttribute(pchar, "cursed.Skullbought");
			CloseQuestHeader("CursedSkeleton");
			NPChar.SaveItemsForDead = true;
            DialogExit();
		break;
		
		case "meeting_1":
			dialog.text = "�� �� ���, ��� ������ ���� �� �����������. ��� ����� ������ � ����� ����. ���������� - � ������� ���� ����� � �������. � ��� ����� � ������ ������� ��� ������ ���� ����� �� �����.";
			link.l1 = "� �� �� �� ������ ���� �����?";
			link.l1.go = "meeting_3";

			link.l2 = "�� ����� � ���� ������ �������!";
			link.l2.go = "skel_fight";
		break;
		
		case "meeting_2":
			dialog.text = "���� ���������� ����� �� �������, � ������� - �� �������. �� � ���� ��� ���� ���� ��������. ��� ����� ������ � ����� ����. ���������� - � ������� ���� ����� � �������. � ��� ����� � ������ ������� ���� ����� ���� �� �����.";
			npchar.quest.answer_1 = "true";
			link.l1 = "� ��� �� ����� ������������ ������ ����� ���� �� "+GetSexPhrase("�������� ���������","������� ��������")+"?";
			link.l1.go = "meeting_3";

			link.l2 = "� �� ��������� ���� �� ������ � ��������!";
			link.l2.go = "skel_fight";
		break;
		
		case "meeting_3":
			dialog.text = "������ ��, � �� ������ ��� �����. � ������� ����� � ���� ��� ����������� �������, ����� ��� � ����. ����� ������ - � ��� ��������, ��� �������� ������� ���� �� ���� ��������. ������, ������ ��� ������� ����� ������� ����� ��� ���-�� ������.";
			link.l2 = "...";
			link.l2.go = "meeting_5";
			link.l1 = "����� � ����.";
			link.l1.go = "meeting_4";
		break;
		case "meeting_4":
			dialog.text = "�� ��������� ����, ������"+ GetSexPhrase("��","��")+", ����� ���� ����� ���������� ����� � ������!";
			link.l1 = "����� ��������, ���������.";
			link.l1.go = "meeting_5";

			link.l2 = "��� ��� ��� ��� �������. ������ � ������� ���� �� ���������!";
			link.l2.go = "skel_fight";
		break;
		case "meeting_5":
			dialog.text = "��� ����� � ��� ������� � ������ ����� ������ ������. � ����� ����� ������ �� ���, � ���������  ������ ����� ����� ������ � �������, ��� ����� � �����. ������ ��� ������, ������� ��, ���, ���� ���� ����� ����� ����� �����, ��� � �� ��� ����������� ��������� �������.";
			link.l1 = "� ��� �� ��� ������?";
			link.l1.go = "meeting_6";

			link.l2 = "��� ��� ����� ���������, �� ��� ���� �� �������, � ���� - �� ��� ����!";
			link.l2.go = "skel_fight";
		break;
		case "meeting_6":
			dialog.text = "��� ����������� �������! � ������ ��� ����� ������ ������, ���� ����� ���� ���� ����� �� ��� ����, � �� ���� ������, ��� � ������� ����������. ��� ��-�� ����� ���������� ������, ���� �� �� �����.";
			link.l1 = "��� �� �����?";
			link.l1.go = "meeting_7";
		break;
		case "meeting_7":
			SelectCursedRendom();
			pchar.questTemp.Cursed.Item = cursed_artifact;
			dialog.text = "���������� ���� �� ����� ����� �� ������ � �����-�� ����� � ��������� �������. ������� ������ �� ���� �����, ��� ��� ��� �����. �� ��� ��� "+ GetConvertStr("itmname_"+pchar.questTemp.Cursed.Item, "ItemsDescribe.txt") +" � ������, ��� ���� � ���� ������ ���� ������� ��� ����, ����� ���� �� �������. �� ����� ���� ����. ����� ������ �����������, ���������� ��������� ���������� ���� ������ ����� �� ��� ����, ����� ����� ����� ������ ���������, � ���������� �������� � � �������� � ����� ���������.";
			link.l1.go = "meeting_7_1";
		break;
		case "meeting_7_1":
			dialog.text = "��� ����, ����� ������������ �������� � �������, ����� ����� ���� ������ �������� �� ����� �����. ��� � � ��������� ��� �������. ������ � ������� ����� �� ������ � ������ �����������, ��� ��� �� ������� ��� ������������� ������ ������ �������� �� ������������� � ������� ������ ���� ������� �����. ��� ����� �������, � ���� ���������� ������ �� ���� ����������� ������, �� �������.";
			link.l1 = "��� � �������, �� ������ ����� ���� "+ GetConvertStr("itmname_"+pchar.questTemp.Cursed.Item, "ItemsDescribe.txt") +"?";
			link.l1.go = "meeting_8";
		break;
		case "meeting_8":
			dialog.text = "��. �  ���� ���� ��� �� ����� ����. ��� ����� �� � �������� ������� ������������ ������ ����� �� "+ XI_ConvertString("Colony" + pchar.questTemp.Cursed.TownId + "Gen") +". ��������� ��� ������� �� ����������� �� �������� �������� ����� �������� � ������ ��� ������ � ���������� ����� ������. ����������� ���� ����������, � ������ �� � ����� �����.";
			link.l1 = "�����.";
			link.l1.go = "meeting_9";
		break;
		case "meeting_9":
			dialog.text = "� ��� ���� ����� ����� �� ������� ������. ���� �� �� ���������� �� ����� ���������. � �� �����, ��� ��� ������ ������ ������� �� �� ���� ����������, � �������� ���� ���� � �����, ��� ��� ��� ������� ����� ���� ���� �� ���� �����.";
			
			ReOpenQuestHeader("CursedSkeleton");
			AddQuestRecord("CursedSkeleton", "1");
			AddQuestUserData("CursedSkeleton", "sSex", GetSexPhrase("","�"));
			AddQuestUserData("CursedSkeleton", "sSex1", GetSexPhrase("��","���"));
			AddQuestUserData("CursedSkeleton", "scityName", XI_ConvertString("Colony" + pchar.questTemp.Cursed.TownId));
			
			link.l1 = "�� ����� ������ ����. ��� � ����, ������ ����. ���� ���� �� "+ XI_ConvertString("Colony" + pchar.questTemp.Cursed.TownId + "Acc") +".";
			pchar.cursed.waitingSkull = true;
			link.l1.go = "exit";
		break;
		
		
// <-- ����������� �������
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetWarriorType(NPChar);
			DialogExit();
		break;
		case "Exit_1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			characters[GetCharacterIndex(npchar)].lifeDay = 0;
			ChangeCharacterAddressGroup(npchar, "Desmoines_town", "goto", "goto2");
			DeleteAttribute(pchar, "cursed.Skullbought");
			chrDisableReloadToLocation = false;
			DialogExit();
		break;
	}
}

void SelectCursedRendom()
{
		int n, nation;
		int storeArray[MAX_COLONIES];
		int howStore = 0;
		for(n=0; n<MAX_COLONIES; n++)
		{
			if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && colonies[n].id != "FortOrange")
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
		nation = storeArray[drand(howStore-1)];
		pchar.questTemp.Cursed.TownId = colonies[nation].id;
		pchar.questTemp.Cursed.TraderId = colonies[nation].id + "_trader";

}

string PickAbook()
{
	int quality = 1;
	if (pchar.rank <= 10) quality = 1;
	if (pchar.rank >= 10) quality = 2;
	if (pchar.rank >= 20) quality = 3;
	if (pchar.rank > 30) quality = 4;
	return "book"+quality+"_"+sti(drand(13)+1);
}