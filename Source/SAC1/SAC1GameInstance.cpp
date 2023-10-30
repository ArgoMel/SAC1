#include "SAC1GameInstance.h"

USAC1GameInstance::USAC1GameInstance()
{
	m_HasWeapons.Init(false, (int32)ECharacterEquip::Food);

	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerTable(TEXT(
		"/Script/Engine.DataTable'/Game/Data/DT_PlayerData.DT_PlayerData'"));
	if (PlayerTable.Succeeded())
	{
		mPlayerDataTable = PlayerTable.Object;
	}
}

void USAC1GameInstance::Init()
{
	Super::Init();
}

const FPlayerDataTable* USAC1GameInstance::FindPlayerData(const FName& Name)
{
	return mPlayerDataTable->FindRow<FPlayerDataTable>(Name, TEXT(""));
}

void USAC1GameInstance::SetHasWeapons(int32 index, bool b)
{
	if (index < 0 || index >= m_HasWeapons.Num())
	{
		return;
	}
	m_HasWeapons[index]= b;
}

bool USAC1GameInstance::GetHasWeapons(int32 index)
{
	if(index<0|| index>=m_HasWeapons.Num())
	{
		return false;
	}
	return m_HasWeapons[index];
}
