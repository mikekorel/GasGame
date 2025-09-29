#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GameplayAbilityBase.h"
#include "DamageGameplayAbility.generated.h"

UCLASS()
class GASGAME_API UDamageGameplayAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
	
};
