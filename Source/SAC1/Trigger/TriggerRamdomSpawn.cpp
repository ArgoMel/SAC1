#include "TriggerRamdomSpawn.h"
#include "../Actor_SpawnVolume.h"

ATriggerRamdomSpawn::ATriggerRamdomSpawn()
{
	m_DestroyWhenTrigger = true;
}

void ATriggerRamdomSpawn::TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(m_SpawnVolume))
	{
		m_SpawnVolume->SetSpawningActive(true);
	}
	if(m_DestroyWhenTrigger)
	{
		Destroy();
	}
}
