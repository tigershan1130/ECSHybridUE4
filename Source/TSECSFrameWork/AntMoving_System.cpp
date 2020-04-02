// Fill out your copyright notice in the Description page of Project Settings.


#include "AntMoving_System.h"
#include "AntComponent.h"

void AAntMoving_System::Start_Implementation()
{
	Super::Start_Implementation();

	CompClassType = UAntComponent::StaticClass();
}

void AAntMoving_System::Update_Implementation(float DeltaTime)
{
	Super::Update_Implementation(DeltaTime);

	for (AECS_Entity* entity : Entities)
	{
		entity->AddActorWorldOffset(FRandomStream().GetUnitVector());
	}
}
