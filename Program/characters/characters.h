#define CHARACTER_NOTUSED_NAME	"Noname"
#define BASE_CHARACTER_ONE 0
#define BASE_CHARACTER_TWO 1

#define MORALE_MAX  100
#define MORALE_NORMAL   50
#define MORALE_MIN      0
#define MORALE_TABLE_SIZE	10
#define MORALET_TREACHEROUS	0	//�������
#define MORALET_AWFUL		1	//��������������
#define MORALET_LOW			2	//������
#define MORALET_POOR		3	//������
#define MORALET_NORMAL		4	//�������
#define MORALET_ELATED		5	//�����������
#define MORALET_GOOD		6	//�������
#define MORALET_HIGH		7	//�������
#define MORALET_EXCELLENT	8	//��������
#define MORALET_HEROIC		9	//�����������
string  MoraleTable[MORALE_TABLE_SIZE];
string  LoyalityTable[MORALE_TABLE_SIZE];

#define REPUTATION_MIN          1
#define REPUTATION_NEUTRAL      45
#define REPUTATION_MAX          90

#define MAX_LOYALITY            35

#define PASSENGERS_MAX	64
#define PRISONER_MAX	20
#define COMPANION_MAX	8

// boal -->
#define SKILL_MAX           100
#define SKILL_MAX_TOTAL	    100 // �������� ��� ����� ��� ������
#define SPECIAL_MAX         10
#define SKILL_TO_OLD        10.0
// ������
#define SKILL_F_LIGHT		"FencingLight"  //1
#define SKILL_FENCING		"Fencing"
#define SKILL_F_HEAVY		"FencingHeavy"
#define SKILL_PISTOL		"Pistol" // boal
#define SKILL_FORTUNE	    "Fortune"     //5
// �����������
#define SKILL_LEADERSHIP	"Leadership"    //6
#define SKILL_COMMERCE		"Commerce"
#define SKILL_ACCURACY		"Accuracy"
#define SKILL_CANNONS		"Cannons"
#define SKILL_SAILING		"Sailing"
#define SKILL_REPAIR		"Repair"
#define SKILL_GRAPPLING		"Grappling"
#define SKILL_DEFENCE		"Defence"
#define SKILL_SNEAK		    "Sneak"   //14

// ��������
#define SPECIAL_S	"Strength"   //15
#define SPECIAL_P	"Perception"
#define SPECIAL_E	"Endurance"
#define SPECIAL_C	"Charisma"
#define SPECIAL_I	"Intellect"
#define SPECIAL_A	"Agility"
#define SPECIAL_L	"Luck"  //21

#define SPECIAL_TYPE	"SPECIAL"
#define SKILL_TYPE	    "Skill"
// boal <--

#define KILL_BY_BALL		1
#define KILL_BY_ABORDAGE	2
#define KILL_BY_SPY			3
#define KILL_BY_ISLAND		4
#define KILL_BY_TOUCH		5
#define KILL_BY_SELF        6 ///boal
