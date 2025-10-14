#include "AbilitySystem/Data/AbilityInfo.h"

#include "GasGame/LogChannels.h"

FGameAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FGameAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
			return Info;
	}

	UE_CLOG(bLogNotFound, LogGasGame, Error, TEXT("Can't find info for AbilityTag [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
		
	return FGameAbilityInfo();
}
