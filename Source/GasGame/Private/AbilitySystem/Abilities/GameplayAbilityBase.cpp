#include "AbilitySystem/Abilities/GameplayAbilityBase.h"

FString UGameplayAbilityBase::GetDescription(int32 Level) const
{
	return FString::Printf(TEXT("<Default>%s, </><Level>%d</>"), L"Default Ability Name - This is a long description about the effects this ability has", Level);
}

FString UGameplayAbilityBase::GetNextLevelDescription(int32 Level) const
{
	return FString::Printf(TEXT("<Default>Next Level: </><Level>%d</>\n<Default>Causes much more damage</>"), Level);
}

FString UGameplayAbilityBase::GetLockedDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Spell Locked Until Level: %d</>"), Level);
}
