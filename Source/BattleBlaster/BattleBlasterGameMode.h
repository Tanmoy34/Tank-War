// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Programs/UnrealBuildAccelerator/Core/Public/UbaBase.h>

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tank.h"
#include "ScreenMassage.h"
#include "BattleBlasterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ABattleBlasterGameMode : public AGameModeBase
{
	GENERATED_BODY()

	

protected:
    	// Called when the game starts or when spawned
    	virtual void BeginPlay() override;
    
    	
    
    	
    	
public:
	
    	// Called every frame
    	virtual void Tick(float DeltaTime) override;

	ATank* Tank;

	//UI
	UPROPERTY(EditAnywhere ,Category="UI")
	TSubclassOf<UScreenMassage> ScreenMassageClass;

	UPROPERTY(VisibleAnywhere ,Category="UI")
	UScreenMassage* ScreenMassageWidget;
	
	UPROPERTY(VisibleAnywhere)
	int32 TowerCount;

	UPROPERTY(EditAnywhere)
	float GameOverTimer = 3.0f;

	UPROPERTY(EditAnywhere)
	int32 CountdownDelay = 3;

	int32 CountdownSeconds;

	FTimerHandle CountdownTimerHandle;
	
	bool IsGameOver = false;
	bool IsVictory = false;
	
	void ActorDied(AActor* DeadActor);

	void OnGameOverTimerTimeout();

	void OnCountdownTimerTimeout();
};
