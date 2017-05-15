// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AIComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_PLUGIN_API UAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Array of target points for patrolling
	UPROPERTY(Category = "AI Component|Patrolling points", EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> PatrollingPoints;

	// AI properties
	UPROPERTY(Category = "AI Component|AI unit properties", EditAnywhere, BlueprintReadWrite)
		bool Hearing;

	UPROPERTY(Category = "AI Component|AI unit properties", EditAnywhere, BlueprintReadWrite)
		bool Sight;
};
