
//������������ ���� ��� ���������

//�����
#include "Loc_ai\types\LAi_player.c"
//������
#include "Loc_ai\types\LAi_officer.c"
//���������
#include "Loc_ai\types\LAi_citizen.c"
//�������
#include "Loc_ai\types\LAi_guardian.c"
//�������
#include "Loc_ai\types\LAi_patrol.c"
//����
#include "Loc_ai\types\LAi_warrior.c"
//��������
#include "Loc_ai\types\LAi_merchant.c"
//������� �������
#include "Loc_ai\types\LAi_stay.c"
//������� �������
#include "Loc_ai\types\LAi_sit.c"
//������
#include "Loc_ai\types\LAi_barman.c"
//����������
#include "Loc_ai\types\LAi_waitress.c"
//�����
#include "Loc_ai\types\LAi_poor.c"
//����������, ������� �� �����
#include "Loc_ai\types\LAi_huber.c"
//����������, ������� �� ���������
#include "Loc_ai\types\LAi_huberstay.c"
//��������
#include "Loc_ai\types\LAi_priest.c"
//����
#include "Loc_ai\types\LAi_actor.c"
//������ ����
#include "Loc_ai\types\LAi_owner.c"
//���������
#include "Loc_ai\types\LAi_carrier.c"
//������ ���, �� ���������
#include "Loc_ai\types\LAi_LSCout.c"
//������� �� �����
#include "Loc_ai\types\LAi_groundSit.c"
// ����������
#include "Loc_ai\types\LAi_stunned.c"
//��������-������
#include "Loc_ai\types\LAi_monkey.c"

//------------------------------------------------------------------------------------------
//Player
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ������
void LAi_SetPlayerType(aref chr)
{
	//��� ��������� �� ���������
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	//������ �����������
	LAi_type_player_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
}

//------------------------------------------------------------------------------------------
//Officer
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �������
void LAi_SetOfficerType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_officer_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
	//LAi_DelAdjustFencingSkill(chr);
}

//���������� ��������� ��� �������
void LAi_SetFollowerType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_follower_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
	//LAi_DelAdjustFencingSkill(chr);
}

//------------------------------------------------------------------------------------------
//Citizen
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ����������
void LAi_SetCitizenType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_citizen_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ����������, ��� ����������� � ������
void LAi_SetCitizenTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_citizen_Init(chr);
}

//------------------------------------------------------------------------------------------
//Guardian
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ���������
void LAi_SetGuardianType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_guardian_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_GUARDS);
// boal	if (!IsOfficer(chr))
	//{
	//	LAi_SetAdjustFencingSkill(chr, -4.0, 2.0);
	//}
}

//���������� ��������� ��� ���������, ��� ����������� � ������
void LAi_SetGuardianTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_guardian_Init(chr);
}

//------------------------------------------------------------------------------------------
//Patrol
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �������
void LAi_SetPatrolType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_SetPatrolTypeNoGroup(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_GUARDS);
// boal	if (!IsOfficer(chr))
//	{
//		LAi_SetAdjustFencingSkill(chr, -4.0, 2.0);
//	}
}

//���������� ��������� ��� �������, ��� ����������� � ������
void LAi_SetPatrolTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_patrol_Init(chr);
}

//------------------------------------------------------------------------------------------
//Warrior
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �����
void LAi_SetWarriorType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_warrior_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_GUARDS);
	if(chr.model == "monkey")
	{
		LAi_SetMonkeyTypeNoGroup(chr);
	}
//	if (!IsOfficer(chr))
//	{
//		LAi_SetAdjustFencingSkill(chr, -4.0, 2.0);
//	}
}

//���������� ��������� ��� �����, ��� ����������� � ������
void LAi_SetWarriorTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_warrior_Init(chr);
	if(chr.model == "monkey")
	{
		LAi_SetMonkeyTypeNoGroup(chr);
	}
}


//------------------------------------------------------------------------------------------
//Merchant
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ��������
void LAi_SetMerchantType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_merchant_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ��������, ��� ����������� � ������
void LAi_SetMerchantTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_merchant_Init(chr);
}

//------------------------------------------------------------------------------------------
//Stay
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ��������
void LAi_SetStayType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_stay_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ��������, ��� ����������� � ������
void LAi_SetStayTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_stay_Init(chr);
}

//------------------------------------------------------------------------------------------
//Sit
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ��������
void LAi_SetSitType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_sit_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ��������, ��� ����������� � ������
void LAi_SetSitTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_sit_Init(chr);
}


//------------------------------------------------------------------------------------------
//Barmen
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ������� (only man)
void LAi_SetBarmanType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_barman_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ����������, ��� ����������� � ������ (only man)
void LAi_SetBarmanTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_barman_Init(chr);
}

//------------------------------------------------------------------------------------------
//Waitress
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ���������� (only woman)
void LAi_SetWaitressType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_waitress_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ����������, ��� ����������� � ������ (only woman)
void LAi_SetWaitressTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_waitress_Init(chr);
}


//------------------------------------------------------------------------------------------
//Poor
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �������
void LAi_SetPoorType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_poor_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� �������, ��� ����������� � ������
void LAi_SetPoorTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_poor_Init(chr);
}

//------------------------------------------------------------------------------------------
//Huber
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �����������
void LAi_SetHuberType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huber_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_HUBER);
}

//���������� ��������� ��� �����������, ��� ����������� � ������
void LAi_SetHuberTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huber_Init(chr);
}

//------------------------------------------------------------------------------------------
//HuberStay
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �����������, �������� �� �������
void LAi_SetHuberStayType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huberstay_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_HUBER);
}

//���������� ��������� ��� �����������, �������� �� �������, ��� ����������� � ������
void LAi_SetHuberStayTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_huberstay_Init(chr);
}

//------------------------------------------------------------------------------------------
//Priest
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ���������
void LAi_SetPriestType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_priest_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� ���������, ��� ����������� � ������
void LAi_SetPriestTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_priest_Init(chr);
}


//------------------------------------------------------------------------------------------
//Actor
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �����
void LAi_SetActorType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_actor_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_ACTOR);
}

//���������� ��������� ��� �����, ��� ����������� � ������
void LAi_SetActorTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_actor_Init(chr);
}

//------------------------------------------------------------------------------------------
//Owner
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ������� ����/�������
void LAi_SetOwnerType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_owner_Init(chr);
	LAi_group_MoveCharacter(chr, "");
}

//���������� ��������� ��� ������� ������� ��� ����������� � ������
void LAi_SetOwnerTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_owner_Init(chr);
}

//------------------------------------------------------------------------------------------
//Carrier
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ������� ����/�������
void LAi_SetCarrierType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_carrier_Init(chr);
	LAi_group_MoveCharacter(chr, "");
}

//���������� ��������� ��� ������� ������� ��� ����������� � ������
void LAi_SetCarrierTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_carrier_Init(chr);
}

//------------------------------------------------------------------------------------------
//LSCout
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ���������� ���
void LAi_SetLSCoutType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAI_type_LSCout_Init(chr);
	LAi_group_MoveCharacter(chr, "");
}

//���������� ��������� ��� ���������� ��� ��� ����������� � ������
void LAi_SetLSCoutTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAI_type_LSCout_Init(chr);
}

//------------------------------------------------------------------------------------------
//GroundSit
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �������� �� �����
void LAi_SetGroundSitType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAI_type_GroundSit_Init(chr);
	LAi_group_MoveCharacter(chr, "");
}

//���������� ��������� ��� �������� �� ����� ��� ����������� � ������
void LAi_SetGroundSitTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAI_type_GroundSit_Init(chr);
}


//------------------------------------------------------------------------------------------
// Stunned 
//------------------------------------------------------------------------------------------

//���������� ��������� ��� �����������
void LAi_SetStunnedType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_Stunned_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

//���������� ��������� ��� �����������, ��� ����������� � ������
void LAi_SetStunnedTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_Stunned_Init(chr);
}

//------------------------------------------------------------------------------------------
//Monkey
//------------------------------------------------------------------------------------------

//���������� ��������� ��� ��������-�������
void LAi_SetMonkeyType(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_monkey_Init(chr);
	LAi_group_MoveCharacter(chr, LAI_GROUP_MONSTERS);
}

//���������� ��������� ��� ��������-�������, ��� ����������� � ������
void LAi_SetMonkeyTypeNoGroup(aref chr)
{
	chr.chr_ai.type = LAI_DEFAULT_TYPE;
	LAi_type_monkey_Init(chr);
}