#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
	for (int32 Level = 0; Level < LevelUpInformation.Num(); Level++)
	{
		if (XP < LevelUpInformation[Level].LevelUpRequirement)
			return Level;
	}
	return LevelUpInformation.Num() - 1;
}
