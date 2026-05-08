// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	ATank* Tank;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="FireRange")
	float FireRange = 600.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="FireRange")
	float FireRate = 2.0f;
	
	void CheckFireCondition();

	bool InFireRange();

	void HandleDestruction();

	
	
};
