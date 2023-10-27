// Fill out your copyright notice in the Description page of Project Settings.


#include "SelfdestructZombi.h"
#include "../DefaultAIAnimInstance.h"

ASelfdestructZombi::ASelfdestructZombi()
{

	PrimaryActorTick.bCanEverTick = true;

	//mName = TEXT("selfdestructZombi");

	//mBody->SetCapsuleHalfHeight(85.f);
	//mBody->SetCapsuleRadius(33.f);

	//mHead->SetCapsuleHalfHeight(25.f);
	//mHead->SetCapsuleRadius(22.f);

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Zombi/selfdestructZombi/Parasite_L_Starkie.Parasite_L_Starkie'"));

	//if (MeshAsset.Succeeded())
	//	mMesh->SetSkeletalMesh(MeshAsset.Object);

	//mMesh->SetRelativeLocation(FVector(0.0, 0.0, -85.0));
	//mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	//mHead->SetRelativeLocation(FVector(20.0, 0.0, 90.0));
	//mHead->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	//static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Zombi/AB_SelfdestructionZombi.AB_SelfdestructionZombi_C'"));

	//if (AnimAsset.Succeeded())
	//	mMesh->SetAnimInstanceClass(AnimAsset.Class);




	mName = TEXT("UndeadZombi");

	mBody->SetCapsuleHalfHeight(85.f);
	mBody->SetCapsuleRadius(40.f);

	mHead->SetCapsuleHalfHeight(30.f);
	mHead->SetCapsuleRadius(30.f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Zombi/UndeadZombi/Pumpkinhulk_L_Shaw.Pumpkinhulk_L_Shaw'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -85.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mHead->SetRelativeLocation(FVector(60.0, 0.0, 70.0));
	mHead->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Zombi/AB_UndeadZombi.AB_UndeadZombi_C'"));

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
