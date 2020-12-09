
// -------------------------------------------------------------
// Mett: ��������� ����
// ��������� �� ������ ���� ��������:
// �����, ������ ����, ����, ��������� ����, ������� ����, �����
// -------------------------------------------------------------

string WhrGetSeaPresetFromWind(float fWind)
{
	string sPreset = "calm";
	if(fWind > 4.0) sPreset = "light_breeze";
	if(fWind > 7.5) sPreset = "breeze";
	if(fWind > 11.0) sPreset = "moderate_breeze";
	if(fWind > 14.5) sPreset = "strong_breeze";
	if(CheckAttribute(&WeatherParams, "Storm") && sti(WeatherParams.Storm) == 1) sPreset = "storm";
	return sPreset;
}

void WhrSetSeaPreset(int iCurWeatherNum, string sPreset)
{
	ref Whr = &Weathers[iCurWeatherNum];
	/* Whr.Sea2.Reflection = 0.8;
    Whr.Sea2.Transparency = 0.3;
    Whr.Sea2.Frenel = 0.3;
    Whr.Sea2.Attenuation = 0.3;
    Whr.Sea2.WaterColor = argb(0, 10, 30, 50);
    Whr.Sea2.SkyColor = argb(0, 255, 255, 255);
    Whr.Sea2.BumpScale = 0.075; //������ ����� */

	switch(sPreset)
	{
			case "calm": //�����
				Whr.Sea2.Amp1 = 1.0;//��������� 1 �����
				Whr.Sea2.AnimSpeed1 = 1.0; //�������� ��������
				Whr.Sea2.Scale1 = 1.5; //������� �����
				Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 1.5"; //�������� ��������

				Whr.Sea2.Amp2 = 0.7;
				Whr.Sea2.AnimSpeed2 = 2.0;
				Whr.Sea2.Scale2 = 2.0;
				Whr.Sea2.MoveSpeed2 = "-1.5, 0.0, 0.0";

				Whr.Sea2.BumpScale = 0.075; //������ �����
				Whr.Sea2.PosShift = 2.0;//��������������� ����

				Whr.Sea2.FoamK = 0.5;//������� ���� �� ������ 0.1 - ���� ����� � 10 ������ 1.0 ����� ���� ����� ������
				Whr.Sea2.FoamV = 0.9;////������ � ������� ���������� ����
				Whr.Sea2.FoamUV = 1.0; //������� ����
				Whr.Sea2.FoamTexDisturb = 0.7;//����� �� �������. �.�. ��� ��� ���� �������. �������� �� 0.0 �� 1.0

				Whr.Sea2.Reflection = 0.8;//0.8;
				Whr.Sea2.Transparency = 0.6;//0.6;
				Whr.Sea2.Frenel = 0.3;//0.6; 
				Whr.Sea2.Attenuation = 0.3;//0.2;
				Whr.Sea2.WaterColor = argb(0, 10, 30, 50);
			break;

			case "light_breeze": //������ ����
				Whr.Sea2.Amp1 = 1.25;//��������� 1 �����
				Whr.Sea2.AnimSpeed1 = 2.0; //�������� ��������
				Whr.Sea2.Scale1 = 1.5; //������� �����
				Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 2.0"; //�������� ��������

				Whr.Sea2.Amp2 = 0.85;
				Whr.Sea2.AnimSpeed2 = 3.0;
				Whr.Sea2.Scale2 = 3.0;
				Whr.Sea2.MoveSpeed2 = "-2.0, 0.0, 0.0";

				Whr.Sea2.BumpScale = 0.075; //������ �����
				Whr.Sea2.PosShift = 1.4;//��������������� ����

				Whr.Sea2.FoamK = 0.5;//������� ���� �� ������ 0.1 - ���� ����� � 10 ������ 1.0 ����� ���� ����� ������
				Whr.Sea2.FoamV = 1.1;////������ � ������� ���������� ����
				Whr.Sea2.FoamUV = 1.0; //������� ����
				Whr.Sea2.FoamTexDisturb = 0.7;//����� �� �������. �.�. ��� ��� ���� �������. �������� �� 0.0 �� 1.0

				Whr.Sea2.Reflection = 0.8;//0.8;
				Whr.Sea2.Transparency = 0.6;//0.6;
				Whr.Sea2.Frenel = 0.3;//0.6; 
				Whr.Sea2.Attenuation = 0.3;//0.2;
				Whr.Sea2.WaterColor = argb(0, 10, 30, 50);
			break;

			case "breeze":	//����
				Whr.Sea2.Amp1 = 2.5;//��������� 1 �����
				Whr.Sea2.AnimSpeed1 = 3.0; //�������� ��������
				Whr.Sea2.Scale1 = 1.0; //������� �����
				Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 2.5"; //�������� ��������

				Whr.Sea2.Amp2 = 2.0;
				Whr.Sea2.AnimSpeed2 = 8.0;
				Whr.Sea2.Scale2 = 2.0;
				Whr.Sea2.MoveSpeed2 = "-2.5, 0.0, 0.0";

				Whr.Sea2.BumpScale = 0.075; //������ �����
				Whr.Sea2.PosShift = 1.1;//��������������� ����

				Whr.Sea2.FoamK = 0.35;//������� ���� �� ������ 0.1 - ���� ����� � 10 ������ 1.0 ����� ���� ����� ������
				Whr.Sea2.FoamV = 2.3;//������ � ������� ���������� ����
				Whr.Sea2.FoamUV = 1.0; //������� ����
				Whr.Sea2.FoamTexDisturb = 0.7;//����� �� �������. �.�. ��� ��� ���� �������. �������� �� 0.0 �� 1.0

				Whr.Sea2.Reflection = 0.8;//0.8;
				Whr.Sea2.Transparency = 0.6;//0.6;
				Whr.Sea2.Frenel = 0.3;//0.6; 
				Whr.Sea2.Attenuation = 0.3;//0.2;
				Whr.Sea2.WaterColor = argb(0, 10, 30, 50);
			break;

			case "moderate_breeze":	//����
				Whr.Sea2.Amp1 = 4.0; //��������� 1 �����
				Whr.Sea2.AnimSpeed1 = 2.5; //�������� ��������
				Whr.Sea2.Scale1 = 0.35; //������� �����
				Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 2.0"; //�������� ��������

				Whr.Sea2.Amp2 = 1.75;
				Whr.Sea2.AnimSpeed2 = 3.5;
				Whr.Sea2.Scale2 = 2.15;
				Whr.Sea2.MoveSpeed2 = "2.0, 0.0, 0.0";

				Whr.Sea2.BumpScale = 0.075; //������ �����
				Whr.Sea2.PosShift = 0.95; //��������������� ����

				Whr.Sea2.FoamK = 0.3;//������� ���� �� ������ 0.1 - ���� ����� � 10 ������ 1.0 ����� ���� ����� ������
				Whr.Sea2.FoamV = 3.1;//������ � ������� ���������� ����
				Whr.Sea2.FoamUV = 1.0; //������� ����
				Whr.Sea2.FoamTexDisturb = 0.7;//����� �� �������. �.�. ��� ��� ���� �������. �������� �� 0.0 �� 1.0

				Whr.Sea2.Reflection = 0.8;//0.8;
				Whr.Sea2.Transparency = 0.6;//0.6;
				Whr.Sea2.Frenel = 0.3;//0.6; 
				Whr.Sea2.Attenuation = 0.3;//0.2;
				Whr.Sea2.WaterColor = argb(0, 10, 30, 50);
			break;

			case "strong_breeze"://�������
				Whr.Sea2.Amp1 = 6.0; //��������� 1 �����
				Whr.Sea2.AnimSpeed1 = 3.0; //�������� ��������
				Whr.Sea2.Scale1 = 0.3; //������� �����
				Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 3.0"; //�������� ��������

				Whr.Sea2.Amp2 = 1.5;
				Whr.Sea2.AnimSpeed2 = 6.0;
				Whr.Sea2.Scale2 = 2.5;
				Whr.Sea2.MoveSpeed2 = "-3.0, 0.0, 0.0";

				Whr.Sea2.BumpScale = 0.075; //������ �����
				Whr.Sea2.PosShift = 0.8; //��������������� ����

				Whr.Sea2.FoamK = 0.25;//������� ���� �� ������ 0.1 - ���� ����� � 10 ������ 1.0 ����� ���� ����� ������
				Whr.Sea2.FoamV = 4.2;//������ � ������� ���������� ����
				Whr.Sea2.FoamUV = 1.0; //������� ����
				Whr.Sea2.FoamTexDisturb = 0.7;//����� �� �������. �.�. ��� ��� ���� �������. �������� �� 0.0 �� 1.0

				Whr.Sea2.Reflection = 0.8;//0.8;
				Whr.Sea2.Transparency = 0.6;//0.6;
				Whr.Sea2.Frenel = 0.3;//0.6; 
				Whr.Sea2.Attenuation = 0.3;//0.2;
				Whr.Sea2.WaterColor = argb(0, 10, 30, 50);
			break;

			case "storm"://�����
				Whr.Sea2.Amp1 = 37.0; //��������� 1 �����
				Whr.Sea2.AnimSpeed1 = 2.0; //�������� ��������
				Whr.Sea2.Scale1 = 0.11; //������� �����
				Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 10.0"; //�������� ��������

				Whr.Sea2.Amp2 = 2.0;
				Whr.Sea2.AnimSpeed2 = 4.0;
				Whr.Sea2.Scale2 = 2.0;
				Whr.Sea2.MoveSpeed2 = "-4.0, 0.0, 0.0";

				Whr.Sea2.BumpScale = 0.05; //������ �����
				Whr.Sea2.PosShift = 1.25; //��������������� ����

				Whr.Sea2.FoamK = 0.05;//������� ���� �� ������ 0.1 - ���� ����� � 10 ������ 1.0 ����� ���� ����� ������
				Whr.Sea2.FoamV = 20.0;//������ � ������� ���������� ����
				Whr.Sea2.FoamUV = 0.75; //������� ����
				Whr.Sea2.FoamTexDisturb = 0.7;//����� �� �������. �.�. ��� ��� ���� �������. �������� �� 0.0 �� 1.0

				Whr.Sea2.Reflection = 0.4;
				Whr.Sea2.Transparency = 0.2;
				Whr.Sea2.Frenel = 0.4;
				Whr.Sea2.Attenuation = 0.3;
				Whr.Sea2.WaterColor = argb(0, 65, 80, 85);
			break;
	}
	Log_TestInfo("WhrSetSeaPreset: ������ ������ " + sPreset);
}

