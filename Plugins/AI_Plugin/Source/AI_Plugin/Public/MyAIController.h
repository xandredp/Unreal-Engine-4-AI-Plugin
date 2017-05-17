// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI_Plugin/Private/AI_PluginPrivatePCH.h"
#include "MyAIController.generated.h"

UCLASS()
class AMyAIController : public AAIController
{
	GENERATED_BODY()

public:

	// Behavior tree component
	UBehaviorTreeComponent* BehaviorTreeComp;
	// Blackboard component reference
	UBlackboardComponent* BlackboardComp;
	
	// Blackboard Keys
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName LocationToGoKey;

	//UPROPERTY(EditDefaultsOnly, Category = "AI")
	//	TArray<AActor*> PatrolTargetPoints;

	virtual void Possess(APawn* Pawn) override;


	AMyAIController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	//FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() const { return PatrolTargetPoints; }
};
