#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeBase.generated.h"

UCLASS()
class GASGAME_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
	bool EnableDebugCommandsInEditor = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
	TArray<FString> DebugCommands;
	
	virtual void BeginPlay() override;
};
