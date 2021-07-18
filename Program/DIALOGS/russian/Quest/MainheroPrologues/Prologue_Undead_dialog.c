void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	ref _location;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.id == "SharleMary")
			{
				chrDisableReloadToLocation = false;
				LAi_SetPlayerType(PChar);
				LAi_SetImmortal(NPChar, true);
				dialog.text = GetSexPhrase("��� �������! �� ���� � �����!","������ ���! �� ��� � �����!");
				link.l1 = "�������. "+GetSexPhrase("����������","�����������")+" �� ����� �� ������. ���� �� ������? ��� ������� ��������� ��� ������.";
				link.l1.go = "2";
			}
			
			NextDiag.TempNode = "First time";
		break;

		case "Gravedigger":
			dialog.text = GetSexPhrase("��","���")+" ���������!!! ��������� ����, �������!";
			link.l1 = "�������!!!";
			link.l1.go = "exit_fight";
		break;
		
		case "DeadmansGod":
			dialog.text = "�� ������, ��� �?";
			link.l1 = "������.";
			link.l1.go = "DeadmansGod_1";
		break;
		case "DeadmansGod_1":
			dialog.text = "� - ����������! � ������� ���� �� ����� � ����� �� �������� � ���� ����� � ������. �� ����� ������ ����� ��� ���. �� � ��������"+GetSexPhrase("��","��")+".";
			link.l1 = "� �����... �����... ���� ������ ������ ������ ���. �� ��!";
			link.l1.go = "DeadmansGod_2";
		break;
		case "DeadmansGod_2":
			dialog.text = "�� ����"+GetSexPhrase(" ","��")+" ������ �� ����, ��� ���� ���� ���. �� � ����� ��� ���� �� ���, ������, ��������, ����������?";
			link.l1 = "�������...";
			link.l1.go = "DeadmansGod_3";
		break;
		case "DeadmansGod_3":
			dialog.text = "�����!\n�� �� ������������ �� �����, �� ���������. ����� ��� ����� �������, � ���� ��� ����� ��������, ��� �� ����� �� ����� ����, �� ������ �����. � ��� �� ������� ��, ��� �� ���� ��������, �� ����������� � ������������! �����!\n�� ���� � � ��������������� �����, �������� � ����� ������ ���� ������ �� �����. � ������ ���� ������ � ��� ������ �������. ���� � ������, �������� ����, � ��� �����������. � ��� �� ����� ���������... ��... ������� ����� �� ������. ������� ����? ��� ������ ������ ������ ������ �����. ���, ���� � �� ���������!";
			link.l1 = "...";
			link.l1.go = "DeadmansGod_4";
		break;
		case "DeadmansGod_4":
			DialogExit();
			DoReloadCharacterToLocation("Common_CryptBig2", "goto", "goto9");
			PlaySound("interface\grob.waw");
			DoQuestFunctionDelay("Undead_Start_Graveyard", 0.1);
			DoQuestFunctionDelay("Undead_Start_Graveyard_1", 1.0);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;
	}
}