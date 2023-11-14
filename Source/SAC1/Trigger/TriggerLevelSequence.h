// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Trigger.h"
#include "TriggerLevelSequence.generated.h"

/**
 * 
 */
UCLASS()
class SAC1_API ATriggerLevelSequence : public ATrigger
{
	GENERATED_BODY()

public:
	ATriggerLevelSequence();

protected:
	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ULevelSequence> mSequence;
//
//
	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FMovieSceneSequencePlaybackSettings mSetting;
//
	TObjectPtr<ULevelSequencePlayer> mSequencePlayer;
	ALevelSequenceActor* mSequenceActor;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



protected:
	virtual void TriggerOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void SequenceFinish();
	
};
