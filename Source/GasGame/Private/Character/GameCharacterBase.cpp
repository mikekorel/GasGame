#include "Character/GameCharacterBase.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"

AGameCharacterBase::AGameCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AGameCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGameCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
