#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/WidgetControllerBase.h"
#include "OverlayWidgetController.generated.h"

class UUserWidgetBase;
struct FOnAttributeChangeData;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidgetBase> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);

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

	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	void HandleOnHealthChanged(const FOnAttributeChangeData& Data) const;
	void HandleOnMaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void HandleOnManaChanged(const FOnAttributeChangeData& Data) const;
	void HandleOnMaxManaChanged(const FOnAttributeChangeData& Data) const;

	template<typename T>
	static T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
