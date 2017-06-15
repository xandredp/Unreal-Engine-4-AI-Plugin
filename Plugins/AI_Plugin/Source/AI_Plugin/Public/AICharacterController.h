// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AICharacter.h"
#include "MyTargetPoint.h"
#include "AIFollwingPoint.h"
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
		FName LeaderToHelpKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName NextWaypointKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetEnemyKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName CurrentWaypointKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName AIStateKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName IsArrayGoingUpKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName LeaderFollwiongLocationKeyName;


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

	bool GetIsArrayGoingUp();

	EBotBehaviorType GetAIState();
	UFUNCTION(BlueprintCallable, Category = "BlackBoard")

	void SetCurrentWayPoint(AMyTargetPoint* NewWaypoint);
	void SetNextWayPoint(AMyTargetPoint* NewWaypoint);
	void SetTargetEnemy(APawn* NewTarget);
	void SetLeaderToHelp(APawn * NewTarget);
	void SetBlackboardBotState(EBotBehaviorType NewState);
	void SetBlackboardFollwiongLocation(AAIFollwingPoint* NewFollowingPoint);


	void ResetSeenTarget();
	void SetBBIsArrayGoingUp(bool NewBool);

	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorTreeComp; }
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
};
