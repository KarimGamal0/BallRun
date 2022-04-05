// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WinVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Crystal.h"

// Sets default values
AWinVolume::AWinVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	Trigger->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void AWinVolume::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWinVolume::OnOverlapBegin);
}


// Called every frame
void AWinVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWinVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {

		if (AnyCrystalRemaining()) {
			UE_LOG(LogTemp, Error, TEXT("Crystal Still remaining"));
		}
		else {
			//UE_LOG(LogTemp, Error, TEXT("There are no crystal remaining"));
			CompleteLevel();
		}
	}
}

bool AWinVolume::AnyCrystalRemaining() {

	TArray<AActor*> Crystals;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACrystal::StaticClass(), Crystals);

	return Crystals.Num() > 0;
}

void AWinVolume::CompleteLevel()
{
	if (std::size(levelNames) - 1 == GetCurrentLevelIndex()) {

	}
	else {

		UGameplayStatics::OpenLevel(GetWorld(), levelNames[GetCurrentLevelIndex() + 1]);
	}
}

int AWinVolume::GetCurrentLevelIndex() const
{
	for (int32 i = 0; i < 10; i++)
	{
		if (FName(*UGameplayStatics::GetCurrentLevelName(GetWorld())) == levelNames[i]) {
			return i;
		}
	}
	return 0;
}
