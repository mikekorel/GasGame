#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NiagaraComponent.h"
#include "DebuffNiagaraComponent.generated.h"

UCLASS()
class GASGAME_API UDebuffNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()
	
public:
	UDebuffNiagaraComponent();

	UPROPERTY(VisibleAnywhere)
	FGameplayTag DebuffTag;

	virtual void BeginPlay() override;
	
protected:
	UFUNCTION()
	void OnOwnerDeath(AActor* DeadActor);
	
	void DebuffTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
};
