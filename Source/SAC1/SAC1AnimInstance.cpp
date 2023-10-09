#include "SAC1AnimInstance.h"
#include "SAC1Character.h"

USAC1AnimInstance::USAC1AnimInstance()
{
	m_CharState=ECharacterEquip::None;
	m_IsMoving=false;
	m_IsInAir = false;
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
	m_IsMoving = m_Character->GetVelocity().Length()>0;
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
