
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = "� �� ����� � ����� �������������! �� �����"+ GetSexPhrase("","�") +" �� �������!!";
				link.l1 = "��� ������..."
				link.l1.go = "exit";
				break;
			}
			//����� ������ ����� ��������
			if (pchar.questTemp.LSC == "barmenIsDead")
			{
				dialog.Text = "��, "+ GetSexPhrase("����� �������","�����������") +", �� ��� ������ � ����� ���������?";
				link.l4 = "� ����� ���������? ��� ���������?";
				link.l4.go = "NB_1";
				pchar.questTemp.LSC = "barmenIsDeadYouKnow";
				break;
			}
			if (pchar.questTemp.LSC == "barmenIsDeadYouKnow" || pchar.questTemp.LSC == "toArmo_BrunnerDead")
			{
				dialog.Text = "��, "+ GetSexPhrase("����� �������","�����������") +", ����� ������! ����� ����!!";
				link.l4 = "��, ����, � � �����. ���� �����, ����� ����...";
				link.l4.go = "NBB_1";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.Text = "��-��, � ���� ���! ���� ����� ������� ��� �������. ��� �, ������ ���� ������, � ������ ��� ���������� � �����! �� ��� ��������� �� ���� �������...";
					Link.l1 = "�� ��, �����"+ GetSexPhrase("","�") +" ��������...";
					link.l1.go = "FT_1";
				}
				else
				{				
					dialog.Text = "��-��, � ���� ���! ��� ��� ������� ������� ��� ���������. ��� �, ������ ���� ������, � ������ ��� ���������� � �����! �� ��� ��������� �� ���� �������...";
					Link.l1 = "�� ��, �����"+ GetSexPhrase("","�") +" ��������...";
					Link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = "��� �� ������, "+ GetSexPhrase("����� �������","�����������") +"?";
				Link.l1 = "���� ������ ���� ���� ��������, " + npchar.name + ".";
				Link.l1.go = "int_quests";
				link.l10 = "�� ���, ������, ����������...";
				link.l10.go = "exit";
				//������������ �� � ���, ���, ��������, �� ��������� ����� ����� �������
				if (pchar.questTemp.LSC == "toSeekMechanik" && !CheckAttribute(pchar, "questTemp.LSC.Armo"))
				{
					link.l4 = "��������, ����, � ���� ���� ��������� ����� �� ������ ������ �����.";
					link.l4.go = "AboutCasper_1";
				}
				//������� �� �������
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 0)
				{
					link.l4 = "����, ���� �����-������ ������� �� ������� ��������?";
					link.l4.go = "Casper1";
				}
				//���� �������
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 2 && CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = "����, ���� �������� ����, ��� ��� ������ �������� ������ �������...";
					link.l4.go = "WaitCasper1";
				}
				//������� �� �������
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 2 && !CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = "����, ���� �����-������ ������� �� ������� ��������?";
					link.l4.go = "Casper2";
				}
				//���� ��������
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 4 && CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = "����, ������ �����.";
					link.l4.go = "WaitCasper2";
				}
				//������� �� ��������
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 4 && !CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = "����, ���� �����-������ ������� �� �������� ��������?";
					link.l4.go = "Casper3";
				}
                //������� ��� ������� ���������� �������
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 11 && npchar.name == "Armo")
				{
					link.l4 = "����, ����� ��������, �� �, �������, ���-���� �������"+ GetSexPhrase("","�") +" � ��������.";
					link.l4.go = "CasperLate";
				}
                //������� ��� ������� ���������� �������
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 15 && npchar.name == "Armo")
				{
					link.l4 = "����, ��� ����� ���� ����������...";
					link.l4.go = "CasperAllFight"; 
				}
				if (pchar.questTemp.LSC == "seekMillionAndHalf" && npchar.name == "����" && !CheckAttribute(npchar, "quest.giveMoney"))
				{
					link.l4 = "������, ����, � ���� ��� �������� ����������...";
					link.l4.go = "askMoney";
				}
				//������������ ���� ���� ������
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toWaitress")
				{
					link.l5 = "��������, " + npchar.name + ", �� �� ������� ��� �����, ����� ������ ������ ������� � ���?";
					link.l5.go = "ELTHusb_SF";
				}
				//����� ������� �� ������
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = "��������, �� �� ������, ��� ����� ��������� ��������� ������.";
					link.l8.go = "SeekGoods";
				}
				//������ ������� �� ������
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = "������, ���� ��������� ��������. � ������� �������, ����� ���� ������ �� �������.";
					link.l8.go = "SeekCrew";
				}
			}
		break;
		case "FT_1":
			dialog.text = "�� ��� ��, ������� �����������. ���� ����� " + GetFullName(npchar) + ". � ���?";
			link.l1 = "��� ��� - " + GetFullName(pchar) + ". � �������... �-��, ����"+ GetSexPhrase("��","��") +" �������...";
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = "��� �� ������� ���� �������, ��� �������?! �����������, ��� ��� ������ ������� �� ������ ����� �����. ��, ��� ����� ����, ��������...";
			link.l1 = "�� ��� �������, ����������...";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "� ���� �������� ��� "+ GetSexPhrase("'����� ���������'","������ '�����������'") +"! �� �� ������?";
			link.l1 = "�� ������, " + npchar.name + ". ������� ��� ������...";
			link.l1.go = "exit";
		break;
		//�������
		case "int_quests":
			dialog.text = "���������, �������.";
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "����� ���-�� �������, �� �� ��������? ��� ������� ��� � ���...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "� �� ��� ���� ������?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "�� �� ������ ��������� ������?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "��������, � ��� �� ����� � ��� ��� ����������? � ���� � ���� '��������' � '��������'.";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = "������, � ���� ����� �� ���� ������ ���������������� � ������. ��� �� ��� ��������� �����-������ �����, ���-��...";
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l6") && CheckActiveQuest("LSC_findDekster"))
			{
				link.l6 = "��������, " + npchar.name + ", �� ���-������ ������ � ������� ��������?";
				link.l6.go = "ansewer_6";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l7") && CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "over" && npchar.name == "����")
			{
				link.l7 = "� ������"+ GetSexPhrase("","�") +", �� ������������ � ������� ������.";
				link.l7.go = "ansewer_7";
			}
			link.l10 = "�� ������, ���-�� � �����"+ GetSexPhrase("","�") +", � ��� �����"+ GetSexPhrase("","�") +" ��������. ������, ��� ������"+ GetSexPhrase("","��") +"...";
			link.l10.go = "exit";
		break;
		case "ansewer_3":
			dialog.text = "�������, ��... �� �� �� ����"+ GetSexPhrase("�","���") +", ��� �� ���������.";
			link.l1 = "��� ��, �� ��� ��... ���������� ���-��.";
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = "�� ������� �����, ��� ������ � ����, ��� ���� ��������. ��� ����������, ������� �� ������ ���������.";
			link.l1 = "���������?";
			link.l1.go = "ansewer_3_2";
		break;
		case "ansewer_3_2":
			dialog.text = "�� ��������� � ���������, ���������� ����� - � ��� ����� ������.";
			link.l1 = "�������... ������� �� ���������.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_1":
			dialog.text = "��� ��, ��� � ��� �����. ��� ������� �������, � ������ �������. ������ ������, � ��������, ��� ���� �� ���, ����� ���� ������ ���������. ��� �����-�� ������� ��������, ��� ��... � �����, �� ���� �, �� ����, ��� ���������, ������.";
			link.l1 = "����...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = "��-��, ��� ����� ��������� ������. ������ ��� ����������.";
			link.l1 = "�� �������?";
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = "��, � ���������. ������� �������� ������ ����, ������ ����� ��� �� ��������. � ������� ����� ������� ��������� �������.";
			link.l1 = "�������.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = "��... � ��� ����� ���� ����� ������� ����, �, �������, �� �� ��������� ��� �������. �� ������ � ���!!";
			link.l1 = "� � ��� ����?";
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = "���� � ���, ��� ��� ������ �����. ������ ���� ����� �� ��� � ����������, ��� �� ���������� ������ ����������������. ��� ����� ��������� ����� ������ ��� ��������� �� ������ ����.";
			link.l1 = "�������, ����.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_5":
			dialog.text = "�����? ���� ����� � ����� ������! ��� ������ ��������.";
			link.l1 = "� ��� ��������� �������?";
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = "�� ������� '����������', "+ GetSexPhrase("����� �������","�����������") +".";
			link.l1 = "�����"+ GetSexPhrase("","�") +". �������� ���� �������, " + npchar.name + ".";
			link.l1.go = "int_quests";
		break;
		case "ansewer_6":
			dialog.text = ""+ GetSexPhrase("����� �������","�����������") +", � ������ �� ���� � ������� ��������. � ����� �� �����.";
			link.l1 = "��, ��, ������...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_7":
			dialog.text = "��, ��� ���. � ����� �� �����������, "+ GetSexPhrase("����� �������","�����������") +"?";
			link.l1 = "�� ���, ������... ���"+ GetSexPhrase("","�") +" �� ���!";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l7 = true;
		break;
		//������ ��������
		case "NB_1":
			dialog.text = "����� �������� �����!!";
			link.l1 = "���?! �� ����� ����!..";
			link.l1.go = "NB_2";
		break;
		case "NB_2":
			dialog.text = "��-��, ������ ���! �������, � �� ��� ��� �� ���� ������ �� ����� �������.";
			link.l1 = "����, �������� ���, ��� ��� ���������.";
			link.l1.go = "NB_3";
		break;
		case "NBB_1":
			dialog.text = "��, ���� ���, � ����������� � ���� ������� �������! ����� �� ��� ������� �������!";
			link.l1 = "��, ��� �����... ����, �������� ���, ��� ��� ���������.";
			link.l1.go = "NB_3";
		break;
		case "NB_3":
			dialog.text = "��, ���� �����-��! �� ���� ���������� �� ���� ��� ����������...";
			link.l1 = "����, � ����� ����, �������� � �������� ���, ��� ��� ����.";
			link.l1.go = "NB_4";
		break;
		case "NB_4":
			dialog.text = "������... � �������� ���� �������� � ������. ����� �� ������ ��� ������ ���� �����, � ����� ���� �� ���������� ���, ��� ��� �������� ����� ��� �����������. � ����� ��� ���...";
			link.l1 = "�� ����� ��� �����?";
			link.l1.go = "NB_5";
		break;
		case "NB_5":
			dialog.text = "��, � ���� ��� �������� �����. ��, � �� ���� ��� ���������� ��� ����...";
			link.l1 = "������, � �� ������ �� ������ �����? ��������� �� �������, ��������...";
			link.l1.go = "NB_6";
		break;
		case "NB_6":
			dialog.text = "���, ������.";
			link.l1 = "������ ������! ���������� ���������... ������, �����, �� ���-������ ���� ������� ����� �������? ��, ������� ������ �����-������...";
			link.l1.go = "NB_7";
		break;
		case "NB_7":
			dialog.text = "��, �� ����, ���������� �� ��� ���, �� �� ������� ����, �� ���� �� � ����-������ �� �������, ��� ��� ����� �� ����.";
			link.l1 = "� ��� �� ��������?";
			link.l1.go = "NB_8";
		break;
		case "NB_8":
			dialog.text = "��������, ��� �� ����. � ����� �� �������, �� ������� �� � � ���������� ����������� � �����-�� ��������...";
			link.l1 = "� ��� �� ��������?";
			link.l1.go = "NB_9";
		break;
		case "NB_9":
			dialog.text = "��� �� �������.";
			link.l1 = "��� ������������� ���?";
			link.l1.go = "NB_10";
		break;
		case "NB_10":
			dialog.text = "�� �������! � ���� �� ��� ��� ����� ������ ����?!";
			link.l1 = "��, �������������... �� ��� ��, ������� ����, ����.";
			link.l1.go = "NB_11";
		break;
		case "NB_11":
			dialog.text = "�� ���?";
			link.l1 = "�� ��, ��� �� ����� ������� �������.";
			link.l1.go = "NB_12";
		break;
		case "NB_12":
			dialog.text = "��... �� ������, "+ GetSexPhrase("����� �������","�����������") +", ��� ������ �� �� �����.";
			link.l1 = "� � � �� ����... �����, ����, �� ��������. ����� ����� ����� - ���� �������...";
			link.l1.go = "NB_13";
		break;
		case "NB_13":
			dialog.text = "������, ���� ����� �������!.. "+ GetSexPhrase("����� �������","�����������") +", �������� ���, ��� ���� �� ���-������ ������� �� ���� ����, �� �������� ���.";
			link.l1 = "������, ����.";
			link.l1.go = "NB_14";
		break;
		case "NB_14":
			dialog.text = "�������. � �� ����� ������ �����, ��� ��� ������. ��� ������� �� ����� ����� ����!";
			link.l1 = "��-��, � � ����� ������"+ GetSexPhrase("��","��") +"...";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toAdmiralBarmenDead";
			npchar.quest.meeting = "1";
			if (CheckAttribute(pchar, "questTemp.LSC.knowMechanic"))
			{
				AddQuestRecord("ISS_MainLine", "26");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","�"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("��","�"));
				DeleteAttribute(pchar, "questTemp.LSC.knowMechanic");
			}
			else
			{
				AddQuestRecord("ISS_MainLine", "25");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("��","���"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("��","��"));
			}
		break;

		case "AboutCasper_1":
			dialog.text = "��������, "+ GetSexPhrase("����� �������","�����������") +".";
			link.l1 = "������, ��� �� ���� ����� ���� '������'.";
			link.l1.go = "AboutCasper_2";
		break;
		case "AboutCasper_2":
			dialog.text = "�� �������?";
			link.l1 = "��, ������"+ GetSexPhrase("","�") +". � ���"+ GetSexPhrase("��","��") +" � ��������, �������"+ GetSexPhrase("","�") +" ��� ������� ������������ ������������� �������� �����, �����"+ GetSexPhrase("","�") +" ������. � �����, ��� ���� �������, ����� � �� ���"+ GetSexPhrase("","��") +" � ��� ����. ����� � ����������.";
			link.l1.go = "AboutCasper_3";
		break;
		case "AboutCasper_3":
			dialog.text = "� ��� ��� ��� '�������'?";
			link.l1 = "��� ���������, ��� ����� ������� � ���������. ����� �����... � ������ ������� ������ �� ����������.";
			link.l1.go = "AboutCasper_4";
		break;
		case "AboutCasper_4":
			dialog.text = "����... � ���� ��������� �� �����.";
			link.l1 = "� ��������� �������� � ������ '������' � ������.";
			link.l1.go = "AboutCasper_5";
		break;
		case "AboutCasper_5":
			dialog.text = "�� ����������� ������ ��� ��"+ GetSexPhrase("��","��") +"?";
			link.l1 = "�� ��. ������� �� ���� ��� �������� ��� �� �����.";
			link.l1.go = "AboutCasper_6";
		break;
		case "AboutCasper_6":
			dialog.text = "��� ��� �����. � ���� ��� ������� ��������, "+ GetSexPhrase("����� �������","�����������") +".";
			link.l1 = "��, ��� �� ��� ���������...";
			link.l1.go = "AboutCasper_7";
		break;
		case "AboutCasper_7":
			dialog.text = "��� ���, � ����, ��� ����� ��� ������. ���� � ���, ��� � ���� �� '��� ��������' ��� ��� ���� ���������. ���� ����������� ��� - ���� ��������. � ���� ��������� �� ��������, � �� ������ ����������� � ���� ���� �� ����.";
			link.l1 = "��! ������� ���������...";
			link.l1.go = "AboutCasper_8";
		break;
		case "AboutCasper_8":
			dialog.text = "��� ��� ����� ������ ��������� ��� �������?";
			link.l1 = "��, �� ����. ���, ����������, ��� �����, ��� ����������� � "+ GetSexPhrase("��������","������") +"...";
			link.l1.go = "AboutCasper_9";
		break;
		case "AboutCasper_9":
			dialog.text = "��-��, ������ �������... ��������� ���� ������, � ����� ���, �� ����� ����� ��������� ��������.";
			link.l1 = "������, ����. ������� ����.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "33");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","��"));
			pchar.questTemp.LSC.Armo = 0; //���� �� �������� ��������. ������ - ���������� ����, �������� - ���� questAction 
			SaveCurrentQuestDateParam("questTemp.LSC"); //�������� ���� ������
		break;
		//������ ������
		case "Casper1":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = "�������, � ������� '������' �� ����� ����� ������ ����� ���������� ����� ������������ �� ����������� ������ '����� �����'. ����� ��������, "+ GetSexPhrase("����� �������","�����������") +", ���� �� �������� �� ������� ������� ������ � '��� ��������', �� ����� ����� ����� �������� ��������� �������, � ����� ��� �����.";
				link.l1 = "� �����"+ GetSexPhrase("","�") +", ����.";
				link.l1.go = "Casper1_1";
			}
			else
			{
				dialog.text = "���� ���, �����.";
				link.l1 = "�����"+ GetSexPhrase("","�") +".";
				link.l1.go = "exit";
			}
		break;
		case "Casper1_1":
			dialog.text = "����� ��� �� ���������� �� ��������, ��� ����� ���������� � ����� �������...";
			link.l1 = ""+ GetSexPhrase("��-��, ��� �����. � ������� ���� �� ����� ��� ����!","��, ��������� ������� �� ����������. ���� �������, �� ����������.") +"";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 1; //����� �������� questAction �� �������
			AddQuestRecord("ISS_MainLine", "34");
		break;

		case "WaitCasper1":
			dialog.text = "�������, "+ GetSexPhrase("����� �������","�����������") +". ��, ���������?";
			link.l1 = "�������, ����!";
			link.l1.go = "WaitCasper1_1";
		break;
		case "WaitCasper1_1":
			dialog.text = "����� ��������� ������, ��������, � ����� �������� ��� ����-������.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +" ����.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Armo.waiting");
			DeleteAttribute(pchar, "questTemp.LSC.Armo.Interrapt");
			SaveCurrentQuestDateParam("questTemp.LSC"); //�������� ���� ������
		break;
		//������ ������
		case "Casper2":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = "��, ����. �� ��� �� �����, � ��� �� ���, � ��������� �������� '�������' �� ����� ���� ������. ���� ��� ���, ����� �� ���� ���������...";
				link.l1 = "��, ������� ��� �������� ��������� ����.";
				link.l1.go = "Casper2_1";
			}
			else
			{
				dialog.text = "���� ���, "+ GetSexPhrase("����� �������","�����������") +". ��������.";
				link.l1 = "����.";
				link.l1.go = "exit";
			}
		break;
		case "Casper2_1":
			dialog.text = "������, ��� ������. ����, "+ GetSexPhrase("����� �������","�����������") +", �� ����������� �� ���������� ������ '����� �����'. �����, ��� �� ����� �������������� �����.";
			link.l1 = "�� � ���� ����, ����.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 3; //����� �������� questAction �� �������
			AddQuestRecord("ISS_MainLine", "37");
		break;

		case "WaitCasper2":
			dialog.text = "����� ������, "+ GetSexPhrase("����� �������","�����������") +". ��� ��������� ���������� ��� ����?";
			link.l1 = "���� �����, ����.";
			link.l1.go = "WaitCasper2_1";
		break;
		case "WaitCasper2_1":
			dialog.text = "�����. ��������� ������, �������, � ����� ����������� ��� � ���-������.";
			link.l1 = "������, ����. ������� ����.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Armo.waiting");
			DeleteAttribute(pchar, "questTemp.LSC.Armo.Interrapt");
			SaveCurrentQuestDateParam("questTemp.LSC"); //�������� ���� ������
		break;
		//������ ������
		case "Casper3":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = "��, �������. ��� ��, ��� � �����, � �� �� �����, ���� ����� ��������� ������ �����. ��������, ����� ���� �� �������.";
				link.l1 = "��, �������� � ��...";
				link.l1.go = "Casper3_1";
			}
			else
			{
				dialog.text = "���� ���, "+ GetSexPhrase("����� �������","�����������") +". ��������.";
				link.l1 = "����.";
				link.l1.go = "exit";
			}
		break;
		case "Casper3_1":
			dialog.text = "���������! ��� �, "+ GetSexPhrase("����� �������","�����������") +", ����� ���.";
			link.l1 = "�������, ��� ��� �����������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 5; //����� �������� questAction �� �������
			AddQuestRecord("ISS_MainLine", "38");
		break;
		//���������� ���� ������ ����
		case "CasperLate":
			dialog.text = "������, ���, "+ GetSexPhrase("����� �������","�����������") +", � �� ��� ���� ������ ����� ������, ����� �� ��� ������������� ���������� � ����� ���������. � �� �������� ����� �������� ���. ��������.";
			link.l1 = "��, ����...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 12; //�������� �����
			AddQuestRecord("ISS_MainLine", "35");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","�"));
		break;
		case "CasperAllFight":
			dialog.text = "��, � ����. �� ��� ����� ���� ���� �����, ��������, �������� ��� ����� �������. �������, ��� �� ����������. � ���� �� ���, "+ GetSexPhrase("����� �������","�����������") +".";
			link.l1 = "�������, ����.";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 16; //����� ������� ������ �� ����
		break;
		//���� ������
		case "ArmoIsDead":
			dialog.text = "������������. � ��� ����, �� "+ GetSexPhrase("��� ����� ����� ���������, � �������","�� ����� ����� ���������, � �������") +" ���� ���� ����� ������.";
			link.l1 = "��, ��� ���.";
			link.l1.go = "ArmoIsDead_1";
		break;
		case "ArmoIsDead_1":
			dialog.text = "����� ����, ��� ���� �������. ����� �� �����, ��� �� ����. � ������� ������ �������� �� ���� �������. ���, ��� �����, ������ �� ���� � ���� ������. ����� �� �� ���� �������� �����, ��� ������ � ������������ ������ � ���� ����������� �����...";
			link.l1 = "���� ������� ��-�� ����, ��� �����!";
			link.l1.go = "ArmoIsDead_2";
		break;
		case "ArmoIsDead_2":
			dialog.text = "��, ������� ���� �� ��������, ��� ���������... ������, � ������ �� ����, � ���� ������� ��� ��� ��, ��� ��� - "+ GetSexPhrase("����� �������","�����������") +". �� �� ������?";
			link.l1 = "�������, ���.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		//���� ���� ����, �� ���� �����
		case "askMoney":
			dialog.text = "��� ����� ������, "+ GetSexPhrase("����� �������","�����������") +"? � �����?";
			link.l1 = "�� ���� ����� ������ ��� ����� ������ ����. ������ ����� � ������!";
			link.l1.go = "askMoney_1";
		break;
		case "askMoney_1":
			dialog.text = "� ���� ���, "+ GetSexPhrase("����� �������","�����������") +". � ���� ��� ������ ��� ����������, ��� �����, ��� ��� ��� �� � ����.";
			link.l1 = "�� ���� ����� �������, ����.";
			link.l1.go = "askMoney_2";
		break;
		case "askMoney_2":
			dialog.text = "��� ����� - ��� ���, ��� � ���� ����������.";
			link.l1 = "�������!";
			link.l1.go = "askMoney_3";
		break;
		case "askMoney_3":
			dialog.text = "����� ������. � ����� ��� �����.";
			link.l1 = "�������, ����!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			npchar.quest.giveMoney = true;
		break;
		//����� ������� �� ������
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("� ����� ������� ���� ����, "+ GetSexPhrase("����� �������","�����������") +"?", 
				"�� ��� ���������� �� ����.", 
				"��� ����������...",
                "�� ��� ���������� ���� �� ���� �������. ����� ������?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� ����� �����, ��������, ��������, �����, ������, ���������...", 
				"��... ������, �����������"+ GetSexPhrase("","�") +".",
                "�-�, �� ��.", 
				"�����"+ GetSexPhrase("","�") +", �����"+ GetSexPhrase("","�") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "����� � ������ ����� �������� � ������ � ��������. ���� �� � ���� �� �������, �� ��� ���� ������, ����� ������, ��� ����� � ����� ������. �� ��������� ������� �� ����.";
			link.l1 = "����... ������� ����.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "48");
			AddQuestUserData("ISS_MainLine", "sName", GetFullName(npchar));
		break;
		//���� �������
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat("� ���?", 
				"�� ��� ���������� �� ����.", 
				"��� ��� ���������, ������ ��� ��������.",
                "������, �������...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("� ���� ���������� ���� ����� �� ��� � �������.", 
				"��... ������, �����������"+ GetSexPhrase("","�") +".",
                "��� ������...", 
				"��, �����...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			if (npchar.name == "����")
			{
				dialog.text = "���, "+ GetSexPhrase("����� �������","�����������") +". �� � ������� �������� � ������.";
				link.l1 = "�� ��� ��� ��� ���� �����?! ��������� �����, �� �������� ������.";
				link.l1.go = "SeekCrew_2";
			}
			else
			{
				dialog.text = "���, "+ GetSexPhrase("����� �������","�����������") +". � �������� �����, � ����� �������.";
				link.l1 = "��������� �����, �� �������� ������.";
				link.l1.go = "SeekCrew_2";
			}
		break;
		case "SeekCrew_2":
			dialog.text = "������?";
			link.l1 = "������������� ����� ������ ����� �������� �����.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "������� ��� ���� ������� ����, ��������� � ��� ����.";
			link.l1 = "���... ��, �����, ��� ������.";
			link.l1.go = "exit";
		break;
		//������������ ���� ���� ������
		case "ELTHusb_SF":
			dialog.text = "�����, "+ GetSexPhrase("����� �������","�����������") +".";
			link.l1 = "�������� ����������, ��� ��� ����.";
			link.l1.go = "ELTHusb_SF_1";
		break;
		case "ELTHusb_SF_1":
			dialog.text = "��, ������������-�� ����� � ������. ������ �������� � ��� ���� ��� � ���� '�� ������'. �������, ��� ������.";
			link.l1 = "�������... ���� ����?";
			link.l1.go = "ELTHusb_SF_2";
		break;
		case "ELTHusb_SF_2":
			dialog.text = "� ����� ���� ��� �����.";
			link.l1 = "�������. ����������, ��� ���� ���� �������� ��� �����?";
			link.l1.go = "ELTHusb_SF_3";
		break;
		case "ELTHusb_SF_3":
			dialog.text = "�� ��.";
			link.l1 = "���! ������� ����, ��������.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "8");
			pchar.questTemp.LSC.ElisHusband = "toZhilBaru";
		break;

	}
	NextDiag.PrevNode = NodeName;
}
 
