#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "GameAbilitySystemGlobals.generated.h"

UCLASS()
class GASGAME_API UGameAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	
};
