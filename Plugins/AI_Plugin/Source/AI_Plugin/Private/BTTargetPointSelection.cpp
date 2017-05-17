// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_PluginPrivatePCH.h"
#include "AI_Plugin.h"
#include "BTTargetPointSelection.h"

#include "MyTargetPoint.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTargetPointSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	// if the controller is valid 
	// 1. get blackboard component, and current point
	// 2. search for the next point thats different from the current one
	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		AMyTargetPoint* CurrentPoint = Cast<AMyTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailableTargetPoints = AICon->GetAvailableTargetPoints();

		// Index to find next patrol point
		//int32 PatrolIndex;

		// move from point to point in order 
		//CurrentPoint = AICon->PatrolTargetPoints[0];

		// Udpate the next location in the blackboard 
		//BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}