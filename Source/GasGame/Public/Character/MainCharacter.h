#pragma once

#include "CoreMinimal.h"
#include "Character/GameCharacterBase.h"
#include "MainCharacter.generated.h"

UCLASS()
class GASGAME_API AMainCharacter : public AGameCharacterBase
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;

private:
	virtual void InitAbilityActorInfo() override;
};
