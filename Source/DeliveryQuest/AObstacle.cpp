// Fill out your copyright notice in the Description page of Project Settings.

#include "AObstacle.h"

// Sets default values
AAObstacle::AAObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	MovementDuration = .2f; // Duration of the movement in seconds
	ElapsedTime = 0.0f;
	bIsMoving = false;
}

// Called when the game starts or when spawned
void AAObstacle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		ElapsedTime += DeltaTime;
		float Alpha = ElapsedTime / MovementDuration;
		Alpha = FMath::Clamp(Alpha, 0.0f, 1.0f);

		FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Alpha);
		SetActorLocation(NewLocation);

		if (Alpha >= 1.0f)
		{
			bIsMoving = false; // Stop the movement
		}
	}
}

void AAObstacle::HandleClick()
{
	if (MeshComponent)
	{
		// disable collision
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// Get the bounds of the mesh
		// FBoxSphereBounds Bounds = MeshComponent->CalcBounds(MeshComponent->GetComponentTransform());

		// // Calculate the length of the mesh (assuming the length is along the X-axis)
		// float Length = Bounds.BoxExtent.X * 2;

		// // Calculate the backward movement vector (assuming forward is along the X-axis)
		// FVector BackwardMovement = GetActorForwardVector() * Length;

		// // Move the actor backward by its length
		// SetActorLocation(GetActorLocation() + BackwardMovement);

		if (!bIsMoving) // Start moving only if not already moving
		{
			StartLocation = GetActorLocation();
			EndLocation = StartLocation + GetActorForwardVector() * 70.0f; // Move backward by 100 units
			ElapsedTime = 0.0f;
			bIsMoving = true;
		}
	}
}
