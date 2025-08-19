#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/WidgetControllerBase.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

UCLASS(BlueprintType, Blueprintable)
class GASGAME_API UOverlayWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

protected:
	void HandleOnHealthChanged(const FOnAttributeChangeData& Data) const;
	void HandleOnMaxHealthChanged(const FOnAttributeChangeData& Data) const;
	
};
