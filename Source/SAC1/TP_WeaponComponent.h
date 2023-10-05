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

private:
	ASAC1Character* Character;
	FTimerHandle m_AutoFireHandle;
	int32 m_CurArmo;
	int32 m_DefaultArmo;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float m_FireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float m_ReloadTime;

public:
	/** Projectile class to spawn */
	//UPROPERTY(EditDefaultsOnly, Category=Projectile)
	//TSubclassOf<class ASAC1Projectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

private:
	void OnStartFire();
	void OnStopFire();
	void OnStartReload();
	void Reload();

public:
	void SetAnimAsset(const FString& Path);
	void SetAnimAsset(UAnimMontage* montage);
	void SetAudioAsset(const FString& Path);
	void SetAudioAsset(USoundBase* Sound);

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(ASAC1Character* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();
};
