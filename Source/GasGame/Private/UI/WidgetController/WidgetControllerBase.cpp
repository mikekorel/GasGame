#include "UI/WidgetController/WidgetControllerBase.h"

#include "GameplayAbilitySpec.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"

void UWidgetControllerBase::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UWidgetControllerBase::BroadcastAbilityInfo()
{
	if (!AbilitySystemComponent->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec)
	{
		FGameAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec), true);
		Info.InputTag = AbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		Info.StatusTag = AbilitySystemComponent->GetStatusFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});

	AbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}
