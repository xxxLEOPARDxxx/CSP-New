
void ProcessDialogEvent()
{
	ref NPChar;
	ref sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First":
			dialog.text = "��������! ��������! �� ���� ������� ��� ���� � ����� ��������� ������� � ���� � ������! ���� ����� ������ �����. ������, � ������ ���� � �������, �� ���� �� ���� ��������� ����������� �������� ������, ����� � ������������ ��� ���� � �������� ��� ������. � ��� ��� ����! ������, ��� ������ ����, ���� ���� ����� �����, �������! �� ����� ����� �������, ������ ���!!!";
			link.l1 = "���� �� �����? ����� ��� ''����''?... �� �������� ���, ��� ���������� �����.";
			link.l1.go = "exit";
			link.l2 = "����? ����? ��� ��� ��� �� ����� �����? ����, ����� ��� � ����� �� �����.";
			link.l2.go = "exit_2";
		break;
		
		case "Second":
			dialog.text = "��, ��������, �� ������ ������� � ����?";
			link.l1 = "���, �������. � ���� �� ����, ��� ����� ��� ''����''.";
			link.l1.go = "exit_3";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DeleteAttribute(npchar,"LifeDay");
			for(i=1; i < sti(npchar.num); i++)
			{
				LAi_SetActorTypeNoGroup(CharacterFromID("GangRapersMan_"+i));
				LAi_ActorFollowEverywhere(CharacterFromID("GangRapersMan_"+i), "", -1);
				DeleteAttribute(CharacterFromID("GangRapersMan_"+i),"LifeDay");
			}
			
			string sTemp = GetArealByCityName(npchar.city);
			if (sTemp == "Cuba2") sTemp = "Cuba1";
			if (sTemp == "Hispaniola2") sTemp = "Hispaniola1";
			aref aPlace, aPlace_2;
			makearef(aPlace, NullCharacter.TravelMap.Islands.(sTemp).Treasure);
			int iQty = GetAttributesNum(aPlace)-1;
			aPlace_2 = GetAttributeN(aPlace, rand(iQty));
			sld = CharacterFromID("GangRapersMan_1");
			sld.num = npchar.num;
			
			pchar.quest.GangRapeOld.win_condition.l1 = "Location";
			pchar.quest.GangRapeOld.win_condition.l1.location = GetAttributeName(aPlace_2);
			pchar.quest.GangRapeOld.win_condition = "GangRapeOld";
			
			Log_Testinfo(GetAttributeName(aPlace_2));
		break;
		
		case "Third":
			dialog.text = "�� ���-�, ������� ������� ����. �� ����� ������, � ��������� - ������� ����!";
			link.l1 = "0_0";
			link.l1.go = "exit_third";
			AddDialogExitQuest("GangRapeOld2");
		break;
		
		case "Final":
			dialog.text = "�������� ���� �����! ���, �������! � �� ����� ������ � �� �����. ���������� �� ������!";
			link.l1 = "O_O";
			link.l1.go = "exit_4";
			AddDialogExitQuest("GangRapeOld3");
		break;
		
		case "exit_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "", "", "", "OpenTheDoors", -1);
			sld = CharacterFromID("GangRapersMan_1");
			sld.num = npchar.num;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "exit_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			for(i=1; i < sti(npchar.num); i++)
			{
				sld = CharacterFromID("GangRapersMan_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "OpenTheDoors", -1);
				sld.LifeDay = 0;
			}
		break;
		
		case "exit_third":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			
			ResetSound();
			SetLaunchFrameFormParam("", "", 0, 20.0);
			PlayStereoSound("Kopcapkz\Voices\Bandits\DedVpeshere.wav");
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
            LaunchFrameForm();
		break;
		
		case "exit_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
