// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TypeClass.h"
#include "MyTargetPoint.h"
#include "AI_Plugin/Private/AI_PluginPrivatePCH.h"
#include "MyAICharacter.generated.h"

UCLASS()
class AMyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyAICharacter();


	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TArray<AMyTargetPoint*> PatrolTargetPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		EBotBehaviorType EnemyState;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE TArray<AMyTargetPoint*> GetAvailableTargetPoints() const { return PatrolTargetPoints; }
	
};
