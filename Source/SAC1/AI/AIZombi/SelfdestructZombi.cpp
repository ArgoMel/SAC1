// Fill out your copyright notice in the Description page of Project Settings.


#include "SelfdestructZombi.h"
#include "../DefaultAIAnimInstance.h"

ASelfdestructZombi::ASelfdestructZombi()
{

	PrimaryActorTick.bCanEverTick = true;

	mName = TEXT("selfdestructZombi");

	mBody->SetCapsuleHalfHeight(110.f);
	mBody->SetCapsuleRadius(33.f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Zombi/selfdestructZombi/Parasite_L_Starkie.Parasite_L_Starkie'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -110.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));


	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);

}

void ASelfdestructZombi::BeginPlay()
{
	Super::BeginPlay();
}

void ASelfdestructZombi::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASelfdestructZombi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
