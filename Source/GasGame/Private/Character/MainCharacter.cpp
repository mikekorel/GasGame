#include "Character/MainCharacter.h"

#include "AbilitySystemComponent.h"
#include "NiagaraComponent.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/MainPlayerController.h"
#include "Player/MainPlayerState.h"
#include "UI/HUD/GameHUD.h"
#include "UI/WidgetController/WidgetControllerBase.h"

AMainCharacter::AMainCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
	
	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagaraComponent");
	LevelUpNiagaraComponent->SetupAttachment(RootComponent);
	LevelUpNiagaraComponent->bAutoActivate = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CharacterClass = ECharacterClass::Elementalist;
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// init ability actor info for the Server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AMainCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// init ability actor info for the Client 
	InitAbilityActorInfo();
}

void AMainCharacter::AddToXP_Implementation(int32 InXP)
{
	AMainPlayerState* State = GetPlayerState<AMainPlayerState>();
	check(State);
	State->AddToXP(InXP);
}

int32 AMainCharacter::GetPlayerLevel_Implementation()
{
	const AMainPlayerState* State = GetPlayerState<AMainPlayerState>();
	check(State);
	return State->GetPlayerLevel();
}

void AMainCharacter::MulticastLevelUpParticles_Implementation() const
{
	if (IsValid(LevelUpNiagaraComponent))
	{
		const FVector CameraLocation = TopDownCameraComponent->GetComponentLocation();
		const FVector NiagaraSystemLocation = LevelUpNiagaraComponent->GetComponentLocation();
		const FRotator ToCameraRotation = (CameraLocation - NiagaraSystemLocation).Rotation();
		LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotation);
		LevelUpNiagaraComponent->Activate(true);
	}
}

void AMainCharacter::InitAbilityActorInfo()
{
	AMainPlayerState* State = GetPlayerState<AMainPlayerState>();
	check(State);
	AbilitySystemComponent = CastChecked<UMainAbilitySystemComponent>(State->GetAbilitySystemComponent());
	AttributeSet = State->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(State, this);
	AbilitySystemComponent->AbilityActorInfoSet();

	if (AMainPlayerController* PC = GetController<AMainPlayerController>())
	{
		if (AGameHUD* GameHUD = PC->GetHUD<AGameHUD>())
		{
			FWidgetControllerParams WCParams = FWidgetControllerParams(PC, State, AbilitySystemComponent, AttributeSet);
			GameHUD->InitOverlay(WCParams);
		}
	}

	InitializeDefaultAttributes();

	State->OnLevelChangedDelegate.AddLambda([this](const int32 NewValue)
	{
		MulticastLevelUpParticles();
	});
}
