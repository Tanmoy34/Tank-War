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
	
}




void ABattleBlasterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
