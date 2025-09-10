#include "AbilitySystem/Abilities/ProjectileSpellBase.h"

#include "Actor/ProjectileBase.h"
#include "Interaction/CombatInterface.h"

void UProjectileSpellBase::SpawnProjectile()
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)
		return;

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		// todo: Set the projectile rotation 
		
		AProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileBase>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetAvatarActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		// todo: Give the projectile a Gameplay Effect Spec for causing damage 
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}

void UProjectileSpellBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
}
