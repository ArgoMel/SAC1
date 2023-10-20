#include "UW_Main.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/Border.h"
//#include "Blueprint/WidgetBlueprintGeneratedClass.h"
//#include "Animation/WidgetAnimation.h"

void UUW_Main::NativeConstruct()
{
	Super::NativeConstruct();
	m_Progress = 0;

    m_ReloadingImage = Cast<UImage>(GetWidgetFromName(TEXT("ReloadingImage")));

	m_RestartBtn = Cast<UButton>(GetWidgetFromName(TEXT("RestartBtn")));
	m_RestartBtn->OnClicked.AddDynamic(this, &UUW_Main::RestartBtnClick);

	m_ExitBtn = Cast<UButton>(GetWidgetFromName(TEXT("ExitBtn")));
	m_ExitBtn->OnClicked.AddDynamic(this, &UUW_Main::ExitBtnClick);

	m_InfoText = Cast<UTextBlock>(GetWidgetFromName(TEXT("InfoText")));
	m_ArmoText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ArmoText")));

	m_ArmoBorder = Cast<UBorder>(GetWidgetFromName(TEXT("ArmoBorder")));
}

void UUW_Main::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(m_ReloadingImage->GetVisibility()==ESlateVisibility::Visible)
	{
		float angle= m_ReloadingImage->GetRenderTransformAngle()+InDeltaTime *200.f;
		angle = (int)angle%360;
		m_ReloadingImage->SetRenderTransformAngle(angle);
	}
}

void UUW_Main::RestartBtnClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), *UGameplayStatics::GetCurrentLevelName(GetWorld()));
}

void UUW_Main::ExitBtnClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);
}

void UUW_Main::SetReloadingImage(ESlateVisibility visible)
{
	m_ReloadingImage->SetVisibility(visible);
}

void UUW_Main::SetPlayerDeadUI(ESlateVisibility visible)
{
	m_RestartBtn->SetVisibility(visible);
	m_ExitBtn->SetVisibility(visible);
}

void UUW_Main::SetWeaponUI(ESlateVisibility visible, const FName& name, int32 curArmo, int32 totalArmo)
{
	m_ArmoBorder->SetVisibility(visible);
	FString temp = name.ToString()+TEXT(" : ")+ FString::FromInt(curArmo)+ TEXT(" / ") + FString::FromInt(totalArmo);
	FText text = FText::FromString(temp);
	m_ArmoText->SetText(text);
}

void UUW_Main::SetMainUIText(int32 progress, const FString& text)
{
	if(m_Progress> progress)
	{
		return;
	}
	m_Progress = progress;
	m_InfoText->SetText(FText::FromString(text));
}
