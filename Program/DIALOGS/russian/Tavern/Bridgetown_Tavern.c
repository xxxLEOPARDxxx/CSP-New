// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(" акие вопросы?", "„то вам угодно, " + GetAddress_Form(NPChar) + "?"), "—овсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "¬ течение этого дн€ вы уже третий раз говорите о каком-то вопросе...",
                          "ќп€ть вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("я "+ GetSexPhrase("передумал","передумала") +"...", "—ейчас мне не о чем говорить"), "’м, что-то с пам€тью моей стало...",
                      "ƒа уж, действительно в третий раз...", "ƒа нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

