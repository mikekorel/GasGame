#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class USplineComponent;
class UMainAbilitySystemComponent;
class UGameInputConfig;
class IEnemyInterface;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class GASGAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> MainInputContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UGameInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UMainAbilitySystemComponent> GameASC;

	UPROPERTY()
	TScriptInterface<IEnemyInterface> LastHit;

	UPROPERTY()
	TScriptInterface<IEnemyInterface> CurrHit;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	FHitResult CursorHit;

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	
	void Move(const FInputActionValue& InputActionValue);
	void CursorTrace();

	UMainAbilitySystemComponent* GetASC();
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	void AutoRun();
};
