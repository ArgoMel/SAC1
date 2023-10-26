// Fill out your copyright notice in the Description page of Project Settings.


#include "UndeadZombi.h"
#include "../DefaultAIAnimInstance.h"
#include "../AIPawn.h"
#include "../AISpawnPoint.h"
#include "../DefaultAIAnimInstance.h"
#include "../AIState.h"
#include "../../Effect/DecalEffect.h"
#include "../PatrolPoint.h"
#include "../../SAC1Character.h"



AUndeadZombi::AUndeadZombi()
{
	PrimaryActorTick.bCanEverTick = true;

	mName = TEXT("UndeadZombi");

	mBody->SetCapsuleHalfHeight(110.f);
	mBody->SetCapsuleRadius(40.f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Zombi/UndeadZombi/Pumpkinhulk_L_Shaw.Pumpkinhulk_L_Shaw'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -110.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Zombi/AB_UndeadZombi.AB_UndeadZombi_C'"));

	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);
}

void AUndeadZombi::BeginPlay()
{
	Super::BeginPlay();
}

void AUndeadZombi::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AUndeadZombi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUndeadZombi::ZombiAttack()
{
	LOG(TEXT("zombi attack"));

	FHitResult	result;


	
	FVector	Start = GetActorLocation();


	FVector	End = Start + GetActorForwardVector() * 1000.f;

	FCollisionQueryParams	param(NAME_None, false, this);

	bool Collision = GetWorld()->SweepSingleByChannel(result,
		Start, End, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(1000.f), param);

	// ����� ��(������)���� ����Ѵ�.
#if ENABLE_DRAW_DEBUG

	// Collision ���� ���� true�� ��� red, false�� ��� green����
	// ����Ѵ�.
	FColor	DrawColor = Collision ? FColor::Red : FColor::Green;

	// FRotationMatrix::MakeFromZ(GetActorForwardVector()) : Z���� ĳ����
	// �� �������� ������ִ� ȸ�� ����� ���Ѵ�.(FMatrix�� ����� ���´�)
	// �׷��� .ToQuat() �� �̿��ؼ� FQuat(ȸ����)���� ��ȯ�Ѵ�.
	DrawDebugCapsule(GetWorld(), (Start + End) / 2.f, 100.f,
		50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 1.f);

#endif

	if (Collision)
	{
		FActorSpawnParameters	ActorParam;
		ActorParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//ADefaultEffect* Effect = GetWorld()->SpawnActor<ADefaultEffect>(
		//	result.ImpactPoint,
		//	FRotator::ZeroRotator, ActorParam);

		FHitResult	LineResult;

		FCollisionQueryParams	param1(NAME_None, false, this);

		bool LineCollision = GetWorld()->LineTraceSingleByChannel(LineResult,
			result.ImpactPoint,
			result.ImpactPoint - FVector(0.0, 0.0, 200.0),
			ECollisionChannel::ECC_GameTraceChannel8, param1);

		//if (LineCollision)
		//{
		//	//ADecalEffect* Decal = GetWorld()->SpawnActor<ADecalEffect>(
		//	//	LineResult.ImpactPoint,
		//	//	FRotator::ZeroRotator, ActorParam);

		//	//Decal->SetDecalMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/ZombiDecal/RE/MIBloodDecalRE.MIBloodDecalRE'"));
		//	//// ������ �����ֱ⸦ �����Ѵ�. 5.f�� �����ϸ� �����ǰ� 5�� �ڿ� ���ŵȴ�.
		//	//Decal->SetLifeSpan(5.f);
		//}


		//���ط� ����
		float	Dmg = 0.f;

		if (IsValid(mAIState))
			Dmg = (float)mAIState->GetData()->AttackPoint;

		//�����̺�Ʈ ����
		FDamageEvent	DmgEvent;
		result.GetActor()->TakeDamage(Dmg, DmgEvent, GetController(),
			this);
	}
}


