#include "net\server\weather\Lightning.c"
#include "net\server\weather\Sea.c"
//#include "weather\Tornado.c"

object	NSWeather;
int		iServerCurWeatherNum = -1;
float	fServerWeatherDelta = 0.0;
float	fServerWeatherAngle, fServerWeatherSpeed;
bool	bServerWeatherIsNight = false;
bool	bServerWeatherIsStorm = false;
bool	bServerWhrTornado = false;
string	sServerLightingPath;
