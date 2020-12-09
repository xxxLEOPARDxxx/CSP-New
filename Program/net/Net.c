#include "Net\Common.h"
#include "Net\Extern.h"
#include "Net\Net_Defines.h"
#include "Net\NetServer.c"
#include "Net\NetClient.c"
#include "Net\Interfaces\Interface.h"

bool bNetActive = false;

object Net;
object NetServer;
object NetClient;

string	sMasterServerAddress = "192.168.0.15";
int		iMasterServerPort = 29029;
