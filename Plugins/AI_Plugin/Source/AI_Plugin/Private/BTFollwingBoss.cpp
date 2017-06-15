// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_PluginPrivatePCH.h"
#include "AI_Plugin.h"
#include "BTFollwingBoss.h"


#include "AICharacterController.h"
#include "AICharacter.h"
#include "AIFollwingPoint.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


EBTNodeResult::Type UBTFollwingBoss::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAICharacterController* MyController = Cast<AAICharacterController>(OwnerComp.GetAIOwner());
	AAICharacter* MyAICharacter = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());

	//if characterisvalid
	//1. Get the Set patrol points in Character-> TArray<AMyTargetPoint*> PatrolTargetPoints
	if (MyController)
	{
		MyAICharacter->AIState = EBotBehaviorType::Neutral;
		MyController->SetBlackboardBotState(MyAICharacter->AIState);
		//2. Get variables
		UBlackboardComponent* BlackboardComp = MyController->GetBlackboardComp();
		AAIFollwingPoint* AvailableAiFollowPoint;
		if (MyAICharacter->AIFollowPoint != nullptr)
		{
			AvailableAiFollowPoint = MyAICharacter->AIFollowPoint;
			MyController->SetBlackboardFollwiongLocation(AvailableAiFollowPoint);

		}
		


	

		return EBTNodeResult::Succeeded;
	}

	else
	{

		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}