
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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
		
		case "First time":								//Автор Sinistra
			dialog.text = "Посмотрите-ка кто здесь! "+ GetSexPhrase("Великий Пират","Великая Пиратка") +", Ужас Морей и Океанов! Только, чёрт возьми, я забыл твоё имя! Эй, ты действительно "+ GetSexPhrase("такой ужасный человек","такая ужасная девушка") +", как люди говорят?";
			link.l1 = "О, я думаю, что на самом деле я вполне "+ GetSexPhrase("обычный ужасный человек","обычная ужасная девушка") +".";
			link.l1.go = "Vstrecha_1";
			link.l2 = "Нет. Честно говоря, на самом деле я "+ GetSexPhrase("кроткий и мягкий","кроткая и магкая") +". Извините, но я бы "+ GetSexPhrase("предпочёл","предпочла") +" ненадолго обратиться в паническое бегство.";
			link.l2.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\James Callow.wav");
		break;
			
		case "Vstrecha_1":
            dialog.text = "Знаешь, кто я? Я Джеймс Кэллоу! Я ограбил испанскую колонию Сан Хуан и взял на абордаж флагман французской эскадры! Разве я не чудовище? Ты не дрожишь при виде меня?";
            link.l1 = "Да нет. Я и "+ GetSexPhrase("сам ужасен","сама ужасна") +", и мне тоже случалось кое-чего пограбить в своё время.";
			link.l1.go = "Vstrecha_2";
		break;	
		
		case "Vstrecha_2":
            dialog.text = "Отлично! Знаешь, "+ GetSexPhrase("юноша","девица") +", мне "+ GetSexPhrase("нужен такой человек","нужна такая") +", как ты. Я задумал авантюру, в которую не хочется ввязываться одному. Из того, что я о тебе слышал, я делаю вывод, что как раз ты-то мне и "+ GetSexPhrase("нужен","нужна") +". Что скажешь, "+ pchar.name +"?";
            link.l1 = "А что за авантюру ты планируешь, Джимми?";
			link.l1.go = "Vstrecha_3";
		break;

		case "Vstrecha_3":
            dialog.text = "Ты веришь в привидений, "+ GetSexPhrase("приятель","подруга") +"? Веришь в злых духов, что приносят несчастье?";
			link.l1 = "Я не верю в эту чепуху. Только дети и старики считают, что духи могут вмешиваться в человеческую жизнь.";
			link.l1.go = "Ne_Veru_1";
            link.l2 = "Мне приходилось слышать рассказы о духах и привидениях. (сесть за стол)";
			link.l2.go = "Vstrecha_4";
		break;
		
		case "Ne_Veru_1":
            dialog.text = "Ты слишком молод"+ GetSexPhrase("","а") +", чтобы понимать подобные вещи, "+ GetSexPhrase("юноша","девушка") +". Тебе бы побольше жизненного опыта, тогда бы ты понял"+ GetSexPhrase("","а") +", что иногда истории, которые рассказывают в тавернах, это не просто вымысел и хвастовство. В некоторых случаях они бывают даже слишком правдивыми.";
			link.l1 = "Знаешь, похоже, что у тебя с головой не всё в порядке, Джеймс. Лучше я оставлю тебя здесь. Прощай.";
			link.l1.go = "exit";
			NextDiag.TempNode = "VstrechNetAgain_1";
		break;
		
		case "Vstrecha_4":
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "sit", "sit_front3");
			LAi_SetSitType(pchar);
			LAi_SetSitType(npchar);
			locCameraTarget(PChar)
            locCameraFollow();
            dialog.text = "Что ж, а я скажу тебе: все эти истории - чистая правда. Есть вещи, которые я никак иначе не могу объяснить. Я нашёл одну штуковину, и готов поклясться, что она проклята!";
            link.l1 = "Правда? И что заставляет тебя верить в это? Ты можешь пощупать этого духа? Или это проклятие является тебе по ночам и клянётся в собственной зловредности?";
			link.l1.go = "Vstrecha_5";
		break;
		
		case "Vstrecha_5":
            dialog.text = "Это не повод для веселья, "+ pchar.name +". С тех пор, как я раздобыл этого проклятого идола, удача меня покинула. Сначала я попал в шторм неподалеку от Кубы. Потом я взял на абордаж испанский галеон. И знаешь, что я нашёл в трюме? Мешки. Пустые мешки. Ни золота, ни серебра, только эти проклятые мешки! Полные трюмы мешков!";
            link.l1 = "Ха! Небогатый улов. А что потом?";
			link.l1.go = "Vstrecha_6";
		break;
		
		case "Vstrecha_6":
            dialog.text = "Днём позже Армандо де Мутиль, известный охотник за головами, заметил мой корабль и попытался захватить меня в плен. Для него это был последний день на этой земле, но мой корабль был сильно повреждён в битве. Я отправился на Бермуды, чтобы отремонтировать судно, но неудачи по-прежнему преследовали меня.\n"+ 
							"У английского побережья береговая охрана заметила на горизонте мой парус, и мне пришлось отдать всё моё золото капитану брига, чтобы выкупить свою свободу. Только тогда я понял, что было причиной всех этих неудач.";
            link.l1 = "И что же это?";
			link.l1.go = "Vstrecha_7";
		break;
		
		case "Vstrecha_7":
            dialog.text = "Месяц назад я встретил бедного старого индейца. Мы брали свежую воду из источника на одном крошечном островке. Это чучело появилось из-за деревьев. Он бормотал что-то насчёт оскорбления великому Хурукацелитипочтли и мести, которая за этим оскорблением последует. Бормоча, он размахивал этим языческим идолом.\n"+ 
							"Когда я увидел, что статуя сделана из чистого золота и украшена большим изумрудом, я вырвал её из рук индейца.\n"+  
							"Нет, я не так плох, как ты думаешь... я дал ему взамен несколько монет. Но он их не взял. Он сказал, что идол может быть только подарен. Потом он сказал, что дарит мне идола 'вместе со злом в его сердце' и с ещё одним даром.\n"+ 
							"Индеец сказал, что раз уж мне так хочется получить этого идола, то он станет моим навсегда, и я никогда не смогу избавиться от него. Я рассмеялся ему в лицо и отрубил ему голову. Я не боюсь ни Бога, ни чёрта, но теперь я напуган, "+ GetSexPhrase("приятель","подруга") +".";
            link.l1 = "Ты, отрубатель голов старым индейцам? Ты напуган? Ладно, прекрати морочить мне голову! Ха! Просто брось эту штуку в море!";
			link.l1.go = "Vstrecha_8";
		break;
		
		case "Vstrecha_8":
            dialog.text = "Послушай, "+ GetSexPhrase("приятель","подруга") +". Я пытался продать его. Я пытался потерять его. Ничего не выходит. Проклятый идол возвращается в мою каюту, мой мешок, мой шкаф - возвращается ко мне, где бы я ни был. Чёртова штуковина преследует меня! Это какое-то проклятие! Ты говоришь, что не веришь в проклятия - так может ты поможешь мне?";
            link.l1 = "Хммм... Может быть. А почему бы тебе просто не отдать её кому-нибудь? Индеец говорил, идол может быть только подарен.";
			link.l1.go = "Vstrecha_9";
		break;
		
		case "Vstrecha_9":
            dialog.text = "Потому что я не могу отдать его! В этом нет никакого смысла, но... Этот индейский шаман каким-то образом... он усилил мою жадность... Я просто... не могу. Я думаю, это часть того подлого проклятия. Я не могу отдать его! Подумать о том, что я отдам такую вещь и не получу прибыли... это просто... непереносимо! Мне кажется, я просто повешусь, если сделаю это. Но у меня есть план...";
            link.l1 = "Что за план?";
			link.l1.go = "Vstrecha_10"
		break;
		
		case "Vstrecha_10":
            dialog.text = "Я знаю человека, который захочет получить этого идола, едва он увидит его. Это мой самый опасный враг. И это, конечно же, не будет бесприбыльным делом! Если я буду знать, что эта штука в руках у Роджера, это будет величайшая радость в моей жизни. Но я не могу сделать это сам. Роджер слишком хорошо меня знает. Не сомневаюсь, что он ничего не заподозрит, если подарок будет исходить от тебя.";
            link.l1 = "А что я за это получу?";
			link.l1.go = "Vstrecha_11";
		break;
		
		case "Vstrecha_11":
            dialog.text = "Мою благодарность. И я буду сопровождать тебя во всех твоих путешествиях... по крайней мере, некоторое время. Того, кому ты долж"+ GetSexPhrase("ен","на") +" отдать идола, зовут Бортоломью Роджер, он главарь поселения Ле Франсуа, что на Мартинике. Ты поможешь мне, "+ GetSexPhrase("приятель","подруга") +"?";
            link.l1 = "Нет, это будет пустой тратой времени.";
			link.l1.go = "VstrechaNet_1";
			link.l2 = "Да. Я помогу тебе.";
			link.l2.go = "VstrechaDa_1";
		break;
		
		case "VstrechaDa_1":
            dialog.text = "Спасибо тебе, "+ GetSexPhrase("брат","сестра") +". Вот, возьми этого идола, не как дар, а, наоборот, в обмен на твоё обещание передать его моему злейшему врагу, Бортоломью Роджеру. Тьфу... надеюсь, это сработает и завтра я не найду идола у себя под подушкой. Быстрее отнеси его Роджеру, иначе - кто знает? - вдруг он может причинить вред и тебе.";
            link.l1 = "До встречи, брат.";
			link.l1.go = "CodDa_1";
			GiveItem2Character(PChar, "Cursed_idol");
			PlayVoice("Interface\important_item.wav");
			Log_info("Джеймс отдал вам идола");
			NextDiag.TempNode = "VstrechDaAgain_1";
		break;
		
		case "VstrechaNet_1":
			dialog.text = "В таком случае, будь ты проклят"+ GetSexPhrase("","а") +". Пусть тело твоё достанется акулам, а душа - дьяволу!";
            link.l1 = "Это вряд ли. Ладно, не скучай. И смотри, хорошенько позаботься о твоём маленьком идоле. До свидания.";
			link.l1.go = "CodNet_1";
			NextDiag.TempNode = "VstrechNetAgain_1";
		break;
		
		case "CodDa_1":
            ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "tables", "stay1");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();
			SetQuestHeader("PDM_Cursed_Idol");
			AddQuestRecord("PDM_Cursed_Idol", "1");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("PDM_Cursed_Idol", "sSex1", GetSexPhrase("ен","на"));
			sld = CharacterFromID("LeFransua_Mayor")   //ссылается на персонажа
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "none", "");   //переместить
			sld = CharacterFromID("PDM_LeFransua_Mayor_Klon")   //ссылается на клона
			ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "sit", "sit1");   //переместить
			sld.Dialog.Filename = "Quest/PDM/Cursed_Idol.c";
			sld.dialog.currentnode = "Rodjer_1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CodNet_1":
            ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "tables", "stay1");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "VstrechDaAgain_1":
			dialog.text = "Аррхх! Почему ты даром теряешь время? Отнеси идола Роджеру, пока он не принёс тебе несчастья. Я не хочу стать причиной твоих неудач.";
            link.l1 = "Не волнуйся, брат. Твой маленький подарок очень скоро будет у Роджера.";
			link.l1.go = "exit";
		break;
		
		case "VstrechNetAgain_1":
			dialog.text = "Арргх! Это ты! Убирайся отсюда, пока я не оторвал тебе голову!";
            link.l1 = "Терпение, терпение, Джимми. Ты просто сам себя выводишь из равновесия.";
			link.l1.go = "exit";
		break;
		
		case "Rodjer_1":
			dialog.text = "Эй! Ты на моей территории, "+ GetSexPhrase("мальчишка","девчонка") +", так что помалкивай здесь, не то замолчишь навеки. Ты меня понял"+ GetSexPhrase("","а") +"?";
            link.l1 = "Придержи свой гонор, Роджер. Я знаю, где я нахожусь.";
			link.l1.go = "Rodjer_2";
			PlayVoice("Kopcapkz\Voices\PDM\Desmond Ray Beltrop.wav");
		break;
		
		case "Rodjer_2":
			dialog.text = "Прекрасно, не забывай об этом. Что тебе нужно, малявка?";
            link.l1 = "У меня есть для тебя подарок.";
			link.l1.go = "Rodjer_3";
		break;
		
		case "Rodjer_3":
			dialog.text = "Подарок? Покажи-ка мне его.";
            link.l1 = "Это индейский идол. Вот, взгляни. Милая безделушка, правда?";
			link.l1.go = "Rodjer_4";
		break;
		
		case "Rodjer_4":
			dialog.text = "Кто тебя послал?";
            link.l1 = "Никто. Я просто решил"+ GetSexPhrase("","а") +" сделать подарок тому, за кем сила в Ле Франсуа.";
			link.l1.go = "RodjerDa_1";
			link.l2 = "Твой старый друг. Он хотел порадовать тебя этим подарком.";
			link.l2.go = "RodjerPodozren_1";
		break;
		
		case "RodjerPodozren_1":
			dialog.text = "Я не верю тебе, "+ GetSexPhrase("парень","девчонка") +". У меня нет друзей, которые могут прислать мне подарок. Но зато у меня куча врагов, которые готовы прислать мне что-нибудь опасное. Так ты всё-таки настаиваешь, что это подарок мне от старого друга?";
            link.l1 = "Да, потому, что это правда.";
			link.l1.go = "RodjerPodozren_2";
			link.l2 = "Нет... Но я хочу, чтобы ты взял эту безделушку.";
			link.l2.go = "RodjerDa_2";
		break;
		
		case "RodjerPodozren_2":
			dialog.text = "Ты "+ GetSexPhrase("нахален","нахальна") +", "+ GetSexPhrase("сосунок","малявка") +". Убирайся отсюда и прихвати с собой свой подарочек. Можешь отдать его шлюхам в таверне. Возвращайся ко мне, когда научишься разговаривать с человеком, держащим этот город в своём кулаке.";
            link.l1 = "...";
			link.l1.go = "RodjerCod_2";
			NextDiag.TempNode = "RodjerPokapoka_1";
		break;
		
		case "RodjerDa_1":
			dialog.text = "Ха! Ты осознал"+ GetSexPhrase("","а") +", кто управляет этим мелким городишкой. И ты решил"+ GetSexPhrase("","а") +" подольститься ко мне с помощью этого подарка... Мне это нравится!";
            link.l1 = "Ух! Ты буквально читаешь мои мысли. Но согласишься ли ты принять от меня дар?";
			link.l1.go = "RodjerDa_2";
		break;
		
		case "RodjerDa_2":
			dialog.text = "Давай сюда... Аррргх! Какая красивая штука! Да, она мне по вкусу! Что ты хочешь в обмен на свой подарок? Говори, и я сделаю это! Но прежде чем просить, подумай как следует.";
			link.l1 = "Я знаю, что пираты часто оставляют здесь захваченные корабли. Я хочу забрать один из них, и мне нужно твоё разрешение. Заодно, может, подскажешь, какой из них находится в приличном состоянии?";
			link.l1.go = "RodjerVar_1";
			link.l2 = "Мне ничего не нужно.";
			link.l2.go = "RodjerVar_2";
			Log_info("Вы отдали идола Роджеру");
			TakeItemFromCharacter(pchar, "Cursed_idol");
		break;
		
		case "RodjerVar_1":
			dialog.text = "К сожалению, "+ GetSexPhrase("парень","девчонка") +", мне нечего тебе предложить. Но я заберу твою безделушку. Теперь, до свидания.";
			link.l1 = "Э-э... До встречи.";
			link.l1.go = "RodjerCod_1";
			NextDiag.TempNode = "RodjerPokapoka_1";
			ChangeCharacterReputation(pchar, -2);
		break;
		
		case "RodjerVar_2":
			dialog.text = "Я не верю тебе, "+ GetSexPhrase("парень","девчонка") +". Подобные подарки не делаются просто так... Забирай его обратно и убирайся отсюда. Ты слишком "+ GetSexPhrase("глуп","глупа") +", чтобы провести меня. Проваливай!";
			link.l1 = "Но...";
			link.l1.go = "RodjerCod_2";
			GiveItem2Character(PChar, "Cursed_idol");
			Log_info("Роджер вернул вам идола");
			NextDiag.TempNode = "RodjerPokapoka_1";
			ChangeCharacterReputation(pchar, 4);
		break;
		
		case "RodjerPokapoka_1":
			dialog.text = "Что тебе нужно?";
			link.l1 = "Ничего, я ухожу";
			link.l1.go = "exit";
			NextDiag.TempNode = "RodjerPokapoka_1";
		break;
		
		case "RodjerCod_1":
			Pchar.quest.PDM_Callow_RodjerFin.win_condition.l1           = "Location";
        	Pchar.quest.PDM_Callow_RodjerFin.win_condition.l1.location  = "LaVega_Tavern";
        	Pchar.quest.PDM_Callow_RodjerFin.win_condition              = "PDM_Callow_RodjerFin";
			Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition.l1           = "ExitFromLocation";
        	Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition.l1.location  = PChar.location;
        	Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition              = "PDM_Callow_RodjerVozvrat";
			AddQuestRecord("PDM_Cursed_Idol", "2");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("","а"));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "RodjerCod_2":
			if (CheckCharacterItem(Pchar, "patent_fra"))
			{
				Pchar.quest.PDM_Callow_RodjerFin.win_condition.l1           = "Location";
				Pchar.quest.PDM_Callow_RodjerFin.win_condition.l1.location  = "LaVega_Tavern";
				Pchar.quest.PDM_Callow_RodjerFin.win_condition              = "PDM_FraOff_Bitva_1_Posle";
				Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition.l1           = "ExitFromLocation";
				Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition.l1.location  = PChar.location;
				Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition              = "PDM_Callow_RodjerVozvrat";
				AddQuestRecord("PDM_Cursed_Idol", "4");
				AddQuestUserData("PDM_Cursed_Idol", "sSex1", GetSexPhrase("ен","на"));
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
			}
			else
			{
				Pchar.quest.PDM_Callow_RodjerProdolg.win_condition.l1           = "Location";
				Pchar.quest.PDM_Callow_RodjerProdolg.win_condition.l1.location  = "LeFransua_ExitTown";
				pchar.quest.PDM_Callow_RodjerProdolg.function = "PDM_Callow_RodjerProdolg";
				Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition.l1           = "ExitFromLocation";
				Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition.l1.location  = PChar.location;
				Pchar.quest.PDM_Callow_RodjerVozvrat.win_condition              = "PDM_Callow_RodjerVozvrat";
				AddQuestRecord("PDM_Cursed_Idol", "4");
				AddQuestUserData("PDM_Cursed_Idol", "sSex1", GetSexPhrase("ен","на"));
				bDisableFastReload = true;	         	//блокируем быстрое перемещение
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
			}
		break;
		
		case "FraOff_1":
			dialog.text = "А ну стоять, пиратское отродье! Парни, вяжите "+ GetSexPhrase("его","её") +".";
			link.l1 = "Ты совершил ошибку, дружок.";
			link.l1.go = "FraOff_Bitva_1";
		break;
		
		case "FraOff_Bitva_1":
			LAi_LocationFightDisable(loadedLocation, false); //Разрешаем оружие
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("FraEnemy_off")
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");	
			for (i=1; i<=3; i++)
				{
				sld = CharacterFromID("FraEnemy_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");	
				}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);		//стравливаем
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PDM_FraOff_Bitva_1_Posle");
			DialogExit();
		break;
		
		case "CollowRad_1":
			dialog.text = "Ах! Наконец-то ты вернул"+ GetSexPhrase("ся","ась") +". Как идут дела? Ты всё сделал"+ GetSexPhrase("","а") +"?";
			link.l1 = "Конечно. Жадный мерзавец при виде золота потерял последние остатки разума.";
			link.l1.go = "CollowRad_2";
			PlayVoice("Kopcapkz\Voices\PDM\James Callow.wav");
		break;
		
		case "CollowRad_2":
			dialog.text = "Агггх! Какое облегчение! Ты и представить себе не можешь, каким тяжким грузом это было для меня.";
			link.l1 = "Теперь ты свободен от его влияния. Но, я вспоминаю, что ты обещал стать моим офицером... как насчёт этого?";
			link.l1.go = "CollowRad_3";
		break;
		
		case "CollowRad_3":
			dialog.text = "Сказать по чести... Я солгал тебе, чтобы убедить тебя помочь мне. Очень жаль, "+ GetSexPhrase("брат","сестра") +", но я не собираюсь становиться твоим офицером. Возьми себе 10000 пиастров, в уплату за твою услугу...  я негодяй, но меня нельзя назвать неблагодарным негодяем. Прощай, "+ GetSexPhrase("брат","сестра") +".";
			link.l1 = "Почему-то меня это не удивляет. Ну что же - попутного тебе ветра, Кэллоу.";
			link.l1.go = "CollowRadCod_1";
			NextDiag.TempNode = "CollowRadPoka_1";
			AddMoneyToCharacter(pchar, 10000);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			AddCharacterExpToSkill(pchar, "Sneak", 40);
		break;
		
		case "CollowRadPoka_1":
			dialog.text = "Ещё раз спасибо, "+ GetSexPhrase("брат","сестра") +".";
			link.l1 = "До встречи, Кэллоу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CollowRadPoka_1";
		break;
		
		case "CollowRadCod_1":
			Pchar.quest.PDM_Callow_RadPoka.win_condition.l1           = "ExitFromLocation";
        	Pchar.quest.PDM_Callow_RadPoka.win_condition.l1.location  = "LaVega_Tavern";
        	Pchar.quest.PDM_Callow_RadPoka.win_condition              = "PDM_Callow_RadPoka";
			AddQuestRecord("PDM_Cursed_Idol", "3");
			CloseQuestHeader("PDM_Cursed_Idol");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CollowNeRad_1":
			dialog.text = "Ах! Наконец-то ты "+ GetSexPhrase("вернулся","вернулась") +". Как дела? Ты сделал"+ GetSexPhrase("","а") +" это?";
			link.l1 = "У меня для тебя плохие новости. Роджер отказался взять идола.";
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "sit", "sit_front3");
			LAi_SetSitType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();
			PlayVoice("Kopcapkz\Voices\PDM\James Callow.wav");
			link.l1.go = "CollowNeRad_2";
		break;
		
		case "CollowNeRad_2":
			dialog.text = "Дьявол! Дьявол его раздери! Почему он отказался взять его? Я знал, что не следует доверять это дело "+ GetSexPhrase("такому молокососу","такой дуре") +", как ты! Всё это из-за твоей глупости, "+ GetSexPhrase("парень","девица") +"!";
			link.l1 = "Я не собираюсь сносить оскорбления, Джеймс. И я не отношусь к терпеливым людям.";
			link.l1.go = "CollowNeRad_3";
		break;
		
		case "CollowNeRad_3":
			dialog.text = "Арргх! Ты прав"+ GetSexPhrase("","а") +". Что ты теперь собираешься делать? Я эту проклятую вещь назад не возьму. Что если мы отдадим идола кому-нибудь другому?";
			link.l1 = "Хорошая идея... Но кого мы выберем в качестве жертвы?";
			link.l1.go = "CollowNeRad_4";
		break;
		
		case "CollowNeRad_4":
			dialog.text = "Люди говорят, что ростовщик на Тортуге с ума сходит по золоту и драгоценным камням... Может, ему понравится наша вещица? Что ты думаешь?";
			link.l1 = "Нет, у меня идея получше - ты просто забираешь своего поганого идола и оставляешь меня в покое. Меня уже тошнит от этой ерунды!";
			link.l1.go = "CollowOchenNeRad_1";
			link.l2 = "Отлично! Просто подсунем ему эту проклятую статуэтку.";
			link.l2.go = "CollowNeRad_5";
		break;
		
		case "CollowNeRad_5":
			dialog.text = "Тебе придётся снова предложить её в дар... Надеюсь, он более жаден, чем Роджер. Спорю, что он проглотит приманку.";
			link.l1 = "Не волнуйся, на этот раз всё будет хорошо. Сначала я дам ему увидеть статую, и только потом заговорю с ним о деле. Блеск золота ослепит его. После этого он купит идола за любые деньги";
			link.l1.go = "CollowNeRad_6";
		break;
		
		case "CollowNeRad_6":
			if (CheckCharacterItem(Pchar, "patent_fra"))
			{
				dialog.text = "Именно так мне это и представляется. Но будь "+ GetSexPhrase("осторожен","осторожна") +". Если что-нибудь пойдёт не так, тебе придётся пробираться через толпу стражи, чтобы выбраться оттуда.";
				link.l1 = "Я надеюсь, до этого не дойдёт.";
				link.l1.go = "CollowNeRad_7";
			}
			else
			{
				dialog.text = "Именно так мне это и представляется. Но будь "+ GetSexPhrase("осторожен","осторожна") +". Если что-нибудь пойдёт не так, тебе придётся пробираться через толпу стражи, чтобы выбраться оттуда.";
				link.l1 = "Я позабочусь об этом. А если придётся убить одного или двух французов, так ведь не в первый же раз.";
				link.l1.go = "CollowNeRad_7";
			}
		break;
		
		case "CollowNeRad_7":
			dialog.text = "Тогда ступай, "+ GetSexPhrase("брат","сестра") +". Удачи тебе.";
			link.l1 = "До встречи, брат. Я скоро вернусь.";
			link.l1.go = "CollowNeRad_8";
			NextDiag.TempNode = "VstrechEsheAgain_2";
		break;
		
		case "CollowNeRad_8":
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "tables", "stay1");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();
			sld = CharacterFromID("Tortuga_usurer")   //ссылается на персонажа
			ChangeCharacterAddressGroup(sld, "Tortuga_town", "none", "");   //переместить
			sld = CharacterFromID("PDM_Tortuga_usurer_Klon")   //ссылается на клона
			ChangeCharacterAddressGroup(sld, "Tortuga_Bank", "barmen", "stay");   //переместить
			sld.name = "Жюст";
			sld.Dialog.Filename = "Quest/PDM/Cursed_Idol.c";
			sld.dialog.currentnode = "Rostovshik_1";
			AddQuestRecord("PDM_Cursed_Idol", "8");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("лся","лась"));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CollowOchenNeRad_1":
			dialog.text = "Что? Ты что сказал"+ GetSexPhrase("","а") +", "+ GetSexPhrase("мерзавец","мерзавка") +"? А ну-ка повтори! Повтори, я сказал!";
			link.l1 = "Следи за моими губами. Я буду говорить медленно, так что ты всё поймёшь. ТЫ ЗАБИРАЕШЬ СВОЕГО ПОГАНОГО ИДОЛА И ОСТАВЛЯЕШЬ МЕНЯ В ПОКОЕ! Вот твой подарочек. Забирай его. И оставь меня!";
			link.l1.go = "CollowOchenNeRad_2";
		break;
		
		case "CollowOchenNeRad_2":
			dialog.text = "Ты делаешь большую ошибку, "+ GetSexPhrase("глупец","глупая") +"! Очень скоро мы снова встретимся! Очень скоро! Ты, "+ GetSexPhrase("проклятый трусливый дурак","проклятая трусливая дура") +"!";
			link.l1 = "Я буду ждать нашей следующей встречи. Уверен"+ GetSexPhrase("","а") +", что ты доживёшь до неё... если удача тебя не покинет. Ха-ха-ха-ха!";
			link.l1.go = "CollowOchenNeRad_3";
			Log_info("Вы отдали идола Джеймсу");
			TakeItemFromCharacter(pchar, "Cursed_idol");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
			AddCharacterExpToSkill(pchar, "Sneak", -150); 
			ChangeCharacterReputation(pchar, 5);
		break;
		
		case "CollowOchenNeRad_3":
			dialog.text = "...";
			link.l1 = "(Допивает ром)";
			link.l1.go = "CollowOchenNeRad_4";
			sld = CharacterFromID("James_Callow")
			LAi_SetActorType(npchar);   //делает нпс актёром
			ChangeCharacterAddressGroup(npchar, "LaVega_tavern", "tables", "stay1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3);  // идёт в определённый локатор.
		break;
		
		case "CollowOchenNeRad_4":
			AddQuestRecord("PDM_Cursed_Idol", "5");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("лся","лась"));
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "tables", "stay1");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
			locCameraFollow();
			ChangeCharacterAddressGroup(sld, "LaVega_town", "none", "");
			pchar.quest.PDM_Callow_Voina.win_condition.l1 = "location";
			pchar.quest.PDM_Callow_Voina.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PDM_Callow_Voina.function = "PDM_Callow_Voina";
			DialogExit();
		break;
		
		case "VstrechEsheAgain_2":
			dialog.text = "Аррхх! Почему ты даром теряешь время? Отнеси идола ростовщику на Тортуге, пока он не принёс тебе несчастья. Я не хочу стать причиной твоих неудач.";
            link.l1 = "Не волнуйся, брат. Твой маленький подарок очень скоро будет на Тортуге.";
			link.l1.go = "exit";
			NextDiag.TempNode = "VstrechEsheAgain_2";
		break;
		
		case "Rostovshik_1":
			dialog.text = "Бонжур, "+ GetSexPhrase("месье","мадемуазель") +"! Чем я могу быть вам полезен?";
            link.l1 = "Здравствуйте! Я хочу преподнести вам дар. Я слышал"+ GetSexPhrase("","а") +", что вы интересуетесь драгоценными камнями... Что вы скажете по поводу этого идола?";
			link.l1.go = "Rostovshik_2";
			PlayVoice("Kopcapkz\Voices\PDM\France\Nicolas de Montferrat.wav");
		break;
		
		case "Rostovshik_2":
			dialog.text = "О-о-о-о! О, Бог мой! "+ GetSexPhrase("месье","мадемуазель") +" "+pchar.name+"! Как прекрасно! Великолепно! Да этот идол может искупить все десять смертных грехов!";
            link.l1 = "Похоже, он вам нравится. Он ваш.";
			link.l1.go = "Rostovshik_3";
		break;
		
		case "Rostovshik_3":
			dialog.text = "Вы преподнесли мне бесценный подарок, "+ GetSexPhrase("месье","мадемуазель") +" "+pchar.name+". Я вам чрезвычайно благодарен. Я вознаграждаю вас 45000 золотых - никто не скажет, что я - скряга! Если вы хотите знать, "+ GetSexPhrase("месье","мадемуазель") +" "+pchar.name+", я, пожалуй, пошлю этого идола Его Величеству! Я слыхал, что он как раз увлекается такими интересными вещами.";
            link.l1 = "Я очень рад"+ GetSexPhrase("","а") +", что мой подарок оказался так кстати.";
			link.l1.go = "Rostovshik_4";
			AddMoneyToCharacter(pchar, 45000);
			Log_info("Вы подарили идола ростовщику");
			TakeItemFromCharacter(pchar, "Cursed_idol");
		break;
		
		case "Rostovshik_4":
			if (CheckCharacterItem(Pchar, "patent_fra"))
			{
			dialog.text = "Да-да, ваш подарок пришёлся очень ко времени. Но я должен попросить вас уйти. Я хочу полюбоваться... э-э, я хотел сказать, я хочу подумать, как отослать этого идола Его Величеству.";
            link.l1 = "Всего вам хорошего";
			link.l1.go = "Domoi";
			}
			else
			{
			dialog.text = "Да-да, ваш подарок пришёлся очень ко времени. Но я должен попросить вас уйти. Я хочу полюбоваться... э-э, я хотел сказать, я хочу подумать, как отослать этого идола Его Величеству.";
            link.l1 = "(сзади открывается дверь)";
			link.l1.go = "Rostovshik_5";
			bDisableFastReload = true;	         	//блокируем быстрое перемещение
			}			
		break;
		
		case "Rostovshik_5":
			int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
			if (Rank < 1) Rank = 1;
			sld = GetCharacter(NPC_GenerateCharacter("FraEnemy_off", "off_fra_1", "man", "man", Rank, FRANCE, -1, true));
			FantomMakeCoolFighter(sld, sti(pchar.rank), 15, 15, "blade19", "", 20);	
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetActorType(sld);
			sld.dialog.filename   = "Quest/PDM/Cursed_Idol.c";		//Название файла диалога
			sld.dialog.currentnode   = "Rostovshik_Fra_Off_1";				//С какой фразы начинать диалог
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			sld = CharacterFromID("PDM_Tortuga_usurer_Klon")   //ссылается на клона
			ChangeCharacterAddressGroup(sld, "Tortuga_Town", "none", "");   //переместить
			sld = CharacterFromID("Tortuga_usurer")   //ссылается на персонажа
			ChangeCharacterAddressGroup(sld, "Tortuga_Bank", "barmen", "stay");
			DialogExit();
		break;
		
		case "Rostovshik_Fra_Off_1":
			dialog.text = "(обращается к ростовщику) Бонжур, Жюст, я хотел тебя позвать на праздничный ужин... Погодите-ка, я знаю "+ GetSexPhrase("этого человека","эту девушку") +", он"+ GetSexPhrase("","а") +" пират"+ GetSexPhrase("","ка") +"! Это он"+ GetSexPhrase("","а") +" перебил"+ GetSexPhrase("","а") +" наш патруль на Мартинике. СТРАЖА!";
            link.l1 = "И чего встали, подходите. Или испугались меня?";
			link.l1.go = "Rostovshik_Fra_Off_2";
			PlayVoice("Kopcapkz\Voices\PDM\Pete - Town Guard.wav");
		break;
		
		case "Rostovshik_Fra_Off_2":
			LAi_LocationFightDisable(loadedLocation, false); //Разрешаем оружие
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("FraEnemy_off")
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sTemp = "sold_fra_"+(rand(7)+1);
				if (i==12) sTemp = "off_fra_1";
				sld = GetCharacter(NPC_GenerateCharacter("FraEnemy_"+i, sTemp, "man", "man", Rank, FRANCE, -1, true));
				FantomMakeCoolFighter(sld, sti(pchar.rank), 15, 15, "blade7", "", 0);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);		//стравливаем
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PDM_Callow_poradomoy");
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, true);
			DialogExit();
		break;
		
		case "Domoi":
			sld = CharacterFromID("James_Callow")
			sld.dialog.filename = "Quest/PDM/Cursed_Idol.c";
			sld.dialog.currentnode = "Callow_POBEDA_1";
			AddQuestRecord("PDM_Cursed_Idol", "9");
			sld = CharacterFromID("PDM_Tortuga_usurer_Klon")   //ссылается на клона
			ChangeCharacterAddressGroup(sld, "Tortuga_Town", "none", "");   //переместить
			sld = CharacterFromID("Tortuga_usurer")   //ссылается на персонажа
			ChangeCharacterAddressGroup(sld, "Tortuga_Bank", "barmen", "stay");
			DialogExit();
		break;
		
		case "Callow_POBEDA_1":
			dialog.text = "Ах! Наконец-то ты "+ GetSexPhrase("вернулся","вернулась") +". Как дела? Ты это сделал"+ GetSexPhrase("","а") +"?";
            link.l1 = "На этот раз всё прошло гладко. Ростовщик взял идола.";
			link.l1.go = "Callow_POBEDA_2";
			PlayVoice("Kopcapkz\Voices\PDM\James Callow.wav");
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "sit", "sit_front3");
			LAi_SetSitType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();
		break;
		
		case "Callow_POBEDA_2":
			dialog.text = "Агггх! Какое облегчение! Ты и представить себе не можешь, каким тяжким грузом это было для меня.";
            link.l1 = "Теперь ты свободен от его влияния. Но, я вспоминаю, что ты обещал стать моим офицером... как насчёт этого?";
			link.l1.go = "Callow_POBEDA_3";
			AddCharacterExpToSkill(pchar, "Leadership", 50);   	//добавить опыт к авторитету
			AddCharacterExpToSkill(pchar, "FencingLight", 50);     //добавить опыт к лёгкому оружию
			AddCharacterExpToSkill(pchar, "FencingHeavy", 50);     //добавить опыт к тяжёлому оружию
			AddCharacterExpToSkill(pchar, "Fencing", 50);    	    //добавить опыт к среднему оружию
			AddCharacterExpToSkill(pchar, "Pistol", 50);			//добавить опыт к пистолетам
			AddCharacterExpToSkill(pchar, "Fortune", 50);			//добавить опыт к удаче
			AddCharacterExpToSkill(pchar, "Sneak", 50);     	    //добавить опыт к скрытности
		break;
		
		case "Callow_POBEDA_3":
			dialog.text = "Я выполняю то, что обещал. Теперь я буду плавать вместе с тобой, "+ GetSexPhrase("брат","сестра") +"";
            link.l1 = "Увидимся в море, брат.";
			link.l1.go = "Callow_POBEDA_4";
			NextDiag.TempNode = "Callow_Officer_1";
		break;
		
		case "Callow_POBEDA_4":
			dialog.text = "...";
			link.l1 = "(Допивает ром)";
			link.l1.go = "FINAL";
			sld = CharacterFromID("James_Callow")
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.greeting = "GR_Jamescallow";
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Payment = true;										//Оплата труда
			sld.quest.OfficerPrice = sti(pchar.rank)*500
			sld.OfficerWantToGo.DontGo = true;
			sld.reputation = -2;
			LAi_SetImmortal(sld, false);
			sld.HalfImmortal = true; 							    //Контузия
			sld.loyality = MAX_LOYALITY;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			LAi_SetActorType(npchar);   //делает нпс актёром
			ChangeCharacterAddressGroup(npchar, "LaVega_tavern", "tables", "stay1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3);  // идёт в определённый локатор.
		break;
		
		case "FINAL":
			AddQuestRecord("PDM_Cursed_Idol", "10");
			CloseQuestHeader("PDM_Cursed_Idol");
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "tables", "stay1");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
			locCameraFollow();
			ChangeCharacterAddressGroup(sld, "LaVega_town", "none", "");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Callow_Officer_1":
			dialog.text = "Да, капитан?";
            link.l1 = "За мной.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Callow_Officer_1";
		break;
		
	}
}