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
	AIStateKeyName = "AIState";
	IsArrayGoingUpKeyName = "IsArrayGoingUp";
	LeaderToHelpKeyName = "LeaderToHelp";
	LeaderFollwiongLocationKeyName = "LeaderFollowingPoint";

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

	 AICharacter = Cast<AAICharacter>(aPawn);

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
	else if (NewState == EBotBehaviorType::Helping)
	{
		CurrentState = "Helping";
	}

	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsName(AIStateKeyName, CurrentState);
	}
}

bool AAICharacterController::GetIsArrayGoingUp()
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(IsArrayGoingUpKeyName);
	}
	return false;
}

EBotBehaviorType AAICharacterController::GetAIState()
{
	EBotBehaviorType ReturnState = EBotBehaviorType::Neutral;
	if (BlackboardComp)
	{
		FString CurrentState = BlackboardComp->GetValueAsString(AIStateKeyName);
		if (CurrentState == "Neutral") { ReturnState = EBotBehaviorType::Neutral; }
		if (CurrentState == "Suspicious") { ReturnState = EBotBehaviorType::Suspicious; }
		if (CurrentState == "Flee") { ReturnState = EBotBehaviorType::Flee; }
		if (CurrentState == "Agression") { ReturnState = EBotBehaviorType::Agression; }
		if (CurrentState == "Helping") { ReturnState = EBotBehaviorType::Helping; }
	}
	return ReturnState;
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

		if (NewTarget == nullptr)
		{
			AICharacter->bChasingEnemy = false;
		}
		else
		{
			AICharacter->bChasingEnemy = true;
		}
	}
}

void AAICharacterController::SetLeaderToHelp(APawn * NewTarget)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(LeaderToHelpKeyName, NewTarget);
	}
}

void AAICharacterController::ResetSeenTarget()
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TargetEnemyKeyName, nullptr);
	}
}


void AAICharacterController::SetBBIsArrayGoingUp(bool NewBool)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(IsArrayGoingUpKeyName, NewBool);
	}
}
void AAICharacterController::SetBlackboardFollwiongLocation(AAIFollwingPoint* NewFollowingPoint)
{
	if (BlackboardComp)
	{
		NewFollowingPoint->GetActorLocation();
		BlackboardComp->SetValueAsVector(LeaderFollwiongLocationKeyName, NewFollowingPoint->GetActorLocation());
			//SetValueAsObject(LeaderFollwiongLocationKeyName, NewFollowingPoint);
	}
}