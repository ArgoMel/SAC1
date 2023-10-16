#pragma once
#include "GameInfo.h"
#include "GameFramework/Character.h"
#include "SAC1Character.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
struct FInputActionValue;

UCLASS(config=Game)
class ASAC1Character : public ACharacter
{
	GENERATED_BODY()	
public:
	ASAC1Character();
protected:
	virtual void BeginPlay();
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<USpringArmComponent> m_SpringArm;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UCameraComponent> m_Camera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_MaxWalkSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_MaxSprintSpeed;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_IsSprinting;

	TArray<TObjectPtr<class UTP_WeaponComponent>> m_Weapons;
	TArray<TObjectPtr<UMaterialInstanceDynamic>>	m_MaterialArray;
	TObjectPtr<class USAC1AnimInstance>	m_AnimInst;
	FVector2D m_ScreenRotVec;
	FVector m_PickUpExtent;
	ETeam		mTeam;
	float m_CameraSpeed;
	int m_CurWeaponIndex;
	int m_WeaponIndexDir;
	bool m_CanMove;
	bool m_IsInvertX;
	bool m_IsInvertY;
	
protected:
	UFUNCTION()
	virtual void BodyHit(UPrimitiveComponent* comp, AActor* otherActor,
		UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& result);
	UFUNCTION()
	virtual void OverlapBegin(UPrimitiveComponent* comp, AActor* otherActor,
		UPrimitiveComponent* otherComp, int32 index, bool bFromSweep, const FHitResult& result);
	UFUNCTION()
	virtual void OverlapEnd(UPrimitiveComponent* comp, AActor* otherActor,
		UPrimitiveComponent* otherComp, int32 index);

	void Move(const FInputActionValue& Value);
	void CameraRotation(const FInputActionValue& Value);
	void ChangeWeapon(const FInputActionValue& Value);
	void Jump();
	void StopJumping();
	void Sprint();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void CollectPickUps();
public:
	ETeam GetTeam()
	{
		return mTeam;
	}
	void SetTeam(ETeam Team)
	{
		mTeam = Team;
	}

	UFUNCTION(BlueprintCallable, Category = Anim)
	void SetCharacterState(ECharacterEquip state);
	UFUNCTION(BlueprintCallable, Category = Anim)
	ECharacterEquip GetCharacterState();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetCurWeapon();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	UTP_WeaponComponent* GetCurWeapon();

	bool TryAddWeapon(UTP_WeaponComponent* weapon, ECharacterEquip equip);

	FVector2D GetScreenRotVec()	{return m_ScreenRotVec;}
	UCameraComponent* GetFirstPersonCameraComponent() const { return m_Camera; }
};

