void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref PChar = GetMainCharacter();
	string sName = PChar.name + " " + PChar.lastname;
	
	int iBricks = sti(PChar.BuildingColony.Blocks);
	int iPlanks = sti(PChar.BuildingColony.Planks);
	int iMahogany = sti(PChar.BuildingColony.Mahogany);
	int iEbony = sti(PChar.BuildingColony.Ebony);
	int iSlaves = sti(PChar.BuildingColony.Slaves);
	int iFood = sti(PChar.BuildingColony.Food);
			
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Чем могу быть полезен, господин капитан " + sName + "?";
			if(PChar.ColonyBuilding.Stage != "3" && PChar.ColonyBuilding.Action != true)
			{
				link.l1 = "Пожалуй, я заинтересован в ваших услугах.";
				link.l1.go = "Building";
			}
			link.l2 = "Просто хотел вас повидать.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "Hi1":
			dialog.text = "Приветствую, капитан! Нуждаетесь в моих услугах?";
			link.l1 = "Здравствуйте. В каких услугах?";
			link.l1.go = "Hi";
			NextDiag.TempNode = "First time";
		break;

		case "Hi":
			dialog.text = "Ах, вы наверное не знаете. Я - известный в этом архипелаге архитектор. Я могу начать строительство колонии на одном из необитаемых островов. За моими плечами очень большой опыт, поверьте.";
			link.l1 = "Вот как? Достаточно интересно.";
			link.l1.go = "First time";
		break;

		case "Building":
			dialog.text = "Что именно вы бы хотели?";
			
			if(PChar.ColonyBuilding.Stage == "0")
			{
				link.l1 = "Я хотел бы начать строительство колонии на одном из необитаемых островов.";
				link.l1.go = "ColonyBuilding";
			}
			
			if(PChar.ColonyBuilding.Stage == "1")
			{
				link.l2 = "Я хотел бы расширить свою колонию, которая носит имя ''" + PChar.ColonyBuilding.ColonyName + "''.";
				link.l2.go = "ColonyModification";
			}
			
			if(PChar.ColonyBuilding.Stage == "2")
			{
				link.l3 = "Я хотел бы укрепить свою колонию - возвести для её охраны форт.";
				link.l3.go = "ColonyFortBuildingNoNo";
			}
			
			link.l4 = "Извините, но мне пора. Дела ждут.";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "ColonyBuilding":
			dialog.text = "Хм... Что же. Думаю, для начала нам необходимо осмотреть необитаемые острова для пригодности на постройку колонии. Кроме того, работа моя, конечно, не бесплатная, и оплата будет составлять "+(1500000*MOD_SKILL_ENEMY_RATE)+" пиастров. К тому же, с вами находится грамотный техник. Вместе с ним мы сможем существенно сократить затраты по деньгам, если, конечно, он мне поможет. Что скажете?";
			if(sti(PChar.money) >= 1500000 * MOD_SKILL_ENEMY_RATE)
			{
				link.l1 = "Я согласен.";
				link.l1.go = "ColonyBuilding_1";
			}
			else
			{
				link.l2 = "Пока я не располагаю такими деньгами.";
				link.l2.go = "exit";
			}
			link.l3 = "Извините, мне пора.";
			link.l3.go = "exit";
		break;

		case "ColonyBuilding_1":
			AddMoneyToCharacter(PChar, -1500000 * MOD_SKILL_ENEMY_RATE);
			dialog.text = "Тогда в кратчайшие сроки нам необходимо освидетельствовать необитаемые острова.";
			link.l1 = "Постараюсь отплыть как можно быстрее!";
			link.l1.go = "ColonyBuilding_exit";
		break;

		case "ColonyBuilding_2":
			dialog.text = "Господин капитан. Тщательно обследовав этот остров, я пришёл к выводу, что это именно то место, где следует начинать постройку колонии. Разведчики обнаружили признаки неких месторождений, а это может быть экономически выгодным для колонии. К тому же, здесь наиболее плодородная почва из всех посещённых нами островов.";
			link.l1 = "Ты что, сухопутная крыса, думаешь, я там буду ананасы с кофе выращивать? Я корсар, а не земледелец!";
			link.l1.go = "ColonyBuilding_2_1";
		break;

		case "ColonyBuilding_2_1":
			dialog.text = "Да?! А как же вы собираетесь добывать пропитание для жителей колонии? Лихо постреливая из своих пушечек по проплывающим мимо кораблям, требуя провизию? В таком случае все либо все передохнут с голоду, либо вас за такое безрассудство приберёт к рукам любая из держав!";
			link.l1 = "Но-но, поаккуратней, архитекторишко.. Ну погорячился я слегка!";
			link.l1.go = "ColonyBuilding_2_2";
		break;

		case "ColonyBuilding_2_2":
			dialog.text = "А вы не учите меня моему делу. Я же не учу вас глотки резать.";
			link.l1 = "Кхе.. Что дальше?";
			link.l1.go = "ColonyBuilding_3";
		break;

		case "ColonyBuilding_3":
			dialog.text = "Теперь мне потребуются некоторые товары, необходимые для постройки колонии. Кирпичи - " + iBricks + " шт., доски - " + iPlanks + " шт., красное дерево - " + iMahogany + " шт., чёрное дерево - " + iEbony + " шт., провиант - " + iFood + " шт., и " + iSlaves + " рабов. Как только все товары будут доставлены, мы приступим к строительству.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "ColonyBuilding_4";
			AddDialogExitQuest("ColonyBuildingCayman");
		break;

		case "ColonyBuilding_4":
			dialog.text = "Что вы хотели, капитан?";
			if(sti(PChar.BuildingColony.Blocks) == 0 && sti(PChar.BuildingColony.Planks) == 0 && sti(PChar.BuildingColony.Mahogany) == 0 && sti(PChar.BuildingColony.Ebony) == 0 && sti(PChar.BuildingColony.Slaves) == 0 && sti(PChar.BuildingColony.Food) == 0)
			{
				dialog.text = "С радостью сообщаю вам, господин капитан, что все необходимые товары доставлены. Мы начинаем строительство! По моим подсчётам строительство будет идти чуть более месяца.";
				link.l1 = "Это не может ни радовать! Буду с нетерпением ждать окончания строительства.";
				link.l1.go = "exit";
				AddDialogExitQuest("ColonyBuilding_1");
				NextDiag.TempNode = "ColonyBuilding_6";
			}
			else
			{			
				link.l1 = "Я бы хотел передать вам необходимые товары.";
				link.l1.go = "ColonyBuilding_5";
				NextDiag.TempNode = "ColonyBuilding_4";
			}
		break;

		case "ColonyBuilding_5":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchColonyBuilding(false, false);
		break;

		case "ColonyBuilding_6":
			dialog.text = "А-а, это вы, господин капитан! Строительство идёт полным ходом!";
			link.l1 = "До встречи.";
			link.l1.go = "exit";
		break;

		case "ColonyBuilding_7":
			dialog.text = "Добрый день, господин капитан! С удовольствием вам сообщаю, что строительство вашей колонии завершено! Если вам снова понадобятся мои услуги, вы сможете найти меня в Вашем поселении.";
			link.l1 = "Отлично, господин " + NPChar.name + " " + NPChar.lastname + ". А теперь прошу меня извинить - дела ждут.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ColonyBuilding_8";
			AddDialogExitQuest("ColonyBuilding_3");
		break;

		case "ColonyBuilding_exit":
			AddDialogExitQuest("ColonyBuilding");
			PChar.ColonyBuilding.Architector = NPChar.id;
			NextDiag.TempNode = "ColonyBuilding_8";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ColonyBuilding_8":
			dialog.text = "Доброго времени суток, " + sName + ".";
			link.l1 = "До встречи.";
			link.l1.go = "exit";
		break;

		//---------------------------------------------------------------------------------------------------------

		case "ColonyModification":
			dialog.text = "Хм... Это вполне решаемая задача. Но вы должны понимать, это будет стоить Вам больших затрат. Сначала нам необходимо встретиться в бухте, что неподалёку, и обсудить все детали предстоящего строительства.";
			link.l1 = "Хорошо, до встречи.";
			link.l1.go = "ColonyModification_exit";
		break;

		case "ColonyModification_1":
			dialog.text = "Вот и вы, капитан. Что же, приступим. Перед тем, как мы начнём наше строительство, мы должны определиться с архитектурой будущего города и его зданий.";
			link.l1 = "Хм... Давайте посмотрим...";
			link.l1.go = "ColonyModification_6";
			NextDiag.TempNode = "ColonyModification_5";
		break;

		case "ColonyModification_2":
			AddQuestRecord("ColonyBuilding", "8");
			dialog.text = "Отлично, капитан. И, сразу вам хочу сообщить, что мне понадобятся следующие товары для строительства - кирпичи - " + iBricks + " шт., доски - " + iPlanks + " шт., красное дерево - " + iMahogany + " шт., чёрное дерево - " + iEbony + " шт., провиант - " + iFood + " шт., и " + iSlaves + " рабов. Когда всё это будет доставлено, мы приступим к строительству.";
			link.l1 = "Постараюсь доставить всё необходимое как можно скорее.";
			link.l1.go = "ColonyModification_3";
			LAi_SetPlayerType(PChar);
			LAi_SetStayType(CharacterFromID("Builder"));
		break;

		case "ColonyModification_3":
			dialog.text = "Что вы хотели, капитан?";
			if(sti(PChar.BuildingColony.Blocks) == 0 && sti(PChar.BuildingColony.Planks) == 0 && sti(PChar.BuildingColony.Mahogany) == 0 && sti(PChar.BuildingColony.Ebony) == 0 && sti(PChar.BuildingColony.Slaves) == 0 && sti(PChar.BuildingColony.Food) == 0)
			{
				dialog.text = "С радостью сообщаю вам, господин капитан, что все необходимые товары доставлены и что мы начинаем строительство. По моим подсчётам строительство будет идти чуть более, чем полтора месяца.";
				link.l1 = "Буду с нетерпением ждать окончания строительства.";
				link.l1.go = "exit";
				AddDialogExitQuest("ColonyModification_2");
				NextDiag.TempNode = "ColonyBuilding_6";
			}
			else
			{			
				link.l1 = "Я бы хотел передать вам необходимые товары.";
				link.l1.go = "ColonyBuilding_5";
				NextDiag.TempNode = "ColonyModification_3";
			}
		break;
		
		case "ColonyModification_4":
			dialog.text = "С радостью сообщаю, что расширение колонии ''" + PChar.ColonyBuilding.ColonyName + "'' завершено! С вами было приятно работать, господин капитан. Пожалуй, я побуду тут ещё какое-то время. Если вы захотите снова меня найти - я буду в порту.";
			link.l1 = "Благодарю вас, " + NPChar.name + ".";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuest("ColonyModification_4");
		break;

		case "ColonyModification_5":
			dialog.text = "Это вы, капитан " + sName + "? Ещё раз обсудим детали строительства?";
			link.l1 = "Да, хочу ещё раз определиться с архитектурой города и зданий.";
			link.l1.go = "ColonyModification_6";
			link.l2 = "Нет, просто хотел Вас навестить.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ColonyModification_5";
		break;

		case "ColonyModification_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchColonyBuilding(true, true);
		break;

		case "ColonyModification_exit":
			PChar.quest.ColonyModification_5.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ColonyModification_5.win_condition.l1.location = PChar.location;
			PChar.quest.ColonyModification_5.win_condition = "ColonyModification_5";
		
			LAi_SetCitizenType(NPChar);
			AddDialogExitQuest("ColonyModification");
			NextDiag.TempNode = "ColonyBuilding_8";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//---------------------------------------------------------------------------------------------------------

		case "ColonyBuilding_Dominica":
			dialog.text = "Слишком рискованно находиться между островами Франции и Англии - каждая не упустит шанса сделать такой лакомый кусочек своим, а вы окажетесь среди двух огней!";			
			link.l1 = "Пожалуй, вы правы. Нужно исследовать дальше...";
			link.l1.go = "exit";
			AddDialogExitQuest("ColonyBuildingDominica");
		break;

		case "ColonyBuilding_Terks":
			dialog.text = "Нет, что вы, Тёркс находится слишком рядом с местом пристанища проклятых пиратов, и было бы безумием строить колонию у них под носом!";
			link.l1 = "Пожалуй, вы правы. Нужно исследовать дальше...";
			link.l1.go = "exit";
			AddDialogExitQuest("ColonyBuildingTerks");
		break;

		//---------------------------------------------------------------------------------------------------------

		case "ColonyFortBuildingNoNo":
			dialog.text = "Хм... Не хочется вас огорчать, капитан, но местность острова не позволяет возвести фортификацию. Могу вам предложить постройку своеобразной охранной базы - она позволит иметь внушительный гарнизон, способный дать отпор любому сопернику, а также создаст благоприятные условия для выставления хорошей защиты береговой линии\n Кроме того, создание охранной базы закроет все подходы к колонии с суши, что значительно усилит охрану и в данном случае, то есть при попытках нападения вражеских отрядов на ваш город с суши. Что думаете, капитан?";
			link.l1 = "Колонию обязательно необходимо защитить. Поэтому нам следует подробнее обговорить детали постройки защитной базы.";
			link.l1.go = "ColonyFortBuilding";
			link.l2 = "Извините, мне пора.";
			link.l2.go = "exit";
		break;

		case "ColonyFortBuilding":
			dialog.text = "Я с радостью помогу вам. Но это вам будет стоить немалых затрат. За свою работу я хочу получить "+(200000*MOD_SKILL_ENEMY_RATE)+" золотых.";
			if(sti(PChar.money) >= 200000 * MOD_SKILL_ENEMY_RATE)
			{
				link.l1 = "Я согласен.";
				link.l1.go = "ColonyFortBuilding_1";
			}
			else
			{
				link.l2 = "Пока я не располагаю такими деньгами.";
				link.l2.go = "exit";
			}
			link.l3 = "Извините, мне пора.";
			link.l3.go = "exit";
		break;

		case "ColonyFortBuilding_1":
			dialog.text = "Отлично, капитан! Встретимся в месте под названием ''Пустынный пляж'' - там то и будет заложен фундамент нашего охранного строения.";
			link.l1 = "До встречи.";
			link.l1.go = "ColonyFortBuilding_to_port";
			AddDialogExitQuest("ColonyFortBuilding_1");
		break;

		case "ColonyFortBuilding_2":
			dialog.text = "Отлично, капитан! Встретимся в месте под названием ''Пустынный пляж''.";
			link.l1 = "До встречи.";
			link.l1.go = "ColonyFortBuilding_to_port";
		break;

		case "ColonyFortBuilding_3":
			AddMoneyToCharacter(PChar, -200000 * MOD_SKILL_ENEMY_RATE);
			dialog.text = "Для строительства нам понадобяться следующие товары: Кирпичи - " + iBricks + " шт., доски - " + iPlanks + " шт., красное дерево - " + iMahogany + " шт., чёрное дерево - " + iEbony + " шт., провиант - " + iFood + " шт., и " + iSlaves + " рабов.";
			link.l1 = "Постараюсь доставить все необходимое как можно скорее.";
			link.l1.go = "ColonyFortBuilding_to_start_transfer_goods";
			AddDialogExitQuest("ColonyFortBuilding_4");
		break;

		case "ColonyFortBuilding_4":
			dialog.text = "Что вы хотели, капитан?";
			if(sti(PChar.BuildingColony.Blocks) == 0 && sti(PChar.BuildingColony.Planks) == 0 && sti(PChar.BuildingColony.Mahogany) == 0 && sti(PChar.BuildingColony.Ebony) == 0 && sti(PChar.BuildingColony.Slaves) == 0 && sti(PChar.BuildingColony.Food) == 0)
			{
				dialog.text = "С радостью сообщаю вам, господин капитан, что все необходимые товары доставлены. Мы начинаем возведение базы! Если ничего сверхестественного не произойдёт, то месяца через полтора на этом месте вы увидите совсем иную картину.";
				link.l1 = "Хорошо, господин " + NPChar.name + " " + NPChar.lastname + ".";
				link.l1.go = "exit";
				AddDialogExitQuest("ColonyFortBuilding_5");
				NextDiag.TempNode = "ColonyFortBuilding_5";
			}
			else
			{			
				link.l1 = "Я бы хотел передать вам необходимые товары.";
				link.l1.go = "ColonyBuilding_5";
				NextDiag.TempNode = "ColonyFortBuilding_4";
			}
		break;

		case "ColonyFortBuilding_5":
			dialog.text = "А-а, это вы, господин капитан! Строительство идёт полным ходом!";
			link.l1 = "До встречи.";
			link.l1.go = "exit";
		break;

		case "ColonyFortBuilding_6":
			dialog.text = "Создание охранной базы для вашей колонии завершено! С вами было приятно работать, господин капитан. Я возвращаюсь домой.";
			link.l1 = "Спасибо вам за работу, господин, " + NPChar.name + " " + NPChar.lastname + ".";
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
			AddDialogExitQuest("ColonyFortBuilding_7");
		break;
		
		case "ColonyFortBuilding_to_port":
			LAi_SetCitizenType(NPChar);
			NextDiag.TempNode = "ColonyBuilding_8";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ColonyFortBuilding_to_start_transfer_goods":
			NextDiag.TempNode = "ColonyFortBuilding_4";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ForSlave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Я так устал - просто с ног валюсь.", "Нет больше сил так жить!"), RandPhraseSimple("Эта работа слишком тяжелая для меня.", "Надсмотрщики уже не оставили живого места на моей шкуре!"));
			link.l1 = RandPhraseSimple("Сочувствую, приятель.", "Мне жаль тебя.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ForSlave";
		break;
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, приятель, когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда мужчины ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял.", "Убираю.");
			}
			link.l1.go = "exit";
		break;
		
	}
}
