// Fill out your copyright notice in the Description page of Project Settings.


#include "SAC1PlayerState.h"
#include "SAC1GameInstance.h"

void ASAC1PlayerState::SetPlayerData(EPlayerJob Job, int32 AttackPoint, 
	int32 ArmorPoint, int32 HP, int32 MP, int32 Level, int32 Exp, int32 Gold, 
	float MoveSpeed, float AttackDistance)
{
	mJob = Job;
	mAttackPoint = AttackPoint;
	mArmorPoint = ArmorPoint;
	mHP = HP;
	mHPMax = HP;
	mMP = MP;
	mMPMax = MP;
	mLevel = Level;
	mExp = Exp;
	mGold = Gold;
	mMoveSpeed = MoveSpeed;
	mAttackDistance = AttackDistance;
}

void ASAC1PlayerState::InitPlayerData(EPlayerJob Job)
{
	// GameInstance를 얻어온다.
	auto GameInst = GetWorld()->GetGameInstance<USAC1GameInstance>();

	if (IsValid(GameInst))
	{
		FName	TableName;

		switch (Job)
		{
		case EPlayerJob::Knight:
			TableName = TEXT("Knight");
			break;
		case EPlayerJob::Archer:
			TableName = TEXT("Archer");
			break;
		case EPlayerJob::Magicion:
			TableName = TEXT("Magicion");
			break;
		}
		
		// 위에서 구한 행이름으로 탐색하여 플레이어 정보를 얻어온다.
		const FPlayerDataTable* Data = GameInst->FindPlayerData(TableName);

		mJob = Job;
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
	}
}
