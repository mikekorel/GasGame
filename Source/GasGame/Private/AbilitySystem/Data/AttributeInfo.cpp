#include "AbilitySystem/Data/AttributeInfo.h"

#include "GasGame/LogChannels.h"

FGameAttributeInfo UAttributeInfo::FindAttributeInfoByTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FGameAttributeInfo& Info : AttributeInformation)
	{
		if (AttributeTag.MatchesTagExact(Info.AttributeTag))
		{
			return Info;
		}
	}

	UE_CLOG(bLogNotFound, LogGasGame, Error, TEXT("Can't find Info for the AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	
	return FGameAttributeInfo();
}
