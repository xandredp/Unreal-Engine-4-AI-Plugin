// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "TypeClass.h"
#include "MyTargetPoint.h"
#include "AIFollwingPoint.h"
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
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "AI")
		USkeletalMeshComponent* AiMesh;

	UPROPERTY(VisibleAnywhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TArray<AMyTargetPoint*> PatrolTargetPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		EBotBehaviorType AIState;

	/*Can The pawn hear?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bisLooping;

	/*Can The pawn hear?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bCanHear;

	/*Can The pawn See?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bCanSee;	/*Can The pawn See?*/


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool YellForHelpOnContact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool DebugDrawEnabled;

	/* Last time the player was spotted */
	float LastSeenTime;

	/* Last time the player was heard */
	float LastHeardTime;

	/* Last time we attacked something */
	float LastMeleeAttackTime;
	/* Bool to get time LastSeenTime - FirstSeenTime (during thhis period) to get the SeenTime 
	This is used to detect how hard it is to detect the player*/
	float FirstSeenTime;

	/* Bool to Check in Onseeplayer */
	bool bFirstTimeSeen;

	/* Maximum Timetaken to detect player This decides how fast enemy is Seen */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DetectionMaxTime;

	/* Time-out value to clear the sensed position of the player. 
	Should be higher than Sense interval in the PawnSense component not never miss sense ticks. 
	Once detectected duration of this much will be following the player*/
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float SenseTimeOut;

	/* Resets after sense time-out to avoid unnecessary clearing of target each tick */
	bool bSensedTarget;

	/*For follwing AI*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TArray<AAIFollwingPoint*> AIFollwingPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		AAIFollwingPoint* AIFollowPoint;

	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);

	UFUNCTION()
		void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
	
};
