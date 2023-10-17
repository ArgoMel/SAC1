#include "Actor_PickUpItem.h"
#include "AC_ItemState.h"
#include "SAC1Character.h"
#include "TP_WeaponComponent.h"

TObjectPtr<UDataTable> AActor_PickUpItem::ItemDataTable;

AActor_PickUpItem::AActor_PickUpItem()
{
	SetReplicateMovement(true);

	m_Name = TEXT("Bullet");

	GetStaticMeshComponent()->SetCollisionProfileName(TEXT("NoCollision"));

	m_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	m_Collider->SetupAttachment(GetStaticMeshComponent());
	m_Collider->SetGenerateOverlapEvents(true);
	m_Collider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	m_ItemState = CreateDefaultSubobject<UAC_ItemState>(TEXT("ItemState"));
}

void AActor_PickUpItem::BeginPlay()
{
	Super::BeginPlay();
}

void AActor_PickUpItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetName(m_Name);
}

void AActor_PickUpItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AActor_PickUpItem::WasCollected()
{
	Super::WasCollected();
	SetLifeSpan(1.f);
}

bool AActor_PickUpItem::PickedUpBy(APawn* pawn)
{
	Super::PickedUpBy(pawn);
	ASAC1Character* player = Cast<ASAC1Character>(m_PickUpInstigator);	
	FItemData* data= m_ItemState->GetItemData();
	if(IsValid(player)&& data)
	{
		if(m_Name==FName(TEXT("Bullet"))) 
		{
			UTP_WeaponComponent* weapon= player->GetCurWeapon(); 
			if(IsValid(weapon))
			{
				weapon->PickUpArmo(data->Value);
			}		
		}
		else if (m_Name == FName(TEXT("Battery")))
		{
			UE_LOG(LogTemp, Warning, TEXT("adad"));
		}
	}
	m_IsActive = false;
	return !m_IsActive;
}

FItemData* AActor_PickUpItem::FindItemData(const FName& Name)
{
	return ItemDataTable->FindRow<FItemData>(Name, TEXT(""));
}

void AActor_PickUpItem::LoadItemData()
{
	ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_ItemData.DT_ItemData"));
}

void AActor_PickUpItem::SetName(const FName& name)
{
	Super::SetName(name);
	if (!IsValid(ItemDataTable))
	{
		LoadItemData();
	}
	if (!IsValid(ItemDataTable))
	{
		return;
	}
	FItemData* data = FindItemData(m_Name);
	if (!data)
	{
		return;
	}
	m_ItemState->SetItemInfo(m_Name, data);
	GetStaticMeshComponent()->SetStaticMesh(m_ItemState->GetItemData()->ItemStaticMesh);
}
