// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Animation/WidgetAnimation.h"

#include "CameraRig_Rail.h"

#include "Kismet/KismetMathLibrary.h"

#include "UObject/NoExportTypes.h"
#include "GameInfo.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(SAC1, Log, All);

#define	LOG_CALLINFO	(FString(__FUNCTION__) + TEXT("[") + FString::FromInt(__LINE__) + TEXT("]"))

// %s : 문자열을 받아와서 그 문자열로 채워준다.
// %s는 Ftring을 바로 넣어줄 수 없다. 앞에 *을 붙여서 FString이 가지고
// 있는 문자열의 주소를 가지고 오고 그 주소를 넣어주어야 한다.
// %d : 정수를 받아와서 그 정수를 문자열로 만들어서 채워준다.
// %f : 실수를 받아와서 그 정수를 문자열로 만들어서 채워준다.
#define	LOG(Format, ...)	UE_LOG(SAC1, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define	LOGSTRING(str)		UE_LOG(SAC1, Warning, TEXT("%S : %S"), *LOG_CALLINFO, *str)

UENUM(BlueprintType)
enum class ECharacterEquip : uint8
{
	None,
	Rifle,
	Pistrol,
	Knife,
	Granade,
};

UENUM(BlueprintType)
enum class EPlayerJob : uint8
{
	None,
	Knight,
	Archer,
	Magicion
};

UENUM(BlueprintType)
enum class EItem : uint8
{
	Weapon,
	Consumable,
	Interaction,	//안없어지고 상호작용만(예-스위치)	
};

UENUM(BlueprintType)
enum class ETeam : uint8
{
	Team1,
	Team2,
	Team3
};

// FTableRowBase 구조체를 상속받아야 데이터테이블 용 구조체를 만들 수 있다.
USTRUCT(BlueprintType)
struct FPlayerDataTable	:
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerJob	Job;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	AttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	ArmorPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	MPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	AttackDistance;
};

// FTableRowBase 구조체를 상속받아야 데이터테이블 용 구조체를 만들 수 있다.
USTRUCT(BlueprintType)
struct FAIDataTable :
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	AttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	ArmorPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	InteractionDistance;
};

USTRUCT(BlueprintType)
struct FWeaponData :	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Armo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	ArmoMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	BulletCount;	//한번에 발사하는 총알 개수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	AtkRate;	//데미지 비율(플레이어 공격력*this= 최종 공격력)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector	MuzzleOffset;	//총구 위치

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacterEquip	State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ReloadAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> HitEmitter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInstance> HitDecalMaterial;
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItem	ItemKind;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FRotator WeaponRot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMesh> ItemMesh;
};

UCLASS()
class SAC1_API UGameInfo : public UObject
{
	GENERATED_BODY()
};
