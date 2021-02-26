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
				LAi_LocationFightDisable(locLoad, true);
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorAnimation(npchar, "Shot", "pchar_back_to_player", 1.0);
				link.l1 = "Черт!";
				link.l1.go = "FB";
			}
			if (npchar.id == "wl_Pirate_Cap")
            {
				
				if (!CheckAttribute(npchar, "quest.meting"))
				{
				dialog.text = "Это еще что за каракатица на моей палубе?! Назовись!";
				link.l1 = "Где я? Как я сюда попала?";
				link.l1.go = "PC";
				npchar.quest.meting = 1;
				break;
				}
				if (npchar.quest.meting == 1)
				{
					dialog.text = "Я решил что буду носить твои клинок с пистолем. Костюмчик мне не подошел, но может и пригодится, если обзаведусь женой-корсаркой.\nВряд ли ты станешь возражать. Пистоль твой, однако - очень убойная штука, к тому же выглядит необычно. Где взяла?";
					link.l1 = "Не твое дело. Долго вы меня собираетесь здесь держать?";
					link.l1.go = "PC_2";
					npchar.quest.meting = 2;
				}
			}
			
			if (npchar.id == "AntonioDeSouza")
            {
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					dialog.text = "Надо же, какой интересный 'экземпляр' привел мне "+GetFullName(characterFromId("wl_Pirate_Cap"))+". Расскажи мне, демон, из какого круга ада ты вышел?";
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
					dialog.text = "Не стоит надеяться на то, что я тебя пожалею, так что лучше начинай говорить. Если пистоль не англичан, то чей, голландцев?";
					link.l1 = "Вы и представить себе не можете, как сильно заблуждаетесь.";
					link.l1.go = "ADS_3";
					npchar.quest.meting = 3;
					break;
				}
				if (npchar.quest.meting == 3)
				{
					dialog.text = "Ну?";
					link.l1 = "Мне нечего вам сказать.";
					pchar.Whisper.DeSouzaHits = 3;
					link.l1.go = "ADS_1_2";
					npchar.quest.meting = 4;
					break;
				}
				if (npchar.quest.meting == 4)
				{
					dialog.text = "Ох, что-то подустал я сегодня. Пойду, прилягу, завтра продолжим. Никуда не уходи, хе-хе.";
					link.l1 = "...";
					link.l1.go = "ADS_4_exit";
					npchar.quest.meting = 5;
					break;
				}
			}
			if (npchar.id == "NineFingers")
            {
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					dialog.text = "Ого, к нам в поселок забрела настоящая красотка! Какими судьбами?";
					link.l1 = "Да так, скрываюсь от инквизиции.";
					link.l1.go = "NF";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					PlayVoice("VOICE\Russian\EvilPirates02.wav");
					dialog.text = "Слыхала? На поселок напал карательный отряд из Сантьяго. За стенами уже вовсю разгорелась битва. Не по твою ли душу они пришли?";
					link.l1 = "Черт! Ты прав, наверное моего спасителя из стражи заставили проговориться под пытками. Что же теперь делать?";
					link.l1.go = "NF_2_1";
					npchar.quest.meting = 2;
					break;
				}
			}
			if (npchar.id == "Wh_Jack")
            {
				dialog.text = "Где наш капитан? Какого черта у тебя его шляпа и клинок?";
				link.l1 = "На поселок устроили облаву испанцы, ваш капитан погиб в бою.";
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
			NextDiag.TempNode = "First time";
		break;

		case "Jim":
			dialog.text = "После того, как ты разделалась с Джеком, никто из команды тебе перечить не пожелает. Он держал в страхе всех. К тому же, у нас на корабле традиция такая - после смерти старого капитана, новым назначать самого отчаянного рубаку, который перебьет остальных претендентов на шляпу. Такой капитан не побоится привести нас к самой богатой добыче. ";
			link.l1 = "Знаешь, мне нравился ваша традиция. А много ли уже капитанов сменилось?";
			link.l1.go = "Jim_1";
		break;
		case "Jim_1":
			dialog.text = "Прилично.  Не зря же корабль 'Черной Вдовой' кличут. На этом посту успели побывать люди всех мастей, возрастов и полов. В среднем кэп удерживает свое положение несколько месяцев, а дальше либо по какой-то нелепой случайности погибает, либо команда бунтует. Билл был самым удачливым - три года продержался. ";
			link.l1 = "Мрачную картину ты мне описал. Кажется, будто эта ваша 'Вдова' - проклята. Но от меня так просто не избавиться. Я согласна стать капитаном, правда не сказала бы, что разбираюсь в управлении кораблем.";
			link.l1.go = "Jim_2";
		break;
		case "Jim_2":
			dialog.text = "Ничего, научишься. Билл поначалу тоже не умел, но тем не менее стал самым успешным капитаном. Мы, если что, поможем, на первых порах. ";
			link.l1 = "Убедил. Ну и где ваш кораблик?";
			link.l1.go = "Jim_EndLine";
		break;
		case "Jim_EndLine":
			dialog.text = "Да прямо здесь, в бухте. Подходи к берегу и залезай в шлюпку. ";
			link.l1 = "...";
			link.l1.go = "Finish";
		break;
		case "Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			
			LocatorReloadEnterDisable("Santiago_ExitTown", "reload3", false);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload4", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload3", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("PuertoPrincipe_Port", "reload1_back", false);
			InterfaceStates.DisFastTravel = false;
			DeleteAttribute(Pchar, "questTemp.WhisperTutorial");
			bDisableLandEncounters = false;
			
            ref mc = GetMainCharacter();
            mc.Ship.Type = GenerateShipExt(SHIP_SOPHIE, true, mc);
            mc.Ship.name="Черная Вдова";
            SetBaseShipData(mc);
            mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
            SetCrewQuantityFull(mc);

            SetCharacterGoods(mc,GOOD_FOOD,200);
        	SetCharacterGoods(mc,GOOD_BALLS,300);//2000);
            SetCharacterGoods(mc,GOOD_GRAPES,300);//700);
            SetCharacterGoods(mc,GOOD_KNIPPELS,300);//700);
            SetCharacterGoods(mc,GOOD_BOMBS,300);//1500);
            SetCharacterGoods(mc,GOOD_POWDER,1000);
            SetCharacterGoods(mc,GOOD_PLANKS,10);
            SetCharacterGoods(mc,GOOD_RUM,40);//600);
            SetCharacterGoods(mc,GOOD_WEAPON,100);//2000);
            DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
			Lai_SetPlayerType(pchar);
			
			SetQuestHeader("WhisperQuestline");
			AddQuestRecord("WhisperQuestline", "1");
			
			AddQuestRecord("WhisperQuestline", "2");
			AddQuestUserData("WhisperQuestline", "sWhCapName", GetFullName(characterFromId("wl_Pirate_Cap")));
			AddQuestRecord("WhisperQuestline", "3");

		break;
		case "Jack":
			dialog.text = "Правда что ли? Ха-ха! То есть, э... Очень жаль, конечно. Ладно, давай сюда его вещички и проваливай.";
			link.l1 = "Это вряд ли. Мне они еще понадобятся.";
			link.l1.go = "Jack_1";
		break;
		case "Jack_1":
			dialog.text = "Ты наверное не поняла. Эти шляпа с клинком, как корона со скипетром - символы власти на 'Черной Вдове'. Тому, кому они принадлежат и быть капитаном. Я долго терпел, в ожидании своей очереди. Не удавил капитана во сне чтобы это ускорить. Собирался, но не стал.";
			link.l1 = "Если судить по сказанному - ты тот еще подонок, а доверять тебе власть - безумие.";
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
			dialog.text = "Будь я инквизитором, тоже непременно захотел бы тебя отжарить. Ха, шутка! Но все равно, у них такая внешность не в почете.";
			link.l1 = "Это я уже поняла.";
			link.l1.go = "NF_1";
		break;
		case "NF_1":
			dialog.text = "Давай знакомиться. Я Девятипалый Билл.";
			link.l1 = "Виспер.";
			link.l1.go = "NF_2";
		break;
		case "NF_2":
			dialog.text = "Черт, у тебя уже есть кличка, как у настоящей корсарки! Вот что я тебе посоветую, Виспер. Раз уж ты прячешься от испанцев, тебе неплохо было бы сделать новые документы, чтоб ты могла скрыться в колониях другой страны.";
			link.l1 = "И где я смогу их раздобыть?";
			link.l1.go = "NF_3";
		break;
		case "NF_3":
			dialog.text = "Да прямо в нашем городке, в таверне. Это большое здание у меня за спиной. Поищи за одним из столиков дипломата. Он тебе все сделает в лучшем виде.";
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
			Lai_SetPlayerType(pchar);
			TakeNItems(npchar, "blade19", 1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlayVoice("People Fight\rifle_fire1.wav");
			LAi_KillCharacter(npchar);
			pchar.questTemp.Whisper.GetHat = true;
			DoQuestCheckDelay("TalkSelf_Quest", 1.0);
		break;
		case "Pirateguard":
			dialog.text = RandPhraseSimple("Чего тебе? Проходи мимо.", "Хватит загораживать дорогу, отвали.");
			link.l1 = RandPhraseSimple("Знаешь что? Не гавкай!", "Поумерь свой пыл. Не то быстро охлажу его!");
			NextDiag.CurrentNode = "Pirateguard";
			link.l1.go = "exit";
		break;
		case "IncqGuard":
			dialog.text = "Черт, сильно же он тебя отделал. Знал бы я какое чудовище этот де Соуза - ни за что не пошел бы сюда на службу.";
			link.l1 = "Ничего, мне и похуже доставалось.";
			link.l1.go = "IncqGuard_1";
		break;
		case "IncqGuard_1":
			dialog.text = "Мне все равно больно на это смотреть. Когда он пытает мужиков я еще могу вынести, но женщин\nЯ тут подумал, дверь ведь еще не заперта. Быть может, ты хочешь на свободу? А я мог бы отвернуться в другую сторону.";
			link.l1 = "Это какая-то инквизиторская уловка? Вы меня отпустите, а потом проследите, куда пойду?";
			link.l1.go = "IncqGuard_2";
		break;
		case "IncqGuard_2":
			dialog.text = "Нет никаких уловок. Простое человеческое сострадание. Я даже немного денег тебе дам, чтоб ты не пропала сразу, как выберешься.";
			link.l1 = "Черт, ты и правда говоришь это всерьез. Какой план?";
			link.l1.go = "IncqGuard_3";
		break;
		case "IncqGuard_3":
			dialog.text = "Беги прямо по коридору к выходу. Остальная стража хватится за оружие, но они все только вернулись после обеда, так что будут неповоротливы. Если поторопишься, они тебя и пальцем тронуть не успеют\nКак только выйдешь из инквизиции, ты сможешь смешаться с толпой в городе, так что дальше твой след потеряется. Но все равно, не задерживайся в Сантьяго, так как тебя наверняка будут разыскивать\nОтправляйся в поселение буканьеров, Пуэрто-Принсипе. Когда выйдешь за ворота, дважды сверни по дороге влево, затем направо, окажешься прямо у входа. Там за мои деньги ты сможешь немного обустроиться, если ты не солгала де Соузе и тебе правда некуда податься. Место это не самое безопасное, но все же там тебя не ждет неминуемая гибель, как в этой клетке.";
			link.l1 = "Даже не знаю, смогу ли я когда-то тебя отблагодарить. Ты настоящий рыцарь! Там, откуда я родом такие люди уже вымерли.";
			link.l1.go = "IncqGuard_4";
			if (CheckAttribute(npchar,"quest.answer_1"))
			{
				link.l1 = "Ладно, я готова.";
				link.l1.go = "IncqGuard_exit";
			}
		break;
		case "IncqGuard_4":
			dialog.text = "Ты мне льстишь. Ну ладно, ты все поняла? Можешь начинать, когда будешь готова. Но лучше не медли.";
			npchar.quest.answer_1 = true;
			link.l1 = "Да, сейчас только соберусь с мыслями.";
			link.l1.go = "IncqGuard_exit";
			link.l2 = "Повтори еще раз пожалуйста, что мне нужно делать.";
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
			link.l1 = "Я пришла из будущего. Несколько веков спустя такое оружие будет также распространено, как сейчас шпаги. И  внешность такая не будет казаться столь необычной.";
			link.l1.go = "ADS_1";
		break;
		case "ADS_1":
			dialog.text = "Из будущего, говоришь? И что же тебе в таком случае понадобилось в нашем времени?";
			link.l1 = "Ничего, перемещение сюда было случайностью. Послушайте, вы должны поговорить с "+GetFullName(characterFromId("wl_Pirate_Cap"))+" и попросить у него устройство, что было при мне. Я покажу вам, как оно работает и докажу свои слова, а потом уберусь отсюда.";
			link.l1.go = "ADS_1_1";
		break;
		case "ADS_1_1":
			dialog.text = "Так, хватит. Ты держишь меня за идиота? Я никогда не поверю в путешествия во времени. Ты бы мне еще байку о 'Летучем Голландце' рассказала\nТот пистоль. Это разработка англичан? Отвечай!";
			pchar.Whisper.DeSouzaHits = 0;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_1_2":
			DoQuestFunctionDelay("WhisperLine_DeSouzaHits", 0.5);
			DialogExit();
		break;
		case "ADS_2":
			dialog.text = "Ты мне еще угрожать смеешь?! Ах ты, мерзавка!";
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
			DoQuestFunctionDelay("WhisperLine_IncqGuard", 15.0);
		break;
		
		
		case "PC":
			dialog.text = "Это я у тебя должен спрашивать! Имя есть?";
			link.l1 = "Виспер.";
			link.l1.go = "PC_1";
		break;
		case "PC_1":
			dialog.text = "Ой, не нравишься ты мне. Вид у тебя уж слишком подозрительный. Ну-ка, ребятки, покажите нашей новой попутчице дорогу в трюм, и хорошенько там свяжите. Потом с ней разберемся.";
			link.l1 = "Так просто я не сдамся!";
			link.l1.go = "PC_fight";
			link.l2 = "Ведите, все равно я вас всех не одолею.";
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
			dialog.text = "Ты считаешь, что это вызовет во мне жалость? Или, быть может, за дурака держишь? Тогда ты глубоко заблуждаешься\nЗнаешь, у меня есть один знакомый, который сможет тебя разговорить - Антониу де Соуза. Это глава инквизиции в Сантьяго\nПо долгу службы мне пришлось однажды с ним поработать. Вот что я тебе скажу, тип весьма неприятный, но своего добиваться умеет\nЯ привел к нему одного неразговорчивого пирата, а на следующий день мы уже знали о местонахождении четырех зарытых им кладов. Сам бедолага при этом умер, давая показания\nБоюсь даже представить, что де Соуза сделает с тобой, когда увидит. С таким цветом волос, скорее всего - сразу на костер.";
			link.l1 = "Пугай сколько влезет, я и пострашней истории знаю!";
			link.l1.go = "PC_2_2";
			link.l2 = "Неужели мы не сможем договориться?";
			link.l2.go = "PC_2_3";
		break;
		case "PC_2_2":
			dialog.text = "Я лишь говорю как есть\nЛадно, крепись. Пока мы доплывем, у тебя есть несколько дней чтобы подготовиться с далеко не самой приятной встрече в своей жизни. ";
			link.l1 = "...";
			link.l1.go = "PC_2_exit";
			link.l2 = "Постой...";
			link.l2.go = "PC_2_exit";
		break;
		case "PC_2_3":
			dialog.text = "Боюсь, что нет. Я предложил тебе вариант, но ты начала увиливать от ответа. Пускай уже де Соуза узнает, можно ли с тебя получить выкуп, или где берутся такие пистоли\nЛадно, крепись. Пока мы доплывем, у тебя есть несколько дней чтобы подготовиться с далеко не самой приятной встрече в твоей жизни. ";
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
            link.l1 = "Послушай, мужик, мне некогда выяснять с тобой отношения. Заказчик ждет.";
			link.l1.go = "CS_2";
		break;
		case "CS_1_2":
			dialog.text = "Ну тогда ты должна понимать, почему его не стоит трогать.";
            link.l1 = "Послушай, мужик, мне некогда выяснять с тобой отношения. Заказчик ждет.";
			link.l1.go = "CS_2";
		break;
		case "CS_2":
			dialog.text = "Заказчик? Я знаю только одного возможного заказчика, которому известно об этом устройстве\nЗначит ты - корпоратская подстилка? Делаешь все, что тебе прикажут?! Я бы тебе врезал, да только меня с детства учили, что женщин бить нельзя...";
            link.l1 = "Попрошу без оскорблений. Я - свободная наемница. Берусь только за ту работу, которую сама выбираю.";
            link.l1.go = "CS_2_1";
		break;
		case "CS_2_1":
			dialog.text = "Это ты так считаешь. На самом деле ты, да и все мы - уже давно у них на крючке. Небось кредитов нахваталась, а они предложили их закрыть? Можешь не отвечать. Я сам работал на Omnitech и видел всю их гнилую систему изнутри.";
            link.l1 = "Хм. В заказе не сказали, что 'безумный ученый' - их бывший сотрудник.";
			link.l1.go = "CS_3";
		break;
		case "CS_3":
			dialog.text = "Ну и прозвище! Да мои мысли яснее, чем у тебя! Это корпораты, что заставили меня разработать штуку в твоих руках - безумцы! Поэтому я и решил спрятать ее от них.";
			link.l1 = "То есть ты украл это устройство у Omnitech?";
            link.l1.go = "CS_3_1";
		break;
		case "CS_3_1":
			dialog.text = "Боюсь, слово 'украл' - неприменимо в данной ситуации. На все сто процентов, это - моя разработка. Но да, по их рабскому закону любая интеллектуальная собственность разработанная сотрудником корпорации на территории корпорации - принадлежит корпорации. Но вором меня все же назвать можно. Когда я забрал машину времени, заодно перепрограммировал под себя десяток корпоратских ботов, которых ты могла встретить по пути сюда.";
			link.l1 = "Для чего корпорации могла понадобиться машина времени?";
			link.l1.go = "CS_4";
		break;
		case "CS_4":
			dialog.text = "А вот это ты уже правильные вопросы начинаешь задавать. Чтоб вернуться в прошлое и поработить все человечество еще быстрее! Имея в запасе такой козырь, как все время мира, они без проблем станут монополистами во всем мыслимом и немыслимом, а нас ждет будущее даже более печальное чем то, что происходит в мире сейчас.";
			LAi_SetImmortal(npchar, false);
			link.l1 = "Я правда тебя понимаю. Но лично мне все равно, что случится с остальным человечеством. И я получу плату за этот заказ, не смотря на то, придется мне переступить через твой труп, или нет!";
			link.l1.go = "CS_bad";
			link.l2 = "Если эта штуковина и правда делает то, что ты говоришь, то пожалуй отдавать ее корпоратам не стоит. Я найду ей гораздо лучшее применение в своих руках. ";
			link.l2.go = "CS_neutral";
			link.l3 = "Черт, а ведь ты прав... Так и быть, забирай и уходи отсюда. Я скажу заказчику, что ты сбежал.";
			link.l3.go = "CS_good";
		break;
		case "CS_bad":
			dialog.text = "Какая же ты все таки сволочь.";
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
			dialog.text = "А ведь ты на самом деле вовсе не бездушная тварь, как мне поначалу казалось. Но устройство лучше оставь у себя. Если меня смогли выследить даже в этой богом забытой дыре, то скорее всего в меня давно уже без моего на то ведома вживили жучок. Я не смогу скрыться. У тебя, с другой стороны, еще есть шанс. ";
			ChangeCharacterReputation(pchar, +100);
			link.l1 = "Это большее, чем то, на что я была готова подписаться. Но отказать не могу, слишком многое на кону. Обещаю, корпораты не получат это устройство.";
			link.l1.go = "CS_good_1";
		break;
		case "CS_good_1":
			dialog.text = "Только будь оторожна на выходе отсюда. Мои датчики показывают, что ты уничтожила не всех ботов. Я не смогу отключить их удаленно, так что тебе придется разбираться с ними самостоятельно.";
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
