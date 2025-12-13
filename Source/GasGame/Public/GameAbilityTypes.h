
#pragma once

#include "GameplayEffectTypes.h"
#include "GameAbilityTypes.generated.h"


class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()
	
	FDamageEffectParams() {}
	
	UPROPERTY()
	TObjectPtr<UObject> WorldContextObject = nullptr;
	
	UPROPERTY()
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetASC;
	
	UPROPERTY()
	float BaseDamage = 0.0f;
	
	UPROPERTY()
	float AbilityLevel = 1.0f;
	
	UPROPERTY()
	FGameplayTag DamageType = FGameplayTag();
	
	UPROPERTY()
	float DebuffChance = 0.0f;
	
	UPROPERTY()
	float DebuffDamage = 0.0f;
	
	UPROPERTY()
	float DebuffFrequency = 0.0f;
	
	UPROPERTY()
	float DebuffDuration = 0.0f;
	
};


USTRUCT(BlueprintType)
struct FMyGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	bool IsBlockedHit() const { return bBlockedHit; }
	bool IsCriticalHit() const { return bCriticalHit; }
	bool IsSuccessfulDebuff() const { return bSuccessfulDebuff; }
	float GetDebuffDamage() const { return DebuffDamage; }
	float GetDebuffDuration() const { return DebuffDuration; }
	float GetDebuffFrequency() const { return DebuffFrequency; }
	TSharedPtr<FGameplayTag> GetDamageType() const { return DamageType; }

	void SetBlockedHit(bool bInBlockedHit) { bBlockedHit = bInBlockedHit; }
	void SetCriticalHit(bool bInCriticalHit) { bCriticalHit = bInCriticalHit; }
	void SetSuccessfulDebuff(bool bInSuccessfulDebuff) { bSuccessfulDebuff = bInSuccessfulDebuff; }
	void SetDebuffDamage(float InDebuffDamage) { DebuffDamage = InDebuffDamage; }
	void SetDebuffDuration(float InDebuffDuration) { DebuffDuration = InDebuffDuration; }
	void SetDebuffFrequency(float InDebuffFrequency) { DebuffFrequency = InDebuffFrequency; }
	void SetDamageType(TSharedPtr<FGameplayTag> InDamageType) { DamageType = InDamageType; }
	
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	// Creates a copy of this context, used to duplicate for later modifications
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
	
	UPROPERTY()
	bool bSuccessfulDebuff = false;
	
	UPROPERTY()
	float DebuffDamage = 0.0f;
	
	UPROPERTY()
	float DebuffDuration = 0.0f;
	
	UPROPERTY()
	float DebuffFrequency = 0.0f;
	
	TSharedPtr<FGameplayTag> DamageType;
};

template<>
struct TStructOpsTypeTraits<FMyGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FMyGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};

