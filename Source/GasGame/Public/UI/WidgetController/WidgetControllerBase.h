#pragma once

#include "CoreMinimal.h"
#include "WidgetControllerBase.generated.h"

class AMainPlayerController;
class AMainPlayerState;
class UMainAbilitySystemComponent;
class UMainAttributeSet;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {};
	FWidgetControllerParams(AMainPlayerController* PC, AMainPlayerState* PS, UMainAbilitySystemComponent* ASC, UMainAttributeSet* AS)
		: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TObjectPtr<AMainPlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AMainPlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMainAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMainAttributeSet> AttributeSet = nullptr;
};

UCLASS()
class GASGAME_API UWidgetControllerBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	virtual void BroadcastInitialValues() {}
	virtual void BindCallbacksToDependencies() {}
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<AMainPlayerController> PlayerController = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<AMainPlayerState> PlayerState = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UMainAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UMainAttributeSet> AttributeSet = nullptr;
	
};
