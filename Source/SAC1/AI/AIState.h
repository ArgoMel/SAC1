// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ActorComponent.h"
#include "AIState.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAC1_API UAIState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIState();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString	mName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mAttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mArmorPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mHPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mMPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	mMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	mAttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	mInteractionDistance;

public:
	int32 GetAttackPoint()	const
	{
		return mAttackPoint;
	}

	float GetAttackDistance()
	{
		return mAttackDistance;
	}

	float GetInteractionDistance()
	{
		return mInteractionDistance;
	}

public:
	void SetInfo(const FString& Name, const FAIDataTable* Data)
	{
		mName = Name;

		mAttackPoint = Data->AttackPoint;
		mArmorPoint = Data->ArmorPoint;
		mHP = Data->HP;
		mHPMax = Data->HP;
		mMP = Data->MP;
		mMPMax = Data->MP;
		mLevel = Data->Level;
		mExp = Data->Exp;
		mGold = Data->Gold;
		mMoveSpeed = Data->MoveSpeed;
		mAttackDistance = Data->AttackDistance;
		mInteractionDistance = Data->InteractionDistance;
	}

	bool AddHP(int32 Dmg)
	{
		mHP -= Dmg;

		if (mHP <= 0)
		{
			mHP = 0;
			return true;
		}

		else if (mHP > mHPMax)
			mHP = mHPMax;

		return false;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
