
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp, sStr, sPlace;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (Dialog.CurrentNode == "First time")
	{
		switch (pchar.questTemp.tugs.berglarState)
		{
			case "2": Dialog.CurrentNode = "Second time";	break;
			case "3": Dialog.CurrentNode = "Third time";	break;
			case "4": Dialog.CurrentNode = "Fourth time";	break;
			case "5": Dialog.CurrentNode = "Fifth time";	break;
			case "6": Dialog.CurrentNode = "Sixth time";	break;
		}
	}
    
	switch (Dialog.CurrentNode)
    {
        //------------- ������ ������ --------------
		case "First time":
            dialog.text = "������, "+ GetSexPhrase("��������","�������") +"... ���� ����"+ GetSexPhrase("","�") +", ����� ���, ��� ���� �����?";
            link.l1 = GetFullName(pchar) + " ����������� ��������. � ��� �����?";
            link.l1.go = "Step1_1";
        break;
 		case "Step1_1":
        	dialog.text = "���, ��-�� ��� � ���"+ GetSexPhrase("��","��") +"...";
    		link.l1 = "����������� ������.";
    		link.l1.go = "Step1_2";
		break;
 		case "Step1_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "���";
			else sStr = "��";
        	dialog.text = "��� ������, ��� �����������, ��� ��� ��� ����� �������� ����� ������... ������, ���: � ���� ����� ���� � ����������, ��� ��������� " + sStr + " �������.";
    		link.l1 = "�����, � ������� ������, ��� �������? ������ ������� ��������� �� �����?";
    		link.l1.go = "Step1_3";
		break;
 		case "Step1_3":
        	dialog.text = "���, ������ ��� � ����� ��� �� �����, �� �� ������ ���...";
    		link.l1 = "��, ���� �� ����... � ���� ���� �����?";
    		link.l1.go = "Step1_4";
		break;
 		case "Step1_4":
        	dialog.text = "���� ����� � ������, "+ GetSexPhrase("��������","�������") +".\n�� �����, ������� ��� � ����� ������������� �����, ��� ���� � ���������� �� ��������. �� ������� - ��� ������...";
    		link.l1 = "��� ��� ��� �����"+ GetSexPhrase("","�") +" ��������...";
    		link.l1.go = "Step_overAll";
		break;
		//--------------
        case "Fight_1":
            dialog.text = "�-�-�, ����"+ GetSexPhrase("��","��") +" ���-����...";
            link.l1 = "��, ����"+ GetSexPhrase("��","��") +". ������ ������, ��� ��� � ���� �� ���� ����� � ������?";
            link.l1.go = "FirstFight_1";
        break;        
		case "FirstFight_1":
            dialog.text = "��� � ����, "+ GetSexPhrase("��������","�������") +", ��� � ����... ����� ������� ������ - ���� ����� ������.";
            link.l1 = "� ��� ��� ��?";
            link.l1.go = "FirstFight_2";
        break;        
		case "FirstFight_2":
            dialog.text = "�������, �� �����������"+ GetSexPhrase("��","���") +" �������. ������ �� ����������� � ��������, ������ �� ��"+ GetSexPhrase("��","��") +" ���������"+ GetSexPhrase("��","��") +", � �� � ���� ���������� �� ����...";
            link.l1 = "���, ���� ������. ��, ������, ������, ��� � ���"+ GetSexPhrase("��","��") +", ����� ��� ��� �� ���� �������������?";
            link.l1.go = "FirstFight_3";
        break;        
		case "FirstFight_3":
            dialog.text = "������� ���"+ GetSexPhrase("��","��") +"-��, � �������� ��� ����� � �� ����. �� �� ����"+ GetSexPhrase("�� �� ��������","�� �������") +", ��� ���� ��������, ����� �� � �������� �������. "+ GetSexPhrase("","���� ���, �� ������ �������, ��������� ������� ����. ") +"������, �� ������ ����� �� ����� �����, ������� ��� ������. � ������ ���, ��� �������.\n���������, � ����������� ������ ���� �����, ����� �����.";
            link.l1 = "���� ��, ������� �� �� �������"+ GetSexPhrase("","�") +", ��� �� ����� ���������� ����� ���������� �������� ������...";
            link.l1.go = "FirstFight_4";        
		break; 
		case "FirstFight_4":
            dialog.text = "���, �� ��� � ������, "+ GetSexPhrase("��������","�������") +", ��������� ���������. ����� ������� - ������� �� �������, �� ����� � ���� �������...";
			link.l1 = "������� ��������� - ����������...";
            link.l1.go = "FirstFight_overAll";
        break; 
        //------------ ������ ������ ----------------
        case "Second time":
            dialog.text = "�������, � ���� ������ ������ ������ �������?";
            link.l1 = "������.";
            link.l1.go = "Step2_1";
        break;
        case "Step2_1":
            dialog.text = "���� ���...";
            link.l1 = GetFullName(pchar) + ". � ���?";
            link.l1.go = "Step2_2";
        break;
        case "Step2_2":
            dialog.text = "����� ��-�� ��� � �����. � ���� ���� ���-��� ��� ���, ��� ����� ����������� � ���� � ���������� ����������.";
            link.l1 = "������� ������� � �������.";
            link.l1.go = "Step2_3";
        break;
        case "Step2_3":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "���";
			else sStr = "��";
            dialog.text = "��������, �� � �� ���� ����� �������, � ��������, ������� ����. � �� ���� ����� ������������� � ����, ��� ��� ����� ��� ������� � ����������, ��� ��������� " + sStr + " �������.";
            link.l1 = "���, ���-�� ��� ��� ����������...";
            link.l1.go = "Step_overAll";
        break;
		//----------
        case "Fight_2":
            dialog.text = "��������...";
            link.l1 = "��, ��� ������, � ����"+ GetSexPhrase("��","��") +". ��� � ���� �� ���, ������ �������!";
            link.l1.go = "SecondFight_1";
        break;
        case "SecondFight_1":
            dialog.text = "���������� ���, ��� � ���� ����, � �����������, ����� � ���� �������, ��� �� ����� � ������...";
            link.l1 = "� ����� ��� �����?";
            link.l1.go = "SecondFight_2";
        break;
        case "SecondFight_2":
            dialog.text = "������, "+ GetSexPhrase("�����","������") +", ����� ���� �������� ������!";
            link.l1 = "����, ������� �����-��! �� ������ ���, ��� �������� ���� ����� ����� ��� �������.";
            link.l1.go = "SecondFight_3";
        break;
        case "SecondFight_3":
            dialog.text = "��, ��� ��� ���\n�� ��� ��, ������ ��� ���-��� ����...";
            link.l1 = "� ��� ���� ����?";
            link.l1.go = "FirstFight_overAll";
        break;
        //------------ ������ �������, ����������� ----------------
        case "Third time":
            dialog.text = "�������� ���������, "+ GetSexPhrase("��������","�������") +"!";
            link.l1 = "����?";
            link.l1.go = "Step3_1";
        break;
        case "Step3_1":
            dialog.text = "���������� ����������� - ����������� ���! ���� �� ��, ��� ��� �������� � ��������...";
            link.l1 = "�� � ��� ���?";
            link.l1.go = "Step3_2";
        break;
        case "Step3_2":
            dialog.text = "��� � ���? ��� �� �� ���������?!\n'�������� ����� ��������������� ����' - ��� ��� ����� ������� ���������, � ��� ����! ������������ ���� ��������� ������� ����������...";
            link.l1 = "��������, �� ����� ������, �� ������ �����. ��� ��� ������, �� � �����...";
            link.l1.go = "Step3_3";
        break;
        case "Step3_3":
            dialog.text = "����?! ���� �� �������? ��� �� ������ ����, � �� ��� ����"+ GetSexPhrase("","�") +" ��������� ������������� � ��� ������� ��������������. ������ ������� � ������� � �������� ������, ��-��-��...";
            link.l1 = "��� �� � �������� �����, ��� �������� ���� � ���������� � �������� �����?";
            link.l1.go = "Step3_4";
        break;
        case "Step3_4":
            dialog.text = "������ ���, "+ GetSexPhrase("���� ���","�����") +", ������ ���...";
            link.l1 = "���� ������, ��� ��� �����?!";
            link.l1.go = "Step3_5";
        break;
        case "Step3_5":
            dialog.text = "��-��-��, �� �����...";
            link.l1 = "�������, �� �� ��� ����� ������!";
            link.l1.go = "Step3_6";
        break;
        case "Step3_6":
            dialog.text = "� ��� �� �����... � ���� ���� ������ ���������, ��� ����������� ��� ������... �-�-�-�, ����� ������� ��� ����!!!\n�� ������ ��� ���������, � ������ �� �����. � ��� ���� �������! ����� ������������ �������, ����� �� �� ��������� ������� ������, � ��������, ����� �������� ��������. ����� ����� ������...";
            link.l1 = "����?!";
            link.l1.go = "Step3_7";
        break;
        case "Step3_7":
            dialog.text = "�� ������, ���� ��� �� ��������. ��� ��� ���� � ��������!";
            link.l1 = "�-�-�, �����������...";
            link.l1.go = "Step3_8";
        break;
        case "Step3_8":
            dialog.text = "��, � �� ��� ��. ���� ����� ��������� �� ������ ������, ��� ��� ������, ��� ��� �� ����"+ GetSexPhrase("","�") +" �����. ���� �������"+ GetSexPhrase("��","��") +" � ���"+ GetSexPhrase("��","��") +", �� ������ ��, ����� ��� ��������!";
            link.l1 = "�����?..";
            link.l1.go = "Step3_9";
        break;
        case "Step3_9":
			sTemp = "berglar" + npchar.city;
			pchar.questTemp.tugs.berglarState = sti(pchar.questTemp.tugs.berglarState) + 1; //�������
			npchar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			DialogExit();
        break;
        //------------ ��������� ������� ----------------
        case "Fourth time":
            dialog.text = "������������, " + GetAddress_Form(NPChar) + ".";
            link.l1 = "������������. ��� ������"+ GetSexPhrase("","�") +"?";
            link.l1.go = "Step4_1";
        break;
        case "Step4_1":
            dialog.text = "����������, � ���� ���� ��� ��� ������, ������� ��������� ��� ������������. � �� ������� ����!";
            link.l1 = "�� ��� ��, � ������ ���"+ GetSexPhrase("","�") +" ������� ������������. ����������, ��� ��� � ����.";
            link.l1.go = "Step4_2";
        break;
        case "Step4_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "���";
			else sStr = "��";
            dialog.text = "������ �� �����, " + GetAddress_Form(NPChar) + ". ��� ������ ����� � ��� �� �����. � ���� ����� ��� �� �������� � ����������, ��� ��������� " + sStr + " �������. ���������, �� ���������!";
            link.l1 = "������, ��������, �� ��� ������ ���������� ���, ��� �������� ���� � ������� ���������. ������� ��� ��� ��������� �������� ��������������...";
            link.l1.go = "Step4_3";
            link.l2 = "���, � ������������� ������ �� ����� �������, �� ���� ������������. ������ �������������?";
            link.l2.go = "Step4_5";
        break;
        case "Step4_3":
            dialog.text = "��, ��� ��� ���... ��������, ���� ������ ����������.";
            link.l1 = "�������?!";
            link.l1.go = "Step4_4";
        break;
        case "Step4_4":
			sTemp = "berglar" + npchar.city;
			npchar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			DialogExit();
        break;
        case "Step4_5":
            dialog.text = "�� ��, �� �������.";
            link.l1 = "����� ������� �������� �����!";
            link.l1.go = "Step4_6";
        break;
        case "Step4_6":
            dialog.text = "�� ��� ��, ��� ��� � �����������, " + GetAddress_Form(NPChar) + ".";
            link.l1 = "�� ������ �������, ��������.";
            link.l1.go = "Step_overAll";
        break;
        case "Fight_4":
            dialog.text = "�-�-�, �� �������-��!";
            link.l1 = "����������, ��� ��� � ����.";
            link.l1.go = "Fight4_1";
        break;
        case "Fight4_1":
            dialog.text = "���, ��� �� ����������. ������� ����� ������"+ GetSexPhrase("","��") +"?";
            link.l1 = "������ ������� ���� �����.";
            link.l1.go = "Fight4_2";
        break;
        case "Fight4_2":
			dialog.text = "�� ��� �������� ������, �� ��� ��� � �� �����"+ GetSexPhrase("","�") +"?";
            link.l1 = "����� ��� ������, ������� ��� �� ����. �� ���� ������ �� �����, ��� �������� ���� ����� ��� ������� ��������. ��� ��� ������, ��� �� ����� � ��� ����� �����?";
            link.l1.go = "Fight4_3";
        break;
        case "Fight4_3":
            dialog.text = "�� ������ ������ ��������...";
            link.l1 = "�������... ��, ������ ������ ���� �� �����, ���������� ������� �� ������� ��� ������!";
            link.l1.go = "Fight4_4";
        break;
        case "Fight4_4":
            dialog.text = "��, � �� �� ��� ��� �����������.";
            link.l1 = "�����������, ������...";
            link.l1.go = "FirstFight_overAll";
        break;
        //------------ ����� ������� ----------------
        case "Fifth time":
            dialog.text = "������������, " + GetAddress_Form(NPChar) + ". �������, �� �� �� �"+ GetSexPhrase("��","�") +" ��������"+ GetSexPhrase("�� �������","�� �������-�������") +", ��� ������"+ GetSexPhrase("","��") +" �� ������� ����� ������� ���� �����?";
            link.l1 = "���, � �� ��������� ����������� ����������� � ������ ����.";
            link.l1.go = "Step5_1";
        break;
        case "Step5_1":
            dialog.text = "��, ��� ����, ��� ����! � ����� ���������� "+ GetSexPhrase("����� ��������","��") +" � ������� ������� �������� ������.";
            link.l1 = "��� ����� ������ �����?";
            link.l1.go = "Step5_2";
        break;
        case "Step5_2":
            dialog.text = "���, ��� ��! � ���� ���� ��������������, �� ������ ������������� �����. ��� ��� ��� ��, � ��� ������� �������� �������� - ������� ����� �� ����� � �������� ������.";
            link.l1 = "� ��� ��� �� �����? ��������, � ������������� ����.";
            link.l1.go = "Step5_3";
        break;
        case "Step5_3":
            dialog.text = "��, �������, ��� ������ � �� ���� ������� �� ����. ���� ��������� - ������������ ������� �����. �� ���� � ������� ���������� ����������� ��� �����.";
            link.l1 = "� ��� �� �, ��� ����� ������ �������, ������ ������� ���������������� ������, ���� �� �� ������� �������� � ������?";
            link.l1.go = "Step5_4";
        break;
        case "Step5_4":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "���";
			else sStr = "��";
            dialog.text = "� ����� ��� ��������� � ������ ������, �� �� �����. ��������� ����������� � ���� ������� � ����������, ��� ��������� " + sStr + " �������. ������� ��� ������ �������, �� � ���� ������ � ����������� ������������.";
            link.l1 = "���, ������� � ����������� ��� ��� ��������� ������. � ��� ��� ���� ��� ���� �������� �����.";
            link.l1.go = "Step5_5";
            link.l2 = "�������, ��� ������������ ����������. � ���� ������� ���� ���� ��-�-���� ����������...";
            link.l2.go = "Step5_7";
        break;
        case "Step5_5":
            dialog.text = "� ����� ������, ��� �� � ��� ��������!";
            link.l1 = "...";
            link.l1.go = "Step5_6";
        break;
        case "Step5_6":
			sTemp = "berglar" + npchar.city;
			npchar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, "none", "", "", "", -1);
			pchar.questTemp.(sTemp) = "over";
			DialogExit();
        break;
        case "Step5_7":
            dialog.text = "��, ��� � ������������. � ���� ����� ��� ��� �� ��������, ���� �� �� ������� - ��� ����������.";
            link.l1 = "������, � �����"+ GetSexPhrase("","�") +".";
            link.l1.go = "Step_overAll";
        break;
        case "Fight_5":
            dialog.text = "���-���, �� ��� ��, �����������!";
            link.l1 = "��������� ���� �����.";
            link.l1.go = "Fight5_1";
        break;
        case "Fight5_1":
            dialog.text = "�� ������, � ���� ���������� �������. ����� ������, �� ��������� ���� �� ���� ��������.";
            link.l1 = "��, ��� ��� ������...";
            link.l1.go = "Fight5_2";
        break;
        case "Fight5_2":
            dialog.text = "�� ��� � ���?";
            link.l1 = "�� ���� ������ �� ��� ��������� ����������, ��� �������� ���� �������� ����� ��� �������. � ��� ���, ����� ����� �� ���� ������?";
            link.l1.go = "Fight5_3";
        break;
        case "Fight5_3":
            dialog.text = "��� ��� �� ����"+ GetSexPhrase("","�") +" �� ����?! ��, ��������� ���������...";
            link.l1 = "������, ��� �����, � ������ ����.";
            link.l1.go = "Fight5_4";
        break;
        case "Fight5_4":
            dialog.text = "���� � �����, ��� �����, ��� � ����� ������ ������, ����� �� ������� �������������. � ��� � ���� ���� ���� ������.";
            link.l1 = "������ � ������� �� ���� � ���� ������ ���. ������, ��������� ������, �� ������� ����...";
            link.l1.go = "Fight5_5";
        break;
        case "Fight5_5":
            dialog.text = "���-���� � ���������!";
            link.l1 = "��, ��� ������...";
            link.l1.go = "FirstFight_overAll";
        break;
        //------------ ������ ������� ----------------
        case "Sixth time":
            dialog.text = "������������ " + GetAddress_Form(NPChar) + ". �������, �� ������� " + GetFullName(pchar) + "?";
            link.l1 = "��, ��� ���� �����.";
            link.l1.go = "Step6_1";
        break;
        case "Step6_1":
			dialog.text = "� ���� ��� ��� ���������: ����� ����� ����� � ���� ���������.";
            link.l1 = "��, � ������"+ GetSexPhrase("��","��") +".";
            link.l1.go = "Step6_2";
        break;
        case "Step6_2":
			if (npchar.city == "SentJons" || npchar.city == "FortFrance") sStr = "���";
			else sStr = "��";
            dialog.text = "���������. �� ����� ����� ��� �� �������� � ����������, ��� ��������� " + sStr + " �������.";
            link.l1 = "��� ��� ������... ��, ������.";
            link.l1.go = "Step_overAll";
        break;
        case "Fight_6":
            dialog.text = "�, ��� � ��...";
            link.l1 = "��� �����?";
            link.l1.go = "Fight6_1";
        break;
        case "Fight6_1":
            dialog.text = "��� ������ ����� ���, �� �� ��������� ��� ������ � �������� ��� �����.";
            link.l1 = "��, ������ ������. � �� ������, ��� ��������� � ����, ��� ������� ��� ������� �� ����?";
            link.l1.go = "Fight6_2";
        break;
        case "Fight6_2":
            dialog.text = "����, �� � �������, ��� � ���� ���������.";
            link.l1 = "��, � ���-�� ����� ���, ���� ���? ������ �� ���� ���, ������ ������.";
            link.l1.go = "Fight6_3";
        break;
        case "Fight6_3":
            dialog.text = "�� ����� � ����� �� ��������� ������ �������, �� �������� ������� �����.";
            link.l1 = "��, ������� �� ����������, ������� �� �� �������"+ GetSexPhrase("��","���") +", ��� ������� ����� ���������� � ����� ���������� ��� ������.";
            link.l1.go = "Fight6_4";
        break;
        case "Fight6_4":
            dialog.text = "��, � ������ ����� ��������, ������� �� �� ��������������� ���� �������.";
            link.l1 = "��� �������, ��������...";
            link.l1.go = "FirstFight_overAll";
			AddQuestRecord("BerglarsGang", "1");
        break;
		//------------ ����� ���� ----------------
 		case "Step_overAll":
			sTemp = "berglar" + npchar.city;
			sStr = "Birglars_fight_" + npchar.index;
			pchar.quest.(sStr).win_condition.l1 = "locator";
			pchar.quest.(sStr).win_condition.l1.location = pchar.questTemp.tugs.(sTemp);
			pchar.quest.(sStr).win_condition.l1.locator_group = "item";
			pchar.quest.(sStr).win_condition.l1.locator = "berglar1";
			pchar.quest.(sStr).function = "Birglars_fight";
			pchar.quest.(sStr).city = npchar.city; //�������� ����� ���������
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
            NextDiag.CurrentNode = "Fight_" + pchar.questTemp.tugs.berglarState;
			if (npchar.city == "SentJons")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade22"));
			}
			if (npchar.city == "FortFrance")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade31"));
			}
			if (npchar.city == "Marigo")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade34"));
			}
			if (npchar.city == "Panama")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade21"));
			}
			if (npchar.city == "Cartahena")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("topor2"));
			}
			if (npchar.city == "SantaCatalina")
			{
				GiveItem2Character(npchar, "pistol2");
				GiveItem2Character(npchar, GetGeneratedItem("blade15"));
			}
			sTemp = "berglar" + npchar.city;
			LAi_LocationDisableMonGenTimer(pchar.questTemp.tugs.(sTemp), 1); //�������� �� �������� 1 ����
			LAi_LocationDisableOffGenTimer(pchar.questTemp.tugs.(sTemp), 1); //�������� �� ������� 1 ����
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", pchar.questTemp.tugs.(sTemp).locator, pchar.questTemp.tugs.(sTemp), "item", "berglar1", "OpenTheDoors", -1.0);
			chrDisableReloadToLocation = true;
			//pchar.questTemp.tugs.(sTemp) = "fight";
			DialogExit();
		break;
		case "FirstFight_overAll":
			LAi_group_Delete("EnemyFight");
			pchar.questTemp.tugs.berglarState = sti(pchar.questTemp.tugs.berglarState) + 1; //�������
			npchar.SaveItemsForDead  = true; 
			npchar.DontClearDead = true; 
			SetCharacterPerk(npchar, "Energaiser"); // ������� ���� ���� 1.5 � �������� �������, ������ �� � ������ �������
			npchar.cirassId           = Items_FindItemIdx("cirass5"); //1.2.3
			sTemp = "berglar" + npchar.city;
			
			// ����� �����
			if(sti(pchar.questTemp.tugs.berglarState) == 2) 
			{
				AddSimpleRumourCityTip("��, � ����������� �� � ����, " + GetAddress_Form(pchar) + ", ������� ����. � ��� ��� ������ ����� ������ �� ����, ������� ��� �� ����� �����, � �� ���� ��� � �� ��������. ������ ����� ������, � ������� �� �������, ������ ����� ��� ����... � ������������ �� ��� �� ��� �������!.. " + 
					"�� ����� �������� ������� ��������, ��� ������ ���� �������� �� ���� � ������ � �����-�� ����� �� �������������� �� ������ ������ �����������. ��� ���, � ��� ����� ������� � ���...", npchar.city, 3, 1, "habitue", "");
			}
			if(sti(pchar.questTemp.tugs.berglarState) == 4) 
			{
				AddSimpleRumourCityTip("���� ��� � ��� ������� - ������� ���� ������... ����� � ������� � �� �����, �� ����. ����� ��� ������� ����� �����, � ������ �� �������. ������ �����������, � � �������� - �� �����! �� ��, " + GetAddress_Form(pchar) + ", ����� � ���, �� ������� �����! ������� �� �������� �� �����. ��� ���� � ������, ��� �����!.. " + 
					"������ �, � ����-������ �������� ��� �� ���������, � �� ��������... ��, ���������...", npchar.city, 3, 1, "habitue", "");
			}
			
			LAi_SetHP(npchar, stf(pchar.questTemp.tugs.(sTemp).hp), stf(pchar.questTemp.tugs.(sTemp).hp));
			LAi_SetCurHPMax(npchar);
			chrDisableReloadToLocation = true;
			DeleteAttribute(npchar, "city"); //����� �� �������� � ������
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			if (npchar.id == "BerglarFortFrance")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man", 18, PIRATE, 0, true));
				FantomMakeCoolFighter(sld, 18, 60, 50, BLADE_LONG, "pistol3", 10);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			if (npchar.id == "BerglarPanama")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man", 21, PIRATE, 0, true));
				FantomMakeCoolFighter(sld, 21, 60, 50, BLADE_LONG, "pistol3", 20);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}
			if (npchar.id == "BerglarSantaCatalina")
			{
				GetCharacterPos(pchar, &locx, &locy, &locz);
				sld = GetCharacter(NPC_GenerateCharacter("Berglars_Helper", "pirate_"+(rand(9)+1), "man", "man", 20, PIRATE, 0, true));
				FantomMakeCoolFighter(sld, 20, 60, 50, BLADE_LONG, "pistol3", 20);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, npchar.location, "monsters", LAi_FindNearestFreeLocator("monsters", locx, locy, locz));
			}						
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
        break;
        //------------ ��������� ������ � ������� ----------------
        case "Final_fight":
            dialog.text = "����������� ����������, ��� �������� ��� ����� �����. ��� ������?";
            link.l1 = "������ ����, �����. �����"+ GetSexPhrase("","�") +" ���������� �� ���� �����, ��� �������. � �� ���� ������� ��������, � ��� � �����������...";
            link.l1.go = "StepF1_1";
        break;
        case "StepF1_1":
            dialog.text = "�����? �������� ����� ��� ��� ���... �-�, � �����. �� � ���� �"+ GetSexPhrase("��","�") +" �������, ��� ����"+ GetSexPhrase("","�") +" ���������� ���� �����. " + GetFullName(pchar) + ", ���� �� ��������...";
            link.l1 = "������ ���, �����... �����-�� ���, ��������, ��� �� ��� �������� �� �����? �� ������� �������� ������, ���������� ���������� ��������� � ���������� �� �����.";
            link.l1.go = "StepF1_2";
        break;
        case "StepF1_2":
            dialog.text = "���� �� ����! �� ���, ���������� ���� ������? � ��� ��� ������� "+ GetSexPhrase("�������, �������","��������, �������") +" ���������� ����� ��� ��!";
            link.l1 = "��� ��� ������?!";
            link.l1.go = "StepF1_3";
        break;
        case "StepF1_3":
            dialog.text = "�� �� �� ��������� �� ���� �� ����������? �� �� �� �������� ����� �������? � � ���� ������ ������, ���� ����? � ��� �� �� ���� ������ - ���� �����.\n�� � ����� "+ GetSexPhrase("������","������") +" �� ����� ����� �����, ������ � - ���������� ����.";
            link.l1 = "� �� ��������� ����� ����� � ����!";
            link.l1.go = "StepF1_4";
        break;
        case "StepF1_4":
            dialog.text = "��, � �� �� �� ���������� ����� ������ ������, ������� ��� ����� �������� ������ � ���������������� � ��� ����������?";
            link.l1 = "��� ������...";
            link.l1.go = "StepF1_5";
        break;
        case "StepF1_5":
            dialog.text = "��� �� �� �����, "+ GetSexPhrase("��������","�������") +"! �����, ��������, ��������� ���������� ������. ��� ��������, "+ GetSexPhrase("������� ����","������� ������") +".\n��� ��� ������ �� ���� ������ � ������ ����� ������ - � ������ �� ���������� ����������������, ��� ��� ���, ��� � ���� ����� �������.";
            link.l1 = "������ �������...";
            link.l1.go = "StepF1_6";
        break;
        case "StepF1_6":
            dialog.text = "��, ����� � ���... ������, ����� ����"+ GetSexPhrase("��","��") +", �����"+ GetSexPhrase("�� ����","�� ������") +".";
            link.l1 = "������� ������ ��������, �� � ���� �� ����� ���"+ GetSexPhrase("","�") +". � ��� ��� � ���� ����� - ����� ���� �������� �������. � ����������� ��� � ���, ��� � ��� ����� ����� - ������� ��� ������� ������. � �� ������ �� �����, � ��� ���� ������ �������� ��� ��, � �����������. ��� ���, �� ���� �� ���.";
            link.l1.go = "StepF1_7";
        break;
        case "StepF1_7":
            dialog.text = "��������� ����"+ GetSexPhrase("��","��") +"?";
            link.l1 = "������. ���� ��������� ������� � �������� ��������� ���� �� �����.";
            link.l1.go = "StepF1_8";
        break;
        case "StepF1_8":
            dialog.text = "��� ��, ��� � �������, �� ���� ��� �������� ������"+ GetSexPhrase("","�") +". ����� ���������, ������"+ GetSexPhrase("","���") +"!";
            link.l1 = "����, �������...";
            link.l1.go = "StepF1_9";
        break;
        case "StepF1_9":
			LAi_LocationFightDisable(loadedLocation, false);
			CloseQuestHeader("BerglarsGang");
			LAi_group_Delete("EnemyFight");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
   			npchar.cirassId           = Items_FindItemIdx("cirass5"); //1.2.3
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
        break;

 		case "Exit":
            NextDiag.TempNode = "First time";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
    }
}
