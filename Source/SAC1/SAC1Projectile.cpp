#include "SAC1Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ASAC1Projectile::ASAC1Projectile() 
{
	InitialLifeSpan = 5.0f;

	m_Damage = 1.f;
	m_ExplosionRadius = 300.f;
	m_HasEndEvent = false;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ASAC1Projectile::OnHit);		
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	CollisionComp->SetupAttachment(RootComponent);

	m_ProjectileMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ProjectileMesh"));
	m_ProjectileMesh->SetupAttachment(CollisionComp);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 700.f;
	ProjectileMovement->MaxSpeed = 700.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> FirstPersonProjectileMesh(TEXT(
	//	"/Game/FPWeapon/Mesh/FirstPersonProjectileMesh.FirstPersonProjectileMesh"));
	//if (FirstPersonProjectileMesh.Succeeded())
	//{
	//	m_StaticMesh->SetStaticMesh(FirstPersonProjectileMesh.Object);
	//}
}

void ASAC1Projectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if(!m_HasEndEvent)
	{
		return;
	}

	TArray<FHitResult> results;
	FVector traceStart = GetActorLocation();
	FVector traceEnd = traceStart + GetActorForwardVector() * m_ExplosionRadius;
	FCollisionQueryParams param(NAME_None, false, this);

	if (IsValid(m_HitEmitter))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_HitEmitter, traceStart);
	}
	if (IsValid(m_HitDecalMaterial))
	{
		UGameplayStatics::SpawnDecalAtLocation(GetWorld(), m_HitDecalMaterial,
			FVector(15.), traceStart, FRotator::ZeroRotator, 10.f);
	}

	bool isCol = GetWorld()->SweepMultiByChannel(results, traceStart, traceEnd, FQuat::Identity,
		ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(m_ExplosionRadius), param);
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
	DrawDebugSphere(GetWorld(), (traceStart + traceEnd) * 0.5, m_ExplosionRadius,0, drawColor, false, 0.5f);
#endif
	if (isCol)
	{
		for (auto& result : results)
		{
			FDamageEvent	dmgEvent;
			result.GetActor()->TakeDamage(m_Damage, dmgEvent, GetInstigatorController(), this);
		}
	}
}

void ASAC1Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}
}

void ASAC1Projectile::SetProjectileMesh(USkeletalMesh* mesh)
{
	m_ProjectileMesh->SetSkeletalMeshAsset(mesh);
}

void ASAC1Projectile::SetProjectileParticle(UParticleSystem* particle)
{
	m_HitEmitter = particle;
}

void ASAC1Projectile::SetProjectileDecal(UMaterialInstance* decal)
{
	m_HitDecalMaterial = decal;
}

void ASAC1Projectile::SetProjectileSound(USoundBase* sound)
{
	m_FireSound = sound;
}

void ASAC1Projectile::SetProjectileDamage(float damage)
{
	m_Damage = damage;
}
