// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_PluginPrivatePCH.h"
#include "AI_Plugin.h"
#include "BTTargetPointSelection.h"

#include "MyAICharacter.h"
#include "MyTargetPoint.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTargetPointSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	AMyAICharacter* AIChar = Cast<AMyAICharacter>(OwnerComp.GetAIOwner());

	// if the controller is valid 
	// 1. get blackboard component, and current point
	// 2. search for the next point thats different from the current one
	//if (AIChar)
	//{
	//	UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
	//	AMyTargetPoint* CurrentPoint = Cast<AMyTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

	//	TArray<AMyTargetPoint*> AvailableTargetPoints = AIChar->GetAvailableTargetPoints();

	//	AMyTargetPoint* NextTargetPoint = nullptr;
	//	
	//	// Index to find next patrol point
	//	int32 RandomIndex;
	//	
	//	do
	//	{
	//		RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num() - 1);
	//		//Remember that the Array provided by the Controller function contains AActor* objects so we need to cast.
	//		NextTargetPoint = Cast<AMyTargetPoint>(AvailableTargetPoints[RandomIndex]);
	//	} while (CurrentPoint == NextTargetPoint);

	//	// Udpate the next location in the blackboard 
	//	BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);
	//}

	if (AIChar)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		TArray<AMyTargetPoint*> AvailableTargetPoints = AIChar->GetAvailableTargetPoints();
		AMyTargetPoint* NextTargetPoint = Cast<AMyTargetPoint>(AvailableTargetPoints[0]);
		BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);

		return EBTNodeResult::Succeeded;
	}

		
	
	return EBTNodeResult::Failed;
}