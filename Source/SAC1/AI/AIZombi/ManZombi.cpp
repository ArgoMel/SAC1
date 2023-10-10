// Fill out your copyright notice in the Description page of Project Settings.


#include "ManZombi.h"
#include "../DefaultAIAnimInstance.h"

AManZombi::AManZombi()
{
	PrimaryActorTick.bCanEverTick = true;

	mName = TEXT("ManZombi");

	mBody->SetCapsuleHalfHeight(98.f);
	mBody->SetCapsuleRadius(33.f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Zombi/ManZombi/Ch10_nonPBR.Ch10_nonPBR'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -98.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	//static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT(""));

	//if (AnimAsset.Succeeded())
	//	mMesh->SetAnimInstanceClass(AnimAsset.Class);

}

void AManZombi::BeginPlay()
{
	Super::BeginPlay();
}

void AManZombi::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AManZombi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
