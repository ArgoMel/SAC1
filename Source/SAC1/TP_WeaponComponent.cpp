#include "TP_WeaponComponent.h"
#include "SAC1Character.h"
//#include "SAC1Projectile.h"
#include "SAC1PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

UTP_WeaponComponent::UTP_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
	m_FireRate = 0.1f;
	m_ReloadTime = 1.25f;
	m_DefaultArmo = 30;
	m_CurArmo = m_DefaultArmo;
	m_IsTargeting = false;

	static ConstructorHelpers::FObjectFinder<UCurveFloat>	Curve_HorizontalRecoil(TEXT(
		"/Game/Recoil/Curves/Curve_HorizontalRecoil.Curve_HorizontalRecoil"));
	if (Curve_HorizontalRecoil.Succeeded())
	{
		m_HorizontalCurve= Curve_HorizontalRecoil.Object;
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat>	Curve_VerticalRecoil(TEXT(
		"/Game/Recoil/Curves/Curve_VerticalRecoil.Curve_VerticalRecoil"));
	if (Curve_VerticalRecoil.Succeeded())
	{
		m_VerticalCurve= Curve_VerticalRecoil.Object;
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem>	P_BelicaHitWorld(TEXT(
		"/Game/KBJ/VFX/P_BelicaHitWorld.P_BelicaHitWorld"));
	if (P_BelicaHitWorld.Succeeded())
	{
		m_HitEmitter = P_BelicaHitWorld.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>	MI_Asphalt_2(TEXT(
		"/Game/KBJ/BulletHoleDecals/Instances/Decals/Asphalt/MI_Asphalt_2.MI_Asphalt_2"));
	if (MI_Asphalt_2.Succeeded())
	{
		m_HitDecalMaterial = MI_Asphalt_2.Object;
	}
}

void UTP_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	FOnTimelineFloat recoilXCurve;
	FOnTimelineFloat recoilYCurve;
	recoilXCurve.BindUFunction(this, FName("StartHorizontalRecoil"));
	recoilYCurve.BindUFunction(this, FName("StartVerticalRecoil"));
	if(IsValid(m_HorizontalCurve)&& IsValid(m_VerticalCurve))
	{
		m_RecoilTimeline.AddInterpFloat(m_HorizontalCurve, recoilXCurve);
		m_RecoilTimeline.AddInterpFloat(m_VerticalCurve, recoilYCurve);
	}
}

void UTP_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(m_RecoilTimeline.IsPlaying())
	{
		m_RecoilTimeline.TickTimeline(DeltaTime);
	}
	if (m_RecoilTimeline.IsReversing())
	{
		if (!IsValid(Character))
		{
			return;
		}
		AController* controller = Character->GetController();
		if (!IsValid(controller))
		{
			return;
		}	
		FVector2D vec = Character->GetScreenRotVec();
		if (abs(vec.Y > 0.005) || abs(vec.X > 0.005))
		{
			m_RecoilTimeline.Stop();
			return;
		}
		FRotator newRot = UKismetMathLibrary::RInterpTo(Character->GetControlRotation(),
			m_StartRot, DeltaTime, 4.5f);	
		Character->GetController()->ClientSetRotation(newRot);	
	}
}

void UTP_WeaponComponent::Fire()
{	
	if (!IsValid(Character)|| m_CurArmo <= 0)
	{
		OnStopFire();
		return;
	}
	UWorld* const world = GetWorld();
	AController* controller = Character->GetController();
	if (!IsValid(world)||!IsValid(controller))
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
	if(!m_IsTargeting)
	{
		traceEnd.Y += traceEnd.Y*FMath::RandRange(-0.35f, 0.35f);
		traceEnd.Z += traceEnd.Z*FMath::RandRange(-0.35f,0.35f);
	}
	else
	{
		traceEnd.Y += traceEnd.Y * FMath::RandRange(-0.05f, 0.05f);
		traceEnd.Z += traceEnd.Z * FMath::RandRange(-0.05f, 0.05f);
	}
	bool isCol=world->LineTraceSingleByChannel(hit, traceStart, traceEnd,ECC_Visibility,params);
//#if ENABLE_DRAW_DEBUG
//	DrawDebugLine(world, traceStart, traceEnd, FColor::Green, false, 3.f, 0, 0.5f);
//#endif
	if(isCol)
	{
//#if ENABLE_DRAW_DEBUG
//		DrawDebugBox(world,hit.Location,FVector(15.),FColor::Red,false,3.f,0,3.f);
//#endif
		if(IsValid(m_HitEmitter))
		{
			UGameplayStatics::SpawnEmitterAtLocation(world, m_HitEmitter, hit.Location);
		}		
		if (IsValid(m_HitDecalMaterial))
		{
			UGameplayStatics::SpawnDecalAtLocation(world, m_HitDecalMaterial,
				FVector(15.), hit.Location, hit.ImpactNormal.Rotation(), 10.f);
		}	
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
	if (!IsValid(Character) || m_CurArmo <= 0)
	{
		OnStopFire();
		return;
	}
	m_StartRot = Character->GetControlRotation();
	Fire();
	StartRecoil();
	GetWorld()->GetTimerManager().SetTimer(m_AutoFireHandle, this,
		&UTP_WeaponComponent::Fire, m_FireRate, true);
}

void UTP_WeaponComponent::OnStopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(m_AutoFireHandle);
	ReverseRecoil();
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

void UTP_WeaponComponent::StartHorizontalRecoil(float value)
{
	if (!IsValid(Character)||m_RecoilTimeline.IsReversing())
	{
		return;
	}
	Character->AddControllerYawInput(value);
}

void UTP_WeaponComponent::StartVerticalRecoil(float value)
{
	if (!IsValid(Character) || m_RecoilTimeline.IsReversing())
	{
		return;
	}
	Character->AddControllerPitchInput(value);
}

void UTP_WeaponComponent::StartRecoil()
{
	m_RecoilTimeline.PlayFromStart();
}

void UTP_WeaponComponent::ReverseRecoil()
{
	m_RecoilTimeline.ReverseFromEnd();
}

void UTP_WeaponComponent::StartTargeting()
{
	m_IsTargeting = true;
}

void UTP_WeaponComponent::StopTargeting()
{
	m_IsTargeting = false;
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
		input->BindAction(controller->m_MouseRClick, ETriggerEvent::Started, this, &UTP_WeaponComponent::StartTargeting);
		input->BindAction(controller->m_MouseRClick, ETriggerEvent::Completed, this, &UTP_WeaponComponent::StopTargeting);
		input->BindAction(controller->m_R, ETriggerEvent::Started, this, &UTP_WeaponComponent::OnStartReload);
		//controller->SetNewController();
	}
}