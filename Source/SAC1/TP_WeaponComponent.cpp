#include "TP_WeaponComponent.h"
#include "SAC1Character.h"
#include "SAC1Projectile.h"
#include "SACPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

UTP_WeaponComponent::UTP_WeaponComponent()
{
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
	ProjectileClass = ASAC1Projectile::StaticClass();
	m_FireRate = 0.1f;
}

void UTP_WeaponComponent::Fire()
{
	if (!IsValid(Character) || !Character->GetController()|| m_FireTimer.IsValid())
	{
		return;
	}

	if (IsValid(ProjectileClass))
	{
		UWorld* const world = GetWorld();
		if (IsValid(world))
		{
			world->GetTimerManager().SetTimer(m_FireTimer, this, &UTP_WeaponComponent::FireReady, m_FireRate, false);

			ASACPlayerController* controller = Cast<ASACPlayerController>(Character->GetController());
			const FRotator SpawnRotation = controller->PlayerCameraManager->GetCameraRotation();
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = 
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			world->SpawnActor<ASAC1Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
	
	// Try and play the sound if specified
	if (IsValid(FireSound))
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
}

void UTP_WeaponComponent::FireStart()
{
	if (IsValid(FireAnimation))
	{
		UAnimInstance* animInst = Character->GetMesh1P()->GetAnimInstance();
		if (IsValid(animInst)&& !animInst->Montage_IsPlaying(FireAnimation))
		{
			//bool 변수로 팔올리는 애니메이션 스테이트로 전환
			animInst->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UTP_WeaponComponent::FireStop()
{
	//손 내리는 애니메이션 재생
	//마지막 프레임의 노티파이로 bool 변수 설정
}

void UTP_WeaponComponent::FireReady()
{
	GetWorld()->GetTimerManager().ClearTimer(m_FireTimer);
}

void UTP_WeaponComponent::AttachWeapon(ASAC1Character* TargetCharacter)
{
	Character = TargetCharacter;
	if (!IsValid(Character))
	{
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);

	// Set up action bindings
	ASACPlayerController* controller = Cast<ASACPlayerController>(Character->GetController());
	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(controller->InputComponent);
	if (IsValid(input) && IsValid(controller))
	{
		input->BindAction(controller->m_MouseLClick, ETriggerEvent::Started, this, &UTP_WeaponComponent::FireStart);
		input->BindAction(controller->m_MouseLClick, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
		input->BindAction(controller->m_MouseLClick, ETriggerEvent::Completed, this, &UTP_WeaponComponent::FireStop);
		//controller->SetNewController();
	}
}