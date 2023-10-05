#pragma once
#include "GameInfo.h"
#include "Actor_PickUp.h"
#include "Actor_PickUpWeapon.generated.h"

UCLASS()
class SAC1_API AActor_PickUpWeapon : public AActor_PickUp
{
	GENERATED_BODY()
public:
	AActor_PickUpWeapon();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void WasCollected() override;
	void PickedUpBy(APawn* pawn) override;

protected:
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Power", 
	//	meta = (AllowPrivateAccess = true))
	//float m_BatteryPower;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pickup")
	TObjectPtr<USphereComponent> m_Collider;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pickup")
	TObjectPtr<class UTP_WeaponComponent> m_Weapon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pickup")
	TObjectPtr<class USkeletalMeshComponent> m_WeaponMesh;
};
