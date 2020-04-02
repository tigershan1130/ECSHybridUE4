// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ECS_Entity.h"
#include "ECS_System.generated.h"

UCLASS()
class ECS_API AECS_System : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AECS_System();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* CompClassType;

	AECS_ZoneManager* ZoneManager;

	std::vector<AECS_Entity*> Entities;

	UFUNCTION(BlueprintCallable)
		void SetZoneManager(AECS_ZoneManager* zoneMgr)
	{
		ZoneManager = zoneMgr;
	}

	// start, initialization step.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Start();

	virtual void Start_Implementation();

	// Called every frame
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Update(float DeltaTime);

	virtual void Update_Implementation(float DeltaTime);


};
