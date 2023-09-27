#include "SAC1Character.h"
#include "SAC1Projectile.h"
#include "SACPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

ASAC1Character::ASAC1Character()
{
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

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void ASAC1Character::BeginPlay()
{
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////// Input

void ASAC1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	ASACPlayerController* controller = Cast<ASACPlayerController>(Controller);
	if (IsValid(input) && IsValid(controller))
	{
		input->BindAction(controller->m_MouseLClick, ETriggerEvent::Started, this, &ASAC1Character::Attack);
		input->BindAction(controller->m_MousePos, ETriggerEvent::Triggered, this, &ASAC1Character::CameraRotation);
		input->BindAction(controller->m_MouseWheel, ETriggerEvent::Triggered, this, &ASAC1Character::CameraZoom);
		input->BindAction(controller->m_Space, ETriggerEvent::Started, this, &ASAC1Character::Jump);
		input->BindAction(controller->m_Space, ETriggerEvent::Completed, this, &ASAC1Character::StopJumping);
		input->BindAction(controller->m_E, ETriggerEvent::Started, this, &ASAC1Character::CollectPickUps);
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

void ASAC1Character::Attack(const FInputActionValue& Value)
{
}

void ASAC1Character::CameraRotation(const FInputActionValue& Value)
{
	float deltaTime = GetWorld()->GetDeltaSeconds();
	double x = Value.Get<FVector2D>().X * deltaTime * m_CameraSpeed;
	double y = Value.Get<FVector2D>().Y * deltaTime * m_CameraSpeed;
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
}

void ASAC1Character::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ASAC1Character::GetHasRifle()
{
	return bHasRifle;
}