#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "MyGameplayTags.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/MainPlayerState.h"
void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	SpellPointsChanged.Broadcast(PlayerState->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	AbilitySystemComponent->AbilityStatusChanged.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 NewLevel)
	{
		if (SelectedAbility.Ability.MatchesTagExact(AbilityTag))
		{
			SelectedAbility.Status = StatusTag;
			
			bool bEnableSpellPointsButton = false;
			bool bEnableEquipButton = false;
			ShouldEnableButtons(StatusTag, CurrentSpellPoints, bEnableSpellPointsButton, bEnableEquipButton);
			SpellGlobeSelectedDelegate.Broadcast(bEnableSpellPointsButton, bEnableEquipButton);
		}
		
		if (AbilityInfo)
		{
			FGameAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	});

	PlayerState->OnSpellPointsChangedDelegate.AddLambda([this](int32 SpellPoints)
	{
		SpellPointsChanged.Broadcast(SpellPoints);
		CurrentSpellPoints = SpellPoints;

		bool bEnableSpellPointsButton = false;
		bool bEnableEquipButton = false;
		ShouldEnableButtons(SelectedAbility.Status, CurrentSpellPoints, bEnableSpellPointsButton, bEnableEquipButton);
		SpellGlobeSelectedDelegate.Broadcast(bEnableSpellPointsButton, bEnableEquipButton);
	});
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	const int32 SpellPoints = PlayerState->GetSpellPoints();
	FGameplayTag AbilityStatus;

	const bool bTagValid = AbilityTag.IsValid();
	const bool bTagNone = AbilityTag.MatchesTagExact(MyGameplayTags::Abilities_None);
	const FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->GetSpecFromAbilityTag(AbilityTag);
	const bool bSpecValid = AbilitySpec != nullptr;

	if (!bTagValid || bTagNone || !bSpecValid)
	{
		AbilityStatus = MyGameplayTags::Abilities_Status_Locked;
	} else
	{
		AbilityStatus = AbilitySystemComponent->GetStatusFromSpec(*AbilitySpec);
	}

	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = AbilityStatus;
	
	bool bEnableSpellPointsButton = false;
	bool bEnableEquipButton = false;
	ShouldEnableButtons(AbilityStatus, SpellPoints, bEnableSpellPointsButton, bEnableEquipButton);
	SpellGlobeSelectedDelegate.Broadcast(bEnableSpellPointsButton, bEnableEquipButton);
}

void USpellMenuWidgetController::SpendPointButtonPressed()
{
	if (AbilitySystemComponent) AbilitySystemComponent->ServerSpendSpellPoint(SelectedAbility.Ability);
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bEnableSpellPointsButton, bool& bEnableEquipButton)
{
	if (AbilityStatus.MatchesTagExact(MyGameplayTags::Abilities_Status_Equipped))
	{
		bEnableEquipButton = true;
		bEnableSpellPointsButton = SpellPoints > 0;
	}
	else if (AbilityStatus.MatchesTagExact(MyGameplayTags::Abilities_Status_Eligible))
	{
		bEnableEquipButton = false;
		bEnableSpellPointsButton = SpellPoints > 0;
	}
	else if (AbilityStatus.MatchesTagExact(MyGameplayTags::Abilities_Status_Unlocked))
	{
		bEnableEquipButton = true;
		bEnableSpellPointsButton = SpellPoints > 0;
	}
	else if (AbilityStatus.MatchesTagExact(MyGameplayTags::Abilities_Status_Locked))
	{
		bEnableEquipButton = false;
		bEnableSpellPointsButton = false;
	}
}
