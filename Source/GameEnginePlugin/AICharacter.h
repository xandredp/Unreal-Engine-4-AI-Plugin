// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyPluginComponent.h"
#include "AICharacter.generated.h"

UCLASS()
class GAMEENGINEPLUGIN_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	AMyPluginComponent* MyPluginComponent;

	// Array of target points for patrolling
	UPROPERTY(EditAnywhere, Category = "Patrolling points")
		TArray<AActor*> PatrollingPoints;

	// AI properties
	UPROPERTY(EditAnywhere, Category = "AI unit properties")
		bool Hearing;

	UPROPERTY(EditAnywhere, Category = "AI unit properties")
		bool Sight;

public:
	// Sets default values for this character's properties
	AAICharacter();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

};
