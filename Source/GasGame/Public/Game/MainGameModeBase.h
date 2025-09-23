#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeBase.generated.h"

class UCharacterClassInfo;

UCLASS()
class GASGAME_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
	bool EnableDebugCommandsInEditor = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
	TArray<FString> DebugCommands;
	
	virtual void BeginPlay() override;
};
