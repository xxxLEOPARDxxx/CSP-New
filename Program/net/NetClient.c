#include "Net\Client\Cameras.c"
#include "Net\Client\ShipLights.c"
#include "Net\Client\Time.c"
#include "Net\Client\Fort.c"
#include "Net\Client\OnChat.c"
#include "Net\Client\OnShip.c"
#include "Net\Client\OnPing.c"
#include "Net\Client\OnStart.c"
#include "Net\Client\Weather\Weather.c"
#include "Net\Interfaces\BattleInterface\BattleInterface.c"

int wClientID;

object NCBalls;
object NCConsole;
object NCIsland, NCCoastFoam;
object NCSail, NCVant, NCRope, NCFlag;
object NCSay;
object NCShipTracks;
object NCLightPillar;

object NCServer;

object NCClients[NET_TOTALCLIENTS];
object NCProfiles;
object NCFavorites;
object NCInetServers;

int iLangNetClient;

string sClientNetCamera = "DeckCamera";
int iClientTime, iClientServerTime, iClientDeltaTime;
int iTestDeltaTime;
