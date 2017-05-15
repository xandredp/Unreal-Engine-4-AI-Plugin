// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/***********************/
//DO NOT USE THIS CLASS
/***********************/

#include "GameFramework/Actor.h"
#include "MyPluginComponent.generated.h"

UCLASS(ClassGroup = (Custom))
class AI_PLUGIN_API AMyPluginComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPluginComponent();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
