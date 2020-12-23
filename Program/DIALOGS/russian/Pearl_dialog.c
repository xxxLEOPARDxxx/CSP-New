
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "�� � ��� ��������!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// ==> ����� ���������
		case "HeadMan":
			NextDiag.TempNode = "HeadMan";
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "����� ���������� � ��� �� ��������. ��� ������ �������"+ GetSexPhrase("���","��") +" " + NationNameGenitive(sti(npchar.nation)) + ". ���� � ������ ���� ���?"; 
				link.l1 = "���� ����� " + GetFullName(pchar) + ". � ������� ������������ �����.";
				link.l1.go = "HeadMan_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("��� ��� ������ ����� � ���� � ����. �� �� ����?", 
					"����� ��? �� ��� ��� �����������, �������.", 
					"�������, ��� ��� ���-������ �����?",
					"�������, � ����� ��� �� ��������� ����!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("���, " + GetAddress_FormToNPC(NPChar) + ", ������ ��� ��������"+ GetSexPhrase("","�") +"...", 
					"��, �������.",
					"���, " + GetAddress_Form(NPChar) + ", ��������...", 
					"������...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";			
			}
			//-------- ��������� ��������� ����� ------------
			if (pchar.questTemp.Sharp != "begin" && pchar.questTemp.Sharp != "over" && pchar.questTemp.Sharp.SeekSpy == "begin")
			{
				link.l2 = "�������, � ����� �������, ��� ���������� � ��������� ����, � ����� ���������� ���������?";
				link.l2.go = "SharpSeekSpy";
			}
			if (pchar.questTemp.Sharp.SeekSpy == "alwaysKnow")
			{
				link.l2 = "� ������"+ GetSexPhrase("","�") +" �� ��������, ������.";
				link.l2.go = "SharpSeekSpy_10";
			}
		break;
		// <------- ��������� ��������� �����
		case "SharpSeekSpy":
			dialog.text = "� �����. � ������ �� �����������?";
			link.l1 = "������ ��, ��������, ����� ������ ������� ���������. ����� �������� �������� ����� ������� ����...";
			link.l1.go = "SharpSeekSpy_1";
		break;
		case "SharpSeekSpy_1":
			dialog.text = "�� �������� � ����� ������ �������, "+ GetSexPhrase("���� ���","�������") +". ��� ��������� ��� ��� ���!\n����� ��������, ��� ��� ������ ������ ������, ������ �� ������ ��������� ��������! � ������ �� ���-��, ������, ��� ��� �������� �����.";
			link.l1 = "��, ����� �� ����� � ������, ��� ����...";
			link.l1.go = "SharpSeekSpy_2";
		break;
		case "SharpSeekSpy_2":
			dialog.text = "�� ��������� ��� ���� ����������������, �� ����������. ���� �� �����, ���-�� ��� ����������� � ����� ������.\n����������, �� ��������� ������ ���� ��������. ��� ���-�� �������� �� ���� ����.";
			link.l1 = "������ ��, ��� � ��� ������"+ GetSexPhrase("","�") +". � ��������� ���� ���� �������� ������� ����...";
			link.l1.go = "SharpSeekSpy_3";
		break;
		case "SharpSeekSpy_3":
			dialog.text = "����. �� ��� ��, ���� ���������� ��� ������, ��� �� � ����� ����� ���������.";
			link.l1 = "� ��� �� ������? ��������� �����?";
			link.l1.go = "SharpSeekSpy_4";
		break;
		case "SharpSeekSpy_4":
			dialog.text = "���, ��� ������� ������. � ���� �� ������������. ���� ��� ��������, ��� ������� ���������� � ����� ����� �����, ������ ������ ���� ������� '�����', � ���� ������� ����� ����� �������.";
			link.l1 = "�������.";
			link.l1.go = "SharpSeekSpy_5";
		break;
		case "SharpSeekSpy_5":
			dialog.text = "� ����, ����� �� ����� ��� ����� ����� ���.";
			link.l1 = "�������. ������ ������� �������...";
			link.l1.go = "SharpSeekSpy_6";
		break;
		case "SharpSeekSpy_6":
			dialog.text = "��, �� ������� �������. ����, � ��� �� ���������� ��� ������ � ������, �� � �������� �����, �� ��� ������, ����� ���������� ��� ���.\n��� �������� ����������. � ���� ������ ���������� ��������, ��������� ������, ���������� ����� � ���������� ������! �������� ���, ���� ������ �������� �����!";
			link.l1 = "���, ��� ��� ���������...";
			link.l1.go = "SharpSeekSpy_7";
		break;
		case "SharpSeekSpy_7":
			dialog.text = "� ��������� � ����� ��������� ����, ��� � ��� ��� ����� ������, �������\n��, ������������!";
			link.l1 = "������"+ GetSexPhrase("��","��") +", ���� ���� ����! ��� �� � �� ��������"+ GetSexPhrase("��","���") +"!";
			link.l1.go = "SharpSeekSpy_8";
			link.l2 = "���, �������, � ��������.";
			link.l2.go = "SharpSeekSpy_8over";
		break;

		case "SharpSeekSpy_8":
			dialog.text = "����� � ��� �� ��� ������� ������, �������! ���������� � �������� ��������� ������� �� ������� � ������ �� ������� ���� ��������� ������ �������, ��� ����� � ����� ������ ��������.";
			link.l1 = "� �����"+ GetSexPhrase("","�") +". ��������� � ������� ����������.";
			link.l1.go = "SharpSeekSpy_9";
		break;
		case "SharpSeekSpy_9":
			GiveItem2Character(pchar, "indian11");
			pchar.questTemp.Sharp.SeekSpy = "seekSpy";
            SetQuestHeader("SharpPearl_SeekSpy");
            AddQuestRecord("SharpPearl_SeekSpy", "1");
			AddQuestUserData("SharpPearl_SeekSpy", "sSex", GetSexPhrase("","�"));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "SharpSeekSpy_8over":
			dialog.text = "�������. �� ��������� �� ���, �������� ���� � �����, � ����� ������������� �� ������. ��� ��� �������������\n�����, � �� ���� ���� ��� ���� "+ GetSexPhrase("�����","�����") +" ������.";
			link.l1 = "���?!..";
			link.l1.go = "SharpSeekSpy_8fight";
		break;
		case "SharpSeekSpy_8fight":
			pchar.questTemp.Sharp.SeekSpy = "over";
			LAi_group_Attack(npchar, pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "SharpSeekSpy_10":
			dialog.text = "��-�-��, ��� ��������, ��� ��. ��, �������������, ��� �� ������ ���������.";
			link.l1 = "� ���"+ GetSexPhrase("��","��") +" �������� �� �����, ��� ������ ����� ���������� � ����� ��������. ��� ������ ������.";
			link.l1.go = "SharpSeekSpy_11";
		break;
		case "SharpSeekSpy_11":
			dialog.text = "�� ������ ��� ��������?";
			link.l1 = "��. ��� ������� ��������� ��� � ���������� � ������ ������ ���-���� ���� ����� ��� ��� � ������ ��������� � ���������� ����� �����. � ����"+ GetSexPhrase("","�") +" �� �����.";
			link.l1.go = "SharpSeekSpy_12";
		break;
		case "SharpSeekSpy_12":
			dialog.text = "�������... �� ��� ��, � ���� ���. ���� ������� �� ����������� ������ - �������� ������ ��������. �����?";
			link.l1 = "����� ���, ������.";
			link.l1.go = "SharpSeekSpy_13";
		break;
		case "SharpSeekSpy_13":
			dialog.text = "����� �������� ��������. ��� ��� ������ ����.";
			link.l1 = "����� ���"+ GetSexPhrase("","�") +", ��� ����"+ GetSexPhrase("","��") +" ��������� ��� "+ GetSexPhrase("�������","�������") +". ��������, ������.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "blade22");
			GiveItem2Character(pchar, "pistol5");
			GiveItem2Character(pchar, "cirass4");
			GiveItem2Character(pchar, "topor2");
			pchar.questTemp.Sharp.SeekSpy = "over";
            AddQuestRecord("SharpPearl_SeekSpy", "5");
			AddQuestUserData("SharpPearl_SeekSpy", "sSex", GetSexPhrase("","�"));
			CloseQuestHeader("SharpPearl_SeekSpy");

			//zagolski. ����� � �����
			pchar.quest.sharp_pre.win_condition.l1 = "location";
			pchar.quest.sharp_pre.win_condition.l1.location = "Shore9";
			pchar.quest.sharp_pre.function = "sharp_pre";	

		break;
		// >------- ��������� ��������� �����
		case "HeadMan_1":
			dialog.text = "���� � ������, ��� �� ������� � ���� �����?";
			link.l1 = "�������� ����������, ��������, � ������� ��� ������ ��� ����������.";
			link.l1.go = "HeadMan_2";
		break;
		case "HeadMan_2":
			dialog.text = "������, �� "+ GetSexPhrase("�������������","�����������������") +". ��� ��, �����������. ���� ������ ��� � ���� ���� ������������ ������������� � ��� ��������� �����.";
			link.l1 = "������ �����������.";
			link.l1.go = "HeadMan_3";
		break;
		case "HeadMan_3":
			dialog.text = "��������� �������� � ������ ������ ����������� " + NationNameGenitive(sti(npchar.nation)) + ", ������� ����� �� ����� ����� �������� ��� ��������� ������.";
			link.l1 = "�������.";
			link.l1.go = "HeadMan_4";
		break;
		case "HeadMan_4":
			dialog.text = "���� �� ����������� ���������� � ��� ������� - ���� ��������� ��� ���������������.";
			link.l1 = "��� ���� �������.";
			link.l1.go = "HeadMan_5";
		break;
		case "HeadMan_5":
			dialog.text = "�� ��� ��, �����������. ������� ��� ��������� � ��������� ������������ � ���, " + GetAddress_Form(NPChar) + ".";
			link.l1 = "��������� ���.";
			link.l1.go = "exit";
		break;
		// ==> ������� � ���������
		case "GuardMan":
			NextDiag.TempNode = "GuardMan";
			dialog.text = NPCStringReactionRepeat("������������! ��������� �������������, ���� ����� " + GetFullName(npchar) + ". ��� ������ - ������������ ��������� ������ ������� � ��������� ���������. ������, ������ ��... � �� ���?", 
				"����������� ��� ���!", 
				"���� ��� ���� ������ �����, ������, ���������� �� � ���...",
                "��, ���� ������, �������� �������� � ������!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("���� ����� " + GetFullName(pchar) + ". � �������, ���������� ��� �����.", 
				"� � ���� ����...",
                "�������.", 
				"���...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("GuardMan_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;

		case "GuardMan_1":
			dialog.text = "���� �� � ���� ���������, �� ����� ����������.";
			link.l1 = "�������, ��������.";
			link.l1.go = "GuardMan_2";
		break;
		case "GuardMan_2":
			chrDisableReloadToLocation = false;
			npchar.quest.TalkOk = true; //���� �������� ���������, ��� ��.
			LAi_SetCitizenTypeNoGroup(npchar);
			DialogExit();
		break;

		case "GuardManAllarm":
			dialog.text = "�������!! ��� �����!!!";
			link.l1 = "������! ���� ���� ���� ����������...";
			link.l1.go = "GuardManAllarm_1";
		break;
		case "GuardManAllarm_1":
			chrDisableReloadToLocation = false;
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			DialogExit();
		break;
		// ==> ����� � ���������
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat("�����������! ���� ����� " + GetFullName(npchar) + ". ��� � ���� ���� ������?", 
				"����������� ��� ���!", 
				"� ����� ����� ����� ����� �����...",
                "��, ������� ��������� � ����� ���������! � �� ��� ����� ��� ����������.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�� ����� ���������...", 
				"� � ���� ����...",
                "�������.", 
				"���...", npchar, Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
			if (pchar.questTemp.Sharp.SeekSpy == "seekSpy")
			{
				link.l2 = LinkRandPhrase("������, ��� ��� ��� ���� ������� ���-���... � �����, �� �� � �����, ���-������ � �������� ��� � ��� �����������?", 
					"�� �� ������, ��������, ��� � ��� ��� � ������� ����� �����?", 
					"� ���� � ���� ������, �������. ��� ��� � ��� ������� � ������ � ��������?");
				link.l2.go = "PearlMan_Sharp_1";
			}
		break;
		case "PearlMan_1":
			dialog.text = "�� ��� ������ ��������, ������ " + NationNameGenitive(sti(npchar.nation)) + ", ����� ��� ����...";
			link.l1 = "��, � � �����...";
			link.l1.go = "exit";
			link.l2 = "������, � ������ �� ��������� ������� ���� ���������� � �������������, ��� �������, �?";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "�� ���, ��� ��!!! �� ����� ���� ����� ��������� ��������� - ������!";
				link.l1 = "���, ������� ��� � ��� ��������...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "� ��� � ���� ����� ������, ����� �������� �������� ������. � ���� �� ���������, �� ���� ������������ ���� ���������� � ������� ��������, ��� �������� ������ � ����. �� ���� ���� ������ � ������ ����, ��� �������� ��� �����...";
				link.l1 = "�������, �� ������� ����.";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("�� ����, �� ������ "+ GetSexPhrase("�������? ��� ������, ��������","�������? ��� ������, ����") +"!", 
				""+ GetSexPhrase("����?!! ��, �����, ������ �� �������, �����","����?!! ��, �����, ������ �� ��������, ������") +"?! ���� ������ �� ������ ���������...", 
				""+ GetSexPhrase("�� � ����� ���, ������? ����� ������?! � ���?!! ��� �� �� ������, �����������","�� � ����� ���, ������? ����� ������?! � ���?!! ��� �� �� ������, �������") +"...");
			link.l1 = RandPhraseSimple("�� ���� ������...", "��� �� ���������?!");
			link.l1.go = "exit";
		break;

		// ==> ������� � ���������
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("�����������","����� ����") +" ����� ��������?", 
				"����� ��, "+ GetSexPhrase("�����������","����� ����") +".", 
				""+ GetSexPhrase("����������� ����� ��������. �� ����� �� ����.","����� ���� ����� ��������.") +"",
                "���� ������� �� ��� ���������"+ GetSexPhrase("��� �����","�� ������") +".", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��.", 
				"��, ����� �.",
                "����� ��������.", 
				"� ���� ���"+ GetSexPhrase("","�") +" ���� ������.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "������, ����� ����"+ GetSexPhrase("��","��") +".";
			link.l1 = "�� ������ ����������, ��������� ���� �����"+ GetSexPhrase("","�") +"...";
			link.l1.go = "exit";
			link.l2 = "� ���� ���� ������ �� �������?";
			link.l2.go = "IndPearlMan_2";
			if (pchar.questTemp.Sharp.SeekSpy == "seekSpy")
			{
				link.l3 = "��������, ��� ����������� ����! � ��� ��� ����� ������ ������� ������ ��������. �� �������� ���?";
				link.l3.go = "IndPearlMan_Sharp_1";
			}
		break;
		//��������� ��������� �����, ������ ������������
		case "IndPearlMan_Sharp_1":
			dialog.text = "��� ���� �����������? ������...";
			link.l1 = "��, ���������, ���� ����������, ��� ���-�� �� ����� ���-���� �������� � ���, ��� � ��������� ���� �� �������� ����� ������.";
			link.l1.go = "IndPearlMan_Sharp_2";
		break;
		case "IndPearlMan_Sharp_2":
			dialog.text = "� ����, ��� ����� "+ GetSexPhrase("�����������","����� ����") +"...";
			link.l1 = "����?";
			link.l1.go = "IndPearlMan_Sharp_3";
		break;
		case "IndPearlMan_Sharp_3":
			dialog.text = "������ ����, "+ GetSexPhrase("����������� ����","����� ����") +", � ����� �������� �� ����. ���� ����� �������, ����� ������ ������. ��� ������ � ������ ����� �����.";
			link.l1 = "����� �����?";
			link.l1.go = "IndPearlMan_Sharp_4";
		break;
		case "IndPearlMan_Sharp_4":
			dialog.text = "�� ��������� �� ����� ���-���� ���� �����. ������ ����� �������� ���� �����, ��� �� ������� � �����, ��� �������� ����� �� �����, � ������ ��� � �������� ����.";
			link.l1 = "������ ��� ����� �� �����?";
			link.l1.go = "IndPearlMan_Sharp_5";
		break;
		case "IndPearlMan_Sharp_5":
			dialog.text = "������ ��� �� ��� �� �������.";
			link.l1 = "�-�-�, �������. �� ��� ��, ������� ����, ��� ����������� ����.";
			link.l1.go = "IndPearlMan_Sharp_6";
		break;
		case "IndPearlMan_Sharp_6":
			dialog.text = "����� ����� ������ ���� ����� ������.";
			link.l1 = "� �� ��� �������. ������...";
			link.l1.go = "exit";
			pchar.questTemp.Sharp.SeekSpy = "toLaVega";
            AddQuestRecord("SharpPearl_SeekSpy", "2");
			AddQuestUserData("SharpPearl_SeekSpy", "sName", npchar.name);
			pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1 = "location";
			pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1.location = "Shore55";
			pchar.quest.SharpSeekSpy_loginSpy.function = "SharpSeekSpy_loginSpy";	
		break;
		//������� �������
		case "IndPearlMan_2":
			if (!CheckAttribute(npchar, "quest.pearl")) npchar.quest.pearl = rand(1);
			if (sti(npchar.quest.pearl) == 0 || CheckAttribute(pchar, "quest.PearlToShore_ForSale.id"))
			{
				dialog.text = "������ � ������ ��������� ���� ���� ����� "+ GetSexPhrase("�����������","�����������") +"? ���.";
				link.l1 = "������ �� �������? ��, ��� ������...";
				link.l1.go = "exit";
			}
			else
			{
				bOk = false;
				int num = FindNearCharacters(npchar, 5.0, -1.0, -1.0, 1.0, false, true);
				if(num > 0)
				{
					for(int i = 0; i < num; i++)
					{
						iTemp = chrFindNearCharacters[i].index;
						if (iTemp == GetMainCharacterIndex()) continue;
						sTemp = characters[iTemp].id;
						if (findsubstr(sTemp, "FightMan" , 0) != -1)
						{
							bOk = true;
							break;
						}
					}
				}				
				if (bOk)
				{
					dialog.text = "� ���� ���� ����� �����. � ����������� ����, ��� ������, ��� ������, ��� ����� ���� �����. � �����...";
					link.l1 = "����?..";
					link.l1.go = "IndPearlMan_4";
				}
				else
				{
					dialog.text = "� ���� ���� ����� �����. ������� � ������� ���� �����, � ���� ��� �� ������ ����.";
					link.l1 = "�������. ��������� �����, �� ��������. ����� �����������.";
					link.l1.go = "IndPearlMan_3";
				}
			}
		break;
		case "IndPearlMan_3":
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
            NextDiag.CurrentNode = "IndPearlMan_Sale";
			LAi_SetActorTypeNoGroup(NPChar);
			if (npchar.location == "Pearl_town_2")
			{
				LAi_ActorRunToLocation(NPChar, "reload", "reload1", "Shore51", "goto", "goto1", "PearlToShore_ForSale", 10.0);
			}
			else
			{
				LAi_ActorRunToLocation(NPChar, "reload", "reload1", "Shore49", "goto", "goto1", "PearlToShore_ForSale", 10.0);
			}
			pchar.quest.PearlToShore_ForSale.idx = npchar.index;
			npchar.quest.Pearl.bigQty = rand(30) + 10;
			npchar.quest.Pearl.smallQty = rand(60) + 20;
			chrDisableReloadToLocation = true;
			DialogExit();
		break;
		case "IndPearlMan_4":
			npchar.LifeDay = 0;
			LAi_group_Attack(NPChar, Pchar);
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			LAi_SetActorType(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 10.0);
			DialogExit();
		break;

		case "IndPearlMan_Sale":
			dialog.text = "�� "+ GetSexPhrase("������","������") +"...";
			link.l1 = "�� ��, � ���� �����?";
			link.l1.go = "IndPearlMan_Sale_1";
		break;
		case "IndPearlMan_Sale_1":
			dialog.text = "������ - �� ������� �����, ���� - �� ���������.";
			link.l1 = "����, ������� � ���� ����?";
			link.l1.go = "IndPearlMan_Sale_2";
			link.l2 = "���, �� ���� �����, ���������"+ GetSexPhrase("","�") +".";
			link.l2.go = "IndPearlMan_Sale_Out";
		break;
		case "IndPearlMan_Sale_2":
			dialog.text = npchar.quest.Pearl.bigQty + " �������, " + npchar.quest.Pearl.smallQty + " ���������.";
			link.l1 = "������, ���� ���!";
			link.l1.go = "IndPearlMan_Sale_3";
		break;
		case "IndPearlMan_Sale_3":
			int iTemp = (sti(npchar.quest.Pearl.bigQty)*10) + (sti(npchar.quest.Pearl.smallQty)*5);
			if (sti(pchar.money) >= iTemp)
			{
				dialog.text = "���� ���������� ���, � �������...";
				link.l1 = "�����, ��������...";
				AddMoneyToCharacter(pchar, -iTemp);
				TakeNItems(pchar, "jewelry11", sti(npchar.quest.Pearl.bigQty));
				TakeNItems(pchar, "jewelry12", sti(npchar.quest.Pearl.smallQty)); 
			}
			else
			{
				dialog.text = "�� "+ GetSexPhrase("������","������") +" ��� " + iTemp + " �����. � ���� ��� �����, � ���� ��� ���� �����. ������.";
				link.l1 = "��, ����...";
			}
			link.l1.go = "IndPearlMan_Sale_Out";	
		break;
		case "IndPearlMan_Sale_Out":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			DialogExit();
			LAi_SetActorType(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "CanFightCurLocation", -1);
		break;
		
		case "CitizenNotBlade":
			dialog.text = "�������, ��� �� ��������! ������� ������, ���� ��� �� ��������!";
			link.l1 = LinkRandPhrase("������.", "�����.", "�� ���������, ��� ������...");
			link.l1.go = "exit";
		break; 
	}
}
