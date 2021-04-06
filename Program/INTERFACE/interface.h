#define INTERFACE_QUANTITY				71

#define INTERFACE_STORE					0
#define INTERFACE_SHIPYARD				1
#define INTERFACE_CHARACTER				2  // �������� ��� � ����� �������
#define INTERFACE_MAINMENU				3
#define INTERFACE_HIRECREW				4
#define INTERFACE_RANSACK_MAIN			5 // ����� �� ��� �����, �� ���-�� ���� �������� �� �����������, �����  INTERFACE_TRANSFER_MAIN �� ����, �� � ��������� �� ���� � �������
#define INTERFACE_TRANSFER_MAIN			6
#define INTERFACE_ITEMS					7
#define INTERFACE_CHARACTER_SELECT		8  // ������ ����
#define INTERFACE_QUESTBOOK				9
#define INTERFACE_SAVELOAD				10
#define INTERFACE_FORTCAPTURE			11
#define INTERFACE_ITEMSBOX				12
#define INTERFACE_OPTIONSCREEN			13
#define INTERFACE_CHARACTER_ALL			14
#define INTERFACE_ITEMSTRADE			15
#define INTERFACE_SALARY				16
#define INTERFACE_PS_HERO	     		17  //boal
#define INTERFACE_NATIONRELATION				18
#define INTERFACE_FOR_TEST  			19  // ��� ������
#define INTERFACE_MAP					20
#define INTERFACE_CANNONS 				21
#define INTERFACE_TRADEBOOK				22
#define INTERFACE_NATION_LEGEND			23
#define INTERFACE_PAPER_MAP				24
#define INTERFACE_COLONY_CAPTURE		25
#define INTERFACE_ABOUT					26
#define INTERFACE_SAILSGERALD 			27  // ���� �� �����
//#define INTERFACE_RIOT_RESULT			27
#define INTERFACE_NET_FINDGAME			28
#define INTERFACE_NET_CREATEGAME		29
#define INTERFACE_NET_BUY				30
#define INTERFACE_NET_CHAT				31
#define INTERFACE_NET_GAMESTATE			32
#define INTERFACE_NET_TOPLIST			33
#define INTERFACE_NET_CHATSTRING		34
#define INTERFACE_NET_PLAYERSETTINGS	35
#define INTERFACE_NET_ENDGAME			36
#define INTERFACE_GAMEMENU			    37
#define INTERFACE_DISEASE_ALERT		    38
#define INTERFACE_SHIP_CHOOSE			39   // to_do
#define INTERFACE_COLONY_INFO			40   // to_do
#define INTERFACE_QUICK_SAVE			41
#define INTERFACE_NET_NETMENU			42
#define INTERFACE_DEBUGER   			43 //boal
#define INTERFACE_BOAL_BETA             44
#define INTERFACE_DICE_GAME             45
#define INTERFACE_CARDSGAME             46
//#define INTERFACE_BOAL_CHARACTER        47
#define INTERFACE_FRAMEFORM             48
#define INTERFACE_LEAVE_BATTLE          49
// Warship -->
#define INTERFACE_BEST_MAP			50	// ��������� �������� �����
#define INTERFACE_TAVERN_WAIT			51	// ��������� ������
#define INTERFACE_GOODS_TRANSFER		52	// ��������� ������� ������ ���������
// <-- Warship
// Ugeen -->
#define INTERFACE_MAPVIEW				53 // ��������� ������ ���� 
#define INTERFACE_STORAGE				54 // ��������� ������
#define INTERFACE_SPEAK                 55  // Philippe, ajout
#define INTERFACE_CONTRATRADE			56 // ��������� �������� � ����������������
#define	INTERFACE_CREATENOTICE			57
// <-- Ugeen

// Lugger -->

#define INTERFACE_COLONYBUILDING		58
#define INTERFACE_MINES				59
#define INTERFACE_ATTACK_MESSAGE		60
#define INTERFACE_COLONY			61
#define	INTERFACE_PLANTATION			62
#define	INTERFACE_STOREHOUSE			63
#define	INTERFACE_COLONYGUARDING		64
#define	INTERFACE_ACADEMY			65
#define	INTERFACE_COLONY_LAND_GUARD		66
#define	INTERFACE_MEKAKHROM			67
#define	INTERFACE_QUICKLY_TRADER		68
// Lugger <--

#define INTERFACE_LOCKPICK				69 //New Abilities - ����� �������

#define	INTERFACE_CREATE_CHARACTER		70

#define RC_INTERFACE_DO_NOTHING			-1

// main menu exit codes
#define RC_INTERFACE_MAIN_MENU_EXIT				45000
#define RC_INTERFACE_DO_NEW_GAME				45001
#define RC_INTERFACE_DO_LOAD_GAME				45002
#define RC_INTERFACE_DO_SAVE_GAME				45003
#define RC_INTERFACE_DO_OPTIONS					45004
#define RC_INTERFACE_DO_CONTROLS				45005
#define RC_INTERFACE_DO_CREDITS					45006
#define RC_INTERFACE_DO_RESUME_GAME				45007
// common interface codes
#define RC_INTERFACE_RIGHT_CHANGE				45010
#define RC_INTERFACE_LEFT_CHANGE				45011
#define RC_INTERFACE_ERROR						45012
// other interfaces exit codes
#define RC_INTERFACE_STORE_EXIT					45020
#define RC_INTERFACE_CHARACTER_EXIT				45021
#define RC_INTERFACE_HIRECREW_EXIT				45022
#define RC_INTERFACE_SHIPSTATE_EXIT				45023
#define RC_INTERFACE_SHIPSTATE_OK				45024
#define RC_INTERFACE_SHIPYARD_EXIT				45025
#define RC_INTERFACE_RANSACK_MAIN_EXIT			45026 // �����, ������������ � ������.�
//#define RC_INTERFACE_TRANSFER_MAIN_EXIT			45027
//#define RC_INTERFACE_TRANSFER_MAIN_RETURN		45028
//#define RC_INTERFACE_TRANSFER_START_GOODS		45029
//#define RC_INTERFACE_TRANSFER_START_CHARACTERS	45030
//#define RC_INTERFACE_TRANSFER_START_CREW		45031
#define RC_INTERFACE_CHARACTER_SELECT_EXIT		45032
#define RC_INTERFACE_QUESTBOOK_EXIT				45033
#define RC_INTERFACE_SAVELOAD_EXIT				45034
#define RC_INTERFACE_ITEMS_EXIT					45035
#define RC_INTERFACE_FORTCAPTURE_EXIT			45036
#define RC_INTERFACE_ITEMSBOX_EXIT				45037
#define RC_INTERFACE_OPTIONSCREEN_EXIT			45038
//#define RC_INTERFACE_SELECTMENU_EXIT			45039
#define RC_INTERFACE_ITEMSTRADE_EXIT			45040
#define RC_INTERFACE_SALARY_EXIT				45041
//#define RC_INTERFACE_PLAYGAME_EXIT				45042
#define RC_INTERFACE_ANY_EXIT				45043
#define RC_INTERFACE_LANGUAGESET_EXIT			45044
#define RC_INTERFACE_COLONY_EXIT				45045
#define RC_INTERFACE_COLONY_MANAGEMENT_EXIT		45046
#define RC_INTERFACE_FOOD_INFO_EXIT				45047
//#define RC_INTERFACE_CAREER_MONEY_EXIT			45048
#define RC_INTERFACE_PAPER_MAP					45049
//#define RC_INTERFACE_ASK_FOR_HELP_EXIT			45050
#define RC_INTERFACE_SPEAK_EXIT					45051
#define RC_INTERFACE_SPEAK_EXIT_AND_CAPTURE		45052
#define RC_INTERFACE_SPEAK_EXIT_AND_TRADE		45053
#define RC_INTERFACE_TO_PASS					45054
#define RC_INTERFACE_TO_SHIP					45055
#define RC_INTERFACE_TO_TRADEBOOK				45056
#define RC_INTERFACE_TO_LOGBOOK					45057
//#define RC_INTERFACE_TO_COLONY					45058
#define RC_INTERFACE_TO_ITEMS					45059
#define RC_INTERFACE_TO_CHAR					45060
//#define RC_INTERFACE_HIRE_OFFICER_EXIT			45061
#define RC_INTERFACE_MAP_EXIT					45061
//#define RC_INTERFACE_RIOT_RESULT_EXIT			45062
#define RC_INTERFACE_NET_EXIT					45063
#define RC_INTERFACE_NET_FINDGAME				45064
#define RC_INTERFACE_NET_CREATEGAME				45065
#define RC_INTERFACE_NET_BUY					45066
#define RC_INTERFACE_NET_CHAT					45067
#define RC_INTERFACE_NET_GAMESTATE				45068
#define RC_INTERFACE_NET_TOPLIST				45069
#define RC_INTERFACE_NET_CHATSTRING				45070
#define RC_INTERFACE_NET_PLAYERSETTINGS			45071
#define RC_INTERFACE_NET_ENDGAME				45072
#define RC_INTERFACE_NET_NETMENU				45073
#define RC_INTERFACE_LAUNCH_GAMEMENU			45074
#define RC_INTERFACE_QUICK_SAVE					45075
// boal -->
#define RC_INTERFACE_DO_BOAL_BETA               45101
// boal <--
// Warship -->
#define RC_INTERFACE_BEST_MAP					45076	// ��������� �������� �����
#define RC_INTERFACE_TAVERN_WAIT				45077	// ��������� ������
#define RC_INTERFACE_GOODS_TRANSFER				45078	// ��������� ������� ������ ���������
// <-- Warship
// Ugeen -->
#define RC_INTERFACE_MAPVIEW					45079   // ��������� ������ ���� 
#define RC_INTERFACE_STORAGE_EXIT				45080   // ��������� ������
#define RC_INTERFACE_CONTRATRADE				45082   // ��������� �������� � ����������������
// <-- Ugeen
#define RC_INTERFACE_LOCKPICK					45083 //New Abilities - ����� �������

#define MAX_SAVE_STORE_BLOCKS	160

int	interfaceResultCommand;
object	GameInterface;
object	LanguageObject;
object  Interfaces[INTERFACE_QUANTITY];


// ��������� ����������
object InterfaceStates;
//������� ������
object PlayerProfile;

extern void InitBaseInterfaces();
extern void InitBaseInterfaces_main();
extern void InitInterfaceTables();