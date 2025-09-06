#include "Player/MainPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "Input/GameEnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AMainPlayerController::AMainPlayerController()
{
	bReplicates = true;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(MainInputContext);

	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		InputSubsystem->AddMappingContext(MainInputContext, 0);
	}

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UGameEnhancedInputComponent* EnhInpComp = CastChecked<UGameEnhancedInputComponent>(InputComponent);
	EnhInpComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Move);

	EnhInpComp->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AMainPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	
}

void AMainPlayerController::CursorTrace()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (!Hit.bBlockingHit) return;

	LastHit = CurrHit;
	CurrHit = Hit.GetActor();

	if (LastHit != CurrHit)
	{
		if (LastHit) LastHit->UnhighlightActor();
		if (CurrHit) CurrHit->HighlightActor();
	}
	
}

UMainAbilitySystemComponent* AMainPlayerController::GetASC()
{
	if (!GameASC)
		GameASC = Cast<UMainAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	return GameASC;
}

void AMainPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// if (GEngine) { GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Yellow, *InputTag.ToString()); }
}

void AMainPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!GetASC()) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

void AMainPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!GetASC()) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}
