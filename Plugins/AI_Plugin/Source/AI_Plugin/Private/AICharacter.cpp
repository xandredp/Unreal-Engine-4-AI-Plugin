// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_PluginPrivatePCH.h"
#include "AI_Plugin.h"
#include "AICharacter.h"

#include "AICharacterController.h"


AAICharacter::AAICharacter()
{

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(20.0f);
	PawnSensingComp->SightRadius = 500;
	PawnSensingComp->HearingThreshold = 600;
	PawnSensingComp->LOSHearingThreshold = 600;

	AIState = EBotBehaviorType::Neutral;

	bCanHear = true;
	bCanSee = true;
	SenseTimeOut = 2.5;
	DetectionMaxTime = 10.0f;
	bFirstTimeSeen = true;
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
				PawnSensingComp->OnHearNoise.AddDynamic(this, &AAICharacter::OnHearNoise);
		}
	}
	bSensedTarget = false;
}


void AAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);



	if (bSensedTarget && (GetWorld()->TimeSeconds - LastSeenTime) > SenseTimeOut && (GetWorld()->TimeSeconds - LastHeardTime) > SenseTimeOut)
	{
		float a = GetWorld()->TimeSeconds - LastSeenTime;
		float b = SenseTimeOut;

		FString TheFloatStr = FString::SanitizeFloat(a);
		FString TheFloatStr1 = FString::SanitizeFloat(b);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("UNDETECTED"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TheFloatStr);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TheFloatStr1);

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
			APawn* AIPawn = AIController->GetControlledPawn();
			FVector End = AIPawn->GetActorLocation();

			UCapsuleComponent* bob = this->GetCapsuleComponent();
			FVector CapStart = bob->GetComponentLocation();
			


			FString TheFloatStr = FString::SanitizeFloat(CapStart.X);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, "Capsule X=" + TheFloatStr);

			FRotator Rot = AIPawn->GetViewRotation();
			
			FVector ForwardVec = AIPawn->GetActorForwardVector();
			

			// The line trace function
			GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, TraceParams);
			DrawDebugLine(GetWorld(), Start, Hit.TraceEnd, FColor::Red, true, 0.05f, 0.0f, 2.0f);

			DrawDebugCone(GetWorld(), CapStart, ForwardVec, this->PawnSensingComp->SightRadius, (this->PawnSensingComp->GetPeripheralVisionAngle() * (3.14159265/180)), (this->PawnSensingComp->GetPeripheralVisionAngle() * (3.14159265 / 180)), 20, FColor::Purple, false, 1.0, 1, 2.0);
			DrawDebugSphere(GetWorld(), CapStart, this->PawnSensingComp->LOSHearingThreshold, 20, FColor::Yellow, false, 0.05, 0, 0.2);
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


		if (AIController && SensedPawn)
		{
			FString TheFloatStr = FString::SanitizeFloat(LastSeenTime - FirstSeenTime);
			FString TheFloatStr1 = FString::SanitizeFloat(SensedPawn->ValToMakePawnUnDetected* DetectionMaxTime);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SEEN"));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TheFloatStr);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TheFloatStr1);
			//delays the  time to assign the target
			if (LastSeenTime - FirstSeenTime > SensedPawn->ValToMakePawnUnDetected* DetectionMaxTime)
			{
				FString TheFloatStr = FString::SanitizeFloat(LastSeenTime - FirstSeenTime);
				FString TheFloatStr1 = FString::SanitizeFloat(SensedPawn->ValToMakePawnUnDetected* DetectionMaxTime);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Following"));
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TheFloatStr);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TheFloatStr1);

				AIState = EBotBehaviorType::Agression;
				AIController->SetBlackboardBotState(AIState);
				//Sensed the player
				AIController->SetTargetEnemy(SensedPawn);
			}
			
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

	
	bSensedTarget = true;
	LastHeardTime = GetWorld()->GetTimeSeconds();

	AAICharacterController* AIController = Cast<AAICharacterController>(GetController());

	if (AIController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("AI Hearing!"));

		AIController->SetTargetEnemy(PawnInstigator);
	}
}
