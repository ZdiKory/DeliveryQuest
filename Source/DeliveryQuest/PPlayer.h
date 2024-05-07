// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "APackage.h" // Needed for follow camera
#include "PPlayer.generated.h"

UCLASS()
class DELIVERYQUEST_API APPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Static Mesh Component
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent *CameraBoom;

	// Main camera
	UPROPERTY(EditDefaultsOnly, Category = Camera)
	UCameraComponent *CameraComponent;

	class AAPackage *AAPackageRef;
	void FollowPackage();
	void Click();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	APlayerController *PlayerControllerRef;
};
