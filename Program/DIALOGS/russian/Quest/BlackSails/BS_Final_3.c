
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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//������� � ���������� ��� ���. �� �������� � ���� � ������� �������. ������ � ��: �����������. �� ������������. ����� ������ ��� ����. ��� �� ��� ��������. ������, ��� ���(��) �������(����)! ����� ����������� � ������������. ������, ��� �� ����� ��!�
		
		//�����, ����� ��� �� ��������. ���������� � �������. �������� ����
		
		case "BS_F3_1":	//������
			dialog.text = "�����"+ GetSexPhrase("��","���") +" �������, �� ������ ���� � �������� ���"+ GetSexPhrase("","�") +"";
			link.l1 = "��� ����? ��� ������?";
			link.l1.go = "BS_F3_2";
		break;
		
		case "BS_F3_2": //������
			dialog.text = "��� ����, �� �������� ���������� � ����. ������ ������� �������� ��� ����, ����� �� ������ �� ���������� ���� � ��� ����� ���� ���. ��������� ��� ����������, �� ������.";
			link.l1 = "����������� ����� ��� ���-������ �����������. ��� ����� �������? �����? ������?";
			link.l1.go = "BS_F3_3";
		break;
		
		case "BS_F3_3":	//������
			dialog.text = "�� ������, �� ������. �� ������ ������ ���� ������ � ���������, ��� �������� �� ��������� ����� �� ����. � �������. ���������, �������� ��� � �������� ��� '����' � ������. ��� �����. �� ����� ��� �� ������. �.�";
			link.l1 = "������ �����! � � ����� �������"+ GetSexPhrase("��","���") +" � ��� '������'. ��� ���������?";
			link.l1.go = "BS_F3_4";
		break;
		
		case "BS_F3_4":	//������
			dialog.text = "�������� � ����������, � ��� ������ � �����, ��� ���� ���� ��� �����. ��������� ����� ���� � ���� ���� �� �����. ���� ��� ������ ����� �� ����, ������ ������ � ������� ����-��";
			link.l1 = "�����, � ���������� ���� ����� �� ��������. �����, ������ ��������.";
			link.l1.go = "exit";
		break;
		
		//������ � ��: ������� ������, ����� ���� ��������� ������. �� ����� ���-�� ������. �������� ���������� ��������. ����� ��� ������? �� �������! � �����.
		
		//� ������� ��� ������ �������� ������, ������� �������� �� ������ 
		
		//�� �������, ��� � ������� � �������� �������� ��� ������� �������� ��������. ������ � ����: ������ ��������!�, ����������� ����!�, ����? � ��� ��?�.
		
		//������ ������:
		
		case "BS_F3_5":	//�����
			dialog.text = "";
			link.l1 = "������� �������!";
			link.l1.go = "BS_F3_6";
		break;
		
		case "BS_F3_6":	//�����
			dialog.text = "���� ������ ...?";
			link.l1 = "��� �����, ����� ������, ��� �����. �����? � ������ ���� ����! ���� ��������!";
			link.l1.go = "BS_F3_7";
		break;
		
		case "BS_F3_7":	//�����
			dialog.text = "����. ��� �� ������ ���.";
			link.l1 = "����������� ��� ������� � ����� �����������. ������. ����� ����� ������ �� ��� ������������, ���� �� ���������, � ��� �!";
			link.l1.go = "BS_F3_8";
		break;
		
		case "BS_F3_8":	//�����
			dialog.text = "� ���� ��� ����� ����������, �� ���������� � �������. ��� ����� � ���� �� �����?";
			link.l1 = "� ���� ����������� � ���  �������, ����� �� �������.";
			link.l1.go = "BS_F3_9";
		break;
		
		case "BS_F3_9":	//�����
			dialog.text = "���������, ���� �� ��������� ���� �� �����, ���������� � ������������";
			link.l1 = "������, �� ���������, ��� ����� ������. ���� ����!";
			link.l1.go = "exit";
		break;
		
		//������ � ��: "�������� ��������(��). ����� ��������� �� ������� � �������� �����. ��� �� �� ���� �� �������".
		//����� �� �������. � ���������� �����, �����, ������.
		
		
		case "BS_F3_10":	//����� �������� ������.
			dialog.text = "���"+ GetSexPhrase("��","��") +" �����?";
			link.l1 = "���. ���� ����, ���� �� �������?";
			link.l1.go = "BS_F3_11";
		break;
		
		case "BS_F3_11":	//������.
			dialog.text = "������, ��� ��������� �� ������ ������� ����, �������� ��� ����� ��� ������ � ��� �����";
			link.l1 = "�������? �� ���������� � ����������!";
			link.l1.go = "BS_F3_12";
		break;
		
		case "BS_F3_12":	//�����.
			dialog.text = "����� �� �����-�� ���� � ������� ������. �������� �� ������ � ���";
			link.l1 = "���� ��� ���� ���-��, � ��� � ���� ��� ������ � ���?";
			link.l1.go = "BS_F3_13";
		break;
		
		case "BS_F3_13":	//�����.
			dialog.text = "�� ����� �� ������ ����� � ��������� ����������� � ����� �����. ������ �����, ��� ������, ��� � �������. �� ���� ��, ���������� �� ��� �������� ����/N� ��������, ��� ����� � ������� �������� � ������������? ���������� ��� ����� ������� ������, � ���, ��� ������� ��� ��������� ����� � ������ ������������, �� �����";
			link.l1 = "(��� ����) ����� ���� �� ����� �� ����� � ��� �������� � ������. (��������� �� ����) ����, ���. �� �������� �� ������? ��������� ��� ����� � ���� �������. ����� �������, ��������� � ������, ������ ����� ������ �� �� ��������";
			link.l1.go = "BS_F3_14";
		break;
		
		case "BS_F3_14":	//������.
			dialog.text = "�� �� � �������������, �� ��� ���������. � ����� ��� �� ����� ������ �����, ������ ������� ������ � ��������� �� �������. � �����, �� ������ ���� ������ �� ���. ������ � ����������� � ���� ���. ������� ����������� �����������, �� � ���, ��������� �� ������";
			link.l1 = "���, ��� �������. ��� ������� �����, ��� �������. ��� � �� ������ ������������! ��� ��. ����� ��� �����. �� ���������� �� ����."; //����� 75�
			link.l1.go = "BS_F3_15";
		break;
		
		case "BS_F3_15":	//�����.
			dialog.text = "����������� ����! �� � ����. ���� ������, � �������� ��������, �� ��������� �������������. � ������ ������ �� ����� ��� �� ����, ��� �� ���������. �� ����� ���� ������ ����? ��������� ��������? � �� ����� ������ �� �������������� ����������� ���� � ������� ��������";
			link.l1 = "� ��� � ������, ���� ���� �������������. ������� �����������. � ��� ��� ��� ����������� �������?";
			link.l1.go = "BS_F3_16";
		break;
		
		case "BS_F3_16":	//�����.
			dialog.text = "� ������ � ���������� ������� � ��������� ���� ���������� ������. ���� �� ������� ��������� ���� �� ����� � ��������� ��������� ��������� ��� ������� ������� ���� ������. � ��������, �������� ��� ������ � ������. �� ��������, ���� � ���� ������� ��� ��������� �������";
			link.l1 = "����� ��������� � ���. �������. ��� ���-������?";
			link.l1.go = "BS_F3_17";
		break;
		
		case "BS_F3_17":	//�����.
			dialog.text = "������. ����� � ������. ���� ����� �����, �� �����!";
			link.l1 = "��� ���? ������. ������� ��������. � ����� ����������� � ������� �� ����. ������� ����� �������. �� �������";
			link.l1.go = "exit";
		break;
		
		//������ � ��: "��������� ������� ���� ��������? ����-������� �������� ��������? ���� � ��� � ������������� ����������? ������ ���� � ����� �������� � ����. �� ��, ��� ���������� ������� ��������. �� ������� ������ ����������� ��������, ���������� ��������� � �������� ���� ������� �������! ��, ������ � ��������. ����. ������� �������"
		//��� � �������. ������� � ����.
		
		case "BS_F3_18":	//������.
			dialog.text = "��� �������, ��� �� � �������� � � �������! �� ����� �����, ��� � ��� ����! ߅";
			link.l1 = "����. ����� �� �����, ��� ��� � ��� ����. � ����������� �� ������ ����� ����� � ��� ���������� ���� ������� �� ������ ����������. �������, �� ����! ��� ����������!";
			link.l1.go = "exit";
		break;
		
		//���� � ���������. ������� � ����.
		//������ � ��: "�������� ������ � ���� �����, ����� �������� �����. � ����� ����, ��� ������ ������"
		//������� ���� � ��. ������ �� �������.
		
		case "BS_F3_19":	//������. ������� � ������� �� ������.
			dialog.text = "������, �� ����� ������� ������ ��� ������, � ��� � �� ������������� �������. �����, ������� �� ����� ��� ���� � ������� ��� �� �������� �������� ����?";
			link.l1 = "��� ���� ������ ����� ������, ���� ��������� � ��� �. ������� ���� � ����������� �����! ��� ����.";
			link.l1.go = "BS_F3_20";
		break;
		
		case "BS_F3_20":	//������.
			dialog.text = "������� ����. �� �������� �������!";
			link.l1 = "(��� ����) � �����...? ���! ����� �� ������!";
			link.l1.go = "exit";
		break;
		
		case "BS_F3_21":	//������. ������� � �������.
			dialog.text = "������, �� ����� ������� ������ ��� ������, � ��� � �� ������������� �������. �����, ������� �� ����� ��� ���� � ������� ��� �� �������� �������� ����?";
			link.l1 = "���������� �����������! ������ �� ���� ���� �������, ���� ��������� � ��� �. ��� ������ ����";
			link.l1.go = "BS_F3_22";
		break;
		
		case "BS_F3_22":	//������. ������� � �������.
			dialog.text = "����� ����� ���! ��� ��!";
			link.l1 = "���! � ��� ��� � ����� ���� ����-������ �������!"; //�� � �������, �������� � ������������.
			link.l1.go = "exit";
		break;
		
		//� ����� ��������� ������ � ��: "����, � �� ���������. ������ ����� � ������ ������ �����? ��� ������, ��� ����� ������ ���������� ����? ��� ����� ��������� ������ �������� � ���������? ����������� �� �����, �������� �� ������ ������� �� �� �����. ������ ���������� �����, ����� � ������� ������, �� � �������� ���� �������� ����, � ����� ������ �� ����� ��������. ������ ������ ����� ��� ������ �����. ���� ������!"
		//��� ����� �����. ���� ������ ������. 
		//���� ������� ������ �������� � �����.
		//����� �� �������, � ������� ������� ������ � ��: "���� � ������� �������, �������, ���� �� ��������. ������� �������. ����� �������, ��� ���� ��� �� ����� �� �����, �������� ����������"
		
		case "BS_F3_23":	//���������.
			dialog.text = "��� ���-������ ��������, �������?";
			link.l1 = "���. ��������, �� �� ������ ��� ����� �����? �� ������� �������� �������, �� ��� �������� �� ��� �����?";
			link.l1.go = "BS_F3_24";
		break;
		
		
		case "BS_F3_24":	//���������.
			dialog.text = "��������� �� ������� �����? �� ������ ��������, ��� ������ �����, ����� ����� ��� � ����� �������� � ����� ���� ����";
			link.l1 = "�������. ��� ���� �� ���..., �� ���-������ ��������!"; //����� 500 ������
			link.l1.go = "exit";
		break;
		
		//������ � ��: "���� ������� � ��������. ����� ���������".
		//� ����� ����� ������ �����. ���� ����� ���������� - ������ �������. �������� ������, �������� � ������ �� �����.
		
		case "BS_F3_25":	//����.
			dialog.text = "��� �� ������ �����������, �������. ���������� ������ ������ ����� ����� ������!";
			link.l1 = "��� ������� �� ���� ���� � ������ � ����. � �� ����! ����� �������! ������ � ������� � �������. �� ����� ������! �� ����� �������, � ������� �� ����. ����������, ��� ���� � ����. ����� ����, ������ � ������� ���� �����. ����� ���� ����������!";
			link.l1.go = "BS_F3_26";
		break;
		
		
		case "BS_F3_26":	//����.
			dialog.text = "� ��� �� �������? �������? �����������, �������?";
			link.l1 = "�� ������ �����, � ���� ���� ����� ������ �����. � ��������������� ������ ���� ����������. �� ����, �����. � ���� ���� ������� ����-������ ���������!";
			link.l1.go = "BS_F3_27";
		break;
		
		case "BS_F3_27":	//����.
			dialog.text = "����� ��������. ��������� � ��������� �������, ��� �� ������ � ��, ������� ��� ������ ������ � ���������� �������. �������������� ������ � �� ���� ������� ������ � ����� � ������. ������� ����� ������� ����� ����� ������ ���� �������, � ��� ����� ������� �� ���, �� ����������. � ���� ��, ����� ���������� ��� ������������ ������ � ��������� ��� ���������. ��� ���, ���� ������ �������� �� ������� � ��� ���� �����. �� ����, ����� � ������, ��� ������ �� ������, � �������� ����� �� ���� � ����";
			link.l1 = "�������. ��������, �������, ��������. �������� ������, �� ����� �� �����������.";
			link.l1.go = "BS_F3_28";
		break;
		
		case "BS_F3_28":	//����.
			dialog.text = "��� ���������� ��������, ��� ������� ����, ������� ���������, ���������� ������, ��� ������-�� ������� �������. ������ ������-������� ������� � �����������, ������� �����������. ����, ����, ��� � �� �, ����������, ��� ������� � ��� ��� ����. � ���� ���� ��� ��������� ��������, ��� ������ �� �������� � ����� ����������";
			link.l1 = "� ���� �����, ����. �����, ������. ��� �� ������ ��� ������?";
			link.l1.go = "BS_F3_29";
		break;
		
		case "BS_F3_29":	//����.
			dialog.text = "���� ������������� ���������� � �������� ������� � ������ ������. ����������� ��������� �� ������ � � ���� ���. �������, ����������. � ����� � ���� ������ � ��� ��������� ������ ����� �� ��. �� � � ����� ���� �� �� ������, � ������ ������ �� �����, �������� ������ �����. ����������� � ������ ������. � ����� �� �������, ������������ ��������. ������� � ����� ���, ���� ������ ������ �������";
			link.l1 = "�� ������, ��� ���� ���������� ���������� � ��������! ��� �� ����� ������ ����� ���������!";
			link.l1.go = "BS_F3_30";
		break;
		
		case "BS_F3_30":	//����.
			dialog.text = "���������� ��� �� ����� ����� � ��������� � ������ ����. ����, ���� ����, ��� ������, ��� � ������.";
			link.l1 = "����� ����, ���� ���� ���� �������?";
			link.l1.go = "BS_F3_31";
		break;
		
		case "BS_F3_31":	//����.
			dialog.text = "����� ������. �� ���� ������ ���������� ���� �� ���������� � ��������� ������ � ������. ����� ������� ������� ����, � �� ����. �� ��� ��� ��� ����.";
			link.l1 = "������, �� ����� �������!";
			link.l1.go = "exit";
		break;
		
		//������ � ��: "�� �����-�������� ����� �������, ����� ����������� ������� ����� ��������� �����. �� ��� ���� ���-��. ����� � ����� ���� �� �� ������"
		//� ����� ���� �� �� ������, �� ������ �����. ������ � ��: "�����. �������� ������. ����� ��������� �����, ������� ��������� � ���� ������, ����� �� ���� �� ��� ���������. ������� � ������. ���, ��������: ���� ��� �����, ����� �������, ����� ��������, ����� ��������. ��� ��, � ����."
		//� ��� ����� � ���� ����������� ���������� ��������. ���. �������. �� ������ ���� 30 ������� � ����. ������ � ��: "������ ���� �����. ���� ������� �� ����� ������ �����. ����� ���� ���������".
		//��������. �� ������ ��������� ������.
		
		case "BS_F3_32":	//������.
			dialog.text = "������� " + GetFullName(pchar) + "? � �� ������� �� �������!";
			link.l1 = "����� �� ����� �� ����������? ��� ��� � ����?";
			link.l1.go = "BS_F3_33";
		break;
		
		case "BS_F3_33":	//������.
			dialog.text = "������ ��������� � ���������! ������ ��������. ��� �� ������.";
			link.l1 = "� ��� ��? ��� �� ���������?";
			link.l1.go = "BS_F3_34";
		break;
		
		
		case "BS_F3_34":	//������.
			dialog.text = "������� �� ����"+ GetSexPhrase("���","���") +", � ������ ���������!" ;
			link.l1 = "������, � �����"+ GetSexPhrase("","�") +".";
			link.l1.go = "exit";
		break;
		
		//������ � ��: "���-�� ���������. ���� ������� ������ ������� � ���������."
		//����� �� ��������. � ������ �������� ����.
		
		case "BS_F3_35":	//����.
			dialog.text = "�� �����. ������. ������ ��������� ������ ������, �� �������� �� ��� ��� �� �������������, ����� ������ ��������. � ��������� ���������� ���" ;
			link.l1 = "��� ��������� ��? �, ������, �������"+ GetSexPhrase("��","���") +" �� ����� ���-����� �� ����� �����. ������ � �������� �����";
			link.l1.go = "BS_F3_36";
		break;
		
		case "BS_F3_36":	//����.
			dialog.text = "����� ��� ��� �� ������. �� ���������, ������������� �� �������, ����������� ���������. �������, ������, �����. � ��������� ���������, �� �������� ���. ��� �����!" ;
			link.l1 = "�� ����� �������� ��� ��� �����?";
			link.l1.go = "BS_F3_37";
		break;
		
		case "BS_F3_37":	//����.
			dialog.text = "���-�� � �������� �� ������ ����� �� �������� � ������ �����, � ��� ����������� �������. ���������� ���� ������, �������� � ������.  ��� ��� ���� ��� ��������� ������. � �������� ��, �� �� �������. � ������� ��������� ���� ���������� � ��������� �� ����������. ��� ���������� ���-���� ��� ������ ������. �� ���� �� ��������� ���� �������, �� ������ ���� ��� ����� �, ���� ���, �������� ��� ������!" ;
			link.l1 = "������� ������? ��� ��, ��� ����� ���������. ������� �����, ���������� �� ���������!";
			link.l1.go = "exit";
		break;
		
		//������ � ��: "��������� ������ ������. ����� ���������� ���������� �������� ��� ����� �����. �������� ����������� ����������� �������. ��, �� �� ����� �������, � ��� �� ����� ����. ������� ������ �� ���������".
		//��� �� ���������. ��� ������ ���� � ��������� � ����������� ���������, ������� �� ������� ���������. ������� ��� ������� ������������! ���� ���� �� ������!� �������� �������� ������� �� �����. � ���-������ �����.
		//�������� ����, ���� ��� : ���� � ����� ����, ��� ������! �������, � ���!�
		
		case "BS_F3_38":	//����.
			dialog.text = "��� � ����� ����, ��� ������! �������, � ���!" ;
			link.l1 = "�� ����!";
			link.l1.go = "exit";
		break;
		
		//������� ������� ���� �� ���������. ��������.
		
		
		case "BS_F3_39":	//����.
			dialog.text = "���, ���� ��� ���� �����?" ;
			link.l1 = "��� ��� �� �����! �������? ����� ��������! ������!";
			link.l1.go = "exit";
		break;
		
		//����� ���� ������� ���-������. �� ����� ��� ����� �������. � ���� ����� � ����. ���� ���� �� ������ - � � � �����������. ��� ������ ������� ��� ������ ����� �������� ������.
		
		case "BS_F3_40":	//�����.
			dialog.text = "����! ���������, ���� ������������ �� �����!" ;
			link.l1 = "� �������, �����!"; //����
			link.l1.go = "BS_F3_41";
		break;
		
		
		case "BS_F3_40":	//�����.
			dialog.text = "� �������. "+pchar.name+" �� �� �� ��� ������� ����������! �� ��� ���� �����." ; //�������.
			link.l1 = "� �� �������. ������ ��� ��������!"; //����. �������.
			link.l1.go = "BS_F3_41";
		break;
		
		case "BS_F3_41":	//����.
			dialog.text = "�� ���? ������ �� � �?!" ; 
			link.l1 = "������ ����� �����? � ��� �� ��� ������!";
			link.l1.go = "BS_F3_42";
		break;
		
		case "BS_F3_42":	//����.
			dialog.text = "�� ������� ����� ������� �������. � ���� ����� ������ ����� ��������!" ; 
			link.l1 = "���?! �����?";
			link.l1.go = "BS_F3_43";
		break;
		
		case "BS_F3_43":	//����.
			dialog.text = "��������� ������ �� �������, ���� � ����� ������ � ������� ��� ��������. �������� ������� � ����� � ���� ���� � �������� � �����. ������ � ������ � � ����� ���� �������. ���� � � ������ �����������, �� �� ����������. ��� ����������. �������� ��� �����, ��� ������ ���������� �������, ���� � ������ � ��� ����� ���. � �� ����" + GetSexPhrase("","�") +" ��������,  ������������ ��������� ������ ��� ���������� ��������" ; 
			link.l1 = "���� ��� ����� ���������? �� ����� ������ � �������!";
			link.l1.go = "BS_F3_44";
		break;
		
		case "BS_F3_44":	//����.
			dialog.text = "� ����� � ����. Ÿ � ������ ���������, ���� �� ����������� ��� ����������. ��� � ����� ����� ��������. ������ �������! ������ ���-�� ���� ����!" ; 
			link.l1 = "� ���� ��� ���� ����, ������. �� ���� �� �����������. ������� ��� ������ �����!";
			link.l1.go = "exit";
		break;
		
		//������� � ������. �������. ��������, ����� ����� �����. ��� � �����. ��������� �������.
		
		case "BS_F3_45":	//�������.
			dialog.text = "�� "+pchar.name+", �� ���� ���� ���! ��� ��� ����? ��� �����?" ; 
			link.l1 = "��������, ����. ��� �� ��� ��������?";
			link.l1.go = "BS_F3_46";
		break;
		
		case "BS_F3_46":	//�������.
			dialog.text = "����� �� ������, ����� �� ����� ������ ���������. ��� ������ ������� �������!" ; 
			link.l1 = "� ����� ������� ��� � ����. �� �� ����?";
			link.l1.go = "BS_F3_47";
		break;
		
		case "BS_F3_47":	//�������.
			dialog.text = "������?! ���! ��! ��, �����, � ����� ���������� �����. � ��� � ���� ��� ������ ������� ��� ������!" ; 
			link.l1 = "����� � ����!";
			link.l1.go = "exit";
		break;
		
		//������ � ��: "����. ���� ���� ����. �� ��� ��� ������! � ����, ������ ����. ���� � �����(��) ������� ���, ��������� �������� ��������. ����� ������. �� �������� � ������! �������� ����������� � ������� � �������, ��� ����� ������!"
		//������� � ����, ��� ������� ���������. �����. ������� �� ��������. �� ��� �� ������ ������� ���������-���� (���� ����� � ������). ����� �������� �� ���������, ���� �� ������-������ �������� �����. ���� ������� � ���� ������ � ��� ��������. ������� �� �������. ��� ������ ����� ������� � ������ (���� ����������). ���� ����� �� �������. � ����� �������� � �������. ����� ������. ������
		
		
		case "BS_F3_48":	//�����.
			dialog.text = "���� ����? ����, �� �� ��� ������� �����������. � �� ������" +GetSexPhrase("","�")+" ����������� ���������� �������? �����������, ������, ����������� �������? �� �� ���������, ��� ��� ����� ���� �������� � ��� �� ����� �������� �� �������. � ��� ����� �� ���!" ; 
			link.l1 = "�";
			link.l1.go = "BS_F3_49";
		break;
		
		case "BS_F3_49":	//�����.
			dialog.text = "��� ������ �� ����� ���� ���� ��������. �� ���� ��� �� ���������.  ���� ��� ������� �� �������. �������� ������ �����, ����� ��� ����������� ������� � � ������� ��� ���������� �����, ������� � ������� ���������. ����� �������, ��������� �� �������� ������� ��������, � ��� ������ � ��� ��� ����� ����� ���. ����� �" ; 
			link.l1 = "��� ��� � ���� ������ ��������? �����, ������ ������? ��� ������, ��� ������. ���� ������ ����������� � ������. �� ������ �������?";
			link.l1.go = "BS_F3_50";
		break;
		
		case "BS_F3_50":	//�����.
			dialog.text = "������ ���������, ������ � ������� ��������, ����������� � ���� � ����������������. ��� ���� � ����� ���. � ��� �� ��������� �����, ����� ������� ������. �� ���" + GetSexPhrase("","��") +" �� ���� �������� ������������, �� � ���� �������������� �������, ������� �������� ����� �������������. ��� � ����. ��� ����� ������� �������, �� ��� ������ ������������!" ; 
			link.l1 = "������ �������� � ������!";
			link.l1.go = "exit";
		break;
		
		//����. �� ����� ������, ����� ���� ������� �������������. � ������� 5�� �����, ������� ������ ������ (������������).
		//��� ������ ��������� ���� ������� ������� - �������. ����� "��������" � ����� ��������. ���, ��� �������� � ������ �������.
		//����� ������ �� �� �����. ������ ����� �������, �� �������. �� ������ ����, �������, ��.
		
		case "BS_F3_51":	//�������.
			dialog.text = "����� ����?" ; 
			link.l1 = "̸���.";
			link.l1.go = "BS_F3_52";
		break;
		
		case "BS_F3_52":	//����.
			dialog.text = "���. ����. ����� ��� � ������� ����� ���� ���� �� ������" ; 
			link.l1 = "����� �����, ��� ����, ����� ����, � ������� ����� ���� ����!";
			link.l1.go = "BS_F3_53";
		break;
		
		case "BS_F3_53":	//����.
			dialog.text = "�����, ��. ������� ����, �������, ����� ��� �����, � �����-�� ��������� � �����. ��� ������ �� ������� �������� �� �������, ������� ���������!" ; 
			link.l1 = "��, ����! ��� ������ ������, �������������. ����������? � � ��� ������� � �������. �����" + GetSexPhrase("","�")+" �������."; //����� �����, ������.
			link.l1.go = "exit";
		break;
		
		//������ � ��: "��� �� �� ���� ���� � ������(��) ������������ �����. ����� ������ ���� ����������? ��������, ����, ������. ��� �� ��������� �� ������, ����� � ������ �������? ����(��) �� � ��������� ������� ��� ������������ ������? ����, ��� ������ �����! ����� ���������".
		//������ �������� "������ ������ �����", ������ �����.
		
		case "BS_F3_54":	//�������.
			dialog.text = "��! �� ���" + GetSexPhrase("","�") +"? ������� �� ������!" ; 
			link.l1 = "���? ��� ������?";
			link.l1.go = "BS_F3_55";
		break;
		
		case "BS_F3_55":	//����.
			dialog.text = "��� ����� ���������. ������, �������. ��. ������� ����� ����� �� ��������� �������, ������!" ; 
			link.l1 = "��� ����� ���� ������, ��� � ���� ������ �������� � ��� �����������.";
			link.l1.go = "BS_F3_56";
		break;
		
		case "BS_F3_56":	//����.
			dialog.text = "�������� ��� �������? ������ ��� ������ � �����? ��� ����� ����� �� �����! ������ ���� �����! ������! ����� ������ ��������, ���������� ������� �����, ������ ���-�� ����!" ; 
			link.l1 = "���� ��� ���������?";
			link.l1.go = "BS_F3_57";
		break;
		
		case "BS_F3_57":	//�������.
			dialog.text = "���? �� �������?" ; 
			link.l1 = "������-��������? �� �������� �� ����.";
			link.l1.go = "BS_F3_58";
		break;
		
		case "BS_F3_58":	//����.
			dialog.text = "��, ���� �������. � ���� ���� �������� ���. �� ������ ����� ������." ; 
			link.l1 = "����� � ����";
			link.l1.go = "exit";
		break;
		
		//���� ������ �� ����. � ����� ������ ������� �������� �������.
		
		
		case "BS_F3_59":	//�������.
			dialog.text = "� ��������� �� �����, ������ ���, ��  �� � ����. � �� ����?" ; 
			link.l1 = "��������� ������ ����. ���� ���-�� ������ ���������. �����, ����!";
			link.l1.go = "exit";
		break;
		
		//����� � ���� �����, ��� � ������, ���������.
		
		case "BS_F3_60":	//���������.
			dialog.text = "�� �� ������ �������?" ; 
			link.l1 = "� �����" +GetSexPhrase("","�")+" ���������������� ������� ����� �����. ������.";
			link.l1.go = "BS_F3_61";
		break;
		
		case "BS_F3_61":	//���������.
			dialog.text = "���, �����! �� � ��� � �������. ��������� � ������ ���� ����, ����� ������ ��������� �� ������ ����������� � ������������. � ��������� � �����!" ; 
			link.l1 = "��������� ���.";
			link.l1.go = "exit";
		break;
		
		//��� � �������. ������� �����.
		
		case "BS_F3_62":	//��
			dialog.text = "� � �� ������" +GetSexPhrase("��","���")+" ������� ���� �����!" ; 
			link.l1 = "��� �������! ���� ��� ������� �������� �����, ��� ������ �� ������. � ����� ������ ��� � � ��������, � � ���������. ������ ����� �������� �� ����.";
			link.l1.go = "BS_F3_63";
		break;
		
		case "BS_F3_63":	//��.
			dialog.text = "��� ��. ����� ��� ������ ���������. ���, ���� ����, ���������. ����� ��, ��� ������� ���������� �� ������ �����" ; //����� 2.5��
			link.l1 = "�� ����� ������������. ��� ����� ��������� �������. � �������� ���������� ���������� �� ����������� ��������. � ����� ����� ���. �� ������" + GetSexPhrase("","�") +" ��� �����?.";
			link.l1.go = "BS_F3_64";
		break;
		
		case "BS_F3_64":	//��.
			dialog.text = "��. ����� ����, ����  ����." ; 
			link.l1 = "������� ������� � �����?";
			link.l1.go = "BS_F3_65";
		break;
		
		case "BS_F3_65":	//��.
			dialog.text = "��� ������, ��. ���� ��� ����� �� ������������ �������. ������ ����!" ; 
			link.l1 = "������� ����, �������, ����� �� �������.";
			link.l1.go = "exit";
		break;
		
		//������ � �����. ���� � ������� � ���� �����, � ����������� ������������. ����� �� �������� ������ �� �˸���� ������.
		//�� ������ �� ������� � ��������� �������
		
		
		case "BS_F3_66":	//�������.
			dialog.text = "���� ����� �����!!! ��� � � ������ ���������� �����! � ������ � ���� ���� �����!" ; 
			link.l1 = "����� ������� �������� �������� ������?";
			link.l1.go = "BS_F3_67";
		break;
		
		
		case "BS_F3_67":	//�������.
			dialog.text = "��! �� �� �����. �����������. ����� ������ � ������! ����� ����� ���!" ; 
			link.l1 = "��� ��� ���� �������, ����. ��� ���� �������. ���� ���� ������� � ������ �� ����� ������ ���� � ������!"; //����� 25�
			link.l1.go = "BS_F3_68";
		break;
		
		case "BS_F3_68":	//�������.
			dialog.text = "�� �� ������" +GetSexPhrase("","�")+"?! ����, ���,  ��. � ����� ����, �����������! �� � �������� �� �� ������� ������!" ; 
			link.l1 = "���������� �������!";
			link.l1.go = "exit";
		break;
		
		//����� ������ � �����.
	
}
	
	
}