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
#include "Runtime/Engine/Classes/Engine/Engine.h"


EBTNodeResult::Type UBTTargetPointSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAICharacterController* MyController = Cast<AAICharacterController>(OwnerComp.GetAIOwner());
	AAICharacter* MyAICharacter = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());

	//if characterisvalid
	//1. Get the Set patrol points in Character-> TArray<AMyTargetPoint*> PatrolTargetPoints
	if(MyController)
	{
		MyAICharacter->AIState = EBotBehaviorType::Neutral;
		MyController->SetBlackboardBotState(MyAICharacter->AIState);

		//2. Get variables
		UBlackboardComponent* BlackboardComp = MyController->GetBlackboardComp();
		TArray<AMyTargetPoint*> AvailableTargetPoints = MyAICharacter->PatrolTargetPoints;

		AMyTargetPoint* CurrentTargetPoint = MyController->GetCurrentWaypoint();
		AMyTargetPoint* NextTargetPoint = MyController->GetNextWaypoint();
		bool bIsFollwingTargetPointsUp = MyController->GetIsArrayGoingUp();
		// 3. Check Current Target Points and set the direction 
		// if points up is true climb up the array if false climb down the array
		int intdex = AvailableTargetPoints.Num();

		if (CurrentTargetPoint == nullptr)
		{
			
			int32 RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num() - 1);
			NextTargetPoint = AvailableTargetPoints[RandomIndex];
		}
		//if Current Position is End position
		else if (CurrentTargetPoint == AvailableTargetPoints[AvailableTargetPoints.Num() - 1])
		{
			bIsFollwingTargetPointsUp = false;
			MyController->SetBBIsArrayGoingUp(bIsFollwingTargetPointsUp);
		}
		else if (CurrentTargetPoint == AvailableTargetPoints[0])
		{
			bIsFollwingTargetPointsUp = true;
			MyController->SetBBIsArrayGoingUp(bIsFollwingTargetPointsUp);
		}

		if (AvailableTargetPoints.Num() > 1)
		{
			for (int i = 0; i < AvailableTargetPoints.Num(); i++)
			{
				if (CurrentTargetPoint == AvailableTargetPoints[i])
				{
					if (bIsFollwingTargetPointsUp == false)
					{
						NextTargetPoint = AvailableTargetPoints[i - 1];
						break;
					}
					if (bIsFollwingTargetPointsUp == true)
					{
						NextTargetPoint = AvailableTargetPoints[i+1];
						break;
					}		
				}
			}
		}


		//	//if Direction is decided
		//	if (MyAICharacter->bIsFollwingTargetPointsUp == true)
		//	{
		//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("InloopTrue!"));
		//		for (int i = 0; i < AvailableTargetPoints.Num() - 1; i++)
		//		{
		//			if (CurrentTargetPoint == AvailableTargetPoints[i])
		//			{
		//				NextTargetPoint = AvailableTargetPoints[i + 1];
		//				break;
		//			}
		//		}
		//	}
		//	else if (MyAICharacter->bIsFollwingTargetPointsUp == false)
		//	{
		//		
		//		for (int i = 0; i < AvailableTargetPoints.Num() - 1; i++)
		//		{
		//			if (CurrentTargetPoint == AvailableTargetPoints[i])
		//			{
		//				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("InloopFalse!"));

		//				NextTargetPoint = AvailableTargetPoints[0];
		//				break;
		//			}
		//		}
		//	}
		//}
		
		
		CurrentTargetPoint = NextTargetPoint;

		MyController->SetCurrentWayPoint(CurrentTargetPoint);
		MyController->SetNextWayPoint(NextTargetPoint);

		return EBTNodeResult::Succeeded;
	}

	else
	{

		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Failed;
}