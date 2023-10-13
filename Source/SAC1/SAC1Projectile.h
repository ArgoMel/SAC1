#pragma once
#include "GameInfo.h"
#include "GameFramework/Actor.h"
#include "SAC1Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class ASAC1Projectile : public AActor
{
	GENERATED_BODY()
public:
	ASAC1Projectile();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	TObjectPtr<USphereComponent> CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> m_ProjectileMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> m_HitEmitter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInstance> m_HitDecalMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> m_FireSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	float m_Damage;
	float m_ExplosionRadius;
	bool m_HasEndEvent;

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void SetProjectileEndEvent(bool hasEvent)
	{
		m_HasEndEvent = hasEvent;
	}
	void SetProjectileMesh(USkeletalMesh* mesh);
	void SetProjectileParticle(UParticleSystem* particle);
	void SetProjectileDecal(UMaterialInstance* decal);
	void SetProjectileSound(USoundBase* sound);
	void SetProjectileDamage(float damage);

	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	USkeletalMeshComponent* GetProjectileMesh() const { return m_ProjectileMesh; }
};

