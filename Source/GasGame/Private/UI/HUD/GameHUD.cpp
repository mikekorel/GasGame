#include "UI/HUD/GameHUD.h"
#include "UI/Widget/UserWidgetBase.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	OverlayWidget = CreateWidget<UUserWidgetBase>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();
}
