int FindFoodFromChr(ref chref, ref arFind, int startIdx)
{
	int i;
	aref arItm;
	for(i=startIdx; i<ITEMS_QUANTITY; i++)
	{
		if (i!= -1)
		{
			makearef(arItm,Items[i]);
			if( CheckAttribute(arItm,"Food") && GetCharacterItem(chref,Items[i].id)>0 )
			{
				arFind = arItm;
				return i;
			}
		}
	}
	return -1;
}

bool EnableFoodUsing(ref mc, aref arItm)
{
	bool bEnableUse = false;
	if(CheckAttribute(arItm,"Food.energy") && !CheckAttribute(mc,"chr_ai.noeat")) 
	{
		if(LAi_GetCharacterEnergy(mc) < LAi_GetCharacterMaxEnergy(mc)) 
		{
			return true;
		}
	}
	if(CheckAttribute(mc,"chr_ai.noeat"))
	{
		if(sti(mc.index)==GetMainCharacterIndex() && !CheckAttribute(pchar, "autofood") && !CheckAttribute(pchar, "query_delay"))
		{
			if (CheckAttribute(pchar, "pressedFoodButton"))
			{
				DeleteAttribute(pchar, "pressedFoodButton");
				
				if (!CheckAttribute(pchar, "foodquery"))
				{
					pchar.foodquery = 1;
					pchar.query_delay = 0.1;
					Log_SetStringToLog("����������� ��� ���������� � �������.");
					Log_SetStringToLog("�������:"+pchar.foodquery);
				}
				else
				{
					pchar.foodquery = sti(pchar.foodquery)+1;
					pchar.query_delay = 0.1;
					Log_SetStringToLog("����������� ��� ���������� � �������.");
					Log_SetStringToLog("�������:"+pchar.foodquery);
				}
			}
			
		}
	}
	
	
	
	return false;
}

void DoCharacterUsedFood(ref chref, string itmID)
{
	aref arItm;
	if( Items_FindItem(itmID,&arItm)<0 ) return;
	TakeItemFromCharacter(chref,itmID);

	if( CheckAttribute(arItm,"Food.energy") )
	{
		chref.chr_ai.noeat = 10.0;
		LAi_UseEnergyBottle(chref,stf(arItm.Food.energy));
		if(sti(chref.index)==GetMainCharacterIndex()) 
		{
			Log_SetStringToLog(XI_ConvertString("Energy Up"));
			PlaySound("interface\_Hrust_"+rand(3)+".wav");
			pchar.questTemp.foodcount = sti(pchar.questTemp.foodcount) + 1;
			// ��������� ����������
			if(sti(pchar.questTemp.foodcount) >= 100) UnlockAchievement("AchFood", 1);
			if(sti(pchar.questTemp.foodcount) >= 250) UnlockAchievement("AchFood", 2);
			if(sti(pchar.questTemp.foodcount) >= 500) UnlockAchievement("AchFood", 3);
		}
	}
}
bool IsQuestUsedItem(string itmID)
{
	aref arItm;
	if( Items_FindItem(itmID,&arItm)<0 ) return false;
	if( CheckAttribute(arItm,"price") && sti(arItm.price)>0 ) return false;
	return true;
}

void DoCharacterUsedItem(ref chref, string itmID)
{
	aref arItm;
	if( Items_FindItem(itmID,&arItm)<0 ) return;
	TakeItemFromCharacter(chref,itmID);

	 // Warship 13.06.09 fix - ���� ������ ��������, � ����� ������ (� ����� ������), �� ������ � ������ � ��� �������� �� ����������� ������
	if(CheckAttribute(arItm,"potion.health") && LAi_GetCharacterHP(chref) < LAi_GetCharacterMaxHP(chref))
	{
		LAi_UseHealthBottle(chref,stf(arItm.potion.health));
		if(sti(chref.index)==GetMainCharacterIndex()) {
			Log_SetStringToLog( XI_ConvertString("Health Up"));
			PlaySound("interface\_Glotok_"+rand(3)+".wav");
		}
		// boal
		if( CheckAttribute(arItm,"potion.health.speed") )
		{
			LAi_UseHealthBottleSpeed(chref, stf(arItm.potion.health.speed));
		}
		if(sti(chref.index)==GetMainCharacterIndex()) 
		{
			pchar.questTemp.healcount = sti(pchar.questTemp.healcount) + 1;
			
			// ��������� ����������
			if(sti(pchar.questTemp.healcount) >= 50) UnlockAchievement("heal_bottles", 1);
			if(sti(pchar.questTemp.healcount) >= 100) UnlockAchievement("heal_bottles", 2);
			if(sti(pchar.questTemp.healcount) >= 200) UnlockAchievement("heal_bottles", 3);
		}
	}
	
	// Warship 13.06.09 fix - ���� �� ��������, �� ������ � ������ � ��� ��������
	if(CheckAttribute(arItm,"potion.antidote") && LAi_IsPoison(chref))
	{
		LAi_UseAtidoteBottle(chref);
		if(sti(chref.index)==GetMainCharacterIndex()) {
			Log_SetStringToLog( XI_ConvertString("You are cured from poison") );
		}
		else{
			Log_SetStringToLog(GetFullName(chref) + XI_ConvertString("are cured from poison") );
		}
	}
	
	//navy --> ��������
	if (CheckAttribute(arItm, "potion.drunk"))
	{
		LAi_AlcoholSetDrunk(chref, stf(arItm.potion.drunk), stf(arItm.potion.drunk.time));
		if(sti(chref.index)==GetMainCharacterIndex())
		{
			Log_SetStringToLog( XI_ConvertString("You're get drunk") );
		}
	}
	//<--
	if( CheckAttribute(arItm,"potion.sound") )
	{
		PlaySound(arItm.potion.sound);
	}
}

float MinHealthPotionForCharacter(ref chref)
{
	float ftmp;
	bool isFinded = false;

	for(int n=0; n<ITEMS_QUANTITY; n++)
	{
		if( CheckAttribute(&Items[n],"potion") )
		{
			if(CheckAttribute(&Items[n],"potion.health"))
			{
				if( GetCharacterItem(chref,Items[n].id)>0 )
				{
					if(isFinded)
					{
						if( stf(Items[n].potion.health)<ftmp )
						{
							ftmp = stf(Items[n].potion.health);
						}
					}else{
						ftmp = stf(Items[n].potion.health);
						isFinded = true;
					}
				}
			}
		}
	}
	if(!isFinded) return 0.0;
	return ftmp;
}

string FindHealthForCharacter(ref chref,float fHealth)
{
	string sret = "";
	float fdelta = fHealth + 100.0;
	float ftmp;

	for(int n=0; n<ITEMS_QUANTITY; n++)
	{
		if( CheckAttribute(&Items[n],"potion") )
		{
			if( CheckAttribute(&Items[n],"potion.health") )
			{
				if( GetCharacterItem(chref,Items[n].id)>0 )
				{
					ftmp = stf(Items[n].potion.health);
					if( ftmp<fHealth )	{ftmp = fHealth - ftmp;}
					else	{ftmp = ftmp - fHealth;}
					if(ftmp<fdelta)
					{
						fdelta = ftmp;
						sret = Items[n].id;
					}
				}
			}
		}
	}

	return sret;
}

string FindFoodForCharacter(ref chref,float fHealth)
{
	string sret = "";
	float fdelta = fHealth + 100.0;
	float ftmp;

	for(int n=0; n<ITEMS_QUANTITY; n++)
	{
		if( CheckAttribute(&Items[n],"Food") )
		{
			if( CheckAttribute(&Items[n],"Food.energy") )
			{
				if( GetCharacterItem(chref,Items[n].id)>0 )
				{
					ftmp = stf(Items[n].Food.energy);
					if( ftmp<fHealth )	{ftmp = fHealth - ftmp;}
					else	{ftmp = ftmp - fHealth;}
					if(ftmp<fdelta)
					{
						fdelta = ftmp;
						sret = Items[n].id;
					}
				}
			}
		}
	}
	return sret;
}
int FindPotionFromChr(ref chref, ref arFind, int startIdx)
{
	int i;
	aref arItm;
	for(i=startIdx; i<ITEMS_QUANTITY; i++)
	{
		makearef(arItm,Items[i]);
		if( CheckAttribute(arItm,"potion") && GetCharacterItem(chref,Items[i].id)>0 )
		{
			arFind = arItm;
			return i;
		}
	}
	return -1;
}

int UseBestPotion(ref chref, bool needAntidote)
{
	int i;
	int curPotionID = -1;
	int curPotionHealAmt = 0;
	int newPotionHealAmt = 0;
	bool potionTooGood = false;
	bool bValidPot;
	int reqHealAmt = LAi_GetCharacterMaxHP(chref) - LAi_GetCharacterHP(chref);
	reqHealAmt = makeint(MakeFloat(reqHealAmt) * 1.2)
	if (reqHealAmt <=0 && !needAntidote) 
	{
		return -1;
	}
	
	aref arItm;
	for(i=1; i<ITEMS_QUANTITY; i++)
	{
		makearef(arItm,Items[i]);
		bValidPot = false;

		if (!needAntidote && CheckAttribute(arItm,"potion.health") && !CheckAttribute(arItm,"potion.antidote")) 
		{
			bValidPot = true;
		}
		else 
		{
			if (needAntidote && CheckAttribute(arItm,"potion.antidote")) 
			{
				bValidPot = true;
			}
		}
		if( bValidPot && (GetCharacterItem(chref,arItm.id) > 0))
		{
			if (CheckAttribute(arItm,"potion.health"))
				newPotionHealAmt = arItm.potion.health;
			else
				newPotionHealAmt = 0;
								
			if (potionTooGood) 
			{
				if (newPotionHealAmt < curPotionHealAmt) 
				{
					curPotionID = i;
					curPotionHealAmt = newPotionHealAmt;
				}
			}
			else
			{
				if ((newPotionHealAmt + 1) > curPotionHealAmt) 
				{
					if (curPotionHealAmt == 0 || newPotionHealAmt <= reqHealAmt) 
					{
						curPotionID = i;
						curPotionHealAmt = newPotionHealAmt;
					}
				}
			}
			if (curPotionHealAmt > reqHealAmt) 
			{
				potionTooGood = true;
			}
		}
	}
	
	if (curPotionID > 0) 
	{
		DoCharacterUsedItem(pchar, Items[curPotionID].id);
		return 1;
	}
	else return 0;
}

int FindQuestUsableItem(ref arFind, int startIdx)
{
	int i;
	aref arItm;
	bool bSeaInterface = bSeaActive && !bAbordageStarted;

	if(startIdx<0) startIdx=0;
	for(i=startIdx; i<ITEMS_QUANTITY; i++)
	{
		makearef(arItm,Items[i]);
		if( CheckAttribute(arItm,"quest") && CheckAttribute(arItm,"quest.tex"))// boal 16.03.2004
		{
			if( bSeaInterface && arItm.quest.tex=="QuestCommands" )
			{
				arFind = arItm;
				return i;
			}
		}
	}

	return -1;
}

bool EnablePotionUsing(ref mc, aref arItm)
{
	if( CheckAttribute(arItm,"potion.health") ) {
		if( LAi_GetCharacterHP(mc)<LAi_GetCharacterMaxHP(mc) ) {
			return true;
		}
	}
	
	return false;
}

// Warship 13.06.09 ��� �����������
bool EnableAntidoteUsing(ref _char, aref _item)
{
	if(CheckAttribute(_item, "potion.antidote") && LAi_IsPoison(_char) && CheckCharacterItem(_char, _item.Id))
	{
		return true;
	}
	
	return false;
}

bool FindCharacterAntidote(ref _char, ref _itemId)
{
	int itemIndex;
	ref item;
	
	for(itemIndex = 0; itemIndex < ITEMS_QUANTITY; itemIndex++)
	{
		item = &Items[itemIndex];
		
		if(EnableAntidoteUsing(_char, item))
		{
			_itemID = item.ID;
			return true;
		}
	}
	
	return false;
}

int FindItem(string sItemID)
{
/*
	for(int i = 0; i < TOTAL_ITEMS; i++)
	{
		if(CheckAttribute(Items[i], "ID") && Items[i].id == sItemID)
		{
			return i;
		}
	}
	return -1;
*/	
	// Warship 07.07.09 ������� �� ��������� ������� - ��-����, ��� ������ �������� �������
	return NativeFindCharacter(&Items, sItemID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Warship 08.05.09 ����� ������� ��������� -->
//      Ugeen --> 10.02.10 ��������� ��������� ��������� ��������� � ����� �� ������� ��������������� ���������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ugeen --> ��������� ��������� ������������ ���������
void GenerateGenerableItems()
{
	ref itemRef;

	for(int i = 0; i < ITEMS_QUANTITY; i++)
	{
		itemRef = &Items[i];	
		if(CheckAttribute(itemRef, "id") && CheckAttribute(itemRef, "Generation.Qty") && !CheckAttribute(itemRef, "GeneratedAll"))
		{
			for(int j = 0; j < sti(itemRef.Generation.Qty); j++) 
			{
				GenerateItem(itemRef.id);
			}	
			SetItemPrice(itemRef.id);
			itemRef.GeneratedAll = true;
		}		
	}
}

//ugeen --> ������ ��������� ID ���������������� �������� ��������
string GetGeneratedItem(string _itemId)
{
	int itemsQty = 0;
	String generatedItems[TOTAL_ITEMS];
	
	if(!IsGenerableItem(_itemId)) // ����������� �� �������
	{
		return _itemID;
	}
	
	for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		if(CheckAttribute(&Items[i], "DefItemID") && Items[i].DefItemID == _itemId)
		{
			generatedItems[itemsQty] = Items[i].ID;
			itemsQty++;
		}
	}
		
	if(itemsQty == 0)
	{
		return _itemId; // ������ �� �������
	}
		
	return generatedItems[rand(itemsQty - 1)];
}

//  ������ ������������ ID ���������������� ��������
string GetGeneratedItemNum(string _itemId, int Num)
{
	int itemsQty = 0;
	String generatedItems[TOTAL_ITEMS];
	
	if(!IsGenerableItem(_itemId)) // ����������� �� �������
	{
		return _itemID;
	}
	
	for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		if(CheckAttribute(&Items[i], "DefItemID") && Items[i].DefItemID == _itemId)
		{
			generatedItems[itemsQty] = Items[i].ID;
			itemsQty++;
		}
	}
		
	if(itemsQty == 0 || itemsQty < Num)
	{
		return _itemId; // ������ �� �������
	}
				
	return generatedItems[itemsQty + Num];
}

void SetItemPrice(String _itemId)
{
	int priceMod;
	ref item = &Items[GetItemIndex(_itemId)];
	
	switch(item.FencingType)
	{
		case "FencingLight": // ������ ������
			priceMod = 4;
		break;
		
		case "Fencing": // ������� ������
			priceMod = 5;
		break;
		
		case "FencingHeavy": // ������� ������
			priceMod = 7;
		break;
	}
	if(CheckAttribute(item, "Weight") && stf(item.Weight) > 0.0)
	{
		item.price = priceMod * (stf(item.dmg_min) * stf(item.dmg_max)) / stf(item.Weight);
	}	
}

// �������� �������, ������ ���� ������ ��������
String GenerateItem(String _itemId)
{
	int i, defItemIndex, priceMod;
	int itemsQty = 0;
	int itemIndex = FindFirstEmptyItem();
	float minValue, maxValue, curMinDmg, curMaxDmg, curWeight;
	ref item, realItem;
	String generatedItems[TOTAL_ITEMS];
	
	if(!IsGenerableItem(_itemId)) // ����������� �� �������
	{
		return _itemID;
	}
	
	if(itemIndex == -1) // ���� ��������� ������ - ������ ��������� ������������
	{
		for(i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
		{
			if(CheckAttribute(&Items[i], "DefItemID") && Items[i].DefItemID == _itemId)
			{
				generatedItems[itemsQty] = Items[i].ID;
				itemsQty++;
			}
		}
		
		if(itemsQty == 0)
		{
			return _itemId; // ������ �� �������
		}
		
		return generatedItems[rand(itemsQty - 1)];
	}
	
	defItemIndex = GetItemIndex(_itemId);
	item = &Items[defItemIndex];
	realItem = &Items[itemIndex];
	
	CopyAttributes(realItem, item); // �������� ���������
	
	// Warship 06.06.09 ����������� - ������� ����� ����
	
	// ����������� ����
	minValue = stf(item.Generation.dmg_min.min); // ������ ������� ���������
	maxValue = stf(item.Generation.dmg_min.max); // ������� ������� ���������
	curMinDmg = minValue + frandsmall(maxValue - minValue);
	realItem.dmg_min = curMinDmg;
	
	// ������������ ����
	minValue = stf(item.Generation.dmg_max.min); // ������ ������� ���������
	maxValue = stf(item.Generation.dmg_max.max); // ������� ������� ���������
	curMaxDmg = minValue + frandsmall(maxValue - minValue);
	realItem.dmg_max = curMaxDmg;
	
	// ���
	minValue = stf(item.Generation.Weight.min); // ������ ������� ���������
	maxValue = stf(item.Generation.Weight.max); // ������� ������� ���������
	curWeight = minValue + frandsmall(maxValue - minValue);
	realItem.Weight = curWeight;
	
	// ���������� ����������� ���� �� ���� ������
	switch(item.FencingType)
	{
		case "FencingLight": // ������ ������
			priceMod = 4;
		break;
		
		case "Fencing": // ������� ������
			priceMod = 5;
		break;
		
		case "FencingHeavy": // ������� ������
			priceMod = 7;
		break;
	}
	
	// ������� ����, ���� �����
	if(CheckAttribute(item, "Generation.price"))
	{
		realItem.price = priceMod * (curMinDmg * curMaxDmg) / curWeight;
	}
	
	realItem.ID = _itemId + "_" + itemIndex; // ����� ���� ��������
	realItem.Index = itemIndex; // ����� ������
	realItem.Generated = true; // ��������������� �������
	realItem.DefItemID = _itemId; // �������� ���� � ������ ���������� ��������
	realItem.DefItemIndex = defItemIndex;
	
	return realItem.ID;
}

// ������ ������ ������ ���� ��� ��������
int FindFirstEmptyItem()
{
	for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		if(!CheckAttribute(&Items[i], "ID") || Items[i].ID == "0")
		{
			return i;
		}
	}	
	return -1;
}

// �������� �� ������ �������� � ������ ��
// ����� ����������� ����� - ����� �������� ��� ��� ��������� ����� ��������� (��� ��� � �������)
void RefreshGeneratedItems()
{
	ref item;
	int curLastIndex = FindFirstEmptyItem();

	for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		item = &Items[i];
		
		if(!CheckAttribute(item, "ID")) continue; // ������ ����
		
		RefreshGeneratedItem(item.ID);
	}
	
	trace("����������� �������� ������ ���������");
	trace("������ ��������� ������� (����/�����) == (" + curLastIndex + "/"+ FindFirstEmptyItem() + ")");
}

// ����� ������� ��� ����������� ��������. ������ ������ �������� - �������� ������� ��� ���
bool RefreshGeneratedItem(String _itemID)
{
	int i, j;
	int itemIndex = GetItemIndex(_itemID);
	String curSimpleBox, curPrivateBox;
	ref reference;
	
	if(itemIndex == -1) return false;

	for(i = 0; i < nLocationsNum; i++)
	{
		reference = &Locations[i];
		
		for(j = 1; j < MAX_HANDLED_BOXES; j++)
		{
			curSimpleBox = "box" + j;
			curPrivateBox = "private" + j;
			if (reference.id == "Caiman_StoreHouse") break;
			
			if(!CheckAttribute(reference, curSimpleBox) && !CheckAttribute(reference, curPrivateBox)) break;
			
			// ����� �����
			if(CheckAttribute(reference, curSimpleBox + ".Items." + _itemID))
			{
				return false;
			}
			
			// �������
			if(CheckAttribute(reference, curPrivateBox + ".Items." + _itemID))
			{
				return false;
			}
		}
	}
	
	for(i = 0; i < TOTAL_CHARACTERS; i++)
	{
		reference = &Characters[i];
			
		// �������� �� ��������, � �������� ��� ����� �������� ��������
		if(CheckAttribute(reference, "Merchant") && CheckNPCQuestDate(reference, "Item_date"))
		{
			DeleteAttribute(reference, "items");
			continue;
		}
		
		if(CheckAttribute(reference, "Items." + _itemID))
		{
			return false;
		}
	}
		
//	DeleteAttribute(&Items[itemIndex], ""); // ������ ��� ���������
	return true;
}

// ��������, �������� �� ������ ������� "�����", ��� �� ���������
bool IsGenerableItem(String _itemID)
{
	int itemIndex = GetItemIndex(_itemID);
	ref itemRef;
	
	if(itemIndex == -1)
	{
		return false;
	}
	
	itemRef = &Items[itemIndex];
	
	if(CheckAttribute(itemRef, "Generation") && !CheckAttribute(itemRef, "Generated"))
	{
		return true;
	}
	
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//										<-- Warship ����� ������� ���������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Warship �������� �� ������
bool IsBlade(String _itemID)
{
	int itemIndex = GetItemIndex(_itemID);
	ref item;
	
	if(itemIndex == -1)
	{
		return false;
	}
	
	item = &Items[itemIndex];

	if(CheckAttribute(&item, "groupID"))
	{
		if(item.groupID == BLADE_ITEM_TYPE)
		{
			return true;
		}
	}
	
	return false;
}

// eddy -->
/////////////////////// ==> Items-������
int GetItemIndex(string _ItemID)
{
	return FindItem(_ItemID);
}

ref ItemsFromID(string _Items)
{
	return &items[GetItemIndex(_Items)];
}

void ChangeItemDescribe(string _Items, string _Describe)
{
    Items[GetItemIndex(_Items)].describe = _Describe;
}

void BackItemDescribe(string _Items)
{
    ref ItemAR = ItemsFromID(_Items);
    ItemAR.describe = "itmdescr_" + ItemAR.id;
}

void ChangeItemName(string _Items, string _Name)
{
    Items[GetItemIndex(_Items)].name = _Name;
}

void BackItemName(string _Items)
{
    ref ItemAR = ItemsFromID(_Items);
    ItemAR.name = "itmname_" + ItemAR.id;
}
///////////////////////  Items-������ <--


void QuestCheckEnterLocItem(aref _location, string _locator) /// <<<�������� ��������� �� � �������� ������ Item.<<<
{
	ref sld;
	int i;
	//======> ��������� ����������.
	if (_location.id == "Santiago_Incquisitio" && CheckNPCQuestDate(_location, "AttackGuard_date") && sti(Colonies[FindColony(_location.fastreload)].nation) == SPAIN && findsubstr(_locator, "detector" , 0) != -1) 
	{
		SetNPCQuestDate(_location, "AttackGuard_date"); //���� ������ � ����.
		
		if (CheckAttribute(pchar, "questTemp.WhisperTutorial"))
		{
			//������ ������ ��������� ����� ����� � ������� �� � �����
			DoQuestFunctionDelay("WhisperIncqAlarm", 2.5);
		}
		else
		{
			StartIncquisitioAttack();
			LAi_group_AttackGroup("SPAIN_CITIZENS", LAI_GROUP_PLAYER);
		}
		
		//==>��.�������, ����� �7. ��� ��������, ���� ������.
		if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace") LAi_ActorWaitDialog(characterFromId("RockBrasilian"), pchar);
	}
	//=======> ����� ��������, �������� �� ������ ������ ���������� � ������
	if (_location.id == "SanJuan_town" && pchar.RomanticQuest == "SeeTalkNearHouse") 
	{
        pchar.quest.Romantic_DeadBrother_Cancel.over = "yes"; //������� ������ �� ������� �� �������
		StartQuestMovie(true, true, true);
		pchar.RomanticQuest = "BrotherIsDead";
		LAi_SetActorType(pchar);
		SetMainCharacterIndex(GetCharacterIndex("Husband"));
        locCameraToPos(40.585, 6.0, -47.549, false);
		LAi_SetActorType(PChar);
		PChar.BaseNation = SPAIN; //������ � ������, ����� ������ ����� ���������
		PChar.RomanticQuest = "";
		LAi_SetActorType(CharacterFromID("MigelDeValdes"));
		SetActorDialogAny2Pchar("MigelDeValdes", "", 1.0, 0.0);
		LAi_ActorFollow(pchar, CharacterFromID("MigelDeValdes"), "ActorDialog_Any2Pchar", 0.0);
	}
	//=======> ����� ��������, ��������� ����� ����, ���� ��������� �� ������ ����� ����� 3 �������
	if (_location.id == "SanJuan_town" && pchar.RomanticQuest == "NewLifeForHero") 
	{
		if (GetQuestPastMonthParam("RomanticQuest") > 3) 
		{
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true);
			pchar.RomanticQuest = "TheDoosIsClosed";
			AddQuestRecord("Romantic_Line", "29");
		}
	}
	//=======> ����� ��������, ��������� ����� ����, ���� ��� � ����
	if (_location.id == "SanJuan_town" && CheckAttribute(pchar, "RomanticQuest.HorseCheck") && pchar.RomanticQuest.HorseCheck != "-1" && sti(pchar.questTemp.HorseQty) > sti(pchar.RomanticQuest.HorseCheck))
	{
		LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true);
		pchar.RomanticQuest = "over";
		pchar.RomanticQuest.HorseCheck = -1;
		AddQuestRecord("Romantic_Line", "29");
	}
	//======> ��������� ����� ���� �����.
	if (_location.id == "Mayak3") 	
	{
		int iNation = GetCityNation(GetCityNameByIsland(GiveArealByLocation(_location)));
		if(iNation == -1) return;
		string sGroup = GetNationNameByType(iNation)  + "_mayak";
		LAi_group_AttackGroup(sGroup, LAI_GROUP_PLAYER);
	}
	//======> ��������� �������� ��� ����� � ������� �����
	if (_locator == "duhi1" && CheckAttribute(_location, "locators.monsters") && !bMonstersGen)
	{
		//��������� ���� ���������� ���������
		if(LAi_LocationIsMonstersGen(_location) && LAi_grp_playeralarm == 0 && GenQuest_CheckMonstersGen()) 
		{
			SetSkeletonsToLocation(_location);
		}
	}
	if (_locator == "fire3" && _location.id == "MountainPath" && !bMonstersGen)
	{
		//��������� ���� ���������� ���������
		if(LAi_LocationIsMonstersGen(_location) && LAi_grp_playeralarm == 0 && GenQuest_CheckMonstersGen()) 
		{
			if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 6.0) SetReefSkeletonsToLocation(_location, "MountainPath");
		}
	}
	if (_locator == "fire56" && _location.id == "DeckWithReefs" && !bMonstersGen)
	{
		//��������� ���� ���������� ���������
		if(LAi_LocationIsMonstersGen(_location) && LAi_grp_playeralarm == 0 && GenQuest_CheckMonstersGen()) 
		{
			if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 6.0) SetReefSkeletonsToLocation(_location, "DeckWithReefs");
		}
	}
	//======> �������� � ������, ��������� ��� ����������
	if (_location.type == "jail" && !sti(pchar.questTemp.jailCanMove) && _locator == "detector1")
	{	
		pchar.questTemp.jailCanMove = true; //����� �� ����������� 2 ����
		if (!LAi_grp_alarmactive && !IsLocationCaptured(_location.id))
		{
			string slai_group = GetNationNameByType(GetCityNation(_location.parent_colony)) + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_SetFightMode(pchar, true);
		}
	}
	//======> ��������� ����� ���������� � �������� item1 � ��������
	if (pchar.questTemp.LSC == "toInterception" && _location.id == "FleuronTavern" && _locator == "detector1")
	{
        pchar.questTemp.LSC.itemState = true;
	}
	//======> ��������
	if (pchar.questTemp.LSC == "toUnderwater" && _location.id == "FenixPlatform")
	{        
		if (pchar.model == "protocusto")
		{	//����� �� ��������� �� �����
			bDisableFastReload = false;
			i = FindLocation("FenixPlatform");
			Locations[i].models.always.inside = "FenixPlatform";
			pchar.model = pchar.questTemp.LSC.immersions.model;
			pchar.model.animation = pchar.questTemp.LSC.immersions.animation;
			LocatorReloadEnterDisable("LostShipsCity_town", "reload58", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload73", true);
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload72", "");
		}
		else
		{	//����� � ����� �� ��������
			if (sti(pchar.questTemp.LSC.immersions.pay))
			{
				bDisableFastReload = true;
				i = FindLocation("FenixPlatform");
				Locations[i].models.always.inside = "FenixPlatform_wout";
				pchar.model = "protocusto";
				pchar.model.animation = "armor";
				LocatorReloadEnterDisable("LostShipsCity_town", "reload58", true);
				LocatorReloadEnterDisable("LostShipsCity_town", "reload73", false);
				DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload72", "");
			}
		}
	}
}

void QuestCheckExitLocItem(aref _location, string _locator) /// <<<�������� ������ �� �� ��������� ������ Item.<<<
{
	//=======> ��������� �������, ����� �4. � ������� ����� ����� ������ ����� ������������ ������
	if (_location.id == "Havana_houseS1Bedroom" && pchar.questTemp.State == "Sp4Detection_toMirderPlace" && CheckCharacterItem(pchar, "letter_notes"))
    {
        DoQuestCheckDelay("TalkSelf_Quest", 0.1); //������ ���-��-���
    }
	//=======> ����� ��������, ����� ��������.
    if (_location.id == "Guadeloupe_Cave" && _locator == "detector1")
    {
        if (pchar.questTemp.Ascold == "Ascold_SeekGrave" || pchar.questTemp.Ascold == "Ascold_CantSeekGrave")
        {
            Log_QuestInfo("���������� �� ���������� ����� � ������ ���������.");
            pchar.questTemp.Ascold = "Ascold_NotEnterFoundGrave";
    		DoQuestCheckDelay("TalkSelf_Quest", 0.1); //������ ���-��-���
        }
    }
	//=======> ����� ��������, �� �������� �� �����, �� ������� ��� �� �����. ������ ���������� �� �������.
    if (_location.id == "Guadeloupe_Cave" && _locator == "button02")
    {
		if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" || pchar.questTemp.Ascold == "Ascold_EnterGrave")
		{
			pchar.questTemp.Ascold = "Ascold_FoundMummy";
			characters[GetCharacterIndex("Ascold")].dialog.currentnode = "Found_Grave";
		}
	}
	//=======> ���������� �������� � ������, ��������� �������� ������ �� �������.
    if (_locator == "CheckReload1" && CheckAttribute(pchar, "GenQuest.OpenTheRopeExit") && pchar.GenQuest.OpenTheRopeExit == pchar.location)
    {
		DeleteAttribute(pchar, "GenQuest.OpenTheRopeExit");
		LocatorReloadEnterDisable(pchar.location, "reload2", false);
	}
	//=======> ��������, � ���� ������ ������� � ������
    if (_location.id == "SanJuan_houseSp6" && pchar.RomanticQuest == "exitFromDetector")
    {
		pchar.RomanticQuest = "executeFromDetector";
		StartQuestMovie(true, true, true);
		// �� ������ ���������
		//sGlobalTemp = GetMainCharacterIndex();
		SetMainCharacterIndex(GetCharacterIndex("MigelDeValdes"));
        PChar   = GetMainCharacter();			
		locCameraToPos(-2.41, 2.35, -2.41, false);
		SetActorDialogAny2Pchar("Isabella", "", 3.0, 0.0);
		LAi_ActorFollow(PChar, CharacterFromID("Isabella"), "ActorDialog_Any2Pchar", 4.0);
	}
	//=======> ��������, � ���� ������ ����� ������ ����
    if (_location.id == "Beliz_houseS4" && pchar.RomanticQuest == "Beliz_exitFromDetector")
    {
		pchar.RomanticQuest = "Beliz_executeFromDetector";
		StartQuestMovie(true, true, true);
        // �� ������ ��������
		ChangeCharacterAddressGroup(CharacterFromID("Isabella"), pchar.location, "goto",  "goto3");
		ChangeCharacterAddressGroup(CharacterFromID("Rosita"), pchar.location, "goto",  "goto1");
        SetMainCharacterIndex(GetCharacterIndex("Isabella"));
        PChar   = GetMainCharacter();			
        locCameraToPos(-3.84, 2.35, 0.85, false);
		LAi_SetActorType(CharacterFromID("Rosita"));
		LAi_SetActorType(pchar);
		PChar.BaseNation = SPAIN; //������ � ������, ����� ������ ����� ���������
		SetActorDialogAny2Pchar("Rosita", "", 1.0, 0.0);
		LAi_ActorFollow(PChar, CharacterFromID("Rosita"), "ActorDialog_Any2Pchar", 0.0);
	}
	//=======> �������, ����� �5
    if (_location.id == "Pirates_houseS1" && pchar.questTemp.piratesLine == "PL5Hunter_exitReload")
    {
		pchar.questTemp.piratesLine = "PL5Hunter_executeReload";
		StartQuestMovie(true, true, true);
		SetMainCharacterIndex(GetCharacterIndex("Orry"));
        PChar   = GetMainCharacter();			
		locCameraToPos(1.34, 2.1, 1.68, false);
		LAi_SetActorType(CharacterFromID("Aivory"));
		LAi_SetActorType(pchar);
		SetActorDialogAny2Pchar("Aivory", "", 3.0, 0.0);
		LAi_ActorFollow(PChar, CharacterFromID("Aivory"), "ActorDialog_Any2Pchar", 4.0);
	}
	//======> ��������� ����� ���������� � �������� item1 � ��������
	if (pchar.questTemp.LSC == "toInterception" && _location.id == "FleuronTavern" && _locator == "detector1")
	{        
		pchar.questTemp.LSC.itemState = false;
	}
}

void QuestCheckUseButton(aref _location, string _locator, string _itemId) /// <<< ��������� �������� ��� ��������� ��������� � button <<<
{
    //==> ����� ��������, ��������� ��������� ��� �������� ����� � ������ � ��������.
    if (_location.id == "Guadeloupe_Cave" && _locator == "button01")
    {
		//==> ���������� ����� ������ ���������
		_location.reload.l1.name = "reload3_back";
		locations[FindLocation("Guadeloupe_CaveEntrance")].reload.l1.emerge = "reload3"; 
		//==> ������������ �� reload5
		DoQuestFunctionDelay("Ascold_OpenTheGrave", 1.5);
    }
    //==> ����� ��������, �������� �������� ��������.
    if (_location.id == "Guadeloupe_Cave" && _locator == "button02" && pchar.questTemp.Ascold == "Ascold_WateringMummy")
    {
        ref sld;
		for (int i=1; i<=3; i++)
        {
			sld = GetCharacter(NPC_GenerateCharacter("Enemy_"+i, "Skel"+i, "skeleton", "skeleton", 30, PIRATE, 0, true));	
			FantomMakeCoolFighter(sld, 30, 85, 85, "topor2", "pistol3", 100);  
            LAi_SetWarriorType(sld);				
			LAi_group_MoveCharacter(sld, "EnemyFight");				
            ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);	
        }
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "Ascold_InGraveAfterFight");
        chrDisableReloadToLocation = true;
    }
    //==> ����� ��������, �������� ����� � ��������� ���� �� ����� 
    if (_location.id == (pchar.questTemp.Ascold.ShipyarderColony + "_shipyard") && _locator == "button01")
    {
		LAi_SetActorType(PChar);
		DoQuestCheckDelay("TalkSelf_Quest", 0.2);
    }
	//==> �������, ����� �7
    if (_location.id == "PuertoPrincipe_town" && _locator == "button01")
    {
		ref loc = &locations[FindLocation("PuertoPrincipe_townhall")];
		loc.reload.l2.name = "reload2";
		loc.reload.l2.go = "PuertoPrincipe_town";
		loc.reload.l2.emerge = "reload9";
		loc.reload.l2.autoreload = "0";
		loc.reload.l2.label = "Street";
		DoQuestFunctionDelay("PQ7_loadToRecidence", 2.0);
	}
	//��������� ������� � ������
    if (findsubstr(_itemId, "Totem_" , 0) != -1)
    {
		SetItemModelOnLocation(_location, _itemId, _locator);
		SetAztecUsedTotem(_location, _itemId, _locator);
	}
	//��������� ������ � ���� � �������
    if (_itemId == "KnifeAztec")
    {
		SetItemModelOnLocation(_location, _itemId, _locator);
		LocatorReloadEnterDisable("Tenochtitlan", "reloadTemple31", false);
	}
}
//�������� ������ ��������� �� �������� item
void QuestCheckTakeItem(aref _location, string _itemId)
{
	//����� ������������� �������� �� ������
	if (_itemId == "ShipyardsMap")
	{		
		AddQuestRecord("ShipyardsMap", "2");
		if (IsLoginTime() && !IsLocationCaptured(_location.id))
		{
			ref sld = characterFromId(_location.fastreload + "_shipyarder");
			sld.dialog.currentnode = "Allarm";	
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", 0, 0);
		}
	}
	//��������� - "�������� ������� ���������" 
	if (_itemId == "CaptainBook")
	{
		ReOpenQuestHeader("GiveShipLetters");
		AddQuestRecord("GiveShipLetters", "1");			
		AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("","�"));			
	}
	//����� ������ ������ ���� � ��������
	if (_itemId == "MayorsRing")
	{
		AddQuestRecord("SeekMayorsRing", "6");
		AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + pchar.questTemp.different.TakeMayorsRing.city + "Gen"));
	}
	//����� ������ ������������ ����� ����������
	if (_itemId == "UsurersJew")
	{
		string sTitle = _location.townsack + "UsurersJewel";
		AddQuestRecordEx(sTitle, "SeekUsurersJewel", "2");
	}
	//�������, ����� �7
	if (_itemId == "OpenBook")
	{
		AddQuestRecord("Pir_Line_7_Soukins", "9");
		SaveCurrentQuestDateParam("questTemp.piratesLine");
		pchar.questTemp.piratesLine = "Soukins_catchBattleship";
		Pchar.quest.PQ7_setBattleShip.win_condition.l1 = "MapEnter";
	    Pchar.quest.PQ7_setBattleShip.function = "PQ7_setBattleShip";
	}
	//������� ���, �������� � �������������� � ������
	if (_itemId == "letter_LSC")
	{
		AddQuestRecord("ISS_PoorsMurder", "11");
		AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("��","���"));
		AddQuestUserData("ISS_PoorsMurder", "sName", pchar.questTemp.LSC.poorName);
		pchar.questTemp.LSC = "readyGoLSC";
		DeleteAttribute(pchar, "questTemp.LSC.poorName");
		int n = FindIsland("LostShipsCity");
		Islands[n].visible = true;
		Islands[n].reload_enable = true;
		Islands[n].alwaysStorm = true; //����� � �������
		Islands[n].MaxSeaHeight = 2.0;
		Islands[n].storm = true;
		Islands[n].tornado = true;
		n = GetCharacterIndex("PoorKillSponsor");
		if (n != -1 && !LAi_IsDead(&characters[n])) 
		{
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_group_Attack(&characters[n], pchar);
			pchar.quest.PQ8_afterFight.win_condition.l1 = "NPC_Death";
			pchar.quest.PQ8_afterFight.win_condition.l1.character = "PoorKillSponsor";
			pchar.quest.PQ8_afterFight.win_condition = "OpenTheDoors";
		}
	}
	//������� ���, ����� �� �������� ��������. ��������� ���� ��������
	if (_itemId == "keyPanama" && CheckAttribute(pchar, "questTemp.LSC.lostDecster") && pchar.questTemp.LSC.lostDecster == "admiralLostKey")
	{
		pchar.quest.LSC_admiralFoundOwnKey.over = "yes"; //������� ������
		AddQuestRecord("LSC_findDekster", "12");
		CloseQuestHeader("LSC_findDekster");
		pchar.questTemp.LSC.lostDecster = "over";
	}
	//������ ������ � ����, ������� 11 �����
	if (_itemId == "Totem_11")
	{
		_location.models.always.seabed = "TenochtitlanWout_sb";
	}
	//������ ����������� ������
	if (_itemId == "SkullAztec")
	{
		LoginDeadmansGod();
	}
	//������ �������
	if (_itemId == "pistol7")
	{
		LoginShotgunGuards();
	}
}

void StartIncquisitioAttack()
{
	ref sld;
    for (int i=1; i<=5; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("IncqAddGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 35, SPAIN, 1, true));
		FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8, 80, 70, BLADE_LONG, "pistol4", 50);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");            
        ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "goto", LAi_FindRandomLocator("goto"));
    }
}

void SetItemModelOnLocation(ref loc, string model, string locator)
{
	loc.models.always.totem = model;
	loc.models.always.totem.locator.group = "item";
	loc.models.always.totem.locator.name = locator;
	loc.models.always.totem.tech = "DLightModel";
}
