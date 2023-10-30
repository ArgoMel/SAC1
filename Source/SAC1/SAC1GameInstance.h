#pragma once
#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "SAC1GameInstance.generated.h"


UCLASS()
class SAC1_API USAC1GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USAC1GameInstance();
public:
	virtual void Init();

private:
	TObjectPtr<UDataTable>	mPlayerDataTable;
	TArray<bool> m_HasWeapons;

public:
	const FPlayerDataTable* FindPlayerData(const FName& Name);

	void SetHasWeapons(int32 index,bool b);
	bool GetHasWeapons(int32 index);
};
