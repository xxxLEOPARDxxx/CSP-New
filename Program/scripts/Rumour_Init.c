#define MAX_RUMOURS 30  // ����� ����� ������
#include "scripts\Rumour_templates.c"
#include "scripts\Rumour_func.c"
#include "scripts\Rumour_generate.c"
#include "scripts\Rumour_Data.h"
#include "scripts\GoldFleet.c"

object	Rumour[MAX_RUMOURS]; // ���� ������
object RumourParams;         // ������ ���������� ��� ��������� ������

int id_counter;




void SetRumourDefaults()// ��������� ���� ���������� - �������� �������
{
	int i;
	ref CurrentRumour;
	id_counter = 0;

	for(i = 0; i < MAX_RUMOURS; i++)
	{
		makeref(CurrentRumour, Rumour[i]);
		CurrentRumour.id = id_counter;  // ID �����
		CurrentRumour.text = DEFAULT_TEXT[i];// ���������� ��������� ����� � �������
		CurrentRumour.state = "1"; // ������� ��� ����� ��������� �� ���� � ��� �� ����
		CurrentRumour.tip = "citizen,capitan"; // �����
		CurrentRumour.rep = "none"; // ���������
		CurrentRumour.starttime = (DateToInt(0));// ����� ������� ���� ������������ ����
		CurrentRumour.actualtime = (DateToInt(40));// ��� ����� ����� ������ ����� = 40 ����
		CurrentRumour.event = "none"; // �������� - ���
		CurrentRumour.next = "none"; // ����������� - ���
		id_counter++; // ������� ������
	}
	for(i = 0; i < 9; i++)
	{
		makeref(CurrentRumour, Rumour[i]);
		CurrentRumour.id = id_counter;  // ID �����
		CurrentRumour.text = POOR_RUMOUR_TEXT[i];// ���������� ��������� ����� � �������
		CurrentRumour.state = "5"; // ������� ��� ����� ��������� �� ���� � ��� �� ����
		CurrentRumour.tip = "poor"; // �����
		CurrentRumour.rep = "none"; // ���������
		CurrentRumour.starttime = (DateToInt(0));// ����� ������� ���� ������������ ����
		CurrentRumour.actualtime = (DateToInt(300));// ��� ����� ����� ������ ����� = 300 ����
		CurrentRumour.event = "none"; // �������� - ���
		CurrentRumour.next = "none"; // ����������� - ���
		id_counter++; // ������� ������
	}
	makeref(CurrentRumour, Rumour[i]);
	CurrentRumour.id = id_counter;  // ID �����
	CurrentRumour.text = "�� �� ������� � ������ �������, ��� ��������� � ��� � ������? ����� ������ �������, � ��� ����������!";
	CurrentRumour.state = "1"; // ������� ��� ����� ��������� �� ���� � ��� �� ����
	CurrentRumour.tip = "citizen"; // �����
	CurrentRumour.City = "PortSpein";
	CurrentRumour.rep = "none"; // ���������
	CurrentRumour.starttime = (DateToInt(0));// ����� ������� ���� ������������ ����
	CurrentRumour.actualtime = (DateToInt(500));
	CurrentRumour.event = "none"; // �������� - ���
	CurrentRumour.next = "none"; // ����������� - ���
	id_counter++; // ������� ������
}

void RumourInit();
{
	//Log_SetStringToLog("�����!");
	trace("�����!");
	TemplateLoad();
	SetRumourDefaults();
	// ==> ������� ������� ��� ���� homo 05/11/06
	SaveCurrentQuestDateParam("Siege_DailyUpdate");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
