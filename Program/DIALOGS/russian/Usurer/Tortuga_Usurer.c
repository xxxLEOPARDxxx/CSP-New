// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������?"), "������ ������� �� �������� ������ ��� ������...", "�-��, ��������� ������... ����� ������ �������������?",
                          "����������, � ��������� ��������, � �� �� ������� �������...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������"), "��, ���-�� � ������� ���� �����...",
                      "�� �������, ��������...", "� �������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> ��������� ���� ��������� �������.
			if (CheckAttribute(pchar, "questTemp.PDM_PI_Rostov"))	//����� "��������"
			{
    			link.l1 = "� ���� ����������� ��� ���. � ������"+ GetSexPhrase("","�") +", ��� �� ������������� ������������ �������... ��� �� ������� �� ������ ����� �����?";
				link.l1.go = "PDM_PI_Rostov_2";
			}
			switch(pchar.questTemp.State)
            {
                case "WormEnglPlans_WormPicarder": //����������� �������, ����� �3. ������ � ������ ����������.
                    link.l2 = "��������, "+ GetSexPhrase("�����","������") +" �� ���������� ���� ���� ���������� ��������...";
                    link.l2.go = "Step_H3_1";
                break;

            }
             // <== ��������� ���� ��������� �������.
		break;
		
		case "PDM_PI_Rostov_2":
			dialog.text = "�-�-�-�! �, ��� ���! "+ GetSexPhrase("�����","�����������") +" "+pchar.name+"! ��� ���������! �����������! �� ���� ���� ����� �������� ��� ������ �������� ������!";
			link.l1 = "������, �� ��� ��������. �� ���.";
			link.l1.go = "PDM_PI_Rostov_3";
        break;
		
		case "PDM_PI_Rostov_3":
			dialog.text = "�� ����������� ��� ��������� �������, "+ GetSexPhrase("�����","�����������") +" "+pchar.name+". � ��� ����������� ����������. � ������������ ��� 45000 ������� - ����� �� ������, ��� � - ������! ���� �� ������ �����, "+ GetSexPhrase("�����","�����������") +" "+pchar.name+", �, �������, ����� ����� ����� ��� ����������! � ������, ��� �� ��� ��� ���������� ������ ����������� ������.";
			link.l1 = "� ����� ���"+ GetSexPhrase("","�") +", ��� ��� ������� �������� ��� ������.";
			link.l1.go = "PDM_PI_Rostov_4";
			AddMoneyToCharacter(pchar, 45000);
			Log_info("�� �������� ����� ����������");
			TakeItemFromCharacter(pchar, "Cursed_idol");
        break;
		
		case "PDM_PI_Rostov_4":
			dialog.text = "��-��, ��� ������� �������� ����� �� �������. �� � ������ ��������� ��� ����. � ���� ������������... �-�, � ����� �������, � ���� ��������, ��� �������� ����� ����� ��� ����������.";
            link.l1 = "(����� ����������� �����)";
			link.l1.go = "Rostovshik_5";
			bDisableFastReload = true;
			DeleteAttribute(pchar, "questTemp.PDM_PI_Rostov");
			DeleteAttribute(pchar, "questTemp.PDM_PI_Skelety_v_more");
        break;
		
		case "Rostovshik_5":
			DialogExit();
			int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
			if (Rank < 1) Rank = 1;
			int Phrase;
			Phrase = rand(2);
            if (Phrase == 0)
            {
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandit_1", "pirate_22", "man", "man", Rank, PIRATE, -1, true));
				FantomMakeCoolFighter(sld, sti(pchar.rank), 15 + MOD_SKILL_ENEMY_RATE * 4, 15 + MOD_SKILL_ENEMY_RATE * 4, "blade19", "", 20 + MOD_SKILL_ENEMY_RATE * 4);	
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
				LAi_SetActorType(sld);
				sld.dialog.filename   = "Quest/PDM/Cursed_Idol.c";
				sld.dialog.currentnode   = "Rostovshik_Fra_Off_1";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			break;
			}
            if (Phrase == 1)
            { 
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandit_1", "off_fra_1", "man", "man", Rank, PIRATE, -1, true));
				FantomMakeCoolFighter(sld, sti(pchar.rank), 15 + MOD_SKILL_ENEMY_RATE * 4, 15 + MOD_SKILL_ENEMY_RATE * 4, "blade19", "", 20 + MOD_SKILL_ENEMY_RATE * 4);	
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
				LAi_SetActorType(sld);
				sld.dialog.filename   = "Quest/PDM/Cursed_Idol.c";
				sld.dialog.currentnode   = "Rostovshik_Fra_Off_2";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			break;
			}
			if (Phrase == 2)
            { 
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Bandit_1", "skel1", "skeleton", "skeleton", Rank, PIRATE, -1, true));
				FantomMakeCoolFighter(sld, sti(pchar.rank), 20 + MOD_SKILL_ENEMY_RATE * 5, 20 + MOD_SKILL_ENEMY_RATE * 5, "blade19", "", 30 + MOD_SKILL_ENEMY_RATE * 4);	
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
				LAi_SetActorType(sld);
				sld.dialog.filename   = "Quest/PDM/Cursed_Idol.c";
				sld.dialog.currentnode   = "Rostovshik_Fra_Off_3";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			break;
			}			
		break;
		
 	 	case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat("����� ���� �������, ��� ������ � ���� �� ����. ������ - ��� ����������.", "����� �� �� ���������� ��������?...", "����� ������ ����� ����������?", "������� ����� ��������, � �� � ����� ��������� �����.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� ������?", "��, ����� �� ��...", "�����...", "�������...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
        break;
 	 	case "Step_H3_2":
			dialog.text = "���� ��������� ��������� ���� �������� ������, ��� �� ��� ������ �������. �� ��� ���, �����?";
			link.l1 = "���, � ��� ��� "+ GetSexPhrase("�����","������") +" ���� ���� ������.";
			link.l1.go = "exit";
            pchar.questTemp.Talks.Usurer = true;
            AddQuestRecord("Hol_Line_3_WormEnglishPlans", "10");
        break;



	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

