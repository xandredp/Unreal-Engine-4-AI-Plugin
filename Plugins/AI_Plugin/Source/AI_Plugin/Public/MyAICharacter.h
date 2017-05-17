// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI_Plugin/Private/AI_PluginPrivatePCH.h"
#include "MyAICharacter.generated.h"

UCLASS()
class AMyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyAICharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
