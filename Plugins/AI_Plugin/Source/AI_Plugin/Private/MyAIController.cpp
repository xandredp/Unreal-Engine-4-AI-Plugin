// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_PluginPrivatePCH.h"
#include "AI_Plugin.h"
#include "MyAIController.h"

#include "MyAICharacter.h"
#include "MyTargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AMyAIController::AMyAIController()
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	// Initialize blackboard keys
	LocationToGoKey = "LocationToGo";
}

void AMyAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	AMyAICharacter* AIChar = Cast<AMyAICharacter>(Pawn);

	if (AIChar)
	{
		//If the blackboard is valid initialize the blackboard for the corresponding behavior tree
		if (AIChar->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AIChar->BehaviorTree->BlackboardAsset));
		}

		// Populate array of target points
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyTargetPoint::StaticClass(), PatrolTargetPoints);

		//Start the behavior tree which corresponds to the specific character
		BehaviorTreeComp->StartTree(*AIChar->BehaviorTree);
	}
}