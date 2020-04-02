// Fill out your copyright notice in the Description page of Project Settings.


#include "ECS_ZoneManager.h"

// Sets default values
AECS_ZoneManager::AECS_ZoneManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AECS_ZoneManager::BeginPlay()
{
	Super::BeginPlay();

	// Get reference of Component and its related entities.	
	GenerateSnapShotFromUE4();

	UWorld* const World = GetWorld();

	// generate systems with each System.
	if (World)
	{
		for (int i = 0; i < Systems.Num(); i++)
		{		
			auto system = GetWorld()->SpawnActor(Systems[i].Get());

			Systems[i].GetDefaultObject()->SetZoneManager(this);

			Systems[i].GetDefaultObject()->Start();
		}
	}
}

// Called every frame
void AECS_ZoneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	for(int i = 0; i < Systems.Num(); i++)
	{		
		Systems[i].GetDefaultObject()->Update(DeltaTime);
	}
	
}

