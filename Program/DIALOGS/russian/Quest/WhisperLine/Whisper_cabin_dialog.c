void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;
	ref shTo;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Exit_Chinaman_Speak":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoQuestFunctionDelay("WhisperChinamanSpeaks", 0.5);
			DialogExit();
		break;
		case "Exit_ChiGuard_Speak":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoQuestFunctionDelay("WhisperChinamanCapSpeaksAgain", 0.5);
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "exit";
			
			if (npchar.id == "W_ChinamanGuard")
			{
				
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "Капитан, смотрите какую 'крысу' мы поймали в трюме.";
					Link.l1 = "Проклятье, только бы не ещё один путешественник во времени. Он наш язык хоть понимает?";
					Link.l1.go = "Exit_Chinaman_Speak";
					npchar.quest.meting = 1;
				break;
				}
				if (npchar.quest.meting == 1)
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "Не то место ты выбрал лучшей жизни. Здесь ситуация ненамного лучше, разве что женщины у нас доступнее. Э-э-э... конечно же я не вас конкретно имел в виду, капитан.";
					link.l1 = "Не мешай мне проводить допрос.";
					link.l1.go = "Exit_Chinaman_Speak";
					npchar.quest.meting = 2;
					break;
				}
				if (npchar.quest.meting == 2)
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "Но капитан\nЭх, ладно.";
					RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
					link.l1.go = "Exit_Chinaman_Speak";
					npchar.quest.meting = 3;
					break;
				}
			}
			if (npchar.id == "W_Chinaman")
			{
				
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "Понимаю.";
					Link.l1 = "И как же тебя звать?";
					Link.l1.go = "ChinamanSpeak_1";
					npchar.quest.meting = 1;
				break;
				}
				if (npchar.quest.meting == 1)
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "Свою ошибку мы понять слишком поздно. Мы плыть очень долго, люди хотеть есть и пить, многие оказаться без сил от голода и быть не готовыми к тому, что случиться\nОднажды мы увидеть на горизонте корабль. Мы сигналить мир, но они не хотеть слушать. Корабль нападать. Многие наш люди погибли, меня взять в плен и сделать рабом.";
					Link.l1 = "Суровая история. Меня примерно также здесь приняли.";
					Link.l1.go = "ChinamanSpeak_1_1";
					npchar.quest.meting = 2;
					break;
				}
				if (npchar.quest.meting == 2)
				{
					Lai_SetPlayerType(pchar);
					dialog.Text = "Спасибо капитан, я не забыть этого.";
					GiveItem2Character(npchar, "blade9");
					EquipCharacterByItem(npchar, "blade9");
					LAi_SetImmortal(NPChar, false);
					Link.l1 = "Очень на это надеюсь.";
					Link.l1.go = "ChinamanOff";
					npchar.quest.meting = 3;
					break;
				}
			}
			
			NextDiag.TempNode = "First time";
		break;

		case "WarDogCap":
			dialog.Text = "Снова ты? Я думал ты давно уже сгинула в стенах инквизиции.";
			Link.l1 = "От меня так просто не избавиться.";
			Link.l1.go = "WarDogCap_1";
		break;
		case "WarDogCap_1":
			dialog.Text = "Как ты меня вообще нашла?";
			Link.l1 = "Твой дружок-инквизитор, Антониу де Соуза, сам устроил эту западню. Твои недавние поступки очень разозлили испанскую корону, де Соуза хотел лично тебя здесь поймать, но я вежливо попросила оказать эту честь мне.";
			Link.l1.go = "WarDogCap_2";
		break;
		case "WarDogCap_2":
			dialog.Text = "Какого чёрта тебе от меня нужно?";
			Link.l1 = "У тебя есть кое-что моё.";
			Link.l1.go = "WarDogCap_2_1";
		break;
		case "WarDogCap_2_1":
			dialog.Text = "Ты про свой пистоль? Могу отдать, если позволишь мне уйти.";
			Link.l1 = "Не только пистоль, всё моё снаряжение, включая устройство, с помощью которого я телепортировалась сюда.";
			Link.l1.go = "WarDogCap_3";
		break;
		case "WarDogCap_3":
			dialog.Text = "Чего? А, ты про ту бесполезную железку? Так я её выкинул давно за борт.";
			Link.l1 = "Что ты сделал, тупица?!";
			Link.l1.go = "WarDogCap_4";
		break;
		case "WarDogCap_4":
			dialog.Text = "Я не позволю бабе так с собой разговаривать!";
			Link.l1 = "Да я тебя закопаю, сволочь!";
			Link.l1.go = "WarDogCap_fight";
		break;
		case "WarDogCap_fight":
			AddQuestRecord("WhisperQuestline", "8");
			CloseQuestHeader("WhisperQuestline");
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
			pchar.Whisper.NanoCostume = true;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "DeSouza":
			dialog.Text = "Надо же, какой сюрприз. А я везде тебя искал, Виспер.";
			Link.l1 = "Мне надоело ждать, когда же ты меня найдёшь, так что я сама к тебе пришла.";
			Link.l1.go = "DeSouza_1";
		break;
		case "DeSouza_1":
			dialog.Text = "Храбро, но глупо. Ты хоть представляешь, что я сейчас с тобой сделаю?";
			Link.l1 = "Сомневаюсь, что тебе хватит на это сил, ты еле на ногах стоишь. Могу предложить тебе передышку. Давай немного поговорим.";
			Link.l1.go = "DeSouza_2";
		break;
		case "DeSouza_2":
			dialog.Text = "И о чём же ты хочешь говорить?";
			Link.l1 = "Я бы хотела знать, где находится "+GetFullName(characterFromId("wl_Pirate_Cap"))+"?";
			Link.l1.go = "DeSouza_3";
		break;
		case "DeSouza_3":
			dialog.Text = "Ха! Я бы тоже хотел это знать. До недавних пор он был образцовым капером, однако в последнее время почувствовал вседозволенность. Ему удалось раздобыть корвет с  характеристиками, равных которым на архипелаге сейчас нет. Он перестал появляться у генерал-губернатора, а его корабль, по слухам, был замечен за грабежами других кораблей Испании. Такое недопустимо, так что генерал-губернатор попросил меня найти его лично и покарать. Этим я и занимаюсь сейчас, а заодно отлавливаю других врагов короны, вроде тебя.";
			Link.l1 = "И что, нет совсем никаких зацепок, где он может быть?";
			Link.l1.go = "DeSouza_4";
		break;
		case "DeSouza_4":
			dialog.Text = "Есть одна, но прежде чем я её назову, позволь и мне задать вопрос. Правда ли ты из будущего?";
			Link.l1 = "Да.";
			Link.l1.go = "DeSouza_5";
		break;
		case "DeSouza_5":
			dialog.Text = "Боже, теперь я вижу что ты не врёшь. Ответь же мне, помнит ли кто-то в будущем обо мне и моём ордене?";
			Link.l1 = "В будущем люди стараются забыть о вашем безумном ордене. Если и вспоминают, то только в негативном ключе, как о рассаднике жестокости и невежества. Всё, чего вы добились - множество смертей и разрушенных жизней.";
			Link.l1.go = "DeSouza_6";
		break;
		case "DeSouza_6":
			dialog.Text = "За такие слова, я тебя\nИ всё же, доля правды в этом есть. Стараясь выполнить волю господа я немало согрешил. Однако я не считаю, что поступал неправильно, иногда грех - это вынужденная мера, чтобы нести добро\nК чёрту людей! Только Господу дано меня судить!";
			Link.l1 = "Я удовлетворила твое любопытство. Твой черёд.";
			Link.l1.go = "DeSouza_7";
		break;
		case "DeSouza_7":
			AddQuestRecord("WhisperQuestline", "7");
			AddQuestUserData("WhisperQuestline", "sWhCapName", GetFullName(characterFromId("wl_Pirate_Cap")));
			SetTimerCondition("Whisper_WarDog", 0, 0, 30, false);
			dialog.Text = "Я заплатил одной бордельной девице, которую часто посещает "+GetFullName(characterFromId("wl_Pirate_Cap"))+", чтобы она пустила ему в ухо один слух, якобы в бухте на Терксе спрятан клад. Он жадный человек, наверняка должен клюнуть. По моим примерным подсчётам, если всё сработало, он должен объявиться там через месяц.";
			Link.l1 = "Коварный и жестокий план, как раз в стиле инквизиции.";
			Link.l1.go = "DeSouza_8";
		break;
		case "DeSouza_8":
			dialog.Text = "Пускай же Господь решит, кому из нас двоих суждено его перехватить, а кому отправиться сегодня на суд Божий.";
			Link.l1 = "Аминь.";
			Link.l1.go = "DeSouza_fight";
		break;
		case "DeSouza_fight":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			pchar.Whisper.DeSouzaTalked = true;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "ChinamanSpeak_1":
			dialog.Text = "Лонг Вэй.";
			Link.l1 = "Вижу, далековато тебя забросило от дома. Ты ведь из Японии? Знаешь, у меня когда-то был японский меч...";
			Link.l1.go = "ChinamanSpeak_2";
		break;
		case "ChinamanSpeak_2":
			dialog.Text = "Я прибыть сюда из Китая, провинция Шаньдун.";
			Link.l1 = "Ясно. А по какой причине, вместо того, чтобы находиться в своём Китае, ты оказался у меня на корабле?";
			Link.l1.go = "ChinamanSpeak_3";
		break;
		case "ChinamanSpeak_3":
			dialog.Text = "Это долгий история\nНа родине круглый год идти война. Император постоянно устраивать призыв в армию. Многие мужчины умирать, так и не познав женщина\nЯ быть капитаном джонки. Мы с командой договориться уплыть прочь, за ночь до крупной битвы\nМы поплыть на запад, в поисках лучшей жизни.";
			Link.l1 = "...";
			Link.l1.go = "Exit_ChiGuard_Speak";
		break;
		case "ChinamanSpeak_1_1":
			dialog.Text = "Меня отправить служить к этим злым людям, что вы встречать на берегу. Они бить меня и заставлять носить тяжести. Я спрятаться от них в трюме этого корабля.";
			Link.l1 = "Ага, теперь мне всё ясно. Значит ты - беглый раб.";
			Link.l1.go = "ChinamanSpeak_1_2";
		break;
		case "ChinamanSpeak_1_2":
			dialog.Text = "Получаться, что так.";
			Link.l1 = "Меня зацепила твоя история. Могу предложить место в команде. Говоришь, был капитаном? Мне бы не помешал кто-то с твоим опытом, так как я сама в этом ремесле недавно.";
			Link.l1.go = "ChinamanSpeak_1_3";
			Link.l2 = "Тогда твоё место - среди других рабов. Хуан, отведи его в трюм.";
			Link.l2.go = "ChinamanSlave";
		break;
		case "ChinamanSpeak_1_3":
			dialog.Text = "Могу помочь управлять кораблём, а также, я владеть мечом, могу быть телохранителем. ";
			Link.l1 = "В таком случае, Хуан, отдай ему свой клинок. Потом найдёшь себе другой.";
			Link.l1.go = "Exit_ChiGuard_Speak";
		break;
		case "ChinamanSlave":
			DialogExit();
			ChangeCharacterReputation(pchar, -30);
			AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7);
			npchar.lifeday = 0;
			sld = characterFromID("W_ChinamanGuard");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 7);
			sld.lifeday = 0;
			
			PlayVoice("interface\_EvEnemy1.wav");
			pchar.questTemp.Whisper.SmugPatrol = true;	
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
		break;
		case "ChinamanOff":
			DialogExit();
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.greeting = "GR_longway";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.HalfImmortal = true;  // Контузия
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			LAi_SetWarriorType(NPChar);
			SetSelfSkill(NPChar, 25, 25, 25, 25, 25);
			SetShipSkill(NPChar, 15, 15, 20, 20, 40, 15, 15, 15, 15);
			SetSPECIAL(sld, 5, 5, 9, 4, 9, 9, 9);
			NPChar.rank = 6;
			LAi_SetHP(npchar, 120.0, 120.0);
			SetCharacterPerk(NPChar, "ByWorker");
			SetCharacterPerk(NPChar, "ShipSpeedUp");
			SetCharacterPerk(NPChar, "ShipTurnRateUp");
			SetCharacterPerk(NPChar, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, даётся ГГ и боссам уровней
			
			sld = characterFromID("W_ChinamanGuard");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 7);
			sld.lifeday = 0;
			PlayVoice("interface\_EvShip3.wav");
			pchar.questTemp.Whisper.SmugPatrol = true;	
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
		break;
	}
}