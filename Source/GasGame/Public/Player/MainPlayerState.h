#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

class UMainAbilitySystemComponent;
class UMainAttributeSet;

UCLASS()
class GASGAME_API AMainPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMainPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UMainAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY()
	TObjectPtr<UMainAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UMainAttributeSet> AttributeSet;
	
};
