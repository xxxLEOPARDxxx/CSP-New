void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, rShip;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr;
    
	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индех в конце
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
 	// генератор ИДХ по кейсу <--
    
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "Если вы читаете эти строки, значит, где-то явный баг в коде";
			Link.l1 = "Выход";
			Link.l1.go = "exit";
			//ОЗГ
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
	    		if (pchar.questTemp.Headhunter == "halen_room")
        		{
        		    dialog.text = "Ну, пока можно и отдохнуть. Надо хорошенько выспаться...";
        			link.l1 = "...";
        			link.l1.go = "exit";
		    		AddDialogExitQuestFunction("RatHunters_Sleep");
        		}
			}
 			//===> Квесты мэра, базар после боевки на палубе
			if (CheckAttribute(pchar, "quest.DestroyPirate_PirateIsOut") || CheckAttribute(pchar,"quest.CaptainComission_CapIsOut"))
			{
				dialog.text = "Пора сваливать отсюда, пока кэп не вернулся с остальной командой...";
				Link.l1 = "...";
    			Link.l1.go = "exit";
				pchar.quest.Munity = "Deads";
			}
			// ==> Английская линейка, квест №8: в поселении буканьеров
   	    	if (pchar.questTemp.State == "ToMansfield_GoOn")
    		{
    		    dialog.text = "Дьявол!!! Что здесь произошло? Нужно попытаться найти хоть кого-нибудь живого...";
    			link.l1 = "...";
    			link.l1.go = "exit";
				Pchar.quest.ToMansfield_OutFromFort.win_condition.l1 = "location";
				Pchar.quest.ToMansfield_OutFromFort.win_condition.l1.location = "LaVega_port";
				Pchar.quest.ToMansfield_OutFromFort.win_condition = "ToMansfield_OutFromFort";
    		}
            // ==> Исп. линейка, квест №4: в спальне донны Анны
            if (pchar.questTemp.State == "Sp4Detection_toMirderPlace")
    		{
    		    dialog.text = "Хм, странное письмо. Она получила известие о прибытии человека... А кто мог ее известить? Тот, кто своим визитом не привлечет внимания слуг! Это может быть только местный житель. Мне нужно найти и допросить местного жителя, который известил донну Анну.";
    			link.l1 = "...";
    			link.l1.go = "exit";
                pchar.questTemp.State = "Sp4Detection_FoundLetter";
                AddQuestRecord("Spa_Line_4_MirderDetection", "2");
				AddQuestUserData("Spa_Line_4_MirderDetection", "sSex", GetSexPhrase("","а"));
    		}
            // ==> Французская линейка, квест №2: в таверне Тортуги
   	    	if (pchar.questTemp.State == "Fr2Letter_SeekProblems")
    		{
    		    dialog.text = "Странная парочка, однако... Пожалуй, стоит проследить, куда это они направились...";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.questTemp.Out = 1;
				SaveCurrentQuestDateParam("questTemp");
    		}
			// ==> Изабелла, нашли мертвую служанку
   	    	if (pchar.RomanticQuest == "SeekIsabella" && pchar.location == "Beliz_ExitTown")
    		{
    		    dialog.text = "Похоже, это и есть служанка Роситы... Дела Сальватора угадать легко - повсюду трупы невинных. Значит, я на верном пути.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.RomanticQuest = "FoundServantGirl";
				characters[GetCharacterIndex("ServantGirl")].LifeDay = 0;
    		}
			// ==> Квест Аскольда, обнаружение входа в пещеру к гробнице
			if (pchar.questTemp.Ascold == "Ascold_NotEnterFoundGrave")
			{
				dialog.text = "Ага, здесь явно вход куда-то. Но он закрыт плитой. Войти не удается.";
				link.l1 = "";
				link.l1.go = "exit";
			}
			//===> Квест Аскольда, попытка вскрыть лампу.
			if (pchar.questTemp.Azzy == "Azzy_IHaveLamp" && locations[reload_location_index].type == "shipyard")
			{
				dialog.text = "Ага, вот и то, что мне нужно: паяльная лампа, коловорот, ножницы для жести... Можно приступать к операции...";
				Link.l1 = "Применить инструменты.";
    			Link.l1.go = "FreedomAzzy";
			}
			//===> шебека Синяя Птица
			if (pchar.questTemp.BlueBird == "seenCarriers")
			{
				dialog.text = "Та-а-ак, слышу какой-то шум. Постою здесь, посмотрю, что будет дальше...";
				Link.l1 = "...";
    			Link.l1.go = "exit";
				AddDialogExitQuestFunction("BlueBird_endCaveDialog");
			}
		break;
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("Жаркая была схватка... Теперь можно позвать разбежавшихся трусов.", "Ха! Это было просто. А эти сухопутные крысы разбежались!");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("Хм... Что бы мне сейчас хотелось сделать?", "Чем бы заняться?");
		//Boyer add
		if(!bDisableMapEnter && !CheckAttribute(pchar,"GenQuest.CannotWait") && CheckSaveGameEnabled() == true) // 21.03.09 Warship fix Во время линейки Блада отдыхать нельзя
	    {
			Link.l4 = "Подождать 2 часа.";
	    		Link.l4.go = "TalkSelf_WasteTime";
				if(PChar.Dozor != "0" && PChar.Dozor != "END")
				{
					if(sti(PChar.Dozor.Riddle.CanInterface) == 1)
					{
							link.l4 = "Текущее задание мекахрома.";
							link.l4.go = "Dozor_MekaKhrom";
					}
				}
		}
		//End Boyer add
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
	        	// Для отдыха теперь есть отдельный интерфейс
	            if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    		{
	    			link.l1 = "Отдыхать до утра.";
	    			link.l1.go = "TalkSelf_room_day";
	    		}
	    		else
	    		{
	    			link.l1 = "Отдыхать до ночи.";
	    			link.l1.go = "TalkSelf_room_night";
	    			link.l2 = "Отдыхать до следующего утра.";
					link.l2.go = "TalkSelf_room_day";
	    		}
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "Вызвать компаньона.";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
			else 
			{   //исп.линейка, квест №6, возможность переночевать в оплаченной комнате
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "Отдыхать до утра.";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "Отдыхать до ночи.";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "Отдыхать до следующего утра.";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        /*if (CheckAttribute(pchar, "Quest.Loans") || CheckAttribute(pchar, "Quest.Deposits"))
	        {
	    		Link.l4 = "Кассовая книга.";
	    		Link.l4.go = "TalkSelf_CashBook";
			}*/
	        if (!bDisableMapEnter)//боя в море нет
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "Зачислить рабов в команду";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // захват города
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
	        {
	            Link.l6 = "Начать захват ближайшего города.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
			
			if(PChar.ColonyBuilding.Stage != "0" && PChar.ColonyBuilding.Hovernor == "")
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
					{
						Link.l18 = "Хм... Необходимо как можно скорее назначить управляющего колонии ''" + PChar.ColonyBuilding.ColonyName + "''. Быть может, я и сам"+GetSexPhrase("","а")+" справлюсь?";
						Link.l18.go = "ColonyBuilding_Hovernor_1";
					}
				}	
			}
					
			if(PChar.ColonyBuilding.Hovernor == PChar.id)
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
					{
						Link.l19 = "Перейти к делам колонии.";
						Link.l19.go = "ColonyBuilding_Hovernor";
					}
				}	
			}
			
			if(PChar.Dozor != "0" && PChar.Dozor != "END")
			{
				if(sti(PChar.Dozor.Riddle.CanInterface) == 1)
				{
		    			link.l10 = "Текущее задание мекахрома.";
		    			link.l10.go = "Dozor_MekaKhrom";
				}
			}
			
			if (!CheckAttribute(pchar,"questTemp.stels.sea")) pchar.questTemp.stels.sea = GetDataDay();
	        if (pchar.location != Get_My_Cabin() && Pchar.questTemp.CapBloodLine == false && !CheckAttribute(pchar, "DisableChangeFlagMode") && sti(pchar.questTemp.stels.sea) != GetDataDay() && CheckSaveGameEnabled() == true)
			{
				Link.l7 = "Отдать приказ на смену флага.";
				Link.l7.go = "TalkSelf_ChangeFlag";
			}
	        if(!bDisableMapEnter && Pchar.questTemp.CapBloodLine == false && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar,"GenQuest.CannotWait")) // 21.03.09 Warship fix Во время линейки Блада отдыхать нельзя
	        {
	        	Link.l8 = "Мне не мешало бы отдохнуть...";
	    		Link.l8.go = "TalkSelf_StartWait";
	    	}
			if(!CheckAttribute(pchar,"bookreadtoday") && CheckAttribute(pchar,"booktime") && !bDisableMapEnter && Pchar.questTemp.CapBloodLine == false && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar,"GenQuest.CannotWait")) // 21.03.09 Warship fix Во время линейки Блада отдыхать нельзя
	        {
	        	Link.l9 = "Почитать книгу.";
	    		Link.l9.go = "ReadBook";
	    	}
			Link.l10 = "Установить приоритет использования еды.";
	    	Link.l10.go = "food_priority";
			Link.l11 = "Использовать еду автоматически.";
	    	Link.l11.go = "autofood";
			if(CheckAttribute(pchar,"autofood"))
	        {
	        	Link.l11 = "Прекратить автоматическое использование еды.";
	    		Link.l11.go = "autofood_stop";
	    	}
			
			Link.l12 = RandPhraseSimple("Не сейчас. Нет времени.", "Некогда. Дела ждут.");
			Link.l12.go = "exit";
		break;
		
		case "autofood":
			Dialog.Text = "Введите процент, до которого должна опуститься энергия, прежде чем начать использовать еду (10-90).";
			//PChar.autofood_use
			link.l1 = "";
			Link.l1.edit = 3;
			Link.l1.go = "autofood_percentage";
		break
		
		case "autofood_stop":
			DeleteAttribute(pchar, "autofood");
			DeleteAttribute(pchar, "autofood_use");
			dialog.text = "Автоматическое использование еды отключено.";
			Link.l1 = "Всё, хватит на сегодня.";
			Link.l1.go = "exit";
		break
		
		case "autofood_percentage":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 10 || iTemp > 90)
			{
				dialog.text = "Что-то я немного не в себе сегодня... В другой раз, пожалуй.";
				link.l1 = "Дьявол!";
				link.l1.go = "exit";
				break;
			}
			PChar.autofood_use = iTemp;
			dialog.text = "Автоматическое использование еды включено.";
			pchar.autofood = true;
			link.l1 = "Славно!";
			link.l1.go = "exit";
		break;

		case "food_priority":
			dialog.text = "Какую еду стоит использовать в первую очередь?.";
			link.l1 = "Менее питательную (Фрукты, хлеб)";
			link.l1.go = "autofood_finished";
			link.l2 = "Более питательную питательную (Рыба, мясо)";
			link.l2.go = "autofood_finished_betterfood";
		break;
		
		case "autofood_finished":
			dialog.text = "Приоритет для еды установлен.";
			DeleteAttribute(pchar, "autofood_betterfood");
			link.l1 = "Славно!";
			link.l1.go = "exit";
		break;
		
		case "autofood_finished_betterfood":
			dialog.text = "Приоритет для еды установлен.";
			PChar.autofood_betterfood = true;
			link.l1 = "Славно!";
			link.l1.go = "exit";
		break;
		
		case "ReadBook":
			Dialog.Text = "Ну что-ж, почитал пару часов...";
			WasteTime(4);
			pchar.booktime = sti(pchar.booktime) - 1;
			pchar.bookreadtoday = true;
			if (sti(pchar.booktime) <= 0)
			{
				AddCharacterExpToSkill(pchar, pchar.booktype, sti(pchar.bookbonus));
				int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
				Log_Info(GetFullName(pchar) + " изучил книгу ''"+LanguageConvertString(idLngFile, pchar.bookname)+"'' и увеличил навык ''"+XI_ConvertString(pchar.booktype)+"''");
				LanguageCloseFile(idLngFile);
				DeleteAttribute(pchar,"booktime");
				DeleteAttribute(pchar,"booktime.full");
				DeleteAttribute(pchar,"bookbonus");
				DeleteAttribute(pchar,"booktime");
				DeleteAttribute(pchar,"booktype");
				DeleteAttribute(pchar,"bookreadtoday");
				string sEquipItem = GetCharacterEquipByGroup(pchar, BOOK_ITEM_TYPE);
				RemoveCharacterEquip(pchar, BOOK_ITEM_TYPE);
				RemoveItems(pchar, sEquipItem, 1);
			}
			Link.l6 = "Всё, хватит на сегодня.";
			Link.l6.go = "exit";
		break
		
		case "TalkSelf_ChangeFlag":
			Dialog.Text = "Какой флаг мне необходим на данный момент? Его смена займёт 1 час.";
			if (IsCharacterPerkOn(pchar,"FlagPir") && sti(pchar.nation) != 4) {Link.l1 = "Поднять пиратский флаг."; Link.l1.go = "TalkSelf_ChangeFlagPir";}
			if (IsCharacterPerkOn(pchar,"FlagEng") && sti(pchar.nation) != 0) {Link.l2 = "Поднять английский флаг."; Link.l2.go = "TalkSelf_ChangeFlagEng";}
			if (IsCharacterPerkOn(pchar,"FlagFra") && sti(pchar.nation) != 1) {Link.l3 = "Поднять французский флаг."; Link.l3.go = "TalkSelf_ChangeFlagFra";}
			if (IsCharacterPerkOn(pchar,"FlagSpa") && sti(pchar.nation) != 2) {Link.l4 = "Поднять испанский флаг."; Link.l4.go = "TalkSelf_ChangeFlagSpa";}
			if (IsCharacterPerkOn(pchar,"FlagHol") && sti(pchar.nation) != 3) {Link.l5 = "Поднять голландский флаг."; Link.l5.go = "TalkSelf_ChangeFlagHol";}
			Link.l6 = RandPhraseSimple("Не сейчас. Нет времени.", "Некогда. Дела ждут.");
			Link.l6.go = "exit";
		break;
		
		case "TalkSelf_ChangeFlagPir":
			Log_Info("Выбран пиратский флаг");
			FlagsProcess1(4);
			DialogExit_Self();
		break;
		
		case "TalkSelf_ChangeFlagEng":
			Log_Info("Выбран английский флаг");
			FlagsProcess1(0);
			DialogExit_Self();
		break;
		
		case "TalkSelf_ChangeFlagFra":
			Log_Info("Выбран французский флаг");
			FlagsProcess1(1);
			DialogExit_Self();
		break;
		
		case "TalkSelf_ChangeFlagSpa":
			Log_Info("Выбран испанский флаг");
			FlagsProcess1(2);
			DialogExit_Self();
		break;
		
		case "TalkSelf_ChangeFlagHol":
			Log_Info("Выбран голландский флаг");
			FlagsProcess1(3);
			DialogExit_Self();
		break;
		
		// Мекахром смотрим
		case "Dozor_MekaKhrom":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchMekakhrom();
		break;
		
		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//Boyer add
		case "TalkSelf_WasteTime":
			NextDiag.CurrentNode = NextDiag.TempNode;
			WasteTime(2);
			DialogExit_Self();
		break;
		//End Boyer add
		//  захват города
		case "TalkSelf_TownAttack":
            bOk = (GetPartyCrewQuantity(Pchar, true) >= 500) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "Начать захват, конечно, можно, да вот только корабль под залпами форта долго не продержится. И десант высадить не успеем.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
	                if (pchar.location == "Panama_ExitTown")
					{
						Dialog.Text = "Не-е-ет, я не сумасшедший. Это же Панама! Взять ее НЕВОЗМОЖНО!!! Надо валить отсюда, а то точно дождусь черной метки...";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						Dialog.Text = "Напасть на город " + GetCityName(chr.City) + ".";
		    			Link.l1 = "К оружию!";
		    			Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "Отставить!";
		    			Link.l2.go = "exit";
					}
	    		}
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "Эх! Команды маловато, нужно хотя бы 500 человек.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "Не разбредаться! Продолжаем атаку!";
					Link.l2 = "...";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // для сухопутных
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "Никто из рабов не хочет идти в команду.";
	            Link.l1 = "Ну и не нужно!";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "На корабле нет места для новых матросов.";
	                Link.l1 = "Эх! Нужно переместить часть экипажа на другой корабль.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "В команду желают пойти " + pchar.GenQuest.SlavesToCrew+ " рабов. Взять их?";
	                Link.l1 = "Да";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "Нет";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
	        if (CheckOfficersPerk(pchar, "IronWill"))
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
	        }
	        else
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
	        }
	        // падение опыта -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "Теперь этот отличный корабль мой, и я здесь капитан! Жаль, пришлось вырезать всю команду.";
			Link.l1 = "Пора на берег...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "Кого из компаньонов вызвать?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "В другой раз.";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		// Квест Аскольда, освобождение Аззи.
		case "FreedomAzzy":
			chr = GetCharacter(NPC_GenerateCharacter("Azzy", "Azzy", "man", "man", 22, PIRATE, -1, false));
			chr.name = "демон";
			chr.lastname = "Аззи";
			chr.Dialog.Filename = "Quest\Azzy_dialog.c";
			GiveItem2Character(chr, "blade28");// сабля Моргана
			chr.equip.blade = "blade28";
			chr.rank 	= 100;
			chr.reputation = "0";
			SetSelfSkill(chr, 100, 100, 100, 100, 100);
			SetShipSkill(chr, 100, 100, 100, 100, 100, 100, 100, 100, 100);
			LAi_SetImmortal(chr, true);
			LAi_SetActorType(chr);
			LAi_SetLoginTime(chr, 0.0, 24.0);
			LAi_SetHP(chr, 10000.0, 10000.0);
			chr.greeting = "Gr_Azzy";
			ChangeCharacterAddressGroup(chr, pchar.location, "officers", "reload1_1");
			DoQuestCheckDelay("Ascold_AzzyIsFree", 4.0);
			pchar.questTemp.Azzy = "Azzy_Freedom";
			DialogExit();
		break;	
		
		// Сами хотим колонией управлять.
		case "ColonyBuilding_Hovernor_1":
			dialog.Text = "Или же найти помошника?";
			Link.l1 = "Пожалуй, я и сам"+GetSexPhrase("","а")+" справлюсь.";
			Link.l1.go = "ColonyBuilding_Hovernor_2";
			Link.l2 = "Я передумал.";
			Link.l2.go = "Exit";
		break;
	        case "ColonyBuilding_Hovernor_2":
		        bQuestDisableMapEnter = true;
		        Log_SetStringToLog("Так как вы стали губернатором, теперь вы не можете покидать пределы острова.");
		        
			PChar.ColonyBuilding.Hovernor = PChar.id;
			DialogExit_Self();
	        break;
	
		case "ColonyBuilding_Hovernor":
			dialog.Text = "Просмотреть текущее состояние дел колонии " + PChar.ColonyBuilding.ColonyName + ".";
			Link.l1 = "Нужно детально изучить текущее состояние дел.";
			Link.l1.go = "ColonyBuilding_Hovernor_3";
			Link.l2 = "Что-то мне не по душе это сухопутная жизнь.";
			Link.l2.go = "ColonyBuilding_Hovernor_4";
			Link.l3 = "Ничего не предпринимать.";
			Link.l3.go = "Exit";
		break;
	
		case "ColonyBuilding_Hovernor_3":
			dialog.Text = "Хм... О каких именно делах я хочу осведомиться?";
			Link.l1 = "Состояния колонии и её финансовые возможности.";
			Link.l1.go = "ColonyBuilding_Hovernor_3_1";
			Link.l2 = "Боевая готовность гарнизона и здоровье жителей.";
			Link.l2.go = "ColonyBuilding_Hovernor_3_2";
			Link.l3 = "Название колонии и внешний вид солдат.";
			Link.l3.go = "ColonyBuilding_Hovernor_3_3";
			Link.l4 = "Ничего не предпринимать.";
			Link.l4.go = "Exit";
		break;

		case "ColonyBuilding_Hovernor_3_1":
			DialogExit_Self();
			LaunchColony();
		break;

		case "ColonyBuilding_Hovernor_3_2":
			DialogExit_Self();
			LaunchColonyLandGuard();
		break;

		case "ColonyBuilding_Hovernor_3_3":
			DialogExit_Self();
			LaunchColonyBuilding(true, false);
		break;

		case "ColonyBuilding_Hovernor_4":
			dialog.Text = "Уверен"+GetSexPhrase("","а")+" ли я, что не хочу управлять своей колонией?";
			Link.l1 = "Да.";
			Link.l1.go = "ColonyBuilding_Hovernor_5";
			Link.l2 = "Нет, я передумал"+GetSexPhrase("","а")+". Моё призвание - губернатор!";
			Link.l2.go = "Exit";
		break;
		
		case "ColonyBuilding_Hovernor_5":
			PChar.ColonyBuilding.Hovernor = "";
		        bQuestDisableMapEnter = false;
		        Log_SetStringToLog("Перестав быть губернатором вы вновь можете быть свободным капитаном!");
			dialog.Text = "Замечательно! Быть сухопутной крысой не мой удел.";
			Link.l1 = "...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "TalkSelf_Main";
		break;
		
		// Мекахром смотрим
		case "Dozor_MekaKhrom":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchMekakhrom();
		break;
		
	}
}

void  DialogExit_Self()
{
    DialogExit();
	locCameraSleep(false); //boal
}


void FlagsProcess1(int nation)
{
	// boal 04.04.2004 -->
	bool bTmpBool = true;
	int i, cn;
	ref chref;
	

	Sea_ClearCheckFlag(); // сбросить всем в море проверку смотрения на флаг.
	DoQuestFunctionDelay("FreeChangeFlagMode", 15.0); // ролик + запас
	
	switch (nation)
	{
    	case ENGLAND:	EnglandProcess();	break;
    	case FRANCE:	FranceProcess();	break;
    	case SPAIN:		SpainProcess();		break;
    	case PIRATE:	PirateProcess();	break;
    	case HOLLAND:	HollandProcess();	break;
	}
}

void PirateProcess()
{
	pchar.DisableChangeFlagMode = true;
    //DoQuestCheckDelay("pir_flag_rise", 1.0);
    PChar.GenQuest.VideoAVI        = "Pirate";
    PChar.GenQuest.VideoAfterQuest = "pir_flag_rise";
	
    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void EnglandProcess()
{
	pchar.DisableChangeFlagMode = true;
    //DoQuestCheckDelay("eng_flag_rise", 1.0);
    PChar.GenQuest.VideoAVI        = "England";
    PChar.GenQuest.VideoAfterQuest = "eng_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void FranceProcess()
{
	pchar.DisableChangeFlagMode = true;
    PChar.GenQuest.VideoAVI        = "France";
    PChar.GenQuest.VideoAfterQuest = "fra_flag_rise";
	
    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void SpainProcess()
{
	pchar.DisableChangeFlagMode = true;
    PChar.GenQuest.VideoAVI        = "Spain";
    PChar.GenQuest.VideoAfterQuest = "spa_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void HollandProcess()
{
	pchar.DisableChangeFlagMode = true;
    PChar.GenQuest.VideoAVI        = "Holland";
    PChar.GenQuest.VideoAfterQuest = "hol_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

