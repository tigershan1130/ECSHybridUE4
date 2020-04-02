// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include <unordered_map>
#include "ECS_System.h"
#include "ECS_Entity.h"
#include "CoreMinimal.h"

/**
 * 
 */
class ECS_API ECS_Core
{
public:
	ECS_Core()
	{
		// Find all world 

	}


	~ECS_Core()
	{



	}

	// Create Entity ID
	uint64 CreateEntityID()
	{
		return currentID++;
	}

	void Update()
	{


	}


private:

	uint64 currentID = 0;
	

protected:

	// here we should hold list of entities
	// here we should hold list of components for each entities
	std::vector<AECS_Entity*> entities;
	

};
