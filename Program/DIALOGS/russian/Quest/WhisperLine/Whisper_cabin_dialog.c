
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
					Link.l1 = "Проклятье, только бы не еще один путешественник во времени. Он наш язык хоть понимает?";
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

		case "ChinamanSpeak_1":
			dialog.Text = "Лонг Вэй.";
			Link.l1 = "Вижу, далековато тебя забросило от дома. Ты ведь из Японии? Знаешь, у меня когда-то был японский меч...";
			Link.l1.go = "ChinamanSpeak_2";
		break;
		case "ChinamanSpeak_2":
			dialog.Text = "Я прибыть сюда из Китая, провинция Шаньдун.";
			Link.l1 = "Ясно. А по какой причине, вместо того, чтобы находиться в своем Китае, ты оказался у меня на корабле?";
			Link.l1.go = "ChinamanSpeak_3";
		break;
		case "ChinamanSpeak_3":
			dialog.Text = "Это долгий история\nНа родине круглый год идти война. Император постоянно устраивать призыв в армию. Многие мужчины умирать, так и не познав женщина\nЯ быть капитаном джонки. Мы с командой договориться уплыть прочь, за ночь до крупной битвы\nМы поплыть на запад, в поисках лучшей жизни.";
			Link.l1 = "...";
			Link.l1.go = "Exit_ChiGuard_Speak";
		break;
		case "ChinamanSpeak_1_1":
			dialog.Text = "Меня отправить служить к этим злым людям, что вы встречать на берегу. Они бить меня и заставлять носить тяжести. Я спрятаться от них в трюме этого корабля.";
			Link.l1 = "Ага, теперь мне все ясно. Значит ты - беглый раб.";
			Link.l1.go = "ChinamanSpeak_1_2";
		break;
		case "ChinamanSpeak_1_2":
			dialog.Text = "Получаться, что так.";
			Link.l1 = "Меня зацепила твоя история. Могу предложить место в команде. Говоришь, был капитаном? Мне бы не помешал кто-то с твоим опытом, так как я сама в этом ремесле недавно.";
			Link.l1.go = "ChinamanSpeak_1_3";
			Link.l2 = "Тогда твое место - среди других рабов. Хуан, отведи его в трюм.";
			Link.l2.go = "ChinamanSlave";
		break;
		case "ChinamanSpeak_1_3":
			dialog.Text = "Могу помочь управлять кораблем, а также, я владеть мечом, могу быть телохранителем. ";
			Link.l1 = "В таком случае, Хуан, отдай ему свой клинок. Потом найдешь себе другой.";
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
			npchar.greeting = "Gr_questOfficer";
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
			SetCharacterPerk(NPChar, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
			
			sld = characterFromID("W_ChinamanGuard");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 7);
			sld.lifeday = 0;
			PlayVoice("interface\_EvEnemy1.wav");
			pchar.questTemp.Whisper.SmugPatrol = true;	
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
		break;
	}
}
