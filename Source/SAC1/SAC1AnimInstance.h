#pragma once
#include "GameInfo.h"
#include "Animation/AnimInstance.h"
#include "SAC1AnimInstance.generated.h"

UCLASS()
class SAC1_API USAC1AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	USAC1AnimInstance();
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	virtual void NativePostEvaluateAnimation();
	virtual void NativeUninitializeAnimation();
	virtual void NativeBeginPlay();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage>	m_GrabItem;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage>	m_EquipChange;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage>	m_DamagedMontage;
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anim", meta = (AllowPrivateAccess = true))
	//TObjectPtr<UAnimMontage>	m_DeadMontage;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Anim", meta = (AllowPrivateAccess = true))
	TObjectPtr<class ASAC1Character> m_Character;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Anim", meta = (AllowPrivateAccess = true))
	ECharacterEquip m_CharState;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Anim", meta = (AllowPrivateAccess = true))
	float m_Speed;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Anim", meta = (AllowPrivateAccess = true))
	bool m_IsInAir;

public:
	void SetCharacterState(ECharacterEquip state)
	{
		m_CharState = state;
	}
	ECharacterEquip GetCharacterState()
	{
		return m_CharState;
	}

	void CollectPickUps();
	void ChangeWeapon();
	void HitReaction();

	//UFUNCTION()
	//void AnimNotify_TransitionFall();
};
