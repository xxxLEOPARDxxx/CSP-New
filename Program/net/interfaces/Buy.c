int iSkillAccuracy = 0, iSkillCannons = 0, iSkillSailing = 0, iSkillDefence = 0, iSkillRepair = 0;

int BuyClients[NET_TOTALCLIENTS];

int iCurrentCredit = 0, iMaxCredit = 0;
int iSkillsQuantity[5];
int iNetGoodsQuantity[6];
int iPerks[6];
int iCurrentShipType = -1;
int iCurrentShipUpgradeHull = -1;
int iCurrentShipUpgradeRigging = -1;
int iCurrentCannonType = -1;
int iCurrentCannonUpgrade = -1;
int iSelectedTeam = -1;
int iNumClients = 0;

int iClientStartTimer = 10000;
bool bStartCountDown = false;
bool bSelectNewTeamWindow = false;

float fServerInfoPiecesLoaded = 0.0;

bool bServerInfoReady = false;
