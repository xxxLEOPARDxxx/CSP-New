#include "Net\Server\OnBall.c"
#include "Net\Server\OnStart.c"
#include "Net\Server\Rigging.c"
#include "Net\Server\Island.c"
#include "Net\Server\Touch.c"
#include "Net\Server\Time.c"
#include "Net\Server\Buy.c"
#include "Net\Server\Fort.c"
#include "Net\Server\ServerInfo.c"
#include "Net\Server\Weather\Weather.c"

#define NET_TOTALCLIENTS			255		// total massive
#define NET_MAXCLIENTS				16		// absolute maximum is 254
#define NET_FORTCLIENT				253
#define MAX_TOPPLAYERS				100
#define MASTERSERVER_UPDATETIME		60000

int		NSSortedPlayers[MAX_TOPPLAYERS];
object	NSClients[NET_TOTALCLIENTS];	// current game clients
object	NSBanList;						// server ban list

object NSPlayers;						// All players in server for last month

int iServerTime;
int iPingTime;
bool bNetServerIsStarted = false;
