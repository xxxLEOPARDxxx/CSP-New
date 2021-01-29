
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
		case "First time":
			NextDiag.TempNode = "First time";
			dialog.text = LinkRandPhrase("Приветсвую вас! Быть кладовщиком непросто...", "Эх, тоска тут смертная!", "Эх, черт возьми, чем бы заняться?..");
			link.l1 = LinkRandPhrase("Конечно!", "Понимаю...", "Да, проблемы у тебя серьезные...");
			link.l1.go = "exit";
			link.l2 = "Здравствуй, " + NPChar.name + ". Я пришёл поинтересоваться делами склада, а возможно и кое-что оставить на хранение.";
			link.l2.go = "StoreHouse_Details";
			
		break;

		case "StoreHouse_Details":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStoreHouse(STORE_HOUSE);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
