// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_PluginPrivatePCH.h"
#include "AI_Plugin.h"
#include "AICharacter.h"

#include "AICharacterController.h"


AAICharacter::AAICharacter()
{

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	PawnSensingComp->SightRadius = 2000;
	PawnSensingComp->HearingThreshold = 600;
	PawnSensingComp->LOSHearingThreshold = 1200;

	AIState = EBotBehaviorType::Neutral;

	bCanHear = true;
	bCanSee = true;
}


// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	AAICharacterController* AIController = Cast<AAICharacterController>(GetController());
	if (AIController)
	{	/*SetBalckboardData*/
		AIState = EBotBehaviorType::Neutral;
		AIController->SetBlackboardBotState(AIState);
		AIController->SetBBIsArrayGoingUp(true);
	}

	if (PawnSensingComp)
	{
		if (bCanSee)
		{
			PawnSensingComp->OnSeePawn.AddDynamic(this, &AAICharacter::OnSeePlayer);
		}
		if (bCanHear)
		{
			//	PawnSensingComp->OnHearNoise.AddDynamic(this, &AAICharacterController::OnHearNoise);
		}
	}
}

void AAICharacter::OnSeePlayer(APawn* Pawn)
{

	
	if (Health <= 0.0)
	{
		return;
		bIsAlive = false;
	}

	if (!bSensedTarget)
	{

	}

	/* Keep track of the time the player was last sensed in order to clear the target */
	LastSeenTime = GetWorld()->GetTimeSeconds();
	bSensedTarget = true;

	AAICharacterController* AIController = Cast<AAICharacterController>(GetController());
	ACharacter* SensedPawn = Cast<ACharacter>(Pawn);
	if (AIController && SensedPawn)
	{
		AIState = EBotBehaviorType::Agression;
		AIController->SetBlackboardBotState(AIState);
		//Sensed the player
		AIController->SetTargetEnemy(SensedPawn);
	}

	
}
