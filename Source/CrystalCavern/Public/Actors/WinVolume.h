// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinVolume.generated.h"

class UBoxComponent;
UCLASS()
class CRYSTALCAVERN_API AWinVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWinVolume();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(EditAnywhere)
		//TArray<FString> LevelNames = { "Level 1","Level 2" };

	UPROPERTY(EditAnywhere)
		FName levelNames[10] = { "Level1","Level2" };
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
		USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
		UBoxComponent* Trigger;




	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool AnyCrystalRemaining();
	void CompleteLevel();
	int GetCurrentLevelIndex() const;
};
