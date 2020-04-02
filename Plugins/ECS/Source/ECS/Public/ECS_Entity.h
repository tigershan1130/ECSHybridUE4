// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <unordered_map>
#include <typeindex>
#include <vector>
#include "ECS_Entity.generated.h"

typedef std::type_index TypeIndex;

template<typename T> TypeIndex getTypeIndex()
{
	return std::typeindex(typeid(T));
}

UCLASS(Blueprintable)
class ECS_API AECS_Entity : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AECS_Entity()
	{
		PrimaryActorTick.bCanEverTick = false;
	}

	// this will create component into 
	void AddECSComponent(TArray<FString>& UniqueComponentNames)
	{
		for (auto c : GetComponents())
		{
			UClass* type = c->GetClass();

			FString cName;
			
			UActorComponent* wr = Cast<UActorComponent>(c);
		
			if (wr)		
			{
				//UE_LOG(LogTemp, Warning, TEXT("Actor Component Name: %s "), *(type->GetName()));

				components.Add(type->GetName(), wr);

				UniqueComponentNames.Add(type->GetName());
			}
		}
	}

private:

	TMap<FString, UActorComponent*> components;	
};
