
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // ����� ������� �� ������� -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // ����� ������� �� ������� <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			if (CheckChit() == true)
                {
					dialog.text = RandPhraseSimple(RandPhraseSimple("��� �� �� ������, ��� ������� ���� ��� �� ���� �����... ���� ��� ��� ����������: ���� �����������, �� ����� ��������� ��������� �� ��������. ����������!","�-�-�, ���� � ����! �� ��� �� ������� ��� ������! � ��� ��� ������ ������, ��������, �� �� ������ ������!"), RandPhraseSimple("�����, ��� �������, ������ ������: ���� ������� ��������, ��� ������������� ��������? ���� ��������� �� ���� ��������� �� ������, ��� ��� ���������� ������ ������� �������... ��������� ������, ������!","�� ��, �� ��, ����� ��� ���������� ���������� ���������! ��, ���, ��� �� ����������...���! �� ����������, � ���������, ��-��-��! ����������, �����."));
            		link.l1 = LinkRandPhrase("��, �� ���� ������� ���� ��������. ���� ������ �����.","�� ���� �������? � ���� ����-���� ���� �������... �����-�����, �����.","���! � ��� �������� - ������ ���� ��� ������...");
            		link.l1.go = "exit";
					break;
                }
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "� �������, ����� �� ���� ���� �������. �� ����� ������� �����, �� ��������� ��������...";
					link.l1 = "������, �� ���� ���� �����������...";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "� ����� ���������, ��� ��� �� ���������� ���� �������, ����� ���. � �� ��������� ��� �� ����� �����...";
					link.l1 = "� ��� ����������, ��� �������� �� ����? " + pchar.questTemp.different.FackWaitress.Name + ", �������...";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "������ ���, �������. ����� ����� - ����������� ���...";
					link.l1 = "�����������!";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "� ��� �� ����, �� ����������� �� ���...";
					link.l1 = "��� ��� ������?!!";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "������, "+ GetSexPhrase("���������","���������") +", � ������. ������� ���� ��� ������� - �� ������ ������� ���� ��� ���������!";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "����������, �������, �� ����������� �������! ����� ��� ��� ������ �������� �������!";
					link.l1 = ""+ GetSexPhrase("���... ����� � �� ���������.","� ���, ������ �� ���������?") +"";
					link.l1.go = "exit";
				break;

				case 2:
					dialog.text = ""+ GetSexPhrase("�, �������! �� ������ �� ������� � ��� ������� �������? � �� ����� ����������, �� ...","��������������, �������. ��������� ������� ������� ����� ������ ����.") +"";
					link.l1 = ""+ GetSexPhrase("���, ������ � �����! ����� � ������ ���!","C������, �������.") +"";
					link.l1.go = "exit";
					// boal 27.03.2004 -->
					if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && pchar.questTemp.piratesLine != "Soukins_toPuertoPrincipe" && PChar.sex != "woman" && pchar.questTemp.piratesLine != "Soukins_seekRings" && Pchar.questTemp.CapBloodLine != true && pchar.GenQuest.EncGirl != "HorseToTavern"/*&& npchar.city != "Villemstad"*/)
					{
						link.l2 = "� ���������� �������������, ������!";
						link.l2.go = "Love_1";
					}
					// boal 27.03.2004 <--
				break;

				case 3:
					dialog.text = "���� �� ������ ���-���� �������� - ����������, ����������, � �������. �� ����� �� �������.";
					link.l1 = "������� �� �����.";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "���� �� ������ ��� ������� ��������� � ��������� �������� - ������� ������� �� ����. ������� � ����� ���� ���� �� �������� ��� ���.";
					link.l1 = "���������.";
					link.l1.go = "exit";
				break;
			}			
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City")) //����� ���� ��� ������ ������
			{
				link.l4 = "����� ���, "+ GetSexPhrase("���������","�������") +", �� �� �������� ����� ������ ��������������� � ��������� �����?";
				if (pchar.GenQuest.SeekSpy.City == "1")
				{
					link.l4.go = "SeekSpy_Seen";
				}
				else
				{
					link.l4.go = "SeekSpy_NotSeen";
				}
			}			
			link.l9 = "� ���� ������ ���� ���� ��������.";
			link.l9.go = "quests";//(���������� � ���� ������)
		break;
		
        case "Love_1":
			dialog.text = "����� ������ �����������. ����� ������� � ��� � �������. ��� ���� � ��� ����. � ��������� �������� � ���� �������...";
			link.l1 = "��! ��� ������, ��������! ���!";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //����������� ���������� �� ���������� �� ����. ����
			//����, ��� �������, ���� ������ ������� �� 0. �� �� �������� ������� ��� ������� �� �������
			pchar.questTemp.different.FackWaitress.Kick = cRand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //�������� ��� ����������
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//������ ����� ����������
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterReputation(pchar, -1);
		break;
        case "Love_IDN":
			dialog.text = "��� ����� ������ �� ��������, ���������... ��������, � ���� ����� ���.";
			link.l1 = "������...";
			link.l1.go = "exit";
		break;
        case "Love_IDN_1":
			dialog.text = "��� ���, ���������� ������. � �� ����, ��� ���� ������! � ������ ���������� �� ��� - ������ ������, � �� ������� �� ��������� � ������!";
			link.l1 = "�����, �� ���� ������... ��� �����.";
			link.l1.go = "Love_IDN_2";
		break;
        case "Love_IDN_2":
			dialog.text = "��� ������, ��� ��� �����. ������ ������ ����� � ����������.";
			link.l1 = "�-��, ����������...";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "�� ��������?";
			link.l1 = "�-�-�.";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "��� �����? ����� ������?";
			link.l1 = "��� �, ���� ������?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "��� �� ������ �� �������? ���� ��, ��� ��� ��������?";
			link.l1 = "���? ��... ��� ������... ��� ������?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "������ ��� �����? ������, ���������� �����, �������� ������� � ����.";
			link.l2 = "�����, ��� �������, �� �������.";
			link.l2.go = "exit";
		break;
		//==> eddy. ����� ����, ������� �� �������� �� ������
		case "SeekSpy_Seen":
			dialog.text = NPCStringReactionRepeat("�� ���� ����... ���������������?.. ����, �������, �������, ���� �����. �� ���� ������� ���������, �� �� ������ ����������� � ��������� �������, �� � �� ������ � ��� ������ � ������. ����� �� ��� ���� �� ���������, � ��� � ������ �����.", 
				"��, �� �� �� �������� ��� ���� ���! � ������ ������ ������� �� ����.", "����� �� �� �����... � ��� ��� ���� �������.", "������� ����� ���������� ���� � �� ��?! �����, ���� ���-������ ������ �����?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������, ����, "+ GetSexPhrase("���������","�������") +". ��� ��, ����� ������ ����� ����.", "��? �� �����...",
                      "��, �� ��...", "������"+ GetSexPhrase(", ���������","") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "SeekSpy_NotSeen":
			dialog.text = NPCStringReactionRepeat("���, ������ ������ �� ������, ����� �������������� ����� ���.", 
				"��, �� �� �� �������� ��� ���� ���! � ������ ������ ������� �� ����.", "����� �� �� �����... � ��� ��� ���� �������.", "������� ����� ���������� ���� � �� ��?! ����� ���� ���-������ ������ �����?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("�������, ����, "+ GetSexPhrase("���������","�������") +". ��� ��, ����� ������ ����� ����.", "��? �� �����...",
                      "��, �� ��...", "������"+ GetSexPhrase(", ���������","") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
}
 
