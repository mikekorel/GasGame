#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Player/MainPlayerState.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	check(AttributeInfo);
	for (FGameAttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Info.Attribute).AddLambda(
			[this, Info](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Info.AttributeTag);
			}
		);
	}

	PlayerState->OnAttributePointsChangedDelegate.AddLambda([this](int32 Points)
	{
		AttributePointsChangedDelegate.Broadcast(Points);
	});
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	check(AttributeInfo)
	for (FGameAttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		BroadcastAttributeInfo(Info.AttributeTag);
	}
	
	AttributePointsChangedDelegate.Broadcast(PlayerState->GetAttributePoints());
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& Tag) const
{
	check(AttributeInfo);
	FGameAttributeInfo Info = AttributeInfo->FindAttributeInfoByTag(Tag);
	Info.AttributeValue = Info.Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
