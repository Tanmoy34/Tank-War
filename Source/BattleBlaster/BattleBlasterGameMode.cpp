// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"

#include "Tower.h"
#include "Kismet/GameplayStatics.h"


void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATower::StaticClass(), Towers); 
	TowerCount = Towers.Num();
	UE_LOG(LogTemp, Warning, TEXT("TowerCount: %d"), TowerCount);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if (PlayerPawn)
	{
		Tank = Cast<ATank>(PlayerPawn);
	}
	
	int32 LoopIndex = 0;
	while (LoopIndex < TowerCount )
	{
		AActor* TowerActor =  Towers[LoopIndex];
		LoopIndex++;
		if (TowerActor)
		{
			ATower* Tower = Cast<ATower>(TowerActor);
			if (Tower && Tank)
			{
				Tower->Tank = Tank;
			}
		}
		
	}
}



void ABattleBlasterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		//Player Died

		Tank->HandleDestruction();
	}
	else
	{
		//ATower Died
		ATower* DeadTower = Cast<ATower>(DeadActor);
		if (DeadTower)
		{
			DeadTower->HandleDestruction();
			TowerCount--;
			
			if (TowerCount == 0)
			{
				UE_LOG(LogTemp,Display,TEXT("You Win"));
			}
			
		}
	}
}
