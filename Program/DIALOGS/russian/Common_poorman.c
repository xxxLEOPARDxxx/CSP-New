#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // ����� ������� �� ������� -->
    /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Poorman\" + NPChar.City + "_Poorman.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
    // ����� ������� �� ������� <--

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (grandfathershit() == true)
                {
					dialog.text = RandPhraseSimple(RandPhraseSimple("��� �� �� �����, ��� ������� ���� ��� �� ���� �����... ���� ��� ��� ����������: ���� �����������, �� ����� ��������� ��������� �� ��������. ����������!","�-�-�, ���� � ����! �� ��� �� ������� ��� ������! � ��� ��� ������ ������, ��������, �� �� ������ ������!"), RandPhraseSimple("�����, ��� �������, ������ ������: ���� ������� ��������, ��� ������������� ��������? ���� ��������� �� ���� ��������� �� ������, ��� ��� ���������� ������ ������� �������... ��������� ������, ������!","�� ��, �� ��, ����� ��� ���������� ���������� ���������! ��, ���, ��� �� ����������...���! �� ����������, � ���������, ��-��-��! ����������, �����."));
            		link.l1 = LinkRandPhrase("��, �� ���� ������� ���� ��������. ���� ������ �����.","�� ���� �������? � ���� ����-���� ���� �������... �����-�����, �����.","���! � ��� �������� - ������ ���� ��� ������...");
            		link.l1.go = "exit";
					break;
                }
			if (grandfatherisashiteater() == true)
                {
					dialog.text = RandPhraseSimple(RandPhraseSimple("��� �� �� �����, ��� ������� ���� ��� �� ���� �����... ���� ��� ��� ����������: ���� �����������, �� ����� ��������� ��������� �� ��������. ����������!","�-�-�, ���� � ����! �� ��� �� ������� ��� ������! � ��� ��� ������ ������, ��������, �� �� ������ ������!"), RandPhraseSimple("�����, ��� �������, ������ ������: ���� ������� ��������, ��� ������������� ��������? ���� ��������� �� ���� ��������� �� ������, ��� ��� ���������� ������ ������� �������... ��������� ������, ������!","�� ��, �� ��, ����� ��� ���������� ���������� ���������! ��, ���, ��� �� ����������...���! �� ����������, � ���������, ��-��-��! ����������, �����."));
            		link.l1 = LinkRandPhrase("��, �� ���� ������� ���� ��������. ���� ������ �����.","�� ���� �������? � ���� ����-���� ���� �������... �����-�����, �����.","���! � ��� �������� - ������ ���� ��� ������...");
            		link.l1.go = "exit";
					break;
                }
			if (grandfatherhater() == true)
                {
					dialog.text = RandPhraseSimple(RandPhraseSimple("��� �� �� �����, ��� ������� ���� ��� �� ���� �����... ���� ��� ��� ����������: ���� �����������, �� ����� ��������� ��������� �� ��������. ����������!","�-�-�, ���� � ����! �� ��� �� ������� ��� ������! � ��� ��� ������ ������, ��������, �� �� ������ ������!"), RandPhraseSimple("�����, ��� �������, ������ ������: ���� ������� ��������, ��� ������������� ��������? ���� ��������� �� ���� ��������� �� ������, ��� ��� ���������� ������ ������� �������... ��������� ������, ������!","�� ��, �� ��, ����� ��� ���������� ���������� ���������! ��, ���, ��� �� ����������...���! �� ����������, � ���������, ��-��-��! ����������, �����."));
            		link.l1 = LinkRandPhrase("��, �� ���� ������� ���� ��������. ���� ������ �����.","�� ���� �������? � ���� ����-���� ���� �������... �����-�����, �����.","���! � ��� �������� - ������ ���� ��� ������...");
            		link.l1.go = "exit";
					break;
                }
			if (npchar.quest.meeting == "0")
			{
				//���� �� ����� ������ ������ -->
				if (pchar.questTemp.LSC == "PoorMurderBegin")
				{
					dialog.text = LinkRandPhrase("� ������, ��� �� ������ ����� � ������ �������. ����� �� ��� �������?", 
						"��� �������, � ����, ��� ��. ����� �� �������� ���?", 
						"��� ���� ����� �� ���? ��� �� ���� �������? ����� ������� ���������� �����?");
					link.l1 = LinkRandPhrase("��� ���� � �������...", "��� ��������� �� ��� ������ ��-�-���� ������� ��������������!", "������ �����... � ������, ��� ���� � �������, ���� ���.");
					link.l1.go = "exit";
					break;
				}
				//<-- ���� �� ����� ������ ������ 
				//������������ ����� -->
				if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
				{
					dialog.text = "�-��, �������� ��������� �� �� �����. � ��� ���� ��� �� �����.";
					link.l1 = "�������...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.MC == "toCaracasPadre" || pchar.questTemp.MC == "toCaracasTavern")
				{
					dialog.text = "�� ������ ����������� � ���� �����? ��, ��� ������... � ��� ��� �����.";
					link.l1 = "����� ������.";
					link.l1.go = "exit";
					break;
				}
				//<-- ������������ ����� 
				dialog.text = LinkRandPhrase("������������. ���� ����� " + GetFullName(npchar) + ". �� �����, ��� ��� ���� �� ������� �� ���� �������������, ��, ��������, �� ��������� ��� ���...", 
					"����������� ���, " + GetAddress_Form(NPChar) +  ". ���� ����� " + GetFullName(npchar) + ".", 
					"��� ��� - " + GetFullName(npchar) + ", " + GetAddress_Form(NPChar) + ". ��� � ���� �������������.");
				link.l1 = RandPhraseSimple("�����������.", "������������.");
				link.l1.go = "First time";
				npchar.quest.meeting = "1";
			}			
			else
			{
				//���� �� ����� ������ ������ -->
				if (pchar.questTemp.LSC == "PoorMurderBegin")
				{
					dialog.text = LinkRandPhrase("� ������, ��� �� "+ GetSexPhrase("������","�������") +" ����� � ������ �������. ����� �� ��� �������?", 
						"��� �������, � ����, ��� ��. ����� �� �������� ���?", 
						"��� ���� ����� �� ���? ��� �� ���� �������? ����� ������� ���������� �����?");
					link.l1 = LinkRandPhrase("��� ���� � �������...", "��� ��������� �� ��� ������ ��-�-���� ������� ��������������!", "������ �����... � ������, ��� ���� � �������, ���� ���.");
					link.l1.go = "exit";
					break;
				}
				//<-- ���� �� ����� ������ ������
				dialog.text = NPCStringReactionRepeat("��, ��� ������, �� ���� ���������...", 
					"���� ��������� ��������...", 
					"�������� �� ��� ��������� �� ������!",
					"����� ��?..", "block", 1, npchar, Dialog.CurrentNode);
				//����������� � ������ � ������
				if (pchar.questTemp.LSC == "SignOnPoorMurder" || pchar.questTemp.LSC == "PoorIsGood")
				{
					if (CheckAttribute(pchar, "questTemp.LSC.qtyTalk.headPoormanId") && pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id)
					{
						link.l1 = "� "+ GetSexPhrase("������","�������") +", ��� �� ����� ���������� �� ����.";
						link.l1.go = "PoorHeadMan"; 
						npchar.quest.talk = true; //������ �� ��������
						break;
					}
					if (!CheckAttribute(npchar, "quest.talk"))
					{
						if (!CheckAttribute(pchar, "questTemp.LSC.qtyTalk")) pchar.questTemp.LSC.qtyTalk = 0;
						pchar.questTemp.LSC.qtyTalk = sti(pchar.questTemp.LSC.qtyTalk) + 1; //��������� �� ������ �� �����
						if (sti(pchar.questTemp.LSC.qtyTalk) > 4) pchar.questTemp.LSC.qtyTalk = 4;
						switch (pchar.questTemp.LSC.qtyTalk)
						{
						case "1":
							link.l1 = "��������, ��� ����� ���������, ����� � ������� - ����� �����������, ��� ��?";
							npchar.quest.talk = true; //������ �� ��������
							break;
						case "2":
							link.l1 = "������, � ���� � ���� ���� �������� ��������� ����.";
							npchar.quest.talk = true; //������ �� ��������
							break;
						case "3":
							link.l1 = "������, � ���� � ���� ���� ���� ������. ����� ��������, �� ������ ������...";
							npchar.quest.talk = true; //������ �� ��������
							break;
						case "4":
							link.l1 = "���� ������ ���� ���� ������, ��������.";
							break;
						}
						link.l1.go = "GoodTalk_" + pchar.questTemp.LSC.qtyTalk;
						break;
					}
				}
				//----------------------------------------------------------------
				link.l1 = HeroStringReactionRepeat("����. ��, ������ ���������.", 
					"��� � �������. �� ��� ������ �� ������������, ����...",
					"����� ���� ����� �� ��������� ����� �����, � ���-�� ������ ��� �����.", 
					"���. ������� "+ GetSexPhrase("������","�������") +"?", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("��� ���� �����?", "���� �� ������?");
				link.l2.go = "Whants";
				link.l3 = LinkRandPhrase("���-������ ���������� ��� ����������?", 
					"��� ������ � ������?", "��, � ������������� "+ GetSexPhrase("��������","���������") +" �� ��������� �������...");
				link.l3.go = "rumours_poor";
				// --------------- ������� ��� ---------------
				//����� ������ � ������� �����������
				if (pchar.questTemp.LSC == "CanFoundStuvesantKey" && CheckCharacterItem(pchar, "letter_LSC") && pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id)
				{
					link.l1 = "��������, ��� �������, ��� � "+ GetSexPhrase("�����","�����") +" � ���������� ���������� ����� ������ ����������!";
					link.l1.go = "FoundLetter";
				}
				//����� � ���, ��� ����� ������� ������ �� �����
				if (pchar.questTemp.LSC == "readyGoLSC" && pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id)
				{
					link.l1 = "�� ������, ��� ������� ��������� ���� ������!";
					link.l1.go = "GoLSC";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("�� ���, ������ ����� "+ GetSexPhrase("������","�������") +"? � �� ����� �����, ��� �� "+ GetSexPhrase("���","����") +" ������...", 
				"�� "+ GetSexPhrase("������","�������") +", �� �������� "+ GetSexPhrase("������","�������") +". � ���� � �����, �� ���� �������.");
			link.l1 = "���, ����...";
			link.l1.go = "exit";
		break;
		//������
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//���������
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("��, " + GetAddress_Form(NPChar) +  ", � ��� ����� ��������� �����. �� � ���� � �����, ���� � �����, ��� ��. � ����� ���� ��� ����� �� ��� � �����, ���������.",
					"����� ���, " + GetAddress_Form(NPChar) +  "! �� �������� ��������� ����������� ��������, ������� �� ����������...");
				link.l1 = RandPhraseSimple("������ ���� �� ���.", "����������.");
				link.l1.go = "exit";
				Link.l2 = "������. � ������� ���� ����� �����?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("�� ����? ������.", "������ �� �����, " + GetAddress_Form(NPChar) + ", �������.");
				link.l1 = RandPhraseSimple("��, �� �����.", "����� ������ ������� ����, ��������.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "� �� ����� �������� �� ��������, " + GetAddress_Form(NPChar) + ". ������� ��� �������� ���� ������� � ����������...";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "������ �������� ���� �������� ������...";
				link.l1 = "��-��-��, � �� ��� �����, ��������, � ���� ����� ���?!";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "������� �� " + FindRussianMoneyString(iTemp) + ", " + GetAddress_Form(NPChar) + ". � ����� ����� �� ��� ������...";
				link.l1 = "�����, ��� ����������, �������.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 100 && iTemp <= 1000)
			{
				dialog.text = "������� ���, " + GetAddress_Form(NPChar) + ". ���� ����� ��� ������ �� ������!";
				link.l1 = ""+ GetSexPhrase("��� ���","���� ����") +" ������.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "��������� ���, " + GetAddress_Form(NPChar) + ". � ���� �������� � ����� �������!";
				link.l1 = "��, ��� �� �����������...";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, sti(iTemp/2000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 5000 && iTemp <= 50000)
			{
				dialog.text = "������� ���, ���������"+ GetSexPhrase("��","��") +" " + GetAddress_Form(NPChar) + ". �� ������ ��� �������...";
				link.l1 = "��, ��������������� ������� ��� �� �������� �� �����!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), sti(iTemp/10000+0.5));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 50000 && iTemp <= 100000)
			{
				dialog.text = "������� ���, "+ GetSexPhrase("�����������","�����������") +" " + GetAddress_Form(NPChar) + ". ����� ��� �����!";
				link.l1 = "�������, ��������.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", sti(iTemp/5000));
				AddCharacterExpToSkill(pchar, "Fortune", sti(iTemp/5000));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 100000)
			{
				dialog.text = "����������, " + GetAddress_Form(NPChar) + ", �� � ����� ���? �� ������� ��� " + FindRussianMoneyString(iTemp) + "! � �� ������ ����� ������, ��������, ����� �����-�� ������... �������!";
				link.l1 = "��, ��� ������...";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -2);
			}
		break;
		//������� ���, ��������� �� ����� � ������ ����� ������ 
		case "GoodTalk_1":
			dialog.text = "�-��, �-��... ����?!!";
			link.l1 = "��-�-�, ��� ���� �������... � �����, ���� ��� ����, ������� �� ��� ����� � �����.";
			link.l1.go = "GoodTalk_1_1";
		break;
		case "GoodTalk_1_1":
			dialog.text = "� ���� �� ����, ��� � �������... "+ GetSexPhrase("���","����") +", ��������, ���������, ��� �� ���� ���������, ��������� � ��� �����������������.";
			link.l1 = "���������, ����� ������ ����� ������?";
			link.l1.go = "GoodTalk_1_2";
		break;
		case "GoodTalk_1_2":
			dialog.text = "������?! ��-�-��, ��� ���� ��. ��������, ��� �� �������� ���� �� ������? ���� ��� ������.";
			link.l1 = "���, � ��������� ������, ��� ������. � �����, �� �� ������, ��� ����� ���� ���� �������������, � ��� �������.";
			link.l1.go = "GoodTalk_1_3";
		break;
		case "GoodTalk_1_3":
			dialog.text = "�� ����, �������! �� �� � ���� "+ GetSexPhrase("�������","��������") +".";
			link.l1 = ""+ GetSexPhrase("�������","��������") +" � ����� �������������, ��� �������. ���� ����������, ��� �� ���� �����... �� �����, ���� ���������, ����.";
			link.l1.go = "GoodTalk_1_4";
		break;
		case "GoodTalk_1_4":
			dialog.text = "�� ��� ������ ����������, ���� ������������ � ���� � ����� �������.";
			link.l1 = "�������. �� � ���� "+ GetSexPhrase("�����������","������������") +".";
			link.l1.go = "exit";
		break;

		case "GoodTalk_2":
			dialog.text = "��, �����, ������� ����.";
			link.l1 = "���������, ��� �� ����� �������� �����, ���� �� ����������� ���������, ��� ��� ������ ������ ��� �� �����?";
			link.l1.go = "GoodTalk_2_1";
		break;
		case "GoodTalk_2_1":
			dialog.text = "������ �� �����? � ���� ��� - ���?";
			link.l1 = "���� ����� �� �������� � ��������� ����.";
			link.l1.go = "GoodTalk_2_2";
		break;
		case "GoodTalk_2_2":
			dialog.text = "���� �� ����, ��� � �������... � ���, ����� �������� �����������?";
			link.l1 = "���. ���������, ��� ������ ����� ������.";
			link.l1.go = "GoodTalk_2_3";
		break;
		case "GoodTalk_2_3":
			dialog.text = "��-�-�, ��� ��� ��!.. ��, �� "+ GetSexPhrase("���","����") +", ��������, ���������, ��� ����� �� ��� ��� ���������� - ���� �� �����. ���� ��-�� ����� ���-�� ����� ��� �������, �� � ������ ������ �� ������� � ���� �����!";
			link.l1 = "��� � � ������, ��� ��� ��������� ������ ����� ���������.";
			link.l1.go = "GoodTalk_2_4";
		break;
		case "GoodTalk_2_4":
			dialog.text = "������, �� ��� ��� ���� ���������� ������. � � ������ �������������...";
			link.l1 = "�������. �� ��� ��, ������, ��� "+ GetSexPhrase("������","��������") +" �� ���.";
			link.l1.go = "GoodTalk_2_5";
		break;
		case "GoodTalk_2_5":
			dialog.text = "�� ������. � �� �� ������, ��� ��� �� ������ �����...";
			link.l1 = "��, ��� �� �����.";
			link.l1.go = "exit";
		break;

		case "GoodTalk_3":
			dialog.text = "������ ����, ���������.";
			link.l1 = "� ��� "+ GetSexPhrase("����������","�����������") +" � �������� ����������� ���������������... � �����, ���� � ���, ��� �� ������� ���� ����, ����� ����������� ����� ������.";
			link.l1.go = "GoodTalk_3_1";
		break;
		case "GoodTalk_3_1":
			dialog.text = "���, � ����, ��� ��!";
			link.l1 = "��, �� � ��� �?";
			link.l1.go = "GoodTalk_3_2";
		break;
		case "GoodTalk_3_2":
			dialog.text = "�� ��� ����� �������, ��� ��������, ��� ��� ��������� �, �����, ������ ����� ������. ����� ��� ����� ����� ������ �����.";
			link.l1 = "��, ��� � � ����. �� � ������ ������ ��� ������ '�����'. � � �� "+ GetSexPhrase("��������������","���������������") +" ��� ������������ ��� ��� �������� - ������� ������ ������������ �� ��� ������.";
			link.l1.go = "GoodTalk_3_3";
		break;
		case "GoodTalk_3_3":
			dialog.text = "��� �� �� �� ����, � ����� �� ��� ���� ����� ���������� ���� �� ���.";
			link.l1 = "� ��� ���?";
			link.l1.go = "GoodTalk_3_4";
		break;
		case "GoodTalk_3_4":
			pchar.questTemp.LSC.qtyTalk.headPoormanId = GetPoorHeadManId(npchar);
			sld = characterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId);
			dialog.text = "��� ����� " + GetFullName(sld) + ", �� ������������ � " + XI_ConvertString("Colony" + sld.city + "Dat") + ".";
			link.l1 = "�������. �� ��� ��, �������, ������ ��� ��� ������.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_PoorsMurder", "3");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("��","���"));
			AddQuestUserData("ISS_PoorsMurder", "sCity", XI_ConvertString("Colony" + sld.city + "Acc"));
			AddQuestUserData("ISS_PoorsMurder", "sName", GetFullName(sld));
		break;

		case "GoodTalk_4":
			dialog.text = "� ������ ����.";
			link.l1 = "��� �� �������, ��� ����� ���� ������������� � ������������ �����?";
			link.l1.go = "GoodTalk_4_1";
		break;
		case "GoodTalk_4_1":
			sld = characterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId);
			dialog.text = "� ���� ����, �� �������� �� ���� ������ �� ����. ���� ����� ���� � " + XI_ConvertString("Colony" + sld.city + "Acc") + ", ��� ������� ������ �� ����� �� ����� " + GetFullName(sld) + ". �� ����� � ����� ������������ �� ����� ������.";
			link.l1 = "�������. � ��� � ��������.";
			link.l1.go = "exit";
		break;
		//�������� �������
		case "PoorHeadMan":
			dialog.text = "���� �� ������� " + GetFullName(pchar) + ", �� ��� � ����.";
			link.l1 = "������ ��� ���� � �����.";
			link.l1.go = "PoorHeadMan_1";
		break;
		case "PoorHeadMan_1":
			dialog.text = "�� ��� ��, ��� ������. ��������� � ���� ������, �� ��������� ������ � �����, ������� �� ������� ��������. ������ ��������� ������, ��� ��� ������ ��� �������. ��� ���������?";
			link.l1 = "�� ��. ������� ������, ��� �� �������, � ������ ������.";
			link.l1.go = "PoorHeadMan_2";
		break;
		case "PoorHeadMan_2":
			dialog.text = "��, ��� ������������ ������... � ��� ����� ���� ��������, ��� ������� � ����� �� ����?";
			link.l1 = "������ �����.";
			link.l1.go = "PoorHeadMan_3";
		break;
		case "PoorHeadMan_3":
			dialog.text = "��� ��� ��� ���������... � �����, ���� � ���� ���� �����������.";
			link.l1 = "�������.";
			link.l1.go = "PoorHeadMan_4";
		break;
		case "PoorHeadMan_4":
			dialog.text = "���� ���� ������� � �����������, �� �������, �������, �� ����� ������, ����� ��������� �������� � ���, ��� ��������� � �����. � �����, � ��� ��� ���� ������� �� ���������, ������� ����� ������������ � ����������, �� �������. ����� ��� ����� ���.\n"+
				"��� ���, ������ �� ��� ����� ������, � �� ���������� ����� ������� ������� �� ����� �������-����������� ������ ����������. � ��� ��� �������� � ������ �������� �� � ��������� � ������, �� � �����������... � ����� ������� ��� �� �����������, � ������ � ��� ������ �� ��������.";
			link.l1 = "��, � ����� ��� ��������� ����� � ����� ����?";
			link.l1.go = "PoorHeadMan_5";
		break;
		case "PoorHeadMan_5":
			dialog.text = "������ ������. ������ �� ��������, ��� � ���� � �������, ���� �� ������, � �������� ���-��� � ����������. �� ���� ���� ��� �����, �� ��������� - ����� ������� ��������� ����� � ����� ���� �� ������!\n"+
				"�� �������� � ������ �������������� � ����������� ����-������� ���������, � ��� ����� ���� ������ - �����������.";
			link.l1 = "�� � ���?";
			link.l1.go = "PoorHeadMan_6";
		break;
		case "PoorHeadMan_6":
			dialog.text = "� ��, ��� ����� ��� ���� - ������ ����. �� �������, �� ����������� � ������? ������ ���������, ������ �� �������� ������������� ��� �������� ������ ����� ���� �� � �������� ��������. ����� ����� ����� ���� �������, ��� ��� ����� ���������\n"+
				"�� ������ �� ������ ������ ��� ����� ������ ����� � ��������� ��� ����� �������, ����������� � ����� ������� �� ������ ����. � ���������, ���� �� �����, ����� �� ����� ������ �����, ������� ��� � �� �������� ����� ��������.";
			link.l1 = "��, ������ ��� ��� ��������� ���������...";
			link.l1.go = "PoorHeadMan_7";
		break;
		case "PoorHeadMan_7":
			dialog.text = "��������, �� ��� ���, ��� � ���� � ���� ������������. ������ ������������� �����, ����� �� ������� � �����������, � �� ����. ��� ��� ���� �� ������ ���-�� ������ �� ���� ����, ��, ��� �������, ������ ����� � ���������� �����������.";
			link.l1 = "� ��� � ����"+ GetSexPhrase("��","��") +" ��� ������ �� ������ ������?";
			link.l1.go = "PoorHeadMan_8";
		break;
		case "PoorHeadMan_8":
			dialog.text = "������, "+ GetSexPhrase("���� ���","������") +", ������� ���������. ���, ��� � ���� ��� ���������, ������������� ��������. ��� �������, ��� �� ������������ ����� ������ ����� ���-�� ������� ����� �������, ������ ������� ��������� ���� �� �� �� ����.";
			link.l1 = "��, � ���� ��� �����. ���-�� ����� ���������, �������� ������ ������� � ����� ��������.";
			link.l1.go = "PoorHeadMan_9";
		break;
		case "PoorHeadMan_9":
			dialog.text = "��, � ������ ���, ��� �����. ������� �� ��, ��� "+ GetSexPhrase("��������","���������") +". ���� ������� ���-������ ������� �������� - ����� ��������� �� ���, ����� ������... � ������� �� ��, ��� �� "+ GetSexPhrase("��������","���������") +" ��� �����.";
			link.l1 = "�� �� �� ���. ���� ������� �� ����������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toVillemstadResidence";
			AddQuestRecord("ISS_PoorsMurder", "4");
			//��������� ����������, ����� �������� �������, ��� ������ ������
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1 = "locator";
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1.location = "Villemstad_TownhallRoom";
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1.locator_group = "box";
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1.locator = "private2";
			pchar.quest.LSC_enterStuvesantBox.function = "LSC_enterStuvesantBox";
		break;
		//����� � �������� ����� ���������� ������
		case "FoundLetter":
			dialog.text = "��, �����, ���������, ��� ��� � ����...";
			link.l1 = "��� ������, ������� � ��������"+ GetSexPhrase("","�") +" � ���������� ����������. ��� ��������� ����� ��� � ����������� ����-������� ���������. �� ���� ���� �������, ��� ������� ����������� ����� ������ ������ �������� ��������.";
			link.l1.go = "FoundLetter_1";
		break;
		case "FoundLetter_1":
			dialog.text = "���, ����...";
			link.l1 = "��� �����-�� ������ �����������. � �������� �������. � ��� ��� ������-�� �� �������� ���������. ��������-�� ���, ��������, � ��� ��� ����.";
			link.l1.go = "FoundLetter_2";
			TakeItemFromCharacter(pchar, "letter_LSC");
		break;
		case "FoundLetter_2":
			dialog.text = "��, ���� �� ����, ��� �������... �������, ��� ����������� ������ - ��� ���������� ������ ��������������, ����� ���������� ����� �����.";
			link.l1 = "����?";
			link.l1.go = "FoundLetter_3";
		break;
		case "FoundLetter_3":
			dialog.text = "��, �������, ��������� ���, ���� ������������ - �������� ������, ���������� �����. � ���� ��� �� ��������, �� �����, �� �����, �� ������� ������ �� ���-�� ������� � �������. ����������� ����� ����� � ������������� ��� ����������� ������� ��������������, �������� ��� ���� ������� �� �����.";
			link.l1 = "�������� ��������� �� ���� �������. ���, ��� ������ � � ��� ������� � ���.";
			link.l1.go = "FoundLetter_4";
		break;
		case "FoundLetter_4":
			dialog.text = "�������, ��� ���-�� � ������ ���� ������, �� �� ���������� �������������. ��� ���, �� ���� ������� ����� ����� � ��������������, ����� ��� ���������������� �������� ��������. ���-�� � � ��� ���� ����, �� ����� ��� ��������������...";
			link.l1 = "��, � ���� � ������ �������, ��� ���� ������ ����������! ��� �����: '����������, ��� ����� �� ������� ����� ��� ����� �������� �����...'";
			link.l1.go = "FoundLetter_5";
		break;
		case "FoundLetter_5":
			dialog.text = "��, �� ����...";
			link.l1 = "� � ���� ������ �����-�� �����? � ���� ��� ��������?";
			link.l1.go = "FoundLetter_6";
		break;
		case "FoundLetter_6":
			dialog.text = "��� � ������ ���� � ��������. �� ������� �� � ���� ��� - ������� ��������� ���������������. ��� ��� ���� �������� - �� ���� � �������, � �� ��� ���� ����� ��� ����... � �����, �� ���������, ��� ��� �� ���� ������� ��������� �������, ��� � �������� ������.";
			link.l1 = "��, � ����������� ����-������� �������� ��������, ��� �� ����� �� � ������... � ��� ������ ���� �����, ��������?";
			link.l1.go = "FoundLetter_7";
		break;
		case "FoundLetter_7":
			dialog.text = "������. �� ��� ��������� �� ������. ����� ��� �����.";
			link.l1 = "��, ��������, �������, ��� � ����������� � ���� �������� ��������. �� ������ ��� ��������, ����� ��...";
			link.l1.go = "FoundLetter_8";
		break;
		case "FoundLetter_8":
			dialog.text = "��-��, ������ ���. ����� ����, ��� �� ������� �� ����� ����������.";
			link.l1 = "���� �� �����, ��� ����� ���� ����� ���� �� �������...";
			link.l1.go = "FoundLetter_9";
		break;
		case "FoundLetter_9":
			dialog.text = "�� ��� ��, ����� ���� � ���� ����! ������� �� ������, "+ GetSexPhrase("�������","" + pchar.name + "") +".";
			link.l1 = "���� ������, ��������.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTalkStuvesant";
			pchar.questTemp.LSC.poorName = GetFullName(npchar));
			AddQuestRecord("ISS_PoorsMurder", "7");
			AddQuestUserData("ISS_PoorsMurder", "sName", pchar.questTemp.LSC.poorName);
			//������� ���������� �� ����� �����, ������ ��� �� ��������
			pchar.quest.ISS_Murder1.over = "yes";
			pchar.quest.ISS_Murder2.over = "yes";
			pchar.quest.ISS_Murder3.over = "yes";
			pchar.quest.ISS_Murder4.over = "yes";
			pchar.quest.ISS_Murder5.over = "yes";
			pchar.quest.ISS_Murder6.over = "yes";
			pchar.quest.ISS_Murder7.over = "yes";
			pchar.quest.ISS_Murder8.over = "yes";
			pchar.quest.ISS_Murder9.over = "yes";
			pchar.quest.ISS_Murder10.over = "yes";
			pchar.quest.ISS_Murder11.over = "yes";
			pchar.quest.ISS_Murder12.over = "yes";
			pchar.quest.ISS_Murder13.over = "yes";
			pchar.quest.ISS_Murder14.over = "yes";
			pchar.quest.ISS_Murder15.over = "yes";
			pchar.quest.ISS_Murder16.over = "yes";
			pchar.quest.ISS_Murder17.over = "yes";
		break;
		//����� � �������� ����� ������ ������� ������
		case "GoLSC":
			dialog.text = NPCStringReactionRepeat("�������! ��, ��������, � ��� ��� ����?", 
				"�� ��� �������� �� ��� ����.", 
				"��, ���������� ���...",
                "��������, ������ ����������� - ��� ��� ������.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������, �� "+ GetSexPhrase("�������� ����","��������� �����") +" � �������������, ������� "+ GetSexPhrase("��������","���������") +" � ����� ������ ������ �������. ��� ���� ������������� � ������ ���� � ��� �������.", 
				"��, �����.",
                "�����!", 
				"��, �� ����...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("GoLSC_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "GoLSC_1":
			dialog.text = "������, ����������!";
			link.l1 = "� ���� �� ���� ����� ��������. �� �����, ��� ������ ������, � ������� �� ��� ����� ����������� - �� �������. ��� ������, � � ������� ����������� ����!";
			link.l1.go = "GoLSC_2";
		break;
		case "GoLSC_2":
			dialog.text = "�������� �� ����!..";
			link.l1 = "���� � ����� ������ ������� - ����� ��� �����.";
			link.l1.go = "GoLSC_3";
		break;
		case "GoLSC_3":
			dialog.text = "�-�, ����! ����...";
			link.l1 = "� ���� ������� � �� �����"+ GetSexPhrase("","�") +" ������ ������, �� ��� ����� �������, ��� ��� ��� �� �������. ������������� ����.";
			link.l1.go = "GoLSC_4";
		break;
		case "GoLSC_4":
			dialog.text = "������, �� ����������� ����� ���� ������? ����� � ����� ���� ���� ������.";
			link.l1 = "��� �� ����?";
			link.l1.go = "GoLSC_5";
		break;
		case "GoLSC_5":
			dialog.text = "����� � �� ����. ����� ����� ��� ��� �� �������� �� ����, ��� ���������� �� �������. �������, ��� ���� ����������, � ��� ��� �������� - ������� �� ����.";
			link.l1 = "���������� ����! ���������...";
			link.l1.go = "GoLSC_6";
		break;
		case "GoLSC_6":
			dialog.text = "�� ��� ������ � ������ ������ ���� ���� ����, ��� ������� ����� ������. ��� ����� �������, ��� ���� ���� ������ ������ �������� ������ ���������� �������. ��� ��� �������� - ������� �� ����, �� � ������������� �������� �������.";
			link.l1 = "�������, �������. � ������.";
			link.l1.go = "exit";
			ChangeItemName("keyQuestLSC", "itmname_keyQuestLSC_Tizer");
			ChangeItemDescribe("keyQuestLSC", "itmdescr_keyQuestLSC_Tizer");
			sld = ItemsFromID("keyQuestLSC");
			DeleteAttribute(sld, "shown");
			GiveItem2Character(pchar, "keyQuestLSC");			
		break;
	}
}

string GetPoorHeadManId(ref NPChar)
{
    ref ch;
	int n;
    string storeArray[30];	locations[n].private9.key = "key3";
	locations[n].private9.items.jewelry1 = 30;
    int howStore = 0;
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_poorman.c" && NPChar.id != ch.id && !CheckAttribute(ch, "quest.talk"))
		{
            storeArray[howStore] = ch.id;
            howStore++;
		}
    }
    if (howStore == 0) return "none";
    else return storeArray[rand(howStore-1)];
}
