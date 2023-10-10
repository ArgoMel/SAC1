#include "Actor_AIPawnVolume.h"
#include "AI/AIPawn.h"

AActor_AIPawnVolume::AActor_AIPawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	if (GetLocalRole() == ROLE_Authority)
	{
		m_SpawnDelayRangeMin = 1.0f;
		m_SpawnDelayRangeMax = 4.5f;
		m_SpawnCountMax = 300;
		m_SpawnCount = 0;

		m_SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
		SetRootComponent(m_SpawnArea);
	}
}

void AActor_AIPawnVolume::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AActor_AIPawnVolume::BeginPlay()
{
	Super::BeginPlay();
	SetSpawningActive(true);
}

void AActor_AIPawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActor_AIPawnVolume::SpawnPickUp()
{
	if (GetLocalRole() == ROLE_Authority && !m_SpawnThings.IsEmpty())
	{
		UWorld* const world = GetWorld();
		if (!IsValid(world))
		{
			return;
		}
		if (m_SpawnCountMax != -1 && m_SpawnCount >= m_SpawnCountMax)
		{
			SetSpawningActive(false);
			return;
		}
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = GetInstigator();
		FVector spawnLoc = GetRandomPointInVolume();
		FRotator spawnRot;
		spawnRot.Yaw = FMath::FRand() * 360.f;
		//spawnRot.Pitch = FMath::FRand() * 360.f;
		//spawnRot.Roll = FMath::FRand() * 360.f;

		int32 randIndex = FMath::Rand() % m_SpawnThings.Num();
		AAIPawn* const spawnedPickUp =
			world->SpawnActor<AAIPawn>(m_SpawnThings[randIndex], spawnLoc, spawnRot, spawnParams);
		SetSpawningActive(true);

		++m_SpawnCount;
	}
}

FVector AActor_AIPawnVolume::GetRandomPointInVolume()
{
	if (!IsValid(m_SpawnArea))
	{
		return FVector();
	}
	FVector spawnOrigin = m_SpawnArea->Bounds.Origin;
	FVector spawnExtent = m_SpawnArea->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnExtent);
}

void AActor_AIPawnVolume::SetSpawningActive(bool isSpawn)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		if (isSpawn)
		{
			m_SpawnDelay = FMath::FRandRange(m_SpawnDelayRangeMin, m_SpawnDelayRangeMax);
			GetWorldTimerManager().SetTimer(m_SpawnTimer, this,
				&AActor_AIPawnVolume::SpawnPickUp, m_SpawnDelay, false);
		}
		else
		{
			GetWorldTimerManager().ClearTimer(m_SpawnTimer);
			m_SpawnCount = 0;
		}
	}
}

