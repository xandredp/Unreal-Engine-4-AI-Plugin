// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_PluginPrivatePCH.h"
#include "AI_Plugin.h"
#include "AICharacterController.h"


#include "AICharacter.h"
#include "MyTargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BehaviorTree.h"

AAICharacterController::AAICharacterController()
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	// Initialize blackboard keys
	NextWaypointKeyName = "NextWayPoint";
	TargetEnemyKeyName = "TargetEnemy";
	CurrentWaypointKeyName = "CurrentWayPoint";
	BotStateKeyName = "BotState";


	/* Initializes PlayerState so we can assign a team index to AI */
	CurrentPatrolPoint = 0;
	bWantsPlayerState = true;
}
// Called when the game starts or when spawned
void AAICharacterController::BeginPlay()
{
	Super::BeginPlay();

}
void AAICharacterController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

	AAICharacter* AICharacter = Cast<AAICharacter>(aPawn);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*AICharacter->BehaviorTree->BlackboardAsset);

			/* Make sure the Blackboard has the type of bot we possessed */
			SetBlackboardBotState(AICharacter->AIState);
		}

		///*Populate patrol opint array to PatrolPoints*/
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyTargetPoint::StaticClass(), PatrolPoints);

		BehaviorTreeComp->StartTree(*AICharacter->BehaviorTree);
	}
}

AMyTargetPoint * AAICharacterController::GetCurrentWaypoint()
{
	if (BlackboardComp)
	{
		return Cast<AMyTargetPoint>(BlackboardComp->GetValueAsObject(CurrentWaypointKeyName));
	}
	return nullptr;
}
AMyTargetPoint * AAICharacterController::GetNextWaypoint()
{
	if (BlackboardComp)
	{
		return Cast<AMyTargetPoint>(BlackboardComp->GetValueAsObject(NextWaypointKeyName));
	}
	return nullptr;
}

EBotBehaviorType AAICharacterController::BlackboardBotState()
{
	EBotBehaviorType CurrentState = EBotBehaviorType::Neutral;
	if (BlackboardComp)
	{
		FName CurrentStateInBlackBoard = BlackboardComp->GetValueAsName(BotStateKeyName);
		if (CurrentStateInBlackBoard == "Neutral")
		{
			CurrentState = EBotBehaviorType::Neutral;
		}
		else if (CurrentStateInBlackBoard == "Suspicious")
		{
			CurrentState = EBotBehaviorType::Suspicious;
		}
		else if (CurrentStateInBlackBoard == "Flee")
		{
			CurrentState = EBotBehaviorType::Flee;
		}
		else if (CurrentStateInBlackBoard == "Agression")
		{
			CurrentState = EBotBehaviorType::Agression;
		}
		return CurrentState;
	}
	return CurrentState;
}


void AAICharacterController::SetCurrentWayPoint(AMyTargetPoint * NewWaypoint)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(CurrentWaypointKeyName, NewWaypoint);
	}
}
void AAICharacterController::SetNextWayPoint(AMyTargetPoint * NewWaypoint)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(NextWaypointKeyName, NewWaypoint);
	}
}
void AAICharacterController::SetTargetEnemy(APawn * NewTarget)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TargetEnemyKeyName, NewTarget);
	}
}

void AAICharacterController::SetBlackboardBotState(EBotBehaviorType NewState)
{
	FName CurrentState = "NULL";

	if (NewState == EBotBehaviorType::Neutral)
	{
		CurrentState = "Neutral";

	}
	else if (NewState == EBotBehaviorType::Suspicious)
	{
		CurrentState = "Suspicious";
	}
	else if (NewState == EBotBehaviorType::Flee)
	{
		CurrentState = "Flee";
	}
	else if (NewState == EBotBehaviorType::Agression)
	{
		CurrentState = "Agression";
	}


	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsName(BotStateKeyName, CurrentState);
	}
}
