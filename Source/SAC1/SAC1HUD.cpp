#include "SAC1HUD.h"
#include "Blueprint/UserWidget.h"

ASAC1HUD::ASAC1HUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_HUD
	(TEXT("/Game/Recoil/UI/WBP_HUD.WBP_HUD_C"));
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
		m_HUD = CreateWidget<UUserWidget>(GetWorld(), m_HUDClass);
		if (IsValid(m_HUD))
		{
			m_HUD->AddToViewport();
		}
	}
}
