#pragma once
#include "GameInfo.h"
#include "GameFramework/Actor.h"
#include "Actor_AIPawnVolume.generated.h"

UCLASS()
class SAC1_API AActor_AIPawnVolume : public AActor
{
	GENERATED_BODY()
public:	
	AActor_AIPawnVolume();
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Spawn", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UBoxComponent> m_SpawnArea;

protected:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<TSubclassOf<class AAIPawn>> m_SpawnThings;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn")
	float m_SpawnDelayRangeMin;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn")
	float m_SpawnDelayRangeMax;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn")
	float m_SpawnCountMax;

	FTimerHandle m_SpawnTimer;
	float m_SpawnDelay;
	float m_SpawnCount;

private:
	void SpawnPickUp();

public:
	FORCEINLINE class UBoxComponent* GetSpawnArea() const { return m_SpawnArea; }

	UFUNCTION(BlueprintPure, Category = "Spawn")
	FVector GetRandomPointInVolume();
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SetSpawningActive(bool isSpawn);
};
