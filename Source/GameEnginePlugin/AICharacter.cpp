// Fill out your copyright notice in the Description page of Project Settings.

#include "GameEnginePlugin.h"
#include "AICharacter.h"


// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Addign the component class to the character
	MyAIComponent = CreateDefaultSubobject<UAIComponent>(TEXT("AIComponent"));

}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


