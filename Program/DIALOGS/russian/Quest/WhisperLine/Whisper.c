void ProcessDialogEvent()
{
	ref locLoad = &locations[reload_location_index];
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	bool hungry = true;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":

			//dialog.text = "Ошибка";
			link.l1 = "...";
			link.l1.go = "Exit";
			npchar.quest.meeting = "1";
		
			if (npchar.id == "CrazyScientist")
			{
				dialog.text = "А ну, стой!";
				link.l1.go = "CS";
			}
			if (npchar.id == "FinalBot")
			{
				dialog.text = "(Вы слишком поздно замечаете бота. Уже после того, как услышали звук выстрела.)";
				LAi_LocationFightDisable(locLoad, false);
				DeleteAttribute(locLoad, "box1");
				DeleteAttribute(locLoad, "box2");
				DeleteAttribute(locLoad, "box3");
				DeleteAttribute(locLoad, "box4");
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorAnimation(npchar, "Shot", "pchar_back_to_player", 1.0);
				link.l1 = "Чёрт!";
				link.l1.go = "FB";
			}
			if (npchar.id == "wl_Pirate_Cap")
			{
				
				if (!CheckAttribute(npchar, "quest.meting"))
				{
				dialog.text = "Это ещё что за каракатица на моей палубе?! Назовись!";
				link.l1 = "Где я? Как я сюда попала?";
				link.l1.go = "PC";
				npchar.quest.meting = 1;
				break;
				}
				if (npchar.quest.meting == 1)
				{
					dialog.text = "Я решил, что буду носить твой клинок с пистолем. Костюмчик оказался мне не по размеру, но может и пригодится, если обзаведусь женой-корсаркой\nВряд ли ты станешь возражать. Пистоль твой, однако - очень убойная штука, к тому же выглядит необычно. Где взяла?";
					link.l1 = "Не твоё дело. Долго вы меня собираетесь здесь держать?";
					link.l1.go = "PC_2";
					npchar.quest.meting = 2;
				}
			}
			
			if (npchar.id == "AntonioDeSouza")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					dialog.text = "Надо же, какой интересный 'экземпляр' привёл мне "+GetFullName(characterFromId("wl_Pirate_Cap"))+". Расскажи мне, демон, из какого круга ада ты вышел?";
					link.l1 = "Я не демон.";
					link.l1.go = "ADS";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					dialog.text = "Ну как, удалось что-то вспомнить?";
					link.l1 = "Зря вы это затеяли, отче. Я ведь и отомстить могу, когда выберусь.";
					link.l1.go = "ADS_2";
					npchar.quest.meting = 2;
					break;
				}
				if (npchar.quest.meting == 2)
				{
					dialog.text = "Не стоит надеяться на то, что я тебя пожалею, так что лучше начинай говорить. Тот пистоль. Это разработка англичан? Отвечай!";
					link.l1 = "Ладно. Я всё скажу.";
					link.l1.go = "ADS_1_truth";
					npchar.quest.meting = 3;
					break;
				}
				if (npchar.quest.meting == 3)
				{
					dialog.text = "Ну?";
					link.l1 = "Мне больше нечего вам сказать.";
					pchar.Whisper.DeSouzaHits = 3;
					link.l1.go = "ADS_1_2";
					npchar.quest.meting = 4;
					break;
				}
				if (npchar.quest.meting == 4)
				{
					dialog.text = "Очень не хочется прерывать нашу милую беседу, да только у меня на сегодня назначен встреча с губернатором. Никуда не уходи, и не скучай тут без меня, хе-хе. Завтра продолжим.";
					link.l1 = "...";
					link.l1.go = "ADS_4_exit";
					if(rand(100) < 90)
					{
						pchar.Whisper.IncqGuard_bad = true;
						Pchar.BaseNation = PIRATE;
					}
					npchar.quest.meting = 5;
					break;
				}
			}
			if (npchar.id == "NineFingers")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					dialog.text = "Ого, к нам в посёлок забрела настоящая красотка! Какими судьбами?";
					chrDisableReloadToLocation = false;
					link.l1 = "Да так, скрываюсь от костра инквизиции.";
					link.l1.go = "NF";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					dialog.text = "Ты это видишь? На посёлок напал карательный отряд из Сантьяго. Не по твою ли душу они пришли?";
					link.l1 = "Чёрт! Ты прав, наверное испанцы вышли на мой след. Что же нам теперь делать?";
					AddMoneyToCharacter(npchar, 777);
					npchar.SaveItemsForDead = true;
					link.l1.go = "NF_2_1";
					npchar.quest.meting = 2;
					break;
				}
			}
			if (npchar.id == "Wh_Jack")
			{
				dialog.text = "Где наш капитан? Какого чёрта у тебя его шляпа и клинок?";
				chrDisableReloadToLocation = true;
				link.l1 = "На посёлок устроили облаву испанцы, ваш капитан погиб в бою.";
				link.l1.go = "Jack";
				break;
			}
			if (npchar.id == "Wh_Jim")
			{
				dialog.text = "Дьявол! ты убила Джека! Теперь ты по праву наш капитан.";
				link.l1 = "Правда что ли? Вот так просто?";
				link.l1.go = "Jim";
				break;
			}
			if (npchar.id == "W_Lejitos")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "Глупцы. Вам следовало бы знать, что зверь, загнанный в угол - опасен. А я не просто какой-то зверь, я - Ягуар. Надеюсь, вы успели помолиться своему мёртвому богу, потому что сейчас я вас к нему отправлю!";
					link.l1.go = "exit_cave_entrance_fight";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "Я бы и сам справился, но всё-равно, благодарю за своевременное вмешательство. У тебя, как я вижу, есть свои счёты с испанцами?";
					link.l1 = "Да, я успела нажить себе парочку врагов. А что ты там говорил перед боем, про мёртвого бога?";
					link.l1.go = "Lejitos";
					npchar.quest.meting = 2;
					break;
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "LejitosOff":
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			//npchar.greeting = "Gr_QuestOfficer";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;  // Контузия
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			//LAi_SetWarriorType(NPChar);
			DialogExit();
		break;
		case "LejitosNoOff":
			DialogExit();
			NPChar.lifeday = 0;
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10);
		break;
		case "Lejitos":
			dialog.Text = "Я не христианин. Мои родители ими были когда-то, но они не прожили достаточно долго, чтоб навязать мне эту веру. Меня нашли, вырастили и воспитали в племени индейцев Гуарани. Они открыли мне глаза на истинную веру и рассказали всю суть про христианского Бога.";
			Link.l1 = "Ты прожил всю жизнь среди индейцев?";
			Link.l1.go = "Lejitos_1";
		break;
		case "Lejitos_1":
			dialog.Text = "К сожалению, испанцы не дали мне такой роскоши. Однажды я отправился на охоту, а когда вернулся домой с добычей - застал нашу деревню в руинах. Всё племя было истреблено. Я конечно же отомстил, но племя этим не вернёшь\nПосле этого я подался жить к испанцам, в так называемом цивилизованном обществе. Несколько лет я жил в спокойствии, осваиваясь на новом месте, пока однажды кто-то не рассказал местному священнику о безобидных индейских ритуалах, что я проводил перед принятием еды. Тот в свою очередь донёс это до инквизиции, а что было дальше думаю ты и сама можешь понять\nС тех пор я скрывался от испанцев в голландских колониях, но даже здесь мне не дают покоя. Это далеко не первая и не последняя группа охотников, что приходит за моей головой.";
			Link.l1 = "Лично мне всё-равно, во что ты веришь. Но как боец я вижу, что ты - настоящий зверь. Не хочешь пойти ко мне на службу? Обещаю, будучи у меня в команде ты перебьёшь немало испанцев. Прямо сейчас я намереваюсь догнать тот корабль, про который говорил один из этих подонков.";
			Link.l1.go = "Lejitos_2";
			Link.l2 = "Не думаю, что нам с тобой по пути, приятель. Прощай.";
			Link.l2.go = "LejitosNoOff";
		break;
		case "Lejitos_2":
			dialog.Text = "Ты умеешь убеждать. Конечно же, я не откажусь добавить ещё парочку испанских скальпов себе в коллекцию.";
			Link.l1 = "Вот и договорились. Кстати, мне говорили, что ты направился в эту пещеру за кладом. Удалось найти что-нибудь?";
			Link.l1.go = "Lejitos_3";
		break;
		case "Lejitos_3":
			dialog.Text = "Это не клад, а индейская реликвия. Я могу отдать её тебе на хранение, только прошу, не продавай. Её наверняка переплавят в слитки, после чего её настоящая ценность будет навсегда утеряна.";
			Link.l1 = "Ну ладно, пойдем.";
			Link.l1.go = "LejitosOff";
		break;
		
		case "DeSouzaHunter":
			dialog.Text = "Надо же, кто пришёл! Похоже, мы убьём одним выстрелом сразу двух зайцев! Этого безбожника Элихио уже было бы достаточно, чтобы обрадовать сеньора де Соузу, но когда мы приведём ему ещё и тебя, нам наверняка выдадут премию!";
			Link.l1 = "Де Соуза, говоришь? А где же он сам?";
			Link.l1.go = "DeSouzaHunter_1";
		break;
		case "DeSouzaHunter_1":
			AddQuestRecord("WhisperQuestline", "6");
			dialog.Text = "Что, не терпится получить от него свежую порцию пыток? Уверяю, ждать осталось недолго, ведь он здесь, недалеко, на корабле. Мы причалили в бухте с ироничным для тебя названием - Берег Спасения\nНа корабле все инструменты уже подготовлены. Ты же Виспер, верно? Я видел там железную деву, подписанную твоим именем\nНу так как, сама пойдёшь? Или сначала хочешь отхватить порцию и от нас? Вам, сеньор Лехито, я тот же вопрос задаю.";
			Link.l1 = "Сейчас посмотрим, кто от кого получит!";
			Link.l1.go = "exit_lejitos_speak";
		break;
		case "exit_lejitos_speak":
			DialogExit();
			sld = characterFromID("W_Lejitos");
			SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
		break;
		case "exit_cave_entrance_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			//ref sld;
			for (int i = 1; i <= 7; i++)
			{
				sld = characterFromID("DeSouzaHunter"+sti(i));
				LAi_SetWarriorType(sld);
				LAi_SetImmortal(sld, false);
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			}
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		case "Smuggler":
			NextDiag.TempNode = "Smuggler";
			if (CheckAttribute(pchar, "Whisper.ContraSmuggler"))
			{
				dialog.Text = "Ты ещё кто такая? Чего тебе здесь надо?";
				Link.l1 = "У нас с вами есть один общий знакомый по имени "+GetCharacterFullName("Tortuga_trader")+". Я привезла товар, как договаривались.";
				Link.l1.go = "Whisper_contraband";
				Link.l2 = "Ничего.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.Text = "Сделка состоялась, а теперь вали отсюда, нечего глаза мозолить!";
				Link.l1 = "Ухожу, только дерзить мне не надо.";
				Link.l1.go = "exit";
			}
			
		break;	
		case "Whisper_contraband":
			if(Pchar.Location != Pchar.location.from_sea)
			{
				dialog.Text = "Это всё очень интересно, но корабль твой где? Или ты весь товар на горбу принесла?";
				Link.l1 = "Корабль будет, я просто сначала место проверить хотела.";
				Link.l1.go = "Whisper_contraband_2";
				break;
			}
			if(GetSquadronGoods(Pchar, GOOD_EBONY) >= 100)
			{
				DeleteAttribute(pchar, "Whisper.ContraSmuggler");
				dialog.Text = "Вижу. Похоже, всё в порядке. Мои рабы... работники, мигом всё выгрузят. Вот твои деньги.";
				AddMoneyToCharacter(PChar, 50000);
				RemoveCharacterGoods(Pchar, GOOD_EBONY, 100);
				Link.l1 = "Неплохая сумма, спасибо.";
				Link.l1.go = "Whisper_contraband_1";
				
				break;
			}
			if(GetSquadronGoods(Pchar, GOOD_EBONY) < 100 && GetSquadronGoods(Pchar, GOOD_EBONY) > 0)
			{
				dialog.Text = "У тебя не хватает товара. Возвращайся, когда соберёшь.";
				Link.l1 = "И правда. Жди, сейчас докуплю и вернусь.";
				Link.l1.go = "Whisper_contraband_2";
				break;
			}
			if(GetSquadronGoods(Pchar, GOOD_EBONY) == 0)
			{
				dialog.Text = "Издеваешься? У тебя в трюме вообще нет нужного товара!";
				Link.l1 = "Кажется, я его куда-то переложила. Никуда не уходи, я сейчас.";
				Link.l1.go = "Whisper_contraband_2";
			}
		break;
		case "Whisper_contraband_1":
			dialog.Text = "Кстати, если ещё что интересное найдёшь, сразу нам неси, а то "+GetCharacterFullName("Tortuga_trader")+" собирается завязывать с подобными сделками. Одного нашего представителя ты всегда сможешь найти в таверне.";
			WhisperRemoveSmugglersFromShore();
			AddQuestRecord("WhisperContraband", "3");
			CloseQuestHeader("WhisperContraband");
			Link.l1 = "Хорошо, я это учту.";
			Link.l1.go = "exit";
			//pchar.quest.WhisperChinaman.win_condition.l1 = "ExitFromLocation";
			pchar.quest.WhisperChinaman.win_condition.l1 = "EnterToSea";
			pchar.quest.WhisperChinaman.function    = "WhisperChinaman";
			WhisperSmugglingPatrol();
			//CaptainComission_GenerateCoastalPatrol();
			
		break;
		case "Whisper_contraband_2":
			dialog.Text = "И пошустрей давай, я всю жизнь в этой бухте торчать не собираюсь.";
			Link.l1.go = "exit";
		break;
		
		case "Jim":
			dialog.text = "После того, как ты разделалась с Джеком, никто из команды тебе перечить не пожелает. Он держал в страхе всех. К тому же, у нас на корабле традиция такая - после смерти старого капитана, новым назначать самого отчаянного рубаку, который перебьёт остальных претендентов на шляпу. Такой капитан не побоится привести нас к самой богатой добыче. ";
			link.l1 = "Знаешь, мне нравится ваша традиция. А много ли уже капитанов сменилось?";
			link.l1.go = "Jim_1";
		break;
		case "Jim_1":
			dialog.text = "Прилично.  Не зря же корабль 'Чёрной Вдовой' кличут. На этом посту успели побывать люди всех мастей, возрастов и полов. В среднем кэп удерживает своё положение несколько месяцев, а дальше либо по какой-то нелепой случайности погибает, либо команда бунтует. Билл был самым удачливым - три года продержался. ";
			link.l1 = "Мрачную картину ты мне описал. Кажется, будто эта ваша 'Вдова' - проклята. Но от меня так просто не избавиться. Я согласна стать капитаном, правда не сказала бы, что разбираюсь в управлении кораблём.";
			link.l1.go = "Jim_2";
		break;
		case "Jim_2":
			SetQuestHeader("WhisperContraband");
			AddQuestRecord("WhisperContraband", "1");
			pchar.Whisper.Contraband = true;
			pchar.Whisper.FindDesouza = true;
			SetTimerCondition("W_Smuggling", 0, 0, 60, false);
			dialog.text = "Ничего, научишься. Билл поначалу тоже не умел, но тем не менее стал самым успешным капитаном 'Вдовы'. Мы, если что, поможем, на первых порах. Кстати, у Билла при себе ещё была карта архипелага, если ты её нашла - пользуйся, чтобы проще было ориентироваться на море\nИ если не знаешь с чего начать - загляни в его судовой журнал. Там заметки, что составлял Билл. Мы вроде собирались отвезти товар кому-то на Тортуге, но всех подробностей я не знаю, так что лучше сама прочитай.";
			link.l1 = "Хорошо, почитаю на досуге. А где наш кораблик?";
			link.l1.go = "Jim_EndLine";
		break;
		case "Jim_EndLine":
			dialog.text = "Да прямо здесь, в бухте. Подходи к берегу и залезай в шлюпку\nИ еще. Не то, чтобы я осуждаю твой внешний вид, но посоветовал бы переодеться во что-нибудь менее приметное. Мы ребята не из впечатлительных, всякого повидали, но в портах тебя не все примут столь радушно, особенно священники. У нас на корабле полно всякого тряпья, можешь подобрать себе что-нибудь.";
			TakeNItems(pchar, "suit_1", 1);
			Log_Info("Вы получили обноски");
			PlaySound("interface\important_item.wav");
			link.l1 = "...";
			link.l1.go = "Finish";
		break;
		case "Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			LocatorReloadEnterDisable("Santiago_ExitTown", "reload3", false);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload4", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload3", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("PuertoPrincipe_Port", "reload1_back", false);
			InterfaceStates.DisFastTravel = false;
			DeleteAttribute(Pchar, "questTemp.WhisperTutorial");
			bDisableLandEncounters = false;
			//DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
			Lai_SetPlayerType(pchar);
			
			SetQuestHeader("WhisperQuestline");
			AddQuestRecord("WhisperQuestline", "1");
			AddQuestRecord("WhisperQuestline", "2");
			AddQuestUserData("WhisperQuestline", "sWhCapName", GetFullName(characterFromId("wl_Pirate_Cap")));
			//AddQuestRecord("WhisperQuestline", "3");
	
			SetQuestsCharacters();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 25);
			for(i=1; i < 5; i++)
			{
				sld = CharacterFromID("Wh_Crew"+sti(i));
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 20);
			}
		break;
		case "Jack":
			dialog.text = "Правда что ли? Ха-ха! То есть, э... Очень жаль, конечно. Ладно, давай сюда его вещички и проваливай.";
			link.l1 = "Это вряд ли. Мне они ещё понадобятся.";
			link.l1.go = "Jack_1";
		break;
		case "Jack_1":
			dialog.text = "Ты наверное не поняла. Эти шляпа с клинком, как корона со скипетром - символы власти на 'Чёрной Вдове'. Тому, кому они принадлежат и быть капитаном. Я долго терпел, в ожидании своей очереди. Не удавил капитана во сне чтобы это ускорить. Собирался, но не стал.";
			link.l1 = "Если судить по сказанному - ты тот ещё подонок, а доверять тебе власть - безумие.";
			link.l1.go = "Jack_2";
		break;
		case "Jack_2":
			dialog.text = "Ах ты, каналья! Да я тебя...";
			link.l1 = "Попробуй.";
			link.l1.go = "Jack_fight";
		break;
		case "Jack_fight":
			Lai_SetPlayerType(pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			PChar.quest.WhisperJimTalk.win_condition.l1 = "NPC_Death";
			PChar.quest.WhisperJimTalk.win_condition.l1.character = npchar.id;
			pchar.quest.WhisperJimTalk.function = "WhisperJimTalk";
			DialogExit();
		break;
		case "NF":
			dialog.text = "Будь я инквизитором, тоже непременно захотел бы тебя отжарить. Ха, шутка! Но всё-равно, у них такая внешность не в почёте.";
			link.l1 = "Это я уже поняла.";
			link.l1.go = "NF_1";
		break;
		case "NF_1":
			dialog.text = "Давай знакомиться. Я Девятипалый Билл.";
			link.l1 = "Виспер.";
			link.l1.go = "NF_2";
		break;
		case "NF_2":
			dialog.text = "Чёрт, у тебя уже есть кличка, как у настоящей корсарки! Вот что я тебе посоветую, Виспер. Раз уж ты прячешься от испанцев, тебе неплохо было бы сделать новые документы, чтоб ты могла скрыться в колониях другой страны.";
			link.l1 = "И где я смогу их раздобыть?";
			link.l1.go = "NF_3";
		break;
		case "NF_3":
			dialog.text = "Да прямо в нашем городке, в таверне. Это большое здание у меня за спиной. Поищи за одним из столиков дипломата. Он тебе всё сделает в лучшем виде.";
			link.l1 = "Спасибо за совет, непременно им воспользуюсь.";
			link.l1.go = "NF_exit";
		break;
		case "NF_exit":
			Lai_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.Whisper.BuyDocuments = true;
		break;
		case "NF_2_1":
			dialog.text = "Не знаю как ты, а я прорываюсь к своему кораблю и отчаливаю отсюда.";
			link.l1 = "...";
			link.l1.go = "NF_2_exit";
		break;
		case "NF_2_exit":
			//Lai_SetPlayerType(pchar);
			TakeNItems(npchar, "blade19", 1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_CharacterPlaySound(pchar, "People Fight\Player_Man_Shoot_01.wav");
			DoQuestFunctionDelay("WhisperKillNineFingers", 0.7);
			DialogExit();
			pchar.questTemp.Whisper.GetHat = true;
			DoQuestCheckDelay("TalkSelf_Quest", 2.5);
		break;
		case "Pirateguard":
			dialog.text = RandPhraseSimple("Чего тебе? Проходи мимо.", "Хватит загораживать дорогу, отвали.");
			link.l1 = RandPhraseSimple("Знаешь что? Не гавкай!", "Поумерь свой пыл. Не то быстро охлажу его!");
			NextDiag.CurrentNode = "Pirateguard";
			link.l1.go = "exit";
		break;
		case "IncqGuard_bad":
			dialog.text = "Вот мы и остались одни\nНаверное ты подумала, что на этом все закончилось? Если так, то вынужден тебя огорчить. Видишь ли, пока де Соуза отдыхает или занимается другими делами, я его здесь подменяю. Вопросы я тебе задавать не буду, этим инквизитор занимается. Я лишь сделаю тебя более покладистой к его приходу, чтобы ему больше не пришлось вытягивать из тебя ответы\nДавай, познакомлю тебя с нашими 'игрушками'. Нам недавно привезли 'Колесо', тебе выпадет честь первой испытать его в действии. Пойдём, не стесняйся. И не вздумай пытаться сбежать, здесь полно стражников.";
			link.l1 = "(Молча следовать за ним)";
			link.l1.go = "IncqGuard_bad_go_to_wheel";
		break;
		case "IncqGuard_bad_go_to_wheel":
			DialogExit();
			LAi_ActorGoToLocator(NPChar, "goto", "goto11", "WhisperLine_IncqGuard_bad_speaks", -1);
			LAi_ActorGoToLocator(PChar, "goto", "goto11", "", 10);
			Npchar.dialog.currentnode = "IncqGuard_bad_wheel";
			//DoQuestFunctionDelay("WhisperLine_IncqGuard_bad_speaks", 5);
		break;
		case "IncqGuard_bad_wheel":
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("IncqGuard_"+i);
				LAi_SetActorTypeNoGroup(sld);
			}
			dialog.text = "Вот и наша красавица\nЕсли я правильно помню инструкцию, тебя следует сначала привязать к колесу, после чего, медленными движениями вращать рычаг. Шипы внизу безнадежно искалечат и изуродуют твое тело. Вряд ли после таого ты вообще сможешь ходить без чужой помощи\nТак... Ну и куда же подевалась верёвка?";
			link.l1 = "Прости, но я вынуждена отказаться от твоего предложения. Способность ходить мне еще понадобится, когда я буду искать отсюда выход. (Пока он замешкался, ты резким движением выхватываешь его пистолет из кобуры)";
			link.l1.go = "IncqGuard_bad_wheel_kill";
		break;
		case "IncqGuard_bad_wheel_kill":
			DialogExit();
			//RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			npchar.SaveItemsForDead = true;
			GiveItem2Character(pchar, "pistol3");
			EquipCharacterByItem(pchar, "pistol3");
			Lai_SetPlayerType(pchar);
			//AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("WhisperLine_WhisperHits", 0.2);
		break;
		case "IncqGuard":
			dialog.text = "Чёрт, сильно же он тебя отделал. Знал бы я какое чудовище этот де Соуза - ни за что не пошёл бы сюда на службу.";
			link.l1 = "Ничего, мне и похуже доставалось.";
			link.l1.go = "IncqGuard_1";
		break;
		case "IncqGuard_1":
			dialog.text = "Мне всё-равно больно на это смотреть. Когда он пытает мужиков я ещё могу вынести, но женщин\nЯ тут подумал, дверь ведь ещё не заперта. Быть может, ты хочешь на свободу? А я мог бы отвернуться в другую сторону.";
			link.l1 = "Это какая-то инквизиторская уловка? Вы меня отпустите, а потом проследите, куда пойду?";
			link.l1.go = "IncqGuard_2";
		break;
		case "IncqGuard_2":
			dialog.text = "Нет никаких уловок. Простое человеческое сострадание. Я даже немного денег тебе дам, чтоб ты не пропала сразу, как выберешься.";
			link.l1 = "Чёрт, ты и правда говоришь это всерьёз. Какой план?";
			link.l1.go = "IncqGuard_3";
		break;
		case "IncqGuard_3":
			dialog.text = "Беги прямо по коридору к выходу. Остальная стража хватится за оружие, но они все только вернулись после обеда, так что будут неповоротливы. Если поторопишься, они тебя и пальцем тронуть не успеют\nКак только выйдешь из инквизиции, ты сможешь смешаться с толпой в городе, так что дальше твой след потеряется. Но всё-равно, не задерживайся в Сантьяго, так как тебя наверняка будут разыскивать\nОтправляйся в поселение буканьеров, Пуэрто-Принсипе. Когда выйдешь за ворота, дважды сверни по дороге влево, затем направо, окажешься прямо у входа. Там за мои деньги ты сможешь немного обустроиться, если ты не солгала де Соузе и тебе правда некуда податься. Место это не самое безопасное, но всё же там тебя не ждёт неминуемая гибель, как в этой клетке.";
			link.l1 = "Даже не знаю, смогу ли я когда-то тебя отблагодарить. Ты настоящий рыцарь! Там, откуда я родом такие люди уже вымерли.";
			link.l1.go = "IncqGuard_4";
			if (CheckAttribute(npchar,"quest.answer_1"))
			{
				link.l1 = "Ладно, я готова.";
				link.l1.go = "IncqGuard_exit";
			}
		break;
		case "IncqGuard_4":
			dialog.text = "Ты мне льстишь. Ну ладно, ты всё поняла? Можешь начинать, когда будешь готова. Но лучше не медли.";
			npchar.quest.answer_1 = true;
			link.l1 = "Да, сейчас только соберусь с мыслями.";
			link.l1.go = "IncqGuard_exit";
			link.l2 = "Повтори ещё раз пожалуйста, что мне нужно делать.";
			link.l2.go = "IncqGuard_3";
		break;
		case "IncqGuard_exit":
			Lai_SetPlayerType(pchar);
			AddMoneyToCharacter(pchar, 1500);
			InterfaceStates.Buttons.Save.enable = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			
			PChar.quest.WhisperEscape.win_condition.l1 = "locator";
			PChar.quest.WhisperEscape.win_condition.l1.location = "Santiago_Incquisitio";
			PChar.quest.WhisperEscape.win_condition.l1.locator_group = "reload";
			PChar.quest.WhisperEscape.win_condition.l1.locator = "reload1_back";
			PChar.quest.WhisperEscape.function = "WhisperEscape";
		break;
		case "ADS":
			dialog.text = "Правда? Говори тогда, кто ты? Такой цвет глаз и волос не каждый день увидишь, знаешь ли. И что за пистоль у тебя изъял "+GetFullName(characterFromId("wl_Pirate_Cap"))+"?";
			link.l1 = "Я... Затрудняюсь ответить.";
			link.l1.go = "ADS_1_lie";
			
		break;
		case "ADS_1":
			dialog.text = "Из будущего, говоришь? И что же тебе в таком случае понадобилось в нашем времени?";
			link.l1 = "Ничего, перемещение сюда было случайностью. Послушайте, вы должны поговорить с Эрнаном Эстебаном и попросить у него устройство, что было при мне. Я покажу вам, как оно работает и докажу свои слова.";
			link.l1.go = "ADS_1_1";
		break;
		case "ADS_1_lie":
			dialog.text = "В молчанку собираешься со мной играть?";
			pchar.Whisper.DeSouzaHits = 0;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_1_truth":
			dialog.text = "Слушаю. ";
			link.l2 = "Возможно, вам будет трудно в это поверить, но я пришла из будущего. Несколько веков спустя такое оружие будет также распространено, как сейчас шпаги. И моя внешность не будет казаться столь необычной.";
			link.l2.go = "ADS_1";
		break;
		case "ADS_1_1":
			dialog.text = "Так, хватит. Ты держишь меня за идиота? Я никогда не поверю в путешествия во времени. Ты бы мне ещё байку о 'Летучем Голландце' рассказала\nВернемся к сути. Если пистоль не англичан, то чей, голландцев?";
			pchar.Whisper.DeSouzaHits = 2;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_1_2":
			DoQuestFunctionDelay("WhisperLine_DeSouzaHits", 0.5);
			DialogExit();
		break;
		case "ADS_2":
			dialog.text = "Ты мне ещё угрожать смеешь?! Ах ты, мерзавка!";
			pchar.Whisper.DeSouzaHits = 1;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_3":
			dialog.text = "Сама ведь напрашиваешься.";
			pchar.Whisper.DeSouzaHits = 2;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_4_exit":
			LAi_SetActorTypeNoGroup(npchar);
			//LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DoQuestFunctionDelay("WhisperLine_IncqGuard", 8.0);
		break;
		
		
		case "PC":
			dialog.text = "Это я у тебя должен спрашивать! Имя есть?";
			link.l1 = "Виспер.";
			link.l1.go = "PC_1";
		break;
		case "PC_1":
			dialog.text = "Ой, не нравишься ты мне. Вид у тебя уж слишком подозрительный. Ну-ка, ребятки, покажите нашей новой попутчице дорогу в трюм, и хорошенько там свяжите. Потом с ней разберёмся.";
			link.l1 = "Так просто я не сдамся!";
			link.l1.go = "PC_fight";
			link.l2 = "Ведите, всё-равно я вас всех не одолею.";
			link.l2.go = "PC_nofight";
		break;
		case "PC_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetCheckMinHP(Pchar, 1, true, "Whisper_PC_CheckHP");
			DialogExit();
		break;
		case "PC_nofight":
			Pchar.model="PGG_Whisper_0_NoHat";
			DoQuestFunctionDelay("WhisperHold", 0.5);
			DialogExit();
		break;
		case "PC_2":
			dialog.text = "Сколько потребуется. На вид эти штучки дорого стоят, наверняка у тебя богатые родители. Предлагаю сходить к ним и потребовать выкуп. Как только я получу деньги - ты свободна. Итак, в какой колонии мы сможем их найти?";
			link.l1 = "Я не из этих мест. У меня здесь нет родных.";
			link.l1.go = "PC_2_1";
		break;
		case "PC_2_1":
			dialog.text = "Ты считаешь, что это вызовет во мне жалость? Или, быть может, за дурака держишь? Тогда ты глубоко заблуждаешься\nЗнаешь, у меня есть один знакомый, который сможет тебя разговорить - Антониу де Соуза. Это глава инквизиции в Сантьяго\nПо долгу службы мне пришлось однажды с ним поработать. Вот что я тебе скажу, тип весьма неприятный, но своего добиваться умеет\nЯ привёл к нему одного неразговорчивого пирата, а на следующий день мы уже знали о местонахождении четырёх зарытых им кладов. Сам бедолага при этом умер, давая показания\nБоюсь даже представить, что де Соуза сделает с тобой, когда увидит. С таким цветом волос, скорее всего - сразу на костёр.";
			link.l1 = "Пугай сколько влезет, я и пострашней истории знаю!";
			link.l1.go = "PC_2_2";
			link.l2 = "Неужели мы не сможем договориться?";
			link.l2.go = "PC_2_3";
		break;
		case "PC_2_2":
			dialog.text = "Я лишь говорю как есть\nЛадно, крепись. Пока мы доплывём, у тебя есть несколько дней чтобы подготовиться к далеко не самой приятной встрече в своей жизни. ";
			link.l1 = "...";
			link.l1.go = "PC_2_exit";
			link.l2 = "Постой...";
			link.l2.go = "PC_2_exit";
		break;
		case "PC_2_3":
			dialog.text = "Боюсь, что нет. Я предложил тебе вариант, но ты начала увиливать от ответа. Пускай уже де Соуза узнает, можно ли с тебя получить выкуп, или где берутся такие пистоли\nЛадно, крепись. Пока мы доплывем, у тебя есть несколько дней чтобы подготовиться к далеко не самой приятной встрече в твоей жизни. ";
			link.l1 = "...";
			link.l1.go = "PC_2_exit";
			link.l2 = "Постой...";
			link.l2.go = "PC_2_exit";
		break;
		case "PC_2_exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.Whisper.HoldMonologue = true;
			DoQuestCheckDelay("TalkSelf_Quest", 3.0);
			
		break;
		
		case "FB":
			//CharacterPlayAction(npchar, "Shot");
			NextDiag.CurrentNode = NextDiag.TempNode;
			dialog.text = "(Вы сами не пострадали, однако этого нельзя сказать об устройстве в ваших руках. Пуля попадает в квантовый выпрямитель частиц, после чего устройство включается и начинает работать произвольным образом, издавая серии тресков и щелчков)";
			PlayVoice("interface\beeping.wav");
			link.l1 = "Дьявол!";
			link.l1.go = "FB_exit";
		break;
		case "FB_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			dialog.text = "(Вы сами не пострадали, однако этого нельзя сказать об устройстве в ваших руках.Пуля попадает в квантовый выпрямитель частиц, после чего устройство включается и начинает работать произвольным образом, издавая серии тресков и щелчков)";
			link.l1 = "Дьявол!";
			link.l1.go = "exit";
			DoReloadCharacterToLocation("Ship_Deck_Low","goto","goto5");
			PChar.quest.WhisperTeleport.win_condition.l1 = "location";
			PChar.quest.WhisperTeleport.win_condition.l1.location = "Ship_Deck_Low";
			PChar.quest.WhisperTeleport.function = "WhisperTeleport";
		break;
		case "CS":
			dialog.text = "Это тебе не игрушка, девочка. Ты и представить себе не можешь, на что способен этот предмет. Положи его на место, медленно и осторожно.";
			link.l1 = "Ты про квантовый выпрямитель частиц?";
			link.l1.go = "CS_1";
		break;
		case "CS_1":
			dialog.text = "Ты хоть сама понимаешь, что только что сказала?";
			link.l1 = "Не очень...";
			link.l1.go = "CS_1_1";
			link.l2 = "Конечно! Я не тупая.";
			link.l2.go = "CS_1_2";
		break;
		case "CS_1_1":
			dialog.text = "Хоть по самому названию может быть не ясно, но это устройство позволяет перемещаться в пространстве и времени. Однако, любое применение может привести к тому, что вся временная последовательность полностью перепишется. Ни я, ни ты, можем никогда не родиться. Так что лучше положи обратно на место, от греха подальше.";
			link.l1 = "Послушай, мужик, мне некогда выяснять с тобой отношения. Заказчик ждёт.";
			link.l1.go = "CS_2";
		break;
		case "CS_1_2":
			dialog.text = "Ну тогда ты должна понимать, почему его не стоит трогать.";
			link.l1 = "Послушай, мужик, мне некогда выяснять с тобой отношения. Заказчик ждёт.";
			link.l1.go = "CS_2";
		break;
		case "CS_2":
			dialog.text = "Заказчик? Я знаю только одного возможного заказчика, которому известно об этом устройстве\nЗначит ты - корпоратская подстилка? Делаешь всё, что тебе прикажут?! Я бы тебе врезал, да только меня с детства учили, что женщин бить нельзя...";
			link.l1 = "Попрошу без оскорблений. Я - свободная наёмница. Берусь только за ту работу, которую сама выбираю.";
			link.l1.go = "CS_2_1";
		break;
		case "CS_2_1":
			dialog.text = "Это ты так считаешь. На самом деле ты, да и все мы - уже давно у них на крючке. Небось кредитов нахваталась, а они предложили их закрыть? Можешь не отвечать. Я сам работал на Omnitech и видел всю их гнилую систему изнутри.";
			link.l1 = "Хм. В заказе не сказали, что 'безумный учёный' - их бывший сотрудник.";
			link.l1.go = "CS_3";
		break;
		case "CS_3":
			dialog.text = "Ну и прозвище! Да мои мысли яснее, чем у тебя! Это корпораты, что заставили меня разработать штуку в твоих руках - безумцы! Поэтому я и решил спрятать её от них.";
			link.l1 = "То есть ты украл это устройство у Omnitech?";
			link.l1.go = "CS_3_1";
		break;
		case "CS_3_1":
			dialog.text = "Боюсь, слово 'украл' - неприменимо в данной ситуации. На все сто процентов, это - моя разработка. Но да, по их рабскому закону любая интеллектуальная собственность разработанная сотрудником корпорации на территории корпорации - принадлежит корпорации. Но вором меня всё же назвать можно. Когда я забрал машину времени, заодно перепрограммировал под себя десяток корпоратских ботов, которых ты могла встретить по пути сюда.";
			link.l1 = "Для чего корпорации могла понадобиться машина времени?";
			link.l1.go = "CS_4";
		break;
		case "CS_4":
			dialog.text = "А вот это ты уже правильные вопросы начинаешь задавать. Чтоб вернуться в прошлое и поработить всё человечество ещё быстрее! Имея в запасе такой козырь, как всё время мира, они без проблем станут монополистами во всём мыслимом и немыслимом, а нас ждёт будущее даже более печальное чем то, что происходит в мире сейчас.";
			LAi_SetImmortal(npchar, false);
			link.l1 = "Я правда тебя понимаю. Но лично мне всё-равно, что случится с остальным человечеством. И я получу плату за этот заказ, не смотря на то, придётся мне переступить через твой труп, или нет!";
			link.l1.go = "CS_bad";
			link.l2 = "Если эта штуковина и правда делает то, что ты говоришь, то пожалуй отдавать её корпоратам не стоит. Я найду ей гораздо лучшее применение в своих руках. ";
			link.l2.go = "CS_neutral";
			link.l3 = "Чёрт, а ведь ты прав... Так и быть, забирай и уходи отсюда. Я скажу заказчику, что ты сбежал.";
			link.l3.go = "CS_good";
		break;
		case "CS_bad":
			dialog.text = "Какая же ты всё-таки сволочь.";
			ChangeCharacterReputation(pchar, -100);
			LAi_tmpl_afraid_SetAfraidCharacter(npchar,pchar,false);
			link.l1 = "А ну, заткнулся!";
			Link.l1.go = "ExitSC";
		break;
		case "CS_neutral":
			dialog.text = "Жадность... Понимаю это чувство. Что же, я безоружен и не в силах тебя остановить.";
			link.l1 = "В этом ты абсолютно прав. Прощай.";
			link.l1.go = "ExitSC";
		break;
		case "CS_good":
			dialog.text = "А ведь ты на самом деле вовсе не бездушная тварь, как мне поначалу казалось. Но устройство лучше оставь у себя. Если меня смогли выследить даже в этой богом забытой дыре, то скорее всего на меня каким-то образом повесили устройство слежения. Сейчас уже слишком поздно начинать его искать, так что я вряд ли сумею скрыться. У тебя, с другой стороны, ещё есть шанс. ";
			ChangeCharacterReputation(pchar, +100);
			link.l1 = "Это большее, чем то, на что я была готова подписаться. Но отказать не могу, слишком многое на кону. Обещаю, корпораты не получат это устройство.";
			link.l1.go = "CS_good_1";
		break;
		case "CS_good_1":
			dialog.text = "Только будь оторожна на выходе отсюда. Мои датчики показывают, что ты уничтожила не всех ботов. Я не смогу отключить их удалённо, так что тебе придётся разбираться с ними самостоятельно.";
			link.l1 = "Ага, прощай.";
			link.l1.go = "ExitSC";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "ExitSC":
			LAi_LocationFightDisable(locLoad, true);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorTypeNoGroup(npchar);
			DialogExit();
		break;
		
		case "exit_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			//LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			//LAi_SetImmortal(npchar, false);
			//LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;
	}
}