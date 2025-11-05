#include "Player/MainPlayerState.h"

#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Net/UnrealNetwork.h"

AMainPlayerState::AMainPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMainAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMainAttributeSet>("AttributeSet");
	
	SetNetUpdateFrequency(100.f);
}

void AMainPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainPlayerState, Level);
	DOREPLIFETIME(AMainPlayerState, XP);
	DOREPLIFETIME(AMainPlayerState, AttributePoints);
	DOREPLIFETIME(AMainPlayerState, SpellPoints);
}

UAbilitySystemComponent* AMainPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMainPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;

	const int32 NewLevel = LevelUpInfo->FindLevelForXP(XP);
	const int32 LevelUpsCount = NewLevel - Level;
	if (LevelUpsCount > 0)
	{
		// Grant attribute/spell points per level surpassed
		for (int32 SurpassedLevel = Level; SurpassedLevel < NewLevel; SurpassedLevel++)
		{
			const int32 AttributePointAward = LevelUpInfo->LevelUpInformation[SurpassedLevel].AttributePointAward;
			const int32 SpellPointAward = LevelUpInfo->LevelUpInformation[SurpassedLevel].SpellPointAward;
			AddToAttributePoints(AttributePointAward);
			AddToSpellPoints(SpellPointAward);
		}
		AddToLevel(LevelUpsCount);
		AttributeSet->RefillHealthAndMana();
	}
	
	OnXPChangedDelegate.Broadcast(XP);
}

void AMainPlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
	AbilitySystemComponent->UpdateAbilityStatuses(Level);
}

void AMainPlayerState::AddToAttributePoints(int32 InAttributePoints)
{
	AttributePoints += InAttributePoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AMainPlayerState::AddToSpellPoints(int32 InSpellPoints)
{
	SpellPoints += InSpellPoints;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

void AMainPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AMainPlayerState::SetLevel(int32 InLevel)
{
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AMainPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level);
}

void AMainPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}

void AMainPlayerState::OnRep_AttributePoints(int32 OldAttributePoints)
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AMainPlayerState::OnRep_SpellPoints(int32 OldSpellPoints)
{
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}
