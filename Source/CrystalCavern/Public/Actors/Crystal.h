// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Crystal.generated.h"

class USphereComponent;
class UTimelineComponent;
class UCurveFloat;
class UPointLightComponent;
UCLASS()
class CRYSTALCAVERN_API ACrystal : public AActor
{
	GENERATED_BODY()

public:
	//Functions
	// Sets default values for this actor's properties
	ACrystal();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void UpdateTimelineLocationComp(float output);

	UFUNCTION()
		void UpdateTimelineScaleComp(float output);

	UFUNCTION()
		void UpdateTimelineLightComp(float output);


	UFUNCTION()
	    void FinishedTimeLineComp();

protected:
	UTimelineComponent* CrystalTimelineComp;
	//FOnTimelineFloat UpdateFunctionFloat;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:

	//Variables
	UPROPERTY(EditAnywhere)
		UCurveFloat* CrystalTimelineFloatLocationCurve;

	UPROPERTY(EditAnywhere)
		UCurveFloat* CrystalTimelineFloatScaleCurve;

	UPROPERTY(EditAnywhere)
		UCurveFloat* CrystalTimelineFloatLightIntensityCurve;

	FVector StartLerpLocation;
	FVector StartScale;
	FVector Endlocation;
	FVector EndScale;
	float PointLightStartIntensity = 0.0f;
	float PointLightEndIntensity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* CrystalTopHalf;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* CrystalBottomHalf;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
		USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
		UPointLightComponent* APointLight;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void MoveToPlayer(float output);
	void ScaleCrystal(float output);
	void LightIntensityCrystal(float output);

};