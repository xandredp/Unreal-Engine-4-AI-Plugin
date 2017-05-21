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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	AAICharacterController* MyController = Cast<AAICharacterController>(OwnerComp.GetAIOwner());
	AAICharacter* MyAICharacter = Cast<AAICharacter>(OwnerComp.GetAIOwner());

	//if characterisvalid
	//1. Get the Set patrol points in Character-> TArray<AMyTargetPoint*> PatrolTargetPoints

	if(MyAICharacter)
	{
		MyAICharacter->AIState = EBotBehaviorType::Neutral;
		MyController->SetBlackboardBotState(MyAICharacter->AIState);


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
		////if Current Position is End position
		//else if (CurrentTargetPoint == AvailableTargetPoints[AvailableTargetPoints.Num() - 1])
		//{
		//	MyAICharacter->bIsFollwingTargetPointsUp = false;
		//}
		//else if (CurrentTargetPoint == AvailableTargetPoints[0])
		//{
		//	MyAICharacter->bIsFollwingTargetPointsUp = true;
		//}
		//else if (CurrentTargetPoint == NextTargetPoint)
		//{
		//	//if Direction is decided
		//	if (MyAICharacter->bIsFollwingTargetPointsUp == true)
		//	{
		//		for (int i = 0; i < AvailableTargetPoints.Num() - 1; i++)
		//		{
		//			if (CurrentTargetPoint == AvailableTargetPoints[i])
		//			{
		//				NextTargetPoint = AvailableTargetPoints[i - 1];
		//			}
		//		}
		//	}
		//	else if (MyAICharacter->bIsFollwingTargetPointsUp == false)
		//	{
		//		for (int i = 0; i < AvailableTargetPoints.Num() - 1; i++)
		//		{
		//			if (CurrentTargetPoint == AvailableTargetPoints[i])
		//			{
		//				NextTargetPoint = AvailableTargetPoints[i + 1];
		//			}
		//		}
		//	}
		//}
		
		
		CurrentTargetPoint = NextTargetPoint;

		MyController->SetCurrentWayPoint(CurrentTargetPoint);
		MyController->SetNextWayPoint(NextTargetPoint);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some Succeeded"));
		return EBTNodeResult::Succeeded;
	}
//	if ((MyController == nullptr) || (MyAICharacter == nullptr))
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some Fail!"));
		return EBTNodeResult::Failed;
	}
	
	//return EBTNodeResult::Succeeded;
}