// Warship. ������ ��� ������ � �������
// ������� ����� ����������� �� ������ ������, ����� ��� � ����� ����� ����

#define PI 3.14159265
#define PIm2 6.28318530
#define PId2 1.57079632

float FRAND(float _x)
{
	return rand(32768) / 32768.0 * _x;
}

// boal
float frandSmall(float _x)
{
	return rand(32) / 32.0 * _x;
}

// Warship 30.07.09. -->
// ������ 0.0 ... 1.0
float Random()
{
	return rand(32768) / 32768.0; // 65536
}

// ������� - �� �������� ��� cRand() - �� ���������� �� ��������������� �����,
// � ��������� �� ����������� ��� ������, �� ��� � ������ ����� ���� ���������
// ���������� �����, ��������, cRand(5) ����� ������ 5 ���� ������ ���� � ����.
// ������� ���� ������ ��������������� �����, ����� ���������� ��� � PChar � ���� �� ��������
// ����� ���� ����� ���������� ���-��. PChar.dayRandom ��������������� � ������ ���� ���������� ���
int dRand(int _max)
{
	float dayRandom;
	
	if(CheckAttribute(PChar, "dayRandom"))
	{
		dayRandom = stf(PChar.dayRandom);
		return MakeInt(dayRandom * _max + 1.0 / (_max + 1)); // 1.0 / (_max + 1) - ��� ����������, ����� _max �� ������� �������
	}
	
	dayRandom = Random();
	PChar.dayRandom = dayRandom;
	
	return MakeInt(dayRandom * _max + 1.0 / (_max + 1));
}
// <-- Warship 30.07.09

// cRand() - ����������� ������ ����. ����� �� �������������, �� ����� ���� - dRand()
//����������� ������
int cRand(int num)
{
	if (num < 1) return 0;
	if (num > 30) return rand(num);
	int sResult = num;
	int iData = GetDataDay();

	int iDel = 30.0 / (num + 1) + 0.5; //�������� ������
	int step = iDel; //��� ���������� ������ ��������� � ������

	for (i=0; i<num; i++)
	{
		if (iData < iDel) 
		{
			sResult = i;
			break;
		}
		else iDel += step;
	}
	return sResult;
}

// ������� � �������
float Radian2Degree(float _rad) 
{
	return 180 / PI * _rad;
}

int func_max(int a, int b)
{
	if (a > b) return a;
	return b;
}

int func_min(int a, int b)
{
	if (a > b) return b;
	return a;
}