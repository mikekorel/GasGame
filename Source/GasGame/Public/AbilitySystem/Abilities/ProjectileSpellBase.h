#pragma once

#include "CoreMinimal.h"
#include "DamageGameplayAbility.h"
#include "AbilitySystem/Abilities/GameplayAbilityBase.h"
#include "ProjectileSpellBase.generated.h"

class AProjectileBase;

UCLASS()
class GASGAME_API UProjectileSpellBase : public UDamageGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxNumProjectiles = 5;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch = false, float PitchOverride = 0.f);
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
