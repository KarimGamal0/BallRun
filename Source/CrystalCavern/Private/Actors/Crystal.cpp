// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Crystal.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "Components/TimelineComponent.h"
#include "Components/PointLightComponent.h"

// Sets default values
ACrystal::ACrystal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	RootComponent = CollisionComponent;

	CrystalTopHalf = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crystal Top Half"));
	CrystalTopHalf->SetupAttachment(RootComponent);

	CrystalBottomHalf = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crystal Bottom Half"));
	CrystalBottomHalf->SetupAttachment(CrystalTopHalf);

	APointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	APointLight->SetupAttachment(RootComponent);

	//Add Timeline Component
	CrystalTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("CrystalTimelineComp"));
}

// Called when the game starts or when spawned
void ACrystal::BeginPlay()
{
	Super::BeginPlay();

	//Intialize varialbles
	StartLerpLocation = GetActorLocation();
	StartScale = GetActorScale3D();

	PointLightStartIntensity = APointLight->Intensity;

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACrystal::OnOverlapBegin);
	CrystalTopHalf->OnComponentBeginOverlap.AddDynamic(this, &ACrystal::OnMeshOverlapBegin);

	FOnTimelineFloat OnTimelineLocationCallback;
	FOnTimelineFloat OnTimelineScaleCallback;
	FOnTimelineFloat OnTimelineLightICallback;

	FOnTimelineEventStatic OnTimeLineFinishedCallback;

	OnTimelineLocationCallback.BindUFunction(this, TEXT("UpdateTimelineLocationComp"));
	OnTimelineScaleCallback.BindUFunction(this, TEXT("UpdateTimelineScaleComp"));
	OnTimelineLightICallback.BindUFunction(this, TEXT("UpdateTimelineLightComp"));

		OnTimeLineFinishedCallback.BindUFunction(this, TEXT("FinishedTimeLineComp"));

	if (CrystalTimelineFloatLocationCurve && CrystalTimelineFloatScaleCurve && CrystalTimelineFloatLightIntensityCurve) {
		CrystalTimelineComp->AddInterpFloat(CrystalTimelineFloatLocationCurve, OnTimelineLocationCallback);
		CrystalTimelineComp->AddInterpFloat(CrystalTimelineFloatScaleCurve, OnTimelineScaleCallback);
		CrystalTimelineComp->AddInterpFloat(CrystalTimelineFloatLightIntensityCurve, OnTimelineLightICallback);

		CrystalTimelineComp->SetTimelineFinishedFunc(OnTimeLineFinishedCallback);
	}
}

// Called every frame
void ACrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CrystalTimelineComp) {
		//CrystalTimelineComp->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

void ACrystal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this) {

		if (OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {
			CrystalTimelineComp->Play();
		}
	}
}

void ACrystal::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this) {
		OtherActor = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

		if (OtherActor) {
			Destroy();
		}
	}
}


void ACrystal::UpdateTimelineLocationComp(float output)
{
	MoveToPlayer(output);
}

void ACrystal::UpdateTimelineScaleComp(float output) {
	ScaleCrystal(output);
}

void ACrystal::UpdateTimelineLightComp(float output) {
	LightIntensityCrystal(output);
}

void ACrystal::FinishedTimeLineComp()
{
	Destroy();
}

void ACrystal::MoveToPlayer(float output)
{
	Endlocation = FMath::Lerp(StartLerpLocation, UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation(), output);
	SetActorLocation(Endlocation);
}

void ACrystal::ScaleCrystal(float output)
{
	EndScale = FMath::Lerp(StartScale, FVector(0.0, 0.0, 0.0), output);
	SetActorScale3D(EndScale);
}

void ACrystal::LightIntensityCrystal(float output) {
	PointLightEndIntensity = FMath::Lerp(PointLightStartIntensity, 0.0f, output);

	if (APointLight)
	{
		UE_LOG(LogTemp, Error, TEXT("light"));
		APointLight->SetIntensity(PointLightEndIntensity);
	}
}