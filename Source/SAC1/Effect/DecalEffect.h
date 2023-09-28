// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DecalEffect.generated.h"

UCLASS()
class SAC1_API ADecalEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADecalEffect();

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDecalComponent>	mDecal;

	TObjectPtr<UMaterialInstanceDynamic>	mDecalMaterial;

	float	mTime;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool	mFadeEnable;

public:
	void SetFaceEnable(bool Enable)
	{
		mFadeEnable = Enable;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetDecalMaterial(const FString& Path);
};
