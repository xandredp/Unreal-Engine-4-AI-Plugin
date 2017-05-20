// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_PluginPrivatePCH.h"
#include "AI_Plugin.h"
#include "BTTargetPointSelection.h"

#include "AICharacterController.h"
#include "AICharacter.h"
#include "MyTargetPoint.h"


/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


EBTNodeResult::Type UBTTargetPointSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAICharacterController* MyController = Cast<AAICharacterController>(OwnerComp.GetAIOwner());
	AAICharacter* MyAICharacter = Cast<AAICharacter>(OwnerComp.GetAIOwner());

	MyAICharacter->AIState = EBotBehaviorType::Neutral;
	MyController->SetBlackboardBotState(MyAICharacter->AIState);
	//if characterisvalid
	//1. Get the Set patrol points in Character-> TArray<AMyTargetPoint*> PatrolTargetPoints

	if(MyAICharacter)
	{
		//2. Get variables
		UBlackboardComponent* BlackboardComp = MyController->GetBlackboardComp();
		TArray<AMyTargetPoint*> AvailableTargetPoints = MyAICharacter->PatrolTargetPoints;

		AMyTargetPoint* CurrentTargetPoint = MyController->GetCurrentWaypoint();
		AMyTargetPoint* NextTargetPoint = MyController->GetNextWaypoint();
		bool bIsPositionSet = false;
		// 3. Check Current Target Points and set the direction 
		// if points up is true climb up the array if false climb down the array
		
		if (CurrentTargetPoint == nullptr)
		{
			int32 RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num() - 1);
			NextTargetPoint = AvailableTargetPoints[RandomIndex];
		}
		//if Current Position is End position
		else if (CurrentTargetPoint == AvailableTargetPoints[AvailableTargetPoints.Num() - 1])
		{
			MyAICharacter->bIsFollwingTargetPointsUp = false;
		}
		else if (CurrentTargetPoint == AvailableTargetPoints[0])
		{
			MyAICharacter->bIsFollwingTargetPointsUp = true;
		}
		else if (CurrentTargetPoint == NextTargetPoint)
		{
			//if Direction is decided
			if (MyAICharacter->bIsFollwingTargetPointsUp == true)
			{
				for (int i = 0; i < AvailableTargetPoints.Num() - 1; i++)
				{
					if (CurrentTargetPoint == AvailableTargetPoints[i])
					{
						NextTargetPoint = AvailableTargetPoints[i - 1];
					}
				}
			}
			else if (MyAICharacter->bIsFollwingTargetPointsUp == false)
			{
				for (int i = 0; i < AvailableTargetPoints.Num() - 1; i++)
				{
					if (CurrentTargetPoint == AvailableTargetPoints[i])
					{
						NextTargetPoint = AvailableTargetPoints[i + 1];
					}
				}
			}
		}
		
		
		CurrentTargetPoint = NextTargetPoint;

		MyController->SetCurrentWayPoint(CurrentTargetPoint);
		MyController->SetNextWayPoint(NextTargetPoint);

		return EBTNodeResult::Succeeded;
	}
//	if ((MyController == nullptr) || (MyAICharacter == nullptr))
	else
	{
		return EBTNodeResult::Failed;
	}
	

}