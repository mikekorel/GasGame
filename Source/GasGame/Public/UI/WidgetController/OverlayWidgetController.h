#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/WidgetControllerBase.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

UCLASS(BlueprintType, Blueprintable)
class GASGAME_API UOverlayWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

protected:
	void HandleOnHealthChanged(const FOnAttributeChangeData& Data) const;
	void HandleOnMaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void HandleOnManaChanged(const FOnAttributeChangeData& Data) const;
	void HandleOnMaxManaChanged(const FOnAttributeChangeData& Data) const;
	
};
