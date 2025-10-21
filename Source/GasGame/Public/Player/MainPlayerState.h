#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

class ULevelUpInfo;
class UMainAbilitySystemComponent;
class UMainAttributeSet;


DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/)

UCLASS()
class GASGAME_API AMainPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TObjectPtr<ULevelUpInfo> LevelUpInfo;
	
	AMainPlayerState();

	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnPlayerStatChanged OnLevelChangedDelegate;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UMainAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE int32 GetPlayerXP() const { return XP; }
	
	void AddToXP(int32 InXP);
	void AddToLevel(int32 InLevel);
	
	void SetXP(int32 InXP);
	void SetLevel(int32 InLevel);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMainAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UMainAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_XP)
	int32 XP = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);
	
};
