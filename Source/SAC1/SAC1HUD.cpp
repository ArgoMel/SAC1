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
