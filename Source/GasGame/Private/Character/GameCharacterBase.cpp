#include "Character/GameCharacterBase.h"

#include "MyGameplayTags.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/Debuff/DebuffNiagaraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GasGame/GasGame.h"
#include "Kismet/GameplayStatics.h"

AGameCharacterBase::AGameCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	BurnDebuffComponent = CreateDefaultSubobject<UDebuffNiagaraComponent>("BurnDebuffComponent");
	BurnDebuffComponent->SetupAttachment(GetRootComponent());
	BurnDebuffComponent->DebuffTag = MyGameplayTags::Debuff_Burn;
}

void AGameCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

UNiagaraSystem* AGameCharacterBase::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

FTaggedMontage AGameCharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (FTaggedMontage TaggedMontage : AttackMontages)
	{
		if (TaggedMontage.MontageTag == MontageTag)
			return TaggedMontage;
	}
	return FTaggedMontage();
}

int32 AGameCharacterBase::GetMinionCount_Implementation()
{
	return MinionCount;
}

void AGameCharacterBase::IncrementMinionCount_Implementation(int32 Amount)
{
	MinionCount += Amount;
}

ECharacterClass AGameCharacterBase::GetCharacterClass_Implementation()
{
	return CharacterClass;
}

FOnASCRegistered& AGameCharacterBase::GetOnASCRegisteredDelegate()
{
	return OnASCRegistered;
}

FOnDeath& AGameCharacterBase::GetOnDeathDelegate()
{
	return OnDeath;
}

void AGameCharacterBase::MulticastHandleDeath_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
	bDead = true;
	OnDeath.Broadcast(this);
}

UAbilitySystemComponent* AGameCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

FVector AGameCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	if (MontageTag.MatchesTagExact(MyGameplayTags::CombatSocket_Weapon) && IsValid(Weapon))
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	
	if (MontageTag.MatchesTagExact(MyGameplayTags::CombatSocket_LeftHand))
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	
	if (MontageTag.MatchesTagExact(MyGameplayTags::CombatSocket_RightHand))
		return GetMesh()->GetSocketLocation(RightHandSocketName);

	if (MontageTag.MatchesTagExact(MyGameplayTags::CombatSocket_Tail))
		return GetMesh()->GetSocketLocation(TailSocketName);

	return FVector::ZeroVector;
}

UAnimMontage* AGameCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

bool AGameCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* AGameCharacterBase::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> AGameCharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

void AGameCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGameCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(AbilitySystemComponent));
	check(GameplayEffectClass);
	
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, AbilitySystemComponent);
}

void AGameCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AGameCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;

	AbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
	AbilitySystemComponent->AddCharacterPassiveAbilities(StartupPassiveAbilities);
}

void AGameCharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		StartDissolveTimeline(DynamicMatInst);
	}

	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		Weapon->SetMaterial(0, DynamicMatInst);
		StartWeaponDissolveTimeline(DynamicMatInst);
	}
}

