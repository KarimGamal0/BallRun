// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Cannon.h"
#include "Actors/Projectile.h"
#include "Components/ArrowComponent.h"
#include "Components/TimelineComponent.h"

// Sets default values
ACannon::ACannon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CannonBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = CannonBase;

	CannonMuzzle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon Mesh"));
	CannonMuzzle->SetupAttachment(CannonBase);

	ArrowSpawnLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	ArrowSpawnLocation->SetupAttachment(CannonBase);

	CannonTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline Component"));
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ACannon::FireProjectile, FireRate, true);

	//Timeline Update Callback
	FOnTimelineFloat OnTimelineLocationCallback;
	OnTimelineLocationCallback.BindUFunction(this, TEXT("UpdateTimelineLocationComp"));

	if (!CannonTimelineCurveFloat)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannon timeline curve float does not exist"));
		return;
	}

	CannonTimelineComp->AddInterpFloat(CannonTimelineCurveFloat, OnTimelineLocationCallback);
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACannon::FireProjectile()
{
	if (!ProjectileToSpawn) {
		UE_LOG(LogTemp, Error, TEXT("Projectile class does not exist"));
		return;
	}

	const FVector SpawnLocation = ArrowSpawnLocation->GetComponentLocation();
	const FRotator SpawnRotation = ArrowSpawnLocation->GetComponentRotation();

	AProjectile* TempProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileToSpawn, FTransform(SpawnRotation, SpawnLocation, ProjectileScale));
	TempProjectile->SetOwner(this);

	CannonTimelineComp->PlayFromStart();
}

void ACannon::UpdateTimelineLocationComp(float output)
{
	MoveCannonBarrel(output);
}

void ACannon::MoveCannonBarrel(float output) {
	CannonMuzzle->SetRelativeLocation(FVector(0.0, output, 0.0));
}