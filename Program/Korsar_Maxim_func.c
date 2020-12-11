//функции для некоторых вычислений
///ТДМ 2 - от LORD-а. -->
object lpitems;
bool iOther;

//Korsar maxim - выбор приветствия ПГГ в зависимости от пола
string GetPggTavernGreeting(ref rChar)
{
    switch (rChar.sex)
    {
    case "skeleton":
        return "skeleton";
    break;
	
    case "man":
        return "Gr_Tavern_Mate";
    break;
	
    case "woman":
        return "Gr_Woman_Citizen";
    break;
    }
}

//LORD - выбор диалога ПГГ в зависимости от пола
string GetPGGDialog(ref rChar)
{
    switch (rChar.sex)
    {
    case "skeleton":
        return "pgg_dialog.c";
    break;
    case "man":
        return "pgg_dialog.c";
    break;
    case "woman":
        return "pgg_dialog_town.c";
    break;
    }
}

//бонусы у итемов
/*
itm.bonus.addhp - на сколько увеличить максимум хп
itm.bonus.addenergy - макс энергии
itm.bonus.addmw - переносимый вес
*/
void LORD_RemoveEquip(ref chref, string sItemID)
{
	aref arItm;

	if( Items_FindItem(sItemID, &arItm)<0 )	return;
	
	if(CheckAttribute(arItm, "bonus"))
	{
		if(CheckAttribute(arItm, "bonus.addhp"))
		{
			if(CheckAttribute(chref, "bonusfromitems.addhp"))
			{
				chref.bonusfromitems.addhp = stf(chref.bonusfromitems.addhp) - stf(arItm.bonus.addhp);
			}
			if(CheckAttribute(chref, "bonusfromitems.realhp"))
			{
				LAi_SetHP(chref, stf(chref.chr_ai.hp) - stf(arItm.bonus.addhp), stf(chref.bonusfromitems.realhp));
			}else{
				LAi_SetHP(chref, stf(chref.chr_ai.hp) - stf(arItm.bonus.addhp), stf(chref.chr_ai.hp_max));
			}
		}
		if(CheckAttribute(arItm, "bonus.addenergy"))
		{
			if(CheckAttribute(chref, "bonusfromitems.addenergy"))
			{
				chref.bonusfromitems.addenergy = stf(chref.bonusfromitems.addenergy) - stf(arItm.bonus.addenergy);
			}
			SetEnergyToCharacter(chref);
		}
		if(CheckAttribute(arItm, "bonus.addmw"))
		{
			if(CheckAttribute(chref, "bonusfromitems.addmw"))
			{
				chref.bonusfromitems.addmw = stf(chref.bonusfromitems.addmw) - stf(arItm.bonus.addmw);
			}
		}
	}
}
void LORD_Add_Equip(ref chref, string sItemID)
{
	aref arItm;
	float temp = 0;
	if( Items_FindItem(sItemID, &arItm)<0 )	return;
	
	if(CheckAttribute(arItm, "bonus"))
	{
		if(CheckAttribute(arItm, "bonus.addhp"))
		{
			if(CheckAttribute(chref, "bonusfromitems.addhp"))
			{
				chref.bonusfromitems.addhp = stf(chref.bonusfromitems.addhp) + stf(arItm.bonus.addhp);
			}else{
				chref.bonusfromitems.addhp = stf(arItm.bonus.addhp);
			}
			if(CheckAttribute(chref, "bonusfromitems.realhp"))
			{
				LAi_SetHP(chref, stf(chref.chr_ai.hp) + stf(arItm.bonus.addhp), stf(chref.bonusfromitems.realhp));
			}else{
				LAi_SetHP(chref, stf(chref.chr_ai.hp) + stf(arItm.bonus.addhp), stf(chref.chr_ai.hp_max));
			}
		}
		if(CheckAttribute(arItm, "bonus.addenergy"))
		{
			if(CheckAttribute(chref, "bonusfromitems.addenergy"))
			{
				chref.bonusfromitems.addenergy = stf(chref.bonusfromitems.addenergy) + stf(arItm.bonus.addenergy);
			}else{
				chref.bonusfromitems.addenergy = stf(arItm.bonus.addenergy);
			}
			SetEnergyToCharacter(chref);
		}
		if(CheckAttribute(arItm, "bonus.addmw"))
		{
			if(CheckAttribute(chref, "bonusfromitems.addmw"))
			{
				chref.bonusfromitems.addmw = stf(chref.bonusfromitems.addmw) + stf(arItm.bonus.addmw);
			}else{
				chref.bonusfromitems.addmw = stf(arItm.bonus.addmw);
			}
		}
	}
}
///ТДМ 2 - от LORD-а. <--

/// Korsar Maxim --> (Выдача рандомного оружия по качеству (бедное, нормальное, хорошее b отличное))
string GiveRandomBladeByType(string sType)
{
	switch(sType)
	{
    string blade = "blade2";
	case "Poor":
	   switch(rand(9))
	   {
		    case 0: blade = "blade5"; break;
		    case 1: blade = "blade2"; break;
		    case 2: blade = "blade1"; break;
	    	case 3: blade = "blade4"; break;
		    case 4: blade = "topor3"; break;
		    case 5: blade = "blade3"; break;
		    case 6: blade = "blade10"; break;
		    case 7: blade = "blade35"; break;
		    case 8: blade = "topor1"; break;
		    case 9: blade = "blade17"; break;
	    }
	break;
	
	case "ordinary":
		switch(rand(7))
	    {
			case 0: blade = "blade6"; break;
			case 1: blade = "blade9"; break;
			case 2: blade = "blade7"; break;
			case 3: blade = "blade12"; break;
			case 4: blade = "blade18"; break;
			case 5: blade = "blade8"; break;
			case 6: blade = "blade11"; break;
			case 7: blade = "blade16"; break;
		}
	break;
	
	case "good":
		switch(rand(6))
	    {
			case 0: blade = "blade19"; break;
			case 1: blade = "blade22"; break;
			case 2: blade = "blade31"; break;
			case 3: blade = "blade34"; break;
			case 4: blade = "blade15"; break;
			case 5: blade = "blade21"; break;
			case 6: blade = "topor2"; break;
		}
	break;
	
	case "excellent":
		switch(rand(10))
	    {
			case 0: blade = "blade28"; break;
			case 1: blade = "blade23"; break;
			case 2: blade = "blade27"; break;
			case 3: blade = "blade30"; break;
			case 4: blade = "blade24"; break;
			case 5: blade = "blade25"; break;
			case 6: blade = "blade26"; break;
			case 7: blade = "blade32"; break;
			case 8: blade = "blade13"; break;
			case 9: blade = "blade20"; break;
			case 10: blade = "blade33"; break;
	    }
	break;
	}
	
	return blade;
}
/// Korsar Maxim <--

void TestVoid()
{
	Log_info("Файл 'Korsar_Maxim_func.c' может обновлятся без начала новой игры.");
}