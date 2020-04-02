// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "ECS_Entity.h"
#include "ECS_System.h"
#include "ECS_ZoneManager.generated.h"

UCLASS()
class ECS_API AECS_ZoneManager : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		TArray<TSubclassOf<AECS_System>> Systems;

private:

	// Holds: Entity List 
	std::vector<AECS_Entity*> Entities;

	// Holds: Component1 | {Entity1,Entity2,Entity3}
	//		  Component2 | {Entity1,Entity2}
	//        Component3 | {Entity2,Entity4}
	std::unordered_map<std::string, std::vector<AECS_Entity*>> CompEntityReferences;


public:
	// Sets default values for this actor's properties
	AECS_ZoneManager();


	//TODO: dynamically create snapshot from snapshot script.
	// this is a new feature allow we create objects from a script side of things.
	void GenerateSnapShot()
	{
		//TODO: 
		//	Component 信息可以从 Schema, XML 文件读取数据， 自动生成 各种Component 信息到Source/Public 文件底下
		//	并且在这里 读取  Snapshot.Schema 文件， 自动加载 各种Component 脚本。
		//	这里也有自动化读取Snapshot.Schema 并且AddComponent 的过程。

		//TODO: 
		// 注册component 1.
		// 注册component 2.
		// 注册component 3.

		// 注册方式细节： Entity->AddComponent
		//               更新CompEntityReferences

	}


	void GenerateSnapShotFromUE4()
	{
		// we go through al the AECS_Entity in the world.
		// then we go through each of those entity to get its component type by using UCLASS->GetName()
		// then we populate relationship between two data
		// one data is entity -> component relation table which is inside of each Entity as TMap
		// the other side of the asynchronous data is CompEntityReferences(Std::unorderedMap)
		// so when we add entity and deleting components and entities
		// we should update both of those data.
		for (TActorIterator<AECS_Entity> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			Entities.push_back(*ActorItr);

			TArray<FString> ComponentNames;

			ActorItr->AddECSComponent(ComponentNames);

			for (int i = 0; i < ComponentNames.Num(); i++)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Entity Name: %s | Actor Component Name: %s "), *(ActorItr->GetName()),  *(ComponentNames[i]));

				std::string STDstring(TCHAR_TO_UTF8(*ComponentNames[i]));

				std::unordered_map<std::string, std::vector<AECS_Entity*>>::const_iterator Found = CompEntityReferences.find(STDstring);

				if (Found != CompEntityReferences.end())
				{
					CompEntityReferences[STDstring].push_back(*ActorItr);
				}
				else
				{
					std::vector<AECS_Entity*> entityPtrs;

					entityPtrs.push_back(*ActorItr);

					CompEntityReferences.emplace(STDstring, entityPtrs);
				}
			}
		}// end for loop

		// for Debug use only.
		for (const auto& n : CompEntityReferences)
		{
			FString UE4String(n.first.c_str());
			UE_LOG(LogTemp, Warning, TEXT("Actor Component Name: %s "), *(UE4String));
			for (int i = 0; i < n.second.size(); i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("Entity Name: %s "), *(n.second[i]->GetName()));
			}
		}
	}

	// this will remove the entity referenced in ZoneManager.
	void RemoveEntityFromWorld(AECS_Entity* EntityToRemove)
	{
		//TODO: when removing entity, we have to get all components under this entity
		//      assuming entity's component length is N
		//      then the time for removing and updating the CompReference UnorderedMap is O(N)
		for (auto c : EntityToRemove->GetComponents())
		{
			UClass* type = c->GetClass();
			std::string STDstring(TCHAR_TO_UTF8(*(type->GetName())));

			for (int i = 0; i < CompEntityReferences[STDstring].size(); ++i)
			{
				if (CompEntityReferences[STDstring][i] == EntityToRemove)
				{
					CompEntityReferences[STDstring].erase(CompEntityReferences[STDstring].begin() + i, CompEntityReferences[STDstring].begin() + i + 1);
					break;
				}
			}
		}
		for (int j = 0; j < Entities.size(); ++j)
		{
			if (Entities[j] == EntityToRemove)
			{
				Entities.erase(Entities.begin() + j, Entities.begin() + j + 1);
				break;
			}
		}
		EntityToRemove->Destroy();
	}

	// Get Entities from Component Names.
	bool GetEntityWithComponent(FString className, std::vector<AECS_Entity*>& entities)
	{
		//FString className = classType->GetName();

		std::string STDString(TCHAR_TO_UTF8(*className));

		std::unordered_map<std::string, std::vector<AECS_Entity*>>::const_iterator Found = CompEntityReferences.find(STDString);

		if (Found == CompEntityReferences.end())
		{
			return false;
		}

		entities = CompEntityReferences[STDString];

		return true;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
