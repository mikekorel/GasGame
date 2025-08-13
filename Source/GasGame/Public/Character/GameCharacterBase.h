#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameCharacterBase.generated.h"

UCLASS(Abstract)
class GASGAME_API AGameCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AGameCharacterBase();

protected:
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	virtual void BeginPlay() override;

};
