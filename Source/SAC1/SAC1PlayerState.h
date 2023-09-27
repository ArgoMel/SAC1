// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/PlayerState.h"
#include "SAC1PlayerState.generated.h"

/**
 *
 */
UCLASS()
class SAC1_API ASAC1PlayerState : public APlayerState
{
	GENERATED_BODY()


protected:
	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerJob	mJob;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mAttackPoint;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mArmorPoint;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mHP;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mHPMax;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mMP;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mMPMax;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mLevel;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mExp;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	mGold;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	mMoveSpeed;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	mAttackDistance;

public:
	int32 GetAttackPoint()
	{
		return mAttackPoint;
	}

public:
	bool AddHP(int32 HP)
	{
		mHP += HP;

		if (mHP <= 0)
		{
			mHP = 0;
			return true;
		}

		else if (mHP > mHPMax)
			mHP = mHPMax;

		return false;
	}

public:
	void SetPlayerData(EPlayerJob Job, int32 AttackPoint, int32 ArmorPoint,
		int32 HP, int32 MP, int32 Level, int32 Exp, int32 Gold,
		float MoveSpeed, float AttackDistance);
	void InitPlayerData(EPlayerJob Job);
};
