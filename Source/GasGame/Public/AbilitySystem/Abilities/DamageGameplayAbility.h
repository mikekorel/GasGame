#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GameplayAbilityBase.h"
#include "DamageGameplayAbility.generated.h"

struct FDamageEffectParams;
struct FTaggedMontage;

UCLASS()
class GASGAME_API UDamageGameplayAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
	
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr) const;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup|Damage", meta = (GameplayTagFilter = "Damage"))
	FGameplayTag DamageType;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup|Damage")
	FScalableFloat Damage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup|Damage")
	float DebuffChance = 20.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup|Damage")
	float DebuffDamage = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup|Damage")
	float DebuffFrequency = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup|Damage")
	float DebuffDuration = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup|Damage")
	float DeathImpulseMagnitude = 60.f;

};
