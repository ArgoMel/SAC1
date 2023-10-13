#pragma once
#include "GameInfo.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class ASAC1Character;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAC1_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:
	UTP_WeaponComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction) override;

private:
	TObjectPtr<ASAC1Character> Character;
	FTimerHandle m_AutoFireHandle;
	FTimeline m_RecoilTimeline;
	FRotator m_StartRot;
	bool m_IsTargeting;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class ASAC1Projectile> m_ProjectileClass;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Recoil|Curves")
	TObjectPtr<UCurveFloat> m_HorizontalCurve;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Recoil|Curves")
	TObjectPtr<UCurveFloat> m_VerticalCurve;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Recoil|Data", meta = (AllowPrivateAccess = true))
	FWeaponData m_WeaponData;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Recoil|Data", meta = (AllowPrivateAccess = true))
	int32 m_CurArmo;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Recoil|Data", meta = (AllowPrivateAccess = true))
	int32 m_TotalArmo;

private:
	void OnStartFire();
	void OnStopFire();
	void OnStartReload();
	void Reload();

	UFUNCTION()
	void StartHorizontalRecoil(float value);
	UFUNCTION()
	void StartVerticalRecoil(float value);
	void StartRecoil();
	void ReverseRecoil();
	void StartTargeting();
	void StopTargeting();

public:
	void SetWeaponData(FWeaponData* data);

	UFUNCTION(BlueprintCallable, Category="Weapon")
	bool TryAttachWeapon(ASAC1Character* TargetCharacter);
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachWeapon();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void MeleeAttack();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ThrowThing();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EatFood();

	void PickUpArmo(float value);
};