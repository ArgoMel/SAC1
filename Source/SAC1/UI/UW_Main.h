#pragma once
#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "UW_Main.generated.h"

class UImage;
class UButton;

UCLASS()
class SAC1_API UUW_Main : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
private:
	UImage* m_ReloadingImage;
	UButton* m_RestartBtn;
	UButton* m_ExitBtn;

private:
	UFUNCTION()
	void RestartBtnClick();
	UFUNCTION()
	void ExitBtnClick();

public:
	UFUNCTION()
	void SetReloadingImage(ESlateVisibility visible);
	UFUNCTION()
	void SetPlayerDeadUI(ESlateVisibility visible);
};
