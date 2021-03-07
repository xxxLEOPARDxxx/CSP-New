// boal 08/04/04 ����� ������ ���������
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	int skullprice = (sti(PChar.rank) * 4000) - ((sti(PChar.rank) * 2400) * (0.01* (GetSummonSkillFromName(PChar, SKILL_COMMERCE))))+ 10000;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney;
	int iQuantityGoods;
	int iTradeGoods;
	int iTmp;
	
    bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // ����� ��������
	ref rColony, chref;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
    int iSeaGoods = LanguageOpenFile("ShipEatGood.txt"); // ����� �������� �� GetGoodsNameAlt(idx)

    if (!CheckAttribute(npchar, "quest.item_date"))
    {
        npchar.quest.item_date = "";
    }
    if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    
    // ����� ������� �� ������� -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // ����� ������� �� ������� <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	string attrLoc   = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("� ������ ������� �������, ���� ����� ����! �� ����� ����� � �� �� ���� ����� �������������.", "��� ��������� ������ ����� �� ������ � ������� ����. � �� ����� � ������������� � ����� �� ����!", "����, "+ GetSexPhrase("��������","�������") +", ���� ������� �� ������� �� ���� ������..."), 
					LinkRandPhrase("��� ���� �����, "+ GetSexPhrase("�������","���������") +"?! ��������� ������ ��� ����� ���� ����, ������ ���� �� ����, "+ GetSexPhrase("������� �����","������� �����") +"!", ""+ GetSexPhrase("�������","�������") +" ������, ��� �� ����� ����! ������!!", "� �� ����� ����, "+ GetSexPhrase("��������","��������") +"! ����� ���� ������� � ����� �����, ������ ���� �� ����..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("���, ������� ��� ���� �� ��������...", "�� ���� �� �� ��� �� �������."), 
					RandPhraseSimple("������ ���� �����, " + GetWorkTypeOfMan(npchar, "") + ", � �� �� ����� ���� ������� ����!", "���, " + GetWorkTypeOfMan(npchar, "") + ", � ��� ���� �� - ������� ������! ��� ��� � ���� �����, ��������: ���� ���� � ������ ����..."));
				link.l1.go = "fight";
				break;
			}
			//homo ������� �����
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase("��, ������ ����! " + TimeGreeting() + ".",
                                    "��� ������ ���, ����� ����.",
                                    "������, ��� �� ��������� �� ���, " + GetFullName(pchar) + ". ��� �������� ��������� �����?");
                Link.l1 = "���, � ��� �����, " + NPChar.name + ". �� �������.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
            }
            dialog.text = NPCharRepPhrase(npchar, "����� ������ - ����� ������. "
							+ LinkRandPhrase("������ �� ����� ������. ", "������� �� ������. ","����� ������������ ��� �� ������! ")+
							+GetFullName(npchar)+  " � ����� �������!",
			                + LinkRandPhrase("������� ������������ � ����� ��������, ", "��� ������ �������, ", "����� ����������, ")
							+ GetAddress_Form(NPChar)+ ". ��� ��� "  + GetFullName(npchar)+
							+ RandPhraseSimple(", ��� ������� � ����� �������.",", � ��������� � ����� ������������."));
			link.l1 = "��������� �������������. " +RandPhraseSimple("���� ����� ","� - ")+ "������� "+ GetFullName(pchar)+".";
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("� ������ ������� �������, ���� ����� ����! �� ����� ����� � �� �� ���� ����� �������������.", "��� ��������� ������ ����� �� ������ � ������� ����. � �� ����� � ������������� � ����� �� ����!", "����, "+ GetSexPhrase("��������","�������") +", ���� ������� �� ������� �� ���� ������..."), 
					LinkRandPhrase("��� ���� �����, "+ GetSexPhrase("�������","���������") +"?! ��������� ������ ��� ����� ���� ����, ������ ���� �� ����, "+ GetSexPhrase("������� �����","������� �����") +"!", ""+ GetSexPhrase("�������","�������") +" ������, ��� �� ����� ����! ������!!", "� �� ����� ����, "+ GetSexPhrase("��������","��������") +"! ����� ���� ������� � ����� �����, ������ ���� �� ����..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("���, ������� ��� ���� �� ��������...", "�� ���� �� �� ��� �� �������."), 
					RandPhraseSimple("������ ���� �����, " + GetWorkTypeOfMan(npchar, "") + ", � �� �� ����� ���� ������� ����!", "���, " + GetWorkTypeOfMan(npchar, "") + ", � ��� ���� �� - ������� ������! ��� ��� � ���� �����, ��������: ���� ���� � ������ ����..."));
				link.l1.go = "fight";
				break;
			}
            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = NPCharRepPhrase(npchar,
                     		  LinkRandPhrase("������� ���� ����! ", "������!!! ", "������ ������!!! ")
							+ LinkRandPhrase("���������� ","��������� ", "��������� ����� ")+ LinkRandPhrase("� ������! ","����� �� �����! ", "� �������! ") + RandPhraseSimple("������!", "�������!"),
							  LinkRandPhrase("��������� ����","������� ������", "������ ���������")+ "! "+ LinkRandPhrase("������! " ,"��������! ","�� �� �����! ")
							+ LinkRandPhrase("� ������ �����! ","��������� � ������! ","�������������! ")+"�������, ����!!");
				link.l1 = pcharrepphrase(LinkRandPhrase("������ �����!","������ �� ������!","�������!")+ " ��� � "
											  + LinkRandPhrase("����� ���� ���� � ������� ��� ����, ", "������ ���� �����, ","����� ���� ������ �� �������, ")+ LinkRandPhrase("�������!", "������!", "��������!"),
							                    LinkRandPhrase("���� ����, ", "����� ���, ", "���������� ")+LinkRandPhrase("�������� ���!", "���������� ��������, ��� ������ �� �����!", "����������, �������!")
											  + LinkRandPhrase(" ��� � �� ��� �� ���� ����� � ��������!"," ���� ��� ����� ���! � ������� �� ����! �� ������?"," ��� ��� �������� ��� ����� �� �����."));
				link.l1.go = "fight";
				break;
			}*/
   			// �������� �������
			/*if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) >= 40)
			{
				dialog.text = NPCharRepPhrase(npchar,
                     LinkRandPhrase("������� ���� ����! ", "������!!! ", "������ ������!!! ")+GetFullName(pchar)+ ", �� �������� "
							+ LinkRandPhrase("'�����', ","'������', ", "'�����������', ") +LinkRandPhrase(" � ������! "," ����� �� �����! ", " � ������� �����! ") + RandPhraseSimple("������!", "�������!"),
							  LinkRandPhrase("��������� ����","������� ������", "������ ���������")+ "! ��� ��� "+GetFullName(pchar)+ LinkRandPhrase("! ������ " ,"! �������� ","! ������� ")
							+ LinkRandPhrase("����������! ","���� � ������! ","������� ����������! ")+"�������, ����!!");
				link.l1 =      pcharrepphrase(LinkRandPhrase("������ �����!","������ �� ������!","�������!")+ " � �� �� �"
											  + LinkRandPhrase(" ����� ���� ����, �������!", " ����� �� ���� �����!"," ���� ����� ������!"),
							                    LinkRandPhrase("���� ���� ���������!", "����� ���! �� �������!", "� ���� ���� ���� ���?")
											  + LinkRandPhrase(" � ��� �����!"," ���� ��� ����� ���!"," � �� ���� ��� �������!"));
				link.l1.go = "fight";
				break;
			}    */
			dialog.text = NPCharRepPhrase(npchar,
			                 pcharrepphrase(LinkRandPhrase("������� ", "�� ��� "+ GetSexPhrase("���","����") +" ", "���� � ����? ��� �� ") +GetFullName(pchar)+"! "
							                 + LinkRandPhrase("���� ��� �� ��������� �� ���? ��-��!","�������, �� "+ GetSexPhrase("���","����") +" � ������ � �������� �������!", "� � ������, ���� �������� � ����-�����.")
											  + RandPhraseSimple(" ��� ���� ������!", " ����� ����������!"),
							                LinkRandPhrase("������������, ", "����� ����������, ", "������ ����, ") + "�������"
											+ RandPhraseSimple(". ��� ���������� ",". ����������� �� ��� ")+" ���"+ RandPhraseSimple(" ������? "," �������? ")
											+ LinkRandPhrase("��� ������ �� �����,","�������� �����,", ""+ GetSexPhrase("����� �������� �������,","� ��� ������������� �����,") +"")+RandPhraseSimple(" �� ������ ��?", " �� ��� ��?")),
							 pcharrepphrase(LinkRandPhrase("������� ","��, ��� ����� ��, ","�� ���� ��������, ") + GetFullName(pchar)
							 				+ LinkRandPhrase(". ����� ������ ������ ��� �������� ����������� �����!",". � �������, � ��� ��� ������ � �������?",". ���� ��������� ��������� ������ �������.")
											 +LinkRandPhrase(" ���� ������ �� ��� �����?"," ��� ��� ������?", " ����� �� ������?"),
							                "����� ����������, ������� " +GetFullName(pchar)+ LinkRandPhrase("! ������� ������� �������",
											"! ������, ���������� �����","! ����������� ������� �����") +", �� ������ ��?"));

			link.l1 = NPCharRepPhrase(npchar,
			            pcharrepphrase(LinkRandPhrase("�� ��� ��� ���, ", "� � ���� "+ GetSexPhrase("���","����") +", ","�� � ����� ����� ������� � �������, ")
									  +LinkRandPhrase("�������!","�������!","������� ����!") +" � � "+ GetSexPhrase("�����","������") +", "
									  +LinkRandPhrase("���� ���� ��� ������� ���� � ����!","���� ������� �������!", "���� ������� ����� ���� �� �����!"),
						               LinkRandPhrase("������ ����, ","������� ��������, ","������, ") + GetAddress_FormToNPC(NPChar)+" " +GetFullName(Npchar)
									   +RandPhraseSimple(". �� �����, ",". ���������� "+ GetSexPhrase("��������","��������") +", ")
									   +LinkRandPhrase("� ������� "+ GetSexPhrase("������� ������ �������������","������ ����� ���������������") +"", "� ���� ������ �������", "� "+ GetSexPhrase("������� ���� �������� ������ ���� ������","�������� � ������ ������ �������") +"")+ "."),
						pcharrepphrase(RandPhraseSimple("� ����� ����� ���������, ","����������� �� ������ ����, ") +GetFullName(Npchar)+ "! "
						              +LinkRandPhrase("��������, ��� �������!", "� �� ������ ��� ������!","���� ����� �� ������ ������!")
						              +RandPhraseSimple(" � "+ GetSexPhrase("������","������") +" � �������!"," � ����� �� ����� ������?"),
						               "������ ����, " + GetAddress_FormToNPC(NPChar)+ "! ��, �� ����� " + LinkRandPhrase("��� ������ �����.",
									    "���� �������� ������.", "�� ���� �� �������.")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,
			                                         pcharrepphrase(RandPhraseSimple("�������� ���� ������! ","���� � �������! ") +LinkRandPhrase("��� ����� "+ GetSexPhrase("�����������","�����������, ��, ������, ����") +" ����� � ���� ��������, ��-��?",
													                                 "����� �������� ������� ��� ������� ������� ��������! ��-��!", "����� �������� ������ ���� ������� � ��� �������?"),
            														LinkRandPhrase("������� �����!", "������ � �����!","������� ����� �� �����!")+RandPhraseSimple(" � ���� �� �������"," � ���� ��������")
																	+LinkRandPhrase(" ����� ������ ���� �� �������."," ���������� ����� �������."," ������ ������ ������� ��������.")
																	+RandPhraseSimple(" � � ����� �������"," ���, ��� ���������")+", �������!"),
													 pcharrepphrase(RandPhraseSimple("����� ������ ��� "+ GetSexPhrase("������������","������������ � ����") +" �����! ��-��! ���� �� �� �������� �������� �� ��������!",
													                                 "����� ������ ���������� � ����� � �������� ���� �����. �� ������� �� ������, �����?!"),
                 												"������� " +LinkRandPhrase("������ ������ ������ " + NationNameGenitive(sti(NPChar.nation)),"������ ��� ������� ����", "�������� �������� �����")
																	+RandPhraseSimple("? � ��������� � ����� ������������!","? ��� ������� � ����� �������!")
																	+RandPhraseSimple(" ��� ��� ������"," ��������������") +", �������!")),
				                                  NPCharRepPhrase(npchar,
												  	 pcharrepphrase("��� ���� �����, ���: �� ����� ����� �� �������. ���������� ����� �������!",
													                "� � ������� ������� ������, ��� �� "+ GetSexPhrase("������ �����","������ �����") +". " +RandPhraseSimple("�� ������ � ����, ��� �� ����� "+ GetSexPhrase("�����","�����������") +".", "�� "+ GetSexPhrase("�����","������") +", �� "
																	+RandPhraseSimple("�� � ���� ������.", "���� �� ��������."))),
													 pcharrepphrase("� ����� �������� � ��� ���� ���� � ����������� ������. ������ ������ ������ ��� �������? ��� ������ � ����!",
													                "�������� ������������ - �������� ������, ������� " + GetFullName(pchar)+", �� ��� ��?")),
												  NPCharRepPhrase(npchar,
												     RandPhraseSimple("��� ��������� ���� �� ��������� �����! ��� �������� � ������ �������! " ,
													   RandPhraseSimple("���������� ������� �� ������ ��������!","���, � ������ ���� ������� �� �����!") +" ��-��-��! � ������� ����. ")
													   +RandPhraseSimple("���� ����, ���?", "��� �� ������ ������, �������?"),
													 pcharrepphrase("� �� ������ �������������, ������� " + GetFullName(pchar)+". ��� ����������� �������, � ��������� ��� ����� �������� ����!",
													                "�� ������, ������� " + GetFullName(pchar)+", �� �������� � ��� � ����� ��� ������� �������� � ����! ��� �� ������?")),
												  NPCharRepPhrase(npchar,
												     "�������, ��� ����� ������������� � �����. "
													 +LinkRandPhrase("���� ���-��� �������� �����. �� ��� ����� ������. ","�� �����, ��� ����� ���� ������ ����� ������� �����? ",
													 pcharrepphrase("���� � ������ �����. ����������� ���� - � �� ��������.","��� ��� ���� ������ ��������� ���� � ����! � ����!!! �� ����� �� �� "+ GetSexPhrase("���� �������","����� ���������") +"...")),
													 pcharrepphrase(RandPhraseSimple("� �������, ","� ��������, ")+RandPhraseSimple("��� �� �������� ��� ������.","��� ������ ������� ��� �� �����.")
													 +RandPhraseSimple(" �������� ����� � ��� �� ���, ��� ���������� �������..."," �������� ������� �� ��������� ����� ����� ��������?!"),
													 "������� " + GetFullName(pchar)+", ���� ������� � ��������� ����������� ��� ��� ��������!"
													 +RandPhraseSimple(" ������ ������� ��������� ������� ����� ���������?", " �� ������ ������ ���-�� ���������?"))),
										"cycle", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("�����, ���������, ��� � ���� ����, ������ �����!",
													               "� ����� ���� ���� ���������� �� ���� ������, ��������."),
													pcharrepphrase("������� ���������, " +GetFullName(npchar)+", � �� ������� ���� ������ ���� �� ���! ���� ��������� ���� ������!",
													               "������� ��������� ���� ������, " +GetAddress_FormToNPC(NPChar)+ ".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("��� �����! ������� �� ��������! ��, ��� � ���� � ����� ����?",
													               "��, ��������, ����� ��������� ����� �����. ����� ������ ������ ��� ����������?"),
												    pcharrepphrase("������� � �� ������� ���� ������, ��-��. ����. ����� ���� ������.",
													               "������� ������� �������� ����, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("��� ��� ����? ���� ������ ���-���!",
													               "�������� ��� ������ � ������, " +GetFullName(npchar)+ ". ��� ����� ���������� ���� ������."),
												    pcharrepphrase("���� � ���� ������! ��� ����� ����� �� ���� ����! ���� ��������� ���� ������",
													               "��� ������ �������. ������� �����������.")),
											  "��������� ������, ������ ���� � ������ ����. � ���������.",
											  npchar, Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("��, ��� �� � "+ GetSexPhrase("��������","���������") +" ����-������! �����, ����� � ����.",
													               "�������� � ������ �����, ��������"),
													pcharrepphrase("��������! � ������ �� ������� ����!",
													               "��� ����� � ���� ���������� �� ����, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("� ���� � ���� ����, ������ �����!",
													               "�������� � �����, ��������!"),
													pcharrepphrase("������� ��������, ���� ���� �� ��������, ��������! � ���� ������ ����!",
													               "��������� "+ GetSexPhrase("��������","��������") +", " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", � ���� �������� � ���� ���� ����.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("��� ��������, ��������?! � ���� � ���� ����.",
													               "� "+ GetSexPhrase("������","������") +" �� ���������, ��������. � ���� ������ ����."),
													pcharrepphrase("������� ���� ���� � ������ ������, �������! � ���� ���� � ����.",
													               "������ ������ �������, " + GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", �� � �� ������� ����.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("�������� ����, ������ �������, � ���� ���� � ����",
													               "������ ��� �� ����, � �������. �������, � �� ��� ���� �� � ��������. �������� � ����."),
													pcharrepphrase("�� � ��� ��� ������� ���� �� �����, ��������! � ���� � ���� ����.",
													               "���� ������ ���������, � ���� � ��� ���� ����� �������")),
											   npchar, Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("������� ����, ����� �������. ���� � ���� ������ ���-���.",
													               "�� ������, ��� ����� ����������."),
													pcharrepphrase("� ����� ����! ������� �� ������� ���, ��� ��� �����.",
													               "� �������������. � ���� ������ ���-���.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("������� �� �����, ������ ������. ��� ���� ���-��� ������.",
													               "� ���� ������������ ������."),
												    pcharrepphrase("������ ��������. � ���� ������ ���-���.",
													               "��, � "+ GetSexPhrase("��������","��������") +". ���� ��� �������� ��� � ���.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("� �����, �� ������, � ��� � ���� ��������.",
													               "� �������, �� �������� ��� �� ��� ������."),
													pcharrepphrase("� ���� � ������ ���� ���-������ ����� ��������? �� ���� � � ���� ��������.",
													               "���� �� �� ����. ��� ����� ���-����� ����������.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("�� ��������, �������! � ������ ���� �������� ����.",
													               "�� ���������� ���, ��� ������ ����. �������� ��� �� ������, � � ����"),
													pcharrepphrase("�� ��� �� ���� ������ ����� - �� � ���� ���������. �� �� ���-��� ������.",
													               "� �� ������� ��� �������. ����� ���� ������.")),
											   npchar, Dialog.CurrentNode);
			link.l3.go = "quests";
			//--> eddy. �������, ����� � ��������� ���������
			if (pchar.questTemp.Ascold == "Seek_powder" && pchar.questTemp.Ascold.TraderId == npchar.id && !CheckAttribute(Pchar, "RomanticQuest.TalkInShop")) 
			{
				link.l3.go = "AscoldTrader";
			}
			if (pchar.questTemp.Ascold == "PowderWasSeek" && pchar.questTemp.Ascold.TraderId == npchar.id) 
			{
				link.l3.go = "AscoldTrader_WasSeek";
			}
			if (CheckAttribute(pchar,"Whisper.Contraband") && npchar.id == "Tortuga_trader" && GetSquadronGoods(Pchar, GOOD_EBONY) >= 100) 
			{//������� ������
				link.l44 = "������������. � ������� ��������� ������������� ������ ������� �������� ����� �������. � ������� �������, ��� � ������ ��� ����� ������ ������� ������. ��� ����� � ���� � ����� � ������ � ���������.";
				link.l44.go = "Whisper_contraband";
			}
			if (CheckAttribute(pchar,"cursed.waitingSkull") && pchar.questTemp.Cursed.TraderId == npchar.id && !CheckAttribute(pchar,"cursed.Skullbought")) 
			{
				link.l44 = "� ���� � ��� ��������� ��������� ������. ���� � ���, ��� � ��� ���� ������� - "+ GetConvertStr("itmname_"+pchar.questTemp.Cursed.Item, "ItemsDescribe.txt") +". ��� ����� ��������, ��� �� ��� ������������ ��������� ����� ��������.";
				link.l44.go = "buy_skull";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "������������, � ����"+ GetSexPhrase("��","��") +" �� ����������� ������ ����."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "� �� ������ ����� ������...";
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			//<-- eddy. �������, ����� � ��������� ���������
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("����, ������ ��������.",
													               "����� �������, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),
													pcharrepphrase("��������! ������ �� �����. � ��� �����.",
													               "������� ���� ��� ������, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! �� ��������!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("������ ��������!",
													               "�� ��������, ��������."),
													pcharrepphrase("��! �� ��� ��� �������? ���? ���!?! �� �����, �����, ����� �������.",
													               "����� ���� ��������, � ���� ������� ���� � ������.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("���! ��� ��������!",
													               "��� ���� ����. ��������, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),
													pcharrepphrase("� �� ���� ��� ��������! ������� ��� ��� � ����� �������!",
													               "�������, ����� ���������, ��� ���� �� �������. ��������, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("��� � �����, �������? ��� �� � - " +GetFullName(pchar)+ "! ��������, � ����� �����.",
													               "�����, ���� ������ ��������� ��� ������, ��� � ��� ��� ����� ����."),
													pcharrepphrase("������ ���� �������, ��������! � ��� �����.",
													               ""+ GetSexPhrase("��� ���","���� ����") +" ��� ������, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											  npchar, Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		//������� ������
		case "Whisper_contraband":
			dialog.text = "������, �������! �� ���, �� ������� �������?";
			DeleteAttribute(pchar,"Whisper.Contraband");
			link.l1 = "��, � ���, ���� �����-�� ��������?";
			link.l1.go = "Whisper_contraband_1";
			link.l2 = "���...";
			link.l2.go = "Whisper_contraband_1";
		break;
		case "Whisper_contraband_1":
			dialog.text = "������-�� ������ ������� �� ������� ��������� ������ ���������. ��� �� � �� �����, � �� ����� ������� � ��� �����.";
			link.l1 = "��� �� ��� ������ � ����� ������? ������ ������� ����������?";
			link.l1.go = "Whisper_contraband_2";
		break;
		case "Whisper_contraband_2":
			dialog.text = "�� ����� ��� ���������� � ��������. �� ������� �� ����� ��������� ����� ����� � �����, �� ������ � ������. ������, ��� ������������ �������� ������\n�� ������ ������� ������� �� ����� ������� � ��������� � �����, ��� ���������� ���� ����. �� ���������� � �������� ����� �������. ��� ��� �������� ��� �������� ������ � ���������� ������ � ����������.";
			link.l1 = "� ���� ���� ������ ������� �����-������ �������?";
			link.l1.go = "Whisper_contraband_3";
		break;
		case "Whisper_contraband_3":
			dialog.text = "� ���� ������ �� ���� �� ����. ���� �� ������� - ����� ������. �� �� ����� ����������� ����������, � ��������� ���� ����� ������ �� �����������.";
			pchar.Whisper.ContraSmuggler = true;
			WhisperPlaceSmugglersOnShore("Shore58");
			AddQuestRecord("WhisperContraband", "2");
			SetTimerCondition("W_Smuggling", 0, 0, 10, false);
			link.l1 = "�����. ����� ������� � �����.";
			link.l1.go = "exit";
		break;
		//������� ������
		case "buy_skull":
			dialog.text = GetConvertStr("itmname_"+pchar.questTemp.Cursed.Item, "ItemsDescribe.txt") +"? ��������, �� ��� �������� ��������, ��� �� ���������. ����� ��� ����� ��� �������� ��� � ������ ������, � � ��� ��� ����� �� ���� �� ������� ���� ����� ��������.";
			link.l1 = "�� �����. ��� ���, ��������, ��� ����� ����, ���� ������ ����. ������� ������ �� ���� �����?";
			link.l1.go = "buy_skull_1";
		break;
		
		case "buy_skull_1":
			dialog.text = sti(skullprice) + " � �� ������� ������.";
			if (sti(pchar.Money) >= skullprice)
            {
    			link.l1 = "��� ������. ������� ��� ����.";
				link.l1.go = "buy_skull_2";
			}
			link.l2 = "�� �� ��� ������ � ������� ����� ������� �����. �� ��������.";
			link.l2.go = "exit";
		break;
		
		case "buy_skull_2":
			pchar.cursed.Skullbought = true;
			AddQuestRecord("CursedSkeleton", "2");
			dialog.text = "� ���� ������� ����� ����.";
			AddMoneyToCharacter(pchar, -skullprice);
			GiveItem2Character(pchar, pchar.questTemp.Cursed.Item);
    		link.l1 = "���, ��������.";
			link.l1.go = "exit";
		break;
		
		
		
		case "market":
//navy -->
			//����� ���
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do ��� ������
			{
				dialog.text = "��������, �� � ������ �����. ������ �������! �������� ������.";
				link.l1 = "�� ��� �� ��������! �����, ����� �������.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("� ���� ���� �����, ���������, �������� ����, ������ ��������� � ������ ������! ��� ��� ����������?", "������ ������ ������ ��� �������? ���, �����, ����������� �������� ������?");
			link.l1 = pcharrepphrase(LinkRandPhrase("� ���� ����� ����� ������! ������� �� ������, �� ��� ��?",
			                         "��� ����� ���������� ���� ���� �� ������ � ������ ��� ����� �������. ��-��!",
									 "�� ����������� ������� �� � ������ ���� �������! �� ��� ����� ���� ����� ��������� ������."),
									 LinkRandPhrase("���� ������� ���� � ��������� ������.",
			                         "� ���� ������ ����� �� �������.",
									 "������ ��� ����, ����� � ������ ������."));
			link.l1.go = "trade_1";
			link.l2 = LinkRandPhrase("������ ��� �����, ���������, � ��� ��� � ���� ��� ����?",
			                         "��� �� �������� ���� ����� ����������, ���� � �������� ��������.",
									 "����������� �����, ���������� ����� - ��� ��� ���� ����������.");
			link.l2.go = "items";
			
			if(IsPCharHaveTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // ����������� �������
			{
				link.l5 = "��� �������� ������� ����������� �������...";
				link.l5.go = "TransferGoods";
			}
			link.l3 = pcharrepphrase(RandPhraseSimple("��������� ��� ��������. �����!",
			                                          "�����, ����� �������. ������ �� �����."),
									 RandPhraseSimple("���, ��� ������ �� �� �������. ��������.",
									                  "��������, � ���� ������� ����. �� ��������!"));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = "������ ��� �����������.";
			link.l1 = "� ������"+ GetSexPhrase("","�") +" ���� ��������.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "��, �������, ������� ��� �������! ��� ���? �������, �� ����������? �� ����� �����, ��� �������, ���������. ����� � � �� ������� �����? ����� ������ ��������... ����� �������, �������, � ��� ����� �� ������, ��� ���� � ���� ���� �� ����. ���! ��� �� ��-������ ������� - ��� � ����, ���� �...\n����, � ��� �� �� ���� �� ���������, ���� �� � ������ � ��� ����� �� ������� � ����� �������������� ���������... �� �� ��� ����������... ��������� ������, �����... � �������.";
			link.l1 = "�������, �� ���� � ������ ���, �� � �� �� �������"+ GetSexPhrase("��","���") +" �� ��������...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "�� ��� �� ���������?.. � ��� ���� ���� ����? ����? ���, ����� ����� - ��������, ����� � ���������...\n��... � ������ �������������� ����, ��� � ����� - ������� ����������.";
			link.l1 = "�������. � ������� � ��������. ���-�� ��� ������������, ��� ��� �� ���� �� �����������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "�, ��� �� � ���� "+ GetSexPhrase("��� �������, ������� �����","�� �������, ������� ��������") +" ����� �������� ���� � ������� ��������?";
				link.l1 = "��, ��� � �����"+ GetSexPhrase("","��") +" �� �������.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "�-�, ����"+ GetSexPhrase("��, �����������","���, ���������������") +". ������ ������� ����?";
				link.l1 = "��, �� ��, ����� �������, �� ������������� �������� �� ������ ��.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "� ����� ��� ����������, ��� �� �������� �� ���� � ��������������� ��������� � ������� ��� � ������ ����� �� ����� ���������� ��������. ��������� ������������� ���, ��� ����. ������� ��� �������� ����� � ������� �� ���� �����.";
			link.l1 = "��������� ���, ��� ���� ������� �������� ���� ������� �����.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "����� �������������?! �� ��� �������������?! ���� ����, ��� ���� ������� ��� ������� ��������� ��� ������, ��� ��� � ����������� ����� �����! �� � � ��� ���� ��� ��� ���� ������. � ��, ���, �����������! � �����������, ���, ����� �� �������, � ���� �������� �����-�� ������ ���������, ������ �������, � ������������� ������������� �����������!";
			link.l1 = "��, ������ �� �� ������ � ��������� �������?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "����� ����� �������?! � ����� �������� �� ��������? ��������, ����� �������, � ���� ��... �������! ������ ��� ������ ���� ������� � ����� ����� �������� �� � ������ �����������. �������� �� ������������� ������ ������� � ����� ���������� ����� �������. �� ����� ��� ������� �������������. ��������.";
			link.l1 = "��� �, � ��� �� �������...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("��","��"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("","�"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		// Warship. ����������� ������� -->
		case "TransferGoods":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea) || (Pchar.location.from_sea == "Shore17");
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = LinkRandPhrase("...��� ������. ����� ������ ������������, �� ���� ������ ������� ���������� ������.",
					"��� �������� ��� ��� ������. ������� ����������� � ��������, �� ������� ����� ���������� ������.",
					"��, " + PChar.name + ", � ����. �� ��� ��� � ���� � �������. �� ����� ������� ����� ������� ������?");
					
				for(i=0; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						if(!GetRemovable(chref)) continue;
						
						attrL = "l"+i;
						Link.(attrL)    = "�� " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
						Link.(attrL).go = "TransferGoodsTo_" + chref.id;
					}
				}
				
				Link.l99    = "� ���������"+ GetSexPhrase("","�") +", ������ �� �����.";
				Link.l99.go = "exit";
			}
			else // ������� ����
			{
				dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("������ ����? � ��� �� ���� �������? � ����� ��� ���!",
					"������� ��������, ���� �� �������� ����! � ����� ��� ������ �������!"),
					pcharrepphrase("� �� ���� ������ ������� � �����, ������� " +GetFullName(pchar)+ ". �������, ��� �� '������� ���������'?",
					"�������, ������� ������� ����� � �����. ������������ ������� � ���������."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"����� ������������!!! �����, ������ �������, ��� ��������!",
					"� �� �����"+ GetSexPhrase("","�") +" ��� �������� " +GetFullName(npchar)+ ", ������� �� ������ ������� �������."),
					pcharrepphrase("���. ��� ������� ���������� Black Pearl. ��� ��� �� �������? ��-��! �����!",
					"������� �� �����, ����������� �� ������������."));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // ��� ��� �� ���������, ���� ������� ��� ���� (������� �������, � ������� ���� �� ����������)
			dialog.text = LinkRandPhrase("�� ��� ���, ���, �� ����� ������� ����� ������� ������?",
				"��� �� ����� ������� ����� ������ �������?",
				PChar.name + ", ��� � ���� ������ ������� ����� ����������� ��������?");
				
			for(i=0; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if(cn > 0)
				{
					chref = GetCharacter(cn);
					if(!GetRemovable(chref)) continue; // ���� ��������� - ����������
					
					attrL = "l"+i;
					Link.(attrL)    = "�� " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}
			
			Link.l99    = "� ���������"+ GetSexPhrase("","�") +", ������ �� �����.";
			Link.l99.go = "exit";
			break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase("��� ������! �� ��������� ������� �������� ��������.", 
						"�� ���, ����� ������ ��������� �� ��������� �������.",
						"���, �������� ������ � ���� ���������� ������� ��������.");
					link.l1 = "�������. � ���� ������� ����� ����.";
					link.l1.go = "exit";
					WaitDate("", 0, 0, 0, 1, 0); // ������ �����
				}
				else
				{
					dialog.text = LinkRandPhrase("�������, ���� �����, ������� �������� ��� ��������, ��� ���� �� ����� ���������� ���� �����!", 
						"���, ���� ����� ��� ������������ �� ��������� ���� �������!",
						"���, ������ ������� � ������������ �� ���������, ��� ��� ���� ����� �� ��� ��� ������������.");
					link.l1 = "��, �����.";
					link.l1.go = "exit";
					link.l2 = "�������, ����� ������� ������ �������.";
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("������� ���, ������� ������ �� ���� ��� ������� �� ������.", 
					"���, ������� ������ � ���� ����� ������� �� ����������!",
					"�������, ������� ������ �� ���������� � ���� ����� �������!");
				link.l1 = "��, �������. ����� ������� ������ �������.";
				link.l1.go = "TransferGoods_2";
				link.l2 = "� ��� �������"+ GetSexPhrase("","�") +"... �� ����� ������ ��������.";
				link.l2.go = "exit";
			}
			break;
		// <-- ����������� �������

		case "trade_1":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea) || (Pchar.location == "Caiman_Store");
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("������ ����? � ��� �� ���� �������? � ����� ��� ���!",
				                                                     "������� ��������, ���� �� �������� ����! � ����� ��� ������ �������!"),
													  pcharrepphrase("� �� ���� ������ ������� � �����, ������� " +GetFullName(pchar)+ ". �������, ��� �� '������� ���������'?",
													                 "�������, ������� ������� ����� � �����. ������������ ������� � ���������."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"����� ������������!!! �����, ������ �������, ��� ��������!",
				                                                 "� �� �����"+ GetSexPhrase("","�") +" ��� �������� " +GetFullName(npchar)+ ", ������� �� ������ ������� �������."),
												  pcharrepphrase("���. ��� ������� ���������� Black Pearl. ��� ��� �� �������? ��-��! �����!",
												                 "������� �� �����, ����������� �� ������������."));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "� ��� �� ������ ��� " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "������, ������ ������ ������.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "� ����� �������.";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "���������.";
				link.l1 = "�������.";
				link.l1.go = "storage_2";
			}
			link.l2 = "���, � ���������"+ GetSexPhrase("","�") +".";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "���, "+ GetSexPhrase("���������","���") +", ����� - ��� ����������. � ��� ����, ��� �� �� �������� ����� �����������.";
			link.l1 = "��� ������. � ��� �������.";
			link.l1.go = "storage_1";
			link.l2 = "�� ���, � ������ ��� ��������"+ GetSexPhrase("","�") +". ����� ����� � �����������...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "��� �� ������� - ������ �� ����� �����.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "����� - �������.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "��� ����. ������ ������ �������.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "������� ������������? ��-��-��, ����� ������������ �����, ����� �������� �������. ������ - ������ ����� �� ������� ��� �� ��������� �������� �����.";
			link.l1 = "� �� ������"+ GetSexPhrase("","�") +" - ����������. ��� �� ����������� ��� ������� �� �������� �������? ������ ������ ������� ����������.";
			link.l1.go = "storage_4";
			link.l2 = "����� �� ���������, ��������? �����, ������� ���� �� �����. �� ���� ������, ����"+ GetSexPhrase("��","��") +" �������... �����������, ����� ������.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "� ��� �� ������ ��� " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "������.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "��������� ���� ����� � � ������ �����.";
				link.l1 = "������.";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar);
		break;

		case "business":
			iTest = 0;
    		//����� ����� �����, ��������� ������
			if (pchar.questTemp.BlueBird == "begin" && sti(npchar.nation) == GetBaseHeroNation() && sti(npchar.nation) != PIRATE && npchar.city != "Panama" && !CheckAttribute(pchar, "questTemp.Headhunter") && !bNoPirateRestrictions)
			{
				dialog.text = RandPhraseSimple("�������, ����� ���, �������� ���!!!", "�������, � ����� � ��� ������ �� ����� ���� ���������!");
				link.l1 = "��� ���������? ��� � ���� ��� ������?"; 
				link.l1.go = "RBlueBird";
				break;
			}			
//navy -->
			//����� ���
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "���� � ���� ���������, �� " + GetFullName(&Characters[iTmp]) + " ��� ������ ��������� �� ��� ����.";
				link.l1 = "�� ��� �� ��������! �����, ����� �������.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"����?! ���������� ��� �� �������!","� ��� ������. � ����� ���� ���� ����?");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea) || (Pchar.location.from_sea == "Shore17");
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			/*if (CheckAttribute(pchar, "CargoQuest.iQuantityGoods"))
    			{
    				int iQuantityShipGoods = pchar.CargoQuest.iQuantityGoods;
    				int iQuestTradeGoods = pchar.CargoQuest.iTradeGoods;
    			}  */
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )//&&  GetSquadronGoods(pchar, iQuestTradeGoods) >= iQuantityShipGoods)
    				{
    					link.l1 = RandPhraseSimple("� ����� ����� ������� ���� ��� ������ ��������.", "��� ������� ����������� ��� �������� ����� � ��� �������. ����� ��� ���������.");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "� ���������, � ��������"+ GetSexPhrase("","�") +" ���������� �� ������ ������������. ������������ ���������� �� ��������� ��� ��������� ����.";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("� ���� ���������� ��� ������������ ��� ����� ��� ��������� �����.",
								                           "� ���� ���������� �������, � � ���� ��������� ����� ����, ���� ������ �� ���������.");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "�� ������ ������������ �����, " +GetAddress_FormToNPC(NPChar)+ "? � ���� �������� ������� � ������� �������.";
    				link.l1.go = "generate_quest";
    			}
    			// --> �� ��������� ���������
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("��, �������"+ GetSexPhrase("��","���") +" � ����... ��� ���, ��������, �������� ������ ����� �����.",
	                                                          "�� ���, ������ ����, ����� ������� ���� ���� ��������."),
	                                        RandPhraseSimple("� �����"+ GetSexPhrase("","�") +" �� �������� � ���� ���������� �������.",
	                                                         "������� ������� ���������� �������, ��� ���� � ��� ������������."));,
	
	                link.l3.go = "LoanForAll";
                }
				//����� ���� - �� ����� � ����� �������
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple("� ����� �� ��������� ������ ��������. ��� ����� ���������� " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " ������� ���� � ���. � ����"+ GetSexPhrase("��","��") +" ���-��� �������...");
					link.l4.go = "IntelligenceForAll";
				}	
				// ----------------- ����� ��������� ����� �����, ����� ����� -----------------
				if (pchar.questTemp.BlueBird == "weWon" && pchar.questTemp.BlueBird.traiderId == npchar.id)
				{
					link.l1 = "���� ��� ���������, ��� ��� ������� ���������� � ����� ����������. ������ '����� �����' �� ����� ����� ��������� ���������. � ������"+ GetSexPhrase("","�") +" �� ����������� ���������.";
					link.l1.go = "RBlueBirdWon";
				}
				if (pchar.questTemp.BlueBird == "DieHard" && pchar.questTemp.BlueBird.traiderId == npchar.id)
				{
					link.l1 = "����"+ GetSexPhrase("��","��") +" ��� ��������, ��� ��� �� ������� �������� ������ '����� �����'. � ������ ���, ��� ���...";
					link.l1.go = "RBlueBirdDieHard";
				}
				if (pchar.questTemp.BlueBird == "returnMoney" && pchar.questTemp.BlueBird.traiderId == npchar.id && sti(pchar.questTemp.BlueBird.count) > 0)
				{
					if (sti(pchar.questTemp.BlueBird.count) < 5)
					{
						link.l1 = "��� ����������� ������ ����� ������ ��������? ��� ���������?";
						link.l1.go = "RBlueBird_retMoney_1";
					}
					else
					{
						link.l1 = "�� ��� �� ���������, �� ������� ������ ��� ��� ������ ������������ ������?";
						link.l1.go = "RBlueBird_retMoney_3";
					}
				}
				// ----------------- ����� ��������� ����� �����, ����������� -----------------
				//homo 25/06/06 �����
                link.l6 = pcharrepphrase(RandPhraseSimple("���������� ��� ��������� �������? ��� ����� ������� ��� ����� ����.",
                                                          "�� �������, ������ ��������, � ����� ��������, ��� ����� ����� �� ����?"),
                                        RandPhraseSimple("�������, ��� ������"+ GetSexPhrase("","�") +" � ���� ����� ��������. ��� ���������� � ����� �����?",
                                                         "��, ��������, ������ ��� ��������� �������? ��� ������� ���������?"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> ����� ������� ��� ��
				if(CheckAttribute(NPChar,"Storage"))
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "��������� ���� � �������. � ���� ��������� �� ��������� ������ ������.";
						link.l7.go = "storage_0";
						link.l8 = "� �����"+ GetSexPhrase("","�") +" ���������� �������. �� ��� ������ ��� ����������.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate") && CheckAttribute(pchar,"questTemp.BlueBird.speakWon"))
						{
							link.l7 = "��������, �� ���-�� � ������ ���������. ����� ��� �� ������?";
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <-- ugeen
				// <-- homo
				link.l99 = "�������, ������ �� �� ����������.";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"� �������"+ GetSexPhrase("","�") +" ������� �� ������ ������� �������. ����� �������!", "����� ���� ��������, " +GetFullName(npchar)+ ", � ����� �����. ��� ������� ��� �� ������� � �����."), pcharrepphrase("������! ��� ������� �� ��������� ������� ��� ��������! ����� �����!", "��������, � ����"+ GetSexPhrase("��","��") +" ��������� ��������� ���� ������� � �����!"));
                link.l1.go = "exit";
    			// --> �� ��������� ���������
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("��, �������"+ GetSexPhrase("��","���") +" � ����... ��� ���, ��������, �������� ������ ����� �����.",
	                                                          "�� ���, ������ ����, ����� ������� ���� ���� ��������."),
	                                        RandPhraseSimple("� �����"+ GetSexPhrase("","�") +" �� �������� � ���� ���������� �������.",
	                                                         "������� ������� ���������� �������, ��� ���� � ��� ������������."));,
	
	                link.l3.go = "LoanForAll";
                }
				//����� ���� - �� ����� � ����� �������
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple("� ����� �� ��������� ������ ��������. ��� ����� ���������� " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " ������� ���� � ���. � ����"+ GetSexPhrase("��","��") +" ���-��� �������...");
					link.l7.go = "IntelligenceForAll";
				}	
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//�������� ������������ ��� ������ ��������
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "���, �� �����! �� ������� ����, �� ��� ���, ���� �� ��������� � " + NationNameAblative(sti(NPChar.nation)) + ".";
					link.l1 = "� ����� ������, ��������.";
					link.l1.go = "exit";
				}
				else
				{
                    // �������� �� ���� ����������� -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear() + "�� ���� " + GetFullName(pchar)+ ", �� ��� ��? � ���� " +
                                      RandPhraseSimple("����� ������� �����","������� �� ������ �������") + ", � �� ���� ����� � ����� ����.";
						link.l1 = RandPhraseSimple("��... ����� �������� ��� ����������, � ��� ����� � ���� �������.",
						                           RandSwear()+ "��� ��, � ���� ���� ������� � ������������, "+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // �������� �� ���� ����������� <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar, "��, "+GetAddress_Form(NPChar)+", �� �� ������� �������. ��������� ������.","������� ������. ��������, � ������ ��� �������� �����������.");
						link.l1 = "������, � ����� ������.";
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //��������� ������/�������
    						iTradeGoods = rand(GOOD_BRICK); //���� � ������ �� ����, ����� � ��� - ��!!
    						//��������� ��������� ����� (��� ���� ������ ��������� �� ������� ���� 100 ������ ���������� �����
    						RecalculateSquadronCargoLoad(pchar); // fix �������� �����
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
    						if (iQuantityGoods < 100)// ��� � ��. ������
    						{
    							dialog.text = NPCharRepPhrase(npchar, "� ���� ������ �������� �� ���������� ���� ����, ������� ������ �� �����.","� ���������, ������� "+GetFullName(pchar)+", ��� �������� ����� ��� ����� ����� ������������� �������, ��� ���.");
    							link.l1 = NPCharRepPhrase(npchar, "� ���� ��������� �������, �� � ����� ���� �����. �� ��������.","� ��� �������, ������ ������ �����. ��������.");
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
								if(CheckOfficersPerk(pchar,"Trader")) iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (5+rand(5) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);
								else iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);
    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							if(CheckOfficersPerk(pchar,"Trader")) pchar.CargoQuest.iDaysExpired = 18 + rand(6);
								else pchar.CargoQuest.iDaysExpired = 12 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = ", ��� �� " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Dat");
                                }
                                dialog.text =  "�! � ��� ��� ����� ��� ��������� ��� �� �������� ��� ����� ������. ���� � ���, ��� ��� ����� ��������� ���� " +
                                               GetGoodsNameAlt(iTradeGoods)+ " � ���������� " + FindRussianQtyString(iQuantityGoods) + " � ����� " +
                                           sNation + sTemp + ", � ��� ����� �������. ���� �� ������� ������� ��� �� " +  FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired)) +
                                           ", �� �� �������� �� ����� �������� " +
                                           FindRussianMoneyString(iMoney) + " ��������������. �� ���?";
    							link.l1 = "�����, ��� � ������"+ GetSexPhrase("��","��") +".";
    							link.l1.go = "exit_trade";
    							link.l2  = "�� �����, ��� ��� ��� ��������.";
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = "������������ ���������� � ���������� �� ��������� ��� ���������. "+
                                          XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter") + " �� ������ �� �����, � ������� ������� ������ � ����.";
    						link.l1 = "�! �������. ����� ��������";
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar, "����� ����������, ��� � ���� ������� �� ������ ���������!","� �� ��� ������� ��� �������, ��� � ���� ������ ��� ��� ���.");
				link.l1 = NPCharRepPhrase(npchar, "�� ������ ������������� ������, ��� � ����� ���� ����������!", "�, ��������.");
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear() + "�� ��������� � ���������� ��� ���� ������� ������, �� ��������? ��� �������� ���������� ����� ��������. ��������.";
				link.l1 = "�������� ����, �� � ��� ������"+ GetSexPhrase("","�") +". ��������, ���� � ������ ���� ������, ��� ����������� ��� ������� ���������?";
				link.l1.go = "generate_quest_failed";
				link.l9 = "����� ��������.";
				link.l9.go = "exit";
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = "�����! � ��� ����� ����. �� ������ ��������� ��� ���� " +
                GetGoodsNameAlt(iTradeGoods) + " � ���������� " + FindRussianQtyString(iQuantityGoods) + " � �������� �� ��� " +
                FindRussianMoneyString(sti(pchar.CargoQuest.iMoney)) + ".";
				link.l1 = "������ ���.";
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // ���� �������� ��� �� ����� -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear() + "� �������� ���������� ����� ����, "+GetAddress_Form(NPChar)+
                              ". ���� � ���, ��� � " + RandPhraseSimple("� ��������������� ��������� � �� ����� �������� ���� ������"," ��� ���� ���� ���� � ������ ����� �� ����� �������� ����")+
                              ". � �������� ������ ������ ������ � ������� ��� ���� ������������ ���� ����.";
				link.l1 = RandSwear() + RandPhraseSimple("� � �����"+ GetSexPhrase("","��") +" ���� ������ ���� �� ���� ��������!!! � ��� ����� ���� ��-�� ���� ����"+ GetSexPhrase("","�") +"!",
                                                         "�� ������� ���� � ����������� ���������, � ��� �������� �����������.");
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Dat"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // ���� �������� ��� �� ����� <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = "�� �������� �� ���� �����!! �������� �������� �������� ��������� ��� "
                              + FindRussianQtyString(iTmp) + " �����.";
				link.l9 = RandPhraseSimple("��, �������������. �������� ���������� ���������. ����� ��� ���.",
                                           RandSwear() +"����������� ����� ��������� ������ ����. � �������� ��������� � ����� ��� ���.");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = "������������! ��� ���� �������, ������� "+GetFullName(pchar)+".";
				link.l1 = "������� � ���� ��������.";
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "������... ����� � " + FindRussianMoneyString(iMoney) + " ��� ��� ������� ��� ������ �� ��������� ���� ������ �������� ������.";
			link.l1 = "���! ��� ��! �������, � �� ���� ������ ������ ������ ��� ������� �����! � ���� �� � ��� ����������!";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "��� ��������� �����";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "������������. ������ � ���� �������� ����� ��������, ��� � ���� ��� �� ����� ����� ����.";
			link.l1 = "�������! � ��������� ��� � �� �������.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = "��. � ������, ��� �� ��� �� ��������� ������������� �� ����������� ������, � ��� ������� �����. �� ������ ���� ��������� ���� " +
            LanguageConvertString(iSeaGoods, "seg_" + Goods[iTradeGoods].Name)+ " � " + XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony) + ".";
			link.l1 = "��, �����! �� �����!";
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear() + GetAddress_Form(NPChar) +", �� ��������� ����!!! �����, ����������� ���-�� ������ ��� ��������?";
			link.l1 = "������. � ���������� ��������� ����.";
			link.l1.go = "exit";
			link.l2 = "���. �� �����. �������";
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "���������! �� �� ������� ��� ������ ���������� ������!! ��� ��������� ��� "
                              + FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods)) + " �����.";
				link.l9 = RandPhraseSimple("��, �������������. �������� ���������� ���������.",
                                           RandSwear() +"����������� ����� ��������� ����. � ������� ����� � ����� ��� ���.");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "�����, � �������... �������� ����� �������.";
    			link.l1 = "�������. � ��������� ��� � �� �������!";
    			link.l1.go = "exit";
    			ChangeCharacterReputation(pchar, -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Dat"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;

		case "no_quests":
			dialog.text = "� ������ ������ � �� �������� � ����� �������.";
			link.l1 = "����� ����. ����� ������� ��������� � ������.";
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":
			if (pchar.questTemp.Ascold == "canTakeQuest" && pchar.questTemp.Ascold.TraderId == npchar.id)//eddy. �������, ������
			{
				dialog.Text = "�� ����� ��� �������. ������, ���� ��������� ���-������ ������� ���������� �����, �� ���� ����"+ GetSexPhrase("","�") +", ������� ��� ���. � ���� ���� ��������� ������ �� ��� ����.";
				Link.l1 = "������.";
				Link.l1.go = "exit";
				SaveCurrentQuestDateParam("questTemp.Ascold");
				pchar.questTemp.Ascold = "Seek_powder";
				AddQuestRecord("Ascold", "1");
				AddQuestUserData("Ascold", "sName", GetFullName(npchar));
				AddQuestUserData("Ascold", "sCity", XI_ConvertString("Colony" + npchar.city + "Dat"));
			}
			else
			{
				Nextdiag.CurrentNode = Nextdiag.TempNode;
				DialogExit();
			}
		break;
	}
	LanguageCloseFile(iSeaGoods);
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // �������
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //������ �������
			if (NPChar.id == "Caiman_trader" || ch.id == "Caiman_trader") continue;
            if (ch.location == "none") continue; // ���� ��� �����, ��������� �� ���� ��������
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // ���� ���, � �� ����!
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
	}
}

// ugeen --> 
//--> ������ ������ ������
int GetStoragePriceExt(ref NPChar, ref chref)
{
	float fLeadership = 1.5 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/120.0; // ��������� ���������
	float fCommerce = 1.5 - GetSummonSkillFromName(pchar, SKILL_COMMERCE)/120.0; // ��������� ��������
	
	int price = makeint(2000 * MOD_SKILL_ENEMY_RATE * fLeadership * fCommerce);
	
	return price;
}
//<-- ������ ������ ������
// --> ���������� ������� ����� �� ������ �� ������� �� � ����������, ����� ��� ����������� ��� ������ �� ���� ���� ��������
void SetStorageGoodsToShip(ref pStorage)
{
	int iStoreQ;
	for (int i = 0; i< GOODS_QUANTITY; i++)
	{
		iStoreQ = GetStorageGoodsQuantity(pStorage, i); 
		if (iStoreQ == 0) continue;
		SetCharacterGoods(pchar, i, GetCargoGoods(pchar, i) + iStoreQ);// ��������
	}
}