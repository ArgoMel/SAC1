#include "SAC1Character.h"
#include "SAC1Projectile.h"
#include "SAC1PlayerController.h"
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
	m_PickUpRadius = 200.f;
	m_MoveSpeed = 100.f;
	m_CameraSpeed=50.f;
	m_ZoomSpeed = 300.f;
	m_CanMove=true;
	m_IsInvertX = false;
	m_IsInvertY=true;
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	GetMesh()->SetupAttachment(FirstPersonCameraComponent);
	GetMesh()->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	GetMesh()->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BrimStone_SkeletonMesh(TEXT(
		"/Game/KBJ/Brimstone/Anims/BrimStone_SkeletonMesh.BrimStone_SkeletonMesh"));
	if (BrimStone_SkeletonMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(BrimStone_SkeletonMesh.Object);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Mannequin_Arms(TEXT(
		"/Game/FirstPersonArms/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms"));
	if(SK_Mannequin_Arms.Succeeded())
	{
		Mesh1P->SetSkeletalMesh(SK_Mannequin_Arms.Object);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimClass(TEXT(
		"/Game/FirstPersonArms/Animations/FirstPerson_AnimBP.FirstPerson_AnimBP_C"));
	if (AnimClass.Succeeded())
	{
		Mesh1P->SetAnimInstanceClass(AnimClass.Class);
	}
}

void ASAC1Character::BeginPlay()
{
	Super::BeginPlay();
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

void ASAC1Character::CollectPickUps()
{
	TArray<FHitResult> results;
	FVector traceStart = GetActorLocation();
	//FVector traceEnd = GetActorLocation() + GetActorForwardVector() * 60.;
	FCollisionQueryParams param(NAME_None, false, this);
	bool isCol = GetWorld()->SweepMultiByChannel(results, traceStart, traceStart, FQuat::Identity,
		ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(m_PickUpRadius), param);
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
	DrawDebugSphere(GetWorld(), traceStart, m_PickUpRadius, 0, drawColor, false, 0.5f);
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

void ASAC1Character::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ASAC1Character::GetHasRifle()
{
	return bHasRifle;
}