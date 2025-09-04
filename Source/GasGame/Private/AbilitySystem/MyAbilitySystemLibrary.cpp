#include "AbilitySystem/MyAbilitySystemLibrary.h"

#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MainPlayerController.h"
#include "Player/MainPlayerState.h"
#include "UI/HUD/GameHUD.h"
#include "UI/WidgetController/WidgetControllerBase.h"

UOverlayWidgetController* UMyAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (AMainPlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)))
	{
		if (AGameHUD* GameHUD = Cast<AGameHUD>(PC->GetHUD()))
		{
			AMainPlayerState* PS = PC->GetPlayerState<AMainPlayerState>();
			UMainAbilitySystemComponent* ASC = Cast<UMainAbilitySystemComponent>(PS->GetAbilitySystemComponent());
			UMainAttributeSet* AS = Cast<UMainAttributeSet>(PS->GetAttributeSet());
			const FWidgetControllerParams WidgetControllerParams = FWidgetControllerParams(PC, PS, ASC, AS);
			return GameHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
