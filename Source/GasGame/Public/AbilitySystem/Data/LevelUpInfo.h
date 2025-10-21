#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FGameLevelUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpRequirement = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointAward = 1;
	
	UPROPERTY(EditDefaultsOnly)
	int32 SpellPointAward = 1;
};

UCLASS()
class GASGAME_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FGameLevelUpInfo> LevelUpInformation;

	int32 FindLevelForXP(int32 XP) const;
	
};
