#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MainAIController.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class GASGAME_API AMainAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMainAIController();

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
};
