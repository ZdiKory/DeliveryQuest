// Fill out your copyright notice in the Description page of Project Settings.

#include "APackage.h"

// Sets default values
AAPackage::AAPackage()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize MeshComponent and attach to root, simulate physics by default
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
}

// Called when the game starts or when spawned
void AAPackage::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAPackage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
