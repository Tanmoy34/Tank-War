// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsulecomp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(Capsulecomp);
	BaseMash = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMash"));
	BaseMash->SetupAttachment(Capsulecomp);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMash);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::RotateTurret(FVector LookATTarget)
{
	FVector VectorToTarget =  LookATTarget - TurretMesh->GetComponentLocation();
	

	FRotator LookAtRotation = FRotator(0, VectorToTarget.Rotation().Yaw, 0);


	FRotator InterpolatedRotation = FMath::RInterpTo(TurretMesh->GetComponentRotation(),LookAtRotation,GetWorld()->GetDeltaSeconds(),10.f);
	TurretMesh->SetWorldRotation(InterpolatedRotation);
}

