#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "MyGameplayTags.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	check(AttributeInfo);
	
	FGameAttributeInfo Info = AttributeInfo->FindAttributeInfoByTag(MyGameplayTags::Attributes_Primary_Strength);
	Info.AttributeValue = AttributeSet->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}