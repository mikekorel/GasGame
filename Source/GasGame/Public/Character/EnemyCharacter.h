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
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
};
