
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string sName = GetNameLugger(PChar, "f");
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			
			if(PChar.Dozor == "0")
			{
				if(sti(PChar.rank) >= 3)
				{
					dialog.text = "������� �����, �����! �����, ��� ����� � ��� ����������� ��� ����. ������ �� � �������� ��� �� � �����. ��, ��� ��� ������� �����.";
					link.l1 = "������ ���� �� ����, ������! ظ� �� ����� �������, � �� �������� �� ������� ����� �� ����.";
					link.l1.go = "1";
				}
				else
				{
					dialog.text = "�� ��� ������� ����, ����� �������� �� ����. ������� �����...";
					link.l1 = "����? �� � ���� ������!.. ��, ������.";
					link.l1.go = "exit";
				}
				break;
			}
		
			dialog.text = "��� ��� ����?";
			link.l1 = "������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "1":
			dialog.text = "�� ����� ��� ���������� �� ����, �����, � ���� ���� ���� ���� ��, ���� �� ������ ���� ���� ������. ���������?";
			link.l1 = "������ ���������. � ��� ��� �� ����? ����� �����-������ ����������� ����������?";
			link.l1.go = "2";
		break;
		
		case "2":
			dialog.text = "�� ����� ��������� �������, � ���� �� ���� ���� ���� � ������, � ����� ������ ������� ������, � ���� ������ ����� � ���� �������� �����������.";
			link.l1 = "������-������. �������� ������! ���� �� �����, ��� ����� �������� �����������, ��� �� �������!";
			link.l1.go = "3";
		break;
		
		case "3":
			dialog.text = "���, ���, ��� ��� ������� ��������, �� ������� ���-�� ����� �������, ���-�� �����, �� �����. � ��� ��� ����, ��� ���� � ����, ����, ��� ����� ��������� � �����, ����, ��-�� ���� � ���� � ����������. ���������, �����?";
			link.l1 = "�� ������. � ��� �� ���?";
			link.l1.go = "4";
		break;
		
		case "4":
			dialog.text = "���������� � ������� �������� � ������� �� �������� �, ����������, ������� ���������� ��� �������� - �����������!";
			link.l1 = "������ ��, ����, ��������� �������, ���� ����������� ��� ������ � �� �����, ����� ���� �����. ��� ��� ���� ��� ����������� �� ������� ��� ���� �������, ��� ����� ��������, �� �������� ��� ����� ���������.";
			link.l1.go = "5";
		break;
		
		case "5":
			dialog.text = "...(��������� ���������)... ����������, � ������� �� �� ����������, � ���� ������ � ���� �������, � ��� ������� - �� ������ � ������������, �� ������� ������� �����������, ��, � ���� ����� ���� �� ��� ���������� �� ������, �� � ���� ������� ������ ������� ����������. ������ �������, � �� ����� ���� ���������� ������� ...(���������� ������)..., �������� �, ���� ������� �����.";
			link.l1 = "��, �����, ���������.";
			link.l1.go = "6";
		break;
		
		case "6":
			dialog.text = "��� ���� ������ ���-�� ����� �� ����� ��������� ����� ''�������''. ������� �����, ������� ������, ������� ����, ������ ������. �� � ��������� ��� ��� �� �������, ��� ������ ������ ��������� �� ���, ������ ���, ����� ��� ��. \n �, ���� �� �� ����������� ��� ����������, ���� ��� ��������� ������ ��� ����� ���� ���, � ��� ���, ��������� � ����� �� ���� ���. � ����� ���������, ������ ��� ����, ����� ����� �� ��������. ��� ���, �������, �����, �����-������� - �� �������. ��� ����� - ������� �������...";
			link.l1 = "�� ��� ��������-�� ������? � ���� �����, ���� �� ������������, ���������� � ����� � ��������� ������. � ������ ������ �����.";
			link.l1.go = "7";
		break;
		
		case "7":
			dialog.text = "� ��� ��� �� ������, �� ����� ������������� � ������������. ������������� - �����. ����������� - ������. ��������?";
			link.l1 = "��������. ��� ��� ��� � ������������-��?";
			link.l1.go = "8";
		break;
		
		case "8":
			dialog.text = "��, ������, ������, ����� ��� �������� �������, � �� ������ ����?";
			link.l1 = "� ��� ���, ���� ����, � ���� ����, � �� ������ �� ������ �� �����, ���������� ����. ����� �����������.";
			link.l1.go = "9";
		break;
		
		case "9":
			dialog.text = "������-������. ����, �� ��������? ������ ������������. � ��������� ���� �����������, � ���� ���� ����� ������ ����. ���� �� ���������, �� ����� ���, �� � � ������� � ������, ���� � ������������ ����� �� ����. � ����, ���, �� ����, �� ��������� �������...";
			link.l1 = "� �� �����, ���� �� �� ����! ��� �� �������, � ���� �� �����, ��������� �������, ���� � ������?";
			link.l1.go = "10";
		break;
		
		case "10":
			dialog.text = "���� ���, ����� �������� � ����?";
			link.l1 = "� ����������� �����? ��� ��� �� ����-�� �����?";
			link.l1.go = "11";
		break;
		
		case "11":
			dialog.text = "�� ����� ������� ����! ������ �� ������ ��� ������, � � �����, ������� �� ���� �������. ���... �� �����-������ ������ �� ���� ��� ��������� �����, �����?";
			link.l1 = "�������, ������!";
			link.l1.go = "12";
			link.l2 = "������� �����. ����� �����������? ��� ��� �� ������ �����?";
			link.l2.go = "13";
		break;
		
		case "12":
			dialog.text = "�������! ����� ���� � ��������� ������ �� ����! ������ � ����� ����, � ������� �� ���������� ������ �� �����: ������ �������, ��� ���������, ������� ��������� � ����������� �� �������. \n ��������� - ����� ������ � ����������� ������, ������� � ���� ��� (����������, ������), ������� �������� �����, �������� �����, � �� ��������� ������, � ������! �������� ��� �������� �����, � ��������� ��������� ��������.";
			link.l1 = "� ��� ��� �� �������� �����?";
			link.l1.go = "15";
		break;
		
		case "13":
			dialog.text = "� ���� ���� ���� ��������� ������ ������ �������. ������ ������� - ��� �������, �����������, ������� �� ������ ���������, ���, ������ ���������������� ������, ''����������''.";
			link.l1 = "��������?";
			link.l1.go = "14";
		break;
		
		case "14":
			dialog.text = "�� ������, ��������, � � � ������ �� �����, � �����, � �������, ��� ������� �� �����? ���������� ����� - �! ����� �� ���� ���� ��. ����� ���� �������. \n �������� - ����� �������� � ����������� ������, ������� � ���� ��� (���������� ������), ������� �������� �����, �������� �����, � �� ��������� ������, � ������! �������� ��� �������� �����, � ��������� ��������� �������.";
			link.l1 = "� ��� ��� �� �������� �����?";
			link.l1.go = "15";
		break;
		
		case "15":
			dialog.text = "��� ���������� ��������� �������� ����.";
			link.l1 = "� ��� ���� ����������� ������������?";
			link.l1.go = "16";
		break;
		
		case "16":
			dialog.text = "����, �� ���� ��� �����-��? �������, �� ���, ��� �� ��� ���������, ���� ������� ������ �����������.";
			link.l1 = "��, ������, ��������, � �������� ��� ������ �������, � ��� � �����? �� ����� ���-�� �������� ��� ������ ��������?";
			link.l1.go = "17";
		break;
		
		case "17":
			dialog.text = "��, ���� ������ �� ����� ����, ����� � ���� � ������, � �����, � ������ ����, ���� ������! �� ��� ��������?";
			link.l1 = "�������, ��������. ������ ��� ��� ������, �����...";
			link.l1.go = "18";
		break;
		
		case "18":
			dialog.text = "�, ������, ��� �������, ������. � ��� ���� ����� 2 ���� ��������, � ���� ��� ������ �� ���� ����...";
			link.l1 = "������?! � ������� �� � ������ ���� ���������?";
			link.l1.go = "19";
		break;
		
		case "19":
			dialog.text = "�, �� �� �����, ���, �� �����. � �� ������ ���� � ���? � ���, ��� � 2 ���� ������� ��� ����! ����� ������� �� ����� ����������, ���������� �������, �� �� �.";
			link.l1 = "� ������� �� �� ������?";
			link.l1.go = "20";
		break;
		
		case "20":
			dialog.text = "20 000 �����.";
			link.l1 = "����?!";
			link.l1.go = "21";
		break;
		
		case "21":
			dialog.text = "...(���������)... ��� �� ��� ������ � �� �����, �����?";
			link.l1 = "� �����, ��� ���� ���������, �� ��� ������ ������������ 20 000 - ���� ��� �����!";
			link.l1.go = "22";
		break;
		
		case "22":
			dialog.text = "�����, ������ ��� ����, �� �������� ����� ������� ����, ������� ���� � �� ������! � ����� ������ �� ����� ����� ��������� ����������.";
			link.l1 = "� ���� � �� ����� �� �����?";
			link.l1.go = "23";
		break;
		
		case "23":
			dialog.text = "��� �������? �������?";
			link.l1 = "� ������ � ������ �� �����!";
			link.l1.go = "24";
		break;
		
		case "24":
			dialog.text = "����� �����! ��������� ������������! �� ���� �� ���� ���� ������, �� ��� ��?!";
			link.l1 = "��, �� ����, ������...";
			link.l1.go = "25";
		break;
		
		case "25":
			dialog.text = "������, � ���������� ����� ��� �����. � ��������� ��� ��������� ����. �� ��� ���?";
			
			if(sti(PChar.money) >= 20000)
			{
				link.l1 = "������ � ��������.";
				link.l1.go = "26";
			}
			
			link.l2 = "��� ����� �����, ����� ������� ����� �����.";
			link.l2.go = "27";
			link.l3 = "�� ����� ��! ��� � ����� ���� ������� ����, � �� ����� ������ �� �������.";
			link.l3.go = "29";
		break;
		
		case "26":
			dialog.text = "��� ��� �� �����. ��� �����, ��� ������ ��������, � ��� ���������� � ������ �������. �����!";
			link.l1 = "� ���� �����. ������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorStart");
		break;
		
		case "27":
			dialog.text = "����������, � ����� ����� �� ����.";
			link.l1 = "��� ����� - ����� � ����. �� �������, ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "28";
			AddDialogExitQuestFunction("DozorWait");
		break;
		
		case "28":
			dialog.text = "����� ������?";
			if(sti(PChar.money) >= 20000)
			{
				link.l1 = "��� 20 000 �����.";
				link.l1.go = "26";
			}
			
			link.l2 = "��� ���, ��� ����� - ����� � ����.";
			link.l2.go = "exit";
			
			link.l3 = "������, � ��� �������... �� ����� ��! ��� � ����� ���� ������� ����, � �� ����� ������ �� �������.";
			link.l3.go = "29";
			NextDiag.TempNode = "28";
		break;
		
		case "29":
			DozorCancel();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}