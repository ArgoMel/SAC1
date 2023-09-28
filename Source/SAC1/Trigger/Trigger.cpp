// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"
#include "../Effect/DefaultEffect.h"

// Sets default values
ATrigger::ATrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));

	SetRootComponent(mBody);

	mBody->bVisualizeComponent = true;

	mBody->SetBoxExtent(FVector(100.0, 100.0, 100.0));

	mBody->SetCollisionProfileName(TEXT("ObjectTrigger"));

	mBody->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	mBody->OnComponentBeginOverlap.AddDynamic(this,
		&ATrigger::OverlapBegin);

	mTriggerType = EUserTriggerType::AllObject;
}

void ATrigger::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	switch (mTriggerType)
	{
	case EUserTriggerType::Player:
		mBody->SetCollisionProfileName(TEXT("PlayerTrigger"));
		break;
	case EUserTriggerType::Enemy:
		mBody->SetCollisionProfileName(TEXT("EnemyTrigger"));
		break;
	case EUserTriggerType::AllObject:
		mBody->SetCollisionProfileName(TEXT("ObjectTrigger"));
		break;
	}
}

// Called when the game starts or when spawned
void ATrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrigger::OverlapBegin(UPrimitiveComponent* OverlappedComponent,
	AActor * OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, 
	const FHitResult& SweepResult)
{
	TriggerOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex,
		bFromSweep, SweepResult);

	/*FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ADefaultEffect* Effect = GetWorld()->SpawnActor<ADefaultEffect>(
		SweepResult.ImpactPoint,
		FRotator::ZeroRotator, ActorParam);

	Effect->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ability/Defense/P_Shield_Spawn.P_Shield_Spawn'"));
	Effect->SetAudioAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/Fire1.Fire1'"));*/
}

void ATrigger::TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

