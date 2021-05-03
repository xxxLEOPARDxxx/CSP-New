
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int Rank = sti(pchar.rank) - 4 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	int Sila = 70 + MOD_SKILL_ENEMY_RATE * 3;
	int DopHP = 60 + MOD_SKILL_ENEMY_RATE * 12;
	int Bonus = sti(pchar.rank);
	if (Bonus <= 6) Bonus = 1;
	if (Bonus >= 7 && Bonus <= 12) Bonus = 1.2;
	if (Bonus >= 13) Bonus = 1.5;
	int Plata1 = 10000 + 1800 * sti(pchar.rank) * Bonus;
	int Plata2 = 20000 + 2000 * sti(pchar.rank) * Bonus;
	pchar.PDM_NK_Plata1.Money = 10000 + 1800 * sti(pchar.rank) * Bonus;
	pchar.PDM_NK_Plata2.Money = 20000 + 2000 * sti(pchar.rank) * Bonus;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":							//Автор Sinistra
			dialog.text = "Эй, "+ GetSexPhrase("парень","деваха") +"! Это мой столик, и я не ищу компании.";
			link.l1 = "Но ты её уже НАШЕЛ. Так что давай поговорим.";
			link.l1.go = "Octavio_1_1";
			link.l2 = "Я не хочу беспокоить тебя. Прощай.";
			link.l2.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\Octavio Lambrini.wav");
		break;
		
		case "Octavio_1_1":
			dialog.text = "Что? Ты осмеливаешься беспокоить Октавио Ламбрини? Кем же ты себя возомнил"+ GetSexPhrase("","а") +"?";
			if (pchar.name == "Питер" && pchar.lastname == "Блад")
			{
				link.l1 = "Да перед тобой сам "+GetFullName(pchar)+". Капитан, благородный разбойник, врач и спаситель Бриджтауна от испанцев. А имя 'Ламбрини' мне ничего не говорит.";
				link.l1.go = "Octavio_1_2";
			}
			if (pchar.name == "Виспер")
			{
				link.l2 = "Да перед тобой сама "+pchar.name+". Капитан, благородная разбойница, путешественница во времени и побывавшая в самом сердце инквизиции. А имя 'Ламбрини' мне ничего не говорит.";
				link.l2.go = "Octavio_1_2";
			}
			if (pchar.name == "Виктория")
			{
				link.l2 = "Да перед тобой сама "+pchar.name+". Весьма отбитая на голову девушка, что в одиночку, только прибыв на Карибы, прибила в честном бою ацтекского Бога мёртвых и она, на секундочку, состоит на службе Голландии, являясь патентованным капером, так что не надо гнать на Голландию, она ещё будет править на Карибах. А имя 'Ламбрини' мне ничего не говорит.";
				link.l2.go = "Octavio_1_2";
			}
			if (pchar.lastname == "Шарп")
			{
				link.l3 = "Моё имя "+GetFullName(pchar)+" - я "+ GetSexPhrase("сын","дочь") +" известного пирата, Николаса Шарпа. А имя 'Ламбрини' мне ничего не говорит.";
				link.l3.go = "Octavio_1_2";
			}
			if (pchar.name == "Шарль" && pchar.lastname == "де Мор")
			{
				link.l4 = "Да перед тобой сам "+GetFullName(pchar)+". Дворянин, капитан, спаситель мира от зловещего Кукулькана. А имя 'Ламбрини' мне ничего не говорит.";
				link.l4.go = "Octavio_1_2";
			}
			if (pchar.lastname == "Хаук")
			{
				link.l6 = "Да перед тобой сам"+ GetSexPhrase("","а") +" "+GetFullName(pchar)+". Капитан, "+ GetSexPhrase("благородный разбойник","благородная разбойница") +" и "+ GetSexPhrase("тот","та") +", кто отправил"+ GetSexPhrase("","а") +" Чёрную Жемчужину на дно. А имя 'Ламбрини' мне ничего не говорит.";
				link.l6.go = "Octavio_1_2";
			}
			if (pchar.lastname == "Кортес")
			{
				link.l7 = "Моё имя "+GetFullName(pchar)+" - я потомок известного конкистадора первооткрывателя, Эрнана Кортеса. А имя 'Ламбрини' мне ничего не говорит.";
				link.l7.go = "Octavio_1_2";
			}
			if (pchar.reputation >= 75)
			{
				link.l8 = "Меня зовут "+GetFullName(pchar)+". Все знают, что я человек чести, и мне можно доверять. А имя 'Ламбрини' мне ничего не говорит.";
				link.l8.go = "Octavio_1_2_DB";
			}
			if (pchar.reputation <= 25)
			{
				link.l8 = "Меня зовут "+GetFullName(pchar)+". И от одного только упоминания моего имени все начинают дрожать и разбегаться в разные стороны. А имя 'Ламбрини' мне ничего не говорит.";
				link.l8.go = "Octavio_1_2_DB";
			}
			if (pchar.reputation >= 0 && pchar.reputation <= 100)
			{
				link.l9 = "Я "+pchar.name+", капитан и "+ GetSexPhrase("наёмник","наёмница") +". А тебя я что-то не припоминаю.";
				link.l9.go = "Octavio_1_2_ostalnoe";
			}
		break;
		
		case "Octavio_1_2":
			if (pchar.name == "Питер" && pchar.lastname == "Блад")
			{	
				dialog.text = "Так это ТЫ тот самый врач, что спас весь город от этих испанцев! Невероятно! Если ты действительно так хорош, как о тебе говорят, то можно и побеседовать.";
			}
			if (pchar.name == "Виспер")
			{
				dialog.text = "Так это ТЫ насолила де Соузу, что весь Сантьяго стоял на ушах! Неплохо! Если ты действительно так хороша, как о тебе говорят, то можно и побеседовать.";
			}
			if (pchar.name == "Виктория")
			{
				dialog.text = "Ты одолела ацтекского Бога мёртвых? Неплохо! Если ты действительно так хороша, как о тебе говорят, то можно и побеседовать.";
			}
			if (pchar.lastname == "Шарп")
			{
				dialog.text = ""+ GetSexPhrase("Сын","Дочь") +" Николаса Шарпа? Неплохо! Я знал твоего отца, давным-давно, когда Ламбрини только что поселились на этом острове. Твой отец был хорошим человеком. Если ты хоть вполовину так же хорош"+ GetSexPhrase("","а") +" как он, то можно и побеседовать.";
			}
			if (pchar.name == "Шарль" && pchar.lastname == "де Мор")
			{
				dialog.text = "Ты бывал в Теночтитлане и победил самого бога? Невероятно! Если ты действительно так хорош, как о тебе говорят, то можно и побеседовать.";
			}
			if (pchar.lastname == "Хаук")
			{
				dialog.text = "Сам"+ GetSexPhrase("","а") +" "+GetFullName(pchar)+"? Здесь, на Тринидаде? Якорь мне в глотку! Если ты действительно так хорош"+ GetSexPhrase("","а") +", как о тебе говорят, то можно и побеседовать.";
			}
			if (pchar.lastname == "Кортес")
			{
				dialog.text = "Родная кровь Эрнана Кортеса? Неплохо! Твой предок был великим человеком, и если ты хоть вполовину так же хорош"+ GetSexPhrase("","а") +" как он, то можно и побеседовать. ";
			}
			link.l1 = "Чем ты занимаешься?";
			link.l1.go = "Octavio_1_3";
		break;
		
		case "Octavio_1_2_ostalnoe":
			dialog.text = "Это твоя проблема, "+ GetSexPhrase("мальчик","девочка") +". Семья Ламбрини хорошо известна на этих островах. Лучше тебе держаться от нас подальше.";
			link.l1 = "Ладно, зайду позже, когда стану более "+ GetSexPhrase("известен","известна") +". (Требуется низкая или высокая репутация)";
			link.l1.go = "exit";
		break;
		
		case "Octavio_1_2_DB":
			dialog.text = ""+GetFullName(pchar)+"? Да, я о тебе наслышан. Если ты действительно так хорош"+ GetSexPhrase("","а") +", как о тебе говорят, то можно и побеседовать.";
			link.l1 = "Чем ты занимаешься?";
			link.l1.go = "Octavio_1_3";
		break;
		
		case "Octavio_1_3":
			dialog.text = "Я и моя семья обделываем дела по всему карибскому архипелагу. Наши прибыли велики, поскольку мы избегаем платить обременительные налоги на свои грузы. Некоторые называют нас контрабандистами.";
			link.l1 = "Ты упомянул свою семью - кто они?";
			link.l1.go = "Octavio_1_4";
		break;
		
		case "Octavio_1_4":
			dialog.text = "А! Семья - это очень важный вопрос для Ламбрини. Мы пришли в Новый Свет с Сицилии сорок лет назад. Тогда мой отец распоряжался нашими действиями здесь. После того, как он умер, я стал главой семьи. Теперь я работаю со своими сыновьями - Фабио и Эмилио, и моим племянником, Цезарио.";
			link.l1 = "Я ищу работу. У тебя есть предложения?";
			link.l1.go = "Octavio_1_5";
		break;
		
		case "Octavio_1_5":
			dialog.text = "Да. Есть проблема, с которой ты можешь нам помочь.";
			link.l1 = "Я слушаю.";
			link.l1.go = "Octavio_1_6";
		break;
		
		case "Octavio_1_6":
			dialog.text = "Мы контрабандисты. И хотя большая часть береговой стражи не против иметь с нами дело, честный человек среди них может доставить немало неприятностей. Да, с большинством из них вполне можно договориться. Но один - исключение. Этот парень, Аркадио де Гальвес, обладает прекрасным кораблём под названием 'Эль Тибурон'. И этот ублюдок не берёт взятки! Так что мы не можем заниматься своим делом рядом с Маракайбо.";
			link.l1 = "И ты хочешь, чтобы я "+ GetSexPhrase("избавился","избавилась") +" от него?";
			link.l1.go = "Octavio_1_7";
			link.l2 = "Меня это не интересует, Октавио. Если ты хоть вполовину так крут, как утверждаешь, ты и сам справишься с этим парнем. Прощай.";
			link.l2.go = "exit";
		break;
		
		case "Octavio_1_7":
			if (pchar.name == "Питер" && pchar.lastname == "Блад")
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Если ты и вправду победил испанцев на Барбадоссе, то с этим парнем ты тем более легко разделаешься.";
			}
			if (pchar.name == "Виспер")
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Если ты и вправду смогла насолить де Соузу, то с этим парнем ты тем более легко разделаешься.";
			}
			if (pchar.name == "Виктория")
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Если ты и вправду победила ацтекского Бога мёртвых, то с этим парнем ты тем более легко разделаешься.";
			}
			if (pchar.lastname == "Шарп")
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Но если ты хоть вполовину так "+ GetSexPhrase("хитёр","хитра") +", каким был твой отец - ты с ним справишься.";
			}
			if (pchar.name == "Шарль" && pchar.lastname == "де Мор")
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Если ты и вправду смог победить Кукулькана, то с этим парнем ты тем более легко разделаешься.";
			}
			if (pchar.lastname == "Хаук")
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Если ты и вправду потопил"+ GetSexPhrase("","а") +" Чёрную Жемчужину, то с этим парнем ты тем более легко разделаешься.";
			}
			if (pchar.lastname == "Кортес")
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, сожги на костре, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. В тебе льётся кровь великого конкистадора, если ты хоть вполовину также "+ GetSexPhrase("хитёр","хитра") +" как и он, то с этим парнем ты тем более легко разделаешься.";
			}
			if (pchar.reputation >= 75)
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Если тебя и вправду зовут "+GetFullName(pchar)+", то с этим парнем ты тем более легко разделаешься.";
			}
			if (pchar.reputation <= 25)
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Если тебя и вправду зовут "+GetFullName(pchar)+", то с этим парнем ты тем более легко разделаешься.";
			}
			link.l1 = "Сколько?";
			link.l1.go = "Octavio_1_8";
			link.l2 = "Меня это не интересует, Октавио. Если ты хоть вполовину так крут, как утверждаешь, ты и сам справишься с этим парнем. Прощай.";
			link.l2.go = "exit";
		break;
		
		case "Octavio_1_8":
			dialog.text = "" + Plata1 + " золотых. И знай - никто не торгуется с Ламбрини!";
			link.l1 = ""+ GetSexPhrase("Согласен","Согласна") +".";
			link.l1.go = "Octavio_1_9";
			link.l2 = "Меня это не интересует, Октавио. Если ты хоть вполовину так крут, как утверждаешь, ты и сам справишься с этим парнем. Прощай.";
			link.l2.go = "exit";
		break;
		
		case "Octavio_1_9":
			if (pchar.name == "Питер" && pchar.lastname == "Блад")
			{
				dialog.text = "Йо-хо, мальчик! Говоришь, как истинный врач. Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.name == "Виспер")
			{
				dialog.text = "Йо-хо, девочка с фиолетовыми волосами! Говоришь, как истинная Виспер. Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.name == "Виктория")
			{
				dialog.text = "Йо-хо, блондиночка! Говоришь, как истинная голландская корсарка. Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.lastname == "Шарп")
			{
				dialog.text = "Йо-хо, "+ GetSexPhrase("мальчик","девочка") +"! Да ты мне напоминаешь своего отца, истинного Шарпа. Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.name == "Шарль" && pchar.lastname == "де Мор")
			{
				dialog.text = "Йо-хо, "+ GetSexPhrase("мальчик","девочка") +"! Говоришь, как истинный дворянин. Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.lastname == "Хаук")
			{
				dialog.text = "Йо-хо, "+ GetSexPhrase("мальчик","девочка") +"! Говоришь, как истинный легендарный Хаук. Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.lastname == "Кортес")
			{
				dialog.text = "Йо-хо, "+ GetSexPhrase("мальчик","девочка") +"! Говоришь, как истинный Эрнан Кортес. Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.reputation >= 75)
			{
				dialog.text = "Йо-хо, "+ GetSexPhrase("мальчик","девочка") +"! Говоришь, как "+ GetSexPhrase("истинный","истинная") +" "+GetFullName(pchar)+". Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.reputation <= 25)
			{
				dialog.text = "Йо-хо, "+ GetSexPhrase("мальчик","девочка") +"! Говоришь, как "+ GetSexPhrase("истинный","истинная") +" "+GetFullName(pchar)+". Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			link.l1 = "До встречи, Октавио.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_1_10_EsheRaz";
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Antonio", "SpaOfficer2", "man", "man", Rank, SPAIN, -1, false));
			sld.name = "Антонио";
			sld.lastname = "де Гальвес";
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Antonio_1_1";
			sld.greeting = "GR_Spainguard";
			FantomMakeCoolFighter(sld, Rank, Sila, Sila, "", "pistol2", DopHP);
			sld.equip.blade = "blade39";
			LAi_SetWarriorType(sld);
			LAi_SetLoginTime(sld, 12.0, 16.00);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.city = "Maracaibo";
			ChangeCharacterAddressGroup(sld,"Maracaibo_town","goto","goto13");
			if (pchar.rank <= 9)
			{
				FantomMakeCoolSailor(sld, SHIP_BRIGHEAVY, "Эль Тибурон", CANNON_TYPE_CULVERINE_LBS16, 100, 100, 100);
			}
			if (pchar.rank >= 10 && pchar.rank <= 14)
			{
				FantomMakeCoolSailor(sld, SHIP_FRIGATEMEDIUM, "Эль Тибурон", CANNON_TYPE_CULVERINE_LBS16, 100, 100, 100);
			}
			if (pchar.rank >= 15 && pchar.rank <= 19)
			{
				FantomMakeCoolSailor(sld, SHIP_DUTCHPINNACE, "Эль Тибурон", CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
			}
			if (pchar.rank >= 20 && pchar.rank <= 25)
			{
				FantomMakeCoolSailor(sld, SHIP_FRIGATE_SAT, "Эль Тибурон", CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
			}
			if (pchar.rank >= 26 && pchar.rank <= 32)
			{
				FantomMakeCoolSailor(sld, SHIP_LINESHIPHEAVY, "Эль Тибурон", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
			}
			if (pchar.rank >= 33)
			{
				FantomMakeCoolSailor(sld, SHIP_SHARK, "Эль Тибурон", CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
			}
			sld.ship.Crew.Morale = Sila;								//Мораль
			ChangeCrewExp(sld, "Sailors", Sila);						//Матросы
			ChangeCrewExp(sld, "Cannoners", Sila);					//Канониры
			ChangeCrewExp(sld, "Soldiers", Sila);						//Солдаты
			sld.DontRansackCaptain = true; 							//Квестовые не сдаются
			sld.SinkTenPercent = false; 								//Уходит с повреждениями
			sld.SaveItemsForDead = true;							//Сохранить предметы после смерти
			sld.DontClearDead = true;								//не убирать труп через 200с
			sld.AnalizeShips = true;
			Group_FindOrCreateGroup("PDM_el_tib");					//Название группы
			Group_SetType("PDM_el_tib", "war");						//Тип поведения
			Group_AddCharacter("PDM_el_tib", "PDM_CL_Antonio");		//Добавить капитана
			
			Group_SetGroupCommander("PDM_el_tib", "PDM_CL_Antonio");
			Group_SetTaskAttack("PDM_el_tib", PLAYER_GROUP);
			Group_SetAddress("PDM_el_tib", "Maracaibo", "quest_ships", "reload_fort1");	//Установить местоположение
			Group_LockTask("PDM_el_tib");
			
			PChar.quest.PDM_CL_Antonio_Ubit.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_CL_Antonio_Ubit.win_condition.l1.character = "PDM_CL_Antonio";
			PChar.quest.PDM_CL_Antonio_Ubit.win_condition = "PDM_CL_Antonio_Ubit";
			
			pchar.questTemp.PDM_CL_Ishem = "Ishem";
			pchar.questTemp.PDM_CL_Tavern = "Tavern";
		break;
		
		case "Octavio_1_10_EsheRaz":
			dialog.text = "Ну, "+ GetSexPhrase("мальчик","девочка") +" - ты прикончил"+ GetSexPhrase("","а") +" этого червяка, де Гальвеса?";
			link.l1 = "Я вырву ему глаза, не сомневайся. Но всему своё время.";
			link.l1.go = "Octavio_1_11_EsheRaz";
		break;
		
		case "Octavio_1_11_EsheRaz":
			dialog.text = "Тогда я дам тебе время, "+ GetSexPhrase("мальчик","девочка") +", но помни - Ламбрини не отличаются терпением.";
			link.l1 = "Будь уверен - я не заставлю тебя долго ждать. Прощай.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_1_10_EsheRaz";
		break;
		
		case "Antonio_1_1":
			dialog.text = "Что вы хотели, сеньор"+ GetSexPhrase("","ита") +"?";
			link.l1 = "Вас зовут Аркадио де Гальвес - и вы из береговой стражи?";
			link.l1.go = "Antonio_1_2";
		break;
		
		case "Antonio_1_2":
			dialog.text = "Да. А вы кто так"+ GetSexPhrase("ой","ая") +"?";
			link.l1 = "Моё имя "+GetFullName(pchar)+".";
			link.l1.go = "Antonio_1_3";
		break;
		
		case "Antonio_1_3":
			dialog.text = "Да, да, я что-то о вас слышал... Зачем вы здесь?";
			link.l1 = "Семья Ламбрини передаёт вам привет! (напасть)";
			link.l1.go = "Antonio_Bitva";
			link.l2 = "Кое-кто хочет убить вас. (предать Ламбрини)";
			link.l2.go = "Antonio_1_4";
			link.l3 = "Мне пора.";
			link.l3.go = "exit";
		break;
		
		case "Antonio_Bitva":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("SPAIN_CITIZENS", LAI_GROUP_PLAYER, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Octavio_2_1":
			dialog.text = "Ну, "+ GetSexPhrase("мальчик","девочка") +" - надеюсь, ты прикончил"+ GetSexPhrase("","а") +" этого червяка, де Гальвеса?";
			link.l1 = "Да. Несчастный ублюдок умолял меня о милосердии, но его мольбы были тщетны.";
			link.l1.go = "Octavio_2_2";
		break;
		
		case "Octavio_2_2":
			if (pchar.name == "Питер" && pchar.lastname == "Блад")
			{
				dialog.text = "Ха, мальчик! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты спаситель Бриджтауна от испанцев. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.name == "Виспер")
			{
				dialog.text = "Ха, девочка! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты напакостила самому де Соузу. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.name == "Виктория")
			{
				dialog.text = "Ха, девочка! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты победила самого Бога мёртвых. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.lastname == "Шарп")
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты "+ GetSexPhrase("сын","дочь") +" Николаса Шарпа, великого пирата. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.name == "Шарль" && pchar.lastname == "де Мор")
			{
				dialog.text = "Ха, мальчик! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты победил самого Кукулькана. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.lastname == "Хаук")
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты "+ GetSexPhrase("тот","та") +", кто потопил"+ GetSexPhrase("","а") +" Чёрную Жемчужину. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.lastname == "Кортес")
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь в тебе течёт кровь Эрнана Кортеса, великого конкистадора. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.reputation >= 75)
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь о тебе все говорят как о честном человеке. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.reputation <= 25)
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь о тебе все говорят как о безжалостном человеке. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			link.l1 = "Да, теперь никто не помешает тебе торговать в Маракайбо, Октавио. Прощай.";
			link.l1.go = "exit";
			sld = CharacterFromID("PDM_Octavio_Lambrini")
			sld.lifeday = 0;
			AddMoneyToCharacter(pchar, sti(Plata1));
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, SPAIN, -6);
			AddCharacterExpToSkill(pchar, "Leadership", 130);
			AddCharacterExpToSkill(pchar, "FencingLight", 130);
			AddCharacterExpToSkill(pchar, "Fencing", 130);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 130);
			AddCharacterExpToSkill(pchar, "Pistol", 130);
			AddCharacterExpToSkill(pchar, "Fortune", 130);
			AddCharacterExpToSkill(pchar, "Sneak", 130);
			AddCharacterExpToSkill(pchar, "Sailing", 130);
			AddCharacterExpToSkill(pchar, "Accuracy", 130);
			AddCharacterExpToSkill(pchar, "Cannons", 130);
			AddCharacterExpToSkill(pchar, "Grappling", 130);
			AddCharacterExpToSkill(pchar, "Defence", 130);
			AddCharacterExpToSkill(pchar, "Repair", 130);
			NextDiag.TempNode = "Octavio_2_3_EsheRaz";
		break;
		
		case "Octavio_2_3_EsheRaz":
			dialog.text = "А, "+pchar.name+"! Я поздравляю тебя с избавлением нас от этого червяка, де Гальвеса! В скором времени я направляюсь в Маракайбо, чтобы заключить контракты с выгодными клиентами.";
			link.l1 = "Удачи!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_2_3_EsheRaz";
		break;
		
		case "Antonio_1_4":
			dialog.text = "И что из этого? Если вы хотели сделать мне сюрприз, то он не удался. Ламбрини хочет меня убить, впрочем, как и остальные контрабандисты были бы не прочь.";
			link.l1 = "Я "+ GetSexPhrase("пришёл","пришла") +" к вам с предложением.";
			link.l1.go = "Antonio_1_5";
		break;
		
		case "Antonio_1_5":
			dialog.text = "Э нет, я не беру взяток от торговцев. И я обязательно доложу о вас сеньору Алькальду!";
			link.l1 = "Ламбрини был прав на счёт вас! (напасть)";
			link.l1.go = "Antonio_Bitva";
			link.l2 = "Что вы сказали бы, если бы я предоставил вам возможность поймать или потопить корабль Ламбрини?";
			link.l2.go = "Antonio_1_6";
			link.l3 = "Что же, тогда прощайте.";
			link.l3.go = "exit";
		break;
		
		case "Antonio_1_6":
			dialog.text = "Я бы отдал за это мою правую руку. Но это невозможно, увы. Он уже подкупил, кажется, каждого таможенника на Карибах. Что я могу сделать в одиночку?";
			link.l1 = "Ламбрини предложил мне помочь ему избавиться от вас. Он уверен, что ему в одиночку с вами не справиться, но я мог бы сделать это.";
			link.l1.go = "Antonio_1_7";
		break;
		
		case "Antonio_1_7":
			dialog.text = "Если вы работаете на контрабандистов, то нам с вами разговаривать не о чем, сеньор. Прощайте.";
			link.l1 = "Э, погодите - вы меня даже не выслушали. Я могу сказать Ламбрини, что утопил"+ GetSexPhrase("","а") +" ваш корабль. После этого, он рано или поздно приплывёт сюда, думая, что ему больше ничего не грозит. А вы сможете подстеречь его в бухте, или рядом с ней.";
			link.l1.go = "Antonio_1_8";
			link.l2 = "Ну тогда прощайте.";
			link.l2.go = "exit";
		break;
		
		case "Antonio_1_8":
			dialog.text = "Любопытно... Этот план может сработать, сеньор"+ GetSexPhrase("","ита") +" "+pchar.name+". А если он сработает, я добьюсь, чтобы сеньор Алькальд щедро вознаградил вас!";
			link.l1 = "И сколько, по-вашему, может Его Превосходительство заплатить за голову Ламбрини?";
			link.l1.go = "Antonio_1_9";
		break;
		
		case "Antonio_1_9":
			dialog.text = "Ну, об этом стоит спросить у Его Превосходительства. Я полагаю, примерно " + Plata2 + ". Наши доходы в последнее время очень снизились из-за контрабандистов.";
			link.l1 = "Думаю, что " + Plata2 + " - это достаточная плата. Итак, я скажу Октавио Ламбрини, что с вами покончено... Когда он приплывёт сюда, мы его здесь сцапаем. Что может быть проще?";
			link.l1.go = "Antonio_1_10";
		break;
		
		case "Antonio_1_10":
			dialog.text = "Как только сообщите Ламбрини о моей смерти - сразу же возвращайтесь ко мне, я буду ждать вас в церкви с 9 утра до часу дня. Мы придумаем, что делать дальше.";
			link.l1 = "Берегите себя, сеньор. Удачи!";
			link.l1.go = "Antonio_1_11";
			NextDiag.TempNode = "Antonio_1_12";
		break;
		
		case "Antonio_1_11":
			sld = CharacterFromID("PDM_Octavio_Lambrini")
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Octavio_3_1";
			DeleteAttribute(pchar, "questTemp.PDM_CL_Tavern");
			DeleteAttribute(pchar, "questTemp.PDM_CL_Ishem");
			PChar.quest.PDM_CL_Antonio_Ubit.over = "yes";
			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Antonio_1_12":
			dialog.text = "Как только сообщите Ламбрини о моей смерти - сразу же возвращайтесь ко мне, я буду ждать вас в церкви с 9 утра до 2 часов дня. Мы придумаем, что делать дальше.";
			link.l1 = "Берегите себя, сеньор. Удачи!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_1_12";
		break;
		
		case "Octavio_3_1":
			dialog.text = "Ну, "+ GetSexPhrase("мальчик","девочка") +" - надеюсь, ты прикончил"+ GetSexPhrase("","а") +" этого червяка, де Гальвеса?";
			link.l1 = "Да. Несчастный ублюдок умолял меня о милосердии, но его мольбы были тщетны.";
			link.l1.go = "Octavio_3_2";
		break;
		
		case "Octavio_3_2":
			if (pchar.name == "Питер" && pchar.lastname == "Блад")
			{
				dialog.text = "Ха, мальчик! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты спаситель Бриджтауна от испанцев. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.name == "Виспер")
			{
				dialog.text = "Ха, девочка! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты напакостила самому де Соузу. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.lastname == "Шарп")
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты "+ GetSexPhrase("сын","дочь") +" Николаса Шарпа, великого пирата. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.name == "Шарль" && pchar.lastname == "де Мор")
			{
				dialog.text = "Ха, мальчик! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты победил самого Кукулькана. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.lastname == "Хаук")
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты "+ GetSexPhrase("тот","та") +", кто потопил"+ GetSexPhrase("","а") +" Чёрную Жемчужину. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.lastname == "Кортес")
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь в тебе течёт кровь Эрнана Кортеса, великого конкистадора. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.reputation >= 75)
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь о тебе все говорят как о честном человеке. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.reputation <= 25)
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь о тебе все говорят как о безжалостном человеке. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			link.l1 = "Да, теперь никто не помешает тебе торговать в Маракайбо, Октавио. Прощай.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_3_3_EsheRaz";
			sld = CharacterFromID("PDM_Octavio_Lambrini")
			sld.lifeday = 0;
			AddMoneyToCharacter(pchar, sti(Plata1));
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, SPAIN, 6);
			AddCharacterExpToSkill(pchar, "Sneak", 160);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			
			sld = CharacterFromID("PDM_CL_Antonio")
			sld.nonTable = true;
			LAi_SetSitType(sld);
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Antonio_2_1";
			ChangeCharacterAddressGroup(sld, "Maracaibo_church", "sit", "sit16");
			LAi_SetLoginTime(sld, 9.0, 13.00);
		break;
		
		case "Octavio_3_3_EsheRaz":
			dialog.text = "А, "+pchar.name+"! Я поздравляю тебя с избавлением нас от этого червяка, де Гальвеса! В скором времени я направляюсь в Маракайбо, чтобы заключить контракты с выгодными клиентами.";
			link.l1 = "Удачи!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_3_3_EsheRaz";
		break;
		
		case "Antonio_2_1":
			dialog.text = "Ола, сеньор"+ GetSexPhrase("","ита") +" "+pchar.name+", как всё прошло?";
			link.l1 = "Октавио Ламбрини поверил в вашу смерть, скорее всего он уже плывёт сюда, в Маракайбо.";
			link.l1.go = "Antonio_2_2";
		break;
		
		case "Antonio_2_2":
			dialog.text = "Отлично. Контрабандисты любят ошиваться в таверне, вам нужно зайти туда и посмотреть, объявился ли он там.";
			link.l1 = "Хорошо, я поищу его в таверне.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_2_3_EsheRaz";
			
			PChar.quest.PDM_CL_PVT.win_condition.l1 = "location";		//Вход в локацию
			PChar.quest.PDM_CL_PVT.win_condition.l1.location = "Maracaibo_tavern";
			PChar.quest.PDM_CL_PVT.win_condition = "PDM_CL_PVT";
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Octavio_Lambrini", "barmen_3", "man", "man", 10, PIRATE, -1, false));
			sld.name	= "Октавио";
			sld.lastname	= "Ламбрини";
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Octavio_4_1";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "sit", "sit_front2");
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Pokupatel", "PGG_Barrows_0", "man", "man", 10, PIRATE, -1, false));
			sld.name	= "Линкольн";
			sld.lastname	= "Бэрроуз";
				
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_1_1";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "sit", "sit_base2");
		break;
		
		case "Antonio_2_3_EsheRaz":
			dialog.text = "Ну что, сеньор"+ GetSexPhrase("","ита") +", вы видели Ламбрини в таверне?";
			link.l1 = "Ещё нет, я как раз туда и собирал"+ GetSexPhrase("ся","ась") +".";
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_2_3_EsheRaz";
		break;
		
		case "Pokupatel_1_1":
			dialog.text = "Чего тебе? Не видишь, я занят"+ NPCharSexPhrase(NPChar,"","а") +"?";
			link.l1 = "Прошу прощения, не хотел"+ GetSexPhrase("","а") +" тебе мешать.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pokupatel_1_1";
		break;
		
		case "Octavio_4_1":
			dialog.text = "(Подслушиваем Октавио. Он в данный момент ведёт диалог со своим предполагаемым клиентом) ...Зачем же?";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_1";
		break;
		
		case "Pokupatel_2_1":
			sld = characterFromID("PDM_CL_Pokupatel");
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 0.0);
			DoQuestFunctionDelay("PDM_CL_Sadis_Pokupatel", 0.06);
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_2_2";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Pokupatel_2_2":
			npchar.lifeday = 0;
			dialog.text = "(обращается к Октавио) Хочу продать то, что не купит ни один торговец на этом острове. В моём трюме лежит товар мечты! Горы сандала, только подумай, а.";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_3";
		break;
		
		case "Pokupatel_2_3":
			sld = characterFromID("PDM_Octavio_Lambrini");
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 0.0);
			DoQuestFunctionDelay("PDM_CL_Sadis_Octavio", 0.06);
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_2_4";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Pokupatel_2_4":
			npchar.lifeday = 0;
			dialog.text = "(обращается к клиенту) Я знаю, с тобой можно иметь дело. Мы будем ждать тебя в месте, называющемся бухта Гуахира.";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_5";
		break;
		
		case "Pokupatel_2_5":
			sld = characterFromID("PDM_CL_Pokupatel");
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 0.0);
			DoQuestFunctionDelay("PDM_CL_Sadis_Pokupatel", 0.06);
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_2_6";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Pokupatel_2_6":
			if (npchar.sex == "woman")
			{
				dialog.text = "(обращается к Октавио) Я обязательно приду, пупсик.";
				link.l1 = "";
				link.l1.go = "Pokupatel_2_7";
			}
			if (npchar.sex == "man")
			{
				dialog.text = "(обращается к Октавио) Я скоро подведу туда корабль, это будет сделка что надо.";
				link.l1 = "";
				link.l1.go = "Pokupatel_2_7";
			}
		break;
		
		case "Pokupatel_2_7":
			sld = characterFromID("PDM_Octavio_Lambrini");
			LAi_CharacterDisableDialog(sld);
			sld = characterFromID("PDM_CL_Pokupatel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "tables", "stay3");
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			sld = CharacterFromID("PDM_CL_Antonio")
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Antonio_5_1";
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		
		case "Antonio_5_1":
			dialog.text = "Сеньор"+ GetSexPhrase("","ита") +" "+pchar.name+", вы очень быстро вернулись. Видели что-нибудь интересное?";
			link.l1 = "Да, Ламбрини уже в городе и чувствует себя очень комфортно. Я сумел"+ GetSexPhrase("","а") +" подслушать его разговор с капитаном, который собирается продать нелегальный и дорогой товар - сандал. Может стоит отправиться в таверну и схватить Ламбрини, тёпленького?";
			link.l1.go = "Antonio_5_2";
		break;
		
		case "Antonio_5_2":
			dialog.text = "Нет! Мы дадим ему провести сделку. Они все соберутся в бухте, вместе с ценным товаром, думая, что им ничего не угрожает. Тут-то появляемся мы и арестовываем всех. А вы смогли узнать, где они собираются вершить свои тёмные дела?";
			link.l1 = "Они собираются в бухте Гуахира.";
			link.l1.go = "Antonio_5_3";
		break;
		
		case "Antonio_5_3":
			dialog.text = "Отлично! Осталось определиться, мы устроим облаву со стороны джунглей и застанем их врасплох, или мы пойдём морем и возьмём на абордаж их корабли?";
			link.l1 = "Пойдём через джунгли.";
			link.l1.go = "Antonio_J_1";
			link.l2 = "Лучше на кораблях, так будет быстрее.";
			link.l2.go = "Antonio_M_1";
		break;
		
		case "Antonio_J_1":
			dialog.text = "(Продолжение следует...)";
			link.l1 = "Вперёд!";
			link.l1.go = "exit";
		break;
		
		case "Antonio_M_1":
			dialog.text = "Тогда не стоит медлить. Держим курс к бухте Гуахира! (Продолжение следует...)";
			link.l1 = "Вперёд!";
			link.l1.go = "exit";
		break;
		
		
	}
}