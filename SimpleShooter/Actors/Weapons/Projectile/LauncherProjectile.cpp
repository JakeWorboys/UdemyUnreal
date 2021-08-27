// Fill out your copyright notice in the Description page of Project Settings.


#include "LauncherProjectile.h"
#include "Components/StaticMeshComponent.h" 
#include "GameFramework/ProjectileMovementComponent.h" 
#include "Kismet/GameplayStatics.h"

// Sets default values
ALauncherProjectile::ALauncherProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	SetRootComponent(BaseMesh);


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	ProjectileMovement->InitialSpeed = 1000;
	ProjectileMovement->MaxSpeed = 1000;
}

// Called when the game starts or when spawned
void ALauncherProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	this->OnActorHit.AddDynamic(this, &ALauncherProjectile::OnHit);
}

// Called every frame
void ALauncherProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALauncherProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) 
{
	AActor* ProjectileOwner = GetOwner()->GetOwner();
	if (!ProjectileOwner) return;

	TArray<AActor*> SafeActors;

	if (OtherActor && OtherActor != this && OtherActor != GetOwner())
	{
		UGameplayStatics::ApplyRadialDamage(this, Damage, GetActorLocation(), ExplosionRadius, DamageType, SafeActors, ProjectileOwner, ProjectileOwner->GetInstigatorController(), false, ECC_Visibility);
		UGameplayStatics::SpawnEmitterAtLocation(this, Impact, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		Destroy();
	}
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
}
