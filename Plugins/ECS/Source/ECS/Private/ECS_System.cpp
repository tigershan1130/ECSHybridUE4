// Fill out your copyright notice in the Description page of Project Settings.


#include "ECS_System.h"


// Sets default values
AECS_System::AECS_System()
{
 	// System's tick function will never be implemented.
	PrimaryActorTick.bCanEverTick = false; 

}

void AECS_System::Start_Implementation() 
{
	// C++ happens first.
	// then bp happens.

	//Zonemanager.getComponent<>
}

void AECS_System::Update_Implementation(float DeltaTime)
{
	// C++ happens first
	// then bp happens.

	if (ZoneManager)
	{
		std::vector<AECS_Entity*> result;

		if (ZoneManager->GetEntityWithComponent(CompClassType->GetName(), result))
		{
			Entities = result;

			// for Debug use only.
			/*for (int i = 0; i < Entities.size(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s Find Entities: %s"),*GetName(), *Entities[i]->GetName());
			}*/
		}
	}

}
