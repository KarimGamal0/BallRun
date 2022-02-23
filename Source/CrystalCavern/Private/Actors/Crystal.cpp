// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Crystal.h"

// Sets default values
ACrystal::ACrystal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;

	CrystalTopHalf = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crystal Top Half"));
	CrystalTopHalf->SetupAttachment(RootComponent);

	CrystalBottomHalf = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crystal Bottom Half"));
	CrystalBottomHalf->SetupAttachment(CrystalTopHalf);

}

// Called when the game starts or when spawned
void ACrystal::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

