#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HandleOnHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HandleOnMaxHealthChanged);
}

void UOverlayWidgetController::HandleOnHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HandleOnMaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}


