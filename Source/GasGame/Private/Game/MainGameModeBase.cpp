#include "Game/MainGameModeBase.h"

#include "Kismet/GameplayStatics.h"

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	if (GIsEditor && EnableDebugCommandsInEditor)
	{
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			for (const FString& DebugCommand : DebugCommands)
			{
				PC->ConsoleCommand(DebugCommand);
			}
		}
	}
#endif
	
}
