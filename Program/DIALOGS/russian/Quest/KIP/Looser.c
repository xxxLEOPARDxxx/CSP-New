void ProcessDialogEvent(){	ref NPChar;	aref Link, NextDiag;	DeleteAttribute(&Dialog,"Links");	makeref(NPChar,CharacterRef);	makearef(Link, Dialog.Links);	makearef(NextDiag, NPChar.Dialog);	switch(Dialog.CurrentNode)	{		case "first time":			dialog.text = "������ ����.";			link.l1 = "��� �� ������� �������, ��� �� ������.";			link.l1.go = "1";		break;				case "1":			dialog.text = "��� � � ����� ��������. �� �� �������� ���� ��� ����� ������� ���. � ������ ��������! �� ���� ������ �� �������.";			link.l1 = "���, ����� �������! � ������, ������. �������, ��� ����� � ����, ��������, ���� ���-���� �������!";			link.l1.go = "exit";			NextDiag.TempNode = "second time";			AddDialogExitQuestFunction("LooserGenerator_TimeFailedEnd");		break;		case "second time":			dialog.text = LinkRandPhrase("� �� ������� ���������? ����������!","� �� ���� � ����� �������������.","����, ����� � ���� �� �����.");			link.l1 = "...";			link.l1.go = "exit";			NextDiag.TempNode = "second time";		break;		case "quest":			dialog.text = "������ ����.";			link.l1 = "� �� ������"+ GetSexPhrase("","�") +", ��� �� ������, ������ ���� �� �����.";			link.l1.go = "2";		break;		case "2":			dialog.text = "� ����� ���� ���������� ���������, "+ GetSexPhrase("��������","�������") +", � ������� ����� ���� ���� �����������. �������, ��� ���� ������ ���������� - ������� � ����� ���� ������� ���� ������.";			link.l1 = "���, ����� �������! � ������, ������. �������, ��� ����� � ����, ��������, ���� ���-���� �������!";			link.l1.go = "exit";						AddDialogExitQuestFunction("LooserGenerator_Complette");			NextDiag.TempNode = "3";		break;		case "3":			dialog.text = LinkRandPhrase("�, ��� ��...","� ����� �����, �� �������.","����� �����-������ ��� �����������...");			link.l1 = "...";			link.l1.go = "exit";			NextDiag.TempNode = "3";		break;		case "exit":			if (CheckAttribute(NextDiag,"TempNode")) NextDiag.CurrentNode = NextDiag.TempNode;			DialogExit();		break;	}}