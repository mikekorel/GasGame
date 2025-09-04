#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/WidgetControllerBase.h"
#include "AttributeMenuWidgetController.generated.h"

UCLASS()
class GASGAME_API UAttributeMenuWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
};
