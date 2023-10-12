#pragma once
#include "../GameInfo.h"
#include "Components/ActorComponent.h"
#include "AIState.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAC1_API UAIState : public UActorComponent
{
	GENERATED_BODY()
public:
	UAIState();

private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	FString	m_Name;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Data", meta = (AllowPrivateAccess = true))
	FAIDataTable m_Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_AttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_ArmorPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_MPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32	m_Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_InteractionDistance;

public:
	int32 GetAttackPoint()	const
	{
		return m_AttackPoint;
	}

	float GetAttackDistance()
	{
		return m_AttackDistance;
	}

	float GetInteractionDistance()
	{
		return m_InteractionDistance;
	}

public:
	FAIDataTable* GetData();
	void SetInfo(const FString& name, const FAIDataTable* data)
	{
		m_Name = name;
		m_Data = *data;

		m_AttackPoint = data->AttackPoint;
		m_ArmorPoint = data->ArmorPoint;
		m_HP = data->HP;
		m_HPMax = data->HP;
		m_MP = data->MP;
		m_MPMax = data->MP;
		m_Level = data->Level;
		m_Exp = data->Exp;
		m_Gold = data->Gold;
		m_MoveSpeed = data->MoveSpeed;
		m_AttackDistance = data->AttackDistance;
		m_InteractionDistance = data->InteractionDistance;
	}

	bool AddHP(int32 Dmg)
	{
		m_Data.HP -= Dmg;

		if (m_Data.HP <= 0)
		{
			m_Data.HP = 0;
			return true;
		}
		else if (m_Data.HP > m_Data.MaxHP)
		{
			m_Data.HP = m_Data.MaxHP;
		}
		return false;
	}

protected:
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
