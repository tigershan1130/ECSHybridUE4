// This is used to store data only, not used with hybrid ECS.
// all auto script generated data should inherit this Component class.

#pragma once

#include "CoreMinimal.h"
#include "ECS_ZoneManager.h"
#include "Components/ActorComponent.h"
#include "ECS_Component.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECS_API UECS_Component : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UECS_Component();
};

