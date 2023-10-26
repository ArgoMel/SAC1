// Fill out your copyright notice in the Description page of Project Settings.


#include "UndeadZombi.h"
#include "../DefaultAIAnimInstance.h"
#include "../AIPawn.h"
#include "../AISpawnPoint.h"
#include "../DefaultAIAnimInstance.h"
#include "../AIState.h"
#include "../../Effect/DecalEffect.h"
#include "../PatrolPoint.h"
#include "../../SAC1Character.h"



AUndeadZombi::AUndeadZombi()
{
	PrimaryActorTick.bCanEverTick = true;

	mName = TEXT("UndeadZombi");

	mBody->SetCapsuleHalfHeight(110.f);
	mBody->SetCapsuleRadius(40.f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Zombi/UndeadZombi/Pumpkinhulk_L_Shaw.Pumpkinhulk_L_Shaw'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -110.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Zombi/AB_UndeadZombi.AB_UndeadZombi_C'"));

	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);
}

void AUndeadZombi::BeginPlay()
{
	Super::BeginPlay();
}

void AUndeadZombi::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AUndeadZombi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUndeadZombi::Attack() 
{
	LOG(TEXT("zombi attack"));

	FAIDataTable* data=mAIState->GetData();

	TArray<FHitResult> results;
	FVector traceStart = GetActorLocation();
	FVector traceEnd = traceStart + GetActorForwardVector() * 300.f;
	FCollisionQueryParams param(NAME_None, false, this);


	FActorSpawnParameters	actorParam;
	actorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ADecalEffect* decal = GetWorld()->SpawnActor<ADecalEffect>(traceStart, FRotator::ZeroRotator, actorParam);
	decal->SetDecalMaterial(mBloodDecal);
	decal->SetLifeSpan(15.f);
	decal->SetDecalSize(FVector(200.f));

	bool isCol = GetWorld()->SweepMultiByChannel(results, traceStart, traceEnd, FQuat::Identity,
		ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(300.f), param);
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
	DrawDebugSphere(GetWorld(), (traceStart + traceEnd) * 0.5, 300.f, 0, drawColor, false, 0.5f);
#endif
	if (isCol)
	{
		for (auto& result : results)
		{
			FDamageEvent	dmgEvent;
			result.GetActor()->TakeDamage(data->AttackPoint, dmgEvent, GetInstigatorController(), this);
		}
	}

	Destroy(); 
}


