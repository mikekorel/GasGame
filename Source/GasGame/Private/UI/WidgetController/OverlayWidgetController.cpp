#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HandleOnHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HandleOnMaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::HandleOnManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::HandleOnMaxManaChanged);
}

void UOverlayWidgetController::HandleOnHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HandleOnMaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HandleOnManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HandleOnMaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}


