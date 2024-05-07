// Fill out your copyright notice in the Description page of Project Settings.

#include "PPlayer.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "AObstacle.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APPlayer::APPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the camera boom (spring arm component)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent); // Attach to the root component or mesh component

	// Create the camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom);

	// Set default camera boom parameters
	// CameraBoom->TargetArmLength = 500.0f;
	// CameraBoom->RelativeLocation = FVector(0.0f, 0.0f, 500.0f);

	// CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	// CameraComponent->SetupAttachment(MeshComponent);
	// CameraComponent->FieldOfView = 90.0f;
	// CameraComponent->SetRelativeLocation(FVector(0, 0, 500));
}

// Called when the game starts or when spawned
void APPlayer::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem *EnhancedInputSubsystem = nullptr;
	PlayerControllerRef = Cast<APlayerController>(GetController()); // get player controller
	if (PlayerControllerRef)
	{
		PlayerControllerRef->bShowMouseCursor = true;						   // show mouse cursor
		if (ULocalPlayer *LocalPlayer = PlayerControllerRef->GetLocalPlayer()) // get local player
		{
			EnhancedInputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(); // get subsystem
			if (EnhancedInputSubsystem)
			{
				// Load the Input Mapping Context asset
				UInputMappingContext *InputMappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/Input/IMC_Player.IMC_Player"));
				if (InputMappingContext)
				{
					// Set the mapping context with a priority (e.g., 0)
					EnhancedInputSubsystem->AddMappingContext(InputMappingContext, 0);
				}
			}
		}
	}

	// Find the AAPackage actor in the level (you can replace AAPackage with the actual class name)
	TArray<AActor *> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAPackage::StaticClass(), FoundActors);

	// Assuming you have only one AAPackage actor in the level, you can set the reference
	if (FoundActors.Num() > 0)
	{
		AAPackageRef = Cast<AAPackage>(FoundActors[0]);
	}
	else
	{
		// Handle the case where AAPackage actor is not found
		UE_LOG(LogTemp, Error, TEXT("AAPackage actor not found in the level"));
	}
}

// Called every frame
void APPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FollowPackage();
}

void APPlayer::FollowPackage()
{
	if (AAPackageRef)
	{
		// Get the location of the AAPackage
		FVector TargetLocation = AAPackageRef->GetActorLocation();

		// Set the PPlayer's location to match the AAPackage's location
		SetActorLocation(TargetLocation);
	}
}

// Called to bind functionality to input
void APPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		const UInputAction *ClickAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_Click.IA_Click"));
		if (ClickAction)
		{
			EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &APPlayer::Click);
		}
	}
}

void APPlayer::Click()
{
	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		if (AActor *HitActor = HitResult.GetActor())
		{
			AAObstacle *HitObstacle = Cast<AAObstacle>(HitActor);
			if (HitObstacle)
			{
				HitObstacle->HandleClick();
				// DrawDebugSphere(GetWorld(), HitResult.Location, 25.0f, 12, FColor::Green, false, 1.0f);
			}
		}
	}
}