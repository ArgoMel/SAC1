#include "SAC1PlayerState.h"
#include "SAC1GameInstance.h"

void ASAC1PlayerState::InitPlayerData(const FName& name)
{
	USAC1GameInstance* gameInst = GetWorld()->GetGameInstance<USAC1GameInstance>();
	if (IsValid(gameInst))
	{
		m_data = *gameInst->FindPlayerData(name);
	}
}

FPlayerDataTable* ASAC1PlayerState::GetData()
{
	return &m_data;
}

void ASAC1PlayerState::SetPlayerData(FPlayerDataTable* data)
{
	m_data = *data;
}

bool ASAC1PlayerState::AddHp(int32 hp)
{
	m_data.HP += hp;
	if (m_data.HP > m_data.HPMax)
	{
		m_data.HP = m_data.HPMax;
	}
	if (m_data.HP < 0)
	{
		return true;
	}
	return false;
}
