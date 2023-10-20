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

public:
	void SetReloadingImage(ESlateVisibility visible);
	void SetPlayerDeadUI(ESlateVisibility visible);
	void SetWeaponUI(ESlateVisibility visible, const FName& name,int32 curArmo, int32 totalArmo);
	void SetMainUIText(int32 progress,const FString& text);
};
