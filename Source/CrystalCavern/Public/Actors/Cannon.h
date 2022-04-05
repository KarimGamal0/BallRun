// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

class AProjectile;
class UArrowComponent;
class UCurveFloat;
class UTimelineComponent;
UCLASS()
class CRYSTALCAVERN_API ACannon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACannon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTimelineComponent* CannonTimelineComp;

private:
	//Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* CannonBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* CannonMuzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
		UArrowComponent* ArrowSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
		TSubclassOf<AProjectile> ProjectileToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
		FVector ProjectileScale;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
		float FireRate = 2.0f;

	UPROPERTY(EditAnywhere)
		UCurveFloat* CannonTimelineCurveFloat;

	FTimerHandle FireRateTimerHandle;

	// Functions
	UFUNCTION()
		void UpdateTimelineLocationComp(float output);

	void FireProjectile();

	void MoveCannonBarrel(float output);
};
