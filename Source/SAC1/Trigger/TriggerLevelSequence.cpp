// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerLevelSequence.h"

ATriggerLevelSequence::ATriggerLevelSequence()
{
	PrimaryActorTick.bCanEverTick = true;

	mSequenceActor = nullptr;
}

void ATriggerLevelSequence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATriggerLevelSequence::TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(mSequence))
	{
		if (!IsValid(mSequencePlayer))
		{
			mSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
				GetWorld(), mSequence, mSetting, mSequenceActor);

			mSequencePlayer->OnFinished.AddDynamic(this, &ATriggerLevelSequence::SequenceFinish);
		}
		// 재생시킨다.
		if (!mSequencePlayer->IsPlaying())
			mSequencePlayer->Play();

	}
}

void ATriggerLevelSequence::SequenceFinish()
{
}
