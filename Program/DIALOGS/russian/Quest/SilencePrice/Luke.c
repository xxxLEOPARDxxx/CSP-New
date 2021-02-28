void ProcessDialogEvent()
{
    ref NPChar;
    ref Pchar = GetMainCharacter();
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
    switch (Dialog.CurrentNode)
    {
    case "Exit":
        NextDiag.CurrentNode = NextDiag.TempNode;
        DialogExit();
    break;
    case "First Time":
        if (!isMainCharacterPatented())
        {
            Log_info("� ��� ��� �������");
            dialog.text = "�������, ���� �����" + GetSexPhrase(".", "�.");
            link.l1 = "�����, �����, �� ��������.";
            link.l1.go = "exit";
        }
        else
        {
            dialog.text = "�! ���� � ����? " + GetFullName(Pchar) + " ����������� ��������! ��� ��� �������!";
            link.l1 = "�-�... �����, � ��� �� �����.";
            link.l1.go = "StartQuest_1";
            SetCharacterPerk(NPChar, "BasicDefense");
            SetCharacterPerk(NPChar, "AdvancedDefense");
            SetCharacterPerk(NPChar, "CriticalHit");
            SetCharacterPerk(NPChar, "Ciras");
            SetCharacterPerk(NPChar, "SwordplayProfessional");
            SetCharacterPerk(NPChar, "Tireless");
            SetCharacterPerk(NPChar, "HardHitter");
            SetCharacterPerk(NPChar, "BladeDancer");
            SetCharacterPerk(NPChar, "Sliding");
            SetCharacterPerk(NPChar, "Gunman");
            SetCharacterPerk(NPChar, "GunProfessional");
            SetCharacterPerk(NPChar, "Turn180");
            SetCharacterPerk(NPChar, "SailingProfessional");
            SetCharacterPerk(NPChar, "SailsMan");
            SetCharacterPerk(NPChar, "Doctor1");
            SetCharacterPerk(NPChar, "Doctor2");
            AddBonusEnergyToCharacter(NPChar, 50);
        }
    break;
    case "StartQuest_1":
        dialog.text = "�� ��� �� �, ���! �� � ����� ������ ��� ������ ����� �����������.";
        link.l1 = "���� ������! ���! ��� �� ���������, �������!";
        link.l2 = "���... ��� ��� ���. �� �� ������� �� ����, ��������, �� ����� �� �������";
        link.l1.go = "StartQuest_3";
        link.l2.go = "exit";
    break;
    case "StartQuest_3":
        dialog.text = "���! � � �� ����� ������ � ��� �����, � ��� �� ��. ������ � �������, �������, ���������!";
        link.l1 = "��! � ��������!";
        AddDialogExitQuest("Taverna");
        SetCharacterPerk(NPChar, "FastReload");
        SetCharacterPerk(NPChar, "HullDamageUp");
        SetCharacterPerk(NPChar, "SailsDamageUp");
        SetCharacterPerk(NPChar, "CrewDamageUp");
        SetCharacterPerk(NPChar, "CriticalShoot");
        SetCharacterPerk(NPChar, "LongRangeShoot");
        SetCharacterPerk(NPChar, "CannonProfessional");
        SetCharacterPerk(NPChar, "LongRangeGrappling");
    break;
    case "StartQuest_4":
        dialog.text = GetFullName(Pchar) + " ��� ��, " + GetSexPhrase("��������", "�������") + "? ��������, ��� ���� ���� �������?";
        link.l1 = "� ������ ���� �������������" + GetSexPhrase("�", "��") + ", �� �� ���� ������ �������, �� �� ������, � ����� � �� ���� ������.";
        link.l1.go = "StartQuest_6";
    break;
    case "StartQuest_6":
        dialog.text = "��� ��� ���. ����� � ���� ��������� �����������, ����� �� ��� ������� � ������ �� ������. ��� ����� ���� �� ��������. ���������, ������� �� ������ ���������, ���� ����� ������ ��������. ��... �� ���� ������� ����... ����� ������ �� ��, ��� �� �������� ����!";
        link.l1 = "��, �� ��, ����� ����� ����� �������. � ���� ����� ��� ����, ���� �� �� �������� ������ ���������! ������!";
        link.l1.go = "StartQuest_7";
        SetCharacterPerk(NPChar, "MusketsShoot");
        SetCharacterPerk(NPChar, "GrapplingProfessional");
        SetCharacterPerk(NPChar, "BasicBattleState");
        SetCharacterPerk(NPChar, "AdvancedBattleState");
        SetCharacterPerk(NPChar, "ShipDefenseProfessional");
        SetCharacterPerk(NPChar, "ShipSpeedUp");
        SetCharacterPerk(NPChar, "ShipTurnRateUp");
        SetCharacterPerk(NPChar, "StormProfessional");
    break;
    case "StartQuest_7":
        dialog.text = "� ������ � ���� � ������� ���� ����, � ������... ������, ��� �� ������ ���� �������, ������� ������� �� ��������, � ��� �����...";
        link.l1 = "�� ���, ����������, ������, ���� �����.";
        link.l1.go = "GiveQuest";
    break;
    case "GiveQuest":
        string spawn_max;
        int Gorod;
        NPChar = characterFromID("Old Friend");
        if (Pchar.PatentNation == "eng")
        {
            while (0 < 1)
            {
                Gorod = rand(5);
                if (Gorod == 0)
                {
                    spawn_max = "PortRoyal_tavern";
                    dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ���� ����. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                    link.l1 = "��! ���� ������ ������! ����� ������!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                    AddQuestUserData("Silence_Price", "sCity2", "���� ����");
                    AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
                if (Gorod == 1)
                {
                    spawn_max = "SentJons_tavern";
                    dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ����-�����. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                    link.l1 = "��! ���� ������ ������! ����� ������!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                    AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                    AddQuestUserData("Silence_Price", "sCity2", "����-�����");
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
                if (Gorod == 2)
                {
                    spawn_max = "Charles_tavern";
                    dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ���������. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                    link.l1 = "��! ���� ������ ������! ����� ������!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                    AddQuestUserData("Silence_Price", "Friendname", NPChar.name + "a " + NPChar.lastname + "�");
                    AddQuestUserData("Silence_Price", "sCity2", "���������");
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
                if (Gorod == 3)
                {
                    spawn_max = "Bridgetown_tavern";
                    dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ���������. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                    link.l1 = "��! ���� ������ ������! ����� ������!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                    AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                    AddQuestUserData("Silence_Price", "sCity2", "���������");
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
                if (Gorod == 4)
                {
                    spawn_max = "Portspein_tavern";
                    dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ���� �� �����. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                    link.l1 = "��! ���� ������ ������! ����� ������!";
                    link.l1.go = "StartQuest_8";
                    SetQuestHeader("Silence_Price");
                    AddQuestRecord("Silence_Price", "1");
                    AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                    AddQuestUserData("Silence_Price", "sCity2", "���� �� �����");
                    AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                    AddDialogExitQuest("AfterDialog");
                    TakeItemFromCharacter(NPChar, "Lukes_letter");
                    GiveItem2Character(Pchar, "Lukes_letter");
                    PlaySound("Interface\important_item.wav");
                    SpawnMaks(spawn_max);
                break;
                }
            }
        }
        else
        {
            if (Pchar.PatentNation == "hol")
            {
                while (0 < 1)
                {
                    Gorod = rand(3);
                    if (Gorod == 0)
                    {
                        spawn_max = "Villemstad_tavern";
                        dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ����������. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                        link.l1 = "��! ���� ������ ������! ����� ������!";
                        link.l1.go = "StartQuest_8";
                        SetQuestHeader("Silence_Price");
                        AddQuestRecord("Silence_Price", "1");
                        AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                        AddQuestUserData("Silence_Price", "sCity2", "����������");
                        AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                        AddDialogExitQuest("AfterDialog");
                        TakeItemFromCharacter(NPChar, "Lukes_letter");
                        GiveItem2Character(Pchar, "Lukes_letter");
                        PlaySound("Interface\important_item.wav");
                        SpawnMaks(spawn_max);
                    break;
                    }
                    if (Gorod == 1)
                    {
                        spawn_max = "Marigo_tavern";
                        dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ������. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                        link.l1 = "��! ���� ������ ������! ����� ������!";
                        link.l1.go = "StartQuest_8";
                        SetQuestHeader("Silence_Price");
                        AddQuestRecord("Silence_Price", "1");
                        AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                        AddQuestUserData("Silence_Price", "sCity2", "������");
                        AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                        AddDialogExitQuest("AfterDialog");
                        TakeItemFromCharacter(NPChar, "Lukes_letter");
                        GiveItem2Character(Pchar, "Lukes_letter");
                        PlaySound("Interface\important_item.wav");
                        SpawnMaks(spawn_max);
                    break;
                    }
                    if (Gorod == 2)
                    {
                        spawn_max = "FortOrange_tavern";
                        dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ����-�����. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                        link.l1 = "��! ���� ������ ������! ����� ������!";
                        link.l1.go = "StartQuest_8";
                        SetQuestHeader("Silence_Price");
                        AddQuestRecord("Silence_Price", "1");
                        AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                        AddQuestUserData("Silence_Price", "sCity2", " ����-�����");
                        AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                        AddDialogExitQuest("AfterDialog");
                        TakeItemFromCharacter(NPChar, "Lukes_letter");
                        GiveItem2Character(Pchar, "Lukes_letter");
                        PlaySound("Interface\important_item.wav");
                        SpawnMaks(spawn_max);
                    break;
                    }
                }
            }
            else
            {
                if (Pchar.PatentNation == "fra")
                {
                    while (0 < 1)
                    {
                        Gorod = rand(4);
                        if (Gorod == 0)
                        {
                            spawn_max = "FortFrance_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ���� �� �����. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "���� �� �����");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 1)
                        {
                            spawn_max = "FortFrance_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ���� �� �����. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "���� �� �����");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 2)
                        {
                            spawn_max = "BasTer_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ��� ���. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1"); 
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "��� ���");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 3)
                        {
                            spawn_max = "Tortuga_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� �� �������. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "�������");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                    }
                }
                else
                {
                    while (0 < 1)
                    {
                        Gorod = rand(9);
                        if (Gorod == 0)
                        {
                            spawn_max = "Caracas_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � �������. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "�������");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 1)
                        {
                            spawn_max = "Cumana_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ������. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "������");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 2)
                        {
                            spawn_max = "Cartahena_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ���������. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "���������");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 3)
                        {
                            spawn_max = "Maracaibo_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ���������. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "���������");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 4)
                        {
                            spawn_max = "PortoBello_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ����� �����. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "����� �����");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 5)
                        {
                            spawn_max = "SantaCatalina_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ����� ��������. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "����� ��������");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 6)
                        {
                            spawn_max = "Beliz_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � �����. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "�����");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 7)
                        {
                            spawn_max = "SantoDomingo_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ����� �������. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1"); 
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "����� �������");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 8)
                        {
                            spawn_max = "SanJuan_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ��� ����. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1")
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "��� ����");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                        if (Gorod == 9)
                        {
                            spawn_max = "Santiago_tavern";
                            dialog.text = "����������, ������� ������ �� ���� ��� ����� ����� � ��������. �� ������ ���, ���� �������� �� ��������! ���������, �� ������� ��� � �������. ����� ����� ����������� �����, �����, ��� �� �� ���� �������.";
                            link.l1 = "��! ���� ������ ������! ����� ������!";
                            link.l1.go = "StartQuest_8";
                            SetQuestHeader("Silence_Price");
                            AddQuestRecord("Silence_Price", "1");
                            AddQuestUserData("Silence_Price", "sSex", GetSexPhrase("", "�"));
                            AddQuestUserData("Silence_Price", "sCity2", "��������");
                            AddQuestUserData("Silence_Price", "FriendName", NPChar.name + "a " + NPChar.lastname + "�");
                            AddDialogExitQuest("AfterDialog");
                            TakeItemFromCharacter(NPChar, "Lukes_letter");
                            GiveItem2Character(Pchar, "Lukes_letter");
                            PlaySound("Interface\important_item.wav");
                            SpawnMaks(spawn_max);
                        break;
                        }
                    }
                }
            }
        }
        break;
    case "StartQuest_8":
        dialog.text = "��, ������ ������ �� ������! ������� �������! ����� ���� � �������� � ��������� �����! ������!";
        link.l1 = "������!";
        NextDiag.TempNode = "Story1";
        link.l1.go = "Exit";
    break;
    case "Story1":
		dialog.text="��� �� �� �����? ���� ���� � ����!";
		link.l1="������, ���. ��� ���� ������� ����� ���������? � �����, ��� � ��"+GetSexPhrase("��","��")+" ��"+GetSexPhrase("��","��")+". ��������, ��� ����� ���������?";
		link.l1.go="Story2";
	break;
	case "Story2":
		dialog.text="��, � ���� ��� �� ��������. ��, ������. �����, ����� ���� ��� �� ��������� � �������, �������� ����� ��� ����� � ����� � � ���� ����� ������� ���. ����� ������ ������, ���� ����� ����� ��������� �������. ��� �� ����� ���� �������, �� ����� � ����... ";
		link.l1="��� �� ���� ������?";
		link.l1.go="Story3";
	break;
	case "Story3":
		dialog.text="��� ������. ��� �� ������ ����, � �������� ������� � ���� �������� � ��������� �� ����. ������� ���� �������� � �������� ��������� � �� �������� ��������� �� �������.";
		link.l1="��� �� �� �������� �� ��� ��?";
		link.l1.go="Story4";
	break;
	case "Story4":
		dialog.text="��, � ������, ��� �������� �� ����, ����� �� ��������� �� ������������. ������ �� ����� ��� ����� ���������.";
		link.l1="������, ���, ������� �� �������� ���� ��������";
		link.l1.go="exit";
		AddQuestRecord("Silence_Price","3");
		AddQuestUserData("Silence_Price","sSex",GetSexPhrase("","�"));
		NextDiag.TempNode="Pause";
	break;
    case "Pause":
        dialog.text = "�, ���� � ����! ������������, ������.";
        link.l1 = "��, ��� �. ���, �������, � ���� ����.";
        link.l1.go = "exit";
    break;
	case "SecondQuest_1":
		dialog.text="�, �� ������"+GetSexPhrase("��","���")+"! ��� ��� ������? �� � ����� ������ ��������?";
		link.l1="��, ��� ������. �� �������� ��� ������ ����� ��������, �������� ����, �� ����� ��������� ������.";
		link.l1.go="SecondQuest_2";
	break;
	case "SecondQuest_2":
		dialog.text="������, ��� ����� ����... ";
		link.l1="� ��! (���������� ����� � ����������)";
		link.l1.go="exit";
		NextDiag.TempNode="Pause";
	break;
	}
}
