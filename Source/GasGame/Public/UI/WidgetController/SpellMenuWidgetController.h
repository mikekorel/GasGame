#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/WidgetControllerBase.h"
#include "SpellMenuWidgetController.generated.h"

UCLASS(BlueprintType, Blueprintable)
class GASGAME_API USpellMenuWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStatChangedSignature SpellPointsChanged;
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
};
