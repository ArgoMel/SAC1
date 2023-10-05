#include "Actor_PickUpWeapon.h"
#include "TP_WeaponComponent.h"
#include "SAC1Character.h"

AActor_PickUpWeapon::AActor_PickUpWeapon()
{
	SetReplicateMovement(true);

	//닿는 순간 ui 출력
	m_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(m_Collider);

	m_Weapon = CreateDefaultSubobject<UTP_WeaponComponent>(TEXT("Weapon"));
	m_Weapon->SetupAttachment(m_Collider);
	m_Weapon->SetAudioAsset(TEXT(
		"/Game/FPWeapon/Audio/FirstPersonTemplateWeaponFire02.FirstPersonTemplateWeaponFire02"));
	m_Weapon->SetAnimAsset(TEXT(
		"/Game/FirstPersonArms/Animations/FP_Rifle_Shoot_Montage.FP_Rifle_Shoot_Montage"));

	m_WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	m_WeaponMesh->SetupAttachment(m_Weapon);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_FPGun(TEXT(
		"/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun"));
	if (SK_FPGun.Succeeded())
	{
		m_WeaponMesh->SetSkeletalMesh(SK_FPGun.Object);
	}
}

void AActor_PickUpWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AActor_PickUpWeapon::WasCollected()
{
	Super::WasCollected();
	ASAC1Character* player = Cast<ASAC1Character>(m_PickUpInstigator);
	if(IsValid(player))
	{
		m_Weapon->AttachWeapon(player);
	}
}

void AActor_PickUpWeapon::PickedUpBy(APawn* pawn)
{
	Super::PickedUpBy(pawn);
}
