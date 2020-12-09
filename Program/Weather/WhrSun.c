object SunGlow;

void WhrDeleteSunGlowEnvironment()
{
	if (isEntity(&SunGlow))
	{
		DeleteClass(&SunGlow);
	}
	DeleteAttribute(&SunGlow,"");
}

void WhrCreateSunGlowEnvironment()
{
	//if (sti(aSun.Glow.Enable) == false && sti(aSun.Flare.Enable) == false)) return;

	// create sunglow
	if (!isEntity(&SunGlow))
	{
		CreateEntity(&SunGlow,"SunGlow");
		LayerAddObject("sea_sunroad",&SunGlow,-1);
	}
	WhrFillSunGlowData(iCurWeatherNum, iBlendWeatherNum);
	SunGlow.isDone = true;
}

void WhrFillSunGlowData(int nw1, int nw2)
{
	if( nw1<0 || nw1>=MAX_WEATHERS ) {return;}

	SunGlow.Clear = "";
	DeleteAttribute(&SunGlow,"");

	aref aSun1;			makearef(aSun1, Weathers[nw1].Sun);
	aref aGlow1;		makearef(aGlow1, aSun1.Glow);
	aref aFlare1;		makearef(aFlare1, aSun1.Flare);
	aref aOverflow1;	makearef(aOverflow1, aSun1.Overflow);
	aref aReflection1;	makearef(aReflection1, aSun1.Reflection);

	aref aFlares,aFlareN;
	int iNumFlares, i;
	string sTemp;

	if( nw2<0 )
	{
		if (sunIsShine)
		{
			if (sti(aSun1.Glow.Enable) != false)
			{
				SunGlow.Glow.Dist = Whr_GetFloat(aGlow1,"Dist");
				SunGlow.Glow.Size = Whr_GetFloat(aGlow1,"Size");
				SunGlow.Glow.Texture = Whr_GetString(aGlow1,"Texture");
				SunGlow.Glow.Color = Whr_GetColor(aGlow1,"Color");
				SunGlow.Glow.RotateSpeed = Whr_GetColor(aGlow1,"RotateSpeed");
				SunGlow.Glow.DecayTime = Whr_GetColor(aGlow1,"DecayTime");
				SunGlow.Glow.TechniqueZ = Whr_GetString(aGlow1,"TechniqueZ");
				SunGlow.Glow.TechniqueNoZ = Whr_GetString(aGlow1,"TechniqueNoZ");
			}

			if (sti(aSun1.Flare.Enable) != false)
			{
				SunGlow.Flare.Dist = Whr_GetFloat(aFlare1,"Dist");
				SunGlow.Flare.Technique = Whr_GetString(aFlare1,"Technique");
				SunGlow.Flare.Scale = Whr_GetFloat(aFlare1,"Scale");
				SunGlow.Flare.Texture = Whr_GetString(aFlare1,"Texture");
				SunGlow.Flare.TexSizeX = Whr_GetString(aFlare1,"TexSizeX");
				SunGlow.Flare.TexSizeY = Whr_GetString(aFlare1,"TexSizeY");

				makearef(aFlares,aSun1.Flares);
				iNumFlares = GetAttributesNum(aFlares);
				for (i=0;i<iNumFlares;i++)
				{
					aFlareN = GetAttributeN(aFlares,i);
					sTemp = "f" + i;
					SunGlow.Flares.(sTemp) = GetAttributeValue(aFlareN);
				}
			}

			if (sti(aSun1.Overflow.Enable) != false)
			{
				SunGlow.Overflow.Texture = Whr_GetString(aOverflow1,"Texture");
				SunGlow.Overflow.Technique = Whr_GetString(aOverflow1,"Technique");
				SunGlow.Overflow.Size = Whr_GetFloat(aOverflow1,"Size");
				SunGlow.Overflow.Color = Whr_GetColor(aOverflow1,"Color");
				SunGlow.Overflow.Start = Whr_GetFloat(aOverflow1,"Start");
			}

			if (sti(aSun1.Reflection.Enable) != false)
			{
				SunGlow.Reflection.Texture = Whr_GetString(aReflection1, "Texture");
				SunGlow.Reflection.Technique = Whr_GetString(aReflection1, "Technique");
				SunGlow.Reflection.Size = Whr_GetFloat(aReflection1, "Size");
				SunGlow.Reflection.Dist = Whr_GetFloat(aReflection1, "Dist");
				SunGlow.Reflection.Color = Whr_GetColor(aReflection1, "Color");
			}

			SunGlow.Moon = aSun1.Moon;
		}
	}
	else
	{	
		if (sti(aSun1.Glow.Enable) != false)
		{
			SunGlow.Glow.Dist = Whr_GetFloat(aGlow1,"Dist");
			SunGlow.Glow.Size = Whr_GetFloat(aGlow1,"Size");
			SunGlow.Glow.Texture = Whr_GetString(aGlow1,"Texture");
			SunGlow.Glow.Color = Whr_GetColor(aGlow1,"Color");
			SunGlow.Glow.RotateSpeed = Whr_GetColor(aGlow1,"RotateSpeed");
			SunGlow.Glow.DecayTime = Whr_GetColor(aGlow1,"DecayTime");
			SunGlow.Glow.TechniqueZ = Whr_GetString(aGlow1,"TechniqueZ");
			SunGlow.Glow.TechniqueNoZ = Whr_GetString(aGlow1,"TechniqueNoZ");
		}

		if (sti(aSun1.Flare.Enable) != false)
		{
			SunGlow.Flare.Dist = Whr_GetFloat(aFlare1,"Dist");
			SunGlow.Flare.Technique = Whr_GetString(aFlare1,"Technique");
			SunGlow.Flare.Scale = Whr_GetFloat(aFlare1,"Scale");
			SunGlow.Flare.Texture = Whr_GetString(aFlare1,"Texture");
			SunGlow.Flare.TexSizeX = Whr_GetString(aFlare1,"TexSizeX");
			SunGlow.Flare.TexSizeY = Whr_GetString(aFlare1,"TexSizeY");

			makearef(aFlares,aSun1.Flares);
			iNumFlares = GetAttributesNum(aFlares);
			for (i=0;i<iNumFlares;i++)
			{
				aFlareN = GetAttributeN(aFlares,i);
				sTemp = "f" + i;
				SunGlow.Flares.(sTemp) = GetAttributeValue(aFlareN);
			}
		}

		if (sti(aSun1.Overflow.Enable) != false)
		{
			SunGlow.Overflow.Texture = Whr_GetString(aOverflow1,"Texture");
			SunGlow.Overflow.Technique = Whr_GetString(aOverflow1,"Technique");
			SunGlow.Overflow.Size = Whr_GetFloat(aOverflow1,"Size");
			SunGlow.Overflow.Color = Whr_GetColor(aOverflow1,"Color");
			SunGlow.Overflow.Start = Whr_GetFloat(aOverflow1,"Start");
		}

		if (sti(aSun1.Reflection.Enable) != false)
		{
			SunGlow.Reflection.Texture = Whr_GetString(aReflection1, "Texture");
			SunGlow.Reflection.Technique = Whr_GetString(aReflection1, "Technique");
			SunGlow.Reflection.Size = Whr_GetFloat(aReflection1, "Size");
			SunGlow.Reflection.Dist = Whr_GetFloat(aReflection1, "Dist");
			SunGlow.Reflection.Color = Whr_GetColor(aReflection1, "Color");
		}

		SunGlow.Moon = aSun1.Moon;
	}

	if( stf(Environment.Time) < 4.5 || stf(Environment.Time) > 23.5 ) {
		SunGlow.Moon = true;
		SunGlow.Reflection.Texture = "weather\sun\reflection\refl_night.tga.tx";
	} else {
		SunGlow.Moon = false;
	}

	if( nw2 >= 0)
	{
		SunGlow.Glow.SunTexture = "weather\sun\glow\sun.tga.tx";
		SunGlow.Glow.GlowTexture = "weather\sun\glow\sunglow.tga.tx";
		
		if (stf(Environment.date.day) > 0 && stf(Environment.date.day) < 4) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon00.tga.tx";
		if (stf(Environment.date.day) > 3 && stf(Environment.date.day) < 8) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon01.tga.tx";
		if (stf(Environment.date.day) > 7 && stf(Environment.date.day) < 12) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon02.tga.tx";
		if (stf(Environment.date.day) > 11 && stf(Environment.date.day) < 16) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon03.tga.tx";
		if (stf(Environment.date.day) > 15 && stf(Environment.date.day) < 20) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon04.tga.tx";
		if (stf(Environment.date.day) > 19 && stf(Environment.date.day) < 24) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon05.tga.tx";
		if (stf(Environment.date.day) > 23 && stf(Environment.date.day) < 28) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon06.tga.tx";
		if (stf(Environment.date.day) > 27 && stf(Environment.date.day) < 32) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon07.tga.tx";
		SunGlow.Glow.SunSize = 400;
		SunGlow.Glow.MoonSize = 110;
		SunGlow.Glow.Color = argb(0,255,255,255);
	}
	else
	{
		if (sunIsShine)
		{
			SunGlow.Glow.SunTexture = "weather\sun\glow\sun.tga.tx";
			SunGlow.Glow.GlowTexture = "weather\sun\glow\sunglow.tga.tx";

			if (stf(Environment.date.day) > 0 && stf(Environment.date.day) < 4) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon00.tga.tx";
			if (stf(Environment.date.day) > 3 && stf(Environment.date.day) < 8) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon01.tga.tx";
			if (stf(Environment.date.day) > 7 && stf(Environment.date.day) < 12) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon02.tga.tx";
			if (stf(Environment.date.day) > 11 && stf(Environment.date.day) < 16) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon03.tga.tx";
			if (stf(Environment.date.day) > 15 && stf(Environment.date.day) < 20) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon04.tga.tx";
			if (stf(Environment.date.day) > 19 && stf(Environment.date.day) < 24) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon05.tga.tx";
			if (stf(Environment.date.day) > 23 && stf(Environment.date.day) < 28) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon06.tga.tx";
			if (stf(Environment.date.day) > 27 && stf(Environment.date.day) < 32) SunGlow.Glow.MoonTexture = "weather\sun\glow\moon07.tga.tx";

			SunGlow.Glow.SunSize = 400;
			SunGlow.Glow.MoonSize = 110;
			SunGlow.Glow.Color = argb(0,255,255,255);
		}
	}
}

void MoveSunGlowToLayers(string sExecuteLayer, string sRealizeLayer)
{
	LayerDelObject("execute",&SunGlow);
	LayerDelObject("realize",&SunGlow);
	LayerDelObject(SEA_EXECUTE,&SunGlow);
	LayerDelObject(SEA_REALIZE,&SunGlow);

	LayerAddObject(sExecuteLayer, &SunGlow, -2);
	LayerAddObject(sRealizeLayer, &SunGlow, -2);
}