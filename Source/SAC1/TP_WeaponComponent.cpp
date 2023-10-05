#include "TP_WeaponComponent.h"
#include "SAC1Character.h"
//#include "SAC1Projectile.h"
#include "SAC1PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

UTP_WeaponComponent::UTP_WeaponComponent()
{
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
	m_FireRate = 0.1f;
	m_ReloadTime = 1.25f;
	m_DefaultArmo = 30;
	m_CurArmo = m_DefaultArmo;
}

void UTP_WeaponComponent::Fire()
{	
	if (!IsValid(Character)||m_CurArmo<=0)
	{
		return;
	}

	UWorld* const world = GetWorld();
	AController* controller = Character->GetController();
	if (!IsValid(world)||!IsValid(Character))
	{
		return;
	}

	--m_CurArmo;

	FHitResult hit;
	FVector camLoc;
	FRotator camRot;
	Character->GetController()->GetPlayerViewPoint(camLoc, camRot);
	FCollisionQueryParams params;
	params.AddIgnoredActor(Character);
	FVector traceStart = camLoc;
	FVector traceEnd = traceStart+ camRot.Vector()*10000;
	bool isCol=world->LineTraceSingleByChannel(hit, traceStart, traceEnd,ECC_Visibility,params);
	DrawDebugLine(world, traceStart, traceEnd, FColor::Green, false, 3.f, 0, 0.5f);
	if(isCol)
	{
		DrawDebugBox(world,hit.Location,FVector(15.),FColor::Red,false,3.f,0,3.f);
	}
	
	//const FRotator SpawnRotation = controller->PlayerCameraManager->GetCameraRotation();
	//const FVector SpawnLocation = GetOwner()->GetActorLocation() 
	//	+ SpawnRotation.RotateVector(MuzzleOffset);
	//FActorSpawnParameters ActorSpawnParams;
	//ActorSpawnParams.SpawnCollisionHandlingOverride = 
	//	ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	//world->SpawnActor<ASAC1Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	
	if (IsValid(FireSound))
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}

	if (IsValid(FireAnimation))
	{
		UAnimInstance* animInst = Character->GetMesh1P()->GetAnimInstance();
		if (IsValid(animInst) && !animInst->Montage_IsPlaying(FireAnimation))
		{
			//bool 변수로 팔올리는 애니메이션 스테이트로 전환
			animInst->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UTP_WeaponComponent::OnStartFire()
{
	Fire();
	GetWorld()->GetTimerManager().SetTimer(m_AutoFireHandle, this,
		&UTP_WeaponComponent::Fire, m_FireRate, true);
}

void UTP_WeaponComponent::OnStopFire()
{
	//손 내리는 애니메이션 재생
	//마지막 프레임의 노티파이로 bool 변수 설정
	GetWorld()->GetTimerManager().ClearTimer(m_AutoFireHandle);
}

void UTP_WeaponComponent::OnStartReload()
{
	FTimerHandle reloadHandle;
	GetWorld()->GetTimerManager().SetTimer(reloadHandle, this,
		&UTP_WeaponComponent::Reload, m_ReloadTime, false);
}

void UTP_WeaponComponent::Reload()
{
	m_CurArmo = m_DefaultArmo;
}

void UTP_WeaponComponent::SetAnimAsset(const FString& Path)
{
	FireAnimation = LoadObject<UAnimMontage>(nullptr, *Path);
}

void UTP_WeaponComponent::SetAnimAsset(UAnimMontage* montage)
{
	FireAnimation = montage;
}

void UTP_WeaponComponent::SetAudioAsset(const FString& Path)
{
	FireSound = LoadObject<USoundBase>(nullptr,*Path);
}

void UTP_WeaponComponent::SetAudioAsset(USoundBase* Sound)
{
	FireSound = Sound;
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
	ASAC1PlayerController* controller = Cast<ASAC1PlayerController>(Character->GetController());
	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(controller->InputComponent);
	if (IsValid(input) && IsValid(controller))
	{
		input->BindAction(controller->m_MouseLClick, ETriggerEvent::Started, this, &UTP_WeaponComponent::OnStartFire);
		input->BindAction(controller->m_MouseLClick, ETriggerEvent::Completed, this, &UTP_WeaponComponent::OnStopFire);
		input->BindAction(controller->m_R, ETriggerEvent::Started, this, &UTP_WeaponComponent::OnStartReload);
		//controller->SetNewController();
	}
}