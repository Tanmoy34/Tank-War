// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"





ATank::ATank()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComp->SetupAttachment(Capsulecomp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);


	
}




// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController= Cast<APlayerController>(Controller))
	{
		if (ULocalPlayer* LocalPlayer =  PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				Subsystem->AddMappingContext(DefaultMappingContext,0);
			}
		}
		
	}
}



// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
		FVector ImpactPosition = HitResult.ImpactPoint;
		DrawDebugSphere(GetWorld(),ImpactPosition,20,20,FColor::Red);
	}
	
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EIC =  Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC)
	{
		EIC->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ATank::MoveInput);
		EIC->BindAction(TurnAction,ETriggerEvent::Triggered,this,&ATank::TurnInput);
	}
}

void ATank::MoveInput(const FInputActionValue& Value)
{
	float Inputvalue =  Value.Get<float>();
	UE_LOG(LogTemp,Display,TEXT("Input: %f"),Inputvalue);
	FVector DeltaLocation = DeltaLocation.Zero();
	DeltaLocation.X = Speed * Inputvalue * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	AddActorLocalOffset(DeltaLocation,true);
}

void ATank::TurnInput(const FInputActionValue& Value)
{
	float Inputvalue =  Value.Get<float>();
	FRotator DeltaRotation = DeltaRotation.ZeroRotator;
	DeltaRotation.Yaw = Inputvalue * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	AddActorLocalRotation(DeltaRotation,true);
}


