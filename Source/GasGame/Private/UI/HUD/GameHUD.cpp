#include "UI/HUD/GameHUD.h"
#include "UI/Widget/UserWidgetBase.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AGameHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

void AGameHUD::InitOverlay(const FWidgetControllerParams& WCParams)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized!"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized!"))
	
	UOverlayWidgetController* OverlayWC = GetOverlayWidgetController(WCParams);
	OverlayWidget = CreateWidget<UUserWidgetBase>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->SetWidgetController(OverlayWC);
	OverlayWC->BroadcastInitialValues();
	OverlayWidget->AddToViewport();
}
