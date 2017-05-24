// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AICharacter.h"
#include "MyTargetPoint.h"
#include "AIController.h"
#include "AICharacterController.generated.h"

/**
 * 
 */
UCLASS()
class AI_PLUGIN_API AAICharacterController : public AAIController
{
	GENERATED_BODY()

		AAICharacterController();

	/* Called whenever the controller possesses a character bot */


	// Behavior tree component
	UBehaviorTreeComponent* BehaviorTreeComp;
	// Blackboard component reference
	UBlackboardComponent* BlackboardComp;

	// Blackboard Keys

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName NextWaypointKeyName;
	//reference to player
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetEnemyKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName CurrentWaypointKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BotStateKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName IsArrayGoingUpKeyName;

public:
	//Track what current Patrol point AI Character is at. 
	int32 CurrentPatrolPoint;



public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Possess(class APawn* InPawn) override;

	//	virtual void UnPossess() override;

	AMyTargetPoint* GetCurrentWaypoint();
	AMyTargetPoint* GetNextWaypoint();
	EBotBehaviorType BlackboardBotState();
	bool GetIsArrayGoingUp();

	void SetCurrentWayPoint(AMyTargetPoint* NewWaypoint);
	void SetNextWayPoint(AMyTargetPoint* NewWaypoint);
	void SetTargetEnemy(APawn* NewTarget);
	void SetBlackboardBotState(EBotBehaviorType NewState);
	void SetBBIsArrayGoingUp(bool NewBool);

	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorTreeComp; }

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
};
