#pragma once

#include "CoreMinimal.h"
#include "Character/GameCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "MainCharacter.generated.h"

UCLASS()
class GASGAME_API AMainCharacter : public AGameCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	// Player Interface
	virtual void AddToXP_Implementation(int32 InXP) override;

	// Combat Interface 
	virtual int32 GetPlayerLevel() override;

private:
	virtual void InitAbilityActorInfo() override;
};
