#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = "� �� ����� � ����� �������������! �� �����"+ GetSexPhrase("","�") +" �� ���� ���������!";
				link.l1 = "��� ������..."
				link.l1.go = "exit";
				break;
			}

			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = "��� ���� ������� �������� ���������? �� ��� ��, ����� ����������! � ����� ������� �������, ����� ���� " + GetFullName(npchar) + ". ���� ������� �������, "+ GetSexPhrase("��������","�������") +"!";
					link.l1 = "�� ��, ������� ������ ��������!.. ���� ����� " + GetFullName(pchar) + ". � ���"+ GetSexPhrase("","�") +" ���������...";
					link.l1.go = "FS_1";
				}
				else				
				{
					dialog.Text = "�-�-�, ��� ��� ���� ������� �������� ���������? �� ��� ��, ����� ����������! � ����� ������� �������, ����� ���� " + GetFullName(npchar) + ". ��� ��� ������, ����� ���...";
					Link.l1 = "������, " + npchar.name + ". ������� �������������, ��� �������... � ���� ����� " + GetFullName(pchar) + ".";
					Link.l1.go = "First time";
				}
			}
			else
			{
				//����� � ������ �������
				if (pchar.questTemp.LSC == "toWineCellarGone" && npchar.location.locator == "stay1")
				{
					dialog.Text = "�-�, ��� � ��!";
					link.l4 = "������! ������ �������� �� ��������� ����.";
					link.l4.go = "TizerCellar";
					PChar.quest.LSC_returnBarmen.over = "yes"; //������� ������ �� ���������, �������� ���������
					break;
				}	
				//����� ������ ����� ��������
				if (pchar.questTemp.LSC == "barmenIsDead" && !CheckAttribute(npchar, "quest.HillNB_1"))
				{
					dialog.Text = "������ ���� �����������.";
					link.l4 = "������ ��� ������� �� ��� �������? � ��� �������?";
					link.l4.go = "NB_1";
					pchar.questTemp.LSC = "barmenIsDeadYouKnow";
					break;
				}
				if (pchar.questTemp.LSC == "barmenIsDeadYouKnow" || pchar.questTemp.LSC == "toAdmiralBarmenDead")
				{
					if (!CheckAttribute(npchar, "quest.HillNBB_1"))
					{
						dialog.Text = "������ ���� �����������.";
						link.l4 = "�-��, ������, ���� ������������� �����...";
						link.l4.go = "NBB_1";
						break;
					}
				}
				//�������� ����
				sld = characterFromId("LSCwaitress");
				if (sld.lastname == "��������" && !CheckAttribute(npchar, "quest.Armo"))
				{
					dialog.Text = "���� �����... ������� ���� �������, ������ ����. �������� ����� ��� �������.";
					link.l4 = "�� ������ �� ��� �������, ����� �������� �����?";
					link.l4.go = "ADied_1";
					npchar.quest.Armo = true;
					break;
				}
				//==> ������ ������
				dialog.Text = LinkRandPhrase("��, " + GetAddress_Form(NPChar) + " " + PChar.name + "! " + TimeGreeting() + ".",
                                    "�-�-�, ��� ������ ���"+ GetSexPhrase("���","��") +" �������"+ GetSexPhrase("���","��") +" ������ ������...",
                                    "��� ���� ������ � ���� � �������. ����� ���������"+ GetSexPhrase("","�") +"?");
				Link.l1 = "� �������, �� ������� �������� �� ���� ��������.";
				Link.l1.go = "int_quests";
				link.l2 = "��� ����� ������������.";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("���-������ ���������� ��� ����������?", 
					"��� ������ � ������?", "��, � ������������� ��������"+ GetSexPhrase("","�") +" �� ��������� �������...");
				link.l3.go = "rumours_LSC";
				Link.l4 = "���, � ��� �����, " + NPChar.name + ". �� �������.";
				Link.l4.go = "exit";
				//==>> ������
				if (pchar.questTemp.LSC == "AfterAdmiral" && GetQuestPastDayParam("questTemp.LSC") > 3)
				{
					link.l4 = "�������, �� �������������� � �����, ��� �� ����������� ������� �� ������ ������ ����...";
					link.l4.go = "Tizer";
				}
				if (pchar.questTemp.LSC == "toWineCellarLate")
				{
					link.l4 = "��������, � ��� � �� ���"+ GetSexPhrase("��","��") +" ���� � ���� ����� ������ �������...";
					link.l4.go = "TizerCellarLate";
				}
				if (pchar.questTemp.LSC == "toDiffindoor" && CheckCharacterItem(pchar, "letter_LSC"))
				{
					link.l4 = "� ����������"+ GetSexPhrase("","�") +" '���������' � ���"+ GetSexPhrase("��","��") +" ��� ������ ������. � ���, ����� �������, ���� ��� � ����� ���������� ������...";
					link.l4.go = "TizerCellarOk_1";
				}
				if (pchar.questTemp.LSC == "afterFightInProtector")
				{
					link.l4 = "��������, ��� ����� ����...";
					link.l4.go = "AfterProtector_1";
				}
				if (pchar.questTemp.LSC == "toAdmNarvalRing" && CheckCharacterItem(pchar, "DOjeronRing"))
				{
					link.l4 = "� ������"+ GetSexPhrase("","�") +", ��� �� ������. ������ '��������' � ����.";
					link.l4.go = "NarvalRing_1";
				}
				if (pchar.questTemp.LSC == "toTavernNarvalDestroyed")
				{
					link.l4 = "�� ������, ��� ����������!";
					link.l4.go = "AfterNarvalDesrt_1";
				}
				if (pchar.questTemp.LSC == "waitInterception" && GetQuestPastDayParam("questTemp.LSC") > 2 && GetHour() < 20)
				{
					link.l4 = "��, ��� ����? �������, ��� ����������?";
					link.l4.go = "Interception";
				}
				if (pchar.questTemp.LSC == "InterceptionLate")
				{
					link.l4 = "������, � �� ����"+ GetSexPhrase("","��") +" � �������� ���� � ����� �������. ��� ��� � ������ �� �����"+ GetSexPhrase("","�") +" � ������ �� �������"+ GetSexPhrase("","�") +".";
					link.l4.go = "InterceptionLate";
				}
				if (pchar.questTemp.LSC == "InterceptionYouSeen")
				{
					link.l4 = "�� ������, ����� � ������� � ���"+ GetSexPhrase("","�") +" � ����� �������. ������� � ��� �����-�� ��� ���������� ����������, �� �������� ���� � ����. ��� ��� � ������ �� �������"+ GetSexPhrase("","�") +".";
					link.l4.go = "InterceptionYouSeen";
				}
				if (pchar.questTemp.LSC == "waitInterceptionResult")
				{
					link.l4 = "��������, ������� ���-������ ������ �� ������ ����?";
					link.l4.go = "Result";
				}
				if (pchar.questTemp.LSC == "InterceptionOk")
				{
					link.l4 = "������, ���� ������ - ������������� ������� ����� ��� ������������� ����������. � ������"+ GetSexPhrase("��","���") +" ����.";
					link.l4.go = "InterceptionOk";
				}
				//����� ������� �� ������
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "������, � ��� ��������� ������.";
					link.l8.go = "SeekGoods";
				}
				//������ ������� �� ������
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "������, ���� ��������� ��������. � ������� �������.";
					link.l8.go = "SeekCrew";
				}
			}
		break;

		case "FS_1":
			dialog.text = "�� ��������"+ GetSexPhrase("���","���") +", �������, ������ ���� ����� �� ���������. ���� �� �� �����"+ GetSexPhrase("��","��") +" � ������ ����� ���� ����� - �� �� �� �� ��� �� �����"+ GetSexPhrase("","�") +" ��������� �� ����.";
			link.l1 = "� ����"+ GetSexPhrase("�","���") +", ������ ������...";
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = "��� ������ �� ������, ����� ���� ���� � ����� ������ ������! ������ ����� ����� �� �����, � ������ ��� ���� ���� ����.";
			link.l1 = "�������...";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//������ �����
		case "room":
   			if (chrDisableReloadToLocation) //���-�� ������ ������� � ��.
			{
				dialog.text = "� �����, ��� ���� �� ����� ������ �����. ������ ���...";
				link.l1 = "�����.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "�� ������ ��������� �� �������, ��� ��������� �� ������� �����. ����� ���� ���������?";
			if(!isDay())
			{
				link.l1 = "�����.";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "� ����.";
				link.l1.go = "hall_night_wait";
				link.l2 = "��������� �����.";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "���������"+ GetSexPhrase("","�") +". �������� ��� ���.";
			link.l3.go = "exit";
		break;
		case "hall_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		case "hall_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//�������
		case "int_quests":
			dialog.text = "����������� ���� ������, "+ GetSexPhrase("�������","" + pchar.name + "") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = "������� � ���, �������, ������ �����������!!";
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "��������, ��� ��� �� ������?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "��� ����������, ��� � �����"+ GetSexPhrase("","�") +" ����?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "� ���, ������ ������������� ���������� ���������? ������� �������� ������, ������� ������ ��������� ���� �����?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "��� �� ����� ������, ���� ������?..";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l6"))
			{
				link.l6 = "��������, �� ���� ������ �������� - ������ ����?";
				link.l6.go = "ansewer_6";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l7") && pchar.questTemp.LSC == "AdmiralIsWaiting" && CheckCharacterItem(pchar, "keyQuestLSC"))
			{
				link.l7 = "��������, �� �� ������, ��� ����� ���������?";
				link.l7.go = "ansewer_7";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l8"))
			{
				link.l8 = "��� �� ����� ����� � ������?";
				link.l8.go = "ansewer_8";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l9"))
			{
				link.l9 = "������, ��� ��� ����� �� ����� �������. ��� ����� ���� ����?";
				link.l9.go = "ansewer_9";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l10"))
			{
				link.l10 = "� ��� ����� ������� �����?";
				link.l10.go = "ansewer_10";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l11"))
			{
				link.l11 = "���-�� � ����� �� ������� � ������. ��� �� �����-������ �����, ��� ��?..";
				link.l11.go = "ansewer_11";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l12") && CheckActiveQuest("LSC_findDekster"))
			{
				link.l12 = "������, �� �� ������ ��� ����� ������ �������?";
				link.l12.go = "ansewer_12";
			}
			link.l20 = "��� ��������. ������, ��������...";
			link.l20.go = "exit";
		break;
		case "ansewer_5":
			dialog.text = "��� ��� ������! ������ � ������. ������ ����� - ������� ����.";
			link.l1 = "�������...";
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = "���� ����� ���������� ������ ����� � ������. � ��� �������� �� �������� ���������� � ��������, ��� ��� ���� �� ��������� ������ �� �� ������� � ����, �� �� ������ ���� ���.";
			link.l1 = "�������?";
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = "��� ������, "+ GetSexPhrase("��������","" + pchar.name + "") +". �� ���� � ���� �����, ��� ���� �����!";
			link.l1 = "����.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_1":
			dialog.text = "��� ����� ���������� ��������, "+ GetSexPhrase("��������","�������") +". ���� �����"+ GetSexPhrase("","�") +" ����, �� ������ ��� ����, ��� ���"+ GetSexPhrase("","�") +" ������. ������ �� ���������, � ���������...";
			link.l1 = "������!!";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "�� ����, ��� ���� ���� ��������, ��� �� ���� ������"+ GetSexPhrase("","�") +". �� �� �������, ����� �������� ���"+ GetSexPhrase("","�") +" � ��������"+ GetSexPhrase("","�") +". ��� � ������ �� ����, ����� ���� � �����, ����� �����, ����� ����� �������... ��� � ���.";
			link.l1 = "� ������ �� �����?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "����� ��� ������, �������, ���� ������� ��������, ��� �������. �� ��� ��� ��� ��������� ���� ������ - ������� �� ����. ����� ��. ������-��, ���� ��� ��������� ����� ��������, ��� ��� ���� �������.";
			link.l1 = "�� ��...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = "��!!! � ������ �� ���"+ GetSexPhrase("��","��") +" ���"+ GetSexPhrase("��","��") +" ����"+ GetSexPhrase("��","���") +"?.. ���� �������, �� ��� ���������. ����������, ��� ���� ����� ��������� � �������� ������ ��. �� ����� ����� �������� ��������, ��� ��� ��� �������� ��� ������������. ���� ����������� �����-������ �������, �� ������ �������� ���������, ��� �������� ��������, ����� ������ �� �������\n� �����, ��� ����� �������. ������� ������ ��� ��������� ����� �������. � ��� �����!";
			link.l1 = "�������...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_4":
			dialog.text = "�� ������ ���������. ����, ������, ������� ��� �� ������... � ������, ����� ����� �� ��������� ������. � ��� ������� ���������� ���� ����� ������ � �������� �������.";
			link.l1 = "��� ��� �� �������?";
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = "���, "+ GetSexPhrase("��������","" + pchar.name + "") +", ��� ���������� ����� �������� ��������������, ��� ������ ��� �����. �������, ��� ������ �� ��� �������, ��� ��� �������� ��� �� ����� ��� ����.";
			link.l1 = "����� � �� ����������... � ���, � ��� ������������� �������� ������, � �������� �������� ��������?";
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = "��, �����-�� ������ ����, �� ������ ��� ��� �� ���������. ��� ������ ����������� �� ������ �������������, ����� �� ����� ������ ������. ��� ����� �� �����...";
			link.l1 = "��� ������ '���'?";
			link.l1.go = "ansewer_4_3";
		break;
		case "ansewer_4_3":
			dialog.text = "�� '���' ���� ��������, ������� ������ ����� ���������. �� ������ �� ��� � ����.";
			link.l1 = "������ ������, ��� ��?";
			link.l1.go = "ansewer_4_4";
		break;
		case "ansewer_4_4":
			dialog.text = "��, ����� � ��� �������. �� ��� ������...";
			link.l1 = "�������.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_6":
			dialog.text = "����. �� ��� � ��� ��������� �������, ����� �����. � ����, ������� ��� �����.";
			link.l1 = "� ��� � ���!";
			link.l1.go = "ansewer_6_1";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_6_1":
			dialog.text = "���, ��������� ��� �����?";
			link.l1 = "�� � �� �� ����! ������, ��� �� �����-�� ������� �������� �� ������� �����...";
			link.l1.go = "ansewer_6_2";
		break;
		case "ansewer_6_2":
			dialog.text = "������!!! �� ����� ����!..";
			link.l1 = "�����. ������, ���, � �����, �� �������� ��� �������, �� ���� �����...";
			link.l1.go = "ansewer_6_3";
		break;
		case "ansewer_6_3":
			dialog.text = "����! ����!! ����!!! ������� ��� ��������?..";
			link.l1 = "�� ��� � ���?";
			link.l1.go = "ansewer_6_4";
		break;
		case "ansewer_6_4":
			dialog.text = "������ ���, "+ GetSexPhrase("��������","" + pchar.name + "") +", ��� ��� � ���� �����: ������ �� ������ �� ����! ���� ������� ������, ��� ���-�� ������� �����, �� ��� � ���� � ��������... � �����, ����� �������� �� ������������.";
			link.l1 = "��, �� �������...";
			link.l1.go = "ansewer_6_5";
		break;
		case "ansewer_6_5":
			dialog.text = "������� �����. � ����, ���� ������ �� �����, ����� ���, ��� � ������. �� �������� ��� ������! �����"+ GetSexPhrase("","�") +"?";
			link.l1 = "�����"+ GetSexPhrase("","�") +".";
			link.l1.go = "ansewer_6_6";
		break;
		case "ansewer_6_6":
			dialog.text = "������. � � ���� ��������� ������� �� ���� ����� �������...";
			link.l1 = "�� �����, ���������.";
			link.l1.go = "int_quests";
			AddQuestRecord("ISS_MainLine", "4");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "�"));
			SaveCurrentQuestDateParam("questTemp.LSC"); //�������� ���� ������
		break;
		case "ansewer_7":
			dialog.text = "��� ����� '�������� ���������', ������ �����.";
			link.l1 = "���� ����, ������...";
			link.l1.go = "ansewer_7_1";
			NextDiag.(NodePrevName).l7 = true;
		break;
		case "ansewer_7_1":
			dialog.text = "����� ���� �� ���� ������ ��� ����� �� ��� - �� ��������� �������� �������. ������, ���-�� �������� �� �����������, ���������, ������, �� ����. � �����, ������� ���� ��������� �����, ����� ��� �� ����� � ���� �� �����.";
			link.l1 = "������?";
			link.l1.go = "ansewer_7_2";
		break;
		case "ansewer_7_2":
			dialog.text = "����� �������, ����� �������� ������� �� ����, ����������� �� ��������� ������. ��� ��� ���� ���� �����������, ����� ��� ��������� �����.";
			link.l1 = "�������...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_8":
			dialog.text = "���� ����� � ��� � ������. ������, ������ ��������� ��, ��� ���� �� ����� ��������. ��� ��� ��� � ���� - �����...";
			link.l1 = "��, ��� ������?";
			link.l1.go = "ansewer_8_1";
			NextDiag.(NodePrevName).l8 = true;
		break;
		case "ansewer_8_1":
			dialog.text = "��, � ��� ����� ���������� ����������, ������... � �����, ������������ ��������, ������� ��������.";
			link.l1 = "�� ��� ���, � ���� � �������� ��������? � ���� �����!";
			link.l1.go = "ansewer_8_2";
		break;
		case "ansewer_8_2":
			dialog.text = "���, �� �� "+ GetSexPhrase("�������","������") +" �����, �� - ��������� �������. ���, � ���� ����"+ GetSexPhrase("��","�") +" � ������� ���� ���� �������� ���� ������?";
			link.l1 = "��, �������, ������ ������.";
			link.l1.go = "ansewer_8_3";
		break;
		case "ansewer_8_3":
			dialog.text = "��� ��� � � ���� � ����... � �����, ������ �� ��� �������, ����� ��� � ���� ��� ���������� � ��������� ��������� �� ������. ������� �� ����� �������� �� ������ � ����, ����� ����� ��� �� ������ ������.";
			link.l1 = "�� � ���, ��������� ������ � ����?";
			link.l1.go = "ansewer_8_4";
		break;
		case "ansewer_8_4":
			dialog.text = "����, �������, �� ������ ��� ����. �� ���� � ����, ��� ���� ������ �� �������� �������� �� �����!";
			link.l1 = "�������. �� ��� ��, ������� �� ����������.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_9":
			dialog.text = "��� ������, ��� � ����. ��� ������ ���� �������, ����� ���� � ���� �������� �� �����.";
			link.l1 = "�-��, ������ ��������, ���� ���...";
			link.l1.go = "ansewer_9_1";
			NextDiag.(NodePrevName).l9 = true;
		break;
		case "ansewer_9_1":
			dialog.text = "��, ��� ���� �������? ��� ������� ������� �� ����� ���� ������� ���������. ���� ������� ���� ����� ����� ���� �� �����, �� � ���������� ���� �������. ���� ������ � ������� � �������� ������� ���� ������ ������������� ������ ����.\n"+
				"���� ���� �� ����������� �����, ���� � ����, ��� ����� ����� ���� � � ������. ���� ������ ���-�� �������� �������, �� ����� ������ ������� ��������, �� �������.";
			link.l1 = "�� ���, ��� �����-����� ����. �������.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_10":
			dialog.text = "��! ���� �� � ����, "+ GetSexPhrase("��������","" + pchar.name + "") +", ��� ����� ������� �����... � ������ � � ����� ����� �� �����.";
			link.l1 = "�������, ����������.";
			link.l1.go = "ansewer_10_1";
			NextDiag.(NodePrevName).l10 = true;
		break;
		case "ansewer_10_1":
			dialog.text = "��, ���� ��� �� ���� ����� - ����� �� �����, � �� ������, ����� � ���� ���-�� ��������. �� ���� ������ � ����, �� ����� �� ���� ��������� ��������"+ GetSexPhrase(", ��������","") +".";
			link.l1 = "������ �� �����"+ GetSexPhrase("","�") +", �� �� �����...";
			link.l1.go = "int_quests";
		break;
		case "ansewer_11":
			dialog.text = "������ � ����� ����� � ��������. � ���� ������ ���� �����.";
			link.l1 = "�������, �������.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l11 = true;
		break;
		case "ansewer_12":
			dialog.text = "�-�� ����, � ���� ����� ���?";
			link.l1 = "��, �� ������ ���������...";
			link.l1.go = "ansewer_12_1";
			NextDiag.(NodePrevName).l12 = true;
		break;
		case "ansewer_12_1":
			dialog.text = "�� ����� ���� �������� � ���� ����, "+ GetSexPhrase("��������","" + pchar.name + "") +", �� ������ ���.";
			link.l1 = "��������, �������. ��� � ���������, ����� ��� ���.";
			link.l1.go = "ansewer_12_2";
		break;
		case "ansewer_12_2":
			dialog.text = "��, �����... � �����, ������� �� ��������� � ����� ��� �������. ��� ��, ��� � ������, ������. � ���-�� � ��� ��������� ����� �� ����������. ������ ������� ������. ��� � ���, ��� � ���� ���� ����������.";
			link.l1 = "��, �� �����... �� ��� �����, ������� ����, " + npchar.name + ".";
			link.l1.go = "int_quests";
		break;

		// ------------------ ������ ------------------
		//������ �������� ������ � ������ �������
		case "Tizer":
			dialog.text = "��-��, � ����������. ������ �������� �� ���� ����� �� ����. ����� ���������� � ���� � ������ ������� ����� ��������.";
			link.l1 = "� ��� ��������� ���� ���� ������ ������?";
			link.l1.go = "Tizer_1";
		break;
		case "Tizer_1":
			dialog.text = "��, �������� � ������� ��� �� ��������, � ������ ��� ���� �� ���� �����. ����� ����� �� �������� ������ '�������' � � ��� ����� � ����������.";
			link.l1 = "�������. �� ��� ��, ������������.";
			link.l1.go = "Tizer_2";
		break;
		case "Tizer_2":
			dialog.text = "�� ������������, ����� ���� ����� � �� �����.";
			link.l1 = "�������. ���� �����������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toWineCellar";
			AddQuestRecord("ISS_MainLine", "5");
		break;
		//������ ��������, ��� �� �� ������ � ������
		case "TizerCellarLate":
			dialog.text = "��� ��� ��������, ���� � ���� ���� ��� ����� ���! ���� ������, ������ �� ���� ���"+ GetSexPhrase("��","��") +" ������������"+ GetSexPhrase("��","��") +" � ����� ��������� ����!";
			link.l1 = "� ����� ����� ���������?";
			link.l1.go = "TizerCellarLate_1";
		break;
		case "TizerCellarLate_1":
			dialog.text = "��� ��� ������, ��� � �� ���� �� ���� ���� ������� � ����� ��������! ��� �������!";
			link.l1 = "�����, �� ��������. ����� ��� ��� ��������� �����������, ��� ��� ��� ����������.";
			link.l1.go = "TizerCellarLate_2";
		break;
		case "TizerCellarLate_2":
			dialog.text = "��, ������. ��� ���� ��� ��, � �������, ������� ����� ��������. �� �� ��� ��� ������ �������.";
			link.l1 = "������, ���� �����������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toWineCellar";
		break;
		//����� � �������� � �������
		case "TizerCellar":
			dialog.text = "�� ������ �� �������"+ GetSexPhrase("","�") +" � ������ ���� �� ��� �����?";
			link.l1 = "���, ��� �� � ��������������.";
			link.l1.go = "TizerCellar_1";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.LSC_returnBarmen_2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_returnBarmen_2.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_returnBarmen_2.function = "LSC_returnBarmen_2";
		break;
		case "TizerCellar_1":
			dialog.text = "��� ������. ����, ����� � ������ ���� ���������� ����� ����������� �� ����� ������.";
			link.l1 = "� ������������� ��������.";
			link.l1.go = "TizerCellar_2";
		break;
		case "TizerCellar_2":
			dialog.text = "��, ��������, ��� � ����� ����, ��� ����� ������ ��������� ������� ���-����, �� ��� ����� ������ ������. ��� ���, � ������ ��� �� �������, ��� ��� ����� ���� ��������� ������� ����� ������, �� ��� � ������� �� ��� ��������� �� ������� �����.";
			link.l1 = "� ���������, ��� ����� � ������� ��������� �� ��������, �����, ��� ��������, � �����"+ GetSexPhrase("","�") +" �� ��� ����������� ����� ����.";
			link.l1.go = "TizerCellar_3";
		break;
		case "TizerCellar_3":
			dialog.text = "��, ����... ��, ����� �������� �� ��, ��� �����. � ����� �� �������, ������� ����� ��������� ��� ����� �������. ������, ��� ���-�� ������, ���������� � ������� ��������, ��� ����� ���� ��������� ������.";
			link.l1 = "� ������ ���?";
			link.l1.go = "TizerCellar_4";
		break;
		case "TizerCellar_4":
			dialog.text = "���� �������� ������, ��� ����� �������� �� ������� �����, ��, ��� ��������, ������ ������� ����������� ��� �������. ������ ������, ��� ���-�� �������� � ������ ����, ����� ����� �������������� ����� �����������.";
			link.l1 = "�� ���� �...";
			link.l1.go = "TizerCellar_5";
		break;
		case "TizerCellar_5":
			dialog.text = "������ ������ ����� ����, "+ GetSexPhrase("��������","" + pchar.name + "") +"\n� ��� ��� �����. �� ����"+ GetSexPhrase("��","��") +" ����������� �� ����� '�������� ���������'. ����� ��� ������� ����������� - ������� ������� ������� � ��������� ��� �������� �� �����������. ������ ������ ��� ����� ��� �������� ����� ����� �������. �������, ��� ������ ��� �� ������ ����� ���� � ����� ������.";
			link.l1 = "��� ���� ���������?";
			link.l1.go = "TizerCellar_6";
		break;
		case "TizerCellar_6":
			dialog.text = "������, ����� �� ��������� � ������ ���������������. ���������� � '����������' ��������� �������� ����� '����� �����' � ���� '��� ��������'. ��� ��, �� ������ ����� ����� ����� �����������, �� ������� ��������� � ����.\n� ���� �������"+ GetSexPhrase("��","��") +" �� '��� ��������', �� ������ ������. ���� ���� - ������������� ����� '������'!";
			link.l1 = "����. ��������, �� ������ ���� �������� �������, ��� �� ���� �� '����������'?";
			link.l1.go = "TizerCellar_7";
		break;
		case "TizerCellar_7":
			dialog.text = "���� �� � ����! ������� ����, ��� �� ���� �������������� ����, ��� ���������� ����� ��� ����� ��������� �� ������� �����.";
			if (CheckCharacterItem(pchar, "letter_LSC"))
			{
				link.l1 = "��, �� ������, �� '����������' � ��� �������"+ GetSexPhrase("","�") +". � ���"+ GetSexPhrase("��","��") +" ��� ������ ������. � ���, ����� �������, ���� ��� � ����� ���������� ������...";
				link.l1.go = "TizerCellarOk_1";
			}
			else
			{
				link.l1 = "�� ������, � ���� ���� ����, ������� ���� ������ ����� ��� �� ������� �����. ���� ���� ����� ��� ������� ������� ����, ��� ���������� �� ������ ������� ��������������, �� ���� ������ ���������� ��������.";
				link.l1.go = "TizerCellar_8";
			}
		break;
		case "TizerCellar_8":
			dialog.text = "���������, ����� ���������... ������, ��� ����� �� ������ �� ����������. ������ ��������� ����, � ����� ����� �� ������ ��������� ������� ��� ����������"+ GetSexPhrase("�","�����") +" �����������. � ����� ��� � ����� ������. ����? �� ������ � ������ �����, ����������� ������ ������ ������ �� ����.";
			link.l1 = "��, ���� �����.";
			link.l1.go = "TizerCellar_9";
		break;
		case "TizerCellar_9":
			dialog.text = "������, ���� - ��� ��� ���. � ��� �������� ������ ������� ��� ����?";
			link.l1 = "��� ��� ���� '���������'.";
			link.l1.go = "TizerCellar_10";
		break;
		case "TizerCellar_10":
			dialog.text = "�����! �� �� ������ ����!\n����������� � '����������'. �������, ��� ��� �� ������� �������, � �������� ������ ���� � ��������. �����, ���� � ������� ��� ��������� � ���������, ��� �� ����� ��� ������ �� �����, ���� �� �����...";
			link.l1 = "�-��, ����� ����. �� ��, ��� �� ��� ��������� ������� - ��� ����.";
			link.l1.go = "TizerCellar_11";
		break;
		case "TizerCellar_11":
			dialog.text = "��������! ��, �� ����� ������ �������. � ��� ���� � ������������ ������������ ������.";
			link.l1 = "����� ����, �������. ������.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "6");
			pchar.questTemp.LSC = "toDiffindoor"; //���� ������� ���
		break;

		case "TizerCellarOk_1":
			dialog.text = "��� ��� �� ������?";
			link.l1 = "������ ���. ���, �����.";
			link.l1.go = "TizerCellarOk_2";
			TakeItemFromCharacter(pchar, "letter_LSC");
		break;
		case "TizerCellarOk_2":
			dialog.text = "���-���, ����� ���������... �� �����: '...��� ��� �� ����� � ����� �������� ����������.' ������, �� ��� �� ����...";
			link.l1 = "��, ���� �� �����, �� ����.";
			link.l1.go = "TizerCellarOk_3";
		break;
		case "TizerCellarOk_3":
			dialog.text = "��-��, ��� ��������! � ������� ���� ������, �� �� �� ��� �� ����� �� ����� �� ��������� � �������� ����� - ���� � ���� �� �� ���� ����� �����. �� ��� �� �����-���� ��������� �� ������� �����, ������, ��� ��������, ��� ���� ����, �������� ������������ � ����������� ����\n��! �� ���� ��� ��� �������, ����� �����!! ��� ���, "+ GetSexPhrase("�������","�������") +", ����������� � ����. �������� � ��� ���� � �����, �������� � ������ ����. � �� ���� �� � �� �����, ��� ���� ������� ���-���� �������� �� ������� �����!";
			link.l1 = "� ��� ����������? ���� ������ ������ ��� �������� ��������������� ���� ����.";
			link.l1.go = "TizerCellarOk_4";
		break;
		case "TizerCellarOk_4":
			dialog.text = "��� �����, ��, ��� �� �����, ���������� ���������, ��� ����� ��������� ���������� ����� ����. � �� �����, ��� ��� ����� ��������� ������ ��������� ������, �� ���� ����������� ����������� ������.";
			link.l1 = "������? ��� ������� ������ �� ��������� ��������, ��� ����� � �������� ����. ��� � �����, ��� �� ��� �������.";
			link.l1.go = "TizerCellarOk_5";
		break;
		case "TizerCellarOk_5":
			dialog.text = "�� ��� ��� ������, "+ GetSexPhrase("�������","" + pchar.name + "") +". �� ������ ���� ����� ������� � ����, � �� ����� ������ ����� ��� ��� ��������. � ������� ��������� ������ �� ����� �� ������ ������� �����, � ��������� ������ ������� ��� ����!";
			link.l1 = "��, �������, �� ����...";
			link.l1.go = "TizerCellarOk_6";
		break;
		case "TizerCellarOk_6":
			dialog.text = "� ��� ����� �� ��������, ��� ������� ���� �� ����� ������, ������� ���� � ���� ������ � �������������. ��������� ������ ��������� ������, ������� ������ �������� � ��������� �� �����������, - ������� ����. �� ������ ������� �������� � ����� �������, � ������� ��� ����� ��������, ��� ��� �������.";
			link.l1 = "������ ��������?";
			link.l1.go = "TizerCellarOk_7";
		break;
		case "TizerCellarOk_7":
			dialog.text = "��, ��� ���� �������... ������ � ����� ���� �� �����, ��� ������� �� �����-�� ������ �������� ������.";
			link.l1 = "��, ���������...";
			link.l1.go = "TizerCellarOk_8";
		break;
		case "TizerCellarOk_8":
			dialog.text = "� �����, ��� ��� ��� �������, � ��� �� �������� �������. � ������ ����� ����� ������ � ��������� ������ ��� � ��� ������� � ���� ������.";
			link.l1 = "������, � ��� � ������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toAndreLabor"; //���� ������� ���
			AddQuestRecord("ISS_MainLine", "7");
			pchar.questTemp.LSC.checkBoxes = true; //������� �� �������� �������� ����������
		break;

		case "AfterProtector_1":
			dialog.text = "��� ���������?";
			link.l1 = "��... ��, � �����, ���������"+ GetSexPhrase("","�") +" � � ���������, ���� ����� �������, � �� �������� ���� ������ � ����� ������� '���������'. � ���� ���"+ GetSexPhrase("��","��") +", ��, � ��� ���, ������ ������ �� ����� ����... � ���� ����� ������ ����������� �� �������� �� ����! �������� ���� ��������� �� ��� ����.";
			link.l1.go = "AfterProtector_2";
		break;
		case "AfterProtector_2":
			dialog.text = "������! ��� ���� ��! ��, ������ ���� �����... ������, ���� ��� ����"+ GetSexPhrase("","�") +", �� �����������, ��� ��� � ���� ��������. ���� ��� ��� ����� �����, � � ��� ������ ����...";
			link.l1 = "���� ���� ��� �������! ����� ���� �� �����, ���� ����� � �� �����, ��� ��� ������"+ GetSexPhrase("","�") +" ������ �. ��� �� ������ ���������� ��� ��� ��������.";
			link.l1.go = "AfterProtector_3";
		break;
		case "AfterProtector_3":
			dialog.text = "�� � ���� ������"+ GetSexPhrase("","�") +"?";
			link.l1 = "���������� ��� ��� ������.";
			link.l1.go = "AfterProtector_4";
		break;
		case "AfterProtector_4":
			dialog.text = "��� �����, ���� ������������� ������ �� ����. ������� ������ �� �����, �� ���� ��������.";
			link.l1 = "� ��� �� �����������?";
			link.l1.go = "AfterProtector_5";
		break;
		case "AfterProtector_5":
			dialog.text = "��, �����, ��� ���� ��� ������� �� ���� �� ������.";
			link.l1 = "�� �����?";
			link.l1.go = "AfterProtector_6";
		break;
		case "AfterProtector_6":
			dialog.text = "�� ���� '������', ��� �������� �����.";
			link.l1 = "� ��� ��� �������? � �� �� ���� ������ � ���� � �������: '��� �� �, ��� ��� '�������'!'.";
			link.l1.go = "AfterProtector_7";
		break;
		case "AfterProtector_7":
			dialog.text = "� ���� ������ ����� '������' ���� ������ � ������������ ������������ ������������ ������. ������� ������ � ��� � ��� � ��������. ���������� ��� � ���, ��� ���"+ GetSexPhrase("��","��") +" ��� �� ����� �������� ����������� � ��������.";
			link.l1 = "�� � ��� ��� ����� ��� ������?";
			link.l1.go = "AfterProtector_8";
		break;
		case "AfterProtector_8":
			dialog.text = "� ������� ����� ������� '�������' ���� �����, � ������� '�������' ������ ������ ������. ��� � ��� ���-�� ����� ��������. ��� ����-������ �� ��� ���, � ����� '������' �������� � ���� ���.";
			link.l1 = "�������. �� ��� ��, ��� � ��������.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "10");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��", "��"));
			pchar.questTemp.LSC = "toKillOneNarval";
			pchar.quest.LSC_KillOneNarval.win_condition.l1 = "locator";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.location = "VelascoShipInside1";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.locator = "reload2";
			pchar.quest.LSC_KillOneNarval.function = "LSC_KillOneNarval";
		break;

		case "NarvalRing_1":
			dialog.text = NPCStringReactionRepeat("�������! ������ ��� � �������� � ��������, ��� ���"+ GetSexPhrase("��","��") +" ��� � ����� '����������'.", 
				"� ��� �����. �� ���, � �������� ��� ���� ����������.", 
				"������, ��� ��� �� ������. ��� � ��������!",
                "��, �� ���"+ GetSexPhrase("��","��") +", ������...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�����"+ GetSexPhrase("","�") +".", 
				"��, �������...",
                "���, �����������!", 
				"��, ���"+ GetSexPhrase("��","��") +" ������"+ GetSexPhrase("��","���") +". ��� ����-�� ����� ���� � ����. �� ��� ����������� - ���������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
	
		case "AfterNarvalDesrt_1":
			dialog.text = "�� ��!";
			link.l1 = "�����! ��� ������ ������� � �����"+ GetSexPhrase("","�") +" �������� �������, ��� �������� ����������� ��������� '�������'. ������� ������� � ������ ���� ���������� �� ����. ��� � � ������"+ GetSexPhrase("","�") +".";
			link.l1.go = "AfterNarvalDesrt_2";
		break;
		case "AfterNarvalDesrt_2":
			dialog.text = "�-��, ����... ��, "+ GetSexPhrase("������","���������") +", ������ ���� ��������. ����, ���� ��� ������� ������������, ����� �� ������ ������ ������, ��� ������.";
			link.l1 = "��� ������?";
			link.l1.go = "AfterNarvalDesrt_3";
		break;
		case "AfterNarvalDesrt_3":
			dialog.text = "���������, �� ������ '�������' � ������ ����������� ������ - '�������' ���������������� '���������'. ������ ��� � �������...";
			link.l1 = "���, �� �� ��� ����� ���� ���������� '��������', � ������ ���������.";
			link.l1.go = "AfterNarvalDesrt_4";
		break;
		case "AfterNarvalDesrt_4":
			dialog.text = "��, � �� ��, ��� ���������, ������ ���� ����������� ����������. � ���� ��, ����� � ������� ���������, �������...";
			link.l1 = "��, �� ��, ��� ���� �������.";
			link.l1.go = "AfterNarvalDesrt_5";
		break;
		case "AfterNarvalDesrt_5":
			dialog.text = "��� ������ ������� ������? �� ���� ������ ����"+ GetSexPhrase("�","���") +".";
			link.l1 = "�� ����. ������, ��� � �����"+ GetSexPhrase("��","���") +" �������� � ����. ������, ��� ����� �������� ���������. �����, � ������� ��������...";
			link.l1.go = "AfterNarvalDesrt_6";
		break;
		case "AfterNarvalDesrt_6":
			dialog.text = "��� ���, "+ GetSexPhrase("��������","" + pchar.name + "") +", �� ���� �������, �� �� ������� ������������ �� ���. � ��� ���������� �������� ���-���...";
			link.l1 = "��� ������?";
			link.l1.go = "AfterNarvalDesrt_7";
		break;
		case "AfterNarvalDesrt_7":
			dialog.text = "���� ���� �������� �� ����.";
			link.l1 = "�����, ����� �������� � ����.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "waitInterception";
			SaveCurrentQuestDateParam("questTemp.LSC"); //�������� ���� ������
			AddQuestRecord("ISS_MainLine", "17");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "�"));
		break;

		case "Interception":
			dialog.text = "������, � ���� � ������� ����� ���� ���������� ���������. ����� � �����, ��� � ���������������� ��� ������ �� ���, ��� ���� �� ����� ����...";
			link.l1 = "����?";
			link.l1.go = "Interception_1";
		break;
		case "Interception_1":
			dialog.text = "� ��������� ����, � ��������� ����, ������ ��... � �����, � ��������� ���� ���������� ���� ����. �� �������, ��� ��������� ��� ������ ������?";
			link.l1 = "�����, �������.";
			link.l1.go = "Interception_2";
		break;
		case "Interception_2":
			dialog.text = "��� ���, ���� ��� ������� �� ��������, ������ ����� ������� �� �������� � �������. ������ ��������� ���, ����� ����� ���� �� ���� ����� ��-�� �������. ��������, ���� ������� ���������� ����� ���������� ��������, ������� �������� �� ���� ������� � ���������� ���������.";
			link.l1 = "��� ��������?";
			link.l1.go = "Interception_3";
		break;
		case "Interception_3":
			dialog.text = "�������� � ��� ������ ��������. ��� ������ ����� ��� ���������, � ��� ��� ��� ��� ������������ ��������... � �����, ������ ���, �, �������, ���������� �� ������ ����������.";
			link.l1 = "������, ��� �������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toInterception";
			pchar.questTemp.LSC.itemState = false; //���� ���������� � �������� ���� � �������
			AddQuestRecord("ISS_MainLine", "18");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��", "��"));
		break;

		case "InterceptionLate":
			dialog.text = "�� ��, �������� ����, ��� ���������... ��, ������ ����� ��� ������ � ���� ��� ������.";
			link.l1 = "��, �������... � ��� ��� ��� �������, � ��� ������� ������ ��� �����������?";
			link.l1.go = "InterceptionBadWork_1";
		break;
		case "InterceptionYouSeen":
			dialog.text = "�� ��, �������� ����, ��� ���������... ��, ������ ����� ��� ������ � ���� ��� ������.";
			link.l1 = "��, �������... � ��� ��� ��� �������, ��� ������������ � ���������?";
			link.l1.go = "InterceptionBadWork_1";
		break;
		case "InterceptionBadWork_1":
			dialog.text = "��� ������� ����� '������' ������ �������.";
			link.l1 = "��-��, ��� ��� ��!..";
			link.l1.go = "InterceptionBadWork_2";
		break;
		case "InterceptionBadWork_2":
			dialog.text = "���-�� � �������� ���������� � ���� � ������� �������, ����� ��� �������������. ����� ��������� �� ���� � �����, ��� ��� ������� ����������� ����� ����� �� �������. ����� �� � ��������, � ��� ��� �������...";
			link.l1 = "��, ����� ��� �� ������? ����� �������� �� ��������� �������.";
			link.l1.go = "InterceptionBadWork_3";
		break;
		case "InterceptionBadWork_3":
			dialog.text = "��������, �������, �� ������ � ��� ��� ������ ������. ��������� ���� �� �������� �� �������� ������ ������, ����� ���������� ����� ����� '��������'. � ������ ���� ����� ���������...";
			link.l1 = "��, �������. � ����� �����?";
			link.l1.go = "InterceptionBadWork_4";
		break;
		case "InterceptionBadWork_4":
			dialog.text = "��� �� ��� ���������.";
			link.l1 = "����. ��, ������. ���� ������������ � ���� ����� �� �������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "waitInterceptionResult";
			AddQuestRecord("ISS_MainLine", "21");
			SetTimerFunction("LSC_changeBarmen", 0, 0, 15);
		break;

		case "Result":
			dialog.text = NPCStringReactionRepeat("���� ���, �� � ��������. ���.", 
				"� ��� ������� ����, ����� �� ���������"+ GetSexPhrase("","�") +" �����. ���� ������ ������.", 
				"� ������ ��� �������� - ���.",
                "�� ������� ���?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������.", 
				"��-��, � �����"+ GetSexPhrase("","�") +".",
                "�����"+ GetSexPhrase("","�") +", ����� �����.", 
				"��-�, � ���"+ GetSexPhrase("��","��") +", �������"+ GetSexPhrase("��","��") +".", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "InterceptionOk":
			sld = characterFromId("LSCMayor");
			if (sld.location == "FleuronTavern")
				dialog.text = "������ ����, "+ GetSexPhrase("��������","�������") +"! � ���� ��� ������� ��� ��� �������������... �� ���, �����"+ GetSexPhrase("","�") +" ��������� ��������?";
			else
				dialog.text = "�����"+ GetSexPhrase("","�") +" ��������� ��������?";
			link.l1 = "�����"+ GetSexPhrase("","�") +". �����������, ������� ��� ���������� �������� �����!";
			link.l1.go = "InterceptionOk_1";
		break;
		case "InterceptionOk_1":
			dialog.text = "�� ����� ����! �� �� ������ ��� ����� ������, ��� ��������� ���� ������� �������!";
			link.l1 = "��, ���� �� ��� �� ������, � ������ ����������.";
			link.l1.go = "InterceptionOk_2";
		break;
		case "InterceptionOk_2":
			dialog.text = "���������� ������� ��� ������ �� ������ �������!";
			link.l1 = "�����. ���� '������' �������� �� ��������. �� � ������, �� �������� �������� ������ ������ �� ����, ����� ��� �� ����.";
			link.l1.go = "InterceptionOk_4";
		break;
		case "InterceptionOk_4":
			dialog.text = "��, �������������... ��, � �� ���� �������, ��� ��� ����� �����!";
			link.l1 = "�-��, ������ ������... ��������, ������� �������� � �����-�� ��������. ��� ���?";
			link.l1.go = "InterceptionOk_5";
		break;
		case "InterceptionOk_5":
			dialog.text = "��, �� ����...";
			link.l1 = "��� ������!.. ��������, �� �� ����� ����� ������, ������ ����� ����.";
			link.l1.go = "InterceptionOk_6";
		break;
		case "InterceptionOk_6":
			dialog.text = "� � ���� �� ����"+ GetSexPhrase("","�") +", ��� ���� ���� ������� ����������? �����, �� ������� �����"+ GetSexPhrase("","�") +" ����� ���������� ���������?";
			link.l1 = "����� ����, �� ���� ��... ������, � ���� ���������, ��� ��� ��� ����� �� ������ ��������� � ������?";
			link.l1.go = "InterceptionOk_7";
		break;
		case "InterceptionOk_7":
			dialog.text = "���-�� ����������� ��������. �����, �� ����� ������...";
			link.l1 = "�����? �������, ��� �������.";
			link.l1.go = "InterceptionOk_8";
		break;
		case "InterceptionOk_8":
			dialog.text = "������, �������, �� �� ������. � ������ ��������, ��� ��� ������� ������.";
			link.l1 = "������������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "waitInterceptionResult";
			AddQuestRecord("ISS_MainLine", "23");
			SetTimerFunction("LSC_changeBarmen", 0, 0, 3);
		break;
		//������ ��������
		case "NB_1":
			dialog.text = "�� ���, ������ �� ������? �������� ������ ���...";
			link.l1 = "��� ���?";
			link.l1.go = "NB_2";
			npchar.quest.HillNB_1 = true;
		break;
		case "NB_2":
			dialog.text = "��� ����� ������� � ������ ������� �������. ������ ��� ����� �� �����, ��� ����� ������ �����? ��� ��� ��� ��� � �����...";
			link.l1 = "��� ��� ��! ����-������ ������? ������ �����?";
			link.l1.go = "NB_3";
		break;
		case "NB_3":
			dialog.text = "���, ����� ������ �� �����. ����, ���� ����������, ����� ��� ��� �������. ��� ����� � ������, ����� ���� ���������� ��� �������, � ���...";
			link.l1 = "���� ������!.. ������ �� ������ �������, ��� � �������.";
			link.l1.go = "NB_4";
		break;
		case "NB_4":
			dialog.text = "��. ��� ������ ��� ����� ��������, ������� ������ ���� � �������� �������� ����� ��������. ��� �������, ���"+ GetSexPhrase("","�") +" ���������, ����� ���...";
			link.l1 = "��� �����... �� �����, ����� ����� �� ����� �����.";
			link.l1.go = "exit";
			if (pchar.questTemp.LSC == "barmenIsDeadYouKnow")
			{
				pchar.questTemp.LSC = "toArmo_BrunnerDead";
			}
			AddQuestRecord("ISS_MainLine", "24");
		break;

		case "NBB_1":
			dialog.text = "������� �� ������, "+ GetSexPhrase("�������","�������") +".";
			link.l1 = "��� ��� ���������?";
			link.l1.go = "NBB_2";
			npchar.quest.HillNBB_1 = true;
		break;
		case "NBB_2":
			dialog.text = "��� ����� ������� � ������ ������� �������. ������ ��� ����� �� �����, ��� ����� ������ �����? ��� ��� ��� ��� � �����...";
			link.l1 = "����-������ ������? ������ �����?";
			link.l1.go = "NB_3";
		break;
		//����� �� �������� ����
		case "ADied_1":
			dialog.text = "���� ���! ����� ���� �� �����, ��� ��� ���������. ��� ����� ����������� � ������� ����� �������, ���, ��� ����� �������. ����� �� �������� �� ����. � ���...";
			link.l1 = "� ��� ������?";
			link.l1.go = "ADied_2";
		break;
		case "ADied_2":
			dialog.text = "�������� ��� ����, � ��� ����� ��� � ������������ ������. ��� � ���, ��� ��� ��� ������-��?";
			link.l1 = "��� ��� ������ �� �������. � �� ������, ��� ���?.. ����, ���� �. ��� ���� �� '��������'.";
			link.l1.go = "ADied_3";
		break;
		case "ADied_3":
			dialog.text = "������, ��� ���-���� ����� ��-��� ��������. �-��... � �� ��� ��� �� �����?";
			link.l1 = "��-�� ���� ���. �� �����"+ GetSexPhrase("","�") +" � ������������� ������. ������, ������� ���� �� �����!";
			link.l1.go = "exit";
		break;
		//����� ������� �� ������
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("��� ������?", 
				"�� ��� ���������"+ GetSexPhrase("","�") +" �� ����.", 
				"��� ���������"+ GetSexPhrase("","�") +"...",
                "�� ��� ���������"+ GetSexPhrase("","�") +" ���� �� ���� �������. ������ � �� ����!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� ����� �����, ��������, ��������, �����, ������, ���������...", 
				"��... ������, �����������"+ GetSexPhrase("","") +".",
                "�-�, �� ��.", 
				"�����"+ GetSexPhrase("","�") +", �����"+ GetSexPhrase("","�") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "������, ������ �� ������.";
			link.l1 = "�����"+ GetSexPhrase("","�") +", �������.";
			link.l1.go = "exit";
		break;
		//���� �������
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("����� �������?", 
				"�� ��� �������� �� ����.", 
				"��� ��� ���������, ������ ��� ��������.",
                "������, ������"+ GetSexPhrase("","�") +"...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�� �������. � ����� �� ������.", 
				"��... ������, �����������"+ GetSexPhrase("","�") +".",
                "��� ������...", 
				"��, �����...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = "� ���, ���� �� ���?";
			link.l1 = "����. ����� � �� ���� �� ����"+ GetSexPhrase("","�") +".";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "�� ��... ������, �, �������, ��������. �������, ����� �� ��� ����� ����������, � ��������� �������.";
			link.l1 = "�� ������ ��������, ���������. �� ����� ���� ������� �����.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "��, �� �������...";
			link.l1 = "��... ��, ��� ������.";
			link.l1.go = "exit";
		break;

	}
	NextDiag.PrevNode = NodeName;
}
