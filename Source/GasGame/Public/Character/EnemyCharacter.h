#pragma once

#include "CoreMinimal.h"
#include "Character/GameCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class GASGAME_API AEnemyCharacter : public AGameCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	/** Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
	
	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
};
