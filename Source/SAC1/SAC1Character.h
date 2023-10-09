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
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;


	TArray<TObjectPtr<UMaterialInstanceDynamic>>	m_MaterialArray;
	TObjectPtr<class USAC1AnimInstance>	m_AnimInst;
	FVector2D m_ScreenRotVec;
	FVector m_ClimbLoc;
	FRotator m_ClimRot;
	ETeam		mTeam;
	float m_PickUpRadius;
	float m_MoveSpeed;
	float m_CameraSpeed;
	float m_ZoomSpeed;
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
	void CameraZoom(const FInputActionValue& Value);
	void Jump();
	void StopJumping();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void CollectPickUps();
public:
	FVector2D GetScreenRotVec()
	{
		return m_ScreenRotVec;
	}
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

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};

