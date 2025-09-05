#include "Input/GameInputConfig.h"

const UInputAction* UGameInputConfig::FindAbilityInputActionForTag(const FGameplayTag InputTag, bool bLogNotFound) const
{
	for (const FGameInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
			return Action.InputAction;
	}
	
	UE_CLOG(bLogNotFound, LogTemp, Error, TEXT("Can't find AbilityInputAction for Input Tag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	return nullptr;
}
