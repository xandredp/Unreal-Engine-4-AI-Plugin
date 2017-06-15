// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_PluginPrivatePCH.h"
#include "AI_Plugin.h"
#include "AICharacter.h"
#include "SoundBlockingActor.h"
#include "AICharacterController.h"


AAICharacter::AAICharacter()
{

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(40.0f);
	PawnSensingComp->SightRadius = 1500;
	PawnSensingComp->HearingThreshold = 600;
	PawnSensingComp->LOSHearingThreshold = 400;

	AIState = EBotBehaviorType::Neutral;

	bCanHear = true;
	bCanSee = true;
	SenseTimeOut = 2.5;
	DetectionMaxTime = 10.0f;
	bFirstTimeSeen = true;
	DebugDrawEnabled = false;
	YellForHelpOnContact = true;
}


// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	AiMesh = GetMesh();
	
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
				PawnSensingComp->OnHearNoise.AddDynamic(this, &AAICharacter::OnHearNoise);
		}
	}
	bSensedTarget = false;

	//The actor is going to be following
	if (AIFollwingPoints.Num() != 0)
	{

		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, TEXT("if"));
		//const FAttachmentTransformRules& attachmentrules(LocationRule, RotationRule, ScaleRule);
		for (int i = 0; i < AIFollwingPoints.Num(); i++)
		{
			GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, TEXT("for"));
			if (AIFollwingPoints[i]->IsValidLowLevel())
			{
				GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, TEXT("attach"));
				AIFollwingPoints[i]->AttachToComponent(AiMesh, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
			}
		}
	}

	if (AIFollowPoint)
	{
		AIFollowPoint->GetActorLocation();
		AIController->SetBlackboardFollwiongLocation(AIFollowPoint);
	}
}


void AAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	


	/*Time calculation to not set target*/
	if (bSensedTarget && (GetWorld()->TimeSeconds - LastSeenTime) > SenseTimeOut && (GetWorld()->TimeSeconds - LastHeardTime) > SenseTimeOut)
	{
		float a = GetWorld()->TimeSeconds - LastSeenTime;
		float b = SenseTimeOut;

		FString TheFloatStr = FString::SanitizeFloat(a);
		FString TheFloatStr1 = FString::SanitizeFloat(b);
		if (DebugDrawEnabled)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("UNDETECTED"));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TheFloatStr);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TheFloatStr1);
		}
		AAICharacterController* AIController = Cast<AAICharacterController>(GetController());
		if (AIController)
		{
			bSensedTarget = false;
			AIState = EBotBehaviorType::Neutral;
			AIController->SetBlackboardBotState(AIState);
			//Sensed the player

			AIController->SetTargetEnemy(nullptr);
			//resetvariableTo use in  OnseePlayer
			bFirstTimeSeen = true;
		}

	}

	
	if (bCanHear)
	{
		AAICharacterController* AIController = Cast<AAICharacterController>(GetController());
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

		if (PlayerCharacter && AIController)
		{
			// Define the parameters
			FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
			TraceParams.bTraceComplex = true;
			TraceParams.bTraceAsyncScene = true;
			TraceParams.bReturnPhysicalMaterial = true;

			// Re-Initialize hit info
			FHitResult Hit(ForceInit);

			// Define start point of the trace
			FVector Start = PlayerCharacter->GetActorLocation();
			
			//getplayercontrol->WasInputKeyJustPressed(EKeys::B)

			// Define end point of the trace
			APawn* AIPawn = AIController->GetPawn();
			FVector End = AIPawn->GetActorLocation();

			UCapsuleComponent* bob = this->GetCapsuleComponent();
			FVector CapStart = bob->GetComponentLocation();
			FString TheFloatStr = FString::SanitizeFloat(CapStart.X);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, "Capsule X=" + TheFloatStr);
			FRotator Rot = AIPawn->GetViewRotation();
			FVector ForwardVec = AIPawn->GetActorForwardVector();
			
			if (DebugDrawEnabled) 
			{			
				DrawDebugCone(GetWorld(), CapStart, ForwardVec, this->PawnSensingComp->SightRadius, (this->PawnSensingComp->GetPeripheralVisionAngle() * (3.14159265 / 180)), (this->PawnSensingComp->GetPeripheralVisionAngle() * (3.14159265 / 180)), 20, FColor::Purple, false, 1.0, 1, 1.0);
				DrawDebugSphere(GetWorld(), CapStart, this->PawnSensingComp->LOSHearingThreshold, 20, FColor::Yellow, false, 0.05, 0, 1.0f);
			}
		}
	}
}

void AAICharacter::OnSeePlayer(APawn* Pawn)
{	
	if (bFirstTimeSeen == true)
	{
		FirstSeenTime = GetWorld()->GetTimeSeconds();
		bFirstTimeSeen = false;
	}
	
	if (Health <= 0.0)
	{
		bIsAlive = false;
		return;
	}

	if (!bSensedTarget)
	{

	}
		/* Keep track of the time the player was last sensed in order to clear the target */
		LastSeenTime = GetWorld()->GetTimeSeconds();
		bSensedTarget = true;

		AAICharacterController* AIController = Cast<AAICharacterController>(GetController());
		ABaseCharacter* SensedPawn = Cast<ABaseCharacter>(Pawn);
		APawn* ThisAIPawn = AIController->GetPawn();



		if (AIController && SensedPawn)
		{

			FString TheFloatStr = FString::SanitizeFloat(LastSeenTime - FirstSeenTime);
			FString TheFloatStr1 = FString::SanitizeFloat(SensedPawn->ValToMakePawnUnDetected* DetectionMaxTime);//FString::SanitizeFloat(SensedPawn->ValToMakePawnUnDetected* DetectionMaxTime);
			if (DebugDrawEnabled)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SEEN"));
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TheFloatStr);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TheFloatStr1);
			}

			AIState = EBotBehaviorType::Suspicious;
			AIController->SetBlackboardBotState(AIState);
		//	AIController->SetTargetEnemy(SensedPawn);

			UCapsuleComponent* bob = this->GetCapsuleComponent();
			FVector ThisAILocation = bob->GetComponentLocation();

			//if the last time seen is bigger than maximun duration
			if (LastSeenTime - FirstSeenTime > SensedPawn->ValToMakePawnUnDetected* DetectionMaxTime)
			{
				if (DebugDrawEnabled)
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Following"));
				}
				
				/*FString TheFloatStr = FString::SanitizeFloat(LastSeenTime - FirstSeenTime);
				FString TheFloatStr1 = FString::SanitizeFloat(SensedPawn->ValToMakePawnUnDetected* DetectionMaxTime);
				
				*/

				AIState = EBotBehaviorType::Agression;
				AIController->SetBlackboardBotState(AIState);
				//Sensed the player
				AIController->SetTargetEnemy(SensedPawn);

				if (YellForHelpOnContact)
				{
					//if (DebugDrawEnabled)
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, AIController->GetName() + TEXT(" - I see the bastard - Form up on me you guys"));
					}
					for (TActorIterator<AAICharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
					{
						ActorItr->GetController()->GetName();

						AAICharacterController* AIController2 = Cast<AAICharacterController>(ActorItr->GetController());

						if (AIController2->GetName() == AIController->GetName())
						{
							//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ActorItr->GetName());
							// Skip me you plonker
						}
						else
						{
							// Dont override any "helping" that is already happening - this should stop a crazy swarm of dumbos from forming

							if (AIController2->GetAIState() == EBotBehaviorType::Helping)
							{
								// This AI is already Helping so skip
							}
							else
							{
								// Make sure the yell for help only works for a limited range

								FVector	ThisLocation = AIController2->GetCharacter()->GetActorLocation();

								float Length = (ThisLocation - ThisAILocation).Size();

								// it calculates MaxHearingRange using the range of the ears of the Listening AI not the ears of the Yelling AI LOSHearingThreshold

								float MaxHearingRange = ActorItr->PawnSensingComp->LOSHearingThreshold;
								if (DebugDrawEnabled)
								{
									GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Hearing test for " + ActorItr->GetName() + " : MaxHearingRange=" + FString::SanitizeFloat(MaxHearingRange) + " Length=" + FString::SanitizeFloat(Length));
								}
								if (Length > MaxHearingRange)
								{
									// Yelled but this AI is too far away to hear us
									if (DebugDrawEnabled)
									{
										GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, ActorItr->GetName() + " Too far to here me yell");
									}
								}
								else
								{
									//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, ActorItr->GetName());
									AIState = EBotBehaviorType::Helping;
									AIController2->SetBlackboardBotState(AIState);
									// Set the others to target my AI position
									AIController2->SetLeaderToHelp(ThisAIPawn);
								}

							}
						}
					}
				}
			}			
		}
		else
		{
			if (DebugDrawEnabled)
			{
				GLog->Log("Out of Seeing range");
			}
			AIState  = EBotBehaviorType::Neutral;
			AIController->SetBlackboardBotState(AIState);
			AIController->ResetSeenTarget();
		}


}


void AAICharacter::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (Health <= 0.0)
	{
		bIsAlive = false;
		return;
	}
	if (!bSensedTarget)
	{
	
	}

	UCapsuleComponent* bob = this->GetCapsuleComponent();
	FVector ThisAILocation = bob->GetComponentLocation();
	
	bSensedTarget = true;
	LastHeardTime = GetWorld()->GetTimeSeconds();

	AAICharacterController* AIController = Cast<AAICharacterController>(GetController());
	APawn* ThisAIPawn = AIController->GetPawn();

	if (AIController)
	{		
		//Check if there is blocking actor between the ai and player
		//if there is do nothing
		if (ASoundBlockingActor* blockingActor = GetSoundBlockingActorInView())
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, "Blocker is blocking the  Noise.");
		}
		//if there is nothing blocking in between assign the target enemy
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("AI detected a Noise!"));
			AIController->SetTargetEnemy(GetWorld()->GetFirstPlayerController()->GetPawn());
			AIState = EBotBehaviorType::Agression;
			AIController->SetBlackboardBotState(AIState);
		}

		if (YellForHelpOnContact)
		{
			if (DebugDrawEnabled)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, AIController->GetName() + TEXT(" - I hear the bastard - Form up on me you guys"));
			}
			for (TActorIterator<AAICharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				ActorItr->GetController()->GetName();

				AAICharacterController* AIController2 = Cast<AAICharacterController>(ActorItr->GetController());

				if (AIController2->GetName() == AIController->GetName())
				{
					//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ActorItr->GetName());
					// Skip me you plonker
				}
				else
				{
					// Dont override any "helping" that is already happening - this should stop a crazy swarm of dumbos from forming

					if (AIController2->GetAIState() == EBotBehaviorType::Helping)
					{
						// This AI is already Helping so skip
					}
					else
					{
						// Make sure the yell for help only works for a limited range

						FVector	ThisLocation = AIController2->GetCharacter()->GetActorLocation();

						float Length = (ThisLocation - ThisAILocation).Size();

						// it calculates MaxHearingRange using the range of the ears of the Listening AI not the ears of the Yelling AI LOSHearingThreshold

						float MaxHearingRange = ActorItr->PawnSensingComp->LOSHearingThreshold;
						if (DebugDrawEnabled)
						{
							GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Hearing test for " + ActorItr->GetName() + " : MaxHearingRange=" + FString::SanitizeFloat(MaxHearingRange) + " Length=" + FString::SanitizeFloat(Length));
						}
						if (Length > MaxHearingRange)
						{
							// Yelled but this AI is too far away to hear us
							if (DebugDrawEnabled)
							{
								GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, ActorItr->GetName() + " Too far to here me yell");
							}
						}
						else
						{
							//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, ActorItr->GetName());
							AIState = EBotBehaviorType::Helping;
							AIController2->SetBlackboardBotState(AIState);
							// Set the others to target my AI position
							AIController2->SetLeaderToHelp(ThisAIPawn);
						}

					}
				}
			}
		}
	}
}
ASoundBlockingActor* AAICharacter::GetSoundBlockingActorInView()
{// Define the parameters
	FCollisionQueryParams TraceParams(TEXT("TraceBlcokingActor"), true, this);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;

	/* Not tracing complex uses the rough collision instead making tiny objects easier to select. */
	TraceParams.bTraceComplex = false;

	AAICharacterController* AIController = Cast<AAICharacterController>(GetController());
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// Re-Initialize hit info
	FHitResult Hit(ForceInit);
	// Define start point of the trace
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	APawn* AIPawn = AIController->GetPawn();
	FVector AILocation = AIPawn->GetActorLocation();

//	Controller->GetPlayerViewPoint(CamLoc, CamRot);
	const FVector TraceStart = PlayerLocation;
	const FVector TraceEnd = AILocation;
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, TraceParams);
	if (DebugDrawEnabled)
	{
		DrawDebugLine(GetWorld(), TraceStart, Hit.TraceEnd, FColor::Green, true, 0.05f, 0.0f, 1.0f);
	}
	return Cast<ASoundBlockingActor>(Hit.GetActor());
}