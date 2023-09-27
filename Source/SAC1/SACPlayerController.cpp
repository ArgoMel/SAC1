#include "SACPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ASACPlayerController::ASACPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	//bShowMouseCursor = true;
}

void ASACPlayerController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	FInputModeGameOnly	InputMode;

	SetInputMode(InputMode);
}

void ASACPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASACPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	m_IMC = NewObject<UInputMappingContext>(this);
	m_MouseLClick = NewObject<UInputAction>(this);
	m_MouseLClick->ValueType = EInputActionValueType::Boolean;
	m_IMC->MapKey(m_MouseLClick, EKeys::LeftMouseButton);
	m_MouseMClick = NewObject<UInputAction>(this);
	m_MouseMClick->ValueType = EInputActionValueType::Boolean;
	m_IMC->MapKey(m_MouseMClick, EKeys::MiddleMouseButton);
	m_MouseWheel = NewObject<UInputAction>(this);
	m_MouseWheel->ValueType = EInputActionValueType::Axis1D;
	m_IMC->MapKey(m_MouseWheel, EKeys::MouseWheelAxis);
	m_MousePos = NewObject<UInputAction>(this);
	m_MousePos->ValueType = EInputActionValueType::Axis2D;
	m_IMC->MapKey(m_MousePos, EKeys::Mouse2D);
	m_E = NewObject<UInputAction>(this);
	m_E->ValueType = EInputActionValueType::Boolean;
	m_IMC->MapKey(m_E, EKeys::E);
	m_Space = NewObject<UInputAction>(this);
	m_Space->ValueType = EInputActionValueType::Boolean;
	m_IMC->MapKey(m_Space, EKeys::SpaceBar);
	m_LShift = NewObject<UInputAction>(this);
	m_LShift->ValueType = EInputActionValueType::Boolean;
	m_IMC->MapKey(m_LShift, EKeys::LeftShift);

	m_Move = NewObject<UInputAction>(this);
	m_Move->ValueType = EInputActionValueType::Axis3D;
	MoveModifier(m_IMC, m_Move, EKeys::W);
	MoveModifier(m_IMC, m_Move, EKeys::S, true);
	MoveModifier(m_IMC, m_Move, EKeys::A, true, true);
	MoveModifier(m_IMC, m_Move, EKeys::D, false, true);
}

void ASACPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void ASACPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ASACPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASACPlayerController::MoveModifier(UInputMappingContext* IMC, UInputAction* IA, FKey key, 
	bool isNegate, bool isSwizzle, EInputAxisSwizzle swizzleOrder)
{
	FEnhancedActionKeyMapping& mapping = IMC->MapKey(IA, key);
	UObject* outer = IMC->GetOuter();
	if (isNegate)
	{
		UInputModifierNegate* negate = NewObject<UInputModifierNegate>(outer);
		mapping.Modifiers.Add(negate);
	}
	if (isSwizzle)
	{
		UInputModifierSwizzleAxis* swizzle = NewObject<UInputModifierSwizzleAxis>(outer);
		swizzle->Order = swizzleOrder;
		mapping.Modifiers.Add(swizzle);
	}
}

void ASACPlayerController::SetNewController()
{
	ULocalPlayer* localPlayer = GetLocalPlayer();
	if (IsValid(localPlayer))
	{
		UEnhancedInputLocalPlayerSubsystem* subSystem =
			localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (IsValid(subSystem))
		{
			subSystem->ClearAllMappings();
			subSystem->AddMappingContext(m_IMC, 0);
		}
	}
}