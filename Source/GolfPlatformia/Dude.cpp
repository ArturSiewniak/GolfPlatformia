// Fill out your copyright notice in the Description page of Project Settings.


#include "Dude.h"

// Sets default values
ADude::ADude()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));

	VisibleComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetupAttachment(VisibleComponent);
	Camera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	SpringArmComponent->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 50.f), FRotator(-60.f, 0.f, 0.f));
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 3.f;
}

// Called when the game starts or when spawned
void ADude::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADude::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		CurrentVelocity = CurrentVelocity.GetSafeNormal() * MaxSpeed;

		FVector NewLocation = GetActorLocation();

		NewLocation += GetActorForwardVector() * CurrentVelocity.X * DeltaTime;

		NewLocation += GetActorRightVector() * CurrentVelocity.Y * DeltaTime;

		SetActorLocation(NewLocation);
	}

	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}

	//Rotate our camera's pitch, but limit it so we're always looking downward
	{
		FRotator NewRotation = SpringArmComponent->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
		SpringArmComponent->SetWorldRotation(NewRotation);
	}

	/*FRotator NewRotationYaw = GetActorRotation();
	NewRotationYaw.Yaw += CameraInput.X;
	SetActorRotation(NewRotationYaw);

	FRotator NewRotationPitch = SpringArm->GetComponentRotation();
	NewRotationPitch.Pitch = FMath::Clamp(NewRotationPitch.Pitch + CameraInput.Y, -80.f, -15.f);
	SpringArm->SetWorldRotation(NewRotationPitch);*/
}

// Called to bind functionality to input
void ADude::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Movement axes binding
	InputComponent->BindAxis("MoveForward", this, &ADude::MoveForward);
	InputComponent->BindAxis("Strafe", this, &ADude::Strafe);

	InputComponent->BindAxis("CameraYaw", this, &ADude::CameraYaw);
	InputComponent->BindAxis("CameraPitch", this, &ADude::CameraPitch);
}

void ADude::MoveForward(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.f, 1.f) * MaxSpeed;
}

void ADude::Strafe(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.f, 1.f) * MaxSpeed;
}

void ADude::CameraYaw(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void ADude::CameraPitch(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

