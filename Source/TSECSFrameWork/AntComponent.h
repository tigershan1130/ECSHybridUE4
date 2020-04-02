// Fill out your copyright notice in the Description page of Project Settings.
// TODO: This is auto generated later on 
#pragma once

#include "CoreMinimal.h"
#include "ECS_Component.h"
#include "AntComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TSECSFRAMEWORK_API UAntComponent : public UECS_Component
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite)
	int32 hp;
};
