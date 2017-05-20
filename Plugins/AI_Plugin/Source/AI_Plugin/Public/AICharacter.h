// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TypeClass.h"
#include "MyTargetPoint.h"
#include "Perception/PawnSensingComponent.h"
#include "BaseCharacter.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class AI_PLUGIN_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
		AAICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TArray<AMyTargetPoint*> PatrolTargetPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		EBotBehaviorType AIState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bIsFollwingTargetPointsUp;


	/* Last time the player was spotted */
	float LastSeenTime;

	/* Last time the player was heard */
	float LastHeardTime;

	/* Last time we attacked something */
	float LastMeleeAttackTime;

	/* Time-out value to clear the sensed position of the player. Should be higher than Sense interval in the PawnSense component not never miss sense ticks. */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float SenseTimeOut;

	/* Resets after sense time-out to avoid unnecessary clearing of target each tick */
	bool bSensedTarget;

	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);
	
};