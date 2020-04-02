// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ECS_System.h"
#include "AntMoving_System.generated.h"

/**
 *
 */
UCLASS()
class TSECSFRAMEWORK_API AAntMoving_System : public AECS_System
{
	GENERATED_BODY()

public:
	void Start_Implementation() override;

	void Update_Implementation(float DeltaTime) override;

};
