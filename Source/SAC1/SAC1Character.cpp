#include "SAC1Character.h"
#include "SAC1Projectile.h"
#include "SAC1PlayerController.h"
#include "SAC1AnimInstance.h"
#include "Actor_PickUp.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

ASAC1Character::ASAC1Character()
{
	float height = 96.f;

	m_PickUpExtent = FVector(50.f,50.f, height);
	m_CameraSpeed = 50.f;
	m_ZoomSpeed = 200.f;
	m_MaxWalkSpeed = 75.f;
	m_MaxSprintSpeed = 375.f;
	m_IsInvertX = false;
	m_IsInvertY = true;
	m_CanMove = true;
	m_IsSprinting = false;
	
	GetCapsuleComponent()->InitCapsuleSize(20.f, height);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	SetRootComponent(GetCapsuleComponent());

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -height));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_SpringArm->SetupAttachment(GetMesh(), TEXT("head"));
	m_SpringArm->TargetArmLength = 0.f;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Camera->SetupAttachment(m_SpringArm);
	m_Camera->SetRelativeLocation(FVector(5., 15., 0.));
	m_Camera->bUsePawnControlRotation = true;

	GetCharacterMovement()->MaxWalkSpeed = 75.f;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_Manny(TEXT(
		"/Game/ControlRig/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn"));
	if (SKM_Manny.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SKM_Manny.Object);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance>	AB_Player(TEXT(
		"/Game/ControlRig/Characters/Mannequins/Animations/AB_Player.AB_Player_C"));
	if (AB_Player.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AB_Player.Class);
	}
}

void ASAC1Character::BeginPlay()
{
	Super::BeginPlay();
	m_AnimInst = Cast<USAC1AnimInstance>(GetMesh()->GetAnimInstance());
}

void ASAC1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	ASAC1PlayerController* controller = Cast<ASAC1PlayerController>(Controller);
	if (IsValid(input) && IsValid(controller))
	{
		input->BindAction(controller->m_MousePos, ETriggerEvent::Triggered, this, &ASAC1Character::CameraRotation);
		input->BindAction(controller->m_MouseWheel, ETriggerEvent::Triggered, this, &ASAC1Character::CameraZoom);
		input->BindAction(controller->m_Space, ETriggerEvent::Started, this, &ASAC1Character::Jump);
		input->BindAction(controller->m_Space, ETriggerEvent::Completed, this, &ASAC1Character::StopJumping);
		input->BindAction(controller->m_F, ETriggerEvent::Started, this, &ASAC1Character::CollectPickUps);
		input->BindAction(controller->m_Move, ETriggerEvent::Triggered, this, &ASAC1Character::Move);
		input->BindAction(controller->m_LShift, ETriggerEvent::Started, this, &ASAC1Character::Sprint);
		input->BindAction(controller->m_LShift, ETriggerEvent::Completed, this, &ASAC1Character::Sprint);
		controller->SetNewController();
	}
}

void ASAC1Character::BodyHit(UPrimitiveComponent* comp, AActor* otherActor, 
	UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& result)
{
}

void ASAC1Character::OverlapBegin(UPrimitiveComponent* comp, AActor* otherActor, 
	UPrimitiveComponent* otherComp, int32 index, bool bFromSweep, const FHitResult& result)
{
}

void ASAC1Character::OverlapEnd(UPrimitiveComponent* comp, AActor* otherActor, 
	UPrimitiveComponent* otherComp, int32 index)
{
}

void ASAC1Character::Move(const FInputActionValue& Value)
{
	FVector movementVector = Value.Get<FVector>();
	if (!m_CanMove || !Controller)
	{
		return;
	}
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector forwardDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(forwardDir, movementVector.X);
	AddMovementInput(rightDir, movementVector.Y);

	//AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	//AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void ASAC1Character::CameraRotation(const FInputActionValue& Value)
{
	float deltaTime = GetWorld()->GetDeltaSeconds();
	m_ScreenRotVec = Value.Get<FVector2D>();
	double x = m_ScreenRotVec.X * deltaTime * m_CameraSpeed;
	double y = m_ScreenRotVec.Y * deltaTime * m_CameraSpeed;
	if (m_IsInvertX)
	{
		x *= -1;
	}
	if (m_IsInvertY)
	{
		y *= -1;
	}
	AddControllerYawInput(x);
	AddControllerPitchInput(y);
}

void ASAC1Character::CameraZoom(const FInputActionValue& Value)
{
	//double length = Value.Get<float>() * -1 * m_ZoomSpeed * GetWorld()->GetDeltaSeconds();
	//m_CameraBoom->TargetArmLength += length;
}

void ASAC1Character::Jump()
{
	Super::Jump();
}

void ASAC1Character::StopJumping()
{
	Super::StopJumping();
}

void ASAC1Character::Sprint()
{
	m_IsSprinting = !m_IsSprinting;
	if (m_IsSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = m_MaxSprintSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = m_MaxWalkSpeed;
	}
}

void ASAC1Character::CollectPickUps()
{
	TArray<FHitResult> results;
	FVector traceStart = GetActorLocation()-GetActorUpVector()* m_PickUpExtent.Z*0.5;
	FVector traceEnd = traceStart + GetActorForwardVector() * m_PickUpExtent.Y;
	FCollisionQueryParams param(NAME_None, false, this);
	bool isCol = GetWorld()->SweepMultiByChannel(results, traceStart, traceEnd, FQuat::Identity,
		ECollisionChannel::ECC_Visibility, FCollisionShape::MakeBox(m_PickUpExtent), param);
		//ECollisionChannel::ECC_GameTraceChannel5, FCollisionShape::MakeBox(m_PickUpExtent), param);
#if ENABLE_DRAW_DEBUG
	FColor drawColor;
	if (isCol)
	{
		drawColor = FColor::Red;
	}
	else
	{
		drawColor = FColor::Green;
	}
	DrawDebugBox(GetWorld(), (traceStart+ traceEnd)*0.5, m_PickUpExtent, drawColor, false, 0.5f);
#endif
	if (isCol)
	{
		for (auto& result : results)
		{
			AActor_PickUp* const pickUP = Cast<AActor_PickUp>(result.GetActor());
			if (IsValid(pickUP) && pickUP->GetActive())
			{
				pickUP->PickedUpBy(this);
				pickUP->SetActive(false);
			}
		}
	}
}

void ASAC1Character::SetCharacterState(ECharacterEquip state)
{
	m_AnimInst->SetCharacterState(state);
}

ECharacterEquip ASAC1Character::GetCharacterState()
{
	return m_AnimInst->GetCharacterState();
}