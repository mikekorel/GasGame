#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ProjectileSpellBase.h"
#include "FireBoltSpell.generated.h"

UCLASS()
class GASGAME_API UFireBoltSpell : public UProjectileSpellBase
{
	GENERATED_BODY()

public:
	virtual FString GetDescription(int32 Level) const override;
	virtual FString GetNextLevelDescription(int32 Level) const override;
	
};
