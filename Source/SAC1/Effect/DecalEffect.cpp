// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalEffect.h"

// Sets default values
ADecalEffect::ADecalEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));

	SetRootComponent(mDecal);

	mDecal->bVisualizeComponent = true;

	mDecal->DecalSize = FVector(128.0, 256.0, 256.0);
	mDecal->SetRelativeRotation(FRotator(-90.0, 0.0, 0.0));

	mTime = 0.f;

	mFadeEnable = true;
}

// Called when the game starts or when spawned
void ADecalEffect::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADecalEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mFadeEnable && IsValid(mDecalMaterial))
	{
		mTime += DeltaTime;

		float	Opacity = 1.f - mTime / InitialLifeSpan;

		mDecalMaterial->SetScalarParameterValue(TEXT("Opacity"), Opacity);
	}
}

void ADecalEffect::SetDecalMaterial(const FString& Path)
{
	UMaterialInterface* Material = LoadObject<UMaterialInterface>(this, *Path);

	if (IsValid(Material))
	{
		mDecal->SetDecalMaterial(Material);

		mDecalMaterial = mDecal->CreateDynamicMaterialInstance();
	}
}

