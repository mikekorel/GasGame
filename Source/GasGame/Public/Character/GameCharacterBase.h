#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "GameCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UMainAttributeSet;
class UMainAbilitySystemComponent;

UCLASS(Abstract)
class GASGAME_API AGameCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AGameCharacterBase();

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UMainAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
	virtual FVector GetCombatSocketLocation() override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	UPROPERTY()
	TObjectPtr<UMainAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UMainAttributeSet> AttributeSet;

	/* Dissolve Effects */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() {}
	virtual void InitializeDefaultAttributes() const;
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	void AddCharacterAbilities();

	/* Dissolve Effects */
	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
	
	void Dissolve();


private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
	
};

