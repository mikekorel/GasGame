#include "AbilitySystem/MyAbilitySystemLibrary.h"

#include "GameAbilityTypes.h"
#include "AbilitySystem/MainAbilitySystemComponent.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Engine/OverlapResult.h"
#include "Game/MainGameModeBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MainPlayerController.h"
#include "Player/MainPlayerState.h"
#include "UI/HUD/GameHUD.h"
#include "UI/WidgetController/WidgetControllerBase.h"

UOverlayWidgetController* UMyAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (AMainPlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)))
	{
		if (AGameHUD* GameHUD = Cast<AGameHUD>(PC->GetHUD()))
		{
			AMainPlayerState* PS = PC->GetPlayerState<AMainPlayerState>();
			UMainAbilitySystemComponent* ASC = Cast<UMainAbilitySystemComponent>(PS->GetAbilitySystemComponent());
			UMainAttributeSet* AS = Cast<UMainAttributeSet>(PS->GetAttributeSet());
			const FWidgetControllerParams WidgetControllerParams = FWidgetControllerParams(PC, PS, ASC, AS);
			return GameHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UMyAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (AMainPlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)))
	{
		if (AGameHUD* GameHUD = Cast<AGameHUD>(PC->GetHUD()))
		{
			AMainPlayerState* PS = PC->GetPlayerState<AMainPlayerState>();
			UMainAbilitySystemComponent* ASC = Cast<UMainAbilitySystemComponent>(PS->GetAbilitySystemComponent());
			UMainAttributeSet* AS = Cast<UMainAttributeSet>(PS->GetAttributeSet());
			const FWidgetControllerParams WidgetControllerParams = FWidgetControllerParams(PC, PS, ASC, AS);
			return GameHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

void UMyAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (!CharacterClassInfo) return;
	
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttrContextHandle = ASC->MakeEffectContext();
	PrimaryAttrContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttrContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data);

	FGameplayEffectContextHandle SecondaryAttrContextHandle = ASC->MakeEffectContext();
	SecondaryAttrContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttrContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data);

	FGameplayEffectContextHandle VitalAttrContextHandle = ASC->MakeEffectContext();
	VitalAttrContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttrContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data);
}

void UMyAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (!CharacterClassInfo) return;
	
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}

	const FCharacterClassDefaultInfo DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (auto AbilityClass : DefaultInfo.StartupAbilities)
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor()))
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, CombatInterface->GetPlayerLevel());
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

UCharacterClassInfo* UMyAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AMainGameModeBase* MainGameMode = Cast<AMainGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!MainGameMode) return nullptr;

	return MainGameMode->CharacterClassInfo;
}

bool UMyAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMyGameplayEffectContext* MyEffectContext = static_cast<const FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return MyEffectContext->IsBlockedHit();
	}
	return false;
}

bool UMyAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FMyGameplayEffectContext* MyEffectContext = static_cast<const FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return MyEffectContext->IsCriticalHit();
	}
	return false;
}

void UMyAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInBlockedHit)
{
	if (FMyGameplayEffectContext* MyEffectContext = static_cast<FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		MyEffectContext->SetBlockedHit(bInBlockedHit);
	}
}

void UMyAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInCriticalHit)
{
	if (FMyGameplayEffectContext* MyEffectContext = static_cast<FMyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		MyEffectContext->SetCriticalHit(bInCriticalHit);
	}
}

void UMyAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(Overlap.GetActor());
			}
		}
	}
}

bool UMyAbilitySystemLibrary::IsFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool bBothPlayers = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));
	const bool bBothEnemies = FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));

	return bBothPlayers || bBothEnemies;
}

int32 UMyAbilitySystemLibrary::GetXPRewardForClassAndLevel(const UObject* WorldContextObject, ECharacterClass CharacterClass, int32 CharacterLevel)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (!CharacterClassInfo) return 0;

	const FCharacterClassDefaultInfo& Info = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	const float XPReward = Info.XPReward.GetValueAtLevel(CharacterLevel);

	return static_cast<int32>(XPReward);
}
