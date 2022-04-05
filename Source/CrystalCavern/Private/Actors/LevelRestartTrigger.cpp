// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelRestartTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h" 

// Sets default values
ALevelRestartTrigger::ALevelRestartTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	Trigger->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ALevelRestartTrigger::BeginPlay()
{
	Super::BeginPlay();

	//Initialize variables
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALevelRestartTrigger::OnOverlapBegin);

	//Code
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(1.0f, 0.0f, Delay, Color);
}

// Called every frame
void ALevelRestartTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelRestartTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this) {

		if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {

			UGameplayStatics::ApplyDamage(OtherActor, 1.0f, this->GetInstigatorController(), this, DamageType);
		}
	}
}