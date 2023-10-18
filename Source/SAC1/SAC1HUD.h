#pragma once
#include "GameInfo.h"
#include "GameFramework/HUD.h"
#include "SAC1HUD.generated.h"

UCLASS()
class SAC1_API ASAC1HUD : public AHUD
{
	GENERATED_BODY()
public:
	ASAC1HUD();
	virtual void BeginPlay() override;

private:
	TSubclassOf<UUserWidget>	m_HUDClass;
	TObjectPtr<class UUW_Main>	m_HUD;
};
