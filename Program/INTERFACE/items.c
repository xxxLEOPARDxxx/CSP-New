/// BOAL меню предметов
#include "interface\character_all.h"

int nCurScrollOfficerNum;

void InitInterface(string iniName)
{
    InterfaceStack.SelectMenu_node = "LaunchItems"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleItems";
	
	xi_refCharacter = pchar;
	
	FillCharactersScroll();
	FillPassengerScroll();
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	
	SetEventHandler("ExitOfficerMenu","ExitOfficerMenu",0);
	SetEventHandler("OfficerChange","OfficerChange",0);
	SetEventHandler("acceptaddofficer","AcceptAddOfficer",0);
	SetEventHandler("ExitRemoveOfficerMenu","ExitRemoveOfficerMenu",0);
	SetEventHandler("AcceptRemoveOfficer","AcceptRemoveOfficer",0);
	
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("ExitMapWindow","ExitMapWindow",0);
	SetEventHandler("ExitItemFromCharacterWindow","ExitItemFromCharacterWindow",0);
	
    SetEventHandler("ShowItemFromCharacterWindow","ShowItemFromCharacterWindow",0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);
    
    XI_RegistryExitKey("IExit_F2");
    SetVariable();
    SetNewGroupPicture("Weight_PIC", "ICONS_CHAR", "weight");
    SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");
}

void FillPassengerScroll()
{
	int i, howWork;
	string faceName;
	string attributeName;
	string PsgAttrName;
	int _curCharIdx;
	ref _refCurChar;
	aref pRef, pRef2;
	bool  ok;
	
	DeleteAttribute(&GameInterface, "PASSENGERSLIST");

	nCurScrollOfficerNum = -1;
	GameInterface.PASSENGERSLIST.current = 0;
	makearef(pRef,pchar.Fellows.Passengers);

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = GetFreePassengersQuantity(pchar);

	GameInterface.PASSENGERSLIST.NotUsed = 6;
	GameInterface.PASSENGERSLIST.ListSize = nListSizeFree + 2;

	GameInterface.PASSENGERSLIST.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("PASSENGERSLIST.ImagesGroup", pchar, 2); // passengers

	GameInterface.PASSENGERSLIST.BadTex1 = 0;
	GameInterface.PASSENGERSLIST.BadPic1 = "emptyface";

	int m = 0;
	for(i=0; i<nListSize; i++)
	{
		attributeName = "pic" + (m+1);
		PsgAttrName = "id"+(i+1);
		makearef(pRef2,GameInterface.PASSENGERSLIST.(attributeName));

		_curCharIdx = sti(pRef.(PsgAttrName));

		if (_curCharIdx!=-1)
		{
			ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
			if (!ok && GetRemovable(&characters[_curCharIdx]))
			{
                // совместители должностей -->
                howWork = 1;
                if (CheckCharacterPerk(&characters[_curCharIdx], "ByWorker"))
                {
                    howWork = 2;
                }
                if (CheckCharacterPerk(&characters[_curCharIdx], "ByWorker2"))
                {
                    howWork = 3;
                }
                ok = !CheckAttribute(&characters[_curCharIdx], "isfree") || sti(characters[_curCharIdx].isfree) < howWork;
                PsgAttrName = GetOfficerTypeByNum(nCurScrollNum);
				// совместители должностей <--
				if (ok && !CheckAttribute(&characters[_curCharIdx], PsgAttrName))
				{
					GameInterface.PASSENGERSLIST.(attributeName).character = _curCharIdx;
					GameInterface.PASSENGERSLIST.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
					GameInterface.PASSENGERSLIST.(attributeName).tex1 = FindFaceGroupNum("PASSENGERSLIST.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
					m++;
				}
			}
		}
	}
	GameInterface.PASSENGERSLIST.ListSize = m + 2; // не знаю зачем, но для совместимости с "было"
}

void ExitOfficerMenu()
{
	XI_WindowShow("OFFICERS_WINDOW", false);
	XI_WindowDisable("OFFICERS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("CHARACTERS_SCROLL");
}

void OfficerChange()
{
    string attributeName = "pic" + (nCurScrollNum+1);

	if(GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
	{
		int iCharacter = sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character);
		xi_refCharacter = &characters[iCharacter];
		if (isOfficerInShip(xi_refCharacter, true) && xi_refCharacter.id != pchar.id)
		{
			XI_WindowShow("REMOVE_OFFICER_WINDOW", true);
			XI_WindowDisable("REMOVE_OFFICER_WINDOW", false);
			XI_WindowDisable("MAIN_WINDOW", true);

			SetCurrentNode("REMOVE_CANCEL_OFFICER");
		}
	}
	else
	{
	    //Boyer mod
	    //if (nCurScrollNum <= 9 && nCurScrollNum != 0)
	    if (nCurScrollNum <= 6 + MAX_NUM_FIGHTERS && nCurScrollNum != 0)
		{
			FillPassengerScroll();
		    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"PASSENGERSLIST",-1);
		    SetCurrentNode("PASSENGERSLIST");
			ProcessFrame();
			SetOfficersSkills();

			XI_WindowShow("OFFICERS_WINDOW", true);
			XI_WindowDisable("OFFICERS_WINDOW", false);
			XI_WindowDisable("MAIN_WINDOW", true);
		}
	}
}

void SetOfficersSkills()
{
	string sCharacter = "pic"+(sti(GameInterface.PASSENGERSLIST.current)+1);
	if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter))
	{
		if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter + ".character"))
		{
			sCharacter = GameInterface.PASSENGERSLIST.(sCharacter).character;
			ref otherchr = &characters[sti(sCharacter)];
	        SetSPECIALMiniTable("TABLE_SMALLSKILL", otherchr);
	        SetOTHERMiniTable("TABLE_SMALLOTHER", otherchr);
	        SetFormatedText("OFFICER_NAME", GetFullName(otherchr));
	        SetSelectable("ACCEPT_ADD_OFFICER", true);
        }
        else
        {
            Table_Clear("TABLE_SMALLSKILL", false, true, true);
            Table_Clear("TABLE_SMALLOTHER", false, true, true);
            SetFormatedText("OFFICER_NAME", "");
            SetSelectable("ACCEPT_ADD_OFFICER", false);
        }
	}
	else
    {
        Table_Clear("TABLE_SMALLSKILL", false, true, true);
        Table_Clear("TABLE_SMALLOTHER", false, true, true);
        SetFormatedText("OFFICER_NAME", "");
        SetSelectable("ACCEPT_ADD_OFFICER", false);
    }
}

void AcceptAddOfficer()
{
	int iCurrentNode = nCurScrollNum;
	bool bNeedFollow = false;
	bool bOk;
	
	string attributeName2 = "pic"+(nCurScrollOfficerNum+1);

    if (checkAttribute(GameInterface, "PASSENGERSLIST."+attributeName2 + ".character"))
    {
		int iChar = sti(GameInterface.PASSENGERSLIST.(attributeName2).character);

		if (!CheckAttribute(&characters[iChar], "isfree"))
		{
			characters[iChar].isfree = 1;
		}
		else
		{
		    characters[iChar].isfree = sti(characters[iChar].isfree) + 1; // совместители
		}
		bOk = (Characters[iChar].location != pchar.location);  // ниже локация перебивается на ГГ
		switch (nCurScrollNum)
		{
			case 1:
				pchar.Fellows.Passengers.navigator = iChar;
			break;

			case 2:
				pchar.Fellows.Passengers.boatswain = iChar;
			break;

			case 3:
				pchar.Fellows.Passengers.cannoner = iChar;
			break;

			case 4:
				pchar.Fellows.Passengers.doctor = iChar;
			break;

			case 5:
				pchar.Fellows.Passengers.treasurer = iChar;
			break;

			case 6:
				pchar.Fellows.Passengers.carpenter = iChar;
			break;

			//Boyer mod
									  
					   
		 

			//default:
				SetOfficersIndex(pchar, nCurScrollNum - 6, iChar);
				bNeedFollow = true;
			break;
			//End Boyer add
		  
									  
					   
		 
		}
        attributeName2 = GetOfficerTypeByNum(nCurScrollNum);
    	characters[iChar].(attributeName2) = true; // совместитель дожности
    	//SetCharacterTask_FollowCharacter(&Characters[iChar], PChar);
    	if (bNeedFollow) // только для офов
    	{
													
	    	//if (Characters[iChar].location.group == "sit")
	    	//{// найм прямо в таверне
	    	//if (bOk && IsEntity(loadedLocation) && !CheckAttribute(loadedLocation, "DisableOfficers"))
	    	if (IsEntity(loadedLocation) && loadedLocation.type == "tavern")
	    	{   //  пусть всегда будут появляться
	    	    PlaceCharacter(&Characters[iChar], "goto", "random_must_be_near");
	    	}
	    	LAi_tmpl_SetFollow(&Characters[iChar], GetMainCharacter(), -1.0);
    	}
		FillCharactersScroll();
		GameInterface.CHARACTERS_SCROLL.current = iCurrentNode;
	}
	ExitOfficerMenu();
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	ProcessFrame();
	SetVariable();
}

void ExitRemoveOfficerMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("CHARACTERS_SCROLL");
}

void AcceptRemoveOfficer()
{
    int iCurrentNode = nCurScrollNum;
	string attributeName2 = "pic"+(nCurScrollNum+1);

	int iChar = sti(GameInterface.CHARACTERS_SCROLL.(attributeName2).character);

    characters[iChar].isfree = sti(characters[iChar].isfree) - 1; // совместители
	if (sti(characters[iChar].isfree) <= 0)
	{
		DeleteAttribute(&characters[iChar], "isfree");
	}

	switch (nCurScrollNum)
	{
		case 1:
			pchar.Fellows.Passengers.navigator = -1;
		break;

		case 2:
			pchar.Fellows.Passengers.boatswain = -1;
		break;

		case 3:
			pchar.Fellows.Passengers.cannoner = -1;
		break;

		case 4:
			pchar.Fellows.Passengers.doctor = -1;
		break;

		case 5:
			pchar.Fellows.Passengers.treasurer = -1;
		break;

		case 6:
			pchar.Fellows.Passengers.carpenter = -1;
		break;

		//Boyer mod
														  
		

		//default:
			RemoveOfficersIndex(pchar, GetOfficersIndex(pchar, nCurScrollNum - 6));
		break;

		//End Boyer mod
														  
		
	}
    attributeName2 = GetOfficerTypeByNum(nCurScrollNum);
    DeleteAttribute(&characters[iChar], attributeName2); // совместитель дожности
    
	FillCharactersScroll();
	GameInterface.CHARACTERS_SCROLL.current = iCurrentNode;
	ExitRemoveOfficerMenu();
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	SetVariable();
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("frame","ProcessFrame");
    DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	
	DelEventHandler("ExitOfficerMenu","ExitOfficerMenu");
	DelEventHandler("OfficerChange","OfficerChange");
	DelEventHandler("acceptaddofficer","AcceptAddOfficer");
	DelEventHandler("ExitRemoveOfficerMenu","ExitRemoveOfficerMenu");
	DelEventHandler("AcceptRemoveOfficer","AcceptRemoveOfficer");
	
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("ExitMapWindow","ExitMapWindow");
	DelEventHandler("ExitItemFromCharacterWindow","ExitItemFromCharacterWindow");
	DelEventHandler("ShowItemFromCharacterWindow","ShowItemFromCharacterWindow");
	
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");

	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
	int  iItemIndex = 0;
	ref itm;
    switch(nodName)
	{
		case "EQUIP_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				EquipPress();
			}
		break;
		
		case "I_CHARACTER_2":
			if(comName=="click")
			{
			    nodName = "I_CHARACTER";
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
				return;
			}
		break;
		case "I_SHIP_2":
			if(comName=="click")
			{
			    nodName = "I_SHIP";
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			}
		break;
		case "I_QUESTBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_QUESTBOOK";
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			}
		break;
		case "I_TRADEBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_TRADEBOOK";
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			}
		break;
		case "I_NATIONS_2":
			if(comName=="click")
			{
			    nodName = "I_NATIONS";
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			}
		break;
		case "I_ITEMS_2":
			if(comName=="click")
			{
			    nodName = "I_ITEMS";
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			}
		break;
		case "QTY_ADD_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				iItemIndex = sti(GameInterface.(CurTable).(CurRow).index);
				itm = &Items[iItemIndex];
				
	            		ADD_BUTTON(itm.id);
			}
		break;
		
		case "QTY_ADD_ALL_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				iItemIndex = sti(GameInterface.(CurTable).(CurRow).index);
				itm = &Items[iItemIndex];
				
	            		ADD_ALL_BUTTON(itm.id);
			}
		break;
		
		case "QTY_REMOVE_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				iItemIndex = sti(GameInterface.(CurTable).(CurRow).index);
				itm = &Items[iItemIndex];
				
	            		REMOVE_BUTTON(itm.id);
			}
		break;
		
		case "QTY_REMOVE_ALL_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				iItemIndex = sti(GameInterface.(CurTable).(CurRow).index);
				itm = &Items[iItemIndex];
				
	            		REMOVE_ALL_BUTTON(itm.id);
			}
		break;

		case "ITEM_FROM_CHARACTER_OK_BUTTON":
			RemoveItemsQuantity();
		break;
		// boal new menu 31.12.04 -->
		if (nodName == "I_CHARACTER" || nodName == "I_SHIP" ||
			nodName == "I_QUESTBOOK" || nodName == "I_TRADEBOOK" ||
			nodName == "I_NATIONS" || nodName == "I_ITEMS")
		{
			if(comName=="click")
			{
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
				return;
			}
		}
	// boal new menu 31.12.04 -->
	}
}

void ProcessFrame()
{
	if (sti(GameInterface.CHARACTERS_SCROLL.current)!=nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		SetButtonsState();
		return;
	}
	if (sti(GameInterface.PASSENGERSLIST.current)!= nCurScrollOfficerNum && GetCurrentNode() == "PASSENGERSLIST")
	{
		nCurScrollOfficerNum = sti(GameInterface.PASSENGERSLIST.current);
		SetOfficersSkills();
		return;
	}
}

void SetButtonsState()
{
	string attributeName = "pic" + (nCurScrollNum+1);
	
	if(GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
	{
		int iCharacter = sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character);
		xi_refCharacter = &characters[iCharacter];
		SetVariable();
	}
	else
	{
        xi_refCharacter = pchar;
	SetVariable();
	}
}

void SetVariable()
{
	SetFormatedText("SETUP_FRAME_CAPTION", XI_ConvertString("Equipment") + ": " + GetFullName(xi_refCharacter));
	// сортировка -->
	SortItems(xi_refCharacter);
	// сортировка -->
	SetControlsTabMode(1);
	HideItemInfo();
	SetFormatedText("Weight_TEXT", XI_ConvertString("weight") + ": " + FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / "+GetMaxItemsWeight(xi_refCharacter));
	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(xi_refCharacter.Money), MONEY_SIGN,MONEY_DELIVER));
	if (sti(xi_refCharacter.index) == sti(pchar.index))
	{
		SetNodeUsing("EQUIP_BUTTON" , true);
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	}
	else
	{
		SetNodeUsing("EQUIP_BUTTON" , true);
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	}
}

void FillItemsTable(int _mode) // 1 - все 2 - оружие 3 - остальное
{
	int n, i;
	string row;
	string sGood;
	int  idLngFile;
	bool ok, ok2 = true;
	aref rootItems, arItem;
	aref  curItem;
	
	GameInterface.TABLE_ITEMS.hr.td1.str = "Наименование предметов";
	GameInterface.TABLE_ITEMS.hr.td1.scale = 0.8;
	GameInterface.TABLE_ITEMS.hr.td2.str = "Вес шт.";
	GameInterface.TABLE_ITEMS.hr.td2.scale = 0.8;
	GameInterface.TABLE_ITEMS.hr.td3.str = "Кол-во";
	GameInterface.TABLE_ITEMS.hr.td3.scale = 0.8;
	GameInterface.TABLE_ITEMS.hr.td4.str = "Вес";
	GameInterface.TABLE_ITEMS.hr.td4.scale = 0.8;
	GameInterface.TABLE_ITEMS.select = 0;
	GameInterface.TABLE_ITEMS.top = 0;
	n = 1;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	Table_Clear("TABLE_ITEMS", false, true, false);
	
	// Заполним вещами от нас
	makearef(rootItems, xi_refCharacter.Items);
    for (i=0; i<GetAttributesNum(rootItems); i++)
    {
		curItem = GetAttributeN(rootItems, i);

		if (Items_FindItem(GetAttributeName(curItem), &arItem)>=0 )
		{
			row = "tr" + n;
			sGood = arItem.id;
			ok = arItem.ItemType == "WEAPON" || arItem.ItemType == "SUPPORT";
			if (CheckAttribute(arItem,"kind")) ok = true;
			if(CheckAttribute(arItem,"mapSpecial"))
			{
				ok2 = false;
			}
			else
			{
				ok2 = true;
			}
			if (_mode == 1 && arItem.ItemType == "MAP" && ok2) continue
			ok2 = ok2 && arItem.ItemType == "MAP";
			if (_mode == 2 && !ok && ok2) continue;
			ok = ok || arItem.ItemType == "MAP";
			if (_mode == 3 && ok && ok2) continue;
			if (_mode == 4 && arItem.ItemType != "MAP") continue;
			
			if (GetCharacterItem(xi_refCharacter, sGood) > 0)
			{		
				GameInterface.TABLE_ITEMS.(row).index = GetItemIndex(arItem.id);
				
				GameInterface.TABLE_ITEMS.(row).td1.icon.group = arItem.picTexture;
				GameInterface.TABLE_ITEMS.(row).td1.icon.image = "itm" + arItem.picIndex;
				GameInterface.TABLE_ITEMS.(row).td1.icon.offset = "-2, 0";
				GameInterface.TABLE_ITEMS.(row).td1.icon.width = 24;
				GameInterface.TABLE_ITEMS.(row).td1.icon.height = 24;
				GameInterface.TABLE_ITEMS.(row).td1.textoffset = "31,0";
				GameInterface.TABLE_ITEMS.(row).td1.str = LanguageConvertString(idLngFile, arItem.name);
				GameInterface.TABLE_ITEMS.(row).td1.scale = 0.85;
				
				GameInterface.TABLE_ITEMS.(row).td2.str   = FloatToString(stf(arItem.Weight), 1);
				GameInterface.TABLE_ITEMS.(row).td2.scale = 0.9;
				GameInterface.TABLE_ITEMS.(row).td3.str   = GetCharacterItem(xi_refCharacter, sGood);
				GameInterface.TABLE_ITEMS.(row).td3.scale = 0.9;
				GameInterface.TABLE_ITEMS.(row).td4.str   = FloatToString(stf(arItem.Weight) * sti(GameInterface.TABLE_ITEMS.(row).td3.str), 1);
				GameInterface.TABLE_ITEMS.(row).td4.scale = 0.9;
				n++;
			}	
		}
    }
    
	Table_UpdateWindow("TABLE_ITEMS");
	LanguageCloseFile(idLngFile);
	if (_mode == 1)
	{
		FillItemsSelected();
	}
}

void FillItemsSelected() 
{
	int    i;
	string sGood;
	int iLastGunItem;
	ref rLastGunItem;
	
	// Скроем по умолчанию
	SetNodeUsing("ITEM_1", false);
	SetNodeUsing("ITEM_2", false);
	SetNodeUsing("ITEM_3", false);
	SetNodeUsing("ITEM_4", false);
	SetNodeUsing("ITEM_5", false);
	SetNodeUsing("ITEM_6", false);
	SetNodeUsing("ITEM_7", false);
	
    for (i = 0; i< TOTAL_ITEMS; i++)
	{
		if(!CheckAttribute(&Items[i], "ID"))
		{
			continue;
		}
		
		sGood = Items[i].id;
		
		if (GetCharacterItem(xi_refCharacter, sGood) > 0)
		{		
			/// экипировка
			if (IsEquipCharacterByItem(xi_refCharacter, sGood))
			{
				switch (Items[i].groupID) 
				{
					case BLADE_ITEM_TYPE:
						SetNewGroupPicture("ITEM_1", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ITEM_1" , true);
					break;
					case GUN_ITEM_TYPE:
						if(CheckAttribute(xi_refCharacter, "IsMushketer"))
						{
							iLastGunItem = GetItemIndex(xi_refCharacter.IsMushketer.LastGunID);
							// Покажем картинку старого пистоля, если он еще есть
							if(iLastGunItem != -1 && GetCharacterItem(xi_refCharacter, xi_refCharacter.IsMushketer.LastGunID) > 0)
							{
								rLastGunItem = &Items[iLastGunItem];
								SetNewGroupPicture("ITEM_2", rLastGunItem.picTexture, "itm" + rLastGunItem.picIndex);
								SetNodeUsing("ITEM_2" , true);
							}
							
							rLastGunItem = &Items[GetItemIndex(xi_refCharacter.IsMushketer.MushketID)];
							SetNodeUsing("ITEM_5", true);
							SetNewGroupPicture("ITEM_5", rLastGunItem.picTexture, "itm" + rLastGunItem.picIndex);
						}
						else
						{
							SetNewGroupPicture("ITEM_2", Items[i].picTexture, "itm" + Items[i].picIndex);
							SetNodeUsing("ITEM_2" , true);
							SetNodeUsing("ITEM_5" , false); // Мушкет не юзается - уберем картинку
						}
					break;
					case SPYGLASS_ITEM_TYPE:
						SetNewGroupPicture("ITEM_3", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ITEM_3" , true);
					break;
					case CIRASS_ITEM_TYPE:
						SetNewGroupPicture("ITEM_4", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ITEM_4" , true);
					break;
					case BACKPACK_ITEM_TYPE:
						SetNewGroupPicture("ITEM_6", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ITEM_6" , true);
					break;
					case TALISMAN_ITEM_TYPE:
						SetNewGroupPicture("ITEM_7", Items[i].picTexture, "itm" + Items[i].picIndex);
						SetNodeUsing("ITEM_7" , true);
					break;
				}
			}
		}		
	}
	SetFormatedText("Weight_TEXT", XI_ConvertString("weight") + ": " + FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / "+GetMaxItemsWeight(xi_refCharacter));
}

//espkk. Returns attack coefficient by weapon. Writes perk multiplier in kPerk
float _GetAttackFactor(ref rBlade, string sType, ref kPerk)
{
	kPerk = 1;
	float kAttackDmg = 1.0;
	float min = stf(rBlade.dmg_min);
	float max  = stf(rBlade.dmg_max);
	
	float bladeDmg = min + (max - min)*frandSmall(LAi_GetCharacterFightLevel(pchar));

	switch(sType)
	{
		case "fast":
		kAttackDmg = 0.7;
		break;
		
		case "force": 	
		kAttackDmg = 1.0;
		break;
		
		case "round":
		kAttackDmg = 0.6;
		if(CheckCharacterPerk(pchar, "BladeDancer"))
		{
			kAttackDmg = kAttackDmg * 1.3;
		}
		break;
	
		case "break":
		kAttackDmg = 3.0;
		break;
		
		case "fient":
		kAttackDmg = 0.5;
		break;
	}
	float dmg = bladeDmg * kAttackDmg;
	
	return dmg;
}
void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sPicture;
	string sGroup, sGroupPicture;
	int iText2Color = 0;

	//Boyer fix #20170401-01 Can't load texture -1.tx log errors
	//sPicture = "-1";
	sPicture = "";
	string sAttributeName;
	int nChooseNum = -1;
	switch (sCurrentNode)
	{
		/*case "CHARACTER_NATION_PICTURE":
		    sHeader = XI_ConvertString("Nation");
			sText1 = GetRPGText("Nation_hint");
		break;   */
	}
	sHeader = "Предметы";
	sText1  = "Здесь Вы можете получить информацию об имеющихся предметах, изучить инвентарь или изменить экипировку главного героя. "+
              "Так же можно посмотреть состояние инвентаря офицеров, компаньонов и пассажиров. Выбор оружия они делают сами при экипировке их новым снаряжением. "+
              "Обмен предметами со своими офицерами осуществляется на суше через команду 'Обмен'.";
	
	if(sCurrentNode == "TABLE_ITEMS")
	{
		int iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
		ref rBlade = &Items[iGoodIndex];
		if (ThisItemCanBeEquip(rBlade))
		{
			if(rBlade.groupID == BLADE_ITEM_TYPE)
			{
				sHeader = "Урон клинка"
				sText1 = "";
			
				iText2Color = argb(255,120-30*(sti(rBlade.quality)+1),150,17);
				
				int ControlsLngFile = LanguageOpenFile("ControlsNames.txt");
				float aSkill = LAi_GetCharacterFightLevel(pchar);
				float kAttackDmg, kPerk;
				
				string sAttackTypes[5];
				sAttackTypes[0] = "fast";
				sAttackTypes[1] = "force";
				sAttackTypes[2] = "break";
				sAttackTypes[3] = "round";
				sAttackTypes[4] = "fient"; //feint = fient in lang file

				for(int index=0; index<5; index++)
				{
					kAttackDmg = _GetAttackFactor(rBlade, sAttackTypes[index], &kPerk);
					
					sText2 += LanguageConvertString(ControlsLngFile, "ChrAttack" + sAttackTypes[index]) + " ";
					sText2 += MakeInt(kAttackDmg);
						
					sText2 += "\n\n";
				}
				
				sGroup = rBlade.picTexture;
				sGroupPicture = "itm" + rBlade.picIndex;
				
				LanguageCloseFile(ControlsLngFile);
			}
		}
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, iText2Color, "", 0, "", 0, "-1", sGroup, sGroupPicture, 64, 64);
}
void HideInfoWindow()
{
	CloseTooltip();
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    
    // отрисовка инфы
    SetItemInfo();
}

void SetItemInfo()
{
	int iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);

	SetFormatedText("INFO_TEXT", GetItemDescribe(iGoodIndex));
	SetNewGroupPicture("INFO_PIC", Items[iGoodIndex].picTexture, "itm" + Items[iGoodIndex].picIndex);
	SetNodeUsing("INFO_TEXT", true);
	SetNodeUsing("INFO_PIC", true);
	SetVAligmentFormatedText("INFO_TEXT");
	
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	SetSelectable("EQUIP_BUTTON",ThisItemCanBeEquip(&Items[iGoodIndex]));
}

void HideItemInfo()
{
	SetNodeUsing("INFO_TEXT", false);
	SetNodeUsing("INFO_PIC", false);
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	SetSelectable("EQUIP_BUTTON",false);
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	SetCurrentNode("TABLE_ITEMS");
	HideItemInfo();
	if( sNodName == "TABBTN_1" )
	{
		SetControlsTabMode( 1 );
		return;
	}
	if( sNodName == "TABBTN_2" )
	{
		SetControlsTabMode( 2 );
		return;
	}
	if( sNodName == "TABBTN_3" )
	{
		SetControlsTabMode( 3 );
		return;
	}
	if( sNodName == "TABBTN_4" )
	{
		SetControlsTabMode( 4 );
		return;
	}
}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(255,196,196,196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;

	string sPic1 = "TabSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;

	switch (nMode)
	{
		case 1: //
			sPic1 = "TabDeSelected";
			nColor1 = argb(255,255,255,255);
		break;
		case 2:
			sPic2 = "TabDeSelected";
			nColor2 = argb(255,255,255,255);
		break;
		case 3:
			sPic3 = "TabDeSelected";
			nColor3 = argb(255,255,255,255);
		break;
		case 4:
			sPic4 = "TabDeSelected";
			nColor4 = argb(255,255,255,255);
		break;
	}
    
	SetNewGroupPicture("TABBTN_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_2", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_3", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_4", "TABS", sPic4);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_1", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_2", 8,0,nColor2);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_3", 8,0,nColor3);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_4", 8,0,nColor4);
	FillControlsList(nMode);
}

void FillControlsList(int nMode)
{
	switch (nMode)
	{
	    case 1: FillItemsTable(1); break;  // все
	    case 2: FillItemsTable(2); break;  // снаряжение
	    case 3: FillItemsTable(3); break;  // остальное
	    case 4: FillItemsTable(4); break;  // карты
	}
}

bool ThisItemCanBeEquip( aref arItem )
{
	if( !CheckAttribute(arItem,"groupID") )
	{
		return false;
	}
	if( !IsCanEquiping(xi_refCharacter, arItem.groupID) )
	{
		return false;
	}
	if(arItem.id == "MapsAtlas") 
	{
		return true;
	}
	if (arItem.groupID == GUN_ITEM_TYPE) 
	{
		if (!IsMainCharacter(xi_refCharacter) && !CheckAttribute(xi_refCharacter, "CanTakeMushket")) 
		{
			return false;
		}	
		if (!CheckAttribute(arItem,"chargeQ") )
		{
			return false;
		}
		int chrgQ = sti(arItem.chargeQ);
		
		if (chrgQ == 2 && !IsCharacterPerkOn(xi_refCharacter,"Gunman") )
		{
			return false;
		}
		
		if (chrgQ >= 4 && !IsCharacterPerkOn(xi_refCharacter,"GunProfessional") )
		{
			return false;
		}
		if(arItem.id == "mushket2x2") return false; // Мушкет квестового офа
		
		// Для мушкетов нужен соответствующий перк
		if(HasSubStr(arItem.id, "mushket") && !IsCharacterPerkOn(xi_refCharacter,"Gunman"))
		{
			return false;
		}
		
		if(arItem.id == "mushket_Shtuzer" && !IsCharacterPerkOn(xi_refCharacter,"GunProfessional"))
		{
			return false;
		}
		if(arItem.id == "mushket2" && !IsCharacterPerkOn(xi_refCharacter,"GunProfessional"))
		{
			return false;
		}
		if(arItem.id == "mushket_drob" && !IsCharacterPerkOn(xi_refCharacter,"GunProfessional"))
		{
			return false;
		}
		
		// Нельзя экипировать мушкет в непредназначенных для этого локациях (Таверна)
		if(HasSubStr(arItem.id, "mushket") && !CanEquipMushketOnLocation(xi_refCharacter.Location))
		{
			return false;
		}
		
		if (HasSubStr(arItem.id, "mushket") && IsMainCharacter(xi_refCharacter) && !IsPCharHaveMushketerModel())
		{
			return false;
		}
	}
    if (IsEquipCharacterByItem(xi_refCharacter, arItem.id))
	{
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Remove that"));
		//aw013	if(arItem.groupID==BLADE_ITEM_TYPE || arItem.groupID==SPYGLASS_ITEM_TYPE || arItem.groupID==PATENT_ITEM_TYPE)
		if(arItem.groupID==PATENT_ITEM_TYPE)	//aw013
		{
			return false;
		}
	}
	else
	{
		if (arItem.groupID == CIRASS_ITEM_TYPE && !IsCharacterPerkOn(xi_refCharacter,"Ciras") && arItem.Clothes == false)
	    {
		    return false;
	    }
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	}
	if (IsMainCharacter(xi_refCharacter) || CheckAttribute(xi_refCharacter, "CanTakeMushket"))
	{
		if(CheckAttribute(xi_refCharacter, "IsMushketer"))
		{
			if(arItem.ID == xi_refCharacter.IsMushketer.MushketID)
			{
				SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Remove that"));
				return true;
			}
		
			if(arItem.groupID == BLADE_ITEM_TYPE || arItem.groupID == SPYGLASS_ITEM_TYPE || arItem.groupID == GUN_ITEM_TYPE || arItem.groupID == CIRASS_ITEM_TYPE)
			{
				return false;
			}
		}
	}
	if (arItem.groupID == CIRASS_ITEM_TYPE && xi_refCharacter.model == "Protocusto") return false;
	return true;
}

void EquipPress()
{
	int  iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itmRef = &Items[iGoodIndex];
	string totalInfo;
	int  i;
	
	if (CheckAttribute(itmRef, "groupID"))
	{
		string itmGroup = itmRef.groupID;
		if (itmGroup == MAPS_ITEM_TYPE)
		{
			// Warship. Отличная карта, у нее отдельный интерфейс
			if(itmRef.ID == "Map_Best")
			{
				PChar.ShowBestMap = true; // Флаг, что смотрим из интерфейса придметов
				IDoExit(RC_INTERFACE_BEST_MAP);
				return;
			}
			// Ugeen --> интерфейс атласа карт
			if(itmRef.ID == "MapsAtlas") // взяли атлас карт
			{
				PChar.ShowMapsAtlas = true; // Флаг, что смотрим из интерфейса предметов
				IDoExit(RC_INTERFACE_MAPVIEW);
				return;
			}
			// Ugeen --> специальная квестовая карта
			if(itmRef.id == "mapQuest")
			{
				totalInfo = GenQuest_GetQuestTreasureMapDescription(itmRef);
				SetNewPicture("MAP_PICTURE", "interfaces\Maps\treasure map.tga");
				SetFormatedText("MAP_TEXT", totalInfo);
				SetVAligmentFormatedText("MAP_TEXT");
				ShowMapWindow();
				return;
			}	
            //pchar.I_MAP_SHOW = true;
            //pchar.I_MAP_SHOW_ITEM = itmRef.id;
            //PostEvent("InterfaceBreak", 400);
            if (itmRef.id == "map_full" || itmRef.id == "map_part1" || itmRef.id == "map_part2")
            {// клады
            	SetNewPicture("MAP_PICTURE", "interfaces\Maps\treasure map.tga");
            	if (GetCharacterItem(pchar, "map_part1")>0  && GetCharacterItem(pchar, "map_part2")>0)
			    {
			        TakeNItems(xi_refCharacter, "map_part1", -1);
			        TakeNItems(xi_refCharacter, "map_part2", -1);
			        TakeNItems(pchar, "map_full",   1);
			        itmRef = &Items[Items_FindItem("map_full", &itmRef)];
			        // здесь генерация назначение и типа клада
			        pchar.GenQuest.TreasureBuild = true;
			        FillMapForTreasure(itmRef);
			        SetVariable();
			    }
			    // тут применяем логику двух кусков, из них одна карта <--
			    if (itmRef.mapType == "Full")
			    {
		            if (sti(itmRef.MapTypeIdx) == -1)
				    {
                        SetFormatedText("MAP_TEXT", GetConvertStr("type_fake", "MapDescribe.txt"));
					    DeleteAttribute(itmRef, "MapIslId");
					    TakeNItems(GetMainCharacter(), "map_full", -1);
				    }
				    else
				    {
				        if (!CheckAttribute(itmRef, "MapIslId"))
				        {
				            FillMapForTreasure(itmRef); //заполним если смотрим карту из сундука
				        }
                        //totalInfo = GetConvertStr(itmRef.MapIslId, "LocLables.txt");
                        i = FindLocation(itmRef.MapLocId);  // ищем ареал
						if (i != -1 && locations[i].islandId != "Mein")
                        {
                            totalInfo = GetConvertStr(locations[i].islandId, "LocLables.txt");
                            totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx + "_isl", "MapDescribe.txt") + " " + totalInfo;
                        }
                        else
                        {
                            totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx + "_mein", "MapDescribe.txt");
                        }
						itmRef.MapIslName = totalInfo;
						totalInfo = GetConvertStr(itmRef.MapLocId, "MapDescribe.txt") + ", " + GetConvertStr(itmRef.MapLocId + "_" + itmRef.MapBoxId, "MapDescribe.txt");
				        itmRef.MaplocName = totalInfo;

				        totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx, "MapDescribe.txt");
				        totalInfo = GetAssembledString(totalInfo, itmRef);
				        SetFormatedText("MAP_TEXT", totalInfo);
				    }
			    }
			    else
			    {
           			SetFormatedText("MAP_TEXT", GetConvertStr("type_part", "MapDescribe.txt"));
				}
            	SetVAligmentFormatedText("MAP_TEXT");
            }
            else
            {
            	SetNewPicture("MAP_PICTURE", "interfaces\Maps\" + itmRef.imageTga + ".tga");
            	SetFormatedText("MAP_TEXT", "");
            }
            ShowMapWindow();
		}
		else
		{
			if (itmGroup == SPECIAL_ITEM_TYPE) // Jason, спецпредметы
			{
				if (itmRef.id == "RingCapBook") // СЖ пинаса 'Санта-Люсия' и дневник Колхауна
				{
					RemoveItems(pchar, itmRef.id, 1);
					AddQuestRecord("RingCapBook", "1");
					pchar.questTemp.LSC.Ring.ReadCapBook = "true";
				}
			}
			else
			{
				bool bCanmakeMushketer = (IsMainCharacter(xi_refCharacter)) || (CheckAttribute(xi_refCharacter, "CanTakeMushket"))
				if(HasSubStr(itmRef.id, "Mushket") && bCanmakeMushketer)
				{
					if (IsMainCharacter(xi_refCharacter)) // ГГ
					{
						if(!CheckAttribute(PChar, "IsMushketer")) // Не мушкетер. Делаем мушкетером
						{
							SetMainCharacterToMushketer(itmRef.id, true);
						}
						else // Мушкетер. Делаем обычным фехтовальщиком
						{
							SetMainCharacterToMushketer("", false);
						}
					}
					else
					{
						if(!CheckAttribute(xi_refCharacter, "IsMushketer")) // Не мушкетер. Делаем мушкетером
						{
							SetOfficerToMushketer(xi_refCharacter, itmRef.id, true);
						}
						else // Мушкетер. Делаем обычным фехтовальщиком
						{
							SetOfficerToMushketer(xi_refCharacter, itmRef.id, false);
						}
					}
				}
				else
				{
					if(IsEquipCharacterByItem(xi_refCharacter, itmRef.id))
					{
						RemoveCharacterEquip(xi_refCharacter, itmGroup);
					}
					else
					{
						EquipCharacterByItem(xi_refCharacter, itmRef.id);
					}
				}
			}
			FillItemsSelected();
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
			SetSelectable("EQUIP_BUTTON",ThisItemCanBeEquip(&Items[iGoodIndex]));
			SetItemInfo();
		}
	}
} 

void ExitMapWindow()
{
	XI_WindowShow("MAP_WINDOW", false);
	XI_WindowDisable("MAP_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_ITEMS");
}

void ShowMapWindow()
{
	XI_WindowShow("MAP_WINDOW", true);
	XI_WindowDisable("MAP_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("MAP_TEXT");
}

void ExitItemFromCharacterWindow()
{
	XI_WindowShow("ITEM_FROM_CHARACTER_WINDOW", false);
	XI_WindowDisable("ITEM_FROM_CHARACTER_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetNodeUsing("ITEM_FROM_CHARACTER_OK_BUTTON", false);
	SetNodeUsing("ITEM_FROM_CHARACTER_CANCEL_BUTTON", false);
	SetNodeUsing("QTY_EDIT", false);
	SetNodeUsing("QTY_ADD_BUTTON", false);
	SetNodeUsing("QTY_ADD_ALL_BUTTON", false);
	SetNodeUsing("QTY_REMOVE_BUTTON", false);
	SetNodeUsing("QTY_REMOVE_ALL_BUTTON", false);

	GameInterface.qty_edit.str = 0;
		
	SetCurrentNode("TABLE_ITEMS");
}

void ShowItemFromCharacterWindow()
{
	if(sti(xi_refCharacter.index) != nMainCharacterIndex)
	{
		return;
	}

	int  iIndex = sti(GameInterface.(CurTable).(CurRow).index);
	
	XI_WindowShow("ITEM_FROM_CHARACTER_WINDOW", true);
	XI_WindowDisable("ITEM_FROM_CHARACTER_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetNodeUsing("ITEM_FROM_CHARACTER_OK_BUTTON", true);
	SetNodeUsing("ITEM_FROM_CHARACTER_CANCEL_BUTTON", true);
	SetNodeUsing("QTY_EDIT", true);
	SetNodeUsing("QTY_ADD_BUTTON", true);
	SetNodeUsing("QTY_ADD_ALL_BUTTON", true);
	SetNodeUsing("QTY_REMOVE_BUTTON", true);
	SetNodeUsing("QTY_REMOVE_ALL_BUTTON", true);

	SetCurrentNode("ITEM_FROM_CHARACTER_TEXT");
	SetCurrentNode("ITEM_FROM_CHARACTER_NAME");
	
	ref itm = &Items[iIndex];

	string sTexture = itm.picTexture;
	string sPicture = "itm" + itm.picIndex;

	SetNewGroupPicture("ITEM_FROM_CHARACTER_PICTURE", sTexture, sPicture);
	SetNewGroupPicture("ITEM_FROM_CHARACTER_WEIGHT_PICTURE", "ICONS", "weight icon");

	int lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	string sGood = itm.name;
	string sGoodName = LanguageConvertString(lngFileID, sGood);
	
	SetFormatedText("ITEM_FROM_CHARACTER_TEXT", GetItemDescribe(iIndex));
	SetFormatedText("ITEM_FROM_CHARACTER_NAME", "Выкинуть предмет: " + sGoodName);
	
	string sItem = itm.id;
	int iQuantity = sti(GameInterface.qty_edit.str);
	float fItemQuantity = iQuantity*stf(itm.Weight);
	float fWeight = GetItemsWeight(PChar) - fItemQuantity;
	
	if(iQuantity <= 0)
	{
		fItemQuantity = GetItemsWeight(PChar);
	}
	
	SetFormatedText("ITEM_FROM_CHARACTER_WEIGHT_TEXT", XI_ConvertString("weight") + ": " + FloatToString(fWeight, 1) + " / "+GetMaxItemsWeight(PChar));
	
	LanguageCloseFile(lngFileID);
}


void confirmChangeQTY_EDIT()
{
	int iItemIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itm = &Items[iItemIndex];
	ChangeQTY_EDIT(itm.id);
}

void ChangeQTY_EDIT(string sItem)
{
	if(sti(GameInterface.qty_edit.str) < 0)
	{
		GameInterface.qty_edit.str = 0;
	}

	if(sti(GameInterface.qty_edit.str) > GetCharacterItem(PChar, sItem))
	{
		GameInterface.qty_edit.str = GetCharacterItem(PChar, sItem);
	}


	if(IsEquipCharacterByItem(PChar, sItem))
	{
		if(sti(GameInterface.qty_edit.str) >= GetCharacterItem(PChar, sItem))
		{
			GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str) - 1;
		}
	}

	if(IsQuestUsedItem(sItem))
	{
		GameInterface.qty_edit.str = 0;
	}

	ref itm = ItemsFromID(sItem);
	int iQuantity = sti(GameInterface.qty_edit.str);
	float fItemQuantity = iQuantity*stf(itm.Weight);
	float fWeight = GetItemsWeight(PChar) - fItemQuantity;
	
	if(iQuantity <= 0)
	{
		fItemQuantity = GetItemsWeight(PChar);
	}
	
	SetFormatedText("ITEM_FROM_CHARACTER_WEIGHT_TEXT", XI_ConvertString("weight") + ": " + FloatToString(fWeight, 1) + " / "+GetMaxItemsWeight(PChar));
	
}

void REMOVE_ALL_BUTTON(string sItem)  // выкинуть все
{
	if(IsQuestUsedItem(sItem))
	{
		return;
	}

	int iQuantity = GetCharacterItem(PChar, sItem);

	GameInterface.qty_edit.str = iQuantity;
	ChangeQTY_EDIT(sItem);
}

void ADD_ALL_BUTTON(string sItem)  // сбросить
{
	GameInterface.qty_edit.str = 0;
	ChangeQTY_EDIT(sItem);
}

void REMOVE_BUTTON(string sItem)  // выкинуть
{
	ref PChar = GetMainCharacter();
	
	if(IsQuestUsedItem(sItem))
	{
		return;
	}
	
	if(GetCharacterItem(PChar, sItem) >= 1)
	{
		GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + 1);
	}
	
	if(sti(GameInterface.qty_edit.str) > GetCharacterItem(PChar, sItem))
	{
		GameInterface.qty_edit.str = GetCharacterItem(PChar, sItem);
	}
	ChangeQTY_EDIT(sItem);
}

void ADD_BUTTON(string sItem)  // не выкидывать
{
	GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - 1);
	
	if(sti(GameInterface.qty_edit.str) < 0)
	{
		GameInterface.qty_edit.str = 0;
	}
	
	ChangeQTY_EDIT(sItem);
}

void RemoveItemsQuantity()
{
	ref PChar = GetMainCharacter();
	
	int  iIndex = sti(GameInterface.(CurTable).(CurRow).index);
	ref itm = &Items[iIndex];
	
	ChangeQTY_EDIT(itm.id);
	
	int iQuantity = sti(GameInterface.qty_edit.str);
	
	if(iQuantity <= 0)
	{
		return;
	}
	
	TakeNItems(PChar, itm.id, -iQuantity);
	
	ExitItemFromCharacterWindow();
	SetVariable();
}
