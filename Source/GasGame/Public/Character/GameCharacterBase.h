#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GameCharacterBase.generated.h"

class UMainAttributeSet;
class UMainAbilitySystemComponent;

UCLASS(Abstract)
class GASGAME_API AGameCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGameCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UMainAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UMainAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UMainAttributeSet> AttributeSet;
	
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() {}

};
