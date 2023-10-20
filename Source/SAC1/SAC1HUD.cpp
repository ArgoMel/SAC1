#include "SAC1HUD.h"
#include "UI/UW_Main.h"
#include "Blueprint/UserWidget.h"

ASAC1HUD::ASAC1HUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_HUD
	(TEXT("/Game/UI/WBP_HUD.WBP_HUD_C"));
	if (WBP_HUD.Succeeded())
	{
		m_HUDClass = WBP_HUD.Class;
	}
}

void ASAC1HUD::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(m_HUDClass))
	{
		m_HUD = CreateWidget<UUW_Main>(GetWorld(), m_HUDClass);
		if (IsValid(m_HUD))
		{
			m_HUD->AddToViewport();
		}
	}
}

void ASAC1HUD::SetReloadingImage(ESlateVisibility visible)
{
	m_HUD->SetReloadingImage(visible);
}

void ASAC1HUD::SetPlayerDeadUI(ESlateVisibility visible)
{
	m_HUD->SetPlayerDeadUI(visible);
}

void ASAC1HUD::SetWeaponUI(ESlateVisibility visible, const FName& name, int32 curArmo, int32 totalArmo)
{
	m_HUD->SetWeaponUI(visible, name, curArmo, totalArmo);
}

void ASAC1HUD::SetMainUIText(int32 progress,const FString& text)
{
	m_HUD->SetMainUIText(progress,text);
}
