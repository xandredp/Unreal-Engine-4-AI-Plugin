// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI_Plugin/Private/AI_PluginPrivatePCH.h"
#include "BaseCharacter.generated.h"

UCLASS()
class AI_PLUGIN_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

	UPROPERTY(EditDefaultsOnly, Category = "Condition")
		float Health;

	UPROPERTY(EditDefaultsOnly, Category = "Condition")
		float Stamina;

	UPROPERTY(EditDefaultsOnly, Category = "Condition")
		bool bIsAlive;
	
};
