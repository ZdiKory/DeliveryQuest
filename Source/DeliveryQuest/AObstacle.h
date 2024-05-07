// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "AObstacle.generated.h"

UCLASS()
class DELIVERYQUEST_API AAObstacle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Static Mesh Component
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *MeshComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void HandleClick();

private:
	FVector StartLocation;
	FVector EndLocation;
	float MovementDuration;
	float ElapsedTime;
	bool bIsMoving;
};
