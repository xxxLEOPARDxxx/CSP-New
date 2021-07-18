
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arAll;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Kamikazi":
			dialog.text = "...";
			link.l1 = "������...";
			link.l1.go = "Kamikazi_2";
		break;
		
		case "Kamikazi_2":
			StopSound(0,0);
			chrDisableReloadToLocation = false;
			LAi_Explosion(NPChar,20);
			LaunchBlood(NPChar,1.0,true);
			LaunchBlast(NPChar);
			LaunchBlastGrenade(NPChar);
			ChangeCharacterAddress(npchar, "none", "");
			
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //������� ����� ������
			makearef(arAll, pchar.GenQuest.DestroyGang);
			pchar.GenQuest.DestroyGang = "Execute"; //���� �������� �������
			pchar.Kamikazi = "Meet";
			string sTemp = GetFullName(&characters[GetCharacterIndex(arAll.MayorId)]);
			// ������� ������
			AddQuestRecord("MayorsQuestsList", "22");
			// �����
			AddSimpleRumour(LinkRandPhrase("�� ������, ���������� " + sTemp + " ������� ����"+ GetSexPhrase("��� ��������","� �������") +" " + GetMainCharacterNameDat() + " ���������� ���������� ������� �� ����� " + GetFullName(arAll) + ". �, �������, ��� "+ GetSexPhrase("������� ��������","��� ���������") +" ������� �����������...", 
				""+ GetSexPhrase("�����-�� ������ ������� ��������","�����-�� ������ ������� ���������") +" ����� � ���������� �������� ������� �� ����� " + GetFullName(arAll) + ". �, ������, ��"+ GetSexPhrase("","�") +" ������"+ GetSexPhrase("","�") +" ���!", 
				"��, �������-�� ��� ���������� ������ �� ��������� ������� � �������� - �� ������� �������� " + GetMainCharacterNameDat() + " ��������� � �������� � ����� �������� ���������� �������. � �� �����, ���� ������, " + GetFullName(arAll) + " - �����!"), sti(characters[GetCharacterIndex(arAll.MayorId)].nation), 5, 1);
			DialogExit();
		break;
	}
}
