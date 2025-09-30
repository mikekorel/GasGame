#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MainAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class UMainAbilitySystemComponent;

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	
	UPROPERTY()
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UMainAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	UMainAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;

};

UCLASS()
class GASGAME_API UMainAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	/*
	 * Primary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Resilience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Vigor);

	/*
	 * Secondary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, ArmorPenetration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, BlockChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CritHitChance;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, CritHitChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CritHitDamage;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, CritHitDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CritHitResistance;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, CritHitResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegen, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, HealthRegen);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegen, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegen;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, ManaRegen);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, MaxMana);

	/*
	 * Resistance Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireResistance, Category = "Resistance Attributes")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, FireResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningResistance, Category = "Resistance Attributes")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, LightningResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArcaneResistance, Category = "Resistance Attributes")
	FGameplayAttributeData ArcaneResistance;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, ArcaneResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category = "Resistance Attributes")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, PhysicalResistance);
	

	/*
	 * Vital Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, Mana);

	/*
	 * Meta Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UMainAttributeSet, IncomingDamage);
	

	UMainAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UFUNCTION()
	void OnRep_CritHitChance(const FGameplayAttributeData& OldCritHitChance) const;

	UFUNCTION()
	void OnRep_CritHitDamage(const FGameplayAttributeData& OldCritHitDamage) const;

	UFUNCTION()
	void OnRep_CritHitResistance(const FGameplayAttributeData& OldCritHitResistance) const;

	UFUNCTION()
	void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const;

	UFUNCTION()
	void OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const;

	UFUNCTION()
	void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const;

	UFUNCTION()
	void OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const;

	UFUNCTION()
	void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const;

private:
	static void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
	void ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const;
	
};
