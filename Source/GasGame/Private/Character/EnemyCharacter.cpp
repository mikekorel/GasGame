#include "Character/EnemyCharacter.h"

#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "GasGame/GasGame.h"
#include "UI/Widget/UserWidgetBase.h"

AEnemyCharacter::AEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMainAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UMainAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();

	if (UUserWidgetBase* UserWidget = Cast<UUserWidgetBase>(HealthBar->GetUserWidgetObject()))
	{
		UserWidget->SetWidgetController(this);
	}
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	OnHealthChanged.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	AbilitySystemComponent->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

void AEnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AEnemyCharacter::UnhighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	
	Weapon->SetRenderCustomDepth(false);
}

int32 AEnemyCharacter::GetPlayerLevel()
{
	return Level;
}
