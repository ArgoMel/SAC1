#include "Actor_SpawnVolume.h"
#include "Actor_PickUp.h"

AActor_SpawnVolume::AActor_SpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	//if(GetLocalRole()==ROLE_Authority)
	//{
		m_SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
		SetRootComponent(m_SpawnArea);
		m_SpawnDelayRangeMin = 1.0f;
		m_SpawnDelayRangeMax = 4.5f;
	//}
}

void AActor_SpawnVolume::BeginPlay()
{
	Super::BeginPlay();
}

void AActor_SpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActor_SpawnVolume::SpawnPickUp()
{
	//if(GetLocalRole()==ROLE_Authority&&IsValid(m_SpawnThing))
	//{
		UWorld* const world = GetWorld();
		if(IsValid(world))
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = GetInstigator();
			FVector spawnLoc = GetRandomPointInVolume();
			FRotator spawnRot;
			spawnRot.Yaw = FMath::FRand() * 360.f;
			spawnRot.Pitch = FMath::FRand() * 360.f;
			spawnRot.Roll = FMath::FRand() * 360.f;

			AActor_PickUp* const spawnedPickUp = 
				world->SpawnActor<AActor_PickUp>(m_SpawnThing,spawnLoc,spawnRot,spawnParams);
			SetSpawningActive(true);
		}
	//}
}

FVector AActor_SpawnVolume::GetRandomPointInVolume()
{
	if(!IsValid(m_SpawnArea))
	{
		return FVector();
	}
	FVector spawnOrigin = m_SpawnArea->Bounds.Origin;
	FVector spawnExtent = m_SpawnArea->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnExtent);
}

void AActor_SpawnVolume::SetSpawningActive(bool isSpawn)
{
	//if(GetLocalRole()==ROLE_Authority)
	//{
		if(isSpawn)
		{
			m_SpawnDelay = FMath::FRandRange(m_SpawnDelayRangeMin, m_SpawnDelayRangeMax);
			GetWorldTimerManager().SetTimer(m_SpawnTimer, this, &AActor_SpawnVolume::SpawnPickUp, m_SpawnDelay, false);
		}
		else
		{
			GetWorldTimerManager().ClearTimer(m_SpawnTimer);
		}
	//}
}

