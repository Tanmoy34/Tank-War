// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Tank.generated.h"

//Forworad Declare

class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;



UCLASS()
class BATTLEBLASTER_API ATank : public ABasePawn
{
	GENERATED_BODY()
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	
	
public:

	ATank();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Component
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	//Input
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	UInputMappingContext* DefaultMappingContext;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	UInputAction * MoveAction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	UInputAction * TurnAction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	UInputAction* FireAction;
	
	void MoveInput(const FInputActionValue& Value);

	void TurnInput(const FInputActionValue& Value);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	float Speed = 300.0f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	float TurnRate = 50.0f;


	
	
};
