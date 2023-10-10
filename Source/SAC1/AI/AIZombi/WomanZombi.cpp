// Fill out your copyright notice in the Description page of Project Settings.


#include "WomanZombi.h"

AWomanZombi::AWomanZombi()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Zombi/WomanZombi/Zombiegirl_W_Kurniawan.Zombiegirl_W_Kurniawan'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);
}

void AWomanZombi::BeginPlay()
{
	Super::BeginPlay();
}

void AWomanZombi::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AWomanZombi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
