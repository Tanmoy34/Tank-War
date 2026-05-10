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
	PlayerController= Cast<APlayerController>(Controller);
	if (PlayerController)
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
	SetPlayerEnable(false);
}



// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if(PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
		FVector ImpactPosition = HitResult.ImpactPoint;
		//DrawDebugSphere(GetWorld(),ImpactPosition,20,20,FColor::Red);
		RotateTurret(ImpactPosition);
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
		EIC->BindAction(FireAction,ETriggerEvent::Started,this,&ATank::Fire);
	}
}

void ATank::MoveInput(const FInputActionValue& Value)
{
	float Inputvalue =  Value.Get<float>();
	
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

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetPlayerEnable(false);
	IsAlive = false;
}

void ATank::SetPlayerEnable(bool Enabled)
{
	if (PlayerController)
	{
		if (Enabled)
        	{
        		EnableInput(PlayerController);
				
        	}
        	else
        	{
        		DisableInput( PlayerController );
        		
        	}
		PlayerController->bShowMouseCursor = Enabled;
	}
}




