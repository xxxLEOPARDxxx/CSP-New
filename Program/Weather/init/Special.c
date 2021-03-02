int Whr_InitSpecial(int n)
{
// ====================================================================

	Weathers[n].id = "Inside";

	Weathers[n].Hour.Min = 0;
	Weathers[n].Hour.Max = 24;

	Weathers[n].Lighting = "inside";
	Weathers[n].LightingLm = "inside";

	Weathers[n].InsideBack = "";

	Weathers[n].Skip = true;
	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = false;
	Weathers[n].Lights = false;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "resource\textures\weather\lightning\lightning.tga";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1; 
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "resource\textures\weather\skies\10\\";
	Weathers[n].Sky.Color = argb(0,64,64,64);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 512;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Stars.Enable = false;
	Weathers[n].Stars.Texture = "resource\textures\weather\astronomy\stars.tga";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 25.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = false;
	Weathers[n].Fog.Height = 100;
	Weathers[n].Fog.Start = 0.0;
	Weathers[n].Fog.Density = 0.001;			
	Weathers[n].Fog.IslandDensity = 0.001;		
	Weathers[n].Fog.SeaDensity = 0.001;		
	Weathers[n].Fog.Color = argb(0,200,220,255);

	Weathers[n].Rain.NumDrops = 0;													
	Weathers[n].Rain.Color = argb(0,23,23,23);
	Weathers[n].Rain.DropLength = 2.9;												
	Weathers[n].Rain.Height = 50.0;												
	Weathers[n].Rain.Radius = 50.0;												
	Weathers[n].Rain.Speed = 18;														
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;						
	Weathers[n].Rain.DropsFarNum = 500;						
	Weathers[n].Rain.DropsNearRadius = 75.0;					
	Weathers[n].Rain.DropsFarRadius = 55.0;						
	Weathers[n].Rain.DropsLifeTime = 0.25;						
	Weathers[n].Rain.DropsSize = 0.06;							
	Weathers[n].Rain.DropsTexture = "resource\textures\weather\rain_drops.tga";
	Weathers[n].Rain.DropsColor = argb(56, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "resource\textures\weather\rainbow\rainbow.tga";

	Weathers[n].Sun.Color = argb(0,80,80,68);
	Weathers[n].Sun.Ambient = argb(0,40,30,20);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(3.0);
	Weathers[n].Sun.HeightAngle = 0.36;

	Weathers[n].Sun.Glow.Enable = false;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "resource\textures\weather\sun\glow\sun.tga";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,54,54,54);

	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "resource\textures\weather\lightning\flash.tga";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "resource\textures\weather\sun\reflection\refl_evening.tga";
	Weathers[n].Sun.Reflection.Technique = "sunglow_z";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(0,54,54,54);

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "resource\textures\weather\sun\reflection\refl_evening.tga";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(54,54,54,54);

	Weathers[n].Sun.Flare.Enable = true;
	Weathers[n].Sun.Flare.Texture = "resource\textures\weather\sun\flare\allflares.tga";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,30,55,100);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.06;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 23.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "resource\textures\weather\sea\bump_g2mx\\";

	Weathers[n].Sea.Transparency = 0.4;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;

	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,30,55,100);
	Weathers[n].Sea.Pena.Color = argb(0,175,175,155);

	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\\";
	Weathers[n].Sea.Bump.Tile = 0.1;
	Weathers[n].Sea.Bump.Ang = 15.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 9.0;
	Weathers[n].Sea.Bump.Scale = 0.1;

	Weathers[n].Sea.SunRoad.Start = 0.99	;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,128,55,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,200,150);
	Weathers[n].Sea.SunRoad.Power = 0.2;

	Weathers[n].Sea.Harmonics.h1 = "0.0,  10.0,  0.1802, 0.0,  -78.00";
	Weathers[n].Sea.Harmonics.h2 = "1.87, 12.0,  0.202,  0.0,   78.00";
	Weathers[n].Sea.Harmonics.h3 = "0.27,  7.0,  0.2002, 0.0,   78.00";
	
	Weathers[n].Sea2.Harmonics.h1 = "0.0,  10.0,  0.1802, 0.0,  -78.00";
	Weathers[n].Sea2.Harmonics.h2 = "1.87, 12.0,  0.202,  0.0,   78.00";
	Weathers[n].Sea2.Harmonics.h3 = "0.27,  7.0,  0.2002, 0.0,   78.00";
//---------------------------------------------------------------------
	Weathers[n].Sea.Harmonics.h1  =" 0.0,  40.0, 0.8, 80.87, -48.00";
	Weathers[n].Sea.Harmonics.h2  = "0.57, 22.0, 0.4, 82.28,  48.00";
	Weathers[n].Sea.Harmonics.h3  = "1.57, 27.0, 0.9, 82.28,  48.00";
	Weathers[n].Sea.Harmonics.h4  = "1.0,  17.0, 0.4, 82.28,  48.00";
	Weathers[n].Sea.Harmonics.h5  = "3.27,  7.0, 0.4, 82.28,  48.00";
	
	Weathers[n].Sea2.Harmonics.h1  =" 0.0,  40.0, 0.8, 80.87, -48.00";
	Weathers[n].Sea2.Harmonics.h2  = "0.57, 22.0, 0.4, 82.28,  48.00";
	Weathers[n].Sea2.Harmonics.h3  = "1.57, 27.0, 0.9, 82.28,  48.00";
	Weathers[n].Sea2.Harmonics.h4  = "1.0,  17.0, 0.4, 82.28,  48.00";
	Weathers[n].Sea2.Harmonics.h5  = "3.27,  7.0, 0.4, 82.28,  48.00";

	Weathers[n].Sea.Harmonics.h1  = "0.00, 10.0, 1.2, 80.87, -68.00";
	Weathers[n].Sea.Harmonics.h2  = "1.57, 10.0, 2.1, 82.28,  88.00";
	Weathers[n].Sea.Harmonics.h3  = "0.47,  7.0, 2.2, 82.28,  68.00";
	Weathers[n].Sea.Harmonics.h4  = "0.27, 47.0, 0.5, 82.28, 288.00";
	Weathers[n].Sea.Harmonics.h5  = "1.27, 57.0, 0.7, 82.28, 188.00";
	Weathers[n].Sea.Harmonics.h6  = "2.27, 57.0, 0.3, 82.28,  88.00";
	Weathers[n].Sea.Harmonics.h7  = "2.27, 37.0, 1.2, 82.28, 188.00";
	Weathers[n].Sea.Harmonics.h8  = "2.77, 17.0, 0.5, 82.28, 288.00";
	Weathers[n].Sea.Harmonics.h9  = "1.77, 17.0, 0.1, 82.28, 188.00";
	Weathers[n].Sea.Harmonics.h10 = " 1.0, 14.0, 0.5, 82.28,  28.00";

	Weathers[n].Sea2.Harmonics.h1  = "0.00, 10.0, 1.2, 80.87, -68.00";
	Weathers[n].Sea2.Harmonics.h2  = "1.57, 10.0, 2.1, 82.28,  88.00";
	Weathers[n].Sea2.Harmonics.h3  = "0.47,  7.0, 2.2, 82.28,  68.00";
	Weathers[n].Sea2.Harmonics.h4  = "0.27, 47.0, 0.5, 82.28, 288.00";
	Weathers[n].Sea2.Harmonics.h5  = "1.27, 57.0, 0.7, 82.28, 188.00";
	Weathers[n].Sea2.Harmonics.h6  = "2.27, 57.0, 0.3, 82.28,  88.00";
	Weathers[n].Sea2.Harmonics.h7  = "2.27, 37.0, 1.2, 82.28, 188.00";
	Weathers[n].Sea2.Harmonics.h8  = "2.77, 17.0, 0.5, 82.28, 288.00";
	Weathers[n].Sea2.Harmonics.h9  = "1.77, 17.0, 0.1, 82.28, 188.00";
	Weathers[n].Sea2.Harmonics.h10 = " 1.0, 14.0, 0.5, 82.28,  28.00";

	Weathers[n].Sea2.BumpScale = 0.09;
	Weathers[n].Sea2.PosShift = 1.25;

	Weathers[n].Sea2.WaterColor = argb(0, 10, 55, 100);
	Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.Reflection = 0.7;
	Weathers[n].Sea2.Transparency = 0.9;
	Weathers[n].Sea2.Frenel = 0.3;
	Weathers[n].Sea2.Attenuation = 0.3;

	Weathers[n].Sea2.Amp1 = 2.75;
	Weathers[n].Sea2.AnimSpeed1 = 2.0;
	Weathers[n].Sea2.Scale1 = 0.15;
	Weathers[n].Sea2.MoveSpeed1 = "2.0, 0.0, 0.0";

	Weathers[n].Sea2.Amp2 = 0.75;
	Weathers[n].Sea2.AnimSpeed2 = 4.0;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "-2.5, 0.0, 0.0";

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 5.0;
	Weathers[n].Wind.Speed.Max = 8.0;

	n++;

	// ====================================================================

	Weathers[n].id = "Underwater";
	Weathers[n].Hour.Min = 0;
	Weathers[n].Hour.Max = 24;

	Weathers[n].Lighting = "morning10";
	Weathers[n].LightingLm = "morning";

	Weathers[n].InsideBack = "m";

	Weathers[n].Skip = true;

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = false;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "resource\textures\weather\lightning\lightning.tga";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1; 
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "resource\textures\weather\skies\10\\";
	Weathers[n].Sky.Color = argb(0,64,64,64);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 512;
	Weathers[n].Sky.Angle = 0.0;

	Weathers[n].Planets.enable = false;

	Weathers[n].Stars.Enable = false;
	Weathers[n].Stars.Texture = "resource\textures\weather\astronomy\stars.tga";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 25.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 200;
	Weathers[n].Fog.Start = 10;
	Weathers[n].Fog.Density = 0.004;			
	Weathers[n].Fog.IslandDensity = 0.002;		
	Weathers[n].Fog.SeaDensity = 0.003;		
	Weathers[n].Fog.Color = argb(0,26,64,59);
	
	Weathers[n].Rain.NumDrops = 0;													
	Weathers[n].Rain.Color = argb(0,23,23,23);
	Weathers[n].Rain.DropLength = 2.9;												
	Weathers[n].Rain.Height = 50.0;												
	Weathers[n].Rain.Radius = 50.0;												
	Weathers[n].Rain.Speed = 18;														
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;										
	Weathers[n].Rain.DropsFarNum = 500;										
	Weathers[n].Rain.DropsNearRadius = 75.0;									
	Weathers[n].Rain.DropsFarRadius = 55.0;										
	Weathers[n].Rain.DropsLifeTime = 0.25;										
	Weathers[n].Rain.DropsSize = 0.06;											
	Weathers[n].Rain.DropsTexture = "resource\textures\weather\rain_drops.tga";
	Weathers[n].Rain.DropsColor = argb(56, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "resource\textures\weather\rainbow\rainbow.tga";

	Weathers[n].Sun.Color = argb(0,10,40,43);
	Weathers[n].Sun.Ambient = argb(0,134,199,209);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(160.0);
	Weathers[n].Sun.HeightAngle = 0.45;

	Weathers[n].Sun.Glow.Enable = false;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "resource\textures\weather\sun\glow\sun.tga";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,54,54,54);

	Weathers[n].Sun.Overflow.Enable = false;
	Weathers[n].Sun.Overflow.Texture = "resource\textures\weather\lightning\flash.tga";
	Weathers[n].Sun.Overflow.Color = argb(0, 100, 100, 100);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "resource\textures\weather\sun\reflection\refl_evening.tga";
	Weathers[n].Sun.Reflection.Technique = "sunglow_z";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(0,54,54,54);

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "resource\textures\weather\sun\reflection\refl_evening.tga";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(54,54,54,54);

	Weathers[n].Sun.Flare.Enable = false;
	Weathers[n].Sun.Flare.Texture = "resource\textures\weather\sun\flare\allflares.tga";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,5,10);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "resource\textures\weather\sea\bump_g2mx\\";

	Weathers[n].Sea.Transparency = 0.2;
	Weathers[n].Sea.FrenelCoefficient = 0.2;
	Weathers[n].Sea.WaterReflection = 0.9;
	Weathers[n].Sea.WaterAttenuation = 0.1;

	Weathers[n].Sea.Sky.Color = argb(0,250,160,140);
	Weathers[n].Sea.Water.Color = argb(0,50,95,75);
	Weathers[n].Sea.Pena.Color = argb(0,175,175,155);

	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\\";
	Weathers[n].Sea.Bump.Tile = 0.1;
	Weathers[n].Sea.Bump.Ang = 15.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 9.0;
	Weathers[n].Sea.Bump.Scale = 0.1;

	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,164,55,0);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,200,50);
	Weathers[n].Sea.SunRoad.Power = 0.2;

	Weathers[n].Sea.Harmonics.h1 = "  0.0, 5.0, 1.0, 0.0, 250.0";
	Weathers[n].Sea.Harmonics.h2 = "270.0, 1.0, 5.0, 0.0,  50.0";
	Weathers[n].Sea.Harmonics.h3 = " 45.0, 2.0, 3.0, 0.0, 150.0";
	Weathers[n].Sea.Harmonics.h4 = " 90.0, 4.0, 2.5, 0.0,  10.0";

	Weathers[n].Sea2.Harmonics.h1 = "  0.0, 5.0, 1.0, 0.0, 250.0";
	Weathers[n].Sea2.Harmonics.h2 = "270.0, 1.0, 5.0, 0.0,  50.0";
	Weathers[n].Sea2.Harmonics.h3 = " 45.0, 2.0, 3.0, 0.0, 150.0";
	Weathers[n].Sea2.Harmonics.h4 = " 90.0, 4.0, 2.5, 0.0,  10.0";
//---------------------------------------------------------------------
	Weathers[n].Sea.Harmonics.h1  =" 0.0,  40.0, 0.8, 80.87, -48.00";
	Weathers[n].Sea.Harmonics.h2  = "0.57, 22.0, 0.4, 82.28,  48.00";
	Weathers[n].Sea.Harmonics.h3  = "1.57, 27.0, 0.9, 82.28,  48.00";
	Weathers[n].Sea.Harmonics.h4  = "1.0,  17.0, 0.4, 82.28,  48.00";
	Weathers[n].Sea.Harmonics.h5  = "3.27,  7.0, 0.4, 82.28,  48.00";
	
	Weathers[n].Sea2.Harmonics.h1  =" 0.0,  40.0, 0.8, 80.87, -48.00";
	Weathers[n].Sea2.Harmonics.h2  = "0.57, 22.0, 0.4, 82.28,  48.00";
	Weathers[n].Sea2.Harmonics.h3  = "1.57, 27.0, 0.9, 82.28,  48.00";
	Weathers[n].Sea2.Harmonics.h4  = "1.0,  17.0, 0.4, 82.28,  48.00";
	Weathers[n].Sea2.Harmonics.h5  = "3.27,  7.0, 0.4, 82.28,  48.00";

	Weathers[n].Sea.Harmonics.h1  = "0.00, 10.0, 1.2, 80.87, -68.00";
	Weathers[n].Sea.Harmonics.h2  = "1.57, 10.0, 2.1, 82.28,  88.00";
	Weathers[n].Sea.Harmonics.h3  = "0.47,  7.0, 2.2, 82.28,  68.00";
	Weathers[n].Sea.Harmonics.h4  = "0.27, 47.0, 0.5, 82.28, 288.00";
	Weathers[n].Sea.Harmonics.h5  = "1.27, 57.0, 0.7, 82.28, 188.00";
	Weathers[n].Sea.Harmonics.h6  = "2.27, 57.0, 0.3, 82.28,  88.00";
	Weathers[n].Sea.Harmonics.h7  = "2.27, 37.0, 1.2, 82.28, 188.00";
	Weathers[n].Sea.Harmonics.h8  = "2.77, 17.0, 0.5, 82.28, 288.00";
	Weathers[n].Sea.Harmonics.h9  = "1.77, 17.0, 0.1, 82.28, 188.00";
	Weathers[n].Sea.Harmonics.h10 = " 1.0, 14.0, 0.5, 82.28,  28.00";

	Weathers[n].Sea2.Harmonics.h1  = "0.00, 10.0, 1.2, 80.87, -68.00";
	Weathers[n].Sea2.Harmonics.h2  = "1.57, 10.0, 2.1, 82.28,  88.00";
	Weathers[n].Sea2.Harmonics.h3  = "0.47,  7.0, 2.2, 82.28,  68.00";
	Weathers[n].Sea2.Harmonics.h4  = "0.27, 47.0, 0.5, 82.28, 288.00";
	Weathers[n].Sea2.Harmonics.h5  = "1.27, 57.0, 0.7, 82.28, 188.00";
	Weathers[n].Sea2.Harmonics.h6  = "2.27, 57.0, 0.3, 82.28,  88.00";
	Weathers[n].Sea2.Harmonics.h7  = "2.27, 37.0, 1.2, 82.28, 188.00";
	Weathers[n].Sea2.Harmonics.h8  = "2.77, 17.0, 0.5, 82.28, 288.00";
	Weathers[n].Sea2.Harmonics.h9  = "1.77, 17.0, 0.1, 82.28, 188.00";
	Weathers[n].Sea2.Harmonics.h10 = " 1.0, 14.0, 0.5, 82.28,  28.00";

	Weathers[n].Sea2.BumpScale = 0.09;
	Weathers[n].Sea2.PosShift = 1.25;

	Weathers[n].Sea2.WaterColor = argb(0, 65, 100, 110);
	Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.Reflection = 0.9;
	Weathers[n].Sea2.Transparency = 0.3;
	Weathers[n].Sea2.Frenel = 10.0;
	Weathers[n].Sea2.Attenuation = 0.3;

	Weathers[n].Sea2.Amp1 = 5.0;
	Weathers[n].Sea2.AnimSpeed1 = 4.0;
	Weathers[n].Sea2.Scale1 = 0.15;
	Weathers[n].Sea2.MoveSpeed1 = "0.0, 0.0, 2.0";

	Weathers[n].Sea2.Amp2 = 1.75;
	Weathers[n].Sea2.AnimSpeed2 = 9.0;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "-2.0, 0.0, 0.0";

	Weathers[n].Sea2.FoamK = 0.1;
	Weathers[n].Sea2.FoamV = 0.0;
	Weathers[n].Sea2.FoamUV = 0.1;
	Weathers[n].Sea2.FoamTexDisturb = 0.0;

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 7.0;
	Weathers[n].Wind.Speed.Max = 14.5;

	n++;

	return n;
}