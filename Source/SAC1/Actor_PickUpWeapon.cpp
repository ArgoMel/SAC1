#include "Actor_PickUpWeapon.h"
#include "TP_WeaponComponent.h"
#include "AC_ItemState.h"
#include "SAC1Character.h"

TObjectPtr<UDataTable> AActor_PickUpWeapon::ItemDataTable;

AActor_PickUpWeapon::AActor_PickUpWeapon()
{
	SetReplicateMovement(true);

	m_Name = TEXT("Rifle");

	//��� ���� ui ���
	m_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(m_Collider);

	m_Weapon = CreateDefaultSubobject<UTP_WeaponComponent>(TEXT("WeaponComponent"));
	m_Weapon->SetupAttachment(m_Collider);

	m_WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	m_WeaponMesh->SetupAttachment(m_Weapon);

	m_ItemState = CreateDefaultSubobject<UAC_ItemState>(TEXT("ItemState"));
}

void AActor_PickUpWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetName(m_Name);
}

void AActor_PickUpWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AActor_PickUpWeapon::WasCollected()
{
	Super::WasCollected();
	ASAC1Character* player = Cast<ASAC1Character>(m_PickUpInstigator);
	if(IsValid(player)&& m_ItemState->GetItemData()->ItemKind==EItem::Weapon)
	{
		m_Weapon->SetWeaponData(m_ItemState->GetWeaponData());
		m_Weapon->AttachWeapon(player);
	}
}

void AActor_PickUpWeapon::PickedUpBy(APawn* pawn)
{
	Super::PickedUpBy(pawn);
}

FItemData* AActor_PickUpWeapon::FindItemData(const FName& Name)
{	
	return ItemDataTable->FindRow<FItemData>(Name, TEXT(""));
}

void AActor_PickUpWeapon::LoadItemData()
{
	ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_ItemData.DT_ItemData"));
}

void AActor_PickUpWeapon::SetName(const FName& name)
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
	m_WeaponMesh->SetSkeletalMesh(m_ItemState->GetItemData()->ItemMesh);
	m_WeaponMesh->SetRelativeRotation(m_ItemState->GetItemData()->WeaponRot);
}
