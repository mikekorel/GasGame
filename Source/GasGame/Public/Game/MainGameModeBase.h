#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeBase.generated.h"

class UAbilityInfo;
class UCharacterClassInfo;

UCLASS()
class GASGAME_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Setup|Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup|Ability Info")
	TObjectPtr<UAbilityInfo> AbilityInfo;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Debug")
	bool EnableDebugCommandsInEditor = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Debug")
	TArray<FString> DebugCommands;
	
	virtual void BeginPlay() override;
};
