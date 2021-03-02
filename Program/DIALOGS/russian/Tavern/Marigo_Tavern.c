// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("��� ������� ������ "+ GetCityName(npchar.city) +" � ����� �������. ��� �� �� ������ ������?",
                          "�� ������ ��� ��������� ��� ����. ��, ��������, ������������...", "������� �� ��� ������ ��� �������� � �����-�� �������...",
                          "��� �� "+ GetSexPhrase("�������","��������") +" ��� ������� ���� � �� ��...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("������, " + NPChar.name + ", ���-������ � ��������� ���.", "�����, "+ GetSexPhrase("�����","������") +" ���-��...",
                      "�� ��, ������������� � ������ ���...", "�� ��...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			//������
			if(CheckAttribute(pchar, "Whisper.FindDesouzaHol"))
			{
				DeleteAttribute(pchar, "Whisper.FindDesouzaHol")
				link.l1 = "��������, � ���� ��� ������� �� ��������� ������ �������������� ����������? � ��� ��� ������ ���� ������ � ����� �������� �� ����.";
				link.l1.go = "FindDesouzaHol";
				break;
			}
			//������
			
			// ==> ��������� ���� ��������� �������.
			switch(pchar.questTemp.State)
            {
                case "SeekChumakeiro_ToAaronHouse": //����������� �������, ����� �1. ������ ���������.
                    link.l1 = HeroStringReactionRepeat("��������, � ��� � ������ ������ ����� ����� ������ ���������. ������ ������?",
                    "� ��� ������ "+ GetSexPhrase("�����","������") +" ��������... ��� ��������, ������.", "�����, ��-�-���-�-��...", "� ������� �����������, ������...", npchar, Dialog.CurrentNode);
                    link.l1.go = DialogGoNodeRepeat("Step_H1_1", "", "", "", npchar, Dialog.CurrentNode);
                break;

            }
            // <== ��������� ���� ��������� �������.
			

 		break;
        //============ ����������� �������, ����� �1. ������ ���������.
 		case "Step_H1_1":
    		dialog.text = "����. � ��� �������� ���������� ��� ��� �����. ������� �������, �������� ��������...";
    		link.l1 = "�������... � ��� ���� ���, ������� ���� �����?";
    		link.l1.go = "Step_H1_2";
 		break;
 		case "Step_H1_2":
    		dialog.text = "������ �� ���������� ������ �����������. ������� ������ ���� � ��� ��������� ��� �������, ������ ����������� �������. �� ������ ��� ��� � �������, " + npchar.name + " ������ ����� �� ������.";
    		link.l1 = "������� ����, ����� ������ ����� ������.";
    		link.l1.go = "Step_H1_3";
 		break;
 		case "Step_H1_3":
    		dialog.text = "������� �������.";
    		link.l1 = "��� ������?";
    		link.l1.go = "Step_H1_4";
 		break;
 		case "Step_H1_4":
    		dialog.text = "��� � ������ - ������� ������� ��������� ������. � ��� ��� ���������� �, ������, ����������� � ���� �� �������.";
    		link.l1 = "���?";
    		link.l1.go = "Step_H1_5";
 		break;
 		case "Step_H1_5":
    		dialog.text = "�����-�� ����������, ������ ��� ��� ����� � ��� � ������. � ������ ������� ���� �������� ������, ��-��.";
    		link.l1 = "�-��, ������ �� ��... �� �� �����, ������� ���� ��� ���. ������.";
    		link.l1.go = "exit";
 		break;
		case "FindDesouzaHol":
    		dialog.text = "�� ��� ���, �� � ���� ���������� ���������� ����, ���������� ��� ��������. ������ � ��� ������ �����������.";
    		link.l1 = "������, �������.";
			pchar.Whisper.FindDesouzaHolWaitress = true;
    		link.l1.go = "exit";
 		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

