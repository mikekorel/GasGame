#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UAttributeMenuWidgetController;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UUserWidgetBase;

UCLASS()
class GASGAME_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	
	void InitOverlay(const FWidgetControllerParams& WCParams);

private:
	UPROPERTY()
	TObjectPtr<UUserWidgetBase> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidgetBase> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
