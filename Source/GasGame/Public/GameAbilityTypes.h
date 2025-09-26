
#pragma once

#include "GameplayEffectTypes.h"
#include "GameAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FMyGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	bool IsBlockedHit() const { return bBlockedHit; }
	bool IsCriticalHit() const { return bCriticalHit; }

	void SetBlockedHit(bool bInBlockedHit) { bBlockedHit = bInBlockedHit; }
	void SetCriticalHit(bool bInCriticalHit) { bCriticalHit = bInCriticalHit; }
	
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FMyGameplayEffectContext* Duplicate() const
	{
		FMyGameplayEffectContext* NewContext = new FMyGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

protected:
	UPROPERTY()
	bool bBlockedHit = false;
	
	UPROPERTY()
	bool bCriticalHit = false;
	
};

template<>
struct TStructOpsTypeTraits<FMyGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FMyGameplayEffectContext>
{
	enum
	{
		WithNetSerialize = true,
		WithCopy = true
	};
};

