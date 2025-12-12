#include "Actor/ProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/MyAbilitySystemLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GasGame/GasGame.h"
#include "Kismet/GameplayStatics.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnSphereOverlap);

	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
}


void AProjectileBase::OnHit()
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	if (LoopingSoundComponent) LoopingSoundComponent->Stop();
	bHit = true;
}

void AProjectileBase::Destroyed()
{
	if (!HasAuthority() && !bHit)
		OnHit();
	
	Super::Destroyed();
}

void AProjectileBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* SourceAvatarActor = DamageEffectParams.SourceASC->GetAvatarActor();
	if (SourceAvatarActor == OtherActor)
		return;

	if (UMyAbilitySystemLibrary::IsFriend(SourceAvatarActor, OtherActor))
		return;
	
	if (!bHit)
		OnHit();

	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			DamageEffectParams.TargetASC = TargetASC;
			UMyAbilitySystemLibrary::ApplyDamageEffect(DamageEffectParams);
		}
		
		Destroy();
	} else
	{
		bHit = true;
	}
}
