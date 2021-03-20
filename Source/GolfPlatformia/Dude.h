// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Dude.generated.h"
UCLASS()
class GOLFPLATFORMIA_API ADude : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADude();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Input variables
	FVector CurrentVelocity;
	FVector CameraInput;
	UPROPERTY(EditAnywhere)
	float MaxSpeed = 500.f;

	//Input functions
	void MoveForward(float AxisValue);
	void Strafe(float AxisValue);
	void CameraYaw(float AxisValue);
	void CameraPitch(float AxisValue);

	UPROPERTY(EditAnywhere)
	USceneComponent* VisibleComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;
};
