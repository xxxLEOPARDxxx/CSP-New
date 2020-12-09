#include "net\client\weather\Lightning.c"
#include "net\client\weather\Rain.c"
#include "net\client\weather\Sea.c"
#include "net\client\weather\Sky.c"
#include "net\client\weather\Sun.c"
#include "net\client\weather\Astronomy.c"

object	NCWeather;
int		iClientCurWeatherNum = -1;
string	sClientCurrentFog;
bool	bClientWeatherIsNight = false;
bool	bClientWeatherIsLight = false;
bool	bClientWeatherIsRain = false;
bool	bClientWeatherIsStorm = false;
string	sClientLightingPath;
