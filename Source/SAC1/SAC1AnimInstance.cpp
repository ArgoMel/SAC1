#include "SAC1AnimInstance.h"
#include "SAC1Character.h"

USAC1AnimInstance::USAC1AnimInstance()
{
	m_CharState=ECharacterEquip::None;
	m_Speed =0.f;
	m_IsInAir = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Picking(TEXT(
		"/Game/AnimStarterPack/ECT/AM_Picking.AM_Picking"));
	if (AM_Picking.Succeeded())
	{
		m_GrabItem=AM_Picking.Object;
	}
}

void USAC1AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	ASAC1Character* player = Cast<ASAC1Character>(TryGetPawnOwner());
	if(IsValid(player))
	{
		m_Character = player;
	}
}

void USAC1AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(!IsValid(m_Character))
	{
		return;
	}
	m_IsInAir = m_Character->GetMovementComponent()->IsFalling();
	m_Speed = m_Character->GetVelocity().Length();
}

void USAC1AnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void USAC1AnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void USAC1AnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void USAC1AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void USAC1AnimInstance::CollectPickUps()
{
	if (!IsValid(m_GrabItem))
	{
		return;
	}
	if (!Montage_IsPlaying(m_GrabItem))
	{
		Montage_Play(m_GrabItem, 2.f);
	}
}
