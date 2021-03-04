// -------------------------------------------------------------
// Mett: настройки мор€
// заготовки на разные типы волнени€:
// штиль, легкий бриз, бриз, умеренный бриз, сильный бриз, шторм
// -------------------------------------------------------------

object PSea;	//объект дл€ хранени€ настроек пресетов

//выбераем нужный пресет от силы ветра в море
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

//настройки пресетов
void WhrSetSeaPreset(string sPreset)
{
	string sMoveSpeed1, sMoveSpeed2
	float fAmp1, fAnimSpeed1, fScale1;
	float fAmp2, fAnimSpeed2, fScale2;
	float fBumpScale, fPosShift;
	float fFoamK, fFoamV, fFoamUV, fFoamTexDisturb;
	float fReflection, fTransparency, fFrenel, fAttenuation;
	int iWaterColor;
	int iSkyColor = argb(0, 255, 255, 255);

	switch(sPreset)
	{
		case "calm": //штиль
			fAmp1 = 1.0;
			fAnimSpeed1 = 1.0;
			fScale1 = 1.5;
			sMoveSpeed1 = "0.0, 0.0, 1.5";

			fAmp2 = 0.7;
			fAnimSpeed2 = 2.0;
			fScale2 = 2.0;
			sMoveSpeed2 = "-1.5, 0.0, 0.0";

			fBumpScale = 0.075; 
			fPosShift = 2.0;

			fFoamK = 0.5;
			fFoamV = 0.9;
			fFoamUV = 1.0;
			fFoamTexDisturb = 0.7;

			fReflection = 0.8;
			fTransparency = 0.6;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			iWaterColor = argb(0, 10, 30, 50);
		break;

		case "light_breeze": //легкий бриз
			fAmp1 = 1.25;
			fAnimSpeed1 = 2.0; 
			fScale1 = 1.5; 
			sMoveSpeed1 = "0.0, 0.0, 2.0"; 

			fAmp2 = 0.85;
			fAnimSpeed2 = 3.0;
			fScale2 = 3.0;
			sMoveSpeed2 = "-2.0, 0.0, 0.0";

			fBumpScale = 0.075; 
			fPosShift = 1.4;

			fFoamK = 0.5;
			fFoamV = 1.1;
			fFoamUV = 1.0;
			fFoamTexDisturb = 0.7;

			fReflection = 0.8;
			fTransparency = 0.6;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			iWaterColor = argb(0, 10, 30, 50);
		break;

		case "breeze":	//бриз
			fAmp1 = 2.5;
			fAnimSpeed1 = 3.0;
			fScale1 = 1.0;
			sMoveSpeed1 = "0.0, 0.0, 2.5";

			fAmp2 = 2.0;
			fAnimSpeed2 = 8.0;
			fScale2 = 2.0;
			sMoveSpeed2 = "-2.5, 0.0, 0.0";

			fBumpScale = 0.075;
			fPosShift = 1.1;

			fFoamK = 0.35;
			fFoamV = 2.3;
			fFoamUV = 1.0;
			fFoamTexDisturb = 0.7;

			fReflection = 0.8;
			fTransparency = 0.6;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			iWaterColor = argb(0, 10, 30, 50);
		break;

		case "moderate_breeze":	//бриз
			fAmp1 = 4.0;
			fAnimSpeed1 = 2.5;
			fScale1 = 0.35;
			sMoveSpeed1 = "0.0, 0.0, 2.0";

			fAmp2 = 1.75;
			fAnimSpeed2 = 3.5;
			fScale2 = 2.15;
			sMoveSpeed2 = "2.0, 0.0, 0.0";

			fBumpScale = 0.075;
			fPosShift = 0.95;

			fFoamK = 0.3;
			fFoamV = 3.1;
			fFoamUV = 1.0;
			fFoamTexDisturb = 0.7;

			fReflection = 0.8;
			fTransparency = 0.6;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			iWaterColor = argb(0, 10, 30, 50);
		break;

		case "strong_breeze"://ветрено
			fAmp1 = 6.0;
			fAnimSpeed1 = 3.0;
			fScale1 = 0.3;
			sMoveSpeed1 = "0.0, 0.0, 3.0";

			fAmp2 = 1.5;
			fAnimSpeed2 = 6.0;
			fScale2 = 2.5;
			sMoveSpeed2 = "-3.0, 0.0, 0.0";

			fBumpScale = 0.075;
			fPosShift = 0.8;

			fFoamK = 0.25;
			fFoamV = 4.2;
			fFoamUV = 1.0;
			fFoamTexDisturb = 0.7;

			fReflection = 0.8;
			fTransparency = 0.6;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			iWaterColor = argb(0, 10, 30, 50);
		break;

		case "storm"://шторм
			fAmp1 = 37.0;
			fAnimSpeed1 = 2.0;
			fScale1 = 0.11;
			sMoveSpeed1 = "0.0, 0.0, 10.0";

			fAmp2 = 2.0;
			fAnimSpeed2 = 4.0;
			fScale2 = 2.0;
			sMoveSpeed2 = "-4.0, 0.0, 0.0";

			fBumpScale = 0.05;
			fPosShift = 1.25;

			fFoamK = 0.05;
			fFoamV = 23.0;
			fFoamUV = 0.5;
			fFoamTexDisturb = 0.7;

			fReflection = 0.4;
			fTransparency = 0.2;
			fFrenel = 0.4;
			fAttenuation = 0.3;
			iWaterColor = argb(0, 65, 80, 85);
		break;
	}

	DeleteAttribute(PSea, "");				//чистим объект перед записью данных

	PSea.Amp1 = fAmp1;						//амплитуда 1 волны
	PSea.AnimSpeed1 = fAnimSpeed1; 			//скорость анимации
	PSea.Scale1 = fScale1;					//размеры волны
	PSea.MoveSpeed1 = sMoveSpeed1;			//скорость движени€

	PSea.Amp2 = fAmp2;						//амплитуда 2 волны
	PSea.AnimSpeed2 = fAnimSpeed2;			//скорость анимации
	PSea.Scale2 = fScale2;					//размеры волны
	PSea.MoveSpeed2 = sMoveSpeed2;			//скорость движени€

	PSea.BumpScale = fBumpScale;			//ћ≈Ћ »≈ ¬ќЋЌџ
	PSea.PosShift = fPosShift;				//остроконечность волн

	PSea.FoamK = fFoamK;					//€ркость пены по высоте 0.1 - пена €рка€ с 10 метров 1.0 через метр после начала
	PSea.FoamV = fFoamV;					//высота с которой начинаетс€ пена
	PSea.FoamUV = fFoamUV;					//тайлинг пены
	PSea.FoamTexDisturb = fFoamTexDisturb;	//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

	/* PSea.Reflection = fReflection;
	PSea.Transparency = fTransparency;
	PSea.Frenel = fFrenel;
	PSea.Attenuation = fAttenuation;
	PSea.WaterColor = iWaterColor;
	PSea.SkyColor = iSkyColor; */

	PSea.Reflection = fReflection;
	PSea.Transparency = fTransparency;
	PSea.Frenel = fFrenel;
	PSea.Attenuation = fAttenuation;
	PSea.WaterColor = iWaterColor;
	PSea.SkyColor = iSkyColor;

	Log_TestInfo("WhrSetSeaPreset: выбран пресет " + sPreset);
}

//записываем значени€ из PSea в море Sea.Sea2
void WhrSetNewSea(float fWind)
{
	string sPreset = WhrGetSeaPresetFromWind(fWind);

	Log_TestInfo("sPreset " + sPreset);

	WhrSetSeaPreset(sPreset);

	Sea.Sea2.Amp1 = Whr_GetFloat(PSea, "Amp1");
	Sea.Sea2.AnimSpeed1 = Whr_GetFloat(PSea, "AnimSpeed1");
	Sea.Sea2.Scale1 = Whr_GetFloat(PSea, "Scale1");
	Sea.Sea2.MoveSpeed1 = Whr_GetString(PSea, "MoveSpeed1");

	Sea.Sea2.Amp2 = Whr_GetFloat(PSea, "Amp2");
	Sea.Sea2.AnimSpeed2 = Whr_GetFloat(PSea, "AnimSpeed2");
	Sea.Sea2.Scale2 = Whr_GetFloat(PSea, "Scale2");
	Sea.Sea2.MoveSpeed2 = Whr_GetString(PSea, "MoveSpeed2");

	Sea.Sea2.BumpScale = Whr_GetFloat(PSea, "BumpScale");
	Sea.Sea2.PosShift = Whr_GetFloat(PSea, "PosShift");
	
	Sea.Sea2.FoamK = Whr_GetFloat(PSea, "FoamK");
	Sea.Sea2.FoamV = Whr_GetFloat(PSea, "FoamV");
	Sea.Sea2.FoamUV = Whr_GetFloat(PSea, "FoamUV");
	Sea.Sea2.FoamTexDisturb = Whr_GetFloat(PSea, "FoamTexDisturb");

	Sea.Sea2.Reflection = Whr_GetFloat(PSea, "Reflection");
	Sea.Sea2.Transparency = Whr_GetFloat(PSea, "Transparency");
	Sea.Sea2.Frenel = Whr_GetFloat(PSea, "Frenel");
	Sea.Sea2.Attenuation = Whr_GetFloat(PSea, "Attenuation");
	Sea.Sea2.WaterColor = Whr_GetColor(PSea, "WaterColor");	

	Sea.Sea2.SkyColor = Whr_GetColor(PSea, "SkyColor");
}
