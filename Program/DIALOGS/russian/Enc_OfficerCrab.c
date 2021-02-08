// BOAL ����� ������ ������� � ���������� 21/06/06
													  
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    sld;
	string attr, attrLoc;
	int    iTemp, iTax, iFortValue;
	
	switch(Dialog.CurrentNode)
	{
        case "hired":
			
			dialog.text = "(������ ���� ����������� ��� �����������, ������ �������)";
			if (isOfficer(Npchar)) // �������� ��� �������, ��� �������� ���
			{
	            Link.l2 = "������ ��� ������!";
	            Link.l2.go = "stay_follow";
            }
			Link.l4 = "���� ��� ���������, ��������. ����������� � �����, � ������ ������.";
			Link.l4.go = "AsYouWish";
			
            Link.l9 = "������. ������.";
            Link.l9.go = "exit";
			Diag.TempNode = "hired";
        break;

		case "exit":
			Diag.TempNode = "hired";
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "AsYouWish":
			dialog.text = "(���� ������� ������ �������� �� �����.)";
			if (isOfficer(Npchar)) // �������� ��� �������, ��� �������� ���
	            Link.l2 = "������, ��� ��� ������������� �������. ��� ���� ������� ������ ��� ��� ������� �����������.";
	            Link.l2.go = "exit_fire";
			Link.l4 = "������, � ���������" + GetSexPhrase("","�")+ ". �� ����, ��� �� ���� �����...";
			Link.l4.go = "exit";
			Diag.TempNode = "hired";
        break;
		
		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
	
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "(���� ������ ��������� ����, ����� ��������, ��� �� ����������� ��� �������.)";
            Link.l1 = "���� �����!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "������ �� ���� � �� ��������!";
            Link.l2.go = "Boal_Follow";

		break;

        // boal 05.09.03 offecer need to go to abordage -->
	      case "Boal_Stay":
             //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
             //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
              Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
              AddDialogExitQuestFunction("LandEnc_OfficerStay");
		      Diag.TempNode = "hired";
		      dialog.text = "(�����, ��� �� �� �������� ������ �������, �� �� ���������� ���������� ������.)";
		      Link.l1 = "������.";
		      Link.l1.go = "Exit";
		      Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	      break;
		  
	      case "Boal_Follow":
		      SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		      Diag.TempNode = "hired";
		      dialog.text = "(���� ������� ������� � ���� ��������.)";
		      Link.l1 = "������.";
		      Link.l1.go = "Exit";
	      break;	      
		  
		  case "Fired":
		      SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
			  Diag.TempNode = "Fired";	
		      dialog.text = "(���� ������ ������� ��� �����.)";
		      Link.l1 = "�� �������� �� �������, ������ � ��� ��������"+ GetSexPhrase("","�")+ ".";
		      Link.l1.go = "Exit";
	      break;
        // boal 05.09.03 offecer need to go to abordage <--
		// <-- ��������������� �������� ����������
	}
}