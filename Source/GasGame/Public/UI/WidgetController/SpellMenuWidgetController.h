#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MyGameplayTags.h"
#include "UI/WidgetController/WidgetControllerBase.h"
#include "SpellMenuWidgetController.generated.h"

struct FGameplayTag;


struct FSelectedAbility
{
	FGameplayTag Ability = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSpellGlobeSelectedSignature, bool, bSpendPointsButtonEnabled, bool, bEquipButtonEnabled);

UCLASS(BlueprintType, Blueprintable)
class GASGAME_API USpellMenuWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStatChangedSignature SpellPointsChanged;

	UPROPERTY(BlueprintAssignable)
	FSpellGlobeSelectedSignature SpellGlobeSelectedDelegate;

	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);
	
	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPressed();
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

private:
	int32 CurrentSpellPoints = 0;
	FSelectedAbility SelectedAbility = { MyGameplayTags::Abilities_None, MyGameplayTags::Abilities_Status_Locked };
	
	static void ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bEnableSpellPointsButton, bool& bEnableEquipButton);
	
};
