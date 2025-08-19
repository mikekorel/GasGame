#include "Character/MainCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/MainPlayerController.h"
#include "Player/MainPlayerState.h"
#include "UI/HUD/GameHUD.h"
#include "UI/WidgetController/WidgetControllerBase.h"

AMainCharacter::AMainCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// init ability actor info for the Server
	InitAbilityActorInfo();
}

void AMainCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// init ability actor info for the Client 
	InitAbilityActorInfo();
}

void AMainCharacter::InitAbilityActorInfo()
{
	AMainPlayerState* State = GetPlayerState<AMainPlayerState>();
	check(State);
	AbilitySystemComponent = CastChecked<UMainAbilitySystemComponent>(State->GetAbilitySystemComponent());
	AttributeSet = State->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(State, this);

	if (AMainPlayerController* PC = GetController<AMainPlayerController>())
	{
		if (AGameHUD* GameHUD = PC->GetHUD<AGameHUD>())
		{
			FWidgetControllerParams WCParams = FWidgetControllerParams(PC, State, AbilitySystemComponent, AttributeSet);
			GameHUD->InitOverlay(WCParams);
		}
	}
}
