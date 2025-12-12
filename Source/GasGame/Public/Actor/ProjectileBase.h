#pragma once

#include "CoreMinimal.h"
#include "GameAbilityTypes.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UNiagaraSystem;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class GASGAME_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FDamageEffectParams DamageEffectParams;
	
	AProjectileBase();
	virtual void Destroyed() override;

protected:
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void BeginPlay() override;
	void OnHit();

private:
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.f;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
	
	bool bHit = false;
	
};
