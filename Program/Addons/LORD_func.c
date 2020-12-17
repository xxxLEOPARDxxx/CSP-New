object lpitems;
bool iOther;

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